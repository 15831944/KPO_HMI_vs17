// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_EVENTLOGHANDLER_420B493301F0_INCLUDED
#define _INC_CDM_EVENTLOGHANDLER_420B493301F0_INCLUDED

#include "CEventMessage.h"
#include "iSMC_DataDefinitions_s.hh"

#include "CDM_DataInterface_Impl.h"
#include "CDM_ProductManagementInterface_Impl.h"
#include "CDM_PlantManagementInterface_Impl.h"


class CDM_EventLogHandler 
{
protected:
	CDM_DataInterface_Impl* m_pDataInterface;
	CDM_ProductManagementInterface_Impl* m_pProductManagementInterface;

	CDM_PlantManagementInterface_Impl* m_pPlantManagementInterface;

public:
	virtual std::string getProcessState(const std::string& ID) = 0;

	virtual std::string getExternalHeatID(const std::string& ID) = 0;

	virtual std::string getExternalTreatID(const std::string& ID) = 0;

	virtual ~CDM_EventLogHandler();

	CDM_EventLogHandler();

	virtual bool EventLog(CEventMessage &Event) = 0;

};

#endif /* _INC_CDM_EVENTLOGHANDLER_420B493301F0_INCLUDED */
