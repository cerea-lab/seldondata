// Copyright (C) 2003-2004 Vivien Mallet
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

#ifndef FILE_SELDONDATA_SELDONDATA_HXX

// Blitz++.
#include <blitz/array.h>
using namespace blitz;

#include <string>
#include <sstream>

namespace SeldonData
{

  //! Converts most types to string.
  /*!
    \param input variable to be converted.
    \return A string containing 'input'.
  */
  template<typename T>
  std::string to_str(const T& input)
  {
    std::ostringstream output;
    output << input;
    return output.str();
  }

  //! Converts string to most types, specially numbers.
  /*!
    \param input string to be converted.
    \return 'input' converted to 'T'.
  */
  template <class T>
  void to_num(std::string s, T& num)
  {
    std::istringstream str(s);
    str >> num;
  }

  //! Converts string to most types, specially numbers.
  /*!
    \param input string to be converted.
    \return 'input' converted to 'T'.
  */
  template <class T>
  T to_num(std::string s)
  {
    T num;
    std::istringstream str(s);
    str >> num;
    return num;
  }

}  // namespace SeldonData.

#include "Errors.hxx"

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
#define TRY try\
{
#endif
#ifndef END
#define END \
}\
catch(SeldonData::Error& Err)\
{\
Err.What();\
}\
catch(...)\
{\
cout << "Unknown error..." <<endl;\
}
#endif


//! To display a message... call Hermes!
#define ERR(x) cout << "Hermes - " #x << endl
//! To display a variable (with its name); same as DISPLAY.
#define DISP(x) cout << #x ": " << x << endl
//! To display a variable (with its name); same as DISP.
#define DISPLAY(x) cout << #x ": " << x << endl

// To get 'min' and 'max' functions.
#include <algorithm>

#include "Function.hxx"
#include "Grid.cxx"
#include "Data.cxx"
#include "Format.cxx"
#include "Functions.cxx"

#define FILE_SELDONDATA_SELDONDATA_HXX
#endif
