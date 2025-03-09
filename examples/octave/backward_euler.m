#!/usr/bin/env -S octave -qf
% Solves ODE using backward Euler method

h = .05; % Step-size
t = 0:h:5; % Calculates up to y(5)
y = zeros(size(t));
y(1) = 2; % Initial condition
f = @(t, y) sin(t)^2 * y; % f(t, y)

for i = 1:length(t) - 1; % Stages
    old_y = y(i);
    y(i + 1) = fzero(@(y) y - h * f(t(i + 1), y) - old_y, old_y); % Backward Euler
end

figure("visible", "off");
plot(t, y, "o", "markersize", .5)
legend("Approximated", "Location", "NorthWest")
title_ = title('Approximation to $y\left(t\right)$ using Backward Euler Method');
xlabel_ = xlabel('$t$');
ylabel_ = ylabel('$y\left(t\right)$');
grid on
set(title_, "interpreter", "latex");
set(xlabel_, "interpreter", "latex");
set(ylabel_, "interpreter", "latex");
saveas(gcf, "backward_euler.pdf", 'pdfcrop')
