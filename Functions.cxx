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

#ifndef FILE_SELDONDATA_FUNCTIONS_CXX

#include "Functions.hxx"
#include "stdio.h"

namespace SeldonData
{

  /////////////
  // UNIFORM //

  //! Linear interpolation for data defined on regular grids.
  /*!
    \param dataIn reference data.
    \param dataOut interpolated data (on exit).
   */
  template<int N, class TIn, class TGIn,
    class TOut, class TGOut>
  void LinearInterpolation(Data<TIn, N, TGIn>& dataIn,
			   Data<TOut, N, TGOut>& dataOut)
  {
    
    int i, j, k, l, m;
    Array<int, 1> IndexIn(10), IndexIn0(10), IndexOut(10);
    Array<int, 1> LengthIn(10), LengthOut(10);
    Array<TIn, 1> Coeff(10), Coeff0(10);
    Array<bool, 1> Pos(N);
    TIn coeff;

    for (i=0; i<10; i++)
      {
	LengthIn(i) = dataIn.GetLength(i);
	LengthOut(i) = dataOut.GetLength(i);
	IndexOut(i) = 0;
	IndexIn(i) = 0;
	while ( (IndexIn(i)<LengthIn(i))
		&& (dataIn[i](IndexIn(i))<dataOut[i](0)) )
	  IndexIn(i)++;
	if (IndexIn(i)==LengthIn(i))
	  IndexIn(i) = LengthIn(i)-1;
	else if (IndexIn(i)==0)
	  IndexIn(i) = 1;
	IndexIn0(i) = IndexIn(i);
	if (LengthIn(i)!=0)
	  Coeff0(i) = ( dataOut[i](0) - dataIn[i](IndexIn(i)-1) ) /
	    ( dataIn[i](IndexIn(i)) - dataIn[i](IndexIn(i)-1) );
	else
	  Coeff0(i) = TIn(0);
	Coeff(i) = Coeff0(i);
      }

    j = N-1;
    for (i=0; i<dataOut.GetNbElements(); i++)
      {

	while ( (IndexIn(j)<LengthIn(j))
		&& (dataIn[j](IndexIn(j))<dataOut[j](IndexOut(j))) )
	  IndexIn(j)++;

	if (IndexIn(j)==LengthIn(j))
	  IndexIn(j) = LengthIn(j)-1;
	else if (IndexIn(j)==0)
	  IndexIn(j) = 1;

	Coeff(j) = ( dataOut[j](IndexOut(j)) - dataIn[j](IndexIn(j)-1) ) /
	  ( dataIn[j](IndexIn(j)) - dataIn[j](IndexIn(j)-1) );

	dataOut.Value(IndexOut(0), IndexOut(1), IndexOut(2),
		      IndexOut(3), IndexOut(4), IndexOut(5),
		      IndexOut(6), IndexOut(7), IndexOut(8),
		      IndexOut(9)) = TOut(0);


	for (k=0; k<int(pow(2.0, double(N))); k++)
	  {
	    l = k; coeff = TIn(1);
	    for (m=0; m<N; m++)
	      {
		Pos(m) = l%2;
		if (l%2 == 1)
		  coeff *= TIn(1) - Coeff(m);
		else
		  coeff *= Coeff(m);
		l = l/2;
	      }

	    dataOut.Value(IndexOut(0), IndexOut(1), IndexOut(2),
			  IndexOut(3), IndexOut(4), IndexOut(5),
			  IndexOut(6), IndexOut(7), IndexOut(8),
			  IndexOut(9)) +=
	      TOut( coeff *
		    dataIn.Value(IndexIn(0) - Pos(0),
				 IndexIn(1) - Pos(1),
				 IndexIn(2) - Pos(2),
				 IndexIn(3) - Pos(3),
				 IndexIn(4) - Pos(4),
				 IndexIn(5) - Pos(5),
				 IndexIn(6) - Pos(6),
				 IndexIn(7) - Pos(7),
				 IndexIn(8) - Pos(8),
				 IndexIn(9) - Pos(9)) );

	  }

	j = N-1;
	while ( (j>=0) && (IndexOut(j)==LengthOut(j)-1) )
	  {
	    IndexOut(j) = 0;
	    IndexIn(j) = IndexIn0(j);
	    Coeff(j) = Coeff0(j);
	    j--;
	  }
	if (j!=-1)
	  IndexOut(j)++;

      }

  }

  // UNIFORM //
  /////////////

  //////////
  // LAST //

