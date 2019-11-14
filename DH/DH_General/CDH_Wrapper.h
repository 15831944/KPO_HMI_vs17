// Copyright (C) 2005 SMS Demag AG Germany

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDH_WRAPPER_4253DBF303C5_INCLUDED
#define _INC_CDH_WRAPPER_4253DBF303C5_INCLUDED

#include <string>
#include "CGC_Plant_Container.h"
#include "CHeatDataConverter.h"
class CDH_Task;

//////////////////////////////////////////////////
//
//Base class for DH_OUT_Wrappers. 
//
//////////////////////////////////////////////////
//##ModelId=4253DBF303C5
class CDH_Wrapper 
{
protected:
	//##ModelId=4412B57A0091
	CHeatDataConverter* m_pHeatDataConverter;

	//##ModelId=433BB8790033
	std::string m_SenderName;

	//##ModelId=433BB8890178
	std::string m_DestinationName;

	//PlantID converter between L1<-->L2
	//##ModelId=43C7D145014C
	CGC_Plant_Container* m_pGC_Plant_Container;

public:
	//##ModelId=4253DC4C02A0
	virtual void log(const std::string& Message, long Level = 1);

	//##ModelId=4253DC470040
	virtual ~CDH_Wrapper();

	//##ModelId=4253DC470237
	CDH_Wrapper();

};

#endif /* _INC_CDH_WRAPPER_4253DBF303C5_INCLUDED */
