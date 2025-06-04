cmake_minimum_required(VERSION 4.0.2)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "OFF")
project(
    CrossFun
    VERSION 1.0
    DESCRIPTION "Lmao"
    LANGUAGES C CXX
)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT ANDROID)
    set(BUILD_SHARED_LIBS OFF)
endif()
include(CTest)
include(FetchContent)
if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

add_subdirectory(extern)
add_subdirectory(source)
add_subdirectory(apps)
add_subdirectory(tests)
