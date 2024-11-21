// src/utils/resize.cpp
#include "utils/resize.hpp"
#include <fstream>
#include <vector>
#include <iostream>
#include <cmath>
#include "openFile.hpp"
#include "resize.hpp"

    void Resize::resize(std::string filePath, int newHeight, int newWidth) {
        // Open input file
        std::ifstream inFile(filePath, std::ios::binary);
        if (!inFile) {
            throw std::runtime_error("Cannot open file: " + filePath);
        }

        // Read BMP header
        std::vector<char> header(54);
        inFile.read(header.data(), 54);

        // Get original dimensions
        int origWidth = *(int*)&header[18];
        int origHeight = *(int*)&header[22];
        
        // Calculate paddings
        int origPadding = (4 - (origWidth * 3) % 4) % 4;
        int newPadding = (4 - (newWidth * 3) % 4) % 4;

        // Read source pixels
        std::vector<char> srcPixels(origWidth * origHeight * 3);
        for (int y = 0; y < origHeight; y++) {
            inFile.read(&srcPixels[y * origWidth * 3], origWidth * 3);
            inFile.seekg(origPadding, std::ios::cur);
        }

        // Create destination pixel buffer
        std::vector< char> dstPixels(newWidth * newHeight * 3);

        // Calculate scaling ratios
        float xRatio = float(origWidth - 1) / newWidth;
        float yRatio = float(origHeight - 1) / newHeight;

        // Resize using bilinear interpolation
        for (int y = 0; y < newHeight; y++) {
            for (int x = 0; x < newWidth; x++) {
                float gx = x * xRatio;
                float gy = y * yRatio;
                int gxi = (int)gx;
                int gyi = (int)gy;
                
                // Calculate interpolation weights
                float xDiff = gx - gxi;
                float yDiff = gy - gyi;
                
                for (int c = 0; c < 3; c++) { // For each color channel
                    // Get pixels for interpolation
                    int index = (gyi * origWidth + gxi) * 3 + c;
                    unsigned char c00 = srcPixels[index];
                    unsigned char c10 = srcPixels[index + 3];
                    unsigned char c01 = srcPixels[index + origWidth * 3];
                    unsigned char c11 = srcPixels[index + origWidth * 3 + 3];
                    
                    // Interpolate
                    float val = c00 * (1 - xDiff) * (1 - yDiff) +
                               c10 * xDiff * (1 - yDiff) +
                               c01 * (1 - xDiff) * yDiff +
                               c11 * xDiff * yDiff;
                               
                    dstPixels[(y * newWidth + x) * 3 + c] = (unsigned char)val;
                }
            }
        }

        // Create output filename
        std::string baseName = filePath.substr(0, filePath.find_last_of('.'));
        std::string extension = filePath.substr(filePath.find_last_of('.'));
        std::string outputPath = baseName + "_resized" + extension;

        // Update header with new dimensions
        *(int*)&header[18] = newWidth;
        *(int*)&header[22] = newHeight;
        *(int*)&header[2] = 54 + newHeight * (newWidth * 3 + newPadding); // File size

        // Write output file
        std::ofstream outFile(outputPath, std::ios::binary);
        if (!outFile) {
            throw std::runtime_error("Cannot create output file: " + outputPath);
        }

        // Write header
        outFile.write(header.data(), 54);

        // Write resized pixels
        char pad = 0;
        for (int y = 0; y < newHeight; y++) {
            outFile.write(&dstPixels[y * newWidth * 3], newWidth * 3);
            for (int p = 0; p < newPadding; p++) {
                outFile.write(&pad, 1);
            }
        }

        FileUtils::openFileInExplorer(outputPath);
    }
