// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLFModelResultWrapper_4118CC3401F4_INCLUDED
#define _INC_CLFModelResultWrapper_4118CC3401F4_INCLUDED

#include "CIntfLF.h"
#include "CLFModelWrapper.h"
#include "CEventMessage.h"
#include "CLFModelTask.h"

class CLFModelResultWrapper : public CLFModelWrapper
  
{
public:

	virtual ~CLFModelResultWrapper();

	CLFModelResultWrapper();

	virtual bool doModelResult(CEventMessage& Event);

private:

	virtual bool doResultGeneral(CEventMessage& Event);

	virtual bool doModelActualSetpoints(CEventMessage& Event);

	virtual bool doMatRecipeSetpoints(CEventMessage& Event);

	bool getModelResultsAtStatus(const std::string& HeatID, const std::string& TreatID, const std::string& Plant, const std::string & Phase, long PhaseNo, seqPredRes& seqPredRes);

	void getMatRecipeSetpoints(const std::string & Plant, long PlantNo, const std::string & RecipeName, long RecipeNo, const std::string & Source, seqRecipeList &MatRecList);

  void getPredCalcResults(double & TotalRemHeatingDur, seqLFElecPredRes  & ElecPredRes, seqLFStirrPredRes & StirrPredRes);

  bool isActualProcessPhase(const std::string& Phase, long PhaseNo);

  double getDurationSince(DM::iDM_Interface_var& pDM_Interface,const std::string &Key, const char* Name);

  //****** writes new calculated setpoints to DataBase ****************************************
  bool writeActualSetpointsToDB(CEventMessage &Event,
                                const seqPredRes            &SeqPredRes,
                                const seqLFElecPredRes      &SeqLFElecPredRes,
                                const seqComputerModes      &ComputerModeAvail,
                                const seqLFStirrPredRes     &SeqLFStirrPredRes);

  //****** writes new calculated setpoints to DataBase ****************************************
  bool writeRecipeSetpointsToDB(CEventMessage &Event,  seqRecipeList  &SeqRecipeList);             // DATA::LFMatRecipe
  //-------------------------------------------------------------------------------------------


};

#endif /* _INC_CLFModelResultWrapper_4118CC3401F4_INCLUDED */
