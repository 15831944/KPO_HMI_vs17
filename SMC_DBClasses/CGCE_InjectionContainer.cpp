#include "CGCE_InjectionContainer.h"
#include "CSMC_EventLogFrameController.h"

CGCE_InjectionContainer::CGCE_InjectionContainer(cCBS_StdConnection * Connection,const std::string & PLANT,long PlantNo)
{
  if ( Connection )
  {
    m_pCGCE_INJECTION = new CGCE_INJECTION( Connection );
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

  if (m_pCGCE_INJECTION)
  {
    m_DevicenameNameList  = m_pCGCE_INJECTION->getDeviceNameList(PLANT, PlantNo , CSMC_DBData::unspecString);
    m_L1DevicenoList      = m_pCGCE_INJECTION->getL1DeviceNoList(PLANT, PlantNo , CSMC_DBData::unspecString);
    m_InjTypeList         = m_pCGCE_INJECTION->getInjTypeList(PLANT, PlantNo);
    // release the pointer
    delete m_pCGCE_INJECTION;
    m_pCGCE_INJECTION = 0;
  }
}

CGCE_InjectionContainer::~CGCE_InjectionContainer(void)
{
}

long CGCE_InjectionContainer::getL1DeviceNoByDeviceName(const std::string& DEVICENAME)
{
  
  long L1DeviceNo = CSMC_DBData::unspecLong;

  std::map<std::string,long>::iterator it;

  it = m_DevicenameNameList.find( DEVICENAME );

  if ( it != m_DevicenameNameList.end() )
  {
    L1DeviceNo = it->second;
  }

  return L1DeviceNo;
}


std::string CGCE_InjectionContainer::getDeviceNameByL1DeviceNo(long  L1_DEVICENO)
{
  std::string DeviceName = CSMC_DBData::unspecString;

  std::map<long,std::string>::const_iterator it;
  std::map<std::string,std::string>::const_iterator itInjType;

  it = m_L1DevicenoList.find( L1_DEVICENO );

  if ( it != m_L1DevicenoList.end() )
  {
    DeviceName = it->second;
  }

  return DeviceName;
}

std::string CGCE_InjectionContainer::getInjectionTypeByL1DeviceNo(long  L1_DEVICENO, const std::string& DEVICENAME)
{
  std::string InjectionType = CSMC_DBData::unspecString;

  std::map<long,std::string>::const_iterator it;
  std::map<std::string,std::string>::const_iterator itInjType;

  it = m_L1DevicenoList.find( L1_DEVICENO );

  if ( it != m_L1DevicenoList.end() )
  {
    std::string DeviceName = it->second;

    itInjType = m_InjTypeList.find( DeviceName );

    if ( itInjType != m_InjTypeList.end() )
    {
      InjectionType = itInjType->second;
    }
  }

  return InjectionType;
}


std::map<std::string,std::string> CGCE_InjectionContainer::getInjTypeList()
{
  return m_InjTypeList;
}
