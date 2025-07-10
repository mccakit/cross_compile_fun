Current Platforms and Build Instructions
=======================================

This project supports building on multiple platforms. Below are the supported platforms and their respective build commands.

Supported Platforms
-------------------

- Windows x64
- Windows ARM64
- Linux x64
- Linux ARM64
- MacOS x64
- MacOS ARM64
- ANDROID ARM64
- WASM32

Build Instructions
------------------

- **WASM32**

  Use Emscripten's `emcmake.py` to generate the build files:

  .. code-block:: console

     C:/dev/toolchains/emsdk/upstream/emscripten/emcmake.py cmake -B build/wasm32 -G Ninja

- **Android ARM64**

  Build using Gradle in the `gradle` directory:

  .. code-block:: console

     cd gradle
     ./gradlew assembleDebug

- **MacOS ARM64**

  Configure the build system via WSL with the appropriate toolchain:

  .. code-block:: console

     cmake -B build/macos-arm64 -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/llvm-macos-arm64.cmake"

- **MacOS x64**

  Similar to ARM64 but targeting x64:

  .. code-block:: console

     cmake -B build/macos-x64 -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/llvm-macos-x64.cmake"

- **Linux ARM64**

  Configure, install, and create an AppImage:

  .. code-block:: console

     cmake -B build/linux-arm64 -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/llvm-linux-arm64.cmake"
     cmake --install build/linux-arm64 --prefix build/linux-arm64/output
     wsl; appimagetool build/linux-arm64/output/crossfun.AppDir

- **Linux x64**

  Same steps as Linux ARM64 but for x64:

  .. code-block:: console

     cmake -B build/linux-x64 -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/llvm-linux-x64.cmake"
     cmake --install build/linux-x64 --prefix build/linux-x64/output
     wsl; appimagetool build/linux-x64/output/crossfun.AppDir

- **Windows ARM64**

  Configure build with LLVM toolchain for ARM64 Windows:

  .. code-block:: console

     cmake -B build/win-arm64 -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/llvm-win-arm64.cmake"

- **Windows x64**

  Configure build with LLVM toolchain for x64 Windows:

  .. code-block:: console

     cmake -B build/win-x64 -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/llvm-win-x64.cmake"
---
iOS will probably never happen—I think Apple is outright hostile to developers. Yes, you can build iOS apps on Linux if you’re determined enough, but you still have to go through their review process, even for non-public apps. Honestly, the juice isn’t worth the squeeze. Supporting iOS means playing along with policies I fundamentally disagree with, and I’m fine giving up that quarter of the potential revenue.
