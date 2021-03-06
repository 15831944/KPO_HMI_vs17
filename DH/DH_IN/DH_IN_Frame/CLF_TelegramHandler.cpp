// Copyright (C) 2012 SMS Siemag AG

#include "CSMC_EventLogLFController.h"

#include "DEF_GC_COMP_STATUS.h"
#include "DEF_GC_MEASUREMENT_TYPE.h"
#include "DEF_GC_LADLE_POS.h"
#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_LADLE_TYPE.h"
#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_SAMPLELOC.h"
#include "DEF_GC_SAMPLEMODE.h"
#include "DEF_GC_COOLWATER.h"
#include "DEF_GC_RECIPE_SOURCE.h"
#include "DEF_GT_PURP.h"
#include "DEF_GC_STIRR_DEVICE.h"
#include "DEF_GC_STIRR_GAS_TYPE.h"
#include "DEF_GCL_STIRR_INT.h"
#include "DEF_GC_RECIPE_STATUS.h"
#include "DEF_GC_CHARGE_DEST.h"
#include "DEF_GC_PARAM_TYPE.h"


#include "CLadleID.h"
#include "CSMC_RecipeHandler.h"

#include "CLF_TelegramHandler.h"

CLF_TelegramHandler::CLF_TelegramHandler()
:m_pPP_HEAT_PLANT (0),
m_pGT_MAT_PURP(0),
m_pGT_PARAM(0),
m_pGCL_STIRR_INT(0),
m_pPP_ORDER(0),
m_pPP_HEAT(0),
m_pPD_MAT_AVAIL(0)

{
  std::stringstream strFunction;
  std::stringstream strAction;

  strFunction << " In CLF_TelegramHandler::CLF_TelegramHandler()";

  try
  {  	  
    cCBS_StdConnection *pConnection = CDH_IN_Task::getInstance()->getStdConnection();

    strAction << "CDH_IN_Task::getInstance()->getConnection() ";

    if(pConnection)
    {
      strAction << "Success get database connection ";

      long PlantNo  = 1;
      std::string Plant = DEF_GC_PLANT_DEF::LF;

      cCBS_StdInitBase::getInstance()->replaceWithEntry("PLANT", "PlantNo", PlantNo);
      cCBS_StdInitBase::getInstance()->replaceWithEntry("PLANT", "Plant"  , Plant);
      // GENERAL
      m_pGC_Plant_Container       = new CGC_Plant_Container       (pConnection, Plant);
      m_pHeatDataConverter        = new CHeatDataConverter        (pConnection);

      m_pGC_Recipe_L1Container    = new CGC_Recipe_L1Container(pConnection,Plant); 
      m_pGC_SourceContainer       = new CGC_SourceContainer(pConnection,Plant,PlantNo);
      m_pGC_Charge_Dest_Container = new CGC_Charge_Dest_Container(pConnection,Plant);
      m_pGC_Plantgroup_Container  = new CGC_Plantgroup_Container(pConnection);

      // SPECIFIC
      m_pGT_MAT_PURP         = new CGT_MAT_PURP              (pConnection);
      m_pGT_PARAM            = new CGT_PARAM                 (pConnection);
      m_pGCL_STIRR_INT       = new CGCL_STIRR_INT            (pConnection);

      m_pPD_MAT_AVAIL        = new CPD_MAT_AVAIL             (pConnection);
      m_pPP_ORDER            = new CPP_ORDER                 (pConnection);
      m_pPP_HEAT             = new CPP_HEAT                  (pConnection);
      m_pPP_HEAT_PLANT       = new CPP_HEAT_PLANT            (pConnection);
			m_pPD_HEAT_DATA        = new CPD_HEAT_DATA(pConnection);

			m_pREPORT_MOTOR_ENTRY  = new CREPORT_MOTOR_ENTRY(pConnection);

      strAction << "create DB classes instance successful ";
    }
    else
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,"", "CLF_TelegramHandler","No database connection");

      // to guaranty EL_ExceptionCaught to be sent to CBS service
      Sleep(3000);

      // terminate programm in case of starting up without getting connection to database
      exit(EXIT_FAILURE);
    }

    log(strFunction.str() + " " + strAction.str(), 1);

  }
  catch(...) 
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"Unknown Exception", "CLF_TelegramHandler","");
    throw;
  }
}

CLF_TelegramHandler::~CLF_TelegramHandler()
{
  if (m_pGC_Plant_Container)  {delete m_pGC_Plant_Container; m_pGC_Plant_Container = 0;}
  if (m_pHeatDataConverter) {delete m_pHeatDataConverter; m_pHeatDataConverter = 0;}

  if (m_pGC_Charge_Dest_Container) {delete m_pGC_Charge_Dest_Container; m_pGC_Charge_Dest_Container = 0;}
  if (m_pGC_SourceContainer)       {delete m_pGC_SourceContainer; m_pGC_SourceContainer = 0;} 
  if (m_pGC_Recipe_L1Container)    {delete m_pGC_Recipe_L1Container; m_pGC_Recipe_L1Container = 0;}

  if (m_pGCL_STIRR_INT) {delete m_pGCL_STIRR_INT; m_pGCL_STIRR_INT = 0;}    
  if (m_pGT_PARAM)      {delete m_pGT_PARAM;  m_pGT_PARAM = 0;  }
  if (m_pGT_MAT_PURP)   {delete m_pGT_MAT_PURP;  m_pGT_MAT_PURP = 0;  }

  if (m_pPD_MAT_AVAIL)  {delete m_pPD_MAT_AVAIL; m_pPD_MAT_AVAIL = 0;}
  if (m_pPP_ORDER)      {delete m_pPP_ORDER; m_pPP_ORDER = 0;}
  if (m_pPP_HEAT)       {delete m_pPP_HEAT; m_pPP_HEAT = 0;}
  if (m_pPP_HEAT_PLANT) {delete m_pPP_HEAT_PLANT; m_pPP_HEAT_PLANT = 0;}
  if (m_pPD_HEAT_DATA)              {delete m_pPD_HEAT_DATA;              m_pPD_HEAT_DATA = 0;}

  if (m_pREPORT_MOTOR_ENTRY) {delete m_pREPORT_MOTOR_ENTRY; m_pREPORT_MOTOR_ENTRY = 0;}
	
}

bool CLF_TelegramHandler::doOnComplete(const std::string& Key, const std::string& TlgName)
{
  //message list used to store the dispatch message
  bool RetValue = true;
  std::stringstream strFunction;
  std::stringstream strAction;
  try
  {
    //doOnCompleteDelete(Key,TlgName);

    strFunction << "CLF_TelegramHandler::doOnComplete;";
    strFunction <<" TlgName: " << TlgName;

    EventMessageVector.clear();

    if(TlgName == "LFL201")
      RetValue =  DoProcessLFL201WatchDog(Key,TlgName); 
    else if(TlgName == "LFL203")
      RetValue =  DoProcessLFL203HeatAnnouncement(Key,TlgName); 
    else if(TlgName == "LFL204")
      RetValue =  DoProcessLFL204HeatStart(Key,TlgName); 
    else if(TlgName == "LFL205")
      RetValue =  DoProcessLFL205HeatEnd(Key,TlgName); 
    else if(TlgName == "LFL206")
      RetValue =  DoProcessLFL206HeatCancel(Key,TlgName); 
    else if(TlgName == "LFL209")
      RetValue =  DoProcessLFL209SampTaken(Key,TlgName); 
    else if(TlgName == "LFL211")
      RetValue =  DoProcessLFL211TempTaken(Key,TlgName);
    else if(TlgName == "LFL212")
      RetValue =  DoProcessLFL212AimTemperature(Key,TlgName);
    else if(TlgName == "LFL213")
      RetValue =  DoProcessLFL213AimDepartureTime(Key,TlgName);
	
		//else if(TlgName == "LFL217")
    //  RetValue =  DoProcessLFL217DelayStatus(Key,TlgName); //saikat  //SARS becuae L1 can not send delay end time
    
		else if(TlgName == "LFL220")
      RetValue =  DoProcessLFL220CompMode(Key,TlgName); 
    else if(TlgName == "LFL221")
      RetValue =  DoProcessLFL221FurnStatus(Key,TlgName); 
    else if(TlgName == "LFL222")
      RetValue =  DoProcessLFL222ElecStatus(Key,TlgName); 
    else if(TlgName == "LFL223")
      RetValue =  DoProcessLFL223ElecActVal(Key,TlgName);
    else if(TlgName == "LFL224")
      RetValue =  DoProcessLFL224BottomStirringStatus(Key,TlgName);
    else if(TlgName == "LFL225")
      RetValue =  DoProcessLFL225EmergencyLanceStirringStatus(Key,TlgName);
    else if(TlgName == "LFL226")
      RetValue =  DoProcessLFL226ActualStirringValues(Key,TlgName);
    else if(TlgName == "LFL230")
      RetValue =  DoProcessLFL230CoolingWater(Key,TlgName);  
    else if(TlgName == "LFL240")
      RetValue =  DoProcessLFL240Level1lParam(Key,TlgName); 
    else if(TlgName == "LFL260")
      RetValue =  DoProcessLFL260MatHandReport(Key,TlgName); 
    else if(TlgName == "LFL261")
      RetValue =  DoProcessLFL261MatAvailibilty(Key,TlgName); 
    else if(TlgName == "LFL270")
      RetValue =  DoProcessLFL270LiqMatReport(Key,TlgName);
    else if(TlgName == "LFL281")
      RetValue =  DoProcessLFL281TreamentSteps(Key,TlgName);
    //else if(TlgName == "LFL290") //motor maintenance as per JSW requirement
    //  RetValue =  DoProcessMotorMaintenance(Key,TlgName); 		

    else 
    {
      strFunction << " is unknown";

      RetValue = false;
    }

    if( RetValue == false )
    {
      log( "ERROR: Can not handle telegram " + TlgName ,1 );
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
    }

    strAction << "Invoke telegram handler for telegram :";
    strAction<< TlgName;
  }
  catch(...)
  {
    RetValue = false;

    m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      strFunction.str().c_str(),strAction.str().c_str());   
  }

  if( RetValue == false )
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),strFunction.str().c_str());
  }

  return RetValue;
}

void CLF_TelegramHandler::SendEventMessage(const std::string& Key, 
                                            const std::string& TlgName,
                                            const std::string& DataKey,
                                            const std::string& PlantId,
                                            const std::string& PlantLocation,
                                            const std::string& HeatId,
                                            const std::string& TreatId,
                                            const std::string& OrderID,
                                            bool isPlantEvent)
{
  //Send all event messages, that are present in EventMessageVector
  std::stringstream strFunction;
  std::stringstream strAction;

  std::vector <std::string>::iterator EventMsgToSend;

  try
  {
    strFunction << "CLF_TelegramHandler::SendEventMessage";
    for ( EventMsgToSend = EventMessageVector.begin(); EventMsgToSend != EventMessageVector.end();++EventMsgToSend)
    {
      string LogMessage = TlgName + " Data handled!";
      log(LogMessage,3);
      // sending event to event channel 
      CEventMessage Message(m_pTelegram_Adapter->m_SenderName,
        m_pTelegram_Adapter->m_DestinationName,
        *EventMsgToSend,
        PlantId,
        PlantLocation,
        "",
        "",
        isPlantEvent,
        HeatId,
        TreatId,
        DataKey);

      if ( OrderID != CSMC_DBData::unspecString )
      {
        Message.setOrderID(OrderID);
      }

      strAction << "sending event:" << TlgName;

      if( !m_EventHandler.dispatchEvent("","",Message) )
      {
        log(" Send Message" + Message.getDataKey() + "failed",2);
      }

			//sankar as per JSW requirement
			handleEventLog(*EventMsgToSend,HeatId,TreatId,PlantId,DataKey);

    }
  }
  catch (cCBS_DBExc &e)
  {
    m_pTelegram_Adapter->m_pIntf_IN->showContent(TlgName,1);
    m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,1);
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), strFunction.str().c_str(), strAction.str().c_str()); 
  }
  catch(CORBA::SystemException& sExc) 
  {
    m_pTelegram_Adapter->m_pIntf_IN->showContent(TlgName,1);
    m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,1);
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(), strFunction.str().c_str(), strAction.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
    m_pTelegram_Adapter->m_pIntf_IN->showContent(TlgName,1);
    m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,1);
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(), strFunction.str().c_str(), strAction.str().c_str());
  }
  catch(...)
  {
    m_pTelegram_Adapter->m_pIntf_IN->showContent(TlgName,1);
    m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,1);
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", strFunction.str().c_str(),strAction.str().c_str()); 
  }
}

bool CLF_TelegramHandler::DoProcessLFL201WatchDog(const std::string& Key, const std::string& TlgName)
{
  //=======================     Watch Dog   ============================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CLF_TelegramHandler::DoProcess" + TlgName;

  try
  {
    if ( m_pTelegram_Adapter && 
      m_pTelegram_Adapter->m_pIntf_IN && 
      m_pTelegram_Adapter->m_pIntf_OUT )
    {

      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      //Read the m_PlantID and generate the string. m_PlantID is defined in all telegrams
      UnitNo = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL201::UnitNo);

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo); 

      //********    Convert and check telegram data  ***********************************************************

      //********    Write telegram data  ***********************************************************************

      //// setting data to output interface
      //m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey,Telegram_LFL201::CPU0_Active,CPU0);
      //m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey,Telegram_LFL201::CPU1_Active,CPU1);

      //********    End processing data  ***********************************************************************

      log (TlgName + ": Finished", 3);
    }// // if ( m_pTelegram_Adapter &&
    else
    {
      RetValue = false;
    }
  }
  catch (cCBS_DBExc &e)
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Function.c_str(), TlgName.c_str()); 
  }
  catch(CORBA::Exception& cExc) 
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      Function.c_str(), TlgName.c_str());
  }
  catch(...)
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str() ,TlgName.c_str());
    RetValue = false;
  }

  return RetValue;
}// bool CLF_TelegramHandler::DoProcessLFL201WatchDog(const std::string& Key, const std::string& TlgName)

bool CLF_TelegramHandler::DoProcessLFL203HeatAnnouncement(const std::string& Key, const std::string& TlgName)
{
  //=====================  L F   H E A T   A N N O U N C E M E N T  ========================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CLF_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo       = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL203::UnitNo);
      CustHeatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL203::HeatId );
      CustTreatId  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL203::TreatId);

      LadleId      = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL203::LadleId);
      long CarNo   = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL203::CarNo);

      std::string OrderId         = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL203::ProdOrderId);
      std::string SteelGradeCode  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL203::SteelGradeCode);
      double AimTemp                = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LFL203::AimTemp);
      double AimWeight              = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LFL203::AimWeight);

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      OrderId         = CDataConversion::Trim(OrderId);
      SteelGradeCode  = CDataConversion::Trim(SteelGradeCode);

      //********    reset statushandler  ***********************************************************************

      m_StatusHandler.removeID( PlantId+CDataConversion::LongToString(CarNo) );

      //********    Convert and check telegram data  ***********************************************************  

      // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
      UnitNo  = CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);
      CarNo   = CDataConversion::SetInvalidToDefault(CarNo,DEF::Inv_Long,LONG_MIN);  

      checkValidity(TlgName,"UnitNo"  ,UnitNo ,1,2);
      checkValidity(TlgName,"CarNo"   ,CarNo  ,1,2); 

      std::string Message = TlgName;

      if ( m_pPP_HEAT_PLANT->selectByCustData(CustHeatId,CustTreatId,Plant,false) )
      {
        HeatId  = m_pPP_HEAT_PLANT->getHEATID(1);
        TreatId = m_pPP_HEAT_PLANT->getTREATID(1);

        if ( OrderId == DEF::Inv_String || OrderId.empty() )
        {
          if ( m_pPP_HEAT->select(HeatId) )
          {
            OrderId = m_pPP_HEAT->getPRODORDERID(1);

            if ( OrderId != CSMC_DBData::unspecString && m_pPP_ORDER->select(OrderId) )
            {
              SteelGradeCode = m_pPP_ORDER->getSTEELGRADECODE(1);
            }
          }
        }

        Message += ": get planning data";

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DBReadInfo(sMessage, "HEATID - TREATID","PP_HEAT_PLANT",Message.c_str());
      }
      else
      {
        Message += ": Heat is not planned";

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DBReadWarning(sMessage, "HeatID - TreatID","PP_HEAT_PLANT",Message.c_str());
      }

      if ( RetValue )
      {
        DataKey   = generateDataKey(HeatId);

        std::string LadleTransferCarId = CDataConversion::LongToString(CarNo);

        LadleId            = CDataConversion::Trim(LadleId);

        CLadleID LadleID;

        if ( LadleID.checkLadleIDWithDefaultType(DEF_GC_LADLE_TYPE::TeemingLadle, LadleId) )
        {
          LadleType          = LadleID.getLadleType(LadleId);
          LadleNo            = LadleID.getLadleNo(LadleId);
        }

        //********    Define Event *******************************************************************************

        EventMessageVector.push_back(LF_EvMsg::evLFHeatAnnouncement);

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setDate  (DataKey.c_str(),DATA::DateTime,Now.assDate());
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::PlantID,PlantId);

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::LadleTransferCarId,LadleTransferCarId);

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::LadleType ,LadleType);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey,DATA::LadleNo   ,LadleNo);

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::CustHeatIdUser   ,CustHeatId);
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::CustTreatIdUser  ,CustTreatId);

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::CustHeatID   ,CustHeatId);
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::CustTreatID  ,CustTreatId);

        // tracker insert or update pp data
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::OrderIdUser    ,OrderId);
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::OrderId        ,OrderId);

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::SteelGradeCode ,SteelGradeCode);
        m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey, DATA::TempAim        ,AimTemp);
        m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey, DATA::AimWeight      ,AimWeight);

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey.c_str(), DATA::UserCode,      "L1");

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************
      }// if ( RetValue )
      else
      {
        RetValue = false;
      }

      log (TlgName + ": Finished", 3);
    }
    catch (cCBS_DBExc &e)
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::Exception& cExc) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
        Function.c_str(), TlgName.c_str());
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(),TlgName.c_str());
      RetValue = false;
    }
  }// // if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
}// bool CLF_TelegramHandler::DoProcessLFL203HeatAnnouncement(const std::string& Key, const std::string& TlgName)

bool CLF_TelegramHandler::DoProcessLFL204HeatStart(const std::string& Key, const std::string& TlgName)
{
  //=========================    H E A T    S T A R T    ===================================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CLF_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo      = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL204::UnitNo);
      HeatId      = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL204::HeatId);
      TreatId     = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL204::TreatId);
      LadleId     = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL204::LadleId);
      long CarNo  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL204::CarNo);

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler  ***********************************************************************

      m_StatusHandler.removeID( PlantId+CDataConversion::LongToString(CarNo) );

      m_StatusHandler.isStatusChanged(PlantId, DEF_DEVICES::FurnaceBreaker   , DEF_GEN_STATES::Undefined);
      m_StatusHandler.isStatusChanged(PlantId, DEF_DEVICES::FurnacePowerOn   , DEF_GEN_STATES::Undefined);
      m_StatusHandler.isStatusChanged(PlantId, DEF_DEVICES::TapChanger       , DEF_GEN_STATES::Undefined);
      m_StatusHandler.isStatusChanged(PlantId, DEF_DEVICES::ImpCurve         , DEF_GEN_STATES::Undefined);
      m_StatusHandler.isStatusChanged(PlantId, DEF_DEVICES::Electrodes       , DEF_GEN_STATES::Undefined);
      m_StatusHandler.isStatusChanged(PlantId, DEF_DEVICES::ElectrodeInhibit , DEF_GEN_STATES::Undefined);

      //********    Convert and check telegram data  ***********************************************************  

      // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
      UnitNo  = CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);
      CarNo   = CDataConversion::SetInvalidToDefault(CarNo,DEF::Inv_Long,LONG_MIN);  

      checkValidity(TlgName,"UnitNo"  ,UnitNo ,1,2);
      checkValidity(TlgName,"CarNo"   ,CarNo  ,1,2);

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        DataKey   = generateDataKey(HeatId);

        std::string LadleTransferCarId = CDataConversion::LongToString(CarNo);

        LadleId            = CDataConversion::Trim(LadleId);

        CLadleID LadleID;

        if ( LadleID.checkLadleIDWithDefaultType(DEF_GC_LADLE_TYPE::TeemingLadle, LadleId) )
        {
          LadleType          = LadleID.getLadleType(LadleId);
          LadleNo            = LadleID.getLadleNo(LadleId);
        }

        //********    Define Event *******************************************************************************

        EventMessageVector.push_back(LF_EvMsg::evLFHeatStart);

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),DATA::DateTime,Now.assDate());
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::PlantID,PlantId);

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::LadleTransferCarId, LadleTransferCarId);
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::LadleType, LadleType);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::LadleNo, LadleNo);

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************
      }// if ( RetValue )
      else
      {
        RetValue = false;
      }

      log (TlgName + ": Finished", 3);
    }
    catch (cCBS_DBExc &e)
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::Exception& cExc) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
        Function.c_str(), TlgName.c_str());
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(),TlgName.c_str());
      RetValue = false;
    }
  }// // if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
}// bool CLF_TelegramHandler::DoProcessLFL204HeatStart(const std::string& Key, const std::string& TlgName)

