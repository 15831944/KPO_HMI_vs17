// Copyright (C) 2007 SMS Demag AG
#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_S.hh"
#include "iEventMessages_s.hh"
#include "iDM_Interface_s.hh"

#include "DEF_GC_LADLE_POS.h"
#include "DEF_GC_RECIPE_STATUS.h"
#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_LADLE_TYPE.h"
#include "DEF_GC_LIQADD_STATUS.h"

#include "CDataConversion.h"
#include "CIntfData.h"
#include "CEventMessage.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_DBExc.h"
#include "cCBS_StdCORBA_Task.h"
#include "CSMC_EventLogFrameController.h"
#include "SRECIPE.h" 

#include "CARCHIVER_Task.h"


#include "CARCHIVER_MaterialHandlingWrapper.h"








//##ModelId=45D5909A030F
CARCHIVER_MaterialHandlingWrapper::CARCHIVER_MaterialHandlingWrapper() 

{
}

//##ModelId=45D5909B0157
CARCHIVER_MaterialHandlingWrapper::~CARCHIVER_MaterialHandlingWrapper()
{
  deleteDBClasses();
}

//##ModelId=45D590B50023
void CARCHIVER_MaterialHandlingWrapper::initDBClasses()
{
  cCBS_StdConnection *pConnection = getStdConnection();

  m_pPD_LADLE                 = new CPD_LADLE(pConnection);
  m_pGC_LADLE_DEF             = new CGC_LADLE_DEF(pConnection);
  m_pPD_PRETREATDATA          = new CPD_PRETREATDATA(pConnection);
  m_pPD_HEAT_DATA_LIQADD      = new CPD_HEAT_DATA_LIQADD(pConnection);
  m_pPD_HEAT_DATA             = new CPD_HEAT_DATA(pConnection);
  m_pHD_HEAT_DATA             = new CHD_HEAT_DATA(pConnection);
  m_pPD_RECIPE                = new CPD_RECIPE(pConnection);
  m_pPD_RECIPE_ENTRY          = new CPD_RECIPE_ENTRY(pConnection);
  m_pPP_HEAT                  = new CPP_HEAT(pConnection);
  m_pPP_ORDER                 = new CPP_ORDER(pConnection);
  m_pPP_HEAT_PLANT            = new CPP_HEAT_PLANT(pConnection);
  m_pGC_Plant_Container       = new CGC_Plant_Container(pConnection);
  m_pPD_MAT_AVAIL             = new CPD_MAT_AVAIL(pConnection);
  m_pGT_MAT                   = new CGT_MAT(pConnection);
  m_pGT_MAT_PURP              = new CGT_MAT_PURP(pConnection);
  m_pGT_PARAM                 = new CGT_PARAM(pConnection);
  m_pGT_PARAM_MATRIX          = new CGT_PARAM_MATRIX(pConnection);
  m_pGC_Plantgroup_Container  = new CGC_Plantgroup_Container(pConnection);
  m_pHeatStatusContainer      = new CHeatStatusContainer(pConnection);
  m_pPD_ACTION                = new CPD_ACTION(pConnection);
  m_pGC_HEAT_STATUS             = new CGC_HEAT_STATUS(pConnection);
  m_pPD_PLANTSTATUS           = new CPD_PLANTSTATUS(pConnection);
  m_pPD_HEAT_REF              = new CPD_HEAT_REF(pConnection);
  m_pPD_PRETREATDATA          = new CPD_PRETREATDATA(pConnection); 
  m_pPD_SCRAP_CONTAINER       = new CPD_SCRAP_CONTAINER(pConnection);
  m_pPD_SCRAP_CONTAINER_ENTRY = new CPD_SCRAP_CONTAINER_ENTRY(pConnection);
  m_pPD_SCRAP_CONTAINER_ORDER = new CPD_SCRAP_CONTAINER_ORDER(pConnection);
  m_pPD_HOT_METAL             = new CPD_HOT_METAL(pConnection);
  m_pPD_HOT_METAL_ORDER       = new CPD_HOT_METAL_ORDER(pConnection);
  //}
}

