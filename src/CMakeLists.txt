add_library(sdl_load_wrapper STATIC)
target_sources(sdl_load_wrapper PUBLIC FILE_SET CXX_MODULES FILES sdl_load_wrapper.cppm)
target_link_libraries(sdl_load_wrapper PRIVATE SDL3::SDL3)

add_library(glad STATIC)
target_sources(glad PRIVATE glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include)

add_library(texture STATIC)
target_sources(texture PUBLIC FILE_SET CXX_MODULES FILES texture.cppm)
target_link_libraries(texture PRIVATE glad SDL3::SDL3)

add_library(gl_config STATIC)
target_sources(gl_config PUBLIC FILE_SET CXX_MODULES FILES gl_config.cppm)
target_link_libraries(gl_config PRIVATE SDL3::SDL3)
if(ANDROID OR EMSCRIPTEN)
    target_compile_definitions(gl_config PUBLIC IMGUI_IMPL_OPENGL_ES3)
elseif(IOS)
    target_compile_definitions(gl_config PUBLIC IMGUI_IMPL_OPENGL_ES2)
endif()

add_library(widgets STATIC)
target_sources(widgets PUBLIC FILE_SET CXX_MODULES FILES widgets.cppm)
target_link_libraries(widgets PRIVATE imgui implot texture)

add_library(bt STATIC)
target_sources(bt PUBLIC FILE_SET CXX_MODULES FILES bt.cppm)
target_link_libraries(bt PRIVATE nlohmann_json_modules)

add_library(scroll STATIC)
target_sources(scroll PUBLIC FILE_SET CXX_MODULES FILES scroll.cppm)
target_link_libraries(scroll PRIVATE imgui)
