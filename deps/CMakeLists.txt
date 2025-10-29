set(HB_HAVE_CORETEXT OFF)
add_subdirectory(sdl)
set(SDLTTF_VENDORED ON)
add_subdirectory(sdl_ttf)

set(SDLMIXER_MIDI_NATIVE OFF)
set(SDLMIXER_MP3_MPG123 OFF)
set(SDLMIXER_GME OFF)
set(SDLMIXER_VENDORED ON)
set(SDLMIXER_MOD_XMP OFF)
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
elseif(DARWIN)
    find_library(OPENGL_LIBRARY OpenGL REQUIRED)
    target_link_libraries(imgui PUBLIC ${OPENGL_LIBRARY})
elseif(IOS)
    find_library(OPENGLES_LIB OpenGLES REQUIRED)
    target_link_libraries(imgui PUBLIC ${OPENGLES_LIB})
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(imgui PUBLIC OpenGL::GL)
endif()

add_library(implot STATIC)
file(GLOB implot_src "${CMAKE_CURRENT_SOURCE_DIR}/implot/*.cpp")
target_sources(implot PRIVATE ${implot_src})
target_include_directories(implot PUBLIC implot)
target_link_libraries(implot PRIVATE imgui)

set(NLOHMANN_JSON_BUILD_MODULES ON)
add_subdirectory(nlohmann_json)
set(LIBPSL_INCLUDE_DIR /home/mccakit/dev/dev-deps/android-arm64/include CACHE PATH "libpsl include dir" FORCE)
set(LIBPSL_LIBRARY /home/mccakit/dev/dev-deps/android-arm64/lib/libpsl.a CACHE FILEPATH "libpsl library" FORCE)
set(LIBPSL_INCLUDE_DIRS /home/mccakit/dev/dev-deps/android-arm64/include CACHE PATH "libpsl include dirs" FORCE)
set(LIBPSL_LIBRARIES /home/mccakit/dev/dev-deps/android-arm64/lib/libpsl.a CACHE FILEPATH "libpsl libraries" FORCE)
set(LIBPSL_FOUND ON CACHE BOOL "libpsl found" FORCE)
set(Libpsl_FOUND ON CACHE BOOL "Libpsl found" FORCE)

set(BUILD_CURL_EXE OFF)
set(CURL_DISABLE_LIBPSL OFF)

set(OPENSSL_ROOT_DIR /home/mccakit/dev/dev-deps/android-arm64)
set(OPENSSL_INCLUDE_DIR /home/mccakit/dev/dev-deps/android-arm64/include CACHE PATH "openssl include" FORCE)
set(OPENSSL_SSL_LIBRARY /home/mccakit/dev/dev-deps/android-arm64/lib/libssl.a CACHE FILEPATH "openssl ssl" FORCE)
set(OPENSSL_CRYPTO_LIBRARY /home/mccakit/dev/dev-deps/android-arm64/lib/libcrypto.a CACHE FILEPATH "openssl crypto" FORCE)
set(OpenSSL_FOUND ON CACHE BOOL "openssl found" FORCE)
set(BUILD_CURL_EXE OFF)
add_subdirectory(curl)
set(CPR_USE_EXISTING_CURL_TARGET ON)
add_subdirectory(cpr)
