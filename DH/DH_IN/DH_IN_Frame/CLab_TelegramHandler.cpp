// Copyright (C) 2006 SMS Demag AG

#include "Telcom_In_s.hh"
#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"

#include "CDH_IN_Task.h"
#include "CDataConversion.h"

#include "DEF_GC_MEASUREMENT_TYPE.h"
#include "DEF_GC_MEASUREMENT_NAME.h"
#include "DEF_GC_MEASUREMENT_ORIGIN.h"
#include "DEF_GC_SAMPLEMODE.h"
#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_SAMPLELOC.h"

#include "CLab_TelegramHandler.h"


//##ModelId=4582CFC1028E
CLab_TelegramHandler::CLab_TelegramHandler()
{
  try
  {
    cCBS_StdConnection* pConnection = CDH_IN_Task::getInstance()->getStdConnection();

    if (pConnection)
    {      
      m_pGC_Plant_Container         = new CGC_Plant_Container(pConnection);
      m_pHeatDataConverter          = new CHeatDataConverter(pConnection);
    }
    else
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,"", "CLab_TelegramHandler","No database connection");

      // to guaranty EL_ExceptionCaught to be sent to CBS service
      Sleep(3000);

      // terminate programm in case of starting up without getting connection to database
      exit(EXIT_FAILURE);
    }
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"", "CLab_TelegramHandler","");
    throw;
  }
}

//##ModelId=4582CFC5032B
CLab_TelegramHandler::~CLab_TelegramHandler()
{
  std::stringstream strFunction;
  std::stringstream strAction;

  try
  {
    strFunction << "CLab__TelegramHandler::~CLab__TelegramHandler()";

    if (m_pGC_Plant_Container)        {delete m_pGC_Plant_Container;        m_pGC_Plant_Container = 0;}
    if (m_pHeatDataConverter)         {delete m_pHeatDataConverter;         m_pHeatDataConverter = 0;}

    strAction << "Delete DBClasses instances ";
  }
  catch (cCBS_DBExc &e)
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), strFunction.str().c_str(), strAction.str().c_str()); 
  }
  catch(CORBA::SystemException& sExc) 
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(), strFunction.str().c_str(), strAction.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(), strFunction.str().c_str(), strAction.str().c_str());
  }
  catch(...)
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", strFunction.str().c_str(),strAction.str().c_str()); 
  }

}
void CLab_TelegramHandler::fillAnalysisSequence(seqAnalysis &SeqAnalysis, const std::string& Element, double Concentration)
{
  if ( !Element.empty() && Element != DEF::Inv_String && Concentration >= 0. )
  {
    sAnalysis   Analysis;

    Analysis.Element        = Element.c_str();
    Analysis.Concentration  = Concentration;

    CIntfData::insert(SeqAnalysis,Analysis);
  }
}



//##ModelId=458692160327
bool CLab_TelegramHandler::doOnComplete(const std::string& Key, const std::string& TlgName)
{

  //message list used to store the dispatch message
  bool RetValue = true;
  std::stringstream strFunction;
  std::stringstream strAction;
  try
  {
    //doOnCompleteDelete(Key,TlgName);

    strFunction << "CLab_TelegramHandler::doOnComplete;";
    strFunction <<" TlgName: " << TlgName;

    EventMessageVector.clear();

    if(TlgName == "LABSMC01")
      RetValue =  DoProcessLABSMC01IsAlive(Key,TlgName); 
    else if(TlgName == "LABSMC02")
      RetValue =  DoProcessLABSMC02SteelAnalysis(Key,TlgName); 
    else if(TlgName == "LABSMC03")
      RetValue =  DoProcessLABSMC03SlagAnalysis(Key,TlgName);
    else 
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),"CLab_TelegramHandler::doOnComplete: Unknown TlgName");

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

  return RetValue;
}

