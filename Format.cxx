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

#ifndef FILE_SELDONDATA_FORMAT_CXX

#include "Format.hxx"

#ifndef CONST_SELDONDATA_BUFFER_SIZE
#define CONST_SELDONDATA_BUFFER_SIZE 16384
#endif

namespace SeldonData
{


  ////////////
  // FORMAT //
  ////////////
  
  //! Default constructor.
  Format::Format()  throw()
  {
  }

  //! Destructor.
  Format::~Format()  throw()
  {
  }


  //////////////////
  // FORMATBINARY //
  //////////////////

  //! Default constructor.
  template<class T>
  FormatBinary<T>::FormatBinary()  throw()
  {
  }

  //! Destructor.
  template<class T>
  FormatBinary<T>::~FormatBinary()  throw()
  {
  }

  /********/
  /* Grid */
  /********/

  //! Reads a binary file.
  template<class T>
  template<class TG>
  void FormatBinary<T>::Read(string FileName, RegularGrid<TG>& G) const
  {

    this->Read(FileName, G.GetArray());

  }

  //! Reads a binary file.
  template<class T>
  template<class TG>
  void FormatBinary<T>::Read(ifstream& FileStream, RegularGrid<TG>& G) const
  {

    this->Read(FileStream, G.GetArray());

  }

  //! Reads a binary file.
  template<class T>
  template<class TG, int n>
  void FormatBinary<T>::Read(string FileName, GeneralGrid<TG, n>& G) const
  {

    this->Read(FileName, G.GetArray());

  }

  //! Reads a binary file.
  template<class T>
  template<class TG, int n>
  void FormatBinary<T>::Read(ifstream& FileStream, GeneralGrid<TG, n>& G) const
  {

    this->Read(FileStream, G.GetArray());

  }

  //! Writes a binary file.
  template<class T>
  template<class TG>
  void FormatBinary<T>::Write(RegularGrid<TG>& G, string FileName) const
  {

    this->Write(G.GetArray(), FileName);

  }

  //! Writes a binary file.
  template<class T>
  template<class TG>
  void FormatBinary<T>::Write(RegularGrid<TG>& G, ofstream FileStream) const
  {

    this->Write(G.GetArray(), FileStream);
    
  }

  //! Writes a binary file.
  template<class T>
  template<class TG, int n>
  void FormatBinary<T>::Write(GeneralGrid<TG, n>& G, string FileName) const
  {

    this->Write(G.GetArray(), FileName);

  }

  //! Writes a binary file.
  template<class T>
  template<class TG, int n>
  void FormatBinary<T>::Write(GeneralGrid<TG, n>& G, ofstream FileStream) const
  {

    this->Write(G.GetArray(), FileStream);
    
  }

  /********/
  /* Data */
  /********/
  
  //! Reads a binary file.
  template<class T>
  template<class TD, int N, class TG>
  void FormatBinary<T>::Read(string FileName, Data<TD, N, TG>& D) const
  {

    this->Read(FileName, D.GetArray());

  }

  //! Reads a binary file.
  template<class T>
  template<class TD, int N, class TG>
  void FormatBinary<T>::Read(ifstream& FileStream, Data<TD, N, TG>& D) const
  {

    this->Read(FileStream, D.GetArray());

  }

  //! Writes a binary file.
  template<class T>
  template<class TD, int N, class TG>
  void FormatBinary<T>::Write(Data<TD, N, TG>& D, string FileName) const
  {

    this->Write(D.GetArray(), FileName);

  }

  //! Writes a binary file.
  template<class T>
  template<class TD, int N, class TG>
  void FormatBinary<T>::Write(Data<TD, N, TG>& D, ofstream FileStream) const
  {

    this->Write(D.GetArray(), FileStream);

  }

  /*********/
  /* Array */
  /*********/

