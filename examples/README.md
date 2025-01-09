There are two options, use [`libmole`](https://aur.archlinux.org/packages/libmole)
from AUR for latest stable version or this
[PKGBUILD](https://raw.githubusercontent.com/carlosal1015/mole_examples/refs/heads/main/PKGBUILDs/libmole-git/PKGBUILD)
for take in account the last development features.

```console
$ pacman -Qi libmole-git                
Name            : libmole-git
Version         : 1.0.r70.gb72198d-1
Description     : The Mimetic Operators Library Enhanced
Architecture    : x86_64
URL             : https://github.com/csrc-sdsu/mole
Licenses        : GPL-3.0-only
Groups          : None
Provides        : mole
Depends On      : armadillo
Optional Deps   : matlab: for MATLAB support
                  octave: for Octave support [installed]
                  eigen: for the sparse LU factorization [installed]
Required By     : None
Optional For    : None
Conflicts With  : mole
Replaces        : None
Installed Size  : 12.01 MiB
Packager        : Unknown Packager
Build Date      : Thu 09 Jan 2025 09:34:17 AM -05
Install Date    : Thu 09 Jan 2025 09:36:58 AM -05
Install Reason  : Explicitly installed
Install Script  : No
Validated By    : None
```

```console
$ cd examples
$ cp -R /usr/share/doc/mole/examples/ .
```