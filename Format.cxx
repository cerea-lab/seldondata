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

namespace SeldonData
{


  ////////////
  // FORMAT //
  ////////////
  
  //! Default constructor.
  template<class T>
  Format<T>::Format()  throw()
  {
  }

  //! Destructor.
  template<class T>
  Format<T>::~Format()  throw()
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

    this->Read(FileName, G.GetValues());

  }

  //! Reads a binary file.
  template<class T>
  template<class TG>
  void FormatBinary<T>::Read(ifstream& FileStream, RegularGrid<TG>& G) const
  {

    this->Read(FileStream, G.GetValues());

  }

  //! Reads a binary file.
  template<class T>
  template<class TG, int n>
  void FormatBinary<T>::Read(string FileName, GeneralGrid<TG, n>& G) const
  {

    this->Read(FileName, G.GetValues());

  }

  //! Reads a binary file.
  template<class T>
  template<class TG, int n>
  void FormatBinary<T>::Read(ifstream& FileStream, GeneralGrid<TG, n>& G) const
  {

    this->Read(FileStream, G.GetValues());

  }

  //! Writes a binary file.
  template<class T>
  template<class TG>
  void FormatBinary<T>::Write(RegularGrid<TG>& G, string FileName) const
  {

    this->Write(G.GetValues(), FileName);

  }

  //! Writes a binary file.
  template<class T>
  template<class TG>
  void FormatBinary<T>::Write(RegularGrid<TG>& G, ofstream FileStream) const
  {

    this->Write(G.GetValues(), FileStream);
    
  }

  //! Writes a binary file.
  template<class T>
  template<class TG, int n>
  void FormatBinary<T>::Write(GeneralGrid<TG, n>& G, string FileName) const
  {

    this->Write(G.GetValues(), FileName);

  }

  //! Writes a binary file.
  template<class T>
  template<class TG, int n>
  void FormatBinary<T>::Write(GeneralGrid<TG, n>& G, ofstream FileStream) const
  {

    this->Write(G.GetValues(), FileStream);
    
  }

  /********/
  /* Data */
  /********/
  
  //! Reads a binary file.
  template<class T>
  template<class TD, int N>
  void FormatBinary<T>::Read(string FileName, Data<TD, N>& D) const
  {

    this->Read(FileName, D.GetArray());

  }

  //! Reads a binary file.
  template<class T>
  template<class TD, int N>
  void FormatBinary<T>::Read(ifstream& FileStream, Data<TD, N>& D) const
  {

    this->Read(FileStream, D.GetArray());

  }

  //! Writes a binary file.
  template<class T>
  template<class TD, int N>
  void FormatBinary<T>::Write(Data<TD, N>& D, string FileName) const
  {

    this->Write(D.GetArray(), FileName);

  }

  //! Writes a binary file.
  template<class T>
  template<class TD, int N>
  void FormatBinary<T>::Write(Data<TD, N>& D, ofstream FileStream) const
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
    FileStream.open(FileName.c_str(), ios::in|ios::binary);
    this->Read(FileStream, A);
    FileStream.close();

  }

  //! Reads a binary file.
  template<class T>
  template<int N>
  void FormatBinary<T>::Read(ifstream& FileStream, Array<T, N>& A) const
  {

    unsigned long DataSize = sizeof(T) * A.numElements();
    T* data = A.data();

    // Checks file length.
    FileStream.seekg(0, ios::end);
    unsigned long FileSize = FileStream.tellg();

    if (DataSize>FileSize)
      throw IOError("FormatBinary<T>::Read(ifstream& FileStream, Array<T, N>& A)",
		    "Reading " + to_str(DataSize) + " bytes is impossible." +
		    " The input file is only " + to_str(FileSize) + " bytes-long.");

    FileStream.seekg(0, ios::beg);
    FileStream.read(reinterpret_cast<char*>(data), DataSize);
    
  }

//    //! Reads a binary file.
//    template<class T>
//    template<class TA, int N>
//    void FormatBinary<T>::Read(ifstream FileStream, Array<TA, N>& A) const
//    {

//      int NbElements = A.numElements();

//      T* data = new T[NbElements];
//      TA* data0 = A.data();

//      fread(data, sizeof(T), NbElements, FileStream);

//      for (int i=0; i<NbElements; i++)
//        data0[i] = data[i];

//    }

//    //! Writes a binary file.
//    template<class T>
//    template<int N>
//    void FormatBinary<T>::Write(Array<T, N>& A, string FileName) const
//    {

//      ofstream f = fopen(FileName.c_str(), "wb");
//      this->Write(A, f);
//      fclose(f);
    
