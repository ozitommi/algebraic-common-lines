function result = IRLSinhom(var)

% Performs IRLS and ADMM/alternating descent

p = 1; % L1 cost function
iter_irls = 1;
IR_iter = var.IR_iter;
T_iter = IR_iter + 1;
objlp_tol = var.objlp_tol;

%% Run ADMM once

Wn = sum(var.W(:));
var.tau = 0.5*Wn;
result = ADMMinhom(var); % run ADMM
var = result.var;
[objl2,objlp] = eval_obj(result.var,p);  % evaluate cost function
diffF = abs(objlp - var.objlp)/max(objlp,var.objlp);
var.objl2 = objl2;
var.objlp = objlp;
var.W = estimate_W(var,p); % estimate weights for IRLS
fprintf('IRLS iter %d IRLS obj L2 %.3e obj Lp(p=1) %.3e\n',iter_irls,objl2,objlp);
iter_irls = iter_irls + 1;

%% Repeat

while iter_irls < T_iter && diffF > 10^-6 && objlp > objlp_tol

    Wn = sum(var.W(:));
    var.tau = 0.5*Wn;
    result = ADMMinhom(var); % run ADMM
    var = result.var;
    [objl2,objlp] = eval_obj(result.var,p);  % evaluate cost function
    diffF = abs(objlp - var.objlp)/max(objlp,var.objlp);
    var.objl2 = objl2;
    var.objlp = objlp;
    var.W = estimate_W(var,p); % estimate weights for IRLS
    fprintf('IRLS iter %d IRLS obj L2 %.3e obj Lp(p=1) %.3e\n',iter_irls,objl2,objlp);
    iter_irls = iter_irls + 1;

end

%% Output

result.var = var;

end

