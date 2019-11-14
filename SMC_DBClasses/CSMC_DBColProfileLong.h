// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMC_DBCOLPROFILELONG_414FE04A0033_INCLUDED
#define _INC_CSMC_DBCOLPROFILELONG_414FE04A0033_INCLUDED

#include "CSMC_DBColProfile.h"

//##ModelId=414FE04A0033
class CSMC_DBColProfileLong 
: public CSMC_DBColProfile
{
protected:
	//##ModelId=414FE05B01DC
	long m_value;

public:
	//##ModelId=4225EA940246
	CSMC_DBColProfileLong(const std::string& TableName, const std::string  & ColName  , long ColSize = -1);

	//##ModelId=41AC4EBC001E
	virtual std::string getSQLString();

	//##ModelId=415949850267
	inline long getvalue() const;

	//##ModelId=415949860008
	 void setvalue(long value);


	//##ModelId=414FE1E503CD
	virtual ~CSMC_DBColProfileLong();

private:

};

//##ModelId=415949850267
inline long CSMC_DBColProfileLong::getvalue() const
{
	return m_value;
}



#endif /* _INC_CSMC_DBCOLPROFILELONG_414FE04A0033_INCLUDED */
