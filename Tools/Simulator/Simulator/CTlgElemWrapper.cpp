#include "StdAfx.h"
#include "CTlgElemWrapper.h"
#include "CStdConverter.h"
#include "CTlgElem.h"
#include "CExpConvertError.h"
#include "CExpLimitError.h"

#using <mscorlib.dll>

//----------------------------------------------------
CTlgElemWrapper::CTlgElemWrapper(void):
ElemTlg(nullptr)
{
}
//----------------------------------------------------
CTlgElemWrapper::~CTlgElemWrapper(void)
{
}
//----------------------------------------------------
int CTlgElemWrapper::compare(String^ val, String^ elemName)
{
  std::string stdVal("");
  std::string stdElemName("");
  CStdConverter::StringToStdStr(val,stdVal);
  CStdConverter::StringToStdStr(elemName,stdElemName);
  return ElemTlg->compare(stdVal,stdElemName);
}
//----------------------------------------------------
CTlgElem* CTlgElemWrapper::getSubElem(int id)
{
  return ElemTlg->getSubElem(id);
}
//----------------------------------------------------
CTlgElem* CTlgElemWrapper::getSubElem(String^ pathOfName)
{
  int index = pathOfName->IndexOf("\\");
  
  if (index != -1)
  {
    String^ elemName = pathOfName->Substring(0,index);
    String^ path = pathOfName->Remove(0,index+1);
    
    int i=1;
    
    while (i <= getSubElemCount())
    {
      if (elemName->Equals(CStdConverter::StdStrToString(getSubElem(i)->getNameElem())))
      {
        return getSubElem(path);
      }
      i++;
    }
  }
  else
  {
    //int a = getSubElemCount();
    //String^ test = getElemName();

    int i = 1;
    while (i <= getSubElemCount())
    {
      if (pathOfName->Equals(CStdConverter::StdStrToString(getSubElem(i)->getNameElem())))
      {
         return getSubElem(i);
      }
      i++;
    }
  }
  return 0;
}
//----------------------------------------------------
String^ CTlgElemWrapper::getElemType()
{
  if (ElemTlg->getElemType() == CElemDescription::tArray)
    return "Array";
  if (ElemTlg->getElemType() == CElemDescription::tDouble)
    return "Double";
  if (ElemTlg->getElemType() == CElemDescription::tFloat)
    return "Float";
  if (ElemTlg->getElemType() == CElemDescription::tInteger)
    return "Integer";
  if (ElemTlg->getElemType() == CElemDescription::tRecord)
    return "Record";
  if (ElemTlg->getElemType() == CElemDescription::tSegment)
    return "Segment";
  if (ElemTlg->getElemType() == CElemDescription::tShortInteger)
    return "ShortInteger";
  if (ElemTlg->getElemType() == CElemDescription::tString)
    return "String";
  if (ElemTlg->getElemType() == CElemDescription::tUnknow)
    return "Unknow";
  
  return nullptr;
}
CElemDescription::ElementType CTlgElemWrapper::getElemTypeAsEnum()
{
	return ElemTlg->getElemType();
}
//----------------------------------------------------
CTlgElem* CTlgElemWrapper::getTlgElem()
{
  return ElemTlg;
}
//----------------------------------------------------
void CTlgElemWrapper::setTlgElem(CTlgElem* elemtlg)
{
  ElemTlg=elemtlg;
}
//----------------------------------------------------
int CTlgElemWrapper::getSubElemCount()
{
  return ElemTlg->getSubElemCount();
}
//----------------------------------------------------
void CTlgElemWrapper::getMinMax(String^& min,String^& max)
{
  std::string MinStr("");
  std::string MaxStr("");
  ElemTlg->getMinMax(MinStr,MaxStr);
  min=CStdConverter::StdStrToString(MinStr);
  max=CStdConverter::StdStrToString(MaxStr);
}
//----------------------------------------------------
void CTlgElemWrapper::getElemInfo(String^& unit,String^& factor,String^& min,String^& max)
{
  std::string MinStr("");
  std::string MaxStr("");
  std::string UnitStr("");
  std::string FactorStr("");
  ElemTlg->getElemInfo(UnitStr,FactorStr,MinStr,MaxStr);
  unit=CStdConverter::StdStrToString(UnitStr);
  factor=CStdConverter::StdStrToString(FactorStr);
  min=CStdConverter::StdStrToString(MinStr);
  max=CStdConverter::StdStrToString(MaxStr);
}
//----------------------------------------------------
String^ CTlgElemWrapper::getElemName()
{
  std::string stdName("");
  stdName=ElemTlg->getNameElem();
  return CStdConverter::StdStrToString(stdName);
}
//----------------------------------------------------
void CTlgElemWrapper::getElemValue(String^& value)
{
  std::string stdValue("");
  ElemTlg->getValue(stdValue);
  value=CStdConverter::StdStrToString(stdValue);
}
//----------------------------------------------------
String^ CTlgElemWrapper::getElemDescription()
{
  std::string stdDescription("");
  stdDescription=ElemTlg->getComment();
  return CStdConverter::StdStrToString(stdDescription);
}
//----------------------------------------------------
String^ CTlgElemWrapper::getElemTransport()
{
  std::string stdTransTyp("");
  stdTransTyp=ElemTlg->getTranspTyp();
  return CStdConverter::StdStrToString(stdTransTyp); 
}
//----------------------------------------------------
int CTlgElemWrapper::getElemLenght()
{
  return ElemTlg->getLen(); 
}
//----------------------------------------------------------------
String^ CTlgElemWrapper::setValue(String^ value,String^ interName)
{
  String^ ret=nullptr;
  std::string stdInter ("");
  std::string stdValue ("");
  CStdConverter::StringToStdStr(value,stdValue);
  CStdConverter::StringToStdStr(interName,stdInter);
  
  try
  {
    ElemTlg->setValue(stdValue,CInterConfig::getInterConfig(stdInter));
  }
  catch(CExpConvertError& e)
  {
    ret = String::Concat("Value <",value,"> of ",CStdConverter::StdStrToString(e.getElem())," is ",
                          CStdConverter::StdStrToString(e.getType()));
  }
  catch(CExpLimitError& e)
  {
    ret = String::Concat("Limit of ",CStdConverter::StdStrToString(e.getElem())," is  out.");      
  }
  return ret;
}