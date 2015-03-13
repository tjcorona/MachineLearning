function thetas = IncrementalGradientDescent(x,y,increment=1,alpha=1.e-6,tol=1.e-6)
%GradientDescent(x,y,tolerance) for theta^T * x = y, computes theta to
%tolerance <tol> with learning rate <alpha>.
assert(rows(x) == rows(y))

theta = zeros(columns(x),1);
thetas = [];
h_theta = zeros(rows(x),1);
h_theta_last = ones(rows(x),1);

norm_h_diff = norm(h_theta_last - h_theta);
norm_y = norm(y);

counter = 0;

while ( norm_h_diff / norm_y > tol)

    if (mod(counter,increment) == 0)
        printf('%i: %e\r',counter, norm_h_diff / norm_y);
        fflush(stdout);
        thetas = [thetas theta];
    end

    for j=1:columns(x)
        theta(j) += alpha * (y - h_theta).' * x(:,j);
    end


    h_theta_last = h_theta;
    h_theta = x*theta;
    norm_h_diff = norm(h_theta_last - h_theta);
    counter += 1;
    
end

printf('                                      \r');

endfunction

