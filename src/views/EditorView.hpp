#pragma once
#include "FileModel.hpp"
#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "gtkmm/grid.h"
#include "input.hpp"
class EditorView : public Gtk::Grid {
public:
  EditorView(FileModel &fileModel);
  ~EditorView();

private:
  FileModel &fileModel;
  Gtk::Grid controlsGrid;
  Input resizeHeightInput;
  Input resizeWidthInput;

  Gtk::Button resizeButton;
  Gtk::Button blackAndWhiteButton;
  Gtk::Button invertButton;
  double aspectRatio;
  void onHeightChanged();
  void onWidthChanged();
  bool updatingDimensions = false;
};