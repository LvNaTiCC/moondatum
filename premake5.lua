workspace "MoonDatum"
    configurations { "Debug", "Release" }

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
        "external/nativefiledialog/src/include",
        "windows",
        "utility"
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
        "windows/*.cpp",
        "windows/*.h",
        "src/main.cpp",
        "utility/utility.cpp"
    }

    libdirs {
        "external/GLFW/lib",
        "external/nativefiledialog/build/lib/Release/x64",
    }
    

    -- Please build using Cygwin or other linux-like prompt. This saves a lot of pain.
    filter "system:windows"
        links { "nfd", "glfw3", "gdi32", "opengl32", "ole32", "uuid"}
        toolset "gcc"
        prebuildcommands {
            "cd external/nativefiledialog/build/gmake_windows && CC=gcc mingw32-make config=release_x64"
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
