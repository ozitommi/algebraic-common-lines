function [A,A_flat] = create_A(n)

R = cell(1,n);
for i = 1:n
    U = RandOrthMat(3);
    if abs(det(U) - (-1)) < 10^(-12)
        R{i} = -U;
    else
        R{i} = U;
    end
end

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

C = A';
D = transpose(abs(A) > 10^(-12));
A_flat = transpose(C(D));

end