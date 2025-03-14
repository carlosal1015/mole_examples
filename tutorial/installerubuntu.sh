#!/bin/bash

sudo apt-get update
sudo apt-get --no-install-recommends --yes install \
    build-essential cmake git octave \
    libarmadillo-dev libsuperlu-dev libeigen3-dev libgtest-dev
sudo apt-get install --reinstall ca-certificates

git clone --filter=blob:none --depth=1 https://github.com/csrc-sdsu/mole.git
sed -i '/^if(POLICY/,+51 s/^/#/' mole/CMakeLists.txt
sed -i '/^set(LINK_LIBS/,+3 s/^/#/' mole/CMakeLists.txt
sed -i '96i set(LINK_LIBS ${ARMADILLO_LIBRARIES} ${OpenBLAS_LIBRARIES} ${LAPACK_LIBRARY} ${SUPERLU_INSTALL_DIR}/lib/x86_64-linux-gnu/libsuperlu.so)' mole/CMakeLists.txt
sed -i '/^include(/,+9 s/^/#/' mole/tests/cpp/CMakeLists.txt

cmake \
    -S mole \
    -B build \
    -DBUILD_SHARED_LIBS=TRUE \
    -DCMAKE_BUILD_TYPE=None \
    -DCMAKE_CXX_STANDARD=14 \
    -DCMAKE_CXX_COMPILER=g++ \
    -DCMAKE_INSTALL_PREFIX=/usr \
    -Wno-dev
cmake --build build --target mole_C++
sudo cmake --build build --target install
sudo install -d /usr/include/mole
sudo install mole/src/cpp/*.h /usr/include/mole
