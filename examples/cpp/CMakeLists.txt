cmake_minimum_required(VERSION 3.10)
project(Tutorial VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

add_executable(elliptic1D elliptic1D.cc)
target_link_libraries(elliptic1D PUBLIC ${ARMADILLO_LIBRARIES} mole)

add_executable(elliptic2D elliptic2D.cc)
target_link_libraries(elliptic2D PUBLIC ${ARMADILLO_LIBRARIES} mole)

add_executable(transport1D transport1D.cc)
target_link_libraries(transport1D PUBLIC ${ARMADILLO_LIBRARIES} mole)

add_executable(schrodinger schrodinger1D.cc)
target_link_libraries(schrodinger PUBLIC ${ARMADILLO_LIBRARIES} mole)

find_package(Eigen3 3.4 REQUIRED NO_MODULE)

add_executable(helloarmadillo helloarmadillo.cc)
target_link_libraries(helloarmadillo ${ARMADILLO_LIBRARIES})

add_executable(helloeigen helloeigen.cc)
target_link_libraries(helloeigen Eigen3::Eigen)