add_library(imgui STATIC)

file(GLOB imgui_src "${CMAKE_CURRENT_SOURCE_DIR}/imgui/*.cpp")
set(imgui_backends
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_sdl3.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_sdlrenderer3.cpp"
)
target_sources(imgui PRIVATE ${imgui_src} ${imgui_backends})
target_include_directories(imgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends
)
target_link_libraries(imgui PRIVATE SDL3::SDL3)