void CLab_TelegramHandler::SendEventMessage(const std::string& Key, 
                                           const std::string& TlgName,
                                           const std::string& DataKey,
                                           const std::string& PlantId,
                                           const std::string& HeatId,
                                           const std::string& TreatId,
                                           bool isPlantEvent)
{
  //Send all event messages, that are present in EventMessageVector
  std::stringstream strFunction;
  std::stringstream strAction;

  std::vector <std::string>::iterator EventMsgToSend;

  try
  {
    strFunction << "CLab_TelegramHandler::SendEventMessage";
    for ( EventMsgToSend = EventMessageVector.begin(); EventMsgToSend != EventMessageVector.end();++EventMsgToSend)
    {
      string LogMessage = TlgName + " Data handled!";
      log(LogMessage,3);
      // sending event to event channel 
      CEventMessage Message(m_pTelegram_Adapter->m_SenderName,
        m_pTelegram_Adapter->m_DestinationName,
        *EventMsgToSend,
        PlantId,
        "",
        "",
        isPlantEvent,
        HeatId,
        TreatId,
        DataKey);      

      strAction << "sending event:" << TlgName;

      if( !m_EventHandler.dispatchEvent("","",Message) )
      {
        log(" Send Message" + Message.getDataKey() + "failed",2);
      }
    }
  }
  catch (cCBS_DBExc &e)
  {
    m_pTelegram_Adapter->m_pIntf_IN->showContent(TlgName,1);
    m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,1);
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      strFunction.str().c_str(), strAction.str().c_str()); 
  }
  catch(CORBA::SystemException& sExc) 
  {
    m_pTelegram_Adapter->m_pIntf_IN->showContent(TlgName,1);
    m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,1);
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      strFunction.str().c_str(), strAction.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
    m_pTelegram_Adapter->m_pIntf_IN->showContent(TlgName,1);
    m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,1);
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      strFunction.str().c_str(), strAction.str().c_str());
  }
  catch(...)
  {
    m_pTelegram_Adapter->m_pIntf_IN->showContent(TlgName,1);
    m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,1);
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      strFunction.str().c_str(),strAction.str().c_str()); 
  }
}


