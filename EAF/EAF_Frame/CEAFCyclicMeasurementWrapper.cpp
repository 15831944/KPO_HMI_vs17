// Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"

#include "CIntfData.h"
#include "CDataConversion.h"

#include "CStirringDataHandler.h"

// Note: The file CIntfEAF.h includes Config.h with definitions which can be used within the Wrapper
#include "CIntfEAF.h"
#include "CKeyStringsEAF.h"

#include "CEAFModelTask.h"


#include "DEF_GCE_BURNER.h"
#include "DEF_GCE_INJECTION.h"
#include "DEF_GCE_INJECTION_TYPE.h"
#include "DEF_GC_COOLWATER.h"
#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GCE_BURNER_GASTYPE.h"

#include "CGCE_BURNER.h"
#include "CGCE_INJECTION.h"
#include "CGCE_INJECTION_TYPE.h"
#include "CGasLanceDataHandler.h"

#include "CEAFCyclicMeasurementWrapper.h"

//##ModelId=411276A3006C
bool CEAFCyclicMeasurementWrapper::doOnCyclicMeasurement( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();
  if (!pIntfEAF ) return false;

  if (!m_pModelTask) 
  {
    log("error CEAFCyclicMeasurementWrapper::doOnCyclicMeasurement, (m_pModelTask) == false", 1);
    return false;
  }

  try
  {
    std::string PlantID   = Event.getPlantID();
    std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
    long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

    long              SeqLength   = 0;
    long              GetAtValue  = 0;
    std::string       Device, DeviceCons;
    std::string       GasType;

    pIntfEAF->indicateCycMeas();

    // get Electric Consumtion
    double ElecCons = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PLANT)->getDouble(DEF_PLANT::Furnace, DATA::ElecCons );
                      

    std::stringstream tmp_elec;
    tmp_elec << "******* electrical data *********" << endl
             << " ElecCons     : "   << ElecCons << endl;

    pIntfEAF->setMeasElecCons(ElecCons);

    CEAFModelTask::getInstance()->setStateDetails(DATA::ElecCons, tmp_elec.str(),4);

#if defined (EAF_INJECTION_LANCES) 
    seqInjectLanceData   InjLanceFlow, InjLanceCons;
    sInjectLanceData     LanceDataFlow, LanceDataCons;

    InjLanceFlow    = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PRODUCT)->getInjectLanceData(
      Event.getProductID().c_str(), DATA::InjectLanceFlow));
    InjLanceCons    = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PRODUCT)->getInjectLanceData(
      Event.getProductID().c_str(), DATA::InjectLanceAmount));

    std::stringstream tmp_carbon_lance;
    tmp_carbon_lance << "******* injection lance data *********" << endl;

    SeqLength = CIntfData::getLength(InjLanceFlow);
    for (int x = 0; x < SeqLength; x++) 
    {
      long SubSeqLong;
      GetAtValue  = CIntfData::getAt(LanceDataFlow, InjLanceFlow, x);

      Device      = LanceDataFlow.Device;

      //find device of flow in amount sequence and provide data to model
      SubSeqLong = CIntfData::getLength(InjLanceCons);
      for (int z = 0; z < SubSeqLong; z++) 
      {
        GetAtValue  = CIntfData::getAt(LanceDataCons, InjLanceCons, z);
        DeviceCons  = LanceDataCons.Device;

        // find purpose code for current injection type
        std::string InjectionType = LanceDataCons.InjectionType;

        std::string RelatedPurpCode = m_pGCE_INJECTION_TYPE->getPurposeCodeByInjType(InjectionType);

        if (Device == DeviceCons)
        {     
          tmp_carbon_lance    << "RelatedPurpCode : "   << RelatedPurpCode
            << " LanceDataCons.Value : "   << LanceDataCons.Value
            << " LanceDataFlow.Value : "   << LanceDataFlow.Value << endl;

          pIntfEAF->setMeasManipInjectLanceCons(RelatedPurpCode, LanceDataCons.Value, LanceDataFlow.Value);
        }
      }
    }// for (int x = 0; x < SeqLength; x++) 
    CEAFModelTask::getInstance()->setStateDetails(DATA::InjectLanceAmount, tmp_carbon_lance.str(),4);
