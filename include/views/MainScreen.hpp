#pragma once
#include "CenterView.hpp"
#include "gtkmm/box.h"
#include <gtkmm/window.h>

class MainScreen : public Gtk::Box {
public:
  MainScreen(Gtk::Window &parentWindow, UploadView *uploadView);
  ~MainScreen() override;

protected:
  // Panes
  Gtk::Paned mainPaned;
  Gtk::Paned rightPaned;
  UploadView *uploadView;
  // Actual Views
  CenterView centerView;

  // Other views/windows/models passed
  Gtk::Window &parentWindow;

  // UI components
  Gtk::Box parent;
};
