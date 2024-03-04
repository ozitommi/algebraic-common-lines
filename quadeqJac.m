clear all;
format long;

results = [];
for i = 3:5

    n = i;
    
    [Asym,S] = create_Asym(n); % create symbols for entries of a and b for A = a*b
    
    eq = create_quadeq(Asym,n); % generate quadric equations symbolically
    
    J = jacobian(eq,S); % generate Jacobian
    
    entries = create_A_factors(n); % get values for entries of a and b
    
    J_num = double(subs(J,S,entries)); % evaluate jacobian

    rows = size(eq,1);
    cols = size(S,1);
    rnk = rank(J_num);
    nul = cols - rnk;

    results = [results; [n,rows,cols,rnk,nul]] % output rank and nullity of jacobian

end
