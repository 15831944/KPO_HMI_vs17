// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif


#include <string>
#include <iostream>
#include <vector>

using namespace std;

#include "CIntfData.h"
//##ModelId=40B6F4B00028
#include "CData_Provider.h"

#include "CData_Provider_RuntimeController.h"

//##ModelId=40B6F5C001A6
#include "CIntfDataElement.h"

//##ModelId=40B6F5C001A6
CIntfDataElement::~CIntfDataElement()
{
  try
  {
    deleteIntfData();
    m_IntfDataList.clear();
    m_IntfReqList.erase(m_IntfReqList.begin(),m_IntfReqList.end());
  }
  catch(...)
  {
    if (m_pDataBuffer)
    {
      m_pDataBuffer->getpData_Provider()->EventLogExc("Unknown exception", 
        m_pDataBuffer->getpData_Provider()->getProviderName()+":~CIntfDataElement", "erase interface");
    }
  }
}

//##ModelId=40B70A170394
CIntfDataElement::CIntfDataElement( CIntfDataBuffer  * DataBuffer, const std::string &Key)
:m_pDataBuffer(DataBuffer),m_Key(Key),is_Completed(false),is_Persistent(false)
{
}


//##ModelId=40B6F4B00028
CIntfData* CIntfDataElement::findData(const std::string & Name)
{
  return findData("", Name);
}

//##ModelId=40B6F4B0003C
bool CIntfDataElement::insertData(const std::string & Name, CIntfData *pIntfData)
{
  bool RetValue = true;
  vector<CIntfData*>::iterator it;

  // do not insert double Key's
  CIntfData *pExistingIntfData = findData(Name);

  if ( pExistingIntfData )
  {
    // first check of data will be changed by inserting !
    if ( pExistingIntfData->getType() == pIntfData->getType()  && 
          pExistingIntfData->getContent() == pIntfData->getContent() )
    {
      if (m_pDataBuffer->getpData_Provider()->getTraceLevel() > 5 )
      {
        std::stringstream Message;
        Message << "CIntfDataElement::insertData() : "
                << " equal data received for Key :"
                << m_Key 
                << " with Name : "
                << Name
                << " value : "
                << pExistingIntfData->getContent();

        log(Message.str(),6);
      }

      pExistingIntfData->setUpdated(false);

      RetValue = false; // nothing inserted, memory must be controlled by caller
    }
    else
    {
      if (m_pDataBuffer->getpData_Provider()->getTraceLevel() > 4 )
      {
        std::string Message = "CIntfDataElement::insertData() : ";
        Message += " overwriting DataElement for Key :";
        Message += m_Key ;
        Message += " with Name : ";
        Message += Name;
        log(Message,6);
      }

      deleteData(Name);

      m_IntfDataList.push_back(pIntfData);
      pIntfData->setUpdated(true);
    }
  }
  else // no entry found, so insert new data
  {
    m_IntfDataList.push_back(pIntfData);
    pIntfData->setUpdated(true);
  }

  pIntfData->showContent(4);
   
  return RetValue;
}

//##ModelId=40B6F7370155
long CIntfDataElement::eraseIntfDataList()
{
  vector<CIntfData*>::iterator it;

  for ( it = m_IntfDataList.begin(); it != m_IntfDataList.end(); it++)
  {
    std::string Message = "Removing Data with name : ";
    Message += (*it)->getName();
    log(Message,6);

    delete (*it);
    (*it) = 0;
  }

	return (long)0;
}

//##ModelId=44FE999A01AE
bool CIntfDataElement::deleteIntfData()
{
  bool RetValue = false;
  vector<CIntfData*>::iterator it;

  for ( it = m_IntfDataList.begin(); it != m_IntfDataList.end(); it++)
  {
    std::string Message = "Removing Data with name : ";
    Message += (*it)->getName();
    log(Message,6);

    RetValue = true;

    delete (*it);
    (*it) = 0;
  }

	return RetValue;
}


//##ModelId=40B6F61700E3
const std::string&  CIntfDataElement::getKey()
{
  return m_Key;
}



//##ModelId=40B6FFB80138
void CIntfDataElement::log(const std::string  & Message, long Level)
{
  if (m_pDataBuffer)
  {
    m_pDataBuffer->log(Message,Level);
  }
}



//##ModelId=40B70F7500D8
long CIntfDataElement::deleteData(const std::string  & Name)
{
  vector<CIntfData*>::iterator it;

  // do not insert double Key's
  for ( it = m_IntfDataList.begin(); it != m_IntfDataList.end(); it++)
  {
    if ( (*it)->getName() == Name ) 
    {
      if ( (*it) )
      {
        try
        {
          delete (*it);
          (*it) = 0;
        }
        catch(...)
        {
          m_pDataBuffer->getpData_Provider()->EventLogExc("Unknown exception", 
            m_pDataBuffer->getpData_Provider()->getProviderName()+":deleteData", "delete " + Name);
        }
      }
      it = m_IntfDataList.erase(it);
      break;
    }
  }
   
  return 0;
}



//##ModelId=40BF15B600E9
std::vector<CIntfData*>  CIntfDataElement::getIntfDataList()
{
  return m_IntfDataList;
}

std::set<std::string>  CIntfDataElement::getIntfReqList()
{
  return m_IntfReqList;
}



//##ModelId=41371FE003A8
void CIntfDataElement::setCompleted(bool value)
{
	is_Completed = value;
	return;
}

//##ModelId=41371FE003B2
bool CIntfDataElement::getCompleted()
{
	return is_Completed;
}



//##ModelId=4149688D001C
void CIntfDataElement::setPersistent(bool value)
{
	is_Persistent = value;
	return;
}



//##ModelId=41496A6302F6
 bool CIntfDataElement::getPersistent() 
{
	return is_Persistent;
}


void CIntfDataElement::setRequestedName(const std::string& Name)
{
  // this data hase been requested
  m_IntfReqList.insert(Name);
}

//##ModelId=418F95AC00E7
CIntfData* CIntfDataElement::findData(const std::string& Type, const std::string& Name)
{


  CIntfData* pIntfData = 0;

  if (!m_IntfDataList.empty())
  {
    for ( vector<CIntfData*>::iterator it = m_IntfDataList.begin(); it != m_IntfDataList.end(); it++)
    {
      if ( (*it)->getName() == Name && 
          ((*it)->getType() == Type || Type.empty()) )
      {
        pIntfData = (*it);
        break;
      }
    }
  }   

 /* if (!pIntfData)
  {
    std::string Message("No Data found in CIntfDataElement::findData for ");
    Message += m_Key;
    Message += " ";
    Message += Name;
    Message += " ";
    Message += Type;
    log (Message,4);
  }*/

  return pIntfData;
}


//##ModelId=44FE999A01C2
bool CIntfDataElement::isUpdated(const std::string Name)
{
  bool RetValue = true;
  
  CIntfData *pIntfData = findData(Name);

  if ( pIntfData && pIntfData->isUpdated())
  {
    RetValue = true;
  }

  return RetValue;
}

bool CIntfDataElement::isRequested(const std::string Name)
{
  bool RetValue = true;
  
  CIntfData *pIntfData = findData(Name);

  if ( pIntfData && pIntfData->isRequested())
  {
    RetValue = true;
  }

  return RetValue;
}