  //! Linear interpolation for data defined on regular grids,
  //! but the last grid.
  /*!
    Performs linear interpolation on data defined on regular grids,
    except the last grid (the grid related to the last dimension)
    which may be a general grid (i.e. depending on other coordinates).
    \param dataIn reference data.
    \param dataOut interpolated data (on exit).
   */
  template<int N, class TIn, class TGIn,
    class TOut, class TGOut>
  void LinearInterpolationLast(Data<TIn, N, TGIn>& dataIn,
			       Data<TOut, N, TGOut>& dataOut)
  {
    
    int i, j, k, l, m;
    Array<int, 1> IndexIn(10), IndexIn0(10), IndexOut(10);
    Array<int, 1> LengthIn(10), LengthOut(10);
    Array<TIn, 1> Coeff(10), Coeff0(10);
    TIn temp;
    Array<bool, 1> Pos(N);
    TIn coeff;

    for (i=0; i<N-1; i++)
      {
	LengthIn(i) = dataIn.GetLength(i);
	LengthOut(i) = dataOut.GetLength(i);
	IndexOut(i) = 0;
	IndexIn(i) = 0;
	while ( (IndexIn(i)<LengthIn(i))
		&& (dataIn[i](IndexIn(i))<dataOut[i](0)) )
	  IndexIn(i)++;
	if (IndexIn(i)==LengthIn(i))
	  IndexIn(i) = LengthIn(i)-1;
	else if (IndexIn(i)==0)
	  IndexIn(i) = 1;
	IndexIn0(i) = IndexIn(i);
	if (LengthIn(i)!=0)
	  Coeff0(i) = ( dataOut[i](0) - dataIn[i](IndexIn(i)-1) ) /
	    ( dataIn[i](IndexIn(i)) - dataIn[i](IndexIn(i)-1) );
	else
	  Coeff0(i) = TIn(0);
	Coeff(i) = Coeff0(i);
      }

    for (i=N-1; i<10; i++)
      {
	LengthIn(i) = dataIn.GetLength(i);
	LengthOut(i) = dataOut.GetLength(i);
	IndexOut(i) = 0;
	IndexIn(i) = 0;
	Coeff0(i) = 0;
	Coeff(i) = 0;
      }

    j = N-1;
    for (i=0; i<dataOut.GetNbElements(); i++)
      {

	if (j!=N-1)
	  {
	    while ( (IndexIn(j)<LengthIn(j))
		    && (dataIn[j].Value(IndexIn(0), IndexIn(1),
					IndexIn(2), IndexIn(3),
					IndexIn(4), IndexIn(5),
					IndexIn(6), IndexIn(7),
					IndexIn(8), IndexIn(9))
			< dataOut[j].Value(IndexOut(0), IndexOut(1),
					   IndexOut(2), IndexOut(3),
					   IndexOut(4), IndexOut(5),
					   IndexOut(6), IndexOut(7),
					   IndexOut(8), IndexOut(9))) )
	      IndexIn(j)++;
		
	    if (IndexIn(j)==LengthIn(j))
	      IndexIn(j) = LengthIn(j)-1;
	    else if (IndexIn(j)==0)
	      IndexIn(j) = 1;
		
	    Coeff(j) = ( dataOut[j](IndexOut(j)) - dataIn[j](IndexIn(j)-1) ) /
	      ( dataIn[j](IndexIn(j)) - dataIn[j](IndexIn(j)-1) );
	  }

	while ( (IndexIn(N-1)<LengthIn(N-1))
		&& (dataIn[N-1].Value(IndexIn(0), IndexIn(1),
				      IndexIn(2), IndexIn(3),
				      IndexIn(4), IndexIn(5),
				      IndexIn(6), IndexIn(7),
				      IndexIn(8), IndexIn(9))
		    < dataOut[N-1].Value(IndexOut(0), IndexOut(1),
					 IndexOut(2), IndexOut(3),
					 IndexOut(4), IndexOut(5),
					 IndexOut(6), IndexOut(7),
					 IndexOut(8), IndexOut(9))) )
	  IndexIn(N-1)++;
	    
	if (IndexIn(N-1)==LengthIn(N-1))
	  IndexIn(N-1) = LengthIn(N-1)-1;
	else if (IndexIn(N-1)==0)
	  IndexIn(N-1) = 1;

	IndexIn(N-1)--;
	temp = dataIn[N-1].Value(IndexIn(0), IndexIn(1),
				 IndexIn(2), IndexIn(3),
				 IndexIn(4), IndexIn(5),
				 IndexIn(6), IndexIn(7),
				 IndexIn(8), IndexIn(9));
	IndexIn(N-1)++;

	Coeff(N-1) = ( dataOut[N-1].Value(IndexOut(0), IndexOut(1),
					  IndexOut(2), IndexOut(3),
					  IndexOut(4), IndexOut(5),
					  IndexOut(6), IndexOut(7),
					  IndexOut(8), IndexOut(9))
		       - temp ) /
	  ( dataIn[N-1].Value(IndexIn(0), IndexIn(1),
			      IndexIn(2), IndexIn(3),
			      IndexIn(4), IndexIn(5),
			      IndexIn(6), IndexIn(7),
			      IndexIn(8), IndexIn(9)) - temp );

	dataOut.Value(IndexOut(0), IndexOut(1), IndexOut(2),
		      IndexOut(3), IndexOut(4), IndexOut(5),
		      IndexOut(6), IndexOut(7), IndexOut(8),
		      IndexOut(9)) = TOut(0);

	for (k=0; k<int(pow(2.0, double(N))); k++)
	  {
	    l = k; coeff = TIn(1);
	    for (m=0; m<N; m++)
	      {
		Pos(m) = l%2;
		if (l%2 == 1)
		  coeff *= TIn(1) - Coeff(m);
		else
		  coeff *= Coeff(m);
		l = l/2;
	      }

	    dataOut.Value(IndexOut(0), IndexOut(1), IndexOut(2),
			  IndexOut(3), IndexOut(4), IndexOut(5),
			  IndexOut(6), IndexOut(7), IndexOut(8),
			  IndexOut(9)) +=
	      TOut( coeff *
		    dataIn.Value(IndexIn(0) - Pos(0),
				 IndexIn(1) - Pos(1),
				 IndexIn(2) - Pos(2),
				 IndexIn(3) - Pos(3),
				 IndexIn(4) - Pos(4),
				 IndexIn(5) - Pos(5),
				 IndexIn(6) - Pos(6),
				 IndexIn(7) - Pos(7),
				 IndexIn(8) - Pos(8),
				 IndexIn(9) - Pos(9)) );

	  }

	j = N-1;
	while ( (j>=0) && (IndexOut(j)==LengthOut(j)-1) )
	  {
	    IndexOut(j) = 0;
	    IndexIn(j) = IndexIn0(j);
	    Coeff(j) = Coeff0(j);
	    j--;
	  }
	if (j!=-1)
	  IndexOut(j)++;

      }

  }

