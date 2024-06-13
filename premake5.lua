workspace "MoonDatum"
    configurations { "Debug", "Release" }

    workspace "MoonDatum"
    configurations { "Debug", "Release" }

-- GLFW project
project "GLFW"
   kind "StaticLib"
   language "C"
   targetdir "external/glfw/lib"

   files { "external/glfw/src/*.c" }
   includedirs { "external/glfw/include" }

   filter "system:windows"
      targetname "glfw3"
      targetextension ".lib"
      defines { "_GLFW_WIN32", "_GLFW_WGL" }

   filter "system:linux"
      targetname "libglfw3"
      targetextension ".a"
      defines { "_GLFW_X11" }
      files {
         "external/glfw/src/context.c",
         "external/glfw/src/init.c",
         "external/glfw/src/input.c",
         "external/glfw/src/monitor.c",
         "external/glfw/src/vulkan.c",
         "external/glfw/src/window.c",
         "external/glfw/src/x11_init.c",
         "external/glfw/src/x11_monitor.c",
         "external/glfw/src/x11_window.c",
         "external/glfw/src/xkb_unicode.c",
         "external/glfw/src/glx_context.c",
         "external/glfw/src/egl_context.c",
         "external/glfw/src/osmesa_context.c",
         "external/glfw/src/linux_joystick.c"
      }
      links { "X11", "pthread", "dl" }

   filter "system:macosx"
      targetname "libglfw3"
      targetextension ".a"
      defines { "_GLFW_COCOA" }
      files {
         "external/glfw/src/context.c",
         "external/glfw/src/init.c",
         "external/glfw/src/input.c",
         "external/glfw/src/monitor.c",
         "external/glfw/src/vulkan.c",
         "external/glfw/src/window.c",
         "external/glfw/src/cocoa_init.m",
         "external/glfw/src/cocoa_joystick.m",
         "external/glfw/src/cocoa_monitor.m",
         "external/glfw/src/cocoa_window.m",
         "external/glfw/src/cocoa_time.c",
         "external/glfw/src/nsgl_context.m",
         "external/glfw/src/egl_context.c",
         "external/glfw/src/osmesa_context.c"
      }
      links { "Cocoa.framework", "IOKit.framework", "CoreVideo.framework" }



project "MoonDatum"
    kind "WindowedApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    includedirs {
        "external",
        "src",
        "external/imgui/backends",
        "external/imgui",
        "utility",
        "external/stb",
        "external/glfw/include",
        "external/nativefiledialog/src/include",
        "utility",
    }


    files {
        "external/glad/glad.c",
        "external/glad/glad.h",
        "external/khr/khrplatform.h",
        "external/GLFW/glfw3.h",
        "external/imgui/*.cpp",
        "external/imgui/*.h",
        "external/imgui/backends/imgui_impl_opengl3.cpp",
        "external/imgui/backends/imgui_impl_opengl3.h",
        "external/imgui/backends/imgui_impl_glfw.h",
        "external/imgui/backends/imgui_impl_glfw.cpp",
        "external/stb/stb_image.h",
        "external/nativefiledialog/src/include/nfd.h",
        "src/*.cpp",
        "utility/utility.cpp"
    }

    libdirs {
        "external/glfw/lib",
        "external/nativefiledialog/build/lib/Release/x64",
    }
    

    -- Please build using Cygwin or other linux-like prompt. This saves a lot of pain.
    filter "system:windows"
        links { "nfd", "glfw3", "gdi32", "opengl32", "ole32", "uuid"}
        toolset "gcc"
        prebuildcommands {
            "cd external/nativefiledialog/build/gmake_windows && mingw32-make config=release_x64"
        }

    filter "system:linux"
        links { "nfd", "glfw", "GL", "pthread", "dl" }
        toolset "gcc"
        prebuildcommands {
            "cd external/nativefiledialog/build/gmake_linux && make config=release_x64"
        }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
