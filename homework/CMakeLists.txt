cmake_minimum_required(VERSION 3.31)
project(Tutorial VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

add_executable(elliptic1D elliptic1D.cpp)
target_compile_definitions(elliptic1D PRIVATE EIGEN=1)
target_link_libraries(elliptic1D PUBLIC ${ARMADILLO_LIBRARIES} mole hdf5)

# find_package(Eigen3 3.4 REQUIRED NO_MODULE)

# add_executable(helloeigen helloeigen.cc)
# target_link_libraries(helloeigen Eigen3::Eigen)

add_custom_command(
  COMMAND elliptic1D
  POST_BUILD
  TARGET elliptic1D
)