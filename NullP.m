function N = NullP(A,p)
% Calculate a basis for the null space of A, modulo p:
%    mod(A*N,p) = 0
[L,D,U,rows,cols] = ModLU(A,p);
N = NullPU(U,p);
N(cols,:) = N;