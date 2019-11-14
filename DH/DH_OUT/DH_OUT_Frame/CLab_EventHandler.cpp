// Copyright (C) 2006 SMS Demag AG Germany

#include "Telcom_Out_s.hh"
#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"

#include "DEF_GC_PHASE.h"
#include "CDH_OUT_Task.h"
#include "CSMC_DataProvider_Impl.h"
#include "cCBS_StdDB_Task.h"
#include "CLab_EventHandler.h"
#include "CDataConversion.h"

//##ModelId=4582C0A50345
CLab_EventHandler::CLab_EventHandler()
: m_pDM_Interface(0)
, m_pDM_InterfaceProduct(0)
//, m_pPD_HEAT_DATA(0)
//, m_pPP_HEAT_PLANT(0)
//, m_pHD_GRADE(0)
//, m_pHD_GRADE_ANL(0) 
//,m_pHeatDataConverter(0)
//, m_pGC_Plant_Container(0)
{
  m_pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();
  
  m_SenderName = cCBS_StdInitBase::getInstance()->m_ServerName;
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage","SenderName",m_SenderName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage","DestinationName",m_DestinationName);

  std::string TaskName = CDH_OUT_Task::getInstance()->getTaskName();
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"SenderName",m_SenderName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"DestinationName",m_DestinationName);

  cCBS_StdConnection* pConnection = CDH_OUT_Task::getInstance()->getStdConnection();

  if (pConnection)
  {
    //    m_pPP_HEAT_PLANT      = new CPP_HEAT_PLANT      (pConnection);
    //    m_pPD_ANL = new CPD_ANL(pConnection);
    //    m_pPD_ANL_ENTRY = new CPD_ANL_ENTRY(pConnection); 
    // m_pHD_GRADE    = new  CHD_GRADE(pConnection);
    // m_pHD_GRADE_ANL = new CHD_GRADE_ANL(pConnection);  
    m_pHeatDataConverter      = new CHeatDataConverter(pConnection);
    m_pGC_Plant_Container     = new CGC_Plant_Container(pConnection);
    m_pGT_GRADE_SAMPLE_FLAG   = new CGT_GRADE_SAMPLE_FLAG(pConnection);
    m_pPD_HEAT_DATA           = new CPD_HEAT_DATA(pConnection);
  }

  else
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"", "CLab_EventHandler","No database connection");

    // to guaranty EL_ExceptionCaught to be sent to CBS service
    Sleep(3000);

    // terminate programm in case of starting up without getting connection to database
    exit(EXIT_FAILURE);
  }

}

CLab_EventHandler::~CLab_EventHandler()
{  
  if(m_pGC_Plant_Container)             {delete m_pGC_Plant_Container;              m_pGC_Plant_Container = 0;}
  if(m_pGT_GRADE_SAMPLE_FLAG)           {delete m_pGT_GRADE_SAMPLE_FLAG;            m_pGT_GRADE_SAMPLE_FLAG = 0;}
  if(m_pPD_HEAT_DATA)                   {delete m_pPD_HEAT_DATA;                    m_pPD_HEAT_DATA = 0;}

//  if(m_pPP_HEAT_PLANT) delete m_pPP_HEAT_PLANT;  
//  if(m_pHD_GRADE) delete m_pHD_GRADE;
//  if(m_pHD_GRADE_ANL) delete m_pHD_GRADE_ANL;
//  if(m_pHeatDataConverter) delete m_pHeatDataConverter;
//  if(m_pGC_Plant_Container) delete m_pGC_Plant_Container;
}

void CLab_EventHandler::getSteelAnalysisStream(DEF::seqString& SteelAnalysisDB)
{
  CIntfData::insert(SteelAnalysisDB, "C");
  CIntfData::insert(SteelAnalysisDB, "Si");
  CIntfData::insert(SteelAnalysisDB, "Mn");
  CIntfData::insert(SteelAnalysisDB, "P");
  CIntfData::insert(SteelAnalysisDB, "S");
  CIntfData::insert(SteelAnalysisDB, "Al");
  CIntfData::insert(SteelAnalysisDB, "Al_S");  
  CIntfData::insert(SteelAnalysisDB, "Cu");
  CIntfData::insert(SteelAnalysisDB, "Cr");
  CIntfData::insert(SteelAnalysisDB, "Mo");
  CIntfData::insert(SteelAnalysisDB, "Ni");
  CIntfData::insert(SteelAnalysisDB, "V");
  CIntfData::insert(SteelAnalysisDB, "Ti");
  CIntfData::insert(SteelAnalysisDB, "Nb");
  CIntfData::insert(SteelAnalysisDB, "Ca");
  CIntfData::insert(SteelAnalysisDB, "Co");
  CIntfData::insert(SteelAnalysisDB, "Pb");
  CIntfData::insert(SteelAnalysisDB, "W");
  CIntfData::insert(SteelAnalysisDB, "Mg");
  CIntfData::insert(SteelAnalysisDB, "Ce");
  CIntfData::insert(SteelAnalysisDB, "B");
  CIntfData::insert(SteelAnalysisDB, "As");
  CIntfData::insert(SteelAnalysisDB, "Sn"); 
  CIntfData::insert(SteelAnalysisDB, "Bi");
  CIntfData::insert(SteelAnalysisDB, "Sb");
  CIntfData::insert(SteelAnalysisDB, "Zr");
  CIntfData::insert(SteelAnalysisDB, "O2");
  CIntfData::insert(SteelAnalysisDB, "N2");
  CIntfData::insert(SteelAnalysisDB, "H2");
  CIntfData::insert(SteelAnalysisDB, "Al_I");
  CIntfData::insert(SteelAnalysisDB, "Zn");
  CIntfData::insert(SteelAnalysisDB, "Fe");
}

