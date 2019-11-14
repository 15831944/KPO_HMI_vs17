// Copyright (C) 2006 SMS Demag AG Germany

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHMD_EVENTHANDLER_4582BE4F0399_INCLUDED
#define _INC_CHMD_EVENTHANDLER_4582BE4F0399_INCLUDED

#include "CDH_EventHandler.h"
#include "iDM_Interface_s.hh"
#include "CGT_MAT_PURP.h"
//##ModelId=4582BE4F0399

class CHeatDataConverter;
class CGC_Plant_Container;
class CPD_HEATDATA;
class CPP_HEAT;
class CPP_HEAT_PLANT;
class CPD_LADLE ;
class CPDH_HEAT_DATA ;
class CPD_PLANTSTATUS;
class CPDH_HM_DATA;
class CGC_Plantgroup_Container;
class CGT_MAT_PURP;

class CHMD_EventHandler 
: public CDH_EventHandler
{
public:
	//This hook operation would be called automatically by 
	//handleEvent( FRISEVENT &event) 
	//when an event is received. And this operation must be 
	//implemented by the user or client
	//in order to use it.
	//##ModelId=4587AA8300F3
	virtual bool handleEvent(CEventMessage& evMessage);

	//##ModelId=4582C01C025D
	CHMD_EventHandler( );

	//##ModelId=4582C01D013C
	virtual ~CHMD_EventHandler();

private:
  CHeatDataConverter  * m_pHeatDataConverter;
  CGC_Plant_Container * m_pPlantIdConverter;
  CPD_HEATDATA        * pPD_HEATDATA;
  CPD_LADLE           * pPD_LADLE;
  CPP_HEAT_PLANT      * pPP_HEAT_PLANT;
  CPP_HEAT            * pPP_HEAT;
  CGT_MAT_PURP        * pGT_Mat_Purp;
  CPDH_HEAT_DATA      * pPDH_HEAT_DATA;
	CPD_PLANTSTATUS			* pPD_PlantStatus;
	CPDH_HM_DATA				* pPDH_HM_Data;
	CGC_Plantgroup_Container * m_pGC_Plantgroup_Container;
	CGT_MAT_PURP      * m_pGT_MAT_PURP;

  bool   provideData_L2HM03     (CEventMessage& Event); 
  bool   provideData_L2HM06     (CEventMessage& Event); 
  bool   provideData_L2HM07     (CEventMessage& Event); 
  bool   provideData_L2HM30     (CEventMessage& Event); 
  bool   provideData_L2HM25     (CEventMessage& Event); 
  bool   provideData_L2HM71     (CEventMessage& Event); 
  bool   provideData_L2HM72     (CEventMessage& Event); 

  CSMC_DataProvider_Impl * m_pTelcom_Interface;
  std::string m_SenderName;
  std::string m_DestinationName;
  DM::iDM_Interface_var m_pDM_Interface;

  const char *AppString;
	bool UseOracleTransfer;
};

#endif /* _INC_CHMD_EVENTHANDLER_4582BE4F0399_INCLUDED */
