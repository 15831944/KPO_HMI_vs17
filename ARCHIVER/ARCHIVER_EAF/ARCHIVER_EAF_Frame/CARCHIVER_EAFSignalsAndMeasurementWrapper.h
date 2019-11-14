// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_EAFSIGNALSANDMEASUREMENTWRAPPER_41DAC61002DD_INCLUDED
#define _INC_CARCHIVER_EAFSIGNALSANDMEASUREMENTWRAPPER_41DAC61002DD_INCLUDED

#include "CEventMessage.h"

#include "CARCHIVER_SignalsAndMeasurementWrapper.h"

class CPDE_CYCL_MEAS_DATA;
class CPDE_HEAT_DATA;
class CPD_HEAT_DATA_STIRR;
class CPDE_HEAT_DATA_INJ;
class CPDE_HEAT_DATA_BURN;
class CPDE_HEAT_DATA_MELT;
class CPDE_CYCL_MEAS_DATA_INJ;
class CPDE_CYCL_MEAS_DATA_BURN;
class CPD_ELEC_SYSTEM;

//##ModelId=41DAC61002DD
class CARCHIVER_EAFSignalsAndMeasurementWrapper 
  : public CARCHIVER_SignalsAndMeasurementWrapper
{

public:

  //##ModelId=41F11FC300D0
  bool doOnDeslagging(CEventMessage& Event, long status);

  //##ModelId=41DAC848028B
  bool doOnCyclicMeasurement(CEventMessage& Event);

  bool doOnAnalysisReceived(CEventMessage& Event, bool Steel);

  bool doOnSampleTaken(CEventMessage& Event, bool Steel);

  bool doOnTempMeasurement(CEventMessage& Event);

  bool doOnElectrodesInOperatingPosition(CEventMessage& Event);

  bool doOnFurnaceBreaker(CEventMessage& Event, long status);

  bool doOnPower(CEventMessage& Event,long status);

  bool doOnTapChange(CEventMessage& Event, long TapChangStatus);


  bool doOnManipInjectLanceStart(CEventMessage& Event);
  bool doOnManipInjectLanceStop(CEventMessage& Event);

  bool doOnBurnerStart(CEventMessage& Event);
  bool doOnBurnerStop(CEventMessage& Event);

  bool doOnManipGasLanceStart(CEventMessage& Event);
  bool doOnManipGasLanceStop(CEventMessage& Event);

  bool doOnStirrStatusData(CEventMessage& Event, long status);

  bool doOnMechanicalSystem(CEventMessage& Event);

  //##ModelId=41DAC69501A0
  virtual ~CARCHIVER_EAFSignalsAndMeasurementWrapper();

  //##ModelId=41DAC6950291
  CARCHIVER_EAFSignalsAndMeasurementWrapper();

protected:


  //##ModelId=41ED21DA0119
  CPDE_HEAT_DATA* m_pPDE_HEAT_DATA;

  //##ModelId=41DAC6BD00EA
  CPDE_CYCL_MEAS_DATA* m_pPDE_CYCL_MEAS_DATA; 


  CPD_HEAT_DATA_STIRR* m_pPD_HEAT_DATA_STIRR;

  CPD_ELEC_SYSTEM* m_pPD_ELEC_SYSTEM;

  CPDE_CYCL_MEAS_DATA_INJ* m_pPDE_CYCL_MEAS_DATA_INJ;

  CPDE_CYCL_MEAS_DATA_BURN* m_pPDE_CYCL_MEAS_DATA_BURN;

  CPDE_HEAT_DATA_INJ* m_pPDE_HEAT_DATA_INJ;

  CPDE_HEAT_DATA_BURN* m_pPDE_HEAT_DATA_BURN;

  CPDE_HEAT_DATA_MELT* m_pPDE_HEAT_DATA_MELT;


  bool InjLanceWrite(
    const std::string& HeatID, 
    const std::string& TreatID, 
    const std::string& Plant, 
    double durSinceHeatAnnouncement, 
    double durSinceStartOfHeat, 
    double ElecCons, 
    const seqStatus &  InjectorStatus,
    const seqInjectLanceData & InjectLanceAmount, 
    const seqInjectLanceData & InjectLanceFlow);

  bool BurnerWrite(
    const std::string& HeatID, 
    const std::string& TreatID, 
    const std::string& PlantID, 
    double durSinceHeatAnnouncement,
    double durSinceStartOfHeat, 
    double ElecCons, 
    seqStatus & seqBurnerStatus,
    seqStatus & seqGasLanceStatus,
    const seqGasLanceGasAvail & EAFBurnerAvail, 
    const seqGasLanceData & seqBurnerFlow, 
    const seqGasLanceData & seqBurnerAmount,
    const seqGasLanceData & seqGasLanceFlow,   
    const seqGasLanceData & seqGasLanceAmount);

  //##ModelId=41DAC69300F3
  virtual void deleteDBClasses();

  //##ModelId=41DAC69302FC
  virtual void initDBClasses(); 


  bool handleCyclicData(CEventMessage& Event);
  bool handleInjection(CEventMessage& Event);
  bool handleBurner(CEventMessage& Event);
  bool handleMatFeeding(CEventMessage& Event);


};

#endif /* _INC_CARCHIVER_EAFSIGNALSANDMEASUREMENTWRAPPER_41DAC61002DD_INCLUDED */
