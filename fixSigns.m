function [A_fixed,keep,vld] = fixSigns(A_err)

% Finds sign flips to the entries of the input common lines matrix so that
% the signs of the determinant equations all match

% theta = 12.5;
theta = 0;

[~,quad2] = checkQuadrics(A_err);
[~,keep] = checkBadDeterminants(A_err,theta);
ind_keep = logical(keep);

n = size(A_err,2);
m = size(quad2,1);

I = {};
for i = 1:m

    I{i} = nonzeros(keep(i,:));

end
% % I = num2cell(keep',1);
A = blkdiag(I{:});
% % A = kron(eye(m),ones(3,1));
% A = [];
X = nchoosek(1:n,3);

for i = 1:n
    for j = 1:n
        if i ~= j

            L1 = [X(:,1),X(:,2)];
            M1 = [X(:,2),X(:,1)];
            R1 = [X(:,3),X(:,1)];

            L1 = (L1 == [i,j]);
            M1 = (M1 == [i,j]);         
            R1 = (R1 == [i,j]);

            L1 = L1(:,1) & L1(:,2);
            M1 = M1(:,1) & M1(:,2);
            R1 = R1(:,1) & R1(:,2);

            L2 = [X(:,1),X(:,3)];
            M2 = [X(:,2),X(:,3)];
            R2 = [X(:,3),X(:,2)];

            L2 = (L2 == [i,j]);
            M2 = (M2 == [i,j]);
            R2 = (R2 == [i,j]);

            L2 = L2(:,1) & L2(:,2);
            M2 = M2(:,1) & M2(:,2);
            R2 = R2(:,1) & R2(:,2);

            C = [double(L1|L2),double(M1|M2),double(R1|R2)];
            % C = C & logical(keep);
            D = C';
            C = D(ind_keep');
            % A = [A,reshape(C',3*m,1)];
            A = [A,C];

        end
    end
end

% b = reshape(sign(quad2)',3*m,[]);

b = sign(quad2)';
b = b(ind_keep');

b(b == 1) = 0;
b(b == -1) = 1;

%% symmetry constraint

eq_sym = [];

for i = 1:n
    for j = i:n
        if i ~= j

            Lambda_ij = zeros(n);
            Lambda_ij(i,j) = 1;
            Lambda_ij(j,i) = 1;
            ind_ij = (triu(ones(n)) - eye(n)) + (triu(ones(n)) - eye(n))';
            eq_ij = Lambda_ij(logical(ind_ij));
            eq_sym = [eq_sym;eq_ij'];

        end
    end
end

% A = [A;[zeros(nchoosek(n,2),m),eq_sym]];
% b = [b;zeros(nchoosek(n,2),1)];

N = NullP(A,2);

if isempty(A)
    vld = 0;
    A_fixed = A_err;
    return;
end

% warning('off','comm:gflineq:NoSolution');
warning('on','comm:gflineq:NoSolution');
[x,vld] = gflineq(A,b,2);

if vld == 1

    sol = x(m+1:end);

    Lambda = triu(ones(n))' - eye(n);
    Lambda = Lambda + Lambda';
    Lambda = reshape(Lambda,n^2,1);
    Lambda(Lambda == 1) = sol;
    Lambda = reshape(Lambda,n,n)';

    Lambda(Lambda == 1) = -1;
    Lambda(Lambda == 0) = 1;

    A_fixed = kron(Lambda,[1;1]).*A_err;

else

    A_fixed = A_err;
    return;

end

end