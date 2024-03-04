clear all;
format long;

D = importdata("Real Data/real_data-aspire-rank-3-matrices.mat");
% output = D.output;
output = D.output_final;
% output_full = D.output_full;
MATRICES = D.MATRICES;
m = 4;

%% (Optional) Remove clusters c3 and c4

c1 = [0, 1, 2, 3, 4, 7, 8, 10, 11, 12, 14, 15, 20, 21, 25, 28, 29, 30, 32, 33, ...
    35, 37, 38, 39, 40, 42, 44, 45, 46, 48, 49, 51, 53, 54, 55, 63, 65, 66, ...
    67, 68, 69, 73, 74, 75, 78, 79, 81] + 1;
c2 = [5, 6, 9, 13, 16, 17, 19, 22, 23, 24, 26, 27, 31, 34, 36, 41, 43, 47,...
    52, 56, 57, 59, 61, 62, 64, 71, 72, 80] + 1;
c3 = [18, 50, 58, 60, 76, 77] + 1;
c4 = [70] + 1;

% c3c4_ind = any(ismember(output(:,3:end),c3),2) | ...
%     any(ismember(output(:,3:end),c4),2);
% output(c3c4_ind,:) = [];

%% Remove insufficiently rank 3 matrices

for i = 1:size(output,1)
    A = MATRICES{i};
    [~,Sigma,~] = svd(A,'vector');
    [quad1,~] = checkQuadrics(A);
    % if any(any(quad1 < 0.3))
    if (log10(Sigma(3)) - log10(Sigma(4)) < 14) || any(any(quad1 < 0.3))
    % if (log10(Sigma(3)) - log10(Sigma(4)) < 14)
        output(i,1) = 0;
    end
end

bad_ind = output(:,1) == 0;
output(bad_ind,:) = [];
MATRICES(bad_ind) = [];
[output,I] = sortrows(output,2);
MATRICES = MATRICES(I);

c3c4_ind = any(ismember(output(:,3:end),c3),2) | ...
    any(ismember(output(:,3:end),c4),2);
output(c3c4_ind,:) = [];
MATRICES(c3c4_ind) = [];

%% Merge the clusters

R = {};
best_clusters = output(:,3:end);
ind_rem = 1:82;
ind_rem = setdiff(ind_rem,union(c3,c4));


max_clust = [47,28];
% max_clust = [47,28,6,1];

for i = 1:m-1

    S = best_clusters(1,:);
    idx = 1;
    best_clusters(idx,:) = [];

    while length(S) < max_clust(i)

        sample = best_clusters(idx,:);

        if not(isempty(intersect(S,sample))) && length(intersect(S,sample)) >= 3
            S = union(S,sample);
            setdiff(S,c1)
            best_clusters(idx,:) = [];
            idx = 1;
        else
            idx = idx + 1;
        end

    end

    best_clusters(any(ismember(best_clusters,S),2),:) = [];
    ind_rem = setdiff(ind_rem,S);
    R(end+1) = {S};

end
R(end+1) = {ind_rem};

%% Calculate Rand index

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

ri = rand_index(clusters_recovered(:,2),clusters_truth);
ri_a = rand_index(clusters_recovered(:,2),clusters_truth,'adjusted');