bool CLab_TelegramHandler::DoProcessLABSMC01IsAlive(const std::string& Key, const std::string& TlgName)
{
  //=======================     Watch Dog   ============================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; // we are LF

  //------------ This variables are used as buffer ------------------

  std::string Function = "CLab_TelegramHandler::DoProcess" + TlgName;

  try
  {
    if ( m_pTelegram_Adapter && 
      m_pTelegram_Adapter->m_pIntf_IN && 
      m_pTelegram_Adapter->m_pIntf_OUT )
    {

      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      //Read the m_PlantID and generate the string. m_PlantID is defined in all telegrams

      //********    Convert and check telegram data  ***********************************************************

      //********    Write telegram data  ***********************************************************************

      // setting data to output interface

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
    pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", "CLab_TelegramHandler::doOnComplete()",TlgName.c_str());
    RetValue = false;
  }

  return RetValue;
}// bool CLab_TelegramHandler::DoProcessLABSMC03IsAlive(const std::string& Key, const std::string& TlgName)

bool CLab_TelegramHandler::DoProcessLABSMC02SteelAnalysis(const std::string& Key, const std::string& TlgName)
{
  //=====================  S T E E L    A N A L Y S I S  ========================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo;
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; // we are LF

  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CLab_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo       = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LABSMC02::UnitNo);
      CustHeatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LABSMC02::HeatId );
      CustTreatId  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LABSMC02::TreatId);

      CORBA::Any SampleTime       = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key,Telegram_LABSMC02::SampleTime);
      CORBA::Any TimeOfAnalysis   = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key,Telegram_LABSMC02::TimeOfAnalysis);
      std::string SampleLocation  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LABSMC02::SampleLocation);
      long SampleNo               = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_LABSMC02::SampleNo);
      long SampleUsable           = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_LABSMC02::SampleUseable);

      double Anl_C              = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_C);
      double Anl_Si             = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_Si);
      double Anl_Mn             = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_Mn);
      double Anl_P              = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_P);
      double Anl_S              = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_S);

      double Anl_Al             = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_Al);
      double Anl_Al_S           = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_Al_S);
      double Anl_Cu             = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_Cu);
      double Anl_Cr             = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_Cr);
      double Anl_Mo             = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_Mo);

      double Anl_Ni             = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_Ni);  
      double Anl_V              = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_V);
      double Anl_Ti             = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_Ti);
      double Anl_Nb             = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_Nb);
      double Anl_Ca             = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_Ca);

      double Anl_Co             = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_Co);
      double Anl_Pb             = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_Pb);
      double Anl_W              = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_W);
      double Anl_Mg             = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_Mg);
      double Anl_Ce             = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_Ce);

      double Anl_B              = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_B);
      double Anl_As             = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_As);
      double Anl_Sn             = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_Sn);
      double Anl_Bi             = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_Bi);
      double Anl_Sb             = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_Sb);

      double Anl_Zr             = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_Zr);
      double Anl_O              = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_O);
      double Anl_N              = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_N);
      double Anl_H              = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_H);
      double Anl_Zn             = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_Zn);
      double Anl_Fe             = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC02::Anl_Fe);

      SampleLocation            = CDataConversion::Trim(SampleLocation);

      std::string SampleLocationL2;
      std::string SampleLocationPlant   = SampleLocation.substr(0,1);
      long        SampleLocationPlantNo = CDataConversion::StringToLong(SampleLocation.substr(1,1));

      if ( m_pGC_Plant_Container )
      {
        if ( SampleLocationPlant == "E" )
        {
          SampleLocationL2 = DEF_GC_SAMPLELOC::EAF;

          m_pGC_Plant_Container->setPlant(DEF_GC_PLANT_DEF::EAF);
          PlantId = m_pGC_Plant_Container->getL2PlantID(SampleLocationPlantNo);
          Plant   = m_pGC_Plant_Container->getPlant(PlantId);
        }
        else if ( SampleLocationPlant == "L" )
        {
          SampleLocationL2 = DEF_GC_SAMPLELOC::LF;

          m_pGC_Plant_Container->setPlant(DEF_GC_PLANT_DEF::LF);
          PlantId = m_pGC_Plant_Container->getL2PlantID(SampleLocationPlantNo);
          Plant   = m_pGC_Plant_Container->getPlant(PlantId);
        }
      }
      else
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorPointerHandling(sMessage, Function.c_str(),"m_pGC_Plant_Container not instatiated !");
      }
      //********    reset statushandler  ***********************************************************************

      //********    Convert and check telegram data  ***********************************************************  

      // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
      CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);

      DEF::seqString LocationValidator;
      CIntfData::insert(LocationValidator,"E1");
      CIntfData::insert(LocationValidator,"L1");
      CIntfData::insert(LocationValidator,"C1");

      checkValidity(TlgName,"SampleLocation",SampleLocation,LocationValidator,"");
      checkValidity(TlgName,"SampleNo"      ,SampleNo     ,1,99);
      checkValidity(TlgName,"SampleUsable" ,SampleUsable,0,1);
      

      seqAnalysis SeqAnalysis;

      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::C    ,Anl_C    );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::Si   ,Anl_Si   );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::Mn   ,Anl_Mn   );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::P    ,Anl_P    );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::S    ,Anl_S    );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::Al   ,Anl_Al   );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::Al_S ,Anl_Al_S );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::Cu   ,Anl_Cu   );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::Cr   ,Anl_Cr   );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::Mo   ,Anl_Mo   );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::Ni   ,Anl_Ni   );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::V    ,Anl_V    );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::Ti   ,Anl_Ti   );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::Nb   ,Anl_Nb   );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::Ca   ,Anl_Ca   );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::Co   ,Anl_Co   );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::Pb   ,Anl_Pb   );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::W    ,Anl_W    );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::Mg   ,Anl_Mg   );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::Ce   ,Anl_Ce   );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::B    ,Anl_B    );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::As   ,Anl_As   );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::Sn   ,Anl_Sn   );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::Bi   ,Anl_Bi   );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::Sb   ,Anl_Sb   );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::Zr   ,Anl_Zr   );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::O2   ,Anl_O    );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::N2   ,Anl_N    );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::H2   ,Anl_H    );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::Zn   ,Anl_Zn   );               
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::Fe   ,Anl_Fe   );               


      if ( CheckCustomerData(TlgName, CustHeatId, CustTreatId, HeatId, TreatId, Plant) )
      {
        DataKey   = generateDataKey(HeatId);

        //********    Define Event *******************************************************************************

        if ( SampleLocationPlant == "E" )
        {
          EventMessageVector.push_back(EAF_EvMsg::evEAFSteelAnalysisReceived);
        }
        else if ( SampleLocationPlant == "L" )
        {
          EventMessageVector.push_back(LF_EvMsg::evLFSteelAnalysisReceived);
        }

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setDate   (DataKey.c_str(), DATA::DateTime         ,CDateTime(TimeOfAnalysis).assDate());

        m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey,         DATA::CustHeatIdUser   ,CustHeatId);
        m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey,         DATA::CustTreatIdUser  ,CustTreatId);
        m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey,         DATA::PlantID          ,PlantId);

        m_pTelegram_Adapter->m_pIntf_OUT->setDate   (DataKey.c_str(), DATA::SteelSampleTime  ,CDateTime(SampleTime).assDate() );
        m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey,         DATA::SampleLocation   ,SampleLocationL2);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,         DATA::SampleNo         ,SampleNo);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,         DATA::SampleOrigin     ,DEF_GC_MEASUREMENT_ORIGIN::Measured);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,         DATA::SampleMode       ,DEF_GC_SAMPLEMODE::automatic);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,         DATA::SampleType       ,DEF_GC_MEASUREMENT_TYPE::Steel);

        if(1 == SampleUsable)
        {
          m_pTelegram_Adapter->m_pIntf_OUT->setLong (DataKey,         DATA::SampleUsable, DEF_GEN_STATES::Yes);
        }
        else
        {
          m_pTelegram_Adapter->m_pIntf_OUT->setLong (DataKey,         DATA::SampleUsable, DEF_GEN_STATES::No);
        }

        m_pTelegram_Adapter->m_pIntf_OUT->setAnalysis(DataKey.c_str(),DATA::SteelMeasAnalysis  ,SeqAnalysis);


        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,HeatId,TreatId,false);

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
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", "CLab_TelegramHandler::doOnComplete()",TlgName.c_str());
      RetValue = false;
    }
  }// // if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
}// bool CLab_TelegramHandler::DoProcessLABSMC02SteelAnalysis(const std::string& Key, const std::string& TlgName)

