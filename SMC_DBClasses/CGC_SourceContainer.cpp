// Copyright (C) 2004 SMS Demag AG, Germany 

#include "CSMC_EventLogFrameController.h"


#include "CGC_SourceContainer.h"

//##ModelId=423ED75C00A3
CGC_SourceContainer::~CGC_SourceContainer()
{
  m_L2SourceNameList.clear();
  m_L1SourceNoList.clear();
}

//##ModelId=423ED762030E
CGC_SourceContainer::CGC_SourceContainer(cCBS_StdConnection * Connection, const std::string & Plant, long PlantNo)
{
  if ( Connection )
  {
	  m_pGC_SOURCE = new CGC_SOURCE( Connection );
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
  if ( m_pGC_SOURCE )
  {
    m_L2SourceNameList  = m_pGC_SOURCE->getL2SourceNameList( Plant, PlantNo );
    m_L1SourceNoList    = m_pGC_SOURCE->getL1SourceNoList( Plant, PlantNo );  
    // release the pointer
    delete m_pGC_SOURCE;
    m_pGC_SOURCE = 0;
  }
}

//##ModelId=423ED8F102A4
long CGC_SourceContainer::getSourceL1InfoNoByName(const std::string & SourceName)
{
	// TODO: Add your specialized code here.
  long lSourceL1IntfNo = -1;
  
  std::map<std::string,long>::iterator it;

  it = m_L2SourceNameList.find( SourceName );

  if ( it != m_L2SourceNameList.end() )
  {
  	lSourceL1IntfNo = it->second;
  }

  return lSourceL1IntfNo;
}

//##ModelId=42401FA0006A
std::string CGC_SourceContainer::getL2SourceNameByL1No(long  L1SourceNo)
{
  std::string SourceName;
  
  std::map<long,std::string>::const_iterator it;

  it = m_L1SourceNoList.find( L1SourceNo );

  if ( it != m_L1SourceNoList.end() )
  {
  	SourceName = it->second;
  }
  return SourceName;
}

