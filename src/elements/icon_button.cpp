#include "icon_button.hpp"
#include "gtkmm/image.h"

IconButton::IconButton(const std::string &iconPath, ClickCallback onClick)
    : mOnClick(onClick) {
  set_name("icon-btn");

  auto pmap = Gtk::make_managed<Gtk::Image>(iconPath);
  set_child(*pmap);
  signal_clicked().connect(sigc::mem_fun(*this, &IconButton::onClick));
}

void IconButton::onClick() {
  if (mOnClick) {
    mOnClick(); // Call the user-defined callback
  }
}
