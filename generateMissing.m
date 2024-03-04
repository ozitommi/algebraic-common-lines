function [missing_mu, missing_tau1, missing_tau2] = generateMissing(n)

missing_mu = [];
missing_tau1 = [];
missing_tau2 = [];

for i = 1:(n-2)
    for j = (i+1):(n-1)
        for k = (j+1):n

            missing_mu = [missing_mu; i, j, k];
            missing_tau1 = [missing_tau1; j, i];
            missing_tau2 = [missing_tau2; k, j];

        end
    end
end

end