bool CLF_TelegramHandler::DoProcessLFL205HeatEnd(const std::string& Key, const std::string& TlgName)
{
  //=======================  H E A T    E N D / H E A T   D E P A R T U R E  ==============================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CLF_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo      = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL205::UnitNo);
      HeatId      = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL205::HeatId);
      TreatId     = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL205::TreatId);
      LadleId     = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL205::LadleId);
      long CarNo  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL205::CarNo);

      long ActionFlag  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL205::ActionFlag);

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler  ***********************************************************************

      //********    Convert and check telegram data  ***********************************************************  

      // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
      UnitNo      = CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);
      CarNo       = CDataConversion::SetInvalidToDefault(CarNo,DEF::Inv_Long,LONG_MIN);  
      ActionFlag  = CDataConversion::SetInvalidToDefault(ActionFlag,DEF::Inv_Long,LONG_MIN);

      checkValidity(TlgName,"UnitNo"    ,UnitNo     ,1,2);
      checkValidity(TlgName,"CarNo"     ,CarNo      ,1,2);
      checkValidity(TlgName,"ActionFlag",ActionFlag ,1,2);

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        DataKey   = generateDataKey(HeatId);

        std::string LadleTransferCarId = CDataConversion::LongToString(CarNo);

        LadleId            = CDataConversion::Trim(LadleId);

        CLadleID LadleID;

        if ( LadleID.checkLadleIDWithDefaultType(DEF_GC_LADLE_TYPE::TeemingLadle, LadleId) )
        {
          LadleType          = LadleID.getLadleType(LadleId);
          LadleNo            = LadleID.getLadleNo(LadleId);
        }

        //********    Define Event *******************************************************************************

        if   (ActionFlag == 1)
        {
          EventMessageVector.push_back(LF_EvMsg::evLFHeatEnd);



					//SARS - 11.03.2015
					EventMessageVector.push_back( LF_EvMsg::evLFHeatDeparture);
          // delete all status 
          m_StatusHandler.removeID( PlantId+CDataConversion::LongToString(CarNo) );
        }
        else if   (ActionFlag == 2)
        {

					//SARS - 11.03.2015
					if ( m_pPD_HEAT_DATA->select(HeatId,TreatId,DEF_GC_PLANT_DEF::LF) )
					{
						if( m_pPD_HEAT_DATA->getHEATDEPARTURE_ACT(1) != CSMC_DBData::unspecDate)
							return true;
					}
					EventMessageVector.push_back(LF_EvMsg::evLFHeatEnd);



          EventMessageVector.push_back( LF_EvMsg::evLFHeatDeparture);

          // delete all status 
          m_StatusHandler.removeID( PlantId+CDataConversion::LongToString(CarNo) );
        }
        else
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorProcessingData(sMessage, Function.c_str(),"LFL205 :: ActionFlag");
        }     

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),DATA::DateTime,Now.assDate());

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::PlantID,PlantId);

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::UserCode           ,"L1");
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::LadleTransferCarId,LadleTransferCarId);
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::LadleType,LadleType);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::LadleNo,LadleNo);

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************
      }// 
      else
      {
        RetValue = false;
      }

      log (TlgName + ": Finished", 3);
    }
    catch (cCBS_DBExc &e)
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::Exception& cExc) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
        Function.c_str(), TlgName.c_str());
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(),TlgName.c_str());
      RetValue = false;
    }
  }// if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
}// bool CLF_TelegramHandler::DoProcessDummy(const std::string& Key, const std::string& TlgName)

bool CLF_TelegramHandler::DoProcessLFL206HeatCancel(const std::string& Key, const std::string& TlgName)
{
  //=======================     L F   H E A T    C A N C E L    ============================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CLF_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo      = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL206::UnitNo);
      HeatId      = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL206::HeatId);
      TreatId     = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL206::TreatId);
      long CarNo  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL206::CarNo);

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler  ***********************************************************************

      //********    Convert and check telegram data  ***********************************************************  

      // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
      UnitNo  = CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);
      CarNo   = CDataConversion::SetInvalidToDefault(CarNo,DEF::Inv_Long,LONG_MIN);  

      checkValidity(TlgName,"UnitNo"  ,UnitNo ,1,2);
      checkValidity(TlgName,"CarNo"   ,CarNo  ,1,2);

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        DataKey   = generateDataKey(HeatId);

        std::string LadleTransferCarId = CDataConversion::LongToString(CarNo); 

        //********    Define Event *******************************************************************************

        EventMessageVector.push_back(LF_EvMsg::evLFHeatCancellation);

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),DATA::DateTime,Now.assDate());

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::PlantID,PlantId);
        m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey, DATA::LadleTransferCarId, LadleTransferCarId);

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey.c_str(),DATA::CustHeatIdUser   ,CustHeatId);
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey.c_str(),DATA::CustTreatIdUser  ,CustTreatId);

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************
      }// 
      else
      {
        RetValue = false;
      }

      log (TlgName + ": Finished", 3);
    }
    catch (cCBS_DBExc &e)
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::Exception& cExc) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
        Function.c_str(), TlgName.c_str());
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(),TlgName.c_str());
      RetValue = false;
    }
  }// if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
}// bool CLF_TelegramHandler::DoProcessLFL206HeatCancel(const std::string& Key, const std::string& TlgName)

bool CLF_TelegramHandler::DoProcessLFL209SampTaken(const std::string& Key, const std::string& TlgName)
{
  //==========================     S A M P L E   T A K E N    ==========================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CLF_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo   = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL209::UnitNo);
      HeatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL209::HeatId );
      TreatId  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL209::TreatId);

      long  CarNo       = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL209::CarNo);
      long SampleType   = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL209::SampleType);
      long SampleNo     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL209::SampleCounter);

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler  ***********************************************************************

      //********    Convert and check telegram data  ***********************************************************  

      // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
      UnitNo      = CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);
      CarNo       = CDataConversion::SetInvalidToDefault(CarNo,DEF::Inv_Long,LONG_MIN);  
      SampleNo    = CDataConversion::SetInvalidToDefault(SampleNo,DEF::Inv_Long,LONG_MIN);
      SampleType  = CDataConversion::SetInvalidToDefault(SampleType,DEF::Inv_Long,LONG_MIN);  

      checkValidity(TlgName,"UnitNo"        ,UnitNo     ,1,2);
      checkValidity(TlgName,"CarNo"         ,CarNo      ,1,2);
      checkValidity(TlgName,"SampleType"    ,SampleType ,2,3);
      checkValidity(TlgName,"SampleCounter" ,SampleNo   ,1,999999);

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        DataKey   = generateDataKey(HeatId); 

        std::string SampleLocation = DEF_GC_SAMPLELOC::LF;

        std::string LadleTransferCarId = CDataConversion::LongToString(CarNo);

        //********    Define Event *******************************************************************************

        if (SampleType == 2)
        {
          EventMessageVector.push_back( LF_EvMsg::evLFSteelSampleTaken);
        }
        else if (SampleType == 3)
        {
          EventMessageVector.push_back( LF_EvMsg::evLFSlagSampleTaken);
        }

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),DATA::DateTime,Now.assDate());

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::PlantID,PlantId);

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey.c_str(), DATA::SampleLocation,SampleLocation.c_str());
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::LadleTransferCarId,LadleTransferCarId);

        m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey,DATA::SampleNo,SampleNo);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey.c_str(),DATA::SampleMode,DEF_GC_SAMPLEMODE::automatic);

        m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey,DATA::SampleUsable,1);
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::ProcessStage,std::string(DEF_PROCESS_STAGE::InProcess));
        // model information m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::SampleId,SampleId);
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::UserCode, "L1");

        if ( SampleType == 2 )        //Steel
        {
          m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str() ,DATA::SteelSampleTime,Now.assDate ());
          m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey         ,DATA::SampleType,DEF_GC_MEASUREMENT_TYPE::Steel);
        }
        else if ( SampleType == 3 )   //Slag
        {
          m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str() ,DATA::SlagSampleTime,Now.assDate ());
          m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey         ,DATA::SampleType,DEF_GC_MEASUREMENT_TYPE::Slag);
        }

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************
      }// 
      else
      {
        RetValue = false;
      }

      log (TlgName + ": Finished", 3);
    }
    catch (cCBS_DBExc &e)
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::Exception& cExc) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
        Function.c_str(), TlgName.c_str());
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(),TlgName.c_str());
      RetValue = false;
    }
  }// if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
}// bool CLF_TelegramHandler::DoProcessLFL209SampTaken(const std::string& Key, const std::string& TlgName)

bool CLF_TelegramHandler::DoProcessLFL211TempTaken(const std::string& Key, const std::string& TlgName)
{
  //===================   T E M P   /   O 2    P P M    I S   T A K E N     ============================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CLF_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo      = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL211::UnitNo);
      HeatId      = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL211::HeatId );
      TreatId     = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL211::TreatId);
      long CarNo  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL211::CarNo);

      long MeasType  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL211::MeasType);
      long MeasNo    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL211::MeasNo);

      double Temp    = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_LFL211::Temp);
      double ConcO2  = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_LFL211::ConcO2);
      double ConcAl  = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_LFL211::ConcAl);
      double ConcC   = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_LFL211::ConcC);
      double ConcFeO = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_LFL211::ConcFeO);
      double ConcMnO = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_LFL211::ConcMnO);
      
      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler  ***********************************************************************

      //********    preparation telegram data   ****************************************************************

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        //********    Convert and check telegram data  *********************************************************  

        // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
        UnitNo    = CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);
        CarNo     = CDataConversion::SetInvalidToDefault(CarNo,DEF::Inv_Long,LONG_MIN);  
        MeasType  = CDataConversion::SetInvalidToDefault(MeasType,DEF::Inv_Long,LONG_MIN);
        MeasNo    = CDataConversion::SetInvalidToDefault(MeasNo,DEF::Inv_Long,LONG_MIN);

        checkValidity(TlgName,"UnitNo"  ,UnitNo   ,1,2);
        checkValidity(TlgName,"CarNo"   ,CarNo    ,1,2);
        checkValidity(TlgName,"MeasType",MeasType ,4,6); //sankar
        checkValidity(TlgName,"MeasNo"  ,MeasNo   ,1,99);

        checkValidityToDefault(TlgName,"Temp"     ,Temp     ,1000.,2000.    , 0.);
        checkValidityToDefault(TlgName,"ConcO2"   ,ConcO2   ,-1.   ,1000000. , 0.);
        checkValidityToDefault(TlgName,"ConcAl"   ,ConcAl   ,-1.   ,1000000. , 0.);
        checkValidityToDefault(TlgName,"ConcC"    ,ConcC    ,-1.   ,1000000. , 0.);
        checkValidityToDefault(TlgName,"ConcFeO"  ,ConcFeO  ,-1.   ,1000000. , 0.);
        checkValidityToDefault(TlgName,"ConcMnO"  ,ConcMnO  ,-1.   ,1000000. , 0.);

        //********    main telegram data   ***********************************************************************

        DataKey   = generateDataKey(HeatId);

        std::string LadleTransferCarId = CDataConversion::LongToString(CarNo);

        std::string SampleId = DEF::Inv_String;

        if ( MeasNo > 0 && MeasNo != DEF::Inv_Long )
        {
          SampleId = CDataConversion::LongToString(MeasNo);
        }

        //********    Define Event *******************************************************************************
        // MeasType information is unsave, check measured values

        std::string Message;

        if ( MeasType == 4 )  //Temp
        {
          if ( Temp > 0. )
          {
            EventMessageVector.push_back( LF_EvMsg::evLFTempMeasurement);
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey,DATA::SampleType    ,DEF_GC_MEASUREMENT_TYPE::Temp);

            m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey,DATA::MeasTemp    ,Temp);
          }
          else
          {
            std::string ProductID = HeatId + "_" + TreatId;
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",ProductID,CustHeatId);

            Message += "TEMP - for HeatID " + CustHeatId; 

            Message += " Temp ";
            pEventLog->EL_MeasurementRejected(sMessage, Message.c_str(), Temp);

            RetValue = false;
          }
        }// if ( MeasType == 4 )  //Temp
        else if ( MeasType == 5 )   //Celox
        {
          if ( (Temp > 0. && ( ConcAl > 0. || ConcO2 > 0. || ConcC  > 0.)) )                                                                 
          {
            EventMessageVector.push_back( LF_EvMsg::evLFCeloxMeasurement);
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey,DATA::SampleType       ,DEF_GC_MEASUREMENT_TYPE::Celox);

            if ( Temp > 0. )
            {
              m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey,DATA::MeasTemp      ,Temp);
            }
            if ( ConcAl > 0. )
            {
              m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey,DATA::MeasAlConc    ,double(ConcAl/10000.));  // ppm -> %
            }
            if ( ConcO2 > 0. )
            {
              m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey,DATA::MeasO2Conc    ,double(ConcO2/10000.));  // ppm -> %
            }
            if ( ConcC > 0. )
            {
              m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey,DATA::MeasCarbonConc,double(ConcC/10000.));   // ppm -> %
            }
          }// if ( ((Temp != DEF::Inv_Long && Temp > 0.) && ( (ConcAl != DEF::Inv_Long && ConcAl > 0.) || 
          else
          {
            std::string ProductID = HeatId + "_" + TreatId;
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",ProductID,CustHeatId);

            Message += "CELOX - for HeatID " + CustHeatId; 

            if ( !(Temp > 0.) )
            {
              Message += " Temp ";
              pEventLog->EL_MeasurementRejected(sMessage, Message.c_str(), Temp);
            }
            if ( !(ConcAl > 0.) )
            {
              Message += " ConcAl ";
              pEventLog->EL_MeasurementRejected(sMessage, Message.c_str(), ConcAl);
            }
            if ( !(ConcO2 > 0.) )
            {
              Message += " ConcO2 ";
              pEventLog->EL_MeasurementRejected(sMessage, Message.c_str(), ConcO2);
            }
            if ( !(ConcC > 0.) )
            {
              Message += " ConcC ";
              pEventLog->EL_MeasurementRejected(sMessage, Message.c_str(), ConcC);
            }

            RetValue = false;
          }
        }// else if ( MeasType == 5 )   //Celox
        else if ( MeasType == 6 )   //CeloxSlag
        {
          if ( ConcFeO > 0. || ConcMnO > 0. )
          {
            EventMessageVector.push_back( LF_EvMsg::evLFSlagCeloxMeasurement);
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey,DATA::SampleType    ,DEF_GC_MEASUREMENT_TYPE::Celox_Slag);

            //if ( Temp != DEF::Inv_Long && Temp > 0. )
            //{
            //  m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey,DATA::MeasTemp      ,Temp);
            //}

            if ( ConcFeO > 0. )
            {
              m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey,DATA::MeasFeOConc   ,double(ConcFeO/10000.)); // ppm -> %
            }

            if ( ConcMnO > 0. )
            {
              m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey,DATA::MeasMnOConc   ,double(ConcMnO/10000.)); // ppm -> %
            }
          }// if ( (ConcFeO != DEF::Inv_Long && ConcFeO > 0.) || (ConcMnO != DEF::Inv_Long && ConcMnO > 0.) )
          else
          {
            std::string ProductID = HeatId + "_" + TreatId;
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",ProductID,CustHeatId);

            Message += "CELOX/SLAG - for HeatID " + CustHeatId;

            if ( !(ConcFeO > 0.) )
            {
              Message += " ConcFeO ";
              pEventLog->EL_MeasurementRejected(sMessage, Message.c_str(), ConcFeO);
            }

            if ( !(ConcMnO > 0.) )
            {
              Message += " ConcMnO ";
              pEventLog->EL_MeasurementRejected(sMessage, Message.c_str(), ConcMnO);
            }

            RetValue = false;
          }
        }//  else if ( MeasType == 6 )   //CeloxSlag

        if ( RetValue )
        {
          //********    Write telegram data  ***********************************************************************

          m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),DATA::DateTime     ,Now.assDate());

          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::PlantID             ,PlantId);
          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::LadleTransferCarId ,LadleTransferCarId);

          m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey,DATA::SampleNo        ,MeasNo);    
          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::SampleId      ,SampleId);
          m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey,DATA::SampleUsable    ,1);
          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::UserCode      ,"L1");
          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::ProcessStage ,DEF_PROCESS_STAGE::InProcess);

          m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

          //********    send internal event  ***********************************************************************

          SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);
        }
        //********    End processing data  ***********************************************************************
      }// 
      else
      {
        RetValue = false;
      }

      log (TlgName + ": Finished", 3);
    }
    catch (cCBS_DBExc &e)
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::Exception& cExc) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
        Function.c_str(), TlgName.c_str());
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(),TlgName.c_str());
      RetValue = false;
    }
  }// if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
}// bool CLF_TelegramHandler::DoProcessLFL211TempTaken(const std::string& Key, const std::string& TlgName)

bool CLF_TelegramHandler::DoProcessLFL212AimTemperature(const std::string& Key, const std::string& TlgName)
{
  //=========================    Update Aim Temperature   ===================================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CLF_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo         = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL212::UnitNo);
      HeatId         = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL212::HeatId );
      TreatId        = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL212::TreatId);
      double AimTemp = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key.c_str(),Telegram_LFL212::AimTemp);

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler  ***********************************************************************

      //********    preparation telegram data   ****************************************************************

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        //********    Convert and check telegram data  *********************************************************   

        // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
        UnitNo  = CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);
  
        checkValidity         (TlgName,"UnitNo" ,UnitNo,  1,  2);
        checkValidityToDefault(TlgName,"AimTemp",AimTemp, 0., 2000., 0. );

        //********    main telegram data   ***********************************************************************

        DataKey   = generateDataKey(HeatId);     

        //********    Define Event *******************************************************************************

        if ( AimTemp != DEF::Inv_Double && AimTemp > 0. )
        {
          EventMessageVector.push_back(LF_EvMsg::evLFUpdateAimTemperature);

          m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey.c_str(), DATA::TempAim, AimTemp);
        }
        else
        {
          std::string ProductID = HeatId + "_" + TreatId;
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",ProductID,CustHeatId);

          std::string Message = "TEMP - for HeatID " + CustHeatId; 

          Message += " AimTemp ";
          pEventLog->EL_MeasurementRejected(sMessage, Message.c_str(), AimTemp);

          RetValue = false;
        }

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************
      }// 
      else
      {
        RetValue = false;
      }

      log (TlgName + ": Finished", 3);
    }
    catch (cCBS_DBExc &e)
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::Exception& cExc) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
        Function.c_str(), TlgName.c_str());
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(),TlgName.c_str());
      RetValue = false;
    }
  }// if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
}// bool CLF_TelegramHandler::DoProcessLFL212AimTemperature(const std::string& Key, const std::string& TlgName)

bool CLF_TelegramHandler::DoProcessLFL213AimDepartureTime(const std::string& Key, const std::string& TlgName)
{
  //=========================    Update Aim Departure Time   ===================================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CLF_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo   = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL213::UnitNo);
      HeatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL213::HeatId );
      TreatId  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL213::TreatId);

      CORBA::Any AnyAimDepTime = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(),Telegram_LFL213::AimDepTime);

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler  ***********************************************************************

      //********    preparation telegram data   ****************************************************************

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        //********    Convert and check telegram data  *********************************************************   

        // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
        UnitNo  = CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);

        checkValidity(TlgName,"UnitNo",UnitNo,1,2);

        //********    main telegram data   ***********************************************************************

        DataKey   = generateDataKey(HeatId);

        CDateTime AimDepTime(AnyAimDepTime);      

        //********    Define Event *******************************************************************************

        if ( AimDepTime != CSMC_DBData::unspecDate )
        {
          EventMessageVector.push_back(LF_EvMsg::evLFUpdateAimDepartureTime);

          //********    Write telegram data  ***********************************************************************

          m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),DATA::TreatEndAim,AimDepTime.assDate());

          m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

          //********    send internal event  ***********************************************************************

          SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);
        }
        else
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);

          pEventLog->EL_InvalidTlgData(sMessage, TlgName.c_str(), "AimDepTime", AimDepTime.asString().c_str());

          RetValue = false;
        }

        //********    End processing data  ***********************************************************************
      }// 
      else
      {
        RetValue = false;
      }

      log (TlgName + ": Finished", 3);
    }
    catch (cCBS_DBExc &e)
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::Exception& cExc) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
        Function.c_str(), TlgName.c_str());
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(),TlgName.c_str());
      RetValue = false;
    }
  }// if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
}// bool CLF_TelegramHandler::DoProcessLFL213AimDepartureTime(const std::string& Key, const std::string& TlgName)


