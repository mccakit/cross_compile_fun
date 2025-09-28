include(/home/mccakit/dev/emscripten/cmake/Modules/Platform/Emscripten.cmake)
add_compile_options(-w -sMEMORY64=1 -sUSE_PTHREADS=1 -sALLOW_MEMORY_GROWTH -sINITIAL_MEMORY=256MB -sMAXIMUM_MEMORY=12GB -flto)
add_link_options(-w -sMEMORY64=1 -sUSE_PTHREADS=1 -sALLOW_MEMORY_GROWTH -sINITIAL_MEMORY=256MB -sMAXIMUM_MEMORY=12GB -flto)
