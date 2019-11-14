// Copyright 2006 SMS - Demag AG

#include "CElemDescription.h"

//----------------------------------------------------------------
CElemDescription::CElemDescription()
{
}
//---------------------------------------------------------------
CElemDescription* CElemDescription::getDescriptionInztanz(int id)
{
   CElemDescription* ret = 0;
   std::map<int,CElemDescription*>::iterator iter = ElemDescrMap.find(id);
   if(iter != ElemDescrMap.end())
	   ret = iter->second;
   return ret; 
}
//---------------------------------------------------------------
int CElemDescription::createDescription()
{
  static int count = 0;
  count++;
  CElemDescription* descr = 0;
	descr = new CElemDescription();
	int key = 0;
  //size_t key = ElemDescrMap.size();
  //Key im Map bestimmen, falls Map nicht leer ist.
  if (ElemDescrMap.size()>0)
  {
    if (!FreeKeyList.empty())
    {
      key = FreeKeyList[0];
      FreeKeyList.erase(FreeKeyList.begin());
    }
    else
    {
      std::map<int,CElemDescription*>::iterator iter = ElemDescrMap.end();
      iter--;
      key = iter->first + 1;
    }
  }
  ElemDescrMap.insert(std::pair<int,CElemDescription*>(key,descr));
	ObjReferenzMap.insert(std::pair<int,int>(key,0));
	return key;
}
//---------------------------------------------------------------
void CElemDescription::reserveElemDescription(int id)
{
	std::map<int,int>::iterator iter = ObjReferenzMap.find(id);
	if(iter != ObjReferenzMap.end())
		iter->second++;
}
//---------------------------------------------------------------
void CElemDescription::releaseElemDescription(int id)
{
  if(!ObjReferenzMap.empty())
  {
    std::map<int,int>::iterator iter = ObjReferenzMap.find(id);
    if(iter != ObjReferenzMap.end())
    {
	    iter->second--;
	    if(iter->second == 0)
	    {
		    std::map<int,CElemDescription*>::iterator iter1 = ElemDescrMap.find(iter->first);
		    delete iter1->second;
		    ElemDescrMap.erase(iter->first);
		    ObjReferenzMap.erase(id);
        FreeKeyList.push_back(id);
	    }
    }
  }
}
//---------------------------------------------------------------
void CElemDescription::setNameElem(const std::string& name)
{
	this->Name = name;
}
//---------------------------------------------------------------
 const std::string &  CElemDescription::getNameElem() const
{
	return this->Name;
}
//---------------------------------------------------------------
void CElemDescription::setElemLen(const int len)
{
	this->Len = len;
}
//--------------------------------------------------------------
int CElemDescription::getElemLen() const
{
	return this->Len;
}
//-------------------------------------------------------------
void CElemDescription::setElemDescr(const std::string& descr)
{
	this->Description = descr;
}
//--------------------------------------------------------------
 const std::string &  CElemDescription::getElemDescr() const
{
	return this->Description;
}
//--------------------------------------------------------------
void CElemDescription::setMaxElem(const std::string& max)
{
  this->Max = max;
}
//--------------------------------------------------------------
 const std::string &  CElemDescription::getMaxElem() const
{
	return this->Max;
}
//---------------------------------------------------------------
void CElemDescription::setMinElem(const std::string& min)
{
  this->Min = min;
}
//---------------------------------------------------------------
void CElemDescription::setNumFmtElem(const std::string& numFmt)
{
  this->NumFmt = numFmt;
}
//---------------------------------------------------------------
const std::string & CElemDescription::getNumFmtElem() const
{
  return this->NumFmt;
}

//----------------------------------------------------------------
 const std::string &  CElemDescription::getMinElem() const
{
	return this->Min;
}
//-----------------------------------------------------------------
void CElemDescription::setUnitElem(const std::string& unit)
{
	this->Unit = unit;
}
//-----------------------------------------------------------------
 const std::string&  CElemDescription::getUnitElem() const
{
	return this->Unit;
}
//-------------------------------------------------------------------
void CElemDescription::setFactorElem(const std::string& factor)
{
	this->Factor = factor;
}
//-------------------------------------------------------------------
 const std::string &  CElemDescription::getFactorElem() const
{
	return this->Factor;
}
//---------------------------------------------------------------------
void CElemDescription::setTtranspTypeElem(const CElemDescription::TransportType& transType)
{
	this->Transport = transType;
}
//-----------------------------------------------------------------
CElemDescription::TransportType CElemDescription::getTranspTypeElem() const
{
	return this->Transport;
}
//------------------------------------------------------------------
CElemDescription::ElementType CElemDescription::getElemType() const
{
	return this->ElemType;
}
//------------------------------------------------------------------
void CElemDescription::setElemType(const CElemDescription::ElementType& elemType)
{
	this->ElemType = elemType;
}
//------------------------------------------------------------------
void CElemDescription::setElemCount(const long count)
{
	this->Count = count;
}
//------------------------------------------------------------------
long CElemDescription::getElemCount() const
{
	return Count;
}
//------------------------------------------------------------------
std::string CElemDescription::getTransTypAsString()
{
  std::string ret("");
  switch(Transport)
  {
      case ascii:
          ret="ascii";
          break;
      case binary:
          ret="binary";
          break;
      case binaryCCSD:
          ret="binaryCCSD";
          break;
      case binaryL3D:
          ret="binaryL3D";
          break;
      case binaryRD:
          ret="binaryRD";
          break;
      case binaryRS:
          ret="binaryRS";
          break;
      default:
          ret="unknow";
  }
  return ret;
}
//--------------------------------------------------------------------
std::map<int,CElemDescription*> CElemDescription::ElemDescrMap;
//--------------------------------------------------------------------
std::map<int,int> CElemDescription::ObjReferenzMap;
//--------------------------------------------------------------------
std::vector<int> CElemDescription::FreeKeyList;
//--------------------------------------------------------------------
void CElemDescription::writeElemDescr(const std::string& path)
{
	int ref;
  std::fstream outFile;
  outFile.open(path.c_str(),std::ios::out);
  std::map<int,CElemDescription*>::iterator iter;
  for(iter=ElemDescrMap.begin();iter != ElemDescrMap.end();++iter)
  {
    ref=ObjReferenzMap.find(iter->first)->second;
	  outFile<<iter->first<<" "<<iter->second->getNameElem()<<" "<<
    ref<<std::endl;
  }
  outFile.close();
}
//--------------------------------------------------------------------