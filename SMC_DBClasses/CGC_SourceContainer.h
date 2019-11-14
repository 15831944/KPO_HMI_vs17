// Copyright (C) 2004 SMS Demag AG, Germany 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGC_SOURCECONTAINER_423E8E14013C_INCLUDED
#define _INC_CGC_SOURCECONTAINER_423E8E14013C_INCLUDED

#include "CGC_Source.h"

//##ModelId=423E8E14013C
class CGC_SourceContainer 
{
public:
	//##ModelId=42401FA0006A
	std::string getL2SourceNameByL1No(long  L1SourceNo);

	//##ModelId=423ED75C00A3
	virtual ~CGC_SourceContainer();

	//##ModelId=423ED762030E
	CGC_SourceContainer(cCBS_StdConnection * Connection, const std::string & Plant, long PlantNo);

	//##ModelId=423ED8F102A4
	long getSourceL1InfoNoByName(const std::string & SourceName);

protected:
	//##ModelId=423E8E8200EA
	CGC_SOURCE* m_pGC_SOURCE;

private:
	//##ModelId=42401C720308
	std::map<long, std::string> m_L1SourceNoList;

	//##ModelId=423ED8960112
	std::map<std::string, long> m_L2SourceNameList;

};

#endif /* _INC_CGC_SOURCECONTAINER_423E8E14013C_INCLUDED */
