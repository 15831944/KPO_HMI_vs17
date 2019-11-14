// Copyright (C) 2009 SMS Demag AG Germany

// DH_OUT_EAF PATTERN IMPLEMENTATION 
//bool CEAF_EventHandler::provideData_TlgName(CEventMessage& Event)
//{
//  //=========================    Example   ===================================
//  bool RetValue = true;
//
//  //------------ read the data from Event ------------------
//  std::string HeatID    = Event.getHeatID();
//  std::string TreatID   = Event.getTreatID(); 
//  std::string ProductID = Event.getProductID();
//  std::string OrderID   = Event.getOrderID();
//  std::string DataKey   = Event.getDataKey();
//  std::string PlantID   = Event.getPlantID();
//  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
//  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID); 
//  long UnitNo           = m_pGC_Plant_Container->getPlantNo(PlantID);
//
//  //------------ This variables are used as buffer ------------------
//  std::string DataKeyL1;
//
//  std::string CustHeatId;
//  std::string CustTreatId;
//
//  std::string LadleType; ;
//  std::string LadleId;
//  long LadleNo   = 0;
//
//  CDateTime Now;
//  DEF::seqLong seqSpare;
//
//  std::string Action    = "Reading DM interface data from ";
//  Action +=  Event.getSender();
//  Action +=  "ProductID:";
//  Action +=  Event.getProductID();
//  Action +=  " - ";
//  Action +=  "Key:";
//  Action +=  Event.getDataKey(); 
//
//  std::string TlgName   = "TlgName";
//  std::string Function = "CEAF_EventHandler::provideData_" + TlgName;
//
//  log (TlgName + ": Started", 3);
//
//  try
//  {
//    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);
//
//    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();
//
//    if ( pDM_Interface && pTelcom_Interface )
//    {
//      //********    preset data  **************************************************************************************
//
//      if ( !HeatID.empty() && HeatID != DEF::Inv_String )
//      {
//        DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);
//
//        // truncate string data to fit telegram length
//        HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
//        TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2); should be 3!!
//
//        //********    Read event related data  ************************************************************************
//
//        //********    Convert and check event data  *******************************************************************
//
//        //********    Log event data **********************************************************************************
//
//        //********    Write telegram data  ****************************************************************************
//
//        pTelcom_Interface->setString  (DataKeyL1, Telegram_X::HeatId,        HeatID);
//        pTelcom_Interface->setString  (DataKeyL1, Telegram_X::TreatId,       TreatID);
//        pTelcom_Interface->setAny     (DataKeyL1, Telegram_X::CreateTime,    Now.asCORBAAny()); 
//
//        pTelcom_Interface->showContent(DataKeyL1, 4);
//
//        //********    send internal event  ***************************************************************************
//
//        SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);
//
//        //********    End processing data  ***************************************************************************
//      }// if ( !HeatID.empty() && HeatID != DEF::Inv_String )
//      else
//      {
//        RetValue = false;
//
//        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
//        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
//        pEventLog->EL_InvalidTlgData(sMessage,TlgName.c_str(),"HeatID","empty");  
//      }
//    }// if ( pDM_Interface && m_pTelcom_Interface )
//    else
//    {
//      RetValue = false;
//    }
//
//  }// try
//  catch (cCBS_DBExc &e)
//  {
//    RetValue = false;
//
//    pTelcom_Interface->showContent(DataKeyL1,1);
//    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
//    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
//    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
//      Function.c_str(), TlgName.c_str()); 
//  }
//  catch(CORBA::SystemException& sExc) 
//  {
//    RetValue = false;
//
//    pTelcom_Interface->showContent(DataKeyL1,1);
//    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
//    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
//    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
//      Function.c_str(), TlgName.c_str());    
//  }
//  catch(CORBA::Exception& cExc) 
//  {
//    RetValue = false;
//
//    pTelcom_Interface->showContent(DataKeyL1,1);
//    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
//    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
//    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
//      Function.c_str(), TlgName.c_str()); 
//  }
//  catch(...)
//  {
//    RetValue = false;
//
//    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
//    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
//    pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(), TlgName.c_str()); 
//  }
//
//  if ( !RetValue )
//  {
//    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
//    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
//    pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
//  }
//
//  log (TlgName + ": Finished", 3);
//
//  return RetValue;
//}// bool CEAF_EventHandler::provideData_TlgName(const std::string& Key, const std::string& TlgName
// DH_OUT_EAF PATTERN IMPLEMENTATION

#include "iEventMessages_s.hh"
#include "Telcom_Out_s.hh"
#include "iSMC_DataDefinitions_s.hh"

#include "cCBS_StdInitBase.h"
#include "CEventMessage.h"
#include "CDateTime.h"
#include "CLadleID.h"
#include "CTelegram_Handler.h" 

#include "CSMC_EventLogEAFController.h"

#include "CDataConversion.h"

#include "CGC_Recipe_L1Container.h"
#include "CGC_SourceContainer.h"

#include "CGC_PHASE.h"
#include "CGT_MAT_PURP.h"
#include "CGT_MAT.h"
#include "CGTE_PP_FLAME_PROFILE.h"
#include "CGCE_INJECTION.h"

#include "CPP_HEAT.h"
#include "CPP_HEAT_PLANT.h"

#include "CPD_HEAT_DATA.h"
#include "CPD_HEAT_DATA_PRODPRAC.h" 
#include "CPD_HOTHEEL.h"
#include "CPD_HOT_METAL.h"
#include "CPD_HOT_METAL_ORDER.h"
#include "CPD_RECIPE.h"                   
#include "CPD_SCRAP_CONTAINER.h"             
#include "CPD_SCRAP_CONTAINER_ENTRY.h"
#include "CPD_SCRAP_CONTAINER_ORDER_ENTRY.h"
#include "CPD_SCRAP_CONTAINER_ORDER.h"             

#include "DEF_GCE_BURNER.h"
#include "DEF_GC_PHASE.h"
#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_PRODPRAC_DEF.h"
#include "DEF_GC_SCRAP_CONTAINER_TYPE.h"
#include "DEF_GC_SCRAP_CONT_ORDER_STATUS.h"
#include "DEF_GC_TREATMENTPHASE_DEF.h"
#include "DEF_GT_PURP.h"
#include "DEF_GC_PLANTGROUP_DESC.h"
#include "DEF_GC_STIRR_GAS_TYPE.h"
#include "DEF_GCE_BURNER_GASTYPE.h"
#include "DEF_GC_LIQADD_TYPE.h"
#include "DEF_GCE_INJECTION_TYPE.h"
#include "DEF_GCE_INJECTION.h"

#include "CEAF_EventHandler.h"

CEAF_EventHandler::CEAF_EventHandler( )
{

  // use existing DB connection from Task
  cCBS_StdConnection* pConnection = CDH_OUT_Task::getInstance()->getStdConnection();

  if (pConnection)
  {
    long PlantNo  = 1;
    std::string Plant = DEF_GC_PLANT_DEF::EAF;

    cCBS_StdInitBase::getInstance()->replaceWithEntry("PLANT", "PlantNo", PlantNo);
    cCBS_StdInitBase::getInstance()->replaceWithEntry("PLANT", "Plant"  , Plant);

		//sankar
		long OracleTransfer = 1;
    cCBS_StdInitBase::getInstance()->replaceWithEntry("UseOracleTransfer", "OracleTransfer"  , OracleTransfer);
		if(OracleTransfer == 1)
			UseOracleTransfer = true;
		else
			UseOracleTransfer = false;


    m_pGC_Plant_Container             = new CGC_Plant_Container(pConnection, Plant);
    m_pHeatDataConverter              = new CHeatDataConverter(pConnection);
    m_pGC_SourceContainer             = new CGC_SourceContainer(pConnection, Plant, PlantNo);
    m_pGC_Recipe_L1Container          = new CGC_Recipe_L1Container (pConnection,Plant); 

    m_pGC_PHASE                       = new CGC_PHASE(pConnection);
    m_pGT_MAT_PURP                    = new CGT_MAT_PURP(pConnection);
    m_pGT_MAT                         = new CGT_MAT(pConnection);
    m_pGTE_PP_FLAME_PROFILE           = new CGTE_PP_FLAME_PROFILE(pConnection);
    m_pGCE_INJECTION                  = new CGCE_INJECTION(pConnection);

    m_pPD_HEAT_DATA                   = new CPD_HEAT_DATA(pConnection);
    m_pPD_HEAT_DATA_PRODPRAC          = new CPD_HEAT_DATA_PRODPRAC(pConnection);
    m_pPD_RECIPE                      = new CPD_RECIPE(pConnection);
    m_pPD_SCRAP_CONTAINER_ORDER       = new CPD_SCRAP_CONTAINER_ORDER(pConnection);
    m_pPD_SCRAP_CONTAINER_ORDER_ENTRY = new CPD_SCRAP_CONTAINER_ORDER_ENTRY(pConnection);

    m_pPD_HOT_METAL                   = new CPD_HOT_METAL(pConnection);
    m_pPD_HOT_METAL_ORDER             = new CPD_HOT_METAL_ORDER(pConnection);
    m_pPD_SCRAP_CONTAINER             = new CPD_SCRAP_CONTAINER(pConnection);
    m_pPD_SCRAP_CONTAINER_ENTRY       = new CPD_SCRAP_CONTAINER_ENTRY(pConnection);
    m_pPD_HOTHEEL                     = new CPD_HOTHEEL(pConnection);

    m_pPP_HEAT                        = new CPP_HEAT(pConnection);
    m_pPP_HEAT_PLANT                  = new CPP_HEAT_PLANT(pConnection);

    std::string PlantID = m_pGC_Plant_Container->getL2PlantID(PlantNo);
    m_StatusHandler.isStatusChanged(PlantID, "PlantStatus"           , DEF_GEN_STATES::Stop);
  }
  else
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"", "CEAF_EventHandler","No database connection");

    // to guaranty EL_ExceptionCaught to be sent to CBS service
    Sleep(3000);

    // terminate programm in case of starting up without getting connection to database
    exit(EXIT_FAILURE);
  }
}

CEAF_EventHandler::~CEAF_EventHandler()
{
  if(m_pPD_HEAT_DATA)                   {delete m_pPD_HEAT_DATA;                    m_pPD_HEAT_DATA = 0;                  }
  if(m_pPP_HEAT_PLANT)                  {delete m_pPP_HEAT_PLANT;                   m_pPP_HEAT_PLANT = 0;                 }
  if(m_pPP_HEAT)                        {delete m_pPP_HEAT;                         m_pPP_HEAT = 0;                       }
  if(m_pPD_RECIPE)                      {delete m_pPD_RECIPE;                       m_pPD_RECIPE = 0;                     }
  if(m_pPD_SCRAP_CONTAINER_ORDER)       {delete m_pPD_SCRAP_CONTAINER_ORDER;        m_pPD_SCRAP_CONTAINER_ORDER = 0;      }               
  if(m_pPD_SCRAP_CONTAINER_ORDER_ENTRY) {delete m_pPD_SCRAP_CONTAINER_ORDER_ENTRY;  m_pPD_SCRAP_CONTAINER_ORDER_ENTRY = 0;}   
  if(m_pPD_HEAT_DATA_PRODPRAC)          {delete m_pPD_HEAT_DATA_PRODPRAC;           m_pPD_HEAT_DATA_PRODPRAC = 0;         } 
  if(m_pGC_Plant_Container)             {delete m_pGC_Plant_Container;              m_pGC_Plant_Container = 0;            }
  if(m_pHeatDataConverter)              {delete m_pHeatDataConverter;               m_pHeatDataConverter = 0;             }
  if(m_pGC_PHASE)                       {delete m_pGC_PHASE;                        m_pGC_PHASE = 0;                      }
  if(m_pGC_SourceContainer)             {delete m_pGC_SourceContainer;              m_pGC_SourceContainer = 0;            }
  if(m_pGC_Recipe_L1Container)          {delete m_pGC_Recipe_L1Container;           m_pGC_Recipe_L1Container = 0;         }
  if(m_pGTE_PP_FLAME_PROFILE)           {delete m_pGTE_PP_FLAME_PROFILE;            m_pGTE_PP_FLAME_PROFILE = 0;          }
  if(m_pGCE_INJECTION)                  {delete m_pGCE_INJECTION;                   m_pGCE_INJECTION = 0;          }

  if(m_pPD_HOT_METAL)                   {delete m_pPD_HOT_METAL;                    m_pPD_HOT_METAL = 0;                  }  
  if(m_pPD_HOT_METAL_ORDER)             {delete m_pPD_HOT_METAL_ORDER;              m_pPD_HOT_METAL_ORDER = 0;            }  
  if(m_pPD_SCRAP_CONTAINER)             {delete m_pPD_SCRAP_CONTAINER;              m_pPD_SCRAP_CONTAINER = 0;            }               
  if(m_pPD_SCRAP_CONTAINER_ENTRY)       {delete m_pPD_SCRAP_CONTAINER_ENTRY;        m_pPD_SCRAP_CONTAINER_ENTRY = 0;      }   
  if(m_pPD_HOTHEEL)                     {delete m_pPD_HOTHEEL;                      m_pPD_HOTHEEL = 0;                    }  

  if(m_pGT_MAT_PURP)                    {delete m_pGT_MAT_PURP;                     m_pGT_MAT_PURP = 0;                   }  
  if(m_pGT_MAT)                         {delete m_pGT_MAT;                          m_pGT_MAT = 0;                        }  
}

bool  CEAF_EventHandler::handleEvent(CEventMessage& evMessage)
{
  bool RetValue = true;

  

  log(evMessage,3);

  if (evMessage.getMessage() == EAF_EvMsg::evEAFPlantStatusRequest )
  {
    if ( UseOracleTransfer )  
    {
      RetValue = provideData_L2EA72StatusRequest     (evMessage);
      RetValue = provideData_L2SY92_SCRAP_LOAD       (evMessage);
    }
    else
    {
      RetValue = provideData_L2EA72StatusRequest        (evMessage);
      RetValue = provideData_L2SY92ScrapLoadInstruction (evMessage);
    }
  }
  else if (evMessage.getMessage() == EAF_EvMsg::evEAFModelResultActualSetpoints )
  {
    if ( UseOracleTransfer )
    {
      RetValue = provideData_L2EA07CompMode       (evMessage);
      //RetValue = provideData_L2EA41ProcessValues  (evMessage);
			RetValue = provideData_L2EA20VoltageTap     (evMessage);
      RetValue = provideData_L2EA40_PROC_PATT     (evMessage);
      RetValue = provideData_L2EA41_PROC_VALUES   (evMessage);
    }
    else
    {
      RetValue = provideData_L2EA07CompMode       (evMessage);
			RetValue = provideData_L2EA20VoltageTap     (evMessage);
      RetValue = provideData_L2EA41ProcessValues  (evMessage);
      RetValue = provideData_L2EA40ProcessPattern (evMessage);
    }
  }
  // send initial status request only once after start-up
  else if (evMessage.getMessage() == EAF_EvMsg::evEAFModelResultRecipeSetpoints )
  {
    // just tap start and aim temp ... should be seperated

    if ( UseOracleTransfer )
    {
      //RetValue = provideData_L2EA03HeatAnnouncement (evMessage, 1);
      RetValue = provideData_L2EA07CompMode         (evMessage); 
      //RetValue = provideData_L2EA41ProcessValues    (evMessage);
			RetValue = provideData_L2EA20VoltageTap     (evMessage);
      RetValue = provideData_L2EA40_PROC_PATT       (evMessage);
      RetValue = provideData_L2EA41_PROC_VALUES     (evMessage);
      RetValue = provideData_L2EA70_MAT_HANDL       (evMessage);
    }
    else
    {
      //RetValue = provideData_L2EA03HeatAnnouncement (evMessage, 1);
      RetValue = provideData_L2EA07CompMode         (evMessage); 
      RetValue = provideData_L2EA41ProcessValues    (evMessage);
			RetValue = provideData_L2EA20VoltageTap     (evMessage);
      RetValue = provideData_L2EA40ProcessPattern   (evMessage); 
      RetValue = provideData_L2EA05BurnerPattern    (evMessage); 
      RetValue = provideData_L2EA32CarbonInjPattern (evMessage);
      RetValue = provideData_L2EA70MatHandling      (evMessage);
    }
  } 
  else if (evMessage.getMessage() == EAF_EvMsg::evEAFModelResultCode )
  {
    if ( UseOracleTransfer )
    {
      RetValue = provideData_L2EA07CompMode       (evMessage);	  
      RetValue = provideData_L2EA41_PROC_VALUES   (evMessage);
      //RetValue = provideData_L2EA41ProcessValues  (evMessage);
			RetValue = provideData_L2EA20VoltageTap     (evMessage);
    }
    else
    {
      RetValue = provideData_L2EA07CompMode       (evMessage);	  
      RetValue = provideData_L2EA41ProcessValues  (evMessage);
			RetValue = provideData_L2EA20VoltageTap     (evMessage);
    }
  }
  else if (evMessage.getMessage() == EAF_EvMsg::evEAFHeatAnnouncement) 
  {
    if ( UseOracleTransfer )
    {
      RetValue = provideData_L2EA03HeatAnnouncement  (evMessage);
      RetValue = provideData_L2EA07CompMode          (evMessage);
      RetValue = provideData_L2SY92_SCRAP_LOAD       (evMessage);
      RetValue = provideData_L2EA70_MAT_HANDL        (evMessage);
    }
    else
    {
      RetValue = provideData_L2EA03HeatAnnouncement     (evMessage);
      RetValue = provideData_L2EA07CompMode             (evMessage);
      RetValue = provideData_L2SY92ScrapLoadInstruction (evMessage);
      RetValue = provideData_L2EA70MatHandling          (evMessage);
    }
  }
  else if ( evMessage.getMessage() == EAF_EvMsg::evEAFHeatStart )   
  {
    RetValue = provideData_L2EA72StatusRequest(evMessage);      // Plant Status Request
  }
  else if (evMessage.getMessage() == EAF_EvMsg::evEAFHeatCancellation )
  {
    RetValue = provideData_L2EA06HeatCancel        (evMessage);
    //RetValue = provideData_L2EA03HeatAnnouncement  (evMessage, 1); 
  }
  else if (evMessage.getMessage() == EAF_EvMsg::evEAFHeatDeparture )
  {
    //RetValue = provideData_L2EA03HeatAnnouncement (evMessage, 1); 
  }
  else if (evMessage.getMessage() == EAF_EvMsg::evEAFRequestMatAvail )
  {
    RetValue = provideData_L2EA71MatAvailRequest   (evMessage);
  }
  else if( (evMessage.getMessage() == EAF_EvMsg::evEAFElectrodeHydraulicSystemInhibitRequest) || 
           (evMessage.getMessage() == EAF_EvMsg::evEAFElectrodeHydraulicSystemReleaseRequest) )
  {
    RetValue = provideData_L2EA23ReleaseElectrodes (evMessage);
  }
  else if(evMessage.getMessage() == EAF_EvMsg::evEAFOrderScrap || 
          evMessage.getMessage() == EAF_EvMsg::evEAFHeatScheduleUpdate ||
          evMessage.getMessage() == EAF_EvMsg::evEAFHandleSetBasketData )
  {
    if ( UseOracleTransfer )
    {
      RetValue = provideData_L2SY92_SCRAP_LOAD(evMessage);
    }
    else
    {
      RetValue = provideData_L2SY92ScrapLoadInstruction(evMessage);
    }
  }
  else if(evMessage.getMessage() == EAF_EvMsg::evEAFHandleBasketDischarged)
  {
    if ( UseOracleTransfer )  
    {
      RetValue = provideData_L2EA70_MAT_HANDL (evMessage);
    }
    else
    {
      RetValue = provideData_L2EA70MatHandling   (evMessage);
    }
  }  
  else if(evMessage.getMessage() == EAF_EvMsg::evEAFScrapMaterialAvail)
  {
    if ( UseOracleTransfer )  
    {
      RetValue = provideData_L2SY95_SCRAP_MAT (evMessage);
    }
    else
    {
      RetValue = provideData_L2SY95ScrapMat   (evMessage);
    }
  }
  else if(evMessage.getMessage() == GEN_EvMsg::evGenSystemStatusReport)
  {
    RetValue = provideData_L2EA07CompMode     (evMessage);
  }
  else if (evMessage.getMessage() == EAF_EvMsg::evEAFChangeTapLadleData || evMessage.getMessage() == EAF_EvMsg::evEAFTapLadleData )
  {
    //RetValue = provideData_L2EA03HeatAnnouncement (evMessage, 1);
  }
  else if(evMessage.getMessage() == "ORACLE_TRANSFER") // for testing purpose only
  {
    RetValue = provideData_L2EA40_PROC_PATT(evMessage);
    RetValue = provideData_L2EA41_PROC_VALUES(evMessage);
    RetValue = provideData_L2EA70_MAT_HANDL(evMessage);

    RetValue = provideData_L2SY92_SCRAP_LOAD(evMessage);
  }
  else
  {
    RetValue = false; // The event is for this handler, but the handler doesn't have a do-method
  }

  return RetValue;
}

void CEAF_EventHandler::SendEventMessage(const std::string& TlgName, const std::string& DataKey, const std::string& PlantID, const std::string& HeatID, const std::string& TreatID, const std::string& OrderID)
{
  try
  {
    //********    Dispatch event ***********************************************************************

    CEventMessage MstToL1Sender;
    MstToL1Sender.setMessage(std::string("TELEGRAM_") + TlgName);
    MstToL1Sender.setHeatID(HeatID);
    MstToL1Sender.setTreatID(TreatID);
    MstToL1Sender.setPlantID(PlantID);
    MstToL1Sender.setDataKey(DataKey);
    MstToL1Sender.setOrderID(OrderID);
    dispatchEvent(m_SenderName,"",MstToL1Sender);  
  }
  catch (cCBS_DBExc &e)
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), "", ""); 
  }
  catch(CORBA::SystemException& sExc) 
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(), "", "");
  }
  catch(CORBA::Exception& cExc) 
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(), "", "");
  }
  catch(...)
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "", ""); 
  }
}

