// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif


#include <string>
#include <iostream>
#include <sstream>
#include "corba.h"

#include "CIntfDataElement.h"
//##ModelId=406AE1EB00D6
#include "CIntfData.h"
//##ModelId=406AE1EB00D6
#include "CData_Provider.h"

#include "CData_Provider_RuntimeController.h"

#include "CIntfDataBuffer.h"


//##ModelId=406AE1EB00D6
CIntfDataElement* CIntfDataBuffer::findElement(const std::string& Key)
{
  CIntfDataElement* pIntfDataElement = 0;

  std::vector<CIntfDataElement*>::reverse_iterator it;

  // using m_LastIntfDataElement for first search will decrease search time
  // take m_LastIntfDataElement if Key is equal
  if (m_LastIntfDataElement && m_LastIntfDataElement->getKey() == Key)
  {
    pIntfDataElement = m_LastIntfDataElement;
  }
  else
  {
    // start search at end of vetor, actual entries will be found here
    for ( it = m_IntfDataElementList.rbegin(); it != m_IntfDataElementList.rend(); it++)
    {
      // empty key allowed as default
      if (Key.empty() && (*it)->getCompleted())
      {
        pIntfDataElement = (*it);
        break;
      }

      if ( (*it)->getKey() == Key ) 
      {
        pIntfDataElement = (*it);
        break;
      }
    }   
  }

  m_LastIntfDataElement = pIntfDataElement;

  return pIntfDataElement;
}

//##ModelId=406AE3520276
CIntfDataElement* CIntfDataBuffer::insertElement(const std::string& Key)
{
  checkIntfDataElementList();

  CIntfDataElement* pNewIntfDataElement = new CIntfDataElement(this,Key);

  // insert new CIntfDataElement at the and of the list
  m_IntfDataElementList.push_back( pNewIntfDataElement );
   
  return pNewIntfDataElement;
}

//##ModelId=407D08D403C6
CIntfDataBuffer::~CIntfDataBuffer()
{
	m_IntfDataElementList.erase(m_IntfDataElementList.begin(),m_IntfDataElementList.end());
}

//##ModelId=407D08D50199
CIntfDataBuffer::CIntfDataBuffer( ) 
: m_KeyCounter(0)
, m_LastIntfDataElement(0)
, m_IntfDataElementListMaxSize(1000)
{
}

//##ModelId=407FAEFC02F1
void CIntfDataBuffer::setBufferSize(long value)
{
	this->m_IntfDataElementListMaxSize = value;
	return;
}

//##ModelId=4067E7F9039D
long CIntfDataBuffer::deleteElement(const std::string& Key)
{
  std::vector<CIntfDataElement*>::iterator it;

  // oldest entries will be delete in general
  // these entries will be found in front of the list
  for ( it = m_IntfDataElementList.begin(); it != m_IntfDataElementList.end(); it++)
  {
    if ( (*it) && (*it)->getKey() == Key ) 
    {
      std::string ProviderName;
	    if (m_pData_Provider)
      {
        ProviderName = m_pData_Provider->getProviderName();
        m_pData_Provider->onDeleteDataKey(Key);
      }

      std::string Message = ProviderName;
      Message += " Removing Element with key : ";
      Message += Key;
      log(Message,6);

      delete (*it);
      (*it) = 0;

      it = m_IntfDataElementList.erase(it); // reduces size of list

      break;
    }
  }

  return (long)0;
}

//##ModelId=40B6FFB40286
void CIntfDataBuffer::log(const std::string & Message, long Level)
{
  if (m_pData_Provider && m_pData_Provider->getTraceLevel() >= Level )
  {
    m_pData_Provider->log(Message,Level);
  }
}



//##ModelId=40B7127E0397
void CIntfDataBuffer::generateKey(std::string& Key)
{
  // control maximum content of m_KeyCounter
  if (m_KeyCounter < LONG_MAX - 1 )
    m_KeyCounter++;
  else
    m_KeyCounter = 1;

  std::ostringstream str_ActKey;
  str_ActKey << m_KeyCounter; 

  Key = str_ActKey.str();

  if (m_pData_Provider->getTraceLevel() >= 3)
  {
    std::string Message("generate Key in CIntfDataProvider ");
    Message += Key;
    log (Message,3);
  }
}



//##ModelId=40B747C401E3
 CIntfDataElement* CIntfDataBuffer::getLastIntfDataElement() 
{
	return m_LastIntfDataElement;
}

//##ModelId=40B747C5022D
void CIntfDataBuffer::setLastIntfDataElement(CIntfDataElement* value)
{
	m_LastIntfDataElement = value;
	return;
}



