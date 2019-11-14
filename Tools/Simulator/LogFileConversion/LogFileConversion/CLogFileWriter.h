#ifndef _CLogFileWriter_
#define _CLogFileWriter_

using namespace System;

public ref class CLogFileWriter
{
  public:
    ~CLogFileWriter();
    static CLogFileWriter^ getLogFileWriter();
    void writeMessage(String^ mess);
  protected:
    CLogFileWriter();
  private:
    static CLogFileWriter^ LogFileWriter = nullptr;
    System::IO::StreamWriter^ Writer;
};
#endif