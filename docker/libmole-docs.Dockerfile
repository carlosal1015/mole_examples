# Copyleft (c) July, 2025, Oromion

FROM ghcr.io/cpp-review-dune/introductory-review/aur AS build

ARG AUR_PACKAGES="\
  python-sphinx-book-theme \
  python-sphinx_design \
  python-sphinx-togglebutton \
  python-sphinxcontrib-katex \
  python-sphinx-hoverxref \
  "

RUN yay --repo --needed --noconfirm --noprogressbar -Syuq >/dev/null 2>&1 && \
  yay --mflags --nocheck --needed --noconfirm -S ${AUR_PACKAGES} 2>&1 | tee -a /tmp/$(date -u +"%Y-%m-%d-%H-%M-%S" --date='5 hours ago').log >/dev/null && \

FROM ghcr.io/cpp-review-dune/introductory-review/python-fenics-dolfinx

LABEL maintainer="Oromion <caznaranl@uni.pe>" \
  name="Libmole docs Arch" \
  description="Libmole docs in Arch." \
  url="https://github.com/orgs/carlosal1015/packages/container/package/mole_examples%2Fdocs" \
  vcs-url="https://github.com/carlosal1015/mole_examples" \
  vendor="Oromion Aznarán" \
  version="1.0"

ARG PACKAGES="\
  git \
  "

COPY --from=build /tmp/*.log /tmp/
COPY --from=build /home/builder/.cache/yay/*/*.pkg.tar.zst /tmp/

RUN sudo pacman-key --init && \
  sudo pacman-key --populate archlinux && \
  sudo pacman --needed --noconfirm --noprogressbar -Sy archlinux-keyring && \
  sudo pacman --needed --noconfirm --noprogressbar -Syuq >/dev/null 2>&1 && \
  sudo pacman --noconfirm -U /tmp/*.pkg.tar.zst && \
  rm /tmp/*.pkg.tar.zst && \
  sudo pacman --needed --noconfirm --noprogressbar -S ${PACKAGES} && \
  find /tmp/ ! -name '*.log' -type f -exec rm -f {} + && \
  sudo pacman -Scc <<< Y <<< Y && \
  sudo rm -r /var/lib/pacman/sync/*
