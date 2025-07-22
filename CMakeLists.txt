cmake_minimum_required(VERSION 4.1.2)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_CXX_FLAGS -stdlib=libc++)
if(LINUX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L/home/mccakit/dev/libc++/linux-x64/lib")
    link_directories(/home/mccakit/dev/libc++/linux-x64/lib)
elseif(WIN32)
    include_directories(/home/mccakit/random-include/windows)#need to include __config_site llvm build doesn't generate that
    link_directories(/mnt/c/dev/toolchains/llvm/lib)#I need to link to windows libc++
    install(FILES /mnt/c/dev/toolchains/llvm/bin/c++.dll DESTINATION .) #lastly I need to copy c++.dll
endif()
add_compile_options(-cxx-isystem /home/mccakit/dev/llvm/include/c++/v1) #IDK why do I need to do this
project(
    CrossFun
    VERSION 1.0
    DESCRIPTION "Lmao"
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_C_EXTENSIONS ON)

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
