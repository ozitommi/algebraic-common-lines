function [A_out,fval,vld,conv] = runADMM(var)

n = var.n;
vld = var.vld;

%% Run IRLS and ADMM

[result] = IRLS(var);
var = result.var;
var.lam

%% Fix norm equations with Sinkhorn

MAX_SH = var.MAX_SH;
diffF = Inf;
obj = Inf;
iter = 1;

while iter < MAX_SH && diffF > 10^-8

    % scale rows
    M = sqrt(reshape(sum(reshape((var.E).^2,2,n^2),1),n,n));
    [L,~] = constructScaleMats(M);
    [~,quad2] = checkQuadrics(var.E);
    var.quad = quad2;
    [D1_mu,D2_mu,~,~] = constructDetMats(var);
    [~,~,V] = svd(L + D1_mu + D2_mu);
    d1 = V(:,end);
    LE = diag(repelem(d1,2))*(var.E);
    var.E = norm(var.E,'fro')*(LE/norm(LE,'fro'));

    % % bound norms inside box
    % M = sqrt(reshape(sum(reshape((var.E).^2,2,n^2),1),n,n));
    % S = ones(n);
    % S(M < var.norm_tol_min) = (var.norm_tol_min)./M(M < var.norm_tol_min);
    % S(logical(eye(n))) = 1;
    % var.E = kron(S,[1;1]).*(var.E);
    % M = sqrt(reshape(sum(reshape((var.E).^2,2,n^2),1),n,n));
    % S = ones(n);
    % S(M > var.norm_tol_max) = (var.norm_tol_max)./M(M > var.norm_tol_max);
    % S(logical(eye(n))) = 1;
    % var.E = kron(S,[1;1]).*(var.E);

    % scale columns
    M = sqrt(reshape(sum(reshape((var.E).^2,2,n^2),1),n,n));
    [~,R] = constructScaleMats(M);
    [~,quad2] = checkQuadrics(var.E);
    var.quad = quad2;
    [~,~,D1_tau,D2_tau] = constructDetMats(var);
    [~,~,V] = svd(R + D1_tau + D2_tau);
    d2 = V(:,end);
    ER = (var.E)*diag(d2);
    var.E = norm(var.E,'fro')*(ER/norm(ER,'fro'));

    % % bound norms inside box
    % M = sqrt(reshape(sum(reshape((var.E).^2,2,n^2),1),n,n));
    % S = ones(n);
    % S(M < var.norm_tol_min) = (var.norm_tol_min)./M(M < var.norm_tol_min);
    % S(logical(eye(n))) = 1;
    % var.E = kron(S,[1;1]).*(var.E);
    % M = sqrt(reshape(sum(reshape((var.E).^2,2,n^2),1),n,n));
    % S = ones(n);
    % S(M > var.norm_tol_max) = (var.norm_tol_max)./M(M > var.norm_tol_max);
    % S(logical(eye(n))) = 1;
    % var.E = kron(S,[1;1]).*(var.E);

    M = sqrt(reshape(sum(reshape((var.E).^2,2,n^2),1),n,n));
    norm_err = norm(M-M','fro');
    [~,quad2] = checkQuadrics(var.E);
    det_err = sum(norm(quad2(:,1) - quad2(:,2))) + sum(norm(quad2(:,2) - quad2(:,3)));

    diffF = abs(obj - (norm_err + det_err));
    obj = norm_err + det_err;
    iter = iter + 1;

end

%% Output

% A_out = var.E;
A_out = var.E/norm(var.E,'fro');
M = sqrt(reshape(sum(reshape((var.E).^2,2,n^2),1),n,n));
norm_err = norm(M-M','fro');
[quad1,quad2] = checkQuadrics(var.E);
det_err = sum(norm(quad2(:,1) - quad2(:,2))) + sum(norm(quad2(:,2) - quad2(:,3)));
fval = norm_err + det_err;

if any(any(quad1 < var.norm_tol))
    conv = 0;
else
    conv = 1;
end

end