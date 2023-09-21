function [quad1,quad2] = checkQuadrics(A)

% Produces the values of the norms of the entries of A (quad1) and the
% determinants of the submatrices of A (quad2).

% The norm equations are satisfied if the two columns of quad1 are equal.

% The determinant equations are satisfies if the second, fourth, and sixth 
% columns of quad2 are equal. These columns correspond to the three columns 
% of equalities on the Overleaf document. The first, third, fifth, and
% seventh columns denote the column numbers from which the determinant
% equations come from.

n = size(A,2);

idx_block = logical(kron(eye(n),ones(2,1)));
A(idx_block) = 0;

% check the norm equations
M = sqrt(reshape(sum(reshape(A.^2,2,n^2),1),n,n));
ind_ij = nchoosek(1:n,2);
ind_ji = [ind_ij(:,2),ind_ij(:,1)];
quad1 = [M(sub2ind(size(M),ind_ij(:,1),ind_ij(:,2))),M(sub2ind(size(M),ind_ji(:,1),ind_ji(:,2)))];

% check the determinant equations
quad2 = [];
for i = 1:(n-2)
    for j = (i+1):(n-1)
        for k = (j+1):n

            det1 = det([A(s3(i),j),A(s3(i),k)]);
            det2 = -det([A(s3(j),i),A(s3(j),k)]);
            det3 = det([A(s3(k),i),A(s3(k),j)]);
            quad2 = [quad2; j, det1, i, det2, k, det3, j];

        end
    end
end

end