  //! Reads a binary file.
  template<class T>
  template<class TA, int N>
  void FormatBinary<T>::Read(string FileName, Array<TA, N>& A) const
  {

    ifstream FileStream;
    FileStream.open(FileName.c_str(), ifstream::binary);

#ifdef DEBUG_SELDONDATA_IO
    // Checks if the file was opened.
    if (!FileStream.is_open())
      throw IOError("FormatBinary<T>::Read(string FileName, Array<TA, N>& A)",
		    "Unable to open file \"" + FileName + "\".");
#endif

    this->Read(FileStream, A);

    FileStream.close();

  }

  //! Reads a binary file.
  template<class T>
  template<int N>
  void FormatBinary<T>::Read(ifstream& FileStream, Array<T, N>& A) const
  {

    unsigned long data_size = A.numElements() * sizeof(T);
    T* data = A.data();

#ifdef DEBUG_SELDONDATA_IO
    // Checks if the file ready.
    if (!FileStream.good())
      throw IOError("FormatBinary<T>::Read(ifstream& FileStream, Array<T, N>& A)",
		    "File is not ready.");

    // Checks file length.
    streampos position;
    position = FileStream.tellg();
    FileStream.seekg(0, ios::end);
    unsigned long file_size = FileStream.tellg() - position;

    if (data_size>file_size)
      throw IOError("FormatBinary<T>::Read(ifstream& FileStream, Array<T, N>& A)",
		    "Unable to read " + to_str(data_size) + " byte(s)." +
		    " The input stream is only " + to_str(file_size) + " byte(s) long.");

    FileStream.seekg(position);
#endif

    FileStream.read(reinterpret_cast<char*>(data), data_size);
    
  }

  //! Reads a binary file.
  template<class T>
  template<class TA, int N>
  void FormatBinary<T>::Read(ifstream& FileStream, Array<TA, N>& A) const
  {

    unsigned long data_size = A.numElements() * sizeof(T);

    unsigned long length = CONST_SELDONDATA_BUFFER_SIZE / sizeof(T);
    T* data = new T[length];

    TA* data_output = A.data();

#ifdef DEBUG_SELDONDATA_IO
    // Checks if the file ready.
    if (!FileStream.good())
      throw IOError("FormatBinary<T>::Read(ifstream& FileStream, Array<TA, N>& A)",
		    "File is not ready.");

    // Checks file length.
    streampos position;
    position = FileStream.tellg();
    FileStream.seekg(0, ios::end);
    unsigned long file_size = FileStream.tellg() - position;

    if (data_size>file_size)
      throw IOError("FormatBinary<T>::Read(ifstream& FileStream, Array<TA, N>& A)",
		    "Unable to read " + to_str(data_size) + " byte(s)." +
		    " The input stream is only " + to_str(file_size) + " byte(s) long.");

    FileStream.seekg(position);
#endif

    int i = 0;
    int j = 0;
    for (i=0; i < data_size / sizeof(T) / length; i++)
      {
	FileStream.read(reinterpret_cast<char*>(data), length * sizeof(T));
	for (j=0; j<length; j++)
	  data_output[j + i*length] = data[j];
      }

    if (data_size % (length * sizeof(T)) != 0)
      {
	FileStream.read(reinterpret_cast<char*>(data), data_size - i * length * sizeof(T));
	for (j=0; j < (data_size % (length * sizeof(T))) / sizeof(T); j++)
	  data_output[j + i*length] = data[j];
      }

  }

  //! Writes a binary file.
  template<class T>
  template<class TA, int N>
  void FormatBinary<T>::Write(Array<TA, N>& A, string FileName) const
  {

    ofstream FileStream;
    FileStream.open(FileName.c_str(), ofstream::binary);

#ifdef DEBUG_SELDONDATA_IO
    // Checks if the file was opened.
    if (!FileStream.is_open())
      throw IOError("FormatBinary<T>::Write(Array<TA, N>& A, string FileName)",
		    "Unable to open file \"" + FileName + "\".");
#endif

    this->Write(A, FileStream);

    FileStream.close();
    
  }

  //! Writes a binary file.
  template<class T>
  template<int N>
  void FormatBinary<T>::Write(Array<T, N>& A, ofstream& FileStream) const
  {

    unsigned long data_size = A.numElements() * sizeof(T);

    T* data = A.data();

#ifdef DEBUG_SELDONDATA_IO
    // Checks if the file ready.
    if (!FileStream.good())
      throw IOError("FormatBinary<T>::Write(Array<T, N>& A, ofstream& FileStream)",
		    "File is not ready.");
#endif

    FileStream.write(reinterpret_cast<char*>(data), data_size);
    
  }

