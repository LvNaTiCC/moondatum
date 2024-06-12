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
    // Begin the main ImageViewer window
    ImGui::Begin("Image View", windowVisible);

    // Set window padding to zero
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    // Calculate the height for the status bar text
    ImVec2 textSize = ImGui::CalcTextSize("9999 x 9999"); // Adjust the text to match the format of your status bar
    float statusBarHeight = textSize.y + ImGui::GetStyle().FramePadding.y * 1.55; // Add padding to the height

    // Get available content size and reserve space for the status bar
    ImVec2 contentSize = ImGui::GetContentRegionAvail();
    contentSize.y -= statusBarHeight * 1.2f;

    // Create a child window for the main content
    ImGui::BeginChild("ImageViewChild", contentSize, true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

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

        // Center the image within the available space
        ImVec2 imagePos = ImGui::GetCursorPos();
        imagePos.x += (windowSize.x - imageSize.x) / 2.0f;
        imagePos.y += (windowSize.y - imageSize.y) / 2.0f;
        ImGui::SetCursorPos(imagePos);

        // Render the image
        ImGui::Image((void*)(intptr_t)currentImageTexture, imageSize);
    }

    ImGui::EndChild();

    // Set the color for the status bar
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.0f, 0.5f, 0.0f, 1.0f)); // Example: dark green background



    // Render the status bar in a separate child window
    ImGui::BeginChild("StatusBarChild", ImVec2(0, statusBarHeight), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    // Calculate the position to center the text
    ImVec2 statusBarSize = ImGui::GetContentRegionAvail();
    float textPosX = 2.0f;
    float textPosY = (statusBarHeight - textSize.y) / 2.0f; // Center vertically within status bar height

    ImGui::SetCursorPos(ImVec2(textPosX, textPosY));
    ImGui::Text("%d x %d", currentImageWidth, currentImageHeight);

    ImGui::EndChild();

    // Reset the color and padding to the default
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();

    ImGui::End();
}

