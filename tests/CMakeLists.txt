FetchContent_Declare(
  catch
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.6)
FetchContent_MakeAvailable(catch)
add_executable(testlib testlib.cpp)
target_link_libraries(testlib PRIVATE Catch2::Catch2)
add_test(NAME testlibtest COMMAND testlib)
