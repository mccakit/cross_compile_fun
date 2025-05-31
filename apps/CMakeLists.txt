if (ANDROID)
	add_library(main SHARED main.cpp)
else()
	add_executable(main main.cpp)
endif()
target_compile_definitions(main PUBLIC SDL_MAIN_USE_CALLBACKS)
target_link_libraries(
    main
    PRIVATE
        SDL3_ttf::SDL3_ttf
        SDL3_mixer::SDL3_mixer
        SDL3_image::SDL3_image
        SDL3::SDL3
        imgui
)
if(EMSCRIPTEN)
    target_link_libraries(
        main
        PRIVATE
            "--preload-file ${CMAKE_CURRENT_LIST_DIR}/Inter-VariableFont.ttf@/"
            "--preload-file ${CMAKE_CURRENT_LIST_DIR}/the_entertainer.ogg@/"
            "--preload-file ${CMAKE_CURRENT_LIST_DIR}/gs_tiger.svg@/"
    )
endif()
macro(copy_helper filename)
    if(ANDROID)
        set(outname ${CMAKE_SOURCE_DIR}/gradle/app/src/main/assets)
    else()
        set(outname ${CMAKE_BINARY_DIR}/apps)
    endif()
    add_custom_command(
        TARGET main POST_BUILD
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
