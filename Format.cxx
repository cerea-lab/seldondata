#ifndef FILE_FORMAT_CXX

#include "Format.hxx"

namespace SeldonData
{


  ////////////
  // FORMAT //
  ////////////
  
  template<class T>
  Format<T>::Format()
  {
    
  }

  template<class T>
  Format<T>::~Format()
  {
    
  }


  //////////////////
  // FORMATBINARY //
  //////////////////

  template<class T>
  FormatBinary<T>::FormatBinary()
  {

  }

  template<class T>
  FormatBinary<T>::~FormatBinary()
  {

  }

  /********/
  /* Grid */
  /********/

  template<class T>
  template<class TG, int n>
  void FormatBinary<T>::Read(string FileName, GeneralGrid<TG, n>& G) const
  {

    this->Read(FileName, G.GetValues());

  }

  template<class T>
  template<class TG, int n>
  void FormatBinary<T>::Read(FILE* FileDes, GeneralGrid<TG, n>& G) const
  {

    this->Read(FileDes, G.GetValues());

  }

  template<class T>
  template<class TG, int n>
  void FormatBinary<T>::Write(GeneralGrid<TG, n>& G, string FileName) const
  {

    this->Write(G.GetValues(), FileName);

  }

  template<class T>
  template<class TG, int n>
  void FormatBinary<T>::Write(GeneralGrid<TG, n>& G, FILE* FileDes) const
  {

    this->Write(G.GetValues(), FileDes);
    
  }

  /********/
  /* Data */
  /********/
  
  template<class T>
  template<class TD, int N>
  void FormatBinary<T>::Read(string FileName, Data<TD, N>& D) const
  {

    this->Read(FileName, D.GetArray());

  }

  template<class T>
  template<class TD, int N>
  void FormatBinary<T>::Read(FILE* FileDes, Data<TD, N>& D) const
  {

    this->Read(FileDes, D.GetArray());

  }

  template<class T>
  template<class TD, int N>
  void FormatBinary<T>::Write(Data<TD, N>& D, string FileName) const
  {

    this->Write(D.GetArray(), FileName);

  }

  template<class T>
  template<class TD, int N>
  void FormatBinary<T>::Write(Data<TD, N>& D, FILE* FileDes) const
  {

    this->Write(D.GetArray(), FileDes);

  }

  /*********/
  /* Array */
  /*********/

  template<class T>
  template<int N>
  void FormatBinary<T>::Read(string FileName, Array<T, N>& A) const
  {

    FILE* f = fopen(FileName.c_str(), "rb");
    this->Read(f, A);
    fclose(f);
    
  }

  template<class T>
  template<class TA, int N>
  void FormatBinary<T>::Read(string FileName, Array<TA, N>& A) const
  {

    FILE* f = fopen(FileName.c_str(), "rb");
    this->Read(f, A);
    fclose(f);

  }

  template<class T>
  template<int N>
  void FormatBinary<T>::Read(FILE* FileDes, Array<T, N>& A) const
  {

    int NbElements = A.numElements();

    T* data = A.data();

    fread(data, sizeof(T), NbElements, FileDes);
    
  }

  template<class T>
  template<class TA, int N>
  void FormatBinary<T>::Read(FILE* FileDes, Array<TA, N>& A) const
  {

    int NbElements = A.numElements();

    T* data = new T[NbElements];
    TA* data0 = A.data();

    fread(data, sizeof(T), NbElements, FileDes);

    for (int i=0; i<NbElements; i++)
      data0[i] = data[i];

  }

  template<class T>
  template<int N>
  void FormatBinary<T>::Write(Array<T, N>& A, string FileName) const
  {

    FILE* f = fopen(FileName.c_str(), "wb");
    this->Write(A, f);
    fclose(f);
    
  }

  template<class T>
  template<class TA, int N>
  void FormatBinary<T>::Write(Array<TA, N>& A, string FileName) const
  {

    FILE* f = fopen(FileName.c_str(), "wb");
    this->Write(A, f);
    fclose(f);

  }

