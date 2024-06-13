#include "TagEditor.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#define NO_FILE false

TagEditorWindow::TagEditorWindow(bool &window_visible)
    : window_visible { &window_visible }, tag_file_path { NO_FILE}
    {
    }

void TagEditorWindow::Update() {}

void TagEditorWindow::Render() {
    ImGui::Begin("Tag Edit/View", window_visible);
    ImGui::Text("Sample Text");
    ImGui::End();
}
