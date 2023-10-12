function eq = create_quadeq(Asym,n)


norm = [];

for i = 1:(n-1)
    for j = (i+1):n
    norm = [norm; sum(Asym(s3(i),j).^2) - sum(Asym(s3(j),i).^2)];
    end
end

vec1 = [];
vec2 = [];
vec3 = [];


for i = 1:(n-2)
    for j = (i+1):(n-1)
        for k = (j+1):n
           vec1 = [vec1; det([Asym(s3(i),j),Asym(s3(i),k)])];
           vec2 = [vec2; det([Asym(s3(j),i),Asym(s3(j),k)])];
           vec3 = [vec3; det([Asym(s3(k),i),Asym(s3(k),j)])];
            
        end
    end
end


vec_det1 = vec1 + vec2; 
vec_det2 = vec1 - vec3;

eq = [norm; vec_det1; vec_det2];

end
