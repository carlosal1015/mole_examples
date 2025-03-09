#!/bin/bash

# [1 / 3] Update the system and install developer tools
sudo pacman --needed --noconfirm -Syu base-devel git
# [1.5 / 3] Optionally install Intel MKL as a replacement for LAPACK linear algebra library
sudo pacman -S intel-oneapi-mkl # or depending on your needs: intel-oneapi-basekit, intel-oneapi-hpckit, lapack, blas-openblas

# [2 / 3] Install armadillo from |\href{https://aur.archlinux.org/armadillo.git}{https://aur.archlinux.org/armadillo.git}|
git clone https://aur.archlinux.org/armadillo.git
pushd armadillo
makepkg -s --noconfirm
popd

# [3 / 3] Install MOLE C++/Octave from |\href{https://aur.archlinux.org/libmole.git}{https://aur.archlinux.org/libmole.git}|
git clone https://aur.archlinux.org/libmole.git
pushd libmole
makepkg -s --noconfirm
popd