//    }

//    //! Writes a binary file.
//    template<class T>
//    template<class TA, int N>
//    void FormatBinary<T>::Write(Array<TA, N>& A, string FileName) const
//    {

//      ofstream f = fopen(FileName.c_str(), "wb");
//      this->Write(A, f);
//      fclose(f);

//    }

//    //! Writes a binary file.
//    template<class T>
//    template<int N>
//    void FormatBinary<T>::Write(Array<T, N>& A, ofstream FileStream) const
//    {

//      int NbElements = A.numElements();

//      T* data = A.data();

//      fwrite(data, sizeof(T), NbElements, FileStream);
    
//    }

//    //! Writes a binary file.
//    template<class T>
//    template<class TA, int N>
//    void FormatBinary<T>::Write(Array<TA, N>& A, ofstream FileStream) const
//    {

//      int NbElements = G.A.numElements();

//      T* data = new T[NbElements];
//      TG* data0 = A.data();

//      for (int i=0; i<NbElements; i++)
//        data[i] = data0[i];

//      fwrite(data, sizeof(T), NbElements, FileStream);

//    }


//    ////////////////
//    // FORMATTEXT //
//    ////////////////

//    //! Default constructor.
//    template<class T>
//    FormatText<T>::FormatText()  throw()
//    {
//      format_ = "e";
//    }

//    //! Main constructor.
//    template<class T>
//    FormatText<T>::FormatText(string format)  throw()
//    {
//      format_ = format;
//    }

//    //! Destructor.
//    template<class T>
//    FormatText<T>::~FormatText()  throw()
//    {

//    }

//    /********/
//    /* Grid */
//    /********/

//    //! Reads a text file.
//    template<class T>
//    template<class TG>
//    void FormatText<T>::Read(string FileName, RegularGrid<TG>& G) const
//    {

//      this->Read(FileName, G.GetValues());

//    }

//    //! Reads a text file.
//    template<class T>
//    template<class TG>
//    void FormatText<T>::Read(ifstream FileStream, RegularGrid<TG>& G) const
//    {

//      this->Read(FileStream, G.GetValues());

//    }

//    //! Reads a text file.
//    template<class T>
//    template<class TG, int n>
//    void FormatText<T>::Read(string FileName, GeneralGrid<TG, n>& G) const
//    {

//      this->Read(FileName, G.GetValues());

//    }

//    //! Reads a text file.
//    template<class T>
//    template<class TG, int n>
//    void FormatText<T>::Read(ifstream FileStream, GeneralGrid<TG, n>& G) const
//    {

//      this->Read(FileStream, G.GetValues());

//    }

//    //! Writes a text file.
//    template<class T>
//    template<class TG>
//    void FormatText<T>::Write(RegularGrid<TG>& G, string FileName) const
//    {

//      this->Write(G.GetValues(), FileName);

//    }

//    //! Writes a text file.
//    template<class T>
//    template<class TG>
//    void FormatText<T>::Write(RegularGrid<TG>& G, ofstream FileStream) const
//    {

//      this->Write(G.GetValues(), FileStream);
    
//    }

//    //! Writes a text file.
//    template<class T>
//    template<class TG, int n>
//    void FormatText<T>::Write(GeneralGrid<TG, n>& G, string FileName) const
//    {

//      this->Write(G.GetValues(), FileName);

//    }

//    //! Writes a text file.
//    template<class T>
//    template<class TG, int n>
//    void FormatText<T>::Write(GeneralGrid<TG, n>& G, ofstream FileStream) const
//    {

//      this->Write(G.GetValues(), FileStream);
    
//    }

//    /********/
//    /* Data */
//    /********/
  
//    //! Reads a text file.
//    template<class T>
//    template<class TD, int N>
//    void FormatText<T>::Read(string FileName, Data<TD, N>& D) const
//    {

//      this->Read(FileName, D.GetArray());

//    }

//    //! Reads a text file.
//    template<class T>
//    template<class TD, int N>
//    void FormatText<T>::Read(ifstream FileStream, Data<TD, N>& D) const
//    {

//      this->Read(FileStream, D.GetArray());

//    }

//    //! Writes a text file.
//    template<class T>
//    template<class TD, int N>
//    void FormatText<T>::Write(Data<TD, N>& D, string FileName) const
//    {

//      this->Write(D.GetArray(), FileName);

//    }

//    //! Writes a text file.
//    template<class T>
//    template<class TD, int N>
//    void FormatText<T>::Write(Data<TD, N>& D, ofstream FileStream) const
//    {

