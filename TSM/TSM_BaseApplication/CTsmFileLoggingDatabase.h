// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTSMFILELOGGINGDATABASE_410A3ED0024C_INCLUDED
#define _INC_CTSMFILELOGGINGDATABASE_410A3ED0024C_INCLUDED

#include "IDatabase.h"
#include <fstream>

class CTsmFileLoggingDatabase 
: public IDatabase
{
private:

public:
	//Protocols the adding of a new schedule item in the 
	//database.
	virtual void addScheduleItem(const CObjectID & eventPointID, const CObjectID & productID, bool isCheckIn);

	virtual ~CTsmFileLoggingDatabase();

	std::string getFileDbName();

  std::string getFileDbName(const std::string& TaskName);

	CTsmFileLoggingDatabase();

  CTsmFileLoggingDatabase(std::string TaskName);

	//Protocols a plant state transition depending on an 
	//incoming event and the current plant state.
	virtual void protocolPlantStateTransition(const CEventID & eventID, const CProcessStatusID & currentPlantState, const CProcessStatusID & nextPlantState);

	//Protocols the information about a product state 
	//transition. This function has to be overwritten to add 
	//database-specific behaviour to the model.
	virtual void protocolProductStateTransition(const CObjectID & productID, const CEventID & eventID, const CProcessStatusID & currentProductState, const CProcessStatusID & currentPlantState, const CProcessStatusID & newProductState);

protected:
	std::ofstream m_fstream;

	std::string m_fileDbName;

};

#endif /* _INC_CTSMFILELOGGINGDATABASE_410A3ED0024C_INCLUDED */
