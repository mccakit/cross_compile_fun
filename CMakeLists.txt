cmake_minimum_required(VERSION 4.0.2)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "OFF")
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
project(
    CrossFun
    VERSION 1.0
    DESCRIPTION "Lmao"
    LANGUAGES C CXX
)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE RELEASE)
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
