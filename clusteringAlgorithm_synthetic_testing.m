
clear all;
format long;

%% Clustering algorithm

tic

% m = 2; % number of clusters
% n = 24; % number of common lines (must be divisible by 4!)
% 
% [C,cluster_labels] = heterogeneousCommonLines(m,n);
% 
% % % add random scaling
% % a = -1;
% % b = 1;
% % randlam = (b-a)*rand(m*n) + a;
% % randlam(logical(eye(m*n))) = 0;
% % randlam = (randlam + randlam')/2;
% % C = C.*kron(sign(randlam),[1;1]);
% 
% n = size(C,2);
% 
% noises = [0,0.025,0.05,0.075,0.1,0.15,0.2,0.25,0.3,0.4,0.5,0.6,0.7,0.8];
% NOISE = 13;
% 
% % rotational noise
% a = -noises(NOISE);
% b = noises(NOISE);
% noise_matrix = zeros(n);
% for i = 1:n
%     for j = 1:n
%         u = (b-a)*rand(1) + a;
%         noise_matrix(i,j) = u;
%         rotMat = [cos(u),-sin(u);sin(u),cos(u)];
%         C(s3(i),j) = rotMat*C(s3(i),j);
%     end
% end

% % C = importdata("synthetic_image_cl_matrix.mat");
% C = importdata("synthetic_imgae_cl_matrix_snr20.mat");
% % C = importdata("synthetic_imgae_cl_matrix_snr1.mat");
% % C = importdata("real_data_cl_matrix.mat");
% % C = importdata("real_data_cl_matrix_updated.mat");
% C = importdata("synthetic_imgae_cl_matrix_aspire_snr100.mat");
% C = importdata("real_data_cl_matrix_updated_aspire.mat");
% C = importdata("synthetic_imgae_cl_matrix_aspire_snr5.mat");
% C = importdata("synthetic_imgae_cl_matrix_aspire_snr1.mat");
% m = 4;
% % m = 3;

% est = importdata("updated_aspire_estimated_cl_matrix.mat");
% C = importdata("updated_aspire_estimated_cl_matrix.mat");
% gt = importdata("updated_aspire_groundtruth_cl_matrix.mat");
% rots = importdata("updated_aspire_rotation_matrix.mat");
% [est_oriented,gt_oriented] = orientLinesData(est,gt,rots);
% C = est_oriented;
% n = size(C,2);
% m = 1;
% % add random scaling
% a = -1;
% b = 1;
% randlam = (b-a)*rand(m*n) + a;
% randlam(logical(eye(m*n))) = 0;
% randlam = (randlam + randlam')/2;
% C = C.*kron(triu(ones(n)) - tril(ones(n)),[1;1]);

est1 = importdata("emd_2811_snr_1.mat");
% est1 = importdata("emd_2811_snr_5.mat");
% est1 = importdata("emd_2811_snr_10.mat");
% est1 = importdata("emd_4214_snr_1.mat");
% rots = importdata("snr_rotation_matrix.mat");
% [est_oriented1,~] = orientLinesData(est1,est1,rots);
% est1 = importdata("emd_2811_snr_10.mat");
est2 = importdata("emd_2858_snr_1.mat");
% est2 = importdata("emd_2858_snr_5.mat");
% est2 = importdata("emd_2858_snr_10.mat");
% [est_oriented2,~] = orientLinesData(est2,est2,rots);
est3 = importdata("emd_4214_snr_1.mat");
% est3 = importdata("emd_4214_snr_5.mat");
% est3 = importdata("emd_4214_snr_10.mat");
% [est_oriented3,~] = orientLinesData(est3,est3,rots);
CLMangles = cell(1,3);
CLMangles{1} = est1;
CLMangles{2} = est2;
CLMangles{3} = est3;
% CLMangles{1} = est_oriented1;
% CLMangles{2} = est_oriented2;
% CLMangles{3} = est_oriented3;
C = simulatedHeterogeneousCL(CLMangles);

% construct R^(1)
R1 = {};
n = size(C,2); % number of common lines
ind_rem = 1:n;

% best = [65,90,83,85,3,77,66,88,84, 31,56,43,53,55,37,71,29,41, 12,4,18,2,17,24,27,28,15, 78,80,63,75,81,60,70,64,67, ...
%     47,45,5,51,50,48,58,35,39, 21,68,7,6,11,23,20,10,14, 59,33,42,34,57,49,38,54,46, 87,79,82,74,72,69,52,76,62]; %% added!!
% ind_rem = setdiff(ind_rem,best); %% added!!

% flip = tril(-ones(n)) + eye(n) + triu(ones(n)) - eye(n);
% C = C.*kron(flip,[1;1]);

% clust_size = 5;
clust_size = 90;
MAX_TRY = 7500;

% set up ADMM parameters
data.n = clust_size;
data.keep = eye(clust_size);
data.IR_iter = 50;
% data.IR_iter = 100;
% data.IR_iter = 500;
data.objlp_tol = 5*10^-13;
data.conv_tol = 10;

num_par = 10; % number of parallel cores to run
output = [];
MATRICES = {};
LAMBDAS = {};
VARS = {};

c1 = 1:30;
c2 = 31:60;
c3 = 61:90;

% c1 = [0, 1, 2, 3, 4, 7, 8, 10, 11, 12, 14, 15, 20, 21, 25, 28, 29, 30, 32, 33, ...
%     35, 37, 38, 39, 40, 42, 44, 45, 46, 48, 49, 51, 53, 54, 55, 63, 65, 66, ...
%     67, 68, 69, 73, 74, 75, 78, 79, 81] + 1;
% c2 = [5, 6, 9, 13, 16, 17, 19, 22, 23, 24, 26, 27, 31, 34, 36, 41, 43, 47,...
%     52, 56, 57, 59, 61, 62, 64, 71, 72, 80] + 1;
% c3 = [18, 50, 58, 60, 76, 77] + 1;
% c4 = [70] + 1;

% parfor j = 1:num_par
for j = 1:num_par

    L1_errs = zeros(MAX_TRY,1);
    clusters = zeros(MAX_TRY,clust_size);
    MATRICES2 = {};
    LAMBDAS2 = {};
    VARS2 = {};

    for i = 1:MAX_TRY

        randinds = ind_rem(randperm(length(ind_rem)));
        randinds = randinds(1:clust_size)
        % intersect(randinds,c1)
        % cluster_labels
        % intersect(randinds,cluster_labels(1,:))
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

        % rows_randlam = zeros(n);
        % cols_randlam = zeros(n);
        % rows_randlam(randinds,:) = 1;
        % cols_randlam(:,randinds) = 1;
        % ind_randlam = logical(rows_randlam) & logical(cols_randlam);
        % randlam_t = randlam';
        % zero_diag_lam = ones(n) - diag(diag(ones(n)));
        % ind_randlam = ind_randlam & logical(zero_diag_lam);
        % cluster_randlam = (triu(ones(clust_size)) - eye(clust_size)) + (triu(ones(clust_size)) - eye(clust_size))';
        % cluster_randlam(cluster_randlam == 1) = randlam_t(ind_randlam')';
        % cluster_randlam = sign(cluster_randlam)'

        var = initialize_param(data,clusterCM);
        if var.vld == 1

            % [A_out,lam_out,fval,vld,conv,var] = runADMM_mex(initialize_param(data,clusterCM));
            [A_out,lam_out,var] = runADMM(initialize_param(data,clusterCM));
            % fval
            % a = 1;

        else

            L1_err = Inf;
            A_out = [];
            lam_out = [];
            var = [];

        end

        % conv
        % [~,Sigma,~] = svd(A_out,'vector');
        % log10(Sigma(3)) - log10(Sigma(4))
        % A_out = A_out/norm(A_out,'fro');
        % M = sqrt(reshape(sum(reshape(A_out.^2,2,clust_size^2),1),clust_size,clust_size));
        % norm_err = norm(M-M','fro');
        % [quad1,quad2] = checkQuadrics(A_out);
        % det_err = sum(norm(quad2(:,1) - quad2(:,2))) + sum(norm(quad2(:,2) - quad2(:,3)));
        % fval = norm_err + det_err;


        L1_errs(i) = var.objlp;
        clusters(i,:) = randinds;
        MATRICES2{i} = A_out;
        LAMBDAS2{i} = lam_out;
        VARS2{i} = var;


        i % printing to check run
        % randinds

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


%%

t = toc;

% output_new = zeros(size(output_full,1),size(output_full,2)+1);
% for i = 1:size(output_full,1)
%     var = VARS_full{i};
%     output_new(i,1) = var.objlp;
%     output_new(i,2:end) = output_full(i,:);
% end

% [output2,I] = sortrows(output_new,1,'ascend');
[output2,I] = sortrows(output_full,1,'ascend');
MATRICES2 = MATRICES_full(I);
LAMBDAS2 = LAMBDAS_full(I);
VARS2 = VARS_full(I);

% bad_ind = (output(:,2) == Inf) | isnan(output(:,2));
% output(bad_ind,:) = [];
% MATRICES(bad_ind) = [];
% LAMBDAS(bad_ind) = [];
% 
% for i = 1:size(output,1)
%     A = MATRICES{i};
%     [~,Sigma,~] = svd(A,'vector');
%     output(i,1) = log10(Sigma(3)) - log10(Sigma(4));
% end
% 
% [output,I] = sortrows(output,1,'descend');
% MATRICES = MATRICES(I);
% LAMBDAS = LAMBDAS(I);
% 
% bad_mats = zeros(size(output,1),1);
% for i = 1:size(output,1)
%     A = MATRICES{i};
%     A = A/norm(A,'fro');
%     [quad1,~] = checkQuadrics(A);
%     % bad_mats(i) = double(any(any(quad1 < 0.03)));
%     % bad_mats(i) = double(any(any(abs(LAMBDAS{i}) > 10)));
%     bad_mats(i) = double(any(any(quad1 < 0.03)) | any(any(abs(LAMBDAS{i}) > 10)));
% end
% 
% output2 = output;
% MATRICES2 = MATRICES;
% LAMBDAS2 = LAMBDAS;
% output2(logical(bad_mats),:) = [];
% MATRICES2(logical(bad_mats)) = [];
% LAMBDAS2(logical(bad_mats)) = [];
% % [output2,I] = sortrows(output2,1,'ascend');
% [output2,I] = sortrows(output2,1,'descend');
% MATRICES2 = MATRICES2(I);
% LAMBDAS2 = LAMBDAS2(I);

%%

% output(output(:,1) == 0,:) = [];
% [output,I] = sortrows(output,2);
% best_clusters = output(:,3:end);
% ind_rem = 1:82;
% % ind_rem = 1:50;
% 
% 
% % MATRICES = {};
% % for i = 1:11
% % 
% %     randinds = output(i,3:end);
% %     rowsC = zeros(2*n,n);
% %     colsC = zeros(2*n,n);
% %     rowsC(s3(randinds),:) = 1;
% %     colsC(:,randinds) = 1;
% %     indC = logical(rowsC) & logical(colsC);
% %     zero_diag = kron(ones(n) - diag(diag(ones(n))),[1;1]);
% %     indC = indC & logical(zero_diag);
% %     D = C';
% %     clusterCM = kron(ones(clust_size) - diag(diag(ones(clust_size))),[1;1])';
% %     clusterCM(clusterCM == 1) = D(indC')';
% %     clusterCM = clusterCM';
% %     [A_out,fval,vld,conv] = runADMM(initialize_param(data,clusterCM));
% %     MATRICES{i} = A_out;
% %     % [~,Sigma,~] = svd(A_out,'vector');
% %     % if log10(Sigma(3)) - log10(Sigma(4)) < 10
% %     %     outputC(i,1) = 0;
% %     % end
% % end
% 
% 
% 
% % CC = mat2cell(output,[31193,31193,31194,31194,31194,31194,31194,31194,31194,31194],6);
% % 
% % output_final = [];
% % MATRICES = {};
% % parfor j = 1:10
% % 
% %     outputC = CC{j};
% %     MATRICES2 = {};
% % 
% %     for i = 1:size(outputC,1)
% % 
% %         randinds = outputC(i,3:end);
% %         rowsC = zeros(2*n,n);
% %         colsC = zeros(2*n,n);
% %         rowsC(s3(randinds),:) = 1;
% %         colsC(:,randinds) = 1;
% %         indC = logical(rowsC) & logical(colsC);
% %         zero_diag = kron(ones(n) - diag(diag(ones(n))),[1;1]);
% %         indC = indC & logical(zero_diag);
% %         D = C';
% %         clusterCM = kron(ones(clust_size) - diag(diag(ones(clust_size))),[1;1])';
% %         clusterCM(clusterCM == 1) = D(indC')';
% %         clusterCM = clusterCM';
% %         [A_out,fval,vld,conv] = runADMM_mex(initialize_param(data,clusterCM));
% %         MATRICES2{i} = A_out;
% %         % [~,Sigma,~] = svd(A_out,'vector');
%         % % if log10(Sigma(3)) - log10(Sigma(4)) < 10
%         % %     outputC(i,1) = 0;
%         % % end
% %         i
% %     end
% % 
% %     output_final = [output_final;outputC];
% %     MATRICES = [MATRICES,MATRICES2];
% % 
% % end
% 
% % ranks = [];
% % for i = 1:11
% %     A = MATRICES{i};
% %     [~,Sigma,~] = svd(A,'vector');
% %     ranks = [ranks,log10(Sigma(3)) - log10(Sigma(4))];
% % end
% 
% 
% D = importdata("real_data_cl_dist_updated_aspire.mat");
% D = double(D);
% D(logical(tril(D))) = 0;
% D = D + D';
% % scale = 0.005;
% d = zeros(size(output,1),1);
% for i = 1:size(output,1)
%     A = MATRICES{i};
%     [~,Sigma,~] = svd(A,'vector');
%     [quad1,~] = checkQuadrics(A);
%     % if any(any(quad1 < 0.3))
%     if (log10(Sigma(3)) - log10(Sigma(4)) < 14) || any(any(quad1 < 0.3))
%         output(i,1) = 0;
%     end
%     % A = A/norm(A,'fro');
%     % M = sqrt(reshape(sum(reshape(A.^2,2,clust_size^2),1),clust_size,clust_size));
%     % norm_err = norm(M-M','fro');
%     % [quad1,quad2] = checkQuadrics(A);
%     % det_err = sum(norm(quad2(:,1) - quad2(:,2))) + sum(norm(quad2(:,2) - quad2(:,3)));
%     % fval = norm_err + det_err;
%     % output(i,2) = fval;
%     % inds = nchoosek(sort(output(i,3:end)),2);
%     % d(i) = -mean(diag(D(inds(:,1),inds(:,2))));
% end
% % output(:,2) = d;
% % output(:,2) = output(:,2) - scale*d;
% 
% bad_ind = output(:,1) == 0;
% output(bad_ind,:) = [];
% MATRICES(bad_ind) = [];
% [output,I] = sortrows(output,2);
% MATRICES = MATRICES(I);
% 
% c3c4_ind = any(ismember(output(:,3:end),c3),2) | ...
%     any(ismember(output(:,3:end),c4),2);
% output(c3c4_ind,:) = [];
% MATRICES(c3c4_ind) = [];
% 
% 
% best_clusters = output(:,3:end);
% ind_rem = 1:82;
% 
% 
% consistent_ind = all(ismember(output(:,3:end),c1),2) | ...
%     all(ismember(output(:,3:end),c2),2) | all(ismember(output(:,3:end),c3),2);
% 
% 
% 
% 
% 
% % consistent_ind = all(ismember(output(:,3:end),23),2) & ...
%     % ~all(ismember(output(:,3:end),c2),2);
% consistent_ind = any(ismember(output(:,3:end),59),2) & ...
%     all(sum(ismember(output(:,3:end),c1),2) >= 3,2);
% consistent_ind = all(ismember(output(:,3:end),c1),2);
% 
% ind_error = (any(ismember(output(:,3:end),59),2) & ...
%     all(sum(ismember(output(:,3:end),c1),2) >= 3,2)) | ...
%     all(ismember(output(:,3:end),c1),2);
% 
% 
% % small = output(all(ismember(output(:,3:end),c1),2),:);
% % small = any(ismember(output(:,3:end),23),2) & ~all(ismember(output(:,3:end),c2),2);
% f = find(consistent_ind == 1);
% 
% % ir = randperm(size(output,1));
% % output = output(ir,:);
% 
% 
% % appear = zeros(n,1);
% % for i = 1:n
% %     appear(i) = sum(sum(ismember(best_clusters,i)));
% % end
% % [~,I] = sort(appear);
% % output(any(ismember(best_clusters,I(1:4)),2),:) = [];
% % best_clusters = output(:,3:end);
% 
% 
% % scale = 0.005;
% % d = zeros(length(best_clusters),1);
% % for i = 1:length(best_clusters)
% %     inds = nchoosek(sort(best_clusters(i,:)),2);
% %     d(i) = mean(diag(D(inds(:,1),inds(:,2))));
% % end
% % output(:,2) = output(:,2) - scale*d;
% % % output(:,2) = d;
% % [output,~] = sortrows(output,2);
% % best_clusters = output(:,3:end);
% 
% % small = output(any(ismember(output(:,3:end),c1),2),:);
% % small = output(all(ismember(output(:,3:end),c1),2),:);
% 
% 
% % appear = [];
% % while ~isempty(output)
% %     sample = output(1,3:end);
% %     ind = all(ismember(output(:,3:end),sample),2);
% %     if sum(ind) == 5
% %         a = 1;
% %     end
% %     appear = [appear; sum(ind)];
% %     output(ind,:) = [];
% %     size(output,1)
% % end
% 
% % output(output(:,2) < 0.07,:) = [];
% 
% %% Merge the clusters
% 
% R = {};
% best_clusters = output(:,3:end);
% ind_rem = 1:82;
% ind_rem = setdiff(ind_rem,union(c3,c4));
% % max_clust = [30,15,5];
% % max_clust = [30,15,5];
% % max_clust = [58,30,11,1];
% % max_clust = [46,28,6,2];
% % max_clust = [50,26,5,1];
% % max_clust = [47,28,6,1];
% max_clust = [47,28];
% % max_clust = [30,15,4,1];
% % max_clust = [26,50,5,1];
% % max_clust = [49,25,4,1];
% % max_clust = [16,16,16];
% % max_clust = [24,24];
% 
% for i = 1:m-1
% 
%     S = best_clusters(1,:);
%     idx = 1;
%     best_clusters(idx,:) = [];
% 
%     while length(S) < max_clust(i)
% 
%         sample = best_clusters(idx,:);
% 
%         if not(isempty(intersect(S,sample))) && length(intersect(S,sample)) >= 3
%             S = union(S,sample);
%             setdiff(S,c1)
%             best_clusters(idx,:) = [];
%             idx = 1;
%         else
%             idx = idx + 1;
%         end
% 
%     end
% 
%     best_clusters(any(ismember(best_clusters,S),2),:) = [];
%     ind_rem = setdiff(ind_rem,S);
%     R(end+1) = {S};
% 
% end
% R(end+1) = {ind_rem};
% 
% % for i = 1:m-1
% % 
% %     S = best_clusters(1,:);
% %     idx = 2;
% % 
% %     while length(S) < max_clust(i)
% % 
% %         if not(isempty(intersect(S,best_clusters(idx,:)))) && length(intersect(S,best_clusters(idx,:))) >= 3
% %             S = union(S,best_clusters(idx,:));
% %         end
% % 
% %         idx = idx + 1;
% % 
% %     end
% % 
% %     best_clusters(any(ismember(best_clusters,S),2),:) = [];
% %     ind_rem = setdiff(ind_rem,S);
% %     R(end+1) = {S};
% % 
% % end
% % R(end+1) = {ind_rem};
% 
% % for i = 1:m-1
% % 
% %     S = best_clusters(1,:);
% %     idx = 2;
% % 
% %     while length(S) < max_clust(i)
% % 
% %         if not(isempty(intersect(S,best_clusters(idx,:))))
% %             S = union(S,best_clusters(idx,:));
% %         end
% % 
% %         idx = idx + 1;
% % 
% %     end
% % 
% %     best_clusters(any(ismember(best_clusters,S),2),:) = [];
% %     ind_rem = setdiff(ind_rem,S);
% %     R(end+1) = {S};
% % 
% % end
% % R(end+1) = {ind_rem};
% 
% 
% 
% % R{1} = best_clusters(1,:);
% % best_clusters(1,:) = [];
% % i = 1;
% % none = 0;
% % while ~isempty(R)
% % 
% %     sample = best_clusters(i,:);
% %     best_clusters(i,:) = [];
% % 
% %     for j = 1:length(R)
% %         if length(intersect(R{j},sample)) >= 3
% %             R{j} = union(R{j},sample);
% %             break;
% %         end
% %         none = 1;
% %     end
% %     if none == 1
% %         R{end} = sample;
% %     else
% % 
% %     end
% % 
% % 
% % 
% % end
% 
% 
% %% Calculate Rand index
% 
% clusters_recovered = [];
% % clusters_truth = [];
% for i = 1:length(R)
%     clusters_recovered = [clusters_recovered; [R{i}',i*ones(length(R{i}'),1)]];
% end
% % for i = 1:m
% %     clusters_truth = [clusters_truth; [cluster_labels(i,:)',i*ones(length(cluster_labels(i,:)'),1)]];
% % end
% clusters_recovered = sortrows(clusters_recovered,1);
% % clusters_truth = sortrows(clusters_truth,1);
% % clusters_truth = [1*ones(5,1);2*ones(30,1);3*ones(15,1)];
% % c1 = 1:5;
% % c2 = 6:35;
% % c3 = 36:50;
% 
% 
% 
% % % c1 = [1, 2, 3, 4, 5, 8, 9, 11, 13, 14, 15, 17, 18, 19, 22, 23, 24, 26, 27, 30, 31, ...
% % %     34, 35, 36, 37, 38, 40, 41, 43, 44, 46, 47, 49, 50, 51, 55, 57, 58, 59, ...
% % %     62, 63, 65, 67, 68, 69, 78, 80, 81, 82, 83, 84, 88, 89, 90, 93, 94, 95, 99] + 1;
% % % c2 = [12, 48, 53, 54, 60, 64, 70, 73, 75, 91, 92] + 1;
% % % c3 = [0, 6, 7, 10, 16, 20, 21, 25, 28, 29, 32, 33, 39, 42, 45, 52, 56, 61, 66, ...
% % %     71, 72, 74, 76, 77, 79, 86, 87, 96, 97, 98] + 1;
% % % c4 = [85] + 1;
% % % clusters_truth = ones(1,100);
% % % clusters_truth(c2) = 2;
% % % clusters_truth(c3) = 3;
% % % clusters_truth(c4) = 4;
% % 
% % % c1 = [6, 7, 10, 16, 20, 21, 25, 28, 29, 30, 32, 33, 39, 42, 45, 52, 56, 61, ...
% % %     66, 71, 72, 74, 76, 77, 79, 86, 87, 95] + 1;
% % % c2 = [1, 2, 3, 4, 5, 8, 9, 11, 13, 14, 17, 19, 26, 27, 31, 34, 36, 38, 40, ...
% % %     41, 44, 46, 47, 49, 50, 55, 57, 58, 59, 62, 63, 65, 67, 68, 69, 78, 80, ...
% % %     81, 82, 83, 84, 88, 89, 90, 93, 94, 99] + 1;
% % % c3 = [22, 64, 73, 75, 91, 92] + 1;
% % % c4 = [85] + 1;
% % % u = [0, 12, 15, 18, 23, 24, 35, 37, 43, 48, 51, 53, 54, 60, 70, 96, 97, 98] + 1;
% % % clusters_truth = ones(1,100);
% % % clusters_truth(c2) = 2;
% % % clusters_truth(c3) = 3;
% % % clusters_truth(c4) = 4;
% % % clusters_truth(u) = [];
% % 
% 
% % c1 = [0, 1, 2, 3, 4, 7, 8, 10, 11, 12, 14, 15, 18, 20, 21, 24, 25, 28, 29, ...
% %     30, 32, 33, 35, 37, 38, 39, 40, 42, 44, 45, 46, 48, 49, 51, 53, 54, 55, ...
% %     63, 65, 66, 67, 68, 69, 73, 74, 75, 78, 79, 80, 81] + 1;
% % c2 = [50, 58, 60, 76, 77] + 1;
% % c3 = [5, 6, 9, 13, 16, 17, 19, 22, 23, 26, 27, 31, 34, 36, 41, 43, 47, 52, ...
% %     56, 57, 59, 61, 62, 64, 71, 72] + 1;
% % c4 = [70] + 1;
% 
% b1 = [0, 1, 2, 3, 4, 7, 8, 10, 11, 12, 14, 15, 18, 20, 21, 24, 25, 28, 29, 30, 32, 33, 35, 37,...
%     38, 39, 40, 42, 44, 45, 46, 48, 49, 51, 53, 54, 55, 63, 65, 66, 67, 68, 69, 73, 74, 75, 78, 79, 80, 81] + 1;
% b2 =  [50, 58, 60, 70, 76, 77] + 1;
% b3 = [5, 6, 9, 13, 16, 17, 19, 22, 23, 26, 27, 31, 34, 36, 41, 43, 47, 52, 56, 57, 59, 61, 62, 64, 71, 72] + 1;
% 
% c1 = [0, 1, 2, 3, 4, 7, 8, 10, 11, 12, 14, 15, 20, 21, 25, 28, 29, 30, 32, 33, ...
%     35, 37, 38, 39, 40, 42, 44, 45, 46, 48, 49, 51, 53, 54, 55, 63, 65, 66, ...
%     67, 68, 69, 73, 74, 75, 78, 79, 81] + 1;
% c2 = [5, 6, 9, 13, 16, 17, 19, 22, 23, 24, 26, 27, 31, 34, 36, 41, 43, 47,...
%     52, 56, 57, 59, 61, 62, 64, 71, 72, 80] + 1;
% c3 = [18, 50, 58, 60, 76, 77] + 1;
% c4 = [70] + 1;
% 
% clusters_truth = ones(1,82);
% clusters_truth(c2) = 2;
% clusters_truth(c3) = 3;
% clusters_truth(c4) = 4;
% clusters_truth(union(c3,c4)) = [];
% 
% 
% % clusters_eric = ones(1,82);
% % clusters_eric(b2) = 2;
% % clusters_eric(b3) = 3;
% % 
% % ri_eric = rand_index(clusters_eric,clusters_truth);
% % ri_a_eric = rand_index(clusters_eric,clusters_truth,'adjusted');
% 
% 
% ri = rand_index(clusters_recovered(:,2),clusters_truth);
% ri_a = rand_index(clusters_recovered(:,2),clusters_truth,'adjusted');
% % ri = rand_index(clusters_recovered(:,2),clusters_truth(:,2));
% % ri_a = rand_index(clusters_recovered(:,2),clusters_truth(:,2),'adjusted');
% 
% t = toc;
% 
% %% Record
% 
% sample_size = MAX_TRY*num_par;
% % save('real_data-3-mil-run-2.mat','ri','ri_a','t','R','output','output_full','sample_size');
% % save('real_data-aspire-1-mil.mat','ri','ri_a','t','R','output','output_full','sample_size');
% % save('synthetic-apire-SNR=5-30000-samples.mat','ri','ri_a','t','R','output','output_full','sample_size');
% % save('real_data-aspire-500k.mat','R','output','output_full')
% % save('real_data-aspire-1k-8-cm.mat','R','output','output_full')
% % save('real_data-aspire-500k-run-2.mat','R','output','output_full')
% % save('real_data-aspire-1-mil-run-2.mat','R','output','output_full')
% % save('real_data-aspire-rank-3-matrices.mat','output_final','MATRICES')
% 
% save('real_data-aspire-8-cm-addie.mat','output_all','MATRICES_all')

% save('simulated_SNR_1-500k-samples.mat','output','MATRICES')
% save('simulated_SNR_1-250k-samples.mat','output','MATRICES','t')
% save('simulated_SNR_1-250k-samples-lambdas.mat','output_full','MATRICES_full','LAMBDAS_full','t')
% save('simulated_SNR_10k-samples-2.mat','output_full','MATRICES_full','LAMBDAS_full','VARS_full','t')
% save('simulated_SNR_50k-samples-1.mat','output_full','MATRICES_full','LAMBDAS_full','VARS_full','t')
% save('simulated_SNR_1mil-samples-1.mat','output_full','MATRICES_full','LAMBDAS_full','VARS_full','t')
% save('simulated_SNR_50k-samples-removed3.mat','output_full','MATRICES_full','LAMBDAS_full','VARS_full','t')
% save('simulated_SNR_50k-samples-removed7.mat','output_full','MATRICES_full','LAMBDAS_full','VARS_full','t')
