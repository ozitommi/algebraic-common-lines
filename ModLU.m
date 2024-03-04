function [L,D,U,rows,cols] = ModLU(A,p)
%
% LU-factorization of A, modulo p:
%     A(rows,cols) - mod(L * diag(D)*U,p)
%
[m,n] = size(A);

% inverses in mod-p:
%     mod(k*invp(k+1)) = 0 if k==0; 1 otherwise
invp = 2:p-2;
for i = 2:p-2; invp = mod(invp.*[2:p-2],p); end
invp = [0,1,invp,p-1];

% Initialize outputs:
L = eye(m); U = A;
rows = 1:m;
cols = 1:n;

% Sweep
for i = 1:m
   % Pivoting
   [row,col] = find(U(i:end,:));
   if isempty(row); break; end
   row = row(1)+i-1; col = col(1);

   r = 1:m; r(i) = row; r(row) = i;
   c = 1:n; c(i) = col; c(col) = i;
   ri = rows(i); rows(i) = rows(row); rows(row)=ri;
   ci = cols(i); cols(i) = cols(col); cols(col)=ci;

   rinv = 1:m; rinv(r) = 1:m;
   U = U(r,c); L=L(r,r);

   % Gaussian elimination
   L(i+1:end,i    ) = mod(invp(U(i,i)+1) * U(i+1:end,i),p);
   U(i+1:end,i:end) = mod(U(i+1:end,i:end) + (p-L(i+1:end,i)) * U(i,i:end),p);
end

% Factorize diagonal
D = zeros(m,1); D(1:min(m,n)) = diag(U);
U = mod(diag(invp(D+1)) * U,p );