bool  CEAF_EventHandler::provideData_L2EA03HeatAnnouncement(CEventMessage& Event, long UpdateFlag /* = 0 */)
{	
  //=================    H E A T   A N N O U N C E M E N T   ===============================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();

  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID);
  long        PlantNo   = m_pGC_Plant_Container->getPlantNo(PlantID);
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  long        UnitNo    = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2EA03";
  std::string Function = "CEAF_EventHandler::provideData_L2EA03HeatAnnouncement";


  try
  {
    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    if ( pDM_Interface && pTelcom_Interface )
    {
      //********    preset data  ************************************************************************

      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);


      DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

      CIntfData::preset(seqSpare,0,5);

      //********    Read event related data  ************************************************************************

      //********    Log event data ***********************************************************************

      //********    Convert and check event data  ***********************************************************

      if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
      {
        if ( m_pPD_HEAT_DATA->select (HeatID, TreatID, Plant) )
        {
          if ( m_pPD_HEAT_DATA->getLastRow() == 1 )         // should be unique
          {
            std::string ProdOrderId = m_pPD_HEAT_DATA->getPRODORDERID_ACT(1);
            if( ProdOrderId == DEF::Inv_String )
            {
              ProdOrderId = m_pPD_HEAT_DATA->getPRODORDERID_PLAN(1);
            }

            std::string SteelGradeCode  = m_pPD_HEAT_DATA->getSTEELGRADECODE_ACT(1);
            if( SteelGradeCode ==  DEF::Inv_String )
            {
              SteelGradeCode = m_pPD_HEAT_DATA->getSTEELGRADECODE_PLAN(1);
            }

            //if can not get the mod time,then select the plan time of treatement  end as the tap start time
            CDateTime TapStartTime  = m_pPD_HEAT_DATA->getTREATEND_MOD(1);
            CDateTime ProdDate      = m_pPD_HEAT_DATA->getTREATSTART_MOD(1);
            double    AimTemp       = m_pPD_HEAT_DATA->getAIMTEMP_MOD(1);

            long LADLENO            = m_pPD_HEAT_DATA->getLADLENO(1);
            std::string LADLETYPE   = m_pPD_HEAT_DATA->getLADLETYPE(1);

            CLadleID LadleID;

            std::string TapLadleId = "";

            if ( LADLETYPE != CSMC_DBData::unspecString   &&
                 LADLENO   != CSMC_DBData::unspecLong )
            {
              TapLadleId = CDataConversion::SetInvalidToDefault(LadleID.generateLadleID(LADLETYPE, LADLENO), "" );
            }

            if   (TapStartTime == CSMC_DBData::unspecDate)
            {
              TapStartTime = m_pPD_HEAT_DATA->getTREATEND_PLAN(1);
              AimTemp      = m_pPD_HEAT_DATA->getAIMTEMP_PLAN(1);
            }


            DEF::seqString HMLadleId;
            DEF::seqDouble HMWgt;

            CIntfData::preset(HMLadleId, "", 3);
            CIntfData::preset(HMWgt, 0., 3);

            if(m_pPD_HOT_METAL_ORDER->select(Plant,ProdOrderId,CSMC_DBData::unspecLong ))
            {
              long LastRow = max(3,m_pPD_HOT_METAL_ORDER->getLastRow());
              for ( long i = 1 ; i <= LastRow; ++i )
              {
                long HOTMETAL_COUNTER = m_pPD_HOT_METAL_ORDER->getHOTMETAL_COUNTER(i);
                if( HOTMETAL_COUNTER != CSMC_DBData::unspecLong )
                {
                  if ( m_pPD_HOT_METAL->select(HOTMETAL_COUNTER) )
                  {
                    long LADLENO          = m_pPD_HOT_METAL->getLADLENO(1);
                    std::string LADLETYPE = m_pPD_HOT_METAL->getLADLETYPE(1);
										double hmWeight  = m_pPD_HOT_METAL->getWEIGHT(1);

                    CLadleID LadleID;

                    std::string LadleId = "";

										//sankar
										LadleId   = CDataConversion::SetInvalidToDefault(LadleID.generateLadleID(LADLETYPE, LADLENO), "" );

                    /*if ( LADLETYPE != DEF::Inv_String            && 
                         LADLETYPE == CSMC_DBData::unspecString   &&
                         LADLENO   == DEF::Inv_Long               && 
                         LADLENO   == CSMC_DBData::unspecLong )
                    {
                      LadleId   = CDataConversion::SetInvalidToDefault(LadleID.generateLadleID(LADLETYPE, LADLENO), "" );
                    }*/

                    //CIntfData::insert(HMLadleId,LadleId.c_str());
										CIntfData::setAt(HMLadleId,LadleId.c_str(),i-1);
                    CIntfData::setAt(HMWgt,hmWeight,i-1);
                  }
                }
              }
            }

            //Init the basket struct info
            DEF::seqLong BasketNos;
            DEF::seqDouble MatWeightSeq;
            CIntfData::preset(BasketNos, -1, 3);
            CIntfData::preset(MatWeightSeq, -1, 3);

            if( m_pPD_SCRAP_CONTAINER_ORDER->selectByContainerType( Plant, ProdOrderId, DEF_GC_SCRAP_CONTAINER_TYPE::Basket ) )
            {
              long LastRow = m_pPD_SCRAP_CONTAINER_ORDER->getLastRow();
              for(int i = 1; i <= LastRow; i++)
              {
                long ContainerSeqNo = m_pPD_SCRAP_CONTAINER_ORDER->getCONTAINERINSEQ(i);
                long CONTAINERNO    = m_pPD_SCRAP_CONTAINER_ORDER->getCONTAINERNO(i);

                if ( CONTAINERNO != CSMC_DBData::unspecLong )
                {
                  CIntfData::setAt(BasketNos, CONTAINERNO, i-1);
                }

                if ( m_pPD_SCRAP_CONTAINER_ENTRY && CONTAINERNO != CSMC_DBData::unspecLong &&
                  m_pPD_SCRAP_CONTAINER_ENTRY->select( CONTAINERNO, CSMC_DBData::unspecString, CSMC_DBData::unspecLong) )
                {
                  double matWeight = 0.;
                  for ( long x = 1 ; x <= m_pPD_SCRAP_CONTAINER_ENTRY->getLastRow(); ++x )
                  {
                    matWeight += CDataConversion::SetInvalidToDefault(m_pPD_SCRAP_CONTAINER_ENTRY->getMATWEIGHT(x), m_pPD_SCRAP_CONTAINER_ENTRY->getMATWEIGHT_CHARGED(x));
                  }

                  CIntfData::setAt(MatWeightSeq, matWeight, i-1 );
                }
                // select material data from  entry table for all recipes
                else if ( m_pPD_SCRAP_CONTAINER_ORDER_ENTRY && CONTAINERNO != CSMC_DBData::unspecLong && 
                  m_pPD_SCRAP_CONTAINER_ORDER_ENTRY->selectByMatChargeSeq(Plant, ProdOrderId, ContainerSeqNo, CSMC_DBData::unspecString, CSMC_DBData::unspecString) )
                {
                  double matWeight = 0.;
                  for ( long x = 1 ; x <= m_pPD_SCRAP_CONTAINER_ORDER_ENTRY->getLastRow(); ++x )
                  {
                    matWeight += m_pPD_SCRAP_CONTAINER_ORDER_ENTRY->getMATWEIGHT(x);                     
                  }

                  CIntfData::setAt(MatWeightSeq, matWeight, i-1 );
                }
              }
            }// if( m_pPD_SCRAP_CONTAINER_ORDER->selectByContainerType( Plant, ProdOrderId, DEF_GC_SCRAP_CONTAINER_TYPE::Basket ) )

            std::string ShiftCode = m_pPD_HEAT_DATA->getSHIFT_ID (1);
            std::string CrewCode  = m_pPD_HEAT_DATA->getCREW_ID  (1);
            std::string OperCode  = m_pPD_HEAT_DATA->getUSERCODE  (1);

            std::string RouteCode;
            if( m_pPP_HEAT->select(HeatID) )
            {
              RouteCode  = m_pPP_HEAT->getROUTECODE_PLAN(1);
            }

            long ProdPracOxygenInj  = 0;
            long ProdPracCarbonInj  = GetProdPracNo(HeatID,TreatID,Plant,DEF_GC_PRODPRAC_DEF::Injection); 
            long ProdPracBurner     = GetProdPracNo(HeatID,TreatID,Plant,DEF_GC_PRODPRAC_DEF::Burner); 
            long ProdPracElec       = GetProdPracNo(HeatID,TreatID,Plant,DEF_GC_PRODPRAC_DEF::Electric); 
            long ProdPracProcess    = GetProdPracNo(HeatID,TreatID,Plant,DEF_GC_PRODPRAC_DEF::Process); 
            long ProdPracMat        = GetProdPracNo(HeatID,TreatID,Plant,DEF_GC_PRODPRAC_DEF::Restriction); 
            long ProdPracScrap      = GetProdPracNo(HeatID,TreatID,Plant,DEF_GC_PRODPRAC_DEF::Scrap); 

            // ***************************************************
            // reset all data in case of cancellation or departure
            // L1 will reset HMI data
            // ***************************************************
            if ( Event.getMessage() == EAF_EvMsg::evEAFHeatCancellation ||
                 Event.getMessage() == EAF_EvMsg::evEAFHeatDeparture )
            {
              CustHeatID  = "";
              CustTreatID = "";
            }


            // setting defaults if invalid data have been detected
            ProdPracOxygenInj  = CDataConversion::SetInvalidToDefault( ProdPracOxygenInj, 0, CSMC_DBData::unspecLong);
            ProdPracCarbonInj  = CDataConversion::SetInvalidToDefault( ProdPracCarbonInj, 0, CSMC_DBData::unspecLong); 
            ProdPracBurner     = CDataConversion::SetInvalidToDefault( ProdPracBurner   , 0, CSMC_DBData::unspecLong);
            ProdPracElec       = CDataConversion::SetInvalidToDefault( ProdPracElec     , 0, CSMC_DBData::unspecLong);
            ProdPracProcess    = CDataConversion::SetInvalidToDefault( ProdPracProcess  , 0, CSMC_DBData::unspecLong);
            ProdPracMat        = CDataConversion::SetInvalidToDefault( ProdPracMat      , 0, CSMC_DBData::unspecLong);
            ProdPracScrap      = CDataConversion::SetInvalidToDefault( ProdPracScrap    , 0, CSMC_DBData::unspecLong);

            long HotHeelWeight      = 0;

            if (m_pPD_HOTHEEL->select(Plant,PlantNo)) 
            {
              double STEELMASS  = m_pPD_HOTHEEL->getSTEELMASS(1);
              double SLAGMASS   = m_pPD_HOTHEEL->getSLAGMASS(1);
              STEELMASS = CDataConversion::SetInvalidToDefault(STEELMASS  ,0  ,CSMC_DBData::unspecDouble);
              SLAGMASS  = CDataConversion::SetInvalidToDefault(SLAGMASS   ,0  ,CSMC_DBData::unspecDouble);

              HotHeelWeight = long(STEELMASS + SLAGMASS);
            }

            // truncate string data to fit telegram length
            HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
            TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

            ShiftCode       = CDataConversion::SetInvalidToDefault(ShiftCode      ," ",CSMC_DBData::unspecString);
            ProdOrderId     = CDataConversion::SetInvalidToDefault(ProdOrderId    ," ",CSMC_DBData::unspecString);
            SteelGradeCode  = CDataConversion::SetInvalidToDefault(SteelGradeCode ," ",CSMC_DBData::unspecString);
            CrewCode        = CDataConversion::SetInvalidToDefault(CrewCode       ," ",CSMC_DBData::unspecString);
            OperCode        = CDataConversion::SetInvalidToDefault(OperCode       ,"NP",CSMC_DBData::unspecString);
            RouteCode       = CDataConversion::SetInvalidToDefault(RouteCode      ," ",CSMC_DBData::unspecString);

            // truncate data to fit telegram length
            HeatID          = CDataConversion::CheckLengthAndTruncate(HeatID          ,10);
            TreatID         = CDataConversion::CheckLengthAndTruncate(TreatID         ,2);
            CustHeatID      = CDataConversion::CheckLengthAndTruncate(CustHeatID      ,10);
            CustTreatID     = CDataConversion::CheckLengthAndTruncate(CustTreatID     ,2);
            ProdOrderId     = CDataConversion::CheckLengthAndTruncate(ProdOrderId     ,10);
            SteelGradeCode  = CDataConversion::CheckLengthAndTruncate(SteelGradeCode  ,12);
            CrewCode        = CDataConversion::CheckLengthAndTruncate(CrewCode        ,2);
            OperCode        = CDataConversion::CheckLengthAndTruncate(OperCode        ,6);
            RouteCode       = CDataConversion::CheckLengthAndTruncate(RouteCode       ,20);

            //********    Write telegram data  ***********************************************************************
            pTelcom_Interface->setLong  ( DataKeyL1, Telegram_L2EA03::UnitNo,        UnitNo);
            pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2EA03::CreateTime,    Now.asCORBAAny());   
            pTelcom_Interface->setString( DataKeyL1, Telegram_L2EA03::HeatId,        HeatID);
            pTelcom_Interface->setString( DataKeyL1, Telegram_L2EA03::TreatId,       TreatID);
            pTelcom_Interface->setString( DataKeyL1, Telegram_L2EA03::ProdOrderId,    ProdOrderId);
            pTelcom_Interface->setString( DataKeyL1, Telegram_L2EA03::SteelGradeCode, SteelGradeCode );
            pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2EA03::ProdDate,       ProdDate.asCORBAAny());
            pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2EA03::TapStartTime,   TapStartTime.asCORBAAny());
            pTelcom_Interface->setString( DataKeyL1, Telegram_L2EA03::TapLadleId,     TapLadleId);
            // HMLadleId not used
            pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2EA03::HMLadleId,      CIntfData::ToAny(HMLadleId));
            // HMWeight not used
            pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2EA03::HMWeight,      CIntfData::ToAny(HMWgt));

            pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2EA03::ContainerNo,    CIntfData::ToAny(BasketNos));
            pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2EA03::ContainerMatWeight,CIntfData::ToAny(MatWeightSeq));
            pTelcom_Interface->setString( DataKeyL1, Telegram_L2EA03::ShiftCode,      ShiftCode );
            pTelcom_Interface->setString( DataKeyL1, Telegram_L2EA03::CrewCode,       CrewCode );
            pTelcom_Interface->setString( DataKeyL1, Telegram_L2EA03::OperCode,       OperCode );
            pTelcom_Interface->setString( DataKeyL1, Telegram_L2EA03::RouteCode,      RouteCode);
            pTelcom_Interface->setLong  ( DataKeyL1, Telegram_L2EA03::AimTemp,           (long)AimTemp);
            //pTelcom_Interface->setLong  ( DataKeyL1, Telegram_L2EA03::ProdPracCarbonInj, ProdPracCarbonInj);
            //pTelcom_Interface->setLong  ( DataKeyL1, Telegram_L2EA03::ProdPracBurner,    ProdPracBurner);
            //pTelcom_Interface->setLong  ( DataKeyL1, Telegram_L2EA03::ProdPracElec,      ProdPracElec);
            //pTelcom_Interface->setLong  ( DataKeyL1, Telegram_L2EA03::ProdPracProcess,   ProdPracProcess);
            //pTelcom_Interface->setLong  ( DataKeyL1, Telegram_L2EA03::ProdPracMat,       ProdPracMat);
            //pTelcom_Interface->setLong  ( DataKeyL1, Telegram_L2EA03::ProdPracScrap,     ProdPracScrap);
            pTelcom_Interface->setLong  ( DataKeyL1, Telegram_L2EA03::UpdateFlag,        UpdateFlag);
            pTelcom_Interface->setLong  ( DataKeyL1, Telegram_L2EA03::HotHeelWeight,     HotHeelWeight);
            pTelcom_Interface->setString( DataKeyL1, Telegram_L2EA03::HeatIdCust,        CustHeatID);
            pTelcom_Interface->setString( DataKeyL1, Telegram_L2EA03::TreatIdCust,       CustTreatID);
            pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2EA03::Spare,             CIntfData::ToAny(seqSpare));

            //********    Dispatch event ***********************************************************************
            SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);

            //********    End processing data  ***********************************************************************
          }// if ( m_pPD_HEAT_DATA->getLastRow() == 1 )         // should be unique
          else
          {
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
          }
        }// if ( m_pPD_HEAT_DATA->select (HeatID, TreatID, Plant) )
        else
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
        }
      }// if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatId, CustTreatId) )
      else
      {
        RetValue = false;
      }

      log( TlgName + ": End", 3);

    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorPointerHandling(sMessage,Function.c_str()," pDM_Interface or pTelcom_Interface invalid ");
      RetValue=false;
    }

    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;

}


bool  CEAF_EventHandler::provideData_L2EA05BurnerPattern(CEventMessage& Event)
{	
  //=================    B U R N E R   D A T A    ===============================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();

  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID);
  long        PlantNo   = m_pGC_Plant_Container->getPlantNo(PlantID);
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  long        UnitNo    = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2EA05";
  std::string Function = "CEAF_EventHandler::provideData_L2EA05BurnerPattern";


  try
  {
    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    if ( pDM_Interface && pTelcom_Interface )
    {
      //********    preset data  ************************************************************************

      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);


      DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

      CIntfData::preset(seqSpare,0,5);

      //********    Read event related data  ************************************************************************
      seqEAFBurnerPredRes SeqEAFBurnerPredRes;
      sEAFBurnerPredRes   EAFBurnerPredRes;
      sEAFBurnerPredRes   PhaseSteps;

      SeqEAFBurnerPredRes = CIntfData::ToCORBAType(pDM_Interface->getEAFBurnerPredRes(ProductID.c_str(),DATA::EAFBurnerPredRes));

      //log(CIntfData::getContent(CIntfData::ToAny(SeqEAFBurnerPredRes)),4);

      //********    Log event data ***********************************************************************

      //********    Convert and check event data  ***********************************************************

      std::string LastPhase;
      long LastPhaseNo = 0;
      long LastStep    = 0;

      // prepare a container containing all relevant phasenames and steps to be sent to L1
      // regard steps to occour several times for same phase in EAFBurnerPredRes
      std::deque < sEAFBurnerPredRes > PhaseStepsInfo;
      for(long i = 0; i < CIntfData::getLength(SeqEAFBurnerPredRes) ; i++)
      {
        CIntfData::getAt(EAFBurnerPredRes,SeqEAFBurnerPredRes,i);

        PhaseSteps.Phase    = EAFBurnerPredRes.Phase;
        PhaseSteps.PhaseNo  = EAFBurnerPredRes.PhaseNo;
        PhaseSteps.Step     = EAFBurnerPredRes.Step;

        // store each step only once per phase
        if ( std::string(PhaseSteps.Phase) != DEF_GC_PHASE::Actual  && 
            (std::string(PhaseSteps.Phase) != LastPhase || PhaseSteps.PhaseNo != LastPhaseNo || PhaseSteps.Step != LastStep ) )
        {
          PhaseStepsInfo.push_back ( PhaseSteps );
        }
        
        LastPhase    = PhaseSteps.Phase;
        LastPhaseNo  = PhaseSteps.PhaseNo;
        LastStep     = PhaseSteps.Step;
      }

      if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
      {
        // truncate string data to fit telegram length
        HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
        TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

        DataKeyL1 = pTelcom_Interface->generateDataKey("L2EA05"); //new key for each message    

        DEF::seqLong  SeqPhaseNo;               
        DEF::seqLong  SeqPhaseType;
        DEF::seqLong  SeqBurnerStepSpecEgy;
        DEF::seqLong  SeqBurnerEgyTotal;
        DEF::seqLong  SeqFlameProfile_Burner_1;
        DEF::seqLong  SeqFlameProfile_Burner_2;
        DEF::seqLong  SeqFlameProfile_Burner_3;
        DEF::seqLong  SeqFlameProfile_Burner_4;
        DEF::seqLong  SeqFlameProfile_Burner_5;
        DEF::seqLong  SeqFlameProfile_DoorBurner;
        DEF::seqLong  SeqFlameProfile_EBTBurner;

        long SeqLenght = 50;

        CIntfData::preset(SeqPhaseNo                        , 0, SeqLenght); 
        CIntfData::preset(SeqPhaseType                      , 0, SeqLenght);
        CIntfData::preset(SeqBurnerStepSpecEgy              , 0, SeqLenght);
        CIntfData::preset(SeqBurnerEgyTotal                 , 0, SeqLenght);
        CIntfData::preset(SeqFlameProfile_Burner_1          , 0, SeqLenght);
        CIntfData::preset(SeqFlameProfile_Burner_2          , 0, SeqLenght);
        CIntfData::preset(SeqFlameProfile_Burner_3          , 0, SeqLenght);
        CIntfData::preset(SeqFlameProfile_Burner_4          , 0, SeqLenght);
        CIntfData::preset(SeqFlameProfile_Burner_5          , 0, SeqLenght);
        CIntfData::preset(SeqFlameProfile_DoorBurner        , 0, SeqLenght);
        CIntfData::preset(SeqFlameProfile_EBTBurner         , 0, SeqLenght);

        long Position                 = min( (long)PhaseStepsInfo.size(), SeqLenght );

        long FlameProfile_Burner_1    = 0;
        long FlameProfile_Burner_2    = 0;
        long FlameProfile_Burner_3    = 0;
        long FlameProfile_Burner_4    = 0; 
        long FlameProfile_Burner_5    = 0; 
        long FlameProfile_DoorBurner  = 0; 
        long FlameProfile_EBTBurner  = 0; 

        // reverse iteration over all phases and steps
        // the pattern are defend like "until certain energy, use profile X"
        // so we have to know the "next" profile durcin iteration if intermediate steps are
        // defined by different energy aims for several burners
        std::deque < sEAFBurnerPredRes >::reverse_iterator it;
        for( it = PhaseStepsInfo.rbegin(); it != PhaseStepsInfo.rend() ; it++)
        {
          PhaseSteps    = (*it);
          std::string Phase = std::string(PhaseSteps.Phase);
          long PhaseNo      = PhaseSteps.PhaseNo;
          long Step         = PhaseSteps.Step;

          Position-- ;

          //iteration over all steps
          for(long i = 0; i < CIntfData::getLength(SeqEAFBurnerPredRes) ; i++)
          {
            // only SeqLenght entries per field
            if ( i >= SeqLenght  )
            {
              continue;
            }

            CIntfData::getAt(EAFBurnerPredRes,SeqEAFBurnerPredRes,i);

            if ( EAFBurnerPredRes.PhaseNo             == PhaseNo && 
                 EAFBurnerPredRes.Step                == Step    && 
                 std::string(EAFBurnerPredRes.Phase)  == Phase )
            { 
              long L1PhaseNo    = GetL1PhaseNo(Phase,Plant,PhaseNo);
              long L1PhaseType  = GetL1PhaseType(Phase);

              std::string BurnerName    = EAFBurnerPredRes.BurnerName;
              long BurnerStepSpecEgy    = CDataConversion::RoundToLong(EAFBurnerPredRes.ElecEgyStep);
              long BurnerEgyTotal       = CDataConversion::RoundToLong(EAFBurnerPredRes.ElecEgy);
              long FlameProfile_Burner  = EAFBurnerPredRes.FlameProfile_Burner;

              CIntfData::setAt(SeqPhaseNo,          L1PhaseNo                           , Position);
              CIntfData::setAt(SeqPhaseType,        L1PhaseType                         , Position);
              CIntfData::setAt(SeqBurnerStepSpecEgy,BurnerStepSpecEgy                   , Position);
              CIntfData::setAt(SeqBurnerEgyTotal   ,BurnerEgyTotal                      , Position);

              // remember last burner profile, update on change of burner only
              if ( BurnerName == DEF_GCE_BURNER::Burner_1 )
              {
                FlameProfile_Burner_1 = FlameProfile_Burner;
              }
              else if ( BurnerName == DEF_GCE_BURNER::Burner_2 )
              {
                FlameProfile_Burner_2 = FlameProfile_Burner;
              }
              else if ( BurnerName == DEF_GCE_BURNER::Burner_3 )
              {
                FlameProfile_Burner_3 = FlameProfile_Burner;
              }
              else if ( BurnerName == DEF_GCE_BURNER::Burner_4 )
              {
                FlameProfile_Burner_4 = FlameProfile_Burner;
              }
              else if ( BurnerName == DEF_GCE_BURNER::DoorBurner )
              {
                FlameProfile_DoorBurner = FlameProfile_Burner;
              }
              else if ( BurnerName == DEF_GCE_BURNER::EBTBurner )
              {
                FlameProfile_EBTBurner = FlameProfile_Burner;
              }

              CIntfData::setAt(SeqFlameProfile_Burner_1,FlameProfile_Burner_1,Position);
              CIntfData::setAt(SeqFlameProfile_Burner_2,FlameProfile_Burner_2,Position);
              CIntfData::setAt(SeqFlameProfile_Burner_3,FlameProfile_Burner_3,Position);
              CIntfData::setAt(SeqFlameProfile_Burner_4,FlameProfile_Burner_4,Position);
              CIntfData::setAt(SeqFlameProfile_Burner_5,FlameProfile_Burner_5,Position);
              CIntfData::setAt(SeqFlameProfile_DoorBurner,FlameProfile_DoorBurner,Position);
              CIntfData::setAt(SeqFlameProfile_DoorBurner,FlameProfile_EBTBurner,Position);

            } // if ( EAFBurnerPredRes.PhaseNo == PhaseNo && 
          } // for(long i = 0; i < CIntfData::getLength(SeqEAFBurnerPredRes) ; i++)

          //********    Write telegram data  ***********************************************************************
          // ShiftCode     = CDataConversion::SetInvalidToDefault(ShiftCode      ,0  ,CSMC_DBData::unspecLong);

          // truncate data to fit telegram length
          // CustHeatID  = CDataConversion::CheckLengthAndTruncate(CustHeatID  ,10);

        } // for( it = Phases.begin(); it != Phases.end() ; it++)

        pTelcom_Interface->setString( DataKeyL1, Telegram_L2EA05::HeatId,            HeatID );
        pTelcom_Interface->setString( DataKeyL1, Telegram_L2EA05::TreatId,           TreatID );
        pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2EA05::CreateTime,        Now.asCORBAAny());

        pTelcom_Interface->setAny  ( DataKeyL1, Telegram_L2EA05::PhaseNo,                CIntfData::ToAny(SeqPhaseNo)); 
        pTelcom_Interface->setAny  ( DataKeyL1, Telegram_L2EA05::PhaseType,              CIntfData::ToAny(SeqPhaseType)); 

        pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2EA05::BurnerStepSpecEgy,     CIntfData::ToAny(SeqBurnerStepSpecEgy));
        //pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2EA05::BurnerElecEnergyTotal, CIntfData::ToAny(SeqBurnerEgyTotal));
        pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2EA05::FlameProfile_Burner_1, CIntfData::ToAny(SeqFlameProfile_Burner_1));
        pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2EA05::FlameProfile_Burner_2, CIntfData::ToAny(SeqFlameProfile_Burner_2));
        pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2EA05::FlameProfile_Burner_3, CIntfData::ToAny(SeqFlameProfile_Burner_3));
        pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2EA05::FlameProfile_Burner_4, CIntfData::ToAny(SeqFlameProfile_DoorBurner));
        pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2EA05::FlameProfile_Burner_5, CIntfData::ToAny(SeqFlameProfile_EBTBurner));

        pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2EA05::Spare,                 CIntfData::ToAny(seqSpare));

        pTelcom_Interface->showContent(DataKeyL1, 4);

        //********    Dispatch event ***********************************************************************
        SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);

        //********    End processing data  ***********************************************************************
      }// if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
      else
      {
        RetValue = false;
      }

      log( TlgName + ": End", 3);
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorPointerHandling(sMessage,Function.c_str()," pDM_Interface or pTelcom_Interface invalid ");
      RetValue=false;
    }

    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;
}


bool  CEAF_EventHandler::provideData_L2EA06HeatCancel(CEventMessage& Event)
{
  //=================    H E A T   C A N C E L L A I O N   ===============================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();

  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID);
  long 				PlantNo   = m_pGC_Plant_Container->getPlantNo(PlantID);
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  long 				UnitNo    = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2EA06";
  std::string Function = "CEAF_EventHandler::provideData_L2EA06HeatCancel";


  try
  {
    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    if ( pDM_Interface && pTelcom_Interface )
    {
      //********    preset data  ************************************************************************

     
      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);


      DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

      CIntfData::preset(seqSpare,0,5);

      //********    Read event related data  ************************************************************************

      //********    Log event data ***********************************************************************

      //********    Convert and check event data  ***********************************************************

      // in case of cancellation CustHeatID and CustTreatID may be invalid at DB
      CustHeatID  = CIntfData::ToStdString(pDM_Interface->getString(ProductID.c_str(), DATA::CustHeatID));
      CustTreatID = CIntfData::ToStdString(pDM_Interface->getString(ProductID.c_str(), DATA::CustTreatID));

      if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
      {
        // truncate string data to fit telegram length
        HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
        TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

        //********    Write telegram data  ***********************************************************************
        pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2EA06::UnitNo,        UnitNo);
        pTelcom_Interface->setString  ( DataKeyL1, Telegram_L2EA06::HeatId,        HeatID);
        pTelcom_Interface->setString  ( DataKeyL1, Telegram_L2EA06::TreatId,       TreatID);
        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA06::CreateTime,    Now.asCORBAAny());   
        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA06::Spare,         CIntfData::ToAny(seqSpare));

        //********    Dispatch event ***********************************************************************
        SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);

        //********    End processing data  ***********************************************************************
      }// if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
      else
      {
        RetValue = false;
      }

      log( TlgName + ": End", 3);
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorPointerHandling(sMessage,Function.c_str()," pDM_Interface or pTelcom_Interface invalid ");

      RetValue=false;
    }

    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;

}



bool  CEAF_EventHandler::provideData_L2EA07CompMode(CEventMessage& Event)
{
  //=================    C O M P U T E R   M O D E S     ===============================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();

  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID);
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  long UnitNo           = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2EA07";
  std::string Function = "CEAF_EventHandler::provideData_L2EA07CompMode";

  try
  {
    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    if ( pDM_Interface && pTelcom_Interface )
    {
      //********    preset data  ************************************************************************

     
      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);


      DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

      CIntfData::preset(seqSpare,0,5);

      //********    Read event related data  ************************************************************************
      long ModeElec     = 0;
      long ModeInj      = 0;
      long ModeMat      = 0;
      long ModeBurner   = 0;
      long ModeStirring = 0;
      long ModePatternFeed  = 0;    
      long ModeTappingBatch = 0; // GEPA:Not used for Fuxin    

      //read the Computer Mode Availabilitys from L2
      seqComputerModes SeqComputerModes = CIntfData::ToCORBAType(pDM_Interface->getComputerModes (ProductID.c_str(), DATA::ComputerModeAvail));

      log(CIntfData::getContent(CIntfData::ToAny(SeqComputerModes)),4);

      //********    Log event data ***********************************************************************

      //********    Convert and check event data  ***********************************************************

      if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
      {
        // truncate string data to fit telegram length
        HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
        TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);


        for (long ii=0; ii < CIntfData::getLength(SeqComputerModes); ii++)
        {
          sComputerMode ComputerMode;

          if (CIntfData::getAt(ComputerMode, SeqComputerModes, ii) && ComputerMode.Status > 0)
          {
            //set the status for bottom stirring mode
            if (std::string(ComputerMode.Device) == std::string(DEF_COMP_MODES::Electric))
            {
              ModeElec      = 1;
            }
            if (std::string(ComputerMode.Device) == std::string(DEF_COMP_MODES::Injection))
            {
              ModeInj       = 1;
            }
            if (std::string(ComputerMode.Device) == std::string(DEF_COMP_MODES::MatHandle))
            {
              ModeMat       = 1;
            }
            // FUXIN specific, ComputerMode Burner from/for L1 is represented by ComputerMode GasLance in L2
            if (std::string(ComputerMode.Device) == std::string(DEF_COMP_MODES::GasLance) || 
                std::string(ComputerMode.Device) == std::string(DEF_COMP_MODES::Burner)  )
            {
              ModeBurner    = 1;
            }
            if (std::string(ComputerMode.Device) == std::string(DEF_COMP_MODES::Stirring))
            {
              ModeStirring  = 1;
            }
            if (std::string(ComputerMode.Device) == std::string(DEF_COMP_MODES::PatternFeed))
            {
              ModePatternFeed   = 1;
            }
            if (std::string(ComputerMode.Device) == std::string(DEF_COMP_MODES::TappingBatch)) 
            {
              ModeTappingBatch   = 1;
            }
          }// if (CIntfData::getAt(ComputerMode, SeqComputerModes, ii) && ComputerMode.Status > 0)
        } // for (long ii=0; ii < CIntfData::getLength(SeqComputerModes); ii++)

        std::stringstream tmp_comp;
        tmp_comp << "******* ComputerModeAvail data *********" << endl
          << "ModeElec        " <<  ModeElec <<  endl
          << "ModeInj         " <<  ModeInj <<  endl
          << "MatHandle       " <<  ModeMat <<  endl
          << "ModeBurner      " <<  ModeBurner <<  endl
          << "Stirring        " <<  ModeStirring <<  endl
          << "ModePatternFeed " <<  ModePatternFeed <<  endl;

        CDH_OUT_Task::getInstance()->setStateDetails(DATA::ComputerModeAvail, tmp_comp.str(),4);

        //********    Write telegram data  ***********************************************************************
        pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2EA07::UnitNo,        UnitNo);
        pTelcom_Interface->setString  ( DataKeyL1, Telegram_L2EA07::HeatId,        HeatID);
        pTelcom_Interface->setString  ( DataKeyL1, Telegram_L2EA07::TreatId,       TreatID);
        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA07::CreateTime,    Now.asCORBAAny());   

        pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2EA07::ModeElec,         ModeElec);
        pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2EA07::ModeInj,          ModeInj);
        pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2EA07::ModeMat,          ModeMat);
        pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2EA07::ModeBurner,       ModeBurner);
        pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2EA07::ModeStirring,     ModeStirring);
        pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2EA07::ModePatternFeed,  ModePatternFeed);
        pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2EA07::ModeTappingBatch, ModeTappingBatch);
        
        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA07::Spare,         CIntfData::ToAny(seqSpare));

        //********    Dispatch event ***********************************************************************
        SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);

        //********    End processing data  ***********************************************************************

        log( TlgName + ": End", 3);
      } // if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorPointerHandling(sMessage,Function.c_str()," pDM_Interface or pTelcom_Interface invalid ");

      RetValue=false;
    }
    
    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;

}



