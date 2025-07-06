### Current Platforms
- Windows X64
- Windows ARM64
- Linux X64
- Linux ARM64
- MacOS X64
- MacOS ARM64
- ANDROID ARM64
- WASM32

To build

- WASM32 = C:/dev/toolchains/emsdk/upstream/emscripten/emcmake.py cmake -B build/wasm32 -G Ninja
- MacOS-ARM64 = wsl; cmake -B build/macos-arm64 -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/llvm-macos-arm64.cmake"
- MacOS-X64 = wsl; cmake -B build/macos-x64 -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/llvm-macos-x64.cmake"
- Linux-ARM64 = cmake -B build/linux-arm64 -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/llvm-linux-arm64.cmake"
- Linux-X64 = cmake -B build/linux-x64 -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/llvm-linux-x64.cmake"
- Windows-ARM64 = cmake -B build/win-arm64 -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/llvm-win-arm64.cmake"
- Windows-X64 = cmake -B build/win-x64 -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/llvm-win-x64.cmake"
