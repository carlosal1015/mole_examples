#!/usr/bin/env python

import sys
from typing import Annotated, Literal, TypeVar

import matplotlib.pyplot as plt
import numpy as np
import numpy.typing as npt
from matplotlib.animation import FFMpegWriter, FuncAnimation
from matplotlib.axes import Axes
from matplotlib.figure import Figure
from tqdm import tqdm

plt.style.use("seaborn-v0_8-white")

DType = TypeVar(name="DType", bound=np.generic)
ArrayN = Annotated[npt.NDArray[DType], Literal["N"]]


def U(
    x: ArrayN[np.float64], a: float = 1.0, b: float = 1.0, c: float = 1.0
) -> ArrayN[np.float64]:
    """Params
    a: height of the curve's peak
    b: position of the center of the peak
    c: width of the bell

    See https://en.wikipedia.org/wiki/Gaussian_function
    """

    return a * np.exp(-np.divide(np.power(x - b, 2), 2 * np.power(c, 2)))


x: ArrayN[np.float64] = np.linspace(start=0, stop=10, num=301)
t: ArrayN[np.float64]
Δt: float
t, Δt = np.linspace(start=0, stop=10, num=101, retstep=True)

a: float = 5
b: float = 2
c: float = 0.2
speed: float = 0.5
fig: Figure
ax: Axes
fig, ax = plt.subplots(layout="constrained")
(ln,) = ax.plot(
    [],
    [],
    color="DarkBlue",
    label="Exacta",
    linestyle="solid",
    linewidth=0.5,
)
ax.set_xlim(left=x[0], right=x[-1])
ax.set_ylim(bottom=0, top=U(x=x, a=a).max())
ax.grid(c="gray", linewidth=0.1, linestyle="dashed")
ax.set_xlabel(xlabel=r"$x$ (m)")
ax.set_ylabel(ylabel=r"$y$ (m)")
ax.legend(loc="upper left")
ax.set_aspect("equal", adjustable="box")
ax.spines["bottom"].set_color("none")
ax.spines["top"].set_alpha(alpha=0.8)
ax.spines["top"].set_edgecolor(color="gray")
ax.spines["top"].set_linewidth(w=0.5)
ax.spines["left"].set_alpha(alpha=0.8)
ax.spines["left"].set_edgecolor(color="gray")
ax.spines["left"].set_linewidth(w=0.5)
ax.spines["right"].set_alpha(alpha=0.8)
ax.spines["right"].set_edgecolor(color="gray")
ax.spines["right"].set_linewidth(w=0.5)


def init():
    ln.set_data(x, U(x=x, a=a, b=b, c=c))

    return (ln,)


def update(frame):
    ln.set_data(x, U(x=x - speed * frame * Δt, a=a, b=b, c=c))
    ax.set_title(
        label=rf"Travel wave $U\left(x - ct\right)=U\left(x, t={frame * Δt:.2f}s\right)$ with $c={speed}$ "
        + r"$\unit{\metre\per\second}$",
        loc="center",
        fontsize=12,
        wrap=True,
    )

    return (ln,)


anim = FuncAnimation(
    fig=fig,
    func=update,
    frames=tqdm(iterable=range(t.size), file=sys.stdout, colour="green"),
    interval=1,
    init_func=init,
    blit=True,
).save(
    filename="animation.mkv",
    writer=FFMpegWriter(
        fps=90,
        codec="libx265",
        metadata={
            "subject": "Numerical Analysis",
            "title": "Animation",
            "author": "Carlos Aznarán",
            "genre": "Mathematics",
            "copyright": "2025",
            "srcform": "Matplotlib 3.10.0",
            "comment": "Numerical Simulation for advection PDE",
        },
    ),
    dpi=300,
    savefig_kwargs={"transparent": True, "facecolor": "none"},
)
