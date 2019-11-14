// Copyright (C) 2004 SMS Demag AG, Germany 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMC_DBTableBase_41D930570288_INCLUDED
#define _INC_CSMC_DBTableBase_41D930570288_INCLUDED

#include <string>
#include "CSMC_DBData.h"

// **
//##ModelId=41D930570288
class CSMC_DBTableBase 
{
protected:
  cCBS_StdConnection* m_pStdConnection;

  CSMC_DBData * m_pSMC_DBData;

	//##ModelId=41D9305A037D
	CSMC_DBTableBase(cCBS_StdConnection* Connection);

public:

	//##ModelId=41D9305C0004
	~CSMC_DBTableBase();

  void setColumnsFromTable(CSMC_DBData* pSourceTable, long Row);
  bool insert();
  void commit();
  bool deleteRows();
  long getLastRow();

  std::string getString(const std::string& ColName, long Row);
	long getLong(const std::string& ColName, long Row);
	double getDouble(const std::string& ColName, long Row);
	bool getBool(const std::string& ColName, long Row);

  void setBool(const std::string &ColName, bool value);
	void setDouble(const std::string  & ColName, double value);
	void setString( const std::string  & ColName, const std::string &value);
	void setLong( const std::string &ColName, long value);
	bool first();
	bool last();
	bool next();
	bool prev();

};

#endif /* _INC_CSMC_DBTableBase_41D930570288_INCLUDED */
