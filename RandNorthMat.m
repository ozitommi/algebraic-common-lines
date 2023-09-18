function M = RandNorthMat(n)

U = RandOrthMat(n);
    if abs(det(U) - (-1)) < 10^(-12)
        M = U;
    else
        I = eye(n);
        I(1,1) = -1;
        M = I*U;
    end

end