// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif


#include <string>
#include <iostream>

#include "iData_Provider_s.hh"
#include "CIntfDataElement.h"
#include "CIntfDataAny.h"
#include "CIntfDataLong.h"
#include "CIntfDataDouble.h"
#include "CIntfDataString.h"
#include "CIntfDataBoolean.h"
#include "CIntfDataRuleSet.h"
#include "CData_Provider_RuntimeController.h"

#include "CData_Provider.h"

CORBA::Any CData_Provider::getAny(const std::string& Key, const std::string &Name)
{
  CORBA::Any ActAny;

  try
  {
    CData_Provider_RuntimeController Controller(this,"CData_Provider::getAny",Key,Name);

    CIntfDataElement *pIntfDataElement = 0;
    CIntfDataAny* pIntfDataAny = 0;
    CIntfData* pIntfData = 0;

    this->beforeDataAccess(Key,Name);

    // in case of empty Key the newest entry will be returned from the DataBuffer
    pIntfDataElement = IntfDataBuffer.findElement(Key);

    // get Any data from DataBuffer entry
    if (pIntfDataElement)
    {
      pIntfDataElement->setRequestedName(Name);
      pIntfData = pIntfDataElement->findData(CIntfData::Any,Name);

      if ( pIntfData )
      {
        pIntfData->setRequested(true);
        pIntfDataAny = dynamic_cast<CIntfDataAny*>(pIntfData);
        
        if (pIntfDataAny)
        {
          std::ostringstream Message;
          if (getTraceLevel() > 4 )
          {
            Message << m_ProviderName
                    << " returning CData_Provider::getAny for " 
                    << Key 
                    << " "
                    << Name;
            Message << " " << pIntfDataAny->getContent();
            log(Message.str(), 6);
          }

          // return stored CORBA::Any
          ActAny = pIntfDataAny->getData();
        }
        else
        {
          log("CData_Provider::getAny: dynamic_cast failed",1);
        }
      }
      else
      {
        std::string Message;
        Message += Key;
        Message += " ";
        Message += CIntfData::Any;
        Message += " ";
        Message += Name;
        
        // write EventLog
        EventLogReadFailure(Message);
      }
    }

    this->afterDataAccess(Key,Name);

  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider::getAny " + Key + " " + Name, "");
  }

  return ActAny;
}

void CData_Provider::setAny(const std::string& Key, const std::string& Name, CORBA::Any &NewAny)
{
  // set new data to member variables
  std::string ActKey = Key;
  
  CData_Provider_RuntimeController Controller(this,"CData_Provider::setAny",Key,Name);

  try
  {
    if (getTraceLevel() > 4 )
    {
	    std::ostringstream Message;
      Message << m_ProviderName
              << " receiving CData_Provider::setAny for " 
              << Key 
              << " "
              << Name;

      logEvaluated(Message.str(),Name);
    }

    // Key must not empty
    if (!ActKey.empty() && ActKey != DEF::Inv_String)
    {
      CIntfDataElement *pIntfDataElement = 0;
    
      pIntfDataElement = IntfDataBuffer.findElement(ActKey);

      if (!pIntfDataElement)
      {
        pIntfDataElement = IntfDataBuffer.insertElement(ActKey);
      }

      if (pIntfDataElement)
      {
        CIntfDataAny* pIntfDataAny = new CIntfDataAny(this,Name,ActKey);

        pIntfDataAny->setData(NewAny);

        if (!pIntfDataElement->insertData(Name,pIntfDataAny))
        {
          delete pIntfDataAny; // free memory !
        }
        this->onNewData();

      }
    } // if (!ActKey.empty())
    else
    {
      EventLogExc("Trying to insert data without DataKey for " + Name, "CData_Provider::setAny", "");
    }

  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider::setAny " + Key + " " + Name, "");
  }


	return;
}

