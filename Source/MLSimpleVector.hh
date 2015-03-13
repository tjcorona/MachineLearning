#ifndef MLSIMPLEVECTOR_DEF
#define MLSIMPLEVECTOR_DEF

#include "MLVector.hh"

#include <vector>

namespace ML
{
  template <typename ValueType>
  class SimpleVector : public Vector<ValueType>
  {
  public:
    SimpleVector() {}
    SimpleVector(unsigned int n,ValueType v=0) { resize(n,v); }
    SimpleVector(const std::vector<ValueType>& v) { fElements = v; }
    virtual ~SimpleVector() {}

    const ValueType& operator()(unsigned int i) const { return fElements.at(i); }
    ValueType& operator[](unsigned int i) { return fElements[i]; }

    unsigned int Dimension() const { return fElements.size(); }

    void resize(unsigned int n,ValueType v=0) { fElements.resize(n,v); }

    void push_back(ValueType val){fElements.push_back(val);};

  private:
    std::vector<ValueType> fElements;
  };
}

#endif /* KSIMPLEVECTOR_DEF */
