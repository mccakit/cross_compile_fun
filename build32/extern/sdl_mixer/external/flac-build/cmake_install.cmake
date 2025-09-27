# Install script for directory: /home/mccakit/desktop/cross_compile_fun/extern/sdl_mixer/external/flac

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/mccakit/dev/emscripten/cache/sysroot")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RELEASE")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/home/mccakit/dev/llvm/bin/llvm-objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/FLAC" TYPE FILE FILES
    "/home/mccakit/desktop/cross_compile_fun/extern/sdl_mixer/external/flac/include/FLAC/all.h"
    "/home/mccakit/desktop/cross_compile_fun/extern/sdl_mixer/external/flac/include/FLAC/assert.h"
    "/home/mccakit/desktop/cross_compile_fun/extern/sdl_mixer/external/flac/include/FLAC/callback.h"
    "/home/mccakit/desktop/cross_compile_fun/extern/sdl_mixer/external/flac/include/FLAC/export.h"
    "/home/mccakit/desktop/cross_compile_fun/extern/sdl_mixer/external/flac/include/FLAC/format.h"
    "/home/mccakit/desktop/cross_compile_fun/extern/sdl_mixer/external/flac/include/FLAC/metadata.h"
    "/home/mccakit/desktop/cross_compile_fun/extern/sdl_mixer/external/flac/include/FLAC/ordinals.h"
    "/home/mccakit/desktop/cross_compile_fun/extern/sdl_mixer/external/flac/include/FLAC/stream_decoder.h"
    "/home/mccakit/desktop/cross_compile_fun/extern/sdl_mixer/external/flac/include/FLAC/stream_encoder.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/FLAC++" TYPE FILE FILES
    "/home/mccakit/desktop/cross_compile_fun/extern/sdl_mixer/external/flac/include/FLAC++/all.h"
    "/home/mccakit/desktop/cross_compile_fun/extern/sdl_mixer/external/flac/include/FLAC++/decoder.h"
    "/home/mccakit/desktop/cross_compile_fun/extern/sdl_mixer/external/flac/include/FLAC++/encoder.h"
    "/home/mccakit/desktop/cross_compile_fun/extern/sdl_mixer/external/flac/include/FLAC++/export.h"
    "/home/mccakit/desktop/cross_compile_fun/extern/sdl_mixer/external/flac/include/FLAC++/metadata.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/mccakit/desktop/cross_compile_fun/build32/extern/sdl_mixer/external/flac-build/src/cmake_install.cmake")
  include("/home/mccakit/desktop/cross_compile_fun/build32/extern/sdl_mixer/external/flac-build/microbench/cmake_install.cmake")
  include("/home/mccakit/desktop/cross_compile_fun/build32/extern/sdl_mixer/external/flac-build/doc/cmake_install.cmake")

endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/mccakit/desktop/cross_compile_fun/build32/extern/sdl_mixer/external/flac-build/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
