# Minimum CMake version and project name
cmake_minimum_required(VERSION 3.16)
project(PixelHop LANGUAGES CXX)

# Use C++17 (change if your code needs another standard)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default to a Release build if none is specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Build the executable. Headers (.h/.hpp) are picked up via include paths,
# so only the .cpp files need to be listed here.
add_executable(PixelHop main.cpp)

# Let #include "physics/Physics.h" and "input/Input.hpp" resolve from the project root
target_include_directories(PixelHop PRIVATE ${CMAKE_SOURCE_DIR})

if(APPLE)
  # macOS ships OpenGL, GLUT and OpenAL as system frameworks
  target_link_libraries(PixelHop PRIVATE
    "-framework OpenGL"
    "-framework GLUT"
    "-framework OpenAL"
  )
  # Silence the "OpenGL/GLUT is deprecated" warnings on macOS
  target_compile_definitions(PixelHop PRIVATE GL_SILENCE_DEPRECATION)
  target_compile_options(PixelHop PRIVATE -Wno-deprecated-declarations)
else()
  # Linux/Windows: locate the libraries (needs freeglut and openal-soft installed)
  find_package(OpenGL REQUIRED)
  find_package(GLUT REQUIRED)
  find_package(OpenAL REQUIRED)
  target_link_libraries(PixelHop PRIVATE
    OpenGL::GL GLUT::GLUT ${OPENAL_LIBRARY}
  )
  target_include_directories(PixelHop PRIVATE ${OPENAL_INCLUDE_DIR})
endif()

# Copy all .wav files next to the built executable so the game can load
# them with relative paths like "gameTrack.wav" at runtime
file(GLOB SOUND_FILES "${CMAKE_SOURCE_DIR}/*.wav")
foreach(snd ${SOUND_FILES})
  add_custom_command(TARGET PixelHop POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${snd} $<TARGET_FILE_DIR:PixelHop>
  )
endforeach()