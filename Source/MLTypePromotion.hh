#ifndef MLTYPEPROMOTION_HH
#define MLTYPEPROMOTION_HH

namespace ML
{
  template<typename T>
  struct TypePromotion
  {
    typedef T value;
  };

  template<>
  struct TypePromotion<float>
  {
    typedef double value;
  };

  template<>
  struct TypePromotion<bool>
  {
    typedef int value;
  };

  template<>
  struct TypePromotion<char>
  {
    typedef int value;
  };

  template<>
  struct TypePromotion<short>
  {
    typedef int value;
  };
}

#endif
