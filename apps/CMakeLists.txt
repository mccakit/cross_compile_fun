add_executable(foo foo.cpp)
target_compile_definitions(foo PUBLIC SDL_MAIN_USE_CALLBACKS)
target_link_libraries(
    foo
    PRIVATE
        SDL3_ttf::SDL3_ttf
        SDL3_mixer::SDL3_mixer
        SDL3_image::SDL3_image
        SDL3::SDL3-static
        imgui
)
if(EMSCRIPTEN)
    target_link_libraries(
        foo
        PRIVATE
            "--preload-file ${CMAKE_CURRENT_LIST_DIR}/Inter-VariableFont.ttf@/"
            "--preload-file ${CMAKE_CURRENT_LIST_DIR}/the_entertainer.ogg@/"
            "--preload-file ${CMAKE_CURRENT_LIST_DIR}/gs_tiger.svg@/"
    )
elseif(ANDROID)
    file(MAKE_DIRECTORY "${MOBILE_ASSETS_DIR}")
endif()
macro(copy_helper filename)
    if(ANDROID)
        set(outname "${MOBILE_ASSETS_DIR}/${filename}")
    else()
        set(outname ${CMAKE_BINARY_DIR}/apps)
    endif()
    add_custom_command(
        TARGET foo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_LIST_DIR}/${filename}"
            "${outname}"
    )
endmacro()
if(NOT EMSCRIPTEN)
    copy_helper("Inter-VariableFont.ttf")
    copy_helper("the_entertainer.ogg")
    copy_helper("gs_tiger.svg")
endif()
