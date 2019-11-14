// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSTATUSHANDLER_47384A8F01B9_INCLUDED
#define _INC_CSTATUSHANDLER_47384A8F01B9_INCLUDED

#include "iSMC_DataDefinitions_s.hh"
#include "CDateTime.h"
#include <string>
#include <map>

#include "CStatusHandlerValidator.h"

class CStatusHandler 
{
public:
	virtual ~CStatusHandler();

	CStatusHandler();

  CStatusHandler(seqStatus& StatusData);

	// compare status value and returns true if
	// status has changed or a new one has been added.
	bool isStatusChanged(const std::string& ID, const std::string& StatusName, long Value);

  // mapping true/false to DEF_GEN_STATES::On/DEF_GEN_STATES::Off
  bool isStatusChanged(const std::string& ID, const std::string& StatusName, bool Value);

  // remove ID with all Status Names
	void removeID(const std::string& ID);

  //set using status of gas availability
  void addStatus(std::string& ID, seqGasAvail& SeqGasAvail);

  // return status of StatusNamne
  long getStatus(const std::string& ID, const std::string& StatusNamne);

  //calls update update(sStatus Status)
  void update(seqStatus& StatusData);

  //calls setStatus or addStatus by using of device as ID
  void update(sStatus Status);

  void update(const std::string& Device, const std::string& StatusName, long Status);

  //return filled seqStatus from m_StatusList
  seqStatus getStatusData();

  seqStatus getStatusData(long Status);

  std::vector<std::string> getIDList(const std::string& StatusName, long Value);

  void updateValue(std::vector<std::string> IDList, const std::string& StatusName, long Value);

  long getMaxStatus(seqStatus& SeqStatus, const std::string& DeviceName = "", const std::string& StatusName = "");

  long getMinStatus(seqStatus& SeqStatus, const std::string& DeviceName = "", const std::string& StatusName = "");

  
  // ********************************
  // handling data on given sequences
  // ********************************

	//change device status in SeqStatus
  //insert DeviceName into SeqStatus if not available yet
	static bool setDeviceStatus(seqStatus& SeqStatus, const std::string& DeviceName, const std::string& StatusName, long Value);

  // mapping true/false to DEF_GEN_STATES::On/DEF_GEN_STATES::Off
  static bool setDeviceStatus(seqStatus& SeqStatus, const std::string& DeviceName, const std::string& StatusName, bool Value);

	//return values: >-1 - device status from SeqStatus
  //                -1 - DeviceName is not found 
	static long getDeviceStatus(seqStatus& SeqStatus, const std::string& DeviceName, const std::string& StatusName);

	//set start time of status start
	static bool setStartTime(seqStatus& SeqStatus, const std::string& DeviceName, const std::string& StatusName, sDate Value);

	//get start time of status start
  //return: CDateTime::InvalidDate() - DeviceName is not found
	static sDate getStartTime(seqStatus& SeqStatus, const std::string& DeviceName, const std::string& StatusName);

	//set end time of status end
	static bool setEndTime(seqStatus& SeqStatus, const std::string& DeviceName, const std::string& StatusName, sDate Value);

	//get end time of status end
  //return: CDateTime::InvalidDate() - DeviceName is not found
	static sDate getEndTime(seqStatus& SeqStatus, const std::string& DeviceName, const std::string& StatusName);


private:
	//first key is group identifier
	//second key is container with state identifier and state value
	std::map<std::string, std::map<std::string, long> > m_StatusList;

  //add status of StatusName for ID
	void addStatus(const std::string& ID, const std::string& StatusName, long Value);

  //return true if StatusName exist for given ID
	bool isStatus(const std::string& ID, const std::string& StatusName);

	//##ModelId=47384B7A0372
	void setStatus(const std::string& ID, const std::string& StatusName, long Value);

  void loadRules();

  CStatusHandlerValidator  m_Validator;

  void fill(seqStatus& StatusData);

};

#endif /* _INC_CSTATUSHANDLER_47384A8F01B9_INCLUDED */
