#include "models/FileModel.hpp"
#include "gdkmm/pixbuf.h"
#include "utils/black&white.hpp"
#include "utils/invert.hpp"
#include "utils/resize.hpp"
#include <iostream>
FileModel::FileModel(Glib::RefPtr<Gio::File> file) {
  auto fileInfo = file->query_info();
  name = fileInfo->get_name();
  filePath = file->get_path();
  fileSize = fileInfo->get_size();

  Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_file(filePath);

  // Get the width and height of the image
  width = pixbuf->get_width();
  height = pixbuf->get_height();
}

std::string FileModel::resize(int newheight, int newwidth) {
  std::cout << "Resizing image to " << newheight << "x" << newwidth << std::endl;
  std::string destinationPath = "hello";
  Resize::resize(filePath, newheight, newwidth);
  return destinationPath;
}
std::string FileModel::blackAndWhite() {
  std::string destinationPath = "";
  BlackAndWhite::blackAndWhite(filePath);
  return destinationPath;
}
std::string FileModel::invert() {
  Invert::invert(filePath);
  return destinationPath;
}
FileModel::~FileModel() {}