//##ModelId=45D590B5027D
void CARCHIVER_MaterialHandlingWrapper::deleteDBClasses()
{
  if (m_pPD_LADLE   )             {delete m_pPD_LADLE; m_pPD_LADLE = 0;}
  if (m_pGC_LADLE_DEF   )         {delete m_pGC_LADLE_DEF; m_pGC_LADLE_DEF = 0;}
  if (m_pPD_PRETREATDATA)         {delete m_pPD_PRETREATDATA; m_pPD_PRETREATDATA = 0;}
  if (m_pPD_HEAT_DATA_LIQADD)     {delete m_pPD_HEAT_DATA_LIQADD; m_pPD_HEAT_DATA_LIQADD = 0;}
  if (m_pPD_HEAT_DATA)            {delete m_pPD_HEAT_DATA; m_pPD_HEAT_DATA = 0;}
  if (m_pHD_HEAT_DATA)            {delete m_pHD_HEAT_DATA; m_pHD_HEAT_DATA = 0;}
  if (m_pPD_RECIPE)               {delete m_pPD_RECIPE; m_pPD_RECIPE = 0; } 
  if (m_pPD_RECIPE_ENTRY)         {delete m_pPD_RECIPE_ENTRY; m_pPD_RECIPE_ENTRY = 0;}
  if (m_pPP_HEAT)                 {delete m_pPP_HEAT; m_pPP_HEAT = 0; }
  if (m_pPP_ORDER)                {delete m_pPP_ORDER; m_pPP_ORDER = 0; }
  if (m_pPP_HEAT_PLANT)           {delete m_pPP_HEAT_PLANT; m_pPP_HEAT_PLANT = 0; }
  if (m_pGC_Plant_Container)      {delete m_pGC_Plant_Container; m_pGC_Plant_Container = 0; }
  if (m_pPD_MAT_AVAIL)            {delete m_pPD_MAT_AVAIL; m_pPD_MAT_AVAIL = 0; }
  if (m_pGT_MAT)                  {delete m_pGT_MAT; m_pGT_MAT = 0; }
  if (m_pGT_MAT_PURP)             {delete m_pGT_MAT_PURP; m_pGT_MAT_PURP = 0; }
  if (m_pGT_PARAM)                {delete m_pGT_PARAM; m_pGT_PARAM = 0; }
  if (m_pGT_PARAM_MATRIX)         {delete m_pGT_PARAM_MATRIX; m_pGT_PARAM_MATRIX = 0; }
  if (m_pGC_Plantgroup_Container) {delete m_pGC_Plantgroup_Container; m_pGC_Plantgroup_Container = 0; }
  if (m_pHeatStatusContainer)     {delete m_pHeatStatusContainer; m_pHeatStatusContainer = 0; }
  if (m_pPD_ACTION)               {delete m_pPD_ACTION; m_pPD_ACTION = 0; }
  if (m_pGC_HEAT_STATUS)            {delete m_pGC_HEAT_STATUS; m_pGC_HEAT_STATUS = 0;}
  if (m_pPD_PRETREATDATA)         {delete m_pPD_PRETREATDATA; m_pPD_PRETREATDATA = 0; }
  if(m_pPD_PLANTSTATUS)           {delete m_pPD_PLANTSTATUS; m_pPD_PLANTSTATUS = 0;}
  if(m_pPD_HEAT_REF)              {delete m_pPD_HEAT_REF; m_pPD_HEAT_REF = 0;}
  if(m_pPD_SCRAP_CONTAINER)       {delete m_pPD_SCRAP_CONTAINER; m_pPD_SCRAP_CONTAINER = 0;}
  if(m_pPD_SCRAP_CONTAINER_ENTRY) {delete m_pPD_SCRAP_CONTAINER_ENTRY; m_pPD_SCRAP_CONTAINER_ENTRY = 0;}
  if(m_pPD_SCRAP_CONTAINER_ORDER) {delete m_pPD_SCRAP_CONTAINER_ORDER; m_pPD_SCRAP_CONTAINER_ORDER = 0;}
  if(m_pPD_HOT_METAL)             {delete m_pPD_HOT_METAL; m_pPD_HOT_METAL = 0;}
  if(m_pPD_HOT_METAL_ORDER)       {delete m_pPD_HOT_METAL_ORDER; m_pPD_HOT_METAL_ORDER = 0;}

}


//##ModelId=45D5B93E028F
long CARCHIVER_MaterialHandlingWrapper::getHighestRecipeNo(const std::string& HeatID, const std::string& TreatID, const std::string& Plant, const std::string& RecipeName, long RecipeStatus, const std::string& RecipeSource)
{
  long RecipeNo = 0;

  if ( m_pPD_RECIPE_ENTRY->select(HeatID, TreatID, Plant, RecipeName, RecipeStatus, RecipeSource, DEF::Inv_Long, DEF::Inv_String) )
  {
    for (int i = 1; i <= m_pPD_RECIPE_ENTRY->getLastRow(); ++i)
    {
      RecipeNo = max(RecipeNo,m_pPD_RECIPE_ENTRY->getRECIPENO(i));
    }
  }
  else
  {
    std::string SearchKey = HeatID + " " + TreatID;
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.c_str(),"PD_RECIPE_ENTRY");
  }
  return RecipeNo;
}

//##ModelId=45F560B603AE
bool CARCHIVER_MaterialHandlingWrapper::handleMaterialHandlingReport(CEventMessage& Event, sMetTimeStamp &MetTimeStamp, long TreatmentPosition )
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID); 

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_MaterialHandlingWrapper::handleMaterialHandlingReport");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;
  //***********************************************************************************

  try
  {
    if (!checkDBConnection())
    {
      log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
      return false;
    }

    sRecipeInfo SRecipeInfo;
    seqBatch SeqBatch;

    setpDM_Interface(Event.getSender(),DM::EVENT);

    std::string HMIClientId = CIntfData::ToStdString(m_pDM_Interface->getString(DataKey.c_str(),DATA::HMIClientId));

    HMIClientId = CDataConversion::SetInvalidToDefault(HMIClientId,"AnyClient");

    //get data from Event Interface and fill SRecipeInfo.

    SRecipeInfo.RecipeName   = CIntfData::ToStdString(m_pDM_Interface->getString(DataKey.c_str(),DATA::RecipeName));
    SRecipeInfo.RecipeSource = CIntfData::ToStdString(m_pDM_Interface->getString(DataKey.c_str(),DATA::RecipeSource));
    SRecipeInfo.RecipeStatus = m_pDM_Interface->getLong(DataKey.c_str(),DATA::RecipeStatus);
    SRecipeInfo.RecipeNo     = m_pDM_Interface->getLong(DataKey.c_str(),DATA::RecipeNo);
    SRecipeInfo.RecipeTarget = CIntfData::ToStdString(m_pDM_Interface->getString(DataKey.c_str(),DATA::RecipeTarget));

    SeqBatch = CIntfData::ToCORBAType(m_pDM_Interface->getBatch(DataKey.c_str(),DATA::RecipeContent));

    log("***********doOnMaterialHandlingReport*************",3);

    std::stringstream tmpStr;
    tmpStr  << "Heatid : "          << HeatID
            << ", Treatid : "       << TreatID
            << ", RecipeName : "    << SRecipeInfo.RecipeName
            << ", RecipeSource : "  << SRecipeInfo.RecipeSource
            << ", RecipeStatus : "  << SRecipeInfo.RecipeStatus
            << ", RecipeNo : "      << SRecipeInfo.RecipeNo
            << ", RecipeTarget : "  << SRecipeInfo.RecipeTarget
            << ", Batch size : "    << CIntfData::getLength(SeqBatch);

    log(tmpStr.str(),3);

    //get info from PRODUCTION_MANAGEMENT_INTERFACE
    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    SRecipeInfo.DurSinceHeatAnnounce = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatAnnounceTime);
    SRecipeInfo.DurSinceHeatStart    = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatStartTime);

    if ( 0 != CIntfData::getLength(SeqBatch) )
    {
      m_pPD_RECIPE->checkBatchStateChange(HeatID, TreatID, ActPlant, SRecipeInfo);

      // in case of materials beeing enabled that are not included in a calcualtion result, write warning to operator
      if ( SRecipeInfo.RecipeStatus == DEF_GC_RECIPE_STATUS::Enabled &&  
          !m_pPD_RECIPE->checkBatchForCalculatedMaterials(HeatID, TreatID, ActPlant, SRecipeInfo, SeqBatch) )
      {
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        sMessage.opAckn   = 1;
        sMessage.severity = c_e_warning;
        sMessage.spare3   = HMIClientId;

        std::string HMIMessage = "WARNING_NOT_CALCULATED_MATERIAL_ENABLED " + SRecipeInfo.RecipeName;

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        pEventLog->EL_HandleHMIOperatorAcknowledge(sMessage, HMIMessage.c_str() );
      }

      RetValue = m_pPD_RECIPE->writeBatch(HeatID, TreatID, ActPlant, SRecipeInfo, MetTimeStamp, SeqBatch, false, m_lastError);
      if ( RetValue )
      {
        m_pPD_RECIPE->commit();
      }
      else
      {
        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PD_RECIPE", m_pPD_RECIPE->getActStatement().c_str());

        m_pPD_RECIPE->logLastError(1);
        m_pPD_RECIPE->rollback();
      }
    } 
    else
    {
      if (SRecipeInfo.RecipeStatus == DEF_GC_RECIPE_STATUS::Enabled ||
          SRecipeInfo.RecipeStatus == DEF_GC_RECIPE_STATUS::Weighed ||
          SRecipeInfo.RecipeStatus == DEF_GC_RECIPE_STATUS::WeighingCompleteUpdate)
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorProcessingData(sMessage,Scope.c_str(),"SeqBatch empty!");
      }
    }
  }
  catch (cCBS_DBExc &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Scope.c_str(), ExceptionMsg.str().c_str()); 
    RetValue = false;
    handleDBConnectionError();
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(...)
  {
    std::string Msg("Unknown exception:");
    Msg += ExceptionMsg.str();
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      Scope.c_str(), Msg.c_str()); 
    RetValue = false;
  }
  return RetValue;
}

