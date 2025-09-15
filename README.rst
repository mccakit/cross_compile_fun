##########################################
Current Platforms and Build Instructions
##########################################

This project supports building on multiple platforms. Below are the
supported platforms and their respective build commands.

*********************
Supported Platforms
*********************

- Windows x64
- Windows ARM64
- Debian x64
- Debian ARM64
- Fedora x64
- Fedora ARM64
- OpenSUSE Tumbleweed x64
- OpenSUSE Tumbleweed ARM64
- Arch x64
- MacOS x64
- MacOS ARM64
- iOS ARM64
- iOS Simulator x64
- Android ARM64
- WASM32

********************
Build Instructions
********************

- **WASM32**

  Use Emscripten's `emcmake.py` to generate the build files:

  .. code-block:: console

     C:/dev/toolchains/emsdk/upstream/emscripten/emcmake.py cmake -B build/wasm32 -G Ninja

- **Android ARM64**

  Build using CMake, then package it with Gradle:

  .. code-block:: console

     cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=toolchains/android-arm64.cmake
     cmake --build build
     cd gradle
     gradle assembleDebug

- **MacOS ARM64**

  Just build with CMake:

  .. code-block:: console

     cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/macos-arm64.cmake"

- **MacOS x64**

  Similar to ARM64:

  .. code-block:: console

     cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/macos-x64.cmake"

iOS Builds
==========

- **iOS ARM64**

  Build for actual iOS devices:

  .. code-block:: console

     cmake -B build/ios-arm64 -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/ios-arm64.cmake"

- **iOS Simulator x64**

  Build for the iOS Simulator on x64 macOS:

  .. code-block:: console

     cmake -B build/iossim-x64 -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/iossim-x64.cmake"

Linux Builds
============

Debian
------

- **ARM64**

  .. code-block:: console

     cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/debian-arm64.cmake"
     cmake --install build --prefix build/output
     appimagetool build/output/crossfun.AppDir

- **x64**

  .. code-block:: console

     cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/debian-x64.cmake"
     cmake --install build --prefix build/output
     appimagetool build/output/crossfun.AppDir

Fedora
------

- **ARM64**

  .. code-block:: console

     cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/fedora-arm64.cmake"
     cmake --install build --prefix build/output
     appimagetool build/output/crossfun.AppDir

- **x64**

  .. code-block:: console

     cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/fedora-x64.cmake"
     cmake --install build --prefix build/output
     appimagetool build/output/crossfun.AppDir

OpenSUSE Tumbleweed
-------------------

- **ARM64**

  .. code-block:: console

     cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/opensuse-tumbleweed-arm64.cmake"
     cmake --install build --prefix build/output
     appimagetool build/output/crossfun.AppDir

- **x64**

  .. code-block:: console

     cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/opensuse-tumbleweed-x64.cmake"
     cmake --install build --prefix build/output
     appimagetool build/output/crossfun.AppDir

Arch
----

- **x64 only**

  .. code-block:: console

     cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/arch-x64.cmake"
     cmake --install build --prefix build/output
     appimagetool build/output/crossfun.AppDir

Windows Builds
==============

- **Windows ARM64**

  Configure build with LLVM toolchain for ARM64 Windows:

  .. code-block:: console

     cmake -B build/win-arm64 -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/llvm-win-arm64.cmake"

- **Windows x64**

  Configure build with LLVM toolchain for x64 Windows:

  .. code-block:: console

     cmake -B build/win-x64 -G Ninja -DCMAKE_TOOLCHAIN_FILE="toolchains/llvm-win-x64.cmake"
