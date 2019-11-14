// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTREATIDCUST_439ECDDE03BE_INCLUDED
#define _INC_CTREATIDCUST_439ECDDE03BE_INCLUDED

#include <string>
#include <map>
#include <set>
#include <vector>

#include "CFormattedID.h"

class CTreatIDCust 
: public CFormattedID
{
public:
	std::string getTreatID(const std::string Prefix = "", long Counter = 0);

	virtual ~CTreatIDCust();

	CTreatIDCust();

	long getMaxCounter();

	long getCounter(const std::string& TreatIDCust = "");

	long getCounterLength();

  std::string getPrefix(const std::string& TreatIDCust = "");

  std::string generateNextTreatID(const std::string TreatIDCust = "");

protected:
	virtual void init();

	static std::string m_QualifierSeparator;

	static std::string m_QualifierPrefix;

	static std::string m_QualifierCounter;

private:
	std::string m_TreatID;

	std::string generateTreatID(const std::string Prefix = "", long Counter = 0);

};

#endif /* _INC_CTREATIDCUST_439ECDDE03BE_INCLUDED */
