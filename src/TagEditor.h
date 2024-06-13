#ifndef TAG_EDITOR_H
#define TAG_EDITOR_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <string>

class TagEditorWindow {
public:
    TagEditorWindow(ImFont* default_font, ImFont* editor_font, bool &window_visible);
    void Update();
    void Render();
    bool LoadFile(std::string file_path);

private:
    std::string tag_string;
    std::string tag_file_path;
    ImFont* editor_font;
    ImFont* default_font;
    bool unsaved_changes;
    bool *window_visible;
    char tag_string_buf[1024 * 8];
};

#endif
