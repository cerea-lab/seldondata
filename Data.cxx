#ifndef FILE_SELDONDATA_DATA_CXX

#include <cstdlib>
#include "Data.hxx"

namespace SeldonData
{

  //! Constructor for one-dimensional data.
  /*!
    
  */
  template<class T, int N>
  Data<T, N>::Data(Grid<T>& G0)  throw():
    data_(G0.GetLength()), grids_(N)
  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=1)
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N>::Data(Grid<T>, ...)."
	     << endl << "   Requires " + to_string(N)
	  + " grids, but got 1 grids." << endl;
	abort();
      }
#endif

    grids_(0) = G0.Duplicate();
    SetVariables();


#ifdef DEBUG_SELDONDATA_DIMENSION
    int i, j;
    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	if ( (grids_(i)->GetLength(j)!=0)
	     && (grids_(i)->GetLength(j)!=grids_(j)->GetLength()) )
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N>::Data(Grid<T>, ...)."
	     << endl << "   Length of grid #" << i << " along dimension #"
	     << j << " is " << grids_(i)->GetLength(j) << " but should be "
	     << grids_(j)->GetLength() << "." << endl;
	abort();
      }
#endif

  }

  template<class T, int N>
  Data<T, N>::Data(Grid<T>& G0, Grid<T>& G1)  throw():
    data_(G0.GetLength(), G1.GetLength()), grids_(N)
  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=2)
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N>::Data(Grid<T>, ...)."
	     << endl << "   Requires " + to_string(N)
	  + " grids, but got 2 grids." << endl;
	abort();
      }
#endif

    grids_(0) = G0.Duplicate(); grids_(1) = G1.Duplicate();
    SetVariables();

#ifdef DEBUG_SELDONDATA_DIMENSION
    int i, j;
    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	if ( (grids_(i)->GetLength(j)!=0)
	     && (grids_(i)->GetLength(j)!=grids_(j)->GetLength()) )
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N>::Data(Grid<T>, ...)."
	     << endl << "   Length of grid #" << i << " along dimension #"
	     << j << " is " << grids_(i)->GetLength(j) << " but should be "
	     << grids_(j)->GetLength() << "." << endl;
	abort();
      }
#endif

  }

  template<class T, int N>
  Data<T, N>::Data(Grid<T>& G0, Grid<T>& G1, Grid<T>& G2)  throw():
    data_(G0.GetLength(), G1.GetLength(),
	  G2.GetLength()), grids_(N)
  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=3)
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N>::Data(Grid<T>, ...)."
	     << endl << "   Requires " + to_string(N)
	  + " grids, but got 3 grids." << endl;
	abort();
      }
#endif

    grids_(0) = G0.Duplicate(); grids_(1) = G1.Duplicate();
    grids_(2) = G2.Duplicate();
    SetVariables();


#ifdef DEBUG_SELDONDATA_DIMENSION
    int i, j;
    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	if ( (grids_(i)->GetLength(j)!=0)
	     && (grids_(i)->GetLength(j)!=grids_(j)->GetLength()) )
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N>::Data(Grid<T>, ...)."
	     << endl << "   Length of grid #" << i << " along dimension #"
	     << j << " is " << grids_(i)->GetLength(j) << " but should be "
	     << grids_(j)->GetLength() << "." << endl;
	abort();
      }
#endif

  }

  template<class T, int N>
  Data<T, N>::Data(Grid<T>& G0, Grid<T>& G1, Grid<T>& G2,
		   Grid<T>& G3)  throw():
    data_(G0.GetLength(), G1.GetLength(),
	  G2.GetLength(), G3.GetLength()), grids_(N)
  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=4)
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N>::Data(Grid<T>, ...)."
	     << endl << "   Requires " + to_string(N)
	  + " grids, but got 4 grids." << endl;
	abort();
      }
#endif

    grids_(0) = G0.Duplicate(); grids_(1) = G1.Duplicate();
    grids_(2) = G2.Duplicate(); grids_(3) = G3.Duplicate();
    SetVariables();


#ifdef DEBUG_SELDONDATA_DIMENSION
    int i, j;
    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	if ( (grids_(i)->GetLength(j)!=0)
	     && (grids_(i)->GetLength(j)!=grids_(j)->GetLength()) )
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N>::Data(Grid<T>, ...)."
	     << endl << "   Length of grid #" << i << " along dimension #"
	     << j << " is " << grids_(i)->GetLength(j) << " but should be "
	     << grids_(j)->GetLength() << "." << endl;
	abort();
      }
#endif

  }

  template<class T, int N>
  Data<T, N>::Data(Grid<T>& G0, Grid<T>& G1, Grid<T>& G2,
		   Grid<T>& G3, Grid<T>& G4)  throw():
    data_(G0.GetLength(), G1.GetLength(),
	  G2.GetLength(), G3.GetLength(),
	  G4.GetLength()), grids_(N)
  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=5)
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N>::Data(Grid<T>, ...)."
	     << endl << "   Requires " + to_string(N)
	  + " grids, but got 5 grids." << endl;
	abort();
      }