void CLab_EventHandler::getSlagAnalysisStream(DEF::seqString& SlagAnalysisDB)
{  
  CIntfData::insert(SlagAnalysisDB, "CaO");
  CIntfData::insert(SlagAnalysisDB, "SiO2");
  CIntfData::insert(SlagAnalysisDB, "P2O5");
  CIntfData::insert(SlagAnalysisDB, "FeO");
  CIntfData::insert(SlagAnalysisDB, "Fe2O3");
  CIntfData::insert(SlagAnalysisDB, "Fe3O4");
  CIntfData::insert(SlagAnalysisDB, "S_X");
  CIntfData::insert(SlagAnalysisDB, "Al2O3");
  CIntfData::insert(SlagAnalysisDB, "MgO");
  CIntfData::insert(SlagAnalysisDB, "MnO");
  CIntfData::insert(SlagAnalysisDB, "Cr2O3");
  CIntfData::insert(SlagAnalysisDB, "MoO");
  CIntfData::insert(SlagAnalysisDB, "NiO");
  CIntfData::insert(SlagAnalysisDB, "V2O5");
  CIntfData::insert(SlagAnalysisDB, "TiO2");
  CIntfData::insert(SlagAnalysisDB, "TiFe");
  CIntfData::insert(SlagAnalysisDB, "CaC2");
  CIntfData::insert(SlagAnalysisDB, "CaF2");
  CIntfData::insert(SlagAnalysisDB, "CaS");
  CIntfData::insert(SlagAnalysisDB, "Fe_X");  
}



//##ModelId=4587AB4C00D5
bool CLab_EventHandler::handleEvent(CEventMessage& evMessage)
{
  // We return true if and only if we are the receiver of the event,
  // and the event message is one of the defined message Id's to be handled here.
  // Note that by design, the Return value does not imply correctness of the handling
  // but only the fact of the handling!

  bool RetValue = true;

  CEventMessage ActEvent(evMessage);
  std::string ActMessage = ActEvent.getMessage();

  if (ActMessage == EAF_EvMsg::evEAFSteelSampleTaken ) //IndicateSampleTaken
  {
    RetValue = provideData_SteelSampleTakenEAF (ActEvent);
  }
  else if (ActMessage == EAF_EvMsg::evEAFSlagSampleTaken ) //IndicateSampleTaken
  {
    RetValue = provideData_SlagSampleTakenEAF (ActEvent);
  }
  else if (ActMessage == AOD_EvMsg::evAODSteelSampleTaken ) //IndicateSampleTaken
  {
    RetValue = provideData_SteelSampleTakenAOD (ActEvent);
  }
  else if (ActMessage == AOD_EvMsg::evAODSlagSampleTaken ) //IndicateSampleTaken
  {
    RetValue = provideData_SlagSampleTakenAOD (ActEvent);
  }
  else if (ActMessage == LF_EvMsg::evLFSteelSampleTaken ) //IndicateSampleTaken
  {
    RetValue = provideData_SteelSampleTakenLF (ActEvent);
  }
  else if (ActMessage == LF_EvMsg::evLFSlagSampleTaken ) //IndicateSampleTaken
  {
    RetValue = provideData_SlagSampleTakenLF (ActEvent);
  }
  else
  {
    RetValue = false;
  }

  if ( RetValue )
  {
    std::string Item = CDataConversion::FillRight(evMessage.getMessage(),50);
    CDH_OUT_Task::getInstance()->setStateDetails(Item ," was handled at " + CDateTime().asString(), 0);
  }

  return RetValue;
}
void CLab_EventHandler::SendEventMessage(const std::string& TlgName, const std::string& DataKey, const std::string& PlantID, const std::string& HeatID, const std::string& TreatID, const std::string& OrderID)
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

