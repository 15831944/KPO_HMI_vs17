// Copyright (C) 2004 SMS Demag AG
#include "CEAFModelTask.h"
#include "CEventMessage.h"
#include "CEAFModelResults_Impl.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CIntfData.h"
#include "CIntfEAF.h"
#include "CSourceEAF.h"
#include "CEAFModelResultEventHandler.h"
#include "iEventMessages_s.hh"

//##ModelId=41470BC401D9
bool CEAFGetModelResultWrapper::doModelResult(CEventMessage EventMessage ) 
{ 
  bool RetValue = false;

  if (m_pModelTask) 
  {
    try // common catch
    {
      std::string ResultMessage;

      // its generate unique key
      m_Key = m_pModelTask->getpModelResults()->generateDataKey(EventMessage.getProductID().c_str());

      // check model interface for calculation type
      long TypeOfCalc = getResultCodeAndMessage();
      
      // read respective date from model interface
      if (TypeOfCalc == 0)
      {
        ResultMessage = EAF_EvMsg::evEAFModelResultCode;
      }
      else if (TypeOfCalc == 1 ) 
      {
        getModelActualSetpoints();
        ResultMessage = EAF_EvMsg::evEAFModelResultActualSetpoints;
      }
      else if (TypeOfCalc == 2 )
      {
        getMatRecipeSetpoints();
        ResultMessage = EAF_EvMsg::evEAFModelResultRecipeSetpoints;
      }

      // generate return event and send it to event channel
      if (!ResultMessage.empty())
      {
        RetValue = true;
      }
    }
    catch (...)
    {
      cCBS_StdEventLogFrame::EL_ExceptionCaught( 
        "",
        "",
        "",
        "CEAFGetModelResultWrapper::doModelResult()",
        "", 
        __FILE__, 
        __LINE__
      );    
    }
  } 
  else 
  {
    log("error CEAFGetModelResultWrapper::doModelResult, (m_pModelTask) == false");
  }
  */         	
	return RetValue;

}

//##ModelId=41470BC40247
long CEAFGetModelResultWrapper::getResultCodeAndMessage() {
  long RetValue_TypeOfCalc = 0;

  (m_pModelTask->getpModelResults())->setLong(
    m_Key.c_str() , 
    EAF_Model::EAFResCode, 
    m_pIntfEAF->getResultCode()
  );

  /* yast: lets implement it later
  std::string message;
  do {
    // repeat until no message is returned
    message = m_pIntfEAF->getResultMessage();
    // could be message string stored in the model results interface ?
    (m_pModelTask->getpModelResults())->setString(        
      m_Key.c_str() , 
      EAF_Model::EAFResM, 
      message.c_str()
    );
  } while (message != ""); // or message!=NULL ??
  // it returns NULL or string with zero length?  
  */
  
  RetValue_TypeOfCalc = m_pIntfEAF->getTypeOfCalc();

  return RetValue_TypeOfCalc;  
}

