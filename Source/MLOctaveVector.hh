#ifndef MLOCTAVEVECTOR_DEF
#define MLOCTAVEVECTOR_DEF

#include "MLVector.hh"

#include <vector>

namespace ML
{
  template <typename ValueType>
  class OctaveVector : public Vector<ValueType>
  {
  public:
    OctaveVector() {}
    OctaveVector(unsigned int n,ValueType v=0) { resize(n,v); }
    OctaveVector(const std::vector<ValueType>& v) { fElements = v; }
    virtual ~OctaveVector() {}

    const ValueType& operator()(unsigned int i) const { return fElements.at(i); }
    ValueType& operator[](unsigned int i) { return fElements[i]; }

    unsigned int Dimension() const { return fElements.size(); }

    void resize(unsigned int n,ValueType v=0) { fElements.resize(n,v); }

    void push_back(ValueType val){fElements.push_back(val);};

  private:
    std::vector<ValueType> fElements;
  };
}

#endif /* KOCTAVEVECTOR_DEF */