  //! Writes a binary file.
  template<class T>
  template<class TA, int N>
  void FormatBinary<T>::Write(Array<TA, N>& A, ofstream& FileStream) const
  {

    unsigned long data_size = A.numElements() * sizeof(T);

    unsigned long length = CONST_SELDONDATA_BUFFER_SIZE / sizeof(T);
    T* data = new T[length];

    TA* data_input = A.data();

#ifdef DEBUG_SELDONDATA_IO
    // Checks if the file ready.
    if (!FileStream.good())
      throw IOError("FormatBinary<T>::Write(Array<TA, N>& A, ofstream& FileStream)",
		    "File is not ready.");
#endif

    int i = 0;
    int j = 0;
    for (i=0; i < data_size / sizeof(T) / length; i++)
      {
	for (j=0; j<length; j++)
	  data[j] = data_input[j+ i*length];
	FileStream.write(reinterpret_cast<char*>(data), length * sizeof(T));
      }

    if (data_size % (length * sizeof(T)) != 0)
      {
	for (j=0; j < (data_size % (length * sizeof(T))) / sizeof(T); j++)
	  data[j] = data_input[j + i*length];
	FileStream.write(reinterpret_cast<char*>(data), data_size - i * length * sizeof(T));
      }

  }


  ////////////////
  // FORMATTEXT //
  ////////////////

  //! Default constructor.
  FormatText::FormatText()  throw()
  {
    separator_ = "\t\t";
    flags_ = fstream::scientific | fstream::skipws;
    precision_ = -1;
    width_ = -1;
  }

  //! Constructor.
  FormatText::FormatText(string separator)  throw()
  {
    separator_ = separator;
    flags_ = fstream::scientific | fstream::skipws;
    precision_ = -1;
    width_ = -1;
  }

  //! Constructor.
  FormatText::FormatText(fstream::fmtflags flags, string separator)  throw()
  {
    separator_ = separator;
    flags_ = flags | fstream::skipws;
    precision_ = -1;
    width_ = -1;
  }

  //! Constructor.
  FormatText::FormatText(fstream::fmtflags flags, streamsize precision,
			 streamsize width, string separator)  throw()
  {
    separator_ = separator;
    flags_ = flags | fstream::skipws;
    precision_ = precision;
    width_ = width;
  }

  //! Destructor.
  FormatText::~FormatText()  throw()
  {

  }

  //! Sets the separator.
  /*!
    \param separator the new separator.
  */
  void FormatText::SetSeparator(string separator)
  {
    separator_ = separator;
  }

  //! Sets format flags.
  /*!
    \param flags format flags.
  */
  void FormatText::SetFlags(fstream::fmtflags flags)
  {
    flags_ = flags;
  }

  //! Sets floating-point decimal presision.
  /*!
    \param precision floating-point decimal presision.
  */
  void FormatText::SetPrecision(streamsize precision)
  {
    precision_ = precision;
  }

  //! Sets field width.
  /*!
    \param width field width.
  */
  void FormatText::SetWidth(streamsize width)
  {
    width_ = width;
  }

  /********/
  /* Grid */
  /********/

  //! Reads a text file.
  template<class TG>
  void FormatText::Read(string FileName, RegularGrid<TG>& G) const
  {

    this->Read(FileName, G.GetArray());

  }

  //! Reads a text file.
  template<class TG>
  void FormatText::Read(ifstream& FileStream, RegularGrid<TG>& G) const
  {

    this->Read(FileStream, G.GetArray());

  }

  //! Reads a text file.
  template<class TG, int n>
  void FormatText::Read(string FileName, GeneralGrid<TG, n>& G) const
  {

    this->Read(FileName, G.GetArray());

  }

  //! Reads a text file.
  template<class TG, int n>
  void FormatText::Read(ifstream& FileStream, GeneralGrid<TG, n>& G) const
  {

    this->Read(FileStream, G.GetArray());

  }