#endif

    grids_(0) = G0.Duplicate(); grids_(1) = G1.Duplicate();
    grids_(2) = G2.Duplicate(); grids_(3) = G3.Duplicate();
    grids_(4) = G4.Duplicate();
    SetVariables();


#ifdef DEBUG_SELDONDATA_DIMENSION
    int i, j;
    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	if ( (grids_(i)->GetLength(j)!=0)
	     && (grids_(i)->GetLength(j)!=grids_(j)->GetLength()) )
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N>::Data(Grid<T>, ...)."
	     << endl << "   Length of grid #" << i << " along dimension #"
	     << j << " is " << grids_(i)->GetLength(j) << " but should be "
	     << grids_(j)->GetLength() << "." << endl;
	abort();
      }
#endif

  }

  template<class T, int N>
  Data<T, N>::Data(Grid<T>& G0, Grid<T>& G1, Grid<T>& G2,
		   Grid<T>& G3, Grid<T>& G4, Grid<T>& G5)  throw():
    data_(G0.GetLength(), G1.GetLength(),
	  G2.GetLength(), G3.GetLength(), G4.GetLength(),
	  G5.GetLength()), grids_(N)
  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=6)
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N>::Data(Grid<T>, ...)."
	     << endl << "   Requires " + to_string(N)
	  + " grids, but got 6 grids." << endl;
	abort();
      }
#endif

    grids_(0) = G0.Duplicate(); grids_(1) = G1.Duplicate();
    grids_(2) = G2.Duplicate(); grids_(3) = G3.Duplicate();
    grids_(4) = G4.Duplicate(); grids_(5) = G5.Duplicate();
    SetVariables();


#ifdef DEBUG_SELDONDATA_DIMENSION
    int i, j;
    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	if ( (grids_(i)->GetLength(j)!=0)
	     && (grids_(i)->GetLength(j)!=grids_(j)->GetLength()) )
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N>::Data(Grid<T>, ...)."
	     << endl << "   Length of grid #" << i << " along dimension #"
	     << j << " is " << grids_(i)->GetLength(j) << " but should be "
	     << grids_(j)->GetLength() << "." << endl;
	abort();
      }
#endif

  }

  template<class T, int N>
  Data<T, N>::Data(Grid<T>& G0, Grid<T>& G1, Grid<T>& G2,
		   Grid<T>& G3, Grid<T>& G4, Grid<T>& G5,
		   Grid<T>& G6)  throw():
    data_(G0.GetLength(), G1.GetLength(),
	  G2.GetLength(), G3.GetLength(), G4.GetLength(),
	  G5.GetLength(), G6.GetLength()), grids_(N)
  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=7)
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N>::Data(Grid<T>, ...)."
	     << endl << "   Requires " + to_string(N)
	  + " grids, but got 7 grids." << endl;
	abort();
      }
#endif

    grids_(0) = G0.Duplicate(); grids_(1) = G1.Duplicate();
    grids_(2) = G2.Duplicate(); grids_(3) = G3.Duplicate();
    grids_(4) = G4.Duplicate(); grids_(5) = G5.Duplicate();
    grids_(6) = G6.Duplicate();
    SetVariables();


#ifdef DEBUG_SELDONDATA_DIMENSION
    int i, j;
    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	if ( (grids_(i)->GetLength(j)!=0)
	     && (grids_(i)->GetLength(j)!=grids_(j)->GetLength()) )
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N>::Data(Grid<T>, ...)."
	     << endl << "   Length of grid #" << i << " along dimension #"
	     << j << " is " << grids_(i)->GetLength(j) << " but should be "
	     << grids_(j)->GetLength() << "." << endl;
	abort();
      }
#endif

  }

  template<class T, int N>
  Data<T, N>::Data(Grid<T>& G0, Grid<T>& G1, Grid<T>& G2,
		   Grid<T>& G3, Grid<T>& G4, Grid<T>& G5,
		   Grid<T>& G6, Grid<T>& G7)  throw():
    data_(G0.GetLength(), G1.GetLength(),
	  G2.GetLength(), G3.GetLength(), G4.GetLength(),
	  G5.GetLength(), G6.GetLength(), G7.GetLength()),
    grids_(N)
  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=8)
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N>::Data(Grid<T>, ...)."
	     << endl << "   Requires " + to_string(N)
	  + " grids, but got 8 grids." << endl;
	abort();
      }
#endif

    grids_(0) = G0.Duplicate(); grids_(1) = G1.Duplicate();
    grids_(2) = G2.Duplicate(); grids_(3) = G3.Duplicate();
    grids_(4) = G4.Duplicate(); grids_(5) = G5.Duplicate();
    grids_(6) = G6.Duplicate(); grids_(7) = G7.Duplicate();
    SetVariables();


