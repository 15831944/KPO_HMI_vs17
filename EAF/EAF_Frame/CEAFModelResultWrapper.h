// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFModelResultWrapper_4118CC3401F4_INCLUDED
#define _INC_CEAFModelResultWrapper_4118CC3401F4_INCLUDED

#include "CEAFModelTask.h"
#include "CEAFModelWrapper.h"

#include "cCBS_StdEventLogFrameController.h"
#include "CEventMessage.h"

#include "CSMC_RecipeHandler.h"


//##ModelId=45EBDA4001B0
class CEAFModelResultWrapper : public CEAFModelWrapper  
{
private:

  // mrut 2013-09-09 JSW aligns result pattern of type T to (electrical) steps in sequence 'process' (seqEAFProcessPredRes)
  template<class T> 
  void alignResultPattern_1(const seqEAFProcessPredRes  &  ProcPredRes, bool LoggingOn, const std::string & ResultSeqName, const double Dur_Ref, const double Egy_Ref, T & PredResultToAlign);
  template<class T> 
  void alignResultPattern_2(const seqEAFProcessPredRes  &  ProcPredRes, bool LoggingOn, const std::string & ResultSeqName, const double Dur_Ref, const double Egy_Ref, T & PredResultToAlign);
  template<class T> 
  void alignResultPattern_3(const seqEAFProcessPredRes  &  ProcPredRes, bool LoggingOn, const std::string & ResultSeqName, const double Dur_Ref, const double Egy_Ref, T & PredResultToAlign);

  // calculates injected amounts per step and adds or replaces values in passed sequence
  bool calculateInjectionAmounts(seqEAFInjectLance & SeqEAFInjectLance);

  // mrut 2014-02-06, work on JIRA SMPJSWTWO-47 determination of material amount for feeding
  // calculates amounts per step of the feeding pattern ( process pattern) and adds or replaces values in passed sequence
  bool calculateMatFeedingPatternAmounts(seqEAFMatFeedPredRes  & MatFeedPredRes, long CurrentlyActiveStepMatFeed);

	//##ModelId=467645DE0398
  bool doModelGeneralResult(CEventMessage &Event);

  //##ModelId=45EBDA4001DC
  bool doModelActualSetpoints(CEventMessage &Event,const std::string& Old_Key);

  //##ModelId=45EBDA4001DF
  bool doMatRecipeSetpoints(CEventMessage &Event);

  //##ModelId=45EBDA4001E1
  bool getModelResultsAtStatus( const std::string& HeatID, const std::string& TreatID, const std::string& Plant, 
                                const std::string&  Phase, 
                                long                PhaseNo, 
                                seqPredRes&         SeqPredRes);

   //##ModelId=45EBDA4001ED
  void getPredCalcResults(  const std::string& Plant, long PlantNo,
                            const std::string&      Phase, 
                            long                    BasketNo,
                            seqEAFProcessPredRes&   ElecPredRes, 
                            seqEAFGasLancePredRes&  GasLancePredRes, 
                            seqEAFInjectLance&      InjctPredRes, 
                            seqEAFGasLancePredRes&  BottomStirrPredRes,
                            double                  BaseMass);

	//##ModelId=45EBDA4001F4
  void getPredCalcResults(  const std::string& Plant, long PlantNo,
                            const std::string&      Phase, 
                            long                    BasketNo,
                            seqEAFMatFeedPredRes&   MatFeedPredRes, 
                            double                  BaseMass);

	//##ModelId=45EBDA400203
  void getPredCalcResults(  const std::string& Plant, long PlantNo,
                            const std::string& Phase, 
                            long                    BasketNo, 
                            seqEAFBurnerPredRes&  BurnerPredRes, 
                            double                  BaseMass);

  void getMatRecipeSetpoints( const std::string& Plant, 
                              const long         PlantNo,     
                              const std::string& treatid, 
                              const std::string& RecipeName, 
                              const long         RecipeNo, 
                              const std::string& Source, 
                              seqRecipeList&     MatRecList);

  bool isActualProcessPhase(const std::string& Phase, long PhaseNo);

  //--------------------- moved from CARCHIVER_EAFModelResultsWrapper to CEAFModelResultWrapper

  double getDurationSince(DM::iDM_Interface_var& pDM_Interface,const std::string &Key, const char* Name);
  
  //****** writes new calculated setpoints to DataBase ****************************************
  bool writeActualSetpointsToDB(CEventMessage &Event,
                                const seqPredRes            &SeqPredRes,                 // DATA::EAFPredRes
                                const seqEAFProcessPredRes  &SeqProcessPredRes,          // DATA::EAFProcessPredRes
                                const seqEAFGasLancePredRes &SeqGasLancePredRes,         // DATA::EAFGasLancePredRes
                                const seqEAFInjectLance     &SeqInjectLanceRes,          // DATA::EAFInjectLance
                                const seqComputerModes      &SeqComputerModes,           // DATA::ComputerModeAvail
                                const seqEAFBurnerPredRes   &SeqBurnerPredRes,           // DATA::EAFBurnerPredRes
                                const seqEAFMatFeedPredRes  &SeqMatFeedPredRes,          // DATA::EAFMatFeedPredRes
                                const seqEAFGasLancePredRes &SeqBottomStirrPredRes,      // DATA::EAFBottomStirrPredRes
                                const seqGasLanceData       &SegEAFBurnerAmount,         // DATA::EAFBurnerAmount
                                const seqInjectLanceData    &SegEAFInjectLanceAmount);   // DATA::EAFInjectLanceAmount

  //****** writes new calculated setpoints to DataBase ****************************************
  bool writeRecipeSetpointsToDB(CEventMessage &Event, seqRecipeList &SeqRecipeList);             // DATA::EAFMatRecipe
  //-------------------------------------------------------------------------------------------

public:

  //##ModelId=45EBDA40021E
  CEAFModelResultWrapper();

  //##ModelId=45EBDA40021C
  virtual ~CEAFModelResultWrapper();

  //##ModelId=45EBDA400214
  bool doModelResult(CEventMessage &Event);

  bool doModelResult(CEventMessage &Event, CEAFModelWrapper& ToCallBack);
};

#endif /* _INC_CEAFModelResultWrapper_4118CC3401F4_INCLUDED */
