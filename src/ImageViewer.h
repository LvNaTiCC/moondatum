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
    GLuint m_texture {}; // ImageData is responsible for proper initialization and disposal of it's texture
    int m_height {};
    int m_width {};
    void clearData ()
    {
        if (m_texture)
            glDeleteTextures(1, &m_texture);
        m_height = 0;
        m_width = 0;
    }
public:
    GLuint getTexture () const { return m_texture; }
    int getHeight     () const { return m_height;   }
    int getWidth      () const { return m_width;    }
    ImageData()
    : m_texture {}, m_width {}, m_height {}
    {}
    ~ImageData()
    {
        // Properly dispose of GL texture
        clearData();
    }
    ImageData(const std::string& path)
    : m_texture {}, m_width {}, m_height {}
    {
        updateTexture(path);
    }
    void updateTexture (const std::string& path)
    {
        clearData();
        LoadTextureFromFile(path.c_str(), &m_texture, &m_width, &m_height);
    }
    // Prevent copy, because ImageData is responsible for disposal of GL texture
    // GLuint destructor does is responsible for disposing of the texture
    ImageData& operator=(const ImageData&) = delete;
    ImageData(const ImageData&) = delete;
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
        m_imdata.updateTexture(path);
    }
    void Update();
    void Render();
};

#endif
