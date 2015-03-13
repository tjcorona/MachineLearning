#include <iostream>
#include "MLSimpleMatrix.hh"
#include "MLSimpleVector.hh"

using namespace ML;

int main(int /*argc*/, char** /*argv*/)
{
  if (false)
  {
    SimpleMatrix<float> A(3,4);
    SimpleVector<float> x(3);
    for (unsigned i=0;i<3;i++)
    {
      x[i] = i;
      for (unsigned j=0;j<4;j++)
      {
	A[i][j] = i+j;
      }
    }
  
    SimpleVector<float> b(4);

    A.MultiplyTranspose(x,b);

    SimpleMatrix<float> A2(4,4);

    A.MultiplyTranspose(A,A2);

    SimpleMatrix<float> I(4,4);
    for (unsigned i=0;i<4;i++)
      for (unsigned j=0;j<4;j++)
	I[i][j] = (i == j ? 1. : 0.);

    A2 += I;

    SimpleMatrix<float> Ainv(4,4);

    A2.Inverse(Ainv);

    A2.Multiply(Ainv,I);

    // std::cout<<"matrix:   "<<A<<std::endl;
    // std::cout<<"vector:   "<<x<<std::endl;
    // std::cout<<"product:  "<<b<<std::endl;
    // std::cout<<"matrix^2: "<<A2<<std::endl;
    // std::cout<<"(matrix^2)^(-1): "<<Ainv<<std::endl;
    // std::cout<<"Unity: "<<I<<std::endl;
  }
  
  {
    SimpleMatrix<float> A(2,2);
    A(0,0) = 1.;
    A(0,1) = 2.;
    A(1,0) = 3.;
    A(1,1) = 4.;

    SimpleMatrix<float> Ainv(2,2);
    
    A.Inverse(Ainv);

    SimpleMatrix<float> I(2,2);
    A.Multiply(Ainv,I);
    
    std::cout<<"matrix: "<<A<<std::endl;
    std::cout<<"inverse: "<<Ainv<<std::endl;
    std::cout<<"unity: "<<I<<std::endl;
  }
  
  return 0;
}
