// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSTIRRINGDATAHANDLER_472846690178_INCLUDED
#define _INC_CSTIRRINGDATAHANDLER_472846690178_INCLUDED

#include <vector>
#include <string>

#include "iSMC_DataProvider_s.hh"

class CStirringDataHandler 
{
public:
  void fill(seqStirringData& SeqStirringData);

  seqStirringData& getStirringData();

  void update(seqStirringData& SeqStirringData);

  void update(sStirringData& NewStirringData);

  void updateGasData(seqGasData& GasData, const seqGasData& NewGasData);

  void updateGasDataValue(const std::string& Device, const std::string& GasType, double GasValue);

  // set gas value for all used gas types of existing Device only
  void setGasDataValue(std::vector<std::string> DeviceList, double Value);

  // set gas value for all used gas types of existing Device only
  void setGasDataValue(const std::string& Device, double Value);

  double getGasValue(const std::string& Device, const std::string& GasType);

  void insertStirringData(sStirringData& NewStirringData);

  void insertGasData(const std::string& Device, seqGasData& GasData);

  void insertGasDataValue(const std::string& Device, const std::string& GasType, double GasValue);

  seqGasData getGasDataSeq(const std::string& Device);

  virtual ~CStirringDataHandler();

  CStirringDataHandler();

  CStirringDataHandler(seqStirringData& SeqStirringData);

  sStirringData findStirringData(const std::string& Device);

  void diff(seqStirringData& SeqStirringData);

  seqGasData getAccumulatedGasDataSeq();
  seqGasData getAccumulatedGasDataSeq(seqStirringData& SeqStirringData);
  double getAccumulatedGasValue(const std::string& GasType);
  double getMaxGasDataValue(const std::string& GasType);
  void add(seqStirringData& SeqStirringData);

private:
  seqStirringData m_SeqStirringData;

  seqGasData getGasDataSeq(seqStirringData& SeqStirringData, const std::string& Device);

  bool isDevice(seqStirringData& SeqStirringData, const std::string& Device);

  bool isDevice(const std::string& Device);

  bool isGasType(seqGasData& GasData, const std::string& GasType);

  sStirringData findStirringData(seqStirringData& SeqStirringData, const std::string& Device);

  sGasData findGasData(seqGasData& GasData, const std::string& GasType);

};

#endif /* _INC_CSTIRRINGDATAHANDLER_472846690178_INCLUDED */
