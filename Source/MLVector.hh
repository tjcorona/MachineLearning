#ifndef MLVECTOR_DEF
#define MLVECTOR_DEF

#include <cmath>

namespace ML
{
  template <typename ValueType>
  class Vector
  {
  public:
    Vector() {}
    virtual ~Vector() {}

    virtual const ValueType& operator()(unsigned int) const = 0;
    virtual ValueType& operator[](unsigned int) = 0;

    virtual ValueType Dot(const Vector<ValueType>& y) const;

    void Multiply(double alpha,Vector<ValueType>& y) const;

    virtual void operator*=(const ValueType& alpha);
    virtual void operator+=(const Vector<ValueType>& aVector);
    virtual void operator-=(const Vector<ValueType>& aVector);

    virtual unsigned int Dimension() const = 0;

    virtual const ValueType& InfinityNorm() const
    {
      static ValueType infinityNorm;
      infinityNorm = 0.;
      for (unsigned int i=0;i<Dimension();i++)
	if (fabs(this->operator()(i))>infinityNorm)
	  infinityNorm = fabs(this->operator()(i));
      return infinityNorm;
    }
  };

  template <typename ValueType>
  ValueType Vector<ValueType>::Dot(const Vector<ValueType>& y) const
  {
    ValueType result = 0.;
    for (unsigned int i=0;i<Dimension();i++)
      result += this->operator()(i)*y(i);
    return result;
  }

  template <typename ValueType>
  void Vector<ValueType>::Multiply(double alpha,
				    Vector<ValueType>& y) const
  {
    // Computes vector y in the equation alpha*x = y
    for (unsigned int i=0;i<Dimension();i++)
      y[i] = alpha*this->operator()(i);
  }

  template <typename ValueType>
  void Vector<ValueType>::operator*=(const ValueType& alpha)
  {
    for (unsigned int i=0;i<Dimension();i++)
      this->operator[](i)*=alpha;
  }

  template <typename ValueType>
  void Vector<ValueType>::operator+=(const Vector<ValueType>& aVector)
  {
    for (unsigned int i=0;i<Dimension();i++)
      this->operator[](i)+=aVector(i);
  }

  template <typename ValueType>
  void Vector<ValueType>::operator-=(const Vector<ValueType>& aVector)
  {
    for (unsigned int i=0;i<Dimension();i++)
      this->operator[](i)-=aVector(i);
  }

  template <typename ValueType>
  inline std::ostream& operator<<(std::ostream& s,const Vector<ValueType>& v)
  {
    s<<"[ ";
    for (unsigned int i=0;i<v.Dimension();i++)
    {
      s<<v(i)<<" ";
    }
    s<<"]";
    return s;
  }
}

#endif /* KVECTOR_DEF */
