function [objL2,objLp]=eval_obj(var,p)

% Evaluates the objective function in terms of the weighted Frobenius L2
% norm and the L1 norm

N = var.n;

e = var.E_est-var.E.*kron(var.lam,ones(2,1));
w = kron(var.W,ones(2,1));
objL2 = 0.5*sum(sum(w.*(e.^2)));

residual=zeros(N);
for i = 1:N
    for j = 1:N
        if var.keep(i,j) == 0
            continue;
        end
        residual(i,j) = norm(e(s3(i),j),'fro');
    end
end

objLp = sum((residual(:)).^p);

end

