function [D1_mu,D2_mu,D1_tau,D2_tau] = constructDetMats(var)

quad2 = var.quad;
quad2_sqrt = sign(quad2).*sqrt(abs(quad2));
missing_mu = var.missing_mu;
missing_tau1 = var.missing_tau1;
missing_tau2 = var.missing_tau2;
n = var.n;
p = size(quad2,1);

%% Construct the Jacobian matrices for the two sets of determinant equations

%% jac1 mu

% diagonal elements
R = repelem((1:n)',p,2);
M = double(repmat(missing_mu(:,[1,2]),n,1));
col = repmat(quad2_sqrt(:,[1,2]),n,1);
col(not(M == R)) = 0;
diagonal = (1/2)*sum((reshape(sum(col,2),p,n)).^2,1);
% off-diagonal elements
B = triu(ones(n),1)';
[row_ind,col_ind] = ind2sub(size(B),find(B));
r = length(row_ind);
row_ind = repelem(row_ind,p);
col_ind = repelem(col_ind,p);
M1 = double(repmat(missing_mu(:,1),r,1));
M2 = double(repmat(missing_mu(:,2),r,1));
col = repmat(quad2_sqrt(:,[1,2]),r,1);
M = [M1,M2,row_ind,col_ind];
miss1_ii = M(:,1) == M(:,3);
miss2_ii = M(:,2) == M(:,3);
miss1_ij = M(:,1) == M(:,4);
miss2_ij = M(:,2) == M(:,4);
IND = (miss1_ii | miss2_ii) & (miss1_ij | miss2_ij);
col([not(IND),not(IND)]) = 0;
col = -prod(col,2);
col = sum(reshape(col,p,size(col,1)/p),1);

D1_mu = triu(ones(n))' - eye(n);
D1_mu(D1_mu == 1) = col;
D1_mu = D1_mu + diag(diagonal);
D1_mu = D1_mu + D1_mu';

%% jac2 mu

% diagonal elements
R = repelem((1:n)',p,2);
M = double(repmat(missing_mu(:,[2,3]),n,1));
col = repmat(quad2_sqrt(:,[2,3]),n,1);
col(not(M == R)) = 0;
diagonal = (1/2)*sum((reshape(sum(col,2),p,n)).^2,1);
% off-diagonal elements
B = triu(ones(n),1)';
[row_ind,col_ind] = ind2sub(size(B),find(B));
r = length(row_ind);
row_ind = repelem(row_ind,p);
col_ind = repelem(col_ind,p);
M1 = double(repmat(missing_mu(:,2),r,1));
M2 = double(repmat(missing_mu(:,3),r,1));
col = repmat(quad2_sqrt(:,[2,3]),r,1);
M = [M1,M2,row_ind,col_ind];
miss1_ii = M(:,1) == M(:,3);
miss2_ii = M(:,2) == M(:,3);
miss1_ij = M(:,1) == M(:,4);
miss2_ij = M(:,2) == M(:,4);
IND = (miss1_ii | miss2_ii) & (miss1_ij | miss2_ij);
col([not(IND),not(IND)]) = 0;
col = -prod(col,2);
col = sum(reshape(col,p,size(col,1)/p),1);

D2_mu = triu(ones(n))' - eye(n);
D2_mu(D2_mu == 1) = col;
D2_mu = D2_mu + diag(diagonal);
D2_mu = D2_mu + D2_mu';

%% jac1 tau

% diagonal elements
R = repelem((1:n)',p,2);
M = double(repmat(missing_tau1(:,[1,2]),n,1));
col = repmat(quad2(:,[1,2]),n,1);
col(not(M == R)) = 0;
diagonal = (1/2)*sum((reshape(sum(col,2),p,n)).^2,1);
% off-diagonal elements
B = triu(ones(n),1)';
[row_ind,col_ind] = ind2sub(size(B),find(B));
r = length(row_ind);
row_ind = repelem(row_ind,p);
col_ind = repelem(col_ind,p);
M1 = double(repmat(missing_tau1(:,1),r,1));
M2 = double(repmat(missing_tau1(:,2),r,1));
col = repmat(quad2(:,[1,2]),r,1);
M = [M1,M2,row_ind,col_ind];
miss1_ii = M(:,1) == M(:,3);
miss2_ii = M(:,2) == M(:,3);
miss1_ij = M(:,1) == M(:,4);
miss2_ij = M(:,2) == M(:,4);
IND = (miss1_ii | miss2_ii) & (miss1_ij | miss2_ij);
col([not(IND),not(IND)]) = 0;
col = -prod(col,2);
col = sum(reshape(col,p,size(col,1)/p),1);

D1_tau = triu(ones(n))' - eye(n);
D1_tau(D1_tau == 1) = col;
D1_tau = D1_tau + diag(diagonal);
D1_tau = D1_tau + D1_tau';

%% jac2 tau

% diagonal elements
R = repelem((1:n)',p,2);
M = double(repmat(missing_tau2(:,[1,2]),n,1));
col = repmat(quad2(:,[2,3]),n,1);
col(not(M == R)) = 0;
diagonal = (1/2)*sum((reshape(sum(col,2),p,n)).^2,1);
% off-diagonal elements
B = triu(ones(n),1)';
[row_ind,col_ind] = ind2sub(size(B),find(B));
r = length(row_ind);
row_ind = repelem(row_ind,p);
col_ind = repelem(col_ind,p);
M1 = double(repmat(missing_tau2(:,1),r,1));
M2 = double(repmat(missing_tau2(:,2),r,1));
col = repmat(quad2(:,[2,3]),r,1);
M = [M1,M2,row_ind,col_ind];
miss1_ii = M(:,1) == M(:,3);
miss2_ii = M(:,2) == M(:,3);
miss1_ij = M(:,1) == M(:,4);
miss2_ij = M(:,2) == M(:,4);
IND = (miss1_ii | miss2_ii) & (miss1_ij | miss2_ij);
col([not(IND),not(IND)]) = 0;
col = -prod(col,2);
col = sum(reshape(col,p,size(col,1)/p),1);

D2_tau = triu(ones(n))' - eye(n);
D2_tau(D2_tau == 1) = col;
D2_tau = D2_tau + diag(diagonal);
D2_tau = D2_tau + D2_tau';

end