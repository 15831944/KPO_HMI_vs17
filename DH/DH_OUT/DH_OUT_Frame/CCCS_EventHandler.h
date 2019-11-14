// Copyright (C) 2010 SMS Demag AG Germany

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CCCS_EVENTHANDLER_4582BEA7000D_INCLUDED
#define _INC_CCCS_EVENTHANDLER_4582BEA7000D_INCLUDED

#include "iDM_Interface_s.hh"
#include "CDH_EventHandler.h"
#include "CDH_OUT_Telcom_Impl.h"

class CPP_HEAT;
class CPP_HEAT_PLANT;
class CPP_ORDER_SINGLE_AIMS;

class CPD_HEAT_REF;
class CPD_HEAT_DATA;
class CPDL_HEAT_DATA;
class CPDE_HEAT_DATA;

class CPD_SAMPLE;
class CPD_SAMPLE_ENTRY;
class CPD_SAMPLE_REF;

class CPD_LADLE;
class CPD_LADLE_LIFE_DATA;
class CPD_RECIPE;

class CGT_PARAM;
class CGC_HEAT_STATUS;
class CPD_HEAT_PLANT_REF;
class CPD_ACTION;

//##ModelId=4582BEA7000D
class CCCS_EventHandler 
: public CDH_EventHandler
{
public:
	//This hook operation would be called automatically by 
	//handleEvent( FRISEVENT &event) 
	//when an event is received. And this operation must be 
	//implemented by the user or client
	//in order to use it.
	//##ModelId=4587AAA80238
	virtual bool handleEvent(CEventMessage& evMessage);

	//##ModelId=4582C08F0093
	CCCS_EventHandler( );

	//##ModelId=4582C08F024B
	virtual ~CCCS_EventHandler();

  /************************************************************************/
  /* Add by Zhu Xinhong for Severskij
  */
  //##ModelId=45E6D6BC026A
  DM::iDM_Interface_var  m_pDM_Interface;
  //##ModelId=45E6D6BC0273
  CSMC_DataProvider_Impl* m_pTelcom_Interface;

	bool provideData_SteelAnalysisData(CEventMessage &Event); 
	bool provideData_SlagAnalysisData(CEventMessage &Event); 
	

	bool provideData_EstimatedLadleArrivalTime(CEventMessage &Event); 
	bool provideData_HeatData(CEventMessage &Event); 
	
private:

  CPP_HEAT              * m_pPP_HEAT;
  CPP_HEAT_PLANT        * m_pPP_HEAT_PLANT;
  CPP_ORDER_SINGLE_AIMS * m_pPP_ORDER_SINGLE_AIMS;

  CPD_HEAT_REF        * m_pPD_HEAT_REF;
  CPD_HEAT_DATA       * m_pPD_HEAT_DATA;
  CPDE_HEAT_DATA      * m_pPDE_HEAT_DATA;
  CPDL_HEAT_DATA      * m_pPDL_HEAT_DATA;

  CPD_SAMPLE          * m_pPD_SAMPLE;
  CPD_SAMPLE_REF      * m_pPD_SAMPLE_REF;

  CPD_LADLE           * m_pPD_LADLE;
  CPD_SAMPLE_ENTRY    * m_pPD_SAMPLE_ENTRY;

  CPD_LADLE_LIFE_DATA * m_pPD_LADLE_LIFE_DATA;
  CPD_RECIPE          * m_pPD_RECIPE;

  CGT_PARAM           * m_pGT_PARAM;
	CGC_HEAT_STATUS     * m_pGC_HEAT_STATUS;
	CPD_HEAT_PLANT_REF  * m_pPD_HEAT_PLANT_REF;
	CPD_ACTION          * m_pPD_ACTION;

  /************************************************************************/

};

#endif /* _INC_CCCS_EVENTHANDLER_4582BEA7000D_INCLUDED */
