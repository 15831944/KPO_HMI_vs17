// Copyright (C) 2004, 2005 SMS Demag AG, Germany 

#include <sstream>

#include "CGC_PLANT.h"
#include "CSMC_EventLogFrameController.h"
#include "cCBS_StdLog_Task.h"

#include "CGC_Plant_Container.h"



//##ModelId=43C65EA702A3
std::string CGC_Plant_Container::getL2PlantID(std::string& L3PlantId)
{
  std::map<const std::string, stPlantDef>::iterator ii;

  for( ii=m_PlantMapList.begin(); ii!=m_PlantMapList.end(); ii++ )
  {
    if ((ii->second).PlantId_l3 == L3PlantId)
      return ii->first;
  }

  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ErrorPlantDataConversion(sMessage,L3PlantId.c_str());

  return m_Empty; 
}

//##ModelId=43C65F060014
std::string CGC_Plant_Container::getL2PlantID(long L1PlantId)
{
  std::map<const std::string, stPlantDef>::iterator ii;

  for( ii=m_PlantMapList.begin(); ii!=m_PlantMapList.end(); ii++ )
  {
    if ( ((ii->second).PlantId_L1 == L1PlantId  )
      && ((ii->second).Plant  == m_Plant))
      return ii->first;
  }

  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ErrorPlantDataConversion(sMessage,L1PlantId);

  return m_Empty; 
}

//##ModelId=43C6611F002A
std::string CGC_Plant_Container::getL2PlantID(std::string& Plant, long PlantNo)
{
  std::map<const std::string, stPlantDef>::iterator ii;

  for( ii=m_PlantMapList.begin(); ii!=m_PlantMapList.end(); ii++ )
  {
    if ( ((ii->second).PlantNo == PlantNo  )
      && ((ii->second).Plant   == Plant))
      return ii->first;
  }

  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ErrorPlantDataConversion(sMessage,Plant.c_str(),PlantNo);

  return m_Empty; 
}

//##ModelId=43C661C3003A
std::string CGC_Plant_Container::getPlant(std::string L2PlantId)
{
  std::map<const std::string, stPlantDef>::iterator ii;

  if ((ii = m_PlantMapList.find(L2PlantId)) != m_PlantMapList.end())
    return (ii->second).Plant;

  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ErrorPlantDataConversion(sMessage,L2PlantId.c_str());

  return m_Empty; 
}

//##ModelId=43C661E10282
long CGC_Plant_Container::getPlantNo(std::string L2PlantId)
{
  std::map<const std::string, stPlantDef>::iterator ii;

  if ((ii = m_PlantMapList.find(L2PlantId)) != m_PlantMapList.end())
    return (ii->second).PlantNo;

  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ErrorPlantDataConversion(sMessage,L2PlantId.c_str());

	return (long)0;
}

//##ModelId=43C6621D0293
long CGC_Plant_Container::getL1PlantID(std::string L2PlantId)
{
  std::map<const std::string, stPlantDef>::iterator ii;

  if ((ii = m_PlantMapList.find(L2PlantId)) != m_PlantMapList.end())
    return (ii->second).PlantId_L1;

  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ErrorPlantDataConversion(sMessage,L2PlantId.c_str());

	return (long)0;
}

//##ModelId=43C662450023
std::string CGC_Plant_Container::getL3PlantID(std::string L2PlantId)
{
  std::map<const std::string, stPlantDef>::iterator ii;

  if ((ii = m_PlantMapList.find(L2PlantId)) != m_PlantMapList.end())
    return (ii->second).PlantId_l3;

  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ErrorPlantDataConversion(sMessage,L2PlantId.c_str());

  return m_Empty; 
}

//##ModelId=43C663440215
CGC_Plant_Container::CGC_Plant_Container(cCBS_StdConnection *Connection)
{
  m_Empty.clear();
  m_Plant.clear();
  init(Connection);
}

//##ModelId=43C666240321
CGC_Plant_Container::CGC_Plant_Container(cCBS_StdConnection *Connection, std::string Plant)
{
  m_Empty.clear();
  m_Plant = Plant;
  init(Connection);
}

//##ModelId=43C663870276
CGC_Plant_Container::~CGC_Plant_Container()
{
  m_PlantMapList.clear();
}

//##ModelId=43C6774C016E
void CGC_Plant_Container::setPlant(const std::string& value)
{
	m_Plant = value;
}

//##ModelId=43C7C97202DC
bool CGC_Plant_Container::init(cCBS_StdConnection* Connection)
{
  bool ret = true;

  try
  {
    if (Connection)
      m_pGC_PLANT = new CGC_PLANT(Connection);
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DatabaseConnectionError(sMessage,
                          "Can not instantiate DB class in case of NULL pointer to connection",
                          "Terminating program!");
      exit(EXIT_FAILURE);
    }
    if (m_pGC_PLANT)
    {
      std::string L2PlId;
      stPlantDef UnitDesc;

      m_pGC_PLANT->select(CSMC_DBData::unspecString,CSMC_DBData::unspecLong);
      long lRowsGot = m_pGC_PLANT->getLastRow();
      for (long i = 1; i <= lRowsGot; i++)
      {
        L2PlId = m_pGC_PLANT->getPLANTID_L2(i);
        UnitDesc.Plant      = m_pGC_PLANT->getPLANT(i);
        UnitDesc.PlantNo    = m_pGC_PLANT->getPLANTNO(i);
        UnitDesc.PlantId_L1 = m_pGC_PLANT->getPLANTID_L1(i);
        UnitDesc.PlantId_l3 = m_pGC_PLANT->getPLANTID_L3(i);
        UnitDesc.RouteCode  = m_pGC_PLANT->getROUTECODEID(i);
        UnitDesc.PlantId_CCS= m_pGC_PLANT->getPLANTID_CCS(i);

        m_PlantMapList.insert(std::pair <std::string,stPlantDef>(L2PlId, UnitDesc));
      }
      delete m_pGC_PLANT;
      m_pGC_PLANT = 0;
    }
  }
  catch(...)
  {
    ret = false;
  }
  return ret;
}

