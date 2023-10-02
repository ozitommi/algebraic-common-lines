
clear all;
format long;

n = 3;

% create pure common lines matrices
[A,~,RotsA] = create_A(n);
[B,~,RotsB] = create_A(n);

% create partial common lines matrix
C = (1 - (-1))*rand(2*2*n,2*n) + (-1);
idx_block = logical(kron(eye(2*n),ones(2,1)));
C(idx_block) = 0;

% fill in the correct entries of C
C(s3(1),4) = A(s3(2),1);
C(s3(1),6) = A(s3(2),3);
C(s3(2),3) = B(s3(3),1);
C(s3(2),5) = B(s3(3),2);
C(s3(3),2) = B(s3(1),3);
C(s3(3),5) = B(s3(1),2);
C(s3(4),1) = A(s3(1),2);
C(s3(4),6) = A(s3(1),3);
C(s3(5),2) = B(s3(2),3);
C(s3(5),3) = B(s3(2),1);
C(s3(6),1) = A(s3(3),2);
C(s3(6),4) = A(s3(3),1);

% the true clusters
trueA = [1;4;6];
trueB = [2;3;5];

% check that pulling the true clusters out gives us back the pure common
% lines matrices
rowsA = zeros(2*2*n,2*n);
rowsB = zeros(2*2*n,2*n);
colsA = zeros(2*2*n,2*n);
colsB = zeros(2*2*n,2*n);
rowsA(s3(trueA),:) = 1;
rowsB(s3(trueB),:) = 1;
colsA(:,trueA) = 1;
colsB(:,trueB) = 1;
indA = logical(rowsA) & logical(colsA);
indB = logical(rowsB) & logical(colsB);
A_take = reshape(C(indA),2*n,n); % it doesn't matter if it doesn't exactly match A, it will still satisfy the constraints
B_take = reshape(C(indB),2*n,n);
[quad1,quad2] = checkQuadrics(A_take);
[quad1,quad2] = checkQuadrics(B_take);
[~,fvalA] = runADMM(A_take);
[~,fvalB] = runADMM(B_take);
fvalA
fvalB

%% Clustering algorithm for toy problem

clusters = cell(1,2);
p = size(C,2);
x0 = randperm(p);
clusters{1} = x0(1:3);
clusters{2} = x0(4:6);
thresh = 10^-10;

rand_inds = sort(randperm(2));
rand_inds = rand_inds(1:2);
clusterA = clusters{rand_inds(1)};
clusterB = clusters{rand_inds(2)};
rowsA = zeros(size(C,1),size(C,2));
rowsB = zeros(size(C,1),size(C,2));
colsA = zeros(size(C,1),size(C,2));
colsB = zeros(size(C,1),size(C,2));
rowsA(s3(clusterA),:) = 1;
rowsB(s3(clusterB),:) = 1;
colsA(:,clusterA) = 1;
colsB(:,clusterB) = 1;
indA = logical(rowsA) & logical(colsA);
indB = logical(rowsB) & logical(colsB);
A_take = reshape(C(indA),2*n,n);
B_take = reshape(C(indB),2*n,n);
% [quad1,quad2] = checkQuadrics(A_take2);
% [quad1,quad2] = checkQuadrics(B_take2);
[~,fvalA] = runADMM(A_take);
[~,fvalB] = runADMM(B_take);

while (fvalA > thresh) && (fvalB > thresh)

    rand_inds = sort(randperm(2));
    rand_inds = rand_inds(1:2);
    clusterA = clusters{rand_inds(1)};
    clusterB = clusters{rand_inds(2)};
    rowsA = zeros(size(C,1),size(C,2));
    rowsB = zeros(size(C,1),size(C,2));
    colsA = zeros(size(C,1),size(C,2));
    colsB = zeros(size(C,1),size(C,2));
    rowsA(s3(clusterA),:) = 1;
    rowsB(s3(clusterB),:) = 1;
    colsA(:,clusterA) = 1;
    colsB(:,clusterB) = 1;
    indA = logical(rowsA) & logical(colsA);
    indB = logical(rowsB) & logical(colsB);
    A_take = reshape(C(indA),2*n,n);
    B_take = reshape(C(indB),2*n,n);
    % [quad1,quad2] = checkQuadrics(A_take2);
    % [quad1,quad2] = checkQuadrics(B_take2);
    [~,fvalA] = runADMM(A_take);
    [~,fvalB] = runADMM(B_take);
    fvalA
    fvalB

    if (fvalA > thresh) && (fvalB > thresh)

        swapA = clusterA(randi(length(clusterA)));
        swapB = clusterB(randi(length(clusterB)));
        clusterA(clusterA == swapA) = [];
        clusterB(clusterB == swapB) = [];
        clusterA = [clusterA, swapB];
        clusterB = [clusterB, swapA];
        clusters{rand_inds(1)} = clusterA;
        clusters{rand_inds(2)} = clusterB;

    end

end