  //! Writes a text file.
  template<class TG>
  void FormatText::Write(RegularGrid<TG>& G, string FileName) const
  {

    this->Write(G.GetArray(), FileName);

  }

  //! Writes a text file.
  template<class TG>
  void FormatText::Write(RegularGrid<TG>& G, ofstream& FileStream) const
  {

    this->Write(G.GetArray(), FileStream);
    
  }

  //! Writes a text file.
  template<class TG, int n>
  void FormatText::Write(GeneralGrid<TG, n>& G, string FileName) const
  {

    this->Write(G.GetArray(), FileName);

  }

  //! Writes a text file.
  template<class TG, int n>
  void FormatText::Write(GeneralGrid<TG, n>& G, ofstream& FileStream) const
  {

    this->Write(G.GetArray(), FileStream);
    
  }

  /********/
  /* Data */
  /********/
  
  //! Reads a text file.
  template<class TD, int N, class TG>
  void FormatText::Read(string FileName, Data<TD, N, TG>& D) const
  {

    this->Read(FileName, D.GetArray());

  }

  //! Reads a text file.
  template<class TD, int N, class TG>
  void FormatText::Read(ifstream& FileStream, Data<TD, N, TG>& D) const
  {

    this->Read(FileStream, D.GetArray());

  }

  //! Writes a text file.
  template<class TD, int N, class TG>
  void FormatText::Write(Data<TD, N, TG>& D, string FileName) const
  {

    this->Write(D.GetArray(), FileName);

  }

  //! Writes a text file.
  template<class TD, int N, class TG>
  void FormatText::Write(Data<TD, N, TG>& D, ofstream& FileStream) const
  {

    this->Write(D.GetArray(), FileStream);

  }

  /*********/
  /* Array */
  /*********/

  //! Reads a text file.
  template<class TA, int N>
  void FormatText::Read(string FileName, Array<TA, N>& A) const
  {

    ifstream FileStream;
    FileStream.open(FileName.c_str(), ifstream::in);
    
    FileStream.flags(flags_);

    if (precision_!=-1)
      FileStream.precision(precision_);

    if (width_!=-1)
      FileStream.width(width_);

#ifdef DEBUG_SELDONDATA_IO
    // Checks if the file was opened.
    if (!FileStream.is_open())
      throw IOError("FormatText::Read(string FileName, Array<TA, N>& A)",
		    "Unable to open file \"" + FileName + "\".");
#endif

    this->Read(FileStream, A);

    FileStream.close();

  }

  //! Reads a text file.
  template<class TA, int N>
  void FormatText::Read(ifstream& FileStream, Array<TA, N>& A) const
  {

#ifdef DEBUG_SELDONDATA_IO
    // Checks if the file ready.
    if (!FileStream.good())
      throw IOError("FormatText::Read(ifstream& FileStream, Array<TA, N>& A)",
		    "File is not ready.");
#endif

    int nb_elements = A.numElements();
    char c;
    int i = 0;
    int j, k;
    Array<int, 1> Index(10), Length(10);
    int sep_length = separator_.length();

    for (j=0; j<10; j++)
      {
	Index(j) = 0;
	Length(j) = A.extent(j);
      }

    j = N-1;
    while ( (i<nb_elements) && (FileStream.good()) )
      {

	FileStream >> A(Index(0), Index(1), Index(2),
			Index(3), Index(4), Index(5),
			Index(6), Index(7), Index(8),
			Index(9));

	c = FileStream.peek();
	while ( (FileStream.good())
		&& ( (c<'0') || (c>'9') )
		&& (c!='.') && (c!='-')
		&& (c!='+') )
	  {
	    FileStream.ignore(1);
	    c = FileStream.peek();
	  }

	j = N-1;
	while ( (j>=0) && (Index(j)==Length(j)-1) )
	  {
	    Index(j) = 0;
	    j--;
	  }

	if (j!=-1)
	  Index(j)++;

	i++;
      }
    
#ifdef DEBUG_SELDONDATA_IO
    // Checks if all was read.
    if (i!=nb_elements)
      throw IOError("FormatText::Read(ifstream& FileStream, Array<TA, N>& A)",
		    to_str(i) + " elements were read instead of "
		    + to_str(nb_elements) + ".");
#endif

  }

