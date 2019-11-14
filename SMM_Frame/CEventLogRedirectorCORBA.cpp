// Copyright (C) 1999 - 2000 SMS Demag AG

#include <iomanip>
#include <sstream>

#include "CModel.h"
#include "CProcCtrl.h"
#include "CRetInfo.h"
#include "CParamMgr.h"
#include "cCBS_Time.h"
#include "CSMC_EventLogFrameController.h"
#include "cCBS_StdInitBase.h"
#include "CDataConversion.h"
#include "CSMC_Mutex.h"

#include "CEventLogRedirectorCORBA.h"


//##ModelId=45F924030152
CEventLogRedirectorCORBA::CEventLogRedirectorCORBA(CSMM_ModelTask * pModelTask)
: m_pEventLog(0)
, m_pModelTask(pModelTask)
{
  m_pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
}

//##ModelId=45F924030153
CEventLogRedirectorCORBA::~CEventLogRedirectorCORBA()
{
}

void CEventLogRedirectorCORBA::handleMessage(int id, int severity, const std::string& m1, const std::string& m2, const std::string& m3, const std::string& file, long line, const std::string& out, const std::string& OutPutSpec, const std::string& FreeText, long Destination)
{
  handleMessage(id, severity, m1, m2, m3, file, line, out, OutPutSpec, FreeText, Destination, 0);
}

