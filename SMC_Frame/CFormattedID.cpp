// Copyright (C) 2004 SMS Demag AG

#include <valarray>
#include <sstream>
#include <algorithm>
#include <iomanip>

#include "iSMC_DataDefinitions_s.hh"

#include "cCBS_StdLog_Task.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CSMC_EventLogFrameController.h"

#include "CFormattedIDElement.h"
#include "CFormattedID.h"

CFormattedID::CFormattedID() 
: m_FormattedIDLength(0)
{
}

CFormattedID::CFormattedID(const CFormattedID& FormattedID)
{
  //simple types can just be copied
  m_SampleTypeList = FormattedID.m_SampleTypeList;
  m_Format = FormattedID.m_Format;
  m_QualifierList = FormattedID.m_QualifierList;
  m_FormattedIDLength = FormattedID.m_FormattedIDLength;
  //complex pointer types need special handling
  std::vector<CFormattedIDElement*>::const_iterator iter;
  for (iter = FormattedID.m_FormattedIDElementList.begin();
    iter != FormattedID.m_FormattedIDElementList.end(); iter++)
  {
    CFormattedIDElement* pFormattedIDElement = new CFormattedIDElement(**iter);

    m_FormattedIDElementList.push_back(pFormattedIDElement);
  }
}

CFormattedID::~CFormattedID()
{
  std::vector<CFormattedIDElement*>::iterator it;

  for ( it = m_FormattedIDElementList.begin() ; it != m_FormattedIDElementList.end() ; it++)
  {
    delete (*it);
  }
}

CFormattedID& CFormattedID::operator=(const CFormattedID& FormattedID)
{
  //check for self-assignment
  if (this == &FormattedID)
    return *this;

  //simple types
  m_SampleTypeList = FormattedID.m_SampleTypeList;
  m_Format = FormattedID.m_Format;
  m_QualifierList = FormattedID.m_QualifierList;
  m_FormattedIDLength = FormattedID.m_FormattedIDLength;
  //complex pointer types need special handling

  std::vector<CFormattedIDElement*>::iterator it;
  for ( it = m_FormattedIDElementList.begin() ; it != m_FormattedIDElementList.end() ; it++)
  {
    delete (*it);
  }

  m_FormattedIDElementList.clear();

  std::vector<CFormattedIDElement*>::const_iterator iter;
  for (iter = FormattedID.m_FormattedIDElementList.begin();
    iter != FormattedID.m_FormattedIDElementList.end(); iter++)
  {
    CFormattedIDElement* pFormattedIDElement = new CFormattedIDElement(**iter);

    m_FormattedIDElementList.push_back(pFormattedIDElement);
  }

  return *this;
}


void CFormattedID::init()
{
}


void CFormattedID::setFormat(const std::string& value)
{
  m_Format            = value;
  m_FormattedIDLength = 0; // will be recalculated

  // parse m_Format for valid entries and build FormattedIDElementList
  std::basic_string <char>::iterator it;

  std::string FormatQualifier;

  for( it = m_Format.begin() ; it != m_Format.end() ; it++)
  {
    std::stringstream ActChar;

    ActChar << *it;

    FormatQualifier = ActChar.str();

    // entry in m_QualifierList or not ?
    if ( m_QualifierList.find(FormatQualifier) == m_QualifierList.end() )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorFormattedIdHandling(sMessage,FormatQualifier.c_str(),
                                           "FormatQualifier not found !");
    }
  }

  // Format could be like TPPC
  // check position and Length of each FormatQualifier

  std::set<std::string>::iterator itQL; 

  for ( itQL = m_QualifierList.begin() ; itQL != m_QualifierList.end(); itQL++)
  {
    std::string QualifierListElement = *itQL;

    // find respective FormattedIDElement if already defined
    CFormattedIDElement* pFormattedIDElement = getFormattedIDElement(QualifierListElement);

    long Position = -1;
    long Length   = 0;

    // if position is available calculate Length
    if ( std::string::npos != (Position = (long)m_Format.find_first_of(QualifierListElement)) )
    {
      Length   = (long)m_Format.find_last_of(QualifierListElement) - Position + 1;

      // Length of FormattedID == Length of valid format entries
      m_FormattedIDLength += Length;

    }

    if (pFormattedIDElement)
    {
      pFormattedIDElement->setLength(Length);
      pFormattedIDElement->setPos(Position);
    }

  }

  return;
}//void CFormattedID::setFormat(const std::string& value)