long CData_Provider::getLong(const std::string & Key, const std::string & Name)
{
  long RetValue = DEF::Inv_Long;

  CData_Provider_RuntimeController Controller(this,"CData_Provider::getLong",Key,Name);

  try
  {
    std::string ConvMessage;
    CIntfDataElement *pIntfDataElement = 0;
    CIntfData* pIntfData = 0;

    this->beforeDataAccess(Key,Name);

    // in case of empty Key the newest entry will be returned from the DataBuffer
    pIntfDataElement = IntfDataBuffer.findElement(Key);

    // get long data from DataBuffer entry
    if (pIntfDataElement)
    {
      pIntfDataElement->setRequestedName(Name);
      pIntfData = pIntfDataElement->findData(Name);

      // check and cast different data types
      if ( pIntfData && pIntfData->getType() == CIntfData::Long )
      {
        pIntfData->setRequested(true);

        CIntfDataLong* pIntfDataLong = dynamic_cast<CIntfDataLong*>(pIntfData);

        if (pIntfDataLong)
        {
          RetValue = pIntfDataLong->getData();
        }
      }
      else if ( pIntfData && pIntfData->getType() == CIntfData::Double )
      {
        pIntfData->setRequested(true);

        CIntfDataDouble* pIntfDataDouble = dynamic_cast<CIntfDataDouble*>(pIntfData);

        if (pIntfDataDouble)
        {
          RetValue = (long)pIntfDataDouble->getData();
          ConvMessage = "Data converted from DOUBLE !";
        }
      }
    }

    if (!pIntfData)
    {
      std::string Message;
      Message += Key;
      Message += " ";
      Message += CIntfData::Long;
      Message += " ";
      Message += Name;
      
      // write EventLog
      EventLogReadFailure(Message);
    }

	  std::ostringstream Message;

    if (getTraceLevel() > 4 )
    {
      Message << m_ProviderName
              << " returning CData_Provider::getLong for " 
              << Key 
              << " "
              << Name
              << " "
              << RetValue
              << " "
              << ConvMessage;

      log(Message.str(),6);
    }

    this->afterDataAccess(Key,Name);
  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider::getLong","read long");
  }

  return RetValue;
}

void CData_Provider::setLong(const std::string & Key, const std::string & Name, long value)
{
  // set new data to member variables
  std::string ActKey = Key;

  CData_Provider_RuntimeController Controller(this,"CData_Provider::setLong",Key,Name);

  try
  {
    if (getTraceLevel() > 4 )
    {
	    std::ostringstream Message;
      Message << m_ProviderName
              << " receiving CData_Provider::setLong for " 
              << Key 
              << " "
              << Name
              << " "
              << value;

      logEvaluated(Message.str(),Name);
    }

    // Key must not empty
    if (!ActKey.empty() && ActKey != DEF::Inv_String)
    {
      CIntfDataElement *pIntfDataElement = 0;
    
      pIntfDataElement = IntfDataBuffer.findElement(ActKey);

      if (!pIntfDataElement)
      {
        pIntfDataElement = IntfDataBuffer.insertElement(ActKey);
      }

      if (pIntfDataElement)
      {
        CIntfDataLong* pIntfDataLong = new CIntfDataLong(this,Name,ActKey);

        pIntfDataLong->setData(value);

        if (!pIntfDataElement->insertData(Name,pIntfDataLong))
        {
          delete pIntfDataLong; // free memory !
        }

        this->onNewData();

      }
    } // if (!ActKey.empty())
    else
    {
      EventLogExc("Trying to insert data without DataKey for " + Name, "CData_Provider::setLong", "set long");
    }
  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider::setLong","");
  }
}

void CData_Provider::indicate(const std::string & Key)
{
  try
  {
    // set new data to member variables
    std::string ActKey = Key;

    // Key must not empty
    if (!ActKey.empty() && ActKey != DEF::Inv_String)
    {
      CIntfDataElement *pIntfDataElement = 0;
    
      pIntfDataElement = IntfDataBuffer.findElement(ActKey);

      if (!pIntfDataElement)
      {
        pIntfDataElement = IntfDataBuffer.insertElement(ActKey);
        IntfDataBuffer.setLastIntfDataElement(pIntfDataElement);
      }
    } // if (!ActKey.empty())
    else
    {
      EventLogExc("Trying to insert data without DataKey", "CData_Provider::indicate", "");
    }

    this->onIndicate(Key);
  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider::indicate","");
  }
}

long CData_Provider::doComplete(const std::string & Key, const std::string & Action)
{
  long RetValue = DEF::Inv_Long;

  try
  {
    // just setting LastIntfDataElement
    if (!Key.empty())
    {
      IntfDataBuffer.findElement(Key);
      IntfDataBuffer.setCompleted(Key);
    }

    RetValue = this->onComplete(Key,Action);
  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider::doComplete","");
  }

  return RetValue;
}

