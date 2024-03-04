function var = initialize_param(data,A)

% initializes all variables for the IRLS and ADMM optimization

n = data.n;
var.n = n;
var.keep = not(logical(data.keep));
var.IR_iter = data.IR_iter;
var.objlp_tol = data.objlp_tol;
var.conv_tol = data.conv_tol;

M = sqrt(reshape(sum(reshape(A.^2,2,n^2),1),n,n));
var.E_est = A./kron(M,[1;1]);
var.E_est(logical(kron(data.keep,[1;1]))) = 0;

A_fixed = var.E_est;
vld = 1;

var.vld = vld;
var.A = A_fixed;

var.X = var.A;
var.E = var.X;

var.Y = var.X;
var.gamma = zeros(size(var.X));

% var.W = logical(data.keep);
var.W = not(logical(data.keep));
var.W = full(var.W);
var.W = var.W/norm(double(var.W),'fro');

Wn = sum(var.W(:));
var.tau = 0.5*Wn;

var.lam = triu(ones(n)) - tril(ones(n));

p = 1;
[objl2,objlp] = eval_obj(var,p);
var.objl2 = objl2;
var.objlp = objlp;

end

