// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_EAFMATERIALHANDLINGWRAPPER_42D244750385_INCLUDED
#define _INC_CARCHIVER_EAFMATERIALHANDLINGWRAPPER_42D244750385_INCLUDED

#include "CARCHIVER_MaterialHandlingWrapper.h"

class CEventMessage;

class CARCHIVER_EAFMaterialHandlingWrapper 
	: public CARCHIVER_MaterialHandlingWrapper
{
public:
	bool doOnHandleBasketDeassignedFromHeat(CEventMessage& Event);

	virtual ~CARCHIVER_EAFMaterialHandlingWrapper();

	CARCHIVER_EAFMaterialHandlingWrapper();

	bool doOnMaterialHandlingReport(CEventMessage& Event);

	bool doOnLiqMatHandlingReport(CEventMessage& Event);

	bool UpdateLadleData(double RemNettWgt,double GrossWgt,double RemSteelWgt,double RemSlagWgt,long ScullMass,long Location,long Deslaged);

  bool doBasketDischarge(CEventMessage& Event);

protected:

	virtual void deleteDBClasses();

	virtual void initDBClasses();
};

#endif /* _INC_CARCHIVER_EAFMATERIALHANDLINGWRAPPER_42D244750385_INCLUDED */
