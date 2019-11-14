// Copyright (C) 2004 SMS Demag AG

#include "iSMC_DataProvider_s.hh"
#include "CDateTime.h"
#include "CIntfData.h"
#include "CSMC_DBData.h"
#include "CPhaseDataHandler.h"




//##ModelId=471EF9AA0073
CPhaseDataHandler::~CPhaseDataHandler()
{
	// ToDo: Add your specialized code here and/or call the base class
}

//##ModelId=471EF9AA01BE
CPhaseDataHandler::CPhaseDataHandler()
{
	m_PhaseDataSeq.length(0);
}


//##ModelId=4720AC3B0215
sPhaseData CPhaseDataHandler::getPhaseData(const std::string& PhaseName, long PhaseNo, long PhaseStatus)
{
  sPhaseData RetValue;

  for ( long i = 0 ; i < CIntfData::getLength(m_PhaseDataSeq) ; ++i )
  {
    sPhaseData ActPhaseData;

    CIntfData::getAt(ActPhaseData,m_PhaseDataSeq,i);

    if ( (std::string)ActPhaseData.PhaseName == PhaseName && 
         ActPhaseData.PhaseNo     == PhaseNo              &&
         ActPhaseData.PhaseStatus == PhaseStatus )
    {
      RetValue = ActPhaseData;
      break;
    }

  }
    
  return RetValue;
}


//##ModelId=471F3ABA02CE
sPhaseData CPhaseDataHandler::getPhaseData(const std::string& PhaseName, long PhaseNo)
{
  sPhaseData RetValue;

  for ( long i = 0 ; i < CIntfData::getLength(m_PhaseDataSeq) ; ++i )
  {
    sPhaseData ActPhaseData;

    CIntfData::getAt(ActPhaseData,m_PhaseDataSeq,i);

    if ( (std::string)ActPhaseData.PhaseName == PhaseName && 
         ActPhaseData.PhaseNo   == PhaseNo  )
    {
      RetValue = ActPhaseData;
      break;
    }

  }
    
  return RetValue;
}


//##ModelId=471EFC4C01C1
seqPhaseData &  CPhaseDataHandler::getPhaseDataSeq()
{
  return m_PhaseDataSeq;
}

//##ModelId=471EFA5E01C5
seqPhaseDataNames CPhaseDataHandler::getPhaseDataNamesSeq(const std::string& PhaseName, long PhaseNo)
{

  seqPhaseDataNames RetValue;
  RetValue.length(0);

  if ( isPhase(PhaseName, PhaseNo) )
  {
    sPhaseData ActPhaseData = getPhaseData(PhaseName, PhaseNo);
    RetValue = ActPhaseData.DataName;
  }

  return RetValue;
}

//##ModelId=471EFC9D01C5
sPhaseDataNames CPhaseDataHandler::getPhaseDataNames(const std::string& PhaseName, long PhaseNo, const std::string& Name)
{
  sPhaseDataNames RetValue;

  if ( isPhase(PhaseName, PhaseNo) )
  {
    sPhaseData ActPhaseData = getPhaseData(PhaseName, PhaseNo);

    seqPhaseDataNames PhaseDataNamesSeq = ActPhaseData.DataName;

    for ( long i = 0 ; i < CIntfData::getLength(PhaseDataNamesSeq) ; ++i )
    {
      sPhaseDataNames ActPhaseDataNames;

      CIntfData::getAt(ActPhaseDataNames,PhaseDataNamesSeq,i);

      if ( (std::string)ActPhaseDataNames.Name == Name ) 
      {
        RetValue = ActPhaseDataNames;
        break;
      }
    }
  }

  return RetValue;
}

//##ModelId=471EFCCF0370
sPhaseDataNames CPhaseDataHandler::getPhaseDataNames(seqPhaseDataNames PhaseDataNames, const std::string& Name)
{
  sPhaseDataNames RetValue;

  for ( long i = 0 ; i < CIntfData::getLength(PhaseDataNames) ; ++i )
  {
    sPhaseDataNames ActPhaseDataNames;

    CIntfData::getAt(ActPhaseDataNames,PhaseDataNames,i);

    if ( (std::string)ActPhaseDataNames.Name == Name ) 
    {
      RetValue = ActPhaseDataNames;
      break;
    }
  }
    
  return RetValue;
}

