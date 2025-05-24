# CMake generated Testfile for 
# Source directory: C:/Users/cakit/Desktop/cmake_project/tests
# Build directory: C:/Users/cakit/Desktop/cmake_project/build/win-x64/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test([=[testlibtest]=] "C:/Users/cakit/Desktop/cmake_project/build/win-x64/tests/Debug/testlib.exe")
  set_tests_properties([=[testlibtest]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/cakit/Desktop/cmake_project/tests/CMakeLists.txt;8;add_test;C:/Users/cakit/Desktop/cmake_project/tests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test([=[testlibtest]=] "C:/Users/cakit/Desktop/cmake_project/build/win-x64/tests/Release/testlib.exe")
  set_tests_properties([=[testlibtest]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/cakit/Desktop/cmake_project/tests/CMakeLists.txt;8;add_test;C:/Users/cakit/Desktop/cmake_project/tests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test([=[testlibtest]=] "C:/Users/cakit/Desktop/cmake_project/build/win-x64/tests/MinSizeRel/testlib.exe")
  set_tests_properties([=[testlibtest]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/cakit/Desktop/cmake_project/tests/CMakeLists.txt;8;add_test;C:/Users/cakit/Desktop/cmake_project/tests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test([=[testlibtest]=] "C:/Users/cakit/Desktop/cmake_project/build/win-x64/tests/RelWithDebInfo/testlib.exe")
  set_tests_properties([=[testlibtest]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/cakit/Desktop/cmake_project/tests/CMakeLists.txt;8;add_test;C:/Users/cakit/Desktop/cmake_project/tests/CMakeLists.txt;0;")
else()
  add_test([=[testlibtest]=] NOT_AVAILABLE)
endif()
subdirs("../_deps/catch-build")
