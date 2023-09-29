function [L,R] = constructScaleMats(M)

n = size(M,1);

%% Construct the Jacobian matrices for the set of norm equations

diagonalL = sum(M.^2,2);
diagonalR = sum(M.^2,1);
ind_upper = logical(triu(ones(n),1));
M_trans = M';
off = -M(ind_upper).*M_trans(ind_upper);
L = triu(ones(n),1);
L(ind_upper) = off;
R = L;
L = L + L' + diag(diagonalL);
R = R + R' + diag(diagonalR);

% L = zeros(n);
% for i = 1:n
%     for j = i:n
%         if i == j
%             ind = 1:n;
%             ind(i) = [];
%             L(i,j) = (1/2)*2*sum(M(i,ind).^2);
%         else
%             L(i,j) = -2*M(i,j)*M(j,i);
%         end
%     end
% end
% L = (1/2)*(L + L')
% 
% R = zeros(n);
% for i = 1:n
%     for j = i:n
%         if i == j
%             ind = 1:n;
%             ind(i) = [];
%             R(i,j) = (1/2)*2*sum(M(ind,i).^2);
%         else
%             R(i,j) = -2*M(i,j)*M(j,i);
%         end
%     end
% end
% R = (1/2)*(R + R')

end