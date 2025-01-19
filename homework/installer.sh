#!/bin/bash

# [1 / 3] Actualizar el sistema
sudo pacman --noconfirm -Syu
# [1.5 / 3] Opcionalmente instale Intel MKL como reemplazo de LAPACK
sudo pacman --noconfirm -S intel-oneapi-mkl # o también intel-oneapi-basekit intel-oneapi-hpckit

# [2 / 3] Instale armadillo
git clone https://aur.archlinux.org/armadillo.git
pushd armadillo
makepkg -s --noconfirm
popd

# [3 / 3] Instale MOLE C++ / Octave
git clone https://aur.archlinux.org/libmole.git
pushd libmole
makepkg -s --noconfirm
popd