bool CLF_TelegramHandler::DoProcessLFL217DelayStatus(const std::string& Key, const std::string& TlgName)
{
	 //=========================    Delay Status   ===================================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CLF_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo   = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL217::UnitNo);
      HeatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL217::HeatId );
      TreatId  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL217::TreatId);

	  string DelayCode = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL217::DelayCode);
	  CORBA::Any AnyDelayStartTime = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(),Telegram_LFL217::DelayStartTime);
	  CORBA::Any AnyDelayEndTime = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(),Telegram_LFL217::DelayEndTime);

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler  ***********************************************************************

      //********    preparation telegram data   ****************************************************************

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        //********    Convert and check telegram data  *********************************************************   

        // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
        UnitNo  = CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);

        checkValidity(TlgName,"UnitNo",UnitNo,1,2);

        //********    main telegram data   ***********************************************************************

        DataKey   = generateDataKey(TlgName);

        CDateTime DelayStartTime(AnyDelayStartTime); 
		CDateTime DelayEndTime(AnyDelayEndTime); 

        //********    Define Event *******************************************************************************

        if ( DelayStartTime != CSMC_DBData::unspecDate || DelayEndTime != CSMC_DBData::unspecDate )
        {
          EventMessageVector.push_back(LF_EvMsg::evLFDelayStatus);

          //********    Write telegram data  ***********************************************************************

		  m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey.c_str(), DATA::DelayCode, DelayCode);
          m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),DATA::DelayStartDate,DelayStartTime.assDate());
		  m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),DATA::DelayEndDate,DelayEndTime.assDate());

          m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

          //********    send internal event  ***********************************************************************

          SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,true);//SARS
        }
        else
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);

          pEventLog->EL_InvalidTlgData(sMessage, TlgName.c_str(), "Delay Code", DelayCode.c_str());

          RetValue = false;
        }

        //********    End processing data  ***********************************************************************
      }// 
      else
      {
        RetValue = false;
      }

      log (TlgName + ": Finished", 3);
    }
    catch (cCBS_DBExc &e)
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::Exception& cExc) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
        Function.c_str(), TlgName.c_str());
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(),TlgName.c_str());
      RetValue = false;
    }
  }// if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
} //bool CLF_TelegramHandler::DoProcessLFL217DelayStatus(const std::string& Key, const std::string& TlgName)


bool CLF_TelegramHandler::DoProcessLFL220CompMode(const std::string& Key, const std::string& TlgName)
{
  //=======================   L F   C O M P U T E R   M O D E S   ============================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CLF_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo   = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL220::UnitNo);
      HeatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL220::HeatId );
      TreatId  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL220::TreatId);

      long CarNo     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL220::CarNo);
      long ModeElec  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL220::ModeElec);
      long ModeStirr = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL220::ModeStirr);
      long ModeMat   = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL220::ModeMat);

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler  ***********************************************************************

      //********    preparation telegram data   ****************************************************************

	    HeatId = CDataConversion::Trim(HeatId);  //// u153 - HeatId can be empty from L1
      if ( !HeatId.empty() && HeatId != DEF::Inv_String )
	    {
        checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);
	    }

      if ( RetValue )
      {
        //********    Convert and check telegram data  *********************************************************   

        // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
        UnitNo    = CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);
        CarNo     = CDataConversion::SetInvalidToDefault(CarNo,DEF::Inv_Long,LONG_MIN);  
        ModeElec  = CDataConversion::SetInvalidToDefault(ModeElec,DEF::Inv_Long,LONG_MIN);
        ModeStirr = CDataConversion::SetInvalidToDefault(ModeStirr,DEF::Inv_Long,LONG_MIN);
        ModeMat   = CDataConversion::SetInvalidToDefault(ModeMat,DEF::Inv_Long,LONG_MIN);

        checkValidity(TlgName,"UnitNo"    ,UnitNo     ,1,2);
        checkValidity(TlgName,"CarNo"     ,CarNo      ,1,2);
        checkValidity(TlgName,"ModeElec"  ,ModeElec   ,0,2);
        checkValidity(TlgName,"ModeStirr" ,ModeStirr  ,0,2);
        checkValidity(TlgName,"ModeMat"   ,ModeMat    ,0,2);

        //********    main telegram data   ***********************************************************************

        DataKey   = generateDataKey(HeatId); 

        std::string LadleTransferCarId = CDataConversion::LongToString(CarNo);

        seqComputerModes SeqComputerModes;      // the Sequence, stores data for Electric, Stirring, MatHandle mode
        sComputerMode ComputerMode;

        bool NewMode = false;

        if ( m_StatusHandler.isStatusChanged(PlantId+CDataConversion::LongToString(CarNo), DEF_COMP_MODES::Electric,  ModeElec)  || 
             m_StatusHandler.isStatusChanged(PlantId+CDataConversion::LongToString(CarNo), DEF_COMP_MODES::Stirring,  ModeStirr) ||
             m_StatusHandler.isStatusChanged(PlantId+CDataConversion::LongToString(CarNo), DEF_COMP_MODES::MatHandle, ModeMat) )
        {
          //============================= Electric =======================================================
          ComputerMode.Device = DEF_COMP_MODES::Electric;
          ComputerMode.Status = DEF_GC_COMP_STATUS::ManualMode;
          
          if(ModeElec == 1) 
          {
            ComputerMode.Status = DEF_GC_COMP_STATUS::AutoMode;
          }
          else if(ModeElec > 1) 
          {
            ComputerMode.Status = DEF_GC_COMP_STATUS::ComputerDynamicMode;
          }

          CIntfData::insert(SeqComputerModes,ComputerMode);

          //============================= Stirring =======================================================
          ComputerMode.Device = DEF_COMP_MODES::Stirring;
          ComputerMode.Status = DEF_GC_COMP_STATUS::ManualMode;
          
          if(ModeStirr == 1) 
          {
            ComputerMode.Status = DEF_GC_COMP_STATUS::AutoMode;
          }
          else if(ModeStirr > 1) 
          {
            ComputerMode.Status = DEF_GC_COMP_STATUS::ComputerDynamicMode;
          }

          CIntfData::insert(SeqComputerModes,ComputerMode);

          //============================= MatHandle =======================================================
          ComputerMode.Device = DEF_COMP_MODES::MatHandle;
          ComputerMode.Status = DEF_GC_COMP_STATUS::ManualMode;

          if(ModeMat == 1) 
          {
            ComputerMode.Status = DEF_GC_COMP_STATUS::AutoMode;
          }
          else if(ModeMat > 1) 
          {
            ComputerMode.Status = DEF_GC_COMP_STATUS::ComputerDynamicMode;
          }

          CIntfData::insert(SeqComputerModes,ComputerMode);

          NewMode = true;
        }

        //********    Define Event *******************************************************************************

        if ( NewMode )
        {
          EventMessageVector.push_back( LF_EvMsg::evLFSetComputerMode);

          //********    Write telegram data  ***********************************************************************

          m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),DATA::DateTime               ,Now.assDate());

          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey.c_str(),DATA::PlantID              ,PlantId);
          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey.c_str(),DATA::LadleTransferCarId   ,LadleTransferCarId);

          m_pTelegram_Adapter->m_pIntf_OUT->setComputerModes(DataKey.c_str(),DATA::ComputerModes ,SeqComputerModes);

          m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

          //********    send internal event  ***********************************************************************

          SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);
        }
        else
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
		  		  
		  //// U153 - if "Computer modes was not changed" it could mean that L1 sent telergam by Plant Status Request - this is not an error!
		  sMessage.severity = c_e_warning;

          pEventLog->EL_InvalidTlgData(sMessage, TlgName.c_str(), "Mode", "Computer modes is not changed");

          ////RetValue = false;
        }

        //********    End processing data  ***********************************************************************
      }// 
      else
      {
        RetValue = false;
      }

      log (TlgName + ": Finished", 3);
    }
    catch (cCBS_DBExc &e)
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::Exception& cExc) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
        Function.c_str(), TlgName.c_str());
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(),TlgName.c_str());
      RetValue = false;
    }
  }// if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
}// bool CLF_TelegramHandler::DoProcessLFL220CompMode(const std::string& Key, const std::string& TlgName)

bool CLF_TelegramHandler::DoProcessLFL221FurnStatus(const std::string& Key, const std::string& TlgName)
{
  //=========================     F U R N A C E    S T A T U S     ======================================== 

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CLF_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo         = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL221::UnitNo);
      long CarNo     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL221::CarNo);

      long GantryPos = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL221::GantryPos);
      long RoofPos   = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL221::RoofPos);

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler  ***********************************************************************

      //********    preparation telegram data   ****************************************************************

      //********    Convert and check telegram data  *********************************************************   

      // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
      UnitNo    = CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);
      CarNo     = CDataConversion::SetInvalidToDefault(CarNo,DEF::Inv_Long,LONG_MIN);  
      GantryPos = CDataConversion::SetInvalidToDefault(GantryPos,DEF::Inv_Long,LONG_MIN);
      RoofPos   = CDataConversion::SetInvalidToDefault(RoofPos,DEF::Inv_Long,LONG_MIN);

      checkValidity(TlgName,"UnitNo"    ,UnitNo   ,1,2);
      checkValidity(TlgName,"CarNo"     ,CarNo    ,0,2);  //// no car can be in treatment position
      checkValidity(TlgName,"GantryPos" ,GantryPos,0,2);
      checkValidity(TlgName,"RoofPos"   ,RoofPos  ,0,1);

      //********    main telegram data   ***********************************************************************

      //DataKey   = generateDataKey(HeatId);
      DataKey   = generateDataKey(TlgName);  

      std:: string LadleTransferCarId = CDataConversion::LongToString(CarNo);
      long LadleCarPosition = DEF_CARPOSITION::OperationPositon;

      if (CarNo == 0)
      {
        LadleCarPosition = DEF_CARPOSITION::OutOfOperatingPosition;
      }

      if ( m_StatusHandler.isStatusChanged(PlantId, Telegram_LFL221::CarNo, CarNo) )
      {
        EventMessageVector.push_back( LF_EvMsg::evLFTransferCarPositionChanged);
      }

      if ( GantryPos == 0 )
      {
        GantryPos = DEF_GANTRY_POS::Maintenance;
      }
      else if ( GantryPos == 1 )
      {
        GantryPos = DEF_GANTRY_POS::Position1;
      }
      else if ( GantryPos == 2 )
      {
        GantryPos = DEF_GANTRY_POS::Position2;
      }

      // reset electrical status handler if gantry is 
      // switched from pos 1 over maintenance to pos 2 or reverse !
      if ( GantryPos == DEF_GANTRY_POS::Maintenance )
      {
        m_StatusHandler.isStatusChanged(PlantId, DEF_DEVICES::FurnaceBreaker   , DEF_GEN_STATES::Undefined);
        m_StatusHandler.isStatusChanged(PlantId, DEF_DEVICES::FurnacePowerOn   , DEF_GEN_STATES::Undefined);
        m_StatusHandler.isStatusChanged(PlantId, DEF_DEVICES::TapChanger       , DEF_GEN_STATES::Undefined);
        m_StatusHandler.isStatusChanged(PlantId, DEF_DEVICES::ImpCurve         , DEF_GEN_STATES::Undefined);
        m_StatusHandler.isStatusChanged(PlantId, DEF_DEVICES::Electrodes       , DEF_GEN_STATES::Undefined);
        m_StatusHandler.isStatusChanged(PlantId, DEF_DEVICES::ElectrodeInhibit , DEF_GEN_STATES::Undefined);

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_LogMessage(sMessage, "resetting electrical status");
      }

      //********    Define Event *******************************************************************************

      if ( m_StatusHandler.isStatusChanged(PlantId, DEF_DEVICES::Gantry, GantryPos) )
      {
        if ( GantryPos == DEF_GANTRY_POS::Maintenance )
        {
          EventMessageVector.push_back( LF_EvMsg::evLFGantrySwungOut);
          EventMessageVector.push_back( LF_EvMsg::evLFMaintenance);
        }
        else if ( GantryPos == DEF_GANTRY_POS::Position1 )
        {
          EventMessageVector.push_back( LF_EvMsg::evLFGantrySwungIn);
        }
        else if ( GantryPos == DEF_GANTRY_POS::Position2 )
        {
          EventMessageVector.push_back( LF_EvMsg::evLFGantrySwungIn);
        }
      }

      if ( m_StatusHandler.isStatusChanged(PlantId+CDataConversion::LongToString(CarNo), DEF_DEVICES::Roof, RoofPos) )
      {
        if ( RoofPos == 0 )
        {
          EventMessageVector.push_back( LF_EvMsg::evLFRoofArrivesInDownPosition);
        }
        else if ( RoofPos == 1 )
        {
          EventMessageVector.push_back( LF_EvMsg::evLFRoofArrivesInUpPosition);
        }
      }

      //********    Write telegram data  ***********************************************************************

      m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),DATA::DateTime     ,Now.assDate());

      m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::PlantID            ,PlantId);
      m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::LadleTransferCarId ,LadleTransferCarId);
      m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey,DATA::GantryPosIn        ,GantryPos);
      m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey,DATA::LadleCarPosition   ,LadleCarPosition);

      m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

      //********    send internal event  ***********************************************************************

      SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,true);

      //********    End processing data  ***********************************************************************

      log (TlgName + ": Finished", 3);
    }
    catch (cCBS_DBExc &e)
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::Exception& cExc) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
        Function.c_str(), TlgName.c_str());
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(),TlgName.c_str());
      RetValue = false;
    }
  }// if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
}// bool CLF_TelegramHandler::DoProcessLFL221FurnStatus(const std::string& Key, const std::string& TlgName)

bool CLF_TelegramHandler::DoProcessLFL222ElecStatus(const std::string& Key, const std::string& TlgName)
{
  //===============   F U R N A C E   E L E C T R I C A L   S T A T U S     =================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;  
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CLF_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo              = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL222::UnitNo);
      long FurnBreakOn    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL222::FurnBreakOn);
      long FurnPowerOn    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL222::FurnPowerOn);
      long TapChanger     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL222::TapChanger);
      long ElecPos        = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL222::ElecPos);
      long GantryPos      = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL222::GantryPos);
      long ElecHydSys     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL222::ElecHydSys);
      long ElecVoltTap    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL222::ElecVoltTap);
      long ElecCurvNo     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL222::ElecCurvNo);
      double ElecCons     = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LFL222::ElecCons);
      CORBA::Any SpareAny = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key,Telegram_LFL222::Spare);

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler  ***********************************************************************

      DEF::seqLong Spare; 
      long ResetStatusHandlerFlag = 0;

      CIntfData::getAt(ResetStatusHandlerFlag, Spare, 0 );

      if ( ResetStatusHandlerFlag == 1 )
      {
        EventMessageVector.push_back(LF_EvMsg::evLFUpdatePlantStatus);            
      }


      //********    preparation telegram data   ****************************************************************

      //********    Convert and check telegram data  *********************************************************   

      // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
      UnitNo      = CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);
      FurnBreakOn = CDataConversion::SetInvalidToDefault(FurnBreakOn,DEF::Inv_Long,LONG_MIN);
      FurnPowerOn = CDataConversion::SetInvalidToDefault(FurnPowerOn,DEF::Inv_Long,LONG_MIN);
      TapChanger  = CDataConversion::SetInvalidToDefault(TapChanger,DEF::Inv_Long,LONG_MIN);
      ElecPos     = CDataConversion::SetInvalidToDefault(ElecPos,DEF::Inv_Long,LONG_MIN);
      GantryPos   = CDataConversion::SetInvalidToDefault(GantryPos,DEF::Inv_Long,LONG_MIN);
      ElecHydSys  = CDataConversion::SetInvalidToDefault(ElecHydSys,DEF::Inv_Long,LONG_MIN);
      ElecVoltTap = CDataConversion::SetInvalidToDefault(ElecVoltTap,DEF::Inv_Long,LONG_MIN);
      ElecCurvNo  = CDataConversion::SetInvalidToDefault(ElecCurvNo,DEF::Inv_Long,LONG_MIN);
      ElecCons    = CDataConversion::SetInvalidToDefault(ElecCons,DEF::Inv_Double,0.);

      checkValidity(TlgName,"UnitNo"      ,UnitNo       ,1,2);
      checkValidity(TlgName,"FurnBreakOn" ,FurnBreakOn  ,0,1);
      checkValidity(TlgName,"FurnPowerOn" ,FurnPowerOn  ,0,1);
      checkValidity(TlgName,"TapChanger"  ,TapChanger   ,0,1);
      checkValidity(TlgName,"ElecPos"     ,ElecPos      ,0,1);
      checkValidity(TlgName,"GantryPos"   ,GantryPos    ,0,2);
      checkValidity(TlgName,"ElecHydSys"  ,ElecHydSys   ,0,1);

      //********    main telegram data   ***********************************************************************

      DataKey   = generateDataKey(HeatId); 

      long FurnBreakOnStat    = DEF_GEN_STATES::Off ;
      long FurnPowerOnStat    = DEF_GEN_STATES::Off ;
      long FurnTapChangOnStat = DEF_GEN_STATES::Off ;
      long ElecPosUpStat      = DEF_GEN_STATES::On ;
      long GantryPosInStat    = DEF_GANTRY_POS::Maintenance ;
      long ElecInhibitStat    = DEF_GEN_STATES::Yes ;

      if ( FurnBreakOn == 1 ) 
      {
        FurnBreakOnStat    = DEF_GEN_STATES::On ;
      }
      if ( FurnPowerOn == 1 ) 
      {
        FurnPowerOnStat    = DEF_GEN_STATES::On ;
      }
      if ( TapChanger  == 1 ) 
      {
        FurnTapChangOnStat = DEF_GEN_STATES::On ;
      }
      if ( ElecPos     == 1 ) // electrode 1 = Down = Not ElecPosUp = OperatingPosition 
      {
        ElecPosUpStat      = DEF_GEN_STATES::Off ;
      }

      if ( GantryPos   == 1 ) 
      {
        GantryPosInStat    = DEF_GANTRY_POS::Position1 ;
      }
      if ( GantryPos   == 2 ) 
      {
        GantryPosInStat    = DEF_GANTRY_POS::Position2 ;
      }

      if ( ElecHydSys  == 1 ) 
      {
        ElecInhibitStat    = DEF_GEN_STATES::No ;
      }

      //********    Define Event *******************************************************************************

      if ( m_StatusHandler.isStatusChanged(PlantId, DEF_DEVICES::FurnaceBreaker, FurnBreakOnStat) )
      {
        if ( FurnBreakOnStat == DEF_GEN_STATES::On )
        {
          EventMessageVector.push_back( LF_EvMsg::evLFFurnaceBreakerOn);
        }
        else
        {
          EventMessageVector.push_back( LF_EvMsg::evLFFurnaceBreakerOff);
        }
      }

      if ( m_StatusHandler.isStatusChanged(PlantId, DEF_DEVICES::FurnacePowerOn, FurnPowerOnStat) )
      {
        if ( FurnPowerOnStat == DEF_GEN_STATES::On )
        {
          EventMessageVector.push_back( LF_EvMsg::evLFPowerOn);
        }
        else
        {
          EventMessageVector.push_back( LF_EvMsg::evLFPowerOff);
        }
      }

      if ( m_StatusHandler.isStatusChanged(PlantId, DEF_DEVICES::TapChanger, FurnTapChangOnStat) )
      {
        if ( FurnTapChangOnStat == DEF_GEN_STATES::On )
        {
          EventMessageVector.push_back( LF_EvMsg::evLFTapChangeStart);
        }
        else
        {
          EventMessageVector.push_back( LF_EvMsg::evLFTapChangeFinished);
        }
      }
      else if ( m_StatusHandler.isStatusChanged(PlantId, DEF_DEVICES::ImpCurve, ElecCurvNo) )
      {
        EventMessageVector.push_back( LF_EvMsg::evLFImpCurveChanged);  
      }

      if ( m_StatusHandler.isStatusChanged(PlantId,DEF_DEVICES::Electrodes, ElecPosUpStat) )
      {
        if ( ElecPosUpStat == DEF_GEN_STATES::Off )
        {
          EventMessageVector.push_back( LF_EvMsg::evLFElectrodesInOperatingPosition);
        }
        else
        {
          EventMessageVector.push_back( LF_EvMsg::evLFElectrodesOutOperatingPosition);
        }
      }

      // Gantry position is sent by LFL221
      //if ( m_StatusHandler.isStatusChanged(PlantId, DEF_DEVICES::Gantry, GantryPosInStat) )
      //{
      //  if ( GantryPosInStat == DEF_GANTRY_POS::Maintenance )
      //  {
      //    EventMessageVector.push_back( LF_EvMsg::evLFGantrySwungOut);
      //    EventMessageVector.push_back( LF_EvMsg::evLFMaintenance);
      //  }
      //  else if ( GantryPosInStat == DEF_GANTRY_POS::Position1 )
      //  {
      //    EventMessageVector.push_back( LF_EvMsg::evLFGantrySwungIn);
      //  }
      //  else if ( GantryPosInStat == DEF_GANTRY_POS::Position2 )
      //  {
      //    EventMessageVector.push_back( LF_EvMsg::evLFGantrySwungIn);
      //  }
      //}

      if ( m_StatusHandler.isStatusChanged(PlantId, DEF_DEVICES::ElectrodeInhibit, ElecInhibitStat) )
      {
        if ( ElecInhibitStat == DEF_GEN_STATES::On )
        {
          EventMessageVector.push_back( LF_EvMsg::evLFElectrodeHydraulicSystemInhibitRequest);
        }
        else
        {
          EventMessageVector.push_back( LF_EvMsg::evLFElectrodeHydraulicSystemReleaseRequest);
        }
      }

      //********    Write telegram data  ***********************************************************************

      m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),DATA::DateTime,Now.assDate());

      m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,DATA::FurnBreakOn     ,FurnBreakOnStat);
      m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,DATA::PowerOn         ,FurnPowerOnStat);
      m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,DATA::FurnTapChangOn  ,FurnTapChangOnStat);
      m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,DATA::ElecPosUp       ,ElecPosUpStat);
      m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,DATA::GantryPosIn     ,GantryPosInStat);
      m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,DATA::ElecInhibit     ,ElecInhibitStat);

      m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,DATA::VoltTapNo       ,ElecVoltTap);
      m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,DATA::ElectrodRegCurve   ,ElecCurvNo);
      m_pTelegram_Adapter->m_pIntf_OUT->setDouble (DataKey,DATA::ElecCons        ,ElecCons);

      m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

      //********    send internal event  ***********************************************************************

      SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

      //********    End processing data  ***********************************************************************

      log (TlgName + ": Finished", 3);
    }
    catch (cCBS_DBExc &e)
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::Exception& cExc) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
        Function.c_str(), TlgName.c_str());
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(),TlgName.c_str());
      RetValue = false;
    }
  }// if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
}// bool CLF_TelegramHandler::DoProcessLFL222ElecStatus(const std::string& Key, const std::string& TlgName)

