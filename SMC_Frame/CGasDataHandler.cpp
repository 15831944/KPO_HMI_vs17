
// Copyright (C) 2010 SMS Demag AG

#include "CGasDataHandler.h"


CGasDataHandler::CGasDataHandler()
{
  clear();
}

CGasDataHandler::CGasDataHandler(seqGasData& seqData)
{
  setGasData(seqData);
}

void CGasDataHandler::addGasData(const std::string& GasName, double Data)
{
  std::map<std::string,double>::iterator it;

  // if GasName exists, add value
  it = m_GasDataList.find(GasName);
  if ( it != m_GasDataList.end() )
  {
    it->second = it->second + Data;
  }
  // else insert list element
  else
  {
    m_GasDataList.insert( std::pair<std::string,double>(GasName,Data));
  }

}

void CGasDataHandler::removeGasData(const std::string& GasName)
{
  std::map<std::string,double>::iterator it;

  // if GasName exists, add value
  it = m_GasDataList.find(GasName);
  if ( it != m_GasDataList.end() )
  {
   it = m_GasDataList.erase(it);    
  }
}


void CGasDataHandler::setGasData(const std::string& GasName, double Data)
{
  std::map<std::string,double>::iterator it;

  it = m_GasDataList.find(GasName);
  if ( it != m_GasDataList.end() )
  {
    it->second = Data;
  }
  else
  {
    m_GasDataList.insert( std::pair<std::string,double>(GasName,Data));
  }

}


double CGasDataHandler::getGasData(const std::string& GasName)
{
  double RetValue = DEF::Inv_Double;

  std::map<std::string,double>::iterator it;

  it = m_GasDataList.find(GasName);
  if ( it != m_GasDataList.end() )
  {
    RetValue = it->second;
  }

  return RetValue;
}


std::map<std::string,double>& CGasDataHandler::getGasDataList()
{
  return m_GasDataList;
}




void CGasDataHandler::diffGasData(const std::string& GasName, double Data)
{
  std::map<std::string,double>::iterator it;

  // if GasName exists, add value
  it = m_GasDataList.find(GasName);
  if ( it != m_GasDataList.end() )
  {
    double Diff = it->second - Data;
    if ( Diff < 0.0 ) Diff = Diff * -1 ; // could not find an usable abs() implementation !
    it->second = Diff;
  }
  // else insert list element
  else
  {
    if ( Data < 0.0 ) Data = Data * -1 ; // could not find an usable abs() implementation !
    m_GasDataList.insert( std::pair<std::string,double>(GasName,Data));
  }
}

void CGasDataHandler::addGasData(seqGasData& seqData)
{
  // step through seqData and ...(see below)
  long ActLength = CIntfData::getLength(seqData);
  for ( long i = 0 ; i < ActLength; ++i )
  {
    sGasData GasStruct ; 
    CIntfData::getAt(GasStruct,&seqData,i);
    // ... add gas value to an axist gas or insert new pair of gas type and value if doesn't exist
    addGasData(std::string(GasStruct.GasType),GasStruct.GasValue);
  }
}

void CGasDataHandler::fillSequence(seqGasData& seqData)
{
  std::map<std::string,double>::iterator it;
  sGasData GasStruct ; 
  int gasListSize = m_GasDataList.size();
  seqData.length(gasListSize);
  int pos = 0;

  for ( it  = m_GasDataList.begin(); it != m_GasDataList.end(); ++it)
  {
    GasStruct.GasType = it->first.c_str();
    GasStruct.GasValue = it->second;
    //CIntfData::insert(seqData,GasStruct);
    CIntfData::setAt(seqData,GasStruct,pos);
     pos++;
  }
}

void CGasDataHandler::diffGasData(seqGasData& seqData)
{
  // step through seqData and try to find data for respective gas types
  long ActLength = CIntfData::getLength(seqData);
  for ( long i = 0 ; i < ActLength; ++i )
  {
    sGasData GasStruct ; 
    // init availabilities to actual state
    CIntfData::getAt(GasStruct,&seqData,i);
    diffGasData(std::string(GasStruct.GasType),GasStruct.GasValue);
  }
}

void CGasDataHandler::addGasData(CGasDataHandler& GasDataHandler)
{
  std::map<std::string,double> GasList;
  std::map<std::string,double>::iterator it;
  std::map<std::string,double>::iterator it_to_add;

  GasList = GasDataHandler.getGasDataList();
  for (it_to_add = GasList.begin(); it_to_add != GasList.end(); it_to_add++)
  {
    // if GasName exists, add value
    it = m_GasDataList.find(it_to_add->first);
    if ( it != m_GasDataList.end() )
    {
      it->second = it->second + it_to_add->second;
    }
    // else insert list element
    else
    {
      m_GasDataList.insert( std::pair<std::string,double>(it_to_add->first,it_to_add->second));
    }
  }
}

void CGasDataHandler::setGasData(seqGasData& seqData)
{
  //clear first
  clear();

  // step through seqData and set 
  long ActLength = CIntfData::getLength(seqData);
  for ( long i = 0 ; i < ActLength; ++i )
  {
    sGasData GasStruct ; 
    // init availabilities to actual state
    CIntfData::getAt(GasStruct,&seqData,i);
    setGasData(std::string(GasStruct.GasType),GasStruct.GasValue);
  }
}


void CGasDataHandler::clear()
{
  m_GasDataList.erase(m_GasDataList.begin(),m_GasDataList.end());
}



seqGasData CGasDataHandler::getGasData()
{
  seqGasData RetValue;

  int pos = 0;
  int mapSize =  m_GasDataList.size();

  RetValue.length(mapSize);

  std::map<std::string,double>::iterator it;

  for ( it  = m_GasDataList.begin(); it != m_GasDataList.end(); ++it)
  {
    sGasData GasStruct ; 

    GasStruct.GasType = it->first.c_str();
    GasStruct.GasValue = it->second;
    //CIntfData::insert(RetValue,GasStruct);
    CIntfData::setAt(RetValue,GasStruct,pos);
    pos++;
  }

  return RetValue;
}


void CGasDataHandler::updateGasData(seqGasData& seqData)
{
  // step through seqData and set 
  long ActLength = CIntfData::getLength(seqData);
  for ( long i = 0 ; i < ActLength; ++i )
  {
    sGasData GasStruct;
    // init availabilities to actual state
    CIntfData::getAt(GasStruct,&seqData,i);
    setGasData(std::string(GasStruct.GasType),GasStruct.GasValue);
  }
}


