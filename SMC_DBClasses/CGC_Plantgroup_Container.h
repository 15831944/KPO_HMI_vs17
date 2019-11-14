// Copyright (C) 2004, 2005 SMS Demag AG, Germany 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGC_PLANTGROUP_CONRAINER_43D4F35C03D8_INCLUDED
#define _INC_CGC_PLANTGROUP_CONRAINER_43D4F35C03D8_INCLUDED

#include "CGC_PLANTGROUP.h"

class cCBS_StdConnection;

class CGC_Plantgroup_Container 
{
public:
	CGC_Plantgroup_Container(cCBS_Connection *Connection);

	CGC_Plantgroup_Container(cCBS_StdConnection *Connection);

	virtual ~CGC_Plantgroup_Container();

	//returns UNITGROUPNO for one Plant type
	long getUnitGroupNo(const std::string& Plant);

	//returns UNITGROUPNO for exact one Plant and PlantNo
	long getUnitGroupNo(const std::string& Plant, long PlantNo);

protected:
	CGC_PLANTGROUP* m_pCGC_PLANTGROUP;

private:
	struct UGNo
	{
	public:
		std::string Unit;
		long UnitNo;
		long UnitGroupNo;
	};


	std::vector<UGNo> m_UnitGroupVector;

};

#endif /* _INC_CGC_PLANTGROUP_CONRAINER_43D4F35C03D8_INCLUDED */
