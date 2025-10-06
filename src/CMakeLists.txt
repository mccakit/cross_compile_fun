add_library(sdl_load_wrapper STATIC)
target_sources(sdl_load_wrapper PUBLIC FILE_SET CXX_MODULES FILES sdl_load_wrapper.cppm)
target_link_libraries(sdl_load_wrapper PRIVATE SDL3::SDL3)

add_library(glad STATIC)
target_sources(glad PRIVATE glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include)
