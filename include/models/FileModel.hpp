
#pragma once
#include "giomm/file.h"
#include "glibmm/refptr.h"
#include <string>

class FileModel {
public:
  // Constructor
  FileModel(Glib::RefPtr<Gio::File> file);
  ~FileModel();
  // A singleton instance of categorymodel across the app

  std::string filePath;
  long long fileSize;

  std::string name;

  std::string destinationPath;

  std::string resize(int height, int width);

  std::string blackAndWhite();
  std::string invert();

  sigc::signal<void()> signalCategoryAdded;

  int height;
  int width;
};