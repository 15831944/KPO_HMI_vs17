// Copyright (C) 2006 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLF_TELEGRAMHANDLER_4582AA150368_INCLUDED
#define _INC_CLF_TELEGRAMHANDLER_4582AA150368_INCLUDED

#include <string>
#include "CDH_IN_Task.h"
#include "CTelegram_Handler.h"
#include "CDataConversion.h"

#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"
#include "Telcom_in_s.hh"

#include "CGC_SourceContainer.h"
#include "CGC_Charge_Dest_Container.h"
#include "CGC_Recipe_L1Container.h"
#include "CGC_Plantgroup_Container.h"

#include "CGT_MAT_PURP.h"
#include "CGCL_STIRR_INT.h"
#include "CGT_PARAM.h"
#include "CPD_MAT_AVAIL.h"
#include "CPP_ORDER.h"
#include "CPP_HEAT.h"
#include "CPP_HEAT_PLANT.h"
#include "CREPORT_MOTOR_ENTRY.h";
#include "CPD_HEAT_DATA.h"

class CLF_TelegramHandler 
: public CTelegram_Handler
{
public:
	CLF_TelegramHandler();

	virtual ~CLF_TelegramHandler();

	virtual bool doOnComplete(const std::string& Key, const std::string& TlgName);

  void handleTelegram(const std::string& Key, const std::string& TlgName);
	void handleEventLog(const string& Message,const std::string& HeatID,const std::string& TreatID,const std::string& PlantID,const std::string& DataKey); //sankar

protected:
  CGC_Plantgroup_Container*  m_pGC_Plantgroup_Container;
  CGC_Charge_Dest_Container* m_pGC_Charge_Dest_Container;
  CGC_SourceContainer*       m_pGC_SourceContainer;
  CGC_Recipe_L1Container*    m_pGC_Recipe_L1Container;
  CGCL_STIRR_INT*            m_pGCL_STIRR_INT;
  CGT_MAT_PURP*              m_pGT_MAT_PURP;
  CGT_PARAM*	               m_pGT_PARAM;
  CPD_MAT_AVAIL*             m_pPD_MAT_AVAIL;
  CPP_ORDER*                 m_pPP_ORDER;
  CPP_HEAT*                  m_pPP_HEAT;
  CPP_HEAT_PLANT*            m_pPP_HEAT_PLANT; 
	CREPORT_MOTOR_ENTRY*       m_pREPORT_MOTOR_ENTRY;
	CPD_HEAT_DATA*             m_pPD_HEAT_DATA;

private:

  void SendEventMessage(const std::string& Key, 
                        const std::string& TlgName,
                        const std::string& DataKey,
                        const std::string& PlantId,
                        const std::string& PlantLocation,
                        const std::string& HeatId,
                        const std::string& TreatId,
                        const std::string& OrderID,
                        bool isPlantEvent);

  bool DoProcessLFL201WatchDog(const std::string& Key, const std::string& TlgName);

  bool DoProcessLFL203HeatAnnouncement(const std::string& Key, const std::string& TlgName);

  bool DoProcessLFL204HeatStart(const std::string& Key, const std::string& TlgName);

  bool DoProcessLFL205HeatEnd(const std::string& Key, const std::string& TlgName);

  bool DoProcessLFL206HeatCancel(const std::string& Key, const std::string& TlgName);

  bool DoProcessLFL209SampTaken(const std::string& Key, const std::string& TlgName);

  bool DoProcessLFL211TempTaken(const std::string& Key, const std::string& TlgName);

  bool DoProcessLFL212AimTemperature(const std::string& Key, const std::string& TlgName);

  bool DoProcessLFL213AimDepartureTime(const std::string& Key, const std::string& TlgName);
  
  bool DoProcessLFL217DelayStatus(const std::string& Key, const std::string& TlgName);
  
  bool DoProcessLFL220CompMode(const std::string& Key, const std::string& TlgName);

  bool DoProcessLFL221FurnStatus(const std::string& Key, const std::string& TlgName);

  bool DoProcessLFL222ElecStatus(const std::string& Key, const std::string& TlgName);

  bool DoProcessLFL223ElecActVal(const std::string& Key, const std::string& TlgName);

  bool DoProcessLFL224BottomStirringStatus(const std::string& Key, const std::string& TlgName);

  bool DoProcessLFL225EmergencyLanceStirringStatus(const std::string& Key, const std::string& TlgName);

  bool DoProcessLFL226ActualStirringValues(const std::string& Key, const std::string& TlgName);

  bool DoProcessLFL230CoolingWater(const std::string& Key, const std::string& TlgName); 

  bool DoProcessLFL240Level1lParam(const std::string& Key, const std::string& TlgName);

  bool DoProcessLFL260MatHandReport(const std::string& Key, const std::string& TlgName);

  bool DoProcessLFL261MatAvailibilty(const std::string& Key, const std::string& TlgName);

  bool DoProcessLFL270LiqMatReport(const std::string& Key, const std::string& TlgName);

  bool DoProcessLFL281TreamentSteps(const std::string& Key, const std::string& TlgName);

  bool DoProcessMotorMaintenance(const std::string& Key, const std::string& TlgName);
  bool updateMotorData(long MotorID,long PlantNo, long MotorStrart);

  // DH_IN_LF PATTERN IMPLEMENTATION 
  bool DoProcessTlgName(const std::string& Key, const std::string& TlgName);
};

#endif /* _INC_CLF_TELEGRAMHANDLER_4582AA150368_INCLUDED */
