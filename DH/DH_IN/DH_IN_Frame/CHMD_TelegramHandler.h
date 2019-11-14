// Copyright (C) 2006 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHMD_TELEGRAMHANDLER_4582AA0701A6_INCLUDED
#define _INC_CHMD_TELEGRAMHANDLER_4582AA0701A6_INCLUDED

#include <string>
#include "CTelegram_Handler.h"

#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"
#include "Telcom_in_s.hh"

#include "CTelegram_Adapter.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CDH_IN_Task.h"

#include "CPP_HEAT.h"
#include "CGC_SourceContainer.h"
#include "CGC_Charge_Dest_Container.h"
#include "CGC_Recipe_L1Container.h"
#include "CGC_Plantgroup_Container.h"
#include "CGC_SAMPLELOC.h"
#include "CGT_MAT_PURP.h"
#include "DEF_GC_MEASUREMENT_TYPE.h"
#include "DEF_GT_PURP.h"
#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_LADLE_TYPE.h"
#include "CDataConversion.h"
#include "CREPORT_MOTOR_ENTRY.h"

#include "CPP_HM.h"
#include "CPD_HOT_METAL.h"
#include "CPD_SAMPLE_REF.h"

	

class CHMD_TelegramHandler : public CTelegram_Handler
{
public:
	//##ModelId=4582CF6703C9
	CHMD_TelegramHandler();

	//##ModelId=4582CF68028B
	virtual ~CHMD_TelegramHandler();

	//##ModelId=4586906D02AE
	virtual bool doOnComplete(const string& Key, const string& TlgName);
	void handleTelegram(const string& Key, const string& TlgName);
	void handleEventLog(const string& message,const std::string& HeatID,const std::string& TreatID,const std::string& PlantID,const std::string& DataKey); //sankar
	bool updateMotorData(long MotorID,long PlantNo, long MotorStrart);
	bool DoAutoHeatScheduleCreation(const std::string& HM_ID);

private:
	std::string m_EventMessageString;
	std::string m_Heat;
	std::string m_Treat;
	std::string m_DataKey;
	std::string m_PlantID;
  std::string OrderID;


protected:
	CGC_SourceContainer       * pGC_Source;
	CGT_MAT_PURP              * pGT_MAT_PURP;
	CGC_Plantgroup_Container  * m_pGC_Plantgroup_Container;
  CGC_Charge_Dest_Container * m_pGC_Charge_Dest;
  CGC_Recipe_L1Container    * m_pGC_Recipe_L1;
  CPP_HEAT                  * m_pPP_Heat;
	CGC_SAMPLELOC             * m_pGC_SampleLoc;
	
	CREPORT_MOTOR_ENTRY       * m_pREPORT_MOTOR_ENTRY;
	CPP_HM                    * m_pPP_HM;
	CPD_HOT_METAL             * m_pPD_HOT_METAL;
	CPD_SAMPLE_REF            * m_pPD_SAMPLE_REF;

};
#endif /* _INC_CHMD_TELEGRAMHANDLER_4582AA0701A6_INCLUDED */
