function quad1 = checkNorms(A)

% Produces the values of the norms of the entries of A (quad1).

% The norm equations are satisfied if the two columns of quad1 are equal.

% The last two rows of quad1 are the i and j indices of r_ij

n = size(A,2);

idx_block = logical(kron(eye(n),ones(2,1)));
A(idx_block) = 0;

% check the norm equations
M = sqrt(reshape(sum(reshape(A.^2,2,n^2),1),n,n));
ind_ij = nchoosek(1:n,2);
ind_ji = [ind_ij(:,2),ind_ij(:,1)];
quad1 = [M(sub2ind(size(M),ind_ij(:,1),ind_ij(:,2))),M(sub2ind(size(M),ind_ji(:,1),ind_ji(:,2))),ind_ij];

end