cmake_minimum_required(VERSION 4.0.2)
project(
    ModernCMakeExample
    VERSION 0.1
    DESCRIPTION "An example project with CMake"
    LANGUAGES C CXX
)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT ANDROID)
    set(BUILD_SHARED_LIBS OFF)
endif()
include(CTest)
include(FetchContent)
if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()
add_subdirectory(extern/sdl3)


set(SDLTTF_VENDORED ON)
add_subdirectory(extern/sdl_ttf)

set(SDLMIXER_MIDI_NATIVE OFF)
set(SDLMIXER_GME OFF)
set(SDLMIXER_WAVPACK OFF)
set(SDLMIXER_MOD OFF)
set(SDLMIXER_OPUS OFF)
set(SDLMIXER_VENDORED ON)
add_subdirectory(extern/sdl_mixer)

set(SDLIMAGE_VENDORED ON)
set(SDLIMAGE_AVIF OFF)
set(SDLIMAGE_BMP OFF)
set(SDLIMAGE_JPEG OFF)
set(SDLIMAGE_WEBP OFF)
add_subdirectory(extern/sdl_image)

add_subdirectory(extern)
add_subdirectory(source)
add_subdirectory(apps)
add_subdirectory(tests)
