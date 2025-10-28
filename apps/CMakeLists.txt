if(ANDROID)
    add_library(main SHARED main.cpp)
else()
    add_executable(main main.cpp)
endif()
target_compile_definitions(main PUBLIC SDL_MAIN_USE_CALLBACKS)

if(ANDROID)
    file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/apps/arm64-v8a")
    add_custom_command(
        TARGET main
        POST_BUILD
        COMMAND
            ${CMAKE_COMMAND} -E rename "$<TARGET_FILE:main>"
            "${CMAKE_BINARY_DIR}/apps/arm64-v8a/libmain.so"
    )
endif()

if(WIN32)
    set_property(TARGET main PROPERTY WIN32_EXECUTABLE TRUE)
elseif(APPLE)
    set_target_properties(main PROPERTIES MACOSX_BUNDLE TRUE)
elseif(LINUX)
    set_property(TARGET main PROPERTY WIN32_EXECUTABLE TRUE)
endif()

target_link_libraries(
    main
    PRIVATE
        SDL3_ttf::SDL3_ttf
        SDL3_mixer::SDL3_mixer
        SDL3_image::SDL3_image
        SDL3::SDL3
        imgui
        implot
        sdl_load_wrapper
        glad
        texture
        gl_config
        widgets
        nlohmann_json_modules
)
if(EMSCRIPTEN)
    target_link_libraries(
        main
        PRIVATE
            "--preload-file ${CMAKE_CURRENT_LIST_DIR}/Ubuntu-Regular.ttf@/"
            "--preload-file ${CMAKE_CURRENT_LIST_DIR}/sky_after_rain.mp3@/"
            "--preload-file ${CMAKE_CURRENT_LIST_DIR}/twisted_garden.mp3@/"
            "--preload-file ${CMAKE_CURRENT_LIST_DIR}/nameless_deity.gif@/"
    )
endif()
macro(copy_helper filename)
    if(ANDROID)
        set(outdir ${CMAKE_SOURCE_DIR}/gradle/app/src/main/assets)
    elseif(APPLE)
        set(outdir ${CMAKE_BINARY_DIR}/apps/main.app/Contents/Resources)
    else()
        set(outdir ${CMAKE_BINARY_DIR}/apps)
    endif()
    file(COPY "${CMAKE_CURRENT_LIST_DIR}/${filename}" DESTINATION "${outdir}")
endmacro()

if(NOT EMSCRIPTEN)
    copy_helper("Ubuntu-Regular.ttf")
    copy_helper("sky_after_rain.mp3")
    copy_helper("twisted_garden.mp3")
    copy_helper("nameless_deity.gif")
endif()
if(Linux)
    install(
        TARGETS main
        RUNTIME
            DESTINATION crossfun.AppDir/usr/bin
            PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
    )
    install(
        FILES Ubuntu-Regular.ttf sky_after_rain.mp3 twisted_garden.mp3 nameless_deity.gif
        DESTINATION crossfun.AppDir/usr/bin
    )
    install(
        FILES appimage/crossfun.desktop appimage/crossfun.png appimage/AppRun
        DESTINATION crossfun.AppDir
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
    )
endif()
if(WIN32)
    install(TARGETS main RUNTIME DESTINATION .)
    install(
        FILES Ubuntu-Regular.ttf sky_after_rain.mp3 twisted_garden.mp3 nameless_deity.gif
        DESTINATION .
    )
endif()
