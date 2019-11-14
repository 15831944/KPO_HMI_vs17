// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CINJECTLANCEDATAHANDLER_4721F8CB036B_INCLUDED
#define _INC_CINJECTLANCEDATAHANDLER_4721F8CB036B_INCLUDED

#include "iSMC_DataProvider_s.hh"

#include <string>

class CInjectLanceDataHandler 
{
public:

	CInjectLanceDataHandler();

	CInjectLanceDataHandler(seqInjectLanceData& InjectLanceData);

	virtual ~CInjectLanceDataHandler();

	void fill(seqInjectLanceData& InjectLanceData);

	void updateLanceValue(const std::string& Device, double LanceVal);

	void updateMatCode(const std::string& Device, const std::string& MatCode);

	void updateModuleName(const std::string& Device, const std::string& ModuleName);

	void update(sInjectLanceData& InjectLanceData);

	void update(seqInjectLanceData& InjectLanceData);

	void insertInjectLanceData(sInjectLanceData& InjectLanceData);

	sInjectLanceData findInjectLanceData(const std::string& Device);

	seqInjectLanceData& getInjectLanceData();

	double getLanceValue(const std::string& Device);

	std::string getMatCode(const std::string& Device);

  std::string getModuleName(const std::string& Device);

  void diff(seqInjectLanceData& InjectLanceData);

  void add(seqInjectLanceData& InjectLanceData);

  std::set<std::string> getDeviceList();

private:

	sInjectLanceData findInjectLanceData(seqInjectLanceData& InjectLanceData, const std::string& Device);

	bool isDevice(seqInjectLanceData& InjectLanceData, const std::string& Device);

	bool isDevice(const std::string& Device);

	seqInjectLanceData m_InjectLanceData;

};

#endif /* _INC_CINJECTLANCEDATAHANDLER_4721F8CB036B_INCLUDED */
