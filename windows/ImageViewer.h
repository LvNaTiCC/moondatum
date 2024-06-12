#ifndef IMAGE_VIEWER_H
#define IMAGE_VIEWER_H

#include <filesystem>
#include <string>
#include <string_view>
#include "GLFW/glfw3.h"
#include <vector>

class ImageViewer {
public:
    ImageViewer(std::string_view folderPath, bool &windowVisible);
    void Update();
    void Render();
    void ChangeFolder();

private:
    std::vector<std::string> imageFiles;
    int currentFolderPosition;
    GLuint currentImageTexture;
    int currentImageWidth;
    int currentImageHeight;
    bool rightArrowHeld;
    bool leftArrowHeld;
    bool *windowVisible;
};

#endif
