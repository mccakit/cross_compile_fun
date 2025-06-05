add_subdirectory(sdl3)
set(SDLTTF_VENDORED ON)
add_subdirectory(sdl_ttf)

set(SDLMIXER_MIDI_NATIVE OFF)
set(SDLMIXER_GME OFF)
set(SDLMIXER_WAVPACK OFF)
set(SDLMIXER_MOD OFF)
set(SDLMIXER_OPUS OFF)
set(SDLMIXER_VENDORED ON)
add_subdirectory(sdl_mixer)

set(SDLIMAGE_VENDORED ON)
set(SDLIMAGE_AVIF OFF)
set(SDLIMAGE_BMP OFF)
set(SDLIMAGE_JPEG OFF)
set(SDLIMAGE_WEBP OFF)
add_subdirectory(sdl_image)

add_library(imgui STATIC)
file(GLOB imgui_src "${CMAKE_CURRENT_SOURCE_DIR}/imgui/*.cpp")

set(imgui_backends
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_sdl3.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp"
)
target_sources(imgui PRIVATE ${imgui_src} ${imgui_backends})
target_include_directories(
    imgui
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends
)
target_link_libraries(imgui PRIVATE SDL3::SDL3)
if(EMSCRIPTEN)
    target_link_options(imgui PUBLIC "-sUSE_WEBGL2=1")
elseif(ANDROID)
    target_link_libraries(imgui PUBLIC GLESv3)
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(imgui PUBLIC OpenGL::GL)
endif()

add_library(stb STATIC)
file(GLOB stb_src stb/*.c)
target_sources(stb PRIVATE ${stb_src})
target_include_directories(stb PUBLIC stb)

add_library(implot STATIC)
file(GLOB implot_src "${CMAKE_CURRENT_SOURCE_DIR}/implot/*.cpp")
target_sources(implot PRIVATE ${implot_src})
target_include_directories(implot PUBLIC implot)
target_link_libraries(implot PRIVATE imgui)
