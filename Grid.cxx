#ifndef FILE_SELDONDATA_GRID_CXX

#include "Grid.hxx"

namespace SeldonData
{
  
  //////////
  // GRID //
  //////////

  template<class T>
  Grid<T>::Grid()  throw()
  {
    length_ = 0;
    variable_ = 0;
    previous_ = T(0);
  }

  template<class T>
  Grid<T>::Grid(int length, int variable)  throw()
  {
    length_ = length;
    variable_ = variable;
    previous_ = T(0);
  }

  template<class T>
  Grid<T>::Grid(const Grid<T>& G)  throw()
  {
    length_ = G.GetLength();
    variable_ = G.GetVariable();
    previous_ = G.GetPrevious();
  }

  template<class T>
  Grid<T>::~Grid()  throw()
  {
  }

  template<class T>
  Grid<T>& Grid<T>::operator= (const Grid<T>& G)
  {
    length_ = G.GetLength();
    variable_ = G.GetVariable();
    previous_ = G.GetPrevious();
  }

  template<class T>
  int Grid<T>::GetLength() const
  {
    return length_;
  }

  template<class T>
  int Grid<T>::GetVariable() const
  {
    return variable_;
  }

  template<class T>
  bool Grid<T>::IsDependent(int i) const
  {

#ifdef DEBUG_SELDONDATA_DIMENSION
    if ( (i<0) || (i>9) )
      throw WrongDim("Grid<T>::IsDependent", "Dimension number is " + i);
#endif

    return (i == variable_);

  }

  template<class T>
  typename Grid<T>::value_type
  Grid<T>::GetPrevious() const
  {
    return previous_;
  }

  template<class T>
  typename Grid<T>::value_type
  Grid<T>::GetStart() const
  {
    return previous_;
  }

  template<class T>
  typename Grid<T>::value_type
  Grid<T>::GetInc() const
  {
    return T(0);
  }

  template<class T>
  int Grid<T>::GetNbElements() const
  {
    return 0;
  }

  template<class T>
  void Grid<T>::SetVariable(int variable)
  {
    variable_ = variable;
  }
  
  template<class T>
  Grid<T>* Grid<T>::Duplicate() const
  {

    Grid<T>* G = new Grid<T>(*this);

#ifdef DEBUG_SELDONDATA_MEMORY
    if ( G == NULL )
      throw NoMemory("Grid<T>::Duplicate");
#endif

    return G;

  }

  template<class T>
  typename Grid<T>::reference
  Grid<T>::operator () (int i)
  {
    return previous_;
  }

  template<class T>
  typename Grid<T>::value_type
  Grid<T>::operator () (int i) const
  {
    return previous_;
  }

  template<class T>
  typename Grid<T>::reference
  Grid<T>::Value(int i0, int i1,
		 int i2, int i3,
		 int i4, int i5,
		 int i6, int i7,
		 int i8, int i9)
  {
    return previous_;
  }

  template<class T>
  typename Grid<T>::value_type
  Grid<T>::Value(int i0, int i1,
		 int i2, int i3,
		 int i4, int i5,
		 int i6, int i7,
		 int i8, int i9) const
  {
    return previous_;
  }

