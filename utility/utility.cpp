#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

// Rewrite to traverse directory
// Preferably, to return an iterator to all images


// void getAllImageFiles(const std::string_view folderPath, std::vector<std::string>& imageFiles) {
//     namespace fs = std::filesystem;
//     imageFiles.clear();
//     for (const auto& entry : fs::directory_iterator(folderPath)) {
//         if (entry.is_regular_file() && (entry.path().extension() == ".png" || entry.path().extension() == ".jpeg" || entry.path().extension() == ".jpg")) {
//             //std::cout << "ADDED " << entry.path().string() << "\n"; debug print
//             imageFiles.push_back(entry.path().string());
//         }
//     }
// }

// Simple helper function to load an image into a OpenGL texture with common settings
bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
{
    // Load from file
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    // Create an OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);
    
    // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

    // Generate mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}
