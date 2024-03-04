function [A_out,fval,vld,conv] = runADMMinhom(var)

n = var.n;
vld = var.vld;

%% Run IRLS and ADMM

[result] = IRLSinhom(var);
var = result.var;

%% Check if ADMM converged

if any(abs(var.lam) > var.conv_tol)
    conv = 0;
else
    conv = 1;
end

%% Fix norm equations with Sinkhorn

% var.E = var.E/norm(var.E,'fro');
var.E = var.E/10;

MAX_SH = var.MAX_SH;
diffF = Inf;
obj = Inf;
iter = 1;

while iter < MAX_SH && diffF > 10^-8

    M = sqrt(reshape(sum(reshape((var.E).^2,2,n^2),1),n,n));
    [L,~] = constructScaleMats(M);
    [~,quad2] = checkQuadrics(var.E);
    var.quad = quad2;
    [D1_mu,D2_mu,~,~] = constructDetMats(var);
    [~,~,V] = svd(L + D1_mu + D2_mu);
    d1 = V(:,end);
    LE = diag(repelem(d1,2))*(var.E);
    var.E = norm(var.E,'fro')*(LE/norm(LE,'fro'));

    M = sqrt(reshape(sum(reshape((var.E).^2,2,n^2),1),n,n));
    [~,R] = constructScaleMats(M);
    [~,quad2] = checkQuadrics(var.E);
    var.quad = quad2;
    [~,~,D1_tau,D2_tau] = constructDetMats(var);
    [~,~,V] = svd(R + D1_tau + D2_tau);
    d2 = V(:,end);
    ER = (var.E)*diag(d2);
    var.E = norm(var.E,'fro')*(ER/norm(ER,'fro'));

    M = sqrt(reshape(sum(reshape((var.E).^2,2,n^2),1),n,n));
    norm_err = norm(M-M','fro');
    [~,quad2] = checkQuadrics(var.E);
    det_err = sum(norm(quad2(:,1) - quad2(:,2))) + sum(norm(quad2(:,2) - quad2(:,3)));
    fprintf('error after rows %.9e\n',norm_err + det_err);

    diffF = abs(obj - (norm_err + det_err));
    obj = norm_err + det_err;
    iter = iter + 1;

end

%% Output

A_out = var.E;
M = sqrt(reshape(sum(reshape((var.E).^2,2,n^2),1),n,n));
norm_err = norm(M-M','fro');
[~,quad2] = checkQuadrics(var.E);
det_err = sum(norm(quad2(:,1) - quad2(:,2))) + sum(norm(quad2(:,2) - quad2(:,3)));
fval = norm_err + det_err;

end