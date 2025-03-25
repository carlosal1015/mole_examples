#!/usr/bin/env python

from pymole.core import grad1D, div1D
import numpy as np

k = 2
n = 5
x, Δx = np.linspace(start=0, stop=n, num=n + 1, retstep=True)
u = np.exp(x)
print(x.shape)
print(u.shape)

G = grad1D(k=2, m=n, dx=Δx)
D = div1D(k=2, m=n, dx=Δx)
print(G.shape)
print(D.shape)

# print(G.todense() * u)
# print(G.todense())
