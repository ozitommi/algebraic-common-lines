function N = NullPU(U,p)
% for an upper triangular matrix, calculate a base for the null space modulo p:
%   U * N = 0

n = size(U,2);
rank = size(find(diag(U)),1);
A = U(1:rank,:);
for i=rank:-1:2
    A(1:i-1,:) = mod(A(1:i-1,:) + (p-1) * A(1:i-1,i) * A(i,:),p);
end
N = [mod(p-A(:,rank+1:end),p); eye(n-rank)];