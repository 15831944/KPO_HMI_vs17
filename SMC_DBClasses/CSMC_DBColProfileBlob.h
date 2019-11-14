// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif

#include "CSMC_DBColProfile.h"

class CSMC_DBColProfileBlob 
: public CSMC_DBColProfile
{
protected:
	cCBS_Blob m_value;

public:
	CSMC_DBColProfileBlob(const std::string& TableName, const std::string  & ColName  , long ColSize = -1);

	virtual std::string getSQLString();

	 void setvalue(cCBS_Blob & value);

	inline const cCBS_Blob& getvalue() const;

	virtual ~CSMC_DBColProfileBlob();

private:

};

inline const cCBS_Blob& CSMC_DBColProfileBlob::getvalue() const
{
	return m_value;
}
