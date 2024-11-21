#include "utils/openFile.hpp"
#include <filesystem>

// Add this at appropriate location in EditorView.cpp
bool FileUtils::openFileInExplorer(const std::string& filePath) {
    // Check if file exists
    if (!std::filesystem::exists(filePath)) {
        return false;
    }

    // Get directory path
    std::string dirPath = std::filesystem::path(filePath).parent_path().string();
    
    // Command to open file explorer and select the file
    std::string command = "xdg-open " + dirPath;
    
    // Execute command
    system(command.c_str());
    return true;
}