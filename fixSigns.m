function [A_fixed,vld] = fixSigns(A_err)

% Finds sign flips to the entries of the input common lines matrix so that
% the signs of the determinant equations all match

[~,quad2] = checkQuadrics(A_err);

n = size(A_err,2);
m = size(quad2,1);

A = kron(eye(m),ones(3,1));
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
            A = [A,reshape(C',3*m,1)];

        end
    end
end

b = reshape(sign(quad2)',3*m,[]);
b(b == 1) = 0;
b(b == -1) = 1;

% warning('off','comm:gflineq:NoSolution');
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