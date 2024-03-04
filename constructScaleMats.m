function [L,R] = constructScaleMats(M)

n = size(M,1);

%% Construct the Jacobian matrices for the set of norm equations

diagonalL = sum(M.^2,2);
diagonalR = sum(M.^2,1);
ind_upper = logical(triu(ones(n),1));
M_trans = M';
off = -M(ind_upper).*M_trans(ind_upper);
L = triu(ones(n),1);
L(ind_upper) = off;
R = L;
L = L + L' + diag(diagonalL);
R = R + R' + diag(diagonalR);

end