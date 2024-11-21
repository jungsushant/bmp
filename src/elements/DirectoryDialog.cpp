#include "DirectoryDialog.hpp"
#include <gtkmm/button.h>
#include <iostream>

DirectoryDialog::DirectoryDialog(Gtk::Window &parentWindow, Callback onSuccess,
                                 ErrorCallback onError)
    : Gtk::FileChooserDialog(parentWindow, "Select a Directory",
                             Gtk::FileChooser::Action::SELECT_FOLDER),
      onSuccess(onSuccess), onError(onError) {
  // Add response buttons
  add_button("_Cancel", Gtk::ResponseType::CANCEL);
  add_button("_Open", Gtk::ResponseType::OK);

  // Connect the response signal
  signal_response().connect(sigc::mem_fun(*this, &DirectoryDialog::onResponse));
}

void DirectoryDialog::onResponse(int response_id) {
  if (response_id == Gtk::ResponseType::OK) {
    auto file = get_file();
    if (file) {
      auto path = file->get_path();
      if (!path.empty()) {
        onSuccess(path);
      } else {
        std::cout << "No directory selected" << std::endl;
        onError("No directory selected");
      }
    } else {
      std::cout << "File object is null" << std::endl;
      onError("File object is null");
    }
  } else {
    std::cout << "Dialog was canceled." << std::endl;
    onError("Dialog was canceled");
  }

  // Hide and delete the dialog
  hide();
}
