// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CINJECTDATAHANDLER_4721F8CB036B_INCLUDED
#define _INC_CINJECTDATAHANDLER_4721F8CB036B_INCLUDED

#include "iSMC_DataProvider_s.hh"

#include <string>

class CInjectDataHandler 
{
public:

	CInjectDataHandler();

	CInjectDataHandler(seqInjectData& InjectData);

	virtual ~CInjectDataHandler();

	void fill(seqInjectData& InjectData);

	void updateInjectMatValue(const std::string& InjectType, double InjectMatValue);

	void updateInjectMatCode(const std::string& InjectType, const std::string& InjectMatCode);

	void update(sInjectData& InjectData);

	void update(seqInjectData& InjectData);

	void insertInjectData(sInjectData& InjectData);

	sInjectData findInjectData(const std::string& InjectType);

	seqInjectData& getInjectData();

	double getInjectMatValue(const std::string& InjectType);

  std::string getInjectMatCode(const std::string& InjectType);

  void diff(seqInjectData& InjectData);

  void add(seqInjectData& InjectData);

private:

	sInjectData findInjectData(seqInjectData& InjectData, const std::string& InjectType);

	bool isInjectType(seqInjectData& InjectData, const std::string& InjectType);

	bool isInjectType(const std::string& InjectType);

	seqInjectData m_InjectData;

};

#endif /* _INC_CINJECTDATAHANDLER_4721F8CB036B_INCLUDED */
