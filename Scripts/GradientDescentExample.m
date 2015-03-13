% An illustrative example of gradient descent.

% dummy evaluation to denote this file as a script file, not a
% function file.
1;

function PlotCostFunction(A,b,x1,x2,nContours)

[xx,yy] = meshgrid(x1,x2);

ff = xx;

for i=1:rows(xx)
    for j=1:columns(xx)
        x=[xx(i,j); yy(i,j)];
        ff(i,j) = .5 * (A * x - b)' *(A * x - b);
    end
end
    
%meshc(xx,yy,ff);
contour(xx,yy,ff,nContours);
xlabel('x_{1}');
ylabel('x_{2}');
zlabel('f(x)');
endfunction


A = [[3 2];
     [2 6]];

b = [2;-8];

PlotCostFunction(A,b,linspace(-4,6,100),linspace(-6,4,100),linspace(-50,300,20));

hold on;

start = [-2.;3.];

axis equal;

colororder = get (gca, 'colororder');

%stepsize = linspace(1.e-2,4.05e-2,7);
stepsize = [linspace(3.e-2,2.e-2,6) -1];
handles = [];
labels = {};

for i=1:columns(stepsize)
    [tmp x_iterative] = GradientDescent(A,b,1,stepsize(i),1.e-8,start);
    nPoints = columns(x_iterative);
    h = plot(x_iterative(1,:), x_iterative(2,:), '--.');
    set (h, 'color', colororder(i,:));
    if (stepsize(i) > 0)
        labels = {labels{:}, ['\alpha = ',num2str(stepsize(i)),': ',num2str(nPoints),' steps']};
    else
        labels = {labels{:}, ['\alpha = adaptive: ',num2str(nPoints),' steps']};
    end
    handles = [handles, h];
end

h = legend(handles, labels, 'location', 'northeast');
legend boxoff

title("Gradient descent with different learning rates");

x_exact = NormalEquations(A,b);
plot(x_exact(1), x_exact(2), 'k*')

hold off;