  template<class T>
  template<int N>
  void FormatBinary<T>::Write(Array<T, N>& A, FILE* FileDes) const
  {

    int NbElements = A.numElements();

    T* data = A.data();

    fwrite(data, sizeof(T), NbElements, FileDes);
    
  }

  template<class T>
  template<class TA, int N>
  void FormatBinary<T>::Write(Array<TA, N>& A, FILE* FileDes) const
  {

    int NbElements = G.A.numElements();

    T* data = new T[NbElements];
    TG* data0 = A.data();

    for (int i=0; i<NbElements; i++)
      data[i] = data0[i];

    fwrite(data, sizeof(T), NbElements, FileDes);

  }


  ////////////////
  // FORMATTEXT //
  ////////////////

  template<class T>
  FormatText<T>::FormatText()
  {
    format_ = "e";
  }

  template<class T>
  FormatText<T>::FormatText(string format)
  {
    format_ = format;
  }

  template<class T>
  FormatText<T>::~FormatText()
  {

  }

  /********/
  /* Grid */
  /********/

  template<class T>
  template<class TG, int n>
  void FormatText<T>::Read(string FileName, GeneralGrid<TG, n>& G) const
  {

    this->Read(FileName, G.GetValues());

  }

  template<class T>
  template<class TG, int n>
  void FormatText<T>::Read(FILE* FileDes, GeneralGrid<TG, n>& G) const
  {

    this->Read(FileDes, G.GetValues());

  }

  template<class T>
  template<class TG, int n>
  void FormatText<T>::Write(GeneralGrid<TG, n>& G, string FileName) const
  {

    this->Write(G.GetValues(), FileName);

  }

  template<class T>
  template<class TG, int n>
  void FormatText<T>::Write(GeneralGrid<TG, n>& G, FILE* FileDes) const
  {

    this->Write(G.GetValues(), FileDes);
    
  }

  /********/
  /* Data */
  /********/
  
  template<class T>
  template<class TD, int N>
  void FormatText<T>::Read(string FileName, Data<TD, N>& D) const
  {

    this->Read(FileName, D.GetArray());

  }

  template<class T>
  template<class TD, int N>
  void FormatText<T>::Read(FILE* FileDes, Data<TD, N>& D) const
  {

    this->Read(FileDes, D.GetArray());

  }

  template<class T>
  template<class TD, int N>
  void FormatText<T>::Write(Data<TD, N>& D, string FileName) const
  {

    this->Write(D.GetArray(), FileName);

  }

  template<class T>
  template<class TD, int N>
  void FormatText<T>::Write(Data<TD, N>& D, FILE* FileDes) const
  {

    this->Write(D.GetArray(), FileDes);

  }

  /*********/
  /* Array */
  /*********/

  template<class T>
  template<class TA, int N>
  void FormatText<T>::Read(string FileName, Array<TA, N>& A) const
  {

    FILE* f = fopen(FileName.c_str(), "r");
    this->Read(f, A);
    fclose(f);

  }

  template<class T>
  template<int N>
  void FormatText<T>::Read(FILE* FileDes, Array<T, N>& A) const
  {

    string format = "%" + format_;

    int NbElements = A.numElements();
    T* data = A.data();

    for (int i=0; i<NbElements; i++)
      fscanf(FileDes, format, data + i * sizeof(T));
    
  }

  template<class T>
  template<class TA, int N>
  void FormatText<T>::Read(FILE* FileDes, Array<TA, N>& A) const
  {

    string format = "%" + format_;

    int NbElements = A.numElements();

    T* data = new T[NbElements];
    TG* data0 = A.data();

    for (int i=0; i<NbElements; i++)
      fscanf(FileDes, format, data + i * sizeof(T));

    for (int i=0; i<NbElements; i++)
      data0[i] = data[i];

  }

  template<class T>
  template<class TA, int N>
  void FormatText<T>::Write(Array<TA, N>& A, string FileName) const
  {

    FILE* f = fopen(FileName.c_str(), "wb");
    this->Write(A, f);
    fclose(f);

  }

