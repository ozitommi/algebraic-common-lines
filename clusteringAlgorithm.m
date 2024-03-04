
clear all;
format long;

%% Clustering algorithm

tic

m = 3; % number of clusters
n = 16; % number of common lines (must be divisible by 4!)

[C,cluster_labels] = heterogeneousCommonLines(m,n);

% add random scaling
a = -1;
b = 1;
randlam = (b-a)*rand(m*n) + a;
randlam(logical(eye(m*n))) = 0;
C = C.*kron(sign(randlam),[1;1]);

n = size(C,2);

noises = [0,0.025,0.05,0.075,0.1,0.15,0.2];
NOISE = 2;

% 0.789893617021277 at 0.025, 10,000 samples
% 0.749113475177305 at 0.025, 10,000 samples
% 0.606382978723404 at 0.05, 10,000 samples
% 0.645390070921986 at 0.05, 20,000 samples
% 0.695921985815603 at 0.05, 30,000 samples
% 0.584219858156028 at 0.075, 30,000 samples
% 0.557624113475177 at 0.1, 30,000 samples

% 0.566489361702128 new at 0.1, 10,000 samples

% rotational noise
a = -noises(NOISE);
b = noises(NOISE);
noise_matrix = zeros(n);
for i = 1:n
    for j = 1:n
        u = (b-a)*rand(1) + a;
        noise_matrix(i,j) = u;
        rotMat = [cos(u),-sin(u);sin(u),cos(u)];
        C(s3(i),j) = rotMat*C(s3(i),j);
    end
end

% construct R^(1)
R1 = {};
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
data.IR_iter = 50;
data.objlp_tol = 5*10^-13;
data.conv_tol = 100;
data.MAX_SH = 1000;

num_par = 1; % number of parallel cores to run
output = [];
A_outs = {};

% parfor j = 1:num_par
for j = 1:num_par

    convs = zeros(MAX_TRY,1);
    clusters = zeros(MAX_TRY,clust_size);
    fvals = zeros(MAX_TRY,1);
    norms = zeros(MAX_TRY,1);

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
        norms(i) = norm(A_out,'fro');
        A_outs(end+1) = {A_out};

        i % printing to check run

    end

    output = [output;[convs,fvals,clusters,norms]];

end

output_full = output;

output(output(:,1) == 0,:) = [];
% output(output(:,7) < 2.816169733772339 - 1*0.277509198115395,:) = [];
[output,I] = sortrows(output,2);
best_clusters = output(:,3:6);

%% Merge the clusters

R = {};
max_clust = 16;
for i = 1:m-1

    S = best_clusters(1,:);
    idx = 2;

    while length(S) < max_clust

        if not(isempty(intersect(S,best_clusters(idx,:))))
            S = union(S,best_clusters(idx,:));
        end

        idx = idx + 1;

    end

    best_clusters(any(ismember(best_clusters,S),2),:) = [];
    ind_rem = setdiff(ind_rem,S);
    R(end+1) = {S};

end
R(end+1) = {ind_rem};

%% Calculate Rand index

clusters_recovered = [];
clusters_truth = [];
for i = 1:length(R)
    clusters_recovered = [clusters_recovered; [R{i}',i*ones(length(R{i}'),1)]];
end
for i = 1:m
    clusters_truth = [clusters_truth; [cluster_labels(i,:)',i*ones(length(cluster_labels(i,:)'),1)]];
end
clusters_recovered = sortrows(clusters_recovered,1);
clusters_truth = sortrows(clusters_truth,1);

ri = rand_index(clusters_recovered(:,2),clusters_truth(:,2));

toc




