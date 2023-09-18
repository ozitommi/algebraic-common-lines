
clear all;
format long;

%% Estimated (unscaled) synthetic common lines matrix initialization, no noise

% A = importdata("common_lines_test.mat");
% n = size(A,2); % number of common lines
% data.n = n;
% data.keep = not(logical(eye(n))); % indicates whether there is any missing data
% 
% data.E_est = cell(n,n); % store the 2x1 entries of the common lines matrix
% for i = 1:n
%     for j = 1:n
%         data.E_est{i,j} = A(s3(i),j);
%     end
% end

% [quad1,quad2] = checkQuadrics(A);

%% Estimated (unscaled) synthetic common lines matrix, added noise

% A = importdata("common_lines_test.mat");
% a = -0.1;
% b = 0.1;
% A = A + (b-a).*rand(size(A,1),size(A,2)) + a;
% n = size(A,2); % number of common lines
% data.n = n;
% data.keep = not(logical(eye(n))); % indicates whether there is any missing data
% 
% data.E_est = cell(n,n); % store the 2x1 entries of the common lines matrix
% for i = 1:n
%     for j = 1:n
%         data.E_est{i,j} = A(s3(i),j);
%     end
% end
% 
% [quad1,quad2] = checkQuadrics(A);

%% Exact (scaled) synthetic common lines matrix initialization

n = 5; % number of common lines
data.n = n;
data.keep = not(logical(eye(n))); % indicates whether there is any missing data

[A,~] = create_A(n);

A_err = A;
% % add noise
% a = -0.1;
% b = 0.1;
% A_err = A + (b-a).*rand(size(A,1),size(A,2)) + a;

data.E_est = cell(n,n); % store the 2x1 entries of the common lines matrix
for i = 1:n
    for j = 1:n
        data.E_est{i,j} = A_err(s3(i),j);
    end
end

% [quad1,quad2] = checkQuadrics(A);

%% Optimization parameter initialization

IR_iter = 500; % maximum number of iterations for IRLS/ADMM
data.A = create_A(n);
[var,data] = initialize_param(data);

% % choose best initial parameter
% lowest = Inf;
% for i = 1:20000
%     data.A = create_A(n);
%     [var,data] = initialize_param(data);
%     [~,objLp]=eval_obj(var,1);
%     if objLp < lowest
%         varBest = var;
%         lowest = objLp
%     end
% end
% var = varBest;

%% Run IRLS and ADMM

% [result] = IRLS(var,IR_iter);
% var = result.var;

% run alternating descent multiple times and choose best output
lowestL1 = Inf;
highestL1 = 0;

for i = 1:20

    data.A = create_A(n);

    [var,data] = initialize_param(data);
    [result] = IRLS(var,IR_iter);
    var = result.var;

    [~,objLp] = eval_obj(var,1);

    if objLp < lowestL1
        varBest = var;
        lowestL1 = objLp;
    end

    if objLp > highestL1
        highestL1 = objLp;
    end

end

%% Check the singular values of the rescaled common lines matrix

% V = result.var;
% E = V.E;
% [~,Sigma,~] = svd(E,"vector")

%% Check whether the output satisfies the quadric equations

% [quad1,quad2] = checkQuadrics(var.E)
% [quad1,quad2] = checkQuadrics(varBest.E)

%% Check the reconstruction error

% E = var.E_est;
% E_rec = kron(var.lam,ones(2,1)).*var.E;
% for i = 1:n
%     for j = 1:n
%         M(i,j) = norm(E(s3(i),j) - E_rec(s3(i),j));
%     end
% end
% M

E = varBest.E_est;
E_rec = kron(varBest.lam,ones(2,1)).*varBest.E;
for i = 1:n
    for j = 1:n
        M(i,j) = norm(E(s3(i),j) - E_rec(s3(i),j));
    end
end
M

% var.E_est
% kron(var.lam,ones(2,1)).*var.E
