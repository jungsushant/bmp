#ifndef DIRECTORY_DIALOG_HPP
#define DIRECTORY_DIALOG_HPP

#include <functional>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/window.h>
#include <string>

class DirectoryDialog : public Gtk::FileChooserDialog {
public:
  using Callback = std::function<void(const std::string &)>;
  using ErrorCallback = std::function<void(const std::string &)>;

  DirectoryDialog(Gtk::Window &parentWindow, Callback onSuccess,
                  ErrorCallback onError);

private:
  void onResponse(int response_id);

  Callback onSuccess;
  ErrorCallback onError;
};

#endif // DIRECTORY_DIALOG_HPP
