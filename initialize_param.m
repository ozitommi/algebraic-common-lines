function var = initialize_param(data,A)

% initializes all variables for the IRLS and ADMM optimization

n = data.n;
var.n = n;
var.keep = not(logical(data.keep));
var.missing_mu = data.missing_mu;
var.missing_tau1 = data.missing_tau1;
var.missing_tau2 = data.missing_tau2;
var.IR_iter = data.IR_iter;
var.objlp_tol = data.objlp_tol;
var.conv_tol = data.conv_tol;
var.norm_tol = data.norm_tol;
var.MAX_SH = data.MAX_SH;

M = sqrt(reshape(sum(reshape(A.^2,2,n^2),1),n,n));
var.E_est = A./kron(M,[1;1]);
var.E_est(logical(kron(data.keep,[1;1]))) = 0;

a = 0.5;
b = 0.75;
randlam = (b-a)*rand(n) + a;
randlam(logical(eye(n))) = 0;
[A_fixed,vld] = fixSigns((var.E_est).*kron(randlam,[1;1]));

A_fixedBest = A_fixed;
MAX_TRY = 25;
if vld == 0
    fvalBest = Inf;
    for i = 1:MAX_TRY
        [A_try,fval] = gafixSigns(A_fixed);
        fval
        if fval < fvalBest
            fvalBest = fval;
            A_fixedBest = A_try;
        end
    end
end
var.vld = vld;
var.A = A_fixedBest;

% var.vld = vld;
% var.A = A_fixed;

var.X = var.A;
var.E = var.X;
[~,quad2] = checkQuadrics(var.E);
var.quad = quad2;

var.Y = var.X;
var.gamma = zeros(size(var.X));

m1 = var.E_est.*var.E;
m2 = var.E.*var.E;
bl1 = conv2(m1,ones(2,1),'valid'); % adds elements of each 2x1 submatrix
% formula: sum of entries of Hadarmard product of A and B is the trace of A'*B
bl1 = bl1(1:2:end,1:end); % keeps only the properly aligned sums
bl2 = conv2(m2,ones(2,1),'valid');
bl2 = bl2(1:2:end,1:end);
lam = bl1./bl2; % diagonals are NaN from 0/0
lam(logical(eye(n))) = 0; % set the NaN values to 0
% bound inside box
lam = min(lam,var.conv_tol);
lam = max(lam,-var.conv_tol);
var.lam = lam;

var.W = logical(data.keep);
var.W = full(var.W);
var.W = var.W/norm(double(var.W),'fro');

Wn = sum(var.W(:));
var.tau = 0.5*Wn;

p = 1;
[objl2,objlp] = eval_obj(var,p);
var.objl2 = objl2;
var.objlp = objlp;

end

