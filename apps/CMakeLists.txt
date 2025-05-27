add_executable(foo foo.cpp)
target_compile_definitions(foo PUBLIC SDL_MAIN_USE_CALLBACKS)
target_link_libraries(
    foo
    PRIVATE
        SDL3_ttf::SDL3_ttf
        SDL3_mixer::SDL3_mixer
        SDL3_image::SDL3_image
        SDL3::SDL3
        imgui
)
if(EMSCRIPTEN)
    target_link_libraries(foo PRIVATE
        "--preload-file ${CMAKE_CURRENT_LIST_DIR}/Inter-VariableFont.ttf@/"
        "--preload-file ${CMAKE_CURRENT_LIST_DIR}/the_entertainer.ogg@/"
        "--preload-file ${CMAKE_CURRENT_LIST_DIR}/gs_tiger.svg@/"
    )
endif()
