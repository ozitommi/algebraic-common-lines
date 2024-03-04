function [angles,keep] = checkBadDeterminants(A,theta)

n = size(A,2);

idx_block = logical(kron(eye(n),ones(2,1)));
A(idx_block) = 0;

% check the determinant equations by computing dot products
X = nchoosek(1:n,3);
m = size(X,1);

ind = logical(kron(eye(m),[1;1]));

ind1_ij = reshape([X(:,1),X(:,2)]',1,2,m);
ind1_ik = reshape([X(:,1),X(:,3)]',1,2,m);
take1_ij = A(reshape(s3(squeeze(ind1_ij(:,1,:))),2,1,m),ind1_ij(1,2,:));
take1_ik = A(reshape(s3(squeeze(ind1_ik(:,1,:))),2,1,m),ind1_ik(1,2,:));
tube1_ij = reshape(take1_ij(ind),2,1,m);
tube1_ik = reshape(take1_ik(ind),2,1,m);
block1 = [tube1_ij,tube1_ik];
dot1 = squeeze(block1(1,1,:).*block1(1,2,:) + block1(2,1,:).*block1(2,2,:));

ind2_ji = reshape([X(:,2),X(:,1)]',1,2,m);
ind2_jk = reshape([X(:,2),X(:,3)]',1,2,m);
take2_ji = A(reshape(s3(squeeze(ind2_ji(:,1,:))),2,1,m),ind2_ji(1,2,:));
take2_jk = A(reshape(s3(squeeze(ind2_jk(:,1,:))),2,1,m),ind2_jk(1,2,:));
tube2_ji = reshape(take2_ji(ind),2,1,m);
tube2_jk = reshape(take2_jk(ind),2,1,m);
block2 = [tube2_ji,tube2_jk];
dot2 = -squeeze(block2(1,1,:).*block2(1,2,:) + block2(2,1,:).*block2(2,2,:));

ind3_ki = reshape([X(:,3),X(:,1)]',1,2,m);
ind3_kj = reshape([X(:,3),X(:,2)]',1,2,m);
take3_ki = A(reshape(s3(squeeze(ind3_ki(:,1,:))),2,1,m),ind3_ki(1,2,:));
take3_kj = A(reshape(s3(squeeze(ind3_kj(:,1,:))),2,1,m),ind3_kj(1,2,:));
tube3_ki = reshape(take3_ki(ind),2,1,m);
tube3_kj = reshape(take3_kj(ind),2,1,m);
block3 = [tube3_ki,tube3_kj];
dot3 = squeeze(block3(1,1,:).*block3(1,2,:) + block3(2,1,:).*block3(2,2,:));

angles = rad2deg(acos(min(1,max(-1,[dot1,dot2,dot3]))));

ind_bad = (angles > 180 - 2*theta) | (angles < 2*theta);
keep = angles;
keep(ind_bad) = 0;
keep(~ind_bad) = 1;

end