#!/usr/bin/env -S octave -qf
% Solves the 1D Poisson Equation with Robin Boundary Conditions and a
% non-constant forcing right hand side using the Mimetic Method with
% MOLE in Octave / MATLAB.
%
%     Δu = f
%
% u : Vertical Displacement of a membrane
% f : Forcing right hand side
% Δ : Laplace Operator

addpath('/usr/share/mole/matlab/')

west = 0; % Domain's limits
east = 1;

k = 6; % Operator's order of accuracy
m = 2 * k + 1; % Minimum number of cells to attain the desired accuracy
dx = (east - west) / m; % Step length

L = lap(k, m, dx); % 1D Mimetic laplacian operator
L_before_name = sprintf("L_before.h5");
save("-hdf5", L_before_name, "L")
figure('visible', 'off');
spy(L);
saveas(gcf, "elliptic1Dsparsebefore.pdf", 'pdfcrop')

% Impose Robin BC on laplacian operator
a = 1;
b = 1;
L = L + robinBC(k, m, dx, a, b);
L_after_name = sprintf("L_after.h5");
save("-hdf5", L_after_name, "L")
spy(L);
saveas(gcf, "elliptic1Dsparseafter.pdf", 'pdfcrop')

% 1D Staggered grid
grid = [west west + dx / 2:dx:east - dx / 2 east];
save("-hdf5", "grid")

% RHS
U = exp(grid)';
U(1) = 0; % West BC
U(end) = 2 * exp(1); % East BC
tic
U = L \ U; % Solve a linear system of equations
toc
save("-hdf5", "U")
% Plot result
plot(grid, U, 'o')
hold on
plot(grid, exp(grid))
legend('Approximated', 'Analytical', 'Location', 'NorthWest')
title('Poisson''s equation with Robin BC')
xlabel('x')
ylabel('u(x)')
saveas(gcf, "elliptic1D.pdf", 'pdfcrop')
