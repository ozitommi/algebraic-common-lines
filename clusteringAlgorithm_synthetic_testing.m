
% clear all;
% format long;

%% Clustering algorithm

C = importdata("real_data_cl_matrix_updated_aspire.mat");
m = 4;

n = size(C,2); % number of common lines
ind_rem = 1:n;
clust_size = 8;
MAX_TRY = 50000;

% set up ADMM parameters
[missing_mu, missing_tau1, missing_tau2] = generateMissing(clust_size);
data.missing_mu = missing_mu;
data.missing_tau1 = missing_tau1;
data.missing_tau2 = missing_tau2;
data.n = clust_size;
data.keep = eye(clust_size);
data.IR_iter = 1000;
data.objlp_tol = 5*10^-13;
data.conv_tol = 15;
data.norm_tol = 10^-3;
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
        % [A_out,fval,vld,conv] = runADMM_mex(initialize_param(data,clusterCM));
        [A_out,fval,vld,conv] = runADMM(initialize_param(data,clusterCM));

        convs(i) = conv;
        fvals(i) = fval;
        clusters(i,:) = randinds;
        MATRICES2{i} = A_out;

        i

    end

    output = [output;[convs,fvals,clusters]];
    MATRICES = [MATRICES,MATRICES2];

end

output_full = output;
