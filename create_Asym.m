function [Asym,S] = create_Asym(n)

S = [];
a = sym(zeros(2*n,3));
for i = 1:2*n
    for j = 1:3
        name = "a" + i + j;
        a_ij = sym(convertStringsToChars(name));
        a(i,j) = a_ij;
        S = [S; a_ij];
    end
end

b = sym(zeros(3,n));
for i = 1:3
    for j = 1:n
        name = "b" + i + j;
        b_ij = sym(convertStringsToChars(name));
        b(i,j) = b_ij;
        S = [S; b_ij];
    end
end

Asym = a*b;
for i = 1:n
    Asym(s3(i),i) = [0;0];
end


end