  //! Writes a text file.
  template<class TA, int N>
  void FormatText::Write(Array<TA, N>& A, string FileName) const
  {

    ofstream FileStream;
    FileStream.open(FileName.c_str(), ofstream::out);
     
    FileStream.flags(flags_);
     
    if (precision_!=-1)
      FileStream.precision(precision_);
     
    if (width_!=-1)
      FileStream.width(width_);

#ifdef DEBUG_SELDONDATA_IO
    // Checks if the file was opened.
    if (!FileStream.is_open())
      throw IOError("FormatText::Write(Array<TA, N>& A, string FileName)",
		    "Unable to open file \"" + FileName + "\".");
#endif

    this->Write(A, FileStream);

    FileStream.close();

  }

  //! Writes a text file.
  template<class TA, int N>
  void FormatText::Write(Array<TA, N>& A, ofstream& FileStream) const
  {

#ifdef DEBUG_SELDONDATA_IO
    // Checks if the file ready.
    if (!FileStream.good())
      throw IOError("FormatText::Write(Array<TA, N>& A, ofstream& FileStream)",
		    "File is not ready.");
#endif

    int nb_elements = A.numElements();
    int i = 0;
    int j;
    Array<int, 1> Index(10), Length(10);

    for (j=0; j<10; j++)
      {
	Index(j) = 0;
	Length(j) = A.extent(j);
      }

    j = N-1;
    while ((i<nb_elements) && (FileStream.good()))
      {

	FileStream << A(Index(0), Index(1), Index(2),
			Index(3), Index(4), Index(5),
			Index(6), Index(7), Index(8),
			Index(9));

	j = N-1;
	while ( (j>=0) && (Index(j)==Length(j)-1) )
	  {
	    Index(j) = 0;
	    j--;
	  }
	 
	if (j!=-1)
	  Index(j)++;

	if ((j!=N-1) || (N==1))
	  FileStream << '\n';
	else
	  FileStream << separator_;
	 
	i++;
      }

  }


  //////////////////
  // FORMATNETCDF //
  //////////////////

#ifdef SELDONDATA_WITH_NETCDF

  //! Default constructor.
  template<class T>
  FormatNetCDF<T>::FormatNetCDF()  throw()
  {
  }

  //! Destructor.
  template<class T>
  FormatNetCDF<T>::~FormatNetCDF()  throw()
  {
  }

  /********/
  /* Grid */
  /********/

  //! Reads a netCDF file.
  template<class T>
  template<class TG>
  void FormatNetCDF<T>::Read(string FileName, string variable, RegularGrid<TG>& G) const
  {

    this->Read(FileName, variable, G.GetArray());

  }

  //! Reads a netCDF file.
  template<class T>
  template<class TG, int n>
  void FormatNetCDF<T>::Read(string FileName, string variable, GeneralGrid<TG, n>& G) const
  {

    this->Read(FileName, variable, G.GetArray());

  }

  /********/
  /* Data */
  /********/
  
  //! Reads a netCDF file.
  template<class T>
  template<class TD, int N, class TG>
  void FormatNetCDF<T>::Read(string FileName, string variable, Data<TD, N, TG>& D) const
  {

    this->Read(FileName, variable, D.GetArray());

  }

  /*********/
  /* Array */
  /*********/

