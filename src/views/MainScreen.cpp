#include "MainScreen.hpp"
#include "gtkmm/object.h"
#include <gtkmm/box.h>

MainScreen::MainScreen(Gtk::Window &parentWindow, UploadView *uploadView)
    : parentWindow(parentWindow), centerView(parentWindow, uploadView) {

  parent.set_orientation(Gtk::Orientation::HORIZONTAL);
  auto _uploadView = Gtk::make_managed<UploadView>(parentWindow, "all");
  // Set Widths

  centerView.set_size_request(
      768, -1); // 60% of the window width for the main content

  // Only allow centerBox to expand
  centerView.set_expand(true);
  // Append views inside parent
  parent.append(centerView);

  // Set default screen to all(all-files)
  centerView.set_visible_child("all");
  // Append parent itself into mainscreen
  append(parent);
}
MainScreen::~MainScreen() {}