//##ModelId=41470BC40084
long CEAFGetModelResultWrapper::getModelActualSetpoints()
{
  long RetValue = 0;

  (m_pModelTask->getpModelResults())->setString(
    m_Key.c_str() , 
    EAF_Model::EAFActualProcessPhase, 
    (m_pIntfEAF->getActualProcessPhase()).c_str()
  );
/*
  (m_pModelTask->getpModelResults())->setLong(
    m_Key.c_str() , 
    EAF_Model::EAFCompuModeBlowAvl, 
    m_pIntfEAF->isCompuModeBlowAvl()
  );

  (m_pModelTask->getpModelResults())->setLong(
    m_Key.c_str() , 
    EAF_Model::EAFCompuModeMatHndlAvl, 
    m_pIntfEAF->isCompuModeMatHndlAvl()
  );*/
  
  
/*  EAFGlobalSetpointsO2_N2Struct strSetpoints;
  sEAFGlobalSetpointsO2_N2 seqSetpoints;
    
  strSetpoints.O2VolStartMatAddn = m_pIntfEAF->getO2VolStartMatAddn();
  strSetpoints.O2VolSartMatDynAddn = m_pIntfEAF->getO2VolStartMatDynAddn();
  strSetpoints.O2VolStartScrapChute =  m_pIntfEAF->getO2VolStartScrapChute();
  strSetpoints.O2VolSubLance = m_pIntfEAF->getO2VolSubLance();
  strSetpoints.O2VolTotal = m_pIntfEAF->getO2VolTotal();
  strSetpoints.O2VolTotalLance = m_pIntfEAF->getO2VolTotalLance();
  strSetpoints.N2VolTotal = m_pIntfEAF->getN2VolTotal();
  strSetpoints.MatFeedRate = m_pIntfEAF->getMatFeedRate();
  strSetpoints.MatDynFeedRate =  m_pIntfEAF->getMatDynFeedRate();

  CIntfData::insert(seqSetpoints, strSetpoints);
  
  (m_pModelTask->getpModelResults())->setEAFGlobalSetpointsO2_N2(
    m_Key.c_str(), 
    EAF_Model::EAFGlobalSetpointsO2_N2, 
    seqSetpoints
  );
*/
  // repeat for all states as defined in CStatusEAF
  // focusOnStatus(StatusName : const string&, StatusNo : long)  
  
  // The StatusNo = 0 for all Status except for the staus DynBlow. 
  // Here the StatusNo is the Dynamic Blowing step.

/*
  sPredRes seqPredRes;
  sEAFBlowPredRes seqBlowPredRes;

  m_pIntfEAF->focusOnStatus(CStatusEAF::Actual, 0);  
  getModelResultsAtStatus(CStatusEAF::Actual, 0, &seqPredRes, &seqBlowPredRes);

  m_pIntfEAF->focusOnStatus(CStatusEAF::Prep, 0);
  getModelResultsAtStatus(CStatusEAF::Prep, 0, &seqPredRes, &seqBlowPredRes);

  m_pIntfEAF->focusOnStatus(CStatusEAF::Tap, 0);
  getModelResultsAtStatus(CStatusEAF::Tap, 0, &seqPredRes, &seqBlowPredRes);

  m_pIntfEAF->focusOnStatus(CStatusEAF::ReblowAfterBlow, 0);
  getModelResultsAtStatus(CStatusEAF::ReblowAfterBlow, 0, &seqPredRes, &seqBlowPredRes);

  m_pIntfEAF->focusOnStatus(CStatusEAF::ReblowAfterRed, 0);
  getModelResultsAtStatus(CStatusEAF::ReblowAfterRed, 0, &seqPredRes, &seqBlowPredRes);

  long StatNo = 0;
  long RetValue_focusOnStatus;
  do {
    RetValue_focusOnStatus = m_pIntfEAF->focusOnStatus(CStatusEAF::DynBlowNo, StatNo);
    if (RetValue_focusOnStatus!=1) {
      // y668: what is return value with error meaning?
      // what value means that calling 'focusOnStatus' with that params is correct
      // and what value means that for that StatNo is not DynBlow defined?
      getModelResultsAtStatus(CStatusEAF::DynBlowNo, StatNo, &seqPredRes, &seqBlowPredRes);
      StatNo++;
    }
  } while (RetValue_focusOnStatus!=1);

  m_pIntfEAF->focusOnStatus(CStatusEAF::AlSiOxid, 0);
  getModelResultsAtStatus(CStatusEAF::AlSiOxid, 0, &seqPredRes, &seqBlowPredRes);

  m_pIntfEAF->focusOnStatus(CStatusEAF::MainBlow, 0);
  getModelResultsAtStatus(CStatusEAF::MainBlow, 0, &seqPredRes, &seqBlowPredRes);

  m_pIntfEAF->focusOnStatus(CStatusEAF::Red, 0);
  getModelResultsAtStatus(CStatusEAF::Red, 0, &seqPredRes, &seqBlowPredRes);

  m_pIntfEAF->focusOnStatus(CStatusEAF::Desul, 0);
  getModelResultsAtStatus(CStatusEAF::Desul, 0, &seqPredRes, &seqBlowPredRes);


  m_pIntfEAF->focusOnStatus(CStatusEAF::Alloy, 0);
  getModelResultsAtStatus(CStatusEAF::Alloy, 0, &seqPredRes, &seqBlowPredRes);


  (m_pModelTask->getpModelResults())->setPredRes(
    m_Key.c_str(), 
    EAF_Model::EAFPredRes, 
    seqPredRes
  );

  (m_pModelTask->getpModelResults())->setEAFBlowPredRes(
    m_Key.c_str(), 
    EAF_Model::EAFBlowPredRes, 
    seqBlowPredRes
  );

  // JAST for testing
  m_pModelTask->getpModelResults()->complete(m_Key.c_str(),"");
*/
  // y668: what could be as return value?
  return RetValue;
	// return CEAFModelWrapper::getModelActualSetPoints();  
}

