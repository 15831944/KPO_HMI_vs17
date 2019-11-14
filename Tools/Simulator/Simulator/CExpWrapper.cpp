
#include "stdafx.h"
#include "CExpWrapper.h"
//----------------------------------------
CExpWrapper::CExpWrapper(String^ mess,ErrorTyp err)
{
  this->Message=mess;
  this->Error=err;
}
//---------------------------------------
CExpWrapper::CExpWrapper(String^ mess)
{
  this->Message=mess;
  this->Error=ErrorTyp::tUnknow;
}
//---------------------------------------
String^ CExpWrapper::getMessage()
{
  return this->Message;
}
//---------------------------------------
CExpWrapper::ErrorTyp CExpWrapper::getErrorTyp()
{
  return this->Error;
}
//---------------------------------------
CExpWrapper::~CExpWrapper()
{
}
//----------------------------------------