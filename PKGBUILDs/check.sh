#!/bin/zsh

archived_pkgbuilds=(
  jupyter_contrib_core
  jupyter_contrib_nbextensions
  jupyter_nbextensions_configurator
  python-jupyter-matlab-proxy-bin
)

for pkgbuild in ${archived_pkgbuilds[@]}; do
  nvchecker -c archived/$pkgbuild/.nvchecker.toml -k keyfile.toml
done
