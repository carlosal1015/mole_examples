cmake_minimum_required(VERSION 3.28)
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

add_executable(schrodinger1D schrodinger1D.cc)
target_link_libraries(schrodinger1D PUBLIC ${ARMADILLO_LIBRARIES} mole)

find_package(Eigen3 3.4 REQUIRED NO_MODULE)

add_executable(helloarmadillo helloarmadillo.cc)
target_link_libraries(helloarmadillo ${ARMADILLO_LIBRARIES})

add_executable(helloeigen helloeigen.cc)
target_link_libraries(helloeigen Eigen3::Eigen)

add_executable(sparse sparse.cc)
target_link_libraries(sparse Eigen3::Eigen)

add_custom_command(
  COMMAND elliptic1D
  POST_BUILD
  TARGET elliptic1D
)
add_custom_command(
  COMMAND elliptic2D
  POST_BUILD
  TARGET elliptic2D
)

add_custom_command(
  COMMAND transport1D
  POST_BUILD
  TARGET transport1D
)

add_custom_command(
  COMMAND schrodinger1D
  POST_BUILD
  TARGET schrodinger1D
)

add_custom_command(
  COMMAND helloarmadillo
  POST_BUILD
  TARGET helloarmadillo
)

add_custom_command(
  COMMAND helloeigen
  POST_BUILD
  TARGET helloeigen
)

add_custom_command(
  COMMAND sparse
  POST_BUILD
  TARGET sparse
)
