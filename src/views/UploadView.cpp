#include "UploadView.hpp"
#include "EditorView.hpp"
#include "giomm/liststore.h"
#include "glibmm/ustring.h"
#include "gtkmm/button.h"
#include "gtkmm/error.h"
#include "gtkmm/filedialog.h"
#include "gtkmm/image.h"
#include "gtkmm/label.h"
#include "models/FileModel.hpp"
#include <iostream>
UploadView::UploadView(Gtk::Window &parentWindow, const std::string id)
    : parentWindow(parentWindow), browseFilesButton("Browse Files"), id(id) {
  set_name("upload-view");

  // If not files in the category, render the empty state
  lockIcon = std::make_shared<Gtk::Image>("../assets/upload-icon.png");
  lockIcon->set_pixel_size(132);
  fileLabel.set_text("Start by uploading some files!");
  fileLabel.add_css_class("muted-label");

  browseFilesButton.set_cursor("pointer");

  browseFilesButton.set_hexpand(false);
  browseFilesButton.set_size_request(10, -1);
  browseFilesButton.set_vexpand(false);
  browseFilesButton.signal_clicked().connect(
      sigc::mem_fun(*this, &UploadView::onBrowseFilesButtonClicked));

  emptyWrapperBox.attach(*lockIcon, 0, 0, 1, 1);
  emptyWrapperBox.attach(fileLabel, 0, 1, 1, 1);
  emptyWrapperBox.attach(browseFilesButton, 0, 2, 1, 1);

  wrapperBox.set_hexpand();
  wrapperBox.set_halign(Gtk::Align::CENTER);
  wrapperBox.set_valign(Gtk::Align::CENTER);

  emptyWrapperBox.set_row_spacing(8);

  wrapperBox.attach(emptyWrapperBox, 0, 0, 1, 1);
  append(wrapperBox);

  set_vexpand();
  set_hexpand();
};
void UploadView::onBrowseFilesButtonClicked() {
  auto dialog = Gtk::FileDialog::create();
  // Add filters, so that only certain file types can be selected:
  auto filters = Gio::ListStore<Gtk::FileFilter>::create();

  // TODO: Add image file pattern
  auto filter_any = Gtk::FileFilter::create();
  filter_any->set_name("Any files");
  filter_any->add_mime_type("image/bmp");

  filters->append(filter_any);

  dialog->set_filters(filters);

  // Show the dialog and wait for a user response:
  dialog->open(
      parentWindow,
      sigc::bind(sigc::mem_fun(*this, &UploadView::onBrowseFilesFinish),
                 dialog));
}
void UploadView::onBrowseFilesFinish(
    const Glib::RefPtr<Gio::AsyncResult> &result,
    const Glib::RefPtr<Gtk::FileDialog> &dialog) {

  try {

    auto file = dialog->open_finish(result);
    auto fileModel = new FileModel(file);

    emptyWrapperBox.remove(*lockIcon);
    emptyWrapperBox.remove(fileLabel);
    fileLabel.set_text(fileModel->filePath);
    emptyWrapperBox.attach(fileLabel, 0, 1, 1, 1);
    lockIcon = std::make_shared<Gtk::Image>(fileModel->filePath);
    lockIcon->set_pixel_size(400);
    emptyWrapperBox.attach(*lockIcon, 0, 0, 1, 1);

    auto editorView = new EditorView(*fileModel);
    // TODO: Set margin to editorView
    wrapperBox.attach(*editorView, 1, 0, 1, 1);

  } catch (const Gtk::DialogError &err) {
    // Can be thrown by dialog->open_finish(result).
    std::cout << "No file selected. " << err.what() << std::endl;
  } catch (const Glib::Error &err) {
    std::cout << "Unexpected exception. " << err.what() << std::endl;
  }
}
