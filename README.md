### Current Platforms
- Windows X64
- Windows ARM64
- Linux X64
- Linux ARM64
- ANDROID ARM64
- WASM32

To build

WASM32 = C:/dev/toolchains/emsdk/upstream/emscripten/emcmake.py cmake -B build/wasm32 -G Ninja
MacOSX = wsl; cmake -B build/macosx-arm64 -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/osxcross-macosx-arm64.cmake"
Linux-ARM64 = cmake -B build/linux-arm64 -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/llvm-linux-arm64.cmake"
Linux-X64 = cmake -B build/linux-x64 -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/llvm-linux-x64.cmake"
