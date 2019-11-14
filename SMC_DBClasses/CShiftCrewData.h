// Copyright (C) 2004, 2005 SMS Demag AG, Germany 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CShiftCrewData_INCLUDED
#define _INC_CShiftCrewData_INCLUDED

#include "CSMC_DBData.h"

/////////////////////////////////////////////////////////
//
//This is not a generated class for a table. It provides 
//possibility to get equipment data depends on 2,3 or more 
//tables.
//
/////////////////////////////////////////////////////////
class CShiftCrewData 
{
protected:
  
  cCBS_StdConnection * m_pCBS_StdConnection;

  void log(const std::string& Message, long Level);

  cCBS_ODBC_DBError m_lastError; 

public:

  cCBS_ODBC_DBError getLastError();

	CShiftCrewData(cCBS_StdConnection* Connection);

	virtual ~CShiftCrewData();

  void getCrewAndShiftByDate(std::string& CREW_ID, std::string& SHIFT_ID, const CDateTime& ActDate, const std::string& PLANT, long PLANTNO);

  std::string getMemberNameByRole(const CDateTime& ActDate, const std::string& PLANT, long PLANTNO, long MemberRole);

  std::string getMemberIdByRole(const CDateTime& ActDate, const std::string& PLANT, long PLANTNO, long MemberRole);

};

#endif /* _INC_CShiftCrewData_INCLUDED */
