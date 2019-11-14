// Copyright (C) 2011 SMS Siemag AG Germany

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLAB_EVENTHANDLER_4582BED401AA_INCLUDED
#define _INC_CLAB_EVENTHANDLER_4582BED401AA_INCLUDED

#include "iDM_Interface_s.hh"
#include "CDH_EventHandler.h"
#include "CDH_OUT_Telcom_Impl.h"
#include "CDateTime.h"

class CLab_EventHandler 
: public CDH_EventHandler
{
public:
	virtual bool handleEvent(CEventMessage& evMessage);

	CLab_EventHandler( );

	virtual ~CLab_EventHandler();
private:
  void SendEventMessage(const std::string& TlgName, const std::string& DataKey, const std::string& PlantID, const std::string& HeatID, const std::string& TreatID, const std::string& OrderID);

protected:
  bool CLab_EventHandler::provideData_SteelSampleTakenEAF(CEventMessage &Event);
  bool CLab_EventHandler::provideData_SteelSampleTakenLF(CEventMessage &Event);
  bool CLab_EventHandler::provideData_SteelSampleTakenAOD(CEventMessage &Event);
  bool CLab_EventHandler::provideData_SlagSampleTakenEAF(CEventMessage &Event);
  bool CLab_EventHandler::provideData_SlagSampleTakenLF(CEventMessage &Event);
  bool CLab_EventHandler::provideData_SlagSampleTakenAOD(CEventMessage &Event);
  bool CLab_EventHandler::provideData_SMCLAB02SteelSampleTaken(CEventMessage &Event);
  void getSteelAnalysisStream(DEF::seqString& SteelAnalysisDB);
  void getSlagAnalysisStream(DEF::seqString& SlagAnalysisDB);
  
  DM::iDM_Interface_var m_pDM_Interface;
  CSMC_DataProvider_Impl*   m_pTelcom_Interface;
  DM::iDM_Interface_var m_pDM_InterfaceProduct;
};

#endif
