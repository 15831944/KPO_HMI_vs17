// Copyright (C) 2004 SMS Demag AG, Germany 

#include "CSMC_EventLogFrameController.h"
#include "CGC_CHARGE_DEST.h"
#include "CGC_Charge_Dest_Container.h"


//##ModelId=42413EC40201
CGC_Charge_Dest_Container::CGC_Charge_Dest_Container(cCBS_StdConnection * Connection, const std::string & Plant)
{
  if ( Connection )
  {
	  m_pCGC_CHARGE_DEST = new CGC_CHARGE_DEST( Connection );
  }
  else
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DatabaseConnectionError(sMessage,
                        "Can not instantiate DB class in case of NULL pointer to connection",
                        "Terminating program!");
    exit(EXIT_FAILURE);
  }

  if ( m_pCGC_CHARGE_DEST )
  {
    m_DestNameList   = m_pCGC_CHARGE_DEST->getDestNameListByPlant( Plant );
   
    // now m_pCGC_CHARGE_DEST is useless, just release the pointer
    delete m_pCGC_CHARGE_DEST;
    m_pCGC_CHARGE_DEST = 0;
  }
}

//##ModelId=42413EC5025D
CGC_Charge_Dest_Container::~CGC_Charge_Dest_Container()
{
	// ToDo: Add your specialized code here and/or call the base class
  m_DestNameList.clear();
}


//##ModelId=42413F1D0096
std::string CGC_Charge_Dest_Container::getDestNameByNo(const long & DestNo)
{
  std::map< long , std::string >::const_iterator it;
  std::string DestName = "";

  it = m_DestNameList.find( DestNo );
  if ( it != m_DestNameList.end() )
  {
    DestName = it->second;  
  }
  return DestName;
}
