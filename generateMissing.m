function missing = generateMissing(n)

% Generates indices for creating the least squares matrices for correcting
% the determinant equations

missing = [];
for i = 1:(n-2)
    for j = (i+1):(n-1)
        for k = (j+1):n

            missing = [missing; "" + j + k, "" + i + k, "" + i + j];

        end
    end
end

end