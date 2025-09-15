set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(triple aarch64-redhat-linux)

set(CMAKE_C_COMPILER /home/mccakit/dev/llvm/bin/clang)
set(CMAKE_C_COMPILER_TARGET ${triple})
set(CMAKE_CXX_COMPILER /home/mccakit/dev/llvm/bin/clang++)
set(CMAKE_CXX_COMPILER_TARGET ${triple})
set(CMAKE_ASM_COMPILER /home/mccakit/dev/llvm/bin/clang)
set(CMAKE_ASM_COMPILER_TARGET ${triple})
set(CMAKE_RC_COMPILER /home/mccakit/dev/llvm/bin/llvm-rc)
set(CMAKE_LINKER_TYPE LLD)
set(CMAKE_AR /home/mccakit/dev/llvm/bin/llvm-ar)
set(CMAKE_RANLIB /home/mccakit/dev/llvm/bin/llvm-ranlib)
set(CMAKE_MT /home/mccakit/dev/llvm/bin/llvm-mt)

set(CMAKE_SYSROOT /home/mccakit/dev/sysroots/fedora-arm64)
set(CMAKE_FIND_ROOT_PATH ${CMAKE_SYSROOT})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
add_compile_options(--gcc-install-dir=${CMAKE_SYSROOT}/lib/gcc/${triple}/15)
add_link_options(--gcc-install-dir=${CMAKE_SYSROOT}/lib/gcc/${triple}/15)

set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -nostdinc++ -nostdlib++ -isystem /home/mccakit/dev/libcxx/fedora-arm64/include/c++/v1"
)
set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} -L/home/mccakit/dev/libcxx/fedora-arm64/lib"
)
set(CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -L/home/mccakit/dev/libcxx/fedora-arm64/lib"
)
link_libraries(libc++.a libc++abi.a libunwind.a)
add_compile_options(-w -flto=thin)
add_link_options(-w -flto=thin)
