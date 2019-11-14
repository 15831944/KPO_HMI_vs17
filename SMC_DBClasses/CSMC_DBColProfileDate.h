// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMC_DBCOLPROFILEDATE_4159282500B6_INCLUDED
#define _INC_CSMC_DBCOLPROFILEDATE_4159282500B6_INCLUDED

#include "CDateTime.h"

#include "CSMC_DBColProfile.h"

//##ModelId=4159282500B6
class CSMC_DBColProfileDate 
: public CSMC_DBColProfile
{
protected:
	//##ModelId=415929390170
	DB_CLASSLIB_DATE m_value;

public:
	//##ModelId=41AC528D00AD
	virtual std::string getSQLString();

	//##ModelId=41594AE20155
	DB_CLASSLIB_DATE *getDateTime() ;

	//Date is given in common CDateTime format and internally 
	//stored as DB_CLASSLIB_DATE.
	//##ModelId=41594B0503A8
	void setDateTime(const CDateTime& value);

	//##ModelId=4159297C0149
	CSMC_DBColProfileDate(const std::string &TableName, const std::string &ColName);

	//##ModelId=4159297C0349
	virtual ~CSMC_DBColProfileDate();

};

#endif /* _INC_CSMC_DBCOLPROFILEDATE_4159282500B6_INCLUDED */
