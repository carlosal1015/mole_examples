#!/bin/bash

# [1/5] Update the system and install developer tools
sudo pacman --needed --noconfirm -Syu base-devel git
# [2/5] Optionally install Intel MKL as a replacement for LAPACK linear algebra library
sudo pacman -S intel-oneapi-mkl # or depending on your needs: intel-oneapi-basekit, intel-oneapi-hpckit, lapack, blas-openblas

# [3/5] Install armadillo from |\href{https://aur.archlinux.org/packages/armadillo}{https://aur.archlinux.org/armadillo.git}|
git clone https://aur.archlinux.org/armadillo.git
pushd armadillo
makepkg -s --noconfirm
popd

# [4/5] Install MOLE C++/Octave from |\href{https://aur.archlinux.org/packages/libmole}{https://aur.archlinux.org/libmole.git}|
git clone https://aur.archlinux.org/libmole.git
pushd libmole
makepkg -s --noconfirm
popd

# [5/5] Install utilities
sudo pacman -S ffmpeg gtest python-matplotlib python-scipy texlive
# matlab -nodisplay -nosplash -nodesktop
