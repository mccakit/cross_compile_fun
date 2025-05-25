cmake_minimum_required(VERSION 4.0.1)
project(
    ModernCMakeExample
    VERSION 0.1
    DESCRIPTION "An example project with CMake"
    LANGUAGES C CXX
)

include(CTest)
include(FetchContent)


set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
set(GLFW_BUILD_WAYLAND ON)
set(GLFW_BUILD_X11 OFF)
add_subdirectory(extern/glfw)
add_subdirectory(source)
add_subdirectory(apps)
add_subdirectory(tests)