CData_Provider::CData_Provider()
{
  IntfDataBuffer.setpData_Provider(this);
  Validator.setpData_Provider(this);
}

void CData_Provider::setBufferSize(long value)
{
  std::stringstream Message ;
  Message << m_ProviderName
          << " setting buffer size to "
          << value;

  log(Message.str(),6);

	IntfDataBuffer.setBufferSize(value);
}

void CData_Provider::onIndicate(const std::string & Key)
{
  try
  {
    if (getTraceLevel() > 4)
    {
      std::string Message = m_ProviderName;
      Message += " executing CData_Provider::onIndicate() for ";
      Message += m_ProviderName;
      Message += "  Key: ";
      Message += Key;

      log(Message,6);
    }
  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider::onIndicate","");
  }

}

long CData_Provider::onComplete(const std::string & Key,const std::string & Action)
{
  long RetValue = DEF::Inv_Long;

  try
  {
    if (getTraceLevel() > 3)
    {
      std::string Message = m_ProviderName;
      Message += " executing CData_Provider::onComplete(...) for ";
      Message += m_ProviderName;
      Message += "  Key: ";
      Message += Key;
      Message += "  Action: ";
      Message += Action;

      log(Message,6);
    }
  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider::onComplete", "");
  }

  return RetValue;
}

void CData_Provider::log(const std::string & Message, long Level)
{
  std::cout << Message << std::endl;
}

std::string  CData_Provider::getString(const std::string & Key, const std::string & Name)
{
  std::string RetValue = DEF::Inv_String;

  CData_Provider_RuntimeController Controller(this,"CData_Provider::getString",Key,Name);

  try
  {
    std::string ConvMessage;
    CIntfDataElement *pIntfDataElement = 0;
    CIntfData* pIntfData = 0;

    this->beforeDataAccess(Key,Name);

    // in case of empty Key the newest entry will be returned from the DataBuffer
    pIntfDataElement = IntfDataBuffer.findElement(Key);

    // get String data from DataBuffer entry
    if (pIntfDataElement)
    {
      pIntfDataElement->setRequestedName(Name);
      pIntfData = pIntfDataElement->findData(Name);

      // check and cast different data types
      if ( pIntfData && pIntfData->getType() == CIntfData::String )
      {
        pIntfData->setRequested(true);

        CIntfDataString* pIntfDataString = dynamic_cast<CIntfDataString*>(pIntfData);

        if (pIntfDataString)
        {
          RetValue = pIntfDataString->getData();
        }
      }
      else if ( pIntfData && pIntfData->getType() == CIntfData::Long )
      {
        pIntfData->setRequested(true);

        CIntfDataLong* pIntfDataLong = dynamic_cast<CIntfDataLong*>(pIntfData);

        if (pIntfDataLong)
        {
          std::ostringstream Value;
          Value << pIntfDataLong->getData();
          RetValue = Value.str();
          ConvMessage = "Data converted from LONG !";
        }
      }
      else if ( pIntfData && pIntfData->getType() == CIntfData::Double )
      {
        pIntfData->setRequested(true);

        CIntfDataDouble* pIntfDataDouble = dynamic_cast<CIntfDataDouble*>(pIntfData);

        if (pIntfDataDouble)
        {
          std::ostringstream Value;
          Value << pIntfDataDouble->getData();
          RetValue = Value.str();
          ConvMessage = "Data converted from DOUBLE !";
        }
      }
      else if ( pIntfData && pIntfData->getType() == CIntfData::Bool )
      {
        pIntfData->setRequested(true);

        CIntfDataBoolean* pIntfDataBoolean = dynamic_cast<CIntfDataBoolean*>(pIntfData);

        if (pIntfDataBoolean)
        {
          std::ostringstream Value;
          Value << pIntfDataBoolean->getData();
          RetValue = Value.str();
          ConvMessage = "Data converted from BOOLEAN !";
        }
      }
    }

    if (!pIntfData)
    {
      std::string Message;
      Message += Key;
      Message += " ";
      Message += CIntfData::String;
      Message += " ";
      Message += Name;
      
      // write EventLog
      EventLogReadFailure(Message);
    }

    if (getTraceLevel() > 4)
    {
  	  std::ostringstream Message;

      Message << m_ProviderName
              << " returning CData_Provider::getString for " 
              << Key 
              << " "
              << Name
              << " "
              << RetValue
              << " " 
              << ConvMessage;


      log(Message.str(),6);
    }

    this->afterDataAccess(Key,Name);

  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider::getString", "");
  }

  return RetValue;
}

