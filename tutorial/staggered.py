#!/usr/bin/env python

# Copyright (C) 2025 Carlos Aznarán <caznaranl@uni.pe>

# This file is part of https://github.com/carlosal1015/mole_examples .
# https://github.com/carlosal1015/mole_examples is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.

# https://github.com/carlosal1015/mole_examples is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with https://github.com/carlosal1015/mole_examples .  If not, see <http://www.gnu.org/licenses/>.


import matplotlib.pyplot as plt
import numpy as np

# from jaxtyping import Array, Float
from matplotlib.axes import Axes
from matplotlib.figure import Figure

plt.style.use("seaborn-v0_8-white")

arr = np.zeros(shape=(1, 14))
# x: Float[Array, "dim"] = np.linspace(start=0, stop=2, num=200)

fig: Figure
ax: Axes
fig, ax = plt.subplots(layout="constrained")
ax.imshow(arr, cmap="Blues")
ax.set_xticklabels([])
ax.set_yticklabels([])

xticks, dxticks = np.linspace(
    start=ax.get_xticks()[0],
    stop=ax.get_xticks()[-1],
    num=arr.shape[1] + 1,  # 15 points == 14 intervals
    retstep=True,
)
yticks, dyticks = np.linspace(
    start=ax.get_yticks()[0],
    stop=ax.get_yticks()[-1],
    num=arr.shape[0] + 1,  # 2 points == 1 interval
    retstep=True,
)
ax.set_xticks(xticks)
ax.set_yticks(yticks)
ax.set_axisbelow(True)
ax.set_frame_on(False)
ax.tick_params(tick1On=False)

for xtick in xticks[1:-1]:
    ax.scatter(x=xtick, y=yticks[0] + dyticks / 2, s=5, c="blue")
    ax.scatter(x=xtick + dxticks / 2, y=yticks[0] + dyticks / 2, s=5, c="red")
ax.scatter(x=xticks[0], y=yticks[0] + dyticks / 2, s=5, c="black")
ax.scatter(x=xticks[0] + dxticks / 2, y=yticks[0] + dyticks / 2, s=5, c="red")
ax.scatter(x=xticks[-1], y=yticks[0] + dyticks / 2, s=5, c="black")

ax.annotate(
    "",
    (xticks[1], yticks[1] - dyticks / 12),
    (xticks[2], yticks[1] - dyticks / 12),
    arrowprops={"arrowstyle": "<->, head_width=0.5"},
    fontsize=4,
)
ax.text(
    x=xticks[1] + dxticks / 2.5,
    y=yticks[1] + dyticks / 8,
    s=r"$\Delta x$",
    fontsize=4,
)
ax.annotate(
    "",
    (xticks[3] - dxticks / 2, yticks[1] - dyticks / 2),
    (xticks[3], yticks[1] - dyticks / 2),
    arrowprops={"arrowstyle": "<->, head_width=0.5"},
    fontsize=4,
)
ax.text(
    x=xticks[3] - dxticks / 3,
    y=yticks[1] - dyticks / 4,
    s=r"$\frac{\Delta x}{2}$",
    fontsize=4,
)
plt.grid(c="gray", lw=0.25)
plt.savefig("staggered.pdf", transparent=True, bbox_inches="tight")
plt.close()

# Domain's limits
west: float = 0
east: float = 1

k: int = 6  # Operator's order of accuracy
m: int = 2 * k + 1  # Minimum number of cells to attain the desired accuracy
dx: float = (east - west) / m  # Step length
# 1D Staggered grid
grid = np.append(np.insert(np.arange(west + dx / 2, east, dx), 0, west), east)
print(grid.shape)