#ifdef DEBUG_SELDONDATA_DIMENSION
    int i, j;
    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	if ( (grids_(i)->GetLength(j)!=0)
	     && (grids_(i)->GetLength(j)!=grids_(j)->GetLength()) )
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N>::Data(Grid<T>, ...)."
	     << endl << "   Length of grid #" << i << " along dimension #"
	     << j << " is " << grids_(i)->GetLength(j) << " but should be "
	     << grids_(j)->GetLength() << "." << endl;
	abort();
      }
#endif

  }

  template<class T, int N>
  Data<T, N>::Data(Grid<T>& G0, Grid<T>& G1, Grid<T>& G2,
		   Grid<T>& G3, Grid<T>& G4, Grid<T>& G5,
		   Grid<T>& G6, Grid<T>& G7, Grid<T>& G8)  throw():
    data_(G0.GetLength(), G1.GetLength(),
	  G2.GetLength(), G3.GetLength(), G4.GetLength(),
	  G5.GetLength(), G6.GetLength(), G7.GetLength(),
	  G8.GetLength()), grids_(N)
  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=9)
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N>::Data(Grid<T>, ...)."
	     << endl << "   Requires " + to_string(N)
	  + " grids, but got 9 grids." << endl;
	abort();
      }
#endif

    grids_(0) = G0.Duplicate(); grids_(1) = G1.Duplicate();
    grids_(2) = G2.Duplicate(); grids_(3) = G3.Duplicate();
    grids_(4) = G4.Duplicate(); grids_(5) = G5.Duplicate();
    grids_(6) = G6.Duplicate(); grids_(7) = G7.Duplicate();
    grids_(8) = G8.Duplicate();
    SetVariables();


#ifdef DEBUG_SELDONDATA_DIMENSION
    int i, j;
    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	if ( (grids_(i)->GetLength(j)!=0)
	     && (grids_(i)->GetLength(j)!=grids_(j)->GetLength()) )
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N>::Data(Grid<T>, ...)."
	     << endl << "   Length of grid #" << i << " along dimension #"
	     << j << " is " << grids_(i)->GetLength(j) << " but should be "
	     << grids_(j)->GetLength() << "." << endl;
	abort();
      }
#endif

  }

  template<class T, int N>
  Data<T, N>::Data(Grid<T>& G0, Grid<T>& G1, Grid<T>& G2,
		   Grid<T>& G3, Grid<T>& G4, Grid<T>& G5,
		   Grid<T>& G6, Grid<T>& G7, Grid<T>& G8,
		   Grid<T>& G9)  throw():
    data_(G0.GetLength(), G1.GetLength(),
	  G2.GetLength(), G3.GetLength(), G4.GetLength(),
	  G5.GetLength(), G6.GetLength(), G7.GetLength(),
	  G8.GetLength(), G9.GetLength()), grids_(N)
  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=10)
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N>::Data(Grid<T>, ...)."
	     << endl << "   Requires " + to_string(N)
	  + " grids, but got 10 grids." << endl;
	abort();
      }
#endif

    grids_(0) = G0.Duplicate(); grids_(1) = G1.Duplicate();
    grids_(2) = G2.Duplicate(); grids_(3) = G3.Duplicate();
    grids_(4) = G4.Duplicate(); grids_(5) = G5.Duplicate();
    grids_(6) = G6.Duplicate(); grids_(7) = G7.Duplicate();
    grids_(8) = G8.Duplicate(); grids_(9) = G9.Duplicate();
    SetVariables();


#ifdef DEBUG_SELDONDATA_DIMENSION
    int i, j;
    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	if ( (grids_(i)->GetLength(j)!=0)
	     && (grids_(i)->GetLength(j)!=grids_(j)->GetLength()) )
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N>::Data(Grid<T>, ...)."
	     << endl << "   Length of grid #" << i << " along dimension #"
	     << j << " is " << grids_(i)->GetLength(j) << " but should be "
	     << grids_(j)->GetLength() << "." << endl;
	abort();
      }
