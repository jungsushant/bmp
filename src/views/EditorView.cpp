#include "EditorView.hpp"
#include "FileModel.hpp"
#include "gtkmm/box.h"
#include "gtkmm/grid.h"
#include "gtkmm/label.h"

#include <cstdio>
#include <iostream>
#include <string>

EditorView::EditorView(FileModel &fileModel)
    : fileModel(fileModel), resizeHeightInput(), resizeWidthInput(),
      resizeButton("Resize"), blackAndWhiteButton("Black & White"),
      invertButton("Invert"),aspectRatio(static_cast<double>(fileModel.width) / fileModel.height) {
  set_name("editorView");

  Gtk::Label editorLabel("Editor");
  editorLabel.set_name("editorLabel");
  controlsGrid.attach(editorLabel, 0, 0, 1, 1);

  attach(controlsGrid, 0, 1, 1, 1);

  Gtk::Grid resizeGrid;

  Gtk::Label resizeLabel("Resize");
  Gtk::Label heightLabel("Height");
  Gtk::Label widthLabel("Width");
  Gtk::Grid heightGrid;
  Gtk::Grid widthGrid;

  resizeLabel.set_halign(Gtk::Align::START);
  resizeLabel.set_name("resizeLabel");

  heightGrid.attach(heightLabel, 0, 0, 1, 1);
  heightGrid.attach(resizeHeightInput, 0, 1, 1, 1);
  heightGrid.set_row_homogeneous(false);
  heightLabel.set_halign(Gtk::Align::START);
  resizeHeightInput.set_halign(Gtk::Align::START);
  resizeHeightInput.setText(std::to_string(fileModel.height / 2));
  resizeHeightInput.getEntry().signal_changed().connect(
    sigc::mem_fun(*this, &EditorView::onHeightChanged)
  );

  heightGrid.set_row_spacing(12);

  widthGrid.attach(widthLabel, 0, 0, 1, 1);
  widthGrid.attach(resizeWidthInput, 0, 1, 1, 1);
  widthGrid.set_row_spacing(12);
  widthGrid.set_row_homogeneous(false);
  widthLabel.set_halign(Gtk::Align::START);
  resizeWidthInput.set_halign(Gtk::Align::START);
  resizeWidthInput.setText(std::to_string(fileModel.width / 2));
  resizeWidthInput.getEntry().signal_changed().connect(
    sigc::mem_fun(*this, &EditorView::onWidthChanged)
  );



  resizeGrid.set_row_spacing(16);

  resizeGrid.attach(resizeLabel, 0, 0, 1, 1);
  resizeGrid.attach(heightGrid, 0, 1, 1, 1);
  resizeGrid.attach(widthGrid, 0, 2, 1, 1);
  resizeGrid.attach(resizeButton, 0, 3, 1, 1);

    resizeButton.signal_clicked().connect([this, &fileModel]() {
  auto stringHeight = resizeHeightInput.getText();
  auto stringWidth = resizeWidthInput.getText();

  int height;
  int width;

  if (!stringWidth.empty() && !stringHeight.empty()) {
    height = std::stoi(stringHeight);
    width = std::stoi(stringWidth);
      // Call the resize function when button is clicked
      
      std::string result =
          fileModel.resize(height,width); // Example dimensions
          std::cout << "Height: " << height << " Width: " << width << std::endl;
      std::cout << "Resized image saved at: " << result << std::endl;
  }
    });

  Gtk::Grid actionBtnGrid;

  actionBtnGrid.attach(blackAndWhiteButton, 0, 0, 1, 1);
  actionBtnGrid.attach(invertButton, 1, 0, 1, 1);
  actionBtnGrid.set_column_spacing(20);

  // Connect the "Black & White" button to the blackAndWhite function
  blackAndWhiteButton.signal_clicked().connect([this, &fileModel]() {
    std::string result = fileModel.blackAndWhite();
    std::cout << "Black & White transformation saved at: " << result
              << std::endl;
  });
  invertButton.signal_clicked().connect([this, &fileModel]() {
    std::string result = fileModel.invert();
    std::cout << "Inverted image saved at: " << result << std::endl;
  });

  Gtk::Box separator;
  separator.set_name("separator");
  separator.set_size_request(-1, 3);
  attach(resizeGrid, 0, 2, 1, 1);
  attach(separator, 0, 3, 1, 1);
  attach(actionBtnGrid, 0, 4, 1, 1);
  set_row_spacing(10);
}
EditorView::~EditorView(){};

void EditorView::onHeightChanged() {
    if (updatingDimensions) return;
    
    auto heightStr = resizeHeightInput.getText();
    if (heightStr.empty()) return;
    
    try {
      std::cout << "Height changed" << std::endl;
        updatingDimensions = true;
        int height = std::stoi(heightStr);
        int width = static_cast<int>(height * aspectRatio);
        std::cout << "Calculated height: " << width << std::endl;
        resizeWidthInput.setText(std::to_string(width));
        updatingDimensions = false;
    } catch (...) {
        updatingDimensions = false;
    }
}

void EditorView::onWidthChanged() {
    if (updatingDimensions) return;
    
    auto widthStr = resizeWidthInput.getText();
    if (widthStr.empty()) return;
    
    try {
        updatingDimensions = true;
        int width = std::stoi(widthStr);
        int height = static_cast<int>(width / aspectRatio);
        resizeHeightInput.setText(std::to_string(height));
        updatingDimensions = false;
    } catch (...) {
        updatingDimensions = false;
    }
}