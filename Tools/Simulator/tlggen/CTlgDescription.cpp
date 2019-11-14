// Copyright 2006 SMS - Demag AG

//--------------------------------------------------
#include "CTlgDescription.h"
//--------------------------------------------------
#include <fstream>
#include <iostream>
#include "CLogWriter.h"
#include "CFormatConverter.h"
//---------------------------------------------------
CTlgDescription::CTlgDescription()
{

}
//---------------------------------------------------
const std::string &  CTlgDescription::getNameTlg() const
{
	return Name;
}
//----------------------------------------------------
void CTlgDescription::setNameTlg(const std::string& name)
{
	this->Name = name;
}
//-----------------------------------------------------
long CTlgDescription::getLenTlg() const
{
  return this->Len;
}
//------------------------------------------------------
void CTlgDescription::setLenTlg(long len)
{
  this->Len = len;
}
//------------------------------------------------------
const std::string&  CTlgDescription::getDescrTlg() const
{
  return this->Description;
}
//-------------------------------------------------------
void CTlgDescription::setDescrTlg(const std::string& descr)
{
  this->Description = descr;
}
//---------------------------------------------------------
void CTlgDescription::setDirection(const std::string& dir)
{
  this->Direction = dir;
}
 //--------------------------------------------------------
const std::string& CTlgDescription::getDirection() const
{
  return this->Direction;
}
//---------------------------------------------------------
CTlgDescription* CTlgDescription::getTlgDescriptionInztanz(int id)
{
	CTlgDescription* ret = 0;
	std::map<int,CTlgDescription*>::iterator iter = TlgDescrMap.find(id);
	if(iter != TlgDescrMap.end())
		ret = iter->second;
	return ret;
}
//-----------------------------------------------------------
int CTlgDescription::createTlgDescription()
{
  CTlgDescription* descr = new CTlgDescription();
  int key = 0;
  //Key im Map bestimmen, falls Map nicht leer ist.
  
  if (TlgDescrMap.size()>0)
  {
    if (!FreeKeyList.empty())
    {
      key = FreeKeyList[0];
      FreeKeyList.erase(FreeKeyList.begin());
    }
    else
    {
      std::map<int,CTlgDescription*>::iterator iter = TlgDescrMap.end();
      iter--;
      key = iter->first + 1;
    }
  }

  TlgDescrMap.insert(std::pair<int,CTlgDescription*>(key,descr));
  ObjReferenzMap.insert(std::pair<int,int>(key,0));
  return key;
}
//-------------------------------------------------------------
void CTlgDescription::reserveTlgDescription(int id)
{
	std::map<int,int>::iterator iter = ObjReferenzMap.find(id);
	if(iter != ObjReferenzMap.end())
	iter->second++;
}
//---------------------------------------------------------------
void CTlgDescription::releaseTlgDescription(int id)
{
  if(!ObjReferenzMap.empty())
  {
    std::map<int,int>::iterator iter = ObjReferenzMap.find(id);
    if(iter != ObjReferenzMap.end())
    {
	    iter->second--;
	    if(iter->second == 0)
	    {
		    std::map<int,CTlgDescription*>::iterator iter1 = TlgDescrMap.find(iter->first);
		    delete iter1->second;
		    TlgDescrMap.erase(iter->first);
        ObjReferenzMap.erase(id);
        FreeKeyList.push_back(id);
	    }
    }
  }
}
//--------------------------------------------------------------
void CTlgDescription::setInterfaceName(const std::string& name)
{
	this->Interface = name;
}
//--------------------------------------------------------------
const std::string& CTlgDescription::getInterfaceName()const
{
	return this->Interface;
}
//---------------------------------------------------------------
std::map<int,CTlgDescription*> CTlgDescription::TlgDescrMap;
//---------------------------------------------------------------
std::map<int,int> CTlgDescription::ObjReferenzMap;
//---------------------------------------------------------------
std::vector<int> CTlgDescription::FreeKeyList;
//---------------------------------------------------------------
void CTlgDescription::writeTlgDescr(const std::string& path)
{
  int ref;
  std::fstream outFile;
  outFile.open(path.c_str(),std::ios::out);
  std::map<int,CTlgDescription*>::iterator iter;
  for(iter=TlgDescrMap.begin();iter != TlgDescrMap.end();++iter)
  {
    ref=ObjReferenzMap.find(iter->first)->second;
    outFile<<iter->first<<" "<<iter->second->getNameTlg()
            <<" "<<iter->second->getInterfaceName()<<" "<<
    ref<<std::endl;
  }
  outFile.close();
}
//----------------------------------------------------------------