bool CLF_TelegramHandler::DoProcessLFL223ElecActVal(const std::string& Key, const std::string& TlgName)
{
  //=================   L F   E L E C T R I C A L   A C T U A L   V A L U E S     =============================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CLF_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo       = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_LFL223::UnitNo);
      HeatId       = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL223::HeatId );
      TreatId      = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL223::TreatId);
      long CarNo   = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_LFL223::CarNo);

      double ElecCons  = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LFL223::ElecCons);
      long ElecVoltTap = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_LFL223::ElecVoltTap);
      long ElecCurvNo  = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_LFL223::ElecCurvNo);

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler  ***********************************************************************

      //********    preparation telegram data   ****************************************************************

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        //********    Convert and check telegram data  *********************************************************   

        // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
        UnitNo      = CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);
        CarNo       = CDataConversion::SetInvalidToDefault(CarNo,DEF::Inv_Long,LONG_MIN);  
        ElecCons    = CDataConversion::SetInvalidToDefault(ElecCons,DEF::Inv_Double,0.);
        ElecVoltTap = CDataConversion::SetInvalidToDefault(ElecVoltTap,DEF::Inv_Long,LONG_MIN);
        ElecCurvNo  = CDataConversion::SetInvalidToDefault(ElecCurvNo,DEF::Inv_Long,LONG_MIN);

        checkValidity(TlgName,"UnitNo"  ,UnitNo ,1,2);
        checkValidity(TlgName,"CarNo"   ,CarNo  ,1,2);

        //********    main telegram data   ***********************************************************************

        DataKey   = generateDataKey(HeatId);

        std::string LadleTransferCarId = CDataConversion::LongToString(CarNo);

        //********    Define Event *******************************************************************************

        EventMessageVector.push_back( LF_EvMsg::evLFCyclicMeasurement);

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),DATA::DateTime     ,Now.assDate());

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::LadleTransferCarId ,LadleTransferCarId);    
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::MeasurementType    ,DEF_CYCLIC_MEASUREMENT_TYPES::Electric);

        m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey,DATA::ElecCons           ,ElecCons);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey,DATA::VoltTapNo            ,ElecVoltTap);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey,DATA::ElectrodRegCurve        ,ElecCurvNo);

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************
      }// 
      else
      {
        RetValue = false;
      }

      log (TlgName + ": Finished", 3);
    }
    catch (cCBS_DBExc &e)
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::Exception& cExc) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
        Function.c_str(), TlgName.c_str());
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(),TlgName.c_str());
      RetValue = false;
    }
  }// if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
}// bool CLF_TelegramHandler::DoProcessLFL223ElecActVal(const std::string& Key, const std::string& TlgName)

bool CLF_TelegramHandler::DoProcessLFL224BottomStirringStatus(const std::string& Key, const std::string& TlgName)
{
  //====================   B O T T O M   S T I R R I N G   S T A T U S   ===================================  

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CLF_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo         = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL224::UnitNo);
      HeatId         = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL224::HeatId );
      TreatId        = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL224::TreatId);

      long CarNo         = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL224::CarNo);

      long PlugNo         = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL224::PlugNo);
      long StirrGasType   = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL224::StirrGasType);
      long StirrStat      = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL224::StirrStat);
      long BypassStat     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL224::BypassStat);
      double StirrGasCons = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_LFL224::StirrGasCons);

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler  ***********************************************************************

      //********    preparation telegram data   ****************************************************************

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        //********    Convert and check telegram data  *********************************************************   

        // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
        UnitNo        = CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);
        CarNo         = CDataConversion::SetInvalidToDefault(CarNo,DEF::Inv_Long,LONG_MIN);  
        PlugNo        = CDataConversion::SetInvalidToDefault(PlugNo,DEF::Inv_Long,LONG_MIN);
        StirrGasType  = CDataConversion::SetInvalidToDefault(StirrGasType,DEF::Inv_Long,LONG_MIN);
        StirrStat     = CDataConversion::SetInvalidToDefault(StirrStat,DEF::Inv_Long,LONG_MIN);
        BypassStat    = CDataConversion::SetInvalidToDefault(BypassStat,DEF::Inv_Long,LONG_MIN);
        StirrGasCons  = CDataConversion::SetInvalidToDefault(StirrGasCons,DEF::Inv_Double,0.);      // l

        checkValidity(TlgName,"UnitNo"      ,UnitNo       ,1,2);
        checkValidity(TlgName,"CarNo"       ,CarNo        ,1,2);
        checkValidity(TlgName,"PlugNo"      ,PlugNo       ,1,2);
        checkValidity(TlgName,"StirrGasType",StirrGasType ,1,2);
        checkValidity(TlgName,"StirrStat"   ,StirrStat    ,0,1);
        checkValidity(TlgName,"BypassStat"  ,BypassStat   ,0,1);

        // l/min -> Nm�/min
        StirrGasCons = StirrGasCons / 1000. ;

        //********    main telegram data   ***********************************************************************

        DataKey   = generateDataKey(HeatId);    

        std::string LadleTransferCarId = CDataConversion::LongToString(CarNo);

        seqStirringData   SeqStirringData;
        sStirringData     StirringData;

        seqGasData        SeqGasData;      
        sGasData          GasData;

        seqStatus         SeqStirringStatus;
        seqStatus         SeqBypassStatus;
        sStatus           Status;

        std::string       GasType;
        std::string       StirringDevice;
        CDateTime         Now;

        if (StirrGasType == 1)
        {
          GasData.GasValue  = StirrGasCons;
          GasData.GasType   = DEF_GC_STIRR_GAS_TYPE::Ar.c_str();
          GasType           = DEF_GC_STIRR_GAS_TYPE::Ar;
        }
        else if (StirrGasType == 2)
        {
          GasData.GasValue  = StirrGasCons;
          GasData.GasType   = DEF_GC_STIRR_GAS_TYPE::N2.c_str();
          GasType           = DEF_GC_STIRR_GAS_TYPE::N2;
        }

        CIntfData::insert(SeqGasData,GasData);

        //********    Define Event *******************************************************************************

        if ( PlugNo == 1 )
        {
          StirringDevice        = DEF_GC_STIRR_DEVICE::Plug1;

          StirringData.Device   = DEF_GC_STIRR_DEVICE::Plug1.c_str();
          StirringData.GasData  = SeqGasData;
          CIntfData::insert(SeqStirringData,StirringData);

          if ( m_StatusHandler.isStatusChanged(PlantId+CDataConversion::LongToString(CarNo), DEF_GC_STIRR_DEVICE::Plug1, StirrStat ) )
          {
            if ( StirrStat == 0 ) 
            {
              EventMessageVector.push_back( LF_EvMsg::evLFBottomStirringEnd);
              Status.Status     = DEF_GEN_STATES::Off;
              Status.StatusName = DEF_STATUS_NAME::Stirring;
              Status.EndTime    = Now.assDate();
              Status.Device     = DEF_GC_STIRR_DEVICE::Plug1.c_str();
              CIntfData::insert(SeqStirringStatus,Status);
            }
            else if ( StirrStat == 1 ) 
            {
              EventMessageVector.push_back( LF_EvMsg::evLFBottomStirringStart);
              Status.Status     = DEF_GEN_STATES::On;
              Status.StatusName = DEF_STATUS_NAME::Stirring;
              Status.StartTime  = Now.assDate();
              Status.Device     = DEF_GC_STIRR_DEVICE::Plug1.c_str();
              CIntfData::insert(SeqStirringStatus,Status);
            }
          } // if ( m_StatusHandler.isStatusChanged(PlantId+CDataConversion::LongToString(CarNo), DEF_GC_STIRR_DEVICE::Plug1, StirrStat ) )

          if ( m_StatusHandler.isStatusChanged(PlantId+CDataConversion::LongToString(CarNo), DEF_GC_STIRR_DEVICE::BypassPlug1, BypassStat ) )
          {
            if ( BypassStat == 0 ) 
            {
              EventMessageVector.push_back( LF_EvMsg::evLFBottomStirringByPassOff);
              Status.Status     = DEF_GEN_STATES::Off;
              Status.StatusName = DEF_STATUS_NAME::Bypass;
              Status.EndTime    = Now.assDate();
              Status.Device     = DEF_GC_STIRR_DEVICE::BypassPlug1.c_str();
              CIntfData::insert(SeqBypassStatus,Status);                
            }
            else if ( BypassStat == 1 ) 
            {
              EventMessageVector.push_back( LF_EvMsg::evLFBottomStirringByPassOn);
              Status.Status     = DEF_GEN_STATES::On;
              Status.StatusName = DEF_STATUS_NAME::Bypass;
              Status.StartTime  = Now.assDate();
              Status.Device     = DEF_GC_STIRR_DEVICE::BypassPlug1.c_str();
              CIntfData::insert(SeqBypassStatus,Status);                
            }
          } // if ( m_StatusHandler.isStatusChanged(PlantId+CDataConversion::LongToString(CarNo), DEF_GC_STIRR_DEVICE::BypassPlug1, BypassStat ) )
        }
        else if ( PlugNo == 2 )
        {
          StirringDevice        = DEF_GC_STIRR_DEVICE::Plug2;

          StirringData.Device   = DEF_GC_STIRR_DEVICE::Plug2.c_str();
          StirringData.GasData  = SeqGasData;
          CIntfData::insert(SeqStirringData,StirringData);

          if ( m_StatusHandler.isStatusChanged(PlantId+CDataConversion::LongToString(CarNo), DEF_GC_STIRR_DEVICE::Plug2, StirrStat ) )
          {
            if ( StirrStat == 0 ) 
            {
              EventMessageVector.push_back( LF_EvMsg::evLFBottomStirringEnd);
              Status.Status   = DEF_GEN_STATES::Off;
              Status.StatusName = DEF_STATUS_NAME::Stirring;
              Status.EndTime  = Now.assDate();
              Status.Device   = DEF_GC_STIRR_DEVICE::Plug2.c_str();
              CIntfData::insert(SeqStirringStatus,Status);
            }
            else if ( StirrStat == 1 ) 
            {
              EventMessageVector.push_back( LF_EvMsg::evLFBottomStirringStart);
              Status.Status     = DEF_GEN_STATES::On;
              Status.StatusName = DEF_STATUS_NAME::Stirring;
              Status.StartTime  = Now.assDate();
              Status.Device     = DEF_GC_STIRR_DEVICE::Plug2.c_str();
              CIntfData::insert(SeqStirringStatus,Status);
            }
          } // if ( m_StatusHandler.isStatusChanged(PlantId+CDataConversion::LongToString(CarNo), DEF_GC_STIRR_DEVICE::Plug2, StirrStat ) )

          if ( m_StatusHandler.isStatusChanged(PlantId+CDataConversion::LongToString(CarNo), DEF_GC_STIRR_DEVICE::BypassPlug2, BypassStat ) )
          {
            if ( BypassStat == 0 ) 
            {
              EventMessageVector.push_back( LF_EvMsg::evLFBottomStirringByPassOff);
              Status.Status     = DEF_GEN_STATES::Off;
              Status.StatusName = DEF_STATUS_NAME::Bypass;
              Status.EndTime    = Now.assDate();
              Status.Device     = DEF_GC_STIRR_DEVICE::BypassPlug2.c_str();
              CIntfData::insert(SeqBypassStatus,Status);
            }
            else if ( BypassStat == 1 ) 
            {
              EventMessageVector.push_back( LF_EvMsg::evLFBottomStirringByPassOn);
              Status.Status     = DEF_GEN_STATES::On;
              Status.StatusName = DEF_STATUS_NAME::Bypass;
              Status.StartTime  = Now.assDate();
              Status.Device     = DEF_GC_STIRR_DEVICE::BypassPlug2.c_str();
              CIntfData::insert(SeqBypassStatus,Status);
            }

          } // if ( m_StatusHandler.isStatusChanged(PlantId+CDataConversion::LongToString(CarNo), DEF_GC_STIRR_DEVICE::BypassPlug2, BypassStat ) )
        }

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setDate   (DataKey.c_str(), DATA::DateTime              , Now.assDate());

        m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey        , DATA::LadleTransferCarId    , LadleTransferCarId);
        m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey.c_str(), DATA::StirringGasType       , GasType);
        m_pTelegram_Adapter->m_pIntf_OUT->setStatus (DataKey.c_str(), DATA::StirringStatus        , SeqStirringStatus);
        m_pTelegram_Adapter->m_pIntf_OUT->setStatus (DataKey.c_str(), DATA::StirringBypassStatus  , SeqBypassStatus);

        m_pTelegram_Adapter->m_pIntf_OUT->setStirringData(DataKey.c_str(), DATA::StirringAmount   , SeqStirringData);

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************
      }// 
      else
      {
        RetValue = false;
      }

      log (TlgName + ": Finished", 3);
    }
    catch (cCBS_DBExc &e)
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::Exception& cExc) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
        Function.c_str(), TlgName.c_str());
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(),TlgName.c_str());
      RetValue = false;
    }
  }// if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
}// bool CLF_TelegramHandler::DoProcessLFL224BottomStirringStatus(const std::string& Key, const std::string& TlgName)

bool CLF_TelegramHandler::DoProcessLFL225EmergencyLanceStirringStatus(const std::string& Key, const std::string& TlgName)
{
  //================   E M E R G E N C Y   L A N C E   S T I R R I N G   S T A T U S    =======================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CLF_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo         = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL225::UnitNo);
      HeatId         = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL225::HeatId );
      TreatId        = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL225::TreatId);
      long CarNo     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL225::CarNo);

      long StirrGasType   = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL225::StirrGasType);
      long StirrStat      = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL225::StirrStat);
      double StirrGasCons = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LFL225::StirrGasCons); //l

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler  ***********************************************************************

      //********    preparation telegram data   ****************************************************************

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        //********    Convert and check telegram data  *********************************************************   

        // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
        UnitNo        = CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);
        CarNo         = CDataConversion::SetInvalidToDefault(CarNo,DEF::Inv_Long,LONG_MIN);  
        StirrGasType  = CDataConversion::SetInvalidToDefault(StirrGasType,DEF::Inv_Long,LONG_MIN);
        StirrStat     = CDataConversion::SetInvalidToDefault(StirrStat,DEF::Inv_Long,LONG_MIN);
        StirrGasCons  = CDataConversion::SetInvalidToDefault(StirrGasCons,DEF::Inv_Double,0.);

        checkValidity(TlgName,"UnitNo"      ,UnitNo       ,1,2);
        checkValidity(TlgName,"CarNo"       ,CarNo        ,1,2);
        checkValidity(TlgName,"StirrGasType",StirrGasType ,1,2);
        checkValidity(TlgName,"StirrStat"   ,StirrStat    ,0,1);

        // l/min -> Nm�/min
        StirrGasCons = StirrGasCons / 1000. ;

        //********    main telegram data   ***********************************************************************

        DataKey   = generateDataKey(HeatId);     

        std::string LadleTransferCarId = CDataConversion::LongToString(CarNo);

        seqStirringData   SeqStirringData;
        sStirringData     StirringData;

        seqGasData        SeqGasData;      
        sGasData          GasData;

        seqStatus         SeqStirringStatus;
        sStatus           Status;

        CDateTime         Now;
        std::string       GasType;
        std::string       StirringDevice;


        if (StirrGasType == 1)
        {
          GasData.GasValue = StirrGasCons;
          GasData.GasType  = DEF_GC_STIRR_GAS_TYPE::Ar.c_str();
          GasType = DEF_GC_STIRR_GAS_TYPE::Ar;
        }
        else if (StirrGasType == 2)
        {
          GasData.GasValue = StirrGasCons;
          GasData.GasType  = DEF_GC_STIRR_GAS_TYPE::N2.c_str();
          GasType = DEF_GC_STIRR_GAS_TYPE::N2;
        }

        CIntfData::insert(SeqGasData,GasData);

        StirringData.Device   = DEF_GC_STIRR_DEVICE::EmergencyLance.c_str();
        StirringData.GasData  = SeqGasData;

        CIntfData::insert(SeqStirringData,StirringData);

        //********    Define Event *******************************************************************************

        if ( m_StatusHandler.isStatusChanged(PlantId+CDataConversion::LongToString(CarNo), DEF_GC_STIRR_DEVICE::EmergencyLance, StirrStat ) )
        {
          StirringDevice    = DEF_GC_STIRR_DEVICE::EmergencyLance;

          Status.Device     = DEF_GC_STIRR_DEVICE::EmergencyLance.c_str();
          Status.StatusName = DEF_STATUS_NAME::Stirring;

          if ( StirrStat == 0 ) 
          {
            EventMessageVector.push_back( LF_EvMsg::evLFEmergencyLanceStirringEnd);
            Status.Status   = DEF_GEN_STATES::Off;
            Status.EndTime  = Now.assDate();
          }
          else if ( StirrStat == 1 ) 
          {
            EventMessageVector.push_back( LF_EvMsg::evLFEmergencyLanceStirringStart);
            Status.Status     = DEF_GEN_STATES::On;
            Status.StartTime  = Now.assDate();
          }

          CIntfData::insert(SeqStirringStatus,Status);

          //********    Write telegram data  ***********************************************************************

          m_pTelegram_Adapter->m_pIntf_OUT->setDate   (DataKey.c_str() , DATA::DateTime             ,Now.assDate());

          m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey.c_str() , DATA::LadleTransferCarId   ,LadleTransferCarId);
          m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey.c_str() , DATA::StirringGasType      ,GasType);
          m_pTelegram_Adapter->m_pIntf_OUT->setStatus (DataKey.c_str() , DATA::StirringStatus       ,SeqStirringStatus);

          m_pTelegram_Adapter->m_pIntf_OUT->setStirringData(DataKey.c_str(), DATA::StirringAmount   ,SeqStirringData);

          m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

          //********    send internal event  ***********************************************************************

          SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);
        }
        else
        {
          RetValue = false;
        }

        //********    End processing data  ***********************************************************************
      }// 
      else
      {
        RetValue = false;
      }

      log (TlgName + ": Finished", 3);
    }
    catch (cCBS_DBExc &e)
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::Exception& cExc) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
        Function.c_str(), TlgName.c_str());
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(),TlgName.c_str());
      RetValue = false;
    }
  }// if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
}// bool CLF_TelegramHandler::DoProcessLFL225EmergencyLanceStirringStatus(const std::string& Key, const std::string& TlgName)

