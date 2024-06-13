#include "TagEditor.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <string>
#include <fstream>

#define NO_FILE false

TagEditorWindow::TagEditorWindow(ImFont* default_font, ImFont* editor_font, bool &window_visible)
    : window_visible { &window_visible }, tag_file_path { NO_FILE}, editor_font { editor_font }, default_font {default_font}, tag_string_buf {}
    {
    }

void TagEditorWindow::Update() {}

void TagEditorWindow::Render() {
    ImGui::Begin("Tag Edit/View", window_visible);
    ImGuiIO& io = ImGui::GetIO();
    
    ImGui::PushFont(editor_font);
    static ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue;
    ImGui::InputTextMultiline("##tags", tag_string_buf, IM_ARRAYSIZE(tag_string_buf), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 10), flags);
    ImGui::PopFont();
    ImGui::End();
}

bool TagEditorWindow::LoadFile(std::string file_path) {
    // # IMPLEMENTATION NOT TESTED
    
    std::ifstream inf{ file_path };
    if (!inf) {
        return false;
    }

    // Purge the old buffer
    memset(tag_string_buf, '\0', sizeof(tag_string_buf));

    inf.read(tag_string_buf, sizeof(tag_string_buf) - 1);
    std::size_t bytesRead = inf.gcount();
    tag_string_buf[bytesRead] = '\0';  // Null-terminate the string

    inf.close();
    return true;

}
