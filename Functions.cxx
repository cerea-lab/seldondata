#ifndef FILE_FUNCTIONS_CXX

#include "Functions.hxx"
#include "stdio.h"

namespace SeldonData
{

  /////////////
  // UNIFORM //

  template<class TIn, int N,
    class TOut>
  void LinearInterpolation(Data<TIn, N>& dataIn,
			   Data<TOut, N>& dataOut)
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

	if (j!=-1)
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

  }

  // UNIFORM //
  /////////////

  //////////
  // LAST //

  // The last coordinate depends upon other coordinates.
  template<class TIn, int N,
    class TOut>
  void LinearInterpolationLast(Data<TIn, N>& dataIn,
			       Data<TOut, N>& dataOut)
  {
    
    int i, j, k, l, m;
    Array<int, 1> IndexIn(10), IndexIn0(10), IndexOut(10);
    Array<int, 1> LengthIn(10), LengthOut(10);
    Array<TIn, 1> Coeff(10), Coeff0(10);
    Array<bool, 1> Pos(N);
    TIn coeff;

    for (i=0; i<N; i++)
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

	if (j!=-1)
	  {

	    while ( (IndexIn(j)<LengthIn(j))
		    && (dataIn[j](IndexIn(j))<dataOut[j](IndexOut(j))) )
	      IndexIn(j)++;

	    if (IndexIn(j)==LengthIn(j))
	      IndexIn(j) = LengthIn(j)-1;
	    else if (IndexIn(j)==0)
	      IndexIn(j) = 1;
	    /////// ------------- HERE	    
	    for (k=0; i<N; i++)
	      {
		IndexIn(k) = 0;
		while ( (IndexIn(k)<LengthIn(k))
			&& (dataIn[k](IndexIn(k))<dataOut[k](IndexOut(j))) )
		  IndexIn(i)++;
		if (IndexIn(i)==LengthIn(i))
		  IndexIn(i) = LengthIn(i)-1;
		else if (IndexIn(i)==0)
		  IndexIn(i) = 1;
	      }
	    /////// ------------- HERE	    

	    Coeff(j) = ( dataOut[j](IndexOut(j)) - dataIn[j](IndexIn(j)-1) ) /
	      ( dataIn[j](IndexIn(j)) - dataIn[j](IndexIn(j)-1) );

	    if (j!=N-1)
	      Coeff(N-1) = ( dataOut[N-1](IndexOut(N-1)) - dataIn[N-1](IndexIn(N-1)-1) ) /
		( dataIn[N-1](IndexIn(N-1)) - dataIn[N-1](IndexIn(N-1)-1) );

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

  }

  // LAST //
  //////////


  /////////////
  // GENERAL //

  // All coordinates depend upon all others.
  template<class TIn, int N,
    class TOut>
  void LinearInterpolationGeneral(Data<TIn, N>& dataIn,
				  Data<TOut, N>& dataOut)
  {
    
    int i, j, k, l, m, n;
    Array<int, 1> IndexIn(10), IndexIn0(10), IndexOut(10);
    Array<int, 1> LengthIn(10), LengthOut(10);
    Array<TIn, 1> Coeff(10), Coeff0(10);
    Array<bool, 1> Pos(N);
    TIn coeff;

    Array<int, 1> ClosestPoint(N);

    for (i=0; i<N; i++)
      {
	LengthIn(i) = dataIn.GetLength(i);
	LengthOut(i) = dataOut.GetLength(i);
	IndexOut(i) = 0;
      }

    for (k=0; k<N; k++)
      IndexOut(k) = 0;

    j = N-1;
    for (i=0; i<dataOut.GetNbElements(); i++)
      {

	for (k=0; k<N; k++)
	  IndexIn(k) = 0;

	TOut dist = TOut(0);
	TOut dist_old, temp;
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

	    if (dist<dist_old)
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

	    if (IndexIn(k)==0)
	      IndexIn(k)=1;
	    else if (IndexIn(k)==LengthIn(k)-1)
	      ;
	    else if (dataIn[k].Value(IndexIn(k)) -
		     dataOut[k].Value(IndexIn(k)) < 0)
	      IndexIn(k)++;

	    Coeff(k) = ( dataOut[k](IndexOut(k)) - dataIn[k](IndexIn(k)-1) ) /
	      ( dataIn[k](IndexIn(k)) - dataIn[k](IndexIn(k)-1) );

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


  ////////////////////////////////////////////////////////////////////////////////////


  //    template<class TU, class TV, class TW,
  //  	   class T>
  //    void LouisKz(Data<TU, 4>& U, Data<TV, 4>& V, Data<TW, 4>& W,
  //  	       Data<TTp, 4>& Tp, Data<T, 4>& Kz, T z0, T L,
  //  	       T Ka, T B, T C, T D)
  //    {

  //      int h, i, j, k;

  //      int Nx = W.GetLength(1);
  //      int Ny = W.GetLength(2);
  //      int Nz = W.GetLength(3);
  //      int Nt = min( min(U.GetLength(0), V.GetLength(0)), W.GetLength(0) );

  //      T L, l, R, F;
  //      T dWind_dz, derivative;
  //      T g = 9.81;

  //      Grid<T>& Levels = W.GetGrid(3);
  //      Grid<T>& Nodes = U.GetGrid(3);

  //      for (h=0; h<Nt; h++)
  //        for (i=0; i<Nx; i++)
  //  	for (j=0; j<Ny; j++)
  //  	  for (k=0; k<Nz; k++)
  //  	    {

  //  	      /*********************/
  //  	      /* l = Ka * ---- ... */
	      
  //  	      if (k==0)
  //  		L = min( (Levels(1)-Levels(0)) / 2.5, T(100) );
  //  	      else
  //  		L = min( (Levels(k)-Levels(k-1)) / 2.5, T(100) );
	      
  //  	      l = Ka * (Levels(k)+z0) / (1.0 + Ka * (Levels(k)+z0) / L);
	      
  //  	      /* l = Ka * ---- ... */
  //  	      /*********************/

  //  	      /**************/
  //  	      /* dWind / dz */

  //  	      // dW/dz.
	      
  //  	      if (k==0)
  //  		{
  //  		  derivative = ( W(h, i, j, k+1) - W(h, i, j, k) )
  //  		    / ( Levels(k+1) - Levels(k) );
  //  		  derivative = derivative * derivative;
  //  		  dWind_dz = derivative;
  //  		}
  //  	      else
  //  		{
  //  		  derivative = ( W(h, i, j, k) - W(h, i, j, k-1) )
  //  		    / ( Levels(k) - Levels(k-1) );
  //  		  derivative = derivative * derivative;
  //  		  dWind_dz = derivative;
  //  		}

  //  	      // dU/dz.

  //  	      if (k==0)
  //  		{
  //  		  derivative = U(h, i, j, k+1) - U(h, i, j, k)
  //  		    / ( Nodes(k+1) - Nodes(k) );
  //  		  derivative = derivative * derivative;
  //  		  dWind_dz += derivative;
  //  		}
  //  	      else if (k!=Nz-2)
  //  		{
  //  		  derivative = U(h, i, j, k) - U(h, i, j, k-1)
  //  		    / ( Nodes(k) - Nodes(k-1) );
  //  		  derivative = derivative * derivative;
  //  		  dWind_dz += derivative;
  //  		}
  //  	      else
  //  		{
  //  		  derivative = U(h, i, j, k-1) - U(h, i, j, k-2)
  //  		    / ( Nodes(k-1) - Nodes(k-2) );
  //  		  derivative = derivative * derivative;
  //  		  dWind_dz += derivative;
  //  		}

  //  	      // dV/dz.

  //  	      if (k==0)
  //  		{
  //  		  derivative = V(h, i, j, k+1) - V(h, i, j, k)
  //  		    / ( Nodes(k+1) - Nodes(k) );
  //  		  derivative = derivative * derivative;
  //  		  dWind_dz += derivative;
  //  		}
  //  	      else if (k!=Nz-2)
  //  		{
  //  		  derivative = V(h, i, j, k) - V(h, i, j, k-1)
  //  		    / ( Nodes(k) - Nodes(k-1) );
  //  		  derivative = derivative * derivative;
  //  		  dWind_dz += derivative;
  //  		}
  //  	      else
  //  		{
  //  		  derivative = V(h, i, j, k-1) - V(h, i, j, k-2)
  //  		    / ( Nodes(k-1) - Nodes(k-2) );
  //  		  derivative = derivative * derivative;
  //  		  dWind_dz += derivative;
  //  		}

  //  	      dWind_dz = sqrt(dWind_dz);

  //  	      /* dWind / dz */
  //  	      /**************/

  //  	      /***********/
  //  	      /* F(R, z) */

  //  	      if (k==0)
  //  		derivative = Tp(h, i, j, k+1) - Tp(h, i, j, k)
  //  		  / ( Nodes(k+1) - Nodes(k) );
  //  	      else if (k!=Nz-2)
  //  		derivative = Tp(h, i, j, k) - Tp(h, i, j, k-1)
  //  		  / ( Nodes(k) - Nodes(k-1) );
  //  	      else
  //  		derivative = Tp(h, i, j, k-1) - Tp(h, i, j, k-2)
  //  		  / ( Nodes(k-1) - Nodes(k-2) );

  //  	      R = g * derivative / ( dWind_dz * dWind_dz );

  //  	      if (R>=0)
  //  		F = 1.0 / ( 1.0 + 3.0 * B * R * sqrt(1.0+D*R) );
  //  	      else
  //  		{
  //  		  F = 1.0 + 3.0 * B * C * sqrt(fabs(R)/27.0) *
  //  		    (l * l) / ( (Levels(k) + z0) * (Levels(k) + z0) );
  //  		  F = 1.0 - 3.0 * B * R / F;
  //  		}

  //  	      /* F(R, z) */
  //  	      /***********/	      

  //  	      Kz(h, i, j, k) = l * l * dWind_dz * F;

  //  	    }

  //    }

}  // namespace SeldonData.

#define FILE_FUNCTIONS_CXX
#endif