//      this->Write(D.GetArray(), FileStream);

//    }

//    /*********/
//    /* Array */
//    /*********/

//    //! Reads a text file.
//    template<class T>
//    template<class TA, int N>
//    void FormatText<T>::Read(string FileName, Array<TA, N>& A) const
//    {

//      ifstream f = fopen(FileName.c_str(), "r");
//      this->Read(f, A);
//      fclose(f);

//    }

//    //! Reads a text file.
//    template<class T>
//    template<int N>
//    void FormatText<T>::Read(ifstream FileStream, Array<T, N>& A) const
//    {

//      string format = "%" + format_;

//      int NbElements = A.numElements();
//      T* data = A.data();

//      for (int i=0; i<NbElements; i++)
//        fscanf(FileStream, format, data + i * sizeof(T));
    
//    }

//    //! Reads a text file.
//    template<class T>
//    template<class TA, int N>
//    void FormatText<T>::Read(ifstream FileStream, Array<TA, N>& A) const
//    {

//      string format = "%" + format_;

//      int NbElements = A.numElements();

//      T* data = new T[NbElements];
//      TG* data0 = A.data();

//      for (int i=0; i<NbElements; i++)
//        fscanf(FileStream, format, data + i * sizeof(T));

//      for (int i=0; i<NbElements; i++)
//        data0[i] = data[i];

//    }

//    //! Writes a text file.
//    template<class T>
//    template<class TA, int N>
//    void FormatText<T>::Write(Array<TA, N>& A, string FileName) const
//    {

//      ofstream f = fopen(FileName.c_str(), "wb");
//      this->Write(A, f);
//      fclose(f);

//    }

//    //! Writes a text file.
//    template<class T>
//    template<int N>
//    void FormatText<T>::Write(Array<T, N>& A, ofstream FileStream) const
//    {

//      string format = "%" + format_ + "%c";

//      int NbElements = A.numElements();

//      T* data = A.data();

//      char* elt = new char[100];

//      for (int i=0; i<NbElements-1; i++)
//        {
//  	sprintf(elt, format.c_str(), data[i], ' ');
//  	fwrite(elt, sizeof(char), strlen(elt), FileStream);
//        }
//      format = "%" + format_;
//      sprintf(elt, format.c_str(), data[NbElements-1]);
//      fwrite(elt, sizeof(char), strlen(elt), FileStream);

//    }

//    //! Writes a text file.
//    template<class T>
//    template<class TA, int N>
//    void FormatText<T>::Write(Array<TA, N>& A, ofstream FileStream) const
//    {

//      string format = "%" + format_ + "%c";

//      int NbElements = A.numElements();

//      T* data = new T[NbElements];
//      TA* data0 = A.data();

//      for (int i=0; i<NbElements; i++)
//        data[i] = data0[i];

//      char* elt = new char[100];

//      for (int i=0; i<NbElements-1; i++)
//        {
//  	sprintf(elt, format.c_str(), data[i], ' ');
//  	fwrite(elt, sizeof(char), strlen(elt), FileStream);
//        }
//      format = "%" + format_;
//      sprintf(elt, format.c_str(), data[NbElements-1]);
//      fwrite(elt, sizeof(char), strlen(elt), FileStream);

//    }


//    ///////////////////
//    // FORMATCHIMERE //
//    ///////////////////

//    //! Default constructor.
//    template<class T>
//    FormatChimere<T>::FormatChimere()  throw()
//    {
//    }

//    //! Destructor.
//    template<class T>
//    FormatChimere<T>::~FormatChimere()  throw()
//    {
//    }

//    /********/
//    /* Data */
//    /********/
 
//    //! Reads a file in "Chimere" format.
//    template<class T>
//    template<class TD, int N>
//    void FormatChimere<T>::Read(string FileName, int date, Data<TD, N>& D) const
//    {

//      this->Read(FileName, date, D.GetArray());

//    }

//    //! Writes a file in "Chimere" format.
//    template<class T>
//    template<class TD, int N>
//    void FormatChimere<T>::Write(Data<TD, N>& D, int date, string FileName) const
//    {

//      this->Write(D.GetArray(), date, FileName);

//    }

//    /*********/
//    /* Array */
//    /*********/

//    //! Reads a file in "Chimere" format.
//    template<class T>
//    template<class TA, int N>
//    void FormatChimere<T>::Read(string FileName, int date, Array<TA, N>& A) const
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
//    template<class T>
//    template<class TA, int N>
//    void FormatChimere<T>::Write(Array<TA, N>& A, int date, string FileName) const
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
