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

#ifndef FILE_SELDONDATA_FORMAT_HXX

#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;
#include <string>
#include <fstream>
using namespace std;

#ifdef SELDONDATA_WITH_NETCDF
#include "netcdfcpp.h"
#endif

#ifdef SELDONDATA_WITH_GRIB
#include "unpackgrib.c"
#endif

namespace SeldonData
{

  //! Base class for input/output classes.
  class Format
  {

  protected:

  public:
    Format()  throw();
    ~Format()  throw();

  };


  //! Input/ouput class to read binary files.
  template<class T>
  class FormatBinary: public Format
  {

  protected:

  public:
    FormatBinary()  throw();
    ~FormatBinary()  throw();

    // Grid.

    template<class TG>
    void Read(string FileName, RegularGrid<TG>& G) const;
    template<class TG>
    void Read(ifstream& FileStream, RegularGrid<TG>& G) const;
    template<class TG, int N>
    void Read(string FileName, GeneralGrid<TG, N>& G) const;
    template<class TG, int N>
    void Read(ifstream& FileStream, GeneralGrid<TG, N>& G) const;

    template<class TG>
    void Write(RegularGrid<TG>& G, string FileName) const;
    template<class TG>
    void Write(RegularGrid<TG>& G, ofstream& FileStream) const;
    template<class TG, int N>
    void Write(GeneralGrid<TG, N>& G, string FileName) const;
    template<class TG, int N>
    void Write(GeneralGrid<TG, N>& G, ofstream& FileStream) const;

    template<class TG>
    void Append(RegularGrid<TG>& G, string FileName) const;
    template<class TG, int N>
    void Append(GeneralGrid<TG, N>& G, string FileName) const;

    // Data.

    template<class TD, int N, class TG>
    void Read(string FileName, Data<TD, N, TG>& D) const;
    template<class TD, int N, class TG>
    void Read(ifstream& FileStream, Data<TD, N, TG>& D) const;

    template<class TD, int N, class TG>
    void Write(Data<TD, N, TG>& D, string FileName) const;
    template<class TD, int N, class TG>
    void Write(Data<TD, N, TG>& D, ofstream& FileStream) const;

    template<class TD, int N, class TG>
    void Append(Data<TD, N, TG>& D, string FileName) const;

    // Array.

    template<class TA, int N>
    void Read(string FileName, Array<TA, N>& A) const;
    template<int N>
    void Read(ifstream& FileStream, Array<T, N>& A) const;
    template<class TA, int N>
    void Read(ifstream& FileStream, Array<TA, N>& A) const;

    template<class TA, int N>
    void Write(Array<TA, N>& A, string FileName) const;
    template<int N>
    void Write(Array<T, N>& A, ofstream& FileStream) const;
    template<class TA, int N>
    void Write(Array<TA, N>& A, ofstream& FileStream) const;

    template<class TA, int N>
    void Append(Array<TA, N>& A, string FileName) const;

  };


  //! Input/ouput class to read text files.
  class FormatText: public Format
  {

  protected:
    string separator_;
    fstream::fmtflags flags_;
    streamsize precision_;
    streamsize width_;

  public:
    FormatText()  throw();
    FormatText(string separator)  throw();
    FormatText(fstream::fmtflags flags, string separator = "\t\t")  throw();
    FormatText(fstream::fmtflags flags, streamsize precision,
	       streamsize width = -1, string separator = "\t\t")  throw();
    ~FormatText()  throw();

    void SetSeparator(string separator);
    void SetFlags(ofstream::fmtflags flags);
    void SetPrecision(streamsize precision);
    void SetWidth(streamsize width);

    // Grid.

    template<class TG>
    void Read(string FileName, RegularGrid<TG>& G) const;
    template<class TG>
    void Read(ifstream& FileStream, RegularGrid<TG>& G) const;
    template<class TG, int N>
    void Read(string FileName, GeneralGrid<TG, N>& G) const;
    template<class TG, int N>
    void Read(ifstream& FileStream, GeneralGrid<TG, N>& G) const;

