% An example of performing linear regression using both gradient
% descent and normal equations.

% load Boston Housing Data, taken from the StatLib library
load housing.data;

% define feature matrix x.  The first column is unity to allow for
% an intercept term in our solution.  The subsequent columns are
% defined from the housing data as follows:
%
%    1. CRIM      per capita crime rate by town
%    2. ZN        proportion of residential land zoned for lots over 
%                 25,000 sq.ft.
%    3. INDUS     proportion of non-retail business acres per town
%    4. CHAS      Charles River dummy variable (= 1 if tract bounds 
%                 river; 0 otherwise)
%    5. NOX       nitric oxides concentration (parts per 10 million)
%    6. RM        average number of rooms per dwelling
%    7. AGE       proportion of owner-occupied units built prior to 1940
%    8. DIS       weighted distances to five Boston employment centres
%    9. RAD       index of accessibility to radial highways
%    10. TAX      full-value property-tax rate per $10,000
%    11. PTRATIO  pupil-teacher ratio by town
%    12. B        1000(Bk - 0.63)^2 where Bk is the proportion of blacks 
%                 by town
%    13. LSTAT    % lower status of the population

columns = [1 2 3 4 5 6 8 9 11];
columns = [3 11];
x = [ones(size(housing,1),1) housing(:,columns)];

% define solution vector y, defined from the housing data as the
% Median value of owner-occupied homes in $1000's.

y = housing(:,14);

% define parameter vector theta_normal, computed using the normal equations.
theta_normal = NormalEquations(x,y);

% define parameter vector theta_gd, computed using batch gradient
% descent.  The third and fourth arguments are the step
% size and convergence tolerance, respectively.
theta_gd = GradientDescent(x,y,1.e4,1.e-6,1.e-8);

printf('\nSolution using normal equations:\n')
disp(theta_normal)
printf('\nSolution using gradient descent:\n')
disp(theta_gd)
printf('\nFractional difference:\n')
disp((theta_normal - theta_gd)./theta_normal)