void CData_Provider::setString(const std::string & Key, const std::string & Name, const std::string & value)
{
  // set new data to member variables
  std::string ActKey = Key;

  CData_Provider_RuntimeController Controller(this,"CData_Provider::setString",Key,Name);

  try
  {
    if (getTraceLevel() > 4 )
    {
	    std::ostringstream Message;
      Message << m_ProviderName
              << " receiving CData_Provider::setString for " 
              << Key 
              << " "
              << Name
              << " "
              << value;

      logEvaluated(Message.str(),Name);
    }

    // Key must not empty
    if (!ActKey.empty() && ActKey != DEF::Inv_String)
    {
      CIntfDataElement *pIntfDataElement = 0;
    
      pIntfDataElement = IntfDataBuffer.findElement(ActKey);

      if (!pIntfDataElement)
      {
        pIntfDataElement = IntfDataBuffer.insertElement(ActKey);
      }

      if (pIntfDataElement)
      {
        CIntfDataString* pIntfDataString = new CIntfDataString(this,Name,ActKey);

        pIntfDataString->setData(value);

        if (!pIntfDataElement->insertData(Name,pIntfDataString))
        {
          delete pIntfDataString; // free memory !
        }

        this->onNewData();

      }
    } // if (!ActKey.empty())
    else
    {
      EventLogExc("Trying to insert data without DataKey for " + Name, "CData_Provider::setString", "set string");
    }
  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider::setString", "");
  }

	return;
}

void CData_Provider::onNewData()
{
}

double CData_Provider::getDouble(const std::string & Key, const std::string & Name)
{
  double RetValue = DEF::Inv_Double;

  CData_Provider_RuntimeController Controller(this,"CData_Provider::getDouble",Key,Name);


  try
  {
    std::string ConvMessage;
    CIntfDataElement *pIntfDataElement = 0;
    CIntfData* pIntfData = 0;

    this->beforeDataAccess(Key,Name);

    // in case of empty Key the newest entry will be returned from the DataBuffer
    pIntfDataElement = IntfDataBuffer.findElement(Key);

    // get double data from DataBuffer entry
    if (pIntfDataElement)
    {
      pIntfDataElement->setRequestedName(Name);
      pIntfData = pIntfDataElement->findData(Name);

      // check and cast different data types
      if ( pIntfData && pIntfData->getType() == CIntfData::Double )
      {
        pIntfData->setRequested(true);

        CIntfDataDouble* pIntfDataDouble = dynamic_cast<CIntfDataDouble*>(pIntfData);

        if (pIntfDataDouble)
        {
          RetValue = pIntfDataDouble->getData();
        }
      }
      else if ( pIntfData && pIntfData->getType() == CIntfData::Long )
      {
        pIntfData->setRequested(true);

        CIntfDataLong* pIntfDataLong = dynamic_cast<CIntfDataLong*>(pIntfData);

        if (pIntfDataLong)
        {
          RetValue = (double)pIntfDataLong->getData();
          ConvMessage = "Data converted from LONG !";
        }
      }
    }

    if (!pIntfData)
    {
      std::string Message;
      Message += Key;
      Message += " ";
      Message += CIntfData::Double;
      Message += " ";
      Message += Name;
      
      // write EventLog
      EventLogReadFailure(Message);
    }

    if (getTraceLevel() > 4)
    {
	    std::ostringstream Message;

      Message << m_ProviderName
              << " returning CData_Provider::getDouble for " 
              << Key 
              << " "
              << Name
              << " "
              << RetValue
              << " " 
              << ConvMessage;

      log(Message.str(),6);
    }

    this->afterDataAccess(Key,Name);
  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider::getDouble", "read double");
  }
  return RetValue;
}