//##ModelId=4688C4F70022
bool CARCHIVER_MaterialHandlingWrapper::handleBasketDischargeStart(CEventMessage& Event, const std::string& BasketNo, seqGasData& SeqGasData, double ElecEgy)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  //long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_MaterialHandlingWrapper::handleBasketDischargeStart");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;
  //***********************************************************************************

  try
  {
    if (!checkDBConnection())
    {
      handleDBConnectionError();
      if (!checkDBConnection()) 
        return false;
    }

    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    logInterfaceDataList(m_pDM_Interface,ProductID);

    //Calc duration since Heat Announcement and Heat Start
    double DurSinceHeatAnnounce = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatAnnounceTime);
    double DurSinceHeatStart    = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatStartTime);

    m_pPD_ACTION->m_Row.ACTIONUNIT                = "Basket";
    m_pPD_ACTION->m_Row.ACTIONVALUE               = BasketNo;
    m_pPD_ACTION->m_Row.ACTIONSTATUS              = 1;
    m_pPD_ACTION->m_Row.DURSINCEHEATANNOUNCEMENT  = DurSinceHeatAnnounce;
    m_pPD_ACTION->m_Row.DURSINCESTARTOFHEAT       = DurSinceHeatStart;
    m_pPD_ACTION->m_Row.ELECEGY                   = ElecEgy;

    int seqLength = CIntfData::getLength(SeqGasData);
    sGasData   sData;
    for(int i = 0; i < seqLength; ++i)
    {
      CIntfData::getAt(sData, SeqGasData, i);
      std::string strGasType = sData.GasType;
      if (strGasType == DEF_GAS::Ar)
        m_pPD_ACTION->m_Row.AR_MOMENT = sData.GasValue;
      else if (strGasType == DEF_GAS::N2)
        m_pPD_ACTION->m_Row.N2_MOMENT = sData.GasValue;
      else if(strGasType == DEF_GAS::O2)
        m_pPD_ACTION->m_Row.O2_MOMENT = sData.GasValue;
    }

    if (!m_pPD_ACTION->write(HeatID, TreatID, ActPlant, DEF_GC_ACTION_DEF::ScrapDischargeStart, true))
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PD_ACTION", Scope.c_str());
    }

    RetValue = true;
  }
  catch (cCBS_DBExc &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Scope.c_str(), ExceptionMsg.str().c_str()); 
    RetValue = false;
    handleDBConnectionError();
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(...)
  {
    std::string Msg("Unknown exception:");
    Msg += ExceptionMsg.str();

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      Scope.c_str(), Msg.c_str()); 
    RetValue = false;
  }
  return RetValue;
}

