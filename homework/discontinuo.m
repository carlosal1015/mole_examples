#!/usr/bin/env -S octave -qf

pkg load symbolic

x = 0:0.005:1;
y = 0:0.005:0.5; % debe ser de 0 a 0.5
[X, Y] = meshgrid(x, y);

figure('visible', 'off');
mesh(X, Y, heaviside(X - 0.25) - heaviside(X - 0.3));
saveas(gcf, "discontinuo.pdf", 'pdfcrop')
