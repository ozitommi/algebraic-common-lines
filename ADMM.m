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
MAX = 10;

while iter < MAX && diff1 > 10^-6

    iter = iter + 1;

    % update A
    mat1 = kron(var.W.*var.lam,ones(2,1)).*var.E_est + var.tau*G;
    mat2 = kron(var.W.*var.lam.^2,ones(2,1)) + var.tau;
    A = mat1./mat2;

    % project A
    M = sqrt(reshape(sum(reshape(A.^2,2,n^2),1),n,n));
    A = A./kron(M,[1;1]); % make all entries have norm 1
    idx_block = logical(kron(eye(n),ones(2,1)));
    A(idx_block) = 0; % make 2x1 block diagonals 0

    var.X = A;
    var.E = var.X;

    % update lambda
    m1 = var.E_est.*var.E;
    m2 = var.E.*var.E;
    bl1 = conv2(m1,ones(2,1),'valid'); % adds elements of each 2x1 submatrix
    % formula: sum of entries of Hadarmard product of A and B is the trace of A'*B
    bl1 = bl1(1:2:end,1:end); % keeps only the properly aligned sums
    bl2 = conv2(m2,ones(2,1),'valid');
    bl2 = bl2(1:2:end,1:end);
    var.lam = bl1./bl2; % diagonals are NaN from 0/0
    var.lam(logical(eye(n))) = 0; % set the NaN values to 0

    f2 = eval_obj_t(var);
    diff1 = abs(f2 - f2_old);
    f2_old = f2;

end

end

function var = opt_Y(var)

% update B
tmpY = var.X - var.gamma;
[U, S, V] = svds(tmpY, 3);
var.Y = U*S*V';

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