bool CLF_TelegramHandler::DoProcessLFL226ActualStirringValues(const std::string& Key, const std::string& TlgName)
{
  //========================   S T I R R I N G   A C T U A L    ========================================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CLF_TelegramHandler::DoProcess" + TlgName;
  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo      = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL226::UnitNo);
      HeatId      = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL226::HeatId );
      TreatId     = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL226::TreatId);
      long CarNo  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL226::CarNo);

      CORBA::Any AnyStirrGasType = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_LFL226::StirrGasType);
      CORBA::Any AnyStirrInt     = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_LFL226::StirrInt);
      CORBA::Any AnyFlowAct      = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_LFL226::FlowAct);        // l/min
      CORBA::Any AnyPressure     = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_LFL226::Pressure);
      CORBA::Any AnyStirrGasCons = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_LFL226::StirrGasCons);   // l

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler  ***********************************************************************

      //********    preparation telegram data   ****************************************************************

      // using DEF_PLANT::TransferCarXX at sendEventMessage to inform tracking about event assignment
      //checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        //********    Convert and check telegram data  *********************************************************   

        // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
        UnitNo  = CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);
        CarNo   = CDataConversion::SetInvalidToDefault(CarNo,DEF::Inv_Long,LONG_MIN);  

        checkValidity(TlgName,"UnitNo"  ,UnitNo ,1,2);
        checkValidity(TlgName,"CarNo"   ,CarNo  ,1,2);

        //Define the sequences for specific data
        DEF::seqLong SeqStirrGasType;
        DEF::seqLong SeqStirrInt;
        DEF::seqDouble SeqFlowAct;
        DEF::seqDouble SeqPressure;
        DEF::seqDouble SeqStirrGasCons;

        CIntfData::FromAny(SeqStirrGasType,AnyStirrGasType);
        CIntfData::FromAny(SeqStirrInt,AnyStirrInt);
        CIntfData::FromAny(SeqFlowAct,AnyFlowAct);
        CIntfData::FromAny(SeqPressure,AnyPressure);
        CIntfData::FromAny(SeqStirrGasCons,AnyStirrGasCons);

        checkValidity(TlgName,"StirrGasType"  ,SeqStirrGasType  ,0,2);
        checkValidity(TlgName,"StirrInt"      ,SeqStirrInt      ,0,6);
        checkValidity(TlgName,"FlowAct"       ,SeqFlowAct       ,0.,10000.);
        checkValidity(TlgName,"Pressure"      ,SeqPressure      ,0.,1000.);
        checkValidity(TlgName,"StirrGasCons"  ,SeqStirrGasCons  ,0.,100000.);

        //********    main telegram data   ***********************************************************************

        DataKey   = generateDataKey(HeatId);     
        std::string LadleTransferCarId = CDataConversion::LongToString(CarNo);

        // define PlantLocation as additional information for senEventMessage
        std::string PlantLocation       = DEF_PLANT::TransferCar1;

        if ( CarNo == 2 )
        {
          PlantLocation = DEF_PLANT::TransferCar2;
        }

        seqStirringData   StirringIntensityData;
        seqStirringData   StirringPressData; 
        seqStirringData   StirringConsData;
        seqStirringData   StirringFlowData;
        sStirringData     StirringData;

        seqGasData        SeqGasData;      
        sGasData          GasData;

        CDateTime         Now;

        // *************************************************************
        // gas type
        // *************************************************************
        std::string      GasType_Plug1;
        std::string      GasType_Plug2;
        std::string      GasType_Lance;
        long GasType1 = -1;
        long GasType2 = -1;
        long GasType3 = -1;
        CIntfData::getAt(GasType1,SeqStirrGasType,0);
        CIntfData::getAt(GasType2,SeqStirrGasType,1);
        CIntfData::getAt(GasType3,SeqStirrGasType,2);

        // consolidation of stirring gas type as leading value
        // we assume the gas type identical for each plugs, if only one plug is working
        if (GasType1 < 1)                 // plug 1 is OFF
        {
          GasType1 = GasType2;
        }
        if (GasType2 < 1)                 // plug 2 is OFF
        {
          GasType2 = GasType1;
        }
        // we assume the gas type identical for lance and the plugs, if only lance is working
        if (GasType1 < 1 && GasType2 < 1) // plugs are OFF
        {
          GasType1 = GasType3;
          GasType2 = GasType3;
        }
        // we assume the gas type identical for the plug 1 and lance, if only plugs are working
        if (GasType3 < 1)                 // lance is OFF
        {
          GasType3 = GasType1;
        }


        if (GasType1 == 1)
        {
          GasType_Plug1 = DEF_GC_STIRR_GAS_TYPE::Ar;
        }
        else if ( GasType1 == 2 )
        {
          GasType_Plug1 = DEF_GC_STIRR_GAS_TYPE::N2;
        }

        if ( GasType2 == 1 )
        {
          GasType_Plug2 = DEF_GC_STIRR_GAS_TYPE::Ar;
        }
        else if ( GasType2 == 2 )
        {
          GasType_Plug2 = DEF_GC_STIRR_GAS_TYPE::N2;
        }

        if ( GasType3 == 1 )
        {
          GasType_Lance = DEF_GC_STIRR_GAS_TYPE::Ar;
        }
        else if ( GasType3 == 2 )
        {
          GasType_Lance = DEF_GC_STIRR_GAS_TYPE::N2;
        }

        // *************************************************************
        // preset seqGasData
        // *************************************************************
        GasData.GasType  = "";
        GasData.GasValue = -1.;
        CIntfData::insert(SeqGasData,GasData);

        // *************************************************************
        // intensity
        // *************************************************************
        long StirrInt1    = -1;
        long StirrInt2    = -1;
        CIntfData::getAt(StirrInt1,SeqStirrInt,0);
        CIntfData::getAt(StirrInt2,SeqStirrInt,1);

        if ( !GasType_Plug1.empty() )
        {
          GasData.GasType  = GasType_Plug1.c_str();
          GasData.GasValue = StirrInt1;
          CIntfData::setAt(SeqGasData,GasData,0);
          StirringData.Device   = DEF_GC_STIRR_DEVICE::Plug1.c_str();
          StirringData.GasData  = SeqGasData;
          CIntfData::insert(StirringIntensityData,StirringData);
        }

        if ( !GasType_Plug2.empty() )
        {
          GasData.GasType  = GasType_Plug2.c_str();
          GasData.GasValue = StirrInt2;
          CIntfData::setAt(SeqGasData,GasData,0);
          StirringData.Device   = DEF_GC_STIRR_DEVICE::Plug2.c_str();
          StirringData.GasData  = SeqGasData;
          CIntfData::insert(StirringIntensityData,StirringData);
        }

        // *************************************************************
        // pressure
        // *************************************************************
        double Pressure1 = -1.;
        double Pressure2 = -1.;
        double Pressure3 = -1.;
        CIntfData::getAt(Pressure1,SeqPressure,0);
        CIntfData::getAt(Pressure2,SeqPressure,1);
        CIntfData::getAt(Pressure3,SeqPressure,2);
        
        if ( !GasType_Plug1.empty() )
        {
          GasData.GasType  = GasType_Plug1.c_str();
          GasData.GasValue = Pressure1;
          CIntfData::setAt(SeqGasData,GasData,0);
          StirringData.Device   = DEF_GC_STIRR_DEVICE::Plug1.c_str();
          StirringData.GasData  = SeqGasData;
          CIntfData::insert(StirringPressData,StirringData);
        }

        if ( !GasType_Plug2.empty() )
        {
          GasData.GasType  = GasType_Plug2.c_str();
          GasData.GasValue = Pressure2;
          CIntfData::setAt(SeqGasData,GasData,0);
          StirringData.Device   = DEF_GC_STIRR_DEVICE::Plug2.c_str();
          StirringData.GasData  = SeqGasData;
          CIntfData::insert(StirringPressData,StirringData);
        }

        if ( !GasType_Lance.empty() )
        {
          GasData.GasType  = GasType_Lance.c_str();
          GasData.GasValue = Pressure3;
          CIntfData::setAt(SeqGasData,GasData,0);
          StirringData.Device   = DEF_GC_STIRR_DEVICE::EmergencyLance.c_str();
          StirringData.GasData  = SeqGasData;
          CIntfData::insert(StirringPressData,StirringData);
        }

        // *************************************************************
        // flow
        // *************************************************************
        double Flow1 = -1.;
        double Flow2 = -1.;
        double Flow3 = -1.;
        CIntfData::getAt(Flow1,SeqFlowAct,0);
        CIntfData::getAt(Flow2,SeqFlowAct,1);
        CIntfData::getAt(Flow3,SeqFlowAct,2);

        // l/min -> Nm�/h
				//sankar 
        //Flow1 = Flow1 * 60. / 1000. ;
        //Flow2 = Flow2 * 60. / 1000. ;
        //Flow3 = Flow3 * 60. / 1000. ;
                
        if ( !GasType_Plug1.empty() )
        {
          GasData.GasType  = GasType_Plug1.c_str();
          GasData.GasValue = Flow1; 
          CIntfData::setAt(SeqGasData,GasData,0);
          StirringData.Device   = DEF_GC_STIRR_DEVICE::Plug1.c_str();
          StirringData.GasData  = SeqGasData;
          CIntfData::insert(StirringFlowData,StirringData);
        }

        if ( !GasType_Plug2.empty() )
        {
          GasData.GasType  = GasType_Plug2.c_str();
          GasData.GasValue = Flow2;
          CIntfData::setAt(SeqGasData,GasData,0);
          StirringData.Device   = DEF_GC_STIRR_DEVICE::Plug2.c_str();
          StirringData.GasData  = SeqGasData;
          CIntfData::insert(StirringFlowData,StirringData);
        }

        if ( !GasType_Lance.empty() )
        {
          GasData.GasType  = GasType_Lance.c_str();
          GasData.GasValue = Flow3;
          CIntfData::setAt(SeqGasData,GasData,0);
          StirringData.Device   = DEF_GC_STIRR_DEVICE::EmergencyLance.c_str();
          StirringData.GasData  = SeqGasData;
          CIntfData::insert(StirringFlowData,StirringData);
        }
        // *************************************************************
        // consumption
        // *************************************************************
        double Cons1 = -1.;
        double Cons2 = -1.;
        double Cons3 = -1.;
        CIntfData::getAt(Cons1,SeqStirrGasCons,0);
        CIntfData::getAt(Cons2,SeqStirrGasCons,1);
        CIntfData::getAt(Cons3,SeqStirrGasCons,2);

        // l -> Nm�
				//sankar
        //Cons1 = Cons1 / 1000. ;
        //Cons2 = Cons2 / 1000. ;
        //Cons3 = Cons3 / 1000. ;
        
        if ( !GasType_Plug1.empty() )
        {
          GasData.GasType  = GasType_Plug1.c_str();
          GasData.GasValue = Cons1;
          CIntfData::setAt(SeqGasData,GasData,0);
          StirringData.Device   = DEF_GC_STIRR_DEVICE::Plug1.c_str();
          StirringData.GasData  = SeqGasData;
          CIntfData::insert(StirringConsData,StirringData);
        }

        if ( !GasType_Plug2.empty() )
        {
          GasData.GasType  = GasType_Plug2.c_str();
          GasData.GasValue = Cons2;
          CIntfData::setAt(SeqGasData,GasData,0);
          StirringData.Device   = DEF_GC_STIRR_DEVICE::Plug2.c_str();
          StirringData.GasData  = SeqGasData;
          CIntfData::insert(StirringConsData,StirringData);
        }

        if ( !GasType_Lance.empty() )
        {
          GasData.GasType  = GasType_Lance.c_str();
          GasData.GasValue = Cons3;
          CIntfData::setAt(SeqGasData,GasData,0);
          StirringData.Device   = DEF_GC_STIRR_DEVICE::EmergencyLance.c_str();
          StirringData.GasData  = SeqGasData;
          CIntfData::insert(StirringConsData,StirringData);
        }
        //********    Define Event *******************************************************************************

        EventMessageVector.push_back(LF_EvMsg::evLFCyclicMeasurement);

        //********    Write telegram data  ***********************************************************************
        m_pTelegram_Adapter->m_pIntf_OUT->setDate        (DataKey.c_str(), DATA::DateTime               ,Now.assDate());

        m_pTelegram_Adapter->m_pIntf_OUT->setString      (DataKey        , DATA::LadleTransferCarId     ,LadleTransferCarId);
        m_pTelegram_Adapter->m_pIntf_OUT->setString      (DataKey        , DATA::MeasurementType        ,DEF_CYCLIC_MEASUREMENT_TYPES::Stirring);
        m_pTelegram_Adapter->m_pIntf_OUT->setStirringData(DataKey.c_str(), DATA::StirringIntensity      ,StirringIntensityData);
        m_pTelegram_Adapter->m_pIntf_OUT->setStirringData(DataKey.c_str(), DATA::StirringFlow           ,StirringFlowData);
        m_pTelegram_Adapter->m_pIntf_OUT->setStirringData(DataKey.c_str(), DATA::StirringAmount         ,StirringConsData);
        m_pTelegram_Adapter->m_pIntf_OUT->setStirringData(DataKey.c_str(), DATA::StirringPressure       ,StirringPressData);

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,PlantLocation,HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************
      }// 
      else
      {
        RetValue = false;
      }

      log (TlgName + ": Finished", 3);
    }
    catch (cCBS_DBExc &e)
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::Exception& cExc) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
        Function.c_str(), TlgName.c_str());
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(),TlgName.c_str());
      RetValue = false;
    }
  }// if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
}// bool CLF_TelegramHandler::DoProcessLFL226ActualStirringValues(const std::string& Key, const std::string& TlgName)

bool CLF_TelegramHandler::DoProcessLFL230CoolingWater(const std::string& Key, const std::string& TlgName)
{
  //================  C O O L I N G   W A T E R   F L O W   A N D   T E M P   ================================= 

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CLF_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo   = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL230::UnitNo);
      HeatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL230::HeatId );
      TreatId  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL230::TreatId);

      long CarNo         = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL230::CarNo);

      double RoofWaterInlet   = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_LFL230::RoofWaterInlet);
      double RoofWaterOutlet  = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_LFL230::RoofWaterOutlet);
      double RoofWaterFlow    = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_LFL230::RoofWaterFlow);    // Nm�/h
      double WGWaterInlet     = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_LFL230::WGWaterInlet);
      double WGWaterOutlet    = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_LFL230::WGWaterOutlet);
      double WGWaterFlow      = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_LFL230::WGWaterFlow);      // Nm�/h
      double ElecCons         = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_LFL230::ElecCons);

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler  ***********************************************************************

      //********    preparation telegram data   ****************************************************************

      // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
      UnitNo  = CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);
      CarNo   = CDataConversion::SetInvalidToDefault(CarNo,DEF::Inv_Long,LONG_MIN);  

      checkValidity(TlgName,Telegram_LFL230::UnitNo,     UnitNo,     1,2);
      checkValidity(TlgName,Telegram_LFL230::CarNo,      CarNo,      1,2);

      //********    Define Event *******************************************************************************

      EventMessageVector.push_back( LF_EvMsg::evLFCyclicMeasurement);

      //********    Convert and check telegram data  *********************************************************   

      // Nm�/h -> Nm�/min
      RoofWaterFlow   = RoofWaterFlow  / 60. ;
      WGWaterFlow     = WGWaterFlow    / 60. ;

      checkValidity(TlgName, Telegram_LFL230::RoofWaterInlet  ,RoofWaterInlet    ,0.,100.);
      checkValidity(TlgName, Telegram_LFL230::RoofWaterOutlet ,RoofWaterOutlet   ,0.,100.);
      checkValidity(TlgName, Telegram_LFL230::RoofWaterFlow   ,RoofWaterFlow     ,0.,100.);
      checkValidity(TlgName, Telegram_LFL230::WGWaterInlet    ,WGWaterInlet      ,0.,100.);
      checkValidity(TlgName, Telegram_LFL230::WGWaterOutlet   ,WGWaterOutlet     ,0.,100.);
      checkValidity(TlgName, Telegram_LFL230::WGWaterFlow     ,WGWaterFlow       ,0.,100.);

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        //********    main telegram data   ***********************************************************************

        DataKey   = generateDataKey(HeatId);

        std::string LadleTransferCarId = CDataConversion::LongToString(CarNo);

        seqCoolWaterData SeqCoolWaterData;
        sCoolWaterDevice CoolWaterDevice;

        CoolWaterDevice.CoolWaterDeviceNo         = 1; // default
        CoolWaterDevice.CoolWaterDevice           = DEF_GC_COOLWATER::Roof.c_str();
        CoolWaterDevice.CoolWaterData.InletTemp   = RoofWaterInlet;
        CoolWaterDevice.CoolWaterData.OutletTemp  = RoofWaterOutlet;
        CoolWaterDevice.CoolWaterData.WaterFlow   = RoofWaterFlow;
        CIntfData::insert(SeqCoolWaterData,CoolWaterDevice);

        CoolWaterDevice.CoolWaterDeviceNo         = 1; // default
        CoolWaterDevice.CoolWaterDevice           = DEF_GC_COOLWATER::WasteGas.c_str();
        CoolWaterDevice.CoolWaterData.InletTemp   = WGWaterInlet;
        CoolWaterDevice.CoolWaterData.OutletTemp  = WGWaterOutlet;
        CoolWaterDevice.CoolWaterData.WaterFlow   = WGWaterFlow;
        CIntfData::insert(SeqCoolWaterData,CoolWaterDevice);

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),DATA::DateTime                  ,Now.assDate());

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey.c_str(),DATA::LadleTransferCarId      ,LadleTransferCarId);

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey.c_str(),DATA::MeasurementType         ,DEF_CYCLIC_MEASUREMENT_TYPES::CoolingWater);

        m_pTelegram_Adapter->m_pIntf_OUT->setCoolWaterData(DataKey.c_str(),DATA::CoolingWaterData ,SeqCoolWaterData);

        m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey,DATA::ElecCons           ,ElecCons);

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************
      }// 
      else
      {
        RetValue = false;
      }

      log (TlgName + ": Finished", 3);
    }
    catch (cCBS_DBExc &e)
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::Exception& cExc) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
        Function.c_str(), TlgName.c_str());
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(),TlgName.c_str());
      RetValue = false;
    }
  }// if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }
  return RetValue;
}// bool CLF_TelegramHandler::DoProcessLFL230CoolingWater(const std::string& Key, const std::string& TlgName)

bool CLF_TelegramHandler::DoProcessLFL240Level1lParam(const std::string& Key, const std::string& TlgName)
{
  //================  L E V E L 1     P A R A M =================================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CLF_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo                = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL240::UnitNo);
      std::string ParamName = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL240::ParamName);
      double ParamValue     = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LFL240::ParamValue);

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      long PlantNo = m_pGC_Plant_Container->getPlantNo(PlantId);

      //********    reset statushandler  ***********************************************************************

      //********    preparation telegram data   ****************************************************************

      //********    Convert and check telegram data  *********************************************************   

      // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
      UnitNo  = CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);

      checkValidity(TlgName,"UnitNo",UnitNo,1,2);

      //********    main telegram data   ***********************************************************************

      DataKey   = generateDataKey(TlgName);  

      ParamName = CDataConversion::Trim(ParamName);
      log("Trimmed Value for ParamName -" + ParamName + "-",3);

      std::map<std::string,double> ParameterList;
      std::map<std::string,double>::iterator itParam;

      // **********************************************************************
      // special handling for stirring values transferred by certain parameters
      // **********************************************************************
     /* if ( ParamName == "BotStirrFlowDflt"    ||
           ParamName == "BotStirrFlowLowLow"  ||							     
           ParamName == "BotStirrFlowLow"     ||								    
           ParamName == "BotStirrFlowMedium"  ||	
           ParamName == "BotStirrFlowHigh"    ||		
           ParamName == "BotStirrFlowHighHigh")	
      {*/ //Maji  09thOct2013

	    if ( ParamName == "BotStirrFlowSoftDflt"    ||
           ParamName == "BotStirrFlowMedDflt"  ||							     
           ParamName == "BotStirrFlowStrongDflt"     ||								    
           ParamName == "BotStirrFlowCoolDflt"  ||	
           ParamName == "BotStirrFlowCleantDflt"    ||		
           ParamName == "BotStirrFlowSoftBubDflt")	
      {
        long Intensity = -1;

		 /* if(ParamName == "BotStirrFlowDflt" )									   
          Intensity = DEF_GCL_STIRR_INT::Soft;			  
        else if(ParamName == "BotStirrFlowLowLow")							     
          Intensity = DEF_GCL_STIRR_INT::Clean;			  
        else if(ParamName == "BotStirrFlowLow")								    
          Intensity = DEF_GCL_STIRR_INT::Initial;			
        else if(ParamName == "BotStirrFlowMedium")	
          Intensity = DEF_GCL_STIRR_INT::Medium;     
        else if(ParamName == "BotStirrFlowHigh")		
          Intensity = DEF_GCL_STIRR_INT::Strong;
        else if(ParamName == "BotStirrFlowHighHigh")	
          Intensity = DEF_GCL_STIRR_INT::Cool;*/ //Maji 09thOct2013

		    if(ParamName == "BotStirrFlowSoftDflt" )									   
          Intensity = DEF_GCL_STIRR_INT::Soft;			  
        else if(ParamName == "BotStirrFlowCleantDflt")							     
          Intensity = DEF_GCL_STIRR_INT::Clean;			  
        else if(ParamName == "BotStirrFlowSoftBubDflt")								    
          Intensity = DEF_GCL_STIRR_INT::Initial;			
        else if(ParamName == "BotStirrFlowMedDflt")	
          Intensity = DEF_GCL_STIRR_INT::Medium;     
        else if(ParamName == "BotStirrFlowStrongDflt")		
          Intensity = DEF_GCL_STIRR_INT::Strong;
        else if(ParamName == "BotStirrFlowCoolDflt")	
          Intensity = DEF_GCL_STIRR_INT::Cool;

        if ( Intensity != -1 && m_pGCL_STIRR_INT->select(Intensity) )
        {
          // l/min -> Nm�/min
          ParamValue = ParamValue / 1000. ;
            
          m_pGCL_STIRR_INT->setSTIRRFLOW(ParamValue);
          RetValue = m_pGCL_STIRR_INT->update();

          if ( RetValue )
          {
            m_pGCL_STIRR_INT->commit();
          }
          else
          {
            RetValue = false;
            std::string Message = "CLF_TelegramHandler: No intensity found for ParamName " + ParamName;

            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Message.c_str());

            m_pGCL_STIRR_INT->rollback();
          }
        }// if ( m_pGCL_STIRR_INT->select(Intensity) )
      }
      // ****************
      // general handling
      // ****************
      else if ( !ParamName.empty() )
      {
        ParameterList.insert ( std::pair<std::string,double> (ParamName, ParamValue) );
        if ( ParameterList.size() > 0 )
        {
          for ( itParam = ParameterList.begin(); itParam != ParameterList.end(); ++itParam)
          {
             std::string Name  = itParam->first;
             double Value      = itParam->second;
             // L1-Double sent parameter may be not a DParam type on L2
             if ( m_pGT_PARAM->isParam(Plant, PlantNo, Name, 0, CSMC_DBData::unspecLong) )
             {
               // This parameter are really in the GT_PARAM
               long ActParamType = m_pGT_PARAM->getTYPE(1);
            
               if ( m_pGT_PARAM->checkMinMaxRange(Plant, PlantNo, Name, 0, ActParamType,CDataConversion::DoubleToString(Value))  )
               {

				
                RetValue = RetValue && m_pGT_PARAM->updateValue(Plant, PlantNo, Name, 0, ActParamType,CDataConversion::DoubleToString(Value));
                 if ( RetValue )
                 {
                  CSMC_EventLogLF *pEventLog = CSMC_EventLogLFController::getInstance()->getpEventLog();
                  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                  pEventLog->EL_ParameterUpdate(sMessage, Name.c_str(), CDataConversion::DoubleToString(Value).c_str());

                  m_pGT_PARAM->commit();
                 }
                 else
                 {
                    std::string Message = "CLF_TelegramHandler: Update failed on parameter " + Name;
                    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                    pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Message.c_str());
                    m_pGT_PARAM->rollback();
                    RetValue = false;
                    break;
                 }
              } // if ( m_pGT_PARAM->checkMinMaxRange(Plant, PlantNo, Name, 0, DEF_GC_PARAM_TYPE::DParam, Value) )
            } // if ( m_pGT_PARAM->isParam(Plant, PlantNo, Name, 0, DEF_GC_PARAM_TYPE::DParam) )
            else
            {
              RetValue = false;

              std::string Message = "CLF_TelegramHandler: Invalid parameter name:" + Name;

              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Message.c_str());

            }
          } // for ( itParam = ParameterList.begin(); itParam != ParameterList.end(); ++itParam)
        }
        else
        {
           RetValue = false;
           std::string Message = "CLF_TelegramHandler: Invalid parameter name:" + ParamName;
           CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
           sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
           pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Message.c_str());
        }
        
      }
       else // Parameter  was empty
      {
          RetValue = false;
      }

      //********    Define Event *******************************************************************************

      if ( RetValue ) 
      {
        EventMessageVector.push_back( LF_EvMsg::evLFParameterUpdate);
        //isPlantEvent = true;

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),   DATA::DateTime        ,Now.assDate());

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey.c_str(), DATA::ParaArea        , "LF");
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey.c_str(), DATA::ProdPracPointer , "unkown"); //Na ja,but the onliest place, it is set outside of HMI

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey.c_str(), DATA::ParamName       , ParamName);
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey.c_str(), DATA::ParamValue      , CDataConversion::DoubleToString(ParamValue).c_str());

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,true);
      }

      //********    End processing data  ***********************************************************************

      log (TlgName + ": Finished", 3);

    }
    catch (cCBS_DBExc &e)
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::Exception& cExc) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
        Function.c_str(), TlgName.c_str());
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(),TlgName.c_str());
      RetValue = false;
    }
  }// if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
}// bool CLF_TelegramHandler::DoProcessLFL240Level1lParam(const std::string& Key, const std::string& TlgName)