  // LAST //
  //////////


  /////////////
  // GENERAL //

  //! Linear interpolation for any kind of data.
  /*!
    \param dataIn reference data.
    \param dataOut interpolated data (on exit).
   */
  template<int N, class TIn, class TGIn,
    class TOut, class TGOut>
  void LinearInterpolationGeneral(Data<TIn, N, TGIn>& dataIn,
				  Data<TOut, N, TGOut>& dataOut)
  {
    
    int i, j, k, l, m, n;
    Array<int, 1> IndexIn(10), IndexIn0(10), IndexOut(10);
    Array<int, 1> LengthIn(10), LengthOut(10);
    Array<TIn, 1> Coeff(10), Coeff0(10);
    Array<bool, 1> Pos(N);
    TIn coeff;

    TOut dist;
    TOut dist_old, temp;

    Array<int, 1> ClosestPoint(N);

    for (i=0; i<10; i++)
      {
	LengthIn(i) = dataIn.GetLength(i);
	LengthOut(i) = dataOut.GetLength(i);
	IndexOut(i) = 0;
	IndexOut(i) = 0;
      }

    j = N-1;
    for (i=0; i<dataOut.GetNbElements(); i++)
      {

	for (k=0; k<N; k++)
	  IndexIn(k) = 0;

	for (k=0; k<dataIn.GetNbElements(); k++)
	  {

	    dist = TOut(0);
	    for (m=0; m<N; m++)
	      {
		temp = dataIn[m].Value(IndexIn(0), IndexIn(1),
				       IndexIn(2), IndexIn(3),
				       IndexIn(4), IndexIn(5),
				       IndexIn(6), IndexIn(7),
				       IndexIn(8), IndexIn(9)) -
		  dataOut[m].Value(IndexOut(0), IndexOut(1),
				   IndexOut(2), IndexOut(3),
				   IndexOut(4), IndexOut(5),
				   IndexOut(6), IndexOut(7),
				   IndexOut(8), IndexOut(9));
		dist += temp * temp;
	      }

	    if ( (k==0) || (dist<dist_old) )
	      {
		dist_old = dist;
		for (n=0; n<N; n++)
		  ClosestPoint(n) = IndexIn(n);
	      }

	    l = N-1;
	    while ( (l>=0) && (IndexIn(l)==LengthIn(l)-1) )
	      {
		IndexIn(l) = 0;
		l--;
	      }
	    if (l!=-1)
	      IndexIn(l)++;

	  }

	for (k=0; k<N; k++)
	  {

	    IndexIn(k) = ClosestPoint(k);

	    if (dataIn[k].Value(ClosestPoint(0), ClosestPoint(1),
				ClosestPoint(2), ClosestPoint(3),
				ClosestPoint(4), ClosestPoint(5),
				ClosestPoint(6), ClosestPoint(7),
				ClosestPoint(8), ClosestPoint(9)) -
		dataOut[k].Value(IndexOut(0), IndexOut(1), IndexOut(2),
				 IndexOut(3), IndexOut(4), IndexOut(5),
				 IndexOut(6), IndexOut(7), IndexOut(8),
				 IndexOut(9)) < 0)
	      IndexIn(k)++;

	    if (IndexIn(k)==0)
	      IndexIn(k) = 1;
	    else if (IndexIn(k)==LengthIn(k))
	      IndexIn(k) = LengthIn(k) - 1;
	    
	    IndexIn(k)--;
	    temp = dataIn[k].Value(IndexIn(0), IndexIn(1),
				   IndexIn(2), IndexIn(3),
				   IndexIn(4), IndexIn(5),
				   IndexIn(6), IndexIn(7),
				   IndexIn(8), IndexIn(9));
	    IndexIn(k)++;
	    
	    Coeff(k) = ( dataOut[k].Value(IndexOut(0), IndexOut(1),
					  IndexOut(2), IndexOut(3),
					  IndexOut(4), IndexOut(5),
					  IndexOut(6), IndexOut(7),
					  IndexOut(8), IndexOut(9))
			 - temp ) /
	      ( dataIn[k].Value(IndexIn(0), IndexIn(1),
				IndexIn(2), IndexIn(3),
				IndexIn(4), IndexIn(5),
				IndexIn(6), IndexIn(7),
				IndexIn(8), IndexIn(9)) - temp );
	    
	    dataOut.Value(IndexOut(0), IndexOut(1), IndexOut(2),
			  IndexOut(3), IndexOut(4), IndexOut(5),
			  IndexOut(6), IndexOut(7), IndexOut(8),
			  IndexOut(9)) = TOut(0);
	    
	  }

	dataOut.Value(IndexOut(0), IndexOut(1), IndexOut(2),
		      IndexOut(3), IndexOut(4), IndexOut(5),
		      IndexOut(6), IndexOut(7), IndexOut(8),
		      IndexOut(9)) = TOut(0);

	for (k=0; k<int(pow(2.0, double(N))); k++)
	  {
	    l = k; coeff = TIn(1);
	    for (m=0; m<N; m++)
	      {
		Pos(m) = l%2;
		if (l%2 == 1)
		  coeff *= TIn(1) - Coeff(m);
		else
		  coeff *= Coeff(m);
		l = l/2;
	      }

	    dataOut.Value(IndexOut(0), IndexOut(1), IndexOut(2),
			  IndexOut(3), IndexOut(4), IndexOut(5),
			  IndexOut(6), IndexOut(7), IndexOut(8),
			  IndexOut(9)) +=
	      TOut( coeff *
		    dataIn.Value(IndexIn(0) - Pos(0),
				 IndexIn(1) - Pos(1),
				 IndexIn(2) - Pos(2),
				 IndexIn(3) - Pos(3),
				 IndexIn(4) - Pos(4),
				 IndexIn(5) - Pos(5),
				 IndexIn(6) - Pos(6),
				 IndexIn(7) - Pos(7),
				 IndexIn(8) - Pos(8),
				 IndexIn(9) - Pos(9)) );

	  }

	j = N-1;
	while ( (j>=0) && (IndexOut(j)==LengthOut(j)-1) )
	  {
	    IndexOut(j) = 0;
	    IndexIn(j) = IndexIn0(j);
	    Coeff(j) = Coeff0(j);
	    j--;
	  }
	if (j!=-1)
	  IndexOut(j)++;

      }

  }

  // GENERAL //
  /////////////

}  // namespace SeldonData.

#define FILE_SELDONDATA_FUNCTIONS_CXX
#endif
