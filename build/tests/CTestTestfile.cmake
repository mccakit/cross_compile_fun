# CMake generated Testfile for 
# Source directory: C:/Users/cakit/Desktop/cmake_template/tests
# Build directory: C:/Users/cakit/Desktop/cmake_template/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[testlibtest]=] "C:/Users/cakit/Desktop/cmake_template/build/tests/testlib")
set_tests_properties([=[testlibtest]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/cakit/Desktop/cmake_template/tests/CMakeLists.txt;8;add_test;C:/Users/cakit/Desktop/cmake_template/tests/CMakeLists.txt;0;")
subdirs("../_deps/catch-build")
