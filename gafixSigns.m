function [A_fixed,fval] = gafixSigns(A_err)

n = size(A_err,2);
[~,quad2] = checkQuadrics(A_err);

fun = @(x)signError(x,sign(quad2),n);
A = [];
b = [];
Aeq = [];
beq = [];
lb = 0*ones(1,2*nchoosek(n,2));
ub = ones(1,2*nchoosek(n,2));
intcon = 1:2*nchoosek(n,2);
nonlcon = [];
% rng default; % only uncomment for testing and reproducibility
[x,fval,~,~] = ga(fun,2*nchoosek(n,2),A,b,Aeq,beq,lb,ub,nonlcon,intcon);
x(x == 0) = -1;

Lambda = triu(ones(n))' - eye(n);
Lambda = Lambda + Lambda';
Lambda(Lambda == 1) = x;
A_fixed = A_err.*kron(Lambda,[1;1]);

function diff = signError(x,quad2,n)
x(x == 0) = -1;
lambda = triu(ones(n))' - eye(n);
lambda = lambda + lambda';
lambda(lambda == 1) = x;
m = nchoosek(n,3);
vec1 = zeros(m,1);
vec2 = zeros(m,1);
vec3 = zeros(m,1);
ind = 1;
for i = 1:(n-2)
    for j = (i+1):(n-1)
        for k = (j+1):n
            vec1(ind) = lambda(i,j)*lambda(i,k)*quad2(ind,1);
            vec2(ind) = lambda(j,i)*lambda(j,k)*quad2(ind,2);
            vec3(ind) = lambda(k,i)*lambda(k,j)*quad2(ind,3);
            ind = ind + 1;
        end
    end
end

diff = sum(abs(vec1 - vec2)) + sum(abs(vec2 - vec3));

% V = [vec1,vec2,vec3];
% V(V == -1) = 0;
% V = logical(V);
% v = double((V(:,1) == V(:,2)) & (V(:,2) == V(:,3)));
% diff = length(v) - sum(v);

end


end