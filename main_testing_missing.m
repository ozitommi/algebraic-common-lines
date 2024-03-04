
clear all;
format long;

ERR = cell(4,4);

for MISS = 1:4

for COMM = 3:2:9

errors = zeros(100,5);
noises = [0,0.05,0.1,0.15,0.2];
missing = [0,floor(nchoosek(COMM,2)/3),2*floor(nchoosek(COMM,2)/3),3*floor(nchoosek(COMM,2)/3)];

for NOISE = 1:5

for TIMES = 1:100

n = COMM; % number of common lines
data.n = n;

keep = eye(n);
for i = 1:missing(MISS)
exit = 0;
while ~exit
    x = randperm(n);
    x = x(1:2);
    if keep(x(1),x(2)) == 0
        keep(x(1),x(2)) = 1;
        exit = 1;
    end
end
end
data.keep = not(logical(keep)); % indicates whether there is any missing data

[A,~,Rots] = create_A(n);

% rotational noise
a = -noises(NOISE);
b = noises(NOISE);
A_err_Rot = A;
for i = 1:n
    for j = 1:n
        u = (b-a)*rand(1) + a;
        rotMat = [cos(u),-sin(u);sin(u),cos(u)];
        A_err_Rot(s3(i),j) = rotMat*A_err_Rot(s3(i),j);
    end
end

% add random scaling
a = -1;
b = 1;
randlam = (b-a)*rand(n) + a;
randlam(logical(eye(n))) = 0;
A_err = A_err_Rot.*kron(sign(randlam),[1;1]);

data.E_est = cell(n,n); % store the 2x1 entries of the common lines matrix
for i = 1:n
    for j = 1:n
        data.E_est{i,j} = A_err(s3(i),j);
    end
end

%% Try to fix the signs of the scaled common lines matrix

[A_fixed,vld] = fixSigns(A_err);
if vld == 0
    fvalBest = Inf;
    for i = 1:25
        [A_fixed_try,fval] = gafixSigns(A_err);
        fval
        if fval < fvalBest
            fvalBest = fval;
            A_fixed = A_fixed_try;
        end
    end
end

%% Optimization parameter initialization

IR_iter = 500; % maximum number of iterations for IRLS/ADMM
M = sqrt(reshape(sum(reshape((A_fixed).^2,2,n^2),1),n,n));
data.A = A_fixed./kron(M,[1;1]);
[var,data] = initialize_param(data);

%% Run IRLS and ADMM

[result] = IRLS(var,IR_iter);
var = result.var;

%% Fix norm equations with Sinkhorn

M = sqrt(reshape(sum(reshape((var.E).^2,2,n^2),1),n,n));
norm_err = norm(M-M','fro');
[~,quad2] = checkQuadrics(var.E);
det_err = sum(norm(quad2(:,1) - quad2(:,2))) + sum(norm(quad2(:,2) - quad2(:,3)));
fprintf('error after before %.9e\n',norm_err + det_err);
MAX_SH = 1000;

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

%% Recover rotations

var.A = A;
var.E = sign(A).*abs(var.E); % fix the signs of E

[R_recover1,A_recover1,R_recover2,A_recover2] = recoverRotations2(var);
Rec1 = [];
Rot = [];
for i = 1:n
    Rec1 = [Rec1;R_recover1{i}];
    Rot = [Rot; Rots{i}];
end
[U,~,V] = svd(Rot'*Rec1);
Q = U*V';
normsq1 = norm(Rec1 - Rot*Q,'fro')^2;

Rec2 = [];
Rot = [];
for i = 1:n
    Rec2 = [Rec2;R_recover2{i}];
    Rot = [Rot; Rots{i}];
end
[U,~,V] = svd(Rot'*Rec2);
Q = U*V';
normsq2 = norm(Rec2 - Rot*Q,'fro')^2;

min(normsq1,normsq2)
if min(normsq1,normsq2) > 1
    a = 1;
end
errors(TIMES,NOISE) = min(normsq1,normsq2);

end
end

ERR{MISS,0.5*COMM-0.5} = errors;

end
end
