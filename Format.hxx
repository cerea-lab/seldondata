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

#ifndef FILE_SELDONDATA_FORMAT_HXX

#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;
#include <string>
#include <fstream>
using namespace std;

namespace SeldonData
{

  //! Base class for input/output classes.
  template<class T>
  class Format
  {

  protected:

  public:
    Format()  throw();
    ~Format()  throw();

  };


  //! Input/ouput class to read binary files.
  template<class T>
  class FormatBinary: public Format<T>
  {

  protected:

  public:
    FormatBinary()  throw();
    ~FormatBinary()  throw();

    // Grid.

    template<class TG>
    void Read(string FileName, RegularGrid<TG>& G) const;
    template<class TG>
    void Read(FILE* FileDes, RegularGrid<TG>& G) const;
    template<class TG, int N>
    void Read(string FileName, GeneralGrid<TG, N>& G) const;
    template<class TG, int N>
    void Read(FILE* FileDes, GeneralGrid<TG, N>& G) const;

    template<class TG>
    void Write(RegularGrid<TG>& G, string FileName) const;
    template<class TG>
    void Write(RegularGrid<TG>& G, FILE* FileDes) const;
    template<class TG, int N>
    void Write(GeneralGrid<TG, N>& G, string FileName) const;
    template<class TG, int N>
    void Write(GeneralGrid<TG, N>& G, FILE* FileDes) const;

    // Data.

    template<class TD, int N>
    void Read(string FileName, Data<TD, N>& D) const;
    template<class TD, int N>
    void Read(FILE* FileDes, Data<TD, N>& D) const;

    template<class TD, int N>
    void Write(Data<TD, N>& D, string FileName) const;
    template<class TD, int N>
    void Write(Data<TD, N>& D, FILE* FileDes) const;

    // Array.

    template<int N>
    void Read(string FileName, Array<T, N>& A) const;
    template<class TA, int N>
    void Read(string FileName, Array<TA, N>& A) const;
    template<int N>
    void Read(FILE* FileDes, Array<T, N>& A) const;
    template<class TA, int N>
    void Read(FILE* FileDes, Array<TA, N>& A) const;

    template<int N>
    void Write(Array<T, N>& A, string FileName) const;
    template<class TA, int N>
    void Write(Array<TA, N>& A, string FileName) const;
    template<int N>
    void Write(Array<T, N>& A, FILE* FileDes) const;
    template<class TA, int N>
    void Write(Array<TA, N>& A, FILE* FileDes) const;

  };


  //! Input/ouput class to read text files.
  template<class T>
  class FormatText: public Format<T>
  {

  protected:
    string format_;

  public:
    FormatText()  throw();
    FormatText(string format)  throw();
    ~FormatText()  throw();

    // Grid.

    template<class TG>
    void Read(string FileName, RegularGrid<TG>& G) const;
    template<class TG>
    void Read(FILE* FileDes, RegularGrid<TG>& G) const;
    template<class TG, int N>
    void Read(string FileName, GeneralGrid<TG, N>& G) const;
    template<class TG, int N>
    void Read(FILE* FileDes, GeneralGrid<TG, N>& G) const;

    template<class TG>
    void Write(RegularGrid<TG>& G, string FileName) const;
    template<class TG>
    void Write(RegularGrid<TG>& G, FILE* FileDes) const;
    template<class TG, int N>
    void Write(GeneralGrid<TG, N>& G, string FileName) const;
    template<class TG, int N>
    void Write(GeneralGrid<TG, N>& G, FILE* FileDes) const;

    // Data.

    template<class TD, int N>
    void Read(string FileName, Data<TD, N>& D) const;
    template<class TD, int N>
    void Read(FILE* FileDes, Data<TD, N>& D) const;

    template<class TD, int N>
    void Write(Data<TD, N>& D, string FileName) const;
    template<class TD, int N>
    void Write(Data<TD, N>& D, FILE* FileDes) const;

    // Array.

    template<class TA, int N>
    void Read(string FileName, Array<TA, N>& A) const;
    template<int N>
    void Read(FILE* FileDes, Array<T, N>& A) const;
    template<class TA, int N>
    void Read(FILE* FileDes, Array<TA, N>& A) const;

    template<class TA, int N>
    void Write(Array<TA, N>& A, string FileName) const;
    template<int N>
    void Write(Array<T, N>& A, FILE* FileDes) const;
    template<class TA, int N>
    void Write(Array<TA, N>& A, FILE* FileDes) const;

  };


  //! Input/ouput class to read files in Chimere format.
  template<class T>
  class FormatChimere: public Format<T>
  {

  protected:

  public:
    FormatChimere()  throw();
    ~FormatChimere()  throw();

    // Data.

    template<class TD, int N>
    void Read(string FileName, int date, Data<TD, N>& D) const;

    template<class TD, int N>
    void Write(Data<TD, N>& D, int date, string FileName) const;

    // Array.

    template<class TA, int N>
    void Read(string FileName, int date, Array<TA, N>& A) const;

    template<class TA, int N>
    void Write(Array<TA, N>& A, int date, string FileName) const;

  };

}  // namespace SeldonData.

#define FILE_SELDONDATA_FORMAT_HXX
#endif
