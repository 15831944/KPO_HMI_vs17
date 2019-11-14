// Copyright (C) 2004 SMS Demag AG

#include "CIntfData.h"

#include "CCoolWaterHandler.h"

CCoolWaterHandler::~CCoolWaterHandler()
{
}

CCoolWaterHandler::CCoolWaterHandler()
{
	m_CoolWaterData.length(0);
}

CCoolWaterHandler::CCoolWaterHandler(seqCoolWaterData& CoolWaterData)
{
	fill(CoolWaterData);
}

void CCoolWaterHandler::fill(seqCoolWaterData& CoolWaterData)
{
	m_CoolWaterData = CoolWaterData;
}

seqCoolWaterData& CCoolWaterHandler::getCoolWaterData()
{
  return m_CoolWaterData;
}

void CCoolWaterHandler::update(seqCoolWaterData& CoolWaterData)
{
  for ( long i = 0 ; i < CIntfData::getLength(CoolWaterData) ; ++i )
  {
    sCoolWaterDevice CoolWaterDevice;
    CIntfData::getAt(CoolWaterDevice,CoolWaterData,i);

    update(CoolWaterDevice);
  }
}

void CCoolWaterHandler::update(sCoolWaterDevice& CoolWaterDevice)
{
  // try to find existing device of CoolWaterData
  if ( isDevice( ( std::string)CoolWaterDevice.CoolWaterDevice, CoolWaterDevice.CoolWaterDeviceNo) )
  {
    for ( long i = 0 ; i < CIntfData::getLength(m_CoolWaterData) ; ++i )
    {
      sCoolWaterDevice ActCoolWaterDevice;
      CIntfData::getAt(ActCoolWaterDevice,m_CoolWaterData,i);

      // find position of new CoolWaterData at m_CoolWaterData
      if ( (std::string)ActCoolWaterDevice.CoolWaterDevice   == (std::string)CoolWaterDevice.CoolWaterDevice &&
                        ActCoolWaterDevice.CoolWaterDeviceNo == CoolWaterDevice.CoolWaterDeviceNo             )
      {
        CIntfData::setAt(m_CoolWaterData,CoolWaterDevice,i);
      }
    }
  }
  else
  {
    insertCoolWaterData(CoolWaterDevice);
  }
}

bool CCoolWaterHandler::getCoolWaterData(const std::string& Device, long DeviceNo, double &InletTemp, double &OutletTemp, double& WaterFlow)
{
  bool RetValue = false;

  sCoolWaterDevice CoolWaterDevice = getCoolWaterDeviceData(Device, DeviceNo);

  if ( CoolWaterDevice.CoolWaterDevice != DEF::Inv_String )
  {
    InletTemp   = CoolWaterDevice.CoolWaterData.InletTemp;
    OutletTemp  = CoolWaterDevice.CoolWaterData.OutletTemp;
    WaterFlow   = CoolWaterDevice.CoolWaterData.WaterFlow;
    RetValue    = true;
  }  
  else
  {
    InletTemp   = DEF::Inv_Double;
    OutletTemp  = DEF::Inv_Double;
    WaterFlow   = DEF::Inv_Double;
    RetValue    = false;
  }  

  return RetValue;
}

sCoolWaterDevice CCoolWaterHandler::getCoolWaterDeviceData(seqCoolWaterData& CoolWaterData, const std::string& Device, long DeviceNo)
{
  sCoolWaterDevice RetValue;

  RetValue.CoolWaterDevice   = DEF::Inv_String;
  RetValue.CoolWaterDeviceNo = DEF::Inv_Long;

  for ( long i = 0 ; i < CIntfData::getLength(CoolWaterData) ; ++i )
  {
    sCoolWaterDevice CoolWaterDevice;

    CIntfData::getAt(CoolWaterDevice,CoolWaterData,i);

    if ( (std::string)CoolWaterDevice.CoolWaterDevice   == Device &&
                      CoolWaterDevice.CoolWaterDeviceNo == DeviceNo )
    {
      RetValue = CoolWaterDevice;
      break;
    }
  }

  return RetValue;
}

sCoolWaterDevice CCoolWaterHandler::getCoolWaterDeviceData(const std::string& Device, long DeviceNo)
{
  return getCoolWaterDeviceData(m_CoolWaterData, Device, DeviceNo);
}

bool CCoolWaterHandler::isDevice(seqCoolWaterData& CoolWaterData, const std::string& Device, long DeviceNo)
{
  bool RetValue = false;

  for ( long i = 0 ; i < CIntfData::getLength(CoolWaterData) ; ++i )
  {
    sCoolWaterDevice CoolWaterDevice;

    CIntfData::getAt(CoolWaterDevice,CoolWaterData,i);

    if ( (std::string)CoolWaterDevice.CoolWaterDevice   == Device &&
                      CoolWaterDevice.CoolWaterDeviceNo == DeviceNo )
    {
      RetValue = true;
      break;
    }
  }

	return RetValue;
}

sCoolWaterDevice CCoolWaterHandler::findCoolWaterData(seqCoolWaterData& CoolWaterData, const std::string& Device, long DeviceNo)
{
  sCoolWaterDevice RetValue;

  for ( long i = 0 ; i < CIntfData::getLength(CoolWaterData) ; ++i )
  {
    sCoolWaterDevice CoolWaterDevice;

    CIntfData::getAt(CoolWaterDevice,CoolWaterData,i);

    if ( (std::string)CoolWaterDevice.CoolWaterDevice   == Device &&
                      CoolWaterDevice.CoolWaterDeviceNo == DeviceNo )
    {
      RetValue = CoolWaterDevice;
      break;
    }
  }

	return RetValue;
}

sCoolWaterDevice CCoolWaterHandler::findCoolWaterData(const std::string& Device, long DeviceNo)
{
	return findCoolWaterData(m_CoolWaterData, Device, DeviceNo);
}

bool CCoolWaterHandler::isDevice(const std::string& Device, long DeviceNo)
{
	return isDevice(m_CoolWaterData, Device, DeviceNo);
}

void CCoolWaterHandler::insertCoolWaterData(sCoolWaterDevice& CoolWaterDevice)
{
  CIntfData::insert(m_CoolWaterData,CoolWaterDevice);
}


std::set<std::string> CCoolWaterHandler::getDeviceList()
{
  std::set<std::string> DeviceList;

  for ( long i = 0 ; i < CIntfData::getLength(m_CoolWaterData) ; ++i )
  {
    sCoolWaterDevice CoolWaterDevice;
    CIntfData::getAt(CoolWaterDevice,m_CoolWaterData,i);

    DeviceList.insert(std::string(CoolWaterDevice.CoolWaterDevice));
  }

  return DeviceList;

}