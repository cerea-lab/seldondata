#ifndef FILE_SELDONDATA_FUNCTIONS_HXX

namespace SeldonData
{
  
  template<int N, class TIn, class TGIn,
    class TOut, class TGOut>
  void LinearInterpolation(Data<TIn, N, TGIn>& dataIn,
			   Data<TOut, N, TGOut>& dataOut);

  template<int N, class TIn, class TGIn,
    class TOut, class TGOut>
  void LinearInterpolationLast(Data<TIn, N, TGIn>& dataIn,
			       Data<TOut, N, TGOut>& dataOut);

  template<int N, class TIn, class TGIn,
    class TOut, class TGOut>
  void LinearInterpolationGeneral(Data<TIn, N, TGIn>& dataIn,
				  Data<TOut, N, TGOut>& dataOut);

//    template<class TU, class TV, class TW,
//  	   class T>
//    void LouisKz(Data<TU, 4>& U, Data<TV, 4>& V, Data<TW, 4>& W,
//  	       Data<TTp, 4>& Tp, Data<T, 4>& Kz,
//  	       T z0 = T(1), T L = T(100),
//  	       T Ka = T(0.4), T B = T(5),
//  	       T C = T(5), T D = T(5));
  
}  // namespace SeldonData.

#define FILE_SELDONDATA_FUNCTIONS_HXX
#endif
