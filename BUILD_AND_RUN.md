# PixelHop: Build and Run Guide

PixelHop is a 2D platformer written in C++ with OpenGL, GLUT and OpenAL.
This guide shows two ways to build it on **macOS**, **Linux** and **Windows**:

1. **Direct compile**: one compiler command, no extra tools.
2. **CMake**: one `CMakeLists.txt` that works on all three systems.

## Project layout

```
PixelHop/
├── main.cpp            # entry point
├── *.h / input/ / physics/   # headers
├── *.wav               # sound files (must be next to the executable)
└── CMakeLists.txt      # needed only for the CMake method
```

> **Important:** the game loads `.wav` files with relative paths such as `gameTrack.wav`.
> Always run the game from a folder that contains those files.

## Includes check (cross-platform)

GLUT and OpenAL headers have different paths on macOS than on Linux/Windows.
If you want the same code to build everywhere, use this pattern in your source:

```cpp
// macOS uses framework-style include paths
#ifdef __APPLE__
  #include <OpenGL/gl.h>
  #include <GLUT/glut.h>
  #include <OpenAL/al.h>
  #include <OpenAL/alc.h>
#else
  // Linux and Windows (MinGW) use the standard paths
  #include <GL/glut.h>
  #include <AL/al.h>
  #include <AL/alc.h>
#endif
```

---

# Method 1: Direct compile and run

Run all commands from inside the `PixelHop` folder.

## macOS

```bash
# 1. Install Apple's compiler tools (skip if already installed)
xcode-select --install

# 2. Compile: OpenGL, GLUT and OpenAL are built-in system frameworks
clang++ main.cpp -o main -std=c++17 \
  -framework OpenGL -framework GLUT -framework OpenAL \
  -DGL_SILENCE_DEPRECATION -Wno-deprecated-declarations

# 3. Run (from this folder so the .wav files are found)
./main
```

## Linux (Ubuntu / Debian)

```bash
# 1. Install the compiler, FreeGLUT, OpenAL and OpenGL development files
sudo apt update
sudo apt install build-essential freeglut3-dev libopenal-dev \
                 libgl1-mesa-dev libglu1-mesa-dev

# 2. Compile
g++ main.cpp -o main -std=c++17 -lglut -lGLU -lGL -lopenal

# 3. Run
./main
```

Other distros:

```bash
# Fedora
sudo dnf install gcc-c++ freeglut-devel openal-soft-devel mesa-libGL-devel mesa-libGLU-devel

# Arch
sudo pacman -S base-devel freeglut openal glu
```

## Windows (MSYS2 + MinGW-w64)

MSYS2 is the easiest way to get a GCC compiler plus FreeGLUT and OpenAL.

```bash
# 1. Install MSYS2 from https://www.msys2.org, then open the
#    "MSYS2 MINGW64" terminal (not the plain MSYS2 one) and run:
pacman -Syu
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-freeglut mingw-w64-x86_64-openal

# 2. Go to your project folder (C:\ is /c/ in MSYS2)
cd /c/Users/YourName/path/to/PixelHop

# 3. Compile
g++ main.cpp -o main.exe -std=c++17 -lfreeglut -lopengl32 -lglu32 -lopenal

# 4. Run
./main.exe
```

To run `main.exe` by double-clicking or from `cmd`/PowerShell, add
`C:\msys64\mingw64\bin` to your Windows `PATH` so it can find the DLLs
(`libfreeglut.dll`, `OpenAL32.dll`).

---

# Method 2: Build with CMake

## Step 1: Install CMake and a compiler

| System                  | Command                                                                                                                          |
| ----------------------- | -------------------------------------------------------------------------------------------------------------------------------- |
| macOS                   | `brew install cmake` (compiler comes from `xcode-select --install`)                                                              |
| Linux (Debian/Ubuntu)   | `sudo apt install cmake build-essential freeglut3-dev libopenal-dev libgl1-mesa-dev libglu1-mesa-dev`                            |
| Windows (MSYS2 MINGW64) | `pacman -S mingw-w64-x86_64-cmake mingw-w64-x86_64-ninja mingw-w64-x86_64-gcc mingw-w64-x86_64-freeglut mingw-w64-x86_64-openal` |