bool  CEAF_EventHandler::provideData_L2EA23ReleaseElectrodes(CEventMessage& Event)
{
  //=================   R E A L E A S E   E L E C T R O D E S    ===============================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();

  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID);
  long 				PlantNo   = m_pGC_Plant_Container->getPlantNo(PlantID);
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  long 				UnitNo    = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2EA23";
  std::string Function = "CEAF_EventHandler::provideData_L2EA23ReleaseElectrodes";


  try
  {
    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    if ( pDM_Interface && pTelcom_Interface )
    {
      //********    preset data  ************************************************************************

     
      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);


      DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

      CIntfData::preset(seqSpare,0,5);

      //********    Read event related data  ************************************************************************

      //********    Log event data ***********************************************************************

      //********    Convert and check event data  ***********************************************************

      if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
      {
        // truncate string data to fit telegram length
        HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
        TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

        // ShiftCode     = CDataConversion::SetInvalidToDefault(ShiftCode      ,0  ,CSMC_DBData::unspecLong);

        // truncate data to fit telegram length
        // CustHeatID  = CDataConversion::CheckLengthAndTruncate(CustHeatID  ,10);

        //********    Write telegram data  ***********************************************************************
        pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2EA23::UnitNo,        UnitNo);
        pTelcom_Interface->setString  ( DataKeyL1, Telegram_L2EA23::HeatId,        HeatID);
        pTelcom_Interface->setString  ( DataKeyL1, Telegram_L2EA23::TreatId,       TreatID);
        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA23::CreateTime,    Now.asCORBAAny());   

        if(Event.getMessage() == EAF_EvMsg::evEAFElectrodeHydraulicSystemInhibitRequest)
        {
          pTelcom_Interface->setLong( DataKeyL1,Telegram_L2EA23::ActionFlag, 0);
          CDH_OUT_Task::getInstance()->setStateDetails(DATA::ElecInhibitReq, " no",4);
        }
        else if(Event.getMessage() == EAF_EvMsg::evEAFElectrodeHydraulicSystemReleaseRequest)
        {
          pTelcom_Interface->setLong( DataKeyL1,Telegram_L2EA23::ActionFlag, 1);
          CDH_OUT_Task::getInstance()->setStateDetails(DATA::ElecInhibitReq, " yes", 4);
        }
        else
        {
          pTelcom_Interface->setLong( DataKeyL1,Telegram_L2EA23::ActionFlag, 0);
          CDH_OUT_Task::getInstance()->setStateDetails(DATA::ElecInhibitReq, " no", 4);
        }

        pTelcom_Interface->setLong( DataKeyL1,Telegram_L2EA23::FurnaceBreakerOff, 2);
        CDH_OUT_Task::getInstance()->setStateDetails(Telegram_L2EA23::FurnaceBreakerOff, " Operator decision", 4);

        pTelcom_Interface->setAny   ( DataKeyL1,Telegram_L2EA23::Spare,            CIntfData::ToAny(seqSpare));

        //********    Dispatch event ***********************************************************************
        SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);

        //********    End processing data  ***********************************************************************
      }// if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatId, CustTreatId) )
      else
      {
        RetValue = false;
      }

      log( TlgName + ": End", 3);

    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorPointerHandling(sMessage,Function.c_str()," pDM_Interface or pTelcom_Interface invalid ");
      RetValue=false;
    }
    
    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;

}


bool  CEAF_EventHandler::provideData_L2EA32CarbonInjPattern(CEventMessage& Event)
{
  //=================    C A R B O N   I N J E C T I O N   D A T A    ===============================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();

  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID);
  long        PlantNo   = m_pGC_Plant_Container->getPlantNo(PlantID);
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  long        UnitNo    = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2EA32";
  std::string Function = "CEAF_EventHandler::provideData_L2EA32CarbonInjPattern";


  try
  {
    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    if ( pDM_Interface && pTelcom_Interface )
    {
      //********    preset data  ************************************************************************

     
      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);


      DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

      CIntfData::preset(seqSpare,0,5);

      //********    Read event related data  ************************************************************************
      seqEAFInjectLance SeqEAFInjectLance;
      sEAFInjectLance   EAFInjectLance;

      SeqEAFInjectLance = CIntfData::ToCORBAType(pDM_Interface->getEAFInjectLance(ProductID.c_str(),DATA::EAFInjectLance));

      //log(CIntfData::getContent(CIntfData::ToAny(SeqEAFInjectLance)),4);


      //********    Log event data ***********************************************************************

      //********    Convert and check event data  ***********************************************************

      // prepare a container containing all relevant phasenames to be sent to L1
      std::deque < std::pair<std::string, long> > Phases;
      for(long i = 0; i < CIntfData::getLength(SeqEAFInjectLance) ; i++)
      {
        CIntfData::getAt(EAFInjectLance,SeqEAFInjectLance,i);

        std::string PhaseName = EAFInjectLance.Phase;
        long        PhaseNo   = EAFInjectLance.PhaseNo;

        if ( PhaseName != DEF_GC_PHASE::Actual )
        {
          Phases.push_back ( std::make_pair(PhaseName,PhaseNo) );
        }
      }

      if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
      {
        // truncate string data to fit telegram length
        HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
        TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

        DataKeyL1 = pTelcom_Interface->generateDataKey("L2EA32"); //new key for each message

        DEF::seqLong  SeqPhaseNo;               
        DEF::seqLong  SeqPhaseType;
        DEF::seqLong  SeqInjectorNo;
        DEF::seqLong  SeqElecEnergyStep;
        DEF::seqLong  SeqElecEnergyTotal;
        DEF::seqLong  SeqRatioCarbDust;
        DEF::seqLong  SeqMatFlowRate;

        long SeqLenght = 50;

        CIntfData::preset(SeqPhaseNo,         0, SeqLenght); 
        CIntfData::preset(SeqPhaseType,       0, SeqLenght);
        CIntfData::preset(SeqInjectorNo,      0, SeqLenght); // always 0, ther are no injector specific setpoints

        CIntfData::preset(SeqElecEnergyStep,  0, SeqLenght);
        CIntfData::preset(SeqElecEnergyTotal, 0, SeqLenght);
        CIntfData::preset(SeqRatioCarbDust,   0, SeqLenght); // always 0%, there is no dust
        CIntfData::preset(SeqMatFlowRate,     0, SeqLenght);

        //iteration over all steps
        for(long i = 0; i < CIntfData::getLength(SeqEAFInjectLance) ; i++)
        {
          // only SeqLenght entries per field
          if ( i >= SeqLenght  )
          {
            continue;
          }

          CIntfData::getAt(EAFInjectLance,SeqEAFInjectLance,i);

          std::string Phase       = EAFInjectLance.Phase;
          long        PhaseNo     = EAFInjectLance.PhaseNo;

          //if ( EAFInjectLance.PhaseNo             == PhaseNo && 
          //     std::string(EAFInjectLance.Phase)  == Phase )
          //{
          //if ( Phase == DEF_GC_TREATMENTPHASE_DEF::Preparation )
          //{
          //  PhaseType        = 1; // Preheating
          //  PhaseNo          = 1;
          //}
          //else if ( Phase == DEF_GC_TREATMENTPHASE_DEF::MeltBskNo )
          //{
          //  PhaseType        = 2; // Basket
          //}
          //else if ( Phase == DEF_GC_TREATMENTPHASE_DEF::Refining )
          //{
          //  PhaseType        = 10; // Refining
          //  PhaseNo          = 1;
          //}

          long L1PhaseNo    = GetL1PhaseNo(Phase,Plant,PhaseNo);
          long L1PhaseType  = GetL1PhaseType(Phase);

          if ( L1PhaseType != CSMC_DBData::unspecLong )
          {
            long ElecEgyStep                      = CDataConversion::RoundToLong(EAFInjectLance.ElecEgyStep);
            long ElecEnergyTotal                  = CDataConversion::RoundToLong(EAFInjectLance.Egy);
            seqInjectLanceData SeqInjectLanceData = EAFInjectLance.InjectFlow;

            double MatFlowRate            = 0.;

            for(long j = 0; j < CIntfData::getLength(SeqInjectLanceData) ; j++)
            {
              sInjectLanceData InjectLanceData;
              CIntfData::getAt(InjectLanceData,SeqInjectLanceData,j);

              MatFlowRate += InjectLanceData.Value;
            }

            CIntfData::setAt(SeqPhaseNo,        L1PhaseNo         ,  i );
            CIntfData::setAt(SeqPhaseType,      L1PhaseType       ,  i );

            CIntfData::setAt(SeqElecEnergyStep,  ElecEgyStep      ,  i );
            CIntfData::setAt(SeqElecEnergyTotal, ElecEnergyTotal  ,  i );
            CIntfData::setAt(SeqMatFlowRate,    long(MatFlowRate) ,  i );
          }// if ( L1PhaseType != CSMC_DBData::unspecLong )
        } // for(long i = 0; i < CIntfData::getLength(SeqEAFInjectLance) ; i++)

        //********    Write telegram data  ***********************************************************************
        // ShiftCode     = CDataConversion::SetInvalidToDefault(ShiftCode      ,0  ,CSMC_DBData::unspecLong);

        // truncate data to fit telegram length
        // CustHeatID  = CDataConversion::CheckLengthAndTruncate(CustHeatID  ,10);
        //} // for( it = Phases.begin(); it != Phases.end() ; it++)

        pTelcom_Interface->setString( DataKeyL1, Telegram_L2EA32::HeatId,           HeatID );
        pTelcom_Interface->setString( DataKeyL1, Telegram_L2EA32::TreatId,          TreatID );
        pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2EA32::CreateTime,       Now.asCORBAAny());

        pTelcom_Interface->setAny  ( DataKeyL1, Telegram_L2EA05::PhaseNo,           CIntfData::ToAny(SeqPhaseNo)); 
        pTelcom_Interface->setAny  ( DataKeyL1, Telegram_L2EA05::PhaseType,         CIntfData::ToAny(SeqPhaseType)); 
        pTelcom_Interface->setAny  ( DataKeyL1, Telegram_L2EA32::InjectorNo,        CIntfData::ToAny(SeqInjectorNo));  

        pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2EA32::ElecEnergyStep,   CIntfData::ToAny(SeqElecEnergyStep));
        //pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2EA32::ElecEnergyTotal,  CIntfData::ToAny(SeqElecEnergyTotal));
        pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2EA32::RatioCarbDust,    CIntfData::ToAny(SeqRatioCarbDust));
        pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2EA32::MatFlowRate,      CIntfData::ToAny(SeqMatFlowRate));

        pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2EA32::Spare,            CIntfData::ToAny(seqSpare));

        pTelcom_Interface->showContent(DataKeyL1, 4);

        //********    Dispatch event ***********************************************************************
        SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);

        //********    End processing data  ***********************************************************************
      } // if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
      else
      {
        RetValue = false;
      }

      log( TlgName + ": End", 3);

    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorPointerHandling(sMessage,Function.c_str()," pDM_Interface or pTelcom_Interface invalid ");
      RetValue=false;
    }

    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;

}


bool  CEAF_EventHandler::provideData_L2EA40ProcessPattern(CEventMessage& Event)
{

  //=================    P R O C E S S   P A T T E R N   ===============================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();

  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID);
  long 				PlantNo   = m_pGC_Plant_Container->getPlantNo(PlantID);
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  long 				UnitNo    = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2EA40";
  std::string Function = "CEAF_EventHandler::provideData_L2EA40ProcessPattern";


  try
  {
    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    if ( pDM_Interface && pTelcom_Interface )
    {
      //********    preset data  ************************************************************************

     
      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);


      DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

      CIntfData::preset(seqSpare,0,5);

      //********    Read event related data  ************************************************************************

      seqEAFProcessPredRes  SeqEAFProcessPredRes   = CIntfData::ToCORBAType(pDM_Interface->getEAFProcessPredRes ( ProductID.c_str(), DATA::EAFProcessPredRes));
      seqEAFGasLancePredRes SeqEAFGasLancePredRes  = CIntfData::ToCORBAType(pDM_Interface->getEAFGasLancePredRes( ProductID.c_str(), DATA::EAFGasLancePredRes));
      seqEAFMatFeedPredRes  SeqEAFMatFeedPredRes   = CIntfData::ToCORBAType(pDM_Interface->getEAFMatFeedPredRes ( ProductID.c_str(), DATA::EAFMatFeedPredRes));

      sEAFProcessPredRes  EAFProcessPredRes;
      sEAFGasLancePredRes EAFGasLancePredRes;
      sEAFMatFeedPredRes  EAFMatFeedPredRes;

      //********    Log event data ***********************************************************************

      //********    Convert and check event data  ***********************************************************

      if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
      {
        // truncate string data to fit telegram length
        HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
        TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

        DEF::seqLong    SeqPhaseNo;               
        DEF::seqLong    SeqPhaseType;             
        DEF::seqLong    SeqAimVoltTap;            
        DEF::seqLong    SeqAimCurveNo;            
        DEF::seqLong    SeqAimReactorTap;            
        DEF::seqDouble  SeqRemDurStep;            
        DEF::seqLong    SeqElecEnergyStep;        
        DEF::seqLong    SeqElecEnergyTotal;        
        DEF::seqDouble  SeqFlowRateO2DoorLance_1;  
        DEF::seqDouble  SeqFlowRateO2DoorLance_2;  
        DEF::seqDouble  SeqFeedingRate_1;          
        DEF::seqDouble  SeqFeedingRate_2;          
        DEF::seqDouble  SeqFeedingRate_3;          
        DEF::seqDouble  SeqFeedingRate_4;
        DEF::seqDouble  SeqFeedingRate_5; 
        DEF::seqDouble  SeqFeedingRate_6; 
        DEF::seqDouble  SeqFeedingRate_7; 
        std::string     MatCode_1;                
        std::string     MatCode_2;                
        std::string     MatCode_3;               
        std::string     MatCode_4;
        std::string     MatCode_5; 
        std::string     MatCode_6; 
        std::string     MatCode_7; 
        long            BaseWeight	= 0;          

        long SeqLenght                = 50;

        CIntfData::preset(SeqPhaseNo               ,0 ,SeqLenght); 
        CIntfData::preset(SeqPhaseType             ,0 ,SeqLenght); 
        CIntfData::preset(SeqAimVoltTap            ,0 ,SeqLenght); 
        CIntfData::preset(SeqAimCurveNo            ,0 ,SeqLenght); 
        CIntfData::preset(SeqAimReactorTap         ,0 ,SeqLenght); 
        CIntfData::preset(SeqRemDurStep            ,0.,SeqLenght); 
        CIntfData::preset(SeqElecEnergyStep        ,0 ,SeqLenght); 
        CIntfData::preset(SeqElecEnergyTotal       ,0 ,SeqLenght); 
        CIntfData::preset(SeqFlowRateO2DoorLance_1 ,0.,SeqLenght); 
        CIntfData::preset(SeqFlowRateO2DoorLance_2 ,0.,SeqLenght); 
        CIntfData::preset(SeqFeedingRate_1         ,0.,SeqLenght); 
        CIntfData::preset(SeqFeedingRate_2         ,0.,SeqLenght); 
        CIntfData::preset(SeqFeedingRate_3         ,0.,SeqLenght); 
        CIntfData::preset(SeqFeedingRate_4         ,0.,SeqLenght);
        CIntfData::preset(SeqFeedingRate_5         ,0.,SeqLenght); 
        CIntfData::preset(SeqFeedingRate_6         ,0.,SeqLenght); 
        CIntfData::preset(SeqFeedingRate_7         ,0.,SeqLenght); 

        //iteration over all steps
        for(long i = 0; i < CIntfData::getLength(SeqEAFProcessPredRes) ; i++)
        {
          // only SeqLenght entries per field
          if ( i >= SeqLenght  )
          {
            //continue;
            break;
          }

          CIntfData::getAt(EAFProcessPredRes,SeqEAFProcessPredRes,i);

          std::string Phase       = EAFProcessPredRes.Phase;
          long        PhaseNo     = EAFProcessPredRes.PhaseNo;

          //if ( Phase == DEF_GC_TREATMENTPHASE_DEF::Preparation )
          //{
          //  PhaseType        = 1; // Preheating
          //  PhaseNo          = 1;
          //}
          //else if ( Phase == DEF_GC_TREATMENTPHASE_DEF::MeltBskNo )
          //{
          //  PhaseType        = 2; // Basket
          //}
          //else if ( Phase == DEF_GC_TREATMENTPHASE_DEF::Refining )
          //{
          //  PhaseType        = 10; // Refining
          //  PhaseNo          = 1;
          //}

          long L1PhaseNo    = GetL1PhaseNo(Phase,Plant,PhaseNo);
          long L1PhaseType  = GetL1PhaseType(Phase);

          CIntfData::setAt(SeqPhaseNo,          L1PhaseNo                           , i);
          CIntfData::setAt(SeqPhaseType,        L1PhaseType                         , i);
          CIntfData::setAt(SeqAimVoltTap,       EAFProcessPredRes.VoltTap           , i);
          CIntfData::setAt(SeqAimCurveNo,       EAFProcessPredRes.ImpCurve          , i);
          CIntfData::setAt(SeqAimReactorTap,    EAFProcessPredRes.ReactorTap        , i);
          CIntfData::setAt(SeqRemDurStep,       EAFProcessPredRes.DurStep           , i);
          CIntfData::setAt(SeqElecEnergyStep,   CDataConversion::RoundToLong(EAFProcessPredRes.ElecEgyStep) , i);
          CIntfData::setAt(SeqElecEnergyTotal,  CDataConversion::RoundToLong(EAFProcessPredRes.ElecEgy)     , i);
          
          long Step = EAFProcessPredRes.Step;

          for(long j = 0; j < CIntfData::getLength(SeqEAFGasLancePredRes) ; j++)
          {
            CIntfData::getAt(EAFGasLancePredRes,SeqEAFGasLancePredRes,j);
            
            if(std::string(EAFGasLancePredRes.Phase)  == Phase    && 
                           EAFGasLancePredRes.PhaseNo == PhaseNo  && 
                           EAFGasLancePredRes.Step    == Step)
            {

              //if ( EAFGasLancePredRes.DeviceNo == 1 )
              //{
              //  // JAST CIntfData::setAt(SeqFlowRateO2DoorLance_1,  EAFGasLancePredRes.O2Flow, i);
              //}
              //else if ( EAFGasLancePredRes.DeviceNo == 2 )
              //{
              //  // JAST CIntfData::setAt(SeqFlowRateO2DoorLance_2,  EAFGasLancePredRes.O2Flow, i);
              //}
            }
          }

          for(long k = 0; k < CIntfData::getLength(SeqEAFMatFeedPredRes) ; k++)
          {
            CIntfData::getAt(EAFMatFeedPredRes,SeqEAFMatFeedPredRes,k);

            if(std::string(EAFMatFeedPredRes.PhaseName) == Phase    && 
                           EAFMatFeedPredRes.BasketNo   == PhaseNo  && 
                           EAFMatFeedPredRes.Step       == Step)
            {
              seqBatch SeqBatch = EAFMatFeedPredRes.MatFeedData;        

              // up to 7 materials per step
              long Materials = CIntfData::getLength(SeqBatch);

              for(long p = 0; p < Materials; p++)
              {
                sBatch sBatch;
                CIntfData::getAt(sBatch,SeqBatch,p);

                if( p == 0 )
                {
                  MatCode_1   = sBatch.MatCode;
                  CIntfData::setAt(SeqFeedingRate_1,  sBatch.MatFeedSpeed, i);
                }
                else if( p == 1 )
                {
                  MatCode_2   = sBatch.MatCode;
                  CIntfData::setAt(SeqFeedingRate_2,  sBatch.MatFeedSpeed, i);
                }
                else if( p == 2 )
                {
                  MatCode_3   = sBatch.MatCode;
                  CIntfData::setAt(SeqFeedingRate_3,  sBatch.MatFeedSpeed, i);
                }
                else if( p == 3 )
                {
                  MatCode_4   = sBatch.MatCode;
                  CIntfData::setAt(SeqFeedingRate_4,  sBatch.MatFeedSpeed, i);
                }
                else if( p == 4 )
                {
                  MatCode_5   = sBatch.MatCode;
                  CIntfData::setAt(SeqFeedingRate_5,  sBatch.MatFeedSpeed, i);
                }
                else if( p == 5 )
                {
                  MatCode_6   = sBatch.MatCode;
                  CIntfData::setAt(SeqFeedingRate_6,  sBatch.MatFeedSpeed, i);
                }
                else if( p == 6 )
                {
                  MatCode_7   = sBatch.MatCode;
                  CIntfData::setAt(SeqFeedingRate_7,  sBatch.MatFeedSpeed, i);
                }
      

              } // for(long p = 0; p < CIntfData::getLength(SeqBatch); p++)
            } // if(std::string(EAFMatFeedPredRes.PhaseName) == Phase    && 
          } // for(long k = 0; k < CIntfData::getLength(SeqEAFMatFeedPredRes) ; k++)
        } // for( it = Phases.begin(); it != Phases.end() ; it++)

        //********    Write telegram data  ***********************************************************************
        pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2EA40::UnitNo,        UnitNo);
        pTelcom_Interface->setString  ( DataKeyL1, Telegram_L2EA40::HeatId,        HeatID);
        pTelcom_Interface->setString  ( DataKeyL1, Telegram_L2EA40::TreatId,       TreatID);
        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA40::CreateTime,    Now.asCORBAAny());   

        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA40::PhaseNo                ,CIntfData::ToAny(SeqPhaseNo));               
        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA40::PhaseType              ,CIntfData::ToAny(SeqPhaseType));             
        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA40::AimVoltTap             ,CIntfData::ToAny(SeqAimVoltTap));            
        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA40::AimCurveNo             ,CIntfData::ToAny(SeqAimCurveNo));            
        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA40::AimReactorTap          ,CIntfData::ToAny(SeqAimReactorTap));            
        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA40::RemDurStep             ,CIntfData::ToAny(SeqRemDurStep));            
        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA40::ElecEnergyStep         ,CIntfData::ToAny(SeqElecEnergyStep));        
        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA40::ElecEnergyTotal        ,CIntfData::ToAny(SeqElecEnergyTotal));        
        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA40::FlowRateO2_DoorLance   ,CIntfData::ToAny(SeqFlowRateO2DoorLance_1));  
        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA40::FlowRateO2_EBTLance    ,CIntfData::ToAny(SeqFlowRateO2DoorLance_2));  
        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA40::FeedingRate_1          ,CIntfData::ToAny(SeqFeedingRate_1));          
        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA40::FeedingRate_2          ,CIntfData::ToAny(SeqFeedingRate_2));          
        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA40::FeedingRate_3          ,CIntfData::ToAny(SeqFeedingRate_3));          
        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA40::FeedingRate_4          ,CIntfData::ToAny(SeqFeedingRate_4)); 
        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA40::FeedingRate_5          ,CIntfData::ToAny(SeqFeedingRate_5));
        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA40::FeedingRate_6          ,CIntfData::ToAny(SeqFeedingRate_6));
        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA40::FeedingRate_7          ,CIntfData::ToAny(SeqFeedingRate_7));
        pTelcom_Interface->setString  ( DataKeyL1, Telegram_L2EA40::MatCode_1              ,MatCode_1);                
        pTelcom_Interface->setString  ( DataKeyL1, Telegram_L2EA40::MatCode_2              ,MatCode_2);                
        pTelcom_Interface->setString  ( DataKeyL1, Telegram_L2EA40::MatCode_3              ,MatCode_3);                
        pTelcom_Interface->setString  ( DataKeyL1, Telegram_L2EA40::MatCode_4              ,MatCode_4);
        //pTelcom_Interface->setString  ( DataKeyL1, Telegram_L2EA40::MatCode_5              ,MatCode_5);
        //pTelcom_Interface->setString  ( DataKeyL1, Telegram_L2EA40::MatCode_6              ,MatCode_6);
        //pTelcom_Interface->setString  ( DataKeyL1, Telegram_L2EA40::MatCode_7              ,MatCode_7);
        pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2EA40::BaseWeight             ,BaseWeight);          

        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA40::Spare,                  CIntfData::ToAny(seqSpare));

        pTelcom_Interface->showContent(DataKeyL1,4);

        //********    Dispatch event ****** *****************************************************************
        SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);

        //********    End processing data  ***********************************************************************
      }// if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatId, CustTreatId) )
      else
      {
        RetValue = false;
      }

      log( TlgName + ": End", 3);

    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorPointerHandling(sMessage,Function.c_str()," pDM_Interface or pTelcom_Interface invalid ");
      RetValue=false;
    }
    
    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;
}


