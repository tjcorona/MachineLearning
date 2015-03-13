#ifndef MLSIMPLEMATRIX_DEF
#define MLSIMPLEMATRIX_DEF

#include "MLMatrix.hh"

#include <vector>

namespace ML
{
  template <typename ValueType>
  class SimpleMatrix : public Matrix<ValueType>
  {
  public:
    SimpleMatrix(unsigned int nrows,unsigned int ncols);
    virtual ~SimpleMatrix() {}

    unsigned int Dimension(unsigned int i) const;
    const ValueType& operator()(unsigned int,unsigned int) const;
    ValueType& operator()(unsigned int,unsigned int);

  protected:
    SimpleMatrix() {}

    unsigned int fNRows;
    unsigned int fNColumns;
    std::vector<ValueType> fElements;
  };

  template <typename ValueType>
  SimpleMatrix<ValueType>::SimpleMatrix(unsigned int nrows,unsigned int ncols)
    : fNRows(nrows), fNColumns(ncols)
  {
    fElements.resize(nrows*ncols);
  }

  template <typename ValueType>
  unsigned int SimpleMatrix<ValueType>::Dimension(unsigned int i) const
  {
    return (i == 0 ? fNRows : fNColumns);
  }

  template <typename ValueType>
  const ValueType& SimpleMatrix<ValueType>::operator()(unsigned int i, unsigned int j) const
  {
    return fElements.at(i*fNColumns + j);
  }

  template <typename ValueType>
  ValueType& SimpleMatrix<ValueType>::operator()(unsigned int i, unsigned int j)
  {
    return fElements.at(i*fNColumns + j);
  }

}

#endif /* KSIMPLEMATRIX_DEF */