  template<class T>
  void Grid<T>::ChangeCoords(Function_Base<T>& f,
			     Array<Grid<T>*, 1> grids)
  {

    int N = grids.numElements();
    int i0, i1, i2, i3, i4, i5, i6, i7, i8, i9;

    grids(variable_) = this;

    if (N==1)
      for (i0=0; i0<int(!IsDependent(0)) +
	     int(IsDependent(0))*grids(0)->GetLength(); i0++)
	f(grids(0)->Value(i0));
    else if (N==2)
      for (i0=0; i0<int(!IsDependent(0)) +
	     int(IsDependent(0))*grids(0)->GetLength(); i0++)
	for (i1=0; i1<int(!IsDependent(1)) +
	       int(IsDependent(1))*grids(1)->GetLength(); i1++)
	  f(grids(0)->Value(i0, i1),
	    grids(1)->Value(i0, i1));
    else if (N==3)
      for (i0=0; i0<int(!IsDependent(0)) +
	     int(IsDependent(0))*grids(0)->GetLength(); i0++)
	for (i1=0; i1<int(!IsDependent(1)) +
	       int(IsDependent(1))*grids(1)->GetLength(); i1++)
	  for (i2=0; i2<int(!IsDependent(2)) +
		 int(IsDependent(2))*grids(2)->GetLength(); i2++)
	    f(grids(0)->Value(i0, i1, i2),
	      grids(1)->Value(i0, i1, i2),
	      grids(2)->Value(i0, i1, i2));
    else if (N==4)
      for (i0=0; i0<int(!IsDependent(0)) +
	     int(IsDependent(0))*grids(0)->GetLength(); i0++)
	for (i1=0; i1<int(!IsDependent(1)) +
	       int(IsDependent(1))*grids(1)->GetLength(); i1++)
	  for (i2=0; i2<int(!IsDependent(2)) +
		 int(IsDependent(2))*grids(2)->GetLength(); i2++)
	    for (i3=0; i3<int(!IsDependent(3)) +
		   int(IsDependent(3))*grids(3)->GetLength(); i3++)
	      f(grids(0)->Value(i0, i1, i2, i3),
		grids(1)->Value(i0, i1, i2, i3),
		grids(2)->Value(i0, i1, i2, i3),
		grids(3)->Value(i0, i1, i2, i3));
    else if (N==5)
      for (i0=0; i0<int(!IsDependent(0)) +
	     int(IsDependent(0))*grids(0)->GetLength(); i0++)
	for (i1=0; i1<int(!IsDependent(1)) +
	       int(IsDependent(1))*grids(1)->GetLength(); i1++)
	  for (i2=0; i2<int(!IsDependent(2)) +
		 int(IsDependent(2))*grids(2)->GetLength(); i2++)
	    for (i3=0; i3<int(!IsDependent(3)) +
		   int(IsDependent(3))*grids(3)->GetLength(); i3++)
	      for (i4=0; i4<int(!IsDependent(4)) +
		     int(IsDependent(4))*grids(4)->GetLength(); i4++)
		f(grids(0)->Value(i0, i1, i2, i3, i4),
		  grids(1)->Value(i0, i1, i2, i3, i4),
		  grids(2)->Value(i0, i1, i2, i3, i4),
		  grids(3)->Value(i0, i1, i2, i3, i4),
		  grids(4)->Value(i0, i1, i2, i3, i4));
    else if (N==6)
      for (i0=0; i0<int(!IsDependent(0)) +
	     int(IsDependent(0))*grids(0)->GetLength(); i0++)
	for (i1=0; i1<int(!IsDependent(1)) +
	       int(IsDependent(1))*grids(1)->GetLength(); i1++)
	  for (i2=0; i2<int(!IsDependent(2)) +
		 int(IsDependent(2))*grids(2)->GetLength(); i2++)
	    for (i3=0; i3<int(!IsDependent(3)) +
		   int(IsDependent(3))*grids(3)->GetLength(); i3++)
	      for (i4=0; i4<int(!IsDependent(4)) +
		     int(IsDependent(4))*grids(4)->GetLength(); i4++)
		for (i5=0; i5<int(!IsDependent(5)) +
		       int(IsDependent(5))*grids(5)->GetLength(); i5++)
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
				     i4, i5));
    else if (N==7)
      for (i0=0; i0<int(!IsDependent(0)) +
	     int(IsDependent(0))*grids(0)->GetLength(); i0++)
	for (i1=0; i1<int(!IsDependent(1)) +
	       int(IsDependent(1))*grids(1)->GetLength(); i1++)
	  for (i2=0; i2<int(!IsDependent(2)) +
		 int(IsDependent(2))*grids(2)->GetLength(); i2++)
	    for (i3=0; i3<int(!IsDependent(3)) +
		   int(IsDependent(3))*grids(3)->GetLength(); i3++)
	      for (i4=0; i4<int(!IsDependent(4)) +
		     int(IsDependent(4))*grids(4)->GetLength(); i4++)
		for (i5=0; i5<int(!IsDependent(5)) +
		       int(IsDependent(5))*grids(5)->GetLength(); i5++)
		  for (i6=0; i6<int(!IsDependent(6)) +
			 int(IsDependent(6))*grids(6)->GetLength(); i6++)
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
				       i4, i5, i6));
    else if (N==8)
      for (i0=0; i0<int(!IsDependent(0)) +
	     int(IsDependent(0))*grids(0)->GetLength(); i0++)
	for (i1=0; i1<int(!IsDependent(1)) +
	       int(IsDependent(1))*grids(1)->GetLength(); i1++)
	  for (i2=0; i2<int(!IsDependent(2)) +
		 int(IsDependent(2))*grids(2)->GetLength(); i2++)
	    for (i3=0; i3<int(!IsDependent(3)) +
		   int(IsDependent(3))*grids(3)->GetLength(); i3++)
	      for (i4=0; i4<int(!IsDependent(4)) +
		     int(IsDependent(4))*grids(4)->GetLength(); i4++)
		for (i5=0; i5<int(!IsDependent(5)) +
		       int(IsDependent(5))*grids(5)->GetLength(); i5++)
		  for (i6=0; i6<int(!IsDependent(6)) +
			 int(IsDependent(6))*grids(6)->GetLength(); i6++)
		    for (i7=0; i7<int(!IsDependent(7)) +
			   int(IsDependent(7))*grids(7)->GetLength(); i7++)
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
					 i4, i5, i6, i7));
    else if (N==9)
      for (i0=0; i0<int(!IsDependent(0)) +
	     int(IsDependent(0))*grids(0)->GetLength(); i0++)
	for (i1=0; i1<int(!IsDependent(1)) +
	       int(IsDependent(1))*grids(1)->GetLength(); i1++)
	  for (i2=0; i2<int(!IsDependent(2)) +
		 int(IsDependent(2))*grids(2)->GetLength(); i2++)
	    for (i3=0; i3<int(!IsDependent(3)) +
		   int(IsDependent(3))*grids(3)->GetLength(); i3++)
	      for (i4=0; i4<int(!IsDependent(4)) +
		     int(IsDependent(4))*grids(4)->GetLength(); i4++)
		for (i5=0; i5<int(!IsDependent(5)) +
		       int(IsDependent(5))*grids(5)->GetLength(); i5++)
		  for (i6=0; i6<int(!IsDependent(6)) +
			 int(IsDependent(6))*grids(6)->GetLength(); i6++)
		    for (i7=0; i7<int(!IsDependent(7)) +
			   int(IsDependent(7))*grids(7)->GetLength(); i7++)
		      for (i8=0; i8<int(!IsDependent(8)) +
			     int(IsDependent(8))*grids(8)->GetLength(); i8++)
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
					   i8));
    else if (N==10)
      for (i0=0; i0<int(!IsDependent(0)) +
	     int(IsDependent(0))*grids(0)->GetLength(); i0++)
	for (i1=0; i1<int(!IsDependent(1)) +
	       int(IsDependent(1))*grids(1)->GetLength(); i1++)
	  for (i2=0; i2<int(!IsDependent(2)) +
		 int(IsDependent(2))*grids(2)->GetLength(); i2++)
	    for (i3=0; i3<int(!IsDependent(3)) +
		   int(IsDependent(3))*grids(3)->GetLength(); i3++)
	      for (i4=0; i4<int(!IsDependent(4)) +
		     int(IsDependent(4))*grids(4)->GetLength(); i4++)
		for (i5=0; i5<int(!IsDependent(5)) +
		       int(IsDependent(5))*grids(5)->GetLength(); i5++)
		  for (i6=0; i6<int(!IsDependent(6)) +
			 int(IsDependent(6))*grids(6)->GetLength(); i6++)
		    for (i7=0; i7<int(!IsDependent(7)) +
			   int(IsDependent(7))*grids(7)->GetLength(); i7++)
		      for (i8=0; i8<int(!IsDependent(8)) +
			     int(IsDependent(8))*grids(8)->GetLength(); i8++)
			for (i9=0; i9<int(!IsDependent(9)) +
			       int(IsDependent(9))*grids(9)->GetLength(); i9++)
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
					     i8, i9));
    
  }

  template<class T>
  void Grid<T>::Print() const
  {
    cout << "Empty grid." << endl;
  }


  /////////////////
  // REGULARGRID //
  /////////////////

  template<class T>
  RegularGrid<T>::RegularGrid()  throw()
  {
  }

  template<class T>
  RegularGrid<T>::RegularGrid(int length, int variable)  throw():
    Grid<T>(length, variable), values_(length_)
  {
    start_ = T(0);
    inc_ = T(1);

    for (int i=0; i<length_; i++)
      values_(i) = start_ + i * inc_;
  }

  template<class T>
  RegularGrid<T>::RegularGrid(typename RegularGrid<T>::value_type start,
			      typename RegularGrid<T>::value_type inc,
			      int length, int variable)  throw():
    Grid<T>(length, variable), values_(length_)
  {
    start_ = start;
    inc_ = inc;

    for (int i=0; i<length_; i++)
      values_(i) = start_ + i * inc_;
  }

  template<class T>
  RegularGrid<T>::RegularGrid(const Array<typename RegularGrid<T>::value_type, 1>& values,
			      int variable)  throw():
    Grid<T>(values.numElements(), variable), values_(values.copy())
  {
    start_ = values_(0);
    if (length_>1)
      inc_ = values_(1) - values_(0);
    else
      inc_ = T(0);
  }

  template<class T>
  RegularGrid<T>::RegularGrid(const Grid<T>& G)  throw():
    Grid<T>(G), values_(G.GetLength())
  {
    for (int i=0; i<G.GetLength(); i++)
      values_(i) = G(i);
    start_ = G.GetStart();
    inc_ = G.GetInc();
  }

  template<class T>
  RegularGrid<T>::RegularGrid(const RegularGrid<T>& G)  throw():
    Grid<T>(G), values_((G.GetValues()).copy())
  {
    start_ = G.GetStart();
    inc_ = G.GetInc();
  }

  template<class T>
  RegularGrid<T>::~RegularGrid()  throw()
  {
  }

  template<class T>
  RegularGrid<T>& RegularGrid<T>::operator= (const Grid<T>& G)
  {
    length_ = G.GetLength();
    variable_ = G.GetVariable();
    start_ = G.GetStart();
    inc_ = G.GetInc();
  }

  template<class T>
  RegularGrid<T>&
  RegularGrid<T>::operator= (const RegularGrid<T>& G)
  {
    length_ = G.GetLength();
    variable_ = G.GetVariable();
    start_ = G.GetStart();
    inc_ = G.GetInc();

    values_ = G.GetValues();
  }

  template<class T>
  typename RegularGrid<T>::value_type
  RegularGrid<T>::GetStart() const
  {
    return start_;
  }

  template<class T>
  typename RegularGrid<T>::value_type
  RegularGrid<T>::GetInc() const
  {
    return inc_;
  }

  template<class T>
  int RegularGrid<T>::GetNbElements() const
  {
    return length_;
  }

  template<class T>
  Array<typename RegularGrid<T>::value_type, 1>&
  RegularGrid<T>::GetValues()
  {
    return values_;
  }

  template<class T>
  const Array<typename RegularGrid<T>::value_type, 1>&
  RegularGrid<T>::GetValues() const
  {
    return values_;
  }

  template<class T>
  Grid<T>* RegularGrid<T>::Duplicate() const
  {
    Grid<T>* G = new RegularGrid<T>(*this);
    return G;
  }

  template<class T>
  typename RegularGrid<T>::reference
  RegularGrid<T>::operator () (int i)
  {
    return values_(i);
  }

  template<class T>
  typename RegularGrid<T>::value_type
  RegularGrid<T>::operator () (int i) const
  {
    return values_(i);
  }

  template<class T>
  typename RegularGrid<T>::reference
  RegularGrid<T>::Value(int i0, int i1,
			int i2, int i3,
			int i4, int i5,
			int i6, int i7,
			int i8, int i9)
  {
    if (variable_==0)
      return values_(i0);
    else if (variable_==1)
      return values_(i1);
    else if (variable_==2)
      return values_(i2);
    else if (variable_==3)
      return values_(i3);
    else if (variable_==4)
      return values_(i4);
    else if (variable_==5)
      return values_(i7);
    else if (variable_==6)
      return values_(i6);
    else if (variable_==7)
      return values_(i7);
    else if (variable_==8)
      return values_(i8);
    else if (variable_==9)
      return values_(i9);
  }

  template<class T>
  typename RegularGrid<T>::value_type
  RegularGrid<T>::Value(int i0, int i1,
			int i2, int i3,
			int i4, int i5,
			int i6, int i7,
			int i8, int i9) const
  {
    if (variable_==0)
      return values_(i0);
    else if (variable_==1)
      return values_(i1);
    else if (variable_==2)
      return values_(i2);
    else if (variable_==3)
      return values_(i3);
    else if (variable_==4)
      return values_(i4);
    else if (variable_==5)
      return values_(i7);
    else if (variable_==6)
      return values_(i6);
    else if (variable_==7)
      return values_(i7);
    else if (variable_==8)
      return values_(i8);
    else if (variable_==9)
      return values_(i9);
  }

  template<class T>
  void RegularGrid<T>::Print() const
  {
    cout << "Regular Grid:" << endl;
    cout << values_ << endl;
  }


  /////////////////
  // GENERALGRID //
  /////////////////

  template<class T, int n>
  GeneralGrid<T, n>::GeneralGrid()  throw()
  {
  }

  // variable_: variable stockee par Grid, soit variable de la grille.
  // main_variable_: dimension du tableau qui correspond a variable_.
  template<class T, int n>
  GeneralGrid<T, n>::GeneralGrid(Array<typename GeneralGrid<T, n>::value_type, n>& values,
				 int variable,
				 const TinyVector<int, n>& dependencies)  throw():
    values_(values.copy()), dependencies_(n)
  {
    int i;

    for (i=0; i<n; i++)
      dependencies_(i) = dependencies(i);

    variable_ = variable;

    i = 0;
    while ((i<n) && (dependencies_(i)!=variable_))
      i++;
    main_variable_ = i;

    length_ = values_.extent(main_variable_);      
  }

  template<class T, int n>
  GeneralGrid<T, n>::GeneralGrid(const TinyVector<int, n>& values_shape,
				 int variable,
				 const TinyVector<int, n>& dependencies)  throw():
    values_(values_shape), dependencies_(n)
  {
    int i;
    
    for (i=0; i<n; i++)
      dependencies_(i) = dependencies(i);

    variable_ = variable;

    i = 0;
    while ((i<n) && (dependencies_(i)!=variable_))
      i++;
    main_variable_ = i;

    length_ = values_.extent(main_variable_);      
  }

  template<class T, int n>
  GeneralGrid<T, n>::GeneralGrid(const Grid<T>& G): Grid<T>(G)  throw()
  {
  }

  template<class T, int n>
  GeneralGrid<T, n>::GeneralGrid(const GeneralGrid<T, n>& G)  throw():
    Grid<T>(G), values_((G.GetValues()).copy()),
    dependencies_((G.GetDependencies()).copy())
  {
    main_variable_ = G.GetMainVariable();
  }

  template<class T, int n>
  GeneralGrid<T, n>::~GeneralGrid()  throw()
  {
  }

  template<class T, int n>
  GeneralGrid<T, n>& GeneralGrid<T, n>::operator= (const Grid<T>& G)
  {
    length_ = G.GetLength();
    variable_ = G.GetVariable();
  }

  template<class T, int n>
  GeneralGrid<T, n>&
  GeneralGrid<T, n>::operator= (const GeneralGrid<T, n>& G)
  {
    length_ = G.GetLength();
    variable_ = G.GetVariable();

    // Warning: must have the same length.
    values_ = G.GetValues();
    dependencies_ = G.GetDependencies();

    main_variable_ = G.GetMainVariable();
  }

  template<class T, int n>
  int GeneralGrid<T, n>::GetNbElements() const
  {
    return values_.numElements();
  }

  template<class T, int n>
  Array<typename GeneralGrid<T, n>::value_type, n>&
  GeneralGrid<T, n>::GetValues()
  {
    return values_;
  }

  template<class T, int n>
  const Array<typename GeneralGrid<T, n>::value_type, n>&
  GeneralGrid<T, n>::GetValues() const
  {
    return values_;
  }

  template<class T, int n>
  Array<int, 1>&
  GeneralGrid<T, n>::GetDependencies()
  {
    return dependencies_;
  }

  template<class T, int n>
  const Array<int, 1>&
  GeneralGrid<T, n>::GetDependencies() const
  {
    return dependencies_;
  }

  template<class T, int n>
  int GeneralGrid<T, n>::GetMainVariable() const
  {
    return main_variable_;
  }

  template<class T, int n>
  bool GeneralGrid<T, n>::IsDependent(int i) const
  {
    bool res = false;
    for (int j=0; j<dependencies_.numElements(); j++)
      res = res || (dependencies_(j)==i);

    return res;
  }

  template<class T, int n>
  Grid<T>* GeneralGrid<T, n>::Duplicate() const
  {
    Grid<T>* G = new GeneralGrid<T, n>(*this);
    return G;
  }

  template<class T, int n>
  typename GeneralGrid<T, n>::reference
  GeneralGrid<T, n>::operator () (int i)
  {
    return previous_;
  }

  template<class T, int n>
  typename GeneralGrid<T, n>::value_type
  GeneralGrid<T, n>::operator () (int i) const
  {
    return previous_;
  }

  template<class T, int n>
  typename GeneralGrid<T, n>::reference
  GeneralGrid<T, n>::Value(int i0, int i1,
			   int i2, int i3,
			   int i4, int i5,
			   int i6, int i7,
			   int i8, int i9)
  {
    Array<int, 1> Indices(10);

    Indices(0) = i0; Indices(1) = i1;
    Indices(2) = i2; Indices(3) = i3;
    Indices(4) = i4; Indices(5) = i5;
    Indices(6) = i6; Indices(7) = i7;
    Indices(8) = i8; Indices(9) = i9;

    if (n==1)
      return values_(Indices(dependencies_(0)));
    if (n==2)
      return values_(Indices(dependencies_(0)),
		     Indices(dependencies_(1)));
    if (n==3)
      return values_(Indices(dependencies_(0)),
		     Indices(dependencies_(1)),
		     Indices(dependencies_(2)));
    if (n==4)
      return values_(Indices(dependencies_(0)),
		     Indices(dependencies_(1)),
		     Indices(dependencies_(2)),
		     Indices(dependencies_(3)));
    if (n==5)
      return values_(Indices(dependencies_(0)),
		     Indices(dependencies_(1)),
		     Indices(dependencies_(2)),
		     Indices(dependencies_(3)),
		     Indices(dependencies_(4)));
    if (n==6)
      return values_(Indices(dependencies_(0)),
		     Indices(dependencies_(1)),
		     Indices(dependencies_(2)),
		     Indices(dependencies_(3)),
		     Indices(dependencies_(4)),
		     Indices(dependencies_(5)));
    if (n==7)
      return values_(Indices(dependencies_(0)),
		     Indices(dependencies_(1)),
		     Indices(dependencies_(2)),
		     Indices(dependencies_(3)),
		     Indices(dependencies_(4)),
		     Indices(dependencies_(5)),
		     Indices(dependencies_(6)));
    if (n==8)
      return values_(Indices(dependencies_(0)),
		     Indices(dependencies_(1)),
		     Indices(dependencies_(2)),
		     Indices(dependencies_(3)),
		     Indices(dependencies_(4)),
		     Indices(dependencies_(5)),
		     Indices(dependencies_(6)),
		     Indices(dependencies_(7)));
    if (n==9)
      return values_(Indices(dependencies_(0)),
		     Indices(dependencies_(1)),
		     Indices(dependencies_(2)),
		     Indices(dependencies_(3)),
		     Indices(dependencies_(4)),
		     Indices(dependencies_(5)),
		     Indices(dependencies_(6)),
		     Indices(dependencies_(7)),
		     Indices(dependencies_(8)));
    if (n==10)
      return values_(Indices(dependencies_(0)),
		     Indices(dependencies_(1)),
		     Indices(dependencies_(2)),
		     Indices(dependencies_(3)),
		     Indices(dependencies_(4)),
		     Indices(dependencies_(5)),
		     Indices(dependencies_(6)),
		     Indices(dependencies_(7)),
		     Indices(dependencies_(8)),
		     Indices(dependencies_(9)));

  }

  template<class T, int n>
  typename GeneralGrid<T, n>::value_type
  GeneralGrid<T, n>::Value(int i0, int i1,
			   int i2, int i3,
			   int i4, int i5,
			   int i6, int i7,
			   int i8, int i9) const
  {
    Array<int, 1> Indices(10);

    Indices(0) = i0; Indices(1) = i1;
    Indices(2) = i2; Indices(3) = i3;
    Indices(4) = i4; Indices(5) = i5;
    Indices(6) = i6; Indices(7) = i7;
    Indices(8) = i8; Indices(9) = i9;

    if (n==1)
      return values_(Indices(dependencies_(0)));
    if (n==2)
      return values_(Indices(dependencies_(0)),
		     Indices(dependencies_(1)));
    if (n==3)
      return values_(Indices(dependencies_(0)),
		     Indices(dependencies_(1)),
		     Indices(dependencies_(2)));
    if (n==4)
      return values_(Indices(dependencies_(0)),
		     Indices(dependencies_(1)),
		     Indices(dependencies_(2)),
		     Indices(dependencies_(3)));
    if (n==5)
      return values_(Indices(dependencies_(0)),
		     Indices(dependencies_(1)),
		     Indices(dependencies_(2)),
		     Indices(dependencies_(3)),
		     Indices(dependencies_(4)));
    if (n==6)
      return values_(Indices(dependencies_(0)),
		     Indices(dependencies_(1)),
		     Indices(dependencies_(2)),
		     Indices(dependencies_(3)),
		     Indices(dependencies_(4)),
		     Indices(dependencies_(5)));
    if (n==7)
      return values_(Indices(dependencies_(0)),
		     Indices(dependencies_(1)),
		     Indices(dependencies_(2)),
		     Indices(dependencies_(3)),
		     Indices(dependencies_(4)),
		     Indices(dependencies_(5)),
		     Indices(dependencies_(6)));
    if (n==8)
      return values_(Indices(dependencies_(0)),
		     Indices(dependencies_(1)),
		     Indices(dependencies_(2)),
		     Indices(dependencies_(3)),
		     Indices(dependencies_(4)),
		     Indices(dependencies_(5)),
		     Indices(dependencies_(6)),
		     Indices(dependencies_(7)));
    if (n==9)
      return values_(Indices(dependencies_(0)),
		     Indices(dependencies_(1)),
		     Indices(dependencies_(2)),
		     Indices(dependencies_(3)),
		     Indices(dependencies_(4)),
		     Indices(dependencies_(5)),
		     Indices(dependencies_(6)),
		     Indices(dependencies_(7)),
		     Indices(dependencies_(8)));
    if (n==10)
      return values_(Indices(dependencies_(0)),
		     Indices(dependencies_(1)),
		     Indices(dependencies_(2)),
		     Indices(dependencies_(3)),
		     Indices(dependencies_(4)),
		     Indices(dependencies_(5)),
		     Indices(dependencies_(6)),
		     Indices(dependencies_(7)),
		     Indices(dependencies_(8)),
		     Indices(dependencies_(9)));

  }

  template<class T, int n>
  void GeneralGrid<T, n>::ChangeCoords(Function_Base<T>& f,
				       Array<Grid<T>*, 1> grids_old)
  {
    ERR(1);
    int i;
    int N = grids_old.numElements();
    int i0, i1, i2, i3, i4, i5, i6, i7, i8, i9;

    Array<Grid<T>*, 1> grids(10);
    //      for (i=0; i<10; i++)
    //        if (i<grids_old.numElement())
    //  	grids(i) = grids_old.Duplicate();
    //        else
    //  	grids(i) = new Grid<T>();

    grids(0) = grids_old(0)->Duplicate();
    for (i=1; i<10; i++)
      grids(i) = new Grid<T>();

    delete grids(variable_);
    grids(variable_) = this;

    DISP(int(!IsDependent(0)) +
	 int(IsDependent(0))*grids(0)->GetLength());

    for (i0=0; i0<int(!IsDependent(0)) +
	   int(IsDependent(0))*grids(0)->GetLength(); i0++)
      {
	if (variable_!=1)
	  {
	    delete grids(1);
	    if (1<grids_old.numElements())
	      grids(1) = grids_old(1)->Duplicate();
	    else
	      grids(1) = new Grid<T>();
	  }
	
	for (i1=0; i1<int(!IsDependent(1)) +
	       int(IsDependent(1))*grids(1)->GetLength(); i1++)
	  {
	    if (variable_!=2)
	      {
		delete grids(2);
		if (2<grids_old.numElements())
		  grids(2) = grids_old(2)->Duplicate();
		else
		  grids(2) = new Grid<T>();
	      }
	
	    for (i2=0; i2<int(!IsDependent(2)) +
		   int(IsDependent(2))*grids(2)->GetLength(); i2++)
	      {
		if (variable_!=3)
		  {
		    delete grids(3);
		    if (3<grids_old.numElements())
		      grids(3) = grids_old(3)->Duplicate();
		    else
		      grids(3) = new Grid<T>();
		  }
	
		for (i3=0; i3<int(!IsDependent(3)) +
		       int(IsDependent(3))*grids(3)->GetLength(); i3++)
		  {
		    if (variable_!=4)
		      {
			delete grids(4);
			if (4<grids_old.numElements())
			  grids(4) = grids_old(4)->Duplicate();
			else
			  grids(4) = new Grid<T>();
		      }
	
		    for (i4=0; i4<int(!IsDependent(4)) +
			   int(IsDependent(4))*grids(4)->GetLength(); i4++)
		      {
			if (variable_!=5)
			  {
			    delete grids(5);
			    if (5<grids_old.numElements())
			      grids(5) = grids_old(5)->Duplicate();
			    else
			      grids(5) = new Grid<T>();
			  }
	
			for (i5=0; i5<int(!IsDependent(5)) +
			       int(IsDependent(5))*grids(5)->GetLength(); i5++)
			  {
			    if (variable_!=6)
			      {
				delete grids(6);
				if (6<grids_old.numElements())
				  grids(6) = grids_old(6)->Duplicate();
				else
				  grids(6) = new Grid<T>();
			      }
	
			    for (i6=0; i6<int(!IsDependent(6)) +
				   int(IsDependent(6))*grids(6)->GetLength(); i6++)
			      {
				if (variable_!=7)
				  {
				    delete grids(7);
				    if (7<grids_old.numElements())
				      grids(7) = grids_old(7)->Duplicate();
				    else
				      grids(7) = new Grid<T>();
				  }
	
				for (i7=0; i7<int(!IsDependent(7)) +
				       int(IsDependent(7))*grids(7)->GetLength(); i7++)
				  {
				    if (variable_!=8)
				      {
					delete grids(8);
					if (8<grids_old.numElements())
					  grids(8) = grids_old(8)->Duplicate();
					else
					  grids(8) = new Grid<T>();
				      }
	
				    for (i8=0; i8<int(!IsDependent(8)) +
					   int(IsDependent(8))*grids(8)->GetLength(); i8++)
				      {
					if (variable_!=9)
					  {
					    delete grids(9);
					    if (9<grids_old.numElements())
					      grids(9) = grids_old(9)->Duplicate();
					    else
					      grids(9) = new Grid<T>();
					  }
	
					for (i9=0; i9<int(!IsDependent(9)) +
					       int(IsDependent(9))*grids(9)->GetLength(); i9++)

					  if (N==1)
					    f(grids(0)->Value(i0));
					  else if (N==2)
					    f(grids(0)->Value(i0, i1),
					      grids(1)->Value(i0, i1));
					  else if (N==3)
					    f(grids(0)->Value(i0, i1, i2),
					      grids(1)->Value(i0, i1, i2),
					      grids(2)->Value(i0, i1, i2));
					  else if (N==4)
					    f(grids(0)->Value(i0, i1, i2, i3),
					      grids(1)->Value(i0, i1, i2, i3),
					      grids(2)->Value(i0, i1, i2, i3),
					      grids(3)->Value(i0, i1, i2, i3));
					  else if (N==5)
					    f(grids(0)->Value(i0, i1, i2, i3, i4),
					      grids(1)->Value(i0, i1, i2, i3, i4),
					      grids(2)->Value(i0, i1, i2, i3, i4),
					      grids(3)->Value(i0, i1, i2, i3, i4),
					      grids(4)->Value(i0, i1, i2, i3, i4));
					  else if (N==6)
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
							      i4, i5));
					  else if (N==7)
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
							      i4, i5, i6));
					  else if (N==8)
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
							      i4, i5, i6, i7));
					  else if (N==9)
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
							      i8));
					  else if (N==10)
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
							      i8, i9));
				      }
				  }
			      }
			  }
		      }
		  }
	      }
	  }
      }    

  }

  template<class T, int n>
  void GeneralGrid<T, n>::Print() const
  {
    cout << "General Grid:" << endl;
    cout << values_ << endl;
  }

}  // namespace SeldonData.


#define FILE_SELDONDATA_GRID_CXX
#endif
