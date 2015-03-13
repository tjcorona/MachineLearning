#ifndef MLDATAPOINT_HH
#define MLDATAPOINT_HH

#include <cstdarg>
#include <ostream>

#include "MLTypePromotion.hh"

namespace ML
{
  template <unsigned int Dimension = 1,typename ValueType=float>
  class DataPoint
  {
  public:
    DataPoint();
    DataPoint(ValueType,...);
    ~DataPoint() {}

    ValueType& operator[](unsigned int i) { return fData[i]; }
    const ValueType& operator[](unsigned int i) const { return fData[i]; }

    bool operator<(const DataPoint& rhs) const { return fData[0] < rhs.fData[0]; }

  private:

    ValueType fData[Dimension+1];
  };

  template <unsigned int Dimension,typename ValueType>
  DataPoint<Dimension,ValueType>::DataPoint()
  {
    // this function is broken for Apple LLVM version 5.0 (clang-500.2.79)
    // (based on LLVM 3.3svn)
    // memset(fData,0.,Dimension+1);

    for (unsigned int i=0;i<Dimension+1;i++)
      fData[i] = 0.;
  }

  template <unsigned int Dimension,typename ValueType>
  DataPoint<Dimension,ValueType>::DataPoint(ValueType x0,...)
  {
    va_list list;

    va_start(list,x0);

    fData[0] = x0;

    // the compiler should unroll this
    for (unsigned int i=0;i<Dimension;i++)
      fData[i+1] = va_arg(list,typename TypePromotion<ValueType>::value);

    va_end(list);
  }

  template <unsigned int Dimension,typename ValueType>
  inline std::ostream& operator<<(std::ostream& s,const DataPoint<Dimension,ValueType>& p)
  {
    s<<"("<<p[0];
    for (unsigned int i=0;i<Dimension;i++)
      s<<","<<p[i+1];
    s<<")";
    return s;
  }
}

#endif
