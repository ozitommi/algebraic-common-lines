

# import Pkg; Pkg.add("HomotopyContinuation")

using HomotopyContinuation
using LinearAlgebra

# Function to generate a random special orthogonal matrix using unit quaternion representation
function random_rotation_matrix()
    q = rand(4)
    q ./= norm(q)
    
    a, b, c, d = q
    
    [a^2+b^2-c^2-d^2 2*(b*c-a*d)     2*(b*d+a*c);
     2*(b*c+a*d)     a^2-b^2+c^2-d^2 2*(c*d-a*b);
     2*(b*d-a*c)     2*(c*d+a*b)     a^2-b^2-c^2+d^2]
end

function common_lines(R1,R2,R3)

      [-R1[2,1] -R1[2,2] -R1[2,3];
      R1[1,1]  R1[1,2]  R1[1,3];
      -R2[2,1] -R2[2,2] -R2[2,3];
      R2[1,1]  R2[1,2]  R2[1,3];
      -R3[2,1] -R3[2,2] -R3[2,3];
      R3[1,1]  R3[1,2]  R3[1,3]]*[R1[1,3] R2[1,3] R3[1,3];
                                           R1[2,3] R2[2,3] R3[2,3];
                                           R1[3,3] R2[3,3] R3[3,3]]

end

# Generate two random special orthogonal matrices
R = random_rotation_matrix()
S = random_rotation_matrix()

# Generate random pure common lines matrices
I = [1 0 0 ;
     0 1 0 ;
     0 0 1]

A = common_lines(I,R,S)

# Set up the system of polynomial equations
@polyvar a1 b1 c1 d1 a2 b2 c2 d2
# @var a1 b1 c1 d1 a2 b2 c2 d2

# Unit quaternion representation for rotation matrix R
Ra1 = a1^2 + b1^2 - c1^2 - d1^2
Ra2 = 2*(b1*c1 - a1*d1)
Ra3 = 2*(b1*d1 + a1*c1)
Rb1 = 2*(b1*c1 + a1*d1)
Rb2 = a1^2 - b1^2 + c1^2 - d1^2
Rb3 = 2*(c1*d1 - a1*b1)
Rc1 = 2*(b1*d1 - a1*c1)
Rc2 = 2*(c1*d1 + a1*b1)
Rc3 = a1^2 - b1^2 - c1^2 + d1^2

# Unit quaternion representation for rotation matrix S
Sa1 = a2^2 + b2^2 - c2^2 - d2^2
Sa2 = 2*(b2*c2 - a2*d2)
Sa3 = 2*(b2*d2 + a2*c2)
Sb1 = 2*(b2*c2 + a2*d2)
Sb2 = a2^2 - b2^2 + c2^2 - d2^2
Sb3 = 2*(c2*d2 - a2*b2)
Sc1 = 2*(b2*d2 - a2*c2)
Sc2 = 2*(c2*d2 + a2*b2)
Sc3 = a2^2 - b2^2 - c2^2 + d2^2

# Create symbolic pure common lines matrix

Rsymb = [Ra1 Ra2 Ra3;
Rb1 Rb2 Rb3;
Rc1 Rc2 Rc3]

Ssymb = [Sa1 Sa2 Sa3;
Sb1 Sb2 Sb3;
Sc1 Sc2 Sc3]

Asymb = [-I[2,1] -I[2,2] -I[2,3];
I[1,1]  I[1,2]  I[1,3];
-Rsymb[2,1] -Rsymb[2,2] -Rsymb[2,3];
Rsymb[1,1]  Rsymb[1,2]  Rsymb[1,3];
-Ssymb[2,1] -Ssymb[2,2] -Ssymb[2,3];
Ssymb[1,1]  Ssymb[1,2]  Ssymb[1,3]]*[I[1,3] Rsymb[1,3] Ssymb[1,3];
                                     I[2,3] Rsymb[2,3] Ssymb[2,3];
                                     I[3,3] Rsymb[3,3] Ssymb[3,3]]

D = Asymb - A

# Equations for the entries of the rotation matrices
equations = [

    D[1, 2],
    D[2, 2],
    D[1, 3],
    D[2, 3],
    D[3, 1],
    D[4, 1],
    D[3, 3],
    D[4, 3],
    D[5, 1],
    D[6, 1],
    D[5, 2],
    D[6, 2],
    a1^2 + b1^2 + c1^2 + d1^2 - 1,  # Constraint for unit quaternion of R
    a2^2 + b2^2 + c2^2 + d2^2 - 1   # Constraint for unit quaternion of S

]

# Solve the polynomial system using homotopy continuation
result = solve(equations)
SOL = real(solutions(result))

s = SOL[1]
a1sol = s[1]
b1sol = s[2]
c1sol = s[3]
d1sol = s[4]
a2sol = s[5]
b2sol = s[6]
c2sol = s[7]
d2sol = s[8]

Rsol = real([a1sol^2+b1sol^2-c1sol^2-d1sol^2 2*(b1sol*c1sol-a1sol*d1sol)     2*(b1sol*d1sol+a1sol*c1sol);
     2*(b1sol*c1sol+a1sol*d1sol)     a1sol^2-b1sol^2+c1sol^2-d1sol^2 2*(c1sol*d1sol-a1sol*b1sol);
     2*(b1sol*d1sol-a1sol*c1sol)     2*(c1sol*d1sol+a1sol*b1sol)     a1sol^2-b1sol^2-c1sol^2+d1sol^2])

Ssol = real([a2sol^2+b2sol^2-c2sol^2-d2sol^2 2*(b2sol*c2sol-a2sol*d2sol)     2*(b2sol*d2sol+a2sol*c2sol);
     2*(b2sol*c2sol+a2sol*d2sol)     a2sol^2-b2sol^2+c2sol^2-d2sol^2 2*(c2sol*d2sol-a2sol*b2sol);
     2*(b2sol*d2sol-a2sol*c2sol)     2*(c2sol*d2sol+a2sol*b2sol)     a2sol^2-b2sol^2-c2sol^2+d2sol^2])

print(Rsol)
print(R)
print(Ssol)
print(S)