//##ModelId=46714E6A00EA
bool CARCHIVER_MaterialHandlingWrapper::handleBasketDischarged(CEventMessage& Event, const std::string & BasketNo, seqGasData &SeqGasData, double ElecEgy)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  //long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_MaterialHandlingWrapper::handleBasketDischarged");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;
  //***********************************************************************************

  try
  {
    if (!checkDBConnection())
    {
      handleDBConnectionError();
      if (!checkDBConnection())
        return false;
    }

    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    logInterfaceDataList(m_pDM_Interface,ProductID);

    //Calc duration since Heat Announcement and Heat Start
    double DurSinceHeatAnnounce = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatAnnounceTime);
    double DurSinceHeatStart    = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatStartTime);

    m_pPD_ACTION->m_Row.ACTIONUNIT                = "Basket";
    m_pPD_ACTION->m_Row.ACTIONVALUE               = BasketNo;
    m_pPD_ACTION->m_Row.ACTIONSTATUS              = 0;
    m_pPD_ACTION->m_Row.DURSINCEHEATANNOUNCEMENT  = DurSinceHeatAnnounce;
    m_pPD_ACTION->m_Row.DURSINCESTARTOFHEAT       = DurSinceHeatStart;
    m_pPD_ACTION->m_Row.ELECEGY                   = ElecEgy;

    int seqLength = CIntfData::getLength(SeqGasData);
    sGasData   sData;
    for(int i = 0; i < seqLength; ++i)
    {
      CIntfData::getAt(sData, SeqGasData, i);
      std::string strGasType = sData.GasType;
      if (strGasType == DEF_GAS::Ar)
        m_pPD_ACTION->m_Row.AR_MOMENT = sData.GasValue;
      else if (strGasType == DEF_GAS::N2)
        m_pPD_ACTION->m_Row.N2_MOMENT = sData.GasValue;
      else if(strGasType == DEF_GAS::O2)
        m_pPD_ACTION->m_Row.O2_MOMENT = sData.GasValue;
    }
    if (!m_pPD_ACTION->write(HeatID, TreatID, ActPlant, DEF_GC_ACTION_DEF::ScrapDischargeEnd, true))
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PD_ACTION", Scope.c_str());
    }

    RetValue = true;
  }
  catch (cCBS_DBExc &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Scope.c_str(), ExceptionMsg.str().c_str()); 
    RetValue = false;
    handleDBConnectionError();
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(...)
  {
    std::string Msg("Unknown exception:");
    Msg += ExceptionMsg.str();

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      Scope.c_str(), Msg.c_str()); 
    RetValue = false;
  }
  return RetValue;
}

//##ModelId=468234CB01CD
bool CARCHIVER_MaterialHandlingWrapper::handleHotMetalDischargeStart(CEventMessage& Event, const std::string& LadleType, long LadleNo, seqGasData& SeqGasData)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  //long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_MaterialHandlingWrapper::handleHotMetalDischargeStart");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;
  //***********************************************************************************

  try
  {
    if (!checkDBConnection())
    {
      log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
      return false;
    }

    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    logInterfaceDataList(m_pDM_Interface,ProductID);

    //Calc duration since Heat Announcement and Heat Start
    double DurSinceHeatAnnounce = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatAnnounceTime);
    double DurSinceHeatStart    = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatStartTime);

    long seqLength = 0;
    seqLength = CIntfData::getLength(SeqGasData);
    sGasData sData;
    m_pPD_ACTION->m_Row.AR_MOMENT = 0;
    m_pPD_ACTION->m_Row.O2_MOMENT = 0;
    m_pPD_ACTION->m_Row.N2_MOMENT = 0;

    for (int i = 0 ; i < seqLength ; ++i)
    {
      CIntfData::getAt(sData,&SeqGasData,i);
      std::string strGasType = sData.GasType;
      if (strGasType == DEF_GAS::O2)
        m_pPD_ACTION->m_Row.O2_MOMENT = sData.GasValue;
      if (strGasType == DEF_GAS::Ar)
        m_pPD_ACTION->m_Row.AR_MOMENT = sData.GasValue;
      if (strGasType== DEF_GAS::N2)
        m_pPD_ACTION->m_Row.N2_MOMENT = sData.GasValue;
    }
    m_pPD_ACTION->m_Row.ACTIONUNIT                = "Ladle";
    m_pPD_ACTION->m_Row.ACTIONVALUE               = LadleType + CDataConversion::LongToString(LadleNo);
    m_pPD_ACTION->m_Row.ACTIONSTATUS              = 0;
    m_pPD_ACTION->m_Row.DURSINCEHEATANNOUNCEMENT  = DurSinceHeatAnnounce;
    m_pPD_ACTION->m_Row.DURSINCESTARTOFHEAT       = DurSinceHeatStart;

    if (!m_pPD_ACTION->write(HeatID, TreatID, ActPlant, DEF_GC_ACTION_DEF::HMDischargeStart, true))
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PD_ACTION", Scope.c_str());
    }

    RetValue = true;
  }
  catch (cCBS_DBExc &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Scope.c_str(), ExceptionMsg.str().c_str()); 
    RetValue = false;
    handleDBConnectionError();
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(...)
  {
    std::string Msg("Unknown exception:");
    Msg += ExceptionMsg.str();

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      Scope.c_str(), Msg.c_str()); 
    RetValue = false;
  }
  return RetValue;
}

