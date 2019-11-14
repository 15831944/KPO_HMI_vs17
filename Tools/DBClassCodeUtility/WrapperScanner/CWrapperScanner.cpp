#include "CWrapperScanner.h"
#using <mscorlib.dll>

using namespace System::Runtime::InteropServices;

Wrapper::CWrapperScanner::CWrapperScanner(void)
{
  //unmanagedClass = new Scanner();  
  // token table safe tokens
  theTokenTable = new CTokenTable<CToken>();
  TokenArray = new ArrayList();
}

Wrapper::CWrapperScanner::~CWrapperScanner(void)
{
  //delete unmanagedClass;
  theTokenTable->clear();
  TokenArray->Clear();
}

void Wrapper::CWrapperScanner::setInFile(String *s)
{
  inFile = s;
  //string _in;
  //StringToStdStr(s,_in);// convert String to standart string
  //unmanagedClass->setInFile(_in);
}

bool Wrapper::CWrapperScanner::scan(void)
{
  if(inFile->Length != 0)
  {
    dll_parseFile parseFile = NULL;
    HMODULE  dll = NULL;
    
    dll = LoadLibrary("scan.dll");
    if(!dll)
      MessageBox(NULL,"scan.dll is missing in CWrapperScanner.cpp", "", MB_OK );

    parseFile = (dll_parseFile)GetProcAddress(dll,"parseFile");
    if(parseFile) // if function found
    {
      std::string _in;
      StringToStdStr(inFile,_in);
      parseFile(_in,*theTokenTable);
    }
    else
    {
      MessageBox(NULL,"access to GetProcAddress functiojn in scan.dll failed", "", MB_OK );
      return false;
    }
    Token *tok = new Token();
    CToken *m_pCToken = new CToken();
    theTokenTable->reinitialize();
    // copy TokenTable to TokenArray, need to use in C#
    while ((m_pCToken = theTokenTable->getToken()) != 0)
    {
      tok->m_kind = m_pCToken->getTokenKind();
      tok->m_linenum = m_pCToken->getLinenumber();
      tok->m_name = StdStrToString(m_pCToken->getName());
      tok->m_text = StdStrToString(m_pCToken->getText());
      TokenArray->Add(tok);
      tok = NULL;
      tok = new Token();
    }
    theTokenTable->reinitialize();
    return true;
  }
  else // if inFile empty
  {
   MessageBox(NULL,"Empty file Name in CWrapperScanner::scan()", "", MB_OK );
   return false;
  }
}

//void Wrapper::CWrapperScanner::getTokenTable(ArrayList *arr)
ArrayList* Wrapper::CWrapperScanner::getTokenTable()
{
  //arr = TokenArray;
  return TokenArray;
}

void Wrapper::CWrapperScanner::StringToStdStr(String* netval,std::string& stdval)
{
  const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(netval)).ToPointer();
  stdval = chars;
  Marshal::FreeHGlobal(System::IntPtr((void*)chars));
}

String* Wrapper::CWrapperScanner::StdStrToString(const std::string& stdval)
{
  return Marshal::PtrToStringAnsi(System::IntPtr((void*)stdval.c_str()));
}
