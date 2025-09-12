set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(triple aarch64-linux-gnu)

set(CMAKE_C_COMPILER /home/mccakit/dev/llvm/bin/clang)
set(CMAKE_C_COMPILER_TARGET ${triple})
set(CMAKE_CXX_COMPILER /home/mccakit/dev/llvm/bin/clang++)
set(CMAKE_CXX_COMPILER_TARGET ${triple})
set(CMAKE_RC_COMPILER /home/mccakit/dev/llvm/bin/llvm-rc)
set(CMAKE_LINKER_TYPE LLD)
set(CMAKE_AR /home/mccakit/dev/llvm/bin/llvm-ar)
set(CMAKE_RANLIB /home/mccakit/dev/llvm/bin/llvm-ranlib)
set(CMAKE_MT /home/mccakit/dev/llvm/bin/llvm-mt)
set(CMAKE_ASM_COMPILER /home/mccakit/dev/llvm/bin/clang)

set(CMAKE_SYSROOT /mnt/c/dev/sysroots/deb-arm64)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

set(VULKAN_SDK /mnt/c/dev/sysroots/vulkansdk-ubuntu-22.04-arm-1.4.313.0/1.4.313.0)

add_compile_options(-nostdinc++ -cxx-isystem /home/mccakit/dev/libc++/linux-arm64/include/c++/v1)
link_directories(/home/mccakit/dev/libc++/linux-arm64/lib)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L/home/mccakit/dev/libc++/linux-arm64/lib")