//##ModelId=4682398003B5
bool CARCHIVER_MaterialHandlingWrapper::handleHotMetalDischarged(CEventMessage& Event, const std::string& LadleType, long LadleNo, seqGasData& SeqGasData)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  //long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_MaterialHandlingWrapper::handleHotMetalDischarged");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;
  //***********************************************************************************

  try
  {
    if (!checkDBConnection())
    {
      log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
      return false;
    }

    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    logInterfaceDataList(m_pDM_Interface,ProductID);

    double DurSinceHeatAnnounce = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatAnnounceTime);
    double DurSinceHeatStart    = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatStartTime);

    long seqLength = 0;
    seqLength = CIntfData::getLength(SeqGasData);
    sGasData sData;
    m_pPD_ACTION->m_Row.AR_MOMENT = 0;
    m_pPD_ACTION->m_Row.O2_MOMENT = 0;
    m_pPD_ACTION->m_Row.N2_MOMENT = 0;

    for (int i = 0 ; i < seqLength ; ++i)
    {
      CIntfData::getAt(sData,&SeqGasData,i);
      std::string strGasType = sData.GasType;
      if (strGasType == DEF_GAS::O2)
        m_pPD_ACTION->m_Row.O2_MOMENT = sData.GasValue;
      if (strGasType == DEF_GAS::Ar)
        m_pPD_ACTION->m_Row.AR_MOMENT = sData.GasValue;
      if (strGasType== DEF_GAS::N2)
        m_pPD_ACTION->m_Row.N2_MOMENT = sData.GasValue;
    }
    m_pPD_ACTION->m_Row.ACTIONUNIT                = "Ladle";
    m_pPD_ACTION->m_Row.ACTIONVALUE               = LadleType + CDataConversion::LongToString(LadleNo);
    m_pPD_ACTION->m_Row.ACTIONSTATUS              = 1;
    m_pPD_ACTION->m_Row.DURSINCEHEATANNOUNCEMENT  = DurSinceHeatAnnounce;
    m_pPD_ACTION->m_Row.DURSINCESTARTOFHEAT       = DurSinceHeatStart;

    if (!m_pPD_ACTION->write(HeatID, TreatID, ActPlant, DEF_GC_ACTION_DEF::HMDischargeEnd, true))
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PD_ACTION", Scope.c_str());
    }

    RetValue = true;
  }
  catch (cCBS_DBExc &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Scope.c_str(), ExceptionMsg.str().c_str()); 
    RetValue = false;
    handleDBConnectionError();
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(...)
  {
    std::string Msg("Unknown exception:");
    Msg += ExceptionMsg.str();

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      Scope.c_str(), Msg.c_str()); 
    RetValue = false;
  }
  return RetValue;
}

//##ModelId=46823A6203DD
bool CARCHIVER_MaterialHandlingWrapper::handleAddLiquidAddition(CEventMessage& Event, const std::string& LadleType, long LadleNo)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_MaterialHandlingWrapper::handleAddLiquidAddition");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;
  //***********************************************************************************

  try
  {
    if (!checkDBConnection())
    {
      log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
      return false;
    }
    
    long maxLiqAddNo  = 0;
    double Temp       = 0.;
    CDateTime lastTempTime;

    //calc next LiqaddNo
    if (m_pPD_HEAT_DATA_LIQADD->select(HeatID, TreatID, ActPlant,CSMC_DBData::unspecLong))
    {
      //Calc next LiqAddNo
      for (int i = 1; i <= m_pPD_HEAT_DATA_LIQADD->getLastRow(); ++i)
      {
        maxLiqAddNo = max(maxLiqAddNo, m_pPD_HEAT_DATA_LIQADD->getLIQADDNO(i) );
      }
    }// if(m_pPD_HEAT_DATA_LIQADD->select(...))

    //write into PD_Heatdata_Liqadd
    m_pPD_HEAT_DATA_LIQADD->setHEATID(HeatID);
    m_pPD_HEAT_DATA_LIQADD->setTREATID(TreatID);
    m_pPD_HEAT_DATA_LIQADD->setPLANT(ActPlant);

    if ( m_pGC_LADLE_DEF->isValidLadle(LadleNo, LadleType) )
    {
      m_pPD_HEAT_DATA_LIQADD->setLADLETYPE(LadleType);
      m_pPD_HEAT_DATA_LIQADD->setLADLENO(LadleNo);
    }

    m_pPD_HEAT_DATA_LIQADD->setLIQADDNO(maxLiqAddNo);
    m_pPD_HEAT_DATA_LIQADD->setSTATUS(DEF_GC_LIQADD_STATUS::ASSIGNED);

    if(m_pPD_HEAT_DATA_LIQADD->insert())
    {
      m_pPD_HEAT_DATA_LIQADD->commit();
    }
    else
    {          
      m_pPD_HEAT_DATA_LIQADD->rollback();

      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PD_HEAT_DATA_LIQADD", Scope.c_str());
    }

    // set default analysis if Hot Metal Ladle only
    if (m_pGT_PARAM_MATRIX->select(CSMC_DBData::unspecLong,"DefltHotMetalAnl",0,CSMC_DBData::unspecLong,
      CSMC_DBData::unspecString,CSMC_DBData::unspecString))
    {
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorSearchingData(sMessage,"DefltHotMetalAnl","GT_PARAM_MATRIX");
    }

    RetValue = true;
  }
  catch (cCBS_DBExc &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Scope.c_str(), ExceptionMsg.str().c_str()); 
    RetValue = false;
    handleDBConnectionError();
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(...)
  {
    std::string Msg("Unknown exception:");
    Msg += ExceptionMsg.str();

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      Scope.c_str(), Msg.c_str()); 
    RetValue = false;
  }
  return RetValue;
}


//##ModelId=4745736A017D
bool CARCHIVER_MaterialHandlingWrapper::handleMaterialFeedingStart(CEventMessage& Event, seqGasData& SeqGasData, double ElecEgy)
{
  bool RetValue = true;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  //long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);
  //std::string ProdOrderID = Event.getOrderID();

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_MaterialHandlingWrapper::handleMaterialFeedingStart");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;
  //***********************************************************************************

  try
  {
    //if (!checkDBConnection())
    //{
    //  handleDBConnectionError();
    //  return false;
    //}

    //// collect data from product data interface
    //setpDM_Interface(Event.getSender(),DM::PRODUCT);
    //logInterfaceDataList(m_pDM_Interface,ProductID);

    ////Calc duration since Heat Announcement and Heat Start
    //double DurSinceHeatAnnounce = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatAnnounceTime);
    //double DurSinceHeatStart    = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatStartTime);

    //m_pPD_ACTION->m_Row.ACTIONSTATUS              = 1;
    //m_pPD_ACTION->m_Row.DURSINCEHEATANNOUNCEMENT  = DurSinceHeatAnnounce;
    //m_pPD_ACTION->m_Row.DURSINCESTARTOFHEAT       = DurSinceHeatStart;
    //m_pPD_ACTION->m_Row.ELECEGY                   = ElecEgy;

    //int seqLength = CIntfData::getLength(SeqGasData);
    //sGasData   sData;
    //for(int i = 0; i < seqLength; ++i)
    //{
    //  CIntfData::getAt(sData, SeqGasData, i);
    //  std::string strGasType = sData.GasType;
    //  if (strGasType == DEF_GAS::Ar)
    //    m_pPD_ACTION->m_Row.AR_MOMENT = sData.GasValue;
    //  else if (strGasType == DEF_GAS::N2)
    //    m_pPD_ACTION->m_Row.N2_MOMENT = sData.GasValue;
    //  else if(strGasType == DEF_GAS::O2)
    //    m_pPD_ACTION->m_Row.O2_MOMENT = sData.GasValue;
    //}

    //RetValue = true;
    //if (!m_pPD_ACTION->write(HeatID, TreatID, ActPlant, DEF_GC_ACTION_DEF::ContinuousFeedingStart, true))
    //{
    //  RetValue = false;

    //  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    //  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    //  pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PD_ACTION", Scope.c_str());
    //}
  }
  catch (cCBS_DBExc &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Scope.c_str(), ExceptionMsg.str().c_str()); 
    RetValue = false;
    handleDBConnectionError();
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(...)
  {
    std::string Msg("Unknown exception:");
    Msg += ExceptionMsg.str();
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", Scope.c_str(), Msg.c_str()); 
    RetValue = false;
  }
  return RetValue;
}

