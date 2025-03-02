#!/bin/zsh

function verification() {
  if hash conda 2>/dev/null; then
    echo "You have conda installed."
    active_environment
  else
    echo "Install miniconda3-bin or anaconda from AUR. For example:"
    echo "yay -Syu miniconda3-bin"
  fi
}

function active_environment() {
  local major_version=3
  local minor_version=13
  local micro_version=2
  echo "Activation environment start"
  echo "By default we using python ${major_version}.${minor_version}.${micro_version}"
  # conda init zsh
  # conda config --set auto_activate_base false
  export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$HOME/MATLAB/bin/glnxa64
  # python -m venv --system-site-packages $PWD/.venv${major_version}${minor_version}${micro_version}
  # source $PWD/.venv${major_version}${minor_version}${micro_version}/bin/activate
  # pip install matlabengine==24.2.2
  [ -d $PWD/.venv-${major_version}${minor_version}${micro_version} ] || conda env create -f environment${major_version}${minor_version}${micro_version}.yml --prefix $PWD/.venv${major_version}${minor_version}${micro_version}
  conda activate $PWD/.venv${major_version}${minor_version}${micro_version} # matlab2024b
}

verification