#endif

    ///////////////////////////
    // mrut : JSL ??
    //Burner Data for EAF-DRI and O2 injection for EAF-Fecr handling
    //Note: setMeasManipGasLanceCons(..) used for EAF-FeCr(O2 injection) and setMeasBurnerCons(..) used for EAF-DRI(O2,Gas)
    ///////////////////////////


    double TotalO2Flow = 0;           // mrut 2013-09-09 JSW for Feeding rate adaption

#if defined (EAF_BURNER)
    if (  m_pGCE_BURNER )
    {

    // mrut 2014-12-09  get the data  from gas lance sequence, as it is used also for burner data.
    seqGasLanceData  BurnerFlow, BurnerCons;

    BurnerFlow    = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PRODUCT)->getGasLanceData(
                    Event.getProductID().c_str(), DATA::GasLanceFlow));
    BurnerCons    = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PRODUCT)->getGasLanceData(
                    Event.getProductID().c_str(), DATA::GasLanceAmount));


    std::stringstream tmp_burner;
    tmp_burner << "******* burner data *********" << endl;
    CGasLanceDataHandler GasLanceDataHandlerBurnerFlow   (BurnerFlow);
    CGasLanceDataHandler GasLanceDataHandlerBurnerAmount (BurnerCons);

    std::set<std::string> DeviceListBurner = GasLanceDataHandlerBurnerAmount.getDeviceList();
    std::set<std::string>::iterator itBurner ;

    for ( itBurner = DeviceListBurner.begin() ; itBurner != DeviceListBurner.end(); ++itBurner)
    {
      std::string Device  = (*itBurner);

      long DeviceNo       = m_pGCE_BURNER->getBurnerNoByPlant(ActPlant,ActPlantNo,Device);

      if ( (DeviceNo != CSMC_DBData::unspecLong)  && (DeviceNo != CInv::InvalidLong) )
      {
        double O2Cons = GasLanceDataHandlerBurnerAmount.getGasValue (Device, DEF_GCE_BURNER_GASTYPE::O2) ;
        double BGCons = GasLanceDataHandlerBurnerAmount.getGasValue (Device, DEF_GCE_BURNER_GASTYPE::BG) ;
        double O2Flow = GasLanceDataHandlerBurnerFlow.getGasValue   (Device, DEF_GCE_BURNER_GASTYPE::O2) ;
        double BGFlow = GasLanceDataHandlerBurnerFlow.getGasValue   (Device, DEF_GCE_BURNER_GASTYPE::BG) ;

        // to do : check unit in data from L1
        if  ( (O2Flow) >= 1.)        // mrut 2013-09-09 JSW for Feeding rate adaption
          TotalO2Flow += O2Flow;

        // model need flow in Nm�/min
        O2Flow=O2Flow/60.;
        BGFlow=BGFlow/60.;

        tmp_burner << Device
          << " DeviceNo:  " << DeviceNo 
          << " BGCons : "   << BGCons 
          << " O2Cons : "   << O2Cons 
          << " BGFlow : "   << BGFlow
          << " O2Flow : "   << O2Flow << endl;
        pIntfEAF->setMeasBurnerCons(DeviceNo,BGCons,O2Cons,BGFlow,O2Flow,0);
      }

      }

    CEAFModelTask::getInstance()->setStateDetails(DATA::BurnerAmount, tmp_burner.str(), 4);
    } // end if (  m_pGCE_BURNER )
#endif

