// Copyright (C) 2006 SMS Demag AG Germany
#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAF_EVENTHANDLER_4582BE930362_INCLUDED
#define _INC_CEAF_EVENTHANDLER_4582BE930362_INCLUDED

#include "iDM_Interface_s.hh"
#include "CDH_EventHandler.h"
#include "CDH_OUT_Telcom_Impl.h"
#include "CDH_OUT_Task.h"

class CDH_L1_EAF_OUT_Telcom_Impl;
class CGC_Recipe_L1Container;
class CGC_SourceContainer;
class CGC_Plant_Container;

class CGC_PHASE;
class CGT_MAT_PURP;
class CGT_MAT;
class CGTE_PP_FLAME_PROFILE;
class CGCE_INJECTION;

class CPP_HEAT;                      
class CPP_HEAT_PLANT;

class CPD_HEAT_DATA;
class CPD_HEAT_DATA_PRODPRAC;        
class CPD_RECIPE;                    
class CPD_SCRAP_CONTAINER_ORDER;
class CPD_SCRAP_CONTAINER_ORDER_ENTRY;         
class CPD_SCRAP_CONTAINER;
class CPD_SCRAP_CONTAINER_ENTRY;         
class CPD_HOT_METAL;
class CPD_HOT_METAL_ORDER;
class CPD_HOTHEEL;


class CEAF_EventHandler 
  : public CDH_EventHandler
{
public:
  //This hook operation would be called automatically by 
  //handleEvent( FRISEVENT &event) 
  //when an event is received. And this operation must be 
  //implemented by the user or client
  //in order to use it.
    virtual bool handleEvent(CEventMessage& evMessage);
  
  CEAF_EventHandler( );
  
  virtual ~CEAF_EventHandler();

private:
  void SendEventMessage(const std::string& TlgName, const std::string& DataKey, const std::string& PlantID, const std::string& HeatID, const std::string& TreatID, const std::string& OrderID);
  
  long GetProdPracNo(std::string &HeatID,std::string &TreatID,const std::string& PlantID,const std::string& DESCR_PP );
  
  long GetL1PhaseType(std::string& PhaseName);

  long GetL1PhaseNo(std::string& PhaseName,std::string& Plant,long PhaseNo);


protected:
 
  bool provideData_L2EA03HeatAnnouncement(CEventMessage& Event, long UpdateFlag = 0);  	
  bool provideData_L2EA05BurnerPattern(CEventMessage& Event);	
  bool provideData_L2EA06HeatCancel(CEventMessage& Event); 	
  bool provideData_L2EA07CompMode(CEventMessage& Event); 
  bool provideData_L2EA23ReleaseElectrodes(CEventMessage& Event);
  bool provideData_L2EA32CarbonInjPattern(CEventMessage& Event);
  bool provideData_L2EA40ProcessPattern(CEventMessage& Event);
  bool provideData_L2EA41ProcessValues(CEventMessage& Event);
  bool provideData_L2EA70MatHandling(CEventMessage& Event);
  bool provideData_L2EA71MatAvailRequest(CEventMessage& Event); 	
  bool provideData_L2EA72StatusRequest(CEventMessage& Event); 

  bool provideData_L2SY92ScrapLoadInstruction(CEventMessage& Event);
  bool provideData_L2SY95ScrapMat(CEventMessage& Event);
  
  
  // DH_OUT_EAF PATTERN ORA IMPLEMENTATION 
  bool provideData_L2EA40_PROC_PATT(CEventMessage& Event);
  bool provideData_L2EA41_PROC_VALUES(CEventMessage& Event);
  bool provideData_L2EA70_MAT_HANDL(CEventMessage& Event);

  bool provideData_L2SY92_SCRAP_LOAD(CEventMessage& Event);
  bool provideData_L2SY95_SCRAP_MAT(CEventMessage& Event);

	bool provideData_L2EA20VoltageTap(CEventMessage& Event);

  // DH_OUT_EAF PATTERN IMPLEMENTATION 
  //bool provideData_TlgName(CEventMessage& Event);

private:
  CGC_SourceContainer *             m_pGC_SourceContainer;
  CGC_Recipe_L1Container *          m_pGC_Recipe_L1Container;

  CGC_PHASE  *                      m_pGC_PHASE;
  CGT_MAT_PURP *                    m_pGT_MAT_PURP;
  CGT_MAT *                         m_pGT_MAT;

  CGTE_PP_FLAME_PROFILE *           m_pGTE_PP_FLAME_PROFILE;
  CGCE_INJECTION *                  m_pGCE_INJECTION;

  CPP_HEAT *                        m_pPP_HEAT;
  CPP_HEAT_PLANT *                  m_pPP_HEAT_PLANT;

  CPD_HEAT_DATA*                    m_pPD_HEAT_DATA;
  CPD_HEAT_DATA_PRODPRAC*           m_pPD_HEAT_DATA_PRODPRAC;
  CPD_RECIPE*                       m_pPD_RECIPE;

  CPD_SCRAP_CONTAINER_ORDER*        m_pPD_SCRAP_CONTAINER_ORDER;
  CPD_SCRAP_CONTAINER_ORDER_ENTRY*  m_pPD_SCRAP_CONTAINER_ORDER_ENTRY;
  CPD_SCRAP_CONTAINER*              m_pPD_SCRAP_CONTAINER;
  CPD_SCRAP_CONTAINER_ENTRY*        m_pPD_SCRAP_CONTAINER_ENTRY;

  CPD_HOT_METAL*                    m_pPD_HOT_METAL;
  CPD_HOT_METAL_ORDER*              m_pPD_HOT_METAL_ORDER;
  CPD_HOTHEEL *                     m_pPD_HOTHEEL;

  bool UseOracleTransfer;

};
#endif /* _INC_CEAF_EVENTHANDLER_4582BE930362_INCLUDED */