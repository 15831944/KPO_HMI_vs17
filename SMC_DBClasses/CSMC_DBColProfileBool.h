// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMC_DBCOLPROFILEBOOL_414FFBB20021_INCLUDED
#define _INC_CSMC_DBCOLPROFILEBOOL_414FFBB20021_INCLUDED

#include "CSMC_DBColProfile.h"

//##ModelId=414FFBB20021
class CSMC_DBColProfileBool 
: public CSMC_DBColProfile
{
protected:
	//##ModelId=414FFBCE0113
	bool m_value;

public:
	//##ModelId=41AC4EC303C2
	virtual std::string getSQLString();

	//##ModelId=415949050334
	inline void setvalue(bool value);

	//##ModelId=415949060137
	inline bool getvalue() const;


	//##ModelId=415133500265
	virtual ~CSMC_DBColProfileBool();

	//##ModelId=41513350002A
	CSMC_DBColProfileBool(const std::string &TableName, const std::string &ColName);

private:

};

//##ModelId=415949050334
inline void CSMC_DBColProfileBool::setvalue(bool value)
{
	m_value = value;
	return;
}

//##ModelId=415949060137
inline bool CSMC_DBColProfileBool::getvalue() const
{
	return m_value;
}


#endif /* _INC_CSMC_DBCOLPROFILEBOOL_414FFBB20021_INCLUDED */
