// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CCOOLWATERHANDLER_4721F8CB036B_INCLUDED
#define _INC_CCOOLWATERHANDLER_4721F8CB036B_INCLUDED

#include "iSMC_DataProvider_s.hh"

#include <string>

class CCoolWaterHandler 
{
public:
  void diff(seqCoolWaterData& CoolWaterData);

  void updateCoolWaterData(seqCoolWaterData& CoolWaterData, const seqCoolWaterData& NewCoolWaterData);

  void insertCoolWaterData(sCoolWaterDevice& CoolWaterDevice);

  sCoolWaterDevice findCoolWaterData(const std::string& Device, long DeviceNo);

  virtual ~CCoolWaterHandler();

  CCoolWaterHandler();

  CCoolWaterHandler(seqCoolWaterData& CoolWaterData);

  void fill(seqCoolWaterData& CoolWaterData);

  seqCoolWaterData& getCoolWaterData();

  void update(seqCoolWaterData& CoolWaterData);

  void update(sCoolWaterDevice& CoolWaterDevice);

  bool getCoolWaterData(const std::string& Device, long DeviceNo, double &InletTemp, double &OutletTemp, double& WaterFlow);

  sCoolWaterDevice getCoolWaterDeviceData(const std::string& Device, long DeviceNo);

  void add(seqCoolWaterData& CoolWaterData);

  std::set<std::string> getDeviceList();

private:
  sCoolWaterDevice findCoolWaterData(seqCoolWaterData& CoolWaterData, const std::string& Device, long DeviceNo);

  sCoolWaterDevice getCoolWaterDeviceData(seqCoolWaterData& CoolWaterData, const std::string& Device, long DeviceNo);

  bool isDevice(seqCoolWaterData& CoolWaterData, const std::string& Device, long DeviceNo);
  bool isDevice(const std::string& Device, long DeviceNo);

  seqCoolWaterData m_CoolWaterData;

};

#endif /* _INC_CCOOLWATERHANDLER_4721F8CB036B_INCLUDED */
