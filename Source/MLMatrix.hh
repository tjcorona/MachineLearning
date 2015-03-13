#ifndef MLMATRIX_DEF
#define MLMATRIX_DEF

#include <assert.h>

#include "MLVector.hh"

namespace ML
{
  template <typename ValueType>
  class Matrix
  {
  public:
    Matrix() : fRow(*this) {}
    virtual ~Matrix() {}

    virtual unsigned int Dimension(unsigned int) const = 0;
    virtual ValueType& operator()(unsigned int,unsigned int) = 0;
    virtual const ValueType& operator()(unsigned int,unsigned int) const = 0;

    class MatrixRow : public Vector<ValueType>
    {
    public:
      friend class Matrix;
      MatrixRow(Matrix& m,unsigned int row=0) :
	Vector<ValueType>(), fParent(m), i(row) {}
      virtual ~MatrixRow() {}

      ValueType& operator[](unsigned int j) { return fParent(i,j); }
      const ValueType& operator()(unsigned int j) const { return fParent(i,j); }

      unsigned int Dimension() const { return fParent.Dimension(1); }

    private:

      Matrix& fParent;
      mutable unsigned int i;
    };

  public:
    class MatrixColumn : public Vector<ValueType>
    {
    public:
      friend class Matrix;
      MatrixColumn(Matrix& m,unsigned int column=0) :
	Vector<ValueType>(), fParent(m), j(column) {}
      virtual ~MatrixColumn() {}

      ValueType& operator[](unsigned int i) { return fParent(i,j); }
      const ValueType& operator()(unsigned int i) const { return fParent(i,j); }

      unsigned int Dimension() const { return fParent.Dimension(0); }

    private:
      Matrix& fParent;
      mutable unsigned int j;
    };

  private:
    MatrixRow fRow;
    
  public:
    const MatrixRow& operator()(unsigned int i) const
    { fRow.i = i; return fRow; }
    MatrixRow& operator[](unsigned int i)
    { fRow.i = i; return fRow; }

    virtual ValueType Determinant() const;

    virtual void Multiply(const Vector<ValueType>& x,
			  Vector<ValueType>& y) const;

    virtual void Multiply(const Matrix<ValueType>& B,
			  Matrix<ValueType>& C) const;

    virtual void MultiplyTranspose(const Vector<ValueType>& x,
				   Vector<ValueType>& y) const;

    virtual void MultiplyTranspose(const Matrix<ValueType>& B,
				   Matrix<ValueType>& C) const;

    virtual void operator*=(const ValueType& alpha);
    virtual void operator+=(const Matrix<ValueType>& aMatrix);
    virtual void operator-=(const Matrix<ValueType>& aMatrix);

    virtual void Inverse(Matrix<ValueType>& inv) const;
  };

  template <typename ValueType>
  ValueType Matrix<ValueType>::Determinant() const
  {
    // TO DO: fill me in!
    return 0.;
  }

  template <typename ValueType>
  void Matrix<ValueType>::Multiply(const Vector<ValueType>& x,
				    Vector<ValueType>& y) const
  {
    // Computes vector y in the equation A*x = y
    for (unsigned int i=0;i<Dimension(0);i++)
    {
      y[i] = 0.;
      for (unsigned int j=0;j<Dimension(1);j++)
	y[i] += this->operator()(i,j)*x(j);
    }
  }

  template <typename ValueType>
  void Matrix<ValueType>::Multiply(const Matrix<ValueType>& B,
				    Matrix<ValueType>& C) const
  {
    // Computes matrix C in the equation A*B = C
    for (unsigned int i=0;i<Dimension(0);i++)
    {
      for (unsigned int j=0;j<Dimension(1);j++)
      {	
	MatrixRow r(const_cast<Matrix<ValueType>&>(*this),i);
	MatrixColumn c(const_cast<Matrix<ValueType>&>(B),j);

	C[i][j] = r.Dot(c);
      }
    }
  }

  template <typename ValueType>
  void Matrix<ValueType>::MultiplyTranspose(const Vector<ValueType>& x,
					     Vector<ValueType>& y) const
  {
    // Computes vector y in the equation A^T*x = y
    for (unsigned int i=0;i<Dimension(1);i++)
    {
      y[i] = 0.;
      for (unsigned int j=0;j<Dimension(0);j++)
	y[i] += this->operator()(j,i)*x(j);
    }
  }

  template <typename ValueType>
  void Matrix<ValueType>::MultiplyTranspose(const Matrix<ValueType>& B,
					    Matrix<ValueType>& C) const
  {
    // Computes matrix C in the equation A^T*B = C
    for (unsigned int i=0;i<Dimension(1);i++)
    {
      for (unsigned int j=0;j<Dimension(0);j++)
      {	
	MatrixColumn r(const_cast<Matrix<ValueType>&>(*this),i);
	MatrixColumn c(const_cast<Matrix<ValueType>&>(B),j);

	C[i][j] = r.Dot(c);
      }
    }
  }

