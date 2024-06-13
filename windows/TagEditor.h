#ifndef TAG_EDITOR_H
#define TAG_EDITOR_H

#include <string>

class TagEditorWindow {
public:
    TagEditorWindow(bool &window_visible);
    void Update();
    void Render();
    void LoadFile();

private:
    std::string tag_string;
    std::string tag_file_path;
    bool unsaved_changes;
    bool *window_visible;
};

#endif
