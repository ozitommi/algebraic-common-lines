
clear all;
format long;

%% Import the data

est1 = importdata("emd_2811_snr_1.mat");
est2 = importdata("emd_2858_snr_1.mat");
est3 = importdata("emd_4214_snr_1.mat");
CLMangles = cell(1,3);
CLMangles{1} = est1;
CLMangles{2} = est2;
CLMangles{3} = est3;
C = simulatedHeterogeneousCL(CLMangles);

%% Set the parameters

% construct R^(1)
R1 = {};
n = size(C,2); % number of common lines
ind_rem = 1:n;

clust_size = 10;

% set up ADMM parameters
data.n = clust_size;
data.keep = eye(clust_size);
data.IR_iter = 50;
data.objlp_tol = 5*10^-13;
data.conv_tol = 10;

num_par = 10; % number of parallel cores to run
% num_par = 1;

c1 = 1:30;
c2 = 31:60;
c3 = 61:90;

exit = 0;
best = [];
N = 1;

%% Find the clusters

while ~exit

tic;

% if (N == 1) || (N == 2)
%     MAX_TRY = 7500;
%     % MAX_TRY = 1;
% else
%     MAX_TRY = 7500;
%     % MAX_TRY = 1;
% end

MAX_TRY = 10000;
% MAX_TRY = 7500;
% MAX_TRY = 1;

output = [];
MATRICES = {};
LAMBDAS = {};
VARS = {};

parfor j = 1:num_par
% for j = 1:num_par

    L1_errs = zeros(MAX_TRY,1);
    clusters = zeros(MAX_TRY,clust_size);
    MATRICES2 = {};
    LAMBDAS2 = {};
    VARS2 = {};

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

        var = initialize_param(data,clusterCM);
        if var.vld == 1

            [A_out,lam_out,var] = runADMM_mex(initialize_param(data,clusterCM));
            % [A_out,lam_out,var] = runADMM(initialize_param(data,clusterCM));

        else

            L1_err = Inf;
            A_out = [];
            lam_out = [];
            var = [];

        end

        L1_errs(i) = var.objlp;
        clusters(i,:) = randinds;
        MATRICES2{i} = A_out;
        LAMBDAS2{i} = lam_out;
        VARS2{i} = var;


        i % printing to check run

    end

    output = [output;[L1_errs,clusters]];
    MATRICES = [MATRICES,MATRICES2];
    LAMBDAS = [LAMBDAS,LAMBDAS2];
    VARS = [VARS,VARS2];

end

output_full = output;
MATRICES_full = MATRICES;
LAMBDAS_full = LAMBDAS;
VARS_full = VARS;

[output2,I] = sortrows(output_full,1,'ascend');
MATRICES2 = MATRICES_full(I);
LAMBDAS2 = LAMBDAS_full(I);
VARS2 = VARS_full(I);

t = toc;

save(strcat('simulated_SNR_full',num2str(N),'.mat'),'output2','MATRICES2','LAMBDAS2','VARS2','t')

best = [best;output2(1,2:end)];
ind_rem = setdiff(ind_rem,best);
N = N + 1;

if length(ind_rem) <= clust_size
    best = [best;ind_rem];
    exit = 1;
end

end

