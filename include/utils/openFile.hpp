#ifndef OPEN_FILE_HPP
#define OPEN_FILE_HPP

#include <string>

namespace FileUtils {
    /**
     * Opens the system file explorer showing the directory containing the specified file
     * @param filePath Full path to the file to show in explorer
     * @return true if operation successful, false otherwise
     */
    bool openFileInExplorer(const std::string& filePath);
}

#endif // OPEN_FILE_HPP