bool CLF_TelegramHandler::DoProcessLFL260MatHandReport(const std::string &Key, const std::string &TlgName)
{
  //=================     M A T E R I A L   H A N D L I N G   R E P O R T         ============================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CLF_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo      = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL260::UnitNo);
      HeatId      = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL260::HeatId );
      TreatId     = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL260::TreatId);
      long CarNo  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL260::CarNo);

      long Target     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL260::Target);
      long Source     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL260::Source);
      long RecipeNo   = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL260::RecipeNo);
      long BatchStat  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL260::BatchStat);

      CORBA::Any AnyMatCode     = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_LFL260::MatCode);
      CORBA::Any AnyMatWeight   = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_LFL260::MatWeight);
      CORBA::Any AnySourceNo    = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_LFL260::SourceNo);
      CORBA::Any AnyFeedingRate = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_LFL260::FeedingRate);

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler  ***********************************************************************

      //********    preparation telegram data   ****************************************************************

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        //********    Convert and check telegram data  *********************************************************   

        // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
        UnitNo    = CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);
        CarNo     = CDataConversion::SetInvalidToDefault(CarNo,DEF::Inv_Long,LONG_MIN);  
        Target    = CDataConversion::SetInvalidToDefault(Target,DEF::Inv_Long,LONG_MIN);
        Source    = CDataConversion::SetInvalidToDefault(Source,DEF::Inv_Long,LONG_MIN);
        RecipeNo  = CDataConversion::SetInvalidToDefault(RecipeNo,DEF::Inv_Long,LONG_MIN);
        BatchStat = CDataConversion::SetInvalidToDefault(BatchStat,DEF::Inv_Long,LONG_MIN);   

        checkValidity(TlgName,"UnitNo"  ,UnitNo ,1,2);
        checkValidity(TlgName,"CarNo"   ,CarNo  ,1,2);
        checkValidity(TlgName,"Target"  ,Target ,1,9);
        checkValidity(TlgName,"Source"  ,Source ,1,3);

        checkValidity(TlgName,"RecipeNo"  ,RecipeNo   ,1,100000); // referenced by GC_RECIPE_L1 
        checkValidity(TlgName,"BatchStat" ,BatchStat  ,0,9);

        //********    main telegram data   ***********************************************************************

        DataKey   = generateDataKey(HeatId);

        std::string LadleTransferCarId = CDataConversion::LongToString(CarNo);

        // RecipeNo and RecipeName handling
        std::string L2RecipeName   = m_pGC_Recipe_L1Container->getL2RecipeNameByL1No( RecipeNo );
        std::string L2RecipeSource = m_pGC_SourceContainer->getL2SourceNameByL1No( Source );
        std::string L2RecipeTarget = m_pGC_Charge_Dest_Container->getDestNameByNo( Target );
        long L2RecipeNo            = m_pGC_Recipe_L1Container->getL2RecipeNoByL1No ( RecipeNo );

        // convert L2RecipeNo in case of receiving L1 data for already finished recipes
        CSMC_RecipeHandler RecipeHandler;
        RecipeHandler.checkMatHandlingRecipeData(Plant, HeatId, TreatId, L2RecipeSource, L2RecipeName, L2RecipeNo);

        // check RecipeStatus change
        m_StatusHandler.isStatusChanged(PlantId, L2RecipeName, BatchStat);

        DEF::seqString SeqMatCode;
        DEF::seqDouble SeqMatWeight;
        DEF::seqLong SeqSourceNo;
        DEF::seqDouble SeqFeedingRate;

        CIntfData::FromAny(SeqMatCode,AnyMatCode);
        CIntfData::FromAny(SeqMatWeight,AnyMatWeight);
        CIntfData::FromAny(SeqSourceNo,AnySourceNo);
        CIntfData::FromAny(SeqFeedingRate,AnyFeedingRate);

        seqBatch SeqBatch;

        // iteration over all sequences, SeqMatCode gives counter for iterator
        for ( long i = 0 ; i < CIntfData::getLength(SeqMatCode) ; ++i)
        {
          sBatch   Batch;

          std::string MatCode;
          double MatWeight    = -1.;
          long SourceNo     = -1;
          double FeedingRate  = -1.;

          CIntfData::getAt(MatCode,SeqMatCode,i);
          CIntfData::getAt(MatWeight,SeqMatWeight,i);
          CIntfData::getAt(SourceNo,SeqSourceNo,i);
          CIntfData::getAt(FeedingRate,SeqFeedingRate,i);        

          MatCode = CDataConversion::Trim(MatCode);
          log("Trimmed Value for MatCode -" + MatCode + "-",3);

          if ( !MatCode.empty() )
          {
            Batch.MatCode       = MatCode.c_str();
            Batch.Mass          = MatWeight;
            Batch.MatFeedSpeed  = FeedingRate;
            Batch.Source        = SourceNo;

            if ( MatCode.empty() || MatWeight < 0.01 )
            { 
              if ( BatchStat != 6 && 
                   BatchStat != 9 )    // // DischargeStart && Discharged     
              {
                std::string Message = TlgName +"::MatCode " + MatCode + " - MatWeight invalid " + CDataConversion::DoubleToString(MatWeight);
                CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                pEventLog->EL_ErrorProcessingData(sMessage, Function.c_str(),Message.c_str());
              }
            }
            else
            {
              CIntfData::insert(SeqBatch,Batch);
            }
          } // if ( !MatCode.empty() )
        } // for ( long i = 0 ; i < CIntfData::getLength(SeqMatCode) ; ++i)

        //********    Define Event *******************************************************************************

        if ( L2RecipeName == DEF::Undefined ||
             L2RecipeName.empty()           || 
             L2RecipeSource.empty()         || 
             L2RecipeTarget.empty()         ||
             L2RecipeNo < 0 )
        {
          std::string Message = TlgName +"::RecipeName = " + L2RecipeName + "; RecipeSource = " + L2RecipeSource + "; RecipeNo = " + CDataConversion::LongToString(L2RecipeNo) + "; RecipeTarget = " + L2RecipeTarget;
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorProcessingData(sMessage, Function.c_str(),Message.c_str());
        }
        else
        {
          if ( CIntfData::getLength(SeqBatch) == 0 )
          {
            if ( BatchStat != 6 && 
                 BatchStat != 9 )    // // DischargeStart && Discharged     
            {
              std::string Message = TlgName +"::MatWeight not available - RecipeName = " + L2RecipeName + "; RecipeNo = " + CDataConversion::LongToString(L2RecipeNo) + ";";
              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              pEventLog->EL_ErrorProcessingData(sMessage, Function.c_str(),Message.c_str());
            }
          }

          EventMessageVector.push_back( LF_EvMsg::evLFMaterialHandlingReport);

          //********    Write telegram data  ***********************************************************************
          m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),DATA::DateTime,Now.assDate());

          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::LadleTransferCarId, LadleTransferCarId);

          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::RecipeName     , L2RecipeName);
          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::RecipeSource   , L2RecipeSource);
          // not correct working on L1.. Target is always ladle
          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::RecipeTarget   , L2RecipeTarget);
          m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::RecipeNo       , L2RecipeNo);

          if ( 0 == BatchStat ) 
          {
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::RecipeStatus, DEF_GC_RECIPE_STATUS::Disabled);
            //m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::RecipeTarget   , DEF_GC_CHARGE_DEST::UnKnown);
          }
          else if ( 1 == BatchStat )
          {
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::RecipeStatus, DEF_GC_RECIPE_STATUS::Enabled);
            //m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::RecipeTarget   , DEF_GC_CHARGE_DEST::WeighingBin);
          }
          else if ( 2 == BatchStat )
          {
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::RecipeStatus, DEF_GC_RECIPE_STATUS::ProcessingStart);
          }
          else if ( 3 == BatchStat ) 
          {
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::RecipeStatus, DEF_GC_RECIPE_STATUS::Weighed);
            //m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::RecipeTarget   , DEF_GC_CHARGE_DEST::WeighingBin);
          }
          else if ( 4 == BatchStat ) 
          {
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::RecipeStatus, DEF_GC_RECIPE_STATUS::WeighingComplete);
            //m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::RecipeTarget   , DEF_GC_CHARGE_DEST::LadleHopper);
          }
          else if ( 5 == BatchStat )
          {
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::RecipeStatus, DEF_GC_RECIPE_STATUS::FirstMaterialInChargingHopper);
            //m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::RecipeTarget   , DEF_GC_CHARGE_DEST::LadleHopper);
          }
          else if ( 6 == BatchStat ) 
          {
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::RecipeStatus, DEF_GC_RECIPE_STATUS::DischargeStart);
          }
          else if ( 7 == BatchStat ) 
          {
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::RecipeStatus, DEF_GC_RECIPE_STATUS::WeighingCompleteUpdate);
            //m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::RecipeTarget   , DEF_GC_CHARGE_DEST::LadleHopper);
          }
          else if ( 8 == BatchStat )
          {
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::RecipeStatus, DEF_GC_RECIPE_STATUS::LastMaterialInChargingHopper);
            //m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::RecipeTarget   , DEF_GC_CHARGE_DEST::LadleHopper);
          }
          else if ( 9 == BatchStat ) 
          {
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::RecipeStatus, DEF_GC_RECIPE_STATUS::Discharged);
          }
          else if ( 50 == BatchStat )
          {
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::RecipeStatus, DEF_GC_RECIPE_STATUS::Level_1_ManualEntered);
          }
          else if ( 51 == BatchStat )
          {
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::RecipeStatus, DEF_GC_RECIPE_STATUS::Level_2_ManualEntered);
          }
          else if ( 99 == BatchStat )
          {
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::RecipeStatus, DEF_GC_RECIPE_STATUS::UnKnown);
          }
          else
          {
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorProcessingData(sMessage, "CLF_TelegramHandler::CLF_TelegramHandler()","LFL260 :: BatchStat");
          }

          m_pTelegram_Adapter->m_pIntf_OUT->setBatch(DataKey.c_str(), DATA::RecipeContent, SeqBatch);

          m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

          //********    send internal event  ***********************************************************************

          SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);
        }

        //********    End processing data  ***********************************************************************
      }// 
      else
      {
        RetValue = false;
      }

      log (TlgName + ": Finished", 3);
    }
    catch (cCBS_DBExc &e)
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::Exception& cExc) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
        Function.c_str(), TlgName.c_str());
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(),TlgName.c_str());
      RetValue = false;
    }
  }// if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
}// bool CLF_TelegramHandler::DoProcessLFL260MatHandReport(const std::string& Key, const std::string& TlgName)

