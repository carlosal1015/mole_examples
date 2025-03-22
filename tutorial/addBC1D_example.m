#!/usr/bin/env -S octave -qf

addpath('/usr/share/mole/matlab/')
% L U = f
% a0 U + b0 dU/dn = g
[A, b] = addBC1D(A, b, k, m, dx, dc, nc, v)
