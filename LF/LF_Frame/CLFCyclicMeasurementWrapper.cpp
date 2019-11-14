// Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"

#include "cCBS_StdEventLogFrameController.h"

#include "CIntfData.h"
#include "CSMC_EventLogLFController.h"

#include "CDataConversion.h"
#include "CStirringDataHandler.h"

#include "DEF_GC_COOLWATER.h"
#include "DEF_GC_STIRR_GAS_TYPE.h"

#include "CIntfLF.h"
#include "CLFModelTask.h"

#include "CLFCyclicMeasurementWrapper.h"


//##ModelId=41124A0202FC
bool CLFCyclicMeasurementWrapper::doOnCyclicMeasurements(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFCyclicMeasurementWrapper::doOnCyclicMeasurements(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }

  try
  {
    pIntfLF->indicateCycMeas();

    // read electical data from PLANT-Interface using respective TransferCarid 
    // TransferCarid will be set as Task during heat announcement !
    std::string LadleTransferCarID = m_pModelTask->getActProcessData(DATA::LadleTransferCarId);

    if ( LadleTransferCarID == DEF::Inv_String )
    {
      CSMC_EventLogLF *pEventLog = CSMC_EventLogLFController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorTransferCarIdentification(sMessage,"");
    }

    std::string mes_DataKey = "The Key for reading ElecData is: ";
    mes_DataKey += LadleTransferCarID;
    log(mes_DataKey, 5);

    double ElecCons  = m_pModelTask->getpDM_Interface(Event.getSender(),CLFModelTask::PLANT)->getDouble(LadleTransferCarID.c_str(), DATA::ElecCons );

    long VoltTap     = m_pModelTask->getpDM_Interface(Event.getSender(),CLFModelTask::PLANT)->getLong(LadleTransferCarID.c_str(), DATA::VoltTapNo );

    long RegCurve    = m_pModelTask->getpDM_Interface(Event.getSender(),CLFModelTask::PLANT)->getLong(LadleTransferCarID.c_str(), DATA::ElectrodRegCurve );

    ElecCons  = CDataConversion::SetInvalidToDefault(ElecCons ,0.);
    VoltTap   = CDataConversion::SetInvalidToDefault(VoltTap  ,0);
    RegCurve  = CDataConversion::SetInvalidToDefault(RegCurve ,0);

    std::stringstream tmp_elec;
    tmp_elec << "******* electrical data ********* TransferCar: " <<LadleTransferCarID << endl
      << "ElecCons : "   << ElecCons << endl
      << "VoltTap  : "   << VoltTap  << endl
      << "RegCurve : "   << RegCurve << endl;

    pIntfLF->setMeasElecCons(ElecCons, VoltTap, RegCurve); 

    CLFModelTask::getInstance()->setStateDetails(DATA::ElecCons, tmp_elec.str(),4);

    
    log("******* coolwater data *********", 4);
    // read CoolingWater data from PLANT-Interface using key for LadleTransferCarID
    // we could have twin shell lf with two different roofs
    seqCoolWaterData SeqCoolWaterData  = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CLFModelTask::PLANT)->getCoolWaterData(LadleTransferCarID.c_str(), DATA::CoolingWaterData ));

    log(CIntfData::getContent(CIntfData::ToAny(SeqCoolWaterData)),4);

    //if car is not in Operating Position do not hand over Cooling Water data 
    long LadleCarPosition   = m_pModelTask->getpDM_Interface(Event.getSender(),CLFModelTask::PLANT)->getLong(LadleTransferCarID.c_str(),DATA::LadleCarPosition);

    std::stringstream tmp_pos;
    tmp_pos << LadleTransferCarID << endl;
    tmp_pos << "Ladle Position: " << LadleCarPosition << ", "; 

    if (LadleCarPosition == DEF_CARPOSITION::OperationPositon)
      tmp_pos << "Operationg Position" << endl;
    else if (LadleCarPosition == DEF_CARPOSITION::OutOfOperatingPosition)
      tmp_pos << "Out of Operationg Position" << endl;
    else if (LadleCarPosition == DEF_CARPOSITION::DeslagPosition)
      tmp_pos << "Deslaging Position" << endl;
    else if (LadleCarPosition == DEF::Inv_Long)
      tmp_pos << "Not known" << endl;
    else
      tmp_pos << "Fatal Error. Not known" << endl;

    log(tmp_pos.str(),2);
    CLFModelTask::getInstance()->setStateDetails(DATA::LadleCarPosition, tmp_pos.str(),4);

    std::stringstream tmp_cool;
    tmp_cool <<"The result of cool data to give to model" << endl;

    for (int k = 0; k < CIntfData::getLength(SeqCoolWaterData); k++)
    {
      sCoolWaterDevice CoolWaterDevice;
      CIntfData::getAt(CoolWaterDevice,SeqCoolWaterData,k);


      //if car is not in Operatinbg Position reset WaterFLow to 0.
      if (LadleCarPosition != DEF_CARPOSITION::OperationPositon && LadleCarPosition != DEF::Inv_Long)
      {
        CoolWaterDevice.CoolWaterData.WaterFlow = 0.;

        tmp_cool  << "Car out of Operating Position : Set CoolWaterFow to 0"  << endl
          << "WaterFlow      : "  << CoolWaterDevice.CoolWaterData.WaterFlow;
      }

      // only DEF_GC_COOLWATER::Roof data will be regarded by model !
      if ((std::string)CoolWaterDevice.CoolWaterDevice == DEF_GC_COOLWATER::Roof)
      {
        log("***Data for cooling water found*******", 3);

        if ( CoolWaterDevice.CoolWaterData.OutletTemp >= CoolWaterDevice.CoolWaterData.InletTemp )
        {
          tmp_cool << "CoolWaterDevice: "  << CoolWaterDevice.CoolWaterDevice            << endl
            << "InletTemp      : "  << CoolWaterDevice.CoolWaterData.InletTemp    << endl
            << "OutletTemp     : "  << CoolWaterDevice.CoolWaterData.OutletTemp   << endl
            << "WaterFlow      : "  << CoolWaterDevice.CoolWaterData.WaterFlow;

          // model expects Nm³/min
          pIntfLF->setMeasCoolWaterData(CoolWaterDevice.CoolWaterData.InletTemp, CoolWaterDevice.CoolWaterData.OutletTemp, CoolWaterDevice.CoolWaterData.WaterFlow / 60.);

        }
        else
        {
          CSMC_EventLogLF *pEventLog = CSMC_EventLogLFController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorProcessingData(sMessage,"CLFCyclicMeasurementWrapper::doOnCyclicMeasurements :: Cooling water data", "InletTemp > OutletTemp");
        }

        break; 
      }
    }

    CLFModelTask::getInstance()->setStateDetails(DATA::CoolingWaterData, tmp_cool.str(),4);

    // read stirring data from PRODUCT-Interface 
    double ArStirrAmount = 0. ;
    double ArStirrFlow   = 0. ;
    double N2StirrAmount = 0. ;
    double N2StirrFlow   = 0. ; 

    seqStirringData StirringFlow    = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CLFModelTask::PRODUCT)->getStirringData(Event.getProductID().c_str(), DATA::StirringFlow ));
    seqStirringData StirringAmount  = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CLFModelTask::PRODUCT)->getStirringData(Event.getProductID().c_str(), DATA::StirringAmount));

    CStirringDataHandler StirringFlowHandler(StirringFlow);
    seqGasData GasDataFlow = StirringFlowHandler.getAccumulatedGasDataSeq();      // equals obsolete DEF_DEVICES::Total

    CStirringDataHandler StirringAmountHandler(StirringAmount);
    seqGasData GasDataAmount = StirringAmountHandler.getAccumulatedGasDataSeq();  // equals obsolete DEF_DEVICES::Total

    log("***********************StirringFlow**************************************",4);
    log(CIntfData::getContent(CIntfData::ToAny(StirringFlow)),4);

    log("***********************StirringAmount**************************************",4);
    log(CIntfData::getContent(CIntfData::ToAny(StirringAmount)),4);

    std::stringstream tmp_stirr;
    tmp_stirr <<"The result of stirr gas data to give to model" << endl;

    for(int i = 0; i < CIntfData::getLength(GasDataFlow); i++)
    {
      sGasData GasData;
      CIntfData::getAt(GasData,GasDataFlow,i);

      if ( std::string(GasData.GasType) == DEF_GC_STIRR_GAS_TYPE::Ar )
      {
        ArStirrFlow += GasData.GasValue;
      }
      else if ( std::string(GasData.GasType) == DEF_GC_STIRR_GAS_TYPE::N2 )
      {
        N2StirrFlow += GasData.GasValue;
      }
    }

    for(int j = 0; j < CIntfData::getLength(GasDataAmount); j++)
    {
      sGasData GasData;
      CIntfData::getAt(GasData,GasDataAmount,j);

      if ( std::string(GasData.GasType) == DEF_GC_STIRR_GAS_TYPE::Ar)
      {
        ArStirrAmount += GasData.GasValue;
      }
      else if ( std::string(GasData.GasType) == DEF_GC_STIRR_GAS_TYPE::N2 )
      {
        N2StirrAmount += GasData.GasValue;
      }
    }

    if (ArStirrFlow > 0.)
    {
      ArStirrFlow   = ArStirrFlow / 60.0;  //Nm3/h-> Nm3/min
      
      tmp_stirr  << "GasType    : " << DEF_GC_STIRR_GAS_TYPE::Ar << endl
        << "StirrFlow  : " << ArStirrFlow   << " [Nm3/min]" << endl
        << "StirrAmount: " << ArStirrAmount << " [Nm3]" << endl;

      pIntfLF->setMeasInertGasData(DEF_GC_STIRR_GAS_TYPE::Ar, ArStirrFlow, ArStirrAmount, 0.);
      CLFModelTask::getInstance()->setStateDetails(DATA::StirringAmount, tmp_stirr.str(),4);
    }

    if (N2StirrFlow > 0.)
    {
      N2StirrFlow   = N2StirrFlow / 60.0;  //Nm3/h-> Nm3/min

      tmp_stirr  << "GasType    : " << DEF_GC_STIRR_GAS_TYPE::N2   << endl
        << "StirrFlow  : " << N2StirrFlow   << " [Nm3/min]" << endl
        << "StirrAmount: " << N2StirrAmount << " [Nm3]" << endl;

      pIntfLF->setMeasInertGasData(DEF_GC_STIRR_GAS_TYPE::N2, N2StirrFlow, N2StirrAmount, 0.);
      CLFModelTask::getInstance()->setStateDetails(DATA::StirringAmount, tmp_stirr.str(),4);
    }

    pIntfLF->hndlEvent();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);

  } 
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFCyclicMeasurementWrapper::doOnCyclicMeasurement()", ""  );    
  }

  return RetValue;
}