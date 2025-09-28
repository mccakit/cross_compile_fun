include(/home/mccakit/dev/emscripten/cmake/Modules/Platform/Emscripten.cmake)
add_compile_options(-w -sALLOW_MEMORY_GROWTH -sINITIAL_MEMORY=256MB -flto)
add_link_options(-w -sALLOW_MEMORY_GROWTH -sINITIAL_MEMORY=256MB -flto)