bool CLF_TelegramHandler::DoProcessLFL261MatAvailibilty(const std::string& Key, const std::string& TlgName)
{
  //================  MATERIAL AVAILABILITIES   =================================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
	long PlantNo	 = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

	//-----------SRKO (JSW SMS3): To handle Bin availabilities for EAF considering EAFTappingBin(Bin for LF) and EAFBin-------------------
	bool updateEAFBin=false;
	std::string EAFPlant=DEF_GC_PLANT_DEF::EAF; 
	long EAFPlantNo=1;
	std::string EAFPurpose=DEF_GT_PURP::EAFTappingBin_Avail;
	long EAFUnitGroupNo = m_pGC_Plantgroup_Container->getUnitGroupNo(EAFPlant,EAFPlantNo);
	//-----------SRKO (JSW SMS3): To handle Bin availabilities for EAF considering EAFTappingBin(Bin for LF) and EAFBin-------------------

  std::string Function = "CLF_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo           = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL261::UnitNo);
      long ActionFlag  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL261::ActionFlag);

      CORBA::Any AnyMatCode     = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_LFL261::MatCode);
      CORBA::Any AnyMinWeight   = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_LFL261::MinWeight);
      CORBA::Any AnySource      = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_LFL261::Source);
      CORBA::Any AnySourceNo    = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_LFL261::SourceNo);

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler  ***********************************************************************

      //********    preparation telegram data   ****************************************************************

      DEF::seqString SeqMatCode;
      DEF::seqDouble SeqMinWeight;
      DEF::seqLong SeqSource;
      DEF::seqLong SeqSourceNo;

      CIntfData::FromAny(SeqMatCode,AnyMatCode);
      CIntfData::FromAny(SeqMinWeight,AnyMinWeight);
      CIntfData::FromAny(SeqSource,AnySource);
      CIntfData::FromAny(SeqSourceNo,AnySourceNo);

      //********    Convert and check telegram data  *********************************************************   

      // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
      UnitNo      = CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);
      ActionFlag  = CDataConversion::SetInvalidToDefault(ActionFlag,DEF::Inv_Long,LONG_MIN);

      RetValue = RetValue && checkValidity(TlgName, Telegram_LFL261::UnitNo,     UnitNo,     1,2);
      RetValue = RetValue && checkValidity(TlgName, Telegram_LFL261::ActionFlag, ActionFlag, 0,1);

      if ( RetValue )
      {
        //********    main telegram data   ***********************************************************************

        DataKey   = generateDataKey(TlgName);     

        checkValidity(TlgName, Telegram_LFL261::Source,     SeqSource,  0,3);   //// u153 - L1 sends Source = 0 if Material position is not used for WireFeeder telegram 
        checkValidity(TlgName, Telegram_LFL261::SourceNo,   SeqSourceNo,0,100); //// same

        std::set<std::string> PurposeList;
        std::multimap<std::string,std::string> SourcePurposeList;

        long UnitGroupNo = -1;

        // check if availabilities should be set for LF or LF_1
        // use entries in ini file
        // [MATERIALHANDLING]
        // PlantIDNames = LF_1,LF_2
        // ...
        bool UseMaterialAvailibilities = true;
        bool UseSourceAvailibilities = false;
        std::vector<std::string> PlantIDNames;
        std::vector<std::string> StaticAvailibilityMaterials;
        std::vector<std::string>::iterator itPlantIDNames;
        std::vector<std::string> Sources;
        std::vector<std::string>::iterator itSources;
        cCBS_StdInitBase::getInstance()->getEntryList("MATERIALHANDLING","PlantIDNames",PlantIDNames);
        // excluded materials which will not changed by L1
        cCBS_StdInitBase::getInstance()->getEntryList("MATERIALHANDLING","StaticAvailibilityMaterials",StaticAvailibilityMaterials);
        cCBS_StdInitBase::getInstance()->replaceWithEntry("MATERIALHANDLING","UseMaterialAvailibilities",UseMaterialAvailibilities);
        cCBS_StdInitBase::getInstance()->replaceWithEntry("MATERIALHANDLING","UseSourceAvailibilities",UseSourceAvailibilities);

        if ( UseMaterialAvailibilities )
        {
          UnitGroupNo = m_pGC_Plantgroup_Container->getUnitGroupNo(Plant,m_pGC_Plant_Container->getPlantNo(PlantId));

          if ( UseSourceAvailibilities )
          {
            cCBS_StdInitBase::getInstance()->getEntryList("MATERIALHANDLING","Sources",Sources);
          }
          // message contains ALL possible materials
          // all existing entreis in GT_MAT_PURP for given source / purpose must be removed !
          if (ActionFlag == 0)								
          { 
            for ( long i = 0 ; i < CIntfData::getLength(SeqSource) ; ++i)
            {
              long Source    = -1;
              CIntfData::getAt(Source,SeqSource,i);

              if ( SourcePurposeList.find(CDataConversion::LongToString(Source)) == SourcePurposeList.end() )
              {
                if ( Source == 1 )
                {
                  SourcePurposeList.insert( std::pair<std::string,std::string> (CDataConversion::LongToString(Source),DEF_GT_PURP::Bin_Avail));

                  // add purposes of Bin System to list that purposes will be deleted for all metarials
                  std::set<std::string>::iterator it;
                  std::set<std::string> PurposeBinSystemList;

                  m_pGT_PARAM->getKeyedValueList(Plant, m_pGC_Plant_Container->getPlantNo(PlantId), "BinSystemPurpose", 0, DEF_GC_PARAM_TYPE::SSParam, CSMC_DBData::unspecString, CSMC_DBData::unspecString, PurposeBinSystemList);

                  for ( it = PurposeBinSystemList.begin(); it != PurposeBinSystemList.end() ; ++ it )
                  {
                    SourcePurposeList.insert( std::pair<std::string,std::string> (CDataConversion::LongToString(Source),(*it)));
                  }

                }
                else if ( Source == 2 )
                {
                  SourcePurposeList.insert( std::pair<std::string,std::string> (CDataConversion::LongToString(Source),DEF_GT_PURP::Hand_Avail));
                }
                else if ( Source == 3 || Source == 4 )
                {
                  SourcePurposeList.insert( std::pair<std::string,std::string> (CDataConversion::LongToString(Source),DEF_GT_PURP::Wire_Avail));
                }
              } // if ( SourcePurposeList.find(CDataConversion::LongToString(Source)) == SourcePurposeList.end() )
            }

            std::multimap<std::string,std::string>::iterator its;
            for ( its = SourcePurposeList.begin() ; its != SourcePurposeList.end(); ++its )
            {
              for ( itSources = Sources.begin() ; itSources != Sources.end() ; ++itSources )
              {
                if ( *itSources == its->first )
                {
                  cCBS_StdInitBase::getInstance()->replaceWithEntry(*itSources,"UnitGroupNo",UnitGroupNo);
                }
              }

              if ( !StaticAvailibilityMaterials.empty() )
              {
                // functions does not commit SQL here!
                m_pGT_MAT_PURP->deleteRows(UnitGroupNo, StaticAvailibilityMaterials, its->second);
              }
              else
              {
                // functions does not commit SQL here!
                m_pGT_MAT_PURP->deleteRow(UnitGroupNo, CSMC_DBData::unspecString, its->second);
              }

              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              pEventLog->EL_MaterialAvailabilityChanged(sMessage, 0, "All", its->second.c_str());
            }

						//SRKO (JSW SMS3): Handle for EAFTappingBin--------------------------------------------------------------------
						if ( !StaticAvailibilityMaterials.empty() )
              {
                // functions does not commit SQL here!
                m_pGT_MAT_PURP->deleteRows(EAFUnitGroupNo, StaticAvailibilityMaterials, DEF_GT_PURP::EAFTappingBin_Avail);
              }
              else
              {
                // functions does not commit SQL here!
                m_pGT_MAT_PURP->deleteRow(EAFUnitGroupNo, CSMC_DBData::unspecString, DEF_GT_PURP::EAFTappingBin_Avail);
          }
						//SRKO (JSW SMS3): Handle for EAFTappingBin--------------------------------------------------------------------
          }
					

          bool doCommit = true;

          // iteration over all sequences, SeqMatCode gives counter for iterator
          for ( long i = 0 ; i < CIntfData::getLength(SeqMatCode) ; ++i)
          {
            std::string Purpose;
            std::string Source;
            std::string MatCode;
            double MinWeight    = -1.;
            double AvailWeight  = -1.;
            long lSource   = -1;
            long SourceNo  = -1;

            CIntfData::getAt(MatCode,SeqMatCode,i);
            CIntfData::getAt(MinWeight,SeqMinWeight,i);
            CIntfData::getAt(AvailWeight,SeqMinWeight,i); // we assume AvailWeight == MinWeight, L1 sends MinWeight == 0 if material is not available
            CIntfData::getAt(lSource,SeqSource,i);
            CIntfData::getAt(SourceNo,SeqSourceNo,i);

            std::string PurposeBinSystem  = CSMC_DBData::unspecString;
            std::string SourceBinSystem   = CDataConversion::LongToString(SourceNo);

            // read PurposeBinSystem from gt_param / gt_param_matrix
            m_pGT_PARAM->getKeyedValue(Plant, m_pGC_Plant_Container->getPlantNo(PlantId), "BinSystemPurpose", 0, DEF_GC_PARAM_TYPE::SSParam, SourceBinSystem, CSMC_DBData::unspecString, PurposeBinSystem);

            MinWeight = CDataConversion::SetInvalidToDefault(MinWeight,0.);

            if ( lSource == 1 )
            {
              Purpose = DEF_GT_PURP::Bin_Avail;
              Source  = DEF_GC_RECIPE_SOURCE::Bin;
							updateEAFBin=true; //SRKO: Update Bin material availabilities for EAF
            }
            else if ( lSource == 2 )
            {
              Purpose = DEF_GT_PURP::Hand_Avail;
              Source  = DEF_GC_RECIPE_SOURCE::Hand;

              // set MinWeight for Hand Additions to a valid value 
              if ( MinWeight <= 0.01 )
              {
                cCBS_StdInitBase::getInstance()->replaceWithEntry("MATERIALHANDLING","MinWeightHand",MinWeight);
              }
            }
            else if ( lSource == 3 || lSource == 4 )
            {
              Purpose = DEF_GT_PURP::Wire_Avail;
              Source  = DEF_GC_RECIPE_SOURCE::Wire;

              // wire feeder sourceno is between 0...7 but is mentioned as 1...8
              SourceNo = SourceNo + 1;
            }

            if ( !Purpose.empty() && PurposeList.find(Purpose) == PurposeList.end() )
            {
              PurposeList.insert(Purpose);
            }

            // sequence might contain empty entries
            // sequence is related to physical bin number
            if ( !MatCode.empty() && !Purpose.empty() )
            {
              log("### LFL261 Update PD_MAT_AVAIL", 3);	

              MatCode = CDataConversion::Trim(MatCode);
              log("Trimmed Value for MatCode -" + MatCode + "-",3);

              // m_pPD_MAT_AVAIL->updateOrInsertRowForMinWeight does not perform commit !
              if ( m_pPD_MAT_AVAIL->updateOrInsertRowForMinWeight(Plant, m_pGC_Plant_Container->getPlantNo(PlantId),
                                                                  Source ,SourceNo, MatCode, AvailWeight, MinWeight) )
              {
                if (ActionFlag == 1)                  // updating existing Materials only
                {
                  if ( MinWeight < 0. )                 // Material set, Weight incorrect
                  {
                    std::string Message = "LFL261 :: MatCode " + MatCode + " - MinWeight < 0";
                    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                    pEventLog->EL_ErrorProcessingData(sMessage, Function.c_str(),Message.c_str());
                  }
                  else if ( MinWeight > 0. )                 // Material set, Weight > 0 means material available
                  {
                    // we need to INSERT this Material if not already set.
                    doCommit = m_pGT_MAT_PURP->insertOrReplace(UnitGroupNo, MatCode, Purpose);
                    
                    if ( PurposeBinSystem != CSMC_DBData::unspecString )
                    {
                      m_pGT_MAT_PURP->insertOrReplace(UnitGroupNo, MatCode, PurposeBinSystem);

                      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                      pEventLog->EL_MaterialAvailabilityChanged(sMessage, 1, MatCode.c_str(), PurposeBinSystem.c_str());
                    }

                    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                    pEventLog->EL_MaterialAvailabilityChanged(sMessage, 1, MatCode.c_str(), Purpose.c_str());
                  }
                  else                                     // Material set, Weight == 0 means material not available 
                  {
                    // we need to DELETE this material if it exists.
                    if (m_pGT_MAT_PURP->deleteOnExist(UnitGroupNo, MatCode, Purpose))
                    {
                      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                      pEventLog->EL_MaterialAvailabilityChanged(sMessage, 0, MatCode.c_str(), Purpose.c_str());
                    }
                  }
                }  
                else if (ActionFlag == 0)                       // complete update 
                {
                  // complete update : delete for all materials has been done before.
                  // we need to INSERT those materials with MatWgt>0 only.
                  if ( MinWeight > 0. )
                  {
                    // m_pGT_MAT_PURP->insertRow does not perform commit !
                    doCommit = m_pGT_MAT_PURP->insertOrReplace(UnitGroupNo, MatCode, Purpose);

                    if ( PurposeBinSystem != CSMC_DBData::unspecString )
                    {
                      m_pGT_MAT_PURP->insertOrReplace(UnitGroupNo, MatCode, PurposeBinSystem);

                      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                      pEventLog->EL_MaterialAvailabilityChanged(sMessage, 1, MatCode.c_str(), PurposeBinSystem.c_str());
                    }

                    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                    pEventLog->EL_MaterialAvailabilityChanged(sMessage, 1, MatCode.c_str(), Purpose.c_str());
                  }
                }
              }
              else
              {
                cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
                sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                pEventLog->EL_DBWriteError(sMessage,"", "PD_MAT_AVAIL", "" );
              }

              if (!doCommit)break;
            } // if (!MatCode.empty()) // update/insert PD_BIN now        


						// SRKO (JSW SMS3):To handle Bin material availabilities for EAF
						// EAF Tapping materials will come from LF Bin
						// EAFBin_Avail: Materials for EAF Bin only
						// EAFTappingBin_Avail: Materials for EAF Tapping
						// REMARKS: EAF Bin materials should not match with EAF Tapping Bin materials
						//----------------------------------------------------------------------------------------------------------------------
            if ( !MatCode.empty() && !Purpose.empty() &&  lSource == 1 )
            {
				
							log("### EAL261 Update PD_MAT_AVAIL", 3);	

              MatCode = CDataConversion::Trim(MatCode);
              log("Trimmed Value for MatCode -" + MatCode + "-",3);

              // m_pPD_MAT_AVAIL->updateOrInsertRowForMinWeight does not perform commit !
              if ( m_pPD_MAT_AVAIL->updateOrInsertRowForMinWeight(EAFPlant, EAFPlantNo,
                                                                  Source ,SourceNo, MatCode, AvailWeight, MinWeight) )
              {
                if (ActionFlag == 1)                  // updating existing Materials only
                {
                  if ( MinWeight < 0. )                 // Material set, Weight incorrect
                  {
                    std::string Message = "EAL261 :: MatCode " + MatCode + " - MinWeight < 0";
                    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                    pEventLog->EL_ErrorProcessingData(sMessage, Function.c_str(),Message.c_str());
                  }
                  else if ( MinWeight > 0. )                 // Material set, Weight > 0 means material available
                  {
										
                    // we need to INSERT this Material if not already set.
                    doCommit = m_pGT_MAT_PURP->insertOrReplace(EAFUnitGroupNo, MatCode, EAFPurpose);            

                    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                    pEventLog->EL_MaterialAvailabilityChanged(sMessage, 1, MatCode.c_str(), EAFPurpose.c_str());
                  }
                  else                                     // Material set, Weight == 0 means material not available 
                  {
                    // we need to DELETE this material if it exists.
                    if (m_pGT_MAT_PURP->deleteOnExist(EAFUnitGroupNo, MatCode, EAFPurpose))
                    {
                      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                      pEventLog->EL_MaterialAvailabilityChanged(sMessage, 0, MatCode.c_str(), EAFPurpose.c_str());
                    }
                  }
                }  
                else if (ActionFlag == 0)                       // complete update 
                {
                  // complete update : delete for all materials has been done before.
                  // we need to INSERT those materials with MatWgt>0 only.
                  if ( MinWeight > 0. )
                  {
                    // m_pGT_MAT_PURP->insertRow does not perform commit !
                    doCommit = m_pGT_MAT_PURP->insertOrReplace(EAFUnitGroupNo, MatCode, EAFPurpose);

                    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                    pEventLog->EL_MaterialAvailabilityChanged(sMessage, 1, MatCode.c_str(), EAFPurpose.c_str());
                  }
                }
              }
              else
              {
                cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
                sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                pEventLog->EL_DBWriteError(sMessage,"", "PD_MAT_AVAIL", "" );
              }

							if (!doCommit)break;
						}// if ( !MatCode.empty() && !Purpose.empty() &&  lSource == 1 )
						//------------------------------------------------------------------------------------------------------------------

          }// for ( long i = 0 ; i < CIntfData::getLength(SeqMatCode) ; ++i)
          //20120810: GEPA commit/rollback moved to here: When L1 is sending an empty material list (is bad, but possible) the deletion of materials
          //          which were available before, transaction is neither finished by commit or rollback !!!

					if(updateEAFBin)//SRKO: Update Bin material availabilities for EAF
					{
						std::string From_Purp_Code_1=DEF_GT_PURP::EAFBin_Avail;
						std::string From_Purp_Code_2=DEF_GT_PURP::EAFTappingBin_Avail;
						std::string To_Purp_Code=DEF_GT_PURP::Bin_Avail;
						Plant=DEF_GC_PLANT_DEF::EAF;
						PlantNo=1;
						UnitGroupNo = m_pGC_Plantgroup_Container->getUnitGroupNo(Plant,PlantNo);
						doCommit=m_pGT_MAT_PURP->mergePurposeCodes(Plant, PlantNo,  From_Purp_Code_1, From_Purp_Code_2, To_Purp_Code);
					} 

          if (doCommit)
          {
             m_pGT_MAT_PURP->commit(); // commits all
          }
          else
          {
             m_pGT_MAT_PURP->rollback(); // rolls back all SQL statements

             CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
             sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
             pEventLog->EL_ErrorProcessingData(sMessage, Function.c_str(),"LFL261 :: DB Error");
          }
          //20120810: end
          seqStringList SeqStringList;
          std::set<std::string>::iterator it;
          for ( it = PurposeList.begin(); it != PurposeList.end(); ++it)
          {
            CIntfData::insert(SeqStringList,(*it).c_str() );
          }

          //********    Define Event *******************************************************************************

          if (doCommit)
          {
            // test item isPlantEvent = true;
            EventMessageVector.push_back( LF_EvMsg::evLFHandleUpdatePurpose);
          }

          //********    Write telegram data  ***********************************************************************
          m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),DATA::DateTime,Now.assDate());

          if (doCommit)
          {
            m_pTelegram_Adapter->m_pIntf_OUT->setStringList(DataKey.c_str(),DATA::UpdatedPurpose,SeqStringList);
          }

          m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

          //********    send internal event  ***********************************************************************

          SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,true);

          //********    End processing data  ***********************************************************************
        }
        else
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_MaterialAvailabilityUnused(sMessage);
        }
      }//  if ( checkValidity(TlgName,"ActionFlag",ActionFlag,0,1) )
      else
      {
        RetValue = false;
      }

      log (TlgName + ": Finished", 3);
    }
    catch (cCBS_DBExc &e)
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::Exception& cExc) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
        Function.c_str(), TlgName.c_str());
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(),TlgName.c_str());
      RetValue = false;
    }
  }// if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
}// bool CLF_TelegramHandler::DoProcessLFL261MatAvailibilty(const std::string& Key, const std::string& TlgName)

bool CLF_TelegramHandler::DoProcessLFL270LiqMatReport(const std::string& Key, const std::string& TlgName)
{
  //==========    L I Q U I D   M A T E R I A L    H A N D L I N G   R E P O R T     ===========================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CLF_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo   = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL270::UnitNo);
      HeatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL270::HeatId );
      TreatId  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL270::TreatId);
      LadleId  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL270::LadleId);

      long WeighingStat   = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL270::WeighingStat);
      double LiquidWeight = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_LFL270::Weight);

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler  ***********************************************************************

      //********    preparation telegram data   ****************************************************************
      
      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        //********    Convert and check telegram data  *********************************************************   

        // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
        UnitNo        = CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);
        WeighingStat  = CDataConversion::SetInvalidToDefault(WeighingStat,DEF::Inv_Long,LONG_MIN);

        checkValidity(TlgName,"UnitNo"      ,UnitNo       ,1,2);
        checkValidity(TlgName,"WeighingStat",WeighingStat ,1,7);

        //********    main telegram data   ***********************************************************************

        DataKey   = generateDataKey(HeatId);

        LadleId            = CDataConversion::Trim(LadleId);

        CLadleID LadleID;

        if ( LadleID.checkLadleIDWithDefaultType(DEF_GC_LADLE_TYPE::TeemingLadle, LadleId) )
        {
          LadleType          = LadleID.getLadleType(LadleId);
          LadleNo            = LadleID.getLadleNo(LadleId);
        }

        long WeighingType = -1;

        switch( WeighingStat )
        {
        case 1:
          WeighingType = DEF_LIQ_MAT_REPORT::LadleWeightReturnHeat;
          break;
        case 2:
          WeighingType = DEF_LIQ_MAT_REPORT::LadleTareWeightBeforeBOFTapping;
          break;
        case 3:
          WeighingType = DEF_LIQ_MAT_REPORT::LadleGrossWeightAfterBOFTapping;
          break;
        case 4:
          WeighingType = DEF_LIQ_MAT_REPORT::LadleWeightBeforeLF;
          break;
        case 5:
          WeighingType = DEF_LIQ_MAT_REPORT::LadleWeightAfterLF;
          break;
        case 6:
          WeighingType = DEF_LIQ_MAT_REPORT::LadleGrossWeightUpdateAtLF;
          break;
        case 7:
          WeighingType = DEF_LIQ_MAT_REPORT::LadleGrossWeightBeforeCasting;
          break;
        default:
          WeighingType = -1 ;
        }

        //********    Define Event *******************************************************************************

        EventMessageVector.push_back( LF_EvMsg::evLFLiqMatHandlReport);   

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey, DATA::LadleNo      ,LadleNo);
        m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey, DATA::LadleType    ,LadleType);
        m_pTelegram_Adapter->m_pIntf_OUT->setDouble (DataKey, DATA::MeasWeight   ,LiquidWeight);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey, DATA::WeighingType ,WeighingType);

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************
      }// 
      else
      {
        RetValue = false;
      }

      log (TlgName + ": Finished", 3);
    }
    catch (cCBS_DBExc &e)
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::Exception& cExc) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
        Function.c_str(), TlgName.c_str());
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(),TlgName.c_str());
      RetValue = false;
    }
  }// if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
}// bool CLF_TelegramHandler::DoProcessDummy(const std::string& Key, const std::string& TlgName)

bool CLF_TelegramHandler::DoProcessLFL281TreamentSteps(const std::string& Key, const std::string& TlgName)
{
  //==================   T R E A T M E N T   S T E P S    ====================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CLF_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo   = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LFL281::UnitNo);
      HeatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL281::HeatId );
      TreatId  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL281::TreatId);
      LadleId  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LFL281::LadleId);

      long CarNo  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL281::CarNo);
      long StepNo = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LFL281::StepNo);

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler  ***********************************************************************

      //********    preparation telegram data   ****************************************************************

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        //********    Convert and check telegram data  *********************************************************   

        // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
        UnitNo  = CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);
        CarNo   = CDataConversion::SetInvalidToDefault(CarNo,DEF::Inv_Long,LONG_MIN);  
        StepNo  = CDataConversion::SetInvalidToDefault(StepNo,DEF::Inv_Long,LONG_MIN);

        checkValidity(TlgName,"UnitNo"  ,UnitNo ,1,2);
        checkValidity(TlgName,"CarNo"   ,CarNo  ,1,2);
        checkValidity(TlgName,"StepNo"  ,StepNo ,1,8);

        //********    main telegram data   ***********************************************************************

        DataKey   = generateDataKey(HeatId);     

        std::string LadleTransferCarId = CDataConversion::LongToString(CarNo);

        LadleId            = CDataConversion::Trim(LadleId);

        CLadleID LadleID;

        if ( LadleID.checkLadleIDWithDefaultType(DEF_GC_LADLE_TYPE::TeemingLadle, LadleId) )
        {
          LadleType          = LadleID.getLadleType(LadleId);
          LadleNo            = LadleID.getLadleNo(LadleId);
        }

        //********    Define Event *******************************************************************************

        EventMessageVector.push_back( LF_EvMsg::evLFPhaseReport);

        switch( StepNo )    //Add the according message
        {
        case 1:
          EventMessageVector.push_back(LF_EvMsg::evLFInitialHeating);
          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::PhaseProcess,DEF_LF_PHASES::HeatingInitial); 
          break;
        case 2:
          EventMessageVector.push_back( LF_EvMsg::evLFMainHeating);
          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::PhaseProcess,DEF_LF_PHASES::HeatingMain); 
          break;
        case 3:
          EventMessageVector.push_back (LF_EvMsg::evLFFinalHeating);
          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::PhaseProcess,DEF_LF_PHASES::HeatingFinal); 
          break;
        case 4:
          EventMessageVector.push_back( LF_EvMsg::evLFTemperatureHold);
          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::PhaseProcess,DEF_LF_PHASES::HeatingTempHold); 
          break;
        case 5:
          EventMessageVector.push_back (LF_EvMsg::evLFSoftStirring);
          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::PhaseProcess,DEF_LF_PHASES::SoftStirring);
          break;
        case 6:
          EventMessageVector.push_back (LF_EvMsg::evLFCooling);
          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::PhaseProcess,DEF_LF_PHASES::Cooling);
          break;
        case 7:
          EventMessageVector.push_back (LF_EvMsg::evLFCleanlinessStirring);
          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::PhaseProcess,DEF_LF_PHASES::CleanStirring);
          break;
        case 8:
          EventMessageVector.push_back (LF_EvMsg::evLFSlagBreaking);
          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::PhaseProcess,DEF_LF_PHASES::Preparation);
          break;
        default:
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorProcessingData(sMessage, Function.c_str(),"LFL281 :: StepNo");
        }

        //********    Write telegram data  ***********************************************************************
        m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),DATA::DateTime      ,Now.assDate());
        m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey.c_str(),DATA::PhaseNoProcess,0);

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::LadleTransferCarId ,LadleTransferCarId);
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::LadleType          ,LadleType);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::LadleNo            ,LadleNo);

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************
      }// if ( checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId) )
      else
      {
        RetValue = false;
      }

      log (TlgName + ": Finished", 3);
    }
    catch (cCBS_DBExc &e)
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::Exception& cExc) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
        Function.c_str(), TlgName.c_str());
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(),TlgName.c_str());
      RetValue = false;
    }
  }// if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
}// bool CLF_TelegramHandler::DoProcessLFL281TreamentSteps(const std::string& Key, const std::string& TlgName)

