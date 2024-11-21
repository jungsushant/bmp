#include <fstream>
#include <iostream>
#include <vector>
#include "utils/black&white.hpp"
#include "utils/openFile.hpp"

void BlackAndWhite::blackAndWhite(std::string filePath) {
    std::cout<<"Converting image to black and white..."<<filePath<<std::endl;
    // Open file in binary mode
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file: " + filePath);
    }

    // Read BMP header (54 bytes)
    std::vector<char> header(54);
    file.read(header.data(), 54);

    // Extract image dimensions from header
    int width = *(int*)&header[18];
    int height = *(int*)&header[22];
    
    // Calculate row padding (rows must be multiple of 4 bytes)
    int padding = (4 - (width * 3) % 4) % 4;
    
    // Read pixel data
    std::vector<char> pixels(width * height * 3);
    
    for (int y = 0; y < height; y++) {
        file.read(&pixels[y * width * 3], width * 3);
        file.seekg(padding, std::ios::cur); // Skip padding bytes
    }

    // Convert to grayscale using luminance formula: 
    // Y = 0.299R + 0.587G + 0.114B
    for (int i = 0; i < width * height * 3; i += 3) {
        unsigned char r = pixels[i];
        unsigned char g = pixels[i+1]; 
        unsigned char b = pixels[i+2];
        
        unsigned char gray = (0.299f * r + 0.587f * g + 0.114f * b);
        
        pixels[i] = gray;   // R
        pixels[i+1] = gray; // G 
        pixels[i+2] = gray; // B
    }

    // Write output BMP
    std::string outPath = filePath.substr(0, filePath.find_last_of('.')) + "_bw.bmp";
    std::ofstream outFile(outPath, std::ios::binary);
    
    // Write header
    outFile.write(header.data(), 54);
    
    // Write pixel data with padding
    for (int y = 0; y < height; y++) {
        outFile.write(&pixels[y * width * 3], width * 3);
        
        // Write padding bytes
        char pad = 0;
        for (int p = 0; p < padding; p++) {
            outFile.write(&pad, 1);
        }
    }
    FileUtils::openFileInExplorer(outPath);
}