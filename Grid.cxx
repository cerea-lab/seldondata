#ifndef FILE_GRID_CXX

#include "Grid.hxx"

namespace SeldonData
{
  
  //////////
  // GRID //
  //////////

  template<class T>
  Grid<T>::Grid()
  {
    length_ = 0;
    variable_ = 0;
    previous_ = T(0);
  }

  template<class T>
  Grid<T>::Grid(int length, int variable)
  {
    length_ = length;
    variable_ = variable;
    previous_ = T(0);
  }

  template<class T>
  Grid<T>::Grid(const Grid<T>& G)
  {
    length_ = G.GetLength();
    variable_ = G.GetVariable();
    previous_ = G.GetPrevious();
  }

  template<class T>
  Grid<T>::~Grid()
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
  void Grid<T>::Print() const
  {
    cout << "Empty grid." << endl;
  }


  /////////////////
  // REGULARGRID //
  /////////////////

  template<class T>
  RegularGrid<T>::RegularGrid()
  {
  }

  template<class T>
  RegularGrid<T>::RegularGrid(int length, int variable):
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
			      int length, int variable):
    Grid<T>(length, variable), values_(length_)
  {
    start_ = start;
    inc_ = inc;

    for (int i=0; i<length_; i++)
      values_(i) = start_ + i * inc_;
  }

  template<class T>
  RegularGrid<T>::RegularGrid(const Array<typename RegularGrid<T>::value_type, 1>& values,
			      int variable):
    Grid<T>(values.numElements(), variable), values_(values)
  {
    start_ = values_(0);
    if (length_>1)
      inc_ = values_(1) - values_(0);
    else
      inc_ = T(0);
  }

  template<class T>
  RegularGrid<T>::RegularGrid(const Grid<T>& G):
    Grid<T>(G), values_(G.GetLength())
  {
    for (int i=0; i<G.GetLength(); i++)
      values_(i) = G(i);
    start_ = G.GetStart();
    inc_ = G.GetInc();
  }

  template<class T>
  RegularGrid<T>::RegularGrid(const RegularGrid<T>& G):
    Grid<T>(G), values_(G.GetValues())
  {
    start_ = G.GetStart();
    inc_ = G.GetInc();
  }

  template<class T>
  RegularGrid<T>::~RegularGrid()
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
  GeneralGrid<T, n>::GeneralGrid()
  {
    nb_dim_ = n;
  }

  template<class T, int n>
  GeneralGrid<T, n>::GeneralGrid(Array<typename GeneralGrid<T, n>::value_type, n>& values,
				 int variable,
				 Array<int, 1>& dependencies):
    values_(values), dependencies_(dependencies)
  {
    int i;

    variable_ = variable;
    nb_dim_ = dependencies.numElements();

    i = 0;
    while ((i<nb_dim_) && (dependencies_(i)!=variable_))
      i++;
    main_variable_ = i;

    length_ = values_.extent(main_variable_);      
  }

  template<class T, int n>
  GeneralGrid<T, n>::GeneralGrid(const Grid<T>& G): Grid<T>(G)
  {
    nb_dim_ = n;
  }

  template<class T, int n>
  GeneralGrid<T, n>::GeneralGrid(const GeneralGrid<T, n>& G):
    Grid<T>(G), values_(G.GetValues()),
    dependencies_(G.GetDependencies())
  {
    main_variable_ = G.GetMainVariable();
    nb_dim_ = n;
  }

  template<class T, int n>
  GeneralGrid<T, n>::~GeneralGrid()
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

    return ( (i == variable_) || res);
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
  void GeneralGrid<T, n>::Print() const
  {
    cout << "General Grid:" << endl;
    cout << values_ << endl;
  }

}  // namespace SeldonData.


#define FILE_GRID_CXX
#endif
