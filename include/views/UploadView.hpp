#pragma once

#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "gtkmm/filedialog.h"
#include "gtkmm/grid.h"
#include "gtkmm/image.h"
#include "gtkmm/label.h"
#include <string>

class UploadView : public Gtk::Box {
public:
  UploadView(Gtk::Window &parentWindow, const std::string id);

protected:
  void onBrowseFilesButtonClicked();
  void onBrowseFilesFinish(const Glib::RefPtr<Gio::AsyncResult> &result,
                           const Glib::RefPtr<Gtk::FileDialog> &dialog);

private:
  std::string id;
  Gtk::Grid wrapperBox;
  Gtk::Grid emptyWrapperBox;
  Gtk::Window &parentWindow;
  Gtk::Button browseFilesButton;
  Glib::RefPtr<Gtk::Image> lockIcon;
  Gtk::Label fileLabel;
};