void CFormattedID::generateString(const CFormattedIDElement* pFormattedIDElement, std::string  Value, std::string &ActString, const std::string  FillSign) const
{
  try
  {
    if (pFormattedIDElement && !Value.empty() )
    {
      long Pos    = pFormattedIDElement->getPos();
      long Length = pFormattedIDElement->getLength();
      bool TruncateLeft = pFormattedIDElement->getTruncateLeft();

      // if ID might be truncated change lenght
      if ( pFormattedIDElement->getTruncate() )
      {

      }

      if ( Length > 0 )
      {
        std::stringstream ssAct;

        // formatting stream
        if ( !FillSign.empty() )
        {
          ssAct << std::setfill(*FillSign.c_str());
          ssAct << std::setw(Length);
        }

        // if Value is longer then Length, Value will be truncated !!
        if ( (long)Value.length() > Length )
        {
          if (!TruncateLeft)
          {
            Value = Value.substr(0,Length);
          }
          else
          { 
            Value = Value.substr((long)Value.length()-Length,Length);
          }
          log("CFormattedID::generateString() Value truncated to " + Value,3);
        }

        long ExtendedLength = Pos + Length - ActString.length();

        // replace will throw exception if ActString is too short!
        if ( ExtendedLength > 0 )
        {
          ActString.append(ExtendedLength,' ');

          // log error !
          log("CFormattedID::generateString() String extended to  " + ActString,3);
        }


        ssAct << Value ;
        std::string Replace = ssAct.str();
        ActString.replace(Pos, Length, Replace);


      }
    }
  }
  catch(...)
  {
    std::stringstream ExceptionMsg;
    ExceptionMsg << "Generating string with value " << Value << " for " << ActString;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                          "CFormattedID::generateString",
                                          ExceptionMsg.str().c_str());

  }
}//void CFormattedID::generateString(CFormattedIDElement* pFormattedIDElement, std::string  Value, std::string &ActString, std::string  FillSign)

void CFormattedID::generateString(const std::string& Qualifier, std::string  Value, std::string &ActString, const std::string  FillSign) const
{
  try
  {
    const CFormattedIDElement* pFormattedIDElement = getFormattedIDElement(Qualifier);

    if (pFormattedIDElement && !Value.empty() )
    {
      long Pos    = pFormattedIDElement->getPos();
      long Length = pFormattedIDElement->getLength();
      bool TruncateLeft = pFormattedIDElement->getTruncateLeft();

      if ( Length > 0 )
      {
        std::stringstream ssAct;

        // formatting stream
        if ( !FillSign.empty() )
        {
          ssAct << std::setfill(*FillSign.c_str());
          ssAct << std::setw(Length);
        }

        // if Value is longer then Length, Value will be truncated !!
        if ( (long)Value.length() > Length )
        {
          if (!TruncateLeft)
          {
            Value = Value.substr(0,Length);
          }
          else
          { 
            Value = Value.substr((long)Value.length()-Length,Length);
          }
          log("CFormattedID::generateString() Value truncated to " + Value,3);
        }

        long ExtendedLength = Pos + Length - ActString.length();

        // replace will throw exception if ActString is too short!
        if ( ExtendedLength > 0 )
        {
          ActString.append(ExtendedLength,' ');

          // log error !
          log("CFormattedID::generateString() String extended to  " + ActString,3);
        }


        ssAct << Value ;
        std::string Replace = ssAct.str();
        ActString.replace(Pos, Length, Replace);


      }
    }
  }
  catch(...)
  {
    std::stringstream ExceptionMsg;
    ExceptionMsg << "Generating string with value " << Value << " for " << ActString;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                          "CFormattedID::generateString",
                                          ExceptionMsg.str().c_str());

  }
}//void CFormattedID::generateString(const std::string& Qualifier, std::string  Value, std::string &ActString, const std::string  FillSign) const



CFormattedIDElement* CFormattedID::getFormattedIDElement(const std::string&  Qualifier)
{
  CFormattedIDElement* pFormattedIDElement = 0;

  std::vector<CFormattedIDElement*>::iterator it;


  for ( it = m_FormattedIDElementList.begin() ; it != m_FormattedIDElementList.end() ; it++)
  {
    if ( (*it)->getQualifier() == Qualifier )
    {
      pFormattedIDElement = (*it);
      break;
    }
  }

  return pFormattedIDElement;
}//CFormattedIDElement* CFormattedID::getFormattedIDElement(const std::string&  Qualifier)