#if defined (EAF_GAS_LANCES)

    seqGasLanceData   GasLanceFlow, GasLanceCons;

    GasLanceFlow    = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PRODUCT)->getGasLanceData(
                    Event.getProductID().c_str(), DATA::GasLanceFlow));
    GasLanceCons    = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PRODUCT)->getGasLanceData(
                    Event.getProductID().c_str(), DATA::GasLanceAmount));


    std::stringstream tmp_gas;
    tmp_gas << "******* gas lances data *********" << endl;
    CGasLanceDataHandler GasLanceDataHandlerGasLanceFlow(GasLanceFlow);
    CGasLanceDataHandler GasLanceDataHandlerGasLanceAmount(GasLanceCons);

    std::set<std::string> DeviceListLances = GasLanceDataHandlerGasLanceAmount.getDeviceList();
    std::set<std::string>::iterator itLances ;

    for ( itLances = DeviceListLances.begin() ; itLances != DeviceListLances.end(); ++itLances)
    {
      std::string Device  = (*itLances);
      long DeviceNo       = 0;

      double O2Cons = GasLanceDataHandlerGasLanceAmount.getGasValue(Device, DEF_GAS::O2) ;
      double O2Flow = GasLanceDataHandlerGasLanceFlow.getGasValue  (Device, DEF_GAS::O2) ;

      // to do : check unit in data from L1
      if  ( (O2Flow) >= 1.)        // mrut 2013-09-09 JSW for Feeding rate adaption
        TotalO2Flow += O2Flow;

      // model need flow in Nm�/min
      //O2Flow=O2Flow/60.;

      if ( m_pGCE_INJECTION )
      {
        DeviceNo = m_pGCE_INJECTION->getL1DeviceNo(ActPlant,ActPlantNo,Device);

        tmp_gas << " DeviceNo : "  << DeviceNo
          << " GasType : "   << DEF_GAS::O2
          << " O2Cons : "    << O2Cons
          << " O2Flow : "    << O2Flow << endl;
        pIntfEAF->setMeasManipGasLanceCons(DeviceNo,DEF_GAS::O2, O2Cons, O2Flow); 
      }
    }
    CEAFModelTask::getInstance()->setStateDetails(DATA::BurnerAmount, tmp_gas.str(),4);
#endif


#if defined (EAF_PATTERN_FEEDING) || defined (EAF_DYNAMIC_FEEDING)
    seqBatch sqMatFeedingBatch;
    sBatch sBatchMatFeedingData;

    sqMatFeedingBatch = CIntfData::ToCORBAType
      (m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PRODUCT)->getBatch(Event.getProductID().c_str(), DATA::MatFeedingData));

    std::stringstream tmp_mat_feed;
    tmp_mat_feed << "******* mat feeding data *********" << endl;

    for (int x = 0; x < CIntfData::getLength(sqMatFeedingBatch); x++) 
    {
      GetAtValue  = CIntfData::getAt(sBatchMatFeedingData, sqMatFeedingBatch, x);
      if ( string(sBatchMatFeedingData.MatCode) != string(DEF::Inv_String) && !string(sBatchMatFeedingData.MatCode).empty() )
      {
        tmp_mat_feed << "Batch given to model " <<  x+1 <<  endl
          << "MatCode : "        << sBatchMatFeedingData.MatCode
          << " Mass : "           << sBatchMatFeedingData.Mass
          << " MatFeedSpeed : "   << sBatchMatFeedingData.MatFeedSpeed << endl;

        pIntfEAF->setMeasFeedingCons(string(sBatchMatFeedingData.MatCode),sBatchMatFeedingData.Mass,sBatchMatFeedingData.MatFeedSpeed);
      }
      else
      {
        tmp_mat_feed << "Batch not given to model " <<  x+1 <<  endl
          << "MatCode : "        << sBatchMatFeedingData.MatCode
          << " Mass : "           << sBatchMatFeedingData.Mass
          << " MatFeedSpeed : "   << sBatchMatFeedingData.MatFeedSpeed << endl;
      }
    }

    CEAFModelTask::getInstance()->setStateDetails(DATA::MatFeedingData, tmp_mat_feed.str(), 4);
