// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTSMOBJECTCREATOR_4105343303BE_INCLUDED
#define _INC_CTSMOBJECTCREATOR_4105343303BE_INCLUDED

#include "CTSM_ObjectCreator.h"

class CTsmObjectCreator 
: public CTSM_ObjectCreator
{
public:
	//Clears the plant backup in the database in the case 
	//that restorePlant ist not successful.
	virtual void clearPlantBackup();

	//Restores the plant from a persistent data storage.
	virtual CPlant* restorePlant();

	//Creates an event point for the given object ID. This 
	//function can be overwritten to create a project 
	//specific event point object.
	virtual CEventPoint* createEventPoint(const CObjectID & eventPointID);

	//Creates a plant object. This function can be 
	//overwritten to create a project specific plant object.
	virtual CPlant* createPlant(const std::string & Plant);

	//Creates a product for the given object ID. This 
	//function can be overwritte to create project specific 
	//product objects.
	virtual CProduct* createProduct(const CObjectID & productID);

};

#endif /* _INC_CTSMOBJECTCREATOR_4105343303BE_INCLUDED */
