function [result] = IRLS(var,IR_iter)

% Performs IRLS and alternating descent

p = 1; %L1 cost function
diffF = Inf;
iter_irls = 1;
T_iter = IR_iter + 1;
var.objlp = 0;

while iter_irls<T_iter && diffF > 10^-8

    Wn = sum(var.W(:));
    var.tau = 0.5*Wn;
    result = alternating_descent(var); % run alternating descent
    var = result.var;

    [objl2,objlp] = eval_obj(result.var,p);  % evaluate cost function

    diffF = abs(objlp - var.objlp)/max(objlp,var.objlp);

    var.objl2 = objl2;
    var.objlp = objlp;

    var.W = estimate_W(var,p); % estimate weights for IRLS

    fprintf('IRLS iter %d IRLS obj L2 %.3e obj Lp(p=1) %.3e\n',iter_irls,objl2,objlp);

    iter_irls = iter_irls+1;

end

result.var = var;

end

