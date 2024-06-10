#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#include <nfd.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <chrono>
#include <thread>

// Define the desired frame rate (e.g., 60 FPS)
const int desiredFPS = 60;
const int frameDuration = 1000 / desiredFPS; // in milliseconds


bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height);

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s/n", error, description);
}

// Main code
int main(int, char**)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);


    GLFWwindow* window = glfwCreateWindow(1280, 720, "Moondatum", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
  
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);

    ImGui_ImplOpenGL3_Init(glsl_version);


    // Our state
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    int my_image_width = 0;
    int my_image_height = 0;
    GLuint my_image_texture = 0;
    bool ret = LoadTextureFromFile("E:/images/vscbg/icons/__hatsune_miku_vocaloid_drawn_by_rrrssr__b1666488558d076a70d9fa5ed989bfc9.png", &my_image_texture, &my_image_width, &my_image_height);
    IM_ASSERT(ret);
    while (!glfwWindowShouldClose(window))
    {
        auto frameStart = std::chrono::high_resolution_clock::now();
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        #if 1
            bool show_demo_window = true;
            ImGui::ShowDemoWindow(&show_demo_window);
        #endif

        ImGui::Begin("OpenGL Texture Text", nullptr);
        if (ImGui::Button("Change Image"))
        {
            nfdchar_t *outPath = NULL;
            nfdresult_t result = NFD_OpenDialog( NULL, NULL, &outPath );
                
            if ( result == NFD_OKAY ) {
                puts("Success!");
                ret = LoadTextureFromFile(outPath, &my_image_texture, &my_image_width, &my_image_height);
                IM_ASSERT(ret);
                puts(outPath);
                free(outPath);

            }
            else if ( result == NFD_CANCEL ) {
                puts("User pressed cancel.");
            }
            else {
                printf("Error: %s\n", NFD_GetError() );
            }
        }
        float aspect_ratio = float(my_image_width)/float(my_image_height);


        ImVec2 windowSize = ImGui::GetWindowSize();
        ImVec2 imageSize;
        if (windowSize.x / aspect_ratio <= windowSize.y)
        {
            imageSize.x = windowSize.x;
            imageSize.y = windowSize.x / aspect_ratio;
        } else {
            imageSize.x = windowSize.y * aspect_ratio;
            imageSize.y = windowSize.y;
        }
        imageSize.x = imageSize.x * 0.9f;
        imageSize.y = imageSize.y * 0.9f;
        ImVec2 position;
        position.x = (windowSize.x - imageSize.x) / 2.0f;
        position.y = (windowSize.y - imageSize.y) / 2.0f;
        ImGui::SetCursorPos(position);
        ImGui::Image((void*)(intptr_t)my_image_texture, imageSize);
        ImGui::Text("Dimensions: %d x %d", my_image_width, my_image_height);
        ImGui::End();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);

        // Measure frame time and sleep to limit frame rate
        auto frameEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float, std::milli> frameTime = frameEnd - frameStart;
        if (frameTime.count() < frameDuration)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(frameDuration) - frameTime);
        }
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

// Simple helper function to load an image into a OpenGL texture with common settings
bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
{
    // Load from file
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}
