
clear all;
format long;

%% Clustering algorithm

tic

% the number of clusters
m = 8; 
% the number of common lines
n = 15; % must be divisible by 3!

[C,cluster_labels] = heterogeneousCommonLines(m,n);
% add random scaling
a = -1;
b = 1;
randlam = (b-a)*rand(m*n) + a;
randlam(logical(eye(m*n))) = 0;
C = C.*kron(sign(randlam),[1;1]);

% construct R^(1)
R1 = {};
p = size(C,2);
ind_rem = 1:p;
thresh = 10^-6;
success = 1;
while ~isempty(ind_rem)

    rand3inds = ind_rem(randperm(length(ind_rem)));
    rand3inds = rand3inds(1:3);
    rowsC = zeros(m*2*n,m*n);
    colsC = zeros(m*2*n,m*n);
    rowsC(s3(rand3inds),:) = 1;
    colsC(:,rand3inds) = 1;
    indC = logical(rowsC) & logical(colsC);
    zero_diag = kron(ones(m*n) - diag(diag(ones(m*n))),[1;1]);
    indC = indC & logical(zero_diag);
    D = C';
    cluster = reshape(D(indC'),2,2*3)';

    clusterCM = kron(ones(3) - diag(diag(ones(3))),[1;1])';
    clusterCM(clusterCM == 1) = cluster';
    clusterCM = clusterCM';
    [A_out,fval] = runADMM(clusterCM);
    if fval < thresh
        R1(end+1) = {rand3inds};
        ind_rem = setdiff(ind_rem,rand3inds);
        fprintf('Clutser %d: consistent triple found! \n',success);
        success = success + 1;
    end
end


% merge the clusters together
R = R1;
R_old = length(R1) + 1;
R_new = length(R1);
while R_new < R_old

    ind_R = 1;
    while ind_R < length(R)

        clusterA = R{ind_R};
        ind_clust = 1;
        exit = 0;
        while ind_clust < length(R)-ind_R+1 && ~exit
            clusterB = R{ind_R + ind_clust};
            indA = randperm(length(clusterA));
            indA = indA([1,2]);
            indB = randperm(length(clusterB));
            indB = indB([1,2]);
            clusterAB = [clusterA(indA), clusterB(indB)];
            k = length(clusterAB);
            fprintf('Attempting to merge cluster of size %d \n',length([clusterA, clusterB]));
            
            rowsC = zeros(m*2*n,m*n);
            colsC = zeros(m*2*n,m*n);
            rowsC(s3(clusterAB),:) = 1;
            colsC(:,clusterAB) = 1;
            indC = logical(rowsC) & logical(colsC);
            zero_diag = kron(ones(m*n) - diag(diag(ones(m*n))),[1;1]);
            indC = indC & logical(zero_diag);
            D = C';
            cluster = reshape(D(indC'),k-1,2*k)';

            clusterCM = kron(ones(k) - diag(diag(ones(k))),[1;1])';
            clusterCM(clusterCM == 1) = cluster';
            clusterCM = clusterCM';
            [A_out,fval,vld] = runADMM(clusterCM);
            if vld == 1
                if fval < thresh
                    fprintf('SUCCESS! Merged cluster \n');
                    R{ind_R} = [clusterA, clusterB];
                    R(ind_R + ind_clust) = [];
                    exit = 1;
                else
                    fprintf('Failed to merge cluster \n');
                end
            else
                fprintf('Failed to merge cluster \n');
            end
            ind_clust = ind_clust + 1;

        end
        ind_R = ind_R + 1;

    end

    R_old = R_new;
    R_new = length(R);

end

toc