void CData_Provider::setDouble(const std::string & Key, const std::string & Name, double value)
{
  // set new data to member variables
  std::string ActKey = Key;
  
  CData_Provider_RuntimeController Controller(this,"CData_Provider::setDouble",Key,Name);

  try
  {
    if (getTraceLevel() > 4 )
    {
	    std::ostringstream Message;
      Message << m_ProviderName
              << " receiving CData_Provider::setDouble for " 
              << Key 
              << " "
              << Name
              << " "
              << value;

      logEvaluated(Message.str(),Name);
    }

    // Key must not empty
    if (!ActKey.empty() && ActKey != DEF::Inv_String)
    {
      CIntfDataElement *pIntfDataElement = 0;
    
      pIntfDataElement = IntfDataBuffer.findElement(ActKey);

      if (!pIntfDataElement)
      {
        pIntfDataElement = IntfDataBuffer.insertElement(ActKey);
      }

      if (pIntfDataElement)
      {
        CIntfDataDouble* pIntfDataDouble = new CIntfDataDouble(this,Name,ActKey);

        pIntfDataDouble->setData(value);

        if (!pIntfDataElement->insertData(Name,pIntfDataDouble))
        {
          delete pIntfDataDouble; // free memory !
        }

        this->onNewData();

      }
    } // if (!ActKey.empty())
    else
    {
      EventLogExc("Trying to insert data without DataKey for " + Name, "CData_Provider::setDouble", "set double");
    }
  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider::setDouble", "");
  }

	return;
}

void CData_Provider::setBoolean(const std::string & Key, const std::string & Name, CORBA::Boolean value)
{
  // set new data to member variables
  std::string ActKey = Key;

  CData_Provider_RuntimeController Controller(this,"CData_Provider::setBoolean",Key,Name);

  try
  {
    if (getTraceLevel() > 4 )
    {
	    std::ostringstream Message;
      Message << m_ProviderName
              << " receiving CData_Provider::setBoolean for " 
              << Key 
              << " "
              << Name
              << " "
              << value;

      logEvaluated(Message.str(),Name);
    }

    // Key must not empty
    if (!ActKey.empty() && ActKey != DEF::Inv_String)
    {
      CIntfDataElement *pIntfDataElement = 0;
    
      pIntfDataElement = IntfDataBuffer.findElement(ActKey);

      if (!pIntfDataElement)
      {
        pIntfDataElement = IntfDataBuffer.insertElement(ActKey);
      }

      if (pIntfDataElement)
      {
        CIntfDataBoolean* pIntfDataBoolean = new CIntfDataBoolean(this,Name,ActKey);

        pIntfDataBoolean->setData(value);

        if (!pIntfDataElement->insertData(Name,pIntfDataBoolean))
        {
          delete pIntfDataBoolean; // free memory !
        }

        this->onNewData();

      }
    } // if (!ActKey.empty())
    else
    {
      EventLogExc("Trying to insert data without DataKey for " + Name, "CData_Provider::setBoolean", "set bool");
    }
  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider::setBoolean", "");
  }

	return;
}

CORBA::Boolean CData_Provider::getBoolean(const std::string & Key, const std::string & Name)
{
  CORBA::Boolean RetValue = 0;

  try
  {
    CIntfDataElement *pIntfDataElement = 0;
    CIntfData* pIntfData = 0;
    this->beforeDataAccess(Key,Name);

    // in case of empty Key the newest entry will be returned from the DataBuffer
    pIntfDataElement = IntfDataBuffer.findElement(Key);

    // get Boolean data from DataBuffer entry
    if (pIntfDataElement)
    {
      pIntfDataElement->setRequestedName(Name);
      pIntfData = pIntfDataElement->findData(CIntfData::Bool,Name);

      if ( pIntfData )
      {
        pIntfData->setRequested(true);

        CIntfDataBoolean* pIntfDataBoolean = dynamic_cast<CIntfDataBoolean*>(pIntfData);

        if (pIntfDataBoolean)
        {
          RetValue = pIntfDataBoolean->getData();
        }
      }
    }

    if (!pIntfData)
    {
      std::string Message;
      Message += Key;
      Message += " ";
      Message += CIntfData::Bool;
      Message += " ";
      Message += Name;
      
      // write EventLog
      EventLogReadFailure(Message);
    }


    if (getTraceLevel() > 4)
    {
	    std::ostringstream Message;

      Message << m_ProviderName
              << " returning CData_Provider::getBoolean for " 
              << Key 
              << " "
              << Name
              << " "
              << RetValue;

      log(Message.str(),6);
    }

    this->afterDataAccess(Key,Name);
  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider::getBoolean", "");
  }

  return RetValue;
}

