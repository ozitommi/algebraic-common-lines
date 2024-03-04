function [est_cl_oriented,gt_cl_oriented] = orientLinesData(est,gt,rots)

n = size(est,2);

A = est;
est = deg2rad(double(est));
gt = deg2rad(double(gt));
rots = double(rots);

est_cl = zeros(2*n,n);
gt_cl = zeros(2*n,n);

rot_matrices = cell(1,n);
for i = 1:n
    rot_matrices{i} = reshape(rots(i,:,:),3,3)';
end

A2 = create_A2(rot_matrices);
angles_pure = zeros(n);
for i = 1:(n-1)
    for j = (i+1):n

        v1 = A2(s3(i),j);
        v2 = A2(s3(j),i);
        % angles_pure(i,j) = rad2deg(atan2(v(2),v(1)));
        angles_pure(i,j) = mod(rad2deg(atan2(v1(2),v1(1))),360);
        angles_pure(j,i) = mod(rad2deg(atan2(v2(2),v2(1))),360);

        if angles_pure(i,j) > 180
        % if abs(angles_pure(i,j) - 180) > 1
            angles_pure(i,j) = angles_pure(i,j) - 180;
            angles_pure(j,i) = angles_pure(j,i) - 180;
        end
        % if angles_pure(j,i) > 180
        %     % angles_pure(i,j) = angles_pure(i,j) - 180;
        %     angles_pure(j,i) = angles_pure(j,i) + 180;
        % end

    end
end

angles_pure = round(angles_pure);

E = abs(mod(angles_pure,360) - A);
E(1:23,1:23)

for i = 1:n-1
    for j = i+1:n

        v1 = A2(s3(i),j)/norm(A2(s3(i),j))
        v2 = A2(s3(j),i)/norm(A2(s3(j),i))

        % [cos(angles_pure(i,j));sin(angles_pure(i,j))]
        % [cos(angles_pure(j,i));sin(angles_pure(j,i))]

        w1 = [cos(est(i,j));sin(est(i,j))]
        w2 = [cos(est(j,i));sin(est(j,i))]

        est_cl(s3(i),j) = w1;
        est_cl(s3(j),i) = -w2;

        % if all(sign(v1) == sign(w1))
        %     est_cl(s3(i),j) = [cos(est(i,j));sin(est(i,j))];
        % else
        %     est_cl(s3(i),j) = -[cos(est(i,j));sin(est(i,j))];
        % end
        % 
        % if all(sign(v2) == sign(w2))
        %     est_cl(s3(j),i) = [cos(est(j,i));sin(est(j,i))];
        % else
        %     est_cl(s3(j),i) = -[cos(est(j,i));sin(est(j,i))];
        % end

        gt_cl(s3(i),j) = [cos(gt(i,j));sin(gt(i,j))];
        gt_cl(s3(j),i) = [cos(gt(j,i));sin(gt(j,i))];

    end
end


% check consistency
for i = 1:n-1
    for j = i+1:n
        
        % v1 = A2(s3(i),j)
        % v2 = A2(s3(j),i)
        % 
        % w1 = est_cl(s3(i),j)
        % w2 = est_cl(s3(j),i)

        % rot_matrices{i}*[est_cl(s3(i),j);0] % they were all consistent
        % rot_matrices{j}*[est_cl(s3(j),i);0]
    end
end


est_cl_oriented = est_cl;
gt_cl_oriented = gt_cl;

end