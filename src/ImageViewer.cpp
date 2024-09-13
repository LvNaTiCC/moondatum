#include "ImageViewer.h"
#include <iostream>
#include <string>
#include "utility.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace fs = std::filesystem;

void ImageViewer::Render()
{
    // Begin the main ImageViewer window
    ImGui::Begin("Image View", m_visible);

    // Set window padding to zero
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    // Calculate the height for the status bar text
    ImVec2 font_size = ImGui::CalcTextSize("9999 x 9999"); // Adjust the text to match the format of your status bar
    float status_bar_height = font_size.y + ImGui::GetStyle().FramePadding.y * 1.55; // Add padding to the height

    // Get available content size and reserve space for the status bar
    ImVec2 content_size = ImGui::GetContentRegionAvail();
    content_size.y -= status_bar_height * 1.2f;

    // Create a child window for the main content
    ImGui::BeginChild("ImageViewChild", content_size, true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    if (m_imdata.getTexture()) {
        float aspect_ratio = static_cast<float>(m_imdata.getWidth()) / m_imdata.getHeight();
        ImVec2 window_size = ImGui::GetContentRegionAvail();
        ImVec2 image_size {};

        if (window_size.x / aspect_ratio <= window_size.y) {
            image_size.x = window_size.x;
            image_size.y = window_size.x / aspect_ratio;
        } else {
            image_size.x = window_size.y * aspect_ratio;
            image_size.y = window_size.y;
        }

        // Center the image within the available space
        ImVec2 imagePos = ImGui::GetCursorPos();
        imagePos.x += (window_size.x - image_size.x) / 2.0f;
        imagePos.y += (window_size.y - image_size.y) / 2.0f;
        ImGui::SetCursorPos(imagePos);

        // Render the image
        ImGui::Image((void*)(intptr_t)(m_imdata.getTexture()), image_size);
    }

    ImGui::EndChild();

    // Set the color for the status bar
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.0f, 0.5f, 0.0f, 1.0f)); // Example: dark green background



    // Render the status bar in a separate child window
    ImGui::BeginChild("StatusBarChild", ImVec2(0, status_bar_height), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    // Calculate the position to center the text
    float font_pos_x = 2.0f;
    float font_pos_y = (status_bar_height - font_size.y) / 2.0f; // Center vertically within status bar height

    ImGui::SetCursorPos(ImVec2(font_pos_x, font_pos_y));
    ImGui::Text("%d x %d", m_imdata.getWidth(), m_imdata.getHeight());

    ImGui::EndChild();

    // Reset the color and padding to the default
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();

    ImGui::End();
};

void ImageViewer::Update()
{
/*stub*/
}