//##ModelId=40D6CE8302E8
void CIntfDataBuffer::showContent(const std::string& Key, long Level)
{
  if (m_pData_Provider->getTraceLevel() >= Level)
  {
    CData_Provider_RuntimeController Controller(m_pData_Provider,"CIntfDataBuffer::showContent",Key,"");

    std::vector<CIntfDataElement*>::reverse_iterator itElement;
    std::vector<CIntfData*>::iterator itDataList;
    std::vector<CIntfData*> DataList ; 

    // actual entries will be found at the end of the vector
    for ( itElement = m_IntfDataElementList.rbegin(); itElement != m_IntfDataElementList.rend(); itElement++)
    {
      CIntfDataElement* pIntfDataElement = (*itElement);

      std::string ActKey = pIntfDataElement->getKey();

      if ( Key.empty() || Key == ActKey )
      {
        DataList = pIntfDataElement->getIntfDataList();
        for ( itDataList = DataList.begin(); itDataList != DataList.end(); itDataList++)
        {
          CIntfData* pIntfData = (*itDataList);
          pIntfData->showContent(Level);
        }
        // Key is unique, if found break for loop
        if ( !Key.empty())
        {
          break;
        }
      }
    }
  }//if (m_pData_Provider->getTraceLevel() >= Level)
}



//##ModelId=41371F5B01DA
void CIntfDataBuffer::setCompleted(const std::string & Key)
{
  CIntfDataElement* ActElement = findElement(Key);
  if (ActElement)
  {
    ActElement->setCompleted(true);
  }
}


// check list size and delete surplus elements
//##ModelId=41496991021C
void CIntfDataBuffer::checkIntfDataElementList()
{
  // control size of data list
  std::vector<CIntfDataElement*>::iterator it;

  // elements will be insertet as begin()
  // using reverse iterator to find oldest entry
  // exit if MaxSize is not reached
  if ( (long)m_IntfDataElementList.size() > m_IntfDataElementListMaxSize )
  {
    long persiCounter = 0;

    for ( it = m_IntfDataElementList.begin() ; it != m_IntfDataElementList.end() ; ++ it)
    {
      // size will be changed during check at "delete" method !
      if ( (long)m_IntfDataElementList.size() <= m_IntfDataElementListMaxSize )
      {
        break;
      }

      // delete if actual element is not set as persistent
      if ( (*it) )
      {
        if ( !(*it)->getPersistent() )
        {
          deleteElement((*it)->getKey()); // perfomrs erase on m_IntfDataElementList

          it = m_IntfDataElementList.begin();
        }
        else
        {
          persiCounter++;
        }
      }
    } // for ( it = m_IntfDataElementList.begin() ; it != m_IntfDataElementList.end() ; ++ it)

    // check for content of persistant data keys !!
    if ( persiCounter >= m_IntfDataElementListMaxSize )
    {
      std::string Message = "critical number of persistent entries at m_IntfDataElementList reached !";
      m_pData_Provider->EventLogExc(Message, m_pData_Provider->getProviderName() + "CIntfDataBuffer::checkIntfDataElementList", "");
    }
  }
}



//##ModelId=4149BA2B000E
void CIntfDataBuffer::setpData_Provider(CData_Provider* value)
{
	m_pData_Provider = value;
}



//##ModelId=414EC21302A2
long CIntfDataBuffer::getIntfDataElementListLength()
{
	return (long)m_IntfDataElementList.size();;
}

//##ModelId=414EC25B0285
std::string  CIntfDataBuffer::findKey(long Index)
{
  std::string RetValue;
  long ListLength = m_IntfDataElementList.size();

  CIntfDataElement* pIntfDataElement = 0;

  if ( ListLength > 0 && Index <= ListLength )
  {
    pIntfDataElement = m_IntfDataElementList.at(Index);
  }

  if (pIntfDataElement)
  {
    RetValue = pIntfDataElement->getKey();

    std::string Message = "CIntfDataBuffer::findKey returning key : ";
    Message += RetValue;
    log(Message,6);
  }

  return RetValue;
}

//##ModelId=429370F5013C
void CIntfDataBuffer::EventLogValidationFailure(const std::string& Message)
{
  m_pData_Provider->EventLogValidationFailure(Message);
}



//##ModelId=42E764680078
CData_Provider* CIntfDataBuffer::getpData_Provider()
{
	return m_pData_Provider;
}

std::vector<CIntfDataElement*>  CIntfDataBuffer::getIntfDataElementList()
{
  return m_IntfDataElementList;
}
