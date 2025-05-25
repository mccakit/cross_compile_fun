cmake_minimum_required(VERSION 4.0.1)
project(
    ModernCMakeExample
    VERSION 0.1
    DESCRIPTION "An example project with CMake"
    LANGUAGES C CXX
)

include(CTest)
include(FetchContent)

add_subdirectory(extern/sdl3)
add_subdirectory(extern/imgui)
add_subdirectory(source)
add_subdirectory(apps)
add_subdirectory(tests)