#endif

    // get Waste Gas Data
    double WGasTemp = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PLANT)->getDouble(
                        DEF_PLANT::Furnace, DATA::WasteGasTemp );
    double WGasFlow = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PLANT)->getDouble(
                        DEF_PLANT::Furnace, DATA::WasteGasFlow );

    std::stringstream tmp_waste_gas;
    tmp_waste_gas << "******* waste gas data *********" << endl
                  << "WGasTemp : "        << WGasTemp << endl
                  << "WGasFlow : "        << WGasFlow << endl;
            

    // we don't use it for fuxin
    // pIntfEAF->setMeasWasteGasData(WGasTemp, WGasFlow);

    //CEAFModelTask::getInstance()->setStateDetails(DATA::WasteGasFlow, tmp_waste_gas.str(),4);


    // doOnGetCoolWaterData( )
    seqCoolWaterData  CoolData;
    sCoolWaterDevice  DeviceData;

    CoolData    = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PLANT)->
                                         getCoolWaterData(DEF_PLANT::Furnace, DATA::CoolingWaterData));
    std::stringstream tmp_cool_water;
    tmp_cool_water << "******* cool water data *********" << endl;

    SeqLength = CIntfData::getLength(CoolData);
    for (int x = 0; x < SeqLength; x++) 
    {
      GetAtValue  = CIntfData::getAt(DeviceData, CoolData, x);
      Device      = DeviceData.CoolWaterDevice;

      if ( DeviceData.CoolWaterData.WaterFlow > 0. )
      {
        if ( Device == DEF_GC_COOLWATER::Roof  ) 
        {
          tmp_cool_water << "Device "    <<  Device
            << " InletTemp : "   << DeviceData.CoolWaterData.InletTemp
            << " OutletTemp : "  << DeviceData.CoolWaterData.OutletTemp 
            << " WaterFlow : "   << DeviceData.CoolWaterData.WaterFlow  << endl;

          pIntfEAF->setMeasCoolWaterRoofData( DeviceData.CoolWaterData.InletTemp,
            DeviceData.CoolWaterData.OutletTemp,
            DeviceData.CoolWaterData.WaterFlow / 60. );          // Nm�/h -> Nm�/min
        }
        else if ( Device == DEF_GC_COOLWATER::Elbow  )
        {
          tmp_cool_water << "Device "    <<  Device
            << " InletTemp : "   << DeviceData.CoolWaterData.InletTemp
            << " OutletTemp : "  << DeviceData.CoolWaterData.OutletTemp 
            << " WaterFlow : "   << DeviceData.CoolWaterData.WaterFlow  << endl;

          pIntfEAF->setMeasCoolWaterElbowData(DeviceData.CoolWaterData.InletTemp,
            DeviceData.CoolWaterData.OutletTemp,
            DeviceData.CoolWaterData.WaterFlow / 60. );          // Nm�/h -> Nm�/min
        }
        else if ( Device == DEF_GC_COOLWATER::Dedusting  )
        {
          tmp_cool_water << "Device "    <<  Device
            << " InletTemp : "   << DeviceData.CoolWaterData.InletTemp
            << " OutletTemp : "  << DeviceData.CoolWaterData.OutletTemp 
            << " WaterFlow : "   << DeviceData.CoolWaterData.WaterFlow  << endl;

          pIntfEAF->setMeasCoolWaterDuctData( DeviceData.CoolWaterData.InletTemp,
            DeviceData.CoolWaterData.OutletTemp,
            DeviceData.CoolWaterData.WaterFlow / 60. );          // Nm�/h -> Nm�/min
        }
        else if ( Device == DEF_GC_COOLWATER::Wall  )
        {
          tmp_cool_water << "Device "    <<  Device
            << " InletTemp : "   << DeviceData.CoolWaterData.InletTemp
            << " OutletTemp : "  << DeviceData.CoolWaterData.OutletTemp 
            << " WaterFlow : "   << DeviceData.CoolWaterData.WaterFlow  << endl;;

          pIntfEAF->setMeasCoolWaterTotalData(DeviceData.CoolWaterData.InletTemp,
            DeviceData.CoolWaterData.OutletTemp,
            DeviceData.CoolWaterData.WaterFlow / 60. );          // Nm�/h -> Nm�/min
        }
        else if ( Device == DEF_GC_COOLWATER::Wall  )
        {
          tmp_cool_water << "Device "    <<  Device
            << " InletTemp : "   << DeviceData.CoolWaterData.InletTemp
            << " OutletTemp : "  << DeviceData.CoolWaterData.OutletTemp 
            << " WaterFlow : "   << DeviceData.CoolWaterData.WaterFlow  << endl;

          pIntfEAF->setMeasCoolWaterTotalData(DeviceData.CoolWaterData.InletTemp,
            DeviceData.CoolWaterData.OutletTemp,
            DeviceData.CoolWaterData.WaterFlow / 60. );          // Nm�/h -> Nm�/min
        }
      }//if ( DeviceData.CoolWaterData.WaterFlow > 0. ) 

      if ( Device == DEF_GC_COOLWATER::DoorPanel  )
      {
        tmp_cool_water << "Device "    <<  Device
          << " id : "   << 400+DeviceData.CoolWaterDeviceNo
          << " InletTemp : "   << DeviceData.CoolWaterData.InletTemp
          << " OutletTemp : "  << DeviceData.CoolWaterData.OutletTemp << endl;

        //INSERT INTO GT_PARAM_MATRIX ( UNITGROUPNO, PNAME, PRACNO, TYPE, KEY1, KEY2, VALUE ) VALUES ( 
        //12, 'PanelType_WTC', 0, 7, '401', '0', 'DoorPnl'); 
        pIntfEAF->setMeasCoolWaterElemData(400+DeviceData.CoolWaterDeviceNo,  DeviceData.CoolWaterData.InletTemp, DeviceData.CoolWaterData.OutletTemp);          // Nm�/h -> Nm�/min
      }
      else if ( Device == DEF_GC_COOLWATER::DoorTunelPanel  )
      {
        tmp_cool_water << "Device "    <<  Device
          << " id : "   << 410+DeviceData.CoolWaterDeviceNo
          << " InletTemp : "   << DeviceData.CoolWaterData.InletTemp
          << " OutletTemp : "  << DeviceData.CoolWaterData.OutletTemp << endl;

        //INSERT INTO GT_PARAM_MATRIX ( UNITGROUPNO, PNAME, PRACNO, TYPE, KEY1, KEY2, VALUE ) VALUES ( 
        //12, 'PanelType_WTC', 0, 7, '411', '0', 'DoorPnl');
        pIntfEAF->setMeasCoolWaterElemData(410+DeviceData.CoolWaterDeviceNo,  DeviceData.CoolWaterData.InletTemp, DeviceData.CoolWaterData.OutletTemp);          // Nm�/h -> Nm�/min
      }
      else if ( Device == DEF_GC_COOLWATER::CoverBay  )
      {
        tmp_cool_water << "Device "    <<  Device
          << " id : "   << 300+DeviceData.CoolWaterDeviceNo
          << " InletTemp : "   << DeviceData.CoolWaterData.InletTemp
          << " OutletTemp : "  << DeviceData.CoolWaterData.OutletTemp << endl;

        //INSERT INTO GT_PARAM_MATRIX ( UNITGROUPNO, PNAME, PRACNO, TYPE, KEY1, KEY2, VALUE ) VALUES ( 
        //12, 'PanelType_WTC', 0, 7, '301', '0', 'BayPnl'); 
        //INSERT INTO GT_PARAM_MATRIX ( UNITGROUPNO, PNAME, PRACNO, TYPE, KEY1, KEY2, VALUE ) VALUES ( 
        //12, 'PanelType_WTC', 0, 7, '302', '0', 'BayPnl'); 
        //INSERT INTO GT_PARAM_MATRIX ( UNITGROUPNO, PNAME, PRACNO, TYPE, KEY1, KEY2, VALUE ) VALUES ( 
        //12, 'PanelType_WTC', 0, 7, '303', '0', 'BayPnl'); 
        pIntfEAF->setMeasCoolWaterElemData(300+DeviceData.CoolWaterDeviceNo,  DeviceData.CoolWaterData.InletTemp, DeviceData.CoolWaterData.OutletTemp);          // Nm�/h -> Nm�/min
      }      
      else if ( Device == DEF_GC_COOLWATER::WallUpPanelLoop  )
      {
        tmp_cool_water << "Device "    <<  Device
          << " id : "   << 100+DeviceData.CoolWaterDeviceNo
          << " InletTemp : "   << DeviceData.CoolWaterData.InletTemp
          << " OutletTemp : "  << DeviceData.CoolWaterData.OutletTemp 
          << " WaterFlow : "   << DeviceData.CoolWaterData.WaterFlow  << endl;

        //INSERT INTO GT_PARAM_MATRIX ( UNITGROUPNO, PNAME, PRACNO, TYPE, KEY1, KEY2, VALUE ) VALUES ( 
        //12, 'PanelType_WTC', 0, 7, '-1', '0', 'WallPnl'); 
        pIntfEAF->setMeasCoolWaterElemData(100+DeviceData.CoolWaterDeviceNo,  DeviceData.CoolWaterData.InletTemp, DeviceData.CoolWaterData.OutletTemp);          // Nm�/h -> Nm�/min
      }
      else if ( Device == DEF_GC_COOLWATER::WallLowPanelLoop  )
      {
        tmp_cool_water << "Device "    <<  Device
          << " id : "   << 200+DeviceData.CoolWaterDeviceNo
          << " InletTemp : "   << DeviceData.CoolWaterData.InletTemp
          << " OutletTemp : "  << DeviceData.CoolWaterData.OutletTemp 
          << " WaterFlow : "   << DeviceData.CoolWaterData.WaterFlow  << endl;

        //INSERT INTO GT_PARAM_MATRIX ( UNITGROUPNO, PNAME, PRACNO, TYPE, KEY1, KEY2, VALUE ) VALUES ( 
        //12, 'PanelType_WTC', 0, 7, '-1', '0', 'WallPnl'); 
        pIntfEAF->setMeasCoolWaterElemData(200+DeviceData.CoolWaterDeviceNo,  DeviceData.CoolWaterData.InletTemp, DeviceData.CoolWaterData.OutletTemp);          // Nm�/h -> Nm�/min
      }
    }// for (int x = 0; x < SeqLength; x++) 

    CEAFModelTask::getInstance()->setStateDetails(DATA::CoolingWaterData, tmp_cool_water.str(),4);

    /////////////////////////////////////
    // get Furnace Bottom Stirring Data
    /////////////////////////////////////
    if( ActPlant == DEF_GC_PLANT_DEF::EAF ) // ActPlant may be EAFCr    mrut : ???????
    {
    #if defined (EAF_BOTTOM_STIRRING)

      // read stirring data from PRODUCT-Interface 
      double StirrAmount = 0. ;
      double StirrFlow   = 0. ; 

      std::string     GasType         = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PRODUCT)->getString(Event.getProductID().c_str(), DATA::StirringGasType ));
      seqStirringData StirringFlow    = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PRODUCT)->getStirringData(Event.getProductID().c_str(), DATA::StirringFlow ));
      seqStirringData StirringAmount  = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PRODUCT)->getStirringData(Event.getProductID().c_str(), DATA::StirringAmount));

      CStirringDataHandler StirringFlowHandler(StirringFlow);
      seqGasData GasDataFlow = StirringFlowHandler.getAccumulatedGasDataSeq();      // equals obsolete DEF_DEVICES::Total

      CStirringDataHandler StirringAmountHandler(StirringAmount);
      seqGasData GasDataAmount = StirringAmountHandler.getAccumulatedGasDataSeq();  // equals obsolete DEF_DEVICES::Total
      
      log("***********************StirringFlow**************************************",4);
      log(CIntfData::getContent(CIntfData::ToAny(StirringFlow)),4);

      log("***********************StirringAmount**************************************",4);
      log(CIntfData::getContent(CIntfData::ToAny(StirringAmount)),4);

      if ( GasType == DEF_GAS::Ar || 
           GasType == DEF_GAS::N2 )
      {
        for(int i = 0; i < CIntfData::getLength(GasDataFlow); i++)
        {
          sGasData GasData;
          CIntfData::getAt(GasData,GasDataFlow,i);

          if ( GasType == std::string(GasData.GasType) )
          {
            StirrFlow = GasData.GasValue;
          }
        }
        for(int j = 0; j < CIntfData::getLength(GasDataAmount); j++)
        {
          sGasData GasData;
          CIntfData::getAt(GasData,GasDataAmount,j);

          if ( GasType == std::string(GasData.GasType) )
          {
            StirrAmount = GasData.GasValue;
          }
        }

      }
      else
      {
        log("*** no data for stirr gas, set defaults - gas to N2 - values to 0. ***", 1);
        GasType     = DEF_GAS::N2;
        StirrFlow   = 0.;
        StirrAmount = 0.;
      }

      StirrFlow   = StirrFlow;  //Nm3/h-> Nm3/min is done in DH_IN
      StirrAmount = StirrAmount;  

      std::stringstream tmp;
      tmp <<"The result of Gas data to give to model" << endl
          << "GasType    : " << GasType   << endl
          << "StirrFlow  : " << StirrFlow   << " [Nm3/min]" << endl
          << "StirrAmount: " << StirrAmount << " [Nm3]" << endl;
      log(tmp.str(), 2);
      
      pIntfEAF->setMeasFurnBottomStirringData(GasType, StirrFlow, StirrAmount); 

    #endif
    }

    

    pIntfEAF->hndlEvent();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CEAFCyclicMeasurementWrapper::doOnCyclicMeasurement",  ""  );          
  }


  return RetValue;
}

