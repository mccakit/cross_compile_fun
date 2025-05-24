cmake_minimum_required(VERSION 4.0.1)
project(
    ModernCMakeExample
    VERSION 0.1
    DESCRIPTION "An example project with CMake"
    LANGUAGES CXX
)

include(CTest)
include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

add_subdirectory(source)
add_subdirectory(apps)
add_subdirectory(tests)