//##ModelId=471EFB2001A1
CORBA::Any CPhaseDataHandler::getStartValue(const std::string& PhaseName, long PhaseNo, const std::string& Name)
{
  CORBA::Any RetValue;

  if ( isPhase(PhaseName, PhaseNo) )
  {
    sPhaseData ActPhaseData = getPhaseData(PhaseName, PhaseNo);

    seqPhaseDataNames PhaseDataNamesSeq = ActPhaseData.DataName;

    if ( CPhaseDataHandler::checkLength(PhaseDataNamesSeq) )
    {
      sPhaseDataNames PhaseDataNames = getPhaseDataNames(PhaseDataNamesSeq, Name);

      RetValue = PhaseDataNames.ValueStart;
    }
  }

  return RetValue;
}

//##ModelId=471EFCFD000C
CORBA::Any CPhaseDataHandler::getEndValue(const std::string& PhaseName, long PhaseNo, const std::string& Name)
{
  CORBA::Any RetValue;

  if ( isPhase(PhaseName, PhaseNo) )
  {
    sPhaseData ActPhaseData = getPhaseData(PhaseName, PhaseNo);

    seqPhaseDataNames PhaseDataNamesSeq = ActPhaseData.DataName;

    if ( CPhaseDataHandler::checkLength(PhaseDataNamesSeq) )
    {
      sPhaseDataNames PhaseDataNames = getPhaseDataNames(PhaseDataNamesSeq, Name);

      RetValue = PhaseDataNames.ValueEnd;
    }
  }

  return RetValue;
}

//##ModelId=471EFCFE02A8
CORBA::Any CPhaseDataHandler::getDeltaValue(const std::string& PhaseName, long PhaseNo, const std::string& Name)
{
  CORBA::Any RetValue;

  if ( isPhase(PhaseName, PhaseNo) )
  {
    sPhaseData ActPhaseData = getPhaseData(PhaseName, PhaseNo);

    seqPhaseDataNames PhaseDataNamesSeq = ActPhaseData.DataName;

    if ( CPhaseDataHandler::checkLength(PhaseDataNamesSeq) )
    {
      sPhaseDataNames PhaseDataNames = getPhaseDataNames(PhaseDataNamesSeq, Name);

      RetValue = PhaseDataNames.Delta;
    }
  }

  return RetValue;
}

//##ModelId=471F03AD02CA
void CPhaseDataHandler::setPhaseDataSeq(seqPhaseData value)
{
	m_PhaseDataSeq = value;
}

//##ModelId=471F1FDD0350
void CPhaseDataHandler::setPhaseData(sPhaseData Value)
{
  if ( isPhase(Value) )
  {
    // find position of given phase and replace sPhaseData
    for ( long i = 0 ; i < CIntfData::getLength(m_PhaseDataSeq) ; ++i )
    {
      sPhaseData ActPhaseData;

      CIntfData::getAt(ActPhaseData,m_PhaseDataSeq,i);

      if ( (std::string)ActPhaseData.PhaseName == (std::string)Value.PhaseName && 
           ActPhaseData.PhaseNo   == Value.PhaseNo  )
      {
        CIntfData::setAt(m_PhaseDataSeq,Value,i);
        break;
      }
    }
  }
  else
  {
    CIntfData::insert(m_PhaseDataSeq,Value);
  }
}

//##ModelId=471F03AD037E
void CPhaseDataHandler::setStartValue(const std::string& PhaseName, long PhaseNo, const std::string& Name, CORBA::Any Value)
{
  if ( isPhaseDataName(PhaseName, PhaseNo,  Name) )
  {
    sPhaseData ActPhaseData = getPhaseData(PhaseName, PhaseNo);

    seqPhaseDataNames PhaseDataNamesSeq = ActPhaseData.DataName;

    // find position of given phase and replace sPhaseData
    for ( long i = 0 ; i < CIntfData::getLength(PhaseDataNamesSeq) ; ++i )
    {
      sPhaseDataNames ActPhaseDataNames;

      CIntfData::getAt(ActPhaseDataNames,PhaseDataNamesSeq,i);

      if ( (std::string)ActPhaseDataNames.Name == Name )
      {
        ActPhaseDataNames.ValueStart = Value;
        break;
      }
    }
  }
  else
  {
    if ( isPhase(PhaseName, PhaseNo) )
    {
      sPhaseData ActPhaseData = getPhaseData(PhaseName, PhaseNo);

      seqPhaseDataNames PhaseDataNamesSeq = ActPhaseData.DataName;

      sPhaseDataNames ActPhaseDataNames;
      ActPhaseDataNames.ValueStart = Value;

      CIntfData::insert(PhaseDataNamesSeq,ActPhaseDataNames);
    }
    else
    {
      // JAST existinng phase ion minimum requirement here
      // ERROR !!!
    }
  }
}

