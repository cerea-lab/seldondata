#ifndef FILE_SELDONDATA_DATA_HXX

#include <iostream>
using std::cout;
using std::endl;

namespace SeldonData
{

  template<class T, int N>
  class Data
  {

  protected:
    //! Array storing data.
    Array<T, N> data_;
    //! Array of pointers to grids.
    Array<Grid<T>*, 1> grids_;

  public:

    // Constructors.

    Data(Grid<T>& G0)  throw();
    Data(Grid<T>& G0, Grid<T>& G1)  throw();
    Data(Grid<T>& G0, Grid<T>& G1,
	 Grid<T>& G2)  throw();
    Data(Grid<T>& G0, Grid<T>& G1,
	 Grid<T>& G2, Grid<T>& G3)  throw();
    Data(Grid<T>& G0, Grid<T>& G1,
	 Grid<T>& G2, Grid<T>& G3,
	 Grid<T>& G4)  throw();
    Data(Grid<T>& G0, Grid<T>& G1,
	 Grid<T>& G2, Grid<T>& G3,
	 Grid<T>& G4, Grid<T>& G5)  throw();
    Data(Grid<T>& G0, Grid<T>& G1,
	 Grid<T>& G2, Grid<T>& G3,
	 Grid<T>& G4, Grid<T>& G5,
	 Grid<T>& G6)  throw();
    Data(Grid<T>& G0, Grid<T>& G1,
	 Grid<T>& G2, Grid<T>& G3,
	 Grid<T>& G4, Grid<T>& G5,
	 Grid<T>& G6, Grid<T>& G7)  throw();
    Data(Grid<T>& G0, Grid<T>& G1,
	 Grid<T>& G2, Grid<T>& G3,
	 Grid<T>& G4, Grid<T>& G5,
	 Grid<T>& G6, Grid<T>& G7,
	 Grid<T>& G8)  throw();
    Data(Grid<T>& G0, Grid<T>& G1,
	 Grid<T>& G2, Grid<T>& G3,
	 Grid<T>& G4, Grid<T>& G5,
	 Grid<T>& G6, Grid<T>& G7,
	 Grid<T>& G8, Grid<T>& G9)  throw();

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

    int GetNbElements();
    int GetNbDim();
    int GetLength(int dim);

    Grid<T>& GetGrid(int i);
    Grid<T>& operator [] (int i);
    Array<Grid<T>*, 1>& GetGrids();

    Array<T, N>& GetArray();
    T* GetData();

    template<class R0>
    void SubData(Data<T, 1>&, R0 r0);
    template<class R0, class R1>
    void SubData(Data<T, 2>&, R0 r0, R1 r1);
    template<class R0, class R1, class R2>
    void SubData(Data<T, 3>&, R0 r0, R1 r1, R2 r2);
    template<class R0, class R1, class R2,
	     class R3>
    void SubData(Data<T, 4>&, R0 r0, R1 r1, R2 r2,
		 R3 r3);
    template<class R0, class R1, class R2,
	     class R3, class R4>
    void SubData(Data<T, 5>&, R0 r0, R1 r1, R2 r2,
		 R3 r3, R4 r4);
    template<class R0, class R1, class R2,
	     class R3, class R4, class R5>
    void SubData(Data<T, 6>&, R0 r0, R1 r1, R2 r2,
		 R3 r3, R4 r4, R5 r5);
    template<class R0, class R1, class R2,
	     class R3, class R4, class R5,
	     class R6>
    void SubData(Data<T, 7>&, R0 r0, R1 r1, R2 r2,
		 R3 r3, R4 r4, R5 r5, R6 r6);
    template<class R0, class R1, class R2,
	     class R3, class R4, class R5,
	     class R6, class R7>
    void SubData(Data<T, 8>&, R0 r0, R1 r1, R2 r2,
		 R3 r3, R4 r4, R5 r5, R6 r6,
		 R7 r7);
    template<class R0, class R1, class R2,
	     class R3, class R4, class R5,
	     class R6, class R7, class R8>
    void SubData(Data<T, 9>&, R0 r0, R1 r1, R2 r2,
		 R3 r3, R4 r4, R5 r5, R6 r6,
		 R7 r7, R8 r8);
    template<class R0, class R1, class R2,
	     class R3, class R4, class R5,
	     class R6, class R7, class R8, class R9>
    void SubData(Data<T, 10>&, R0 r0, R1 r1, R2 r2,
		 R3 r3, R4 r4, R5 r5, R6 r6,
		 R7 r7, R8 r8, R9 r9);

    // Calculus.
    void Apply(void function(T&));
    template <class F>
    void Apply(F& function);

    void SetZero();
    bool IsZero();

    void ChangeCoords(Function_Base<T>& f);
    void ChangeCoordsInPlace(Function_Base<T>& f);

    void Print();

  private:
    void SetVariables();

  };


}  // namespace Data.


#define FILE_SELDONDATA_DATA_HXX
#endif
