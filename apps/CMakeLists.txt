if(ANDROID)
    add_library(main SHARED main-opengl.cpp)
    target_compile_definitions(main PUBLIC IMGUI_IMPL_OPENGL_ES3)
elseif(EMSCRIPTEN)
    add_executable(main main-opengl.cpp)
    target_compile_definitions(main PUBLIC IMGUI_IMPL_OPENGL_ES3)
else()
    add_executable(main main-opengl.cpp)
endif()
target_compile_definitions(main PUBLIC SDL_MAIN_USE_CALLBACKS)
set_property(TARGET main PROPERTY WIN32_EXECUTABLE TRUE)
target_link_libraries(
    main
    PRIVATE
        SDL3_ttf::SDL3_ttf
        SDL3_mixer::SDL3_mixer
        SDL3_image::SDL3_image
        SDL3::SDL3
        stb
        imgui
        implot
)
if(EMSCRIPTEN)
    target_link_libraries(
        main
        PRIVATE
            "--preload-file ${CMAKE_CURRENT_LIST_DIR}/Roboto_Condensed-Regular.ttf@/"
            "--preload-file ${CMAKE_CURRENT_LIST_DIR}/sky_after_rain.mp3@/"
            "--preload-file ${CMAKE_CURRENT_LIST_DIR}/twisted_garden.mp3@/"
            "--preload-file ${CMAKE_CURRENT_LIST_DIR}/nameless_deity@/nameless_deity"
    )
endif()
macro(copy_helper filename)
    if(ANDROID)
        set(outname ${CMAKE_SOURCE_DIR}/gradle/app/src/main/assets)
    else()
        set(outname ${CMAKE_BINARY_DIR}/apps)
    endif()
    add_custom_command(
        TARGET main
        POST_BUILD
        COMMAND
            ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_LIST_DIR}/${filename}" "${outname}"
    )
endmacro()
macro(copy_directory_helper foldername)
    if(ANDROID)
        set(outdir ${CMAKE_SOURCE_DIR}/gradle/app/src/main/assets)
    else()
        set(outdir ${CMAKE_BINARY_DIR}/apps)
    endif()
    add_custom_command(
        TARGET main
        POST_BUILD
        COMMAND
            ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_LIST_DIR}/${foldername}" "${outdir}/${foldername}"
    )
endmacro()
if(NOT EMSCRIPTEN)
    copy_helper("Roboto_Condensed-Regular.ttf")
    copy_helper("sky_after_rain.mp3")
    copy_helper("twisted_garden.mp3")
    copy_directory_helper("nameless_deity")
endif()