//##ModelId=45E6FFC503E7
bool CLab_EventHandler::provideData_SteelSampleTakenEAF(CEventMessage &Event)
{
  bool RetValue = true; // assume success

  //read the data from Event
  std::string HeatID            = Event.getHeatID();
  std::string TreatID           = Event.getTreatID();
  std::string ProductID         = Event.getProductID();
  std::string OrderID           = Event.getOrderID();
  std::string DataKey           = Event.getDataKey();
  std::string PlantID           = Event.getPlantID();

  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyLab;
  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID);

  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));

  std::string TlgName;
  std::string Function;
  std::string tmp;
  std::string ProdOrderID;
  std::string SteelGradeCode;
  std::string Workstation;
  std::string SampleLocation;
  std::string ActPhase;
  std::string ActPhaseResNo;

  CDateTime SampleTime;

  long SampleNo;
  long OESFlag        = 0;
  long OES_CSFlag     = 0;
  long OES_CS_ONFlag  = 0;
  long OES_ONFlag     = 0;
  long CSFlag         = 0;
  long CS_ONFlag      = 0;
  long CS_ONHFlag     = 0;
  long ONFlag         = 0;
  long ONHFlag        = 0;
  long UnitNo         = m_pGC_Plant_Container->getPlantNo(PlantID);

  bool bResult = 0;
        
  TlgName   = "SMCLAB02";
  Function  = "CLab_EventHandler::provideData_SMCLAB02SteelSampleTakenEAF";

  try
  {
    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();
    m_pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::EVENT);
    m_pDM_InterfaceProduct = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    if (m_pDM_Interface && m_pTelcom_Interface)
    {
      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);


      DataKeyLab = pTelcom_Interface->generateDataKey(TlgName);
      SteelGradeCode = m_pPD_HEAT_DATA->getSteelGradeCode(HeatID,TreatID,Plant);
      ProdOrderID = m_pPD_HEAT_DATA->getPRODORDERID_ACT(1);

      ActPhase = m_pDM_InterfaceProduct->getString(Event.getProductID().c_str(), DATA::PhaseAct);


      if(ActPhase == DEF_GC_PHASE::Refining)
      {
        if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"SamplingFlagAfterMelting") == 1)
        {
          //SamplingFlagAfterMelting
        }
      }
      else if (ActPhase == DEF_GC_PHASE::Tapped)
      {
        if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"SamplingFlagAfterDeslag") == 1)
        {
          //SamplingFlagAfterDeslag
        }
      }
      else
      {
        log("No analysis for the EAF SteelSampleTaken found for "+ ActPhase,3);
      }
      
      // Prepare Customer's Heat and Treatment Id for sending instead of internal data.

      if( m_pHeatDataConverter &&  m_pHeatDataConverter->getCustHeatData(HeatID,TreatID,CustHeatID,CustTreatID,Plant) )
      {
        CustHeatID    = CDataConversion::Trim(CustHeatID);
        CustTreatID   = CDataConversion::Trim(CustTreatID); 
      } // else there is not much we can do about it


      SampleLocation  = m_pDM_Interface->getString(Event.getDataKey().c_str(),DATA::SampleLocation);
      SampleTime      = m_pDM_Interface->getDate(Event.getDataKey().c_str(),DATA::SteelSampleTime);

      // Sample Time regularly is not provided if the SampleTaken event comes from HMI instead of L1.
      // Provide "now" as default.

      if   (SampleTime == CDateTime::InvalidDateTime() )
      {
        CDateTime now;
        SampleTime = now;
      }
      SampleNo        = m_pDM_Interface->getLong(Event.getDataKey().c_str(),DATA::SampleNo);

      //if((12 - tmp.length()) > 0) //insert spaces at the end of SteelGradeCode.
      //{
      //    std::string SteelGradeCodeWithSpaces;
      //    std::stringstream strNewcode;
      //    strNewcode << tmp << setw(10 - tmp.length()) << setfill(' ') << "";            
      //    SteelGradeCodeWithSpaces = strNewcode.str();          
      //    tmp = SteelGradeCodeWithSpaces;
      //    //SteelGradeCode = tmp + SteelGradeCode;
      //}

      // truncate data to fit telegram length
        
      CustHeatID            = CDataConversion::CheckLengthAndTruncate(CustHeatID          ,10);
      CustTreatID           = CDataConversion::CheckLengthAndTruncate(CustTreatID         ,2);
      ProdOrderID       = CDataConversion::CheckLengthAndTruncate(ProdOrderID     ,10);
      SteelGradeCode    = CDataConversion::CheckLengthAndTruncate(SteelGradeCode  ,12);
      Workstation       = CDataConversion::CheckLengthAndTruncate(Workstation     ,20);
      //SampleTime      = CDataConversion::CheckLengthAndTruncate(SampleTime      ,4);
      SampleLocation    = CDataConversion::CheckLengthAndTruncate(SampleLocation  ,2);
      //SampleNo        = CDataConversion::CheckLengthAndTruncate(SampleNo        ,4);



      //********    Write telegram data  ***********************************************************************
      //pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::UnitNo,            1l); //UnitNo);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB02::HeatId,            CustHeatID);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB02::TreatId,           CustTreatID);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB02::ProdOrderId,       ProdOrderID);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB02::SteelGradeCode,    SteelGradeCode );
      pTelcom_Interface->setAny     ( DataKeyLab, Telegram_SMCLAB02::SampleTime,        SampleTime.asCORBAAny());
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB02::SampleLocation,    SampleLocation);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::SampleNo,          SampleNo);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB02::Workstation,       Workstation);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::OESFlag,           OESFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::OES_CSFlag,        OES_CSFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::OES_CS_ONFlag,     OES_CS_ONFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::OES_ONFlag,        OES_ONFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::CSFlag,            CSFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::CS_ONFlag,         CS_ONFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::CS_ONHFlag,        CS_ONHFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::ONFlag,            ONFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::ONHFlag,           ONHFlag);
            
      //********    Dispatch event ***********************************************************************
      SendEventMessage(TlgName,DataKeyLab,L1PlantID,HeatID,TreatID,OrderID);

    }
    else
    {
      // no Telcom-Interface (unlikely error case)
      RetValue=false;
    }
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
      "CDH_LAB_OUTModelResultWrapper::provideData_SMCLAB02SteelSampleTaken(CEventMessage &Event)","Reading DM Interface Data");
    RetValue=false;
  }
  return RetValue;
}

