cmake_minimum_required(VERSION 3.31)
project(ArmadilloTutorial VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})
find_package(Eigen3 3.4 REQUIRED NO_MODULE)

add_executable(1 1.cc)
target_link_libraries(1 ${ARMADILLO_LIBRARIES})
add_executable(2 2.cc)
add_executable(3 3.cc)
target_link_libraries(3 Eigen3::Eigen) # superlu

add_custom_command(
  COMMAND 1
  POST_BUILD
  TARGET 1
)

add_custom_command(
  COMMAND 2
  POST_BUILD
  TARGET 2
)

add_custom_command(
  COMMAND 3
  POST_BUILD
  TARGET 3
)