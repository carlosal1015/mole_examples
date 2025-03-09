#!/usr/bin/env -S octave -qf
% Solves ODE using explicit RK2 method

h = .05; % Step-size
t = 0:h:5; % Calculates up to y(5)
y = zeros(size(t));
y(1) = 2; % Initial condition
f = @(t, y) sin(t)^2 * y; % f(t, y)

for i = 1:length(t) - 1; % Stages
    k1 = f(t(i), y(i));
    k2 = f(t(i) + h / 2, y(i) + h / 2 * k1);
    y(i + 1) = y(i) + h * k2; % y(i + 1)
end

figure("visible", "off");
plot(t, y, "o", "markersize", .5)
legend("Approximated", "Location", "NorthWest")
title_ = title('2nd-order approximation to $y\left(t\right)$ using RK2 Method');
xlabel_ = xlabel('$t$');
ylabel_ = ylabel('$y\left(t\right)$');
grid on
set(title_, "interpreter", "latex");
set(xlabel_, "interpreter", "latex");
set(ylabel_, "interpreter", "latex");
saveas(gcf, "RK2.pdf", 'pdfcrop')
