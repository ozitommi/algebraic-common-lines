
n = 90;

R = {[66 84 90 39 83 74 75 78 62 61 76 73 65 72 51 68 32 80 88 67 82 15 87 85 70 64 79],...
     [2 5 12 27 17 7 6 11 28 13 8 52 14 4 18 3 24 10 16 46 1 20 23 30 22 69 9],...
     [89 43 54 53 37 47 40 56 41 81 55 50 35 38 49 45 33 31 21 60 58 42 34 48 29 36 57]};


% R = {[66 84 90 39 83 74 75 78 62 61 76 73 65 72 51 68 32 80 88 67 82 15 87 85 70 64 79 19 25 26 44 59 63 71 77 86],...
%     [2 5 12 27 17 7 6 11 28 13 8 52 14 4 18 3 24 10 16 46 1 20 23 30 22 69 9],...
%     [89 43 54 53 37 47 40 56 41 21 60 58 42 34 48 29 36 57 81 55 50 35 38 49 45 33 31]};

c1 = 1:30;
c2 = 31:60;
c3 = 61:90;

bad = [19,25,26,44,59,63,71,77,86];

G = zeros(n);
G(R{1},R{1}) = 1;
G(R{2},R{2}) = 1;
G(R{3},R{3}) = 1;
G(bad,bad) = 1;

G(logical(eye(size(G,1)))) = 0;
H = graph(G);
% H = rmnode(H,union(c3,c4));
p = plot(H);
highlight(p,c1,'NodeColor',[0.4940 0.1840 0.5560]);
highlight(p,c2,'NodeColor',[0.4660 0.6740 0.1880]);
highlight(p,c3,'NodeColor',[0.9290 0.6940 0.1250]);
% highlight(p,c4,'NodeColor',[0 0.4470 0.7410]);
highlight(p,1:90,'MarkerSize',15);
% C = conncomp(H);


