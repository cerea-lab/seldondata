#ifndef FILE_SELDONDATA_SELDONDATA_HXX

// Blitz++.
#include <blitz/array.h>
using namespace blitz;


namespace SeldonData
{

  // In <algorithm>.
  // template<class T>
  // T min(T& a, T& b)
  // {
  //   return (a<b?a:b);
  // }
  
  // template<class T>
  // T max(T& a, T& b)
  // {
  //   return (a>b?a:b);
  // }

}  // namespace SeldonData.


////////////
// MACROS //
////////////

//! Convenient structure to catch exceptions.
/*!
  Use TRY and END to catch exceptions thrown by SeldonData:

  [...]
  TRY;

  Code that could throw an exception.

  END;

  [...]

  If an exception is caught, explanations are displayed to identify
  the problem (name of the involved function and comments).

*/
#ifndef TRY
#define TRY try\\
{
#endif
#ifndef END
#define END \\
}\\
catch(Seldon::Error& Err)\\
{\\
Err.What();\\
}\\
catch(...)\\
{\\
cout << "Unknown error..." <<endl;\\
}
#endif


#define ERR(x) cout << "Hermes - " #x << endl
#define DISP(x) cout << #x ": " << x << endl
#define DISPLAY(x) cout << #x ": " << x << endl

#include <algorithm>
#include "Function.hxx"
#include "Grid.cxx"
#include "Data.cxx"
#include "Format.cxx"
#include "Functions.cxx"

#define FILE_SELDONDATA_SELDONDATA_HXX
#endif
