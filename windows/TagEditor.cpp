#include "TagEditor.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#define NO_FILE false

TagEditorWindow::TagEditorWindow(ImFont* default_font, ImFont* editor_font, bool &window_visible)
    : window_visible { &window_visible }, tag_file_path { NO_FILE}, editor_font { editor_font }, default_font {default_font}
    {
    }

void TagEditorWindow::Update() {}

void TagEditorWindow::Render() {
    ImGui::Begin("Tag Edit/View", window_visible);
    static char tag_string_buf[1024 * 8] = "";
    ImGuiIO& io = ImGui::GetIO();
    
    ImGui::PushFont(editor_font);
    static ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue;
    ImGui::InputTextMultiline("##tags", tag_string_buf, IM_ARRAYSIZE(tag_string_buf), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 10), flags);
    ImGui::PopFont();
    ImGui::End();
}