  //! Reads a netCDF file.
  template<class T>
  template<class TA, int N>
  void FormatNetCDF<T>::Read(string FileName, string variable, Array<TA, N>& A) const
  {

    NcFile File(FileName.c_str());

#ifdef DEBUG_SELDONDATA_IO
    // Checks if the file is valid.
    if (!File.is_valid())
      throw IOError("FormatNetCDF<T>::Read(string FileName, Array<TA, N>& A)",
		    "\"" + FileName + "\" is not a valid netCDF file.");
#endif

    int Nb_vars = File.num_vars();

    int i(0);
    while ( (i<Nb_vars) && (string(File.get_var(i)->name()) != variable) )
      i++;

#ifdef DEBUG_SELDONDATA_IO
    // Checks whether the variable was found.
    if (i==Nb_vars)
      throw IOError("FormatNetCDF<T>::Read(string FileName, Array<TA, N>& A)",
		    "Unable to find variable \"" + variable
		    + "\" in \"" + FileName + "\".");
#endif

    NcVar* var = File.get_var(i);

#ifdef DEBUG_SELDONDATA_DIMENSION
    // Checks the dimension.
    if (var->num_dims() != N)
      throw WrongDim("FormatNetCDF<T>::Read(string FileName, Array<TA, N>& A)",
		     "Data has " + to_str(N) + "dimensions, but stored data has "
		     + to_str(var->num_dims()) + "dimensions.");
#endif

#ifdef DEBUG_SELDONDATA_INDICES
  long* input_dimensions = var->edges();
  for (i=0; i<var->num_dims(); i++)
    if (A.extent(i) > input_dimensions[i])
      throw WrongIndex("FormatNetCDF<T>::Read(string FileName, Array<TA, N>& A)",
		       "Array extent is " + to_str(A.extent(i))
		       + " along dimension #" + to_str(i)
		       + " , but it should not be strictly more than "
		       + to_str(input_dimensions[i]) + ".");
  delete[] input_dimensions;
#endif

  long* extents = new long[N];
  for (i=0; i<N; i++)
    extents[i] = A.extent(i);

  bool op = var->get(A.data(), extents);

#ifdef DEBUG_SELDONDATA_IO
    // Checks whether input operation succeeded.
    if (!op)
      throw IOError("FormatNetCDF<T>::Read(string FileName, Array<TA, N>& A)",
		    "Data type doesn't match type of stored values.");
#endif

  }

#endif


  ////////////////
  // FORMATGRIB //
  ////////////////

#ifdef SELDONDATA_WITH_GRIB

  //! Default constructor.
  template<class T>
  FormatGrib<T>::FormatGrib()  throw()
  {
  }

  //! Destructor.
  template<class T>
  FormatGrib<T>::~FormatGrib()  throw()
  {
  }

  /********/
  /* Grid */
  /********/

  //! Reads a Grib file.
  template<class T>
  template<class TG>
  void FormatGrib<T>::Read(string FileName, int variable, RegularGrid<TG>& G) const
  {

    this->Read(FileName, variable, G.GetArray());

  }

  //! Reads a Grib file.
  template<class T>
  template<class TG, int n>
  void FormatGrib<T>::Read(string FileName, int variable, GeneralGrid<TG, n>& G) const
  {

    this->Read(FileName, variable, G.GetArray());

  }

  /********/
  /* Data */
  /********/
  
  //! Reads a Grib file.
  template<class T>
  template<class TD, int N, class TG>
  void FormatGrib<T>::Read(string FileName, int variable, Data<TD, N, TG>& D) const
  {

    this->Read(FileName, variable, D.GetArray());

  }

  /*********/
  /* Array */
  /*********/

