#include <iostream>

#include <octave/oct.h>
#include <octave/builtin-defun-decls.h>

int main (int /*argc*/,char** /*argv*/)
{
  std::cout << "Hello Octave world!\n";

  int n = 2;
  Matrix a_matrix = Matrix (n, n);

  for (octave_idx_type i = 0; i < n; i++)
    for (octave_idx_type j = 0; j < n; j++)
      a_matrix(i,j) = (i + 1) * 10 + (j + 1) + a_matrix((i+1+n)%n,(j-1+n)%n);

  std::cout << a_matrix;

  octave_value_list in;
  in(0) = a_matrix;

  octave_value_list out = Finv (in, 1);
  Matrix a_inv = out(0).matrix_value();

  std::cout << a_inv;

  std::cout << a_matrix * a_inv;

  return 0;
}