//##ModelId=43E885F70221
std::string CGC_Plant_Container::getRouteCodeID(std::string L2PlantId)
{
  std::map<const std::string, stPlantDef>::iterator ii;

  if ((ii = m_PlantMapList.find(L2PlantId)) != m_PlantMapList.end())
    return (ii->second).RouteCode;

  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ErrorPlantDataConversion(sMessage,L2PlantId.c_str());

  return m_Empty; 
}

std::string CGC_Plant_Container::getRouteCodeID(std::string& Plant, long PlantNo)
{
  std::map<const std::string, stPlantDef>::iterator ii;

  for( ii=m_PlantMapList.begin(); ii!=m_PlantMapList.end(); ii++ )
  {
    if ((ii->second).Plant    == Plant && 
        (ii->second).PlantNo  == PlantNo )
    {
      return (ii->second).RouteCode;
    }
  }

  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ErrorPlantDataConversion(sMessage,Plant.c_str(),PlantNo);

  return m_Empty; 
}



//##ModelId=448974180080
std::string CGC_Plant_Container::getL2PlantIDFromCCS(std::string& CCSPlantId)
{
  std::map<const std::string, stPlantDef>::iterator ii;

  for( ii=m_PlantMapList.begin(); ii!=m_PlantMapList.end(); ii++ )
  {
    if ((ii->second).PlantId_CCS == CCSPlantId)
      return ii->first;
  }

  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ErrorPlantDataConversion(sMessage,CCSPlantId.c_str());

  return m_Empty; 
}



std::string CGC_Plant_Container::getCCSPlantID(std::string L2PlantId)
{
  std::map<const std::string, stPlantDef>::iterator ii;

  if ((ii = m_PlantMapList.find(L2PlantId)) != m_PlantMapList.end())
    return (ii->second).PlantId_CCS;

  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ErrorPlantDataConversion(sMessage,L2PlantId.c_str());

  return m_Empty; 
}

std::string CGC_Plant_Container::getL2RouteCodeID(std::string L3PlantId)
{
  std::map<const std::string, stPlantDef>::iterator ii;

  for( ii=m_PlantMapList.begin(); ii!=m_PlantMapList.end(); ii++ )
  {
    if((ii->second).PlantId_l3 == L3PlantId)
    {
      return (ii->second).RouteCode;
    }
  }

  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ErrorPlantDataConversion(sMessage,L3PlantId.c_str());

  return m_Empty; 
}

bool CGC_Plant_Container::isRouteCode(const std::string &RouteCode)
{
  std::map<const std::string, stPlantDef>::iterator ii;

  for( ii=m_PlantMapList.begin(); ii!=m_PlantMapList.end(); ii++ )
  {
    if((ii->second).RouteCode == RouteCode)
    {
      return true;
    }
  }

  return false;
}

sPlantRoute CGC_Plant_Container::getSinglePlantRoute(const std::string &RouteCode)
{
  sPlantRoute PlantRoute;

  std::map<const std::string, stPlantDef>::iterator ii;

  for( ii=m_PlantMapList.begin(); ii!=m_PlantMapList.end(); ii++ )
  {
    if((ii->second).RouteCode == RouteCode)
    {
      PlantRoute.Plant   = (ii->second).Plant;
      PlantRoute.PlantNo = (ii->second).PlantNo;
      break;
    }
  }

  return PlantRoute;
}


std::vector<sPlantRoute> CGC_Plant_Container::getPlantRoute(const std::string &RouteCode)
{
  std::vector<sPlantRoute> PlantRoute;

  // determine all ROUTECODEIDs in RouteCode

  std::string RemainingRouteCode = RouteCode;

  for ( long Pos = 0; Pos < long(RemainingRouteCode.length()); ++Pos) 
  {
    for ( long Width = 1; Width <= 6-Pos ; ++Width )  // Max lenght of 6 given by database, 
                                                      // we need only consider up to width-pos characters, 
                                                      // not try to look beyond end of RouteCode
    {
      std::string ActRouteCode = RemainingRouteCode.substr(Pos,Width);

      if ( isRouteCode(ActRouteCode) )
      {
        sPlantRoute ActPlantRoute = getSinglePlantRoute(ActRouteCode);

        PlantRoute.push_back(ActPlantRoute);

        Pos = Pos + Width;   // to continue scan, shift right by width of this act route code

        break;
      }
    }
  }

  return PlantRoute;
}