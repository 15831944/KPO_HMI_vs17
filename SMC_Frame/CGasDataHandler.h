
// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGASDATAHANDLER_425FDBD601AD_INCLUDED
#define _INC_CGASDATAHANDLER_425FDBD601AD_INCLUDED

#include "iSMC_DataDefinitions_s.hh"

#include <map>
#include <string>
#include "CIntfData.h"


class CGasDataHandler 
{
public:

  CGasDataHandler();
  CGasDataHandler(seqGasData& seqData);

  void updateGasData(seqGasData& seqData);

  void removeGasData(const std::string& GasName);

  seqGasData getGasData();

  //initialize with gas data
  void setGasData(seqGasData& seqData);

  //New values from other gas handler will be added
  //Set gas if it doesn't exist yet
  void addGasData(CGasDataHandler& GasDataHandler);

  //calculate absolute gas difference for gas types in seqData
  void diffGasData(seqGasData& seqData);

  //unload all gas types with values into sequence
  void fillSequence(seqGasData& seqData);

  //New values will be added to existing one
  //Set gas if it doesn't exist yet
  void addGasData(seqGasData& seqData);

  //clear gas handler
  void clear();

  //calculate absolute difference for given gas
  //given Data will taken if gas doesn't exist 
  void diffGasData(const std::string& GasName, double Data);

  //Data will be added to respective gas
  void addGasData(const std::string& GasName, double Data);

  //update or insert respective gas with new value 
  void setGasData(const std::string& GasName, double Data);

  //return value of gas. DEF::Inv_Double if not found
  double getGasData(const std::string& GasName);

  //return container of all gas types with values
  std::map<std::string,double>& getGasDataList();

private:
  std::map<std::string, double>  m_GasDataList;

};

#endif /* _INC_CGASDATAHANDLER_425FDBD601AD_INCLUDED */