bool  CEAF_EventHandler::provideData_L2EA41ProcessValues(CEventMessage& Event)
{
  bool RetValue = true; // assume success

  //------------ read the data from Event ------------------
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID(); 
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID); // =  DEF_GC_PLANT_DEF::EAF
  long UnitNo           = m_pGC_Plant_Container->getPlantNo(PlantID);


  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2EA41";
  std::string Function = "CEAF_EventHandler::provideData_L2EA41ProcessValues";

  try
  {
    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    if ( pDM_Interface && pTelcom_Interface )
    {
      if ( !HeatID.empty() && HeatID != DEF::Inv_String )
      {       
        // truncate string data to fit telegram length
        HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
        TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

        OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

        //********    preset data  ************************************************************************

        log("****************************************************************************************", 3);
        log( TlgName + ": Start", 3);
        log("****************************************************************************************", 3);


        DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

        CIntfData::preset(seqSpare,0,5);
        std::string curPhaseName;

        long PhaseNo          = 0;
        long PhaseType        = 0;
        //Electric
        long AimVoltTap       = 0   ;
        long AimCurveNo       = 0   ;
        long AimReactTapNo    = 0   ;
        long ElecEnergyStep   = 0  ;
        long ElecEnergyTotal  = 0;

        long AmountO2Total    = 0;
        long RatioCarbDust    = 0; // always 0%, there is no dust

        double RemDurStep           = 0;
        double NextPhaseEnergyTotal = 0;

        // burner / O2 lance
        double FlowRateO2_SideLance_1 = 0;
        double FlowRateO2_SideLance_2 = 0;
        double FlowRateO2_SideLance_3 = 0;
        double FlowRateO2_SideLance_4 = 0;
        double FlowRateO2_SideLance_5 = 0;
        double FlowRateO2_DoorLance   = 0;
        double FlowRateO2_EBTLance    = 0;

        double FlowRateC_SideLance_1        = 0.;
        double FlowRateC_SideLance_2        = 0.;
        double MatFlowRateEBTDoor_1         = 0.;
        double MatFlowRateEBTDoor_2         = 0.;
        double AmountC_SideLance_1          = 0.;
        double AmountC_SideLance_2          = 0.;
        double AmountC_EBTLance             = 0.;
        double AmountC_DoorLance           = 0.;


        //Mat Feeding
        std::string     MatCode_1;                
        std::string     MatCode_2;                
        std::string     MatCode_3;               
        std::string     MatCode_4;
        std::string     MatCode_5; 
        std::string     MatCode_6; 
        std::string     MatCode_7;
        std::string     MatCode_8;
        std::string     MatCode_9;

        //int  lMatWeight ;
        double FeedingRate_1 = 0;
        double FeedingRate_2 = 0;
        double FeedingRate_3 = 0;
        double FeedingRate_4 = 0;
        double FeedingRate_5 = 0;
        double FeedingRate_6 = 0;
        double FeedingRate_7 = 0;
        double FeedingRate_8 = 0;
        double FeedingRate_9 = 0;

        double TargetAmount_1 = 0;
        double TargetAmount_2 = 0;
        double TargetAmount_3 = 0;
        double TargetAmount_4 = 0;
        double TargetAmount_5 = 0;
        double TargetAmount_6 = 0;
        double TargetAmount_7 = 0;
        double TargetAmount_8 = 0;
        double TargetAmount_9 = 0;

        long lngStirrGasType      = 0;


        seqEAFProcessPredRes  SeqEAFProcessPredRes  = CIntfData::ToCORBAType(pDM_Interface->getEAFProcessPredRes( ProductID.c_str(), DATA::EAFProcessPredRes));
        seqPredRes SeqEAFPredRes                    = CIntfData::ToCORBAType(pDM_Interface->getPredRes          ( ProductID.c_str(), DATA::EAFPredRes));
        seqGasLanceData SeqEAFBurnerAmount          = CIntfData::ToCORBAType(pDM_Interface->getGasLanceData     ( ProductID.c_str(), DATA::EAFBurnerAmount));
        seqGasLanceData SeqEAFGasLanceAmount        = CIntfData::ToCORBAType(pDM_Interface->getGasLanceData     ( ProductID.c_str(), DATA::EAFGasLanceAmount));
        seqInjectLanceData SeqEAFInjectLanceAmount  = CIntfData::ToCORBAType(pDM_Interface->getInjectLanceData  ( ProductID.c_str(), DATA::EAFInjectLanceAmount));
        seqBatch seqRecipeContent                   = CIntfData::ToCORBAType(pDM_Interface->getBatch            ( ProductID.c_str(), DATA::RecipeContent));

				log(CIntfData::getContent(CIntfData::ToAny(SeqEAFInjectLanceAmount)),4);

        long BaseWeight          = (long)pDM_Interface->getDouble(ProductID.c_str(),DATA::AimWeight);

        double StirrGasFlow       = pDM_Interface->getDouble(ProductID.c_str(),DATA::EAFActSetPointStirrFlow);
        std::string StirrGasType  = pDM_Interface->getString(ProductID.c_str(),DATA::EAFActSetPointStirrGasType);

        //First get Phase and PhaseNO
        long currentPhaseNo = 0;

        sPredRes PredRes;
        for (int i = 0 ; i < CIntfData::getLength(SeqEAFPredRes); ++i)
        {
          CIntfData::getAt(PredRes, SeqEAFPredRes, i);

          if(PredRes.PhaseActive == 1)
          {
            curPhaseName    = PredRes.Phase;
            currentPhaseNo  = PredRes.PhaseNo;
            RemDurStep      = PredRes.GenRes.DurPhase;
            ElecEnergyStep  = 0;///Not needed
            ElecEnergyTotal = CDataConversion::RoundToLong(PredRes.GenRes.MetTimeStamp.Elec_Moment); //Not needed
            //lBaseMass = PredRes.GenRes.SteelWeight;
            break;
          }
        }

        PhaseNo   = GetL1PhaseNo(curPhaseName,Plant,currentPhaseNo); //get PhaseNo from GC_Phase
        PhaseType = GetL1PhaseType(curPhaseName);

        if ( PhaseType != CSMC_DBData::unspecLong )
        {
          //get electric related info
          AimVoltTap    = pDM_Interface->getLong(ProductID.c_str(),DATA::VoltTapNoAim);
          AimCurveNo    = pDM_Interface->getLong(ProductID.c_str(),DATA::ElectrodRegCurveAim);
          AimReactTapNo = pDM_Interface->getLong(ProductID.c_str(),DATA::ReactTapNoAim);

          AimReactTapNo = CDataConversion::SetInvalidToDefault(AimReactTapNo, 0 );

          // *******************************************************************
          // Gas Lance
          // *******************************************************************
          sGasLanceData  sDataGasLance;
          for(long k = 0; k < CIntfData::getLength(SeqEAFGasLanceAmount) ; k++)
          {
            CIntfData::getAt(sDataGasLance,SeqEAFGasLanceAmount,k);

            std::string DeviceName  = sDataGasLance.Device;
            long L1DeviceNo         = 0;
            double GasFlow          = 0.; 

            if ( m_pGCE_INJECTION )
            {
              L1DeviceNo         = m_pGCE_INJECTION->getL1DeviceNo(Plant, UnitNo, DeviceName);
            }

            for(long i = 0; i < CIntfData::getLength(sDataGasLance.LanceData) ; i++)
            {
              sGasData sGData;
              CIntfData::getAt(sGData,sDataGasLance.LanceData,i);

              GasFlow = sGData.GasValue;

              if ( L1DeviceNo == 1 )
              {
                FlowRateO2_SideLance_1 = GasFlow * 60. ; // Nm�/min -> Nm�/h
              }
              else if ( L1DeviceNo == 2 )
              {
                FlowRateO2_SideLance_2 = GasFlow * 60. ; // Nm�/min -> Nm�/h
              }
            }
          }

          // *******************************************************************
          // Burner
          // *******************************************************************
          sGasLanceData  sDataBurner;
          for(long k = 0; k < CIntfData::getLength(SeqEAFBurnerAmount) ; k++)
          {
            CIntfData::getAt(sDataBurner,SeqEAFBurnerAmount,k);

            std::string BurnerName    = sDataBurner.Device;
            double GasFlow     = 0.; 
            double O2Flow      = 0.; 

            for(long i = 0; i < CIntfData::getLength(sDataBurner.LanceData) ; i++)
            {
              sGasData sGData;
              CIntfData::getAt(sGData,sDataBurner.LanceData,i);

              if ( std::string(sGData.GasType) == DEF_GCE_BURNER_GASTYPE::BG )
              {
                GasFlow = sGData.GasValue;
              }
              else if ( std::string(sGData.GasType) == DEF_GCE_BURNER_GASTYPE::O2 )
              {
                O2Flow = sGData.GasValue;
              }
            }

            // remember last burner profile, update on change of burner only
            if ( BurnerName == DEF_GCE_BURNER::Burner_1 )
            {
              if(m_pGTE_PP_FLAME_PROFILE->selectbyFlowData(Plant, UnitNo, BurnerName, O2Flow,GasFlow))
              {
                FlowRateO2_SideLance_1 = m_pGTE_PP_FLAME_PROFILE->getFLAMEPROFILENO(1);
              }
              else
              {
                FlowRateO2_SideLance_1 = 0;
              }
            }
            else if ( BurnerName == DEF_GCE_BURNER::Burner_2 )
            {
              if(m_pGTE_PP_FLAME_PROFILE->selectbyFlowData(Plant, UnitNo, BurnerName, O2Flow,GasFlow))
              {
                FlowRateO2_SideLance_2 = m_pGTE_PP_FLAME_PROFILE->getFLAMEPROFILENO(1);
              }
              else
              {
                FlowRateO2_SideLance_2 = 0;
              }
            }
            else if ( BurnerName == DEF_GCE_BURNER::Burner_3 )
            {
              if(m_pGTE_PP_FLAME_PROFILE->selectbyFlowData(Plant, UnitNo, BurnerName, O2Flow,GasFlow))
              {
                FlowRateO2_SideLance_3 = m_pGTE_PP_FLAME_PROFILE->getFLAMEPROFILENO(1);
              }
              else
              {
                FlowRateO2_SideLance_3 = 0;
              }
            }
            else if ( BurnerName == DEF_GCE_BURNER::DoorBurner )
            {
              if(m_pGTE_PP_FLAME_PROFILE->selectbyFlowData(Plant, UnitNo, BurnerName, O2Flow,GasFlow))
              {
                FlowRateO2_DoorLance = m_pGTE_PP_FLAME_PROFILE->getFLAMEPROFILENO(1);
              }
              else
              {
                FlowRateO2_DoorLance = 0;
              }
            }
            else if ( BurnerName == DEF_GCE_BURNER::EBTBurner )
            {
              if(m_pGTE_PP_FLAME_PROFILE->selectbyFlowData(Plant, UnitNo, BurnerName, O2Flow,GasFlow))
              {
                FlowRateO2_EBTLance = m_pGTE_PP_FLAME_PROFILE->getFLAMEPROFILENO(1);
              }
              else
              {
                FlowRateO2_EBTLance = 0;
              }
            }
          }

          // *******************************************************************
          // Material Feeding
          // *******************************************************************
          for(int Counter =0; Counter < CIntfData::getLength(seqRecipeContent); Counter++)
          {
            sBatch sBatch;
            CIntfData::getAt(sBatch,seqRecipeContent,Counter);

            std::string strMatCode = sBatch.MatCode;
            double dFeedSpeed      = sBatch.MatFeedSpeed;

            if ( sBatch.FeedingRateRel2Energy > 0. )
            {
              dFeedSpeed =  sBatch.FeedingRateRel2Energy;
            }

            if( Counter == 0 )
            {
              MatCode_1     = sBatch.MatCode;
              FeedingRate_1 = dFeedSpeed;
              TargetAmount_1 = CDataConversion::RoundToLong(sBatch.Mass);
            }
            else if( Counter == 1 )
            {
              MatCode_2   = sBatch.MatCode;
              FeedingRate_2 = dFeedSpeed;
              TargetAmount_2 = CDataConversion::RoundToLong(sBatch.Mass) ;
            }
            else if( Counter == 2 )
            {
              MatCode_3 = sBatch.MatCode;
              FeedingRate_3 = dFeedSpeed;
              TargetAmount_3 = CDataConversion::RoundToLong(sBatch.Mass) ;
            }
            else if( Counter == 3 )
            {
              MatCode_4   = sBatch.MatCode;
              FeedingRate_4 = dFeedSpeed;
              TargetAmount_4 = CDataConversion::RoundToLong(sBatch.Mass) ;
            }
            else if( Counter == 4 )
            {
              MatCode_5      = sBatch.MatCode;
              FeedingRate_5  = dFeedSpeed;
              TargetAmount_5 =  CDataConversion::RoundToLong(sBatch.Mass);
            }
            else if( Counter == 5 )
            {
              MatCode_6      = sBatch.MatCode;
              FeedingRate_6  = dFeedSpeed;
              TargetAmount_6 = CDataConversion::RoundToLong(sBatch.Mass) ;
            }
            else if( Counter == 6 )
            {
              MatCode_7   = sBatch.MatCode;
              FeedingRate_7 =  dFeedSpeed;
              TargetAmount_7 = CDataConversion::RoundToLong(sBatch.Mass) ;
            }
            else if( Counter == 7 )
            {
              MatCode_8   = sBatch.MatCode;
              FeedingRate_8 =  dFeedSpeed;
              TargetAmount_8 = CDataConversion::RoundToLong(sBatch.Mass) ;
            }
            else if( Counter == 8 )
            {
              MatCode_9   = sBatch.MatCode;
              FeedingRate_9 =  dFeedSpeed;
              TargetAmount_9 = CDataConversion::RoundToLong(sBatch.Mass) ;
            }
          }

          // *******************************************************************
          // Injectors
          // *******************************************************************
          for(long k = 0; k < CIntfData::getLength(SeqEAFInjectLanceAmount) ; k++)
          {
            sInjectLanceData sInj;
            CIntfData::getAt(sInj,SeqEAFInjectLanceAmount,k);

            double MatFlowRateCarbon        = 0.;
            double MatFlowRateSilicon       = 0.;

            if ( DEF_GCE_INJECTION_TYPE::CarbonInjection == std::string(sInj.InjectionType) )
            {
              //right now just one system  !!! depens on configuration
              MatFlowRateCarbon += sInj.Value;
            }
            else if ( DEF_GCE_INJECTION_TYPE::SiliconInjection == std::string(sInj.InjectionType) )
            {
              //right now just one system  !!! depens on configuration
              MatFlowRateSilicon += sInj.Value;
            }

            if ( MatFlowRateCarbon > 0 )
            {
              FlowRateC_SideLance_1 = MatFlowRateCarbon;
              AmountC_SideLance_1   = CDataConversion::RoundToDecimals(MatFlowRateCarbon * RemDurStep,1); // kg/min * min 
            }

            if ( MatFlowRateSilicon > 0 )
            {
              FlowRateC_SideLance_2 = MatFlowRateSilicon;
              AmountC_SideLance_2   = CDataConversion::RoundToDecimals(MatFlowRateSilicon * RemDurStep,1); // kg/min * min 
            }
          }

          // *******************************************************************
          // Bottrom Stirring
          // *******************************************************************

          if(DEF_GAS::Ar == StirrGasType)
          {
            lngStirrGasType = 1;
          }
          else if(DEF_GAS::N2 == StirrGasType)
          {
            lngStirrGasType = 2;
          }
          sEAFProcessPredRes  EAFProcessPredRes;
          for(long i = 0; i < CIntfData::getLength(SeqEAFProcessPredRes) ; i++)
          {
            CIntfData::getAt(EAFProcessPredRes,SeqEAFProcessPredRes,i);

            if ( std::string(EAFProcessPredRes.Phase) == curPhaseName && EAFProcessPredRes.PhaseNo == currentPhaseNo )
            {
              NextPhaseEnergyTotal += EAFProcessPredRes.ElecEgyStep;
            }
          }


          // truncate string data to fit telegram length
          HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
          TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

          StirrGasFlow   = CDataConversion::SetInvalidToDefault(StirrGasFlow,  0.);
          ElecEnergyStep = CDataConversion::RoundToLong(NextPhaseEnergyTotal) - ElecEnergyTotal;
          if ( ElecEnergyStep < 0 )
          {
            ElecEnergyStep = 0;
          }


          std::stringstream tmp_elec;
          tmp_elec << "******* Process data *********" << endl;



          //********    Write telegram data  ***********************************************************************

          pTelcom_Interface->setLong  ( DataKeyL1, Telegram_L2EA41::UnitNo,        UnitNo);
          pTelcom_Interface->setString( DataKeyL1, Telegram_L2EA41::HeatId,        HeatID);
          tmp_elec << "HeatID : "   << HeatID << endl;
          pTelcom_Interface->setString( DataKeyL1, Telegram_L2EA41::TreatId,       TreatID);
          pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2EA41::CreateTime,    Now.asCORBAAny()); 

          pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2EA41::PhaseNo                ,PhaseNo);
          tmp_elec << "PhaseNo : "   << PhaseNo << endl;
          pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2EA41::PhaseType              ,PhaseType);
          tmp_elec << "PhaseType : "   << PhaseType << endl;

          pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2EA41::AimVoltTap             ,AimVoltTap);
          tmp_elec << "AimVoltTap : "   << AimVoltTap << endl;
          pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2EA41::AimCurveNo             ,AimCurveNo);
          tmp_elec << "AimCurveNo : "   << AimCurveNo << endl;
          pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2EA41::AimReactorTap          ,AimReactTapNo);
          tmp_elec << "AimReactTapNo : "   << AimReactTapNo << endl;

          pTelcom_Interface->setDouble  ( DataKeyL1, Telegram_L2EA41::RemDurStep             ,RemDurStep     ); 
          tmp_elec << "RemDurStep : "   << RemDurStep << endl;
          pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2EA41::ElecEnergyStep         ,ElecEnergyStep );
          tmp_elec << "ElecEnergyStep : "   << ElecEnergyStep << endl;
          pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2EA41::ElecEnergyTotal        ,ElecEnergyTotal);
          tmp_elec << "ElecEnergyTotal : "   << ElecEnergyTotal << endl;
          pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2EA41::AmountO2Total          ,AmountO2Total  );
          tmp_elec << "AmountO2Total : "   << AmountO2Total << endl;

          pTelcom_Interface->setDouble  ( DataKeyL1, Telegram_L2EA41::FlowRateO2_EBTLance    ,FlowRateO2_EBTLance );
          tmp_elec << "FlowRateO2_EBTLance : "   << FlowRateO2_EBTLance << endl;
          pTelcom_Interface->setDouble  ( DataKeyL1, Telegram_L2EA41::FlowRateO2_DoorLance   ,FlowRateO2_DoorLance);
          tmp_elec << "FlowRateO2_DoorLance : "   << FlowRateO2_DoorLance << endl;

          pTelcom_Interface->setDouble  ( DataKeyL1, Telegram_L2EA41::FlowRateO2_SideLance_1 ,FlowRateO2_SideLance_1);
          tmp_elec << "FlowRateO2_SideLance_1 : "   << FlowRateO2_SideLance_1 << endl;
          pTelcom_Interface->setDouble  ( DataKeyL1, Telegram_L2EA41::FlowRateO2_SideLance_2 ,FlowRateO2_SideLance_2);
          tmp_elec << "FlowRateO2_SideLance_2 : "   << FlowRateO2_SideLance_2 << endl;
          pTelcom_Interface->setDouble  ( DataKeyL1, Telegram_L2EA41::FlowRateO2_SideLance_3 ,FlowRateO2_SideLance_3);
          tmp_elec << "FlowRateO2_SideLance_3 : "   << FlowRateO2_SideLance_3 << endl;

          pTelcom_Interface->setDouble  ( DataKeyL1, Telegram_L2EA41::FlowRateO2_SideLance_4 ,FlowRateO2_SideLance_4);
          pTelcom_Interface->setDouble  ( DataKeyL1, Telegram_L2EA41::FlowRateO2_SideLance_5 ,FlowRateO2_SideLance_5);


          pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2EA41::RatioCarbDust          ,RatioCarbDust);
          tmp_elec << "RatioCarbDust : "   << RatioCarbDust << endl;

          pTelcom_Interface->setDouble    ( DataKeyL1, Telegram_L2EA41::FlowRateC_EBTLance     ,MatFlowRateEBTDoor_1);
          tmp_elec << "MatFlowRateEBTDoor_1 : "   << MatFlowRateEBTDoor_1 << endl;
          pTelcom_Interface->setDouble    ( DataKeyL1, Telegram_L2EA41::FlowRateC_DoorLance    ,MatFlowRateEBTDoor_2);
          tmp_elec << "MatFlowRateEBTDoor_2 : "   << MatFlowRateEBTDoor_2 << endl;
          pTelcom_Interface->setDouble    ( DataKeyL1, Telegram_L2EA41::AmountC_EBTLance       ,AmountC_EBTLance);
          tmp_elec << "AmountC_EBTLance : "   << AmountC_EBTLance << endl;
          pTelcom_Interface->setDouble    ( DataKeyL1, Telegram_L2EA41::AmountC_DoorLance      ,AmountC_DoorLance);
          tmp_elec << "AmountC_DoorLance : "   << AmountC_DoorLance << endl;

          pTelcom_Interface->setDouble    ( DataKeyL1, Telegram_L2EA41::FlowRateC_SideLance_1  ,FlowRateC_SideLance_1);
          tmp_elec << "FlowRateC_SideLance_1 : "   << FlowRateC_SideLance_1 << endl;
          pTelcom_Interface->setDouble    ( DataKeyL1, Telegram_L2EA41::FlowRateC_SideLance_2  ,FlowRateC_SideLance_2);
          tmp_elec << "FlowRateC_SideLance_2 : "   << FlowRateC_SideLance_2 << endl;
          pTelcom_Interface->setDouble    ( DataKeyL1, Telegram_L2EA41::AmountC_SideLance_1    ,AmountC_SideLance_1);
          tmp_elec << "AmountC_SideLance_1 : "   << AmountC_SideLance_1 << endl;
          pTelcom_Interface->setDouble    ( DataKeyL1, Telegram_L2EA41::AmountC_SideLance_2    ,AmountC_SideLance_2);
          tmp_elec << "AmountC_SideLance_2 : "   << AmountC_SideLance_2 << endl;

          pTelcom_Interface->setString     ( DataKeyL1, Telegram_L2EA41::MatCode_1              ,MatCode_1);
          tmp_elec << "MatCode_1 : "   << MatCode_1 << endl;
          pTelcom_Interface->setDouble     ( DataKeyL1, Telegram_L2EA41::FeedingRate_1          ,FeedingRate_1);
          tmp_elec << "FeedingRate_1 : "   << FeedingRate_1 << endl;
          pTelcom_Interface->setDouble     ( DataKeyL1, Telegram_L2EA41::TargetAmount_1         ,TargetAmount_1);
          tmp_elec << "TargetAmount_1 : "   << TargetAmount_1 << endl;
          pTelcom_Interface->setString     ( DataKeyL1, Telegram_L2EA41::MatCode_2              ,MatCode_2);
          tmp_elec << "MatCode_2 : "   << MatCode_2 << endl;
          pTelcom_Interface->setDouble     ( DataKeyL1, Telegram_L2EA41::FeedingRate_2          ,FeedingRate_2);
          tmp_elec << "FeedingRate_2 : "   << FeedingRate_2 << endl;
          pTelcom_Interface->setDouble     ( DataKeyL1, Telegram_L2EA41::TargetAmount_2         ,TargetAmount_2);
          tmp_elec << "TargetAmount_2 : "   << TargetAmount_2 << endl;
          pTelcom_Interface->setString     ( DataKeyL1, Telegram_L2EA41::MatCode_3              ,MatCode_3);
          tmp_elec << "MatCode_3 : "   << MatCode_3 << endl;
          pTelcom_Interface->setDouble     ( DataKeyL1, Telegram_L2EA41::FeedingRate_3          ,FeedingRate_3);
          tmp_elec << "FeedingRate_3 : "   << FeedingRate_3 << endl;
          pTelcom_Interface->setDouble     ( DataKeyL1, Telegram_L2EA41::TargetAmount_3         ,TargetAmount_3);
          tmp_elec << "TargetAmount_3 : "   << TargetAmount_3 << endl;
          pTelcom_Interface->setString     ( DataKeyL1, Telegram_L2EA41::MatCode_4              ,MatCode_4);
          tmp_elec << "MatCode_4 : "   << MatCode_4 << endl;
          pTelcom_Interface->setDouble     ( DataKeyL1, Telegram_L2EA41::FeedingRate_4          ,FeedingRate_4);
          tmp_elec << "FeedingRate_4 : "   << FeedingRate_4 << endl;
          pTelcom_Interface->setDouble     ( DataKeyL1, Telegram_L2EA41::TargetAmount_4         ,TargetAmount_4);
          tmp_elec << "TargetAmount_4 : "   << TargetAmount_4 << endl;
          pTelcom_Interface->setString     ( DataKeyL1, Telegram_L2EA41::MatCode_5              ,MatCode_5);
          tmp_elec << "MatCode_5 : "   << MatCode_5 << endl;
          pTelcom_Interface->setDouble     ( DataKeyL1, Telegram_L2EA41::FeedingRate_5          ,FeedingRate_5);
          tmp_elec << "FeedingRate_5 : "   << FeedingRate_5 << endl;
          pTelcom_Interface->setDouble     ( DataKeyL1, Telegram_L2EA41::TargetAmount_5         ,TargetAmount_5);
          tmp_elec << "TargetAmount_5 : "   << TargetAmount_5 << endl;
          pTelcom_Interface->setString     ( DataKeyL1, Telegram_L2EA41::MatCode_6              ,MatCode_6);
          tmp_elec << "MatCode_6 : "   << MatCode_6 << endl;
          pTelcom_Interface->setDouble     ( DataKeyL1, Telegram_L2EA41::FeedingRate_6          ,FeedingRate_6);
          tmp_elec << "FeedingRate_6 : "   << FeedingRate_6 << endl;
          pTelcom_Interface->setDouble     ( DataKeyL1, Telegram_L2EA41::TargetAmount_6         ,TargetAmount_6);
          tmp_elec << "TargetAmount_6 : "   << TargetAmount_6 << endl;
          pTelcom_Interface->setString     ( DataKeyL1, Telegram_L2EA41::MatCode_7              ,MatCode_7);
          tmp_elec << "MatCode_7 : "   << MatCode_7 << endl;
          pTelcom_Interface->setDouble     ( DataKeyL1, Telegram_L2EA41::FeedingRate_7          ,FeedingRate_7);
          tmp_elec << "FeedingRate_7 : "   << FeedingRate_7 << endl;
          pTelcom_Interface->setDouble     ( DataKeyL1, Telegram_L2EA41::TargetAmount_7         ,TargetAmount_7);
          tmp_elec << "TargetAmount_7 : "   << TargetAmount_7 << endl;
          pTelcom_Interface->setString     ( DataKeyL1, Telegram_L2EA41::MatCode_8              ,MatCode_8);
          tmp_elec << "MatCode_8 : "   << MatCode_8 << endl;
          pTelcom_Interface->setDouble     ( DataKeyL1, Telegram_L2EA41::FeedingRate_8          ,FeedingRate_8);
          tmp_elec << "FeedingRate_8 : "   << FeedingRate_8 << endl;
          pTelcom_Interface->setDouble     ( DataKeyL1, Telegram_L2EA41::TargetAmount_8         ,TargetAmount_8);
          tmp_elec << "TargetAmount_8 : "   << TargetAmount_8 << endl;
          pTelcom_Interface->setString     ( DataKeyL1, Telegram_L2EA41::MatCode_9              ,MatCode_9);
          tmp_elec << "MatCode_9 : "   << MatCode_9 << endl;
          pTelcom_Interface->setDouble     ( DataKeyL1, Telegram_L2EA41::FeedingRate_9          ,FeedingRate_9);
          tmp_elec << "FeedingRate_9 : "   << FeedingRate_9 << endl;
          pTelcom_Interface->setDouble     ( DataKeyL1, Telegram_L2EA41::TargetAmount_9         ,TargetAmount_9);
          tmp_elec << "TargetAmount_9 : "   << TargetAmount_9 << endl;

          pTelcom_Interface->setLong     ( DataKeyL1, Telegram_L2EA41::BaseWeight             ,BaseWeight);
          pTelcom_Interface->setLong     ( DataKeyL1, Telegram_L2EA41::StirrGasType           ,lngStirrGasType);   
          pTelcom_Interface->setDouble   ( DataKeyL1, Telegram_L2EA41::StirrGasFlowrate       ,StirrGasFlow); 

          pTelcom_Interface->setAny      ( DataKeyL1.c_str(), Telegram_L2EA41::Spare,             CIntfData::ToAny(seqSpare));

          pTelcom_Interface->showContent(DataKeyL1, 4);

          CDH_OUT_Task::getInstance()->setStateDetails(TlgName, tmp_elec.str(),4);

          //********    Dispatch event ****** *****************************************************************
          SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);  

        }// if ( L1PhaseType != CSMC_DBData::unspecLong )

        //********    End processing data  ***********************************************************************
      }// if ( !HeatID.empty() && HeatID != DEF::Inv_String )
      else
      {
        RetValue = false;

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_InvalidTlgData(sMessage,TlgName.c_str(),"HeatID","empty");  
      }
    }// if ( pDM_Interface && m_pTelcom_Interface )
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorPointerHandling(sMessage,Function.c_str()," pDM_Interface or pTelcom_Interface invalid ");
      RetValue=false;
    }

    log( TlgName + ": End", 3);

    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }		
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;
}

