#include "CenterView.hpp"
#include "gtkmm/object.h"

CenterView::CenterView(Gtk::Window &parentWindow, UploadView *uploadView)
    : uploadView(uploadView), parentWindow(parentWindow) {

  // Set the widget name for CSS identification
  set_name("center-view");
  auto allFiles = Gtk::make_managed<UploadView>(parentWindow, "all");
  add(*allFiles, "all", "Category");

  set_visible_child("all");
}

CenterView::~CenterView() {}