
% clear all;
% format long;
% 
% D = importdata("Real Data/real_data-aspire-rank-3-matrices.mat");
% output = D.output_final;
% MATRICES = D.MATRICES;
% 
% m = 4;
% 
% c1 = [0, 1, 2, 3, 4, 7, 8, 10, 11, 12, 14, 15, 20, 21, 25, 28, 29, 30, 32, 33, ...
%     35, 37, 38, 39, 40, 42, 44, 45, 46, 48, 49, 51, 53, 54, 55, 63, 65, 66, ...
%     67, 68, 69, 73, 74, 75, 78, 79, 81] + 1;
% c2 = [5, 6, 9, 13, 16, 17, 19, 22, 23, 24, 26, 27, 31, 34, 36, 41, 43, 47,...
%     52, 56, 57, 59, 61, 62, 64, 71, 72, 80] + 1;
% c3 = [18, 50, 58, 60, 76, 77] + 1;
% c4 = [70] + 1;
% 
% %% Remove insufficiently rank 3 matrices
% 
% for i = 1:size(output,1)
%     A = MATRICES{i};
%     [~,Sigma,~] = svd(A,'vector');
%     [quad1,~] = checkQuadrics(A);
%     if (log10(Sigma(3)) - log10(Sigma(4)) < 14) || any(any(quad1 < 0.3))
%         output(i,1) = 0;
%     end
% end
% 
% bad_ind = output(:,1) == 0;
% output(bad_ind,:) = [];
% MATRICES(bad_ind) = [];
% [output,I] = sortrows(output,2);
% MATRICES = MATRICES(I);

%% Remove clusters c3 and c4

% c3c4_ind = any(ismember(output(:,3:end),c3),2) | ...
%     any(ismember(output(:,3:end),c4),2);
% output(c3c4_ind,:) = [];
% MATRICES(c3c4_ind) = [];

%% Construct weighted adjacency matrix

n = 82;
G = zeros(n);
% G = Inf*ones(n);
CMs= [];
best_clusters = output(:,3:end);
errors = output(:,2);
i = 1;
while i <= length(errors)
% while length(CMs) < n

    inds = best_clusters(i,:);
    CMs = union(CMs,inds);
    % G(inds,inds) = min(G(inds,inds),errors(i));
    G(inds,inds) = max(G(inds,inds),-log(errors(i)));
    i = i + 1;

end
% G(G == Inf) = 0;
G(logical(eye(n))) = 0;

%% Prune edges whose similarity is not high enough

% G_tril = tril(G);
% rank = 4;
% for i = 1:size(G,1)
% 
%     scores = sort(unique(G_tril(i:end,i)),'descend');
%     end_ind = max(1,length(scores)-1);
%     ind = G_tril(:,i) < scores(min(rank,end_ind));
%     G_tril(ind,i) = 0;
% 
% end
% 
% G = G_tril + G_tril';

%% Remove clusters c3 and c4

% G(union(c3,c4),union(c3,c4)) = [];
% G = G(union(c1,c2),union(c1,c2));

%% Plot graph

H = graph(G);
p = plot(H);
% highlight(p,c1,'NodeColor',[0.4940 0.1840 0.5560]);
% highlight(p,c2,'NodeColor',[0.4660 0.6740 0.1880]);
% highlight(p,c3,'NodeColor',[0.9290 0.6940 0.1250]);
% highlight(p,c4,'NodeColor',[0 0.4470 0.7410]);
% highlight(p,1:82,'MarkerSize',15);

%% Run Louvain community detection

% [clusters_recovered,Q] = community_louvain(G,0.76);
% % clusters_recovered(union(c3,c4)) = [];
% clusters_recovered

%% Perform spectral clustering

k = 2;
% idx = spectralcluster(G,k);
idx = spectralcluster(G,k,'Distance','precomputed');

% c1_rec = find(idx == 1)';
% c2_rec = find(idx == 2)';
% c3_rec = find(idx == 3)';
% c4_rec = find(idx == 4)';

c1_rec = setdiff(find(idx == 1)',union(c3,c4));
c2_rec = setdiff(find(idx == 2)',union(c3,c4));
% c3_rec = find(idx == 3)';
% c4_rec = find(idx == 4)';

R = {};
R{1} = c1_rec;
R{2} = c2_rec;
% R{3} = c3_rec;
% R{1} = setdiff(c1_rec,c4);
% R{2} = setdiff(c2_rec,c4);
% R{3} = setdiff(c3_rec,c4);

%% Compute Rand index

clusters_recovered = [];
for i = 1:length(R)
    clusters_recovered = [clusters_recovered; [R{i}',i*ones(length(R{i}'),1)]];
end
clusters_recovered = sortrows(clusters_recovered,1);

c1 = [0, 1, 2, 3, 4, 7, 8, 10, 11, 12, 14, 15, 20, 21, 25, 28, 29, 30, 32, 33, ...
    35, 37, 38, 39, 40, 42, 44, 45, 46, 48, 49, 51, 53, 54, 55, 63, 65, 66, ...
    67, 68, 69, 73, 74, 75, 78, 79, 81] + 1;
c2 = [5, 6, 9, 13, 16, 17, 19, 22, 23, 24, 26, 27, 31, 34, 36, 41, 43, 47,...
    52, 56, 57, 59, 61, 62, 64, 71, 72, 80] + 1;
c3 = [18, 50, 58, 60, 76, 77] + 1;
c4 = [70] + 1;

clusters_truth = ones(1,82);
clusters_truth(c2) = 2;
clusters_truth(c3) = 3;
clusters_truth(c4) = 4;
clusters_truth(union(c3,c4)) = [];
% clusters_truth(c4) = [];

ri = rand_index(clusters_recovered(:,2),clusters_truth);
ri_a = rand_index(clusters_recovered(:,2),clusters_truth,'adjusted');
% ri = rand_index(clusters_recovered,clusters_truth);
% ri_a = rand_index(clusters_recovered,clusters_truth,'adjusted');

%% Plot clustered graphs

U = G;
U(:,union(c3,c4)) = 0;
U(union(c3,c4),:) = 0;
U(c1_rec,c2_rec) = 0;
U(c2_rec,c1_rec) = 0;
H = graph(U);
p = plot(H);
highlight(p,c1,'NodeColor',[0.4940 0.1840 0.5560]);
highlight(p,c2,'NodeColor',[0.4660 0.6740 0.1880]);
highlight(p,c3,'NodeColor',[0.9290 0.6940 0.1250]);
highlight(p,c4,'NodeColor',[0 0.4470 0.7410]);
highlight(p,1:82,'MarkerSize',15);
