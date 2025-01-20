#!/usr/bin/env python

import sys

import matplotlib.pyplot as plt
import numpy as np
from h5py import File

try:
    with File(name="../examples/cpp/build/elliptic1d_grid.h5", mode="r") as f:
        grid = np.array(f["elliptic1d_grid"][:][0])
    with File(name="../examples/cpp/build/elliptic1d_solution.h5", mode="r") as f:
        solution = np.array(f["elliptic1d_solution"][:][0])
except OSError as err:
    print(f"OS error: {err}")
    sys.exit(0)

exact = np.exp(grid)
fig, ax = plt.subplots(layout="constrained")
ax.set_xlabel(xlabel=r"$x$")
ax.set_ylabel(ylabel=r"$u\left(x\right)$")
ax.set_xlim(left=grid[0] - 5e-3, right=grid[-1] + 5e-3)
ax.set_ylim(bottom=exact.min() - 5e-3, top=exact.max() + 5e-3)
ax.set_xticks(ticks=np.linspace(start=grid[0], stop=grid[-1], num=6))
ax.set_yticks(
    ticks=np.linspace(
        start=solution.min(), stop=np.ceil(solution[-1] * 10) / 10, num=10
    )
)
ax.set_xticklabels(labels=ax.get_xticklabels(which="major"), fontdict=dict(size=8))
ax.set_yticklabels(labels=ax.get_yticklabels(which="major"), fontdict=dict(size=8))
ax.scatter(x=grid, y=solution, c="red", s=2, label="Solución mimética")
ax.plot(
    grid,
    exact,
    alpha=0.8,
    label="Solución exacta",
    linestyle="dashed",
    linewidth=0.8,
)
ax.legend(loc="best")
ax.set_title(
    label=r"Solución exacta para $\diff[2]{{u}}{{x}}=e^{{x}}$ con condiciones de frontera Robin",
    loc="center",
    fontsize=12,
)
ax.grid(c="gray", linewidth=0.1, linestyle="dashed")
ax.set_aspect("equal", adjustable="box")
ax.spines["bottom"].set_color("none")
ax.spines["top"].set_color("none")
ax.spines["left"].set_color("none")
ax.spines["right"].set_color("none")
plt.savefig("elliptic1D.pdf", transparent=True, bbox_inches="tight")
plt.clf()

error = np.abs(exact - solution)
fig, ax = plt.subplots(layout="constrained")
ax.scatter(x=grid, y=error, c="red", s=2)
ax.set_xticks(np.linspace(start=grid[0], stop=grid[-1], num=5))
ax.set_xlabel(xlabel=r"$x$")
ax.set_ylabel(ylabel=r"$\left|u\left(x_{j-\frac12}\right)-u_{j-\frac12}\right|$")
ax.set_xlim(left=grid[0] - 5e-3, right=grid[-1] + 5e-3)
ax.set_ylim(
    bottom=np.floor(error.min() * 1e10) * 1e-10, top=np.ceil(error.max() * 1e10) * 1e-10
)
ax.set_xticks(ticks=np.linspace(start=grid[0], stop=grid[-1], num=6))
ax.set_yticks(
    ticks=np.linspace(
        start=np.floor(error.min() * 1e10) * 1e-10,
        stop=np.ceil(error.max() * 1e10) * 1e-10,
        num=4,
    )
)
ax.set_title(
    label="Error puntual",
    loc="center",
    fontsize=12,
)
ax.grid(c="gray", linewidth=0.1, linestyle="dashed")
ax.spines["bottom"].set_color("none")
ax.spines["top"].set_color("none")
ax.spines["left"].set_color("none")
ax.spines["right"].set_color("none")
plt.savefig("elliptic1Derror.pdf", transparent=True, bbox_inches="tight")
plt.clf()

# for m in range(10, 1000, 100):
#     try:
#         with File(name=f"sandbox/grid{m}.h5", mode="r") as f:
#             grid = np.array(f["elliptic1d_grid"][:][0])
#         with File(name="../examples/cpp/build/elliptic1d_solution.h5", mode="r") as f:
#             solution = np.array(f["elliptic1d_solution"][:][0])
#     except OSError as err:
#         print(f"OS error: {err}")
#         sys.exit(0)
#     error = np.abs(exact - solution)

# Δx = np.logspace(start=-15, stop=0, num=16, base=2)
# fig, ax = plt.subplots(layout="constrained")
# ax.loglog(
#     Δx,
#     Δx,
#     "--",
#     mfc="none",
#     label=r"$\mathcal{O}\left(\Delta x\right)$",
#     linewidth=0.8,
# )
# ax.loglog(
#     Δx,
#     np.power(Δx, 2),
#     "--",
#     mfc="none",
#     label=r"$\mathcal{O}\left(\Delta x^{2}\right)$",
#     linewidth=0.8,
# )
# ax.set_xlabel(r"Tamaño malla equivalente $\Delta x$")
# ax.set_ylabel("Error")
# ax.set_xlim(left=Δx[0], right=Δx[-1])
# ax.set_ylim(bottom=1e-5, top=1e-1)
# ax.grid(c="gray", linewidth=0.1, linestyle="dashed")
# ax.legend(loc="upper left", shadow=True)
# plt.savefig("elliptic1Dconvergenceorder.pdf", transparent=True, bbox_inches="tight")
# plt.clf()
