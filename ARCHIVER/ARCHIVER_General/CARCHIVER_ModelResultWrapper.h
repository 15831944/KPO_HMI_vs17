// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_MODELREASULTWRAPPER_45D58257025F_INCLUDED
#define _INC_CARCHIVER_MODELREASULTWRAPPER_45D58257025F_INCLUDED

#include "CARCHIVER_Wrapper.h"
#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"

#include "CGC_MEASUREMENT_NAME.h"
#include "CChem_Elem_Container.h"
#include "CGC_PHASE.h"
#include "CGC_PHASE_RES_PLANT.h"

#include "CGT_MAT.h"
#include "CGT_MAT_PURP.h"
#include "CGC_Plant_Container.h"

#include "CPD_ACTION.h"
#include "CPD_HEAT_DATA.h"
#include "CPD_MAT_FEED_RES.h"
#include "CPD_PHASE_RES.h"
#include "CPD_PHASE_RES_PLANT.h"
#include "CPD_PLANTSTATUS.h"
#include "CPD_Phase_Res.h"
#include "CPD_RECIPE.h"
#include "CPD_RECIPE_ENTRY.h"
#include "CPD_SAMPLE.h"
#include "CPD_SAMPLE_REF.h"

//##ModelId=45D58257025F
class CARCHIVER_ModelResultWrapper 
: public CARCHIVER_Wrapper
{
public:
	//##ModelId=45D5829901D4
	CARCHIVER_ModelResultWrapper();

	//##ModelId=45D5829A003A
	virtual ~CARCHIVER_ModelResultWrapper();

	//##ModelId=45D582D5013A
	bool handleGenParameterUpdate(CEventMessage& Event);

	//##ModelId=45D582D50158
	bool handleRecipeSetpoints(CEventMessage& Event, seqRecipeList& SeqRecipeList);



  long   getResPhaseNo(std::string PhaseName, long PhaseNo ,std::string Plant);
  double getDurUntEndOfPhase(const std::string & HeatID, const std::string & TreatID, const std::string & Plant, long ResPhaseNo);
  double getDurUntEndOfPhase(const std::string & HeatID, const std::string & TreatID, const std::string & Plant, const std::string & PhaseName, long PhaseNo);
  double getPhaseDuration(const std::string & HeatID, const std::string & TreatID, const std::string & Plant, const std::string & PhaseName, long PhaseNo, const std::string & PrevPhaseName = CSMC_DBData::unspecString, long PrevPhaseNo = CSMC_DBData::unspecLong);
  double getPhaseDuration(const std::string & HeatID, const std::string & TreatID, const std::string & Plant, long ResPhaseNo, long PrevResPhaseNo = CSMC_DBData::unspecLong);

protected:

  CGC_MEASUREMENT_NAME * m_pGC_MEASUREMENT_NAME;
  CChem_Elem_Container * m_pChem_Elem_Container;

  CGC_PHASE* m_pGC_PHASE;

  CGC_PHASE_RES_PLANT* m_pGC_PHASE_RES_PLANT;

  CGC_Plant_Container *m_pGC_Plant_Container;

  CGT_MAT* m_pGT_MAT;

  CGT_MAT_PURP* m_pGT_MAT_PURP;

  CPD_ACTION* m_pPD_ACTION;

  CPD_HEAT_DATA *m_pPD_HEAT_DATA;

  CPD_MAT_FEED_RES* m_pPD_MAT_FEED_RES;

  CPD_PHASE_RES* m_pPD_PHASE_RES;

  CPD_PHASE_RES_PLANT* m_pPD_PHASE_RES_PLANT;

  CPD_PLANTSTATUS* m_pPD_PLANTSTATUS;

  CPD_RECIPE* m_pPD_RECIPE;

  CPD_RECIPE_ENTRY* m_pPD_RECIPE_ENTRY;

  CPD_SAMPLE * m_pPD_SAMPLE;

  CPD_SAMPLE_REF * m_pPD_SAMPLE_REF;

	//##ModelId=45D5829E025A
	virtual void initDBClasses();

	//##ModelId=45D5829F00FD
	virtual void deleteDBClasses();

  bool writeCalculatedAnalysis(const std::string & HeatID, const std::string & TreatID, const std::string & Plant, long PlantNo, long SampleRef, seqAnalysis& SeqAnalysis, double Temp, bool commit);

  bool writeFinalCalculatedAnalysis(const std::string & HeatID, const std::string & TreatID, const std::string & Plant, long PlantNo, long SampleRef, seqAnalysis& SeqAnalysis, double Temp, bool commit);

};

#endif /* _INC_CARCHIVER_MODELREASULTWRAPPER_45D58257025F_INCLUDED */