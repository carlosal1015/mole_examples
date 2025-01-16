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

k = 4; % Operator's order of accuracy
m = 10; % Minimum number of cells to attain the desired accuracy
dx = (east - west) / m; % Step length

L = lap(k, m, dx); % 1D Mimetic laplacian operator
figure('visible', 'off');
spy(L);
saveas(gcf, "elliptic1DAznaransparsebefore.pdf", 'pdfcrop')

% Impose Robin BC on laplacian operator
a = 1;
b = 1;
L = L + robinBC(k, m, dx, a, b);
spy(L);
saveas(gcf, "elliptic1DAznaransparseafter.pdf", 'pdfcrop')

% 1D Staggered grid
grid = [west west + dx / 2:dx:east - dx / 2 east];
save("-hdf5", "grid")

% RHS
U = 1 + grid';
U(1) = 0; % West BC
U(end) = 2 * exp(1); % East BC

U = L \ U; % Solve a linear system of equations
save("-hdf5", "U")
% Plot result
plot(grid, U, 'o')
hold on
plot(grid, grid.^2/2 + grid.^3/6 + (grid + 1) * (2/3 * exp(1) - 13/18))
legend('Approximated', 'Analytical', 'Location', 'NorthWest')
title('Poisson''s equation with Robin BC')
xlabel('x')
ylabel('u(x)')
saveas(gcf, "elliptic1DAznaran.pdf", 'pdfcrop')