bool  CEAF_EventHandler::provideData_L2EA70MatHandling(CEventMessage& Event)
{
  //=================    M A T E R I A L   H A N D L I N G   ===============================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();

  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID);
  long 				PlantNo   = m_pGC_Plant_Container->getPlantNo(PlantID);
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  long 				UnitNo    = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2EA70";
  std::string Function = "CEAF_EventHandler::provideData_L2EA70MatHandling";


  try
  {
    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    if ( pTelcom_Interface )
    {
      //********    preset data  ************************************************************************

      log("****************************************************************************************", 3);
      log( TlgName + ": Start: " + HeatID, 3);
      log("****************************************************************************************", 3);

      CIntfData::preset(seqSpare,0,5);

      //********    Convert and check event data  ***********************************************************

      //********    Convert and check event data  ***********************************************************

      if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
      {
        // truncate string data to fit telegram length
        HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
        TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

        //*******************************************************************************
        // sending reset event !
        // L1 has to reset all recipes that are not yet in use !
        //*******************************************************************************

        //********    Write telegram data  ***********************************************************************
        {
          long SeqLenght = 10;
          DEF::seqString  SeqMatCode;
          DEF::seqLong    SeqMatWeight;
          DEF::seqLong    SeqMatSequence;
          DEF::seqLong    SeqFeedSpeed;
          

          // preset sequences with empty values
          CIntfData::preset(SeqMatCode    ,"",SeqLenght);
          CIntfData::preset(SeqMatWeight  ,0,SeqLenght);
          CIntfData::preset(SeqMatSequence,0,SeqLenght);
          CIntfData::preset(SeqFeedSpeed  ,0,SeqLenght);

          DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName+"reset");

          //set the data to telcom interface
          pTelcom_Interface->setLong   ( DataKeyL1,Telegram_L2EA70::UnitNo,      UnitNo);
          pTelcom_Interface->setString ( DataKeyL1,Telegram_L2EA70::HeatId,      HeatID);
          pTelcom_Interface->setString ( DataKeyL1,Telegram_L2EA70::TreatId,     TreatID);
          pTelcom_Interface->setAny    ( DataKeyL1,Telegram_L2EA70::CreateTime,  Now.asCORBAAny());    

          pTelcom_Interface->setLong   ( DataKeyL1,Telegram_L2EA70::Source,    0);
          pTelcom_Interface->setLong   ( DataKeyL1,Telegram_L2EA70::RecipeNo,  0);

          pTelcom_Interface->setAny    ( DataKeyL1, Telegram_L2EA70::MatCode     ,CIntfData::ToAny(SeqMatCode));
          pTelcom_Interface->setAny    ( DataKeyL1, Telegram_L2EA70::MatWeight   ,CIntfData::ToAny(SeqMatWeight));
          pTelcom_Interface->setAny    ( DataKeyL1, Telegram_L2EA70::MatSequence ,CIntfData::ToAny(SeqMatSequence));

          pTelcom_Interface->setAny    ( DataKeyL1, Telegram_L2EA70::FeedRate    ,CIntfData::ToAny(SeqFeedSpeed));

          pTelcom_Interface->setAny    ( DataKeyL1, Telegram_L2EA70::Spare       ,CIntfData::ToAny(seqSpare));

          pTelcom_Interface->showContent(DataKeyL1, 4);

          //CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          //sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          //pEventLog->EL_RejectingRecipe(sMessage,"",CustHeatID.c_str(),CustTreatID.c_str(),Plant );

          //********    Dispatch event ***********************************************************************
          //            multiple telegrams send if model results contains more materials than defined in telegram sequence! 
          SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);

        }

        // request by L1 one, send only reset telegram at evEAFHeatDeparture but not model set points
        if ( Event.getMessage() == EAF_EvMsg::evEAFModelResultRecipeSetpoints )
        {
          DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

          if ( pDM_Interface )
          {
            DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

            //********    Read event related data  ************************************************************************
            seqRecipeList RecipeList = CIntfData::ToCORBAType(pDM_Interface->getRecipeList(ProductID.c_str(),DATA::EAFMatRecipe));

            //********    Log event data ***********************************************************************

            //********    Write telegram data  ***********************************************************************
            // loop entire list and create one L1 Telegram per entry
            for (long ii=0; ii < CIntfData::getLength(RecipeList); ii++)    
            {
              // get current Recipe from RecipeList
              sRecipe Recipe;
              CIntfData::getAt(Recipe,RecipeList,ii);

              long l1RecipeNo = 0;
              long l1BatchNo  = 0;
              long l1Source   = 0;

              //Get the recipe name from the table by recipe number and recipe name
              l1RecipeNo = m_pGC_Recipe_L1Container->getL1RecipeNoByL2Name ( Recipe.RecipeNo,std::string(Recipe.RecipeName));

              if ( l1RecipeNo != 0 )
              {
                // get source from the table by string from L2
                l1Source = m_pGC_SourceContainer->getSourceL1InfoNoByName( std::string(Recipe.RecipeSource) );

                // no of materials per telegram is limited
                long SeqLenght = 10;

                //get the content of current recipe
                seqBatchPrio SeqBatchPrio = Recipe.RecipeContent;

                DEF::seqString  SeqMatCode;
                DEF::seqLong    SeqMatWeight;
                DEF::seqLong    SeqMatSequence;
                DEF::seqLong    SeqFeedSpeed;


                // preset sequences with empty values
                CIntfData::preset(SeqMatCode    ,"",SeqLenght);
                CIntfData::preset(SeqMatWeight  ,0,SeqLenght);
                CIntfData::preset(SeqMatSequence,0,SeqLenght);
                CIntfData::preset(SeqFeedSpeed  ,0,SeqLenght);

                long ActSeqLenght = SeqLenght;

                long MatCounter = 0;
                long TelCounter = 1;

                if ( CIntfData::getLength(SeqBatchPrio) != 0 )
                {
                  // max no of Materials limited by SeqLenght
                  // send more than one telegram per Recipe if required
                  for (long jj=0; jj < CIntfData::getLength(SeqBatchPrio) ; jj++)    
                  {
                    // read batch data from Recipe
                    sBatchPrio BatchPrio;
                    CIntfData::getAt(BatchPrio,SeqBatchPrio,jj);

                    long ChargPrio        = BatchPrio.ChargPrio;
                    std::string MatCode   = BatchPrio.BatchData.MatCode;
                    double Mass           = BatchPrio.BatchData.Mass;
                    double MatFeedSpeed   = BatchPrio.BatchData.MatFeedSpeed;

                    MatCode   = CDataConversion::CheckLengthAndTruncate(MatCode,10);

                    CIntfData::setAt(SeqMatCode     ,MatCode.c_str(),MatCounter);
                    CIntfData::setAt(SeqMatWeight   ,CDataConversion::RoundToLong(Mass),MatCounter);
                    CIntfData::setAt(SeqMatSequence ,ChargPrio      ,MatCounter);

                    // check if no of materials (CIntfData::getLength(SeqBatchPrio)) fits to
                    // length of telegram sequence (SeqLenght)
                    if ( CIntfData::getLength(SeqBatchPrio) >= TelCounter * SeqLenght - 1 || 
                      CIntfData::getLength(SeqBatchPrio) == jj + 1                     )
                    {
                      DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

                      //set the data to telcom interface
                      pTelcom_Interface->setLong   ( DataKeyL1,Telegram_L2EA70::UnitNo,      UnitNo);
                      pTelcom_Interface->setString ( DataKeyL1,Telegram_L2EA70::HeatId,      HeatID);
                      pTelcom_Interface->setString ( DataKeyL1,Telegram_L2EA70::TreatId,     TreatID);
                      pTelcom_Interface->setAny    ( DataKeyL1,Telegram_L2EA70::CreateTime,  Now.asCORBAAny());   

                      pTelcom_Interface->setLong   ( DataKeyL1,Telegram_L2EA70::Source,    l1Source);
                      pTelcom_Interface->setLong   ( DataKeyL1,Telegram_L2EA70::RecipeNo,  l1RecipeNo);                    

                      pTelcom_Interface->setAny    ( DataKeyL1, Telegram_L2EA70::MatCode     ,CIntfData::ToAny(SeqMatCode));
                      pTelcom_Interface->setAny    ( DataKeyL1, Telegram_L2EA70::MatWeight   ,CIntfData::ToAny(SeqMatWeight));
                      pTelcom_Interface->setAny    ( DataKeyL1, Telegram_L2EA70::MatSequence ,CIntfData::ToAny(SeqMatSequence));

                      pTelcom_Interface->setAny    ( DataKeyL1, Telegram_L2EA70::FeedRate    ,CIntfData::ToAny(SeqFeedSpeed));

                      pTelcom_Interface->setAny    ( DataKeyL1, Telegram_L2EA70::Spare       ,CIntfData::ToAny(seqSpare));

                      pTelcom_Interface->showContent(DataKeyL1, 4);

                      //********    Dispatch event ***********************************************************************
                      //            multiple telegrams send if model results contains more materials than defined in telegram sequence! 
                      SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);

                      CIntfData::preset(SeqMatCode    ,"",SeqLenght);
                      CIntfData::preset(SeqMatWeight  ,0,SeqLenght);
                      CIntfData::preset(SeqMatSequence,0,SeqLenght);

                      RetValue = true;

                      TelCounter++;
                      MatCounter = 0;
                    }

                    MatCounter++;

                  } // for (long jj=0; jj < CIntfData::getLength(SeqBatchPrio) ; jj++)    
                } // if ( CIntfData::getLength(SeqBatchPrio) != 0 )
                else
                {
                  //// send an empty telegram for this recipe to reset L1 Batches!
                  //// readrding only recipes that ar not yet in use (not yet enabled)
                  //if ( !m_pPD_RECIPE->isRecipeIniUse(HeatID,TreatID,Plant,std::string(Recipe.RecipeName),Recipe.RecipeNo,std::string(Recipe.RecipeSource) ) )
                  //{
                  //  DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

                  //  //set the data to telcom interface
                  //  pTelcom_Interface->setLong   (DataKeyL1,Telegram_L2EA70::UnitNo,      UnitNo);
                  //  pTelcom_Interface->setString (DataKeyL1,Telegram_L2EA70::HeatId,      HeatID);
                  //  pTelcom_Interface->setString (DataKeyL1,Telegram_L2EA70::TreatId,     TreatID);
                  //  pTelcom_Interface->setAny    (DataKeyL1,Telegram_L2EA70::CreateTime,  Now.asCORBAAny());   

                  //  pTelcom_Interface->setLong   (DataKeyL1,Telegram_L2EA70::RecipeNo,  l1RecipeNo);
                  //  pTelcom_Interface->setLong   (DataKeyL1,Telegram_L2EA70::BatchNo,   l1BatchNo);
                  //  pTelcom_Interface->setLong   (DataKeyL1,Telegram_L2EA70::Source,    l1Source);

                  //  pTelcom_Interface->setAny    (DataKeyL1, Telegram_L2EA70::Spare,CIntfData::ToAny(seqSpare));

                  //  pTelcom_Interface->setAny    (DataKeyL1, Telegram_L2EA70::MatCode     ,CIntfData::ToAny(SeqMatCode));
                  //  pTelcom_Interface->setAny    (DataKeyL1, Telegram_L2EA70::MatWeight   ,CIntfData::ToAny(SeqMatWeight));
                  //  pTelcom_Interface->setAny    (DataKeyL1, Telegram_L2EA70::MatSequence ,CIntfData::ToAny(SeqMatSequence));

                  //  pTelcom_Interface->showContent(DataKeyL1, 4);

                  //  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                  //  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                  //  pEventLog->EL_RejectingRecipe(sMessage,Recipe.RecipeName,CustHeatID.c_str(),CustTreatID.c_str(),Plant );

                  //  //********    Dispatch event ***********************************************************************
                  //  //            multiple telegrams send if model results contains more materials than defined in telegram sequence! 

                  //  CEventMessage MstToL1Sender;
                  //  MstToL1Sender.setMessage(std::string("TELEGRAM_") + TlgName);
                  //  MstToL1Sender.setPlantID(L1PlantID);
                  //  MstToL1Sender.setDataKey(DataKeyL1);
                  //  MstToL1Sender.setOrderID(OrderID);
                  //  dispatchEvent(m_SenderName,"",MstToL1Sender);
                  //}
                } // // if ( CIntfData::getLength(SeqBatchPrio) == 0 )
              }  // if ( l1RecipeNo != 0 )
            }  // for (long ii=0; ii < CIntfData::getLength(RecipeList); ii++)    
          }
          else
          {
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorPointerHandling(sMessage,Function.c_str()," pDM_Interface or pTelcom_Interface invalid ");
            RetValue=false;
          }      
        }
      } // if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )

      //********    End processing data  ***********************************************************************

      log( TlgName + ": End", 3);
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorPointerHandling(sMessage,Function.c_str()," pDM_Interface or pTelcom_Interface invalid ");
      RetValue=false;
    }
    
    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;

}


bool  CEAF_EventHandler::provideData_L2EA71MatAvailRequest(CEventMessage& Event)
{
  //=================    M A T E R I A L   A V A I L A B I L I T Y   R E Q U E S T   ===============================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();

  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID);
  long 				PlantNo   = m_pGC_Plant_Container->getPlantNo(PlantID);
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  long 				UnitNo    = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2EA71";
  std::string Function = "CEAF_EventHandler::provideData_L2EA71MatAvailRequest";

  try
  {
    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    if ( pDM_Interface && pTelcom_Interface )
    {
      //********    preset data  ************************************************************************

      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);

      DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

      CIntfData::preset(seqSpare,0,5);

      //********    Read event related data  ************************************************************************

      //********    Log event data ***********************************************************************

      //********    Convert and check event data  ***********************************************************

      //if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
      //{
      // truncate string data to fit telegram length
      //  HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
      //  TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

      //********    Write telegram data  ***********************************************************************
      pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2EA71::UnitNo,        UnitNo);
      pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA71::CreateTime,    Now.asCORBAAny());   

      pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA71::Spare,         CIntfData::ToAny(seqSpare));

      //********    Dispatch event ***********************************************************************
      SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);

      //********    End processing data  ***********************************************************************
      //}// if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatId, CustTreatId) )
      //else
      //{
      //  RetValue = false;
      //}

      log( TlgName + ": End", 3);

    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorPointerHandling(sMessage,Function.c_str()," pDM_Interface or pTelcom_Interface invalid ");
      RetValue=false;
    }
    
    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;
}




bool  CEAF_EventHandler::provideData_L2EA72StatusRequest(CEventMessage& Event)
{
  //=================    S T A T U S   R E Q U E S T   ===============================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();

  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID);
  long 				PlantNo   = m_pGC_Plant_Container->getPlantNo(PlantID);
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  long 				UnitNo    = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2EA72";
  std::string Function = "CEAF_EventHandler::provideData_L2EA72StatusRequest";


  try
  {
    //next not needed, brings only trouble when message should be sent ufter startup of DH_OUT
    //DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    //if ( pDM_Interface && pTelcom_Interface )
    if ( pTelcom_Interface )
    {
      //********    preset data  ************************************************************************

      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);


      DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

      CIntfData::preset(seqSpare,0,5);

      //********    Read event related data  ************************************************************************

      //********    Log event data ***********************************************************************

      //********    Convert and check event data  ***********************************************************

      //********    Write telegram data  ***********************************************************************
      pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2EA72::UnitNo,        UnitNo);
      pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA72::CreateTime,    Now.asCORBAAny());   
      pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2EA72::Spare,         CIntfData::ToAny(seqSpare));

      //********    Dispatch event ***********************************************************************
      SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);

      //********    End processing data  ***********************************************************************

      log( TlgName + ": End", 3);

    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorPointerHandling(sMessage,Function.c_str()," pDM_Interface or pTelcom_Interface invalid ");
      RetValue=false;
    }

    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;

}


bool  CEAF_EventHandler::provideData_L2SY92ScrapLoadInstruction(CEventMessage& Event)
{
  //=================   S C R A P    L O A D   I N S T R U C T I O N    ===============================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();

  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID);
  long 				PlantNo   = m_pGC_Plant_Container->getPlantNo(PlantID);
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  long 				UnitNo    = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2SY92";
  std::string Function = "CEAF_EventHandler::provideData_L2SY92ScrapLoadInstruction";

  log("****************************************************************************************", 3);
  log( TlgName + ": Start", 3);
  log("****************************************************************************************", 3);

  try
  {
    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    if ( pDM_Interface && pTelcom_Interface )
    {
      //********    preset data  ************************************************************************

      DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

      CIntfData::preset(seqSpare,0,5);

      //********    Read event related data  ************************************************************************

      std::string sContainerType = CIntfData::ToStdString(pDM_Interface->getString(ProductID.c_str(),DATA::ContainerType));
      //std::string ProdOrderId    = CIntfData::ToStdString(pDM_Interface->getString(ProductID.c_str(),DATA::OrderID));

      //********    Log event data ***********************************************************************

      //********    Convert and check event data  ***********************************************************

      OrderID         = CDataConversion::SetInvalidToDefault(OrderID,        "");
      sContainerType  = CDataConversion::SetInvalidToDefault(sContainerType, "");
      //sContainerType = DEF_GC_SCRAP_CONTAINER_TYPE::Basket only used

      CustHeatID              = "";
      CustTreatID             = "";

      long ContainerSeqNo       = 0;
      long TotalNoOfContainers  = 0;
      long ContainerType        = 0;

      DEF::seqString MatCodeSeq;
      DEF::seqLong   MatWeightSeq;
      DEF::seqLong   MatLoadSeq;

      CIntfData::preset(MatCodeSeq,   "",10);
      CIntfData::preset(MatWeightSeq, 0,10);
      CIntfData::preset(MatLoadSeq,   0,10);

      bool ContainerFound = false;

      log ("Event.OrderID = " + OrderID, 1);

      // find next planned order if ProdOrderId is unknown
      // select all valid "planned" data in chronological ordered by treatstart_plan
      if ( m_pPD_SCRAP_CONTAINER_ORDER && m_pPD_SCRAP_CONTAINER_ORDER->selectByContainerState(Plant, OrderID, DEF_GC_SCRAP_CONT_ORDER_STATUS::Planned) )
      {
        if ( sContainerType.empty() )
        {
          sContainerType = m_pPD_SCRAP_CONTAINER_ORDER->getCONTAINERTYPE(1);
        }
        if ( OrderID.empty() )
        {
          OrderID        = m_pPD_SCRAP_CONTAINER_ORDER->getPRODORDERID(1);
        }// if ( ProdOrderId.empty() )
      }// if ( m_pPD_SCRAP_CONTAINER_ORDER && m_pPD_SCRAP_CONTAINER_ORDER->selectByContainerState(Plant, OrderID, DEF_GC_SCRAP_CONT_ORDER_STATUS::Planned) )
      else
      {
        log("READING DATA FROM PD_SCRAP_CONTAINER_ORDER FAILED/NOT PLANNED", 1);     
      }

      if ( !OrderID.empty() )
      {
        if ( m_pPP_HEAT && m_pPP_HEAT->selectOrder(OrderID) )
        {
          // get respective prodorderid from planning data
          if ( m_pPP_HEAT_PLANT && m_pPP_HEAT_PLANT->selectByHeatData(m_pPP_HEAT->getHEATID(1), CSMC_DBData::unspecString, Plant, false) )
          {
            CustHeatID              = m_pPP_HEAT_PLANT->getHEATID_CUST_PLAN(1);
            CustTreatID             = m_pPP_HEAT_PLANT->getTREATID_CUST_PLAN(1);

            // check respective state and stop iteration.
            if ( OrderID != CSMC_DBData::unspecString   && 
              m_pPD_SCRAP_CONTAINER_ORDER->selectByContainerTypeAndState(Plant, OrderID, sContainerType, DEF_GC_SCRAP_CONT_ORDER_STATUS::Planned) )
            {
              ContainerType        =  1; // preset with 1 = Basket
              ContainerFound = true;

              // get the first dataset
              ContainerSeqNo = m_pPD_SCRAP_CONTAINER_ORDER->getCONTAINERINSEQ(1);

              long CONTAINERNO = m_pPD_SCRAP_CONTAINER_ORDER->getCONTAINERNO(1);

              // detect the total no of containers by counting all datasets for the prodorderid
              if ( m_pPD_SCRAP_CONTAINER_ORDER->selectByContainerTypeAndState(Plant, OrderID, CSMC_DBData::unspecString, CSMC_DBData::unspecLong) )
              {
                TotalNoOfContainers = m_pPD_SCRAP_CONTAINER_ORDER->getLastRow();
              }

              // select material data from  entry table for all recipes
              if ( m_pPD_SCRAP_CONTAINER_ORDER_ENTRY && 
                m_pPD_SCRAP_CONTAINER_ORDER_ENTRY->selectByMatChargeSeq(Plant, OrderID, ContainerSeqNo, CSMC_DBData::unspecString, CSMC_DBData::unspecString) )
              {
                for ( long i = 1 ; i <= m_pPD_SCRAP_CONTAINER_ORDER_ENTRY->getLastRow(); ++i )
                {
                  if ( i > 10 ) // max no of materials is limited to 10 by telegram
                  {
                    break;
                  }

                  CIntfData::setAt( MatCodeSeq,    m_pPD_SCRAP_CONTAINER_ORDER_ENTRY->getMAT_CODE(i).c_str()                          , i-1 );
                  CIntfData::setAt( MatWeightSeq,  CDataConversion::RoundToLong(m_pPD_SCRAP_CONTAINER_ORDER_ENTRY->getMATWEIGHT(i))   , i-1 );
                  CIntfData::setAt( MatLoadSeq,    m_pPD_SCRAP_CONTAINER_ORDER_ENTRY->getMATCHARGESEQ(i)                              , i-1 );
                }
              } 
            }// m_pPD_SCRAP_CONTAINER_ORDER->selectByContainerTypeAndState(Plant, ProdOrderId, DEF_GC_SCRAP_CONTAINER_TYPE::Basket, DEF_GC_SCRAP_CONT_ORDER_STATUS::Planned) )
            else
            {
              if ( OrderID == CSMC_DBData::unspecString )
              {
                CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                pEventLog->EL_DBReadError(sMessage,"PRODORDERID","PP_HEAT","" );
              }
              else
              {
                log("READING DATA FROM PD_SCRAP_CONTAINER_ORDER FAILED/NOT PLANNED- ProdOrderId = " + OrderID, 1);
              }
            }
          } // if ( m_pPP_HEAT_PLANT && m_pPP_HEAT_PLANT->selectByData(m_pPP_HEAT->getHEATID(1), CSMC_DBData::unspecString, Plant, false) )
          else
          {
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_DBReadError(sMessage,"PLANT,PLANTNO...,","PP_HEAT_PLANT","" );
          }
        } // if ( m_pPP_HEAT && m_pPP_HEAT->selectOrder(ProdOrderId) )
        else
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_DBReadError(sMessage,"HEATID","PP_HEAT",OrderID.c_str() );
        }


        // truncate string data to fit telegram length
        OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

        // truncate string data to fit telegram length
        HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
        TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

        //********    Write telegram data  ***********************************************************************
        pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2SY92::UnitNo,               UnitNo);
        pTelcom_Interface->setString  ( DataKeyL1, Telegram_L2SY92::HeatId,               HeatID);
        pTelcom_Interface->setString  ( DataKeyL1, Telegram_L2SY92::TreatId,              TreatID);
        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2SY92::CreateTime,           Now.asCORBAAny());   

        pTelcom_Interface->setString  ( DataKeyL1, Telegram_L2SY92::ProdOrderId,          OrderID);

        pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2SY92::ContainerSeqNo,       ContainerSeqNo);
        pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2SY92::TotalNoOfContainers,  TotalNoOfContainers);
        pTelcom_Interface->setLong    ( DataKeyL1, Telegram_L2SY92::ContainerType,        ContainerType);

        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2SY92::MatCode,              CIntfData::ToAny(MatCodeSeq) );
        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2SY92::MatWeight,            CIntfData::ToAny(MatWeightSeq) );
        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2SY92::MatLoadSeq,           CIntfData::ToAny(MatLoadSeq) );

        pTelcom_Interface->setAny     ( DataKeyL1, Telegram_L2SY92::Spare,                CIntfData::ToAny(seqSpare));

        //********    Dispatch event ***********************************************************************
        SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);

        if ( ContainerType == 1 )
        {
          sContainerType = DEF_GC_SCRAP_CONTAINER_TYPE::Basket;
        }
        else if ( ContainerType == 2 )
        {
          sContainerType = DEF_GC_SCRAP_CONTAINER_TYPE::Chute;
        }
        else
        {
          sContainerType = "";
        }

        CSMC_EventLogEAF *pEventLog = CSMC_EventLogEAFController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);

        if ( ContainerFound )
        {
          pEventLog->EL_HandleScrapOrder(sMessage, OrderID.c_str(), (int)ContainerSeqNo, sContainerType.c_str());
        }
        else
        {
          pEventLog->EL_ScrapContainerAssignmentError(sMessage, -1, -1);
          RetValue=false;
        }
      }// if ( !OrderID.empty() )
      else
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DBReadWarning(sMessage,"ODERID","PD_SCRAP_CONTAINER_ORDER", "READING FROM ORDER FAILED/IS ALREADY ORDERED" );
      }

      //********    End processing data  ***********************************************************************
    }// if ( pDM_Interface && pTelcom_Interface )
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorPointerHandling(sMessage,Function.c_str()," pDM_Interface or pTelcom_Interface invalid ");
      RetValue=false;
    }

    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  log( TlgName + ": End", 3);

  return RetValue;

}

