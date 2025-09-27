include(/home/mccakit/dev/emscripten/cmake/Modules/Platform/Emscripten.cmake)
add_compile_options(-w -sASSERTIONS -sALLOW_MEMORY_GROWTH)
add_link_options(-w -sASSERTIONS -sALLOW_MEMORY_GROWTH)
