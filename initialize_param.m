function [var,data] = initialize_param(data)

% Initializes all variables for the IRLS and ADMM optimization

n = data.n;
var.n = n;

% var.R = data.R; % comment out if rotations are not provided
var.X = data.A;
var.E = var.X;

var.E_est = zeros(2*n,n);
for i = 1:n
    for j = 1:n
        if data.keep(i,j)

            E_tmp{i,j} = data.E_est{i,j};

            if isempty(E_tmp{i,j})
                E_tmp{i,j} = zeros(2,1);
            end

            var.E_est(s3(i),j) = E_tmp{i,j};

        end
    end
end

var.W = logical(data.keep);
var.W = full(var.W);

lam = zeros(n);
for i = 1:n
    for j = 1:n

        lam(i,j) = sum(sum(var.E_est(s3(i),j).*var.E(s3(i),j)))/...
            (norm(var.E(s3(i),j),'fro')^2);
    
    end
end

var.lam = lam;
var.lam(logical(eye(n))) = 0;

var.keep = data.keep;

var.gamma = zeros(size(var.X));
var.Y = var.X;
var.W = var.W/norm(double(var.W),'fro');

end

