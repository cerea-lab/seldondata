// Copyright (C) 2003 Vivien Mallet
//
// This file is part of SeldonData library.
// SeldonData library is a tool for data processing.
// 
// SeldonData is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// SeldonData is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License (file "license") for more details.
//
// For more information, please see the SeldonData home page:
//     http://membres.lycos.fr/vmallet/seldondata/

#ifndef FILE_SELDONDATA_DATA_CXX

#include <cstdlib>
#include "Data.hxx"

namespace SeldonData
{

  //! Constructor for one-dimensional data.
  /*!
    \param G0 grid for dimension #0.
  */
  template<class T, int N, class TG>
  Data<T, N, TG>::Data(Grid<TG>& G0)  throw():
    data_(G0.GetLength()), grids_(N)
  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=1)
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N, TG>::Data(Grid<TG>, ...)."
	     << endl << "   Required " + to_str(N)
	  + " grids, but got 1 grids." << endl;
	abort();
      }
#endif

    grids_(0) = G0.Copy();
    SetVariables();


#ifdef DEBUG_SELDONDATA_DIMENSION
    int i, j;
    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	if ( (grids_(i)->GetLength(j)!=0)
	     && (grids_(i)->GetLength(j)!=grids_(j)->GetLength()) )
	  {
	    cout << "ERROR!" << endl;
	    cout << "Wrong dimension in Data<T, N, TG>::Data(Grid<TG>, ...)."
		 << endl << "   Length of grid #" << i << " along dimension #"
		 << j << " is " << grids_(i)->GetLength(j) << " but should be "
		 << grids_(j)->GetLength() << "." << endl;
	    abort();
	  }
#endif

  }

  //! Constructor for two-dimensional data.
  /*!
    \param G0 grid for dimension #0.
    \param G1 grid for dimension #1.
  */
  template<class T, int N, class TG>
  Data<T, N, TG>::Data(Grid<TG>& G0, Grid<TG>& G1)  throw():
    data_(G0.GetLength(), G1.GetLength()), grids_(N)
  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=2)
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N, TG>::Data(Grid<TG>, ...)."
	     << endl << "   Required " + to_str(N)
	  + " grids, but got 2 grids." << endl;
	abort();
      }
#endif

    grids_(0) = G0.Copy(); grids_(1) = G1.Copy();
    SetVariables();

#ifdef DEBUG_SELDONDATA_DIMENSION
    int i, j;
    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	if ( (grids_(i)->GetLength(j)!=0)
	     && (grids_(i)->GetLength(j)!=grids_(j)->GetLength()) )
	  {
	    cout << "ERROR!" << endl;
	    cout << "Wrong dimension in Data<T, N, TG>::Data(Grid<TG>, ...)."
		 << endl << "   Length of grid #" << i << " along dimension #"
		 << j << " is " << grids_(i)->GetLength(j) << " but should be "
		 << grids_(j)->GetLength() << "." << endl;
	    abort();
	  }
#endif

  }

  //! Constructor for three-dimensional data.
  /*!
    \param G0 grid for dimension #0.
    \param G1 grid for dimension #1.
    \param G2 grid for dimension #2.
  */
  template<class T, int N, class TG>
  Data<T, N, TG>::Data(Grid<TG>& G0, Grid<TG>& G1, Grid<TG>& G2)  throw():
    data_(G0.GetLength(), G1.GetLength(),
	  G2.GetLength()), grids_(N)
  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=3)
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N, TG>::Data(Grid<TG>, ...)."
	     << endl << "   Required " + to_str(N)
	  + " grids, but got 3 grids." << endl;
	abort();
      }
#endif

    grids_(0) = G0.Copy(); grids_(1) = G1.Copy();
    grids_(2) = G2.Copy();
    SetVariables();


#ifdef DEBUG_SELDONDATA_DIMENSION
    int i, j;
    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	if ( (grids_(i)->GetLength(j)!=0)
	     && (grids_(i)->GetLength(j)!=grids_(j)->GetLength()) )
	  {
	    cout << "ERROR!" << endl;
	    cout << "Wrong dimension in Data<T, N, TG>::Data(Grid<TG>, ...)."
		 << endl << "   Length of grid #" << i << " along dimension #"
		 << j << " is " << grids_(i)->GetLength(j) << " but should be "
		 << grids_(j)->GetLength() << "." << endl;
	    abort();
	  }
#endif

  }

  //! Constructor for four-dimensional data.
  /*!
    \param G0 grid for dimension #0.
    \param G1 grid for dimension #1.
    \param G2 grid for dimension #2.
    \param G3 grid for dimension #3.
  */
  template<class T, int N, class TG>
  Data<T, N, TG>::Data(Grid<TG>& G0, Grid<TG>& G1, Grid<TG>& G2,
		       Grid<TG>& G3)  throw():
    data_(G0.GetLength(), G1.GetLength(),
	  G2.GetLength(), G3.GetLength()), grids_(N)
  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=4)
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N, TG>::Data(Grid<TG>, ...)."
	     << endl << "   Required " + to_str(N)
	  + " grids, but got 4 grids." << endl;
	abort();
      }
#endif

    grids_(0) = G0.Copy(); grids_(1) = G1.Copy();
    grids_(2) = G2.Copy(); grids_(3) = G3.Copy();
    SetVariables();


#ifdef DEBUG_SELDONDATA_DIMENSION
    int i, j;
    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	if ( (grids_(i)->GetLength(j)!=0)
	     && (grids_(i)->GetLength(j)!=grids_(j)->GetLength()) )
	  {
	    cout << "ERROR!" << endl;
	    cout << "Wrong dimension in Data<T, N, TG>::Data(Grid<TG>, ...)."
		 << endl << "   Length of grid #" << i << " along dimension #"
		 << j << " is " << grids_(i)->GetLength(j) << " but should be "
		 << grids_(j)->GetLength() << "." << endl;
	    abort();
	  }
#endif

  }

  //! Constructor for five-dimensional data.
  /*!
    \param G0 grid for dimension #0.
    \param G1 grid for dimension #1.
    \param G2 grid for dimension #2.
    \param G3 grid for dimension #3.
    \param G4 grid for dimension #4.
  */
  template<class T, int N, class TG>
  Data<T, N, TG>::Data(Grid<TG>& G0, Grid<TG>& G1, Grid<TG>& G2,
		       Grid<TG>& G3, Grid<TG>& G4)  throw():
    data_(G0.GetLength(), G1.GetLength(),
	  G2.GetLength(), G3.GetLength(),
	  G4.GetLength()), grids_(N)
  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=5)
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N, TG>::Data(Grid<TG>, ...)."
	     << endl << "   Required " + to_str(N)
	  + " grids, but got 5 grids." << endl;
	abort();
      }
#endif

    grids_(0) = G0.Copy(); grids_(1) = G1.Copy();
    grids_(2) = G2.Copy(); grids_(3) = G3.Copy();
    grids_(4) = G4.Copy();
    SetVariables();


