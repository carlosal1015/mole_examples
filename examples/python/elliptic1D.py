from pymole.core import lap1D, robinBC1D
import numpy as np
from scipy.sparse.linalg import spsolve
import matplotlib.pyplot as plt  # type: ignore

west = 0
east = 1

k = 6
m = 2 * k + 1
dx = (east - west) / m

L = lap1D(k, m, dx)

a = 1.0
b = 1.0
L = L + robinBC1D(k, m, dx, a, b)

grid = np.append(np.insert(np.arange(west + dx / 2, east, dx), 0, west), east)
U = np.exp(grid)
U[0] = 0  #  West BC
U[-1] = 2 * np.exp(1)  #  East BC
U = spsolve(L, U)  # L\U

plt.plot(grid, U, "o-")
plt.savefig("elliptic1D.pdf")
