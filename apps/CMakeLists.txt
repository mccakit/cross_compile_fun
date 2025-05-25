add_executable(foo foo.cpp)
target_link_libraries(foo PRIVATE SDL3::SDL3-static)