//##ModelId=4745736D03A2
bool CARCHIVER_MaterialHandlingWrapper::handleMaterialFeedingStop(CEventMessage& Event, seqGasData& SeqGasData, double ElecEgy)
{
  bool RetValue = true;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  //long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);
  //std::string ProdOrderID = Event.getOrderID();

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_MaterialHandlingWrapper::handleMaterialFeedingStop");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;
  //***********************************************************************************

  try
  {
    //if (!checkDBConnection())
    //{
    //  handleDBConnectionError();
    //  return false;
    //}

    //// collect data from product data interface
    //setpDM_Interface(Event.getSender(),DM::PRODUCT);
    //logInterfaceDataList(m_pDM_Interface,ProductID);

    ////Calc duration since Heat Announcement and Heat Start
    //double DurSinceHeatAnnounce = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatAnnounceTime);
    //double DurSinceHeatStart    = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatStartTime);

    //m_pPD_ACTION->m_Row.ACTIONSTATUS              = 0;
    //m_pPD_ACTION->m_Row.DURSINCEHEATANNOUNCEMENT  = DurSinceHeatAnnounce;
    //m_pPD_ACTION->m_Row.DURSINCESTARTOFHEAT       = DurSinceHeatStart;
    //m_pPD_ACTION->m_Row.ELECEGY                   = ElecEgy;

    //int seqLength = CIntfData::getLength(SeqGasData);
    //sGasData   sData;
    //for(int i = 0; i < seqLength; ++i)
    //{
    //  CIntfData::getAt(sData, SeqGasData, i);
    //  std::string strGasType = sData.GasType;
    //  if (strGasType == DEF_GAS::Ar)
    //    m_pPD_ACTION->m_Row.AR_MOMENT = sData.GasValue;
    //  else if (strGasType == DEF_GAS::N2)
    //    m_pPD_ACTION->m_Row.N2_MOMENT = sData.GasValue;
    //  else if(strGasType == DEF_GAS::O2)
    //    m_pPD_ACTION->m_Row.O2_MOMENT = sData.GasValue;
    //}

    //RetValue = true;
    //if (!m_pPD_ACTION->write(HeatID, TreatID, ActPlant, DEF_GC_ACTION_DEF::ContinuousFeedingStop, true))
    //{
    //  RetValue = false;

    //  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    //  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    //  pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PD_ACTION", Scope.c_str());
    //}
  }
  catch (cCBS_DBExc &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Scope.c_str(), ExceptionMsg.str().c_str()); 
    RetValue = false;
    handleDBConnectionError();
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(...)
  {
    std::string Msg("Unknown exception:");
    Msg += ExceptionMsg.str();
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", Scope.c_str(), Msg.c_str()); 
    RetValue = false;
  }
  return RetValue;
}

bool CARCHIVER_MaterialHandlingWrapper::handleUpdateLiquidAddition(CEventMessage& Event, long LiqAddNo)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_MaterialHandlingWrapper::handleUpdateLiquidAddition");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;
  //***********************************************************************************

  try
  {
    if (!checkDBConnection())
    {
      log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
      return false;
    }

    if(m_pPD_HEAT_DATA_LIQADD->select(HeatID, TreatID, ActPlant, LiqAddNo))
    {
      std::string LadleType = m_pPD_HEAT_DATA_LIQADD->getLADLETYPE(1);
      long LadleNo          = m_pPD_HEAT_DATA_LIQADD->getLADLENO(1);

      //get SLAGWEIGHT and STEELWEIGHT from PD_LADLE
      if(m_pPD_LADLE->select(LadleNo, LadleType))
      {
        //m_pPD_HEAT_DATA_LIQADD->setSLAGWEIGHT(m_pPD_LADLE->getREMSLAGMASS(1));
        //m_pPD_HEAT_DATA_LIQADD->setSTEELWEIGHT(m_pPD_LADLE->getREMSTEELMASS(1));
      }
      if(m_pPD_HEAT_DATA_LIQADD->update())
      {
        m_pPD_HEAT_DATA_LIQADD->commit();
      }
      else
      {          
        m_pPD_HEAT_DATA_LIQADD->rollback();

        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PD_HEAT_DATA_LIQADD", Scope.c_str());
      }
    }//if(m_pPD_HEAT_DATA_LIQADD->select(HeatID, TreatID, ActPlant, LiqAddNo))
    else
    {
      std::stringstream Mes;
      Mes << HeatID << " " << TreatID << " " << ActPlant << " " << LiqAddNo;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorSearchingData(sMessage,Mes.str().c_str(),"PD_Heatdata_Liqadd");
    }

    RetValue = false;
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(...)
  {
    std::string Msg("Unknown exception:");
    Msg += ExceptionMsg.str();

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      Scope.c_str(), Msg.c_str()); 
    RetValue = false;
  }
  return RetValue;
}

