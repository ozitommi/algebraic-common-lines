function result = ADMM(var)

max_ite = 500;
threshold = 10^-8;
count = 1;
diff = inf;

[obj] = objective_fun(var);

out = struct;
out.residual = zeros(max_ite,1);
out.obj = zeros(max_ite,1);

% profile on
actv = 1;
while count < max_ite && actv && diff > threshold

    % run alternating ADMM optimization
    out.obj(count) = obj;

    var = opt_X(var);
    var = opt_Y(var);
    var = opt_gamma(var);

    count = count + 1;

    if mod(count,20) == 1

        obj = objective_fun(var);

    end

    if mod(count,20) == 10

        obj1 = objective_fun(var);
        diff = abs((obj - obj1))/max(abs(obj),abs(obj1));

        if diff < threshold

            actv = 0;

        end
    end

end

result = struct;
result.var = var;
result.out = out;

end

function [obj] = objective_fun(var)

% full objective
obj1 = eval_obj_t(var);
obj3 = norm(var.Y - var.X + var.gamma, 'fro')^2;
obj = obj1 + var.tau/2.0*obj3;

end

function [var] = opt_X(var)

% update A and Lambda
n = var.n;
G = var.Y + var.gamma;

iter = 0;
f2_old = 0;
diff1 = Inf;
MAX = 1; % changed

while iter < MAX && diff1 > 10^-6

    iter = iter + 1;

    % update A
    mat1 = kron(var.W.*var.lam,ones(2,1)).*var.E_est + var.tau*G;
    mat2 = kron(var.W.*var.lam.^2,ones(2,1)) + var.tau;
    A = mat1./mat2;

    idx_block = logical(kron(eye(n),ones(2,1)));
    A(idx_block) = 0; % make 2x1 block diagonals 0

    var.X = A;
    var.E = var.X;

    %% symmetric version
    W = var.W;
    d1 = reshape(sum(reshape(var.E_est.*var.E,2,n^2),1),n,n);
    d2 = reshape(sum(reshape(var.E.*var.E,2,n^2),1),n,n);
    D = (W.*d1 + (W.*d1)')./(W.*d2 + (W.*d2)');
    ind = triu(ones(n)) - eye(n);
    D(ind == 0) = 0;
    var.lam = D + D';

    % bound scales inside box
    var.lam = min(var.lam,var.conv_tol);
    var.lam = max(var.lam,-var.conv_tol);

    f2 = eval_obj_t(var);
    diff1 = abs(f2 - f2_old);
    f2_old = f2;

end

end

function var = opt_Y(var)

% update B
tmpY = var.X - var.gamma;
[U, S, V] = svd(tmpY);
var.Y = U(:,1:3)*S(1:3,1:3)*V(:,1:3)';
% [U, S, V] = svds(tmpY, 3);
% var.Y = U*S*V';

end

function var = opt_gamma(var)

% update Gamma
var.gamma = var.gamma + (var.Y - var.X);

end

function f = eval_obj_t(var)

% objective for A and Lambda
e = var.E_est - var.E.*kron(var.lam,ones(2,1));
w = kron(var.W,ones(2,1));
f = 0.5*sum(sum(w.*e.^2));

end
