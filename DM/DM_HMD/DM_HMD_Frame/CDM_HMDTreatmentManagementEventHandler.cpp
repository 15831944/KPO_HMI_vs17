// Copyright (C) 2007 SMS Demag AG

#include "CDM_HMDTask.h"
#include "CDM_HMDTreatmentManagementEventHandler.h"
#include "CPP_HEAT.h"
#include "CPP_HEAT_PLANT.h"
#include "CGC_Plant_Container.h"
#include "CPP_ORDER.h"
#include "CGT_PARAM.h"
#include "CHeatID.h"
//#include "DEF_GC_HEAT_STAT.h"
#include "CDataConversion.h"

CDM_HMDTreatmentManagementEventHandler::CDM_HMDTreatmentManagementEventHandler()
: CDM_TreatmentManagementEventHandler( CDM_HMDTask::getInstance() )
, m_pConnection(0)
{
  //try
  //{
  //  m_pDMTask->handleDBConnectionError();
  //  m_pConnection = m_pDMTask->getConnection();

  //  if (!m_pConnection)
  //  {
  //    log("ERROR: CDM_HMDTreatmentManagementEventHandler: No connection from CDM_Task!");
  //  }
  //}
  //catch(...) 
  //{
  //  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  //  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  //  pEventLog->EL_ExceptionCaught(sMessage,"", "CDM_HMDTreatmentManagementEventHandler","");
  //  throw;
  //}
}

CDM_HMDTreatmentManagementEventHandler::~CDM_HMDTreatmentManagementEventHandler()
{
}

bool CDM_HMDTreatmentManagementEventHandler::handleEvent(CEventMessage& evMessage)
{
	HANDLE_EVENT(HMDHeatAnnouncement);		
  HANDLE_EVENT(HMDHeatDeparture);     
  HANDLE_EVENT(HMDHeatCancellation);
  HANDLE_EVENT(HMDHeatStart);
  HANDLE_EVENT(HMDHeatEnd);
  HANDLE_EVENT(HMDHeatScheduleUpdate); 
  HANDLE_EVENT(HMDPlantStatus);
  HANDLE_EVENT(HMDDelayStatus);

  HANDLE_EVENT_DATA(HMDPlantStatusRequest);
  HANDLE_EVENT_DATA(HMDUpdateAimDepartureTime);
  //HANDLE_EVENT_DATA(HMDApplicationSystemRestart);

//	HANDLE_EVENT(HMDHeatAnnouncementOffline);
//  HANDLE_EVENT_DATA(HMDLevel1HeatReset);
//  HANDLE_EVENT_DATA(HMDEventReport);
//  HANDLE_EVENT_DATA(HMDProductionReport);
//  HANDLE_EVENT_DATA(HMDChangeAimData);
//  HANDLE_EVENT_DATA(HMDChangeProdPracPointerParameter);
//  HANDLE_EVENT_DATA(HMDChangeProdPracPointerRestriction);
//  HANDLE_EVENT_DATA(HMDGenerateTreatmentId);

	return false;
}

bool CDM_HMDTreatmentManagementEventHandler::doHMDHeatAnnouncement(CEventMessage& Event)
{
  cout << "************ SS>> in DM::doHMDHeatAnnouncement)" << endl;
  bool RetValue = false;
  copyDataEventData(Event);
  if (CDM_HMDDBManagerTask::getInstance()->getDBManager()->evHeatAnnouncement(Event))
  {
    RetValue = doHeatAnnouncement( Event );
    CDM_HMDDBManagerTask::getInstance()->getDBManager()->doHeatAnnouncement(Event);
  }
  cout << "************ SS<< out of DM::doHMDHeatAnnouncement)" << endl;

  return RetValue;
}

bool CDM_HMDTreatmentManagementEventHandler::doHMDHeatCancellation(CEventMessage& Event)
{
  bool RetValue = false;
  copyDataEventData(Event);
  if(CDM_HMDDBManagerTask::getInstance()->getDBManager()->evCancelHeat(Event))
    RetValue = doHeatCancellation( Event );
  
  return RetValue;
}