std::vector<CIntfData*> CData_Provider::getIntfDataList(const std::string& Key)
{
  CData_Provider_RuntimeController Controller(this,"CData_Provider::getIntfDataList",Key,"");

  std::vector<CIntfData*> RetList;

  try
  { 
    std::string Message = m_ProviderName;
    Message += " returning CData_Provider::getIntfDataList for ";
    Message += Key;

    log(Message,6);


    CIntfDataElement *pIntfDataElement = 0;

    // in case of empty Key the newest entry will be returned from the DataBuffer
    pIntfDataElement = IntfDataBuffer.findElement(Key);

    // get Boolean data from DataBuffer entry
    if (pIntfDataElement)
    {
      RetList = pIntfDataElement->getIntfDataList();
    }
  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider::getIntfDataList", "");
  }

  return RetList;
}

std::set<std::string> CData_Provider::getIntfReqList(const std::string& Key)
{
  CData_Provider_RuntimeController Controller(this,"CData_Provider::getIntfReqList",Key,"");

  std::set<std::string> RetList;

  try
  { 
    if (getTraceLevel() > 4)
    {
      std::string Message = m_ProviderName;
      Message += " returning CData_Provider::getIntfReqList for ";
      Message += Key;

      log(Message,6);
    }

    CIntfDataElement *pIntfDataElement = 0;

    // in case of empty Key the newest entry will be returned from the DataBuffer
    pIntfDataElement = IntfDataBuffer.findElement(Key);

    // get Boolean data from DataBuffer entry
    if (pIntfDataElement)
    {
      RetList = pIntfDataElement->getIntfReqList();
    }
  }
  catch(...)
  {
    EventLogExc("Unknown","CData_Provider::getIntfReqList","");
  }

  return RetList;
}

std::vector<std::string> CData_Provider::getIntfKeyList()
{
  std::vector<CIntfDataElement*>  IntfDataElementList = IntfDataBuffer.getIntfDataElementList();
  std::vector<CIntfDataElement*>::iterator it;

  std::vector<std::string> IntfKeyList;

  for ( it = IntfDataElementList.begin(); it != IntfDataElementList.end(); ++ it)
  {
    std::string Key = (*it)->getKey();
    IntfKeyList.push_back(Key);
  }

  return IntfKeyList;
}



std::string  CData_Provider::generateDataKey(const std::string& Value)
{
  std::string NewDataKey;

  try
  {
    IntfDataBuffer.generateKey(NewDataKey);

    NewDataKey = Value + "_" + NewDataKey;
  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider::generateDataKey", "");
  }

  return NewDataKey;
}


void CData_Provider::showContent(const std::string& Key, long Level)
{
  if (! m_Critical_Section.lock("CData_Provider::showContent"))
  {
    return;
  }

  try
  {
    if ( getTraceLevel() >= Level)
    {
      std::string Message("************* Actual interface content ************** :  ");
      Message += m_ProviderName;

      log(Message,Level);

	    IntfDataBuffer.showContent(Key,Level);

      log("****************************************************",Level);
    }
  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider::showContent", "");
  }

  m_Critical_Section.unlock("CData_Provider::showContent");

}

void CData_Provider::setPersistence(const std::string& Key, bool Value)
{
  if (! m_Critical_Section.lock("CData_Provider::setPersistence"))
  {
    return;
  }

  CData_Provider_RuntimeController Controller(this,"CData_Provider::setPersistence",Key,"");


  try
  {
    CIntfDataElement *pIntfDataElement = 0;

    // in case of empty Key the newest entry will be returned from the DataBuffer
    pIntfDataElement = IntfDataBuffer.findElement(Key);

    if (!pIntfDataElement)
    {
      pIntfDataElement = IntfDataBuffer.insertElement(Key);
    }
   
    // get Boolean data from DataBuffer entry
    pIntfDataElement->setPersistent(Value);

  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider::setPersistence", "");
  }

  m_Critical_Section.unlock("CData_Provider::setPersistence");

}

bool CData_Provider::getPersistence(const std::string& Key)
{
  if (! m_Critical_Section.lock("CData_Provider::getPersistence"))
  {
    return false;
  }

  bool RetValue = false;

  CData_Provider_RuntimeController Controller(this,"CData_Provider::setPersistence",Key,"");

  try
  {
    CIntfDataElement *pIntfDataElement = 0;

    // in case of empty Key the newest entry will be returned from the DataBuffer
    pIntfDataElement = IntfDataBuffer.findElement(Key);

    if (pIntfDataElement)
    {
      // get Boolean data from DataBuffer entry
      RetValue = pIntfDataElement->getPersistent();
    }
  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider::setPersistence", "");
  }

  m_Critical_Section.unlock("CData_Provider::getPersistence");

  return RetValue;
}