  template<class T>
  template<int N>
  void FormatText<T>::Write(Array<T, N>& A, FILE* FileDes) const
  {

    string format = "%" + format_ + "%c";

    int NbElements = A.numElements();

    T* data = A.data();

    char* elt = new char[100];

    for (int i=0; i<NbElements-1; i++)
      {
	sprintf(elt, format.c_str(), data[i], ' ');
	fwrite(elt, sizeof(char), strlen(elt), FileDes);
      }
    format = "%" + format_;
    sprintf(elt, format.c_str(), data[NbElements-1]);
    fwrite(elt, sizeof(char), strlen(elt), FileDes);

  }

  template<class T>
  template<class TA, int N>
  void FormatText<T>::Write(Array<TA, N>& A, FILE* FileDes) const
  {

    string format = "%" + format_ + "%c";

    int NbElements = A.numElements();

    T* data = new T[NbElements];
    TA* data0 = A.data();

    for (int i=0; i<NbElements; i++)
      data[i] = data0[i];

    char* elt = new char[100];

    for (int i=0; i<NbElements-1; i++)
      {
	sprintf(elt, format.c_str(), data[i], ' ');
	fwrite(elt, sizeof(char), strlen(elt), FileDes);
      }
    format = "%" + format_;
    sprintf(elt, format.c_str(), data[NbElements-1]);
    fwrite(elt, sizeof(char), strlen(elt), FileDes);

  }


  /////////////////
  // FORMATECMXF //
  /////////////////

  template<class T>
  FormatECMWF<T>::FormatECMWF()
  {
  }

  template<class T>
  FormatECMWF<T>::~FormatECMWF()
  {
  }

  /********/
  /* Data */
  /********/
  
  template<class T>
  template<class TD, int N>
  void FormatECMWF<T>::Read(string FileName, int date, Data<TD, N>& D) const
  {

    this->Read(FileName, date, D.GetArray());

  }

  template<class T>
  template<class TD, int N>
  void FormatECMWF<T>::Write(Data<TD, N>& D, int date, string FileName) const
  {

    this->Write(D.GetArray(), date, FileName);

  }

  /*********/
  /* Array */
  /*********/

  template<class T>
  template<class TA, int N>
  void FormatECMWF<T>::Read(string FileName, int date, Array<TA, N>& A) const
  {

    ifstream File(FileName.c_str());
    int t, h, i, j, k, z;TA x;
    int Nt = A.extent(0), Nlon = A.extent(1), Nlat = A.extent(2),
      Nz = A.numElements() / (Nt * Nlon * Nlat);
    string line;

    File >> t; File >> z;
    while ( (File.good()) && (t!=date) )
      for (k=0; k<Nz; k++)
	{
	  // Read the field.
	  for (j=0; j<Nlat; j++)
	    getline(File, line);
	  // Read the date.
	  File >> t;
	  // Read level number.
	  File >> z;
	}

    for (h=0; h<Nt; h++)
      for (k=0; k<Nz; k++)
	{
	  // Read the field.
	  for (j=0; j<Nlat; j++)
	    for (i=0; i<Nlon; i++)
	      File >> scientific >> A(h, i, j, k);
	  // Read the date.
	  File >> t;
	  // Read level number.
	  File >> z;
	}
    
  }

  template<class T>
  template<class TA, int N>
  void FormatECMWF<T>::Write(Array<TA, N>& A, int date, string FileName) const
  {

//     string format = "%" + format_ + "%c";

//     int NbElements = A.numElements();

//     T* data = A.data();

//     char* elt = new char[100];

//     for (int i=0; i<NbElements-1; i++)
//       {
// 	sprintf(elt, format.c_str(), data[i], ' ');
// 	fwrite(elt, sizeof(char), strlen(elt), FileDes);
//       }
//     format = "%" + format_;
//     sprintf(elt, format.c_str(), data[NbElements-1]);
//     fwrite(elt, sizeof(char), strlen(elt), FileDes);

  }

}  // namespace SeldonData.

#define FILE_FORMAT_CXX
#endif