const CFormattedIDElement* CFormattedID::getFormattedIDElement(const std::string& Qualifier) const
{
  CFormattedIDElement* pFormattedIDElement = 0;

  std::vector<CFormattedIDElement*>::const_iterator it;


  for ( it = m_FormattedIDElementList.begin() ; it != m_FormattedIDElementList.end() ; it++)
  {
    if ( (*it)->getQualifier() == Qualifier )
    {
      pFormattedIDElement = (*it);
      break;
    }
  }

  return pFormattedIDElement;
}//const CFormattedIDElement* CFormattedID::getFormattedIDElement(const std::string& Qualifier) const

bool CFormattedID::isValidID(const std::string & ID, std::string & ErrorMessage) const
{
  bool RetValue = true;
  std::stringstream Message;

  std::vector<CFormattedIDElement*>::const_iterator it;

  // format could be like HH:MM:SS
  // ID could be like 12:34:56 or like 123:4:56

  // first check for valid Length, ID may be shorter !
  if ( (long)ID.length() > m_FormattedIDLength )
  {
    Message << " - ERROR : ID " << ID << " too long for format " <<  m_Format;
    RetValue = false;
  }

  if ( (long)ID.length() < m_FormattedIDLength )
  {
    Message << " - WARNING : ID " << ID << " too short for format " <<  m_Format;
    RetValue = false;
  }

  if ( ID.empty() )
  {
    Message << " - WARNING : ID empty ";
    RetValue = false;
  }


  // check if FixedType and/or Fixed are correct
  for ( it = m_FormattedIDElementList.begin() ; it != m_FormattedIDElementList.end() ; it++)
  {
    long Pos = (*it)->getPos();
    long Len = (*it)->getLength();

    if( (*it)->isUsed() )
    {
      std::string Qual = (*it)->getQualifier();

      std::string Extract;
      
      if ( (long)ID.length() >= Pos + Len )
      {
        Extract = ID.substr(Pos,Len);
      }

      std::string Fixed     = (*it)->getFixed();
      std::string FixedType = (*it)->getFixedType();

      // check if fixed entry is found at correct position and Length
      if ( !Fixed.empty() && Fixed != Extract ) 
      {
        RetValue = false;
      }

      // check for numeric entry
      if ( FixedType == CFormattedIDElement::Numeric )
      {
        long ActNum = 0;
        std::istringstream istr(Extract);
        
        // does not seem to be numeric !
        if (! (istr >> ActNum ) )
        {
          Message << " - ERROR : ID not numeric ";
          RetValue = false;
        }
      } // if ( FixedType == CFormattedIDElement::Numeric )
    } // if( Pos >= 0 && Len > 0 )
  } // for ( it = m_FormattedIDElementList.begin() ; it != m_FormattedIDElementList.end() ; it++)

  ErrorMessage += Message.str();

  return RetValue;
}//bool CFormattedID::isValidID(const std::string & ID, std::string & ErrorMessage)



void CFormattedID::fixFormattedIDElement(const std::string& Qualifier, const std::string& Fixed)
{
  std::vector<CFormattedIDElement*>::iterator it;
  std::string ActFixed(Fixed);

  // find Qualifier 
  for ( it = m_FormattedIDElementList.begin() ; it != m_FormattedIDElementList.end() ; it++)
  {
    if ( Qualifier == (*it)->getQualifier() )
    {
      (*it)->setFixed(ActFixed);
    }
  }
}//void CFormattedID::fixFormattedIDElement(const std::string& Qualifier, const std::string& Fixed)



void CFormattedID::addFormattedIDElement(const std::string& Qualifier, const std::string& FixedType /* = "" */, const std::string& Fixed /* = "" */, bool Truncate /* = false */)
{
  m_QualifierList.insert(Qualifier);

  CFormattedIDElement* pFormattedIDElement = new CFormattedIDElement(Qualifier);

  pFormattedIDElement->setFixedType(std::string(FixedType));
  pFormattedIDElement->setFixed(std::string(Fixed));
  pFormattedIDElement->setTruncate(Truncate);

  m_FormattedIDElementList.push_back(pFormattedIDElement);

}//void CFormattedID::addFormattedIDElement(const std::string& Qualifier, const std::string& FixedType /* = "" */, const std::string& Fixed /* = "" */, bool Truncate /* = false */)



