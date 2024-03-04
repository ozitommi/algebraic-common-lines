function C = simulatedHeterogeneousCL(CLMangles)

m = length(CLMangles);
sizes = zeros(1,m);
for i = 1:m
    sizes(i) = size(CLMangles{i},2);
end

CLMs = cell(1,m);
for k = 1:m
    est = deg2rad(double(CLMangles{k}));
    n = sizes(k);
    est_cl = zeros(2*n,n);
    for i = 1:n-1
        for j = i+1:n
            est_cl(s3(i),j) = [cos(est(i,j));sin(est(i,j))];
            % est_cl(s3(i),j) = -[cos(est(i,j));sin(est(i,j))];
            % est_cl(s3(j),i) = [cos(est(j,i));sin(est(j,i))];
            est_cl(s3(j),i) = -[cos(est(j,i));sin(est(j,i))];
        end
    end
    CLMs{k} = est_cl;
end

% create partial common lines matrix
C = (1 - (-1))*rand(2*sum(sizes),sum(sizes)) + (-1);
idx_block = logical(kron(eye(sum(sizes)),ones(2,1)));
C(idx_block) = 0;

D = blkdiag(CLMs{:});
blocks_inds = {ones(2*n,n),ones(2*n,n),ones(2*n,n)};
idx_block = logical(blkdiag(blocks_inds{:}));
% D(idx_block) = 0;
% inds = (D ~= 0);
% C(inds) = D(inds);
C(idx_block) = D(idx_block);
% D(D == Inf) = 0;

end