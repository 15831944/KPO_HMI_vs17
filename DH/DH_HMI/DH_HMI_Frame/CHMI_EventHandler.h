// Copyright (C) 2006 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHMI_EVENTHANDLER_4152A1FD016D_INCLUDED
#define _INC_CHMI_EVENTHANDLER_4152A1FD016D_INCLUDED

#include "CDH_EventHandler.h"

#include "CGC_Plant_Container.h"
#include "CPP_HEAT.h"
#include "CPD_HEAT_PLANT_REF.h"
#include "CEventMessage.h"
#include "CPP_HM.h"

//##ModelId=4586730301AB
class CHMI_EventHandler 
  : public CDH_EventHandler
{
public:
	//##ModelId=4586739B00EC
	CHMI_EventHandler();

	//##ModelId=4586739B010A
	virtual ~CHMI_EventHandler();

	//##ModelId=4586739B013C
  virtual bool changeMissingEventData(CEventMessage& Event);
  virtual bool changeMissingEventDataHMD(CEventMessage& Event);//SARS

	virtual bool copyDMData(CEventMessage& Event, std::vector<std::string>& NameList, const std::string& Key = "");

	virtual bool copyDMData(CEventMessage& Event, const std::string& Name = "", const std::string& Key = "");

  std::vector<std::string> getRequestedDataList(const std::string& Key, const std::string& Name);

  // to get order
	//##ModelId=4586739B01DD
  CPP_HEAT* m_pPP_HEAT;
	CPP_HM* m_pPP_HM;

  // to get external heat, treat
  CPD_HEAT_PLANT_REF* m_pPD_HEAT_PLANT_REF;

	CGC_Plant_Container* m_pGC_Plant_Container;


};

#endif /* _INC_CHMI_EVENTHANDLER_4152A1FD016D_INCLUDED */