  template <typename ValueType>
  void Matrix<ValueType>::operator*=(const ValueType& alpha)
  {
    for (unsigned int i=0;i<Dimension(0);i++)
      for (unsigned int j=0;j<Dimension(1);j++)
	this->operator()(i,j)*=alpha;
  }

  template <typename ValueType>
  void Matrix<ValueType>::operator+=(const Matrix<ValueType>& aMatrix)
  {
    for (unsigned int i=0;i<Dimension(0);i++)
      for (unsigned int j=0;j<Dimension(1);j++)
	this->operator()(i,j)+=aMatrix(i,j);
  }

  template <typename ValueType>
  void Matrix<ValueType>::operator-=(const Matrix<ValueType>& aMatrix)
  {
    for (unsigned int i=0;i<Dimension(0);i++)
      for (unsigned int j=0;j<Dimension(1);j++)
	this->operator()(i,j)-=aMatrix(i,j);
  }

  template <typename ValueType>
  void Matrix<ValueType>::Inverse(Matrix<ValueType>& inv) const
  {
    assert(Dimension(0) == inv.Dimension(0));
    assert(Dimension(1) == inv.Dimension(1));
    assert(Dimension(0) == Dimension(1));

    /*
    ValueType** a = new ValueType*[Dimension(0)];

    for (int row=0;row<inv.Dimension(0);row++)
    {
      a[row] = new ValueType[Dimension(1)];
      for (int col=0;col<inv.Dimension(1);col++)
      {
	a[row][col] = (*this)(row,col);
	inv(row,col) = (row != col ? 0. : 1.);
      }
    }

    std::cout<<"start: "<<std::endl;

    for (int row=0;row<Dimension(0);row++)
    {
      for (int col=0;col<Dimension(1);col++)
      {
	// std::cout<<"a["<<row<<"]["<<col<<"]: "<<a[row][col]<<std::endl;
	std::cout<<"inv["<<row<<"]["<<col<<"]: "<<inv[row][col]<<std::endl;
      }
    }

    // make matrix a upper triangular
    for (int i=0;i<Dimension(0);i++)
    {
      for (int row=i+1;row<Dimension(0);row++)
      {
	ValueType factor = a[row][i]/a[i][i];
	for (int col=i+1;col<Dimension(1);col++)
	{
	  a[row][col] -= factor*a[i][col];
	  inv[row][col] -= factor*a[i][col];
	}
	a[row][i] = 0.;
      }
    }

    std::cout<<"upper triangular: "<<std::endl;

    for (int row=0;row<Dimension(0);row++)
    {
      for (int col=0;col<Dimension(1);col++)
      {
	// std::cout<<"a["<<row<<"]["<<col<<"]: "<<a[row][col]<<std::endl;
	std::cout<<"inv["<<row<<"]["<<col<<"]: "<<inv[row][col]<<std::endl;
      }
    }

    // backsolve to make matrix a diagonal
    for (int i=Dimension(0)-1;i>=0;i--)
    {
      for (int row=0;row<i;row++)
      {
	ValueType factor = a[row][i]/a[i][i];
	for (int col=0;col<Dimension(1);col++)
	{
	  a[row][col] -= factor*a[i][col];
	  inv[row][col] -= factor*a[i][col];
	}
      }
    }

    std::cout<<"backsolved: "<<std::endl;

    for (int row=0;row<Dimension(0);row++)
    {
      for (int col=0;col<Dimension(1);col++)
      {
	// std::cout<<"a["<<row<<"]["<<col<<"]: "<<a[row][col]<<std::endl;
	std::cout<<"inv["<<row<<"]["<<col<<"]: "<<inv[row][col]<<std::endl;
      }
    }

    // normalize the rows of a
    for (int row=0;row<Dimension(0);row++)
    {
      ValueType factor = a[row][row];
      for (int col=0;col<Dimension(1);col++)
      {
	a[row][col] /= factor;
	inv[row][col] /= factor;
      }
    }

    std::cout<<"normalized: "<<std::endl;

    for (int row=0;row<Dimension(0);row++)
    {
      for (int col=0;col<Dimension(1);col++)
      {
	// std::cout<<"a["<<row<<"]["<<col<<"]: "<<a[row][col]<<std::endl;
	std::cout<<"inv["<<row<<"]["<<col<<"]: "<<inv[row][col]<<std::endl;
      }
    }
    */
  }

  template <typename ValueType>
  inline std::ostream& operator<<(std::ostream& s,const Matrix<ValueType>& m)
  {
    s<<"[ ";
    for (unsigned int i=0;i<m.Dimension(0);i++)
    {
      s<<m(i)<<" ";
    }
    s<<"]";
    return s;
  }
}

#endif