bool CLab_TelegramHandler::DoProcessLABSMC03SlagAnalysis(const std::string& Key, const std::string& TlgName)
{
  //=====================  S L A G    A N A L Y S I S  ========================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo;
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; // we are LF

  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CLab_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo       = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LABSMC03::UnitNo);
      CustHeatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LABSMC03::HeatId );
      CustTreatId  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LABSMC03::TreatId);

      CORBA::Any SampleTime       = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key,Telegram_LABSMC03::SampleTime);
      CORBA::Any TimeOfAnalysis   = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key,Telegram_LABSMC03::TimeOfAnalysis);
      std::string SampleLocation  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_LABSMC03::SampleLocation);
      long SampleNo               = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_LABSMC03::SampleNo);
      long SampleUsable          = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_LABSMC03::SampleUseable);

      double Anl_CaO           = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC03::Anl_CaO);                         
      double Anl_SiO2          = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC03::Anl_SiO2);                        
      double Anl_P2O5          = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC03::Anl_P2O5);                        
      double Anl_FeO           = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC03::Anl_FeO);                         
      double Anl_Fe2O3         = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC03::Anl_Fe2O3);                       

      double Anl_Fe3O4         = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC03::Anl_Fe3O4);                       
      double Anl_S             = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC03::Anl_S);                           
      double Anl_Al2O3         = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC03::Anl_Al2O3);                       
      double Anl_MgO           = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC03::Anl_MgO);                         
      double Anl_MnO           = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC03::Anl_MnO);                         

      double Anl_Cr2O3         = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC03::Anl_Cr2O3);                       
      double Anl_MoO           = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC03::Anl_MoO);                         
      double Anl_NiO           = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC03::Anl_NiO);                         
      double Anl_V2O5          = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC03::Anl_V2O5);                        
      double Anl_TiO2          = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC03::Anl_TiO2);                        

      double Anl_TiFe          = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC03::Anl_TiFe);                        
      double Anl_CaC2          = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC03::Anl_CaC2);                        
      double Anl_CaF2          = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC03::Anl_CaF2);                        
      double Anl_CaS           = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC03::Anl_CaS);                         
      double Anl_Fe_X          = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_LABSMC03::Anl_Fe_X);                        

      SampleLocation            = CDataConversion::Trim(SampleLocation);

      std::string SampleLocationL2;
      std::string SampleLocationPlant   = SampleLocation.substr(0,1);
      long        SampleLocationPlantNo = CDataConversion::StringToLong(SampleLocation.substr(1,1));

      if ( m_pGC_Plant_Container )
      {
        if ( SampleLocationPlant == "E" )
        {
          SampleLocationL2 = DEF_GC_SAMPLELOC::EAF;

          m_pGC_Plant_Container->setPlant(DEF_GC_PLANT_DEF::EAF);
          PlantId = m_pGC_Plant_Container->getL2PlantID(SampleLocationPlantNo);
          Plant   = m_pGC_Plant_Container->getPlant(PlantId);
        }
        else if ( SampleLocationPlant == "L" )
        {
          SampleLocationL2 = DEF_GC_SAMPLELOC::LF;

          m_pGC_Plant_Container->setPlant(DEF_GC_PLANT_DEF::LF);
          PlantId = m_pGC_Plant_Container->getL2PlantID(SampleLocationPlantNo);
          Plant   = m_pGC_Plant_Container->getPlant(PlantId);
        }
      }
      else
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorPointerHandling(sMessage, Function.c_str(),"m_pGC_Plant_Container not instatiated !");
      }



      //********    reset statushandler  ***********************************************************************

      //********    Convert and check telegram data  ***********************************************************  

      // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
      CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);

      DEF::seqString LocationValidator;
      CIntfData::insert(LocationValidator,"E1");
      CIntfData::insert(LocationValidator,"L1");
      CIntfData::insert(LocationValidator,"C1");

      checkValidity(TlgName,"SampleLocation",SampleLocation,LocationValidator,"");
      checkValidity(TlgName,"SampleNo"      ,SampleNo     ,1,99);
      checkValidity(TlgName,"SampleUsable" ,SampleUsable,0,1);


      seqAnalysis SeqAnalysis;

      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::CaO  ,Anl_CaO  );              
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::SiO2 ,Anl_SiO2 );              
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::P2O5 ,Anl_P2O5 );              
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::FeO  ,Anl_FeO  );              
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::Fe2O3,Anl_Fe2O3);              
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::Fe3O4,Anl_Fe3O4);              
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::S    ,Anl_S    );              
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::Al2O3,Anl_Al2O3);              
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::MgO  ,Anl_MgO  );              
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::MnO  ,Anl_MnO  );              
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::Cr2O3,Anl_Cr2O3);              
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::MoO  ,Anl_MoO  );              
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::NiO  ,Anl_NiO  );              
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::V2O5 ,Anl_V2O5 );              
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::TiO2 ,Anl_TiO2 );              
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::TiFe ,Anl_TiFe );              
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::CaC2 ,Anl_CaC2 );              
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::CaF2 ,Anl_CaF2 );              
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::CaS  ,Anl_CaS  );              
      fillAnalysisSequence(SeqAnalysis,DEF_GC_MEASUREMENT_NAME::Fe_X ,Anl_Fe_X );              


      if ( CheckCustomerData(TlgName, CustHeatId, CustTreatId, HeatId, TreatId, Plant) )
      {
        DataKey   = generateDataKey(HeatId);

        //********    Define Event *******************************************************************************

        if ( SampleLocationPlant == "E" )
        {
          EventMessageVector.push_back(EAF_EvMsg::evEAFSlagAnalysisReceived);
        }
        else if ( SampleLocationPlant == "L" )
        {
          EventMessageVector.push_back(LF_EvMsg::evLFSlagAnalysisReceived);
        }

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setDate   (DataKey.c_str(), DATA::DateTime         ,CDateTime(TimeOfAnalysis).assDate());

        m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey,         DATA::CustHeatIdUser   ,CustHeatId);
        m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey,         DATA::CustTreatIdUser  ,CustTreatId);
        m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey,         DATA::PlantID          ,PlantId);

        m_pTelegram_Adapter->m_pIntf_OUT->setDate   (DataKey.c_str(), DATA::SteelSampleTime  ,CDateTime(SampleTime).assDate() );
        m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey,         DATA::SampleLocation   ,SampleLocationL2);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,         DATA::SampleNo         ,SampleNo);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,         DATA::SampleOrigin     ,DEF_GC_MEASUREMENT_ORIGIN::Measured);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,         DATA::SampleMode       ,DEF_GC_SAMPLEMODE::automatic);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,         DATA::SampleType       ,DEF_GC_MEASUREMENT_TYPE::Slag);

        if(1 == SampleUsable)
        {
          m_pTelegram_Adapter->m_pIntf_OUT->setLong (DataKey,         DATA::SampleUsable,DEF_GEN_STATES::Yes);
        }
        else
        {
          m_pTelegram_Adapter->m_pIntf_OUT->setLong (DataKey,         DATA::SampleUsable, DEF_GEN_STATES::No);
        }

        m_pTelegram_Adapter->m_pIntf_OUT->setAnalysis(DataKey.c_str(),DATA::SteelMeasAnalysis  ,SeqAnalysis);


        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,HeatId,TreatId,false);

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
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", "CLab_TelegramHandler::doOnComplete()",TlgName.c_str());
      RetValue = false;
    }
  }// // if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
}// bool CLab_TelegramHandler::DoProcessLABSMC03SlagAnalysis(const std::string& Key, const std::string& TlgName)

