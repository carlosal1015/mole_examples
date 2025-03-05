#!/bin/bash

# [1 / 3] Update the system
sudo pacman --noconfirm -Syu
# [1.5 / 3] Optionally install Intel MKL as a replacement for LAPACK linear algebra library
sudo pacman --noconfirm -S intel-oneapi-mkl # or one of them depending on your needs: intel-oneapi-basekit, intel-oneapi-hpckit

# [2 / 3] Install armadillo
git clone https://aur.archlinux.org/armadillo.git
pushd armadillo
makepkg -s --noconfirm
popd

# [3 / 3] Install MOLE C++/Octave
git clone https://aur.archlinux.org/libmole.git
pushd libmole
makepkg -s --noconfirm
popd

sudo apt update
sudo apt upgrade
sudo apt install cmake libarmadillo-dev libsuperlu-dev libeigen3-dev octave build-essential git libgtest-dev
git clone https://github.com/csrc-sdsu/mole.git
cd mole
