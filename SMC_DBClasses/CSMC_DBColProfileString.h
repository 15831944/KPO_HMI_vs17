// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMC_DBCOLPROFILESTRING_414FDFD40015_INCLUDED
#define _INC_CSMC_DBCOLPROFILESTRING_414FDFD40015_INCLUDED

#include "CSMC_DBColProfile.h"

//##ModelId=414FDFD40015
class CSMC_DBColProfileString 
: public CSMC_DBColProfile
{
protected:
	//##ModelId=414FDFF30006
	std::string m_value;

public:
	//##ModelId=4225EA0400C6
	CSMC_DBColProfileString(const std::string& TableName, const std::string  & ColName  , long ColSize = -1);

	//##ModelId=41AC4ECA02D2
	virtual std::string getSQLString();

	//##ModelId=415949660008
	 void setvalue( std::string & value);

	//##ModelId=4159496601BF
	inline const std::string& getvalue() const;


	//##ModelId=414FE1E003DA
	virtual ~CSMC_DBColProfileString();

private:

};


//##ModelId=4159496601BF
inline const std::string& CSMC_DBColProfileString::getvalue() const
{
	return m_value;
}


#endif /* _INC_CSMC_DBCOLPROFILESTRING_414FDFD40015_INCLUDED */