//##ModelId=45F924030155
void CEventLogRedirectorCORBA::handleMessage(int id, int severity, const std::string& m1, const std::string& m2, const std::string& m3, const std::string& file, long line, const std::string& out, const std::string& OutPutSpec, const std::string& FreeText, long Destination, int opAckn)
{
  CSMC_Mutex SMC_Mutex("HandleMessageMutex");

  // prepare heat id and consumptions for logging
  std::string Msg; 
  std::string MsgData; 
  std::string ExternalHeatId, AllCons,ExternalTreatNo;
  std::string InternalProductID ;
 	std::map<std::string, double> MainCons;
  std::string useLanguage = "M1";
  std::string CodeInfo;
  std::string PlantUnit, Aggregate, Location;
  long Severity = severity; // Data type conversion
  std::string Spare3;

  sEventLogMessage EventLogMessage;

  std::string actualMessage = m1; // Default in case we have no model pointer and consequently no parameter

  std::stringstream TmpCodeInfo;
  TmpCodeInfo << "File : " << file << " Line : " << line;

  CodeInfo = TmpCodeInfo.str();

  // get the pointer of the running model
  CModel* pModel = CProcCtrl::Instance()->getpModel();

  if (pModel && m_pModelTask)
  {
    // We use the second argument to suppress the EventLog EL_ParamNotFound. The
    // case that the parameter is not found results in recursive calls
    useLanguage = pModel->getpParamMgr()->getString("LanguageBuffer", true);

    if (useLanguage == "M2")
      actualMessage = m2;

    // get the ExternalHeatId and ExternalTreatNo from Task !
    ExternalHeatId    = m_pModelTask->getActHeatIDCust();
    ExternalTreatNo   = m_pModelTask->getActTreatIDCust();
    InternalProductID = pModel->getHeatId() + "_" + pModel->getTreatNo();

    // get all actual consumptions for this heat from map MainCons
  	MainCons = pModel->getMainCons();

    // reset string
    AllCons.erase(); 

    // construct string with all consumptions
    std::map<std::string, double>::const_iterator pit; 
    for (pit = MainCons.begin(); pit != MainCons.end(); ++pit)
    {
      std::stringstream Cons;
      Cons << pit->first + ": " << CDataConversion::SetInvalidToDefault(CDataConversion::RoundToLong(pit->second), 0) << "  ";
        
      AllCons += Cons.str();
    }

    std::stringstream tmp;
  
    if (!ExternalHeatId.empty())
    {
      tmp << ExternalHeatId << "_" << ExternalTreatNo << " ";
    }

    if ( !AllCons.empty())
    {
      tmp << AllCons.c_str() << " ";
    }
    
    tmp << actualMessage;
    Msg = tmp.str();

    // result buffer
    CRetInfo* pRetInfo ;

    if ( E_TEST != Severity )
    {
      // write the message to model result buffer
      pRetInfo = pModel->getpRetInfo();

      if (pRetInfo) 
      {
        pRetInfo->setMsg(Msg); 
      }
    }

    // write the message (m3) to model result buffer
    Msg = tmp.str();
    
    tmp.str("");
    tmp << m3;
    MsgData = tmp.str();

    if ( E_TEST != Severity)
    {
      pRetInfo = pModel->getpRetInfoData();

      if (pRetInfo) 
      {
        pRetInfo->setMsg(MsgData); 
      }
    }
  }
  else
  {
    Msg = actualMessage;
  }

  CCfg *pCfg = CProcCtrl::Instance()->getpCfg();
  if (pCfg)
  {
    PlantUnit       = pCfg->getModelSpec();
    Aggregate       = pCfg->getPlantSpec();
  }

  Location = cCBS_StdInitBase::getInstance()->m_ServerName;

  long ActOpAckn = opAckn;

  // look for general settings to change eventlog data
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EVENTLOG_SMM","Location",Location);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EVENTLOG_SMM","Severity",Severity);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EVENTLOG_SMM","Destination",Destination);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EVENTLOG_SMM","OpAckn",ActOpAckn);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EVENTLOG_SMM","Spare3",Spare3);

  // look for severity related settings to change eventlog data
  std::vector<std::string> SeverityList;

  if ( m_pEventLog && cCBS_StdInitBase::getInstance()->getEntryList("EVENTLOG_SMM","SeverityList",SeverityList) )
  {
    std::vector<std::string>::iterator itSeverity;

    for ( itSeverity = SeverityList.begin(); itSeverity != SeverityList.end(); ++itSeverity)
    {
      std::string BlockName = (*itSeverity);

      if ( BlockName == CDataConversion::IntToString(Severity) ) 
      {
        cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"Severity",Severity);
        cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"Destination",Destination);
        cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"Spare3",Spare3);
      }
    }
  }

  // look for Destination related settings to change eventlog data
  std::vector<std::string> DestinationList;

  if ( m_pEventLog && cCBS_StdInitBase::getInstance()->getEntryList("EVENTLOG_SMM","DestinationList",DestinationList) )
  {
    std::vector<std::string>::iterator itDestination;

    for ( itDestination = DestinationList.begin(); itDestination != DestinationList.end(); ++itDestination)
    {
      std::string BlockName = (*itDestination);

      if ( BlockName == CDataConversion::IntToString(Destination) ) 
      {
        cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"Severity",Severity);
        cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"Destination",Destination);
        cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"Spare3",Spare3);
      }
    }
  }

  // look for id related settings to change eventlog data
  std::vector<std::string> EventIdList;

  if ( m_pEventLog && cCBS_StdInitBase::getInstance()->getEntryList("EVENTLOG_SMM","EventIdList",EventIdList) )
  {
    std::vector<std::string>::iterator itEventId;

    for ( itEventId = EventIdList.begin(); itEventId != EventIdList.end(); ++itEventId)
    {
      std::string BlockName = (*itEventId);

      if ( BlockName == CDataConversion::IntToString(id) ) 
      {
        cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"Location",Location);
        cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"Severity",Severity);
        cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"Destination",Destination);
        cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"OpAckn",ActOpAckn);
        cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"Spare3",Spare3);
      }
    }
  }

  // now fill EventLog Message
  EventLogMessage = cCBS_StdEventLog::initMessage(file,line,Destination);

  switch (Severity)
  {
    case E_INFO:
      {
        EventLogMessage.severity        = c_e_info;
        break;
      }
    case E_WARNING:
      {
        EventLogMessage.severity        = c_e_warning;
        break;
      }
    case E_ERROR:
      {
        EventLogMessage.severity        = c_e_error;
        break;
      }
    case E_TEST:
      {
        EventLogMessage.severity        = c_e_test;
        break;
      }

    case E_FATAL_ERROR:
      {
        EventLogMessage.severity        = c_e_fatal;
        break;
      }
    default : 
      {
        EventLogMessage.severity        = c_e_test;
        break;
      }
  }

  if ( useLanguage == "M1" )
    EventLogMessage.language        = 1;
  else
    EventLogMessage.language        = 2;

  cCBS_Time::localTime(EventLogMessage.applDateTime);

  EventLogMessage.productId       = ExternalHeatId;
  EventLogMessage.processState    = AllCons;
  EventLogMessage.eventId         = id  ;
  //CBS iterface changed since package 4.0 EventLogMessage.eventIdAlter    = id  ;
  EventLogMessage.messageText     = m1;
  EventLogMessage.messageText2    = m2;
  EventLogMessage.trigger         = true;
  EventLogMessage.originLocation  = Location;
  EventLogMessage.plantUnit       = PlantUnit;
  EventLogMessage.aggregate       = Aggregate;
  EventLogMessage.spare1          = CodeInfo;
  EventLogMessage.spare2          = InternalProductID;
  EventLogMessage.spare3          = Spare3;
  EventLogMessage.opAckn          = ActOpAckn;

  // workaround !!!!
  // HMI needs configuration to read EventLogMessage from messagetext2 
  // for second language but is reading from unimessage
  EventLogMessage.uniMessage      = CDataConversion::StringToWstring(m2);
  
  m_pEventLog->sendMessage(EventLogMessage);

  TRACING(CTL::GEN_OUT, "EventLog", Msg + " " + CodeInfo );
}

