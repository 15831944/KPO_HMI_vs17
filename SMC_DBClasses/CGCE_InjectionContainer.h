#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGCE_INJECTIONCONTAINER_INCLUDED
#define _INC_CGCE_INJECTIONCONTAINER_INCLUDED

#include "CGCE_INJECTION.h"

class CGCE_InjectionContainer
{
public:
  std::string getDeviceNameByL1DeviceNo(long L1_DEVICENO);

  virtual ~CGCE_InjectionContainer();

  CGCE_InjectionContainer(cCBS_StdConnection* Connection, const std::string& PLANT, long PlantNo);

  long getL1DeviceNoByDeviceName(const std::string& DEVICENAME);

  std::string getInjectionTypeByL1DeviceNo(long  L1_DEVICENO, const std::string& DEVICENAME);

  std::map<std::string,std::string> CGCE_InjectionContainer::getInjTypeList();

protected:
  // to fill container
  CGCE_INJECTION* m_pCGCE_INJECTION;

private:
  //##ModelId=42401C720308
  std::map<long, std::string> m_L1DevicenoList;

  //##ModelId=423ED8960112
  std::map<std::string, long> m_DevicenameNameList;

  std::map<std::string, std::string> m_InjTypeList;
};
#endif