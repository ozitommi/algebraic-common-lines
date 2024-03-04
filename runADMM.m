function [A_out,lam_out,var] = runADMM(var)

%% Run IRLS and ADMM

[result] = IRLS(var);
var = result.var;

%% Output

A_out = var.E;
lam_out = var.lam;

end