#!/usr/bin/env -S octave -qf
% Solves the 2D Heat equation with Dirichlet boundary conditions

clc
close all

pkg load symbolic
addpath('/usr/share/mole/matlab/')

alpha = 1; % Thermal diffusivity
west = 0; % Domain's limits
east = 1;
south = 0;
north = 0.5;

k = 2; % Operator's order of accuracy
m = 50; % Minimum number of cells to attain the desired accuracy (5)
dx = (east - west) / m; % 0.2000
dy = (north - south) / m; % 0.2000

t = 1; % Simulation time
dt = dx^2 / (3 * alpha); % von Neumann stability criterion for explicit scheme, if k > 2 then /(4*alpha)

L = lap2D(k, m, dx, m, dy); % 2D Mimetic laplacian operator

% 1D Staggered grid
gridx = [west west + dx / 2:dx:east - dx / 2 east]
gridy = [south south + dy / 2:dy:north - dy / 2 north];

BCI = @(x) x;
BCII = @(x) 2 * x;
BCIII = @(x) 3 * x;
BCIV = @(x) 4 * x;

% IC
U = zeros(m + 2, m + 2, 1);
% BC
U(:, 1) = 100; % x = 0, 0 <= y <= 1
U(:, end) = 100; % x = 1, 0 <= y <= 1
U(1, :) = heaviside(gridx -0.5); % 0 <= x <= 1, y = 0
U(end, :) = BCI(100 * gridx); % 0 <= x <= 1, y = 1

[X, Y] = meshgrid(gridx, gridy);

figure('visible', 'off');
mesh(X, Y, U)
saveas(gcf, "parabolic2D.pdf", 'pdfcrop')

% explicit = 1; % 0 = Implicit scheme

% if explicit
%     tic
%     % Explicit
%     L = alpha * dt * L + speye(size(L));

%     % Time integration loop
%     for i = 0:t / dt + 1
%         mesh(X, Y, U)
%         axis([0 1 0 105])
%         str = sprintf('Explicit \t t = %.2f', i * dt);
%         title(str)
%         xlabel('x')
%         ylabel('y')
%         zlabel('T')
%         pause(0.01)
%         U = L * U; % Apply the operator
%     end

%     toc
% else
%     tic
%     % Implicit
%     L = -alpha * dt * L + speye(size(L));

%     % Time integration loop
%     for i = 0:t / dt + 1
%         plot(grid, U, 'o-')
%         axis([0 1 0 105])
%         str = sprintf('Implicit \t t = %.2f', i * dt);
%         title(str)
%         xlabel('x')
%         ylabel('T')
%         pause(0.01)
%         U = L \ U; % Solve a linear system of equations (unconditionally stable)
%         % Next time better do: dL = decomposition(L)
%         % outside the loop, and use dL instead of L to solve the linear system more efficiently.
%     end

%     toc
% end