#endif

  }

  template<class T, int N>
  Data<T, N>::~Data()  throw()
  {
    for (int i=0; i<N; i++)
      delete grids_(i);
  }

  template<class T, int N>
  T& Data<T, N>::operator() (int i0)  
  {
    return data_(i0);
  }

  template<class T, int N>
  T& Data<T, N>::operator() (int i0, int i1)  
  {
    return data_(i0, i1);
  }

  template<class T, int N>
  T& Data<T, N>::operator() (int i0, int i1, int i2)
  {
    return data_(i0, i1, i2);
  }

  template<class T, int N>
  T& Data<T, N>::operator() (int i0, int i1, int i2,
			     int i3)

  {
    return data_(i0, i1, i2, i3);
  }

  template<class T, int N>
  T& Data<T, N>::operator() (int i0, int i1, int i2,
			     int i3, int i4)

  {
    return data_(i0, i1, i2, i3, i4);
  }

  template<class T, int N>
  T& Data<T, N>::operator() (int i0, int i1, int i2,
			     int i3, int i4, int i5)

  {
    return data_(i0, i1, i2, i3, i4, i5);
  }

  template<class T, int N>
  T& Data<T, N>::operator() (int i0, int i1, int i2,
			     int i3, int i4, int i5,
			     int i6)

  {
    return data_(i0, i1, i2, i3, i4, i5, i6);
  }

  template<class T, int N>
  T& Data<T, N>::operator() (int i0, int i1, int i2,
			     int i3, int i4, int i5,
			     int i6, int i7)

  {
    return data_(i0, i1, i2, i3, i4, i5, i6, i7);
  }

  template<class T, int N>
  T& Data<T, N>::operator() (int i0, int i1, int i2,
			     int i3, int i4, int i5,
			     int i6, int i7, int i8)

  {
    return data_(i0, i1, i2, i3, i4, i5, i6, i7, i8);
  }

  template<class T, int N>
  T& Data<T, N>::operator() (int i0, int i1, int i2,
			     int i3, int i4, int i5,
			     int i6, int i7, int i8,
			     int i9)

  {
    return data_(i0, i1, i2, i3, i4, i5, i6, i7, i8, i9);
  }

  template<class T, int N>
  T& Data<T, N>::Value(int i0, int i1, int i2,
		       int i3, int i4, int i5,
		       int i6, int i7, int i8,
		       int i9)    
  {
    if (N==1)
      return data_(i0);
    if (N==2)
      return data_(i0, i1);
    if (N==3)
      return data_(i0, i1, i2);
    if (N==4)
      return data_(i0, i1, i2, i3);
    if (N==5)
      return data_(i0, i1, i2, i3, i4);
    if (N==6)
      return data_(i0, i1, i2, i3, i4, i5);
    if (N==7)
      return data_(i0, i1, i2, i3, i4, i5, i6);
    if (N==8)
      return data_(i0, i1, i2, i3, i4, i5, i6, i7);
    if (N==9)
      return data_(i0, i1, i2, i3, i4, i5, i6, i7, i8);
    if (N==10)
      return data_(i0, i1, i2, i3, i4, i5, i6, i7, i8, i9);
  }

  template<class T, int N>
  T Data<T, N>::Value(int i0, int i1, int i2,
		      int i3, int i4, int i5,
		      int i6, int i7, int i8,
		      int i9) const
  {
    if (N==1)
      return data_(i0);
    if (N==2)
      return data_(i0, i1);
    if (N==3)
      return data_(i0, i1, i2);
    if (N==4)
      return data_(i0, i1, i2, i3);
    if (N==5)
      return data_(i0, i1, i2, i3, i4);
    if (N==6)
      return data_(i0, i1, i2, i3, i4, i5);
    if (N==7)
      return data_(i0, i1, i2, i3, i4, i5, i6);
    if (N==8)
      return data_(i0, i1, i2, i3, i4, i5, i6, i7);
    if (N==9)
      return data_(i0, i1, i2, i3, i4, i5, i6, i7, i8);
    if (N==10)
      return data_(i0, i1, i2, i3, i4, i5, i6, i7, i8, i9);
  }

  template<class T, int N>
  int Data<T, N>::GetNbElements()
  {
    return data_.numElements();
  }

  template<class T, int N>
  int Data<T, N>::GetNbDim()
  {
    return N;
  }

  template<class T, int N>
  int Data<T, N>::GetLength(int i)
  {
    if (i<N)
      return data_.extent(i);
    else
      return 0;
  }

  template<class T, int N>
  Grid<T>& Data<T, N>::GetGrid(int i)
  {
    return *grids_(i);
  }

  template<class T, int N>
  Grid<T>& Data<T, N>::operator [] (int i)
  {
    return *grids_(i);
  }

  template<class T, int N>
  Array<Grid<T>*, 1>& Data<T, N>::GetGrids()
  {
    return grids_;
  }

  template<class T, int N>
  Array<T, N>& Data<T, N>::GetArray()
  {
    return data_;
  }

  template<class T, int N>
  T* Data<T, N>::GetData()
  {
    return data_.data();
  }

  // SubArrays.
  
  template<class T, int N>
  template<class R0>
  void Data<T, N>::SubData(Data<T, 1>& data, R0 r0)
  {
    Array<T, 1>& array = data.GetArray();
    this->data_ = array(r0);
  }

  template<class T, int N>
  template<class R0, class R1>
  void Data<T, N>::SubData(Data<T, 2>& data, R0 r0, R1 r1)
  {
    Array<T, 2>& array = data.GetArray();
    this->data_ = array(r0, r1);
  }

  template<class T, int N>
  template<class R0, class R1, class R2>
  void Data<T, N>::SubData(Data<T, 3>& data, R0 r0, R1 r1, R2 r2)
  {
    Array<T, 3>& array = data.GetArray();
    this->data_ = array(r0, r1, r2);
  }

  template<class T, int N>
  template<class R0, class R1, class R2,
    class R3>
  void Data<T, N>::SubData(Data<T, 4>& data, R0 r0, R1 r1, R2 r2,
			   R3 r3)
  {
    Array<T, 4>& array = data.GetArray();
    this->data_ = array(r0, r1, r2,
			r3);
  }

  template<class T, int N>
  template<class R0, class R1, class R2,
    class R3, class R4>
  void Data<T, N>::SubData(Data<T, 5>& data, R0 r0, R1 r1, R2 r2,
			   R3 r3, R4 r4)
  {
    Array<T, 5>& array = data.GetArray();
    this->data_ = array(r0, r1, r2,
			r3, r4);
  }

  template<class T, int N>
  template<class R0, class R1, class R2,
    class R3, class R4, class R5>
  void Data<T, N>::SubData(Data<T, 6>& data, R0 r0, R1 r1, R2 r2,
			   R3 r3, R4 r4, R5 r5)
  {
    Array<T, 6>& array = data.GetArray();
    this->data_ = array(r0, r1, r2,
			r3, r4, r5);
  }

  template<class T, int N>
  template<class R0, class R1, class R2,
    class R3, class R4, class R5,
    class R6>
  void Data<T, N>::SubData(Data<T, 7>& data, R0 r0, R1 r1, R2 r2,
			   R3 r3, R4 r4, R5 r5, R6 r6)
  {
    Array<T, 7>& array = data.GetArray();
    this->data_ = array(r0, r1, r2,
			r3, r4, r5, r6);
  }

  template<class T, int N>
  template<class R0, class R1, class R2,
    class R3, class R4, class R5,
    class R6, class R7>
  void Data<T, N>::SubData(Data<T, 8>& data, R0 r0, R1 r1, R2 r2,
			   R3 r3, R4 r4, R5 r5, R6 r6,
			   R7 r7)
  {
    Array<T, 8>& array = data.GetArray();
    this->data_ = array(r0, r1, r2,
			r3, r4, r5, r6,
			r7);
  }

  template<class T, int N>
  template<class R0, class R1, class R2,
    class R3, class R4, class R5,
    class R6, class R7, class R8>
  void Data<T, N>::SubData(Data<T, 9>& data, R0 r0, R1 r1, R2 r2,
			   R3 r3, R4 r4, R5 r5, R6 r6,
			   R7 r7, R8 r8)
  {
    Array<T, 9>& array = data.GetArray();
    this->data_ = array(r0, r1, r2,
			r3, r4, r5, r6,
			r7, r8);
  }

  template<class T, int N>
  template<class R0, class R1, class R2,
    class R3, class R4, class R5,
    class R6, class R7, class R8, class R9>
  void Data<T, N>::SubData(Data<T, 10>& data, R0 r0, R1 r1, R2 r2,
			   R3 r3, R4 r4, R5 r5, R6 r6,
			   R7 r7, R8 r8, R9 r9)
  {
    Array<T, 10>& array = data.GetArray();
    this->data_ = array(r0, r1, r2,
			r3, r4, r5, r6,
			r7, r8, r9);
  }

  // Calculus.
  
  template<class T, int N>
  void Data<T, N>::Apply(void function(T&))
  {
    T* data = data_.data();
    int NbElements = data_.numElements();
    
    for (int i=0; i<NbElements; i++)
      function(data[i]);
  }

  template<class T, int N>
  template<class F>
  void Data<T, N>::Apply(F& function)
  {
    T* data = data_.data();
    int NbElements = data_.numElements();
    
    for (int i=0; i<NbElements; i++)
      function.Apply(data[i]);
  }

  template<class T, int N>
  void Data<T,N>::SetZero()
  {
    T* data = data_.data();
    int NbElements = data_.numElements();
    
    for (int i=0; i<NbElements; i++)
      data[i] = T(0);
  }

  template<class T, int N>
  bool Data<T,N>::IsZero()
  {
    bool res = true;

    T* data = data_.data();
    int NbElements = data_.numElements();
    
    for (int i=0; i<NbElements; i++)
      res = res && (data[i] == T(0));

    return res;
  }

  template<class T, int N>
  void Data<T, N>::ChangeCoords(Function_Base<T>& f)
  {
    
    int i;
    int i0, i1, i2, i3, i4, i5, i6, i7, i8, i9;

    Array<Grid<T>*, 1> grids(N);
    for (i=0; i<N; i++)
      grids(i) = grids_(i)->Duplicate();

    if (N==1)
      for (i0=0; i0<grids(0)->GetLength(); i0++)
	f(grids(0)->Value(i0),
	  grids_(0)->Value(i0));
    else if (N==2)
      for (i0=0; i0<grids(0)->GetLength(); i0++)
	for (i1=0; i1<grids(1)->GetLength(); i1++)
	  f(grids(0)->Value(i0, i1),
	    grids(1)->Value(i0, i1),
	    grids_(0)->Value(i0, i1),
	    grids_(1)->Value(i0, i1));
    else if (N==3)
      for (i0=0; i0<grids(0)->GetLength(); i0++)
	for (i1=0; i1<grids(1)->GetLength(); i1++)
	  for (i2=0; i2<grids(2)->GetLength(); i2++)
	    f(grids(0)->Value(i0, i1, i2),
	      grids(1)->Value(i0, i1, i2),
	      grids(2)->Value(i0, i1, i2),
	      grids_(0)->Value(i0, i1, i2),
	      grids_(1)->Value(i0, i1, i2),
	      grids_(2)->Value(i0, i1, i2));
    else if (N==4)
      for (i0=0; i0<grids(0)->GetLength(); i0++)
	for (i1=0; i1<grids(1)->GetLength(); i1++)
	  for (i2=0; i2<grids(2)->GetLength(); i2++)
	    for (i3=0; i3<grids(3)->GetLength(); i3++)
	      f(grids(0)->Value(i0, i1, i2, i3),
		grids(1)->Value(i0, i1, i2, i3),
		grids(2)->Value(i0, i1, i2, i3),
		grids(3)->Value(i0, i1, i2, i3),
		grids_(0)->Value(i0, i1, i2, i3),
		grids_(1)->Value(i0, i1, i2, i3),
		grids_(2)->Value(i0, i1, i2, i3),
		grids_(3)->Value(i0, i1, i2, i3));
    else if (N==5)
      for (i0=0; i0<grids(0)->GetLength(); i0++)
	for (i1=0; i1<grids(1)->GetLength(); i1++)
	  for (i2=0; i2<grids(2)->GetLength(); i2++)
	    for (i3=0; i3<grids(3)->GetLength(); i3++)
	      for (i4=0; i4<grids(4)->GetLength(); i4++)
		f(grids(0)->Value(i0, i1, i2, i3, i4),
		  grids(1)->Value(i0, i1, i2, i3, i4),
		  grids(2)->Value(i0, i1, i2, i3, i4),
		  grids(3)->Value(i0, i1, i2, i3, i4),
		  grids(4)->Value(i0, i1, i2, i3, i4),
		  grids_(0)->Value(i0, i1, i2, i3, i4),
		  grids_(1)->Value(i0, i1, i2, i3, i4),
		  grids_(2)->Value(i0, i1, i2, i3, i4),
		  grids_(3)->Value(i0, i1, i2, i3, i4),
		  grids_(4)->Value(i0, i1, i2, i3, i4));
    else if (N==6)
      for (i0=0; i0<grids(0)->GetLength(); i0++)
	for (i1=0; i1<grids(1)->GetLength(); i1++)
	  for (i2=0; i2<grids(2)->GetLength(); i2++)
	    for (i3=0; i3<grids(3)->GetLength(); i3++)
	      for (i4=0; i4<grids(4)->GetLength(); i4++)
		for (i5=0; i5<grids(5)->GetLength(); i5++)
		  f(grids(0)->Value(i0, i1, i2, i3,
				    i4, i5),
		    grids(1)->Value(i0, i1, i2, i3,
				    i4, i5),
		    grids(2)->Value(i0, i1, i2, i3,
				    i4, i5),
		    grids(3)->Value(i0, i1, i2, i3,
				    i4, i5),
		    grids(4)->Value(i0, i1, i2, i3,
				    i4, i5),
		    grids(5)->Value(i0, i1, i2, i3,
				    i4, i5),
		    grids_(0)->Value(i0, i1, i2, i3,
				    i4, i5),
		    grids_(1)->Value(i0, i1, i2, i3,
				    i4, i5),
		    grids_(2)->Value(i0, i1, i2, i3,
				    i4, i5),
		    grids_(3)->Value(i0, i1, i2, i3,
				    i4, i5),
		    grids_(4)->Value(i0, i1, i2, i3,
				    i4, i5),
		    grids_(5)->Value(i0, i1, i2, i3,
				    i4, i5));
    else if (N==7)
      for (i0=0; i0<grids(0)->GetLength(); i0++)
	for (i1=0; i1<grids(1)->GetLength(); i1++)
	  for (i2=0; i2<grids(2)->GetLength(); i2++)
	    for (i3=0; i3<grids(3)->GetLength(); i3++)
	      for (i4=0; i4<grids(4)->GetLength(); i4++)
		for (i5=0; i5<grids(5)->GetLength(); i5++)
		  for (i6=0; i6<grids(6)->GetLength(); i6++)
		    f(grids(0)->Value(i0, i1, i2, i3,
				      i4, i5, i6),
		      grids(1)->Value(i0, i1, i2, i3,
				      i4, i5, i6),
		      grids(2)->Value(i0, i1, i2, i3,
				      i4, i5, i6),
		      grids(3)->Value(i0, i1, i2, i3,
				      i4, i5, i6),
		      grids(4)->Value(i0, i1, i2, i3,
				      i4, i5, i6),
		      grids(5)->Value(i0, i1, i2, i3,
				      i4, i5, i6),
		      grids(6)->Value(i0, i1, i2, i3,
				      i4, i5, i6),
		      grids_(0)->Value(i0, i1, i2, i3,
				      i4, i5, i6),
		      grids_(1)->Value(i0, i1, i2, i3,
				      i4, i5, i6),
		      grids_(2)->Value(i0, i1, i2, i3,
				      i4, i5, i6),
		      grids_(3)->Value(i0, i1, i2, i3,
				      i4, i5, i6),
		      grids_(4)->Value(i0, i1, i2, i3,
				      i4, i5, i6),
		      grids_(5)->Value(i0, i1, i2, i3,
				      i4, i5, i6),
		      grids_(6)->Value(i0, i1, i2, i3,
				      i4, i5, i6));
    else if (N==8)
      for (i0=0; i0<grids(0)->GetLength(); i0++)
	for (i1=0; i1<grids(1)->GetLength(); i1++)
	  for (i2=0; i2<grids(2)->GetLength(); i2++)
	    for (i3=0; i3<grids(3)->GetLength(); i3++)
	      for (i4=0; i4<grids(4)->GetLength(); i4++)
		for (i5=0; i5<grids(5)->GetLength(); i5++)
		  for (i6=0; i6<grids(6)->GetLength(); i6++)
		    for (i7=0; i7<grids(7)->GetLength(); i7++)
		      f(grids(0)->Value(i0, i1, i2, i3,
					i4, i5, i6, i7),
			grids(1)->Value(i0, i1, i2, i3,
					i4, i5, i6, i7),
			grids(2)->Value(i0, i1, i2, i3,
					i4, i5, i6, i7),
			grids(3)->Value(i0, i1, i2, i3,
					i4, i5, i6, i7),
			grids(4)->Value(i0, i1, i2, i3,
					i4, i5, i6, i7),
			grids(5)->Value(i0, i1, i2, i3,
					i4, i5, i6, i7),
			grids(6)->Value(i0, i1, i2, i3,
					i4, i5, i6, i7),
			grids(7)->Value(i0, i1, i2, i3,
					i4, i5, i6, i7),
			grids_(0)->Value(i0, i1, i2, i3,
					i4, i5, i6, i7),
			grids_(1)->Value(i0, i1, i2, i3,
					i4, i5, i6, i7),
			grids_(2)->Value(i0, i1, i2, i3,
					i4, i5, i6, i7),
			grids_(3)->Value(i0, i1, i2, i3,
					i4, i5, i6, i7),
			grids_(4)->Value(i0, i1, i2, i3,
					i4, i5, i6, i7),
			grids_(5)->Value(i0, i1, i2, i3,
					i4, i5, i6, i7),
			grids_(6)->Value(i0, i1, i2, i3,
					i4, i5, i6, i7),
			grids_(7)->Value(i0, i1, i2, i3,
					i4, i5, i6, i7));
    else if (N==9)
      for (i0=0; i0<grids(0)->GetLength(); i0++)
	for (i1=0; i1<grids(1)->GetLength(); i1++)
	  for (i2=0; i2<grids(2)->GetLength(); i2++)
	    for (i3=0; i3<grids(3)->GetLength(); i3++)
	      for (i4=0; i4<grids(4)->GetLength(); i4++)
		for (i5=0; i5<grids(5)->GetLength(); i5++)
		  for (i6=0; i6<grids(6)->GetLength(); i6++)
		    for (i7=0; i7<grids(7)->GetLength(); i7++)
		      for (i8=0; i8<grids(8)->GetLength(); i8++)
			f(grids(0)->Value(i0, i1, i2, i3,
					  i4, i5, i6, i7,
					  i8),
			  grids(1)->Value(i0, i1, i2, i3,
					  i4, i5, i6, i7,
					  i8),
			  grids(2)->Value(i0, i1, i2, i3,
					  i4, i5, i6, i7,
					  i8),
			  grids(3)->Value(i0, i1, i2, i3,
					  i4, i5, i6, i7,
					  i8),
			  grids(4)->Value(i0, i1, i2, i3,
					  i4, i5, i6, i7,
					  i8),
			  grids(5)->Value(i0, i1, i2, i3,
					  i4, i5, i6, i7,
					  i8),
			  grids(6)->Value(i0, i1, i2, i3,
					  i4, i5, i6, i7,
					  i8),
			  grids(7)->Value(i0, i1, i2, i3,
					  i4, i5, i6, i7,
					  i8),
			  grids(8)->Value(i0, i1, i2, i3,
					  i4, i5, i6, i7,
					  i8),
			  grids_(0)->Value(i0, i1, i2, i3,
					  i4, i5, i6, i7,
					  i8),
			  grids_(1)->Value(i0, i1, i2, i3,
					  i4, i5, i6, i7,
					  i8),
			  grids_(2)->Value(i0, i1, i2, i3,
					  i4, i5, i6, i7,
					  i8),
			  grids_(3)->Value(i0, i1, i2, i3,
					  i4, i5, i6, i7,
					  i8),
			  grids_(4)->Value(i0, i1, i2, i3,
					  i4, i5, i6, i7,
					  i8),
			  grids_(5)->Value(i0, i1, i2, i3,
					  i4, i5, i6, i7,
					  i8),
			  grids_(6)->Value(i0, i1, i2, i3,
					  i4, i5, i6, i7,
					  i8),
			  grids_(7)->Value(i0, i1, i2, i3,
					  i4, i5, i6, i7,
					  i8),
			  grids_(8)->Value(i0, i1, i2, i3,
					  i4, i5, i6, i7,
					  i8));
    else if (N==10)
      for (i0=0; i0<grids(0)->GetLength(); i0++)
	for (i1=0; i1<grids(1)->GetLength(); i1++)
	  for (i2=0; i2<grids(2)->GetLength(); i2++)
	    for (i3=0; i3<grids(3)->GetLength(); i3++)
	      for (i4=0; i4<grids(4)->GetLength(); i4++)
		for (i5=0; i5<grids(5)->GetLength(); i5++)
		  for (i6=0; i6<grids(6)->GetLength(); i6++)
		    for (i7=0; i7<grids(7)->GetLength(); i7++)
		      for (i8=0; i8<grids(8)->GetLength(); i8++)
			for (i9=0; i9<grids(9)->GetLength(); i9++)
			  f(grids(0)->Value(i0, i1, i2, i3,
					    i4, i5, i6, i7,
					    i8, i9),
			    grids(1)->Value(i0, i1, i2, i3,
					    i4, i5, i6, i7,
					    i8, i9),
			    grids(2)->Value(i0, i1, i2, i3,
					    i4, i5, i6, i7,
					    i8, i9),
			    grids(3)->Value(i0, i1, i2, i3,
					    i4, i5, i6, i7,
					    i8, i9),
			    grids(4)->Value(i0, i1, i2, i3,
					    i4, i5, i6, i7,
					    i8, i9),
			    grids(5)->Value(i0, i1, i2, i3,
					    i4, i5, i6, i7,
					    i8, i9),
			    grids(6)->Value(i0, i1, i2, i3,
					    i4, i5, i6, i7,
					    i8, i9),
			    grids(7)->Value(i0, i1, i2, i3,
					    i4, i5, i6, i7,
					    i8, i9),
			    grids(8)->Value(i0, i1, i2, i3,
					    i4, i5, i6, i7,
					    i8, i9),
			    grids(9)->Value(i0, i1, i2, i3,
					    i4, i5, i6, i7,
					    i8, i9),
			    grids_(0)->Value(i0, i1, i2, i3,
					    i4, i5, i6, i7,
					    i8, i9),
			    grids_(1)->Value(i0, i1, i2, i3,
					    i4, i5, i6, i7,
					    i8, i9),
			    grids_(2)->Value(i0, i1, i2, i3,
					    i4, i5, i6, i7,
					    i8, i9),
			    grids_(3)->Value(i0, i1, i2, i3,
					    i4, i5, i6, i7,
					    i8, i9),
			    grids_(4)->Value(i0, i1, i2, i3,
					    i4, i5, i6, i7,
					    i8, i9),
			    grids_(5)->Value(i0, i1, i2, i3,
					    i4, i5, i6, i7,
					    i8, i9),
			    grids_(6)->Value(i0, i1, i2, i3,
					    i4, i5, i6, i7,
					    i8, i9),
			    grids_(7)->Value(i0, i1, i2, i3,
					    i4, i5, i6, i7,
					    i8, i9),
			    grids_(8)->Value(i0, i1, i2, i3,
					    i4, i5, i6, i7,
					    i8, i9),
			    grids_(9)->Value(i0, i1, i2, i3,
					    i4, i5, i6, i7,
					    i8, i9));

    for (i=0; i<N; i++)
      delete grids(i);
    
  }

  template<class T, int N>
  void Data<T, N>::ChangeCoordsInPlace(Function_Base<T>& f)
  {

    int i, j;
    int NbGrids = grids_.numElements();
    Array<Grid<T>*, 1> grids_old(NbGrids),
      grids(NbGrids);

    Grid<T>* old_grid;

    for (i=0; i<NbGrids; i++)
      grids_old(i) = grids_(i)->Duplicate();

    for (i=0; i<N; i++)
      {
	for (j=0; j<NbGrids; j++)
	  grids(j) = grids_old(j)->Duplicate();
	grids_(i)->ChangeCoordsInPlace(f, grids);
	for (j=0; j<NbGrids; j++)
	  delete grids(j);
      }

    for (int i=0; i<N; i++)
      delete grids_old(i);

  }

  template<class T, int N>
  void Data<T, N>::Print()
  {
    cout << data_ << endl;
  }

  template<class T, int N>
  void Data<T, N>::SetVariables()
  {
    for (int i=0; i<N; i++)
      grids_(i)->SetVariable(i);
  }

}  // namespace SeldonData.


#define FILE_SELDONDATA_DATA_CXX
#endif
