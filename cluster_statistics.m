

% clear all;
format long;

%% Clustering algorithm

tic

C = importdata("real_data_cl_matrix_updated_aspire.mat");
% C = importdata("real_data_cl_matrix_cluster_0_updated_aspire.mat");

n = size(C,2); % number of common lines
ind_rem = 1:n;
clust_size = 4;
MAX_TRY = 1000;

% set up ADMM parameters
[missing_mu, missing_tau1, missing_tau2] = generateMissing(clust_size);
data.missing_mu = missing_mu;
data.missing_tau1 = missing_tau1;
data.missing_tau2 = missing_tau2;
data.n = clust_size;
data.keep = eye(clust_size);
data.IR_iter = 500;
data.objlp_tol = 5*10^-13;
data.conv_tol = 100;
data.norm_tol = 0.1;
data.MAX_SH = 1000;

num_par = 10; % number of parallel cores to run
output = [];
MATRICES = {};

% parfor j = 1:num_par
for j = 1:num_par

    convs = zeros(MAX_TRY,1);
    clusters = zeros(MAX_TRY,clust_size);
    fvals = zeros(MAX_TRY,1);
    MATRICES2 = {};

    for i = 1:MAX_TRY

        randinds = ind_rem(randperm(length(ind_rem)));
        randinds = randinds(1:clust_size);
        rowsC = zeros(2*n,n);
        colsC = zeros(2*n,n);
        rowsC(s3(randinds),:) = 1;
        colsC(:,randinds) = 1;
        indC = logical(rowsC) & logical(colsC);
        zero_diag = kron(ones(n) - diag(diag(ones(n))),[1;1]);
        indC = indC & logical(zero_diag);
        D = C';

        clusterCM = kron(ones(clust_size) - diag(diag(ones(clust_size))),[1;1])';
        clusterCM(clusterCM == 1) = D(indC')';

        clusterCM = clusterCM';
        [A_out,fval,vld,conv] = runADMM_mex(initialize_param(data,clusterCM));

        % [~,Sigma,~] = svd(A_out,'vector')
        % A_out
        % A_out = A_out/norm(A_out,'fro');
        % M = sqrt(reshape(sum(reshape(A_out.^2,2,clust_size^2),1),clust_size,clust_size));
        % norm_err = norm(M-M','fro');
        % [quad1,quad2] = checkQuadrics(A_out);
        % det_err = sum(norm(quad2(:,1) - quad2(:,2))) + sum(norm(quad2(:,2) - quad2(:,3)));
        % fval = norm_err + det_err
        % sum(sum(quad1 < data.norm_tol))
        % setdiff([13,16,49],randinds)

        convs(i) = conv;
        fvals(i) = fval;
        clusters(i,:) = randinds;
        MATRICES2{i} = A_out;

        i % printing to check run

    end

    output = [output;[convs,fvals,clusters]];
    MATRICES = [MATRICES,MATRICES2];

end

output_full = output;

output = output_full;
% output(:,1) = ones(size(output,1),1);
for i = 1:size(output,1)
    A = MATRICES{i};
    [~,Sigma,~] = svd(A,'vector');
    % [quad1,~] = checkQuadrics(A);
    % if any(any(quad1 < 0.001))
    % if (log10(Sigma(3)) - log10(Sigma(4)) < 8) || any(any(quad1 < 0.2))
    if (log10(Sigma(3)) - log10(Sigma(4)) < 10)
        % output(i,1) = 0;
        output(i,2) = 0;
    end
    % A = A/norm(A,'fro');
    % M = sqrt(reshape(sum(reshape(A.^2,2,clust_size^2),1),clust_size,clust_size));
    % norm_err = norm(M-M','fro');
    % [quad1,quad2] = checkQuadrics(A);
    % det_err = sum(norm(quad2(:,1) - quad2(:,2))) + sum(norm(quad2(:,2) - quad2(:,3)));
    % fval = norm_err + det_err;
    % output(i,2) = fval;
    % inds = nchoosek(sort(output(i,3:end)),2);
    % d(i) = -mean(diag(D(inds(:,1),inds(:,2))));
end
% bad_ind = output(:,1) == 0;
bad_ind = output(:,2) == 0;
output(bad_ind,:) = [];
MATRICES(bad_ind) = [];
[output,I] = sortrows(output,2);
MATRICES = MATRICES(I);
best_clusters = output(:,3:end);
ind_rem = 1:82;

consistent_ind = all(ismember(output(:,3:end),c1),2) | ...
    all(ismember(output(:,3:end),c2),2) | all(ismember(output(:,3:end),c3),2);

t = toc;

% save('real_data-aspire-6-cm.mat','output_full','MATRICES')