bool CDM_HMDTreatmentManagementEventHandler::doHMDHeatDeparture(CEventMessage& Event)
{
  //changePlantInformation
  //ProductManager->changeAssignedModel("")
  //ProductManager->changeSampleData
  //return doHeatDeparture( Event );
	bool RetValue = false;

  if (copyDataEventData(Event))
  {
    checkEventAssignment(Event);

    if(CDM_HMDDBManagerTask::getInstance()->getDBManager()->evHeatDeparture(Event))
    {
      RetValue = doHeatDeparture( Event );
    }

		//SARS : AutoDelay
		bool isDelay;
    if(CDM_HMDDBManagerTask::getInstance()->getDBManager()->AutomaticlyFillRelativeDelays(Event,true,isDelay))
    {
			if(isDelay)
			{
				Event.setMessage(HMD_EvMsg::evHMDDelayStatus);
				if(CDM_HMDDBManagerTask::getInstance()->getDBManager()->evDelayStatus(Event))
				{
					dispatchEvent(Event);
				}
			}
    }




		
  }
  return RetValue;
}

bool CDM_HMDTreatmentManagementEventHandler::doHMDHeatStart(CEventMessage& Event)
{
  //changeProductInformation	
  //changePlantInformation
  bool RetValue = false;
	if (copyDataEventData(Event))
  {
    checkEventAssignment(Event);

    if(CDM_HMDDBManagerTask::getInstance()->getDBManager()->evHeatStart(Event))
    {
      RetValue = doHeatStart( Event ); //SARS
    }
  }
  return RetValue;
}

bool CDM_HMDTreatmentManagementEventHandler::doHMDHeatEnd(CEventMessage& Event)
{
  //changeProductInformation	
  bool RetValue = false;

  if (copyDataEventData(Event))
  {
    checkEventAssignment(Event);

    if(CDM_HMDDBManagerTask::getInstance()->getDBManager()->evHeatEnd(Event))
    {
      RetValue = doHeatEnd( Event ); //SARS
    }

  }
  return RetValue;
}

bool CDM_HMDTreatmentManagementEventHandler::doHMDHeatScheduleUpdate(CEventMessage& Event)
{
  // try to update Event with assigend data (ProductID...)
  if ( checkEventAssignment(Event) )
  {
    if ( copyDataEventData(Event) )
    {
      // reaction of following processes is similar to 
      // "evHMDChangeAimData"
      Event.setMessage(HMD_EvMsg::evHMDChangeAimData);

      // send event to respective destinations
      dispatchEvent(Event);

    }
  }
	return true;
}

//ssbool CDM_HMDTreatmentManagementEventHandler::doHMDHeatAnnouncementOffline(CEventMessage& Event)
//ss{
//ss	return doHeatAnnouncementOffline( Event ); 
//ss}

bool CDM_HMDTreatmentManagementEventHandler::doHMDPlantStatus(CEventMessage& Event)
{
  if ( copyDataEventData(Event) )
  {
    // update Plant manager 
    if (m_pDMTask->getpPlantManager() )
    {
      m_pDMTask->getpPlantManager()->changePlantInformation(Event);
    }

    std::vector<std::string> Mess;
    m_pDMTask->getpPlantManager()->getAdditionallyMessages(Mess);
    // send events to respective destinations
    dispatchEvents(Event, Mess);
  }
	return true;
}

bool CDM_HMDTreatmentManagementEventHandler::doOnRemoveProduct(CEventMessage& Event, const std::string& ProductID)
{
  CEventMessage NewEvent(Event);

  NewEvent.setMessage(HMD_EvMsg::evHMDResetOfHeat);
  NewEvent.setProductID(ProductID);
  NewEvent.setDataKey(ProductID);

  return dispatchEvent(NewEvent);
}

bool CDM_HMDTreatmentManagementEventHandler::doOnUnknownProduct(CEventMessage& Event)
{
  // send event to tsm to add product and be able to pass all product events
  CEventMessage NewEvent(Event);

  NewEvent.setMessage(HMD_EvMsg::evHMDSetUpOfHeat);

  return dispatchEvent(NewEvent);
}



bool CDM_HMDTreatmentManagementEventHandler::doHMDDelayStatus(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if(CDM_HMDDBManagerTask::getInstance()->getDBManager()->evDelayStatus(Event))
  {
    RetValue = dispatchEvent(Event);
  }

  return RetValue;  
}

