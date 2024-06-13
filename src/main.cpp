#include "glad/glad.h"
#include "GLFW/glfw3.h" // Will drag system OpenGL headers
#include "ImageViewer.h"
#include "TagEditor.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#define GL_SILENCE_DEPRECATION


#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#include <stdio.h>
#include <filesystem>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

// Frames per second limit
const int desiredFPS = 120;
const int frameDuration = 1000 / desiredFPS; // in milliseconds



bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height);

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s/n", error, description);
}


// Dragging by the main menu callback
// Allows to drag the window, descpite not having a top bar.
// void UpdateWindowPos(GLFWwindow* window, ImGuiIO& io)
// {
//     static bool dragging = false;
//     static ImVec2 dragOffset;

//     if (ImGui::IsMouseDragging(ImGuiMouseButton_Left))
//     {
//         ImVec2 mousePos = ImGui::GetMousePos();
//         if (!dragging)
//         {
//             int windowX, windowY;
//             glfwGetWindowPos(window, &windowX, &windowY);

//             dragOffset.x = mousePos.x - windowX;
//             dragOffset.y = mousePos.y - windowY;
//             std::cout << dragOffset.x;
//             std::cout << dragOffset.y;
//             dragging = true;
//         }

//         int newX = static_cast<int>(mousePos.x - dragOffset.x);
//         int newY = static_cast<int>(mousePos.y - dragOffset.y);
//         glfwSetWindowPos(window, newX, newY);
//     }
//     else
//     {
//         dragging = false;
//     }
// }


int main(int, char**)
{
    //  GLFW Configuration and Initialization
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    //glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); // Make a borderless window

    GLFWwindow* window = glfwCreateWindow(700, 900, "Moondatum", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    //  Bind OpenGL with GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    

    //  Dear ImGui Context Configuration
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

    ImFont* font_default = io.Fonts->AddFontFromFileTTF("fonts/Roboto-Regular.ttf", 18.0f);
    ImFont* font_medium = io.Fonts->AddFontFromFileTTF("fonts/Roboto-Regular.ttf", 22.0f);
    ImFont* font_large = io.Fonts->AddFontFromFileTTF("fonts/Roboto-Regular.ttf", 26.0f);


    //  Dear ImGui Style Configuration
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;

    // Load Fonts

    


    // Platform/Renderer ImGui backends Configuration
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);



    // GL Clear color. Doesn't matter, since it is overriden by ImGui's own background color.
    ImVec4 clear_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);


    // Window/Widget States
    static bool show_image_viewport = true;
    static bool show_demo_window = true;
    static bool show_tag_editor = true;


    // Default folder
    // #TODO Create the "no folder opened" state along with placeholder image
    std::string folderPath = "E:/datadump/ml_datasets/sd/v1v404/cumulative";
    ImageViewer imageWindow(folderPath, show_image_viewport);
    TagEditorWindow tagEditorWindow(font_default, font_medium, show_tag_editor);
    while (!glfwWindowShouldClose(window))
    {
        auto frameStart = std::chrono::high_resolution_clock::now();
        //  GLFW/Imgui Rendering Setup
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        //  Create a dockespace for the main window
        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

        //  Demo for debugging & learning. No real reason to remove it.
        #if 1
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
        #endif

        // Show Image Viewer if not closed.
        if (show_image_viewport) {
            imageWindow.Update();
            imageWindow.Render();
        }

        if (show_tag_editor) {
            tagEditorWindow.Update();
            tagEditorWindow.Render();
        }
    

        // Main Menu / Top Bar
        if (ImGui::BeginMainMenuBar()) {
            // if (ImGui::IsMouseDragging(ImGuiMouseButton_Left) && ImGui::IsItemActive())
            // {
            //     // Drag the main window if user drags along main menu.
            //     UpdateWindowPos(window, io);
            // }

            // if (!ImGui::IsMouseReleased(ImGuiMouseButton_Left) && ImGui::IsItemActive())
            // {
            //     // Reset the dragging state inside UpdateWindowPos
            //     // This is called every frame in which user hovering their mouse
            //     // over the main menu.
            //     // #TODO Come up with less expensive idea
            //     UpdateWindowPos(window, io);
            // }


            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Open another folder")) {
                    imageWindow.ChangeFolder();
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("View")) {
                if (ImGui::MenuItem("Image viewport")) {
                    show_image_viewport = true;
                }
                if (ImGui::MenuItem("Tag Editor")) {
                    show_tag_editor = true;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        //  GL/Imgui Rendering logic
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
        // if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        // {
        //     GLFWwindow* backup_current_context = glfwGetCurrentContext();
        //     ImGui::UpdatePlatformWindows();
        //     ImGui::RenderPlatformWindowsDefault();
        //     glfwMakeContextCurrent(backup_current_context);
        // }

        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(window);

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