//##ModelId=471F03AD0392
void CPhaseDataHandler::setEndValue(const std::string& PhaseName, long PhaseNo, const std::string& Name, CORBA::Any Value)
{
  if ( isPhaseDataName(PhaseName, PhaseNo, Name) )
  {
    sPhaseData ActPhaseData = getPhaseData(PhaseName, PhaseNo);

    seqPhaseDataNames PhaseDataNamesSeq = ActPhaseData.DataName;

    // find position of given phase and replace sPhaseData
    for ( long i = 0 ; i < CIntfData::getLength(PhaseDataNamesSeq) ; ++i )
    {
      sPhaseDataNames ActPhaseDataNames;

      CIntfData::getAt(ActPhaseDataNames,PhaseDataNamesSeq,i);

      if ( (std::string)ActPhaseDataNames.Name == Name )
      {
        ActPhaseDataNames.ValueEnd = Value;
        break;
      }
    }
  }
  else
  {
    if ( isPhase(PhaseName, PhaseNo) )
    {
      sPhaseData ActPhaseData = getPhaseData(PhaseName, PhaseNo);

      seqPhaseDataNames PhaseDataNamesSeq = ActPhaseData.DataName;

      sPhaseDataNames ActPhaseDataNames;
      ActPhaseDataNames.ValueEnd = Value;

      CIntfData::insert(PhaseDataNamesSeq,ActPhaseDataNames);
    }
    else
    {
      // JAST existinng phase ion minimum requirement here
      // ERROR !!!
    }
  }
}

//##ModelId=471F03AD03BA
void CPhaseDataHandler::setDeltaValue(const std::string& PhaseName, long PhaseNo, const std::string& Name, CORBA::Any Value)
{
  if ( isPhaseDataName(PhaseName, PhaseNo, Name) )
  {
    sPhaseData ActPhaseData = getPhaseData(PhaseName, PhaseNo);

    seqPhaseDataNames PhaseDataNamesSeq = ActPhaseData.DataName;

    // find position of given phase and replace sPhaseData
    for ( long i = 0 ; i < CIntfData::getLength(PhaseDataNamesSeq) ; ++i )
    {
      sPhaseDataNames ActPhaseDataNames;

      CIntfData::getAt(ActPhaseDataNames,PhaseDataNamesSeq,i);

      if ( (std::string)ActPhaseDataNames.Name == Name )
      {
        ActPhaseDataNames.Delta = Value;
        break;
      }
    }
  }
  else
  {
    if ( isPhase(PhaseName, PhaseNo) )
    {
      sPhaseData ActPhaseData = getPhaseData(PhaseName, PhaseNo);

      seqPhaseDataNames PhaseDataNamesSeq = ActPhaseData.DataName;

      sPhaseDataNames ActPhaseDataNames;
      ActPhaseDataNames.Delta = Value;

      CIntfData::insert(PhaseDataNamesSeq,ActPhaseDataNames);
    }
    else
    {
      // JAST existinng phase ion minimum requirement here
      // ERROR !!!
    }
  }
}



//##ModelId=471F06FE0266
bool CPhaseDataHandler::checkLength(seqPhaseData& PhaseData)
{
	bool RetValue = false;
  
  if ( CIntfData::getLength(PhaseData) > 0 )
  {
    RetValue = true;
  }

	return RetValue;
}

//##ModelId=471F072E0012
bool CPhaseDataHandler::checkLength(seqPhaseDataNames& PhaseDataNames)
{
	bool RetValue = false;
  
  if ( CIntfData::getLength(PhaseDataNames) > 0 )
  {
    RetValue = true;
  }

	return RetValue;
}


//##ModelId=472076ED025E
bool CPhaseDataHandler::isPhase(const std::string& PhaseName)
{
  bool RetValue = false;

  for ( long i = 0 ; i < CIntfData::getLength(m_PhaseDataSeq) ; ++i )
  {
    sPhaseData ActPhaseData;

    CIntfData::getAt(ActPhaseData,m_PhaseDataSeq,i);

    if ( (std::string)ActPhaseData.PhaseName == PhaseName ) 
    {
      RetValue = true;
      break;
    }

  }
    
  return RetValue;
}

