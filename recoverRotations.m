function [R_recover1,Q_recover1,A_recover1,R_recover2,Q_recover2,A_recover2] = recoverRotations(var)

n = var.n;

X = sym('X',[3,3]);
[U,~,~] = svd(var.E);
B = U(:,1:3);

% set up least squares problem
V = B*X*transpose(B);
I_rep = repmat(ones(2), 1, n);
I_cell = mat2cell(I_rep, 2, repmat(2,1,n));
ind = not(logical(blkdiag(I_cell{:})));
V(ind) = 0;

frob = sum(sum((V - eye(2*n)).^2));
jac = jacobian(frob,reshape(X,3^2,1));
S = vpasolve(jac == 0,reshape(X,3^2,1)); % symbolically solve for X
S = arrayfun(@(f) [S.(f{:})].', fieldnames(S), 'un', 0);
S = reshape([S{:}],3,3);
[V,Sigma] = eig(S);
if Sigma(3,3) < 0
    V = V*[1,0,0;0,1,0;0,0,-1];
    Sigma = Sigma*[1,0,0;0,1,0;0,0,-1];
end
B = B*V*sqrt(Sigma);

% recover the rotation matrices
Q_recover1 = cell(1,n);
R_recover1 = cell(1,n);

for i = 1:n
    Q = zeros(3);
    rows = B(s3(i),:);
    Q(1,:) = rows(2,:);
    Q(2,:) = -rows(1,:);
    v = cross(Q(1,:),Q(2,:));
    Q(3,:) = v;
    Q_recover1{i} = Q;
    [Z,~,W] = svd(Q);
    R_recover1{i} = Z*W'; % round to the nearest orthogonal matrix
end

A_recover1 = create_A2(R_recover1); % reconstruct the pure common lines matrix

%%

B = U(:,1:3);

X = sym('X',[3,3]);

% set up least squares problem
V = B*X*transpose(B);
I_rep = repmat(ones(2), 1, n);
I_cell = mat2cell(I_rep, 2, repmat(2,1,n));
ind = not(logical(blkdiag(I_cell{:})));
V(ind) = 0;

frob = sum(sum((V - eye(2*n)).^2));
jac = jacobian(frob,reshape(X,3^2,1));
S = vpasolve(jac == 0,reshape(X,3^2,1)); % symbolically solve for X
S = arrayfun(@(f) [S.(f{:})].', fieldnames(S), 'un', 0);
S = reshape([S{:}],3,3);
[V,Sigma] = eig(S);
if Sigma(3,3) < 0
    V = V*[1,0,0;0,1,0;0,0,-1];
    Sigma = Sigma*[1,0,0;0,1,0;0,0,-1];
end
B = -B*V*sqrt(Sigma);

% recover the rotation matrices
Q_recover2 = cell(1,n);
R_recover2 = cell(1,n);
for i = 1:n
    Q = zeros(3);
    rows = B(s3(i),:);
    Q(1,:) = rows(2,:);
    Q(2,:) = -rows(1,:);
    v = cross(Q(1,:),Q(2,:));
    Q(3,:) = v;
    Q_recover2{i} = Q;
    [Z,~,W] = svd(Q);
    R_recover2{i} = Z*W'; % round to the nearest orthogonal matrix
end

A_recover2 = create_A2(R_recover2); % reconstruct the pure common lines matrix

end

