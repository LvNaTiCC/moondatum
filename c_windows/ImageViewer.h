#ifndef IMAGE_VIEWER_H
#define IMAGE_VIEWER_H

#include <filesystem>
#include <string>
#include <string_view>
#include "GLFW/glfw3.h"
#include <vector>

//namespace fs = std::filesystem;

class ImageViewer {
public:
    ImageViewer(std::string_view folderPath);
    void Update();
    void Render();

private:
    std::vector<std::string> imageFiles;
    int currentFolderPosition;
    GLuint currentImageTexture;
    int currentImageWidth;
    int currentImageHeight;
    bool rightArrowHeld;
    bool leftArrowHeld;
};

#endif
