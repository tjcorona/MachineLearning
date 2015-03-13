function [x X] = GradientDescent(A,b,output_interval=1.e4,alpha=1.e-6,tol=1.e-6,x=zeros(columns(A),1))
%GradientDescent(A,b,tolerance) for A * x = b, computes x to
%tolerance <tol> with learning rate <alpha>.
assert(rows(A) == rows(b))

A_x = A * x;
A_x_last = ones(rows(A),1);

X = [x];

convergence_parameter = norm(A_x_last - A_x);
b_norm = norm(b);

counter = 0;

At_A = A' * A;

while ( convergence_parameter > tol)

    counter += 1;

    if (mod(counter,output_interval) == 0)
        printf('%i: %e\r', counter, convergence_parameter);
        fflush(stdout);
        X = [X x];
    end

    r = b - A_x;
    At_r = A' * r;
    
    if (alpha > 0)
        % Stochastic gradient descent: better convergence properties,
        % but slower in Octave
        %for j=1:columns(A)
        %    x(j) += alpha * r' * A(:,j);
        %end

        % Batch gradient descent: worse convergence properties, but
        % faster in octave
        x += alpha * At_r;
    else
        % It turns out that the optimal step size can be computed
        % by minimizing our function along the direction of
        % steepest descent.
        alfa = At_r' * At_r / (At_r' * At_A * At_r);

        x += alfa * At_r;
    end
    
    A_x_last = A_x;
    A_x = A*x;
    convergence_parameter = norm(A_x_last - A_x)/b_norm;

end

printf('                                      \r');

endfunction

