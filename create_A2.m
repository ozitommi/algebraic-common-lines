function A = create_A2(R)

% Creates a synthetic pure (unscaled) common lines matrix from a given set
% of rotations.

n = size(R,2);

a = zeros(2*n,3);
for i = 1:2:2*n
    Ri = R{(i+1)/2};
    a(i,:) = -Ri(2,:);
    a(i+1,:) = Ri(1,:);
end

b = zeros(3,n);
for i = 1:n
    Ri = R{i};
    b(:,i) = Ri(3,:)';
end

A = a*b;
idx_block = logical(kron(eye(n),ones(2,1)));
A(idx_block) = 0;

end