//##ModelId=462F05A5003A
bool CARCHIVER_MaterialHandlingWrapper::handleLiqMatHandlingReport(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);
  std::string ProdOrderID = Event.getOrderID();

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_LFMaterialHandlingWrapper::doOnLiqMatHandlingReport");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;
  //***********************************************************************************

  try
  {
    if (!checkDBConnection())
    {
      log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
      return false;
    }

    long    WeighingType  = DEF::Inv_Long;
    double  MeasWeight    = 0;
    double  NettWeight    = 0;
    double  SteelWeight   = 0;
    double  SlagWeight    = 0;
    double  ScullMass   = 0;
    double  GrossWeight   = 0;
    double  TareWeight    = 0;

    long    LadleNo       = DEF::Inv_Long;
    long    LadleLocation = DEF_GC_LADLE_POS::UNDEF;
    long    Deslaged      = 0;
    std::string LadleType;

    setpDM_Interface(Event.getSender(),DM::EVENT);

    WeighingType    = m_pDM_Interface->getLong  (DataKey.c_str(), DATA::WeighingType);
    LadleNo         = m_pDM_Interface->getLong  (DataKey.c_str(), DATA::LadleNo);
    LadleType       = m_pDM_Interface->getString(DataKey.c_str(), DATA::LadleType);
    MeasWeight      = m_pDM_Interface->getDouble(DataKey.c_str(), DATA::MeasWeight);
    LadleLocation   = m_pDM_Interface->getLong  (DataKey.c_str(), DATA::LadleLocation);

    std::stringstream mes;
    mes << "Received: LadleNo:" << LadleNo << ", LadleType:" << LadleType << ", Weight:" << MeasWeight << ", WeighingType:" << WeighingType;
    log(mes.str(),4);

    if( m_pPD_LADLE->select(LadleNo, LadleType) )
    {
      TareWeight     = m_pPD_LADLE->getTAREWEIGHT(1);
      ScullMass      = m_pPD_LADLE->getSCULLMASS(1);
// column removed     GrossWeight    = m_pPD_LADLE->getGROSSWEIGHT(1);

      TareWeight     = CDataConversion::SetInvalidToDefault(TareWeight, 0);
      ScullMass      = CDataConversion::SetInvalidToDefault(ScullMass, 0);
      GrossWeight    = CDataConversion::SetInvalidToDefault(GrossWeight, 0);

      if ( LadleType == DEF_GC_LADLE_TYPE::TeemingLadle  || ScullMass < 0 )
      {
        ScullMass = 0; 
      }

      long PreTreatCounter_Act  = m_pPD_LADLE->getPRETREAT_CNT_ACT(1);
      long PreTreatCounter_Prev = m_pPD_LADLE->getPRETREAT_CNT_PREV(1);

      long PreTreatCounter    = CDataConversion::SetInvalidToDefault(PreTreatCounter_Act, PreTreatCounter_Prev);

      if ( PreTreatCounter != CSMC_DBData::unspecLong )
      {
        if  ( m_pPD_PRETREATDATA->select(PreTreatCounter) )
        {
          SteelWeight   = m_pPD_PRETREATDATA->getSTEELWEIGHT(1);
          SlagWeight    = m_pPD_PRETREATDATA->getSLAGWEIGHT(1);

          SteelWeight   = CDataConversion::SetInvalidToDefault(SteelWeight, 0);
          SlagWeight    = CDataConversion::SetInvalidToDefault(SlagWeight, 0);

          NettWeight    = SteelWeight + SlagWeight;
        }
      }

      if(   WeighingType == DEF_LIQ_MAT_REPORT::HMLadleGrossWeightBeforePouring   ||
            WeighingType == DEF_LIQ_MAT_REPORT::HMLadleGrossWeightAfterPouring    ||
            WeighingType == DEF_LIQ_MAT_REPORT::HMLadleGrossWeightBeforeDesul     ||
            WeighingType == DEF_LIQ_MAT_REPORT::HMLadleGrossWeightAfterDesul      ||
            WeighingType == DEF_LIQ_MAT_REPORT::HMLadleGrossWeightBeforBOFCharge  ||
            WeighingType == DEF_LIQ_MAT_REPORT::HMLadleGrossWeightforEAF          ||
            WeighingType == DEF_LIQ_MAT_REPORT::FeCrWeightGrossforEAF             ||
            WeighingType == DEF_LIQ_MAT_REPORT::LadleGrossWeightAfterBOFTapping   ||
            WeighingType == DEF_LIQ_MAT_REPORT::LadleWeightBeforeLF               ||
            WeighingType == DEF_LIQ_MAT_REPORT::LadleWeightAfterLF                ||
            WeighingType == DEF_LIQ_MAT_REPORT::LadleGrossWeightBeforeCasting     ||
            WeighingType == DEF_LIQ_MAT_REPORT::LadleGrossWeightAfterCasting      ||
            WeighingType == DEF_LIQ_MAT_REPORT::LadleWeightReturnHeat             ||
            WeighingType == DEF_LIQ_MAT_REPORT::LadleWeightAfterEAFTapping        ||
            WeighingType == DEF_LIQ_MAT_REPORT::LadleGrossWeightUpdateAtLF               )
      {
        GrossWeight = MeasWeight;  
        NettWeight  = GrossWeight - TareWeight - ScullMass;           
      }
      else if(  WeighingType == DEF_LIQ_MAT_REPORT::LadleNettWeightAfterEAFTapping )
      {
        NettWeight = MeasWeight;
        GrossWeight = NettWeight + TareWeight;
      }

      if( WeighingType == DEF_LIQ_MAT_REPORT::HMLadleTareweightAfterEAFCharge     ||
          WeighingType == DEF_LIQ_MAT_REPORT::FeCrLadleTareWeightAfterEAFCharge   ||
          WeighingType == DEF_LIQ_MAT_REPORT::HMLadleTareWeightAfterBOFCharge      )
      {
        ScullMass = GrossWeight - MeasWeight - NettWeight;
      } 

      if( WeighingType == DEF_LIQ_MAT_REPORT::LadleTareWeightBeforeBOFTapping ||
          WeighingType == DEF_LIQ_MAT_REPORT::LadleWeightBeforeEAFTapping       )
      {
        TareWeight  = MeasWeight;
        GrossWeight = TareWeight;
      }

      if( WeighingType == DEF_LIQ_MAT_REPORT::LadleSteelWeightAfterEAFDeslagging )
      {    
        GrossWeight = MeasWeight;
        SteelWeight = GrossWeight - TareWeight;
        SlagWeight  = 0;
        Deslaged    = 1;
      }

      if ( ScullMass < 0 )
      {
        ScullMass = 0;
      }

// column removed      m_pPD_LADLE->setGROSSWEIGHT(GrossWeight);
      m_pPD_LADLE->setLADLEPOSID(LadleLocation);
      m_pPD_LADLE->setSCULLMASS(ScullMass);
      m_pPD_LADLE->setDESLAGGED(Deslaged);
      m_pPD_LADLE->setTAREWEIGHT(TareWeight);

      if (m_pPD_LADLE->update())
      {
        m_pPD_LADLE->commit();
      }
      else
      {
        m_pPD_LADLE->rollback();
      }
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorSearchingData(sMessage,CDataConversion::LongToString(LadleNo).c_str(),"PD_LADLE");
    }
    RetValue = true;
  }
  catch (cCBS_DBExc &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Scope.c_str(), ExceptionMsg.str().c_str()); 
    RetValue = false;
    handleDBConnectionError();
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(...)
  {
    std::string Msg("Unknown exception:");
    Msg += ExceptionMsg.str();
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      Scope.c_str(), Msg.c_str()); 
    RetValue = false;
  }
  return RetValue;
}