/* satk 25-05-2018
bool CLF_TelegramHandler::DoProcessMotorMaintenance(const std::string& Key, const std::string& TlgName)
{
	const long 	BoosterFan_ID = 42;
	const long 	HydPresPump1_ID = 43;
	const long 	HydPresPump2_ID = 44;
	const long 	HydCircuPump1_ID = 45;
	const long 	HydCircuPump2_ID = 46;
	const long 	LFDiscBelt_ID = 47;
	const long 	BeltConyFafa_ID = 48;
	const long 	EAFDiscBelt_ID = 49;
	const long 	FurnBrker_ID = 50;

	long UnitNo = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(),Telegram_LFL290::UnitNo);
	std::string PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
  long PlantNo = m_pGC_Plant_Container->getPlantNo(PlantId);

	long    BoosterFan  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_LFL290::BoosterFan);
	CORBA::Any    HydPresPump  = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(), Telegram_LFL290::HydPresPump);
	CORBA::Any    HydCircuPump  = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(), Telegram_LFL290::HydCircuPump);

	long    LFDiscBelt  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_LFL290::LFDiscBelt);
	long    BeltConyFafa  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_LFL290::BeltConyFafa);
	long    EAFDiscBelt  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_LFL290::EAFDiscBelt);
	long    FurnBrker  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_LFL290::FurnBrker);

	bool RetValue = true;

	RetValue = RetValue && updateMotorData(BoosterFan_ID,PlantNo, BoosterFan);

	//HydPresPump
	DEF::seqLong *longHydPresPumpSeq;
	if( HydPresPump >>= longHydPresPumpSeq)
	{
		long Length = longHydPresPumpSeq->length();
			for (long idx=0; idx < Length; idx ++ ) 
			{
				std::stringstream tempStr;
				long condition;
				tempStr << (*longHydPresPumpSeq)[idx];
				tempStr >> condition;

				if(idx == 0)
				RetValue = RetValue && updateMotorData(HydPresPump1_ID,PlantNo, condition);
				if(idx == 1)
				RetValue = RetValue && updateMotorData(HydPresPump2_ID,PlantNo, condition);
			}
	}

	//HydCircuPump
	DEF::seqLong *longHydCircuPumpSeq;
	if( HydCircuPump >>= longHydCircuPumpSeq)
	{
		long Length = longHydCircuPumpSeq->length();
			for (long idx=0; idx < Length; idx ++ ) 
			{
				std::stringstream tempStr;
				long condition;
				tempStr << (*longHydCircuPumpSeq)[idx];
				tempStr >> condition;

				if(idx == 0)
				RetValue = RetValue && updateMotorData(HydCircuPump1_ID,PlantNo, condition);
				if(idx == 1)
				RetValue = RetValue && updateMotorData(HydCircuPump2_ID,PlantNo, condition);
			}
	}

	RetValue = RetValue && updateMotorData(LFDiscBelt_ID,PlantNo, LFDiscBelt);
	RetValue = RetValue && updateMotorData(BeltConyFafa_ID,PlantNo, BeltConyFafa);
	RetValue = RetValue && updateMotorData(EAFDiscBelt_ID,PlantNo, EAFDiscBelt);
	RetValue = RetValue && updateMotorData(FurnBrker_ID,PlantNo, FurnBrker);

	if (RetValue)
		CDH_IN_Task::getInstance()->getStdConnection()->commit();
	else
		CDH_IN_Task::getInstance()->getStdConnection()->rollback();

	return true;
}


bool CLF_TelegramHandler::updateMotorData(long MotorID,long PlantNo, long MotorStrart)
{
	  std::string Function = "CLF_TelegramHandler::updateMotorData";
		std::string TlgName = "LFL290";
		cCBS_ODBC_DBError lastError;

		CDateTime Now;
		bool RetValue = true;
		try
		{
			if(m_pREPORT_MOTOR_ENTRY->selectByMOTORID(MotorID,PlantNo))
			{
				CDateTime startTime = m_pREPORT_MOTOR_ENTRY->getSTART_TIME(1);
				CDateTime stopTime = m_pREPORT_MOTOR_ENTRY->getSTOP_TIME(1);

				if(MotorStrart == 1 && stopTime != CSMC_DBData::unspecDate)
				{
					m_pREPORT_MOTOR_ENTRY->setMOTORID(MotorID);
					m_pREPORT_MOTOR_ENTRY->setSTART_TIME(Now);
					m_pREPORT_MOTOR_ENTRY->setPLANT_NO(PlantNo);

					RetValue = RetValue && m_pREPORT_MOTOR_ENTRY->insert();
				}
				else if(MotorStrart == 0 && stopTime == CSMC_DBData::unspecDate)
				{
					RetValue = RetValue && m_pREPORT_MOTOR_ENTRY->updateOrInsert(MotorID,startTime,PlantNo,Now,false,lastError);
				}
			}
			else
			{
				if(MotorStrart == 1)
				{
					m_pREPORT_MOTOR_ENTRY->setMOTORID(MotorID);
					m_pREPORT_MOTOR_ENTRY->setSTART_TIME(Now);
					m_pREPORT_MOTOR_ENTRY->setPLANT_NO(PlantNo);

					RetValue = RetValue && m_pREPORT_MOTOR_ENTRY->insert();
				}
			}
		}
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
			RetValue = false;
    }
    catch(CORBA::SystemException& sExc) 
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,sExc._name(), Function.c_str(), TlgName.c_str());
      RetValue = false;
    }
    catch(CORBA::Exception& cExc) 
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(), Function.c_str(), TlgName.c_str());
      RetValue = false;
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(), TlgName.c_str());
      RetValue = false;
    }

	return RetValue;
}
*/
void CLF_TelegramHandler::handleEventLog(const string& Message,const std::string& HeatID,const std::string& TreatID,const std::string& PlantID,const std::string& DataKey)
{
  CDateTime now;
	
  CSMC_EventLogLF *pEventLog = CSMC_EventLogLFController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  
    if ( Message == LF_EvMsg::evLFHeatAnnouncement )
    {  
      pEventLog->EL_HeatAnnouncement(sMessage,HeatID.c_str(),TreatID.c_str(),PlantID.c_str(),
                                     m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::LadleTransferCarId).c_str(),
                                    (m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::LadleType) + 
                                    CDataConversion::IntToString(m_pTelegram_Adapter->m_pIntf_OUT->getLong(DataKey,DATA::LadleNo))     ).c_str() );
    }

    else if ( Message == LF_EvMsg::evLFHeatAnnouncementOffline )
    {
      pEventLog->EL_HeatAnnouncementOffline(sMessage,HeatID.c_str(),TreatID.c_str(),PlantID.c_str(),
                                     m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::LadleTransferCarId).c_str(),
                                    (m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::LadleType) + 
                                     CDataConversion::IntToString(m_pTelegram_Adapter->m_pIntf_OUT->getLong(DataKey,DATA::LadleNo))     ).c_str() );
    }

    else if ( Message == LF_EvMsg::evLFHeatCancellation )
    {
      pEventLog->EL_HeatCancellation(sMessage,HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
    }
    else if ( Message == LF_EvMsg::evLFHeatDeparture )
    {
      pEventLog->EL_HeatDeparture(sMessage,HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
    }
    else if ( Message == LF_EvMsg::evLFHeatStart )
    {
      pEventLog->EL_HeatStart(sMessage,HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
    }
    else if ( Message == LF_EvMsg::evLFHeatEnd )
    {
      pEventLog->EL_HeatEnd(sMessage,HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
    }

    else if ( Message == LF_EvMsg::evLFDelayStatus )
    {
      CDateTime StartTime, EndTime;
      StartTime << m_pTelegram_Adapter->m_pIntf_OUT->getDate(DataKey.c_str(),DATA::DelayStartDate);
      EndTime << m_pTelegram_Adapter->m_pIntf_OUT->getDate(DataKey.c_str(),DATA::DelayEndDate);

      pEventLog->EL_DelayStatus(sMessage,
        m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::DelayPlant).c_str(),
        m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::DelayCode).c_str(),
        StartTime.asString().c_str(),
        EndTime.asString().c_str(),
        m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::DelayDescription).c_str()      );
    }
    else if ( Message == LF_EvMsg::evLFChangeAimData )
    {
      CDateTime TreatEndAimTime;
      TreatEndAimTime << m_pTelegram_Adapter->m_pIntf_OUT->getDate(DataKey.c_str(),DATA::TreatEndAim);

      pEventLog->EL_ChangeAimData(sMessage,
        CDataConversion::SetInvalidToDefault(m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::SteelGradeCode),"-").c_str(),
        CDataConversion::SetInvalidToDefault(m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::TempAim),"-").c_str(),
        CDataConversion::SetInvalidToDefault(TreatEndAimTime,"-").c_str(),
        CDataConversion::SetInvalidToDefault(m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::AimWeight),"-").c_str());
    }
    else if ( Message == LF_EvMsg::evLFSteelGradeChanged )
    {
      std::string SteelGrade  = m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey, DATA::SteelGradeCode);

      pEventLog->EL_SteelGradeChanged(sMessage,SteelGrade.c_str());
    }
    else if ( Message == LF_EvMsg::evLFChangeProdPracPointerElec )
    {
      pEventLog->EL_ChangeProdPracPointerElec(sMessage,
        m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::ProdPracPointer).c_str());
    }
    else if ( Message == LF_EvMsg::evLFChangeProdPracPointerParameter )
    {
      pEventLog->EL_ChangeProdPracPointerParameter(sMessage,
        m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::ProdPracPointer).c_str());
    }
    else if ( Message == LF_EvMsg::evLFChangeProdPracPointerRestriction )
    {
      pEventLog->EL_ChangeProdPracPointerRestriction(sMessage,
        m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::ProdPracPointer).c_str());
    }
    else if ( Message == LF_EvMsg::evLFChangeProdPracPointerStirring )
    {
      pEventLog->EL_ChangeProdPracPointerStirring(sMessage,
        m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::ProdPracPointer).c_str());
    }
    else if ( Message == LF_EvMsg::evLFFinalHeating )
    {
      pEventLog->EL_FinalHeating(sMessage);
    }
    else if ( Message == LF_EvMsg::evLFInitialHeating )
    {
      pEventLog->EL_InitialHeating(sMessage);
    }
    else if ( Message == LF_EvMsg::evLFMainHeating )
    {
      pEventLog->EL_MainHeating(sMessage);
    }
    else if ( Message == LF_EvMsg::evLFCreateTreatmentID )
    {
      pEventLog->EL_CreateTreatmentID(sMessage );
    }
    else if ( Message == LF_EvMsg::evLFSteelSampleTaken )
    {
      pEventLog->EL_SteelSampleTaken(sMessage,"","","LF" );
    }
    else if ( Message == LF_EvMsg::evLFSlagSampleTaken )
    {
      pEventLog->EL_SlagSampleTaken(sMessage,"","","LF" );
    }
    else if ( Message == LF_EvMsg::evLFTempMeasurement )
    {
      pEventLog->EL_TempMeasurement(sMessage,CDataConversion::DoubleToString(m_pTelegram_Adapter->m_pIntf_OUT->getDouble(DataKey,DATA::MeasTemp)).c_str(),-1,m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::LadleTransferCarId).c_str() );
    }		
    else if ( Message == LF_EvMsg::evLFCeloxMeasurement )
    {
      pEventLog->EL_CeloxMeasurement(sMessage,CDataConversion::DoubleToString(m_pTelegram_Adapter->m_pIntf_OUT->getDouble(DataKey,DATA::MeasCarbonConc)).c_str(),CDataConversion::DoubleToString(m_pTelegram_Adapter->m_pIntf_OUT->getDouble(DataKey,DATA::MeasAlConc)).c_str(),"",CDataConversion::DoubleToString(m_pTelegram_Adapter->m_pIntf_OUT->getDouble(DataKey,DATA::MeasTemp)).c_str(),CDataConversion::DoubleToString(m_pTelegram_Adapter->m_pIntf_OUT->getDouble(DataKey,DATA::MeasO2Conc)).c_str() );
    }		
    else if ( Message == LF_EvMsg::evLFSlagCeloxMeasurement )
    {
      pEventLog->EL_SlagCeloxMeasurement(sMessage,CDataConversion::DoubleToString(m_pTelegram_Adapter->m_pIntf_OUT->getDouble(DataKey,DATA::MeasFeOConc)).c_str(),CDataConversion::DoubleToString(m_pTelegram_Adapter->m_pIntf_OUT->getDouble(DataKey,DATA::MeasMnOConc)).c_str());
    }
    else if ( Message == LF_EvMsg::evLFUpdateAimTemperature )
    {
      pEventLog->EL_ChangeAimData(sMessage,CDataConversion::DoubleToString(m_pTelegram_Adapter->m_pIntf_OUT->getDouble(DataKey,DATA::TempAim)).c_str(),"");
    }
    else if ( Message == LF_EvMsg::evLFUpdateAimDepartureTime )
    {
      CDateTime TreatEndAimTime;
      TreatEndAimTime << m_pTelegram_Adapter->m_pIntf_OUT->getDate(DataKey.c_str(),DATA::TreatEndAim);
      pEventLog->EL_ChangeAimData(sMessage,"",CDataConversion::SetInvalidToDefault(TreatEndAimTime,"-").c_str());
    }
    else if ( Message == LF_EvMsg::evLFSetComputerMode )
    {
			seqComputerModes ActSeq         =  CIntfData::ToCORBAType(m_pTelegram_Adapter->m_pIntf_OUT->getComputerModes(DataKey.c_str(),DATA::ComputerModes)); 
      sComputerMode ActStruct ; 
      long seqLength = CIntfData::getLength(ActSeq);

      for(int i=0;i<seqLength;i++)
      {
        CIntfData::getAt(ActStruct, ActSeq,i);

        if ( ActStruct.Status == DEF_GC_COMP_STATUS::AutoMode )
        {
          pEventLog->EL_SetComputerModeAutomatic(sMessage,m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::LadleTransferCarId).c_str(),ActStruct.Device);
        }
        else if ( ActStruct.Status == DEF_GC_COMP_STATUS::ComputerDynamicMode )
        {
          pEventLog->EL_SetComputerModeDynamic(sMessage,m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::LadleTransferCarId).c_str(),ActStruct.Device);
        }
        else if ( ActStruct.Status == DEF_GC_COMP_STATUS::ComputerPatternMode )
        {
          pEventLog->EL_SetComputerModePattern(sMessage,m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::LadleTransferCarId).c_str(),ActStruct.Device);
        }
        else if ( ActStruct.Status == DEF_GC_COMP_STATUS::ManualMode )
        {
          pEventLog->EL_SetComputerModeManual(sMessage,m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::LadleTransferCarId).c_str(),ActStruct.Device);
        }
			}
    }
    else if ( Message == LF_EvMsg::evLFTransferCarPositionChanged )
    {
      pEventLog->EL_TransferCarPositionChanged(sMessage,m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::LadleTransferCarId).c_str(),m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::LadleCarPosition).c_str(),"");
    }		
    else if ( Message == LF_EvMsg::evLFGantrySwungOut )
    {
      pEventLog->EL_GantryOutTreatmentPosition(sMessage);
    }		
    else if ( Message == LF_EvMsg::evLFMaintenance )
    {
      pEventLog->EL_GantryInMaintenancePosition(sMessage);
    }
    else if ( Message == LF_EvMsg::evLFGantrySwungIn )
    {
      pEventLog->EL_GantryInTreatmentPosition(sMessage,m_pTelegram_Adapter->m_pIntf_OUT->getLong(DataKey,DATA::GantryPosIn),m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::LadleTransferCarId).c_str());
			
    }				
    else if ( Message == LF_EvMsg::evLFRoofArrivesInDownPosition )
    {
      pEventLog->EL_RoofArrivesInDownPosition(sMessage,"");
    }		
    else if ( Message == LF_EvMsg::evLFRoofArrivesInUpPosition )
    {
      pEventLog->EL_RoofArrivesInUpPosition(sMessage,"");
    }		
    else if ( Message == LF_EvMsg::evLFUpdatePlantStatus )
    {
      // no log function is there
    }		
    else if ( Message == LF_EvMsg::evLFFurnaceBreakerOn )
    {
      pEventLog->EL_FurnaceBreakerOn(sMessage);
    }		
    else if ( Message == LF_EvMsg::evLFFurnaceBreakerOff )
    {
      pEventLog->EL_FurnaceBreakerOff(sMessage);
    }		
    else if ( Message == LF_EvMsg::evLFPowerOn )
    {
      pEventLog->EL_PowerOn(sMessage);
    }		
    else if ( Message == LF_EvMsg::evLFPowerOff )
    {
      pEventLog->EL_PowerOff(sMessage);
    }		
    else if ( Message == LF_EvMsg::evLFTapChangeStart )
    {
      pEventLog->EL_TapChangeStart(sMessage,CDataConversion::DoubleToString(m_pTelegram_Adapter->m_pIntf_OUT->getLong(DataKey,DATA::VoltTapNo)).c_str(),CDataConversion::DoubleToString(m_pTelegram_Adapter->m_pIntf_OUT->getLong(DataKey,DATA::ElectrodRegCurve)).c_str());
    }		
    else if ( Message == LF_EvMsg::evLFTapChangeFinished )
    {
      pEventLog->EL_TapChangeFinished(sMessage,CDataConversion::DoubleToString(m_pTelegram_Adapter->m_pIntf_OUT->getLong(DataKey,DATA::VoltTapNo)).c_str(),CDataConversion::DoubleToString(m_pTelegram_Adapter->m_pIntf_OUT->getLong(DataKey,DATA::ElectrodRegCurve)).c_str());
    }		
    else if ( Message == LF_EvMsg::evLFImpCurveChanged )
    {
      pEventLog->EL_TapChangeFinished(sMessage,CDataConversion::DoubleToString(m_pTelegram_Adapter->m_pIntf_OUT->getLong(DataKey,DATA::VoltTapNo)).c_str(),CDataConversion::DoubleToString(m_pTelegram_Adapter->m_pIntf_OUT->getLong(DataKey,DATA::ElectrodRegCurve)).c_str());
    }				
    else if ( Message == LF_EvMsg::evLFElectrodesInOperatingPosition )
    {
      pEventLog->EL_ElectrodesInOperatingPosition(sMessage);
    }		
    else if ( Message == LF_EvMsg::evLFElectrodesOutOperatingPosition || Message == LF_EvMsg::evLFElectrodeHydraulicSystemInhibitRequest ||  Message == LF_EvMsg::evLFElectrodeHydraulicSystemReleaseRequest)
    {
       // no log function is there
    }		
    else if ( Message == LF_EvMsg::evLFCyclicMeasurement )
    {
			//nothing is recorded for cyclic measurement
    }		
    else if ( Message == LF_EvMsg::evLFBottomStirringEnd )
    {
      pEventLog->EL_BottomStirringEnd(sMessage,m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::LadleTransferCarId).c_str(),m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::StirringGasType).c_str(),"");
    }		
    else if ( Message == LF_EvMsg::evLFBottomStirringStart )
    {
      pEventLog->EL_BottomStirringStart(sMessage,m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::LadleTransferCarId).c_str(),m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::StirringGasType).c_str(),"");
    }		
    else if ( Message == LF_EvMsg::evLFBottomStirringByPassOff )
    {
      pEventLog->EL_BottomStirringByPassOff(sMessage,m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::LadleTransferCarId).c_str(),"");
    }		
    else if ( Message == LF_EvMsg::evLFBottomStirringByPassOn )
    {
      pEventLog->EL_BottomStirringByPassOn(sMessage,m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::LadleTransferCarId).c_str(),"");
    }				
    else if ( Message == LF_EvMsg::evLFEmergencyLanceStirringEnd || Message == LF_EvMsg::evLFEmergencyLanceStirringStart)
    {
       // no log function is there
    }		
    else if ( Message == LF_EvMsg::evLFParameterUpdate )
    {
      pEventLog->EL_ParameterUpdate(sMessage,m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::ParamName).c_str(),m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::ParamValue).c_str());
    }		
    else if ( Message == LF_EvMsg::evLFMaterialHandlingReport )
    {
      seqBatch RecipeBatch = CIntfData::ToCORBAType(m_pTelegram_Adapter->m_pIntf_OUT->getBatch(DataKey.c_str(),DATA::RecipeContent));

      long seqLength = CIntfData::getLength(RecipeBatch);
      for(int i=0;i<seqLength;i++)
      {
        sBatch sRecipeElement;
        CIntfData::getAt(sRecipeElement, RecipeBatch,i);
        pEventLog->EL_MaterialHandlingReport(sMessage,
                                           m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::LadleTransferCarId).c_str(),
                                           m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::RecipeName).c_str(),
                                           m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::RecipeSource).c_str(),
                                           m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::RecipeStatus).c_str(),
                                           sRecipeElement.MatCode,
                                           sRecipeElement.Mass);
      }
    }				
    else if ( Message == LF_EvMsg::evLFHandleUpdatePurpose )
    {
      pEventLog->EL_HandleUpdatePurpose(sMessage);
    }		
    else if ( Message == LF_EvMsg::evLFPhaseReport || Message == LF_EvMsg::evLFTemperatureHold || Message == LF_EvMsg::evLFSlagBreaking)
    {
      // no log function is there
    }		
    else if ( Message == LF_EvMsg::evLFSoftStirring )
    {
      pEventLog->EL_SoftStirring(sMessage);
    }		
    else if ( Message == LF_EvMsg::evLFCooling )
    {
      pEventLog->EL_CoolingStirring(sMessage);
    }		
    else if ( Message == LF_EvMsg::evLFCleanlinessStirring )
    {
      pEventLog->EL_CleanlinessStirring(sMessage);
    }		
		else
		{
			//
		}
}