bool CLab_EventHandler::provideData_SteelSampleTakenLF(CEventMessage &Event)
{
  bool RetValue = true; // assume success

  //read the data from Event
  std::string HeatID            = Event.getHeatID();
  std::string TreatID           = Event.getTreatID();
  std::string ProductID         = Event.getProductID();
  std::string OrderID           = Event.getOrderID();
  std::string DataKey           = Event.getDataKey();
  std::string PlantID           = Event.getPlantID();

  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyLab;
  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID);
  std::string TlgName;
  std::string Function;
  std::string tmp;
  std::string ProdOrderID;
  std::string SteelGradeCode;
  std::string Workstation;
  std::string SampleLocation;
  std::string ActPhase;
  std::string ActPhaseResNo;

  CDateTime SampleTime;

  long SampleNo;
  long OESFlag        = 0;
  long OES_CSFlag     = 0;
  long OES_CS_ONFlag  = 0;
  long OES_ONFlag     = 0;
  long CSFlag         = 0;
  long CS_ONFlag      = 0;
  long CS_ONHFlag     = 0;
  long ONFlag         = 0;
  long ONHFlag        = 0;
  long UnitNo         = m_pGC_Plant_Container->getPlantNo(PlantID);

  bool bResult = 0;
  
  TlgName = "SMCLAB02";
  Function = "CLab_EventHandler::provideData_SMCLAB02SteelSampleTakenLF";


  try
  {
    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();
    m_pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::EVENT);
    m_pDM_InterfaceProduct = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    if (m_pDM_Interface && m_pTelcom_Interface)
    {
      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);

      DataKeyLab      = pTelcom_Interface->generateDataKey(TlgName);
      SteelGradeCode  = m_pPD_HEAT_DATA->getSteelGradeCode(HeatID,TreatID,Plant);
      ProdOrderID     = m_pPD_HEAT_DATA->getPRODORDERID_ACT(1);

      ActPhase = m_pDM_InterfaceProduct->getString(Event.getProductID().c_str(), DATA::PhaseAct);

      if(ActPhase == DEF_GC_PHASE::Preparation)
      {
        //SamplingFlagBeforeHeating
      }
      else if(ActPhase == DEF_GC_PHASE::Adjusting)
      {
        if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"SamplingFlagDuringHeating") == 1)
        {
          if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"CS_SamplingFlagDuringHeating") == 1)
          {
            if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"ON_SamplingFlagDuringHeating") == 1)
            {
              if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"H_SamplingFlagDuringHeating") == 1)
              {
                CS_ONHFlag = 1;
              }
              else
              {
                CS_ONFlag = 1;
              }
            }
            else
            {
              CSFlag = 1;
            }
          }
          if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"ON_SamplingFlagDuringHeating") == 1)
          {
            if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"H_SamplingFlagDuringHeating") == 1)
            {
              ONHFlag = 1;
            }
            else
            {
              ONFlag = 1;
            }
          }
        }
      }
      else if(ActPhase == DEF_GC_PHASE::CleanStirring)
      {
        if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"SamplingFlagBeforeRefining") == 1)
        {
          if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"CS_SamplingFlagforeRefining") == 1)
          {
            if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"ON_SamplingFlagforeRefining") == 1)
            {
              if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"H_SamplingFlagforeRefining") == 1)
              {
                CS_ONHFlag = 1;
              }
              else
              {
                CS_ONFlag = 1;
              }
            }
            else
            {
              CSFlag = 1;
            }
          }
          if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"ON_SamplingFlagforeRefining") == 1)
          {
            if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"H_SamplingFlagforeRefining") == 1)
            {
              ONHFlag = 1;
            }
            else
            {
              ONFlag = 1;
            }
          }
        }
      }
      else
      {
        log("No analysis for the LF SampleTaken found for "+ ActPhase,3);
      }

      // Prepare Customer's Heat and Treatment Id for sending instead of internal data.

      if( m_pHeatDataConverter &&  m_pHeatDataConverter->getCustHeatData(HeatID,TreatID,CustHeatID,CustTreatID,Plant) )
      {
        CustHeatID    = CDataConversion::Trim(CustHeatID);
        CustTreatID   = CDataConversion::Trim(CustTreatID); 
      } // else there is not much we can do about it


      SampleLocation  = m_pDM_Interface->getString(Event.getDataKey().c_str(),DATA::SampleLocation);
      SampleTime      = m_pDM_Interface->getDate(Event.getDataKey().c_str(),DATA::SteelSampleTime);
      // Sample Time regularly is not provided if the SampleTaken event comes from HMI instead of L1.
      // Provide "now" as default.

      if   (SampleTime == CDateTime::InvalidDateTime() )
      {
        CDateTime now;
        SampleTime = now;
      }

      SampleNo        = m_pDM_Interface->getLong(Event.getDataKey().c_str(),DATA::SampleNo);

      //if((12 - tmp.length()) > 0) //insert spaces at the end of SteelGradeCode.
      //{
      //    std::string SteelGradeCodeWithSpaces;
      //    std::stringstream strNewcode;
      //    strNewcode << tmp << setw(10 - tmp.length()) << setfill(' ') << "";            
      //    SteelGradeCodeWithSpaces = strNewcode.str();          
      //    tmp = SteelGradeCodeWithSpaces;
      //    //SteelGradeCode = tmp + SteelGradeCode;
      //}

      // truncate data to fit telegram length
        
      CustHeatID          = CDataConversion::CheckLengthAndTruncate(CustHeatID          ,10);
      CustTreatID         = CDataConversion::CheckLengthAndTruncate(CustTreatID         ,2);
      ProdOrderID     = CDataConversion::CheckLengthAndTruncate(ProdOrderID     ,10);
      SteelGradeCode  = CDataConversion::CheckLengthAndTruncate(SteelGradeCode  ,12);
      Workstation     = CDataConversion::CheckLengthAndTruncate(Workstation     ,20);
      //SampleTime      = CDataConversion::CheckLengthAndTruncate(SampleTime      ,4);
      SampleLocation  = CDataConversion::CheckLengthAndTruncate(SampleLocation  ,2);
      //SampleNo        = CDataConversion::CheckLengthAndTruncate(SampleNo        ,4);



      //********    Write telegram data  ***********************************************************************
      //pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::UnitNo,            UnitNo);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB02::HeatId,            CustHeatID);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB02::TreatId,           CustTreatID);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB02::ProdOrderId,       ProdOrderID);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB02::SteelGradeCode,    SteelGradeCode );
      pTelcom_Interface->setAny     ( DataKeyLab, Telegram_SMCLAB02::SampleTime,        SampleTime.asCORBAAny());
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB02::SampleLocation,    SampleLocation);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::SampleNo,          SampleNo);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB02::Workstation,       Workstation);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::OESFlag,           OESFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::OES_CSFlag,        OES_CSFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::OES_CS_ONFlag,     OES_CS_ONFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::OES_ONFlag,        OES_ONFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::CSFlag,            CSFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::CS_ONFlag,         CS_ONFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::CS_ONHFlag,        CS_ONHFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::ONFlag,            ONFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::ONHFlag,           ONHFlag);
            
      //********    Dispatch event ***********************************************************************
      SendEventMessage(TlgName,DataKeyLab,L1PlantID,HeatID,TreatID,OrderID);

    }
    else
    {
      // no Telcom-Interface (unlikely error case)
      RetValue=false;
    }
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
      "CDH_LAB_OUTModelResultWrapper::provideData_SMCLAB02SteelSampleTaken(CEventMessage &Event)","Reading DM Interface Data");
    RetValue=false;
  }
  return RetValue;
}

