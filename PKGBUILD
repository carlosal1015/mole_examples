# Maintainer: Carlos Aznarán <caznaranl@uni.pe>
pkgname=mole
pkgver=3.0
pkgrel=1
pkgdesc="Mimetic Operators Library Enhanced"
url="https://github.com/jcorbino/${pkgname}" # csrc-sdsu
license=(GPL3)
arch=(x86_64)
depends=(armadillo openblas)
makedepends=(cmake doxygen graphviz eigen)
optdepends=('matlab: for MATLAB support'
  'octave: for Octave support'
  'eigen: for the sparse LU factorization') # openmp
source=(${pkgname}-${pkgver}.tar.gz::${url}/archive/v${pkgver}.tar.gz
  https://raw.githubusercontent.com/carlosal1015/mole_examples/main/patches/include.patch)
sha512sums=('5a5eff6bafe2ad8d529611d8bb7b3176b2d39ed9cc570dd1c6f08978dd196650a1c74b4e67bc62739c7aaea9d5fe994ea1b14d61a0bfcc33c5a0157c8abf5dda'
  'f35f4a39340f645a4903bec32c791cf77b90e5bc1e5e13acf53d9dbd2d6fa6e8b02588d53b35dac2db26a0cdc94c1c54acec9925e7c91050037cd7862ac8ea91')

prepare() {
  cd ${pkgname}-${pkgver}
  patch -p1 -i ../include.patch
}

build() {
  cd ${pkgname}-${pkgver}
  make SHARED_LIB=1 EIGEN=1
  doxygen
}

package() {
  cd ${pkgname}-${pkgver}

  install -Dm 755 mole_C++/libmole.so -t "${pkgdir}/usr/lib"

  install -d ${pkgdir}/usr/include/${pkgname}
  install mole_C++/*.h ${pkgdir}/usr/include/${pkgname}

  # install docs
  install -d ${pkgdir}/usr/share/doc/${pkgname}
  mv doc_C++ ${pkgdir}/usr/share/doc/${pkgname}
  mv doc_MATLAB ${pkgdir}/usr/share/doc/${pkgname}

  # install tutorials
  install -d ${pkgdir}/usr/share/doc/${pkgname}/examples
  mv examples_C++ ${pkgdir}/usr/share/doc/${pkgname}/examples
  mv examples_MATLAB ${pkgdir}/usr/share/doc/${pkgname}/examples

  install -Dm 644 LICENSE -t "${pkgdir}/usr/share/licenses/${pkgname}"
}