//
//    if   (TlgName == "LABSMC02")              //Steel or slag Sample Taken on LF.
//    {
//      try
//      {
//        RetValue = true;
//        log ("### Begin to handle LABSMC02", 2);
//
//        sCustHeatNo   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_LABSMC02::HeatId);
//        sCustHeatNo = sCustHeatNo.substr(0,6);
//        sCustTreatID  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_LABSMC02::TreatId);
//        lPlant = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_LABSMC02::UnitNo);
//        std::string sSampleLocation = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_LABSMC02::SampleLocation);
//
//        if(sSampleLocation.substr(0,1) == "E")//EAF
//        {
//          EventMessageString = EAF_EvMsg::evEAFSteelAnalysisReceived;
//          ActPlant = DEF_GC_PLANT_DEF::EAF;
//        }
//        else if(sSampleLocation.substr(0,1) == "L")//LF
//        {
//          EventMessageString = LF_EvMsg::evLFSteelAnalysisReceived;
//          ActPlant = DEF_GC_PLANT_DEF::LF;
//        }
//        else if(sSampleLocation.substr(0,1) == "V")//VD
//        {
//          EventMessageString = VD_EvMsg::evVDSteelAnalysisReceived;
//          //ActPlant = DEF_GC_PLANT_DEF::VD;
//        }
//        else
//        {
//          log("WARNING: LABSMC02: Invalid SampleLocation neither EAF nor LF and VD");
//        }
//
//        m_pHeatDataConverter->getInternalHeatData(sCustHeatNo, sCustTreatID, HeatNo,TreatId,ActPlant); //chang outside code(string) to inside code(string)
//        DataKey   = generateDataKey(HeatNo);   
//
//        long SmplCounter = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LABSMC02::SampleNo);
//        CORBA::Any datetime = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_LABSMC02::SampleTime);
//        CDateTime DT(datetime);  
//        
//        long SmplUsesable = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_LABSMC02::SampleUsable);
//
//        CORBA::Any TimeOfAnalysis = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_LABSMC02::TimeOfAnalysis);
//        CDateTime DTAnalysis(TimeOfAnalysis); 
//
//        DEF::seqString SteelAnalysisDB;
//        getSteelAnalysisStream(SteelAnalysisDB);          
//        seqAnalysis     seqSteelAnl;
//        seqSteelAnl.length(SteelAnalysisDB.length());
//        for (unsigned int i = 0; i < SteelAnalysisDB.length(); i ++)
//        {            
//          seqSteelAnl[i].Element        = SteelAnalysisDB[i];
////          seqSteelAnl[i].Concentration  = (*DoubleSampleAnlSeq)[i];
//        }
//        m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::SampleType, DEF_GC_MEASUREMENT_TYPE::Steel);
//        m_pTelegram_Adapter->m_pIntf_OUT->setAnalysis(DataKey.c_str(), DATA::SteelMeasAnalysis, seqSteelAnl); 
//        m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),DATA::SteelSampleTime,DT.assDate ());
//
//        // setting data to output interface
//        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::HeatID,HeatNo);
//        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::TreatID,TreatId);
//        m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::SampleNo, SmplCounter);
//
//        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::SampleLocation,sSampleLocation);
//
//
//        if(0 == SmplUsesable)
//        {
//          m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::SampleUsable,DEF_GEN_STATES::No);
//        }
//        else if (1 == SmplUsesable)
//        {
//          m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::SampleUsable, DEF_GEN_STATES::Yes);
//        }
//        else
//        {
//          log("WARNING: LABSMC02: Invalid SmplUsesable neither 1 nor 0");
//        }
//        
//        // show interface content
//        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey, 4);
//
//        //trigger event regarding Sample Location and sample type
//
//        //if(SampleType == 1)//1:Steel
//        {
//          if(sSampleLocation.substr(0,1) == "E")//EAF
//          {
//            EventMessageString = EAF_EvMsg::evEAFSteelAnalysisReceived;
//          }
//          else if(sSampleLocation.substr(0,1) == "L")//LF
//          {
//            EventMessageString = LF_EvMsg::evLFSteelAnalysisReceived;
//          }
//          else if(sSampleLocation.substr(0,1) == "V")//VD
//          {
//            EventMessageString = VD_EvMsg::evVDSteelAnalysisReceived;
//          }
//          else
//          {
//            log("WARNING: LABSMC02: Invalid SampleLocation neither EAF nor LF and VD");
//          }
//        }
//        EventMessageVector.push_back(EventMessageString);
//      }
//      catch (...)
//      {
//        ;//nothing
//      }      
//
//    }
//  }
//  //		if (!EventMessageString.empty())
//  for ( EventMsgToSend = EventMessageVector.begin(); EventMsgToSend != EventMessageVector.end();++EventMsgToSend)
//  {
//
//    std::string LogMessageString = TlgName + " LAB handled!";
//    log(LogMessageString);
//
//    CEventMessage Message(m_pTelegram_Adapter->m_SenderName,
//      m_pTelegram_Adapter->m_DestinationName,
//      *EventMsgToSend,//EventMessageString,
//      m_PlantID,
//      "",
//      "",
//      false,
//      HeatNo,
//      TreatId,
//      DataKey);
//    RetValue = m_EventHandler.dispatchEvent("","",Message);
//  }
//  EventMessageVector.clear();  
//  return RetValue;
//}
//