bool CLab_EventHandler::provideData_SteelSampleTakenAOD(CEventMessage &Event)
{
  bool RetValue = true; // assume success

  //read the data from Event
  std::string HeatID            = Event.getHeatID();
  std::string TreatID           = Event.getTreatID();
  std::string ProductID         = Event.getProductID();
  std::string OrderID           = Event.getOrderID();
  std::string DataKey           = Event.getDataKey();
  std::string PlantID           = Event.getPlantID();

  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyLab;
  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID);

  std::string TlgName;
  std::string Function;
  std::string tmp;
  std::string ProdOrderID;
  std::string SteelGradeCode;
  std::string Workstation = "Test";
  std::string SampleLocation;
  std::string ActPhase;
  std::string ActPhaseResNo;

  CDateTime SampleTime;

  long SampleNo;
  long OESFlag        = 0;
  long OES_CSFlag     = 0;
  long OES_CS_ONFlag  = 0;
  long OES_ONFlag     = 0;
  long CSFlag         = 0;
  long CS_ONFlag      = 0;
  long CS_ONHFlag     = 0;
  long ONFlag         = 0;
  long ONHFlag        = 0;
  long UnitNo         = m_pGC_Plant_Container->getPlantNo(PlantID);

  bool bResult = 0;
  
  TlgName = "SMCLAB02";
  Function = "CLab_EventHandler::provideData_SMCLAB02SteelSampleTakenAOD";

  try
  {
    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();
    m_pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::EVENT);
    m_pDM_InterfaceProduct = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    if (m_pDM_Interface && m_pTelcom_Interface)
    {
      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);

      DataKeyLab = pTelcom_Interface->generateDataKey(TlgName);
      SteelGradeCode = m_pPD_HEAT_DATA->getSteelGradeCode(HeatID,TreatID,Plant);
      ProdOrderID = m_pPD_HEAT_DATA->getPRODORDERID_ACT(1);

      ActPhase = m_pDM_InterfaceProduct->getString(Event.getProductID().c_str(), DATA::PhaseAct);


      if(ActPhase == DEF_GC_PHASE::MainBlow || ActPhase == DEF_GC_PHASE::DynBlowNo)
      {
        //SamplingFlagDuringBlow
      }
      else if(ActPhase == DEF_GC_PHASE::ReblowAfterBlow)
      {
        //SamplingFlagAfterBlow
      }
      else if(ActPhase == DEF_GC_PHASE::ReblowAfterRed)
      {
        //SamplingFlagAfterReduction
      }
      else if(ActPhase == DEF_GC_PHASE::Red)
      {
        if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"SamplingFlagBeforeTap") == 1)
        {
          if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"CS_SamplingFlagBeforeTap") == 1)
          {
            if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"ON_SamplingFlagBeforeTap") == 1)
            {
              OES_CS_ONFlag = 1;
            }
            else
            {
              OES_CSFlag = 1;
            }
          }
          else if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"ON_SamplingFlagBeforeTap") == 1)
          {
            OES_ONFlag = 1;
          }
        }
      }
      else if(ActPhase == DEF_GC_PHASE::Tap)
      {
        if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"SamplingFlagLast") == 1)
        {
          if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"CS_SamplingFlagLast") == 1)
          {
            if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"ON_SamplingFlagLast") == 1)
            {
              OES_CS_ONFlag = 1;
            }
            else
            {
              OES_CSFlag = 1;
            }
          }
          else if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"ON_SamplingFlagLast") == 1)
          {
            OES_ONFlag = 1;
          }
        }
      }
      else if(ActPhase == DEF_GC_PHASE::Prep)
      {
        //SamplingFlagBeforeBlow
      }
      else
      {
        log("No analysis for the AOD SteelSampleTaken found for "+ ActPhase,3);
      }
      
      // Prepare Customer's Heat and Treatment Id for sending instead of internal data.

      if( m_pHeatDataConverter &&  m_pHeatDataConverter->getCustHeatData(HeatID,TreatID,CustHeatID,CustTreatID,Plant) )
      {
        CustHeatID    = CDataConversion::Trim(CustHeatID);
        CustTreatID   = CDataConversion::Trim(CustTreatID); 
      } // else there is not much we can do about it

      SampleLocation  = m_pDM_Interface->getString(Event.getDataKey().c_str(),DATA::SampleLocation);
      SampleTime      = m_pDM_Interface->getDate(Event.getDataKey().c_str(),DATA::SteelSampleTime);
      // Sample Time regularly is not provided if the SampleTaken event comes from HMI instead of L1.
      // Provide "now" as default.

      if   (SampleTime == CDateTime::InvalidDateTime() )
      {
        CDateTime now;
        SampleTime = now;
      }

      SampleNo        = m_pDM_Interface->getLong(Event.getDataKey().c_str(),DATA::SampleNo);

      //if((12 - tmp.length()) > 0) //insert spaces at the end of SteelGradeCode.
      //{
      //    std::string SteelGradeCodeWithSpaces;
      //    std::stringstream strNewcode;
      //    strNewcode << tmp << setw(10 - tmp.length()) << setfill(' ') << "";            
      //    SteelGradeCodeWithSpaces = strNewcode.str();          
      //    tmp = SteelGradeCodeWithSpaces;
      //    //SteelGradeCode = tmp + SteelGradeCode;
      //}

      // truncate data to fit telegram length
        
      CustHeatID          = CDataConversion::CheckLengthAndTruncate(CustHeatID          ,10);
      CustTreatID         = CDataConversion::CheckLengthAndTruncate(CustTreatID         ,2);
      ProdOrderID     = CDataConversion::CheckLengthAndTruncate(ProdOrderID     ,10);
      SteelGradeCode  = CDataConversion::CheckLengthAndTruncate(SteelGradeCode  ,12);
      Workstation     = CDataConversion::CheckLengthAndTruncate(Workstation     ,20);
      //SampleTime      = CDataConversion::CheckLengthAndTruncate(SampleTime      ,4);
      SampleLocation  = CDataConversion::CheckLengthAndTruncate(SampleLocation  ,2);
      //SampleNo        = CDataConversion::CheckLengthAndTruncate(SampleNo        ,4);



      //********    Write telegram data  ***********************************************************************
      //pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::UnitNo,            UnitNo);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB02::HeatId,            CustHeatID);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB02::TreatId,           CustTreatID);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB02::ProdOrderId,       ProdOrderID);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB02::SteelGradeCode,    SteelGradeCode );
      pTelcom_Interface->setAny     ( DataKeyLab, Telegram_SMCLAB02::SampleTime,        SampleTime.asCORBAAny());
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB02::SampleLocation,    SampleLocation);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::SampleNo,          SampleNo);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB02::Workstation,       Workstation);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::OESFlag,           OESFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::OES_CSFlag,        OES_CSFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::OES_CS_ONFlag,     OES_CS_ONFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::OES_ONFlag,        OES_ONFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::CSFlag,            CSFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::CS_ONFlag,         CS_ONFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::CS_ONHFlag,        CS_ONHFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::ONFlag,            ONFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::ONHFlag,           ONHFlag);
            
      //********    Dispatch event ***********************************************************************
      SendEventMessage(TlgName,DataKeyLab,L1PlantID,HeatID,TreatID,OrderID);

    }
    else
    {
      // no Telcom-Interface (unlikely error case)
      RetValue=false;
    }
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
      "CDH_LAB_OUTModelResultWrapper::provideData_SMCLAB02SteelSampleTaken(CEventMessage &Event)","Reading DM Interface Data");
    RetValue=false;
  }
  return RetValue;
}