  //! Reads a Grib file.
  template<class T>
  template<class TA, int N>
  void FormatGrib<T>::Read(string FileName, int variable, Array<TA, N>& A) const
  {

    GRIBRecord grib_rec;
    FILE *grib_file;
    size_t n, m;
    size_t nrec(0);

    int status;
    
    grib_rec.buffer=NULL;
    grib_rec.pds_ext=NULL;
    grib_rec.gridpoints=NULL;

    grib_file = fopen(FileName.c_str(), "r");


    int nb_elements = A.numElements();
    int i = 0;
    int j, k;
    Array<int, 1> Index(10), Length(10);

    for (j=0; j<10; j++)
      {
	Index(j) = 0;
	Length(j) = A.extent(j);
      }

    j = N-1;
    while ((status = unpackgrib(grib_file, &grib_rec)) == 0)
      {

	if (grib_rec.param==variable)
	  {
	    
	    nrec++;
	    
	    for (n=0; n<grib_rec.ny; n++)
	      for (m=0; m<grib_rec.nx; m++)
#ifdef DEBUG_SELDONDATA_IO
		if (i<nb_elements)
#endif
		  {
		    A(Index(0), Index(1), Index(2),
		      Index(3), Index(4), Index(5),
		      Index(6), Index(7), Index(8),
		      Index(9))
		      = grib_rec.gridpoints[n][m];
		    
		    j = N-1;
		    while ( (j>=0) && (Index(j)==Length(j)-1) )
		      {
			Index(j) = 0;
			j--;
		      }
		    
		    if (j!=-1)
		      Index(j)++;
		    
		    i++;
		  }
#ifdef DEBUG_SELDONDATA_IO
		else
		  i++;
#endif

	  }

      }
    
#ifdef DEBUG_SELDONDATA_IO

    if (status == 1)
      throw IOError("FormatGrib::Read(string FileName, Array<TA, N>& A)",
		    "Read error after " + to_str(nrec) + " records.");

    if (i>nb_elements)
      throw IOError("FormatGrib::Read(string FileName, Array<TA, N>& A)",
		    "File \"" + FileName + "\" contains " + to_str(i)
		    + " elements for field #"
		    + to_str(variable) + ", but data has only "
		    + to_str(nb_elements) + " elements. All values must be read.");

    // Checks if all was read.
    if (i<nb_elements)
      {
	throw IOError("FormatGrib::Read(string FileName, Array<TA, N>& A)",
		    "Cannot find all values. File \"" + FileName + "\" contains "
		    + to_str(i) + " elements for field #"
		    + to_str(variable) + ", but data has "
		    + to_str(nb_elements) + " elements.");

	if (status == -1)
	  throw IOError("FormatGrib::Read(string FileName, Array<TA, N>& A)",
			"End of file found. " + to_str(i)
			+ " elements were read for field #" + to_str(variable)
			+ ", but data has " + to_str(nb_elements) + " elements.");
      }

#endif
    
  }

#endif


  ///////////////////
  // FORMATCHIMERE //
  ///////////////////

  //! Default constructor.
  FormatChimere::FormatChimere()  throw()
  {
    date_ = -1;
  }

  //! Constructor.
  FormatChimere::FormatChimere(int date)  throw()
  {
    date_ = date;
  }

  //! Destructor.
  FormatChimere::~FormatChimere()  throw()
  {
  }

  //! Sets the date.
  /*!
    \param date date.
  */
  void FormatChimere::SetDate(int date)
  {
    date_ = date;
  }

  //! Get the date.
  /*!
    \return The date.
  */
  int FormatChimere::GetDate() const
  {
    return date_;
  }

  /********/
  /* Data */
  /********/
 
  //! Reads a file in "Chimere" format.
  template<class TD, int N, class TG>
  void FormatChimere::Read(string FileName, Data<TD, N, TG>& D, int nb_lines) const
  {

    this->Read(FileName, D.GetArray(), nb_lines);

  }

  //! Reads a file in "Chimere" format.
  template<class TD, int N, class TG>
  void FormatChimere::Read(ifstream& FileStream, Data<TD, N, TG>& D, int nb_lines) const
  {

    this->Read(FileStream, D.GetArray(), nb_lines);

  }

  /*********/
  /* Array */
  /*********/

  //! Reads a file in "Chimere" format.
  template<class TA, int N>
  void FormatChimere::Read(string FileName, Array<TA, N>& A, int nb_lines) const
  {

    ifstream FileStream;
    FileStream.open(FileName.c_str(), ifstream::in);
    FileStream.flags(fstream::scientific | fstream::skipws);

#ifdef DEBUG_SELDONDATA_IO
    // Checks if the file was opened.
    if (!FileStream.is_open())
      throw IOError("FormatChimere::Read(string FileName, Array<TA, N>& A, int nb_lines)",
		    "Unable to open file \"" + FileName + "\".");
#endif

    this->Read(FileStream, A);

    FileStream.close();

  }

