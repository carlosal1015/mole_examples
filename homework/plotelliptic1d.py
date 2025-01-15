#!/usr/bin/env python

import sys
from h5py import File
import numpy as np
import matplotlib.pyplot as plt

try:
    with File(name="../../examples/cpp/build/elliptic1d_grid.h5", mode="r") as f:
        grid = np.array(f["elliptic1d_grid"][:][0])
    with File(name="../../examples/cpp/build/elliptic1d_solution.h5", mode="r") as f:
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
# ax.set_xticklabels(labels=ax.get_xticklabels(which="major"), fontdict=dict(size=8))
ax.scatter(x=grid, y=solution, c="red", s=2, label="Mimetic solution")
ax.plot(
    grid,
    exact,
    alpha=0.8,
    label="Exact solution",
    linestyle="dashed",
    linewidth=0.8,
)
ax.legend(loc="best")
ax.set_title(
    label=r"Exact solution for $\diff[2]{{u}}{{x}}=e^{{x}}$ with Robin boundary conditions",
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

fig, ax = plt.subplots(layout="constrained")
ax.set_xlabel(xlabel=r"$x$")
ax.grid(c="gray", linewidth=0.1, linestyle="dashed")
ax.set_aspect("equal", adjustable="box")
plt.savefig("elliptic1Derror.pdf", transparent=True, bbox_inches="tight")
plt.clf()