#ifdef DEBUG_SELDONDATA_DIMENSION
    int i, j;
    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	if ( (grids_(i)->GetLength(j)!=0)
	     && (grids_(i)->GetLength(j)!=grids_(j)->GetLength()) )
	  {
	    cout << "ERROR!" << endl;
	    cout << "Wrong dimension in Data<T, N, TG>::Data(Grid<TG>, ...)."
		 << endl << "   Length of grid #" << i << " along dimension #"
		 << j << " is " << grids_(i)->GetLength(j) << " but should be "
		 << grids_(j)->GetLength() << "." << endl;
	    abort();
	  }
#endif

  }

  //! Constructor for six-dimensional data.
  /*!
    \param G0 grid for dimension #0.
    \param G1 grid for dimension #1.
    \param G2 grid for dimension #2.
    \param G3 grid for dimension #3.
    \param G4 grid for dimension #4.
    \param G5 grid for dimension #5.
  */
  template<class T, int N, class TG>
  Data<T, N, TG>::Data(Grid<TG>& G0, Grid<TG>& G1, Grid<TG>& G2,
		       Grid<TG>& G3, Grid<TG>& G4, Grid<TG>& G5)  throw():
    data_(G0.GetLength(), G1.GetLength(),
	  G2.GetLength(), G3.GetLength(), G4.GetLength(),
	  G5.GetLength()), grids_(N)
  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=6)
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N, TG>::Data(Grid<TG>, ...)."
	     << endl << "   Required " + to_str(N)
	  + " grids, but got 6 grids." << endl;
	abort();
      }
#endif

    grids_(0) = G0.Copy(); grids_(1) = G1.Copy();
    grids_(2) = G2.Copy(); grids_(3) = G3.Copy();
    grids_(4) = G4.Copy(); grids_(5) = G5.Copy();
    SetVariables();


#ifdef DEBUG_SELDONDATA_DIMENSION
    int i, j;
    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	if ( (grids_(i)->GetLength(j)!=0)
	     && (grids_(i)->GetLength(j)!=grids_(j)->GetLength()) )
	  {
	    cout << "ERROR!" << endl;
	    cout << "Wrong dimension in Data<T, N, TG>::Data(Grid<TG>, ...)."
		 << endl << "   Length of grid #" << i << " along dimension #"
		 << j << " is " << grids_(i)->GetLength(j) << " but should be "
		 << grids_(j)->GetLength() << "." << endl;
	    abort();
	  }
#endif

  }

  //! Constructor for seven-dimensional data.
  /*!
    \param G0 grid for dimension #0.
    \param G1 grid for dimension #1.
    \param G2 grid for dimension #2.
    \param G3 grid for dimension #3.
    \param G4 grid for dimension #4.
    \param G5 grid for dimension #5.
    \param G6 grid for dimension #6.
  */
  template<class T, int N, class TG>
  Data<T, N, TG>::Data(Grid<TG>& G0, Grid<TG>& G1, Grid<TG>& G2,
		       Grid<TG>& G3, Grid<TG>& G4, Grid<TG>& G5,
		       Grid<TG>& G6)  throw():
    data_(G0.GetLength(), G1.GetLength(),
	  G2.GetLength(), G3.GetLength(), G4.GetLength(),
	  G5.GetLength(), G6.GetLength()), grids_(N)
  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=7)
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N, TG>::Data(Grid<TG>, ...)."
	     << endl << "   Required " + to_str(N)
	  + " grids, but got 7 grids." << endl;
	abort();
      }
#endif

    grids_(0) = G0.Copy(); grids_(1) = G1.Copy();
    grids_(2) = G2.Copy(); grids_(3) = G3.Copy();
    grids_(4) = G4.Copy(); grids_(5) = G5.Copy();
    grids_(6) = G6.Copy();
    SetVariables();


#ifdef DEBUG_SELDONDATA_DIMENSION
    int i, j;
    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	if ( (grids_(i)->GetLength(j)!=0)
	     && (grids_(i)->GetLength(j)!=grids_(j)->GetLength()) )
	  {
	    cout << "ERROR!" << endl;
	    cout << "Wrong dimension in Data<T, N, TG>::Data(Grid<TG>, ...)."
		 << endl << "   Length of grid #" << i << " along dimension #"
		 << j << " is " << grids_(i)->GetLength(j) << " but should be "
		 << grids_(j)->GetLength() << "." << endl;
	    abort();
	  }
#endif

  }

  //! Constructor for eight-dimensional data.
  /*!
    \param G0 grid for dimension #0.
    \param G1 grid for dimension #1.
    \param G2 grid for dimension #2.
    \param G3 grid for dimension #3.
    \param G4 grid for dimension #4.
    \param G5 grid for dimension #5.
    \param G6 grid for dimension #6.
    \param G7 grid for dimension #7.
  */
  template<class T, int N, class TG>
  Data<T, N, TG>::Data(Grid<TG>& G0, Grid<TG>& G1, Grid<TG>& G2,
		       Grid<TG>& G3, Grid<TG>& G4, Grid<TG>& G5,
		       Grid<TG>& G6, Grid<TG>& G7)  throw():
    data_(G0.GetLength(), G1.GetLength(),
	  G2.GetLength(), G3.GetLength(), G4.GetLength(),
	  G5.GetLength(), G6.GetLength(), G7.GetLength()),
    grids_(N)
  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=8)
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N, TG>::Data(Grid<TG>, ...)."
	     << endl << "   Required " + to_str(N)
	  + " grids, but got 8 grids." << endl;
	abort();
      }
#endif

    grids_(0) = G0.Copy(); grids_(1) = G1.Copy();
    grids_(2) = G2.Copy(); grids_(3) = G3.Copy();
    grids_(4) = G4.Copy(); grids_(5) = G5.Copy();
    grids_(6) = G6.Copy(); grids_(7) = G7.Copy();
    SetVariables();


#ifdef DEBUG_SELDONDATA_DIMENSION
    int i, j;
    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	if ( (grids_(i)->GetLength(j)!=0)
	     && (grids_(i)->GetLength(j)!=grids_(j)->GetLength()) )
	  {
	    cout << "ERROR!" << endl;
	    cout << "Wrong dimension in Data<T, N, TG>::Data(Grid<TG>, ...)."
		 << endl << "   Length of grid #" << i << " along dimension #"
		 << j << " is " << grids_(i)->GetLength(j) << " but should be "
		 << grids_(j)->GetLength() << "." << endl;
	    abort();
	  }
