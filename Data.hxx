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

#ifndef FILE_SELDONDATA_DATA_HXX

#include <iostream>
using std::cout;
using std::endl;

namespace SeldonData
{

  //! Data class.
  template<class T, int N, class TG = T>
  class Data
  {

  protected:
    //! Array storing data.
    Array<T, N> data_;
    //! Array of pointers to grids.
    Array<Grid<TG>*, 1> grids_;

  public:

    // Constructors.

    Data()  throw();
    Data(Grid<TG>& G0)  throw();
    Data(Grid<TG>& G0, Grid<TG>& G1)  throw();
    Data(Grid<TG>& G0, Grid<TG>& G1,
	 Grid<TG>& G2)  throw();
    Data(Grid<TG>& G0, Grid<TG>& G1,
	 Grid<TG>& G2, Grid<TG>& G3)  throw();
    Data(Grid<TG>& G0, Grid<TG>& G1,
	 Grid<TG>& G2, Grid<TG>& G3,
	 Grid<TG>& G4)  throw();
    Data(Grid<TG>& G0, Grid<TG>& G1,
	 Grid<TG>& G2, Grid<TG>& G3,
	 Grid<TG>& G4, Grid<TG>& G5)  throw();
    Data(Grid<TG>& G0, Grid<TG>& G1,
	 Grid<TG>& G2, Grid<TG>& G3,
	 Grid<TG>& G4, Grid<TG>& G5,
	 Grid<TG>& G6)  throw();
    Data(Grid<TG>& G0, Grid<TG>& G1,
	 Grid<TG>& G2, Grid<TG>& G3,
	 Grid<TG>& G4, Grid<TG>& G5,
	 Grid<TG>& G6, Grid<TG>& G7)  throw();
    Data(Grid<TG>& G0, Grid<TG>& G1,
	 Grid<TG>& G2, Grid<TG>& G3,
	 Grid<TG>& G4, Grid<TG>& G5,
	 Grid<TG>& G6, Grid<TG>& G7,
	 Grid<TG>& G8)  throw();
    Data(Grid<TG>& G0, Grid<TG>& G1,
	 Grid<TG>& G2, Grid<TG>& G3,
	 Grid<TG>& G4, Grid<TG>& G5,
	 Grid<TG>& G6, Grid<TG>& G7,
	 Grid<TG>& G8, Grid<TG>& G9)  throw();
    template <class T0>
    Data(Data<T0, N, TG>& data)  throw();

    // Destructor.

    ~Data()  throw();

    // Methods.

    T& operator() (int i0);
    T& operator() (int i0, int i1);
    T& operator() (int i0, int i1, int i2);
    T& operator() (int i0, int i1, int i2,
		   int i3);
    T& operator() (int i0, int i1, int i2,
		   int i3, int i4);
    T& operator() (int i0, int i1, int i2,
		   int i3, int i4, int i5);
    T& operator() (int i0, int i1, int i2,
		   int i3, int i4, int i5,
		   int i6);
    T& operator() (int i0, int i1, int i2,
		  int i3, int i4, int i5,
		   int i6, int i7);
    T& operator() (int i0, int i1, int i2,
		  int i3, int i4, int i5,
		   int i6, int i7, int i8);
    T& operator() (int i0, int i1, int i2,
		   int i3, int i4, int i5,
		   int i6, int i7, int i8,
		   int i9);

    T& operator() (Array<int, 1>& indices);

    T& Value(int i0, int i1 = -1,
	     int i2 = -1, int i3 = -1,
	     int i4 = -1, int i5 = -1,
	     int i6 = -1, int i7 = -1,
	     int i8 = -1, int i9 = -1);

    T Value(int i0, int i1 = -1,
	    int i2 = -1, int i3 = -1,
	    int i4 = -1, int i5 = -1,
	    int i6 = -1, int i7 = -1,
	    int i8 = -1, int i9 = -1) const;

    template <class T0>
    void Copy(Data<T0, N, TG>& data);

    int GetNbElements();
    int GetNbDim();
    int GetLength(int dim) const;

    Grid<TG>* GetGrid(int i);
    Grid<TG>& operator [] (int i);
    Array<Grid<TG>*, 1>& GetGrids();

    Array<T, N>& GetArray();
    T* GetData();
    const T* GetData() const;