  //! Reads a file in "Chimere" format.
  template<class TA, int N>
  void FormatChimere::Read(ifstream& FileStream, Array<TA, N>& A, int nb_lines) const
  {

#ifdef DEBUG_SELDONDATA_IO
    // Checks if the file ready.
    if (!FileStream.good())
      throw IOError("FormatChimere::Read(ifstream& FileStream, Array<TA, N>& A, int nb_lines)",
		    "File is not ready.");
#endif

    int nb_elements = A.numElements();
    int i, j, k;
    char c;
    bool reading = false;
    TA temp;
    int date, level;
    Array<int, 1> Index(10), Length(10);

    for (j=0; j<10; j++)
      {
	Index(j) = 0;
	Length(j) = A.extent(j);
      }

    int nb_elements_per_line = Length(N-1);

    if (nb_lines==-1)
      if (N==2)
	nb_lines = 1;
      else if (N==3)
	nb_lines = Length(1);
      else
	nb_lines = nb_elements
	  / nb_elements_per_line
	  / Length(0)
	  / Length(1);

    fstream::fmtflags flags = FileStream.flags();
     
    c = FileStream.peek();
    while ( (FileStream.good())
	    && ( (c<'0') || (c>'9') )
	    && (c!='.') && (c!='-')
	    && (c!='+') )
      {
	FileStream.ignore(1);
	c = FileStream.peek();
      }

    FileStream.flags(ifstream::dec | fstream::skipws);
    FileStream >> date;
    FileStream.flags(flags);

    reading = ((date_==-1) || (date==date_));

    string temp_str;
    while ( (!reading) && (FileStream.good()) )
      {
	for (i=0; i<nb_lines+1; i++)
	  getline(FileStream, temp_str);

	FileStream.flags(ifstream::dec | fstream::skipws);
	FileStream >> date;
	FileStream.flags(flags);
	
	reading = ((date_==-1) || (date==date_));
      }

    i = 0;
    while ((i<nb_elements) && (FileStream.good()))
      {

	// Reads level.
	FileStream.flags(ifstream::dec | fstream::skipws);
	FileStream >> level;
	FileStream.flags(flags);

	k = 0;
	j = N-1;

	while ((k<nb_lines * nb_elements_per_line)
	       && (FileStream.good()))
	  {

	    c = FileStream.peek();
	    while ( (FileStream.good())
		    && ( (c<'0') || (c>'9') )
		    && (c!='.') && (c!='-')
		    && (c!='+') )
	      {
		FileStream.ignore(1);
		c = FileStream.peek();
	      }
	     
	    // Reads level.
	    if (reading)
	      FileStream >> A(Index(0), Index(1), Index(2),
			      Index(3), Index(4), Index(5),
			      Index(6), Index(7), Index(8),
			      Index(9));
	    else
	      FileStream >> temp;

	    if (reading)
	      {
		j = N-1;
		while ( (j>=0) && (Index(j)==Length(j)-1) )
		  {
		    Index(j) = 0;
		    j--;
		  }
		 
		if (j!=-1)
		  Index(j)++;
	      }
	     
	    k++;
	  }
	 
	if (reading)
	  i += k;
	 
	c = FileStream.peek();
	while ( (FileStream.good())
		&& ( (c<'0') || (c>'9') )
		&& (c!='.') && (c!='-')
		&& (c!='+') )
	  {
	    FileStream.ignore(1);
	    c = FileStream.peek();
	  }
	FileStream.flags(ifstream::dec | fstream::skipws);
	FileStream >> date;
	FileStream.flags(flags);

	reading = (reading || (date_==-1) || (date==date_));

      }

#ifdef DEBUG_SELDONDATA_IO
    // Checks if all was read.
    if (!reading)
      throw IOError("FormatChimere::Read(ifstream& FileStream, Array<TA, N>& A)",
		    "The date was not found.");
    // Checks if all was read.
    if (i!=nb_elements)
      throw IOError("FormatChimere::Read(ifstream& FileStream, Array<TA, N>& A)",
		    to_str(i) + " elements were read instead of "
		    + to_str(nb_elements) + ".");
#endif

  }


}  // namespace SeldonData.

#define FILE_SELDONDATA_FORMAT_CXX
#endif
