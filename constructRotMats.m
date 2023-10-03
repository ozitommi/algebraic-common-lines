function [M,b] = constructRotMats(B)

% Creates the linear least squares matrix for the rotation recovery problem

n = size(B,1)/2;

b1 = B(:,1);
b2 = B(:,2);
b3 = B(:,3);

diagonal = zeros(9,1);
diagonal(1) = sum((kron(eye(n),[1,1])*(b1.*b1))'*(kron(eye(n),[1,1])*(b1.*b1)));
diagonal(2) = sum((kron(eye(n),[1,1])*(b1.*b2))'*(kron(eye(n),[1,1])*(b1.*b2)));
diagonal(3) = sum((kron(eye(n),[1,1])*(b1.*b3))'*(kron(eye(n),[1,1])*(b1.*b3)));
diagonal(4) = sum((kron(eye(n),[1,1])*(b2.*b1))'*(kron(eye(n),[1,1])*(b2.*b1)));
diagonal(5) = sum((kron(eye(n),[1,1])*(b2.*b2))'*(kron(eye(n),[1,1])*(b2.*b2)));
diagonal(6) = sum((kron(eye(n),[1,1])*(b2.*b3))'*(kron(eye(n),[1,1])*(b2.*b3)));
diagonal(7) = sum((kron(eye(n),[1,1])*(b3.*b1))'*(kron(eye(n),[1,1])*(b3.*b1)));
diagonal(8) = sum((kron(eye(n),[1,1])*(b3.*b2))'*(kron(eye(n),[1,1])*(b3.*b2)));
diagonal(9) = sum((kron(eye(n),[1,1])*(b3.*b3))'*(kron(eye(n),[1,1])*(b3.*b3)));

off = zeros(nchoosek(9,2),1);

off(1) = sum((kron(eye(n),[1,1])*(b1.*b1))'*(kron(eye(n),[1,1])*(b1.*b2)));
off(2) = sum((kron(eye(n),[1,1])*(b1.*b1))'*(kron(eye(n),[1,1])*(b1.*b3)));
off(3) = sum((kron(eye(n),[1,1])*(b1.*b1))'*(kron(eye(n),[1,1])*(b2.*b1)));
off(4) = sum((kron(eye(n),[1,1])*(b1.*b2))'*(kron(eye(n),[1,1])*(b1.*b2)));
off(5) = sum((kron(eye(n),[1,1])*(b1.*b2))'*(kron(eye(n),[1,1])*(b1.*b3)));
off(6) = sum((kron(eye(n),[1,1])*(b1.*b1))'*(kron(eye(n),[1,1])*(b3.*b1)));
off(7) = sum((kron(eye(n),[1,1])*(b1.*b2))'*(kron(eye(n),[1,1])*(b3.*b1)));
off(8) = sum((kron(eye(n),[1,1])*(b1.*b3))'*(kron(eye(n),[1,1])*(b1.*b3)));

off(9)  = sum((kron(eye(n),[1,1])*(b1.*b2))'*(kron(eye(n),[1,1])*(b1.*b3)));
off(10) = sum((kron(eye(n),[1,1])*(b1.*b1))'*(kron(eye(n),[1,1])*(b2.*b2)));
off(11) = sum((kron(eye(n),[1,1])*(b1.*b2))'*(kron(eye(n),[1,1])*(b2.*b2)));
off(12) = sum((kron(eye(n),[1,1])*(b1.*b3))'*(kron(eye(n),[1,1])*(b2.*b2)));
off(13) = sum((kron(eye(n),[1,1])*(b1.*b1))'*(kron(eye(n),[1,1])*(b2.*b3))); 
off(14) = sum((kron(eye(n),[1,1])*(b1.*b2))'*(kron(eye(n),[1,1])*(b3.*b2)));
off(15) = sum((kron(eye(n),[1,1])*(b1.*b3))'*(kron(eye(n),[1,1])*(b2.*b3))); 

off(16) = sum((kron(eye(n),[1,1])*(b1.*b1))'*(kron(eye(n),[1,1])*(b2.*b3)));
off(17) = sum((kron(eye(n),[1,1])*(b1.*b2))'*(kron(eye(n),[1,1])*(b2.*b3))); 
off(18) = sum((kron(eye(n),[1,1])*(b1.*b3))'*(kron(eye(n),[1,1])*(b2.*b3)));
off(19) = sum((kron(eye(n),[1,1])*(b1.*b1))'*(kron(eye(n),[1,1])*(b3.*b3)));  
off(20) = sum((kron(eye(n),[1,1])*(b1.*b2))'*(kron(eye(n),[1,1])*(b3.*b3))); 
off(21) = sum((kron(eye(n),[1,1])*(b1.*b3))'*(kron(eye(n),[1,1])*(b3.*b3)));

off(22) = sum((kron(eye(n),[1,1])*(b2.*b2))'*(kron(eye(n),[1,1])*(b1.*b2)));
off(23) = sum((kron(eye(n),[1,1])*(b2.*b1))'*(kron(eye(n),[1,1])*(b2.*b3)));
off(24) = sum((kron(eye(n),[1,1])*(b2.*b1))'*(kron(eye(n),[1,1])*(b3.*b1)));
off(25) = sum((kron(eye(n),[1,1])*(b2.*b2))'*(kron(eye(n),[1,1])*(b3.*b1)));
off(26) = sum((kron(eye(n),[1,1])*(b2.*b3))'*(kron(eye(n),[1,1])*(b3.*b1))); 

off(27) = sum((kron(eye(n),[1,1])*(b2.*b2))'*(kron(eye(n),[1,1])*(b2.*b3))); 
off(28) = sum((kron(eye(n),[1,1])*(b2.*b1))'*(kron(eye(n),[1,1])*(b3.*b2)));
off(29) = sum((kron(eye(n),[1,1])*(b2.*b2))'*(kron(eye(n),[1,1])*(b3.*b2)));
off(30) = sum((kron(eye(n),[1,1])*(b2.*b3))'*(kron(eye(n),[1,1])*(b3.*b2)));

off(31) = sum((kron(eye(n),[1,1])*(b2.*b1))'*(kron(eye(n),[1,1])*(b3.*b3))); 
off(32) = sum((kron(eye(n),[1,1])*(b2.*b2))'*(kron(eye(n),[1,1])*(b3.*b3)));
off(33) = sum((kron(eye(n),[1,1])*(b2.*b3))'*(kron(eye(n),[1,1])*(b3.*b3)));

off(34) = sum((kron(eye(n),[1,1])*(b3.*b1))'*(kron(eye(n),[1,1])*(b3.*b2)));
off(35) = sum((kron(eye(n),[1,1])*(b3.*b1))'*(kron(eye(n),[1,1])*(b3.*b3)));

off(36) = sum((kron(eye(n),[1,1])*(b3.*b2))'*(kron(eye(n),[1,1])*(b3.*b3)));

M = triu(ones(9))' - eye(9);
M(M == 1) = off;
M = M + M' + diag(diagonal);

b = zeros(9,1);

b(1) = sum(b1.^2);
b(2) = sum(b1.*b2);
b(3) = sum(b1.*b3);
b(4) = sum(b2.*b1);
b(5) = sum(b2.^2);
b(6) = sum(b2.*b3);
b(7) = sum(b1.*b3);
b(8) = sum(b2.*b3);
b(9) = sum(b3.^2);

end