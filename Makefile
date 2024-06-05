CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -fdiagnostics-color=always -g
LDFLAGS = -lglfw3 -lgdi32 -lopengl32 -lcomctl32 -lnfd -lole32 -loleaut32 -luuid

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = build/win64
IMGUI_DIR = external/imgui
STB_DIR = external/stb
IMGUI_BACKENDS_DIR = $(IMGUI_DIR)/backends
NFD_DIR = external/nativefiledialog/src/include
GLAD_SRC = external/glad/glad.c

SOURCES = $(wildcard $(SRC_DIR)/*.cpp) \
          $(wildcard $(IMGUI_DIR)/*.cpp) \
          $(IMGUI_BACKENDS_DIR)/imgui_impl_opengl3.cpp \
          $(IMGUI_BACKENDS_DIR)/imgui_impl_glfw.cpp \
          $(GLAD_SRC)

OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.cpp)) \
          $(patsubst $(IMGUI_DIR)/%.cpp, $(OBJ_DIR)/imgui_%.o, $(wildcard $(IMGUI_DIR)/*.cpp)) \
          $(OBJ_DIR)/imgui_impl_opengl3.o \
          $(OBJ_DIR)/imgui_impl_glfw.o \
          $(OBJ_DIR)/glad.o

EXECUTABLE = $(BIN_DIR)/main.exe

INCLUDES = -I$(SRC_DIR) \
           -Iincludes \
           -I$(IMGUI_DIR) \
           -I$(IMGUI_BACKENDS_DIR) \
           -I$(NFD_DIR) \
           -I$(STB_DIR) \
           -Iexternal

LIB_PATHS = -Lexternal/GLFW/lib \
            -Lexternal/nativefiledialog/build/lib/Release/x64

.PHONY: all clean

ifeq ($(OS), Windows_NT)
    MKDIR = if not exist "$(subst /,\,$@)" mkdir "$(subst /,\,$@)"
    RMDIR = rmdir /S /Q
else
    MKDIR = mkdir -p $@
    RMDIR = rm -rf
endif

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $@ $(LIB_PATHS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/imgui_%.o: $(IMGUI_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/imgui_impl_opengl3.o: $(IMGUI_BACKENDS_DIR)/imgui_impl_opengl3.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/imgui_impl_glfw.o: $(IMGUI_BACKENDS_DIR)/imgui_impl_glfw.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/glad.o: $(GLAD_SRC) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	$(MKDIR)


clean:
	rm -rf $(OBJ_DIR) build