#pragma once
#using <mscorlib.dll>
//#include "Scanner.h"
#include "CTokenTable.h"
#include "CToken.h"
#include <windows.h>
//#include "Lexer.h"
//#include "CPLexer.h"
//#include "tokstr.h"

using namespace System;
using namespace System::Collections;

namespace Wrapper
{
  public __gc class Token
  {
  public:

	String *m_text;   // token text

	int m_kind;      // kind of token

	int m_linenum;   // line number of token place

	String *m_name;   // token name

  };

  public __gc class CWrapperScanner
  {
  private:
   // Scanner* unmanagedClass;
    typedef bool ( *dll_parseFile)(std::string , CTokenTable<CToken> &);

    String *inFile;

    CTokenTable<CToken>* theTokenTable;

    ArrayList *TokenArray;// copy of TokenTable

  public:
    CWrapperScanner(void);

    ~CWrapperScanner(void);

    void setInFile(System::String *s);

    bool scan(void); // get token from IN-File

    void StringToStdStr(String* netval,std::string& stdval);

    String* StdStrToString(const std::string& stdval);

    //void getTokenTable(ArrayList *arr);
    ArrayList* getTokenTable(void);

  };
}
