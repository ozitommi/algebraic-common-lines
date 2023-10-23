% function [A_recover,R_recover] = recoverRotations2(var)
function [R_recover1,A_recover1,R_recover2,A_recover2] = recoverRotations(var)

n = var.n;

[U,~,~] = svd(var.E);
B = U(:,1:3);

[M,b] = constructRotMats(B);
S = reshape(lsqminnorm(M,b),3,3);
[V,Sigma] = eig(S);
B = B*V*sqrt(Sigma);

% recover the rotation matrices
R_recover1 = cell(1,n);

for i = 1:n
    Q = zeros(3);
    rows = B(s3(i),:);
    Q(1,:) = -rows(2,:);
    Q(2,:) = rows(1,:);
    v = cross(Q(1,:),Q(2,:));
    Q(3,:) = v;
    [Z,~,W] = svd(Q);
    R_recover1{i} = Z*W'; % round to the nearest orthogonal matrix
end

A_recover1 = create_A2(R_recover1); % reconstruct the pure common lines matrix

C = -B;

% recover the rotation matrices
R_recover2 = cell(1,n);

for i = 1:n
    Q = zeros(3);
    rows = C(s3(i),:);
    Q(1,:) = -rows(2,:);
    Q(2,:) = rows(1,:);
    v = cross(Q(1,:),Q(2,:));
    Q(3,:) = v;
    [Z,~,W] = svd(Q);
    R_recover2{i} = Z*W'; % round to the nearest orthogonal matrix
end

A_recover2 = create_A2(R_recover2); % reconstruct the pure common lines matrix

end
