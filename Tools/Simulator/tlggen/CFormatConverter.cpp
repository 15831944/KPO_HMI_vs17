// Copyright 2006 SMS - Demag AG

//-----------------------------------------------------------------
#include <stdio.h>
#include <sstream>
//-----------------------------------------------------------------
#include "CFormatConverter.h"
#include "CLogWriter.h"
//-----------------------------------------------------------------

//-------------------------------------------------------------------
long CFormatConverter::StringToLong(const std::string& val) throw(CExpConvertError)
{
  long ret = 0;
  char* wrongStr=0;
  
  ret = strtol(val.c_str(),&wrongStr,10);
  if((*wrongStr) != 0)
  {
    throw CExpConvertError(val,"invalid long");
  }

  return ret;
}
//---------------------------------------------------------------
int CFormatConverter::StringToInt(const std::string& val) throw(CExpConvertError)
{
  int ret = 0;
  if(val.empty())
  {
    return -1;
  }
  else
  {
    std::istringstream str(val);
    str>>ret;
    if(str.fail())
    {
      throw CExpConvertError(val,"invalid integer");
    }
  }
  return ret;
}
//----------------------------------------------------------------
unsigned short int CFormatConverter::StringToShortInt(const std::string& val) throw (CExpConvertError)
{
  unsigned short int ret = 0;
  std::istringstream str(val);
  str>>ret;
  if(str.fail())
  {
    std::string mess = "invalid short integer";
    CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,val + " : " + mess,__FILE__,__FUNCTION__,__LINE__);
    throw CExpConvertError(val,mess);
  }
  return ret;
}
//----------------------------------------------------------------
double CFormatConverter::StringToDouble(const std::string& val) throw(CExpConvertError)
{
  double ret = 0.0;
  if(val.empty())
  {
    return -1.0;
  }
  else
  {
    std::string sss=val;
    CheckDelimeter(sss);
    std::istringstream str(sss);
    str>>ret;
    if(str.fail())
    {
      std::string mess = "invalid double";
      CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,val + " : " + mess,__FILE__,__FUNCTION__,__LINE__);
      throw CExpConvertError(val,mess);
    }
  }
  return ret;
}
//---------------------------------------------------------------
float CFormatConverter::StringToFloat(const std::string& val) throw (CExpConvertError)
{
  float ret = 0.0;
  if(val.empty())
  {
    return -1.0;
  }
  else
  {
    std::string sss = val;
    CheckDelimeter(sss);
    std::istringstream str(sss);
    str>>ret;
    if(str.fail())
    {
      std::string mess = "invalid float";
      CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,val + " : " + mess,__FILE__,__FUNCTION__,__LINE__);
      throw CExpConvertError(val,mess);
    }
  }
  return ret;
}
//---------------------------------------------------------------
std::string  CFormatConverter::IntToString(const int val)
{
  std::ostringstream os;
  os<<val;
  return os.str();
}
//---------------------------------------------------------------
std::string CFormatConverter::LongToString(const long val)
{
  std::ostringstream os;
  os<<val;
  return os.str();
}
//---------------------------------------------------------------
std::string CFormatConverter::DoublToString(const double val)
{
  std::ostringstream os;
  os<<val; 
  return os.str();
}
//---------------------------------------------------------------
int CFormatConverter::StringToInt(const std::string& val,int len) throw (CExpConvertError)
{
  int ret = 0;
  int maske = 1;
  ret=CFormatConverter::StringToInt(val);
  if((len > 0) && (len < 4))
  {
    if (ret >=0) //Wenn positiv
    {
      maske = maske << (len*8);
      maske--; 
      
      if((ret & maske) != ret)
      {
        std::string mess = "overflow, valid size of this integer is " + IntToString(len) + " byte(s)";
        CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,val + " - " + mess,__FILE__,__FUNCTION__,__LINE__);
        throw CExpConvertError(val,mess);
      }

      return ret;
    }
    if (ret < 0) //Wenn negativ
    {
      maske = -1;
      maske = maske << ((len*8)-1);
      
      if((ret | maske) != ret)
      {
        std::string mess = "overflow, valid size of this integer is " + IntToString(len) + " byte(s)";
        CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,val + " - " + mess,__FILE__,__FUNCTION__,__LINE__);
        throw CExpConvertError(val,mess);
      }

      return ret;
    }
    
  }
  return ret;
}
//----------------------------------------------------------------
std::string CFormatConverter::FloatToString(const float val)
{ 
  std::ostringstream os;
  os<<val;
  return os.str();
}
//---------------------------------------------------------------
void CFormatConverter::CheckDelimeter(std::string& val)
{
  int pos = int(val.find(','));
  if(pos != std::string::npos)
  {
    val.replace(pos,1,".");
  }
}
//---------------------------------------------------------------