function [A_out,fval,vld] = runADMM(A)

n = size(A,2);
data.n = n;
data.keep = not(logical(eye(n)));

data.E_est = cell(n,n);
for i = 1:n
    for j = 1:n
        data.E_est{i,j} = A(s3(i),j);
    end
end

%% Try to fix the signs of the scaled common lines matrix

[A_fixed,vld] = fixSigns(A);
if vld == 0
    A_out = zeros(2*n,n);
    fval = 0;
    return;
end

%% Optimization parameter initialization

IR_iter = 1;
data.A = A_fixed;
[var,~] = initialize_param(data);

%% Run IRLS and ADMM

[result] = IRLS(var,IR_iter);
var = result.var;

%% Output

A_out = var.E;
% quad1 = checkNorms(var.E);
[quad1,quad2] = checkQuadrics(var.E);
% fval = sum(abs(quad1(:,1) - quad1(:,2)));
fval = sum(abs(abs(quad2(:,1)) - abs(quad2(:,2)))) + sum(abs(abs(quad2(:,2)) - abs(quad2(:,2))));

% %% Fix norm equations with Sinkhorn
% 
% M = sqrt(reshape(sum(reshape((var.E).^2,2,n^2),1),n,n));
% fprintf('error before %.9e\n',norm(M-M','fro'));
% MAX_SH = 1000;
% 
% for i = 1:MAX_SH
% 
%     [L,~] = constructScaleMats(M);
%     [~,~,V] = svd(L);
%     d1 = V(:,end);
%     LM = diag(d1)*M;
%     M = norm(M,'fro')*(LM/norm(LM,'fro'));
%     LE = diag(repelem(d1,2))*(var.E);
%     var.E = norm(var.E,'fro')*(LE/norm(LE,'fro'));
% 
%     [~,R] = constructScaleMats(M);
%     [~,~,V] = svd(R);
%     d2 = V(:,end);
%     MR = M*diag(d2);
%     M = norm(M,'fro')*(MR/norm(MR,'fro'));
%     ER = (var.E)*diag(d2);
%     var.E = norm(var.E,'fro')*(ER/norm(ER,'fro'));
% 
% end
% 
% fprintf('error after %.9e\n',norm(M-M','fro'));
% 
% %% Fix determinant equations
% 
% var.A = var.E;
% [~,quad2] = checkQuadrics(var.E);
% var.quad = quad2;
% [D1,D2] = constructDetMats(var);
% [~,~,V] = svd(D1 + D2);
% scales = 1./V(:,end);
% Lambda = triu(ones(n))' - eye(n);
% Lambda(Lambda == 1) = scales;
% Lambda = Lambda + Lambda';
% E_new = kron(Lambda,ones(2,1)).*var.E;
% var.E = E_new*(norm(var.E,'fro')/norm(E_new,'fro'));
% 
% A_out = var.E;
% [quad1,quad2] = checkQuadrics(var.E)
% % fval = sum(abs(abs(quad2(:,1)) - abs(quad2(:,2)))) + sum(abs(abs(quad2(:,2)) - abs(quad2(:,2))));
% % M = sqrt(reshape(sum(reshape((var.E).^2,2,n^2),1),n,n));
% % fval = norm(M-M','fro');
% quad1 = checkNorms(var.E);
% fval = sum(abs(quad1(:,1) - quad1(:,2)));

end