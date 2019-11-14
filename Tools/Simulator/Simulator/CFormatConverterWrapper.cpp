#include "StdAfx.h"

#include "CFormatConverterWrapper.h"
#include "CStdConverter.h"
#include "CFormatConverter.h"
#include "CExpWrapper.h"
#include "CLogWriterWrapper.h"

//#using <mscorlib.dll>

//-----------------------------------------------------------------
//throw(CExpConvertError)
double CFormatConverterWrapper::StringToDouble(System::String^ val) 
{
  /*std::string temp;*/
  double ret;

  //if (!mTemp)
  //  mTemp = new std::string();

  !mTemp ? mTemp = new std::string() : mTemp->clear();

  try
  {
    CStdConverter::StringToStdStr(val,*mTemp);
    ret=CFormatConverter::StringToDouble(*mTemp);
  }
  catch (CExpConvertError& e)
  {
    String^ mess = String::Concat("<",CStdConverter::StdStrToString(e.getValue()),"> is invalid double data type.");
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    mTemp->clear();
    throw gcnew CExpWrapper(mess);
  } 
  return ret; 
}
//-----------------------------------------------------------------
//throw(CExpConvertError)
System::String^ CFormatConverterWrapper::DoubleToString(double val) 
{
  //std::string temp;

  !mTemp ? mTemp = new std::string() : mTemp->clear();

  *mTemp=CFormatConverter::DoublToString(val);
  return CStdConverter::StdStrToString(*mTemp);
}
//-----------------------------------------------------------------
long CFormatConverterWrapper::StringToLong(System::String^ val)
{
  /*std::string temp;*/
  long ret;
  !mTemp ? mTemp = new std::string() : mTemp->clear();
  try
  {
    CStdConverter::StringToStdStr(val,*mTemp);
    ret = CFormatConverter::StringToLong(*mTemp);
  }
  catch (CExpConvertError& e)
  {
    String^ mess = String::Concat("<",CStdConverter::StdStrToString(e.getValue()),"> is invalid long data type.");
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    mTemp->clear();
    throw gcnew CExpWrapper(mess);
  } 
  return ret; 
}
//-----------------------------------------------------------------
System::String^ CFormatConverterWrapper::LongToString(long val)
{
  /*std::string temp;*/
  !mTemp ? mTemp = new std::string() : mTemp->clear();
  *mTemp=CFormatConverter::LongToString(val);
  return CStdConverter::StdStrToString(*mTemp);
}
//-----------------------------------------------------------------
//throw(CExpConvertError)
int CFormatConverterWrapper::StringToInt(System::String^ val) 
{
  /*std::string temp;*/
  !mTemp ? mTemp = new std::string() : mTemp->clear();
  int ret;
  try
  {
    CStdConverter::StringToStdStr(val,*mTemp);
    ret = CFormatConverter::StringToInt(*mTemp);
  }
  catch (CExpConvertError& e)
  {
    String^ mess = String::Concat("<",CStdConverter::StdStrToString(e.getValue()),"> is invalid integer data type.");
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    mTemp->clear();
    throw gcnew CExpWrapper(mess);
  } 
  return ret; 
}
//-----------------------------------------------------------------
//throw(CExpConvertError)
System::String^ CFormatConverterWrapper::IntToString(int val) 
{
  /*std::string temp;*/
  !mTemp ? mTemp = new std::string() : mTemp->clear();
  *mTemp=CFormatConverter::IntToString(val);
  return CStdConverter::StdStrToString(*mTemp);
}
//-----------------------------------------------------------------
CFormatConverterWrapper::CFormatConverterWrapper()
{
}
//-----------------------------------------------------------------
CFormatConverterWrapper::~CFormatConverterWrapper()
{
  delete mTemp;
}