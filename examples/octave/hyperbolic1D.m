#!/usr/bin/env -S octave -qf
% Solves the 1D Advection equation with periodic boundary conditions

addpath('/usr/share/mole/matlab/')

a = 1; % Velocity
west = 0; % Domain's limits
east = 1;

k = 2; % Operator's order of accuracy
m = 50; % Number of cells
dx = (east - west) / m;

t = 1; % Simulation time
dt = dx / abs(a); % CFL condition for explicit schemes
alpha = abs(a) * dt / dx;

D = div(k, m, dx); % 1D Mimetic divergence operator% size(D)
save("-hdf5", "D_before.h5", "D")
figure('visible', 'off');
spy(D);
saveas(gcf, "hyperbolic1D_divergence_sparsebefore.pdf", 'pdfcrop')
I = interpol(m, 0.5); % 1D 2nd order interpolator% 0<=c<=1% size(I);
spy(I);
saveas(gcf, "hyperbolic1D_interpolator_sparse.pdf", 'pdfcrop')
save("-hdf5", "I_name.h5", "I")

% 1D Staggered grid
grid = [west west + dx / 2:dx:east - dx / 2 east];
size(grid);
% IC
U = sin(2 * pi * grid)'; % 100 * ones(m + 2, 1) or repmat(100, [m + 2, 1])

% Periodic BC imposed on the divergence operator
D(1, 2) = 1 / (2 * dx);
D(1, end - 1) = -1 / (2 * dx);
D(end, 2) = 1 / (2 * dx);
D(end, end - 1) = -1 / (2 * dx);

% Premultiply out of the time loop (since it doesn't change)
D = -a * dt * 2 * D * I;
% One could also have said: D = -a*dt*2*I*D if the grid
% was defined as: grid = west : dx : east (nodal)
save("-hdf5", "D_after.h5", "D")
spy(D);
saveas(gcf, "hyperbolic1D_divergence_sparseafter.pdf", 'pdfcrop')

U2 = U + D / 2 * U; % Compute one step using Euler's method

figure('visible', 'off');
% Time integration loop
for i = 1:t / dt
    plot(grid, U2, 'o-')% Plot approximation
    hold on
    plot(grid, sin(2 * pi * (grid - a * i * dt)))% Plot exact solution
    hold off
    str = sprintf('t = %.2f', i * dt);
    title(str)
    xlabel('x')
    ylabel('u(x, t)')
    axis([west east -1.5 1.5])
    pause(0.04)
    U3 = U + D * U2; % Compute next step using Leapfrog scheme
    U = U2;
    U2 = U3;
    plot_name = sprintf("hyperbolic1D%i.pdf", i);
    saveas(gcf, plot_name, 'pdfcrop')
end
