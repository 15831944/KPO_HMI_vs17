// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_STATUSHANDLER_4214DDBF01B9_INCLUDED
#define _INC_CDM_STATUSHANDLER_4214DDBF01B9_INCLUDED

#include <map>
#include <string>


class CDM_StatusHandler 
{
public:
	void addStatus(const std::string& StatusName, long Status);

	void setStatus(const std::string& StatusName, long Status);

	long getStatus(const std::string& StatusName);

	std::map<std::string,long> &  getStatusList();

	//! compare status value and returns true if
	//! status has changed or a new one has been added.
	bool isStatusChanged(const std::string& StatusName, long value);

private:
	std::map<std::string,long> m_StatusList;

};

#endif /* _INC_CDM_STATUSHANDLER_4214DDBF01B9_INCLUDED */
