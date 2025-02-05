#!/usr/bin/env -S octave-cli -qf
% Nullity test of Divergence operator

addpath('/usr/share/mole/matlab/')

tol = 1e-10;

for k = [2, 4, 6, 8]; % Different orders of accuracy
    m = 2 * k + 1;
    dx = 1 / m;
    D = div(k, m, dx);
    field = ones(m + 1, 1);
    sol = D * field;

    if (norm(sol) > tol)
        fprintf("Test FAILED!\n");
    end

end

fprintf("Test PASSED!\n");