bool CLab_EventHandler::provideData_SlagSampleTakenEAF(CEventMessage &Event)
{
  bool RetValue = true; // assume success

  //read the data from Event
  std::string HeatID            = Event.getHeatID();
  std::string TreatID           = Event.getTreatID();
  std::string ProductID         = Event.getProductID();
  std::string OrderID           = Event.getOrderID();
  std::string DataKey           = Event.getDataKey();
  std::string PlantID           = Event.getPlantID();

  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyLab;
  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID);

  std::string TlgName;
  std::string Function;
  std::string tmp;
  std::string ProdOrderID;
  std::string SteelGradeCode;
  std::string Workstation = "Test";
  std::string SampleLocation;
  std::string ActPhase;
  std::string ActPhaseResNo;

  CDateTime SampleTime;

  long SampleNo;
  long OESFlag        = 0;
  long OES_CSFlag     = 0;
  long OES_CS_ONFlag  = 0;
  long OES_ONFlag     = 0;
  long CSFlag         = 0;
  long CS_ONFlag      = 0;
  long CS_ONHFlag     = 0;
  long ONFlag         = 0;
  long ONHFlag        = 0;
  long UnitNo         = m_pGC_Plant_Container->getPlantNo(PlantID);

  bool bResult = 0;

  
  TlgName = "SMCLAB03";
  Function = "CLab_EventHandler::provideData_SMCLAB03SlagSampleTakenEAF";

  try
  {
    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();
    m_pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::EVENT);
    m_pDM_InterfaceProduct = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    if (m_pDM_Interface && m_pTelcom_Interface)
    {
      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);

      DataKeyLab      = pTelcom_Interface->generateDataKey(TlgName);
      SteelGradeCode  = m_pPD_HEAT_DATA->getSteelGradeCode(HeatID,TreatID,Plant);
      ProdOrderID     = m_pPD_HEAT_DATA->getPRODORDERID_ACT(1);

      ActPhase = m_pDM_InterfaceProduct->getString(Event.getProductID().c_str(), DATA::PhaseAct);


      if (ActPhase == DEF_GC_PHASE::Tapped)
      {
        if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"SlagSamplingFlag") == 1)
        {
          //SlagSamplingFlag
        }
      }
      else
      {
        log("No analysis for the EAF SlagSampleTaken found for "+ ActPhase,3);
      }

      // Prepare Customer's Heat and Treatment Id for sending instead of internal data.

      if( m_pHeatDataConverter &&  m_pHeatDataConverter->getCustHeatData(HeatID,TreatID,CustHeatID,CustTreatID,Plant) )
      {
        CustHeatID    = CDataConversion::Trim(CustHeatID);
        CustTreatID   = CDataConversion::Trim(CustTreatID); 
      } // else there is not much we can do about it
      
      SampleLocation  = m_pDM_Interface->getString(Event.getDataKey().c_str(),DATA::SampleLocation);
      SampleTime      = m_pDM_Interface->getDate(Event.getDataKey().c_str(),DATA::SlagSampleTime);    // SLAG! 
      // Sample Time regularly is not provided if the SampleTaken event comes from HMI instead of L1.
      // Provide "now" as default.

      if   (SampleTime == CDateTime::InvalidDateTime() )
      {
        CDateTime now;
        SampleTime = now;
      }

      SampleNo        = m_pDM_Interface->getLong(Event.getDataKey().c_str(),DATA::SampleNo);

      //if((12 - tmp.length()) > 0) //insert spaces at the end of SteelGradeCode.
      //{
      //    std::string SteelGradeCodeWithSpaces;
      //    std::stringstream strNewcode;
      //    strNewcode << tmp << setw(10 - tmp.length()) << setfill(' ') << "";            
      //    SteelGradeCodeWithSpaces = strNewcode.str();          
      //    tmp = SteelGradeCodeWithSpaces;
      //    //SteelGradeCode = tmp + SteelGradeCode;
      //}

      // truncate data to fit telegram length
        
      CustHeatID          = CDataConversion::CheckLengthAndTruncate(CustHeatID          ,10);
      CustTreatID         = CDataConversion::CheckLengthAndTruncate(CustTreatID         ,2);
      ProdOrderID     = CDataConversion::CheckLengthAndTruncate(ProdOrderID     ,10);
      SteelGradeCode  = CDataConversion::CheckLengthAndTruncate(SteelGradeCode  ,12);
      Workstation     = CDataConversion::CheckLengthAndTruncate(Workstation     ,20);
      //SampleTime      = CDataConversion::CheckLengthAndTruncate(SampleTime      ,4);
      SampleLocation  = CDataConversion::CheckLengthAndTruncate(SampleLocation  ,2);
      //SampleNo        = CDataConversion::CheckLengthAndTruncate(SampleNo        ,4);



      //********    Write telegram data  ***********************************************************************
      //pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::UnitNo,            UnitNo);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB03::HeatId,            CustHeatID);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB03::TreatId,           CustTreatID);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB03::ProdOrderId,       ProdOrderID);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB03::SteelGradeCode,    SteelGradeCode );
      pTelcom_Interface->setAny     ( DataKeyLab, Telegram_SMCLAB03::SampleTime,        SampleTime.asCORBAAny());
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB03::SampleLocation,    SampleLocation);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::SampleNo,          SampleNo);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB03::Workstation,       Workstation);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::OESFlag,           OESFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::OES_CSFlag,        OES_CSFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::OES_CS_ONFlag,     OES_CS_ONFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::OES_ONFlag,        OES_ONFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::CSFlag,            CSFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::CS_ONFlag,         CS_ONFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::CS_ONHFlag,        CS_ONHFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::ONFlag,            ONFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::ONHFlag,           ONHFlag);
            
      //********    Dispatch event ***********************************************************************
      SendEventMessage(TlgName,DataKeyLab,L1PlantID,HeatID,TreatID,OrderID);

    }
    else
    {
      // no Telcom-Interface (unlikely error case)
      RetValue=false;
    }
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
      "CDH_LAB_OUTModelResultWrapper::provideData_SMCLAB02SteelSampleTaken(CEventMessage &Event)","Reading DM Interface Data");
    RetValue=false;
  }
  return RetValue;
}

