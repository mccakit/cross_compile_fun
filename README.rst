####################
 Cross Compile Fun!
####################

Cool isn't it?

*********************
 Supported Platforms
*********************

.. csv-table::
   :header: "Platform", "Architecture"
   :widths: 20, 20

   "Windows", "x64, ARM64"
   "Debian", "x64, ARM64"
   "Fedora", "x64, ARM64"
   "OpenSUSE Tumbleweed", "x64, ARM64"
   "Arch", "x64"
   "MacOS", "x64, ARM64"
   "iOS", "ARM64"
   "iOS Simulator", "x64, ARM64"
   "Android", "ARM64"
   "Emscripten", "WASM32, WASM64"

****************************
 Build Instructions Summary
****************************

.. csv-table::
   :header: "Platform", "Architecture", "Requirements", "Command"
   :widths: 15, 15, 30, 40

   "Emscripten", "WASM32, WASM64", "llvm, emsdk, binaryen", "Edit the emcc-wasm* toolchain file to point to your installation then use the toolchain with cmake"
   "Android", "ARM64", "llvm, android-ndk", "Build compiler rt, create symlink in your llvm installation to point to that, then build libc++ and edit some .inc files in the std folder of your llvm installation, then build with cmake by tweaking the toolchain and use gradle to package it"
   "MacOS", "X64, ARM64", "XCode, llvm", "Grab XCode by creating an apple account at Apple Music or simply talking to support, then extract it with apple-sdk-tools, build libc++ then build with cmake after tweaking the toolchain"
   "Windows", "X64, ARM64", "llvm, msvc-wine", "Grab 148992 and 150182 PR's from llvm repository, build libc++ with benchmarks disabled then build with cmake after tweaking the toolchain"
   "IOS", "ARM64", "XCode, llvm", "Similar to MacOS"
   "IOSSIM", "X64, ARM64", "XCode, llvm", "Similar to IOS"
   "Debian", "X64, ARM64", "Docker, llvm", "Pull a debian container from docker hub, install the required packages from the SDL3 wiki, build libc++ then build with cmake after tweaking the toolchain"
   "Fedora", "X64, ARM64", "Docker, llvm", "Same as debian, but you may need to manually patch ZLIB cmake file"
   "OpenSUSE Tumbleweed", "X64, ARM64", "Docker, llvm", "Same as Fedora"
   "Arch", "X64", "Docker, llvm", "Same as Debian"


.. note:: You can package linux builds into an appimage if you so desire, example:

  .. code:: console

      cmake --install build --prefix build/output
      appimagetool build/output/crossfun.AppDir
