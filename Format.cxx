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


//    ///////////////////
//    // FORMATCHIMERE //
//    ///////////////////

//    //! Default constructor.
//    FormatChimere::FormatChimere()  throw()
//    {
//    }

//    //! Destructor.
//    FormatChimere::~FormatChimere()  throw()
//    {
//    }

//    /********/
//    /* Data */
//    /********/
 
//    //! Reads a file in "Chimere" format.
//    template<class TD, int N, class TG>
//    void FormatChimere::Read(string FileName, int date, Data<TD, N, TG>& D) const
//    {

//      this->Read(FileName, date, D.GetArray());

//    }

//    //! Writes a file in "Chimere" format.
//    template<class TD, int N, class TG>
//    void FormatChimere::Write(Data<TD, N, TG>& D, int date, string FileName) const
//    {

//      this->Write(D.GetArray(), date, FileName);

//    }

//    /*********/
//    /* Array */
//    /*********/

//    //! Reads a file in "Chimere" format.
//    template<class TA, int N>
//    void FormatChimere::Read(string FileName, int date, Array<TA, N>& A) const
//    {

//      ifstream File(FileName.c_str());
//      int t, h, i, j, k, z;TA x;
//      int Nt = A.extent(0), Nlon = A.extent(1), Nlat = A.extent(2),
//        Nz = A.numElements() / (Nt * Nlon * Nlat);
//      string line;

//      File >> t; File >> z;
//      while ( (File.good()) && (t!=date) )
//        for (k=0; k<Nz; k++)
//  	{
//  	  // Read the field.
//  	  for (j=0; j<Nlat; j++)
//  	    getline(File, line);
//  	  // Read the date.
//  	  File >> t;
//  	  // Read level number.
//  	  File >> z;
//  	}

//      for (h=0; h<Nt; h++)
//        for (k=0; k<Nz; k++)
//  	{
//  	  // Read the field.
//  	  for (j=0; j<Nlat; j++)
//  	    for (i=0; i<Nlon; i++)
//  	      File >> scientific >> A(h, i, j, k);
//  	  // Read the date.
//  	  File >> t;
//  	  // Read level number.
//  	  File >> z;
//  	}
    
//    }

//    //! Writes a file in "Chimere" format.
//    template<class TA, int N>
//    void FormatChimere::Write(Array<TA, N>& A, int date, string FileName) const
//    {

//  //     string format = "%" + format_ + "%c";

//  //     int NbElements = A.numElements();

//  //     T* data = A.data();

//  //     char* elt = new char[100];

//  //     for (int i=0; i<NbElements-1; i++)
//  //       {
//  // 	sprintf(elt, format.c_str(), data[i], ' ');
//  // 	fwrite(elt, sizeof(char), strlen(elt), FileStream);
//  //       }
//  //     format = "%" + format_;
//  //     sprintf(elt, format.c_str(), data[NbElements-1]);
//  //     fwrite(elt, sizeof(char), strlen(elt), FileStream);

//    }

}  // namespace SeldonData.

#define FILE_SELDONDATA_FORMAT_CXX
#endif