bool CEAF_EventHandler::provideData_L2EA40_PROC_PATT(CEventMessage& Event)
{
  //=================    P R O C E S S   P A T T E R N   ===============================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();

  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID);
  long 				PlantNo   = m_pGC_Plant_Container->getPlantNo(PlantID);
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2EA40_PROC_PATT";
  std::string Function = "CEAF_EventHandler::provideData_L2EA40_PROC_PATT";

  try
  {
    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    if ( pDM_Interface && pTelcom_Interface )
    {
      //********    preset data  ************************************************************************

      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);

      //********    Read event related data  ************************************************************************

      seqEAFInjectLance     SeqEAFInjectLanceRes  = CIntfData::ToCORBAType(pDM_Interface->getEAFInjectLance    ( ProductID.c_str(), DATA::EAFInjectLance));
      seqEAFProcessPredRes  SeqEAFProcessPredRes  = CIntfData::ToCORBAType(pDM_Interface->getEAFProcessPredRes ( ProductID.c_str(), DATA::EAFProcessPredRes));
      seqEAFGasLancePredRes SeqEAFGasLancePredRes = CIntfData::ToCORBAType(pDM_Interface->getEAFGasLancePredRes( ProductID.c_str(), DATA::EAFGasLancePredRes));
      seqEAFMatFeedPredRes  SeqEAFMatFeedPredRes  = CIntfData::ToCORBAType(pDM_Interface->getEAFMatFeedPredRes ( ProductID.c_str(), DATA::EAFMatFeedPredRes));
      seqEAFGasLancePredRes SeqBottomStirrPredRes = CIntfData::ToCORBAType(pDM_Interface->getEAFGasLancePredRes( ProductID.c_str(), DATA::EAFBottomStirrPredRes));
      seqEAFBurnerPredRes   SeqEAFBurnerPredRes   = CIntfData::ToCORBAType(pDM_Interface->getEAFBurnerPredRes  ( ProductID.c_str(), DATA::EAFBurnerPredRes));
            
      sEAFProcessPredRes  EAFProcessPredRes;
      sEAFGasLancePredRes EAFGasLancePredRes;
      sEAFMatFeedPredRes  EAFMatFeedPredRes;
      sEAFInjectLance     EAFInjectLanceRes;
      sEAFGasLancePredRes EAFStirrPredRes;
      sEAFBurnerPredRes   EAFBurnerPredRes;

      //********    Log event data ***********************************************************************
			log(CIntfData::getContent(CIntfData::ToAny(SeqEAFInjectLanceRes)),4);
      //********    Convert and check event data  ***********************************************************

      if ( !HeatID.empty() && HeatID != DEF::Inv_String )
      {
        // truncate string data to fit telegram length
        HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
        TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

        DEF::seqLong    SeqPhaseNo;               
        DEF::seqLong    SeqPhaseType;             
        DEF::seqLong    SeqAimVoltTap;            
        DEF::seqLong    SeqAimCurveNo;            
        DEF::seqLong    SeqAimReactorTap;            
        DEF::seqDouble  SeqRemDurStep;            
        DEF::seqLong    SeqElecEnergyStep;        
        DEF::seqLong    SeqElecEnergyTotal;
        DEF::seqLong    SeqAmountO2Total;

        DEF::seqDouble  SeqFlowRateO2EBTLance;
        DEF::seqDouble  SeqFlowRateO2DoorLance; 
        DEF::seqDouble  SeqFlameProfile_O2SideLance_1;
        DEF::seqDouble  SeqFlameProfile_O2SideLance_2;
        DEF::seqDouble  SeqFlameProfile_O2SideLance_3;
        DEF::seqDouble  SeqFlameProfile_O2SideLance_4;
        DEF::seqDouble  SeqFlameProfile_O2SideLance_5;
        DEF::seqDouble  SeqFlowRateO2SideLance_4;
        DEF::seqDouble  SeqFlowRateO2SideLance_5;

        DEF::seqLong    SeqRatioCarbDust;
        DEF::seqDouble  SeqFlowRateC_EBTLance;   
        DEF::seqDouble  SeqFlowRateC_DoorLance;  
        DEF::seqDouble  SeqAmountC_EBTLance;
        DEF::seqDouble  SeqAmountC_DoorLance;
        DEF::seqDouble  SeqFlowRateC_SideLance_1;
        DEF::seqDouble  SeqFlowRateC_SideLance_2;
        DEF::seqDouble  SeqAmountC_SideLance_1;
        DEF::seqDouble  SeqAmountC_SideLance_2;
        
        DEF::seqDouble  SeqFeedingRate_1;          
        DEF::seqDouble  SeqFeedingRate_2;          
        DEF::seqDouble  SeqFeedingRate_3;          
        DEF::seqDouble  SeqFeedingRate_4;
        DEF::seqDouble  SeqFeedingRate_5; 
        DEF::seqDouble  SeqFeedingRate_6; 
        DEF::seqDouble  SeqFeedingRate_7;
        DEF::seqDouble  SeqFeedingRate_8;
        DEF::seqDouble  SeqFeedingRate_9;
        
        DEF::seqDouble  SeqTargetAmount_1;
        DEF::seqDouble  SeqTargetAmount_2;
        DEF::seqDouble  SeqTargetAmount_3;
        DEF::seqDouble  SeqTargetAmount_4;
        DEF::seqDouble  SeqTargetAmount_5;
        DEF::seqDouble  SeqTargetAmount_6;
        DEF::seqDouble  SeqTargetAmount_7;
        DEF::seqDouble  SeqTargetAmount_8;
        DEF::seqDouble  SeqTargetAmount_9;
        
        std::string     MatCode_1;                
        std::string     MatCode_2;                
        std::string     MatCode_3;               
        std::string     MatCode_4;
        std::string     MatCode_5; 
        std::string     MatCode_6; 
        std::string     MatCode_7;
        std::string     MatCode_8;
        std::string     MatCode_9;
        DEF::seqDouble  SeqBaseWeight;
        DEF::seqLong    SeqStirrGasType;
        DEF::seqDouble  SeqStirrGasFlow;
        long            Spare_1       = 0;
        long            Spare_2       = 0;
        long            Spare_3       = 0;
        long            Spare_4       = 0;
        long            Spare_5       = 0;

        long SeqLenght = 25;

        CIntfData::preset(SeqPhaseNo               ,0 ,SeqLenght); 
        CIntfData::preset(SeqPhaseType             ,0 ,SeqLenght); 
        CIntfData::preset(SeqAimVoltTap            ,0 ,SeqLenght); 
        CIntfData::preset(SeqAimCurveNo            ,0 ,SeqLenght); 
        CIntfData::preset(SeqAimReactorTap         ,0 ,SeqLenght); 
        CIntfData::preset(SeqRemDurStep            ,0.,SeqLenght); 
        CIntfData::preset(SeqElecEnergyStep        ,0 ,SeqLenght); 
        CIntfData::preset(SeqElecEnergyTotal       ,0 ,SeqLenght);
        CIntfData::preset(SeqAmountO2Total         ,0 ,SeqLenght);

        CIntfData::preset(SeqFlowRateO2EBTLance         ,0.,SeqLenght); // not used
        CIntfData::preset(SeqFlowRateO2DoorLance        ,0.,SeqLenght); // not used
        CIntfData::preset(SeqAmountC_EBTLance           ,0.,SeqLenght); // not used
        CIntfData::preset(SeqAmountC_DoorLance          ,0.,SeqLenght); // not used
        CIntfData::preset(SeqFlameProfile_O2SideLance_1 ,0.,SeqLenght); // used for O2 injection Lance 1
        CIntfData::preset(SeqFlameProfile_O2SideLance_2 ,0.,SeqLenght); // used for O2 injection Lance 2
        CIntfData::preset(SeqFlameProfile_O2SideLance_3 ,0.,SeqLenght); // not used
        CIntfData::preset(SeqFlameProfile_O2SideLance_4 ,0.,SeqLenght); // not used
        CIntfData::preset(SeqFlameProfile_O2SideLance_5 ,0.,SeqLenght); // not used
        CIntfData::preset(SeqFlowRateO2SideLance_4      ,0.,SeqLenght); // not used
        CIntfData::preset(SeqFlowRateO2SideLance_5      ,0.,SeqLenght); // not used

        CIntfData::preset(SeqRatioCarbDust         ,0 ,SeqLenght);  // not used
        CIntfData::preset(SeqFlowRateC_EBTLance    ,0.,SeqLenght);  // not used
        CIntfData::preset(SeqFlowRateC_DoorLance   ,0.,SeqLenght);  // not used
        CIntfData::preset(SeqFlowRateC_SideLance_1 ,0.,SeqLenght);  // used for Corbon injection
        CIntfData::preset(SeqFlowRateC_SideLance_2 ,0.,SeqLenght);  // used for Silicon injection
        CIntfData::preset(SeqAmountC_SideLance_1   ,0.,SeqLenght);  // used for Corbon injection
        CIntfData::preset(SeqAmountC_SideLance_2   ,0.,SeqLenght);  // used for Silicon injection

        CIntfData::preset(SeqFeedingRate_1         ,0.,SeqLenght); // not used
        CIntfData::preset(SeqFeedingRate_2         ,0.,SeqLenght); // not used
        CIntfData::preset(SeqFeedingRate_3         ,0.,SeqLenght); // not used
        CIntfData::preset(SeqFeedingRate_4         ,0.,SeqLenght); // not used
        CIntfData::preset(SeqFeedingRate_5         ,0.,SeqLenght); // not used
        CIntfData::preset(SeqFeedingRate_6         ,0.,SeqLenght); // not used
        CIntfData::preset(SeqFeedingRate_7         ,0.,SeqLenght); // not used
        CIntfData::preset(SeqFeedingRate_8         ,0.,SeqLenght); // not used
        CIntfData::preset(SeqFeedingRate_9         ,0.,SeqLenght); // not used

        CIntfData::preset(SeqTargetAmount_1        ,0.,SeqLenght); // not used
        CIntfData::preset(SeqTargetAmount_2        ,0.,SeqLenght); // not used
        CIntfData::preset(SeqTargetAmount_3        ,0.,SeqLenght); // not used 
        CIntfData::preset(SeqTargetAmount_4        ,0.,SeqLenght); // not used
        CIntfData::preset(SeqTargetAmount_5        ,0.,SeqLenght); // not used
        CIntfData::preset(SeqTargetAmount_6        ,0.,SeqLenght); // not used
        CIntfData::preset(SeqTargetAmount_7        ,0.,SeqLenght); // not used
        CIntfData::preset(SeqTargetAmount_8        ,0.,SeqLenght); // not used
        CIntfData::preset(SeqTargetAmount_9        ,0.,SeqLenght); // not used

        CIntfData::preset(SeqBaseWeight            ,0.,SeqLenght); // not used
        CIntfData::preset(SeqStirrGasType          ,0 ,SeqLenght); // not used
        CIntfData::preset(SeqStirrGasFlow          ,0.,SeqLenght); // not used

        double PrevElecEgy = 0;

        //iteration over all steps
        for(long i = 0; i < CIntfData::getLength(SeqEAFProcessPredRes) ; i++)
        {
          // only SeqLenght entries per field
          if ( i >= SeqLenght  )
          {
            //continue;
            break;
          }

          CIntfData::getAt(EAFProcessPredRes,SeqEAFProcessPredRes,i);

          std::string Phase       = EAFProcessPredRes.Phase;
          long        PhaseNo     = EAFProcessPredRes.PhaseNo;

          long L1PhaseNo    = GetL1PhaseNo(Phase,Plant,PhaseNo);
          long L1PhaseType  = GetL1PhaseType(Phase);

          std::ostringstream L2PhaseName;
          L2PhaseName <<" L2EA140: Phase :" << Phase << " No: " <<PhaseNo << " L1 No : " << L1PhaseNo<< " Type: "<<L1PhaseType;
          log ("####"+L2PhaseName.str(),2);

          if ( L1PhaseType != CSMC_DBData::unspecLong )
          {
            CIntfData::setAt(SeqPhaseNo,          L1PhaseNo                           , i);
            CIntfData::setAt(SeqPhaseType,        L1PhaseType                         , i);
            CIntfData::setAt(SeqAimVoltTap,       EAFProcessPredRes.VoltTap           , i);
            CIntfData::setAt(SeqAimCurveNo,       EAFProcessPredRes.ImpCurve          , i);
            CIntfData::setAt(SeqAimReactorTap,    EAFProcessPredRes.ReactorTap        , i);
            CIntfData::setAt(SeqRemDurStep,       EAFProcessPredRes.DurStep           , i);
            CIntfData::setAt(SeqElecEnergyStep,   CDataConversion::RoundToLong(EAFProcessPredRes.ElecEgyStep) , i);
            CIntfData::setAt(SeqElecEnergyTotal,  CDataConversion::RoundToLong(EAFProcessPredRes.ElecEgy)     , i);
            //CIntfData::setAt(SeqAmountO2Total,    CDataConversion::RoundToLong(EAFProcessPredRes.O2Amount)    , i);
            CIntfData::setAt(SeqBaseWeight,       EAFProcessPredRes.BaseMass          , i);

            long   Step    = EAFProcessPredRes.Step;
            double ElecEgy = EAFProcessPredRes.ElecEgy;

            // *******************************************************************
            // Gas Lance
            // *******************************************************************
            for(long k = 0; k < CIntfData::getLength(SeqEAFGasLancePredRes) ; k++)
            {
              CIntfData::getAt(EAFGasLancePredRes,SeqEAFGasLancePredRes,k);

              if(std::string(EAFGasLancePredRes.Phase)  == Phase    && 
                EAFGasLancePredRes.PhaseNo == PhaseNo  && 
                EAFGasLancePredRes.Step    == Step)
              {

                seqDeviceGasData SeqDeviceGasData = EAFGasLancePredRes.GasFlow;

                for(long j = 0; j < CIntfData::getLength(SeqDeviceGasData) ; j++)
                {
                  sDeviceGasData DeviceGasData;
                  CIntfData::getAt(DeviceGasData,SeqDeviceGasData,j);

                  std::string Device    = DeviceGasData.Device;
                  seqGasData SeqGasData = DeviceGasData.GasData;
                  sGasData GasData;

                  // there is only one set of gas data per device
                  if ( CIntfData::getAt(GasData, SeqGasData, 0 ) )
                  {
                    if ( Device == DEF_GCE_INJECTION::Oxygen_Injector_1 )
                    {
                      CIntfData::setAt(SeqFlameProfile_O2SideLance_1,  GasData.GasValue * 60. , i); // Nm�/min -> Nm�/h
                    }
                    else if ( Device == DEF_GCE_INJECTION::Oxygen_Injector_2 )
                    {
                      CIntfData::setAt(SeqFlameProfile_O2SideLance_2,  GasData.GasValue * 60. , i);  // Nm�/min -> Nm�/h
                    }
                  }
                }
              }
            }

            // *******************************************************************
            // Burner
            // *******************************************************************
            long FlameProfile_Burner_1      = 0;
            long FlameProfile_Burner_2      = 0;
            long FlameProfile_Burner_3      = 0;
            long FlameProfile_Burner_4      = 0;
            long FlameProfile_Burner_5      = 0;
            long FlameProfile_Burner_Door   = 0;
            long FlameProfile_Burner_EBT    = 0;

            for(long k = 0; k < CIntfData::getLength(SeqEAFBurnerPredRes) ; k++)
            {
              CIntfData::getAt(EAFBurnerPredRes,SeqEAFBurnerPredRes,k);

              if(std::string(EAFBurnerPredRes.Phase)  == Phase    && 
                EAFBurnerPredRes.PhaseNo == PhaseNo  && 
                EAFBurnerPredRes.Step    == Step     )           
                //(PrevElecEgy <= EAFBurnerPredRes.ElecEgy &&
                //EAFBurnerPredRes.ElecEgy >= ElecEgy) )
              {

                std::string BurnerName    = EAFBurnerPredRes.BurnerName;
                long BurnerStepSpecEgy    = CDataConversion::RoundToLong(EAFBurnerPredRes.ElecEgyStep);
                long BurnerEgyTotal       = CDataConversion::RoundToLong(EAFBurnerPredRes.ElecEgy);
                long FlameProfile_Burner  = EAFBurnerPredRes.FlameProfile_Burner;

                // remember last burner profile, update on change of burner only
                if ( BurnerName == DEF_GCE_BURNER::Burner_1 )
                {
                  FlameProfile_Burner_1 = FlameProfile_Burner;
                }
                else if ( BurnerName == DEF_GCE_BURNER::Burner_2 )
                {
                  FlameProfile_Burner_2 = FlameProfile_Burner;
                }
                else if ( BurnerName == DEF_GCE_BURNER::Burner_3 )
                {
                  FlameProfile_Burner_3 = FlameProfile_Burner;
                }
                else if ( BurnerName == DEF_GCE_BURNER::DoorBurner )
                {
                  FlameProfile_Burner_Door = FlameProfile_Burner;
                }
                else if ( BurnerName == DEF_GCE_BURNER::EBTBurner )
                {
                  FlameProfile_Burner_EBT = FlameProfile_Burner;
                }

                CIntfData::setAt(SeqFlameProfile_O2SideLance_1,FlameProfile_Burner_1,i);
                CIntfData::setAt(SeqFlameProfile_O2SideLance_2,FlameProfile_Burner_2,i);
                CIntfData::setAt(SeqFlameProfile_O2SideLance_3,FlameProfile_Burner_3,i);
                CIntfData::setAt(SeqFlameProfile_O2SideLance_4,FlameProfile_Burner_4,i);
                CIntfData::setAt(SeqFlameProfile_O2SideLance_5,FlameProfile_Burner_5,i);
                CIntfData::setAt(SeqFlowRateO2EBTLance,    FlameProfile_Burner_EBT, i );
                CIntfData::setAt(SeqFlowRateO2DoorLance,   FlameProfile_Burner_Door,  i );
                CIntfData::setAt(SeqAmountO2Total,    CDataConversion::RoundToLong(EAFBurnerPredRes.O2Flow * EAFBurnerPredRes.DurStep)    , i);
                PrevElecEgy = EAFBurnerPredRes.ElecEgy;
              }           
            }

            // *******************************************************************
            // Material Feeding
            // *******************************************************************
            for(long k = 0; k < CIntfData::getLength(SeqEAFMatFeedPredRes) ; k++)
            {
              CIntfData::getAt(EAFMatFeedPredRes,SeqEAFMatFeedPredRes,k);

              if(std::string(EAFMatFeedPredRes.PhaseName) == Phase    && 
                EAFMatFeedPredRes.BasketNo   == PhaseNo  && 
                EAFMatFeedPredRes.Step       == Step)
              {
                seqBatch SeqBatch = EAFMatFeedPredRes.MatFeedData;        

                // up to 7 materials per step
                long Materials = CIntfData::getLength(SeqBatch);

                for(long Counter = 0; Counter < Materials; Counter++)
                {
                  sBatch sBatch;
                  CIntfData::getAt(sBatch,SeqBatch,Counter);

                  if( Counter == 0 )
                  {
                    MatCode_1   = sBatch.MatCode;

                    CIntfData::setAt(SeqFeedingRate_1,  sBatch.MatFeedSpeed, i);
                 // mrut 2014-02-10 :  JIRA SMPJSWTWO-55 : The feeding mass should be determined together with the feeding rate and duration, not in a separate module (EAF-handler)
                 // CIntfData::setAt(SeqTargetAmount_1, CDataConversion::RoundToLong(EAFMatFeedPredRes.DurStep*sBatch.MatFeedSpeed), i);
                    CIntfData::setAt(SeqTargetAmount_1, CDataConversion::RoundToLong(sBatch.Mass), i);
                  }
                  else if( Counter == 1 )
                  {
                    MatCode_2   = sBatch.MatCode;
                    CIntfData::setAt(SeqFeedingRate_2,  sBatch.MatFeedSpeed, i);
                 // mrut 2014-02-10 :  JIRA SMPJSWTWO-55 : The feeding mass should be determined together with the feeding rate and duration, not in a separate module (EAF-handler)
                 // CIntfData::setAt(SeqTargetAmount_2, CDataConversion::RoundToLong(EAFMatFeedPredRes.DurStep*sBatch.MatFeedSpeed), i);
                    CIntfData::setAt(SeqTargetAmount_2, CDataConversion::RoundToLong(sBatch.Mass), i);
                  }
                  else if( Counter == 2 )
                  {
                    MatCode_3   = sBatch.MatCode;
                    CIntfData::setAt(SeqFeedingRate_3,  sBatch.MatFeedSpeed, i);
                 // mrut 2014-02-10 :  JIRA SMPJSWTWO-55 : The feeding mass should be determined together with the feeding rate and duration, not in a separate module (EAF-handler)
                 // CIntfData::setAt(SeqTargetAmount_3, CDataConversion::RoundToLong(EAFMatFeedPredRes.DurStep*sBatch.MatFeedSpeed), i);
                    CIntfData::setAt(SeqTargetAmount_3, CDataConversion::RoundToLong(sBatch.Mass), i);
                  }
                  else if( Counter == 3 )
                  {
                    MatCode_4   = sBatch.MatCode;
                    CIntfData::setAt(SeqFeedingRate_4,  sBatch.MatFeedSpeed, i);
                 // mrut 2014-02-10 :  JIRA SMPJSWTWO-55 : The feeding mass should be determined together with the feeding rate and duration, not in a separate module (EAF-handler)
                 // CIntfData::setAt(SeqTargetAmount_4, CDataConversion::RoundToLong(EAFMatFeedPredRes.DurStep*sBatch.MatFeedSpeed), i);
                    CIntfData::setAt(SeqTargetAmount_4, CDataConversion::RoundToLong(sBatch.Mass), i);
                  }
                  else if( Counter == 4 )
                  {
                    MatCode_5   = sBatch.MatCode;
                    CIntfData::setAt(SeqFeedingRate_5,  sBatch.MatFeedSpeed, i);
                 // mrut 2014-02-10 :  JIRA SMPJSWTWO-55 : The feeding mass should be determined together with the feeding rate and duration, not in a separate module (EAF-handler)
                 // CIntfData::setAt(SeqTargetAmount_5, CDataConversion::RoundToLong(EAFMatFeedPredRes.DurStep*sBatch.MatFeedSpeed), i);
                    CIntfData::setAt(SeqTargetAmount_5, CDataConversion::RoundToLong(sBatch.Mass), i);
                  }
                  else if( Counter == 5 )
                  {
                    MatCode_6   = sBatch.MatCode;
                    CIntfData::setAt(SeqFeedingRate_6,  sBatch.MatFeedSpeed, i);
                 // mrut 2014-02-10 :  JIRA SMPJSWTWO-55 : The feeding mass should be determined together with the feeding rate and duration, not in a separate module (EAF-handler)
                 // CIntfData::setAt(SeqTargetAmount_6, CDataConversion::RoundToLong(EAFMatFeedPredRes.DurStep*sBatch.MatFeedSpeed), i);
                    CIntfData::setAt(SeqTargetAmount_6, CDataConversion::RoundToLong(sBatch.Mass), i);
                  }
                  else if( Counter == 6 )
                  {
                    MatCode_7   = sBatch.MatCode;
                    CIntfData::setAt(SeqFeedingRate_7,  sBatch.MatFeedSpeed, i);
                 // mrut 2014-02-10 :  JIRA SMPJSWTWO-55 : The feeding mass should be determined together with the feeding rate and duration, not in a separate module (EAF-handler)
                 // CIntfData::setAt(SeqTargetAmount_7, CDataConversion::RoundToLong(EAFMatFeedPredRes.DurStep*sBatch.MatFeedSpeed), i);
                    CIntfData::setAt(SeqTargetAmount_7, CDataConversion::RoundToLong(sBatch.Mass), i);
                  }
                  else if( Counter == 7 )
                  {
                    MatCode_8   = sBatch.MatCode;
                    CIntfData::setAt(SeqFeedingRate_8,  sBatch.MatFeedSpeed, i);
                 // mrut 2014-02-10 :  JIRA SMPJSWTWO-55 : The feeding mass should be determined together with the feeding rate and duration, not in a separate module (EAF-handler)
                 // CIntfData::setAt(SeqTargetAmount_8, CDataConversion::RoundToLong(EAFMatFeedPredRes.DurStep*sBatch.MatFeedSpeed), i);
                    CIntfData::setAt(SeqTargetAmount_8, CDataConversion::RoundToLong(sBatch.Mass), i);
                  }
                  else if( Counter == 8 )
                  {
                    MatCode_9   = sBatch.MatCode;
                    CIntfData::setAt(SeqFeedingRate_9,  sBatch.MatFeedSpeed, i);
                 // mrut 2014-02-10 :  JIRA SMPJSWTWO-55 : The feeding mass should be determined together with the feeding rate and duration, not in a separate module (EAF-handler)
                 // CIntfData::setAt(SeqTargetAmount_9, CDataConversion::RoundToLong(EAFMatFeedPredRes.DurStep*sBatch.MatFeedSpeed), i);
                    CIntfData::setAt(SeqTargetAmount_9, CDataConversion::RoundToLong(sBatch.Mass), i);
                  }
                } // for(long Counter = 0; Counter < CIntfData::getLength(SeqEAFMatFeedPredRes); Counter++)
              } // if(std::string(EAFMatFeedPredRes.PhaseName) == Phase    && 
            } // for(long k = 0; k < CIntfData::getLength(SeqEAFMatFeedPredRes) ; k++)


            // *******************************************************************
            // Injectors
            // *******************************************************************
            for(long k = 0; k < CIntfData::getLength(SeqEAFInjectLanceRes) ; k++)
            {
              CIntfData::getAt(EAFInjectLanceRes,SeqEAFInjectLanceRes,k);

              if(std::string(EAFInjectLanceRes.Phase)  == Phase    && 
                EAFInjectLanceRes.PhaseNo == PhaseNo  &&
                EAFInjectLanceRes.Step    == Step  )               
              {
                seqInjectLanceData SeqInjectLanceData     = EAFInjectLanceRes.InjectFlow;

                double MatFlowRateCarbon        = 0.;
                double MatFlowRateSilicon       = 0.;

                for(long m = 0; m < CIntfData::getLength(SeqInjectLanceData) ; m++)
                {
                  sInjectLanceData InjectLanceData;
                  CIntfData::getAt(InjectLanceData,SeqInjectLanceData,m);

                  if ( DEF_GCE_INJECTION_TYPE::CarbonInjection == std::string(InjectLanceData.InjectionType) )
                  {
                    //right now just one system  !!! depens on configuration
                    MatFlowRateCarbon += InjectLanceData.Value;
                  }
                  else if ( DEF_GCE_INJECTION_TYPE::SiliconInjection == std::string(InjectLanceData.InjectionType) )
                  {
                    //right now just one system  !!! depens on configuration
                    MatFlowRateSilicon += InjectLanceData.Value;
                  }               
                }// for(long m = 0; m < CIntfData::getLength(SeqInjectLanceData) ; m++)

                if ( MatFlowRateCarbon > 0 )
                {
                  CIntfData::setAt(SeqFlowRateC_SideLance_1,    MatFlowRateCarbon,  i );

                  CIntfData::setAt(SeqAmountC_SideLance_1,  CDataConversion::RoundToDecimals(MatFlowRateCarbon * EAFProcessPredRes.DurStep,1),  i ); // kg/min * min 
                }

                if ( MatFlowRateSilicon > 0 )
                {
                  CIntfData::setAt(SeqFlowRateC_SideLance_2,    MatFlowRateSilicon,  i );

                  CIntfData::setAt(SeqAmountC_SideLance_2,  CDataConversion::RoundToDecimals(MatFlowRateSilicon * EAFProcessPredRes.DurStep,1),  i ); // kg/min * min 
                }
              }
            }


            // *******************************************************************
            // Bottrom Stirring
            // *******************************************************************
            for(long k = 0; k < CIntfData::getLength(SeqBottomStirrPredRes) ; k++)
            {
              CIntfData::getAt(EAFStirrPredRes,SeqBottomStirrPredRes,k);

              if(std::string(EAFStirrPredRes.Phase)     == Phase    && 
                EAFStirrPredRes.PhaseNo   == PhaseNo  && 
                EAFStirrPredRes.Step       == Step)
              {
                seqDeviceGasData  SeqDeviceGasData = EAFStirrPredRes.GasFlow;

                for(long j = 0; j < CIntfData::getLength(SeqBottomStirrPredRes) ; j++)
                {
                  sDeviceGasData  DeviceGasData;
                  CIntfData::getAt(DeviceGasData,SeqDeviceGasData,j);

                  seqGasData  seqFlow = DeviceGasData.GasData;

                  sGasData sFlow;
                  CIntfData::getAt(sFlow, seqFlow, 0);

                  if( std::string(sFlow.GasType)     == DEF_GC_STIRR_GAS_TYPE::Ar )
                  {
                    CIntfData::setAt(SeqStirrGasType,    1 ,  i );
                  }
                  else if( std::string(sFlow.GasType) == DEF_GC_STIRR_GAS_TYPE::N2 )
                  {
                    CIntfData::setAt(SeqStirrGasType,    2 ,  i );
                  }

                  CIntfData::setAt(SeqStirrGasFlow,    sFlow.GasValue ,  i );
                }
              }
            }//for(long k = 0; k < CIntfData::getLength(SeqBottomStirrPredRes) ; k++)
          }// if ( L1PhaseType != CSMC_DBData::unspecLong )
        } // for( it = Phases.begin(); it != Phases.end() ; it++)

        //********    Write telegram data  ***********************************************************************

        DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

        pTelcom_Interface->setString   ( DataKeyL1, Telegram_L2EA40_PROC_PATT::CreateTime,   Now.toDBString());   
        pTelcom_Interface->setString   ( DataKeyL1, Telegram_L2EA40_PROC_PATT::HeatId,       HeatID);   
        pTelcom_Interface->setString   ( DataKeyL1, Telegram_L2EA40_PROC_PATT::TreatId,      TreatID);   

        Telegram_L2EA40_PROC_PATT::t_ENTRY seqENTRY;

        for(long j = 0; j < SeqLenght ; j++)
        {
          Telegram_L2EA40_PROC_PATT::sENTRY ENTRY;
          
          ENTRY.MessageIndex            = j;
          ENTRY.HeatId                  = HeatID.c_str()         ;
          ENTRY.TreatId                 = TreatID.c_str()        ;

          CIntfData::getAt(ENTRY.PhaseNo                ,SeqPhaseNo                 ,j);
          CIntfData::getAt(ENTRY.PhaseType              ,SeqPhaseType               ,j);
          CIntfData::getAt(ENTRY.AimVoltTap             ,SeqAimVoltTap              ,j);
          CIntfData::getAt(ENTRY.AimCurveNo             ,SeqAimCurveNo              ,j); 
          CIntfData::getAt(ENTRY.AimReactorTap          ,SeqAimReactorTap           ,j);
          CIntfData::getAt(ENTRY.RemDurStep             ,SeqRemDurStep              ,j); 
          CIntfData::getAt(ENTRY.ElecEnergyStep		      ,SeqElecEnergyStep          ,j);	
          CIntfData::getAt(ENTRY.ElecEnergyTotal        ,SeqElecEnergyTotal         ,j);
          CIntfData::getAt(ENTRY.AmountO2Total          ,SeqAmountO2Total           ,j);
          CIntfData::getAt(ENTRY.FlowRateO2_EBTLance    ,SeqFlowRateO2EBTLance      ,j);
          CIntfData::getAt(ENTRY.FlowRateO2_DoorLance   ,SeqFlowRateO2DoorLance     ,j);
          CIntfData::getAt(ENTRY.FlowRateO2_SideLance_1 ,SeqFlameProfile_O2SideLance_1  ,j);
          CIntfData::getAt(ENTRY.FlowRateO2_SideLance_2 ,SeqFlameProfile_O2SideLance_2  ,j);
          CIntfData::getAt(ENTRY.FlowRateO2_SideLance_3 ,SeqFlameProfile_O2SideLance_3  ,j);
          CIntfData::getAt(ENTRY.FlowRateO2_SideLance_4 ,SeqFlameProfile_O2SideLance_4  ,j);
          CIntfData::getAt(ENTRY.FlowRateO2_SideLance_5 ,SeqFlameProfile_O2SideLance_5  ,j);
          CIntfData::getAt(ENTRY.RatioCarbDust          ,SeqRatioCarbDust               ,j);
          CIntfData::getAt(ENTRY.FlowRateC_EBTLance     ,SeqFlowRateC_EBTLance           ,j);
          CIntfData::getAt(ENTRY.AmountC_EBTLance       ,SeqAmountC_EBTLance             ,j);
          CIntfData::getAt(ENTRY.FlowRateC_DoorLance    ,SeqFlowRateC_DoorLance          ,j);
          CIntfData::getAt(ENTRY.AmountC_DoorLance      ,SeqAmountC_DoorLance            ,j);
          CIntfData::getAt(ENTRY.FlowRateC_SideLance_1  ,SeqFlowRateC_SideLance_1        ,j);
          CIntfData::getAt(ENTRY.FlowRateC_SideLance_2  ,SeqFlowRateC_SideLance_2        ,j);
          CIntfData::getAt(ENTRY.AmountC_SideLance_1    ,SeqAmountC_SideLance_1         ,j);
          CIntfData::getAt(ENTRY.AmountC_SideLance_2    ,SeqAmountC_SideLance_2         ,j);
          ENTRY.MatCode_1                               = MatCode_1.c_str();
          CIntfData::getAt(ENTRY.FeedingRate_1          ,SeqFeedingRate_1             ,j);
          CIntfData::getAt(ENTRY.TargetAmount_1         ,SeqTargetAmount_1            ,j);
          ENTRY.MatCode_2                               = MatCode_2.c_str();
          CIntfData::getAt(ENTRY.FeedingRate_2          ,SeqFeedingRate_2             ,j);
          CIntfData::getAt(ENTRY.TargetAmount_2         ,SeqTargetAmount_2            ,j);
          ENTRY.MatCode_3                               = MatCode_3.c_str();
          CIntfData::getAt(ENTRY.FeedingRate_3          ,SeqFeedingRate_3             ,j);
          CIntfData::getAt(ENTRY.TargetAmount_3         ,SeqTargetAmount_3            ,j);
          ENTRY.MatCode_4                               = MatCode_4.c_str();
          CIntfData::getAt(ENTRY.FeedingRate_4          ,SeqFeedingRate_4             ,j);
          CIntfData::getAt(ENTRY.TargetAmount_4         ,SeqTargetAmount_4            ,j);
          ENTRY.MatCode_5                               = MatCode_5.c_str();
          CIntfData::getAt(ENTRY.FeedingRate_5          ,SeqFeedingRate_5             ,j);
          CIntfData::getAt(ENTRY.TargetAmount_5         ,SeqTargetAmount_5            ,j);
          ENTRY.MatCode_6                               = MatCode_6.c_str();
          CIntfData::getAt(ENTRY.FeedingRate_6          ,SeqFeedingRate_6             ,j);
          CIntfData::getAt(ENTRY.TargetAmount_6         ,SeqTargetAmount_6            ,j);
          ENTRY.MatCode_7                               = MatCode_7.c_str();
          CIntfData::getAt(ENTRY.FeedingRate_7          ,SeqFeedingRate_7             ,j);
          CIntfData::getAt(ENTRY.TargetAmount_7         ,SeqTargetAmount_7            ,j);
          ENTRY.MatCode_8                               = MatCode_8.c_str();
          CIntfData::getAt(ENTRY.FeedingRate_8          ,SeqFeedingRate_8             ,j);
          CIntfData::getAt(ENTRY.TargetAmount_8         ,SeqTargetAmount_8            ,j);
          ENTRY.MatCode_9                               = MatCode_9.c_str();
          CIntfData::getAt(ENTRY.FeedingRate_9          ,SeqFeedingRate_9             ,j);
          CIntfData::getAt(ENTRY.TargetAmount_9         ,SeqTargetAmount_9            ,j);
          CIntfData::getAt(ENTRY.BaseWeight             ,SeqBaseWeight                ,j);
          CIntfData::getAt(ENTRY.StirrGasType           ,SeqStirrGasType              ,j);
          CIntfData::getAt(ENTRY.StirrGasFlowrate       ,SeqStirrGasFlow              ,j);
          ENTRY.Spare_1                                 = Spare_1                   ;
          ENTRY.Spare_2                                 = Spare_2                   ;
          ENTRY.Spare_3                                 = Spare_3                   ;
          ENTRY.Spare_4                                 = Spare_4                   ;
          ENTRY.Spare_5                                 = Spare_5                   ;

          CIntfData::insert(seqENTRY,ENTRY);
          //********    Dispatch event ****** *****************************************************************
        }

        CORBA::Any seqAny;
        seqAny = CIntfData::ToAny(seqENTRY);

        pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2EA40_PROC_PATT::ENTRY       ,     seqAny);

        pTelcom_Interface->showContent(DataKeyL1, 4);


        SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);


        //********    End processing data  ***********************************************************************
      }// if ( !HeatID.empty() && HeatID != DEF::Inv_String )
      else
      {
        RetValue = false;

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_InvalidTlgData(sMessage,TlgName.c_str(),"HeatID","empty");  
      }

      log( TlgName + ": End", 3);

    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorPointerHandling(sMessage,Function.c_str()," pDM_Interface or pTelcom_Interface invalid ");
      RetValue=false;
    }
    
    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;
}// bool CEAF_EventHandler::provideData_L2EA40_PROCESS_PATT(const std::string& Key, const std::string& TlgName

