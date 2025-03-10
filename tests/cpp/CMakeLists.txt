cmake_minimum_required(VERSION 3.31)
project(Tutorial VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

find_package(GTest)
enable_testing()

add_executable(test1 test1.cpp)
target_link_libraries(test1 PUBLIC GTest::gtest_main ${ARMADILLO_LIBRARIES} mole_C++)

add_executable(test2 test2.cpp)
target_link_libraries(test2 PUBLIC GTest::gtest_main ${ARMADILLO_LIBRARIES} mole_C++)

add_executable(test3 test3.cpp)
target_link_libraries(test3 PUBLIC GTest::gtest_main ${ARMADILLO_LIBRARIES} mole_C++)

add_executable(test4 test4.cpp)
target_link_libraries(test4 PUBLIC GTest::gtest_main ${ARMADILLO_LIBRARIES} mole_C++)

add_executable(test5 test5.cpp)
target_compile_definitions(test5 PRIVATE LAPACK=1)
target_link_libraries(test5 PUBLIC GTest::gtest_main ${ARMADILLO_LIBRARIES} mole_C++)

include(GoogleTest)
gtest_discover_tests(test1)
gtest_discover_tests(test2)
gtest_discover_tests(test3)
gtest_discover_tests(test4)
gtest_discover_tests(test5)

add_custom_command(
  COMMAND test1
  POST_BUILD
  TARGET test1
)

add_custom_command(
  COMMAND test2
  POST_BUILD
  TARGET test2
)

add_custom_command(
  COMMAND test3
  POST_BUILD
  TARGET test3
)

add_custom_command(
  COMMAND test4
  POST_BUILD
  TARGET test4
)

add_custom_command(
  COMMAND test5
  POST_BUILD
  TARGET test5
)
