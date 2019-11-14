// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHEADIDCUST_439ECDDE03BE_INCLUDED
#define _INC_CHEADIDCUST_439ECDDE03BE_INCLUDED

#include <string>
#include <map>
#include <set>
#include <vector>

#include "CFormattedID.h"

class CHeatIDCust 
: public CFormattedID
{
public:
	std::string getHeatIDCust(const std::string Prefix = "", long Counter = 0);

	virtual ~CHeatIDCust();

	CHeatIDCust();

	long getMaxCounter();

	long getCounter(const std::string& HeatIDCust = "");

	long getCounterLength();

  std::string getPrefix(const std::string& HeatIDCust = "");

  std::string generateNextHeatIDCust(const std::string HeatIDCust = "");

  std::string generateNextHeatIDCust(const std::string Prefix, long Counter);

protected:

	virtual void init();

	static std::string m_QualifierSeparator;

	static std::string m_QualifierPrefix;

	static std::string m_QualifierCounter;

private:
	std::string m_HeatIDCust;

	std::string generateHeatIDCust(const std::string Prefix = "", long Counter = 0);

};

#endif /* _INC_CHEADIDCUST_439ECDDE03BE_INCLUDED */