#endif

  }

  //! Constructor for nine-dimensional data.
  /*!
    \param G0 grid for dimension #0.
    \param G1 grid for dimension #1.
    \param G2 grid for dimension #2.
    \param G3 grid for dimension #3.
    \param G4 grid for dimension #4.
    \param G5 grid for dimension #5.
    \param G6 grid for dimension #6.
    \param G7 grid for dimension #7.
    \param G8 grid for dimension #8.
  */
  template<class T, int N, class TG>
  Data<T, N, TG>::Data(Grid<TG>& G0, Grid<TG>& G1, Grid<TG>& G2,
		       Grid<TG>& G3, Grid<TG>& G4, Grid<TG>& G5,
		       Grid<TG>& G6, Grid<TG>& G7, Grid<TG>& G8)  throw():
    data_(G0.GetLength(), G1.GetLength(),
	  G2.GetLength(), G3.GetLength(), G4.GetLength(),
	  G5.GetLength(), G6.GetLength(), G7.GetLength(),
	  G8.GetLength()), grids_(N)
  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=9)
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N, TG>::Data(Grid<TG>, ...)."
	     << endl << "   Required " + to_str(N)
	  + " grids, but got 9 grids." << endl;
	abort();
      }
#endif

    grids_(0) = G0.Copy(); grids_(1) = G1.Copy();
    grids_(2) = G2.Copy(); grids_(3) = G3.Copy();
    grids_(4) = G4.Copy(); grids_(5) = G5.Copy();
    grids_(6) = G6.Copy(); grids_(7) = G7.Copy();
    grids_(8) = G8.Copy();
    SetVariables();


#ifdef DEBUG_SELDONDATA_DIMENSION
    int i, j;
    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	if ( (grids_(i)->GetLength(j)!=0)
	     && (grids_(i)->GetLength(j)!=grids_(j)->GetLength()) )
	  {
	    cout << "ERROR!" << endl;
	    cout << "Wrong dimension in Data<T, N, TG>::Data(Grid<TG>, ...)."
		 << endl << "   Length of grid #" << i << " along dimension #"
		 << j << " is " << grids_(i)->GetLength(j) << " but should be "
		 << grids_(j)->GetLength() << "." << endl;
	    abort();
	  }
#endif

  }

  //! Constructor for ten-dimensional data.
  /*!
    \param G0 grid for dimension #0.
    \param G1 grid for dimension #1.
    \param G2 grid for dimension #2.
    \param G3 grid for dimension #3.
    \param G4 grid for dimension #4.
    \param G5 grid for dimension #5.
    \param G6 grid for dimension #6.
    \param G7 grid for dimension #7.
    \param G8 grid for dimension #8.
    \param G9 grid for dimension #9.
  */
  template<class T, int N, class TG>
  Data<T, N, TG>::Data(Grid<TG>& G0, Grid<TG>& G1, Grid<TG>& G2,
		       Grid<TG>& G3, Grid<TG>& G4, Grid<TG>& G5,
		       Grid<TG>& G6, Grid<TG>& G7, Grid<TG>& G8,
		       Grid<TG>& G9)  throw():
    data_(G0.GetLength(), G1.GetLength(),
	  G2.GetLength(), G3.GetLength(), G4.GetLength(),
	  G5.GetLength(), G6.GetLength(), G7.GetLength(),
	  G8.GetLength(), G9.GetLength()), grids_(N)
  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=10)
      {
	cout << "ERROR!" << endl;
	cout << "Wrong dimension in Data<T, N, TG>::Data(Grid<TG>, ...)."
	     << endl << "   Required " + to_str(N)
	  + " grids, but got 10 grids." << endl;
	abort();
      }
#endif

    grids_(0) = G0.Copy(); grids_(1) = G1.Copy();
    grids_(2) = G2.Copy(); grids_(3) = G3.Copy();
    grids_(4) = G4.Copy(); grids_(5) = G5.Copy();
    grids_(6) = G6.Copy(); grids_(7) = G7.Copy();
    grids_(8) = G8.Copy(); grids_(9) = G9.Copy();
    SetVariables();


#ifdef DEBUG_SELDONDATA_DIMENSION
    int i, j;
    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	if ( (grids_(i)->GetLength(j)!=0)
	     && (grids_(i)->GetLength(j)!=grids_(j)->GetLength()) )
	  {
	    cout << "ERROR!" << endl;
	    cout << "Wrong dimension in Data<T, N, TG>::Data(Grid<TG>, ...)."
		 << endl << "   Length of grid #" << i << " along dimension #"
		 << j << " is " << grids_(i)->GetLength(j) << " but should be "
		 << grids_(j)->GetLength() << "." << endl;
	    abort();
	  }
#endif

  }

  //! Destructor.
  template<class T, int N, class TG>
  Data<T, N, TG>::~Data()  throw()
  {
    for (int i=0; i<N; i++)
      delete grids_(i);
  }

  //! Access operator for one-dimensional data.
  /*!
    \param i0 index for dimension #0.
    \return A reference to element #i0.
    \exception SeldonData::WrongDim data dimension is not 1.
    \exception SeldonData::WrongIndex index is out of range.
  */
  template<class T, int N, class TG>
  inline T& Data<T, N, TG>::operator() (int i0)  
  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=1)
      throw WrongDim("Data<T, " + to_str(N) + ">::operator()",
		     "operator() was called with 1 argument.");
#endif

#ifdef DEBUG_SELDONDATA_INDICES
    if ( (i0<0) || (i0>=data_.extent(0)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #0 should be in [0, "
		       + to_str(data_.extent(0)-1) + "], but is equal to "
		       + to_str(i0) + ".");
#endif

    return data_(i0);
  }

  //! Access operator for two-dimensional data.
  /*!
    \param i0 index for dimension #0.
    \param i1 index for dimension #1.
    \return A reference to element (i0, i1).
    \exception SeldonData::WrongDim data dimension is not 2.
    \exception SeldonData::WrongIndex an index is out of range.
  */
  template<class T, int N, class TG>
  inline T& Data<T, N, TG>::operator() (int i0, int i1)  
  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=2)
      throw WrongDim("Data<T, " + to_str(N) + ">::operator()",
		     "operator() was called with 2 arguments.");
#endif

#ifdef DEBUG_SELDONDATA_INDICES
    if ( (i0<0) || (i0>=data_.extent(0)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #0 should be in [0, "
		       + to_str(data_.extent(0)-1) + "], but is equal to "
		       + to_str(i0) + ".");
    if ( (i1<0) || (i1>=data_.extent(1)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #1 should be in [0, "
		       + to_str(data_.extent(1)-1) + "], but is equal to "
		       + to_str(i1) + ".");
#endif

    return data_(i0, i1);
  }

  //! Access operator for three-dimensional data.
  /*!
    \param i0 index for dimension #0.
    \param i1 index for dimension #1.
    \param i2 index for dimension #2.
    \return A reference to element (i0, i1, i2).
    \exception SeldonData::WrongDim data dimension is not 3.
    \exception SeldonData::WrongIndex an index is out of range.
  */
  template<class T, int N, class TG>
  inline T& Data<T, N, TG>::operator() (int i0, int i1, int i2)
  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=3)
      throw WrongDim("Data<T, " + to_str(N) + ">::operator()",
		     "operator() was called with 3 arguments.");
