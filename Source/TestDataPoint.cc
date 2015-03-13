#include <iostream>
#include "MLDataPoint.hh"

using namespace ML;

int main(int /*argc*/, char** /*argv*/)
{
  DataPoint<2> p1(1.,0.5,.3);
  
  std::cout<<"data point 1: "<<p1<<std::endl;
  
  DataPoint<2,double> p1d(1.,0.5,.3);
  
  std::cout<<"data point 1 (double): "<<p1d<<std::endl;
  
  DataPoint<1,int> p2(1,2);
  
  std::cout<<"data point 2: "<<p2<<std::endl;

  return 0;
}
