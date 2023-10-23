function W = estimate_W(var,p)

% Updates the weights of the IRLS method

delta = 10^-3;
W = zeros(var.n);

for i = 1:var.n
    for j = 1:var.n
        if (var.keep(i,j)~=0)
            
            W(i,j) = 1/max(delta,(norm(var.E_est(s3(i),j) - var.E(s3(i),j)*var.lam(i,j),'fro')^(2-p)));
        
        end
    end
end

W(~var.keep) = 0;
W(logical(eye(size(W,1)))) = 0;

W = W/norm(W,'fro');

end