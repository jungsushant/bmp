#pragma once

#include "UploadView.hpp"
#include "gtkmm/stack.h"
#include <gtkmm.h>

class CenterView : public Gtk::Stack {
public:
  CenterView(Gtk::Window &parentWindow, UploadView *uploadView);
  ~CenterView() override;

private:
  Gtk::Window &parentWindow;
  UploadView *uploadView;
  // Additional UI elements for the center view can be added here
};