    template<class TG>
    void Write(RegularGrid<TG>& G, string FileName) const;
    template<class TG>
    void Write(RegularGrid<TG>& G, ofstream& FileStream) const;
    template<class TG, int N>
    void Write(GeneralGrid<TG, N>& G, string FileName) const;
    template<class TG, int N>
    void Write(GeneralGrid<TG, N>& G, ofstream& FileStream) const;

    // Data.

    template<class TD, int N, class TG>
    void Read(string FileName, Data<TD, N, TG>& D) const;
    template<class TD, int N, class TG>
    void Read(ifstream& FileStream, Data<TD, N, TG>& D) const;

    template<class TD, int N, class TG>
    void Write(Data<TD, N, TG>& D, string FileName) const;
    template<class TD, int N, class TG>
    void Write(Data<TD, N, TG>& D, ofstream& FileStream) const;

    // Array.

    template<class TA, int N>
    void Read(string FileName, Array<TA, N>& A) const;
    template<class TA, int N>
    void Read(ifstream& FileStream, Array<TA, N>& A) const;

    template<class TA, int N>
    void Write(Array<TA, N>& A, string FileName) const;
    template<class TA, int N>
    void Write(Array<TA, N>& A, ofstream& FileStream) const;

  };


#ifdef SELDONDATA_WITH_NETCDF
  //! Input/ouput class to read netCDF files.
  template<class T>
  class FormatNetCDF: public Format
  {

  protected:

  public:
    FormatNetCDF()  throw();
    ~FormatNetCDF()  throw();

    // Grid.

    template<class TG>
    void Read(string FileName, string variable, RegularGrid<TG>& G) const;
    template<class TG, int N>
    void Read(string FileName, string variable, GeneralGrid<TG, N>& G) const;

    // Data.

    template<class TD, int N, class TG>
    void Read(string FileName, string variable, Data<TD, N, TG>& D) const;

    // Array.

    template<class TA, int N>
    void Read(string FileName, string variable, Array<TA, N>& A) const;

  };
#endif


#ifdef SELDONDATA_WITH_GRIB
  //! Input/ouput class to read Grib files.
  class FormatGrib: public Format
  {

  protected:

  public:
    FormatGrib()  throw();
    ~FormatGrib()  throw();

    // Grid.

    template<class TG>
    void Read(string FileName, int variable, RegularGrid<TG>& G) const;
    template<class TG, int N>
    void Read(string FileName, int variable, GeneralGrid<TG, N>& G) const;

    // Data.

    template<class TD, int N, class TG>
    void Read(string FileName, int variable, Data<TD, N, TG>& D) const;

    // Array.

    template<int N>
    void Read(string FileName, int variable, Array<double, N>& A) const;
    template<class TA, int N>
    void Read(string FileName, int variable, Array<TA, N>& A) const;

  };
#endif


  //! Input/ouput class to read files in Chimere format.
  class FormatChimere: public Format
  {

  protected:
    int date_;

  public:
    FormatChimere()  throw();
    FormatChimere(int date)  throw();
    ~FormatChimere()  throw();

    void SetDate(int date);
    int GetDate() const;

    // Data.

    template<class TD, int N, class TG>
    void Read(string FileName, Data<TD, N, TG>& D,
	      int nb_lines = -1) const;
    template<class TD, int N, class TG>
    void Read(ifstream& FileStream, Data<TD, N, TG>& D,
	      int nb_lines = -1) const;

    // Array.

    template<class TA, int N>
    void Read(string FileName, Array<TA, N>& A,
	      int nb_lines = -1) const;
    template<class TA, int N>
    void Read(ifstream& FileStream, Array<TA, N>& A,
	      int nb_lines = -1) const;

  };

}  // namespace SeldonData.

#define FILE_SELDONDATA_FORMAT_HXX
#endif