bool CARCHIVER_MaterialHandlingWrapper::handleMaterialAvailability(CEventMessage& Event, seqMaterials& SeqMaterials, bool AllMat)
{
  bool RetValue = false;

  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_MaterialHandlingWrapper::handleMaterialAvailability");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender() << DataKey;
  //***********************************************************************************

  try
  {
    if (!checkDBConnection())
    {
      log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
      return false;
    }

    sMaterial SMaterial;
    long MatLength = CIntfData::getLength(SeqMaterials);
    bool Transaction = true;
    cCBS_ODBC_DBError pError;

    //m_pPD_MAT_AVAIL->deleteOldRows(ActPlant,CSMC_DBData::unspecString,DEF_RECIPE_SOURCE::Bin,CSMC_DBData::unspecString,true,pError);

    for (long idx=0; idx<MatLength; idx++)
    {
      CIntfData::getAt(SMaterial,SeqMaterials,idx);
      //Transaction = Transaction && m_pPD_MAT_AVAIL->updateOrInsertRow(ActPlant, ActPlantNo, std::string(SMaterial.MatCode), CSMC_DBData::unspecLong, (long)SMaterial.MatWeight);
      Transaction = Transaction && m_pPD_MAT_AVAIL->updateOrInsertRow(ActPlant,ActPlantNo,CSMC_DBData::unspecString,CSMC_DBData::unspecLong,std::string(SMaterial.MatCode),(long)SMaterial.MatWeight);
    }

    if (Transaction)
    {
      m_pPD_MAT_AVAIL->commit();
      RetValue = true;
    }
    else
    {
      m_pPD_MAT_AVAIL->rollback();
    }
  }
  catch (cCBS_DBExc &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Scope.c_str(), ExceptionMsg.str().c_str()); 
    RetValue = false;
    handleDBConnectionError();
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(...)
  {
    std::string Msg("Unknown exception:");
    Msg += ExceptionMsg.str();
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      Scope.c_str(), Msg.c_str()); 
    RetValue = false;
  }
  return RetValue;
}

bool CARCHIVER_MaterialHandlingWrapper::handleMinChargeableBinWeightUpdate(CEventMessage& Event, seqMaterials& SeqMaterials)
{
  bool RetValue = false;

  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_MaterialHandlingWrapper::handleMinChargeableBinWeightUpdate");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender() << DataKey;
  //***********************************************************************************

  try
  {
    if (!checkDBConnection())
    {
      log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
      return false;
    }

    setpDM_Interface(Event.getSender(),DM::EVENT);

    bool AllFlag = m_pDM_Interface->getBoolean(DataKey.c_str(), DATA::AllMaterials);
    
    sMaterial SMaterial;
    long MatLength = CIntfData::getLength(SeqMaterials);
    bool Transaction = true;

    for (long idx=0; idx<MatLength; idx++)
    {
      CIntfData::getAt(SMaterial,SeqMaterials,idx);
      if((long)SMaterial.MatWeight > 0)//only insert or update Material which weight is not zero. 
      {
        //new version,can read the source from interface          
        std::string strLocation = "Ladle";//Djx Currently, just ignore the location,when L1 can give clear location,then update source coding.
        
        // JAST bullshit - no plant specifics in general classes !!!
        // if( ActPlant == DEF_GC_PLANT_DEF::BOF ) strLocation = "FURN";

        // JAST 
        // update PD_MAT_AVAIL

        std::string strSource = CIntfData::ToStdString(m_pDM_Interface->getString(DataKey.c_str(), DATA::UpdatedPurpose));
      }
    }
  }

  catch (cCBS_DBExc &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Scope.c_str(), ExceptionMsg.str().c_str()); 
    RetValue = false;
    handleDBConnectionError();
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(...)
  {
    std::string Msg("Unknown exception:");
    Msg += ExceptionMsg.str();
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      Scope.c_str(), Msg.c_str()); 
    RetValue = false;
  }
  return RetValue;
}