std::string CFormattedID::getString(const std::string& ID, const std::string& Default, const std::string& Qualifier) const
{
  std::string Result;
  std::string ActID(ID);

  try
  {
    if ( ActID.empty() )
    {
      ActID = Default;
    }

    if ( !ActID.empty() && ActID != DEF::Inv_String )
    {
      const CFormattedIDElement* pFormattedIDElement = getFormattedIDElement(Qualifier);

      if (pFormattedIDElement && pFormattedIDElement->isUsed() )
      {
        if ( (long)ActID.length() >= ( pFormattedIDElement->getPos() + pFormattedIDElement->getLength() ) )
        {
          Result = ActID.substr(pFormattedIDElement->getPos(),pFormattedIDElement->getLength());
        }
      }
    }
  }

  catch(...)
  {
    Result.erase();

    std::stringstream ExceptionMsg;
    ExceptionMsg << "Extracting string for Qualifier " << Qualifier << " for " << ActID;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                          "CFormattedID::getString",
                                          ExceptionMsg.str().c_str());
  }

  return Result;
}//std::string CFormattedID::getString(const std::string& ID, const std::string& Default, const std::string& Qualifier) const

long CFormattedID::getLong(const std::string& ID, const std::string& Default, const std::string& Qualifier) const
{
  long Result = -1;
  std::string ActID(ID);

  try
  {
    if ( ActID.empty() )
    {
      ActID = Default;
    }

    if (!ActID.empty() && ActID != DEF::Inv_String)
    {
      const CFormattedIDElement* pFormattedIDElement = getFormattedIDElement(Qualifier);

      if (pFormattedIDElement && pFormattedIDElement->isUsed() )
      {
        bool isNumerical = false;

        // use only part of ID given by Format
        if ( (long)ActID.length() >= ( pFormattedIDElement->getPos() + pFormattedIDElement->getLength() ) )
        {
          ActID = ActID.substr(pFormattedIDElement->getPos(),pFormattedIDElement->getLength());
        }

        // extract numerical part
        for ( std::basic_string <char>::size_type i = 0; i < ActID.length();++i)
        {
          std::string Extract = ActID.substr(i,ActID.length());

          std::stringstream Message;
          Message << "Extracting numerical part from " << Extract;
          log(Message.str(),4);

          // try to find numerical part 
          std::istringstream ActData(Extract);
          if ( ActData >> Result )
          {
            isNumerical = true;
            break;
          }
        }

        if(!isNumerical)
        {
          std::stringstream Message;
          Message << "Error extracting data at CFormattedID::getLong() " << ActID << " seems not beeing numeric!";
          log(Message.str(),2);
        }
      }
    } // if (!ActID.empty() && ActID != DEF::Inv_String)
  }
  catch(...)
  {
    Result = -1;
    std::stringstream ExceptionMsg;
    ExceptionMsg << "Extracting string for Qualifier " << Qualifier << " for " << ActID;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                          "CFormattedID::getString",
                                          ExceptionMsg.str().c_str());
  }

  return Result;
}//long CFormattedID::getLong(const std::string& ID, const std::string& Default, const std::string& Qualifier) const

void CFormattedID::log(const std::string & Message, long Level) const
{
  cCBS_StdLog_Task::getInstance()->log(Message,Level);
}


void CFormattedID::trimString(std::string &ActString, const std::string& Sign ) const
{
  ActString = ActString.substr(ActString.find_first_not_of(Sign),ActString.length());
  ActString = ActString.substr(0,ActString.find_first_of(Sign));
}

long CFormattedID::getLength(const std::string& Qualifier) const
{
  long RetValue = 0;

  const CFormattedIDElement* pFormattedIDElement = getFormattedIDElement(Qualifier);

  if (pFormattedIDElement)
  {
    RetValue = pFormattedIDElement->getLength();
  }

  return RetValue;

}//long CFormattedID::getLength(const std::string& Qualifier) const

std::string CFormattedID::getFormat(const std::string& Qualifier) const
{
  std::string RetValue;

  const CFormattedIDElement* pFormattedIDElement = getFormattedIDElement(Qualifier);

  if (pFormattedIDElement)
  {
    RetValue = pFormattedIDElement->getFormat();
  }

  return RetValue;

}//std::string CFormattedID::getFormat(const std::string& Qualifier) const

void CFormattedID::clear()
{
  std::vector<CFormattedIDElement*>::iterator it;

  for ( it = m_FormattedIDElementList.begin() ; it != m_FormattedIDElementList.end() ; it++)
  {
    delete (*it);
  }
  
  m_FormattedIDElementList.clear();

  m_QualifierList.clear();
}//void CFormattedID::clear()

