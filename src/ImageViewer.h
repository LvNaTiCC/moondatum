#ifndef IMAGE_VIEWER_H
#define IMAGE_VIEWER_H

#include <filesystem>
#include <string>
#include <string_view>
#include <vector>
#include "GLFW/glfw3.h"
#include "utility.h"



// Class deisgned to contain data crucial for proper image rendering
class ImageData
{
private:
    GLuint m_texture {};
    int m_height {};
    int m_width {};
public:
    GLuint getTexture () const { return m_texture; }
    int getHeight     () const { return m_height;   }
    int getWidth      () const { return m_width;    }
    ImageData()
    : m_texture {}, m_width {}, m_height {}
    {}
    ImageData(const std::string& path)
    : m_texture {}, m_width {}, m_height {}
    {
        LoadTextureFromFile(path.c_str(), &m_texture, &m_width, &m_height);
    }
};

class ImageViewer {
private:
    ImageData m_imdata {};
    bool *m_visible {};
public:
    ImageViewer(bool* window_visible)
    : m_visible { window_visible }
    {
    }
    void setImage(const std::string& path)
    {
        m_imdata = ImageData(path);
    }
    void Update();
    void Render();
};

#endif