bool  CEAF_EventHandler::provideData_L2EA41_PROC_VALUES(CEventMessage& Event)
{
  bool RetValue = true; // assume success

  //------------ read the data from Event ------------------
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID(); 
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID); // =  DEF_GC_PLANT_DEF::EAF
  long UnitNo           = m_pGC_Plant_Container->getPlantNo(PlantID);


  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2EA41_PROC_VALUES";
  std::string Function = "CEAF_EventHandler::provideData_L2EA41_PROC_VALUES";

  try
  {
    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    if ( pDM_Interface && pTelcom_Interface )
    {
      if ( !HeatID.empty() && HeatID != DEF::Inv_String )
      {       
        // truncate string data to fit telegram length
        HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
        TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

        OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

        //********    preset data  ************************************************************************

        log("****************************************************************************************", 3);
        log( TlgName + ": Start", 3);
        log("****************************************************************************************", 3);


        DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

        std::string curPhaseName;

        long PhaseNo          = 0;
        long PhaseType        = 0;
        //Electric
        long AimVoltTap       = 0   ;
        long AimCurveNo       = 0   ;
        long AimReactTapNo    = 0   ;
        long ElecEnergyStep   = 0  ;
        long ElecEnergyTotal  = 0;

        long AmountO2Total    = 0;
        long RatioCarbDust    = 0; // always 0%, there is no dust

        double RemDurStep           = 0;
        double NextPhaseEnergyTotal = 0;

        // burner / O2 lance
        double FlowRateO2_SideLance_1 = 0;
        double FlowRateO2_SideLance_2 = 0;
        double FlowRateO2_SideLance_3 = 0;
        double FlowRateO2_SideLance_4 = 0;
        double FlowRateO2_SideLance_5 = 0;
        double FlowRateO2_DoorLance   = 0;
        double FlowRateO2_EBTLance    = 0;

        double FlowRateC_SideLance_1        = 0.;
        double FlowRateC_SideLance_2        = 0.;
        double MatFlowRateEBTDoor_1         = 0.;
        double MatFlowRateEBTDoor_2         = 0.;
        double AmountC_SideLance_1          = 0.;
        double AmountC_SideLance_2          = 0.;
        double AmountC_EBTLance             = 0.;
        double AmountC_DoorLance           = 0.;


        //Mat Feeding
        std::string     MatCode_1;                
        std::string     MatCode_2;                
        std::string     MatCode_3;               
        std::string     MatCode_4;
        std::string     MatCode_5; 
        std::string     MatCode_6; 
        std::string     MatCode_7;
        std::string     MatCode_8;
        std::string     MatCode_9;

        //int  lMatWeight ;
        double FeedingRate_1 = 0;
        double FeedingRate_2 = 0;
        double FeedingRate_3 = 0;
        double FeedingRate_4 = 0;
        double FeedingRate_5 = 0;
        double FeedingRate_6 = 0;
        double FeedingRate_7 = 0;
        double FeedingRate_8 = 0;
        double FeedingRate_9 = 0;

        double TargetAmount_1 = 0;
        double TargetAmount_2 = 0;
        double TargetAmount_3 = 0;
        double TargetAmount_4 = 0;
        double TargetAmount_5 = 0;
        double TargetAmount_6 = 0;
        double TargetAmount_7 = 0;
        double TargetAmount_8 = 0;
        double TargetAmount_9 = 0;

        long lngStirrGasType      = 0;
        long Spare_1 = 0;
        long Spare_2 = 0;
        long Spare_3 = 0;
        long Spare_4 = 0;
        long Spare_5 = 0;

        seqEAFProcessPredRes  SeqEAFProcessPredRes  = CIntfData::ToCORBAType(pDM_Interface->getEAFProcessPredRes( ProductID.c_str(), DATA::EAFProcessPredRes));
        seqPredRes SeqEAFPredRes                    = CIntfData::ToCORBAType(pDM_Interface->getPredRes          ( ProductID.c_str(), DATA::EAFPredRes));
        seqGasLanceData SeqEAFBurnerAmount          = CIntfData::ToCORBAType(pDM_Interface->getGasLanceData     ( ProductID.c_str(), DATA::EAFBurnerAmount));
        seqGasLanceData SeqEAFGasLanceAmount        = CIntfData::ToCORBAType(pDM_Interface->getGasLanceData     ( ProductID.c_str(), DATA::EAFGasLanceAmount));
        seqInjectLanceData SeqEAFInjectLanceAmount  = CIntfData::ToCORBAType(pDM_Interface->getInjectLanceData  ( ProductID.c_str(), DATA::EAFInjectLanceAmount));
        seqBatch seqRecipeContent                   = CIntfData::ToCORBAType(pDM_Interface->getBatch            ( ProductID.c_str(), DATA::RecipeContent));

				log(CIntfData::getContent(CIntfData::ToAny(SeqEAFInjectLanceAmount)),4);

        long BaseWeight          = (long)pDM_Interface->getDouble(ProductID.c_str(),DATA::AimWeight);

        double StirrGasFlow       = pDM_Interface->getDouble(ProductID.c_str(),DATA::EAFActSetPointStirrFlow);
        std::string StirrGasType  = pDM_Interface->getString(ProductID.c_str(),DATA::EAFActSetPointStirrGasType);

        //First get Phase and PhaseNO
        long currentPhaseNo = 0;

        sPredRes PredRes;
        for (int i = 0 ; i < CIntfData::getLength(SeqEAFPredRes); ++i)
        {
          CIntfData::getAt(PredRes, SeqEAFPredRes, i);

          if(PredRes.PhaseActive == 1)
          {
            curPhaseName    = PredRes.Phase;
            currentPhaseNo  = PredRes.PhaseNo;
            RemDurStep      = PredRes.GenRes.DurPhase;
            ElecEnergyStep  = 0;///Not needed
            ElecEnergyTotal = CDataConversion::RoundToLong(PredRes.GenRes.MetTimeStamp.Elec_Moment); //Not needed
            //lBaseMass = PredRes.GenRes.SteelWeight;
            break;
          }
        }

        PhaseNo   = GetL1PhaseNo(curPhaseName,Plant,currentPhaseNo); //get PhaseNo from GC_Phase
        PhaseType = GetL1PhaseType(curPhaseName);

        if ( PhaseType != CSMC_DBData::unspecLong )
        {
          //get electric related info
          AimVoltTap    = pDM_Interface->getLong(ProductID.c_str(),DATA::VoltTapNoAim);
          AimCurveNo    = pDM_Interface->getLong(ProductID.c_str(),DATA::ElectrodRegCurveAim);
          AimReactTapNo = pDM_Interface->getLong(ProductID.c_str(),DATA::ReactTapNoAim);

          AimReactTapNo = CDataConversion::SetInvalidToDefault(AimReactTapNo, 0 );

          // *******************************************************************
          // Gas Lance
          // *******************************************************************
          sGasLanceData  sDataGasLance;
          for(long k = 0; k < CIntfData::getLength(SeqEAFGasLanceAmount) ; k++)
          {
            CIntfData::getAt(sDataGasLance,SeqEAFGasLanceAmount,k);

            std::string DeviceName  = sDataGasLance.Device;
            long L1DeviceNo         = 0;
            double GasFlow          = 0.; 

            if ( m_pGCE_INJECTION )
            {
              L1DeviceNo         = m_pGCE_INJECTION->getL1DeviceNo(Plant, UnitNo, DeviceName);
            }

            for(long i = 0; i < CIntfData::getLength(sDataGasLance.LanceData) ; i++)
            {
              sGasData sGData;
              CIntfData::getAt(sGData,sDataGasLance.LanceData,i);

              GasFlow = sGData.GasValue;

              if ( L1DeviceNo == 1 )
              {
                FlowRateO2_SideLance_1 = GasFlow * 60. ; // Nm�/min -> Nm�/h
              }
              else if ( L1DeviceNo == 2 )
              {
                FlowRateO2_SideLance_2 = GasFlow * 60. ; // Nm�/min -> Nm�/h
              }
            }
          }

          // *******************************************************************
          // Burner
          // *******************************************************************
          sGasLanceData  sDataBurner;
          for(long k = 0; k < CIntfData::getLength(SeqEAFBurnerAmount) ; k++)
          {
            CIntfData::getAt(sDataBurner,SeqEAFBurnerAmount,k);

            std::string BurnerName    = sDataBurner.Device;
            double GasFlow     = 0.; 
            double O2Flow      = 0.; 

            for(long i = 0; i < CIntfData::getLength(sDataBurner.LanceData) ; i++)
            {
              sGasData sGData;
              CIntfData::getAt(sGData,sDataBurner.LanceData,i);

              if ( std::string(sGData.GasType) == DEF_GCE_BURNER_GASTYPE::BG )
              {
                GasFlow = sGData.GasValue;
              }
              else if ( std::string(sGData.GasType) == DEF_GCE_BURNER_GASTYPE::O2 )
              {
                O2Flow = sGData.GasValue;
              }
            }

            // remember last burner profile, update on change of burner only
/*    see gas lance data        if ( BurnerName == DEF_GCE_BURNER::Burner_1 )
            {
              if(m_pGTE_PP_FLAME_PROFILE->selectbyFlowData(Plant, UnitNo, BurnerName, O2Flow,GasFlow))
              {
                FlowRateO2_SideLance_1 = m_pGTE_PP_FLAME_PROFILE->getFLAMEPROFILENO(1);
              }
              else
              {
                FlowRateO2_SideLance_1 = 0;
              }
            }
            else if ( BurnerName == DEF_GCE_BURNER::Burner_2 )
            {
              if(m_pGTE_PP_FLAME_PROFILE->selectbyFlowData(Plant, UnitNo, BurnerName, O2Flow,GasFlow))
              {
                FlowRateO2_SideLance_2 = m_pGTE_PP_FLAME_PROFILE->getFLAMEPROFILENO(1);
              }
              else
              {
                FlowRateO2_SideLance_2 = 0;
              }
            }
            else */if ( BurnerName == DEF_GCE_BURNER::Burner_3 )
            {
              if(m_pGTE_PP_FLAME_PROFILE->selectbyFlowData(Plant, UnitNo, BurnerName, O2Flow,GasFlow))
              {
                FlowRateO2_SideLance_3 = m_pGTE_PP_FLAME_PROFILE->getFLAMEPROFILENO(1);
              }
              else
              {
                FlowRateO2_SideLance_3 = 0;
              }
            }
            else if ( BurnerName == DEF_GCE_BURNER::DoorBurner )
            {
              if(m_pGTE_PP_FLAME_PROFILE->selectbyFlowData(Plant, UnitNo, BurnerName, O2Flow,GasFlow))
              {
                FlowRateO2_DoorLance = m_pGTE_PP_FLAME_PROFILE->getFLAMEPROFILENO(1);
              }
              else
              {
                FlowRateO2_DoorLance = 0;
              }
            }
            else if ( BurnerName == DEF_GCE_BURNER::EBTBurner )
            {
              if(m_pGTE_PP_FLAME_PROFILE->selectbyFlowData(Plant, UnitNo, BurnerName, O2Flow,GasFlow))
              {
                FlowRateO2_EBTLance = m_pGTE_PP_FLAME_PROFILE->getFLAMEPROFILENO(1);
              }
              else
              {
                FlowRateO2_EBTLance = 0;
              }
            }
          }

          // *******************************************************************
          // Material Feeding
          // *******************************************************************
          for(int Counter =0; Counter < CIntfData::getLength(seqRecipeContent); Counter++)
          {
            sBatch sBatch;
            CIntfData::getAt(sBatch,seqRecipeContent,Counter);

            std::string strMatCode = sBatch.MatCode;
            double dFeedSpeed      = sBatch.MatFeedSpeed;

            if ( sBatch.FeedingRateRel2Energy > 0. )
            {
              dFeedSpeed =  sBatch.FeedingRateRel2Energy;
            }

            if( Counter == 0 )
            {
              MatCode_1     = sBatch.MatCode;
              FeedingRate_1 = dFeedSpeed;
              TargetAmount_1 = CDataConversion::RoundToLong(sBatch.Mass);
            }
            else if( Counter == 1 )
            {
              MatCode_2   = sBatch.MatCode;
              FeedingRate_2 = dFeedSpeed;
              TargetAmount_2 = CDataConversion::RoundToLong(sBatch.Mass) ;
            }
            else if( Counter == 2 )
            {
              MatCode_3 = sBatch.MatCode;
              FeedingRate_3 = dFeedSpeed;
              TargetAmount_3 = CDataConversion::RoundToLong(sBatch.Mass) ;
            }
            else if( Counter == 3 )
            {
              MatCode_4   = sBatch.MatCode;
              FeedingRate_4 = dFeedSpeed;
              TargetAmount_4 = CDataConversion::RoundToLong(sBatch.Mass) ;
            }
            else if( Counter == 4 )
            {
              MatCode_5      = sBatch.MatCode;
              FeedingRate_5  = dFeedSpeed;
              TargetAmount_5 =  CDataConversion::RoundToLong(sBatch.Mass);
            }
            else if( Counter == 5 )
            {
              MatCode_6      = sBatch.MatCode;
              FeedingRate_6  = dFeedSpeed;
              TargetAmount_6 = CDataConversion::RoundToLong(sBatch.Mass) ;
            }
            else if( Counter == 6 )
            {
              MatCode_7   = sBatch.MatCode;
              FeedingRate_7 =  dFeedSpeed;
              TargetAmount_7 = CDataConversion::RoundToLong(sBatch.Mass) ;
            }
            else if( Counter == 7 )
            {
              MatCode_8   = sBatch.MatCode;
              FeedingRate_8 =  dFeedSpeed;
              TargetAmount_8 = CDataConversion::RoundToLong(sBatch.Mass) ;
            }
            else if( Counter == 8 )
            {
              MatCode_9   = sBatch.MatCode;
              FeedingRate_9 =  dFeedSpeed;
              TargetAmount_9 = CDataConversion::RoundToLong(sBatch.Mass) ;
            }
          }

          // *******************************************************************
          // Injectors
          // *******************************************************************
          for(long k = 0; k < CIntfData::getLength(SeqEAFInjectLanceAmount) ; k++)
          {
            sInjectLanceData sInj;
            CIntfData::getAt(sInj,SeqEAFInjectLanceAmount,k);

            double MatFlowRateCarbon        = 0.;
            double MatFlowRateSilicon       = 0.;

            if ( DEF_GCE_INJECTION_TYPE::CarbonInjection == std::string(sInj.InjectionType) )
            {
              //right now just one system  !!! depens on configuration
              MatFlowRateCarbon += sInj.Value;
            }
            else if ( DEF_GCE_INJECTION_TYPE::SiliconInjection == std::string(sInj.InjectionType) )
            {
              //right now just one system  !!! depens on configuration
              MatFlowRateSilicon += sInj.Value;
            }

            if ( MatFlowRateCarbon > 0 )
            {
              FlowRateC_SideLance_1 = MatFlowRateCarbon;
              AmountC_SideLance_1   = CDataConversion::RoundToDecimals(MatFlowRateCarbon * RemDurStep,1); // kg/min * min 
            }

            if ( MatFlowRateSilicon > 0 )
            {
              FlowRateC_SideLance_2 = MatFlowRateSilicon;
              AmountC_SideLance_2   = CDataConversion::RoundToDecimals(MatFlowRateSilicon * RemDurStep,1); // kg/min * min 
            }
          }

          // *******************************************************************
          // Bottrom Stirring
          // *******************************************************************

          if(DEF_GAS::Ar == StirrGasType)
          {
            lngStirrGasType = 1;
          }
          else if(DEF_GAS::N2 == StirrGasType)
          {
            lngStirrGasType = 2;
          }

          sEAFProcessPredRes  EAFProcessPredRes;
          for(long i = 0; i < CIntfData::getLength(SeqEAFProcessPredRes) ; i++)
          {
            CIntfData::getAt(EAFProcessPredRes,SeqEAFProcessPredRes,i);

            if ( std::string(EAFProcessPredRes.Phase) == curPhaseName && EAFProcessPredRes.PhaseNo == currentPhaseNo )
            {
              NextPhaseEnergyTotal += EAFProcessPredRes.ElecEgyStep;
            }
          }

          // truncate string data to fit telegram length
          HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
          TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

          StirrGasFlow   = CDataConversion::SetInvalidToDefault(StirrGasFlow,  0.);

          ElecEnergyStep = CDataConversion::RoundToLong(NextPhaseEnergyTotal) - ElecEnergyTotal;
          if ( ElecEnergyStep < 0 )
          {
            ElecEnergyStep = 0;
          }


          Telegram_L2EA41_PROC_VALUES::sENTRY ENTRY;
          
          ENTRY.MessageIndex            = 1;
          ENTRY.HeatId                  = HeatID.c_str()        ;
          ENTRY.TreatId                 = TreatID.c_str()       ;
          ENTRY.PhaseNo                 = PhaseNo               ;
          ENTRY.PhaseType               = PhaseType             ;
          ENTRY.AimVoltTap              = AimVoltTap            ;
          ENTRY.AimCurveNo              = AimCurveNo            ; 
          ENTRY.AimReactorTap           = AimReactTapNo         ;
          ENTRY.RemDurStep              = RemDurStep            ; 
          ENTRY.ElecEnergyStep		      = ElecEnergyStep        ;	
          ENTRY.ElecEnergyTotal         = ElecEnergyTotal       ;
          ENTRY.AmountO2Total           = AmountO2Total         ;
          ENTRY.FlowRateO2_EBTLance     = FlowRateO2_EBTLance ;
          ENTRY.FlowRateO2_DoorLance    = FlowRateO2_DoorLance  ;
          ENTRY.FlowRateO2_SideLance_1  = FlowRateO2_SideLance_1;
          ENTRY.FlowRateO2_SideLance_2  = FlowRateO2_SideLance_2;
          ENTRY.FlowRateO2_SideLance_3  = FlowRateO2_SideLance_3;
          ENTRY.FlowRateO2_SideLance_4  = FlowRateO2_SideLance_4;
          ENTRY.FlowRateO2_SideLance_5  = FlowRateO2_SideLance_5;
          ENTRY.RatioCarbDust           = RatioCarbDust         ;
          ENTRY.FlowRateC_EBTLance      = MatFlowRateEBTDoor_1  ;
          ENTRY.AmountC_EBTLance        = AmountC_EBTLance ;
          ENTRY.FlowRateC_DoorLance     = MatFlowRateEBTDoor_2  ;
          ENTRY.AmountC_DoorLance       = AmountC_DoorLance ;
          ENTRY.FlowRateC_SideLance_1   = FlowRateC_SideLance_1 ;
          ENTRY.FlowRateC_SideLance_2   = FlowRateC_SideLance_2 ;
          ENTRY.AmountC_SideLance_1     = AmountC_SideLance_1 ;
          ENTRY.AmountC_SideLance_2     = AmountC_SideLance_2 ;
          ENTRY.MatCode_1               = MatCode_1.c_str()             ;
          ENTRY.FeedingRate_1           = FeedingRate_1         ;
          ENTRY.TargetAmount_1          = TargetAmount_1        ;
          ENTRY.MatCode_2               = MatCode_2.c_str()             ;
          ENTRY.FeedingRate_2           = FeedingRate_2         ;
          ENTRY.TargetAmount_2          = TargetAmount_2        ;
          ENTRY.MatCode_3               = MatCode_3.c_str()             ;
          ENTRY.FeedingRate_3           = FeedingRate_3         ;
          ENTRY.TargetAmount_3          = TargetAmount_3        ;
          ENTRY.MatCode_4               = MatCode_4.c_str()             ;
          ENTRY.FeedingRate_4           = FeedingRate_4         ;
          ENTRY.TargetAmount_4          = TargetAmount_4        ;
          ENTRY.MatCode_5               = MatCode_5.c_str()             ;
          ENTRY.FeedingRate_5           = FeedingRate_5         ;
          ENTRY.TargetAmount_5          = TargetAmount_5        ;
          ENTRY.MatCode_6               = MatCode_6.c_str()             ;
          ENTRY.FeedingRate_6           = FeedingRate_6         ;
          ENTRY.TargetAmount_6          = TargetAmount_6        ;
          ENTRY.MatCode_7               = MatCode_7.c_str()             ;
          ENTRY.FeedingRate_7           = FeedingRate_7         ;
          ENTRY.TargetAmount_7          = TargetAmount_7        ;
          ENTRY.MatCode_8               = MatCode_8.c_str()             ;
          ENTRY.FeedingRate_8           = FeedingRate_8         ;
          ENTRY.TargetAmount_8          = TargetAmount_8        ;
          ENTRY.MatCode_9               = MatCode_9.c_str()             ;
          ENTRY.FeedingRate_9           = FeedingRate_9         ;
          ENTRY.TargetAmount_9          = TargetAmount_9        ;
          ENTRY.BaseWeight              = BaseWeight            ;
          ENTRY.StirrGasType            = lngStirrGasType          ;
          ENTRY.StirrGasFlowrate        = StirrGasFlow      ;
          ENTRY.Spare_1                 = Spare_1               ;
          ENTRY.Spare_2                 = Spare_2               ;
          ENTRY.Spare_3                 = Spare_3               ;
          ENTRY.Spare_4                 = Spare_4               ;
          ENTRY.Spare_5                 = Spare_5               ;


          Telegram_L2EA41_PROC_VALUES::t_ENTRY seqENTRY;
          CORBA::Any seqAny;

          CIntfData::insert(seqENTRY,ENTRY);

          seqAny = CIntfData::ToAny(seqENTRY);


          //********    Write telegram data  ***********************************************************************


          pTelcom_Interface->setString( DataKeyL1, Telegram_L2EA41_PROC_VALUES::HeatId,         HeatID);   
          pTelcom_Interface->setString( DataKeyL1, Telegram_L2EA41_PROC_VALUES::TreatId,        TreatID);   
          pTelcom_Interface->setLong  ( DataKeyL1, Telegram_L2EA41_PROC_VALUES::UnitNo,         UnitNo);
          pTelcom_Interface->setString( DataKeyL1, Telegram_L2EA41_PROC_VALUES::CreateTime,     Now.toDBString());   

          pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2EA41_PROC_VALUES::ENTRY       ,     seqAny);


          pTelcom_Interface->showContent(DataKeyL1, 4);

          //********    Dispatch event ****** *****************************************************************
          SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID); 

        }// if ( PhaseType != CSMC_DBData::unspecLong )

        //********    End processing data  ***********************************************************************
      }// if ( !HeatID.empty() && HeatID != DEF::Inv_String )
      else
      {
        RetValue = false;

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_InvalidTlgData(sMessage,TlgName.c_str(),"HeatID","empty");  
      }
    }// if ( pDM_Interface && m_pTelcom_Interface )
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorPointerHandling(sMessage,Function.c_str()," pDM_Interface or pTelcom_Interface invalid ");
      RetValue=false;
    }

    log( TlgName + ": End", 3);

    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }		
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;
}


bool CEAF_EventHandler::provideData_L2EA70_MAT_HANDL(CEventMessage& Event)
{
  //=================    M A T E R I A L   H A N D L I N G   ===============================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();

  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID);
  long 				PlantNo   = m_pGC_Plant_Container->getPlantNo(PlantID);
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  CDateTime Now;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2EA70_MAT_HANDL";
  std::string Function = "CEAF_EventHandler::provideData_L2EA70_MAT_HANDL";

  try
  {
    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    if ( pTelcom_Interface && pDM_Interface)
    {
      //********    preset data  ************************************************************************

      log("****************************************************************************************", 3);
      log( TlgName + ": Start: " + HeatID, 3);
      log("****************************************************************************************", 3);

      //********    Read event related data  ************************************************************************

      seqRecipeList RecipeList = CIntfData::ToCORBAType(pDM_Interface->getRecipeList(ProductID.c_str(),DATA::EAFMatRecipe));

      DEF::seqLong    Seql1Source;
      DEF::seqLong    Seql1RecipeNo;
      DEF::seqString  SeqMatCode;
      DEF::seqLong    SeqMatWeight;
      DEF::seqLong    SeqMatSequence;
      DEF::seqLong    SeqFeedSpeed;

      if ( !HeatID.empty() && HeatID != DEF::Inv_String )
      {
        //********    Convert and check event data  ***********************************************************
        // truncate string data to fit telegram length
        HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
        TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

        long Spare_1       = 0;
        long Spare_2       = 0;      

        std::string DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

        CORBA::Any seqAny;
        long MatCounter       = 0;
        long MatSeqLenght     = 300;

        // preset sequences with empty values
        CIntfData::preset(Seql1Source       ,0              ,MatSeqLenght);
        CIntfData::preset(Seql1RecipeNo     ,0              ,MatSeqLenght);
        CIntfData::preset(SeqMatCode        ,""             ,MatSeqLenght);
        CIntfData::preset(SeqMatWeight      ,0              ,MatSeqLenght);
        CIntfData::preset(SeqMatSequence    ,0              ,MatSeqLenght);
        CIntfData::preset(SeqFeedSpeed      ,0              ,MatSeqLenght);


        for (long ii=0; ii < CIntfData::getLength(RecipeList); ii++)    
        {
          long l1RecipeNo   = 0;
          long l1BatchNo    = 0;
          long l1Source     = 0;

          // get current Recipe from RecipeList
          sRecipe Recipe;
          CIntfData::getAt(Recipe,RecipeList,ii);

          //Get the recipe name from the table by recipe number and recipe name
          l1RecipeNo = m_pGC_Recipe_L1Container->getL1RecipeNoByL2Name ( Recipe.RecipeNo,std::string(Recipe.RecipeName));

          if ( l1RecipeNo != 0 && l1RecipeNo > 0 )
          {
            // get source from the table by string from L2
            l1Source = m_pGC_SourceContainer->getSourceL1InfoNoByName( std::string(Recipe.RecipeSource) );

            //get the content of current recipe
            seqBatchPrio SeqBatchPrio = Recipe.RecipeContent;
 
            if ( CIntfData::getLength(SeqBatchPrio) != 0 )
            {
              // max no of Materials limited by MatSeqLenght
              for (long jj=0; jj < MatSeqLenght ; jj++)    
              {
                // read batch data from Recipe
                sBatchPrio BatchPrio;

                if ( CIntfData::getAt(BatchPrio,SeqBatchPrio,jj) )
                {
                  long ChargPrio        = BatchPrio.ChargPrio;
                  std::string MatCode   = BatchPrio.BatchData.MatCode;
                  double Mass           = BatchPrio.BatchData.Mass;
                  long MatFeedSpeed     = (long)BatchPrio.BatchData.MatFeedSpeed;

                  MatCode   = CDataConversion::CheckLengthAndTruncate(MatCode,10);

                  CIntfData::setAt(Seql1Source     ,l1Source                          ,MatCounter);
                  CIntfData::setAt(Seql1RecipeNo   ,l1RecipeNo                        ,MatCounter);
                  CIntfData::setAt(SeqMatCode      ,MatCode.c_str()                   ,MatCounter);
                  CIntfData::setAt(SeqMatWeight    ,CDataConversion::RoundToLong(Mass),MatCounter);
                  CIntfData::setAt(SeqMatSequence  ,ChargPrio                         ,MatCounter);
                  CIntfData::setAt(SeqFeedSpeed    ,MatFeedSpeed                      ,MatCounter);

                  MatCounter++;
                }
              } // for (long jj=0; jj < CIntfData::getLength(SeqBatchPrio) ; jj++)    
            } // if ( CIntfData::getLength(SeqBatchPrio) != 0 )
          }  // if ( l1RecipeNo != 0 )

          //********    Write telegram data  ***********************************************************************

          Telegram_L2EA70_MAT_HANDL::t_ENTRY seqENTRY;

          for(long j = 0; j < MatSeqLenght ; j++)
          {
            Telegram_L2EA70_MAT_HANDL::sENTRY ENTRY;
          
            ENTRY.MessageIndex            = j;
            ENTRY.HeatId                  = HeatID.c_str()         ;
            ENTRY.TreatId                 = TreatID.c_str()        ;

            CIntfData::getAt(ENTRY.Source               ,Seql1Source           ,j);
            CIntfData::getAt(ENTRY.RecipeNo             ,Seql1RecipeNo         ,j);
            CIntfData::getAt(ENTRY.MatCode              ,SeqMatCode            ,j);
            CIntfData::getAt(ENTRY.MatWeight            ,SeqMatWeight          ,j);
            CIntfData::getAt(ENTRY.MatSequence          ,SeqMatSequence        ,j);
            CIntfData::getAt(ENTRY.FeedRate             ,SeqFeedSpeed          ,j);
            ENTRY.Spare_1                                 = Spare_1            ;
            ENTRY.Spare_2                                 = Spare_2            ;

            CIntfData::insert(seqENTRY,ENTRY);
            //********    Dispatch event ****** *****************************************************************
          }

          seqAny = CIntfData::ToAny(seqENTRY);

        } // for (long ii=0; ii < CIntfData::getLength(RecipeList); ii++)    

        // *************************************************************************
        // fill one entry to set data in datail table that L1 could reset batch list
        // *************************************************************************
        if ( CIntfData::getLength(RecipeList) == 0 )
        {
          //********    Write telegram data  ***********************************************************************

          Telegram_L2EA70_MAT_HANDL::t_ENTRY seqENTRY;

          for(long j = 0; j < MatSeqLenght ; j++)
          {
            Telegram_L2EA70_MAT_HANDL::sENTRY ENTRY;
          
            ENTRY.MessageIndex            = j;
            ENTRY.HeatId                  = HeatID.c_str();
            ENTRY.TreatId                 = TreatID.c_str();

            ENTRY.Source                  = 0;
            ENTRY.RecipeNo                = 0;
            ENTRY.MatCode                 = "";
            ENTRY.MatWeight               = 0;
            ENTRY.MatSequence             = 0;
            ENTRY.FeedRate                = 0;
            ENTRY.Spare_1                 = Spare_1;
            ENTRY.Spare_2                 = Spare_2;

            CIntfData::insert(seqENTRY,ENTRY);
          }

          seqAny = CIntfData::ToAny(seqENTRY);

        }

        //set the data to telcom interface
        pTelcom_Interface->setString   ( DataKeyL1, Telegram_L2EA70_MAT_HANDL::HeatId,          HeatID);
        pTelcom_Interface->setString   ( DataKeyL1, Telegram_L2EA70_MAT_HANDL::TreatId,         TreatID);
        pTelcom_Interface->setString   ( DataKeyL1, Telegram_L2EA70_MAT_HANDL::CreateTime,      Now.toDBString());   
        pTelcom_Interface->setAny      ( DataKeyL1, Telegram_L2EA70_MAT_HANDL::ENTRY,           seqAny);

        pTelcom_Interface->showContent(DataKeyL1, 4);

        //********    Dispatch event ***********************************************************************
        //            multiple telegrams send if model results contains more materials than defined in telegram sequence! 
        SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);

      } // if ( !HeatID.empty() && HeatID != DEF::Inv_String )

      //********    End processing data  ***********************************************************************

      log( TlgName + ": End", 3);
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorPointerHandling(sMessage,Function.c_str()," pDM_Interface or pTelcom_Interface invalid ");
      RetValue=false;
    }
    
    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;
}//bool CEAF_EventHandler::provideData_L2EA70_MAT_HANDL(CEventMessage& Event)

