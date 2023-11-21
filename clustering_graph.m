





% A = [0, 1, 1, 0, 0, 0, 0, 0;
% 1, 0, 1, 1, 0, 0, 0, 0;
% 1, 1, 0, 0, 0, 0, 0, 0;
% 0, 1, 0, 0, 0, 0, 0, 0;
% 0, 0, 0, 0, 0, 1, 0, 0;
% 0, 0, 0, 0, 1, 0, 0, 0;
% 0, 0, 0, 0, 0, 0, 0, 0;
% 0, 0, 0, 0, 0, 0, 0, 0];
% 
% G = graph(A);
% plot(G);

% n = 82;
% % G = Inf*ones(n);
% G = zeros(n);
% % G2 = zeros(n);
% CMs= [];
% best_clusters = output(:,3:end);
% errors = output(:,2);
% i = 1;
% % while length(CMs) < n
% while i <= length(errors)
% 
%     inds = best_clusters(i,:);
%     CMs = union(CMs,inds);
%     % G(inds,inds) = G(inds,inds) + (1/i)*errors(i);
%     G(inds,inds) = min(G(inds,inds),errors(i));
%     % G2(inds,inds) = G2(inds,inds) + 1;
%     % G(inds,inds) = (G(inds,inds) + errors(i))/2;
%     % G(inds,inds) = G(inds,inds) + 1;
%     i = i + 1;
% 
% end
% % G(G == Inf) = 0;
% % G = G./G2;
% % G(isnan(G)) = 0;
% % G2 = 1./G2;
% % G2(G2 == Inf) = 0;
% % G2(isnan(G2)) = 0;
% % G2(logical(eye(n))) = 0;
% 
% % G = G + G2;
% G(logical(eye(n))) = 0;
% % G(logical(eye(n))) = Inf;

G = D;

% thresh = -1.9724;
% % thresh = -1.85;
% % thresh = -0.00045;
% G(G > thresh) = 0;

% thresh = 0.00075;
% thresh = 7;
% G = G/sum(sum(G));
thresh = 1.99;
G(G < thresh) = 0;


% G = zeros(n);
% G(R{1},R{1}) = 1;
% G(R{2},R{2}) = 1;
% G(R{3},R{3}) = 1;
% G(logical(eye(n))) = 0;
H = graph(G);
p = plot(H);
C = conncomp(H);
highlight(p,c1,'NodeColor',[0.4940 0.1840 0.5560]);
highlight(p,c2,'NodeColor',[0.4660 0.6740 0.1880]);
highlight(p,c3,'NodeColor',[0.9290 0.6940 0.1250]);
highlight(p,c4,'NodeColor',[0 0.4470 0.7410]);
highlight(p,1:82,'MarkerSize',15);

% c = find(C == 1)
% G(G > 0) = 1;

% G = Inf*ones(n);
% CMs = [];
% i = 1;
% while length(CMs) < n
% % while i <= length(errors)
% 
%     inds = best_clusters(i,:);
%     CMs = union(CMs,inds);
%     G(inds,inds) = min(G(inds,inds),errors(i));
%     % G(inds,inds) = (G(inds,inds) + errors(i))/2;
%     % G(inds,inds) = G(inds,inds) + 1;
%     i = i + 1;
% 
% end
% % G(G == Inf) = 0;
% % G(logical(eye(n))) = 0;
% G(logical(eye(n))) = Inf;
% G(c1,c1) = Inf;
% 
% thresh = 0.015;
% G(G > thresh) = 0;
% 
% % thresh = 0.0008;
% % G = G/sum(sum(G));
% % G(G < thresh) = 0;
% 
% H = graph(G);
% plot(H);
% C = conncomp(H);
% % c1 = find(C == 1)
% 
% 
% % idx = find(maxk(G,30));
% % [x,y] = ind2sub(size(G), idx);
% % 
% % U = triu(G);
% % [A,ind] = sort(U(:),'descend');
% % sz = [82,82];
% % [row,col] = ind2sub(sz,ind);
% % j = 1;
% % c = [];
% % c1 = [];
% % while length(c1) < 50
% %     % [~,ind] = maxk(U(:),j);
% %     % sz = [82,82];
% %     % [row,col] = ind2sub(sz,ind);
% %     % c1 = union(c1,union(row,col));
% %     c1 = union(c1,union(row(j),col(j)));
% %     length(c1)
% %     j = j + 1;
% % end
% % % U(c1,c1) = -1;
% % % j = 1;
% % c = union(c,c1);
% % c2 = [];
% % while length(c2) < 26
% %     % [~,ind] = maxk(U(:),j);
% %     % ind = ind(51:end);
% %     % sz = [82,82];
% %     % [row,col] = ind2sub(sz,ind);
% %     if ~ismember(row(j),c) && ~ismember(col(j),c)
% %         c2 = union(c2,union(row(j),col(j)));
% %         length(c2)
% %     end
% %     j = j + 1;
% % end
% % c = union(c,c2);
% % % U(c2,c2) = -1;
% % % j = 1;
% % c3 = [];
% % while length(c3) < 5
% %     [~,ind] = maxk(U(:),j);
% %     ind = ind(77:end);
% %     sz = [82,82];
% %     [row,col] = ind2sub(sz,ind);
% %     c3 = union(c3,union(row,col));
% %     length(c3)
% %     j = j + 1;
% % end
% % 
% % [max_count,ind] = maxk(G(:),230);
% % sz = [82,82];
% % [row,col] = ind2sub(sz,ind);
% % c1 = union(row,col);
% % R{1} = c1';
% % R{2} = setdiff(ind_rem,c1);
% 



