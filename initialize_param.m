function [var,data] = initialize_param(data)

% Initializes all variables for the IRLS and ADMM optimization

n = data.n;
var.n = n;

var.keep = data.keep;

% find missing indices for determinant equation correction
missing = generateMissing(n);
indices = [];
for i = 1:n
    for j = (i+1):n
        indices = [indices, "" + i + j];
    end
end
indices1 = indices;
indices1(1) = [];
indices2 = indices;
indices2(end) = [];
m = length(indices1);
indices1mat = strings(m);
indices2mat = strings(m);
for i = 1:m
    for j = i:m
        indices1mat(i,j) = indices1(j);
        indices2mat(i,j) = indices2(j);
    end
end
var.ind1mat = indices1mat;
var.ind2mat = indices2mat;
var.missing = missing;

var.E_est = zeros(2*n,n);
for i = 1:n
    for j = 1:n
        if data.keep(i,j)

            E_tmp{i,j} = data.E_est{i,j}/norm(data.E_est{i,j});
            % E_tmp{i,j} = data.E_est{i,j};

            if isempty(E_tmp{i,j})
                E_tmp{i,j} = zeros(2,1);
            end

            var.E_est(s3(i),j) = E_tmp{i,j};

        end
    end
end

var.A = data.A;
var.X = data.A;
var.E = var.X;

var.W = logical(data.keep);
var.W = full(var.W);
var.W = var.W/norm(double(var.W),'fro');

var.lam = ones(n);
var.lam(logical(eye(n))) = 0;

var.Y = var.X;

var.gamma = zeros(size(var.X));

end

