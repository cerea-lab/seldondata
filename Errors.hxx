#define FILE_SELDONDATA_ERRORS_HXX

#include <iostream>
using std::cout;
using std::endl;
#include <string>

namespace Seldon
{
  
  ///////////
  // ERROR //
  ///////////

  //! Base class.
  class Error
  {

  protected:
    //! Name of the function where the error occured.
    string function;
    //! Comment about the error.
    string comment;

  public:
    //! Default Constructor.
    Error()
    {
      cout << "ERROR!" << endl;
      function = "";
      comment = "";
    }
    //! Constructor.
    /*!
      \param f name of the function where the error occured.
     */
    Error(string f)
    {
      cout << "ERROR!" << endl;
      function = f;
      comment = "";
    }
    //! Constructor.
    /*!
      \param f name of the function where the error occured.
      \param c comment about the error.
     */
    Error(string f, string c)
    {
      cout << "ERROR!" << endl;
      function = f;
      comment = c;
    }

    //! Displays error description.
    virtual void What()
    {
      cout << "An unknown error occured";
      if (function.length()!=0)
	cout << " in " << function;
      cout << "." << endl;
      if (comment.length()!=0)
	cout << "   " << comment << endl;
      cout << endl;
    }

  };



  //////////////
  // NOMEMORY //
  //////////////


  //! No memory available.
  class NoMemory: public Error
  {

  public:
    //! Main constructor.
    NoMemory(string f, string c): Error(f, c)
    {
    }
    //! Constructor.
    NoMemory(string f): Error(f)
    {
    }

    //! Displays error description.
    virtual void What()
    {
      cout << "No more memory is available";
      if (this->function!="")
	cout << " in " << this->function;
      cout << "." << endl;
      if (this->comment!="")
	cout << "   " << this->comment << endl;
      cout << endl;
    }

  };
  


  //////////////
  // WRONGDIM //
  //////////////


  //! Wrong dimension.
  /*!
    Dimensions do not match.
  */
  class WrongDim: public Error
  {

  public:
    //! Main constructor.
    WrongDim(string f, string c): Error(f, c)
    {
    }

    //! Displays error description.
    virtual void What()
    {
      cout << "Wrong dimension";
      if (this->function!="")
	cout << " in " << this->function;
      cout << "." << endl;
      if (this->comment!="")
	cout << "   " << this->comment << endl;
      cout << endl;
    }

  };
  


  ////////////////
  // WRONGINDEX //
  ////////////////


  //! Wrong index.
  /*!
    The index is out of range.
  */
  class WrongIndex: public Error
  {

  public:
    //! Main constructor.
    WrongIndex(string f, string c): Error(f, c)
    {
    }

    //! Displays error description.
    virtual void What()
    {
      cout << "Index out of range";
      if (this->function!="")
	cout << " in " << this->function;
      cout << "." << endl;
      if (this->comment!="")
	cout << "   " << this->comment << endl;
      cout << endl;
    }

  };
  


  /////////////
  // IOERROR //
  /////////////


  //! Error while performing an I/O operation.
  class IOError: public Error
  {

  public:
    //! Main constructor.
    IOError(string f, string c): Error(f, c)
    {
    }

    //! Displays error description.
    virtual void What()
    {
      cout << "An input/output operation failed";
      if (this->function!="")
	cout << " in " << this->function;
      cout << "." << endl;
      if (this->comment!="")
	cout << "   " << this->comment << endl;
      cout << endl;
    }

  };

  
}  // namespace Seldon.


#define FILE_SELDONDATA_ERRORS_HXX
#endif