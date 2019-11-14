// Copyright (C) 2006 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAF_TELEGRAMHANDLER_4582CCDA0055_INCLUDED
#define _INC_CEAF_TELEGRAMHANDLER_4582CCDA0055_INCLUDED

class CGC_Recipe_L1Container;
class CGC_SourceContainer;
class CGC_Charge_Dest_Container;
class CGC_Plantgroup_Container;
class CGC_PHASE;
class CGC_COOLWATER;
class CGCE_BURNER;
class CGCE_InjectionContainer;
class CGT_MAT;
class CGT_MAT_PURP;
class CGT_PARAM;
class CGTE_PP_FLAME_PROFILE;

class CPDE_HEAT_DATA;
class CPDE_CYCL_MEAS_DATA;

class CPP_ORDER;
class CPP_ORDER_SINGLE_AIMS;
class CPP_HEAT;
class CPP_HEAT_PLANT;
class CPD_HEAT_REF;
class CHeatStatusContainer;

class CPD_ACTION;
class CPD_MAT_AVAIL;
class CPD_COOLWATER;
class CPD_HEAT_DATA;
class CPD_RECIPE;
class CPD_RECIPE_ENTRY;
class CPD_SCRAP_CONTAINER;
class CPD_SCRAP_CONTAINER_ENTRY;
class CPD_SCRAP_CONTAINER_ORDER;
class CPD_SCRAP_CONTAINER_ORDER_ENTRY;
class CREPORT_MOTOR_ENTRY;
class CPD_PLANTSTATUS_PLANT;
class CPD_HEAT_DATA_LIQADD;

class CPD_LADLE;
class CPDH_HM_DATA;
class CPD_HOT_METAL;
class CPDE_HEAT_DATA_MELT;


#include <string>
#include "CTelegram_Handler.h"

//##ModelId=4582CCDA0055
class CEAF_TelegramHandler : public CTelegram_Handler
{
public:
  //##ModelId=4582D0000066
  CEAF_TelegramHandler();

  //##ModelId=4582D0040115
  virtual ~CEAF_TelegramHandler();

  //##ModelId=4586921F00E1
  virtual bool doOnComplete(const std::string& Key, const std::string& TlgName);
  //virtual bool doOnCompleteBAK(const std::string& Key, const std::string& TlgName);
	void handleEventLog(const string& Message,const std::string& HeatID,const std::string& TreatID,const std::string& PlantID,const std::string& DataKey); //sankar


private:
  CGC_Recipe_L1Container*     m_pGC_Recipe_L1;
  CGC_SourceContainer*        m_pGC_SourceContainer;
  CGC_Charge_Dest_Container*  m_pGC_Charge_Dest_Container;
  CGC_Recipe_L1Container*     m_pGC_Recipe_L1Container;
  CGC_Plantgroup_Container*   m_pGC_Plantgroup_Container;
  CGC_PHASE*                  m_pGC_PHASE;
  CGC_COOLWATER*              m_pGC_COOLWATER;
  CGCE_BURNER*                m_pGCE_BURNER;
  CGCE_InjectionContainer*    m_pGCE_InjectionContainer;
  CGT_MAT*                    m_pGT_MAT;
  CGT_MAT_PURP*               m_pGT_MAT_PURP;
  CGT_PARAM*                  m_pGT_PARAM;
  CGTE_PP_FLAME_PROFILE*      m_pGTE_PP_FLAME_PROFILE;

  CPDE_CYCL_MEAS_DATA*        m_pPDE_CYCL_MEAS_DATA;
  CPDE_HEAT_DATA*             m_pPDE_HEAT_DATA;

  CPP_ORDER*                  m_pPP_ORDER;
  CPP_ORDER_SINGLE_AIMS*      m_pPP_ORDER_SINGLE_AIMS;
  CPP_HEAT*                   m_pPP_HEAT;
  CPP_HEAT_PLANT*             m_pPP_HEAT_PLANT;

