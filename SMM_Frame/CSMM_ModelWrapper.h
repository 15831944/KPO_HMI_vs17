// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMM_ModelWrapper_4118A55C0130_INCLUDED
#define _INC_CSMM_ModelWrapper_4118A55C0130_INCLUDED

#include <string>
#include <limits>

#include "CSMM_ModelTask.h"
#include "CGC_Plant_Container.h"
#include "CChem_Elem_Container.h"
#include "CModelWrapper.h"


class CEventMessage;
class CGC_Plant_Container;
class CChem_Elem_Container;

class CSMM_ModelWrapper : public CModelWrapper 
{
protected:

  CSMM_ModelWrapper();

  long m_HeatPredCalcNo;

  long m_HeatCyclCalcNo;

  static std::string m_PrevSetpointsKey;

  std::string m_Key;  

  //****** writes new calculated setpoints to DataBase ****************************************
  bool writeRecipeSetpointsToDB(CEventMessage& Event, 
                                const seqRecipeList &SeqRecipeList, 
                                double DurSinceHeatAnnounce, 
                                double DurSinceHeatStart);
  //-------------------------------------------------------------------------------------------

  //****** updates new calculated setpoints to DataBase ****************************************
  bool updateRecipeSetpointsToDB(CEventMessage& Event, 
                                const seqRecipeList &SeqRecipeList);
  //-------------------------------------------------------------------------------------------

  //****** writes new calculated analysis to DataBase ****************************************
  bool writeCalculatedAnalysis(CEventMessage& Event,
                               long SampleRef,
                               seqAnalysis& SeqAnalysis,
                               double Temp,
                               bool Commit);

  //****** writes new calculated final analysis to DataBase ****************************************
  bool writeFinalCalculatedAnalysis(CEventMessage& Event,
                                    long SampleRef, 
                                    seqAnalysis& SeqAnalysis, 
                                    double Temp, 
                                    bool Commit);

  //****** writes new weights and temperature to DataBase ****************************************
  bool writeCalculatedWeightsAndTemp(CEventMessage& Event,
                                     double SteelWeightCalc, 
                                     double SlagWeightCalc, 
                                     double TempCalc, 
                                     bool Commit);

  CGC_Plant_Container*  m_pGC_Plant_Container;
  CChem_Elem_Container* m_pChem_Elem_Container;

public:
  virtual void initDBClasses() = 0;

  virtual void deleteDBClasses() = 0;

  // this method will check if the DB classes are initialized
  // to prevent operations on nullpointers this method should be called first
  virtual bool checkDBConnection(); 

  void setpModelTask(CModelTask* pModelTask);

  virtual ~CSMM_ModelWrapper();

  virtual bool doResultCodeAndMessage(CEventMessage &Event);

  virtual bool doMatRecipeSetpoints(CEventMessage &Event);

  virtual bool doModelResult(CEventMessage &Event);

  virtual bool doModelHeatStatus(CEventMessage &Event);

  long getTypeOfCalc();

  //This methode gets the heat identification out of the 
  //incomming event information
  long getHeatIdetificationData();

  //If the heat identification is valid calculation if 
  //getModelHeatStatus gives the same heat or that no heat 
  //is announced.
  long ValidateEvent();

  cCBS_StdConnection * getStdConnection();

};

#endif /* _INC_CSMM_ModelWrapper_4118A55C0130_INCLUDED */
