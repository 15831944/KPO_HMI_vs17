// Copyright (C) 2004-2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMC_DATAPROVIDER_IMPL_4125E9EC0186_INCLUDED
#define _INC_CSMC_DATAPROVIDER_IMPL_4125E9EC0186_INCLUDED

#include "iSMC_DataProvider_s.hh"

#include "CData_Provider_Impl.h"

#include "CIntfData.h"

#include "cCBS_StdCORBA_Task.h"


class CSMC_DataProvider_Impl 
: public CData_Provider_Impl
, public iSMC_DataProvider
, public POA_iSMC_DataProvider
  
{
protected:
  cCBS_StdCORBA_Task* m_pCorbaTask;

  template<typename SE>
  void SeqToAny(const char* Key, const char* Name, SE Value)
  {
    CORBA::Any anything;
    anything <<= Value;
    CData_Provider_Impl::setAny(Key,Name,anything);
  }

  template<typename SE>
  SE* AnyToSeq(const char* Key, const char* Name, const char* scope)
  {
    if (! m_Critical_Section.lock(std::string(scope)))
    {
      SE* t = new SE();
      return t;
    }

    SE seq;

    CIntfData::FromAny(seq,&CData_Provider::getAny(Key,Name));

    SE* ret = new SE(seq);

    m_Critical_Section.unlock(std::string(scope));

    return ret;
  }

  template<typename ST>
  void StructToAny(const char* Key, const char* Name, ST Value)
  {
    std::string Function = "CSMC_DataProvider_Impl";
    Function += " ";
    Function += Key;
    Function += " ";
    Function += Name;

    CORBA::Any anything;
    anything <<= Value;
    CData_Provider_Impl::setAny(Key,Name,anything);
  }

  template<typename ST>
  void AnyToStruct(ST& Value, const char* Key, const char* Name)
  {

    ST* temp = 0;
      
    CORBA::Any_var ActAny = CData_Provider_Impl::getAny(Key,Name);

    if( ActAny >>= temp )
    {
      Value = *temp;
    }
  }



public:

  static void insertSampleValue(seqSample & SeqSample, const std::string MeasName, double MeasValue);
  static void insertAnalysisValue(seqAnalysis & SeqAnalysis, const std::string Element, double Concentration);
  static sSample getsSample(seqSample & SeqSample, const std::string MeasName);
  static double getSampleValue(seqSample & SeqSample, const std::string MeasName);
  static double getAnalysisValue(seqAnalysis & SeqAnalysis, const std::string MeasName);
  static bool updateAnalysisValue(seqAnalysis & SeqAnalysis, const std::string Element, double Concentration);
  static bool updateSampleValue(seqSample & SeqSample, const std::string MeasName, double MeasValue);

  static bool insertSeqAnalysis(seqAnalysis & SeqActAnalysis, const seqAnalysis SeqAnalysis);
  static bool insertSeqSample(seqSample & SeqActSample, const seqSample SeqSample);

  static bool removeAnalysisEntry(seqAnalysis & SeqAnalysis, const std::string Element);
  static bool removeSampleEntry(seqSample & SeqSample, const std::string MeasName);

  static sAnalysis getsAnalysis(seqAnalysis & SeqAnalysis, const std::string Element);
  static sAnalysisString getsAnalysisString(seqAnalysis & SeqAnalysis, const std::string Element);

  static bool addBatch(seqBatch & SeqBatch, sBatch NewBatch);

  virtual seqConArcBlowData* getConArcBlowData(const char* Key, const char* Name);

  virtual void setConArcBlowData(const char* Key, const char* Name, const seqConArcBlowData& NewData);

  virtual seqConArcModelResult* getConArcModelResult(const char* Key, const char* Name);

  virtual void setConArcModelResult(const char* Key, const char* Name,  const seqConArcModelResult& NewData);

  virtual seqLTSStirrPredRes* getLTSStirrPredRes(const char* Key, const char* Name);

  virtual void setLTSStirrPredRes(const char* Key, const char* Name, const seqLTSStirrPredRes& NewData);

  virtual seqVDModelResult* getVDModelResult(const char* Key, const char* Name);

  virtual void setVDModelResult(const char* Key, const char* Name, const seqVDModelResult& NewData);

  virtual seqInjectData* getInjectData(const char* Key, const char* Name);

  virtual void setInjectData(const char* Key, const char* Name, const seqInjectData& NewData);

  virtual seqStirringData* getStirringData(const char* Key, const char* Name);

  virtual void setStirringData(const char* Key, const char* Name, const seqStirringData& NewData);

  virtual seqMaterials* getMaterials(const char* Key, const char* Name);

  virtual void setMaterials(const char* Key, const char* Name, const seqMaterials& NewData);

  virtual seqEAFMatFeedPredRes* getEAFMatFeedPredRes(const char *Key, const char *Name);
  virtual void setEAFMatFeedPredRes(const char* Key, const char* Name, const seqEAFMatFeedPredRes& NewData);

  virtual seqHMDModelResult *  getHMDModelResult(const char* Key, const char* Name);
  virtual void setHMDModelResult(const char* Key, const char* Name, const seqHMDModelResult& NewData);


  // copy data by names of NameList from one data provider interface to another
  template<typename S>
  static bool copyIntfData(S SourceIntf,  
                           CSMC_DataProvider_Impl* DestIntf, 
                           const std::string& SourceKey, 
                           const std::string& DestKey, 
                           std::vector<std::string>   NameList)
  {
    bool RetValue = false;

    if ( SourceIntf && DestIntf )
    {
      std::vector<std:: string>::iterator itNames;
      for (itNames = NameList.begin() ; itNames != NameList.end() ; ++ itNames)
      {
        CSMC_DataProvider_Impl::copyIntfData(SourceIntf,
                                             DestIntf, 
                                             SourceKey, 
                                             DestKey, 
                                             (*itNames));
      }
    }

    return RetValue;
  }

  // copy data by name from one data provider interface to another
  template<typename S> // must be kind of :_var_type
  static bool copyIntfData( S SourceIntf,  
                            CSMC_DataProvider_Impl* DestIntf, 
                            const std::string& SourceKey, 
                            const std::string& DestKey, 
                            const std::string& Name = "")
  {
    // empty name is realized as "copy all"
    bool RetValue = false;
    if ( SourceIntf && DestIntf )
    {
      seqIntfDataList IntfDataListSeq = SourceIntf->getIntfDataList(SourceKey.c_str());

      for ( long i = 0 ; i < CIntfData::getLength(IntfDataListSeq) ; ++i )
      {
        sIntfDataList IntfDataListStruct;

        CIntfData::getAt(IntfDataListStruct,IntfDataListSeq,i);

        std::string ActName = IntfDataListStruct.Name;
        std::string ActType = IntfDataListStruct.Type;

        if ( Name.empty() || Name == ActName )
        {
          RetValue = CSMC_DataProvider_Impl::readAndWrite(SourceIntf,  
                                                           DestIntf, 
                                                           SourceKey, 
                                                           DestKey, 
                                                           ActType,
                                                           ActName);
        }//if ( Name.empty() || Name == ActName )
      }//for ( long i = 0 ; i < CIntfData::getLength(IntfDataListSeq) ; ++i )
    
    }
    return RetValue;
  }

  // read data from SourceIntf and write data to DestIntf
  // for respective DataKeys, Type and Name
  template<typename S>
  static bool readAndWrite(S SourceIntf,  
                           CSMC_DataProvider_Impl* DestIntf, 
                           const std::string& SourceKey, 
                           const std::string& DestKey, 
                           const std::string& ActType,
                           const std::string& ActName)
  {
    bool RetValue = false;

    try
    {
      if ( ActType== CIntfData::Any )
      {
        RetValue = true;
        DestIntf->setAny(DestKey.c_str(),ActName.c_str(),SourceIntf->getAny(SourceKey.c_str(),ActName.c_str()) );
      }
      else if ( ActType == CIntfData::String )
      {
        RetValue = true;
        DestIntf->setString(DestKey.c_str(),ActName.c_str(),SourceIntf->getString(SourceKey.c_str(),ActName.c_str()) );
      }
      else if ( ActType == CIntfData::Bool )
      {
        RetValue = true;
        DestIntf->setBoolean(DestKey.c_str(),ActName.c_str(),SourceIntf->getBoolean(SourceKey.c_str(),ActName.c_str()));
      }
      else if ( ActType == CIntfData::Long )
      {
        RetValue = true;
        DestIntf->setLong(DestKey.c_str(),ActName.c_str(),SourceIntf->getLong(SourceKey.c_str(),ActName.c_str()));
      }
      else if ( ActType == CIntfData::Double )
      {
        RetValue = true;
        DestIntf->setDouble(DestKey.c_str(),ActName.c_str(),SourceIntf->getDouble(SourceKey.c_str(),ActName.c_str()));
      }
    }
    catch(...)
    {
     // log("CIntfData::readAndWrite() - Exception caught during copying data !",2);
    }
    return RetValue;

  }



  // **********************************************************************************************
  // ***** following functions will allow access to data provider directly                    *****
  // ***** CORBA functionalities like string_dup will not be called to prevent memory leakage *****
  // **********************************************************************************************

  CORBA::Any getAny(const std::string& Key, const std::string& Name);

  bool getBoolean(const std::string& Key, const std::string& Name);

  double getDouble(const std::string& Key, const std::string& Name);

  seqIntfDataList getIntfDataList(const std::string& Key);

  long getLong(const std::string& Key, const std::string& Name);

  std::string getString(const std::string& Key, const std::string& Name);

  void setAny(const std::string& Key, const std::string& Name, CORBA::Any& NewAny);

  void setBoolean(const std::string& Key, const std::string& Name, bool value);

  void setDouble(const std::string& Key, const std::string& Name, double value);

  void setLong(const std::string& Key, const std::string& Name, long value);

  void setString(const std::string& Key, const std::string& Name, const std::string& value);

  std::set<std::string> getIntfReqList(const std::string& Key);

  // ***************************************************************************
  // ***************************************************************************
  // ***************************************************************************
  // ***************************************************************************

  virtual seqElecPhaseData* getElecPhaseData(const char* Key, const char* Name);
  virtual void setElecPhaseData(const char* Key, const char* Name, const seqElecPhaseData& NewData);

  virtual seqBOFBlowPredRes* getBOFBlowPredRes(const char* Key, const char* Name);
  virtual void setBOFBlowPredRes(const char* Key, const char* Name, const seqBOFBlowPredRes& NewData);

  virtual seqBOFGlobalSetpoints* getBOFGlobalSetpoints(const char* Key, const char* Name);
  virtual void setBOFGlobalSetpoints(const char* Key, const char* Name, const seqBOFGlobalSetpoints& NewData);

  virtual seqGasLanceGasAvail* getGasLanceGasAvail(const char* Key, const char* Name);
  virtual void setGasLanceGasAvail(const char* Key, const char* Name, const seqGasLanceGasAvail& NewData);

  void loadEvaluationList();

  virtual void log(const std::string& Message, long Level);

  virtual void EventLogReadFailure(const std::string& Message);

  virtual void EventLogValidationFailure(const std::string& Message);

  void loadRules();

  virtual bool isLoggingOn();

  virtual long getTraceLevel();

  virtual seqLiqMatReport* getLiqMatReport(const char* Key, const char* Name);
  virtual void setLiqMatReport(const char* Key, const char* Name, const seqLiqMatReport& NewData);

  virtual void EventLogExc(const std::string & Message, const std::string& Function, const std::string& Action);

  virtual seqHeatData* getHeatData(const char* Key, const char* Name);
  virtual void setHeatData(const char* Key, const char* Name, const seqHeatData& NewData);

  virtual seqOrderData* getOrderData(const char* Key, const char* Name);
  virtual void setOrderData(const char* Key, const char* Name, const seqOrderData& NewData);

  virtual void setStatus(const char* Key, const char* Name, const seqStatus& NewData);
  virtual seqStatus* getStatus(const char* Key, const char* Name);

  virtual void setAnalysisData(const char* Key, const char* Name, const seqAnalysisData& NewData);
  virtual seqAnalysisData* getAnalysisData(const char* Key, const char* Name);

  virtual void setSampleData(const char* Key, const char* Name, const seqSampleData& NewData);
  virtual seqSampleData* getSampleData(const char* Key, const char* Name);

  virtual void setGasLanceData(const char* Key, const char* Name, const seqGasLanceData& NewData);
  virtual seqGasLanceData* getGasLanceData(const char* Key, const char* Name);

  virtual void setInjectLanceData(const char* Key, const char* Name, const seqInjectLanceData& NewData);
  virtual seqInjectLanceData* getInjectLanceData(const char* Key, const char* Name);

  virtual seqStringList* getStringList(const char* Key, const char* Name);
  virtual void setStringList(const char* Key, const char* Name, const seqStringList& NewData);

  CSMC_DataProvider_Impl();

  virtual ~CSMC_DataProvider_Impl();

  virtual seqRecipeList* getRecipeList(const char* Key, const char* Name);
  virtual void setRecipeList(const char* Key, const char* Name, const seqRecipeList& NewData);

  virtual sDate getDate(const char* Key, const char* Name);
  virtual void setDate(const char* Key, const char* Name, const sDate& NewData);

  virtual seqAnalysis* getAnalysis(const char* Key, const char* Name);
  virtual void setAnalysis(const char* Key, const char* Name, const seqAnalysis& NewData);

  virtual seqAODBlowPredRes* getAODBlowPredRes(const char* Key, const char* Name);
  virtual void setAODBlowPredRes(const char* Key, const char* Name, const seqAODBlowPredRes& NewData);

  virtual seqEAFBurnerPredRes* getEAFBurnerPredRes(const char* Key, const char* Name);
  virtual void setEAFBurnerPredRes(const char* Key, const char* Name, const seqEAFBurnerPredRes& NewData);

  virtual seqAODGlobalSetpoints* getAODGlobalSetpoints(const char* Key, const char* Name);
  virtual void setAODGlobalSetpoints(const char* Key, const char* Name, const seqAODGlobalSetpoints& NewData);

  virtual seqPredRes* getPredRes(const char* Key, const char* Name);
  virtual void setPredRes(const char* Key, const char* Name, const seqPredRes& NewData);

  virtual seqHeatSchedule* getHeatSchedule (const char* Key, const char* Name);
  virtual void setHeatSchedule(const char* Key, const char* Name, 
                               const seqHeatSchedule& NewData);

  virtual seqHeatSchedulePlant * getHeatSchedulePlant (const char* Key, const char* Name);
  virtual void setHeatSchedulePlant(const char* Key, const char* Name, 
                                    const seqHeatSchedulePlant& NewData);

  virtual seqBatch* getBatch(const char* Key, const char* Name);
  virtual void setBatch(const char* Key, const char* Name, const seqBatch& NewData);

  virtual void setProductIdentification(const char* Key, const char* Name, const seqProductIdentification& NewData);
  virtual seqProductIdentification* getProductIdentification(const char* Key, const char* Name);

  virtual void setLFElecPredRes(const char* Key, const char* Name, const seqLFElecPredRes& NewData);
  virtual seqLFElecPredRes* getLFElecPredRes(const char* Key, const char* Name);

  virtual void setLFStirrPredRes(const char* Key, const char* Name, const seqLFStirrPredRes& NewData);
  virtual seqLFStirrPredRes* getLFStirrPredRes(const char* Key, const char* Name);

  virtual void setConArcGlobalSetpoints(const char* Key, const char* Name,  const seqConArcGlobalSetpoints & NewData);
  virtual seqConArcGlobalSetpoints *  getConArcGlobalSetpoints(const char* Key, const char* Name);

  virtual void setRHModelResult(const char* Key, const char* Name,  const seqRHModelResult & NewData);
  virtual seqRHModelResult *  getRHModelResult(const char* Key, const char* Name);

  virtual void setEAFInjectLance(const char* Key, const char* Name, const seqEAFInjectLance& NewData);
  virtual seqEAFInjectLance* getEAFInjectLance(const char* Key, const char* Name);

  virtual void setEAFMatFeed(const char* Key, const char* Name, const seqEAFMatFeed& NewData);
  virtual seqEAFMatFeed* getEAFMatFeed(const char* Key, const char* Name);

  virtual void setEAFGasLancePredRes(const char* Key, const char* Name, const seqEAFGasLancePredRes& NewData);
  virtual seqEAFGasLancePredRes* getEAFGasLancePredRes(const char* Key, const char* Name);

  //virtual void setEAFElecPredRes(const char* Key, const char* Name, const seqEAFElecPredRes& NewData);
  //virtual seqEAFElecPredRes* getEAFElecPredRes(const char* Key, const char* Name);

  void setEAFProcessPredRes(const char* Key, const char * Name, const seqEAFProcessPredRes& NewData);
  seqEAFProcessPredRes* getEAFProcessPredRes(const char* Key,const char* Name);
  virtual seqGasAvail* getGasAvail     (const char* Key, const char* Name);
  virtual void setGasAvail (const char* Key, const char* Name, const seqGasAvail& NewData);

  virtual seqWasteGas* getWasteGas     (const char* Key, const char* Name);
  virtual void setWasteGas(const char* Key, const char* Name, const seqWasteGas& NewData);

  virtual seqWireFeeder *getWireFeeder (const char* Key, const char* Name);
  virtual void setWireFeeder (const char* Key, const char* Name, const seqWireFeeder& NewData);

  virtual seqCoolWaterData *getCoolWaterData (const char* Key, const char* Name);
  virtual void setCoolWaterData(const char* Key, const char* Name, const seqCoolWaterData& NewData);

  virtual seqComputerModes *getComputerModes (const char* Key, const char* Name);
  virtual void setComputerModes(const char* Key, const char* Name, const seqComputerModes& NewData);

  virtual seqGasData *getGasData (const char* Key, const char* Name);
  virtual void setGasData (const char* Key, const char* Name, const seqGasData& NewData);

  virtual seqBlowStatus *getBlowStatus (const char* Key, const char* Name);
  virtual void setBlowStatus (const char* Key, const char* Name, const seqBlowStatus& NewData);

  virtual seqPhaseStatus *getPhaseStatus (const char* Key, const char* Name);
  virtual void setPhaseStatus (const char* Key, const char* Name, const seqPhaseStatus& NewData);

  std::string generateDataKey(const std::string& Value);

  virtual void setConArcElecData (const char* Key, const char* Name,    const seqConArcElecData  & NewData);
  virtual seqConArcElecData* getConArcElecData (const char* Key, const char* Name);

  virtual void setConArcMediaData (const char* Key, const char* Name, const seqConArcMediaData& NewData);
  virtual seqConArcMediaData* getConArcMediaData (const char* Key, const char* Name);

  virtual void setConArcSetptData (const char* Key, const char* Name, const seqConArcSetptData& NewData);
  virtual seqConArcSetptData* getConArcSetptData (const char* Key, const char* Name);

  virtual void setConArcMeasData (const char* Key, const char* Name, const seqConArcMeasData& NewData);
  virtual seqConArcMeasData* getConArcMeasData (const char* Key, const char* Name);

  virtual seqSample* getSample(const char* Key, const char* Name);
  virtual void setSample(const char* Key, const char* Name, const seqSample& NewData);

  virtual void setPhaseDataReport(const char* Key, const char * Name, const seqPhaseDataReport& NewData);
  virtual seqPhaseDataReport* getPhaseDataReport(const char* Key, const char* Name);
  virtual void setTorpedoData(const char* Key, const char * Name, const seqTorpedoData& NewData);
  virtual seqTorpedoData* getTorpedoData(const char* Key, const char* Name);
  virtual void setEquipmentLifeData(const char* Key, const char * Name, const seqEquipmentLifeData& NewData);
  virtual seqEquipmentLifeData* getEquipmentLifeData(const char* Key, const char* Name);

  void setPPRestriction(const char* Key, const char * Name, const seqPPRestriction& NewData);
  seqPPRestriction* getPPRestriction(const char* Key, const char* Name);

  void setHeatStack(const char* Key, const char * Name, const seqHeatStack& NewData);
  seqHeatStack* getHeatStack(const char* Key, const char* Name);

  seqMediaConsumed* getMediaConsumed(const char* Key, const char* Name);
  void setMediaConsumed(const char* Key, const char* Name, const seqMediaConsumed& NewData);

  seqEnergyConsumed* getEnergyConsumed(const char* Key, const char* Name);
  void setEnergyConsumed(const char* Key, const char* Name, const seqEnergyConsumed& NewData);

  seqSAF_Bin* getSAFBinData(const char* Key, const char* Name);
  void setSAFBinData(const char* Key, const char* Name, const seqSAF_Bin& NewData);

  seqHarmonics* getHarmonics(const char* Key, const char* Name);
  void setHarmonics(const char* Key, const char* Name, const seqHarmonics& NewData);

  seqWallTemp* getWallTemp(const char* Key, const char* Name);
  void setWallTemp(const char* Key, const char* Name, const seqWallTemp& NewData);

  seqHMPouringData* getHMPouringData(const char* Key, const char* Name);
  void setHMPouringData(const char* Key, const char * Name, const seqHMPouringData& NewData);
};

#endif /* _INC_CSMC_DATAPROVIDER_IMPL_4125E9EC0186_INCLUDED */