bool  CEAF_EventHandler::provideData_L2SY92_SCRAP_LOAD(CEventMessage& Event)
{
  //=================   S C R A P    L O A D   I N S T R U C T I O N    ===============================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();

  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID);
  long 				PlantNo   = m_pGC_Plant_Container->getPlantNo(PlantID);
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  long 				UnitNo    = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2SY92_SCRAP_LOAD";
  std::string Function = "CEAF_EventHandler::provideData_L2SY92_SCRAP_LOAD";

  log("****************************************************************************************", 3);
  log( TlgName + ": Start", 3);
  log("****************************************************************************************", 3);

  try
  {
    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    if ( pDM_Interface && pTelcom_Interface )
    {
      //********    preset data  ************************************************************************

      //********    Read event related data  ************************************************************************

      std::string ContainerType = CIntfData::ToStdString(pDM_Interface->getString(ProductID.c_str(),DATA::ContainerType));
      //std::string ProdOrderId    = CIntfData::ToStdString(pDM_Interface->getString(ProductID.c_str(),DATA::OrderID));

      //********    Log event data ***********************************************************************

      //********    Convert and check event data  ***********************************************************

      OrderID        = CDataConversion::SetInvalidToDefault(OrderID,       "");
      ContainerType  = CDataConversion::SetInvalidToDefault(ContainerType, "");
      //ContainerType = DEF_GC_SCRAP_CONTAINER_TYPE::Basket only used

      CustHeatID     = "";
      CustTreatID    = "";

      DEF::seqString    SeqMatCode;
      DEF::seqLong      SeqMatWeight;
      DEF::seqLong      SeqMatLoadSeq;

      long MatSeqLenght   = 10;

      if ( ContainerType.empty() )
      {
        ContainerType = CSMC_DBData::unspecString;
      }

      // we will send data for all available orders
      //if ( OrderID.empty() )
      //{
        OrderID = CSMC_DBData::unspecString;
      //}

      std::set<std::string> OrderIdList;

      // ***************************************************************************************
      // select heats in production that need update
      // ***************************************************************************************
      if  ( m_pPD_HEAT_DATA->selectCurrentHeat(Plant) )
      {
        for( long i = 1 ; i <= m_pPD_HEAT_DATA->getLastRow(); ++i )
        {
          if  ( m_pPP_HEAT->select(m_pPD_HEAT_DATA->getHEATID(i)) )
          {
            std::string PRODORDERID = m_pPP_HEAT->getPRODORDERID(1);

            if ( m_pPD_SCRAP_CONTAINER_ORDER->selectByContainerTypeAndState(Plant, PRODORDERID, CSMC_DBData::unspecString, DEF_GC_SCRAP_CONT_ORDER_STATUS::Planned) || 
                !m_pPD_SCRAP_CONTAINER_ORDER->selectByContainerTypeAndState(Plant, PRODORDERID, CSMC_DBData::unspecString, CSMC_DBData::unspecLong) )
            {
              log ("HEATID " + m_pPD_HEAT_DATA->getHEATID(i) + " IS ANNOUNCED",3);
              log ("ORDERID = " + PRODORDERID + ", FOUND = " + CDataConversion::LongToString(i), 1);

              OrderIdList.insert(PRODORDERID);
            }
          }// if  ( PP_HEAT.select(PD_HEAT_PLANT_REF.getHEATID(i)) )
        }// for( long i = 1 ; i <= PD_HEAT_PLANT_REF.getLastRow(); ++i )
      }// if  ( PD_HEAT_DATA.selectCurrentHeat(HeatInfo.Plant) )


      // *****************************************************************************************
      // select heats that are planned that need update
      // *****************************************************************************************
      if  ( m_pPP_HEAT_PLANT->selectByPlanningState(Plant, PlantNo, 1) )
      {
        for( long i = 1 ; i <= m_pPP_HEAT_PLANT->getLastRow(); ++i )
        {
          if  ( m_pPP_HEAT->select(m_pPP_HEAT_PLANT->getHEATID(i)) )
          {
            std::string PRODORDERID = m_pPP_HEAT->getPRODORDERID(1);

            if ( m_pPD_SCRAP_CONTAINER_ORDER->selectByContainerTypeAndState(Plant, PRODORDERID, CSMC_DBData::unspecString, DEF_GC_SCRAP_CONT_ORDER_STATUS::Planned) || 
                !m_pPD_SCRAP_CONTAINER_ORDER->selectByContainerTypeAndState(Plant, PRODORDERID, CSMC_DBData::unspecString, CSMC_DBData::unspecLong) )
            {
              log ("HEATID " + m_pPD_HEAT_DATA->getHEATID(i) + " IS PLANNED",3);
              log ("ORDERID = " + PRODORDERID + ", FOUND = " + CDataConversion::LongToString(i), 1);

              OrderIdList.insert(PRODORDERID);
            }
          }// f  ( PP_HEAT.select(PP_HEAT_PLANT.getHEATID(i)) )
        }// for( long i = 1 ; i <= PP_HEAT_PLANT.getLastRow(); ++i )
      }// if  ( PP_HEAT_PLANT.selectByPlanningState(Plant,PlantNo, 1, CSMC_DBData::unspecLong ) )


      // determine all orders to be send
      std::set<std::string>::iterator it;

      for ( it = OrderIdList.begin(); it != OrderIdList.end(); ++it )
      {
        std::string ActOrderId = (*it);
        log ("#### Scrap Order : "+ ActOrderId,3);

        if ( ActOrderId != CSMC_DBData::unspecString )
        {
          long TotalNoOfContainers = 0;

          if ( m_pPD_SCRAP_CONTAINER_ORDER->selectByContainerTypeAndState(Plant, ActOrderId, CSMC_DBData::unspecString, CSMC_DBData::unspecLong) )
          {
            TotalNoOfContainers = m_pPD_SCRAP_CONTAINER_ORDER->getLastRow();
          }

          // select all valid "planned" data in chronological ordered by treatstart_plan
          if ( m_pPD_SCRAP_CONTAINER_ORDER->selectByContainerTypeAndState(Plant, ActOrderId, ContainerType, DEF_GC_SCRAP_CONT_ORDER_STATUS::Planned) )
          {
            log ("#### Scrap Order : "+ ActOrderId+" found Container",3);

            for ( long i = 1 ; i <= m_pPD_SCRAP_CONTAINER_ORDER->getLastRow(); ++i )
            {
              // take all containers to determine 

              DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

              CIntfData::preset(SeqMatCode         ,"" ,MatSeqLenght);
              CIntfData::preset(SeqMatWeight       ,0  ,MatSeqLenght);
              CIntfData::preset(SeqMatLoadSeq      ,0  ,MatSeqLenght);

              // use DB values in case of selected data were invalid
              ContainerType       = m_pPD_SCRAP_CONTAINER_ORDER->getCONTAINERTYPE(i);
              long CONTAINERINSEQ = m_pPD_SCRAP_CONTAINER_ORDER->getCONTAINERINSEQ(i);
              long CONTAINERNO    = m_pPD_SCRAP_CONTAINER_ORDER->getCONTAINERNO(i);

              long CONTAINERTYPE = 0;
              if ( ContainerType == DEF_GC_SCRAP_CONTAINER_TYPE::Basket )
              {
                CONTAINERTYPE = 1;
              }
              else if ( ContainerType == DEF_GC_SCRAP_CONTAINER_TYPE::Chute )
              {
                CONTAINERTYPE = 2;
              }

              if ( m_pPP_HEAT && m_pPP_HEAT->selectOrder(ActOrderId) )
              {
                log ("#### Found in PP_HEAT Scrap Order : "+ ActOrderId,3);

                // get respective prodorderid from planning data
                if ( m_pPP_HEAT_PLANT && m_pPP_HEAT_PLANT->selectByHeatData(m_pPP_HEAT->getHEATID(1), CSMC_DBData::unspecString, Plant, false) )
                {
                  CustHeatID              = m_pPP_HEAT_PLANT->getHEATID_CUST_PLAN(1);
                  CustTreatID             = m_pPP_HEAT_PLANT->getTREATID_CUST_PLAN(1);
                  log ("#### Found in PP_HEAT_PLANT Scrap Order : "+ ActOrderId + " Cust Heat "+CustHeatID,3);

                  // select material data from  entry table for all recipes
                  if ( m_pPD_SCRAP_CONTAINER_ORDER_ENTRY && 
                    m_pPD_SCRAP_CONTAINER_ORDER_ENTRY->selectByMatChargeSeq(Plant, ActOrderId, CONTAINERINSEQ, CSMC_DBData::unspecString, CSMC_DBData::unspecString) )
                  {
                    log ("#### Found in m_pPD_SCRAP_CONTAINER_ORDER_ENTRY Scrap Order : "+ ActOrderId ,3);

                    for ( long j = 1 ; j <= m_pPD_SCRAP_CONTAINER_ORDER_ENTRY->getLastRow(); ++j )
                    {
                      if ( j > 10 ) // max no of materials is limited to 10 by telegram
                      {
                        break;
                      }

                      CIntfData::setAt( SeqMatCode,     m_pPD_SCRAP_CONTAINER_ORDER_ENTRY->getMAT_CODE(j).c_str()   , j-1 );
                      CIntfData::setAt( SeqMatWeight,   (long)m_pPD_SCRAP_CONTAINER_ORDER_ENTRY->getMATWEIGHT(j)    , j-1 );
                      CIntfData::setAt( SeqMatLoadSeq,  m_pPD_SCRAP_CONTAINER_ORDER_ENTRY->getMATCHARGESEQ(j)       , j-1 );
                    }
                  } 
                } // if ( m_pPP_HEAT_PLANT && m_pPP_HEAT_PLANT->selectByData(m_pPP_HEAT->getHEATID(1), CSMC_DBData::unspecString, Plant, false) )
                //else
                //{
                //  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                //  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                //  pEventLog->EL_DBReadError(sMessage,"PLANT,PLANTNO...,","PP_HEAT_PLANT","" );
                //}

                // truncate string data to fit telegram length
                ActOrderId   = CDataConversion::CheckLengthAndTruncate(ActOrderId,10);

                // truncate string data to fit telegram length
                CustHeatID    = CDataConversion::CheckLengthAndTruncate(CustHeatID,10);
                CustTreatID   = CDataConversion::CheckLengthAndTruncate(CustTreatID,2);

                Telegram_L2SY92_SCRAP_LOAD::t_ENTRY seqENTRY;

                for(long j = 0; j < MatSeqLenght ; j++)
                {
                  Telegram_L2SY92_SCRAP_LOAD::sENTRY ENTRY;
          
                  ENTRY.MessageIndex                = j;
                  ENTRY.HeatIdCust                  = CustHeatID.c_str()         ;
                  ENTRY.TreatIdCust                 = CustTreatID.c_str()        ;
                  ENTRY.ProdOrderId                 = ActOrderId.c_str()            ;

                  ENTRY.ContainerSeqNo              = CONTAINERINSEQ;
                  ENTRY.TotalNoOfContainers         = TotalNoOfContainers;
                  ENTRY.ContainerType               = CONTAINERTYPE; 

                  CIntfData::getAt(ENTRY.MatCode,     SeqMatCode    , j);
                  CIntfData::getAt(ENTRY.MatWeight,   SeqMatWeight  , j);
                  CIntfData::getAt(ENTRY.MatLoadSeq,  SeqMatLoadSeq , j);

                  ENTRY.Spare_1                     = 0 ;
                  ENTRY.Spare_2                     = 0 ;

                  CIntfData::insert(seqENTRY,ENTRY);
                  //********    Dispatch event ****** *****************************************************************
                }

                CORBA::Any seqAny;
                seqAny = CIntfData::ToAny(seqENTRY);

                //set the data to telcom interface
                pTelcom_Interface->setLong     ( DataKeyL1, Telegram_L2SY92_SCRAP_LOAD::UnitNo,               UnitNo);
                pTelcom_Interface->setString   ( DataKeyL1, Telegram_L2SY92_SCRAP_LOAD::CreateTime,           Now.toDBString());   
                pTelcom_Interface->setString   ( DataKeyL1, Telegram_L2SY92_SCRAP_LOAD::HeatIdCust,           CustHeatID);
                pTelcom_Interface->setString   ( DataKeyL1, Telegram_L2SY92_SCRAP_LOAD::TreatIdCust,          CustTreatID);
                pTelcom_Interface->setString   ( DataKeyL1, Telegram_L2SY92_SCRAP_LOAD::ProdOrderId,          ActOrderId);
                pTelcom_Interface->setLong     ( DataKeyL1, Telegram_L2SY92_SCRAP_LOAD::ContainerSeqNo,       CONTAINERINSEQ);
                pTelcom_Interface->setLong     ( DataKeyL1, Telegram_L2SY92_SCRAP_LOAD::TotalNoOfContainers,  TotalNoOfContainers);
                pTelcom_Interface->setLong     ( DataKeyL1, Telegram_L2SY92_SCRAP_LOAD::ContainerType,        CONTAINERTYPE);

                pTelcom_Interface->setAny      ( DataKeyL1, Telegram_L2SY92_SCRAP_LOAD::ENTRY,                seqAny);

                pTelcom_Interface->showContent(DataKeyL1, 4);

                //********    Dispatch event ***********************************************************************
                //            multiple telegrams send if model results contains more materials than defined in telegram sequence! 
                log ("#### Send to L1 Scrap Order : "+ ActOrderId+ " HeadIdCust: "+ CustHeatID ,3);

                SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,ActOrderId);
              }

              CSMC_EventLogEAF *pEventLog = CSMC_EventLogEAFController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);

              if ( TotalNoOfContainers > 0 )
              {
                pEventLog->EL_HandleScrapOrder(sMessage, ActOrderId.c_str(), CONTAINERINSEQ, ContainerType.c_str());
              }
              else
              {
                pEventLog->EL_ScrapContainerAssignmentError(sMessage, -1, -1);
                RetValue = false;
              }
            }
          }// if ( m_pPD_SCRAP_CONTAINER_ORDER && m_pPD_SCRAP_CONTAINER_ORDER->selectByContainerState(Plant, ActOrderId, DEF_GC_SCRAP_CONT_ORDER_STATUS::Planned) )
          else
          {
            log("READING DATA FROM PD_SCRAP_CONTAINER_ORDER FAILED/NOT PLANNED", 1);     
          }
        } // if ( ActOrderId != CSMC_DBData::unspecString )
      } // for ( it = OrderIdList.begin(); it != OrderIdList.end(); ++it )
      //********    End processing data  ***********************************************************************
    }// if ( pDM_Interface && pTelcom_Interface )
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorPointerHandling(sMessage,Function.c_str()," pDM_Interface or pTelcom_Interface invalid ");
      RetValue=false;
    }

    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  log( TlgName + ": End", 3);

  return RetValue;

}
bool  CEAF_EventHandler::provideData_L2SY95_SCRAP_MAT(CEventMessage& Event)
{
  //=================   Availability of S C R A P    Materials   ===============================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();

  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID);
  long 				PlantNo   = m_pGC_Plant_Container->getPlantNo(PlantID);
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  long 				UnitNo    = m_pGC_Plant_Container->getPlantNo(PlantID);


  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2SY95_SCRAP_MAT";
  std::string Function = "CEAF_EventHandler::provideData_L2SY95_SCRAP_MATERIAL_REQUEST";

  log("****************************************************************************************", 3);
  log( TlgName + ": Start", 3);
  log("****************************************************************************************", 3);

  try
  {
    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    if ( pTelcom_Interface )
    {
      //********    preset data  ************************************************************************

      //********    Read event related data  ************************************************************************


      //********    Log event data ***********************************************************************

      //********    Convert and check event data  ***********************************************************

      CustHeatID     = "";
      CustTreatID    = "";

      DEF::seqString    SeqMatCode;
      DEF::seqString    SeqMatDesc;

      long MatSeqLength   = 20;
      std::string MatCode;

      CIntfData::preset(seqSpare,0,5);

      CIntfData::preset(SeqMatCode         ,"" ,MatSeqLength);
      CIntfData::preset(SeqMatDesc         ,"" ,MatSeqLength);

      // select scrap materials from  gt_mat_purp table 
      if ( m_pGT_MAT_PURP && m_pGT_MAT_PURP->selectAllMaterialsBySpecPurpose(DEF_GT_PURP::Scrap))
      {
           for ( long i = 1 ; i <= m_pGT_MAT_PURP->getLastRow(); ++i )
           {
              if ( i > MatSeqLength ) // max no of materials is limited to MatSeqLenght by telegram
              {
                 break;
              }
              CIntfData::setAt( SeqMatCode,     m_pGT_MAT_PURP->getMAT_CODE(i).c_str()     , i-1 );
              MatCode =  m_pGT_MAT_PURP->getMAT_CODE(i).c_str();
              if ( m_pGT_MAT && m_pGT_MAT->select(MatCode) )
              {
                 CIntfData::setAt( SeqMatDesc, m_pGT_MAT->getDESCRIPTION(1).c_str()     , i-1 );
              }
            }
      } 
      DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);
      Telegram_L2SY95_SCRAP_MAT::t_ENTRY seqENTRY;

      for(long j = 0; j < MatSeqLength ; j++)
      {
           Telegram_L2SY95_SCRAP_MAT::sENTRY ENTRY;
           ENTRY.MessageIndex                = j;
           CIntfData::getAt(ENTRY.MatCode,   SeqMatCode    , j);
           CIntfData::getAt(ENTRY.MatDescr,  SeqMatDesc  , j);
           ENTRY.Spare_1  = 0 ; ENTRY.Spare_2 = 0 ; ENTRY.Spare_3 = 0 ; ENTRY.Spare_4  = 0 ; ENTRY.Spare_5  = 0 ;
           CIntfData::insert(seqENTRY,ENTRY);
      }

      CORBA::Any seqAny;
      seqAny = CIntfData::ToAny(seqENTRY);

      //set the data to telcom interface
      pTelcom_Interface->setLong     ( DataKeyL1, Telegram_L2SY95_SCRAP_MAT::UnitNo,               UnitNo);
      pTelcom_Interface->setString   ( DataKeyL1, Telegram_L2SY95_SCRAP_MAT::CreateTime,           Now.toDBString());   
      pTelcom_Interface->setAny      ( DataKeyL1, Telegram_L2SY95_SCRAP_MAT::ENTRY,                seqAny);

      pTelcom_Interface->showContent(DataKeyL1, 4);

      //********    Dispatch event ***********************************************************************
      //            multiple telegrams send if model results contains more materials than defined in telegram sequence! 
      SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorPointerHandling(sMessage,Function.c_str()," pDM_Interface or pTelcom_Interface invalid ");
      RetValue=false;
    }

    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  log( TlgName + ": End", 3);

  return RetValue;

}
bool  CEAF_EventHandler::provideData_L2SY95ScrapMat(CEventMessage& Event)
{
  //=================   Availability of S C R A P    Materials   ===============================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();

  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID);
  long 				PlantNo   = m_pGC_Plant_Container->getPlantNo(PlantID);
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  long 				UnitNo    = m_pGC_Plant_Container->getPlantNo(PlantID);


  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2SY95";
  std::string Function = "CEAF_EventHandler::provideData_L2SY95_SCRAP_MATERIAL_REQUEST";

  log("****************************************************************************************", 3);
  log( TlgName + ": Start", 3);
  log("****************************************************************************************", 3);

  try
  {
    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    if ( pTelcom_Interface )
    {
      //********    preset data  ************************************************************************

      //********    Read event related data  ************************************************************************


      //********    Log event data ***********************************************************************

      //********    Convert and check event data  ***********************************************************

      CustHeatID     = "";
      CustTreatID    = "";

      DEF::seqString    SeqMatCode;
      DEF::seqString    SeqMatDesc;

      long MatSeqLenght   = 20;
      std::string MatCode;

      CIntfData::preset(seqSpare,0,5);

      CIntfData::preset(SeqMatCode         ,"" ,MatSeqLenght);
      CIntfData::preset(SeqMatDesc         ,"" ,MatSeqLenght);

      // select scrap materials from  gt_mat_purp table 
      if ( m_pGT_MAT_PURP && m_pGT_MAT_PURP->selectAllMaterialsBySpecPurpose(DEF_GT_PURP::Scrap))
      {
           for ( long i = 1 ; i <= m_pGT_MAT_PURP->getLastRow(); ++i )
           {
              if ( i > MatSeqLenght ) // max no of materials is limited to MatSeqLenght by telegram
              {
                 break;
              }
              CIntfData::setAt( SeqMatCode,     m_pGT_MAT_PURP->getMAT_CODE(i).c_str()     , i-1 );
              MatCode =  m_pGT_MAT_PURP->getMAT_CODE(i).c_str();
              if ( m_pGT_MAT && m_pGT_MAT->select(MatCode) )
              {
                 CIntfData::setAt( SeqMatDesc, m_pGT_MAT->getDESCRIPTION(1).c_str()     , i-1 );
              }
            }
      } 
       DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

       //********    Dispatch event ****** *****************************************************************
       pTelcom_Interface->setAny    ( DataKeyL1, Telegram_L2SY95::CreateTime, Now.asCORBAAny());   
       pTelcom_Interface->setAny    ( DataKeyL1, Telegram_L2SY95::MatCode,    CIntfData::ToAny(SeqMatCode));
       pTelcom_Interface->setAny    ( DataKeyL1, Telegram_L2SY95::MatDescr,   CIntfData::ToAny(SeqMatDesc));
       pTelcom_Interface->setAny    ( DataKeyL1, Telegram_L2SY95::Spare,      CIntfData::ToAny(seqSpare));
       SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorPointerHandling(sMessage,Function.c_str()," pDM_Interface or pTelcom_Interface invalid ");
      RetValue=false;
    }

    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  log( TlgName + ": End", 3);

  return RetValue;

}

long CEAF_EventHandler::GetProdPracNo(std::string &HeatID,std::string &TreatID,const std::string& Plant,const std::string& DESCR_PP )
{
  long row    = 0;
  long PracNo = CSMC_DBData::unspecLong;

  if( m_pPD_HEAT_DATA_PRODPRAC->select(HeatID,TreatID,Plant,DESCR_PP))
  {
    if((row = m_pPD_HEAT_DATA_PRODPRAC->getLastRow()) == 1)
    {
      if (!m_pPD_HEAT_DATA_PRODPRAC->isNull(CPD_HEAT_DATA_PRODPRAC::PRODPRACID_MOD, row))
      {
        PracNo = m_pPD_HEAT_DATA_PRODPRAC->getPRODPRACID_MOD(row);
      }
      else if (!m_pPD_HEAT_DATA_PRODPRAC->isNull(CPD_HEAT_DATA_PRODPRAC::PRODPRACID_PLAN, row))
      {
        PracNo = m_pPD_HEAT_DATA_PRODPRAC->getPRODPRACID_PLAN(row);
      }
      else
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DBReadError(sMessage,"PRODPRACID_MOD/PRODPRACID_PLAN","PD_HEAT_DATA_PRODPRAC",std::string("Failed to find the Practice no for HeatID:" + HeatID +";DESCR_PP ="+DESCR_PP).c_str() );
      }
    }						
  }

  return PracNo;
}


long CEAF_EventHandler::GetL1PhaseType(std::string& PhaseName)
{
  long nPhaseTypeNo = 0;

  if(PhaseName.find(DEF_GC_PHASE::Preparation) != std::string::npos)
  {
    nPhaseTypeNo = 1; //preparation phase
  }
  if(PhaseName.find(DEF_GC_PHASE::MeltBskNo) != std::string::npos)
  {
    nPhaseTypeNo = 2; //First, mediate or Last Basket
  }
  else if(PhaseName.find(DEF_GC_PHASE::HeatLiqChgNo) != std::string::npos)
  {
    nPhaseTypeNo = 3; //Liquid
  }
  else if(PhaseName.find(DEF_GC_PHASE::BskAndLiqChgNo) != std::string::npos)
  {
    nPhaseTypeNo = 4; //Basket+Liquid
  }
  else if(PhaseName.find(DEF_GC_PHASE::Refining) != std::string::npos)
  {
    nPhaseTypeNo = 10; //Refining
  }
  else if(PhaseName.find(DEF_GC_PHASE::Actual) != std::string::npos ||
    //PhaseName.find(DEF_GC_PHASE::Preparation) != std::string::npos ||
    PhaseName.find(DEF_GC_PHASE::Tapping) != std::string::npos ||
    PhaseName.find(DEF_GC_PHASE::Tapped) != std::string::npos )
  {
    nPhaseTypeNo = 0; //Actual set point, no type, so set as 0
  }
  else if( PhaseName.find(DEF_GC_LIQADD_TYPE::HotHeel) != std::string::npos )
  {
    nPhaseTypeNo = CSMC_DBData::unspecLong;
  }
  else if( PhaseName.empty() )
  {
    nPhaseTypeNo = CSMC_DBData::unspecLong;
  }
  else
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBReadError(sMessage,"PHASENAME","DEF_GC_PHASE",std::string("Error: Failed to define the PhaseType for Phasename:" + PhaseName).c_str() );
  }
  return nPhaseTypeNo;
}

long CEAF_EventHandler::GetL1PhaseNo(std::string& PhaseName,std::string& Plant,long PhaseNo)
{
  long nL1PhaseNO = 0;
  if(m_pGC_PHASE->selectByPhase(Plant,PhaseName,PhaseNo,CSMC_DBData::unspecLong))
  {
    nL1PhaseNO = m_pGC_PHASE->getL1_PHASE_NO(1);
  }
	
  return nL1PhaseNO;
}

bool CEAF_EventHandler::provideData_L2EA20VoltageTap(CEventMessage& Event)
{
  //============   V O L T A G E   T A P   /   R E G    C U R V E      ============================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID); 
  long UnitNo           = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2EA20";
  std::string Function = "CLF_EventHandler::provideData_L2EA20VoltageTap";

  try
  {
    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();


    if ( pDM_Interface && pTelcom_Interface )
    {
      //********    preset data  ***********************************************************************
      
      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);


      DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

      CIntfData::preset(seqSpare,0,5);

      //********    Read event related data  ************************************************************************
      long AimVoltTap = pDM_Interface->getLong(ProductID.c_str(), DATA::VoltTapNoAim);
      long AimCurveNo = pDM_Interface->getLong(ProductID.c_str(), DATA::ElectrodRegCurveAim);
			long AimReactTapNo = pDM_Interface->getLong(ProductID.c_str(), DATA::ReactTapNoAim);

			CIntfData::setAt(seqSpare,AimReactTapNo,0);

      /*if (AimVoltTap != AimVoltTapPrev || AimCurveNo != AimCurveNoPrev)
      {
        ElPatternChanged = true;
        AimVoltTapPrev = AimVoltTap;
        AimCurveNoPrev = AimCurveNo;
      }
      else
        ElPatternChanged = false;*/

      //********    Log event data ***********************************************************************

      //********    Convert and check event data  ***********************************************************

      if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
      {
        // truncate string data to fit telegram length
        HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
        TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

        std::stringstream tmp_elec;
          tmp_elec << "******* Process data *********" << endl;

        //********    Write telegram data  ***********************************************************************

        pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF20::UnitNo,        UnitNo);
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF20::HeatId,        HeatID);
        tmp_elec << "HeatID : "   << HeatID << endl;
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF20::TreatId,       TreatID);
        pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF20::CreateTime,    Now.asCORBAAny());
        tmp_elec << "CreateTime : "   << Now.asString() << endl;

        pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF20::AimCurveNo,    AimCurveNo);
        tmp_elec << "AimCurveNo : "   << AimCurveNo << endl;
        pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF20::AimVoltTap,    AimVoltTap);
        tmp_elec << "AimVoltTap : "   << AimVoltTap << endl;

        pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF20::Spare,         CIntfData::ToAny(seqSpare));

        pTelcom_Interface->showContent(DataKeyL1, 4);

        CDH_OUT_Task::getInstance()->setStateDetails(TlgName, tmp_elec.str(),4);

        //********    Dispatch event ***********************************************************************

        SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);


        //********    End processing data  ***********************************************************************
      }
      else
      {
        RetValue = false;
      }

      log( TlgName + ": End", 3);

    }
    else
    {
      // EL_
      RetValue=false;
    }

    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;
}//end of L2EA20 VoltageTap/RegCurve 