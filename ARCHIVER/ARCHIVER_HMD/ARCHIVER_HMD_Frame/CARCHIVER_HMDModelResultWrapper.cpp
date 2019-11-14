// Copyright (C) 2007 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"
#include "iEventMessages_s.hh"
#include "iDM_Interface_s.hh"

#include "CIntfData.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CSMC_EventLogFrameController.h"
#include "cCBS_DBExc.h"

#include "CARCHIVER_HMDTask.h"
#include "CARCHIVER_HMDModelResultWrapper.h"

//##ModelId=45D58A91011B
CARCHIVER_HMDModelResultWrapper::CARCHIVER_HMDModelResultWrapper() 
//: m_pPDH_Actual_Res(0)
//SS ,m_pPD_Ladle_Anl(0)
{
  //m_PlantID = DEF_DB_PLANT::HMD;
}

//##ModelId=45D58A9103C3
CARCHIVER_HMDModelResultWrapper::~CARCHIVER_HMDModelResultWrapper()
{
}

//##ModelId=47693EE3015F
bool CARCHIVER_HMDModelResultWrapper::doOnModelResult(CEventMessage& Event)
{
  bool RetValue = false;

  ////std::string ProductID = Event.getProductID();
  ////std::string HeatID    = Event.getHeatID();
  ////std::string TreatID   = Event.getTreatID();
  ////std::string DataKey   = Event.getDataKey();
  ////std::string PlantID   = Event.getPlantID();
  ////std::string Plant     = DEF_DB_PLANT::HMD;
  ////std::string ActPlant  = m_pPlantID_Interpreter->getPlantName(PlantID);

  ////// Unified exception handling *******************************************************
  ////std::string Scope("CARCHIVER_HMDModelResultWrapper::doOnModelResult");
  ////std::stringstream ExceptionMsg;
  ////ExceptionMsg << "Handling event: " << Event.getSender()
  ////             << ", " << ProductID << ", " << HeatID
  ////             << ", " << TreatID   << ", " << DataKey;
  //////***********************************************************************************

  ////try
  ////{
  ////  if (!m_pConnection)
  ////  {
  ////    handleDBConnectionError();
  ////    if (!m_pConnection) return false;
  ////  }

  ////  double d1;
  ////  double d2;
  ////  seqHMDModelResult SeqHMDModelResult;
  ////  sHMDModelResult   HMDModelResult;
  ////  seqComputerModes  SeqComputerModesAvail;
  ////  std::string ActPhase;
  ////  CDateTime now;
  ////  setpDM_Interface(Event.getSender(),DM::PRODUCT);

  ////  d1             = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatAnnounceTime);
  ////  d2             = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatStartTime);
  ////  ActPhase       = CIntfData::ToStdString(m_pDM_Interface->getString(ProductID.c_str(),DATA::PhaseAct));
  ////  SeqHMDModelResult     = CIntfData::ToCORBAType(m_pDM_Interface->getHMDModelResult(ProductID.c_str(),DATA::HMDPredRes));
  ////  SeqComputerModesAvail = CIntfData::ToCORBAType(m_pDM_Interface->getComputerModes(ProductID.c_str(),DATA::ComputerModeAvail));

  ////  log("***********************SeqPredRes**************************************",3);
  ////  log(CIntfData::getContent(CIntfData::ToAny(SeqHMDModelResult)),3);
  ////  log("***********************SeqComputerModes**************************************",3);
  ////  log(CIntfData::getContent(CIntfData::ToAny(SeqComputerModesAvail)),3);

  ////  m_pPDH_Actual_Res->writeResults(HeatID,TreatID,ActPlant,d1,SeqHMDModelResult,SeqComputerModesAvail);

  ////  //---------------------------------------------------------------------------


  ////  //Writing TreatementKind Suggested By Model Into PDH_HEAT_DATA To display on HMI.
  ////  long ModelResSeqLength = CIntfData::getLength(SeqHMDModelResult);
  ////  if (ModelResSeqLength > 0)
  ////  {
  ////    CIntfData::getAt(HMDModelResult, SeqHMDModelResult, 0);//There will be only 1 TreatmentKind suggested by Model
  ////    if(m_pPDH_HEAT_DATA->select(Plant,HeatID,TreatID))
  ////    {
  ////      double Saim           = m_pPDH_HEAT_DATA->getAIM_S_OPER(1);
  ////      double HMwghtEnd      = m_pPDH_HEAT_DATA->getHM_WEIGHT_END(1); 
  ////      std::string LadleType = DEF_LADLE_TYPES::HotMetalLadle ;
  ////      std::string LadleNo   = m_pPDH_HEAT_DATA->getLADLENO(1);
  ////      
  ////      m_pPDH_HEAT_DATA->setTREAT_TYPE_MODEL(HMDModelResult.TreatmentKind );
  ////      
  ////      //get analysis from PD_Ladle_Anl for HISTTYPE == "LAST"
  ////      //SS if(m_pPD_Ladle_Anl->select(LadleType, LadleNo, "LAST", "S"))
  ////      //SS {
  ////      //SS   double Sact     = m_pPD_Ladle_Anl->getANL(1);
  ////      //SS   double Sdiffppm = (Sact - Saim)* 10000;                 // Sdiff[ppm]
  ////      //SS   double Sdiffkg  = (Sdiffppm * HMwghtEnd)/1000000;       // Sdiff[kg]

  ////      //SS   //Update PDH_ACTUAL_RES with DeltaSulphur Kg & ppm both for all 5 TreatmentKind.
  ////      //SS   for(long j=1; j<=5; ++j)
  ////      //SS   {
  ////      //SS     if(m_pPDH_Actual_Res->select(Plant, HeatID, TreatID, CSMC_DBData::unspecDate , j))
  ////      //SS     {
  ////      //SS       m_pPDH_Actual_Res->setSULPHUR_PPM_AIM(Saim * 10000);
  ////      //SS       m_pPDH_Actual_Res->setSULPHUR_DELTA_PPM(Sdiffppm);
  ////      //SS       m_pPDH_Actual_Res->setSULPHUR_DELTA_KG(Sdiffkg);
  ////      //SS       
  ////      //SS       m_pPDH_Actual_Res->update();
  ////      //SS     }
  ////      //SS   }
  ////      //SS }

  ////      if (m_pPDH_HEAT_DATA->update())
  ////        m_pPDH_HEAT_DATA->commit();
  ////      else
  ////        m_pPDH_HEAT_DATA->rollback();
  ////    }
  ////  }
  ////  else
  ////    log("WARNING: struct SeqHMDModelResult from PRODUCT_MANAGEMENT_INTERFACE is empty!",2);
  //// 

  ////  //write result into PD_PHASE_RES_PLANT
  ////  std::string Sender    = Event.getSender();

  ////  setpDM_Interface(Sender,DM::PRODUCT);


  ////  setpDM_Interface(Sender,DM::PLANT);

  ////}
  ////catch (cCBS_DBExc &e)
  ////{
  ////  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  ////    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  ////    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
  ////    Scope.c_str(), ExceptionMsg.str().c_str()); 
  ////  RetValue = false;
  ////  handleDBConnectionError();
  ////}
  ////catch(CORBA::SystemException& sExc) 
  ////{
	 //// cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  ////  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  ////  pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
  ////    Scope.c_str(), ExceptionMsg.str().c_str());
  ////  RetValue = false;
  ////}
  ////catch(CORBA::Exception& cExc) 
  ////{
	 //// cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  ////  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  ////  pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
  ////    Scope.c_str(), ExceptionMsg.str().c_str());
  ////  RetValue = false;
  ////}
  ////catch(...)
  ////{
  ////  std::string Msg("Unknown exception:");
  ////  Msg += ExceptionMsg.str();
  ////  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  ////    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  ////    pEventLog->EL_ExceptionCaught(sMessage, "",
  ////    Scope.c_str(), Msg.c_str()); 
  ////  RetValue = false;
  ////}
	return RetValue;
}

