// Copyright (C) 2009 SMS Demag AG, Germany 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGT_MAT_PURP_CONRAINER_43D4F35C03D8_INCLUDED
#define _INC_CGT_MAT_PURP_CONRAINER_43D4F35C03D8_INCLUDED

#include "CSMC_EventLogFrameController.h"
#include "cCBS_StdLog_Task.h"
#include "CGT_MAT_PURP.h"
#include "CGC_PLANTGROUP.h"

class CGT_MAT_PURP;
class CGC_PLANTGROUP;

class CGT_MAT_PURP_Container 
{
public:

  CGT_MAT_PURP_Container(cCBS_StdConnection *Connection);
	virtual ~CGT_MAT_PURP_Container();

  std::string getPurpCode(std::string& MatCode, long UnitGroupNo, std::set<std::string> PurpCode);

protected:

	CGT_MAT_PURP   * m_pGT_MAT_PURP;

private:

	std::map<std::string, std::pair<long, std::string> > m_MatPurpList;

};

#endif
