// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGASLANCEDATAHANDLER_4721F8CB036B_INCLUDED
#define _INC_CGASLANCEDATAHANDLER_4721F8CB036B_INCLUDED

#include "iSMC_DataProvider_s.hh"

#include <string>

class CGasLanceDataHandler 
{
public:
  void updateGasDataValue(const std::string& Device, const std::string& GasType, double GasValue);

  void diff(seqGasLanceData& GasLanceData);

  void updateGasData(seqGasData& GasData, const seqGasData& NewGasData);

  void insertGasLanceData(sGasLanceData& GasLanceData);

  void insertGasData(const std::string& Device,  seqGasData& GasData);

  void insertGasDataValue(const std::string& Device, const std::string& GasType, double GasValue);

  sGasLanceData findGasLanceData(const std::string& Device);

  virtual ~CGasLanceDataHandler();

  CGasLanceDataHandler();

  CGasLanceDataHandler(seqGasLanceData& GasLanceData);

  void fill(seqGasLanceData& GasLanceData);

  seqGasLanceData& getGasLanceData();

  void update(seqGasLanceData& GasLanceData);

  void update(sGasLanceData& GasLanceData);

  double getGasValue(const std::string& Device, const std::string& GasType);

  seqGasData getGasDataSeq(const std::string& Device);

  double getTotalGasValue(const std::string& GasType);

  void add(seqGasLanceData& GasLanceData);

  std::set<std::string> getDeviceList();

private:
  sGasData findGasData(seqGasData& GasData, const std::string& GasType);

  bool isGasType(seqGasData& GasData, const std::string& GasType);
  sGasLanceData findGasLanceData(seqGasLanceData& GasLanceData, const std::string& Device);

  seqGasData getGasDataSeq(seqGasLanceData& GasLanceData, const std::string& Device);

  bool isDevice(seqGasLanceData& GasLanceData, const std::string& Device);
  bool isDevice(const std::string& Device);

  seqGasLanceData m_GasLanceData;

};

#endif /* _INC_CGASLANCEDATAHANDLER_4721F8CB036B_INCLUDED */