std::string  CData_Provider::getKey(long Index)
{
  if (! m_Critical_Section.lock("CData_Provider::getKey"))
  {
    std::string t;
    return t;
  }

  std::string RetValue;

  try
  {
    RetValue = IntfDataBuffer.findKey(Index);
  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider::getKey", "");
  }

  m_Critical_Section.unlock("CData_Provider::getKey");

  return RetValue;
}

long CData_Provider::getSize()
{
  if (! m_Critical_Section.lock("CData_Provider::getSize"))
  {
    return DEF::Inv_Long;
  }

  long RetValue;

  try
  {
    RetValue = IntfDataBuffer.getIntfDataElementListLength();
  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider::getSize", "");
  }

  m_Critical_Section.unlock("CData_Provider::getSize");

  return RetValue;

}

std::map<std::string,std::string> CData_Provider::getIntfDataTypeList(const std::string& Key)
{
  CData_Provider_RuntimeController Controller(this,"CData_Provider::getIntfDataTypeList",Key,"");
  
  std::map<std::string,std::string> IntfDataNameList;

  try
  {
    std::vector<CIntfData*>::iterator it;
    std::vector<CIntfData*> IntfDataList = getIntfDataList(Key);

    for ( it = IntfDataList.begin(); it != IntfDataList.end(); ++ it)
    {
      IntfDataNameList.insert( std::pair<std::string,std::string>( (*it)->getName(),(*it)->getType() ) );
    }
  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider::getIntfDataTypeList", "");
  }

  return IntfDataNameList;
  
}

std::map<std::string,std::string> CData_Provider::getRequestedIntfDataTypeList(const std::string& Key)
{
  CData_Provider_RuntimeController Controller(this,"CData_Provider::getRequestedIntfDataTypeList",Key,"");
  
  std::map<std::string,std::string> IntfDataNameList;

  try
  {
    std::vector<CIntfData*>::iterator it;
    std::vector<CIntfData*> IntfDataList = getIntfDataList(Key);

    for ( it = IntfDataList.begin(); it != IntfDataList.end(); ++ it)
    {
      if ( (*it)->isRequested() )
      {
        IntfDataNameList.insert( std::pair<std::string,std::string>( (*it)->getName(),(*it)->getType() ) );
      }
    }
  }
  catch(...)
  {
    EventLogExc("Unknown","CData_Provider::getRequestedIntfDataTypeList","");
  }

  return IntfDataNameList;
  
}




void CData_Provider::beforeDataAccess(const std::string & Key,const std::string & Name)
{
}


void CData_Provider::afterDataAccess(const std::string & Key,const std::string & Name)
{
}


bool CData_Provider::deleteData(const std::string & Key, const std::string & Name)
{
  if (! m_Critical_Section.lock("CData_Provider::deleteData"))
  {
    return false;
  }

  bool RetValue = false;

  try
  {
    if (!Key.empty())
    {
      CIntfDataElement *pIntfDataElement = 0;
      pIntfDataElement = IntfDataBuffer.findElement(Key);

      if (pIntfDataElement)
      {
        std::vector<CIntfData*> IntfDataList = getIntfDataList(Key);
        std::vector<CIntfData*>::iterator it;

        for ( it = IntfDataList.begin(); it != IntfDataList.end(); ++ it)
        {
          // delete each entry if Name == ""
          if (Name.empty())        
          {
            pIntfDataElement->deleteData((*it)->getName());
            RetValue = true;
          }
          // delete only entry for name
          else
          {
            if ( Name == (*it)->getName() )
            {
              pIntfDataElement->deleteData((*it)->getName());
              RetValue = true;
              break;
            }
          }// else
        }// for ( it = IntfDataList
      }// if (pIntfDataElement)
    }// if (!Key.empty())
    else
    {
      log("Error deleting Data! Empty Key received", 6);
    }
  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider::deleteData", "");
  }

  m_Critical_Section.unlock("CData_Provider::deleteData");

  return RetValue;
}

void CData_Provider::setProviderName(std::string& value)
{
  if (! m_Critical_Section.lock("CData_Provider::setProviderName"))
  {
    return;
  }

  m_Critical_Section.setProviderName(value);
  m_ProviderName = value;

  m_Critical_Section.unlock("CData_Provider::setProviderName");

}