//##ModelId=471F10F902DD
bool CPhaseDataHandler::isPhase(const std::string& PhaseName, long PhaseNo)
{
  bool RetValue = false;

  for ( long i = 0 ; i < CIntfData::getLength(m_PhaseDataSeq) ; ++i )
  {
    sPhaseData ActPhaseData;

    CIntfData::getAt(ActPhaseData,m_PhaseDataSeq,i);

    if ( (std::string)ActPhaseData.PhaseName == PhaseName && 
         ActPhaseData.PhaseNo   == PhaseNo    )
    {
      RetValue = true;
      break;
    }

  }
    
  return RetValue;
}

//##ModelId=471F202C0276
bool CPhaseDataHandler::isPhase(sPhaseData& Phase)
{
  return isPhase((std::string)Phase.PhaseName, Phase.PhaseNo );
}



//##ModelId=471F22C200CD
bool CPhaseDataHandler::isPhaseDataName(const std::string& PhaseName, long PhaseNo, const std::string& Name)
{
  bool RetValue = false;

  if ( isPhase(PhaseName, PhaseNo) )
  {
    sPhaseData ActPhaseData = getPhaseData(PhaseName, PhaseNo);

    seqPhaseDataNames PhaseDataNamesSeq = ActPhaseData.DataName;

    // find position of given phase and replace sPhaseData
    for ( long i = 0 ; i < CIntfData::getLength(PhaseDataNamesSeq) ; ++i )
    {
      sPhaseDataNames ActPhaseDataNames;

      CIntfData::getAt(ActPhaseDataNames,PhaseDataNamesSeq,i);

      if ( (std::string)ActPhaseDataNames.Name == Name )
      {
        RetValue = true;
        break;
      }
    }
  }

  return RetValue;
}

//##ModelId=471F22C70059
bool CPhaseDataHandler::isPhaseDataName(sPhaseData& Phase, const std::string& Name)
{
  return isPhaseDataName((std::string)Phase.PhaseName, Phase.PhaseNo, Name);
}



//##ModelId=471F25EA0258
void CPhaseDataHandler::setStartTime(const std::string& PhaseName, long PhaseNo, sDate& Value)
{
  if ( isPhase(PhaseName, PhaseNo) )
  {
    sPhaseData ActPhaseData = getPhaseData(PhaseName, PhaseNo);
    ActPhaseData.StartTime = Value;
  }
}

//##ModelId=471F25EB0306
void CPhaseDataHandler::setEndTime(const std::string& PhaseName, long PhaseNo, sDate& Value)
{
  if ( isPhase(PhaseName, PhaseNo) )
  {
    sPhaseData ActPhaseData = getPhaseData(PhaseName, PhaseNo);
    ActPhaseData.EndTime = Value;
  }
}

//##ModelId=471F25ED021B
void CPhaseDataHandler::setDuration(const std::string& PhaseName, long PhaseNo, double Value)
{
  if ( isPhase(PhaseName, PhaseNo) )
  {
    sPhaseData ActPhaseData = getPhaseData(PhaseName, PhaseNo);
    ActPhaseData.Duration = Value;
  }
}

//##ModelId=472092D30113
double CPhaseDataHandler::sumDuration( long PhaseStatus )
{
  double RetValue = 0.0;

  for ( long i = 0 ; i < CIntfData::getLength(m_PhaseDataSeq) ; ++i )
  {
    sPhaseData ActPhaseData;
    CIntfData::getAt(ActPhaseData,m_PhaseDataSeq,i);

    if ( ActPhaseData.PhaseStatus == PhaseStatus )
    {
      RetValue += ActPhaseData.Duration;
    }
  }

  return RetValue;
}



//##ModelId=471F475B03E5
double CPhaseDataHandler::getDuration(const std::string& PhaseName, long PhaseNo)
{
  double RetValue = DEF::Inv_Double;

  if ( isPhase(PhaseName, PhaseNo) )
  {
    sPhaseData ActPhaseData = getPhaseData(PhaseName, PhaseNo);
    RetValue = ActPhaseData.Duration;
  }

  return RetValue;
}


//##ModelId=471F477600AC
long CPhaseDataHandler::getStatus(const std::string& PhaseName, long PhaseNo)
{
  long RetValue = DEF::Inv_Long;

  if ( isPhase(PhaseName, PhaseNo) )
  {
    sPhaseData ActPhaseData = getPhaseData(PhaseName, PhaseNo);
    RetValue = ActPhaseData.PhaseStatus;
  }

  return RetValue;
}