bool CLab_EventHandler::provideData_SlagSampleTakenLF(CEventMessage &Event)
{
  bool RetValue = true; // assume success

  //read the data from Event
  std::string HeatID            = Event.getHeatID();
  std::string TreatID           = Event.getTreatID();
  std::string ProductID         = Event.getProductID();
  std::string OrderID           = Event.getOrderID();
  std::string DataKey           = Event.getDataKey();
  std::string PlantID           = Event.getPlantID();

  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyLab;
  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID);

  std::string TlgName;
  std::string Function;
  std::string tmp;
  std::string ProdOrderID;
  std::string SteelGradeCode;
  std::string Workstation;
  std::string SampleLocation;
  std::string ActPhase;
  std::string ActPhaseResNo;

  CDateTime SampleTime;

  long SampleNo;
  long OESFlag        = 0;
  long OES_CSFlag     = 0;
  long OES_CS_ONFlag  = 0;
  long OES_ONFlag     = 0;
  long CSFlag         = 0;
  long CS_ONFlag      = 0;
  long CS_ONHFlag     = 0;
  long ONFlag         = 0;
  long ONHFlag        = 0;
  long UnitNo         = m_pGC_Plant_Container->getPlantNo(PlantID);

  bool bResult = 0;

  try
  {
    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();
    m_pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::EVENT);
    m_pDM_InterfaceProduct = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    if (m_pDM_Interface && m_pTelcom_Interface)
    {
      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);

      DataKeyLab      = pTelcom_Interface->generateDataKey(TlgName);
      SteelGradeCode  = m_pPD_HEAT_DATA->getSteelGradeCode(HeatID,TreatID,Plant);
      ProdOrderID     = m_pPD_HEAT_DATA->getPRODORDERID_ACT(1);

      ActPhase = m_pDM_InterfaceProduct->getString(Event.getProductID().c_str(), DATA::PhaseAct);

      TlgName = "SMCLAB03";
      Function = "CLab_EventHandler::provideData_SMCLAB03SlagSampleTakenLF";

      if(ActPhase == DEF_GC_PHASE::Preparation)
      {
        if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"SlagSamplingFlagBeforeTap") == 1)
        {

        }
      }
      else if(ActPhase == DEF_GC_PHASE::Adjusting)
      {
        if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"SlagSamplingFlagLast") == 1)
        {

        }
      }
      else if(ActPhase == DEF_GC_PHASE::CleanStirring)
      {
      }
      else
      {
        log("No analysis for the LF SlagSampleTaken found for "+ ActPhase,3);
      }

      // Prepare Customer's Heat and Treatment Id for sending instead of internal data.

      if( m_pHeatDataConverter &&  m_pHeatDataConverter->getCustHeatData(HeatID,TreatID,CustHeatID,CustTreatID,Plant) )
      {
        CustHeatID    = CDataConversion::Trim(CustHeatID);
        CustTreatID   = CDataConversion::Trim(CustTreatID); 
      } // else there is not much we can do about it
      
      SampleLocation  = m_pDM_Interface->getString(Event.getDataKey().c_str(),DATA::SampleLocation);
      SampleTime      = m_pDM_Interface->getDate(Event.getDataKey().c_str(),DATA::SlagSampleTime);
      // Sample Time regularly is not provided if the SampleTaken event comes from HMI instead of L1.
      // Provide "now" as default.

      if   (SampleTime == CDateTime::InvalidDateTime() )
      {
        CDateTime now;
        SampleTime = now;
      }

      SampleNo        = m_pDM_Interface->getLong(Event.getDataKey().c_str(),DATA::SampleNo);

      //if((12 - tmp.length()) > 0) //insert spaces at the end of SteelGradeCode.
      //{
      //    std::string SteelGradeCodeWithSpaces;
      //    std::stringstream strNewcode;
      //    strNewcode << tmp << setw(10 - tmp.length()) << setfill(' ') << "";            
      //    SteelGradeCodeWithSpaces = strNewcode.str();          
      //    tmp = SteelGradeCodeWithSpaces;
      //    //SteelGradeCode = tmp + SteelGradeCode;
      //}

      // truncate data to fit telegram length
        
      CustHeatID          = CDataConversion::CheckLengthAndTruncate(CustHeatID          ,10);
      CustTreatID         = CDataConversion::CheckLengthAndTruncate(CustTreatID         ,2);
      ProdOrderID     = CDataConversion::CheckLengthAndTruncate(ProdOrderID     ,10);
      SteelGradeCode  = CDataConversion::CheckLengthAndTruncate(SteelGradeCode  ,12);
      Workstation     = CDataConversion::CheckLengthAndTruncate(Workstation     ,20);
      //SampleTime      = CDataConversion::CheckLengthAndTruncate(SampleTime      ,4);
      SampleLocation  = CDataConversion::CheckLengthAndTruncate(SampleLocation  ,2);
      //SampleNo        = CDataConversion::CheckLengthAndTruncate(SampleNo        ,4);



      //********    Write telegram data  ***********************************************************************
      //pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::UnitNo,            UnitNo);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB03::HeatId,            CustHeatID);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB03::TreatId,           CustTreatID);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB03::ProdOrderId,       ProdOrderID);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB03::SteelGradeCode,    SteelGradeCode );
      pTelcom_Interface->setAny     ( DataKeyLab, Telegram_SMCLAB03::SampleTime,        SampleTime.asCORBAAny());
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB03::SampleLocation,    SampleLocation);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::SampleNo,          SampleNo);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB03::Workstation,       Workstation);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::OESFlag,           OESFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::OES_CSFlag,        OES_CSFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::OES_CS_ONFlag,     OES_CS_ONFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::OES_ONFlag,        OES_ONFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::CSFlag,            CSFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::CS_ONFlag,         CS_ONFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::CS_ONHFlag,        CS_ONHFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::ONFlag,            ONFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::ONHFlag,           ONHFlag);
           

      //********    Dispatch event ***********************************************************************
      SendEventMessage(TlgName,DataKeyLab,L1PlantID,HeatID,TreatID,OrderID);

    }
    else
    {
      // no Telcom-Interface (unlikely error case)
      RetValue=false;
    }
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
      "CDH_LAB_OUTModelResultWrapper::provideData_SMCLAB02SteelSampleTaken(CEventMessage &Event)","Reading DM Interface Data");
    RetValue=false;
  }
  return RetValue;

}



