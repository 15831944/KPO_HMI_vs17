// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_GENPRODUCTMANAGER_413DC90903A3_INCLUDED
#define _INC_CDM_GENPRODUCTMANAGER_413DC90903A3_INCLUDED

#include <string>
#include <vector>

#include "CDM_ProductManager.h"

class CEventMessage;
class CDM_ProductManagementInterface_Impl;

//Handling ProductID's at ProductManagment interface 
//regarding to incoming events
class CDM_GENProductManager : public CDM_ProductManager
{
public:
	CDM_GENProductManager();

	virtual ~CDM_GENProductManager();

	//Register ProductID at ProductManagement interface by 
	//Event data

public:
	virtual bool changeSampleInformation(CEventMessage& Event);

	virtual bool changeAnalysisInformation(CEventMessage& Event);

private:
	//Remove ProductID at ProductManagement interface by 
	//ProductID or HeatID+TreatID

};

#endif /* _INC_CDM_GENPRODUCTMANAGER_413DC90903A3_INCLUDED */