//##ModelId=471F472A036F
void CPhaseDataHandler::setStatus(const std::string& PhaseName, long PhaseNo, long Value)
{
  if ( isPhase(PhaseName, PhaseNo) )
  {
    sPhaseData ActPhaseData = getPhaseData(PhaseName, PhaseNo);
    ActPhaseData.PhaseStatus = Value;
  }	
}



//##ModelId=4720523A0385
void CPhaseDataHandler::setStartTime(const std::string& PhaseName, long PhaseNo, CDateTime& Value)
{
  setStartTime(PhaseName, PhaseNo, Value.assDate());
}

//##ModelId=4720524E02D0
void CPhaseDataHandler::setEndTime(const std::string& PhaseName, long PhaseNo, CDateTime& Value)
{
  setEndTime(PhaseName, PhaseNo, Value.assDate());
}

//##ModelId=4720515D017F
void CPhaseDataHandler::newPhase(const std::string& PhaseName, long PhaseNo, long PhaseStatus)
{
  CDateTime Now;

  seqPhaseDataNames PhaseDataNames;
  PhaseDataNames.length(0);

  sPhaseData ActPhaseData;

  ActPhaseData.PhaseName    = PhaseName.c_str();
  ActPhaseData.PhaseNo      = PhaseNo;
  ActPhaseData.PhaseStatus  = PhaseStatus;
  ActPhaseData.StartTime    = Now.assDate();
  ActPhaseData.EndTime      = CSMC_DBData::unspecDate.assDate(); // using CSMC_DBData::unspecDate because 
                                                                  // data will be inserted into database later
  ActPhaseData.Duration     = 0.0;
  ActPhaseData.DataName     = PhaseDataNames;

  newPhase(ActPhaseData);
}

//##ModelId=4720527401F8
void CPhaseDataHandler::newPhase(sPhaseData& Phase)
{
  if ( !isPhase(Phase) )
  {
    CIntfData::insert(m_PhaseDataSeq,Phase);
  }  

}



//##ModelId=4720897802BA
long CPhaseDataHandler::getLastPhaseNo(const std::string& PhaseName)
{
  long RetValue = DEF::Inv_Long;

  for ( long i = 0 ; i < CIntfData::getLength(m_PhaseDataSeq) ; ++i )
  {
    sPhaseData ActPhaseData;

    CIntfData::getAt(ActPhaseData,m_PhaseDataSeq,i);

    if ( (std::string)ActPhaseData.PhaseName == PhaseName )
    {
      RetValue = max(RetValue, ActPhaseData.PhaseNo ) ;
    }
  }
    
  return RetValue;
}




//##ModelId=4720AF640016
CORBA::Any CPhaseDataHandler::getStartValue(sPhaseData& PhaseData, const std::string& Name)
{
  CORBA::Any RetValue;

  seqPhaseDataNames PhaseDataNamesSeq = PhaseData.DataName;

  if ( checkLength(PhaseDataNamesSeq) )
  {
    sPhaseDataNames PhaseDataNames = getPhaseDataNames(PhaseDataNamesSeq, Name);

    RetValue = PhaseDataNames.ValueStart;
  }

  return RetValue;
}

//##ModelId=4720AF68027F
CORBA::Any CPhaseDataHandler::getEndValue(sPhaseData& PhaseData, const std::string& Name)
{
  CORBA::Any RetValue;

  seqPhaseDataNames PhaseDataNamesSeq = PhaseData.DataName;

  if ( checkLength(PhaseDataNamesSeq) )
  {
    sPhaseDataNames PhaseDataNames = getPhaseDataNames(PhaseDataNamesSeq, Name);

    RetValue = PhaseDataNames.ValueEnd;
  }

  return RetValue;
}

//##ModelId=4720AF6D0150
CORBA::Any CPhaseDataHandler::getDeltaValue(sPhaseData& PhaseData, const std::string& Name)
{
  CORBA::Any RetValue;

  seqPhaseDataNames PhaseDataNamesSeq = PhaseData.DataName;

  if ( checkLength(PhaseDataNamesSeq) )
  {
    sPhaseDataNames PhaseDataNames = getPhaseDataNames(PhaseDataNamesSeq, Name);

    RetValue = PhaseDataNames.Delta;
  }

  return RetValue;
}