  CPD_MAT_AVAIL*              m_pPD_MAT_AVAIL;
  CPD_ACTION*                 m_pPD_ACTION;
  CPD_COOLWATER*              m_pPD_COOLWATER;
  CPD_HEAT_DATA*              m_pPD_HEAT_DATA;
  CPD_RECIPE*                 m_pPD_RECIPE;
  CPD_RECIPE_ENTRY*           m_pPD_RECIPE_ENTRY;

	CREPORT_MOTOR_ENTRY*        m_pREPORT_MOTOR_ENTRY;
	
	CPD_LADLE*                  m_pPD_LADLE;
	CPD_PLANTSTATUS_PLANT*      m_pPD_PLANTSTATUS_PLANT;
	CPD_HEAT_REF*               m_pPD_HEAT_REF;
	CHeatStatusContainer*       m_pHeatStatusContainer;
	CPD_SCRAP_CONTAINER_ORDER* m_pPD_SCRAP_CONTAINER_ORDER;
	CPD_HEAT_DATA_LIQADD*      m_pPD_HEAT_DATA_LIQADD;

	CPDH_HM_DATA*              m_pPDH_HM_DATA;
	CPD_HOT_METAL*             m_pPD_HOT_METAL;
	CPDE_HEAT_DATA_MELT*       m_pPDE_HEAT_DATA_MELT;


private:
  void SendEventMessage(const std::string& Key, 
                        const std::string& TlgName,
                        const std::string& DataKey,
                        const std::string& PlantId,
                        const std::string& PlantLocation,
                        const std::string& HeatNo,
                        const std::string& TreatId,
                        const std::string& OrderID,
                        bool isPlantEvent);

  bool DoProcessEAL200ACK(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL201WatchDog(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL203HeatAnnouncement(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL204HeatStart(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL205HeatEnd(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL206HeatCancel(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL207Tapping(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL209SampTaken(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL211TempTaken(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL214TapLadleData(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL215BasketHMDischarged(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL216DeslagStatus(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL220CompMode(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL221FurnStatus(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL222ElecStatus(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL223ElecActVal(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL224InjectionMatAvail(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL225InjectionMatStatus(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL226InjectionMatActVal(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL227BurnerGasAvail(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL228BurnerStatus(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL229BurnerActVal(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL233CoolingWater(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL234VesselStirrStatus(const string& Key, const string& TlgName);

  bool DoProcessEAL235VesselStirrCons(const string& Key, const string& TlgName);

  bool DoProcessEAL236LadleStirrStatus(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL237LadleStirrCons(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL240EAFFlameProfile(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL241Level1Param(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL250WasteGas(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL260MatHandReport(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL261MatAvailibilty(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL262MaterialFeedingSystem(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL263MaterialFeedingStatus(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL270LiqMatReport(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAL280PhaseReport(const std::string& Key, const std::string& TlgName);

  bool DoProcessSYL293ScrapLoadingInstructionRequest(const std::string& Key, const std::string& TlgName);

  bool DoProcessSYL292ScrapLoadingResults(const std::string& Key, const std::string& TlgName);

  bool DoProcessSYL295ScrapMaterialRequest(const std::string& Key, const std::string& TlgName);

  bool DoProcessEAFL217DelayStatus(const std::string& Key, const std::string& TlgName); //SARS
	

  bool DoProcessMotorMaintenance(const std::string& Key, const std::string& TlgName);
  bool updateMotorData(long MotorID,long PlantNo, long MotorStrart);

  //DH_IN_EAF PATTERN IMPLEMENTATION 
  bool DoProcessTlgName(const std::string& Key, const std::string& TlgName);
	bool DoAutoHeatScheduleCreation();
	int  getNextChargeNo(const std::string& HeatID,const std::string& TreatID,const std::string& ChargeName);
	int  getNextLadleNo();
	bool  isRefiningPhaseStart(const std::string& HeatID,const std::string& TreatID);
	

	//for testing
	long TempCount;              
  std::string TempHeatId;
	std::string HeatIdRefiningPhase;
};

#endif /* _INC_CEAF_TELEGRAMHANDLER_4582CCDA0055_INCLUDED */