void CEventLogRedirectorCORBA::handleMessage(int id, int severity, const std::string& m1, const std::wstring& m2, const std::string& m3, const std::string& file, long line, const std::string& out, const std::string& OutPutSpec, const std::string& FreeText, long Destination)
{
  handleMessage(id, severity, m1, m2, m3, file, line, out, OutPutSpec, FreeText, Destination, 0);
}

void CEventLogRedirectorCORBA::handleMessage(int id, int severity, const std::string& m1, const std::wstring& m2, const std::string& m3, const std::string& file, long line, const std::string& out, const std::string& OutPutSpec, const std::string& FreeText, long Destination, int opAckn)
{
  // prepare heat id and consumptions for logging
  std::string Msg; 
  std::string MsgData; 
  std::string ExternalHeatId, AllCons, ExternalTreatNo;
  std::string InternalProductID ;
 	std::map<std::string, double> MainCons;
  std::string useLanguage = "M1";
  std::string PlantUnit, Location;
  std::stringstream PlantNo;
  std::stringstream CodeInfo;
  long Severity = severity; // Data type conversion
  std::string Spare3;

  sEventLogMessage EventLogMessage;

  CodeInfo << "File : " << file << " Line : " << line;

  // get the pointer of the running model
  CModel* pModel = CProcCtrl::Instance()->getpModel();

  if (pModel && m_pModelTask)
  {
    // We use the second argument to suppress the EventLog EL_ParamNotFound. The
    // case that the parameter is not found results in recursive calls
    useLanguage = pModel->getpParamMgr()->getString("LanguageBuffer", true);

    // get the ExternalHeatId and ExternalTreatNo from Task !
    ExternalHeatId    = m_pModelTask->getActHeatIDCust();
    ExternalTreatNo   = m_pModelTask->getActTreatIDCust();
    InternalProductID = m_pModelTask->getActProductID();
    PlantUnit         = m_pModelTask->getActPlant();
    PlantNo          << m_pModelTask->getActPlantNo();

    // get all actual consumptions for this heat from map MainCons
  	MainCons = pModel->getMainCons();

    // reset string
    AllCons.erase(); 

    // construct string with all consumptions
    std::map<std::string, double>::const_iterator pit; 
    for (pit = MainCons.begin(); pit != MainCons.end(); ++pit)
    {
      std::stringstream Cons;
      Cons << pit->first + ": " << CDataConversion::SetInvalidToDefault(CDataConversion::RoundToLong(pit->second), 0) << "  ";
        
      AllCons += Cons.str();
    }

    std::stringstream tmp;
  
    if (!ExternalHeatId.empty())
    {
      tmp << ExternalHeatId << "_" << ExternalTreatNo << " ";
    }

    if ( !AllCons.empty())
    {
      tmp << AllCons.c_str() << " ";
    }

    tmp << m1;
    Msg = tmp.str();

    // result buffer
    CRetInfo* pRetInfo = 0;

    if ( E_TEST != Severity )
    {
      // write the message to model result buffer
      pRetInfo = pModel->getpRetInfo();

      if (pRetInfo) 
      {
        pRetInfo->setMsg(Msg); 
      }
    }

    // write the message (m3) to model result buffer
    Msg = tmp.str();
    
    tmp.str("");
    tmp << m3;
    MsgData = tmp.str();

    if ( E_TEST != Severity)
    {
      pRetInfo = pModel->getpRetInfoData();

      if (pRetInfo) 
      {
        pRetInfo->setMsg(MsgData); 
      }
    }
  }
  else
  {
    Msg = m1;
  }

  Location = cCBS_StdInitBase::getInstance()->m_ServerName;

  long ActOpAckn = opAckn;

  // look for general settings to change eventlog data
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EVENTLOG_SMM","Location",Location);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EVENTLOG_SMM","Severity",Severity);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EVENTLOG_SMM","Destination",Destination);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EVENTLOG_SMM","OpAckn",ActOpAckn);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EVENTLOG_SMM","Spare3",Spare3);

  // look for severity related settings to change eventlog data
  std::vector<std::string> SeverityList;

  if ( m_pEventLog && cCBS_StdInitBase::getInstance()->getEntryList("EVENTLOG_SMM","SeverityList",SeverityList) )
  {
    std::vector<std::string>::iterator itSeverity;

    for ( itSeverity = SeverityList.begin(); itSeverity != SeverityList.end(); ++itSeverity)
    {
      std::string BlockName = (*itSeverity);

      if ( BlockName == CDataConversion::IntToString(Severity) ) 
      {
        cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"Severity",Severity);
        cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"Destination",Destination);
        cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"Spare3",Spare3);
      }
    }
  }

  // look for Destination related settings to change eventlog data
  std::vector<std::string> DestinationList;

  if ( m_pEventLog && cCBS_StdInitBase::getInstance()->getEntryList("EVENTLOG_SMM","DestinationList",DestinationList) )
  {
    std::vector<std::string>::iterator itDestination;

    for ( itDestination = DestinationList.begin(); itDestination != DestinationList.end(); ++itDestination)
    {
      std::string BlockName = (*itDestination);

      if ( BlockName == CDataConversion::IntToString(Destination) ) 
      {
        cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"Severity",Severity);
        cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"Destination",Destination);
        cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"Spare3",Spare3);
      }
    }
  }


  // look for id related settings to change eventlog data
  std::vector<std::string> EventIdList;

  if ( m_pEventLog && cCBS_StdInitBase::getInstance()->getEntryList("EVENTLOG_SMM","EventIdList",EventIdList) )
  {
    std::vector<std::string>::iterator itEventId;

    for ( itEventId = EventIdList.begin(); itEventId != EventIdList.end(); ++itEventId)
    {
      std::string BlockName = (*itEventId);

      if ( BlockName == CDataConversion::IntToString(id) ) 
      {
        cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"Location",Location);
        cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"Severity",Severity);
        cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"Destination",Destination);
        cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"OpAckn",ActOpAckn);
        cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"Spare3",Spare3);
      }
    }
  }

  // now fill EventLog Message
  EventLogMessage = cCBS_StdEventLog::initMessage(file,line,Destination);

  switch (Severity)
  {
    case E_INFO:
      {
        EventLogMessage.severity = c_e_info;
        break;
      }
    case E_WARNING:
      {
        EventLogMessage.severity = c_e_warning;
        break;
      }
    case E_ERROR:
      {
        EventLogMessage.severity = c_e_error;
        break;
      }
    case E_TEST:
      {
        EventLogMessage.severity = c_e_test;
        break;
      }

    default : 
      {
        EventLogMessage.severity = c_e_test;
        break;
      }
  }

  if ( useLanguage == "M1" )
  {
    EventLogMessage.messageText2 = m1;
    EventLogMessage.language = 1;
  }
  else
  {
    EventLogMessage.language = 2;
  }

  cCBS_Time::localTime(EventLogMessage.applDateTime);

  EventLogMessage.productId       = ExternalHeatId;
  EventLogMessage.processState    = AllCons;
  EventLogMessage.eventId         = id  ;
  //CBS iterface changed since package 4.0 
  //EventLogMessage.eventIdAlter    = id  ;
  EventLogMessage.messageText     = m1;
  EventLogMessage.trigger         = true;
  EventLogMessage.originLocation  = Location;
  EventLogMessage.plantUnit       = PlantUnit;
  EventLogMessage.aggregate       = PlantNo.str();
  EventLogMessage.spare1          = CodeInfo.str();
  EventLogMessage.spare2          = InternalProductID;
  EventLogMessage.spare3          = Spare3;
  EventLogMessage.opAckn          = ActOpAckn;
  EventLogMessage.uniMessage      = m2;

  m_pEventLog->sendMessage(EventLogMessage);
  TRACING(CTL::GEN_OUT, "EventLog", Msg + " " + CodeInfo.str());
}
