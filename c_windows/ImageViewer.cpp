#include "ImageViewer.h"
#include <iostream>
#include <string>
#include "utility.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "nfd.h"

namespace fs = std::filesystem;

void getAllImageFiles(const std::string_view folderPath, std::vector<std::string>& imageFiles) {
    imageFiles.clear();
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file() && (entry.path().extension() == ".png" || entry.path().extension() == ".jpeg" || entry.path().extension() == ".jpg")) {
            //std::cout << "ADDED " << entry.path().string() << "\n"; debug print
            imageFiles.push_back(entry.path().string());
        }
    }
}

ImageViewer::ImageViewer(const std::string_view folderPath, bool &windowVisible)
    : currentFolderPosition{0}, currentImageTexture{0}, currentImageWidth{0}, currentImageHeight{0}, rightArrowHeld{false}, leftArrowHeld{false}, windowVisible { &windowVisible } {
        getAllImageFiles(folderPath, imageFiles);

        if (!imageFiles.empty()) {
            LoadTextureFromFile(imageFiles[currentFolderPosition].c_str(), &currentImageTexture, &currentImageWidth, &currentImageHeight);
        }
    }

void ImageViewer::Update() {
    ImGuiIO& io = ImGui::GetIO();
    if (io.KeysDown[ImGuiKey_RightArrow]) {
        if (!rightArrowHeld) {
            currentFolderPosition = (currentFolderPosition + 1) % imageFiles.size();
            LoadTextureFromFile(imageFiles[currentFolderPosition].c_str(), &currentImageTexture, &currentImageWidth, &currentImageHeight);
            rightArrowHeld = true;
        }
    } else {
        rightArrowHeld = false;
    }

    if (io.KeysDown[ImGuiKey_LeftArrow]) {
        if (!leftArrowHeld) {
            if (currentFolderPosition == 0) {
                currentFolderPosition = imageFiles.size() - 1;
            } else {
                --currentFolderPosition;
            }
            LoadTextureFromFile(imageFiles[currentFolderPosition].c_str(), &currentImageTexture, &currentImageWidth, &currentImageHeight);
            leftArrowHeld = true;
        }
    } else {
        leftArrowHeld = false;
    }
}

void ImageViewer::ChangeFolder() {
        nfdchar_t *outPath = NULL;
        nfdresult_t result = NFD_PickFolder(NULL, &outPath);
        if (result == NFD_OKAY) {
            getAllImageFiles(outPath, imageFiles);
            currentFolderPosition = 0;
            LoadTextureFromFile(imageFiles[currentFolderPosition].c_str(), &currentImageTexture, &currentImageWidth, &currentImageHeight);
            free(outPath);
        } else if (result == NFD_CANCEL) {
            return;
        } else {
            printf("Error: %s\n", NFD_GetError());
        }
}

void ImageViewer::Render() {
    ImGui::Begin("Image View", windowVisible);
    if (!imageFiles.empty()) {
        float aspect_ratio = static_cast<float>(currentImageWidth) / static_cast<float>(currentImageHeight);
        ImVec2 windowSize = ImGui::GetContentRegionAvail();
        ImVec2 imageSize;

        if (windowSize.x / aspect_ratio <= windowSize.y) {
            imageSize.x = windowSize.x;
            imageSize.y = windowSize.x / aspect_ratio;
        } else {
            imageSize.x = windowSize.y * aspect_ratio;
            imageSize.y = windowSize.y;
        }

        imageSize.x = imageSize.x * 0.9f;
        imageSize.y = imageSize.y * 0.9f;

        // Calculate the frame size and position
        float framePadding = 10.0f;
        ImVec2 frameSize = {imageSize.x + framePadding * 2, imageSize.y + framePadding * 2};
        ImVec2 framePos = ImGui::GetCursorPos();
        framePos.x += (windowSize.x - frameSize.x) / 2.0f;
        framePos.y += (windowSize.y - frameSize.y) / 2.0f;
        
        // Set the position for the frame
        ImGui::SetCursorPos(framePos);

        // Begin the frame with a child window
        ImGui::BeginChild("ImageFrame", frameSize, true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

        // Calculate the image position to be centered within the frame
        ImVec2 imagePos = {(frameSize.x - imageSize.x) / 2.0f, (frameSize.y - imageSize.y) / 2.0f};
        ImGui::SetCursorPos(imagePos);

        // Render the image
        ImGui::Image((void*)(intptr_t)currentImageTexture, imageSize);

        ImGui::EndChild();
    }

    ImGui::Text("Image: %s", !imageFiles.empty() ? imageFiles[currentFolderPosition].c_str() : "No Image");
    ImGui::Text("Dimensions: %d x %d", currentImageWidth, currentImageHeight);

    ImGui::End();
}
