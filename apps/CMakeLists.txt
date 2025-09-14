if(ANDROID)
    add_library(main SHARED main-opengl.cpp)
else()
    add_executable(main main-opengl.cpp)
endif()
if(ANDROID OR EMSCRIPTEN)
    target_compile_definitions(main PUBLIC IMGUI_IMPL_OPENGL_ES3)
elseif(IOS)
    target_compile_definitions(main PUBLIC IMGUI_IMPL_OPENGL_ES2)
endif()
target_compile_definitions(main PUBLIC SDL_MAIN_USE_CALLBACKS)

if(ANDROID)
    target_link_options(
        main
        PRIVATE
            "-Wl,--version-script=/home/mccakit/desktop/projects/cross_compile_fun/gradle/android.export.sym"
    )
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
        stb
        imgui
        implot
        sdl_load_wrapper
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
        set(outdir ${CMAKE_SOURCE_DIR}/gradle/app/src/main/assets)
    elseif(APPLE)
        set(outdir ${CMAKE_BINARY_DIR}/apps/main.app/Contents/Resources)
    else()
        set(outdir ${CMAKE_BINARY_DIR}/apps)
    endif()
    file(COPY "${CMAKE_CURRENT_LIST_DIR}/${filename}" DESTINATION "${outdir}")
endmacro()

if(NOT EMSCRIPTEN)
    copy_helper("Roboto_Condensed-Regular.ttf")
    copy_helper("sky_after_rain.mp3")
    copy_helper("twisted_garden.mp3")
    copy_helper("nameless_deity")
endif()
if(Linux)
    install(
        TARGETS main
        RUNTIME
            DESTINATION crossfun.AppDir/usr/bin
            PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
    )
    install(
        FILES Roboto_Condensed-Regular.ttf sky_after_rain.mp3 twisted_garden.mp3
        DESTINATION crossfun.AppDir/usr/bin
    )
    install(DIRECTORY nameless_deity DESTINATION crossfun.AppDir/usr/bin)
    install(
        FILES appimage/crossfun.desktop appimage/crossfun.png appimage/AppRun
        DESTINATION crossfun.AppDir
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
    )
endif()
if(WIN32)
    install(TARGETS main RUNTIME DESTINATION .)
    install(
        FILES Roboto_Condensed-Regular.ttf sky_after_rain.mp3 twisted_garden.mp3
        DESTINATION .
    )
    install(DIRECTORY nameless_deity DESTINATION .)
endif()