bool CLab_EventHandler::provideData_SlagSampleTakenAOD(CEventMessage &Event)
{
  bool RetValue = true; // assume success

  //read the data from Event
  std::string HeatID            = Event.getHeatID();
  std::string TreatID           = Event.getTreatID();
  std::string ProductID         = Event.getProductID();
  std::string OrderID           = Event.getOrderID();
  std::string DataKey           = Event.getDataKey();
  std::string PlantID           = Event.getPlantID();

  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyLab;
  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID);

  std::string TlgName;
  std::string Function;
  std::string tmp;
  std::string ProdOrderID;
  std::string SteelGradeCode;
  std::string Workstation;
  std::string SampleLocation;
  std::string ActPhase;
  std::string ActPhaseResNo;

  CDateTime SampleTime;

  long SampleNo;
  long OESFlag        = 0;
  long OES_CSFlag     = 0;
  long OES_CS_ONFlag  = 0;
  long OES_ONFlag     = 0;
  long CSFlag         = 0;
  long CS_ONFlag      = 0;
  long CS_ONHFlag     = 0;
  long ONFlag         = 0;
  long ONHFlag        = 0;
  long UnitNo         = m_pGC_Plant_Container->getPlantNo(PlantID);

  bool bResult = 0;

  try
  {
    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();
    m_pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::EVENT);
    m_pDM_InterfaceProduct = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    if (m_pDM_Interface && m_pTelcom_Interface)
    {
      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);

      DataKeyLab      = pTelcom_Interface->generateDataKey(TlgName);
      SteelGradeCode  = m_pPD_HEAT_DATA->getSteelGradeCode(HeatID,TreatID,Plant);
      ProdOrderID     = m_pPD_HEAT_DATA->getPRODORDERID_ACT(1);

      ActPhase = m_pDM_InterfaceProduct->getString(Event.getProductID().c_str(), DATA::PhaseAct);

      TlgName = "SMCLAB03";
      Function = "CLab_EventHandler::provideData_SMCLAB03SlagSampleTakenAOD";

      if(ActPhase == "Red")
      {
        if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"SlagSamplingFlagBeforeTap") == 1)
        {

        }
      }
      else if(ActPhase == "Tap")
      {
        if(m_pGT_GRADE_SAMPLE_FLAG->getFLAG(Plant,SteelGradeCode,"SlagSamplingFlagLast") == 1)
        {

        }
      }
      else
      {
        log("No analysis for the AOD SlagSampleTaken found for "+ ActPhase,3);
      }

      // Prepare Customer's Heat and Treatment Id for sending instead of internal data.

      if( m_pHeatDataConverter &&  m_pHeatDataConverter->getCustHeatData(HeatID,TreatID,CustHeatID,CustTreatID,Plant) )
      {
        CustHeatID    = CDataConversion::Trim(CustHeatID);
        CustTreatID   = CDataConversion::Trim(CustTreatID); 
      } // else there is not much we can do about it

      SampleLocation  = m_pDM_Interface->getString(Event.getDataKey().c_str(),DATA::SampleLocation);
      SampleTime      = m_pDM_Interface->getDate(Event.getDataKey().c_str(),DATA::SlagSampleTime);
      // Sample Time regularly is not provided if the SampleTaken event comes from HMI instead of L1.
      // Provide "now" as default.

      if   (SampleTime == CDateTime::InvalidDateTime() )
      {
        CDateTime now;
        SampleTime = now;
      }

      SampleNo        = m_pDM_Interface->getLong(Event.getDataKey().c_str(),DATA::SampleNo);

      //if((12 - tmp.length()) > 0) //insert spaces at the end of SteelGradeCode.
      //{
      //    std::string SteelGradeCodeWithSpaces;
      //    std::stringstream strNewcode;
      //    strNewcode << tmp << setw(10 - tmp.length()) << setfill(' ') << "";            
      //    SteelGradeCodeWithSpaces = strNewcode.str();          
      //    tmp = SteelGradeCodeWithSpaces;
      //    //SteelGradeCode = tmp + SteelGradeCode;
      //}

      // truncate data to fit telegram length
        
      CustHeatID          = CDataConversion::CheckLengthAndTruncate(CustHeatID          ,10);
      CustTreatID         = CDataConversion::CheckLengthAndTruncate(CustTreatID         ,2);
      ProdOrderID     = CDataConversion::CheckLengthAndTruncate(ProdOrderID     ,10);
      SteelGradeCode  = CDataConversion::CheckLengthAndTruncate(SteelGradeCode  ,12);
      Workstation     = CDataConversion::CheckLengthAndTruncate(Workstation     ,20);
      //SampleTime      = CDataConversion::CheckLengthAndTruncate(SampleTime      ,4);
      SampleLocation  = CDataConversion::CheckLengthAndTruncate(SampleLocation  ,2);
      //SampleNo        = CDataConversion::CheckLengthAndTruncate(SampleNo        ,4);



      //********    Write telegram data  ***********************************************************************
      //pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB02::UnitNo,            UnitNo);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB03::HeatId,            CustHeatID);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB03::TreatId,           CustTreatID);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB03::ProdOrderId,       ProdOrderID);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB03::SteelGradeCode,    SteelGradeCode );
      pTelcom_Interface->setAny     ( DataKeyLab, Telegram_SMCLAB03::SampleTime,        SampleTime.asCORBAAny());
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB03::SampleLocation,    SampleLocation);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::SampleNo,          SampleNo);
      pTelcom_Interface->setString  ( DataKeyLab, Telegram_SMCLAB03::Workstation,       Workstation);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::OESFlag,           OESFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::OES_CSFlag,        OES_CSFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::OES_CS_ONFlag,     OES_CS_ONFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::OES_ONFlag,        OES_ONFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::CSFlag,            CSFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::CS_ONFlag,         CS_ONFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::CS_ONHFlag,        CS_ONHFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::ONFlag,            ONFlag);
      pTelcom_Interface->setLong    ( DataKeyLab, Telegram_SMCLAB03::ONHFlag,           ONHFlag);
           

      //********    Dispatch event ***********************************************************************
      SendEventMessage(TlgName,DataKeyLab,L1PlantID,HeatID,TreatID,OrderID);

    }
    else
    {
      // no Telcom-Interface (unlikely error case)
      RetValue=false;
    }
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
      "CDH_LAB_OUTModelResultWrapper::provideData_SMCLAB02SteelSampleTaken(CEventMessage &Event)","Reading DM Interface Data");
    RetValue=false;
  }
  return RetValue;
}