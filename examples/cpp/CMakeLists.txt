cmake_minimum_required(VERSION 3.31)
project(Tutorial VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

add_executable(convection_diffusion convection_diffusion.cpp)
target_link_libraries(convection_diffusion PUBLIC ${ARMADILLO_LIBRARIES} mole_C++)

# find_package(HDF5 REQUIRED)
add_executable(elliptic1D elliptic1D.cpp)
# target_compile_definitions(elliptic1D PRIVATE EIGEN=1)
# target_link_libraries(elliptic1D PUBLIC ${ARMADILLO_LIBRARIES} mole_C++ Eigen3::Eigen hdf5)
target_compile_definitions(elliptic1D PRIVATE LAPACK=1)
target_link_libraries(elliptic1D PUBLIC ${ARMADILLO_LIBRARIES} mole_C++ hdf5) # superlu

add_executable(elliptic2D elliptic2D.cpp)
target_link_libraries(elliptic2D PUBLIC ${ARMADILLO_LIBRARIES} mole_C++)

add_executable(parabolic1D parabolic1D.cpp)
target_link_libraries(parabolic1D PUBLIC ${ARMADILLO_LIBRARIES} mole_C++)

add_executable(RK2 RK2.cpp)
target_link_libraries(RK2 PUBLIC ${ARMADILLO_LIBRARIES})

add_executable(schrodinger1D schrodinger1D.cpp)
target_link_libraries(schrodinger1D PUBLIC ${ARMADILLO_LIBRARIES} mole_C++)

add_executable(schrodinger2D schrodinger2D.cpp)
target_link_libraries(schrodinger2D PUBLIC ${ARMADILLO_LIBRARIES} mole_C++)

add_executable(transport1D transport1D.cpp)
target_link_libraries(transport1D PUBLIC ${ARMADILLO_LIBRARIES} mole_C++)

add_executable(hyperbolic1D_upwind hyperbolic1D_upwind.cpp)
target_link_libraries(hyperbolic1D_upwind PUBLIC ${ARMADILLO_LIBRARIES} mole_C++)

add_executable(helloarmadillo helloarmadillo.cc)
target_link_libraries(helloarmadillo ${ARMADILLO_LIBRARIES})

find_package(Eigen3 3.4 REQUIRED NO_MODULE)
add_executable(helloeigen helloeigen.cc)
target_link_libraries(helloeigen Eigen3::Eigen)

add_executable(sparse sparse.cc)
target_link_libraries(sparse Eigen3::Eigen)

add_custom_command(
  COMMAND convection_diffusion
  POST_BUILD
  TARGET convection_diffusion
)

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
  COMMAND parabolic1D
  POST_BUILD
  TARGET parabolic1D
)

add_custom_command(
  # COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_BINARY_DIR}/data.txt
  COMMAND RK2
  POST_BUILD
  TARGET RK2
)

add_custom_command(
  COMMAND schrodinger1D
  POST_BUILD
  TARGET schrodinger1D
)

add_custom_command(
  COMMAND schrodinger2D
  POST_BUILD
  TARGET schrodinger2D
)

add_custom_command(
  COMMAND transport1D
  POST_BUILD
  TARGET transport1D
)

add_custom_command(
  COMMAND hyperbolic1D_upwind
  POST_BUILD
  TARGET hyperbolic1D_upwind
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
