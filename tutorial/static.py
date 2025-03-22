#!/usr/bin/env python

import matplotlib.pyplot as plt
import numpy as np
from matplotlib.axes import Axes
from matplotlib.figure import Figure
from pymole.core import div

fig: Figure
ax: Axes

plt.style.use("seaborn-v0_8-white")

fig, ax = plt.subplots(layout="constrained")
ax.spy(x, precision=0.1, markersize=5)
plt.savefig(
    "1.pdf",
    transparent=True,
    bbox_inches="tight",
)