#endif

#ifdef DEBUG_SELDONDATA_INDICES
    if ( (i0<0) || (i0>=data_.extent(0)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #0 should be in [0, "
		       + to_str(data_.extent(0)-1) + "], but is equal to "
		       + to_str(i0) + ".");
    if ( (i1<0) || (i1>=data_.extent(1)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #1 should be in [0, "
		       + to_str(data_.extent(1)-1) + "], but is equal to "
		       + to_str(i1) + ".");
    if ( (i2<0) || (i2>=data_.extent(2)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #2 should be in [0, "
		       + to_str(data_.extent(2)-1) + "], but is equal to "
		       + to_str(i2) + ".");
#endif

    return data_(i0, i1, i2);
  }

  //! Access operator for four-dimensional data.
  /*!
    \param i0 index for dimension #0.
    \param i1 index for dimension #1.
    \param i2 index for dimension #2.
    \param i3 index for dimension #3.
    \return A reference to element (i0, i1, i2, i3).
    \exception SeldonData::WrongDim data dimension is not 4.
    \exception SeldonData::WrongIndex an index is out of range.
  */
  template<class T, int N, class TG>
  inline T& Data<T, N, TG>::operator() (int i0, int i1, int i2,
					int i3)

  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=4)
      throw WrongDim("Data<T, " + to_str(N) + ">::operator()",
		     "operator() was called with 4 arguments.");
#endif

#ifdef DEBUG_SELDONDATA_INDICES
    if ( (i0<0) || (i0>=data_.extent(0)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #0 should be in [0, "
		       + to_str(data_.extent(0)-1) + "], but is equal to "
		       + to_str(i0) + ".");
    if ( (i1<0) || (i1>=data_.extent(1)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #1 should be in [0, "
		       + to_str(data_.extent(1)-1) + "], but is equal to "
		       + to_str(i1) + ".");
    if ( (i2<0) || (i2>=data_.extent(2)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #2 should be in [0, "
		       + to_str(data_.extent(2)-1) + "], but is equal to "
		       + to_str(i2) + ".");
    if ( (i3<0) || (i3>=data_.extent(3)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #3 should be in [0, "
		       + to_str(data_.extent(3)-1) + "], but is equal to "
		       + to_str(i3) + ".");
#endif

    return data_(i0, i1, i2, i3);
  }

  //! Access operator for five-dimensional data.
  /*!
    \param i0 index for dimension #0.
    \param i1 index for dimension #1.
    \param i2 index for dimension #2.
    \param i3 index for dimension #3.
    \param i4 index for dimension #4.
    \return A reference to element (i0, i1, i2, i3, i4).
    \exception SeldonData::WrongDim data dimension is not 5.
    \exception SeldonData::WrongIndex an index is out of range.
  */
  template<class T, int N, class TG>
  inline T& Data<T, N, TG>::operator() (int i0, int i1, int i2,
					int i3, int i4)

  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=5)
      throw WrongDim("Data<T, " + to_str(N) + ">::operator()",
		     "operator() was called with 5 arguments.");
#endif

#ifdef DEBUG_SELDONDATA_INDICES
    if ( (i0<0) || (i0>=data_.extent(0)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #0 should be in [0, "
		       + to_str(data_.extent(0)-1) + "], but is equal to "
		       + to_str(i0) + ".");
    if ( (i1<0) || (i1>=data_.extent(1)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #1 should be in [0, "
		       + to_str(data_.extent(1)-1) + "], but is equal to "
		       + to_str(i1) + ".");
    if ( (i2<0) || (i2>=data_.extent(2)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #2 should be in [0, "
		       + to_str(data_.extent(2)-1) + "], but is equal to "
		       + to_str(i2) + ".");
    if ( (i3<0) || (i3>=data_.extent(3)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #3 should be in [0, "
		       + to_str(data_.extent(3)-1) + "], but is equal to "
		       + to_str(i3) + ".");
    if ( (i4<0) || (i4>=data_.extent(4)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #4 should be in [0, "
		       + to_str(data_.extent(4)-1) + "], but is equal to "
		       + to_str(i4) + ".");
#endif

    return data_(i0, i1, i2, i3, i4);
  }

  //! Access operator for six-dimensional data.
  /*!
    \param i0 index for dimension #0.
    \param i1 index for dimension #1.
    \param i2 index for dimension #2.
    \param i3 index for dimension #3.
    \param i4 index for dimension #4.
    \param i5 index for dimension #5.
    \return A reference to element (i0, i1, i2, i3, i4, i5).
    \exception SeldonData::WrongDim data dimension is not 6.
    \exception SeldonData::WrongIndex an index is out of range.
  */
  template<class T, int N, class TG>
  inline T& Data<T, N, TG>::operator() (int i0, int i1, int i2,
					int i3, int i4, int i5)

  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=6)
      throw WrongDim("Data<T, " + to_str(N) + ">::operator()",
		     "operator() was called with 6 arguments.");
#endif

#ifdef DEBUG_SELDONDATA_INDICES
    if ( (i0<0) || (i0>=data_.extent(0)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #0 should be in [0, "
		       + to_str(data_.extent(0)-1) + "], but is equal to "
		       + to_str(i0) + ".");
    if ( (i1<0) || (i1>=data_.extent(1)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #1 should be in [0, "
		       + to_str(data_.extent(1)-1) + "], but is equal to "
		       + to_str(i1) + ".");
    if ( (i2<0) || (i2>=data_.extent(2)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #2 should be in [0, "
		       + to_str(data_.extent(2)-1) + "], but is equal to "
		       + to_str(i2) + ".");
    if ( (i3<0) || (i3>=data_.extent(3)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #3 should be in [0, "
		       + to_str(data_.extent(3)-1) + "], but is equal to "
		       + to_str(i3) + ".");
    if ( (i4<0) || (i4>=data_.extent(4)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #4 should be in [0, "
		       + to_str(data_.extent(4)-1) + "], but is equal to "
		       + to_str(i4) + ".");
    if ( (i5<0) || (i5>=data_.extent(5)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #5 should be in [0, "
		       + to_str(data_.extent(5)-1) + "], but is equal to "
		       + to_str(i5) + ".");
#endif

    return data_(i0, i1, i2, i3, i4, i5);
  }

  template<class T, int N, class TG>
  //! Access operator for seven-dimensional data.
  /*!
    \param i0 index for dimension #0.
    \param i1 index for dimension #1.
    \param i2 index for dimension #2.
    \param i3 index for dimension #3.
    \param i4 index for dimension #4.
    \param i5 index for dimension #5.
    \param i6 index for dimension #6.
    \return A reference to element (i0, i1, i2, i3,
    i4, i5, i6).
    \exception SeldonData::WrongDim data dimension is not 7.
    \exception SeldonData::WrongIndex an index is out of range.
  */
  inline T& Data<T, N, TG>::operator() (int i0, int i1, int i2,
					int i3, int i4, int i5,
					int i6)

  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=7)
      throw WrongDim("Data<T, " + to_str(N) + ">::operator()",
		     "operator() was called with 7 arguments.");
#endif

#ifdef DEBUG_SELDONDATA_INDICES
    if ( (i0<0) || (i0>=data_.extent(0)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #0 should be in [0, "
		       + to_str(data_.extent(0)-1) + "], but is equal to "
		       + to_str(i0) + ".");
    if ( (i1<0) || (i1>=data_.extent(1)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #1 should be in [0, "
		       + to_str(data_.extent(1)-1) + "], but is equal to "
		       + to_str(i1) + ".");
    if ( (i2<0) || (i2>=data_.extent(2)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #2 should be in [0, "
		       + to_str(data_.extent(2)-1) + "], but is equal to "
		       + to_str(i2) + ".");
    if ( (i3<0) || (i3>=data_.extent(3)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #3 should be in [0, "
		       + to_str(data_.extent(3)-1) + "], but is equal to "
		       + to_str(i3) + ".");
    if ( (i4<0) || (i4>=data_.extent(4)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #4 should be in [0, "
		       + to_str(data_.extent(4)-1) + "], but is equal to "
		       + to_str(i4) + ".");
    if ( (i5<0) || (i5>=data_.extent(5)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #5 should be in [0, "
		       + to_str(data_.extent(5)-1) + "], but is equal to "
		       + to_str(i5) + ".");
    if ( (i6<0) || (i6>=data_.extent(6)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #6 should be in [0, "
		       + to_str(data_.extent(6)-1) + "], but is equal to "
		       + to_str(i6) + ".");
#endif

    return data_(i0, i1, i2, i3, i4, i5, i6);
  }

  template<class T, int N, class TG>
  //! Access operator for eight-dimensional data.
  /*!
    \param i0 index for dimension #0.
    \param i1 index for dimension #1.
    \param i2 index for dimension #2.
    \param i3 index for dimension #3.
    \param i4 index for dimension #4.
    \param i5 index for dimension #5.
    \param i6 index for dimension #6.
    \param i7 index for dimension #7.
    \return A reference to element (i0, i1, i2, i3, i4,
    i5, i6, i7).
    \exception SeldonData::WrongDim data dimension is not 8.
    \exception SeldonData::WrongIndex an index is out of range.
  */
  inline T& Data<T, N, TG>::operator() (int i0, int i1, int i2,
					int i3, int i4, int i5,
					int i6, int i7)

  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=8)
      throw WrongDim("Data<T, " + to_str(N) + ">::operator()",
		     "operator() was called with 8 arguments.");
#endif

#ifdef DEBUG_SELDONDATA_INDICES
    if ( (i0<0) || (i0>=data_.extent(0)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #0 should be in [0, "
		       + to_str(data_.extent(0)-1) + "], but is equal to "
		       + to_str(i0) + ".");
    if ( (i1<0) || (i1>=data_.extent(1)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #1 should be in [0, "
		       + to_str(data_.extent(1)-1) + "], but is equal to "
		       + to_str(i1) + ".");
    if ( (i2<0) || (i2>=data_.extent(2)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #2 should be in [0, "
		       + to_str(data_.extent(2)-1) + "], but is equal to "
		       + to_str(i2) + ".");
    if ( (i3<0) || (i3>=data_.extent(3)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #3 should be in [0, "
		       + to_str(data_.extent(3)-1) + "], but is equal to "
		       + to_str(i3) + ".");
    if ( (i4<0) || (i4>=data_.extent(4)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #4 should be in [0, "
		       + to_str(data_.extent(4)-1) + "], but is equal to "
		       + to_str(i4) + ".");
    if ( (i5<0) || (i5>=data_.extent(5)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #5 should be in [0, "
		       + to_str(data_.extent(5)-1) + "], but is equal to "
		       + to_str(i5) + ".");
    if ( (i6<0) || (i6>=data_.extent(6)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #6 should be in [0, "
		       + to_str(data_.extent(6)-1) + "], but is equal to "
		       + to_str(i6) + ".");
    if ( (i7<0) || (i7>=data_.extent(7)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #7 should be in [0, "
		       + to_str(data_.extent(7)-1) + "], but is equal to "
		       + to_str(i7) + ".");
#endif

    return data_(i0, i1, i2, i3, i4, i5, i6, i7);
  }

  template<class T, int N, class TG>
  //! Access operator for nine-dimensional data.
  /*!
    \param i0 index for dimension #0.
    \param i1 index for dimension #1.
    \param i2 index for dimension #2.
    \param i3 index for dimension #3.
    \param i4 index for dimension #4.
    \param i5 index for dimension #5.
    \param i6 index for dimension #6.
    \param i7 index for dimension #7.
    \param i8 index for dimension #8.
    \return A reference to element (i0, i1, i2, i3, i4,
    i5, i6, i7, i8).
    \exception SeldonData::WrongDim data dimension is not 9.
    \exception SeldonData::WrongIndex an index is out of range.
  */
  inline T& Data<T, N, TG>::operator() (int i0, int i1, int i2,
					int i3, int i4, int i5,
					int i6, int i7, int i8)

  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=9)
      throw WrongDim("Data<T, " + to_str(N) + ">::operator()",
		     "operator() was called with 9 arguments.");
#endif

#ifdef DEBUG_SELDONDATA_INDICES
    if ( (i0<0) || (i0>=data_.extent(0)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #0 should be in [0, "
		       + to_str(data_.extent(0)-1) + "], but is equal to "
		       + to_str(i0) + ".");
    if ( (i1<0) || (i1>=data_.extent(1)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #1 should be in [0, "
		       + to_str(data_.extent(1)-1) + "], but is equal to "
		       + to_str(i1) + ".");
    if ( (i2<0) || (i2>=data_.extent(2)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #2 should be in [0, "
		       + to_str(data_.extent(2)-1) + "], but is equal to "
		       + to_str(i2) + ".");
    if ( (i3<0) || (i3>=data_.extent(3)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #3 should be in [0, "
		       + to_str(data_.extent(3)-1) + "], but is equal to "
		       + to_str(i3) + ".");
    if ( (i4<0) || (i4>=data_.extent(4)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #4 should be in [0, "
		       + to_str(data_.extent(4)-1) + "], but is equal to "
		       + to_str(i4) + ".");
    if ( (i5<0) || (i5>=data_.extent(5)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #5 should be in [0, "
		       + to_str(data_.extent(5)-1) + "], but is equal to "
		       + to_str(i5) + ".");
    if ( (i6<0) || (i6>=data_.extent(6)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #6 should be in [0, "
		       + to_str(data_.extent(6)-1) + "], but is equal to "
		       + to_str(i6) + ".");
    if ( (i7<0) || (i7>=data_.extent(7)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #7 should be in [0, "
		       + to_str(data_.extent(7)-1) + "], but is equal to "
		       + to_str(i7) + ".");
    if ( (i8<0) || (i8>=data_.extent(8)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #8 should be in [0, "
		       + to_str(data_.extent(8)-1) + "], but is equal to "
		       + to_str(i8) + ".");
#endif

    return data_(i0, i1, i2, i3, i4, i5, i6, i7, i8);
  }

  //! Access operator for ten-dimensional data.
  /*!
    \param i0 index for dimension #0.
    \param i1 index for dimension #1.
    \param i2 index for dimension #2.
    \param i3 index for dimension #3.
    \param i4 index for dimension #4.
    \param i5 index for dimension #5.
    \param i6 index for dimension #6.
    \param i7 index for dimension #7.
    \param i8 index for dimension #8.
    \param i9 index for dimension #9.
    \return A reference to element (i0, i1, i2, i3, i4,
    i5, i6, i7, i8, i9).
    \exception SeldonData::WrongDim data dimension is not 10.
    \exception SeldonData::WrongIndex an index is out of range.
  */
  template<class T, int N, class TG>
  inline T& Data<T, N, TG>::operator() (int i0, int i1, int i2,
					int i3, int i4, int i5,
					int i6, int i7, int i8,
					int i9)

  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if (N!=10)
      throw WrongDim("Data<T, " + to_str(N) + ">::operator()",
		     "operator() was called with 10 arguments.");
#endif

#ifdef DEBUG_SELDONDATA_INDICES
    if ( (i0<0) || (i0>=data_.extent(0)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #0 should be in [0, "
		       + to_str(data_.extent(0)-1) + "], but is equal to "
		       + to_str(i0) + ".");
    if ( (i1<0) || (i1>=data_.extent(1)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #1 should be in [0, "
		       + to_str(data_.extent(1)-1) + "], but is equal to "
		       + to_str(i1) + ".");
    if ( (i2<0) || (i2>=data_.extent(2)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #2 should be in [0, "
		       + to_str(data_.extent(2)-1) + "], but is equal to "
		       + to_str(i2) + ".");
    if ( (i3<0) || (i3>=data_.extent(3)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #3 should be in [0, "
		       + to_str(data_.extent(3)-1) + "], but is equal to "
		       + to_str(i3) + ".");
    if ( (i4<0) || (i4>=data_.extent(4)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #4 should be in [0, "
		       + to_str(data_.extent(4)-1) + "], but is equal to "
		       + to_str(i4) + ".");
    if ( (i5<0) || (i5>=data_.extent(5)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #5 should be in [0, "
		       + to_str(data_.extent(5)-1) + "], but is equal to "
		       + to_str(i5) + ".");
    if ( (i6<0) || (i6>=data_.extent(6)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #6 should be in [0, "
		       + to_str(data_.extent(6)-1) + "], but is equal to "
		       + to_str(i6) + ".");
    if ( (i7<0) || (i7>=data_.extent(7)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #7 should be in [0, "
		       + to_str(data_.extent(7)-1) + "], but is equal to "
		       + to_str(i7) + ".");
    if ( (i8<0) || (i8>=data_.extent(8)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #8 should be in [0, "
		       + to_str(data_.extent(8)-1) + "], but is equal to "
		       + to_str(i8) + ".");
    if ( (i9<0) || (i9>=data_.extent(9)) )
      throw WrongIndex("Data<T, " + to_str(N) + ">::operator()",
		       "Index along dimension #9 should be in [0, "
		       + to_str(data_.extent(9)-1) + "], but is equal to "
		       + to_str(i9) + ".");
#endif

    return data_(i0, i1, i2, i3, i4, i5, i6, i7, i8, i9);
  }

  //! General access function.
  /*!
    Only useful arguments are taken into account.
    \param i0 index for dimension #0.
    \param i1 index for dimension #1.
    \param i2 index for dimension #2.
    \param i3 index for dimension #3.
    \param i4 index for dimension #4.
    \param i5 index for dimension #5.
    \param i6 index for dimension #6.
    \param i7 index for dimension #7.
    \param i8 index for dimension #8.
    \param i9 index for dimension #9.
    \return A reference to the required element.
  */
  template<class T, int N, class TG>
  inline T& Data<T, N, TG>::Value(int i0, int i1, int i2,
				  int i3, int i4, int i5,
				  int i6, int i7, int i8,
				  int i9)    
  {
    if (N==1)
      return (*this)(i0);
    if (N==2)
      return (*this)(i0, i1);
    if (N==3)
      return (*this)(i0, i1, i2);
    if (N==4)
      return (*this)(i0, i1, i2, i3);
    if (N==5)
      return (*this)(i0, i1, i2, i3, i4);
    if (N==6)
      return (*this)(i0, i1, i2, i3, i4, i5);
    if (N==7)
      return (*this)(i0, i1, i2, i3, i4, i5, i6);
    if (N==8)
      return (*this)(i0, i1, i2, i3, i4, i5, i6, i7);
    if (N==9)
      return (*this)(i0, i1, i2, i3, i4, i5, i6, i7, i8);
    if (N==10)
      return (*this)(i0, i1, i2, i3, i4, i5, i6, i7, i8, i9);
  }

  //! General access function.
  /*!
    Only useful arguments are taken into account.
    \param i0 index for dimension #0.
    \param i1 index for dimension #1.
    \param i2 index for dimension #2.
    \param i3 index for dimension #3.
    \param i4 index for dimension #4.
    \param i5 index for dimension #5.
    \param i6 index for dimension #6.
    \param i7 index for dimension #7.
    \param i8 index for dimension #8.
    \param i9 index for dimension #9.
    \return Value of the required element.
  */
  template<class T, int N, class TG>
  inline T Data<T, N, TG>::Value(int i0, int i1, int i2,
				 int i3, int i4, int i5,
				 int i6, int i7, int i8,
				 int i9) const
  {
    if (N==1)
      return (*this)(i0);
    if (N==2)
      return (*this)(i0, i1);
    if (N==3)
      return (*this)(i0, i1, i2);
    if (N==4)
      return (*this)(i0, i1, i2, i3);
    if (N==5)
      return (*this)(i0, i1, i2, i3, i4);
    if (N==6)
      return (*this)(i0, i1, i2, i3, i4, i5);
    if (N==7)
      return (*this)(i0, i1, i2, i3, i4, i5, i6);
    if (N==8)
      return (*this)(i0, i1, i2, i3, i4, i5, i6, i7);
    if (N==9)
      return (*this)(i0, i1, i2, i3, i4, i5, i6, i7, i8);
    if (N==10)
      return (*this)(i0, i1, i2, i3, i4, i5, i6, i7, i8, i9);
  }

  //! Sets current Data instance to data.
  /*!
    \param data Data instance to be copied.
  */
  template<class T, int N, class TG>
  void Data<T, N, TG>::Copy(Data<T, N, TG>& data)
  {
    for (int i=0; i<N; i++)
      {
	delete grids_(i);
	grids_(i) = data[i].Copy();
      }

    data_.resize(data.GetArray().shape());
    data_ = data.GetArray();
  }

  //! Returns the number of stored elements.
  /*!
    \return Number of elements.
  */
  template<class T, int N, class TG>
  inline int Data<T, N, TG>::GetNbElements()
  {
    return data_.numElements();
  }

  //! Returns the number of stored elements.
  /*!
    \return Number of elements.
  */
  template<class T, int N, class TG>
  inline int Data<T, N, TG>::GetNbDim()
  {
    return N;
  }

  //! Returns length along dimension #i.
  /*!
    \param i dimension number.
    \return Length along the i-th dimension.
  */
  template<class T, int N, class TG>
  inline int Data<T, N, TG>::GetLength(int i)
  {
    if ((i>=0) && (i<N))
      return data_.extent(i);
    else
      return 0;
  }

  //! Returns a pointer to the grid #i.
  /*!
    \param i grid to be returned.
    \return A pointer to the grid #i.
  */
  template<class T, int N, class TG>
  inline Grid<TG>* Data<T, N, TG>::GetGrid(int i)
  {
    return grids_(i);
  }

  //! Returns a reference to the grid #i.
  /*!
    \param i grid to be returned.
    \return A reference to the grid #i.
  */
  template<class T, int N, class TG>
  inline Grid<TG>& Data<T, N, TG>::operator[] (int i)
  {
    return *grids_(i);
  }

  //! Returns the array of pointers to grids.
  /*!
    For every Data, an array gathers pointers to grids.
    The i-th element of the array is the grid related to
    dimension #i.
    \return A reference to the array of pointers to grids.
  */
  template<class T, int N, class TG>
  inline Array<Grid<TG>*, 1>& Data<T, N, TG>::GetGrids()
  {
    return grids_;
  }

  //! Returns the blitz::Array storing elements.
  /*!
    \return A reference to the blitz::Array storing data.
  */
  template<class T, int N, class TG>
  inline Array<T, N>& Data<T, N, TG>::GetArray()
  {
    return data_;
  }

  //! Returns the array storing elements.
  /*!
    \return A reference to the array storing data.
  */
  template<class T, int N, class TG>
  inline T* Data<T, N, TG>::GetData()
  {
    return data_.data();
  }

  //! Extracts data.
  /*!
    Current data (*this) is set to a sub-data of 'data'.
    \param data source data.
    \param r0 range for dimension #0 (source).
  */
  template<class T, int N, class TG>
  template<class DTG, class R0>
  void Data<T, N, TG>::SubData(Data<T, 1, DTG>& data, R0 r0)
  {
    Array<T, 1>& array = data.GetArray();
    this->data_ = array(r0);
  }

  //! Extracts data.
  /*!
    Current data (*this) is set to a sub-data of 'data'.
    \param data source data.
    \param r0 range for dimension #0 (source).
    \param r1 range for dimension #1 (source).
  */
  template<class T, int N, class TG>
  template<class DTG, class R0, class R1>
  void Data<T, N, TG>::SubData(Data<T, 2, DTG>& data, R0 r0, R1 r1)
  {
    Array<T, 2>& array = data.GetArray();
    this->data_ = array(r0, r1);
  }

  //! Extracts data.
  /*!
    Current data (*this) is set to a sub-data of 'data'.
    \param data source data.
    \param r0 range for dimension #0 (source).
    \param r1 range for dimension #1 (source).
    \param r2 range for dimension #2 (source).
  */
  template<class T, int N, class TG>
  template<class DTG, class R0, class R1, class R2>
  void Data<T, N, TG>::SubData(Data<T, 3, DTG>& data, R0 r0, R1 r1, R2 r2)
  {
    Array<T, 3>& array = data.GetArray();
    this->data_ = array(r0, r1, r2);
  }

  //! Extracts data.
  /*!
    Current data (*this) is set to a sub-data of 'data'.
    \param data source data.
    \param r0 range for dimension #0 (source).
    \param r1 range for dimension #1 (source).
    \param r2 range for dimension #2 (source).
    \param r3 range for dimension #3 (source).
  */
  template<class T, int N, class TG>
  template<class DTG, class R0, class R1, class R2,
    class R3>
  void Data<T, N, TG>::SubData(Data<T, 4, DTG>& data, R0 r0, R1 r1, R2 r2,
			       R3 r3)
  {
    Array<T, 4>& array = data.GetArray();
    this->data_ = array(r0, r1, r2,
			r3);
  }

  //! Extracts data.
  /*!
    Current data (*this) is set to a sub-data of 'data'.
    \param data source data.
    \param r0 range for dimension #0 (source).
    \param r1 range for dimension #1 (source).
    \param r2 range for dimension #2 (source).
    \param r3 range for dimension #3 (source).
    \param r4 range for dimension #4 (source).
  */
  template<class T, int N, class TG>
  template<class DTG, class R0, class R1, class R2,
    class R3, class R4>
  void Data<T, N, TG>::SubData(Data<T, 5, DTG>& data, R0 r0, R1 r1, R2 r2,
			       R3 r3, R4 r4)
  {
    Array<T, 5>& array = data.GetArray();
    this->data_ = array(r0, r1, r2,
			r3, r4);
  }

  //! Extracts data.
  /*!
    Current data (*this) is set to a sub-data of 'data'.
    \param data source data.
    \param r0 range for dimension #0 (source).
    \param r1 range for dimension #1 (source).
    \param r2 range for dimension #2 (source).
    \param r3 range for dimension #3 (source).
    \param r4 range for dimension #4 (source).
    \param r5 range for dimension #5 (source).
  */
  template<class T, int N, class TG>
  template<class DTG, class R0, class R1, class R2,
    class R3, class R4, class R5>
  void Data<T, N, TG>::SubData(Data<T, 6, DTG>& data, R0 r0, R1 r1, R2 r2,
			       R3 r3, R4 r4, R5 r5)
  {
    Array<T, 6>& array = data.GetArray();
    this->data_ = array(r0, r1, r2,
			r3, r4, r5);
  }

  //! Extracts data.
  /*!
    Current data (*this) is set to a sub-data of 'data'.
    \param data source data.
    \param r0 range for dimension #0 (source).
    \param r1 range for dimension #1 (source).
    \param r2 range for dimension #2 (source).
    \param r3 range for dimension #3 (source).
    \param r4 range for dimension #4 (source).
    \param r5 range for dimension #5 (source).
    \param r6 range for dimension #6 (source).
  */
  template<class T, int N, class TG>
  template<class DTG, class R0, class R1, class R2,
    class R3, class R4, class R5,
    class R6>
  void Data<T, N, TG>::SubData(Data<T, 7, DTG>& data, R0 r0, R1 r1, R2 r2,
			       R3 r3, R4 r4, R5 r5, R6 r6)
  {
    Array<T, 7>& array = data.GetArray();
    this->data_ = array(r0, r1, r2,
			r3, r4, r5, r6);
  }

  //! Extracts data.
  /*!
    Current data (*this) is set to a sub-data of 'data'.
    \param data source data.
    \param r0 range for dimension #0 (source).
    \param r1 range for dimension #1 (source).
    \param r2 range for dimension #2 (source).
    \param r3 range for dimension #3 (source).
    \param r4 range for dimension #4 (source).
    \param r5 range for dimension #5 (source).
    \param r6 range for dimension #6 (source).
    \param r7 range for dimension #7 (source).
  */
  template<class T, int N, class TG>
  template<class DTG, class R0, class R1, class R2,
    class R3, class R4, class R5,
    class R6, class R7>
  void Data<T, N, TG>::SubData(Data<T, 8, DTG>& data, R0 r0, R1 r1, R2 r2,
			       R3 r3, R4 r4, R5 r5, R6 r6,
			       R7 r7)
  {
    Array<T, 8>& array = data.GetArray();
    this->data_ = array(r0, r1, r2,
			r3, r4, r5, r6,
			r7);
  }

  //! Extracts data.
  /*!
    Current data (*this) is set to a sub-data of 'data'.
    \param data source data.
    \param r0 range for dimension #0 (source).
    \param r1 range for dimension #1 (source).
    \param r2 range for dimension #2 (source).
    \param r3 range for dimension #3 (source).
    \param r4 range for dimension #4 (source).
    \param r5 range for dimension #5 (source).
    \param r6 range for dimension #6 (source).
    \param r7 range for dimension #7 (source).
    \param r8 range for dimension #8 (source).
  */
  template<class T, int N, class TG>
  template<class DTG, class R0, class R1, class R2,
    class R3, class R4, class R5,
    class R6, class R7, class R8>
  void Data<T, N, TG>::SubData(Data<T, 9, DTG>& data, R0 r0, R1 r1, R2 r2,
			       R3 r3, R4 r4, R5 r5, R6 r6,
			       R7 r7, R8 r8)
  {
    Array<T, 9>& array = data.GetArray();
    this->data_ = array(r0, r1, r2,
			r3, r4, r5, r6,
			r7, r8);
  }

  //! Extracts data.
  /*!
    Current data (*this) is set to a sub-data of 'data'.
    \param data source data.
    \param r0 range for dimension #0 (source).
    \param r1 range for dimension #1 (source).
    \param r2 range for dimension #2 (source).
    \param r3 range for dimension #3 (source).
    \param r4 range for dimension #4 (source).
    \param r5 range for dimension #5 (source).
    \param r6 range for dimension #6 (source).
    \param r7 range for dimension #7 (source).
    \param r8 range for dimension #8 (source).
    \param r9 range for dimension #9 (source).
  */
  template<class T, int N, class TG>
  template<class DTG, class R0, class R1, class R2,
    class R3, class R4, class R5,
    class R6, class R7, class R8, class R9>
  void Data<T, N, TG>::SubData(Data<T, 10, DTG>& data, R0 r0, R1 r1, R2 r2,
			       R3 r3, R4 r4, R5 r5, R6 r6,
			       R7 r7, R8 r8, R9 r9)
  {
    Array<T, 10>& array = data.GetArray();
    this->data_ = array(r0, r1, r2,
			r3, r4, r5, r6,
			r7, r8, r9);
  }

  //! Applies a given function on all elements.
  /*!
    \param function function to be applied.
  */
  template<class T, int N, class TG>
  void Data<T, N, TG>::Apply(void function(T&))
  {
    T* data = data_.data();
    int NbElements = data_.numElements();
    
    for (int i=0; i<NbElements; i++)
      function(data[i]);
  }

  //! Applies a given function on all elements.
  /*!
    \param function function to be applied.
  */
  template<class T, int N, class TG>
  template<class F>
  void Data<T, N, TG>::Apply(F& function)
  {
    T* data = data_.data();
    int NbElements = data_.numElements();
    
    for (int i=0; i<NbElements; i++)
      function.Apply(data[i]);
  }

  //! Sets data to zero.
  template<class T, int N, class TG>
  void Data<T, N, TG>::SetZero()
  {
    T* data = data_.data();
    int NbElements = data_.numElements();
    
    for (int i=0; i<NbElements; i++)
      data[i] = T(0);
  }

  //! Is data equal to zero?
  /*!
    \return true if data is zero, false otherwise.
  */
  template<class T, int N, class TG>
  bool Data<T, N, TG>::IsZero()
  {
    bool res = true;

    T* data = data_.data();
    int NbElements = data_.numElements();
    
    for (int i=0; i<NbElements; i++)
      res = res && (data[i] == T(0));

    return res;
  }

  //! Change coordinates.
  /*!
    The coordinates transformation is provided by function
    f. f takes as input old coordinates and new coordinates (in this
    order). Old coordinates are assumed to be unchanged by f.
    \param f coordinates transformation. It must be an instance of
    FuncCoords_Base<TG> or of a class derived from FuncCoords_Base<TG>.
  */
  template<class T, int N, class TG>
  void Data<T, N, TG>::ChangeCoords(FuncCoords_Base<TG>& f)
  {
    
    int i;
    int i0, i1, i2, i3, i4, i5, i6, i7, i8, i9;

    Array<Grid<TG>*, 1> grids(N);
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

  //! Coordinate transformation "in place".
  /*!
    Function f takes as inputs all coordinates and transforms those coordinates.
    This transformation is performed in place because function f works directly
    on its inputs.
    \param f coordinate transformation. It must be an instance of
    Function_Base<TG> or of a class derived from Function_Base<TG>.
    \warning One should use ChangeCoords instead of ChangeCoordsInPlace in order
    to save memory.
  */
  template<class T, int N, class TG>
  void Data<T, N, TG>::ChangeCoordsInPlace(Function_Base<TG>& f)
  {

    int i, j;
    int NbGrids = grids_.numElements();
    Array<Grid<TG>*, 1> grids_old(NbGrids),
      grids(NbGrids);

    Grid<TG>* old_grid;

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

  //! Displays data.
  template<class T, int N, class TG>
  void Data<T, N, TG>::Print()
  {
    cout << data_ << endl;
  }

  //! For every grid, sets dimension to which the grid is related.
  template<class T, int N, class TG>
  void Data<T, N, TG>::SetVariables()
  {
    for (int i=0; i<N; i++)
      grids_(i)->SetVariable(i);
  }

}  // namespace SeldonData.


#define FILE_SELDONDATA_DATA_CXX
#endif