bool CData_Provider::isLoggingOn()
{
	return true;
}


std::string  CData_Provider::getIntfDataType(const std::string& Key, const std::string& Name)
{
  CData_Provider_RuntimeController Controller(this,"CData_Provider::getIntfDataType",Key,Name);

  std::string RetValue;

  try
  { 
    // in case of empty Key the newest entry will be returned from the DataBuffer
    CIntfDataElement *pIntfDataElement = IntfDataBuffer.findElement(Key);

    // get Data from DataBuffer entry
    if (pIntfDataElement)
    {
      CIntfData* pIntfData = pIntfDataElement->findData(Name);

      if (pIntfData)
      {
        RetValue = pIntfData->getType();

        if (getTraceLevel() > 4)
        {
          std::string Message = m_ProviderName;
          Message += " returning CData_Provider::getIntfDataType for ";
          Message += Key;
          Message += " ";
          Message += Name;
          Message += " ";
          Message += RetValue;

          log(Message,6);
        }
      }
    }
  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider::getIntfDataList", "");
  }

  return RetValue;
}

/** not used 
std::multimap<std::string,CIntfDataRuleSet*> CData_Provider::getRuleSetList(const std::string &Key)
{
  CData_Provider_RuntimeController Controller(this,"CData_Provider::getRuleSetList",Key,"");

  std::multimap<std::string,CIntfDataRuleSet*> ActRuleSetList;
  std::multimap<std::string,CIntfDataRuleSet*> NewRuleSetList;
  std::multimap<std::string,CIntfDataRuleSet*>::iterator it;

  ActRuleSetList = Validator.getRuleSetList();

  for( it = ActRuleSetList.begin() ; it != ActRuleSetList.end() ; ++it)
  {
    if ( it->second->getKey() == Key )
    {
      NewRuleSetList.insert(std::pair<std::string,CIntfDataRuleSet*>(it->first,it->second));
    }
  }

	return NewRuleSetList;
}
**/


/** not used 
std::set<std::string> CData_Provider::getRuleSetNames(const std::string& Key)
{
  CData_Provider_RuntimeController Controller(this,"CData_Provider::getRuleSetNames",Key,"");

  std::multimap<std::string,CIntfDataRuleSet*> ActRuleSetList;
  std::multimap<std::string,CIntfDataRuleSet*>::iterator it;
  std::set<std::string> RuleSetNames;

  ActRuleSetList = Validator.getRuleSetList();

  for( it = ActRuleSetList.begin() ; it != ActRuleSetList.end() ; ++it)
  {
    if ( it->second->getKey() == Key )
    {
      RuleSetNames.insert(it->first);
    }
  }

	return RuleSetNames;
}
**/

std::string CData_Provider::getProviderName()
{
	return m_ProviderName;
}

void CData_Provider::logEvaluated(const std::string& Message, const std::string& Name)
{
  try
  { 
    std::set<std::string>::iterator it = m_EvaluationList.find(Name);

    if ( it != m_EvaluationList.end() )
    {
      log(" ********** Evaluating ************ " + Name,6);
    }

    log(Message,6);

  }
  catch(...)
  {
    EventLogExc("Unknown", "CData_Provider::logEvaluated", "");
  }
}

bool CData_Provider::isKey(const std::string& Key)
{
  if (! m_Critical_Section.lock("CData_Provider::isKey"))
  {
    return false;
  }

  CData_Provider_RuntimeController Controller(this,"CData_Provider::isKey",Key,"isKey");

  bool RetValue = false;

  CIntfDataElement *pIntfDataElement = 0;

  // in case of empty Key the newest entry will be returned from the DataBuffer
  pIntfDataElement = IntfDataBuffer.findElement(Key);

  // get Any data from DataBuffer entry
  if (pIntfDataElement)
  {
	  RetValue = true;
  }

  m_Critical_Section.unlock("CData_Provider::isKey");

  return RetValue;
}

bool CData_Provider::isUpdated(const std::string& Key,const std::string& Name)
{
  bool RetValue = false;

  CIntfDataElement *pIntfDataElement = IntfDataBuffer.findElement(Key);

  if (pIntfDataElement)
  {
    RetValue = pIntfDataElement->isUpdated(Name);
  }

  return RetValue;
}

void CData_Provider::onDeleteDataKey(const std::string& Key)
{
}