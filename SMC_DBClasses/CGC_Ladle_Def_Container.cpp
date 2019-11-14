// Copyright (C) 2004 SMS Demag AG, Germany 

#include "CSMC_EventLogFrameController.h"
#include "CGC_LADLE_DEF.h"
#include "CGC_Ladle_Def_Container.h"


CGC_Ladle_Def_Container::CGC_Ladle_Def_Container(cCBS_StdConnection * Connection)
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

  CGC_LADLE_DEF GC_LADLE_DEF( Connection );

  if ( GC_LADLE_DEF.select(CSMC_DBData::unspecLong, CSMC_DBData::unspecString))
  {
    for ( long i = 1 ; i <= GC_LADLE_DEF.getLastRow(); ++i )
    {
      long LadleNo          = GC_LADLE_DEF.getLADLENO(i);
      std::string LadleType = GC_LADLE_DEF.getLADLETYPE(i);

      m_LadleDefList.insert( std::pair< long, std::string > ( LadleNo, LadleType ) );
    }  
  }
}

CGC_Ladle_Def_Container::~CGC_Ladle_Def_Container()
{
	// ToDo: Add your specialized code here and/or call the base class
  m_LadleDefList.clear();
}


bool CGC_Ladle_Def_Container::isValidLadle(long LadleNo, const std::string& LadleType)
{
  bool RetValue = false;

  std::multimap< long, std::string >::iterator it;

  for ( it = m_LadleDefList.begin(); it !=  m_LadleDefList.end(); ++it )
  {
    if ( LadleNo == it->first && LadleType == it->second )
    {
      RetValue = true;
      break;
    }
  }

  return RetValue;
}
