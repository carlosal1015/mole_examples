cmake_minimum_required(VERSION 3.30)
project(Tutorial VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

add_executable(elliptic1D elliptic1D.cpp)
target_link_libraries(elliptic1D PUBLIC ${ARMADILLO_LIBRARIES} mole)

add_executable(elliptic2D elliptic2D.cpp)
target_link_libraries(elliptic2D PUBLIC ${ARMADILLO_LIBRARIES} mole)

add_executable(schrodinger1D schrodinger1D.cpp)
target_link_libraries(schrodinger1D PUBLIC ${ARMADILLO_LIBRARIES} mole)

add_executable(transport1D transport1D.cpp)
target_link_libraries(transport1D PUBLIC ${ARMADILLO_LIBRARIES} mole)

find_package(Eigen3 3.4 REQUIRED NO_MODULE)

add_executable(helloarmadillo helloarmadillo.cc)
target_link_libraries(helloarmadillo ${ARMADILLO_LIBRARIES})

add_executable(helloeigen helloeigen.cc)
target_link_libraries(helloeigen Eigen3::Eigen)

add_executable(sparse sparse.cc)
target_link_libraries(sparse Eigen3::Eigen)

add_executable(test1 test1.cpp)
target_link_libraries(test1 PUBLIC ${ARMADILLO_LIBRARIES} mole)

add_executable(test2 test2.cpp)
target_link_libraries(test2 PUBLIC ${ARMADILLO_LIBRARIES} mole)

add_executable(test3 test3.cpp)
target_link_libraries(test3 PUBLIC ${ARMADILLO_LIBRARIES} mole)

add_executable(test4 test4.cpp)
target_link_libraries(test4 PUBLIC ${ARMADILLO_LIBRARIES} mole)

add_executable(test5 test5.cpp)
target_link_libraries(test5 PUBLIC ${ARMADILLO_LIBRARIES} mole)

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
  COMMAND schrodinger1D
  POST_BUILD
  TARGET schrodinger1D
)

add_custom_command(
  COMMAND transport1D
  POST_BUILD
  TARGET transport1D
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