// Copyright (C) 2012 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMC_DBCOLPROFILE_414FDE3F01E9_INCLUDED
#define _INC_CSMC_DBCOLPROFILE_414FDE3F01E9_INCLUDED

#include <math.h>
#include <cmath>
#include <string>
#include <sstream>

enum SMC_DB_Type;

class CSMC_DBColProfile 
{
public:
	enum SMC_DB_Type 
	{
	
		SMC_DB_Bool,

		SMC_DB_String,

		SMC_DB_Long,

		SMC_DB_Double,

		SMC_DB_Date,

		SMC_DB_Blob,

    SMC_DB_UndefinedType
	};

	CSMC_DBColProfile(const std::string  & TableName,  SMC_DB_Type Type, const std::string  & ColName  , long ColSize = -1);

	virtual ~CSMC_DBColProfile();

	inline long getCol() const;

	inline void setCol(long value);

	inline const std::string& getColName() const;

	inline void setColName(const std::string& value);

	inline bool isActive() const;

	inline void setActive(bool value);

	 inline CSMC_DBColProfile::SMC_DB_Type  getType() const;

protected:
	bool m_writeNullValue;
	std::string m_TableName;
	bool m_isActive;
	std::string m_ColName;
	SMC_DB_Type m_Type;
  long m_Col;
  static bool m_ShowPrecisionTestLogs;
  static bool m_IniFileAlreadyRead;

public:
	long m_ColSize;

	virtual std::string getSQLString() = 0;

  bool isWriteNullValue();

};

inline long CSMC_DBColProfile::getCol() const
{
	return m_Col;
}

inline void CSMC_DBColProfile::setCol(long value)
{
	m_Col = value;
}

inline const std::string& CSMC_DBColProfile::getColName() const
{
	return m_ColName;
}

inline void CSMC_DBColProfile::setColName(const std::string& value)
{
	m_ColName = value;
}

inline bool CSMC_DBColProfile::isActive() const
{
	return m_isActive;
}

inline void CSMC_DBColProfile::setActive(bool value)
{
	m_isActive = value;
}
inline CSMC_DBColProfile::SMC_DB_Type  CSMC_DBColProfile::getType() const
{
	return m_Type;
}

#endif /* _INC_CSMC_DBCOLPROFILE_414FDE3F01E9_INCLUDED */