//##ModelId=41470BC400B6
long CEAFGetModelResultWrapper::getMatRecipeSetpoints()
{
  long RetValue = 0;

  // repeat for all different recipes as defined in CRecipeEAF
  // excluding "Total"
  // RecipeNo=0 for EAF. Source a defined in CSourceEAF
  // focusOnRecipeOrig(RecipeName : const string&, RecipeNo : long, Source : const string&, dump : bool)

  // repeat until no values are returned.
	// getMatSetpoint(Code : string&, Mass : double&)


/*Material results will be given to the model by the model interface for following RecipeNames define in CRecipeCodesEAF:
SlagForm                = 0 Batch (Zero Batch) on Levle 1 HMI
MainAlloy                = Main Blow 1 on Level 1 HMI
MainAlloy2ndBatch  = Main Blow 2 on Level 1 HMI
DynBlow                 = Main Blow 3 on Level 1 HMI
Red                        = Reduction
Desul                     = Desulph.
Alloy                      = Alloying
Tap                        = Tapping

RecipeNo=0 for EAF.

Source = EAFBin. Results to be charged over EAFBinSystem
Source = EAFHand These Materials are non bin materials. The operator has to move these data to the chute if he wants to prepare these data in the chute.
Source = EAFChute (data directly directed to a chute(depents on model configuration), will probably not be used because the operator shall move materials to the chute only.) */
  
/*  getMatRecipeSetpoints0(CRecipeEAF::FinalAlloy, CSourceEAF::EAFBin);
  getMatRecipeSetpoints0(CRecipeEAF::FinalAlloy, CSourceEAF::EAFHand);
  getMatRecipeSetpoints0(CRecipeEAF::FinalAlloy, CSourceEAF::EAFChute);
  getMatRecipeSetpoints0(CRecipeEAF::FinalAlloy, CSourceEAF::EAFBinAv);
  getMatRecipeSetpoints0(CRecipeEAF::FinalAlloy, CSourceEAF::EAFHandAv);
  getMatRecipeSetpoints0(CRecipeEAF::FinalAlloy, CSourceEAF::EAFChuteAv);
  getMatRecipeSetpoints0(CRecipeEAF::FinalAlloy, CSourceEAF::EAFBinDef);
  getMatRecipeSetpoints0(CRecipeEAF::FinalAlloy, CSourceEAF::EAFHandDef);
  getMatRecipeSetpoints0(CRecipeEAF::FinalAlloy, CSourceEAF::EAFChuteDef);

  getMatRecipeSetpoints0(CRecipeEAF::SlagForm, CSourceEAF::EAFBin);
  getMatRecipeSetpoints0(CRecipeEAF::SlagForm, CSourceEAF::EAFHand);
  getMatRecipeSetpoints0(CRecipeEAF::SlagForm, CSourceEAF::EAFChute);
  getMatRecipeSetpoints0(CRecipeEAF::SlagForm, CSourceEAF::EAFBinAv);
  getMatRecipeSetpoints0(CRecipeEAF::SlagForm, CSourceEAF::EAFHandAv);
  getMatRecipeSetpoints0(CRecipeEAF::SlagForm, CSourceEAF::EAFChuteAv);
  getMatRecipeSetpoints0(CRecipeEAF::SlagForm, CSourceEAF::EAFBinDef);
  getMatRecipeSetpoints0(CRecipeEAF::SlagForm, CSourceEAF::EAFHandDef);
  getMatRecipeSetpoints0(CRecipeEAF::SlagForm, CSourceEAF::EAFChuteDef);

  getMatRecipeSetpoints0(CRecipeEAF::ScrapChute, CSourceEAF::EAFBin);
  getMatRecipeSetpoints0(CRecipeEAF::ScrapChute, CSourceEAF::EAFHand);
  getMatRecipeSetpoints0(CRecipeEAF::ScrapChute, CSourceEAF::EAFChute);
  getMatRecipeSetpoints0(CRecipeEAF::ScrapChute, CSourceEAF::EAFBinAv);
  getMatRecipeSetpoints0(CRecipeEAF::ScrapChute, CSourceEAF::EAFHandAv);
  getMatRecipeSetpoints0(CRecipeEAF::ScrapChute, CSourceEAF::EAFChuteAv);
  getMatRecipeSetpoints0(CRecipeEAF::ScrapChute, CSourceEAF::EAFBinDef);
  getMatRecipeSetpoints0(CRecipeEAF::ScrapChute, CSourceEAF::EAFHandDef);
  getMatRecipeSetpoints0(CRecipeEAF::ScrapChute, CSourceEAF::EAFChuteDef);

  getMatRecipeSetpoints0(CRecipeEAF::MainAlloy, CSourceEAF::EAFBin);
  getMatRecipeSetpoints0(CRecipeEAF::MainAlloy, CSourceEAF::EAFHand);
  getMatRecipeSetpoints0(CRecipeEAF::MainAlloy, CSourceEAF::EAFChute);
  getMatRecipeSetpoints0(CRecipeEAF::MainAlloy, CSourceEAF::EAFBinAv);
  getMatRecipeSetpoints0(CRecipeEAF::MainAlloy, CSourceEAF::EAFHandAv);
  getMatRecipeSetpoints0(CRecipeEAF::MainAlloy, CSourceEAF::EAFChuteAv);
  getMatRecipeSetpoints0(CRecipeEAF::MainAlloy, CSourceEAF::EAFBinDef);
  getMatRecipeSetpoints0(CRecipeEAF::MainAlloy, CSourceEAF::EAFHandDef);
  getMatRecipeSetpoints0(CRecipeEAF::MainAlloy, CSourceEAF::EAFChuteDef);

  getMatRecipeSetpoints0(CRecipeEAF::MainAlloy2ndBatch, CSourceEAF::EAFBin);
  getMatRecipeSetpoints0(CRecipeEAF::MainAlloy2ndBatch, CSourceEAF::EAFHand);
  getMatRecipeSetpoints0(CRecipeEAF::MainAlloy2ndBatch, CSourceEAF::EAFChute);
  getMatRecipeSetpoints0(CRecipeEAF::MainAlloy2ndBatch, CSourceEAF::EAFBinAv);
  getMatRecipeSetpoints0(CRecipeEAF::MainAlloy2ndBatch, CSourceEAF::EAFHandAv);
  getMatRecipeSetpoints0(CRecipeEAF::MainAlloy2ndBatch, CSourceEAF::EAFChuteAv);
  getMatRecipeSetpoints0(CRecipeEAF::MainAlloy2ndBatch, CSourceEAF::EAFBinDef);
  getMatRecipeSetpoints0(CRecipeEAF::MainAlloy2ndBatch, CSourceEAF::EAFHandDef);
  getMatRecipeSetpoints0(CRecipeEAF::MainAlloy2ndBatch, CSourceEAF::EAFChuteDef);

  getMatRecipeSetpoints0(CRecipeEAF::Desul, CSourceEAF::EAFBin);
  getMatRecipeSetpoints0(CRecipeEAF::Desul, CSourceEAF::EAFHand);
  getMatRecipeSetpoints0(CRecipeEAF::Desul, CSourceEAF::EAFChute);
  getMatRecipeSetpoints0(CRecipeEAF::Desul, CSourceEAF::EAFBinAv);
  getMatRecipeSetpoints0(CRecipeEAF::Desul, CSourceEAF::EAFHandAv);
  getMatRecipeSetpoints0(CRecipeEAF::Desul, CSourceEAF::EAFChuteAv);
  getMatRecipeSetpoints0(CRecipeEAF::Desul, CSourceEAF::EAFBinDef);
  getMatRecipeSetpoints0(CRecipeEAF::Desul, CSourceEAF::EAFHandDef);
  getMatRecipeSetpoints0(CRecipeEAF::Desul, CSourceEAF::EAFChuteDef);

  getMatRecipeSetpoints0(CRecipeEAF::Red, CSourceEAF::EAFBin);
  getMatRecipeSetpoints0(CRecipeEAF::Red, CSourceEAF::EAFHand);
  getMatRecipeSetpoints0(CRecipeEAF::Red, CSourceEAF::EAFChute);
  getMatRecipeSetpoints0(CRecipeEAF::Red, CSourceEAF::EAFBinAv);
  getMatRecipeSetpoints0(CRecipeEAF::Red, CSourceEAF::EAFHandAv);
  getMatRecipeSetpoints0(CRecipeEAF::Red, CSourceEAF::EAFChuteAv);
  getMatRecipeSetpoints0(CRecipeEAF::Red, CSourceEAF::EAFBinDef);
  getMatRecipeSetpoints0(CRecipeEAF::Red, CSourceEAF::EAFHandDef);
  getMatRecipeSetpoints0(CRecipeEAF::Red, CSourceEAF::EAFChuteDef);

  getMatRecipeSetpoints0(CRecipeEAF::Alloy, CSourceEAF::EAFBin);
  getMatRecipeSetpoints0(CRecipeEAF::Alloy, CSourceEAF::EAFHand);
  getMatRecipeSetpoints0(CRecipeEAF::Alloy, CSourceEAF::EAFChute);
  getMatRecipeSetpoints0(CRecipeEAF::Alloy, CSourceEAF::EAFBinAv);
  getMatRecipeSetpoints0(CRecipeEAF::Alloy, CSourceEAF::EAFHandAv);
  getMatRecipeSetpoints0(CRecipeEAF::Alloy, CSourceEAF::EAFChuteAv);
  getMatRecipeSetpoints0(CRecipeEAF::Alloy, CSourceEAF::EAFBinDef);
  getMatRecipeSetpoints0(CRecipeEAF::Alloy, CSourceEAF::EAFHandDef);
  getMatRecipeSetpoints0(CRecipeEAF::Alloy, CSourceEAF::EAFChuteDef);

  getMatRecipeSetpoints0(CRecipeEAF::Tap, CSourceEAF::EAFBin);
  getMatRecipeSetpoints0(CRecipeEAF::Tap, CSourceEAF::EAFHand);
  getMatRecipeSetpoints0(CRecipeEAF::Tap, CSourceEAF::EAFChute);
  getMatRecipeSetpoints0(CRecipeEAF::Tap, CSourceEAF::EAFBinAv);
  getMatRecipeSetpoints0(CRecipeEAF::Tap, CSourceEAF::EAFHandAv);
  getMatRecipeSetpoints0(CRecipeEAF::Tap, CSourceEAF::EAFChuteAv);
  getMatRecipeSetpoints0(CRecipeEAF::Tap, CSourceEAF::EAFBinDef);
  getMatRecipeSetpoints0(CRecipeEAF::Tap, CSourceEAF::EAFHandDef);
  getMatRecipeSetpoints0(CRecipeEAF::Tap, CSourceEAF::EAFChuteDef);

  getMatRecipeSetpoints0(CRecipeEAF::DynBlow, CSourceEAF::EAFBin);
  getMatRecipeSetpoints0(CRecipeEAF::DynBlow, CSourceEAF::EAFHand);
  getMatRecipeSetpoints0(CRecipeEAF::DynBlow, CSourceEAF::EAFChute);
  getMatRecipeSetpoints0(CRecipeEAF::DynBlow, CSourceEAF::EAFBinAv);
  getMatRecipeSetpoints0(CRecipeEAF::DynBlow, CSourceEAF::EAFHandAv);
  getMatRecipeSetpoints0(CRecipeEAF::DynBlow, CSourceEAF::EAFChuteAv);
  getMatRecipeSetpoints0(CRecipeEAF::DynBlow, CSourceEAF::EAFBinDef);
  getMatRecipeSetpoints0(CRecipeEAF::DynBlow, CSourceEAF::EAFHandDef);
  getMatRecipeSetpoints0(CRecipeEAF::DynBlow, CSourceEAF::EAFChuteDef);

  getMatRecipeSetpoints0(CRecipeEAF::ScrapChuteAfterBlow, CSourceEAF::EAFBin);
  getMatRecipeSetpoints0(CRecipeEAF::ScrapChuteAfterBlow, CSourceEAF::EAFHand);
  getMatRecipeSetpoints0(CRecipeEAF::ScrapChuteAfterBlow, CSourceEAF::EAFChute);
  getMatRecipeSetpoints0(CRecipeEAF::ScrapChuteAfterBlow, CSourceEAF::EAFBinAv);
  getMatRecipeSetpoints0(CRecipeEAF::ScrapChuteAfterBlow, CSourceEAF::EAFHandAv);
  getMatRecipeSetpoints0(CRecipeEAF::ScrapChuteAfterBlow, CSourceEAF::EAFChuteAv);
  getMatRecipeSetpoints0(CRecipeEAF::ScrapChuteAfterBlow, CSourceEAF::EAFBinDef);
  getMatRecipeSetpoints0(CRecipeEAF::ScrapChuteAfterBlow, CSourceEAF::EAFHandDef);
  getMatRecipeSetpoints0(CRecipeEAF::ScrapChuteAfterBlow, CSourceEAF::EAFChuteDef);

  getMatRecipeSetpoints0(CRecipeEAF::ReblowAfterRed, CSourceEAF::EAFBin);
  getMatRecipeSetpoints0(CRecipeEAF::ReblowAfterRed, CSourceEAF::EAFHand);
  getMatRecipeSetpoints0(CRecipeEAF::ReblowAfterRed, CSourceEAF::EAFChute);
  getMatRecipeSetpoints0(CRecipeEAF::ReblowAfterRed, CSourceEAF::EAFBinAv);
  getMatRecipeSetpoints0(CRecipeEAF::ReblowAfterRed, CSourceEAF::EAFHandAv);
  getMatRecipeSetpoints0(CRecipeEAF::ReblowAfterRed, CSourceEAF::EAFChuteAv);
  getMatRecipeSetpoints0(CRecipeEAF::ReblowAfterRed, CSourceEAF::EAFBinDef);
  getMatRecipeSetpoints0(CRecipeEAF::ReblowAfterRed, CSourceEAF::EAFHandDef);
  getMatRecipeSetpoints0(CRecipeEAF::ReblowAfterRed, CSourceEAF::EAFChuteDef);
*/
  return RetValue;
}




//##ModelId=4118A79202E2
long CEAFGetModelResultWrapper::getModelResult()
{
	// TODO: Add your specialized code here.
	return (long)0;
}

//##ModelId=4147F9F600E1
long CEAFGetModelResultWrapper::getPredictionCalculationResult()
{
	// ToDo: Add your specialized code here or after the call to base class
	
	return CEAFModelWrapper::getPredictionCalculationResult();
}

