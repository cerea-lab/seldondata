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
  // REGULAR //

  //! Linear interpolation for data defined on regular grids.
  /*!
    Linear interpolation from data defined on regular grids to
    data defined on regular grids.
    \param dataIn reference data.
    \param dataOut interpolated data (on exit).
  */
  template<int N, class TIn, class TGIn,
	   class TOut, class TGOut>
  void LinearInterpolationRegular(Data<TIn, N, TGIn>& dataIn,
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

  // REGULAR //
  /////////////


  ////////////////////////
  // UNIFORM TO GENERAL //

  //! Linear interpolation from data defined on uniform grids
  //! to data defined on any grid.
  /*! Linear interpolation from an input data defined on uniform grids only
    to an output data defined on any type of grids. Uniform grids are
    regular grids with fixed steps.
    \param dataIn reference data defined on uniform grids.
    \param dataOut interpolated data (on exit) defined on any type of grids.
  */
  template<int N, class TIn, class TGIn,
	   class TOut, class TGOut>
  void LinearInterpolationUniformToGeneral(Data<TIn, N, TGIn>& dataIn,
					   Data<TOut, N, TGOut>& dataOut)
  {
    
    int i, j, k, l, m;
    Array<int, 1> IndexIn(10), IndexOut(10);
    Array<int, 1> LengthIn(10), LengthOut(10);
    Array<TIn, 1> MinIn(10), DeltaIn(10), Coeff(10);
    Array<bool, 1> Pos(N);
    TIn coord_out, coord_in, coeff;

    for (i=0; i<10; i++)
      {
	LengthIn(i) = dataIn.GetLength(i);
	LengthOut(i) = dataOut.GetLength(i);
	Coeff(i) = 0;
	IndexOut(i) = 0;
	IndexIn(i) = 0;
      }

    for (i=0; i<N; i++)
      {
	MinIn(i) = dataIn[i](0);
	DeltaIn(i) = dataIn[i](1) - dataIn[i](0);
      }

    j = N-1;
    for (i=0; i<dataOut.GetNbElements(); i++)
      {

	for (k=0; k<N; k++)
	  {
	    coord_out = dataOut[k].Value(IndexOut(0), IndexOut(1), IndexOut(2),
					 IndexOut(3), IndexOut(4), IndexOut(5),
					 IndexOut(6), IndexOut(7), IndexOut(8),
					 IndexOut(9));
	    l = (coord_out - MinIn(k)) / DeltaIn(k);
	    l = l<1? 1 : l;
	    l = l<LengthIn(k)? l : (LengthIn(k)-1);
	    IndexIn(k) = l;

	    coord_in = MinIn(k) + TIn(l-1) * DeltaIn(k);
	    Coeff(k) = ( coord_out - coord_in ) / DeltaIn(k);
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
	    j--;
	  }
	IndexOut(j)++;

      }

  }

  // UNIFORM TO GENERAL //
  ////////////////////////


  ////////////////
  // ONEGENERAL //

  //! Linear interpolation for data defined on regular grids,
  //! but one grid.
  /*!
    Performs linear interpolation on data defined on regular grids,
    except one grid which may be a general grid (i.e. depending on other coordinates).
    Both input and output data may be defined on a general grid along
    dimension 'dim', but only along this dimension. Moreover, input data or
    output data can still be defined on regular grids along dimension 'dim'.
    \param dataIn reference data.
    \param dataOut interpolated data (on exit).
    \param dim dimension related to the general grid.
  */
  template<int N, class TIn, class TGIn,
	   class TOut, class TGOut>
  void LinearInterpolationOneGeneral(Data<TIn, N, TGIn>& dataIn,
				     Data<TOut, N, TGOut>& dataOut,
				     int dim)
  {
    
    int i, j, k, l, m;
    Array<int, 1> IndexIn(10), IndexIn0(10), IndexOut(10);
    Array<int, 1> LengthIn(10), LengthOut(10);
    Array<TIn, 1> Coeff(10), Coeff0(10);
    TIn temp;
    Array<bool, 1> Pos(N), Pos_dim(N);
    TIn coeff;

    dataOut.SetZero();

    for (i=0; i<10; i++)
      if ((i<N)&&(i!=dim))
	{
	  LengthIn(i) = dataIn.GetLength(i);
	  LengthOut(i) = dataOut.GetLength(i);
	  IndexOut(i) = 0;
	  IndexIn(i) = 1;
	  while ( (IndexIn(i)<LengthIn(i)-1)
		  && (dataIn[i](IndexIn(i))<dataOut[i](0)) )
	    IndexIn(i)++;
	  IndexIn0(i) = IndexIn(i);
	  Coeff0(i) = ( dataOut[i](0) - dataIn[i](IndexIn(i)-1) ) /
	    ( dataIn[i](IndexIn(i)) - dataIn[i](IndexIn(i)-1) );
	  Coeff(i) = Coeff0(i);
	}
      else
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

	if (j!=dim)
	  {
	    while ( (IndexIn(j)<LengthIn(j)-1)
		    && (dataIn[j](IndexIn(j))
			< dataOut[j](IndexOut(j))) )
	      IndexIn(j)++;
		
	    Coeff(j) = ( dataOut[j](IndexOut(j)) - dataIn[j](IndexIn(j)-1) ) /
	      ( dataIn[j](IndexIn(j)) - dataIn[j](IndexIn(j)-1) );
	  }

	for (k=0; k<int(pow(2.0, double(N))+0.5); k++)
	  {

	    l = k;
	    for (m=0; m<N; m++)
	      {
		Pos_dim(m) = l%2;
		l = l/2;
	      }
	    Pos_dim(dim) = 0;

	    IndexIn(dim) = 1;
	    while ( (IndexIn(dim)<LengthIn(dim)-1)
		    && (dataIn[dim].Value(IndexIn(0) - Pos_dim(0), IndexIn(1) - Pos_dim(1),
					  IndexIn(2) - Pos_dim(2), IndexIn(3) - Pos_dim(3),
					  IndexIn(4) - Pos_dim(4), IndexIn(5) - Pos_dim(5),
					  IndexIn(6) - Pos_dim(6), IndexIn(7) - Pos_dim(7),
					  IndexIn(8) - Pos_dim(8), IndexIn(9) - Pos_dim(9))
			< dataOut[dim].Value(IndexOut(0), IndexOut(1),
					     IndexOut(2), IndexOut(3),
					     IndexOut(4), IndexOut(5),
					     IndexOut(6), IndexOut(7),
					     IndexOut(8), IndexOut(9))) )
	      IndexIn(dim)++;
	    
	    IndexIn(dim)--;
	    temp = dataIn[dim].Value(IndexIn(0) - Pos_dim(0), IndexIn(1) - Pos_dim(1),
				     IndexIn(2) - Pos_dim(2), IndexIn(3) - Pos_dim(3),
				     IndexIn(4) - Pos_dim(4), IndexIn(5) - Pos_dim(5),
				     IndexIn(6) - Pos_dim(6), IndexIn(7) - Pos_dim(7),
				     IndexIn(8) - Pos_dim(8), IndexIn(9) - Pos_dim(9));
	    IndexIn(dim)++;

	    Coeff(dim) = ( dataOut[dim].Value(IndexOut(0), IndexOut(1),
					      IndexOut(2), IndexOut(3),
					      IndexOut(4), IndexOut(5),
					      IndexOut(6), IndexOut(7),
					      IndexOut(8), IndexOut(9))
			   - temp ) /
	      ( dataIn[dim].Value(IndexIn(0) - Pos_dim(0), IndexIn(1) - Pos_dim(1),
				  IndexIn(2) - Pos_dim(2), IndexIn(3) - Pos_dim(3),
				  IndexIn(4) - Pos_dim(4), IndexIn(5) - Pos_dim(5),
				  IndexIn(6) - Pos_dim(6), IndexIn(7) - Pos_dim(7),
				  IndexIn(8) - Pos_dim(8), IndexIn(9) - Pos_dim(9)) - temp );

	    l = k;
	    coeff = TIn(1);
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

  // ONEGENERAL //
  ////////////////


  ///////////////
  // DIMENSION //

  //! Linear interpolation along a given dimension.
  /*!
    Linear interpolation only along a given dimension.
    \param dataIn reference data.
    \param dataOut interpolated data (on exit).
  */
  template<int N, class TIn, class TGIn,
	   class TOut, class TGOut>
  void LinearInterpolationDimension(Data<TIn, N, TGIn>& dataIn,
				    Data<TOut, N, TGOut>& dataOut, int dim)
  {
    
    int i, j, k, l, m;
    Array<int, 1> IndexIn(10), IndexOut(10);
    Array<int, 1> Length(10);
    TIn coeff, coord;
    int Ndim_in, Ndim_out;

    for (i=0; i<10; i++)
      {
	Length(i) = dataOut.GetLength(i);
	IndexOut(i) = 0;
	IndexIn(i) = 0;
      }

#ifdef DEBUG_SELDONDATA_DIMENSION
    // Checks whether dimensions match.
    for (i=0; i<10; i++)
      if ((i!=dim) && (Length(i) != dataIn.GetLength(i)))
	throw WrongDim("LinearInterpolationDimension(Data&, Data&, " + to_str(dim) + ")",
		       "Along dimension #" + to_str(i) + ", input data has "
		       + to_str(dataIn.GetLength(i)) + " elements and ouput data"
		       + " has " + to_str(Length(i)) + " elements. There must be the same"
		       + " number of elements.");
#endif

    Ndim_in = dataIn.GetLength(dim);
    Ndim_out = dataOut.GetLength(dim);

    for (i=0; i<dataOut.GetNbElements() / Ndim_out; i++)
      {

	IndexIn(dim) = 1;
	for (k=0; k<Ndim_out; k++)
	  {
	    IndexOut(dim) = k;
	    coord = dataOut[dim].Value(IndexOut(0), IndexOut(1), IndexOut(2),
				       IndexOut(3), IndexOut(4), IndexOut(5),
				       IndexOut(6), IndexOut(7), IndexOut(8),
				       IndexOut(9));
	    while ( (IndexIn(dim)<Ndim_in)
		    && (dataIn[dim].Value(IndexIn(0), IndexIn(1), IndexIn(2),
					  IndexIn(3), IndexIn(4), IndexIn(5),
					  IndexIn(6), IndexIn(7), IndexIn(8),
					  IndexIn(9)) < coord) )
	      IndexIn(dim)++;

	    if (IndexIn(dim)==Ndim_in)
	      IndexIn(dim) = Ndim_in-1;

	    IndexIn(dim)--;
	    coord = dataIn[dim].Value(IndexIn(0), IndexIn(1), IndexIn(2),
				      IndexIn(3), IndexIn(4), IndexIn(5),
				      IndexIn(6), IndexIn(7), IndexIn(8),
				      IndexIn(9));
	    IndexIn(dim)++;

	    coeff = ( dataOut[dim].Value(IndexOut(0), IndexOut(1), IndexOut(2),
					 IndexOut(3), IndexOut(4), IndexOut(5),
					 IndexOut(6), IndexOut(7), IndexOut(8),
					 IndexOut(9)) - coord )
	      / ( dataIn[dim].Value(IndexIn(0), IndexIn(1), IndexIn(2),
				    IndexIn(3), IndexIn(4), IndexIn(5),
				    IndexIn(6), IndexIn(7), IndexIn(8),
				    IndexIn(9)) - coord );

	    dataOut.Value(IndexOut(0), IndexOut(1), IndexOut(2),
			  IndexOut(3), IndexOut(4), IndexOut(5),
			  IndexOut(6), IndexOut(7), IndexOut(8),
			  IndexOut(9)) =
	      coeff * dataIn.Value(IndexIn(0), IndexIn(1), IndexIn(2),
				   IndexIn(3), IndexIn(4), IndexIn(5),
				   IndexIn(6), IndexIn(7), IndexIn(8),
				   IndexIn(9));

	    IndexIn(dim)--;
	    dataOut.Value(IndexOut(0), IndexOut(1), IndexOut(2),
			  IndexOut(3), IndexOut(4), IndexOut(5),
			  IndexOut(6), IndexOut(7), IndexOut(8),
			  IndexOut(9)) +=
	      (TIn(1.0) - coeff) * dataIn.Value(IndexIn(0), IndexIn(1), IndexIn(2),
						IndexIn(3), IndexIn(4), IndexIn(5),
						IndexIn(6), IndexIn(7), IndexIn(8),
						IndexIn(9));
	    IndexIn(dim)++;
	  }

	j = N-1;
	while ( (j>=0) && ((IndexOut(j)==Length(j)-1) || (j==dim)) )
	  {
	    IndexOut(j) = 0;
	    IndexIn(j) = 0;
	    j--;
	  }
	IndexOut(j)++;
	IndexIn(j)++;

      }

  }

  // DIMENSION //
  ///////////////


}  // namespace SeldonData.

#define FILE_SELDONDATA_FUNCTIONS_CXX
#endif