/*
bool CDM_HMDTreatmentManagementEventHandler::makeEntryInHeatSchedule(CEventMessage& Event)
{
  bool RetValue = true;
  std::string CustTapID = Event.getHeatID();
  std::string PlantID = Event.getPlantID();
  std::string DataKey = Event.getDataKey();

  //USAD ONLY FOR TEST
  //cCBS_StdInitBase::getInstance()->replaceWithEntry("DEFAULT_DATA","CustTapID",CustTapID);

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();

  try
  {
    CPP_HEAT_PLANT PP_Heat_Plant(m_pConnection);
    CPP_HEAT       PP_Heat(m_pConnection);
    CGC_Plant_Container PlantIdConverter(m_pConnection);
    CPP_ORDER      PP_Order(m_pConnection);
//SS    CPP_GRADE      PP_Grade(m_pConnection);
//SS    CPP_GRADE_ANL  PP_Grade_Anl(m_pConnection);
    CGT_PARAM      GT_Param(m_pConnection);
//SS    CPP_CREW_USER_ASSIGNMENT PP_Crew_User_Assignment(m_pConnection);
//SS    CPP_GRADE_PRODPRAC PP_Grade_Prodprac(m_pConnection);
//SS    CPP_GRADE_SINGLE_AIMS PP_Grade_Single_Aims(m_pConnection);

    bool        InsertAllowed = true;
    long        HeatStatOrder = 0; //SS DEF_GC_HEAT_STAT_NUM::Planned,
    long            PlantNo = PlantIdConverter.getPlantNo(PlantID); //SS
    std::string CustHeatID = CustTapID.substr((CustTapID.length() - 7), 7), //CustHeatId contains last 7 signs fo CustTapID
                CustTreatID = "H01", //there will be no retreatment on HMD
                HeatID,
                TreatID = "01",
                OrderID,
                HMDStdOrderID,
                ProductID,
                PlantName = PlantIdConverter.getPlantName(PlantID),
                DefaultOrdStatNo, 
                HMDSteelGrade,
                DefaultSteelGrade,
                MetalType = "HM",
                RouteCodePlan = PlantIdConverter.getRouteCodeID(PlantID); //,
//SS                UserCode = PP_Crew_User_Assignment.getActualUserCode(PlantName, PlantNo);
    CDateTime   StartTime, 
                EndTime, 
                Now;
    sDate       DepartTime;
    double      AimSteelConArc = 0.0,
                AimSulphur     = 0.0;


    //read default data from INI-File
    cCBS_StdInitBase::getInstance()->replaceWithEntry("DEFAULT_DATA", "HMDOrderID",    HMDStdOrderID);
    cCBS_StdInitBase::getInstance()->replaceWithEntry("DEFAULT_DATA", "DfltOrdStatNo", DefaultOrdStatNo);
    cCBS_StdInitBase::getInstance()->replaceWithEntry("DEFAULT_DATA", "HMDSteelGrade", DefaultSteelGrade);

    //get data from DH Interface
    std::string HMLadleNo = CIntfData::ToStdString(m_pDMTask->getpDH_Interface(Event.getSender())->getString(DataKey.c_str(), DATA::LadleNo));
    std::string CustCONHeatID = CIntfData::ToStdString(m_pDMTask->getpDH_Interface(Event.getSender())->getString(DataKey.c_str(), DATA::CustHeatID));
	AimSulphur = m_pDMTask->getpDH_Interface(Event.getSender())->getDouble(DataKey.c_str(), DATA::SulphurAim);
    DepartTime = m_pDMTask->getpDH_Interface(Event.getSender())->getDate(DataKey.c_str(), DATA::TreatEndAim);
    if (!(DepartTime == CDateTime::InvalidDate()))
    {
      EndTime.SetTime(DepartTime);
    }

    //check, if ladle should be assigned to ConArc heat
    if (!CustCONHeatID.empty() && CustCONHeatID != DEF::Inv_String)
    {
      if (PP_Heat.select(CustCONHeatID))
      {
        if (PP_Order.select(PP_Heat.getPRODORDERID(1)))
        {
          HMDSteelGrade = PP_Order.getSTEELGRADECODE(1);
//SS          AimSteelConArc = PP_Order.getAIMSTEEL_CONARC(1);
          OrderID = PP_Heat.getPRODORDERID(1);
        }
      }
    }
    else
    {
      OrderID = HMDStdOrderID;
      HMDSteelGrade = DefaultSteelGrade;
    }

    // fill PP_GEADE with a default gradecode, if it's missing and HMD heat is not connected to a ConArc heat
    //SS if (!PP_Grade.select(HMDSteelGrade))
    //SS {
    //SS   PP_Grade.setSTEELGRADECODE(HMDSteelGrade);
    //SS   PP_Grade.setSTEELGRADECODEDESC("Default steelgrade for HMD");
    //SS   PP_Grade.setSTEELGRADECODEDESC_C("Default steelgrade for HMD");
    //SS   PP_Grade.setREVTIME(Now);
    //SS   PP_Grade.setUSERCODE("HMD");
    //SS   PP_Grade.setLiqTemp(1500);

    //SS   if (PP_Grade.insert())
    //SS   {
    //SS     PP_Grade.commit();
    //SS   }
    //SS   else
    //SS   {
    //SS     PP_Grade.rollback();
    //SS     return false;
    //SS   }
    //SS }
    //-----------------------------------------------

    //set aim analysis to PP_Grade_Anl
    //SS if (GT_Param.select("DefltStartSulphurHMD", 0, CSMC_DBData::unspecLong, PlantName, PlantNo) && 
    //SS     (AimSulphur <= 0.0 || AimSulphur == DEF::Inv_Double))
    //SS {
    //SS   AimSulphur = CDataConversion::StringToDouble(GT_Param.getVALUE(1));
    //SS }
  
    //SS PP_Grade_Anl.setSTEELGRADECODE(HMDSteelGrade);
    //SS PP_Grade_Anl.setPLANT(PlantName);
    //SS PP_Grade_Anl.setAIMTYPE("Aim");
    //SS PP_Grade_Anl.setENAME("S");
    //SS PP_Grade_Anl.setANL(AimSulphur);

    //SS PP_Grade_Anl.cleanWhereStatement();
    //SS PP_Grade_Anl.addWhereClause("STEELGRADECODE", HMDSteelGrade);
    //SS PP_Grade_Anl.addWhereClause("PLANT", PlantName);
    //SS PP_Grade_Anl.addWhereClause("AIMTYPE", "Aim");
    //SS PP_Grade_Anl.addWhereClause("ENAME", "S");

    //SS if (PP_Grade_Anl.updateOrInsert())
    //SS {
    //SS   PP_Grade_Anl.commit();
    //SS }
    //SS else
    //SS {
    //SS   PP_Grade_Anl.rollback();
    //SS   return false;
    //SS }
    //-----------------------------------------------
    bool InsertGrade = true;
    // make a copy of any steelgrade with all practice pointers in it
    std::string TempSteelGrade = DEF::Inv_String;
    //SS if (!PP_Grade_Prodprac.select(DefaultSteelGrade, CSMC_DBData::unspecString))
    //SS {
    //SS   CPP_GRADE_PRODPRAC *pPP_Grade_Prodprac;
    //SS   pPP_Grade_Prodprac = new CPP_GRADE_PRODPRAC(m_pConnection);

    //SS   // select any steelgradecode
    //SS   if (pPP_Grade_Prodprac->select(CSMC_DBData::unspecString, DEF_DB_PLANT::CON))
    //SS   {
    //SS     TempSteelGrade = pPP_Grade_Prodprac->getSTEELGRADECODE(1);
    //SS     log(("Source steelgradecode = " + TempSteelGrade));
    //SS     // select all rows for selected steelgradecode
    //SS     pPP_Grade_Prodprac->select(TempSteelGrade, CSMC_DBData::unspecString);
    //SS     for (long i = 1; i <= pPP_Grade_Prodprac->getLastRow(); ++i)
    //SS     {
    //SS       PP_Grade_Prodprac.setSTEELGRADECODE(DefaultSteelGrade);
    //SS       PP_Grade_Prodprac.setColumnsFromTable(pPP_Grade_Prodprac, i);

    //SS       InsertGrade = InsertGrade && PP_Grade_Prodprac.insert();
    //SS     }

    //SS     if (InsertGrade)
    //SS       PP_Grade_Prodprac.commit();
    //SS     else
    //SS       PP_Grade_Prodprac.rollback();
    //SS   }
    //SS   delete pPP_Grade_Prodprac;
    //SS }

    //SS  copy data in PP_GRADE_SINGLE_AIMS
    //SS if (!PP_Grade_Single_Aims.select(DefaultSteelGrade, CSMC_DBData::unspecString))
    //SS {
    //SS   CPP_GRADE_SINGLE_AIMS *pPP_Grade_Single_Aims;
    //SS   pPP_Grade_Single_Aims = new CPP_GRADE_SINGLE_AIMS(m_pConnection);

    //SS   // select any steelgradecode
    //SS   if (pPP_Grade_Single_Aims->select(TempSteelGrade, CSMC_DBData::unspecString))
    //SS   {
    //SS     // select all rows for selected steelgradecode
    //SS     for (long i = 1; i <= pPP_Grade_Single_Aims->getLastRow(); ++i)
    //SS     {
    //SS       PP_Grade_Single_Aims.setSTEELGRADECODE(DefaultSteelGrade);
    //SS       PP_Grade_Single_Aims.setColumnsFromTable(pPP_Grade_Single_Aims, i);

    //SS       InsertGrade = InsertGrade && PP_Grade_Single_Aims.insert();
    //SS     }

    //SS     if (InsertGrade)
    //SS       PP_Grade_Prodprac.commit();
    //SS     else
    //SS       PP_Grade_Prodprac.rollback();
    //SS   }
    //SS   delete pPP_Grade_Single_Aims;
    //SS }

    //SS if (!PP_Grade_Prodprac.select(HMDSteelGrade, PlantName, "Parameter"))
    //SS {
    //SS   PP_Grade_Prodprac.setSTEELGRADECODE(HMDSteelGrade);
    //SS   PP_Grade_Prodprac.setPRODPRAC_ID(0);
    //SS   PP_Grade_Prodprac.setPLANT(PlantName);
    //SS   PP_Grade_Prodprac.setDESCR_PP("Parameter");
    //SS   PP_Grade_Prodprac.setHEATING_MODE_NO(1);
    //SS   InsertGrade = PP_Grade_Prodprac.insert();
    //SS }
    //SS if (!PP_Grade_Prodprac.select(HMDSteelGrade, PlantName, "Treatment"))
    //SS {
    //SS   PP_Grade_Prodprac.setSTEELGRADECODE(HMDSteelGrade);
    //SS   PP_Grade_Prodprac.setPRODPRAC_ID(0);
    //SS   PP_Grade_Prodprac.setPLANT(PlantName);
    //SS   PP_Grade_Prodprac.setDESCR_PP("Treatment");
    //SS   PP_Grade_Prodprac.setHEATING_MODE_NO(1);
    //SS   InsertGrade = InsertGrade && PP_Grade_Prodprac.insert();
    //SS }
    //SS if (!PP_Grade_Prodprac.select(HMDSteelGrade, PlantName, "Restriction"))
    //SS {
    //SS   PP_Grade_Prodprac.setSTEELGRADECODE(HMDSteelGrade);
    //SS   PP_Grade_Prodprac.setPRODPRAC_ID(0);
    //SS   PP_Grade_Prodprac.setPLANT(PlantName);
    //SS   PP_Grade_Prodprac.setDESCR_PP("Restriction");
    //SS   PP_Grade_Prodprac.setHEATING_MODE_NO(1);
    //SS   InsertGrade = InsertGrade && PP_Grade_Prodprac.insert();
    //SS }
    //SS if (InsertGrade)
    //SS   PP_Grade_Prodprac.commit();
    //SS else
    //SS   PP_Grade_Prodprac.rollback();

    //-----------------------------------------------
    
    if (OrderID == HMDStdOrderID)
    {
      // fill/update PP_ORDER with a default OrderID
      PP_Order.setPRODORDERID(OrderID);
//SS      PP_Order.setORD_STAT_NO(CDataConversion::StringToLong(DefaultOrdStatNo));
      PP_Order.setSTEELGRADECODE(HMDSteelGrade);
//SS      PP_Order.setAIMSTEEL_CONARC(AimSteelConArc);

      PP_Order.cleanWhereStatement();
      PP_Order.addWhereClause("PRODORDERID", OrderID);

      if (PP_Order.updateOrInsert())
      {
        PP_Order.commit();
      }
      else
      {
        PP_Order.rollback();
        return false;
      }
    }
    //-----------------------------------------------

    //fill PP_HEAT_PLANT
    if (!PP_Heat_Plant.selectByCustData(CustHeatID, CustTreatID, PlantName))
    {
      // generate next HeatID
//SS      HeatID = CDataConversion::LongToString(PP_Heat_Plant.getMaxHeatID() + 1);
      CHeatID FormattedHeatID;
//SS      HeatID = FormattedHeatID.generateHeatID(HeatID);

      //add default heat duration, if Planned Heat ID is not set
      if (EndTime == Now)
      {
        double HeatDuration = 480;//seconds, default if parameter isn't in DB
//SS         if (GT_Param.select("DefltTreatDuration", 0, CSMC_DBData::unspecLong, PlantName, PlantNo))
//SS         {
//SS           HeatDuration = CDataConversion::StringToDouble(GT_Param.getVALUE(1)) * 60;
//SS         }
        EndTime.addTime(HeatDuration);
      }

      // insert new Row in PP_HEAT_PLANT
//SS      PP_Heat_Plant.setHEATID_CUST(CustHeatID);
//SS      PP_Heat_Plant.setTREATID_CUST(CustTreatID);
      PP_Heat_Plant.setHEATID(HeatID);
      PP_Heat_Plant.setTREATID(TreatID);
//SS      PP_Heat_Plant.setPLANLADLETYPE(std::string(DEF_LADLE_TYPES::HotMetalLadle));
//SS      PP_Heat_Plant.setPLANLADLENO(HMLadleNo);
      PP_Heat_Plant.setPLANTNO(PlantIdConverter.getPlantNo(PlantID));
      PP_Heat_Plant.setPLANT(PlantIdConverter.getPlantName(PlantID));
//SS      PP_Heat_Plant.setVALIDEXPIRATIONDATE(std::string("VALID"));
//SS      PP_Heat_Plant.setPLANTREATSTART(StartTime);
//SS      PP_Heat_Plant.setPLANTREATEND(EndTime);
//SS      PP_Heat_Plant.setTAP_ID_CUST(CustTapID);
//SS      PP_Heat_Plant.setMETAL_TYPE(MetalType);

      RetValue = PP_Heat_Plant.insert();
    }
    else
    {
      HeatID = PP_Heat_Plant.getHEATID(1);
      TreatID = PP_Heat_Plant.getTREATID(1);
    }
    //-----------------------------------------------

    if (!PP_Heat.select(CustHeatID) && RetValue)
    {
      PP_Heat.setHEATID(HeatID);
//SS      PP_Heat.setHEATID_CUST(CustHeatID);
      PP_Heat.setPRODORDERID(OrderID);
//SS      PP_Heat.setUSERCODE(UserCode);
      PP_Heat.setROUTECODEPLAN(RouteCodePlan);
      PP_Heat.setREVTIME(Now);
//SS      PP_Heat.setTAP_ID_CUST(CustTapID);
//SS      PP_Heat.setHEATSTATORDER(DEF_GC_HEAT_STAT_NUM::Planned);
//SS      PP_Heat.setHEATSTAT_HMD(DEF_GC_HEAT_STAT_NUM::Planned);
//SS      PP_Heat.setMETAL_TYPE(MetalType);
      RetValue = PP_Heat.insert();
    }
    //-----------------------------------------------

    if (RetValue)
      PP_Heat.commit();
    else
      PP_Heat.rollback();

    // set data to Event
    if (RetValue)
    {
      Event.setHeatID(HeatID);
      Event.setTreatID(TreatID);
      Event.setOrderID(OrderID);
      Event.setProductID(ProductID); //should be empty
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),"CDM_HMDTreatmentManagementEventHandler::makeEntryInHeatSchedule()",ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),"CDM_HMDTreatmentManagementEventHandler::makeEntryInHeatSchedule()",ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"","CDM_HMDTreatmentManagementEventHandler::makeEntryInHeatSchedule()",ExceptionMsg.str().c_str());
    RetValue = false;
  }
  return RetValue;
}
*/