% %% Merge the clusters
% 
% % save('simulated_SNR_full_best','best');
% 
% est1 = importdata("emd_2811_snr_1.mat");
% est2 = importdata("emd_2858_snr_1.mat");
% est3 = importdata("emd_4214_snr_1.mat");
% CLMangles = cell(1,3);
% CLMangles{1} = est1;
% CLMangles{2} = est2;
% CLMangles{3} = est3;
% C = simulatedHeterogeneousCL(CLMangles);
% n = 90;
% clust_size = 9;
% 
% % best = [66,84,90,39,83,74,75,78,62;
% %     2,5,12,27,17,7,6,11,28;
% %     89,43,54,53,37,47,40,56,41;
% %     81,55,50,35,38,49,45,33,31;
% %     61,76,73,65,72,51,68,32,80;
% %     13,8,52,14,4,18,3,24,10;
% %     88,67,82,15,87,85,70,64,79;
% %     21,60,58,42,34,48,29,36,57;
% %     16,46,1,20,23,30,22,69,9];
% 
% best = [66,84,90,39,83,74,75,78,62;
%     2,5,12,27,17,7,6,11,28;
%     89,43,54,53,37,47,40,56,41;
%     81,55,50,35,38,49,45,33,31;
%     61,76,73,65,72,51,68,32,80;
%     13,8,52,14,4,18,3,24,10;
%     88,67,82,15,87,85,70,64,79;
%     21,60,58,42,34,48,29,36,57;
%     16,46,1,20,23,30,22,69,9;
%     19,25,26,44,59,63,71,77,86];
% 
% t = tic;
% 
% R1 = cell(1,size(best,1));
% for i = 1:size(best,1)
%     R1{i} = best(i,:);
% end
% 
% R = R1;
% std_devs = 8;
% sample_size = 100;
% R_old = length(R1) + 1;
% R_new = length(R1);
% 
% % % find fits of random clusters
% % m = n/clust_size;
% % scores = zeros(m-2,sample_size);
% % for j = 1:m-2
% % 
% %     k = j*clust_size;
% % 
% %     % set up ADMM parameters
% %     [missing_mu, missing_tau1, missing_tau2] = generateMissing(k);
% %     data.missing_mu = missing_mu;
% %     data.missing_tau1 = missing_tau1;
% %     data.missing_tau2 = missing_tau2;
% %     data.n = k;
% %     data.keep = eye(k);
% %     data.IR_iter = 5;
% %     data.objlp_tol = 5*10^-13;
% %     data.conv_tol = 10;
% %     data.norm_tol = 0.03;
% %     data.MAX_SH = 1000;
% % 
% %     for i = 1:sample_size
% % 
% %         randinds = randperm(n);
% %         randinds = randinds(1:k);
% %         rowsC = zeros(2*n,n);
% %         colsC = zeros(2*n,n);
% %         rowsC(s3(randinds),:) = 1;
% %         colsC(:,randinds) = 1;
% %         indC = logical(rowsC) & logical(colsC);
% %         zero_diag = kron(ones(n) - diag(diag(ones(n))),[1;1]);
% %         indC = indC & logical(zero_diag);
% %         D = C';
% %         cluster = reshape(D(indC'),k-1,2*k)';
% % 
% %         clusterCM = kron(ones(k) - diag(diag(ones(k))),[1;1])';
% %         clusterCM(clusterCM == 1) = cluster';
% %         clusterCM = clusterCM';
% % 
% %         % [A_out,lam_out,fval,vld,conv,var] = runADMM_mex(initialize_param(data,clusterCM));
% %         [~,~,var] = runADMM(initialize_param(data,clusterCM));
% %         var.objlp
% %         scores(j,i) = var.objlp;
% % 
% %     end
% % 
% % end
% % 
% % save('simulated_SNR_full_scores','scores');
% 
% while R_new < R_old
% 
%     ind_R = 1;
%     while ind_R < length(R)
% 
%         clusterA = R{ind_R};
%         ind_clust = 1;
%         exit = 0;
%         while ind_clust < length(R)-ind_R+1 && ~exit
% 
%             clusterB = R{ind_R + ind_clust};
%             clusterAB = [clusterA,clusterB];
%             k = length(clusterAB);
%             fprintf('Attempting to merge cluster of size %d \n',k);
% 
%             % set up ADMM parameters
%             data.n = k;
%             data.keep = eye(k);
%             data.IR_iter = 5;
%             data.objlp_tol = 5*10^-13;
%             data.conv_tol = 10;
% 
%             % find fit of merged clusters
%             rowsC = zeros(2*n,n);
%             colsC = zeros(2*n,n);
%             rowsC(s3(clusterAB),:) = 1;
%             colsC(:,clusterAB) = 1;
%             indC = logical(rowsC) & logical(colsC);
%             zero_diag = kron(ones(n) - diag(diag(ones(n))),[1;1]);
%             indC = indC & logical(zero_diag);
%             D = C';
%             cluster = reshape(D(indC'),k-1,2*k)';
% 
%             clusterCM = kron(ones(k) - diag(diag(ones(k))),[1;1])';
%             clusterCM(clusterCM == 1) = cluster';
%             clusterCM = clusterCM';
% 
%             % [~,~,~,~,~,var] = runADMM_mex(initialize_param(data,clusterCM));
%             [~,~,var] = runADMM(initialize_param(data,clusterCM));
%             var.objlp
% 
%             (mean(scores(k/clust_size,:)) - std_devs*std(scores(k/clust_size,:)))
%             clusterAB
%             if var.objlp < (mean(scores(k/clust_size,:)) - std_devs*std(scores(k/clust_size,:)))
% 
%                 fprintf('SUCCESS! Merged cluster \n');
%                 R{ind_R} = [clusterA, clusterB];
%                 R(ind_R + ind_clust) = [];
%                 exit = 1;
% 
%             else
% 
%                 fprintf('Failed to merge cluster \n');
% 
%             end
% 
%             ind_clust = ind_clust + 1;
% 
%         end
% 
%         ind_R = ind_R + 1;
% 
%     end
% 
%     R_old = R_new;
%     R_new = length(R);
% 
% end
% 
% toc
% 
% %% Calculate the Rand index
% 
% clusters_recovered = [];
% clusters_truth = [];
% for i = 1:length(R)
%     clusters_recovered = [clusters_recovered; [R{i}',i*ones(length(R{i}'),1)]];
% end
% % bad = [19,25,26,44,59,63,71,77,86];
% % ind_rem = 1:n;
% % ind_rem = setdiff(ind_rem,bad);
% clusters_recovered = [clusters_recovered;[bad',zeros(9,1)]];
% 
% c1 = 1:30;
% c2 = 31:60;
% c3 = 61:90;
% cluster_labels = [c1;c2;c3];
% for i = 1:3
%     clusters_truth = [clusters_truth; [cluster_labels(i,:)',i*ones(length(cluster_labels(i,:)'),1)]];
% end
% clusters_recovered = sortrows(clusters_recovered,1);
% clusters_truth = sortrows(clusters_truth,1);
% 
% clusters_recovered(bad,:) = [];
% clusters_truth(bad,:) = [];
% 
% ri = rand_index(clusters_recovered(:,2),clusters_truth(:,2))
% ri_a = rand_index(clusters_recovered(:,2),clusters_truth(:,2),'adjusted')

