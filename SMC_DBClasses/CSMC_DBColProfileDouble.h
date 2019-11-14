// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMC_DBCOLPROFILEDOUBLE_414FF0C60314_INCLUDED
#define _INC_CSMC_DBCOLPROFILEDOUBLE_414FF0C60314_INCLUDED

#include "CSMC_DBColProfile.h"

//##ModelId=414FF0C60314
class CSMC_DBColProfileDouble 
: public CSMC_DBColProfile
{
protected:
	//##ModelId=414FF0D70176
	double m_value;

public:
	//##ModelId=4225EA8A0060
	CSMC_DBColProfileDouble(const std::string& TableName, const std::string  & ColName  , long ColSize = -1);

	//##ModelId=41AC4EB50168
	virtual std::string getSQLString();

	//##ModelId=4159493401FE
	inline double getvalue() const;

	//##ModelId=415949350252
	 void setvalue(double value);


	//##ModelId=414FF0EE0028
	virtual ~CSMC_DBColProfileDouble();

private:

};

//##ModelId=4159493401FE
inline double CSMC_DBColProfileDouble::getvalue() const
{
	return m_value;
}



#endif /* _INC_CSMC_DBCOLPROFILEDOUBLE_414FF0C60314_INCLUDED */
