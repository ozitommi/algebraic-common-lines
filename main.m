
clear all;
format long;

%% Estimated common lines matrix initialization

% % A = importdata("common_lines_test.mat");
% A = importdata("synthetic_image_cl_matrix.mat");
% n = size(A,2); % number of common lines
% data.n = n;
% data.keep = not(logical(eye(n))); % indicates whether there is any missing data
% 
% % adds noise
% % a = -0.1;
% % b = 0.1;
% % A_err = A + (b-a).*rand(size(A,1),size(A,2)) + a;
% % n = size(A,2); % number of common lines
% 
% A_err = A;
% 
% data.E_est = cell(n,n); % store the 2x1 entries of the common lines matrix
% for i = 1:n
%     for j = 1:n
%         data.E_est{i,j} = A_err(s3(i),j);
%     end
% end

%% Synthetic common lines matrix initialization

n = 10; % number of common lines
data.n = n;
data.keep = not(logical(eye(n))); % indicates whether there is any missing data

[A,~,Rots] = create_A(n);

noises = [0,0.05,0.1,0.15,0.2];
NOISE = 3;

% rotational noise
a = -noises(NOISE);
b = noises(NOISE);
for i = 1:n
    for j = 1:n
        u = (b-a)*rand(1) + a;
        rotMat = [cos(u),-sin(u);sin(u),cos(u)];
        A(s3(i),j) = rotMat*A(s3(i),j);
    end
end

% add random scaling
a = -1;
b = 1;
randlam = (b-a)*rand(n) + a;
randlam(logical(eye(n))) = 0;
A_err = A.*kron(randlam,[1;1]);

data.E_est = cell(n,n); % store the 2x1 entries of the common lines matrix
for i = 1:n
    for j = 1:n
        data.E_est{i,j} = A_err(s3(i),j);
    end
end

%% Optimization parameter initialization

IR_iter = 3000; % maximum number of iterations for IRLS/ADMM

M = sqrt(reshape(sum(reshape(A_err.^2,2,n^2),1),n,n));
A_err = A_err./kron(M,[1;1]);
idx_block = logical(kron(eye(n),ones(2,1)));
A_err(idx_block) = 0; % make 2x1 block diagonals 0

% a = 0.5;
% b = 0.75;
% randlam = (b-a)*rand(n) + a;
% randlam(logical(eye(n))) = 0;
% A_fixed = A_err.*kron(randlam,[1;1]);
% 
% [~,quad2] = checkQuadrics(A);
% sign(quad2);
% [~,quad2] = checkQuadrics(A_err);
% sign(quad2);
[A_fixed,vld] = fixSigns(A_err);
% [A_fixed,vld] = fixSigns(A_fixed);
% [~,quad2] = checkQuadrics(A_fixed);
% sign(quad2);

MAX_TRY = 25;
if vld == 0
    fvalBest = Inf;
    for i = 1:MAX_TRY
        % a = 0.5;
        % b = 0.75;
        % a = -1;
        % b = 1;
        % randlam = (b-a)*rand(n) + a;
        % randlam(logical(eye(n))) = 0;
        % [A_try,fval] = gafixSigns(A.*kron(sign(randlam),[1;1]));
        [A_try,fval] = gafixSigns(A_err);
        fval/2
        if fval < fvalBest
            fvalBest = fval;
            A_fixed = A_try;
        end
    end
end

data.A = A_fixed; % maybe try different random initializations
[var,data] = initialize_param(data);

%% Run IRLS and ADMM

[result] = IRLS(var,IR_iter);
var = result.var;

%% Check whether the output has rank 3

var.E = var.E/norm(var.E,'fro');

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
M;

%% Fix norm equations with Sinkhorn

M = sqrt(reshape(sum(reshape((var.E).^2,2,n^2),1),n,n));
norm_err = norm(M-M','fro');
[~,quad2] = checkQuadrics(var.E);
det_err = sum(norm(quad2(:,1) - quad2(:,2))) + sum(norm(quad2(:,2) - quad2(:,3)));
fprintf('error after before %.9e\n',norm_err + det_err);
MAX_SH = 500;

for i = 1:MAX_SH

    [L,~] = constructScaleMats(M);
    [~,quad2] = checkQuadrics(var.E);
    var.quad = quad2;
    [D1_mu,D2_mu,~,~] = constructDetMats(var);
    [~,~,V] = svd(L + D1_mu + D2_mu);
    % [~,~,V] = svd(L);
    d1 = V(:,end);
    LM = diag(d1)*M;
    M = norm(M,'fro')*(LM/norm(LM,'fro'));
    LE = diag(repelem(d1,2))*(var.E);
    var.E = norm(var.E,'fro')*(LE/norm(LE,'fro'));

    norm_err = norm(M-M','fro');
    [~,quad2] = checkQuadrics(var.E);
    det_err = sum(norm(quad2(:,1) - quad2(:,2))) + sum(norm(quad2(:,2) - quad2(:,3)));
    fprintf('error after rows %.9e\n',norm_err + det_err);

    [~,R] = constructScaleMats(M);
    [~,quad2] = checkQuadrics(var.E);
    var.quad = quad2;
    [~,~,D1_tau,D2_tau] = constructDetMats(var);
    [~,~,V] = svd(R + D1_tau + D2_tau);
    d2 = V(:,end);
    MR = M*diag(d2);
    M = norm(M,'fro')*(MR/norm(MR,'fro'));
    ER = (var.E)*diag(d2);
    var.E = norm(var.E,'fro')*(ER/norm(ER,'fro'));

    norm_err = norm(M-M','fro');
    [~,quad2] = checkQuadrics(var.E);
    det_err = sum(norm(quad2(:,1) - quad2(:,2))) + sum(norm(quad2(:,2) - quad2(:,3)));
    fprintf('error after columns %.9e\n',norm_err + det_err);

end

[quad1,quad2] = checkQuadrics(var.E)
[~,Sigma,~] = svd(var.E,'vector')

%% Recover rotations



var.E = sign(A).*abs(var.E); % fix the signs of E

[R_recover1,A_recover1,R_recover2,A_recover2] = recoverRotations(var);
Rec1 = [];
Rot = [];
for i = 1:n
    Rec1 = [Rec1;R_recover1{i}];
    Rot = [Rot; Rots{i}];
end
[U,~,V] = svd(Rot'*Rec1);
Q = U*V';
norm(Rec1 - Rot*Q,'fro')

Rec2 = [];
Rot = [];
for i = 1:n
    Rec2 = [Rec2;R_recover2{i}];
    Rot = [Rot; Rots{i}];
end
[U,~,V] = svd(Rot'*Rec2);
Q = U*V';
norm(Rec2 - Rot*Q,'fro')