//##ModelId=45D58A96024B
void CARCHIVER_HMDModelResultWrapper::deleteDBClasses()
{
  CARCHIVER_ModelResultWrapper::deleteDBClasses();
  //if (m_pPDH_Actual_Res)   {delete m_pPDH_Actual_Res; m_pPDH_Actual_Res = 0; }
  //if (m_pPD_Phase_Res)     {delete m_pPD_Phase_Res;   m_pPD_Phase_Res = 0;}
  //if (m_pPD_Phase_Res_Anl) {delete m_pPD_Phase_Res_Anl; m_pPD_Phase_Res_Anl = 0;}
  //if (m_pPDH_HEAT_DATA) {delete m_pPDH_HEAT_DATA; m_pPDH_HEAT_DATA = 0;}
//SS  if (m_pPD_Ladle_Anl) {delete m_pPD_Ladle_Anl; m_pPD_Ladle_Anl = 0;}
}

//##ModelId=45D58A970077
void CARCHIVER_HMDModelResultWrapper::initDBClasses()
{
  CARCHIVER_ModelResultWrapper::initDBClasses();

//  m_pPDH_Actual_Res   = new CPDH_ACTUAL_RES(m_pConnection);
//  m_pPD_Phase_Res     = new CPD_PHASE_RES(m_pConnection);
////SS  m_pPD_Phase_Res_Anl = new CPD_PHASE_RES_ANL(m_pConnection);
//  m_pPDH_HEAT_DATA    = new CPDH_HEAT_DATA(m_pConnection);
//SS  m_pPD_Ladle_Anl     = new CPD_LADLE_ANL(m_pConnection);
}

