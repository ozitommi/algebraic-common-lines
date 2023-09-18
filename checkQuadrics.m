function [quad1,quad2] = checkQuadrics(A)

n = size(A,2);

idx_block=logical(kron(eye(n),ones(2,1)));
A(idx_block)=0;

M = sqrt(reshape(sum(reshape(A.^2,2,n^2),1),n,n));
ind_ij = nchoosek(1:n,2);
ind_ji = [ind_ij(:,2),ind_ij(:,1)];
quad1 = [M(sub2ind(size(M),ind_ij(:,1),ind_ij(:,2))),M(sub2ind(size(M),ind_ji(:,1),ind_ji(:,2)))];

quad2 = zeros(nchoosek(n,3),3);
ind_ijk = nchoosek(1:n,3);
for i = 1:nchoosek(n,3)
    P = perms(ind_ijk(i,:));
    P(:,3) = [];
    P = flip(P);
    P = [s3(P(:,1)),kron(P(:,2),[1;1])];
    V = A(sub2ind(size(A),P(:,1),P(:,2)));
    quad2(i,:) = [det([V(1:2,1),V(3:4,1)]),-det([V(5:6,1),V(7:8,1)]),det([V(9:10,1),V(11:12,1)])];
end


end