Check the install:

```bash
# Should print a version number (3.16 or newer is required)
cmake --version
```

## Step 2: Create `CMakeLists.txt`

Put this file in the project root, next to `main.cpp`:

```cmake
# Minimum CMake version and project name
cmake_minimum_required(VERSION 3.16)
project(PixelHop LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default to a Release build if none is specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Build the executable (headers are found via include paths)
add_executable(PixelHop main.cpp)

# Allow #include "physics/Physics.h" and "input/Input.hpp" from the project root
target_include_directories(PixelHop PRIVATE ${CMAKE_SOURCE_DIR})

if(APPLE)
  # macOS ships OpenGL, GLUT and OpenAL as system frameworks
  target_link_libraries(PixelHop PRIVATE
    "-framework OpenGL"
    "-framework GLUT"
    "-framework OpenAL"
  )
  # Hide the "OpenGL/GLUT is deprecated" warnings
  target_compile_definitions(PixelHop PRIVATE GL_SILENCE_DEPRECATION)
  target_compile_options(PixelHop PRIVATE -Wno-deprecated-declarations)
else()
  # Linux and Windows: find the libraries installed in Step 1
  find_package(OpenGL REQUIRED)
  find_package(GLUT REQUIRED)
  find_package(OpenAL REQUIRED)
  target_link_libraries(PixelHop PRIVATE
    OpenGL::GL GLUT::GLUT ${OPENAL_LIBRARY}
  )
  target_include_directories(PixelHop PRIVATE ${OPENAL_INCLUDE_DIR})
endif()

# Copy all .wav files next to the built executable so the game can load them
file(GLOB SOUND_FILES "${CMAKE_SOURCE_DIR}/*.wav")
foreach(snd ${SOUND_FILES})
  add_custom_command(TARGET PixelHop POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${snd} $<TARGET_FILE_DIR:PixelHop>
  )
endforeach()
```

## Step 3: Configure, build and run

### macOS and Linux

```bash
# Configure: generate build files into a separate "build" folder
cmake -S . -B build

# Compile
cmake --build build

# Run from inside build/ so the copied .wav files are found
cd build && ./PixelHop
```

### Windows (MSYS2 MINGW64 terminal)

```bash
# Configure with Ninja (installed in Step 1)
cmake -S . -B build -G Ninja

# Compile
cmake --build build

# Run
cd build && ./PixelHop.exe
```

If you prefer Makefiles on Windows, use `-G "MinGW Makefiles"` instead of `-G Ninja`.

## Useful CMake commands

```bash
# Debug build (for lldb / gdb)
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug

# Start completely fresh
rm -rf build

# Rebuild after editing code
cmake --build build
```

## Using CMake in VS Code

1. Install the **CMake Tools** extension (`ms-vscode.cmake-tools`).
2. When asked to select a kit, choose:
   - **macOS:** `Clang ... arm64-apple-darwin`
   - **Linux:** `GCC ...`
   - **Windows:** `GCC ... mingw64` (make sure `C:\msys64\mingw64\bin` is in `PATH`)
3. Click **Build** in the bottom status bar, then the **play (▶)** button to run.

---

# Troubleshooting

| Problem                                                | Fix                                                                             |
| ------------------------------------------------------ | ------------------------------------------------------------------------------- |
| `fatal error: GL/glut.h: No such file` (Linux/Windows) | Install FreeGLUT (see Step 1)                                                   |
| `fatal error: GLUT/glut.h` not found on Linux/Windows  | Use the `#ifdef __APPLE__` include pattern above                                |
| `OpenAL not found` in CMake                            | Install `libopenal-dev` (Linux) or `mingw-w64-x86_64-openal` (MSYS2)            |
| Game runs but has no sound                             | Run from a folder that contains the `.wav` files                                |
| `cmake: command not found`                             | Install CMake, then open a new terminal                                         |
| Windows: `libfreeglut.dll was not found`               | Add `C:\msys64\mingw64\bin` to `PATH`, or run inside the MSYS2 MINGW64 terminal |
| `-lglut` linker error on Windows                       | Use `-lfreeglut` instead of `-lglut`                                            |
| Deprecation warnings on macOS                          | Safe to ignore; the flags above silence them                                    |
