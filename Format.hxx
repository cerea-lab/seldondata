#ifndef FILE_FORMAT_HXX

#include <iostream>
using std::cout;
using std::endl;
#include <string>

namespace SeldonData
{

  template<class T>
  class Format
  {

  protected:

  public:
    Format();
    ~Format();

  };


  template<class T>
  class FormatBinary: public Format<T>
  {

  protected:

  public:
    FormatBinary();
    ~FormatBinary();

    // Grid.

    template<class TG, int N>
    void Read(string FileName, GeneralGrid<TG, N>& G) const;
    template<class TG, int N>
    void Read(FILE* FileDes, GeneralGrid<TG, N>& G) const;

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

  template<class T>
  class FormatText: public Format<T>
  {

  protected:
    string format_;

  public:
    FormatText();
    FormatText(string format);
    ~FormatText();

    // Grid.

    template<class TG, int N>
    void Read(string FileName, GeneralGrid<TG, N>& G) const;
    template<class TG, int N>
    void Read(FILE* FileDes, GeneralGrid<TG, N>& G) const;

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

}  // namespace SeldonData.

#define FILE_FORMAT_HXX
#endif
