#ifndef FILE_GRID_HXX

namespace SeldonData
{


  /********/
  /* Grid */
  /********/

  template <class T>
  class Grid
  {

  public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    
  protected:
    int length_;
    int variable_;

    value_type previous_;
    
  public:
    Grid();
    Grid(int length, int variable = 0);
    Grid(const Grid& G);
    virtual ~Grid();

    virtual Grid<T>& operator= (const Grid<T>&);

    int GetLength() const;
    int GetVariable() const;
    virtual bool IsDependent(int i) const;

    value_type GetPrevious() const;
    virtual value_type GetStart() const;
    virtual value_type GetInc() const;

    virtual int GetNbElements() const;

    void SetVariable(int variable);

    virtual Grid<T>* Duplicate() const;

    virtual reference operator () (int i);
    virtual value_type operator () (int i) const;

    virtual reference Value(int i0, int i1 = -1,
			    int i2 = -1, int i3 = -1,
			    int i4 = -1, int i5 = -1,
			    int i6 = -1, int i7 = -1,
			    int i8 = -1, int i9 = -1);

    virtual value_type Value(int i0, int i1 = -1,
			     int i2 = -1, int i3 = -1,
			     int i4 = -1, int i5 = -1,
			     int i6 = -1, int i7 = -1,
			     int i8 = -1, int i9 = -1) const;

    virtual void ChangeCoords(Function_Base<T>& f, Array<Grid<T>*, 1> grids);

    virtual void Print() const;

  };


  /***************/
  /* RegularGrid */
  /***************/

  template<class T>
  class RegularGrid: public Grid<T>
  {
    
  public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    
  protected:
    value_type start_;
    value_type inc_;
    Array<value_type, 1> values_;

  public:
    RegularGrid();
    RegularGrid(int length, int variable = 0);
    RegularGrid(value_type start, value_type inc, int length, int variable = 0);
    RegularGrid(const Array<value_type, 1>& values, int variable = 0);
    RegularGrid(const Grid<T>& G);
    RegularGrid(const RegularGrid<T>& G);
    ~RegularGrid();

    RegularGrid<T>& operator= (const Grid<T>&);
    RegularGrid<T>& operator= (const RegularGrid<T>&);

    value_type GetStart() const;
    value_type GetInc() const;

    int GetNbElements() const;
    Array<value_type, 1>& GetValues();
    const Array<value_type, 1>& GetValues() const;

    Grid<T>* Duplicate() const;

    reference operator () (int i);
    value_type operator () (int i) const;

    reference Value(int i0, int i1 = -1,
		    int i2 = -1, int i3 = -1,
		    int i4 = -1, int i5 = -1,
		    int i6 = -1, int i7 = -1,
		    int i8 = -1, int i9 = -1);

    value_type Value(int i0, int i1 = -1,
		     int i2 = -1, int i3 = -1,
		     int i4 = -1, int i5 = -1,
		     int i6 = -1, int i7 = -1,
		     int i8 = -1, int i9 = -1) const;

    void Print() const;

  };
  

  /***************/
  /* GeneralGrid */
  /***************/

  template<class T, int n>
  class GeneralGrid: public Grid<T>
  {
    
  public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;

  protected:
    Array<value_type, n> values_;
    Array<int, 1> dependencies_;

  public:
    GeneralGrid();
    GeneralGrid(Array<value_type, n>& values,
		int variable,
		const TinyVector<int, n>& dependencies);
    GeneralGrid(const TinyVector<int, n>& values_shape,
		int variable,
		const TinyVector<int, n>& dependencies);
    GeneralGrid(const GeneralGrid<T, n>& G);
    GeneralGrid(const Grid<T>& G);
    ~GeneralGrid();

    GeneralGrid<T, n>& operator= (const Grid<T>&);
    GeneralGrid<T, n>& operator= (const GeneralGrid<T, n>&);

    int GetNbElements() const;
    Array<value_type, n>& GetValues();
    const Array<value_type, n>& GetValues() const;
    Array<int, 1>& GetDependencies();
    const Array<int, 1>& GetDependencies() const;
    int GetMainVariable() const;
    bool IsDependent(int i) const;
    
    Grid<T>* Duplicate() const;

    reference operator () (int i);
    value_type operator () (int i) const;

    reference Value(int i0, int i1 = -1,
		    int i2 = -1, int i3 = -1,
		    int i4 = -1, int i5 = -1,
		    int i6 = -1, int i7 = -1,
		    int i8 = -1, int i9 = -1);
    
    value_type Value(int i0, int i1 = -1,
		     int i2 = -1, int i3 = -1,
		     int i4 = -1, int i5 = -1,
		     int i6 = -1, int i7 = -1,
		     int i8 = -1, int i9 = -1) const;

    void Print() const;

  private:
    int main_variable_;

  };


}  // namespace Data.


#define FILE_GRID_HXX
#endif
