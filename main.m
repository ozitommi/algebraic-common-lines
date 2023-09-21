
clear all;
format long;

%% Estimated common lines matrix initialization

% A = importdata("common_lines_test.mat");
% n = size(A,2); % number of common lines
% data.n = n;
% data.keep = not(logical(eye(n))); % indicates whether there is any missing data

% % adds noise
% a = -0.1;
% b = 0.1;
% A = A + (b-a).*rand(size(A,1),size(A,2)) + a;
% n = size(A,2); % number of common lines

% data.E_est = cell(n,n); % store the 2x1 entries of the common lines matrix
% for i = 1:n
%     for j = 1:n
%         data.E_est{i,j} = A(s3(i),j);
%     end
% end

% [quad1,quad2] = checkQuadrics(A);

%% Synthetic common lines matrix initialization

A = importdata("common_lines_synthetic_n=4.mat");
n = size(A,2); % number of common lines

% n = 4; % number of common lines
data.n = n;
data.keep = not(logical(eye(n))); % indicates whether there is any missing data

% [A,~,R] = create_A(n);

% add random scaling
a = -0.1;
b = 0.1;
randlam = (b-a)*rand(n) + a;
randlam(logical(eye(n)))=0;
A_err = A.*kron(randlam,ones(2,1));

% % add noise
% a = -0.1;
% b = 0.1;
% A_err = A + (b-a).*rand(size(A,1),size(A,2)) + a;

% A_err = A;

data.E_est = cell(n,n); % store the 2x1 entries of the common lines matrix
for i = 1:n
    for j = 1:n
        data.E_est{i,j} = A_err(s3(i),j);
    end
end

% [quad1,quad2] = checkQuadrics(A);

%% Optimization parameter initialization

IR_iter = 10000; % maximum number of iterations for IRLS/ADMM
% data.A = create_A(n);
data.A = (1 - (-1))*rand(2*n,n) + (-1);
[var,data] = initialize_param(data);

%% Run IRLS and ADMM

[result] = IRLS(var,IR_iter);
var = result.var;

%% Check whether the output has rank 3

[~,Sigma,~] = svd(var.E,"vector")

%% Check whether the output satisfies the quadric equations

[quad1,quad2] = checkQuadrics(var.E)

%% Check the reconstruction error

E = var.E_est;
E_rec = kron(var.lam,ones(2,1)).*var.E;
for i = 1:n
    for j = 1:n
        M(i,j) = norm(E(s3(i),j) - E_rec(s3(i),j));
    end
end
M

%% Recover rotations

% [R_recover,A_recover] = recoverRotations(var);