    template<class DTG, class R0>
    void SubData(Data<T, 1, DTG>&, R0 r0);
    template<class DTG, class R0, class R1>
    void SubData(Data<T, 2, DTG>&, R0 r0, R1 r1);
    template<class DTG, class R0, class R1, class R2>
    void SubData(Data<T, 3, DTG>&, R0 r0, R1 r1, R2 r2);
    template<class DTG, class R0, class R1, class R2,
	     class R3>
    void SubData(Data<T, 4, DTG>&, R0 r0, R1 r1, R2 r2,
		 R3 r3);
    template<class DTG, class R0, class R1, class R2,
	     class R3, class R4>
    void SubData(Data<T, 5, DTG>&, R0 r0, R1 r1, R2 r2,
		 R3 r3, R4 r4);
    template<class DTG, class R0, class R1, class R2,
	     class R3, class R4, class R5>
    void SubData(Data<T, 6, DTG>&, R0 r0, R1 r1, R2 r2,
		 R3 r3, R4 r4, R5 r5);
    template<class DTG, class R0, class R1, class R2,
	     class R3, class R4, class R5,
	     class R6>
    void SubData(Data<T, 7, DTG>&, R0 r0, R1 r1, R2 r2,
		 R3 r3, R4 r4, R5 r5, R6 r6);
    template<class DTG, class R0, class R1, class R2,
	     class R3, class R4, class R5,
	     class R6, class R7>
    void SubData(Data<T, 8, DTG>&, R0 r0, R1 r1, R2 r2,
		 R3 r3, R4 r4, R5 r5, R6 r6,
		 R7 r7);
    template<class DTG, class R0, class R1, class R2,
	     class R3, class R4, class R5,
	     class R6, class R7, class R8>
    void SubData(Data<T, 9, DTG>&, R0 r0, R1 r1, R2 r2,
		 R3 r3, R4 r4, R5 r5, R6 r6,
		 R7 r7, R8 r8);
    template<class DTG, class R0, class R1, class R2,
	     class R3, class R4, class R5,
	     class R6, class R7, class R8, class R9>
    void SubData(Data<T, 10, DTG>&, R0 r0, R1 r1, R2 r2,
		 R3 r3, R4 r4, R5 r5, R6 r6,
		 R7 r7, R8 r8, R9 r9);

    void Resize();
    void Resize(Grid<TG>& G0);
    void Resize(Grid<TG>& G0, Grid<TG>& G1);
    void Resize(Grid<TG>& G0, Grid<TG>& G1,
		Grid<TG>& G2);
    void Resize(Grid<TG>& G0, Grid<TG>& G1,
		Grid<TG>& G2, Grid<TG>& G3);
    void Resize(Grid<TG>& G0, Grid<TG>& G1,
		Grid<TG>& G2, Grid<TG>& G3,
		Grid<TG>& G4);
    void Resize(Grid<TG>& G0, Grid<TG>& G1,
		Grid<TG>& G2, Grid<TG>& G3,
		Grid<TG>& G4, Grid<TG>& G5);
    void Resize(Grid<TG>& G0, Grid<TG>& G1,
		Grid<TG>& G2, Grid<TG>& G3,
		Grid<TG>& G4, Grid<TG>& G5,
		Grid<TG>& G6);
    void Resize(Grid<TG>& G0, Grid<TG>& G1,
		Grid<TG>& G2, Grid<TG>& G3,
		Grid<TG>& G4, Grid<TG>& G5,
		Grid<TG>& G6, Grid<TG>& G7);
    void Resize(Grid<TG>& G0, Grid<TG>& G1,
		Grid<TG>& G2, Grid<TG>& G3,
		Grid<TG>& G4, Grid<TG>& G5,
		Grid<TG>& G6, Grid<TG>& G7,
		Grid<TG>& G8);
    void Resize(Grid<TG>& G0, Grid<TG>& G1,
		Grid<TG>& G2, Grid<TG>& G3,
		Grid<TG>& G4, Grid<TG>& G5,
		Grid<TG>& G6, Grid<TG>& G7,
		Grid<TG>& G8, Grid<TG>& G9);

    // Calculus.
    void Mlt(T alpha);
    void Add(T alpha);
    void Apply(void function(T&));
    template <class F>
    void Apply(F& function);

    T GetMax() const;
    T GetMaxAbs() const;
    T GetSignedMaxAbs() const;
    T GetMin() const;

    Array<int, 1> GetMaxIndex() const;
    Array<int, 1> GetMaxAbsIndex() const;
    Array<int, 1> GetMinIndex() const;

    T Sum() const;
    T Mean() const;
    T Variance() const;
    T StandardDeviation() const;

    T Norm1() const;
    T Norm2() const;
    T Norm(T p) const;

    void Fill(T value);

    void SetZero();
    bool IsZero();

    void Threshold(T threshold);
    void ThresholdAbs(T threshold);

    template <class T0, class TG0>
    T NGE_interpolation(Data<T0, N, TG0>& data, T limit = T(0));
    template <class T0, class TG0>
    T NGE(Data<T0, N, TG0>& data, T limit = T(0));

    template <class T0, class TG0>
    T Bias_interpolation(Data<T0, N, TG0>& data);
    template <class T0, class TG0>
    T Bias(Data<T0, N, TG0>& data);

    template <class T0, class TG0>
    T RMS_interpolation(Data<T0, N, TG0>& data);
    template <class T0, class TG0>
    T RMS(Data<T0, N, TG0>& data);

    template <class T0, class TG0>
    T Corr_interpolation(Data<T0, N, TG0>& data);
    template <class T0, class TG0>
    T Corr(Data<T0, N, TG0>& data);

    template <class T0, class TG0>
    T ErrorLessThan_interpolation(Data<T0, N, TG0>& data, T threshold);
    template <class T0, class TG0>
    T ErrorLessThan(Data<T0, N, TG0>& data, T threshold);

    void ChangeCoords(FuncCoords_Base<TG>& f);
    void ChangeCoordsInPlace(Function_Base<TG>& f);

    void Print();

  private:
    void ClearGrids();
    void SetVariables();

  };


}  // namespace Data.


#define FILE_SELDONDATA_DATA_HXX
#endif
