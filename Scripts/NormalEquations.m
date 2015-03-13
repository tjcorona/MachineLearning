function x = NormalEquations(A,b)
%NormalEquations(A,b)   for A x = b, computes x using the
%pseudoinverse of A (x = (A^T * A)^-1 * A^T * b)
assert(rows(A) == rows(b))
x = inv(A.' * A) * A.' * b;
endfunction