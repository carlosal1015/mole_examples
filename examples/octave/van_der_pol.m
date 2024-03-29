#!/usr/bin/env -S octave -qf

% Solves a second order ODE using our implementation of RK4 (mole_MATLAB/rk4.m)

addpath('/usr/share/mole/mole_MATLAB')

%             func   tspan  dt    y0
[t, y] = rk4(@vdp1, [0 20], .1, [2 0]);

plot(t, y(1, :), '-o', t, y(2, :), '-*')
title('Solution of van der Pol''s Equation');
xlabel('t');
ylabel('y');
legend('y_1', 'y_2', 'Location', 'NorthWest')
