// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTREADID_439ECDDE03BE_INCLUDED
#define _INC_CTREADID_439ECDDE03BE_INCLUDED

#include <string>
#include <map>
#include <set>
#include <vector>

#include "CFormattedID.h"

//##ModelId=439ECDDE03BE
class CTreatID 
: public CFormattedID
{
public:
	//##ModelId=439ECDFE00F7
	std::string getTreatID(const std::string Prefix = "", long Counter = 0);

	//##ModelId=439ECDFE0110
	virtual ~CTreatID();

	//##ModelId=439ECDFE0115
	CTreatID();

	//##ModelId=439ECDFE011F
	long getMaxCounter();

	//##ModelId=439ECDFE0129
	long getCounter(const std::string& TreatID = "");

	//##ModelId=439ECDFE0133
	long getCounterLength();

	//##ModelId=439ECDFE013D
  std::string getPrefix(const std::string& TreatID = "");

  std::string generateNextTreatID(const std::string TreatID = "");

protected:
	//##ModelId=439EDC1601E5
	virtual void init();

	//##ModelId=439ED57303DF
	static std::string m_QualifierSeparator;

	//##ModelId=439ECE040269
	static std::string m_QualifierPrefix;

	//##ModelId=439ECE040273
	static std::string m_QualifierCounter;

private:
	//##ModelId=439ECE040291
	std::string m_TreatID;

	//##ModelId=439ECDFE010B
	std::string generateTreatID(const std::string Prefix = "", long Counter = 0);

};

#endif /* _INC_CTREADID_439ECDDE03BE_INCLUDED */
