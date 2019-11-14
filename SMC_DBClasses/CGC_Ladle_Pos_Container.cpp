// Copyright (C) 2004 SMS Demag AG, Germany 

#include "CSMC_EventLogFrameController.h"

#include "DEF_GC_LADLE_POS.h"
#include "CGC_LADLE_POS.h"
#include "CGC_Ladle_Pos_Container.h"



CGC_Ladle_Pos_Container::CGC_Ladle_Pos_Container(cCBS_StdConnection * Connection)
{
  if ( !Connection )
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DatabaseConnectionError(sMessage,
                        "Can not instantiate DB class in case of NULL pointer to connection",
                        "Terminating program!");
    exit(EXIT_FAILURE);
  }

  CGC_LADLE_POS GC_LADLE_POS( Connection );

  if ( GC_LADLE_POS.select(CSMC_DBData::unspecLong) )
  {
    LadlePosData LPD;

    for ( long i = 1 ; i <= GC_LADLE_POS.getLastRow(); ++i )
    {
      LPD.LadlePosId      = GC_LADLE_POS.getLADLEPOSID(i);
      LPD.LadlePos        = GC_LADLE_POS.getLADLEPOS(i);
      LPD.LadlePosDesc    = GC_LADLE_POS.getLADLEPOSDESCR(i);
      LPD.LadleType       = GC_LADLE_POS.getLADLETYPE(i);

      m_LadlePosDataList.insert( std::pair< std::string, LadlePosData > ( LPD.LadlePos, LPD ) );
    }  
  }
}

CGC_Ladle_Pos_Container::~CGC_Ladle_Pos_Container()
{
	// ToDo: Add your specialized code here and/or call the base class
  m_LadlePosDataList.clear();
}

long CGC_Ladle_Pos_Container::getLadlePosIdDefault(const std::string& LadleType)
{
  long LadlePosId = CSMC_DBData::unspecLong;

  std::map<std::string, LadlePosData>::iterator it;

  for ( it = m_LadlePosDataList.begin(); it !=  m_LadlePosDataList.end(); ++it )
  {
    if ( (string)DEF_GC_LADLE_POS::UNDEF  == it->first && 
         LadleType                == it->second.LadleType )
    {
      LadlePosId = it->second.LadlePosId;
      break;
    }
  }

  return LadlePosId;
}



long CGC_Ladle_Pos_Container::getLadlePosId(const std::string& LadlePos, const std::string& LadleType)
{
  long LadlePosId = getLadlePosIdDefault(LadleType);

  std::map<std::string, LadlePosData>::iterator it;

  for ( it = m_LadlePosDataList.begin(); it !=  m_LadlePosDataList.end(); ++it )
  {
    if ( LadlePos   == it->first && 
         LadleType  == it->second.LadleType )
    {
      LadlePosId = it->second.LadlePosId;
      break;
    }
  }

  return LadlePosId;
}
