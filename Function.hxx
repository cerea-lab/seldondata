#ifndef FILE_FUNCTION_HXX

#include <iostream>
using std::cout;
using std::endl;

namespace SeldonData
{
  
  template<class T>
  class Function_Base
  {
  public:
    Function_Base() {}
    ~Function_Base() {}
    
    void operator () (T& i0)
    { 
    }

    virtual void operator () (T& i0, T& i1)
    { 
    }

    virtual void operator () (T& i0, T& i1,
			      T& i2)
    { 
    }

    virtual void operator () (T& i0, T& i1,
			      T& i2, T& i3)
    { 
    }

    virtual void operator () (T& i0, T& i1,
			      T& i2, T& i3,
			      T& i4)
    { 
    }

    virtual void operator () (T& i0, T& i1,
			      T& i2, T& i3,
			      T& i4, T& i5)
    { 
    }

    virtual void operator () (T& i0, T& i1,
			      T& i2, T& i3,
			      T& i4, T& i5,
			      T& i6)
    { 
    }

    virtual void operator () (T& i0, T& i1,
			      T& i2, T& i3,
			      T& i4, T& i5,
			      T& i6, T& i7)
    { 
    }

    virtual void operator () (T& i0, T& i1,
			      T& i2, T& i3,
			      T& i4, T& i5,
			      T& i6, T& i7,
			      T& i8)
    { 
    }

    virtual void operator () (T& i0, T& i1,
			      T& i2, T& i3,
			      T& i4, T& i5,
			      T& i6, T& i7,
			      T& i8, T& i9)
    { 
    }

  };

}  // namespace SeldonData.

#define FILE_FUNCTION_HXX
#endif
