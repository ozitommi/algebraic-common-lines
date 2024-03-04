function [C,ind] = heterogeneousCommonLines(m,n)

% m is the number of clusters
% n is the number of common lines per cluster

% create partial common lines matrix
C = (1 - (-1))*rand(m*2*n,m*n) + (-1);
idx_block = logical(kron(eye(m*n),ones(2,1)));
C(idx_block) = 0;

% create pure common lines matrices
CLMs = cell(1,m);
for i = 1:m
    [A,~,~] = create_A(n);
    CLMs{i} = A;
end

% create the random permutations of rotations
ind = reshape(randperm(m*n),m,n);


for i = 1:m
    cluster_perm = ind(i,:);
    rowsC = zeros(m*2*n,m*n);
    colsC = zeros(m*2*n,m*n);
    rowsC(s3(cluster_perm),:) = 1;
    colsC(:,cluster_perm) = 1;
    indC = logical(rowsC) & logical(colsC);
    A = CLMs{i};
    [~,I] = sort(cluster_perm);
    A = A(s3(I'),I');
    D = C';
    D(indC') = A';
    C = D';
end

end