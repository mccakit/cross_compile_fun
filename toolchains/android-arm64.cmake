set(CMAKE_SYSTEM_NAME Android)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(CMAKE_SYSTEM_VERSION 30)
set(CMAKE_ANDROID_NDK /home/mccakit/dev/android-clt/ndk/29.0.13599879)
set(CMAKE_ANDROID_STL_TYPE c++_static)
set(CMAKE_ANDROID_ARCH_ABI arm64-v8a)

set(CMAKE_C_COMPILER /home/mccakit/dev/llvm/bin/clang)
set(CMAKE_CXX_COMPILER /home/mccakit/dev/llvm/bin/clang++)
set(CMAKE_ASM_COMPILER /home/mccakit/dev/llvm/bin/clang)
set(CMAKE_RC_COMPILER /home/mccakit/dev/llvm/bin/llvm-rc)
set(CMAKE_AR /home/mccakit/dev/llvm/bin/llvm-ar)
set(CMAKE_RANLIB /home/mccakit/dev/llvm/bin/llvm-ranlib)
set(CMAKE_MT /home/mccakit/dev/llvm/bin/llvm-mt)

add_compile_options(
    --sysroot=/home/mccakit/dev/android-clt/ndk/29.0.13599879/toolchains/llvm/prebuilt/linux-x86_64/sysroot
    -w
    -L/home/mccakit/dev/android-clt/ndk/29.0.13599879/toolchains/llvm/prebuilt/linux-x86_64/lib/clang/20/lib/linux/aarch64
)

add_link_options(
    --sysroot=/home/mccakit/dev/android-clt/ndk/29.0.13599879/toolchains/llvm/prebuilt/linux-x86_64/sysroot
    -w
    -L/home/mccakit/dev/android-clt/ndk/29.0.13599879/toolchains/llvm/prebuilt/linux-x86_64/lib/clang/20/lib/linux/aarch64
)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostdinc++ -nostdlib++ -isystem /home/mccakit/dev/libcxx/android-arm64/include/c++/v1")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/home/mccakit/dev/libcxx/android-arm64/lib")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -L/home/mccakit/dev/libcxx/android-arm64/lib")
link_libraries(libc++abi.a libc++_static.a)
