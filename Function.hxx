#ifndef FILE_SELDONDATA_FUNCTION_HXX

#include <iostream>
using std::cout;
using std::endl;

namespace SeldonData
{


  ///////////////////
  // FUNCTION_BASE //  
  ///////////////////


  //! Based class for functions.
  /*!
    A function f should be a class derived from Function_Base.
    Then, operator() should be overloaded to define the function f.
   */
  template<class T>
  class Function_Base
  {

  public:

    //! Constructor.
    Function_Base() {}
    //! Destructor.
    ~Function_Base() {}
    
    //! Undefined function.
    virtual void operator () (T& i0)
    { 
      throw Undefined("Function_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (T& i0, T& i1)
    { 
      throw Undefined("Function_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (T& i0, T& i1,
			      T& i2)
    { 
      throw Undefined("Function_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (T& i0, T& i1,
			      T& i2, T& i3)
    { 
      throw Undefined("Function_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (T& i0, T& i1,
			      T& i2, T& i3,
			      T& i4)
    { 
      throw Undefined("Function_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (T& i0, T& i1,
			      T& i2, T& i3,
			      T& i4, T& i5)
    { 
      throw Undefined("Function_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (T& i0, T& i1,
			      T& i2, T& i3,
			      T& i4, T& i5,
			      T& i6)
    { 
      throw Undefined("Function_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (T& i0, T& i1,
			      T& i2, T& i3,
			      T& i4, T& i5,
			      T& i6, T& i7)
    { 
      throw Undefined("Function_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (T& i0, T& i1,
			      T& i2, T& i3,
			      T& i4, T& i5,
			      T& i6, T& i7,
			      T& i8)
    { 
      throw Undefined("Function_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (T& i0, T& i1,
			      T& i2, T& i3,
			      T& i4, T& i5,
			      T& i6, T& i7,
			      T& i8, T& i9)
    { 
      throw Undefined("Function_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (T& i0, T& i1,
			      T& i2, T& i3,
			      T& i4, T& i5,
			      T& i6, T& i7,
			      T& i8, T& i9,
			      T& i10)
    { 
      throw Undefined("Function_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (T& i0, T& i1,
			      T& i2, T& i3,
			      T& i4, T& i5,
			      T& i6, T& i7,
			      T& i8, T& i9,
			      T& i10, T& i11)
    { 
      throw Undefined("Function_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (T& i0, T& i1,
			      T& i2, T& i3,
			      T& i4, T& i5,
			      T& i6, T& i7,
			      T& i8, T& i9,
			      T& i10, T& i11,
			      T& i12)
    { 
      throw Undefined("Function_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (T& i0, T& i1,
			      T& i2, T& i3,
			      T& i4, T& i5,
			      T& i6, T& i7,
			      T& i8, T& i9,
			      T& i10, T& i11,
			      T& i12, T& i13)
    { 
      throw Undefined("Function_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (T& i0, T& i1,
			      T& i2, T& i3,
			      T& i4, T& i5,
			      T& i6, T& i7,
			      T& i8, T& i9,
			      T& i10, T& i11,
			      T& i12, T& i13,
			      T& i14)
    { 
      throw Undefined("Function_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (T& i0, T& i1,
			      T& i2, T& i3,
			      T& i4, T& i5,
			      T& i6, T& i7,
			      T& i8, T& i9,
			      T& i10, T& i11,
			      T& i12, T& i13,
			      T& i14, T& i15)
    { 
      throw Undefined("Function_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (T& i0, T& i1,
			      T& i2, T& i3,
			      T& i4, T& i5,
			      T& i6, T& i7,
			      T& i8, T& i9,
			      T& i10, T& i11,
			      T& i12, T& i13,
			      T& i14, T& i15,
			      T& i16)
    { 
      throw Undefined("Function_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (T& i0, T& i1,
			      T& i2, T& i3,
			      T& i4, T& i5,
			      T& i6, T& i7,
			      T& i8, T& i9,
			      T& i10, T& i11,
			      T& i12, T& i13,
			      T& i14, T& i15,
			      T& i16, T& i17)
    { 
      throw Undefined("Function_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (T& i0, T& i1,
			      T& i2, T& i3,
			      T& i4, T& i5,
			      T& i6, T& i7,
			      T& i8, T& i9,
			      T& i10, T& i11,
			      T& i12, T& i13,
			      T& i14, T& i15,
			      T& i16, T& i17,
			      T& i18)
    { 
      throw Undefined("Function_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (T& i0, T& i1,
			      T& i2, T& i3,
			      T& i4, T& i5,
			      T& i6, T& i7,
			      T& i8, T& i9,
			      T& i10, T& i11,
			      T& i12, T& i13,
			      T& i14, T& i15,
			      T& i16, T& i17,
			      T& i18, T& i19)
    { 
      throw Undefined("Function_Base<T>::operator()");
    }

  };



  /////////////////////
  // FUNCCOORDS_BASE //  
  /////////////////////


  //! Based class for coordinates transformations.
  /*!
    A function f for coordinates transformation should be a class derived
    from FuncCoords_Base. Then, operator() should be overloaded
    to define the function f.
   */
  template<class T>
  class FuncCoords_Base
  {

  public:

    //! Constructor.
    FuncCoords_Base() {}
    //! Destructor.
    ~FuncCoords_Base() {}
    
    //! Undefined function.
    virtual void operator () (T& i0)
    { 
      throw Undefined("FuncCoords_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (const T& i0, T& i1)
    { 
      throw Undefined("FuncCoords_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (const T& i0, const T& i1,
			      T& i2, T& i3)
    { 
      throw Undefined("FuncCoords_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (const T& i0, const T& i1,
			      const T& i2, T& i3,
			      T& i4, T& i5)
    { 
      throw Undefined("FuncCoords_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (const T& i0, const T& i1,
			      const T& i2, const T& i3,
			      T& i4, T& i5,
			      T& i6, T& i7)
    { 
      throw Undefined("FuncCoords_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (const T& i0, const T& i1,
			      const T& i2, const T& i3,
			      const T& i4, const T& i5,
			      T& i6, T& i7,
			      T& i8, T& i9)
    { 
      throw Undefined("FuncCoords_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (const T& i0, const T& i1,
			      const T& i2, const T& i3,
			      const T& i4, const T& i5,
			      T& i6, T& i7,
			      T& i8, T& i9,
			      T& i10, T& i11)
    { 
      throw Undefined("FuncCoords_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (const T& i0, const T& i1,
			      const T& i2, const T& i3,
			      const T& i4, const T& i5,
			      const T& i6, T& i7,
			      T& i8, T& i9,
			      T& i10, T& i11,
			      T& i12, T& i13)
    { 
      throw Undefined("FuncCoords_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (const T& i0, const T& i1,
			      const T& i2, const T& i3,
			      const T& i4, const T& i5,
			      const T& i6, const T& i7,
			      T& i8, T& i9,
			      T& i10, T& i11,
			      T& i12, T& i13,
			      T& i14, T& i15)
    { 
      throw Undefined("FuncCoords_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (const T& i0, const T& i1,
			      const T& i2, const T& i3,
			      const T& i4, const T& i5,
			      const T& i6, const T& i7,
			      const T& i8, T& i9,
			      T& i10, T& i11,
			      T& i12, T& i13,
			      T& i14, T& i15,
			      T& i16, T& i17)
    { 
      throw Undefined("FuncCoords_Base<T>::operator()");
    }

    //! Undefined function.
    virtual void operator () (const T& i0, const T& i1,
			      const T& i2, const T& i3,
			      const T& i4, const T& i5,
			      const T& i6, const T& i7,
			      const T& i8, const T& i9,
			      T& i10, T& i11,
			      T& i12, T& i13,
			      T& i14, T& i15,
			      T& i16, T& i17,
			      T& i18, T& i19)
    { 
      throw Undefined("FuncCoords_Base<T>::operator()");
    }

  };


}  // namespace SeldonData.

#define FILE_SELDONDATA_FUNCTION_HXX
#endif
