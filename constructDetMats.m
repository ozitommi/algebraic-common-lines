function [D1,D2] = constructDetMats(var)

quad2 = var.quad;
indices1mat = var.ind1mat;
indices2mat = var.ind2mat;
missing = var.missing;
m = size(indices1mat,2);

%% Construct the Jacobian matrices for the two sets of determinant equations

% diagonal elements
R = repelem(diag(double(indices1mat)),size(quad2,1),2);
M = double(repmat(missing(:,[1,2]),m,1));
col = repmat(quad2(:,[1,2]),m,1);
col(not(M == R)) = 0;
diagonal = (1/2)*sum((reshape(sum(col,2),size(quad2,1),m)).^2,1);
% off-diagonal elements
num = size(quad2,1)*((m-1):-1:1);
indices1 = diag(double(indices1mat));
indices1(end) = [];
cross = repelem(indices1,[num]);
B = triu(double(indices1mat),1)';
u = tril(true(size(B)),-1);
v = B(u);
M1 = double(repmat(missing(:,1),size(v,1),1));
M2 = double(repmat(missing(:,2),size(v,1),1));
col = repmat(quad2(:,[1,2]),size(v,1),1);
v = repelem(v,size(quad2,1));
M = [M1,M2,cross,v];
miss1_ii = M(:,1) == M(:,3);
miss2_ii = M(:,2) == M(:,3);
miss1_ij = M(:,1) == M(:,4);
miss2_ij = M(:,2) == M(:,4);
IND = (miss1_ii | miss2_ii) & (miss1_ij | miss2_ij);
col([not(IND),not(IND)]) = 0;
col = -prod(col,2);
col = sum(reshape(col,size(quad2,1),size(col,1)/size(quad2,1)),1);

D1_small = triu(ones(m))' - eye(m);
D1_small(D1_small == 1) = col;
D1_small = D1_small + diag(diagonal);
D1_small = D1_small + D1_small';
D1 = zeros(m+1);
D1(2:m+1,2:m+1) = D1_small;

% diagonal elements
R = repelem(diag(double(indices2mat)),size(quad2,1),2);
M = double(repmat(missing(:,[2,3]),m,1));
col = repmat(quad2(:,[2,3]),m,1);
col(not(M == R)) = 0;
diagonal = (1/2)*sum((reshape(sum(col,2),size(quad2,1),m)).^2,1);
% off-diagonal elements
num = size(quad2,1)*((m-1):-1:1);
indices2 = diag(double(indices2mat));
indices2(end) = [];
cross = repelem(indices2,[num]);
B = triu(double(indices2mat),1)';
u = tril(true(size(B)),-1);
v = B(u);
M1 = double(repmat(missing(:,2),size(v,1),1));
M2 = double(repmat(missing(:,3),size(v,1),1));
col = repmat(quad2(:,[2,3]),size(v,1),1);
v = repelem(v,size(quad2,1));
M = [M1,M2,cross,v];
miss1_ii = M(:,1) == M(:,3);
miss2_ii = M(:,2) == M(:,3);
miss1_ij = M(:,1) == M(:,4);
miss2_ij = M(:,2) == M(:,4);
IND = (miss1_ii | miss2_ii) & (miss1_ij | miss2_ij);
col([not(IND),not(IND)]) = 0;
col = -prod(col,2);
col = sum(reshape(col,size(quad2,1),size(col,1)/size(quad2,1)),1);

D2_small = triu(ones(m))' - eye(m);
D2_small(D2_small == 1) = col;
D2_small = D2_small + diag(diagonal);
D2_small = D2_small + D2_small';
D2 = zeros(m+1);
D2(1:m,1:m) = D2_small;

end