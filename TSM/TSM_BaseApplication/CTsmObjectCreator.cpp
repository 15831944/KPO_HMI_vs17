// Copyright (C) 2004 SMS Demag AG

#include "CTsmObjectCreator.h"

CEventPoint* CTsmObjectCreator::createEventPoint(const CObjectID & eventPointID)
{
	return CTSM_ObjectCreator::createEventPoint(eventPointID);
}

CPlant* CTsmObjectCreator::createPlant(const std::string & Plant)
{
	return CTSM_ObjectCreator::createPlant(Plant);
}

CProduct* CTsmObjectCreator::createProduct(const CObjectID & productID)
{
	return CTSM_ObjectCreator::createProduct(productID);
}

void CTsmObjectCreator::clearPlantBackup()
{
	// ToDo: Add your specialized code here
	
	static_cast<void>(0);
}

CPlant* CTsmObjectCreator::restorePlant()
{
	// ToDo: Add your specialized code here
	
	return static_cast<CPlant*>(0);
}

