// Copyright (C) 2009 SMS Demag AG

#include "iData_Provider_s.hh"

#include <string>
#include "cCBS_StdLog_Task.h"
#include "CSMC_EventLogFrameController.h"
#include "CIntfData.h"
#include "CDateTime.h"

#include "CARCHIVER_Task.h"
#include "CPD_PRETREATDATA.h"
#include "CPD_PLANTSTATUS.h"
#include "CPD_HEAT_REF.h"
#include "CPD_HEAT_PLANT_REF.h"
#include "CPD_HEAT_DATA.h"
#include "CPD_HEAT_DATA_LIQADD.h"
#include "CGC_STATUS.h"
#include "CPD_SAMPLE_REF.h"

#include "DEF_GC_STATUS.h"

#include "CARCHIVER_Wrapper.h"


CARCHIVER_Wrapper::~CARCHIVER_Wrapper()
{
}

CARCHIVER_Wrapper::CARCHIVER_Wrapper() 
{
}

void CARCHIVER_Wrapper::log(const std::string& Message,long Level)
{
  if ( Level <= getTraceLevel() )
  {
    cCBS_StdLog_Task::getInstance()->log(Message,Level);
  }
}

void CARCHIVER_Wrapper::log(const char* Message, long Level)
{
  if ( Level <= getTraceLevel() )
  {
    cCBS_StdLog_Task::getInstance()->log(Message,Level);
  }
}

long CARCHIVER_Wrapper::getTraceLevel()
{
  return cCBS_StdLog_Task::getInstance()->getTraceLevel();
}

void CARCHIVER_Wrapper::setpDM_Interface(const std::string& ServerName, const std::string& InterfaceTypeName)
{
  m_pDM_Interface = 0;

  if (m_pArchiverTask)
  {
    m_pArchiverTask->setpDM_Interface(ServerName,InterfaceTypeName);

    m_pDM_Interface = m_pArchiverTask->getpDM_Interface();
  }
}

void CARCHIVER_Wrapper::setTaskAndInitDBClasses(CARCHIVER_Task* value)
{
  m_pArchiverTask = value;

  if (m_pArchiverTask->getStdConnection())
  {
    initDBClasses();
  }
  else
  {
    log("ERROR: setTaskAndInitDBClasses: call initDBClasses() not possible. NO CONNECTION!", 1);
  }
}

bool CARCHIVER_Wrapper::checkDBConnection()
{
  log("CARCHIVER_Wrapper::checkDBConnection()",4);

  bool RetValue = false;

  if ( m_pArchiverTask )
  {
    RetValue = m_pArchiverTask->checkDBConnection();

    if ( !RetValue )
    {
      m_pArchiverTask->handleDBConnectionError();

      RetValue = m_pArchiverTask->checkDBConnection();
    }
  }

  return RetValue;
}

cCBS_StdConnection* CARCHIVER_Wrapper::getStdConnection()
{
  cCBS_StdConnection *pConnection = 0;

  if ( m_pArchiverTask )
  {
    pConnection = m_pArchiverTask->getStdConnection();
  }

  return pConnection;
}

void CARCHIVER_Wrapper::handleDBConnectionError()
{
  if ( m_pArchiverTask )
  {
    m_pArchiverTask->handleDBConnectionError();
  }
}


void CARCHIVER_Wrapper::logInterfaceDataList(DM::iDM_Interface_var& pDM_Interface,const std::string &Datakey)
{
  if (pDM_Interface)
  {
    // to avoid iteration and making CORBA unnecessary calls
    if ( 3 < cCBS_StdLog_Task::getInstance()->getTraceLevel())
    {
      std::stringstream LogMessage;
      std::string Key = Datakey;

      seqIntfDataList IntfDataListSeq = CIntfData::ToCORBAType(pDM_Interface->getIntfDataList(Key.c_str()));

      
      LogMessage << "Data available at DM for Datakey " 
                << Key
                << std::endl;

      for ( long i = 0 ; i < CIntfData::getLength(IntfDataListSeq) ; ++i )
      {
        bool UseActName = false;
        sIntfDataList IntfDataListStruct;

        CIntfData::getAt(IntfDataListStruct,IntfDataListSeq,i);

        std::string ActName = IntfDataListStruct.Name;
        std::string ActType = IntfDataListStruct.Type;

        LogMessage << ActName 
                  << " " 
                  << ActType 
                  << std::endl;
      }

      log(LogMessage.str(),3);
    }
  }
}

double CARCHIVER_Wrapper::getDurationSince(DM::iDM_Interface_var& pDM_Interface,const std::string &Key, const char* Name)
{
  double Dur = DEF::Inv_Double;

  if (pDM_Interface)
  {
    std::stringstream LogMessage;
    LogMessage << " Calculate duration since:";
    LogMessage << Name;


    CDateTime now;
    CDateTime start;
    CDeltaTime dtTime;

    start.SetTime(pDM_Interface->getDate(Key.c_str(), Name));

    if ( start != CDateTime::InvalidDateTime() )
    {
   	  dtTime = CDateTime::subTimes(now, start);
	    Dur    = dtTime.asSeconds() / 60.;
    }
    else
    {
	    Dur = 0.;
    }

    LogMessage << ". Duration (min): " << Dur;
    log(LogMessage.str(),3);
  }
  return Dur;
}

bool CARCHIVER_Wrapper::handleSampleRef( const std::string& HEATID, const std::string& TREATID,const std::string& PLANT, long PLANTNO, long MeasType, long SampleCounter)
{
  bool RetValue = false;

  long SampleRef = -1;
  bool IsSampleRefCreated = false;

  cCBS_StdConnection *pConnection = getStdConnection();

  CPD_HEAT_DATA         PD_HEAT_DATA(pConnection);
  CPD_HEAT_PLANT_REF    PD_HEAT_PLANT_REF(pConnection);
  CGC_STATUS            GC_STATUS(pConnection);
  CPD_SAMPLE_REF        PD_SAMPLE_REF(pConnection);
  CPD_HEAT_DATA_LIQADD  PD_HEAT_DATA_LIQADD(pConnection);

  // check for existing sample reference, insert nwe one if required and update PD_HEAT_DATA
  if ( PD_HEAT_DATA.select(HEATID, TREATID, PLANT) )
  {
    RetValue = true;

    // determine existing or new SAMPLE_REF
    SampleRef = PD_HEAT_DATA.getSAMPLE_REF(1);

    if ( SampleRef == CSMC_DBData::unspecLong )
    {
      SampleRef = PD_SAMPLE_REF.insertNewSAMPLE_REF(false);

      PD_HEAT_DATA.setSAMPLE_REF(SampleRef);

      RetValue = RetValue && PD_HEAT_DATA.update();
    }

    RetValue = RetValue && PD_SAMPLE_REF.updateSAMPLE_REF(SampleRef, SampleCounter ,MeasType, false, m_lastError);

    if (RetValue)
    {
      PD_HEAT_DATA.commit();
    }
    else
    {
      PD_HEAT_DATA.rollback();
    }
  }

  //If After Heat Ann but before Start of Heat, then update pd_Heat_data_liqadd related sample_ref
  if(PD_HEAT_PLANT_REF.select(HEATID, TREATID, PLANT))
  {
    long LiqAddSampelRef = -1;

    long Status        = PD_HEAT_PLANT_REF.getSTATUSNO(1);
    long HeatAnnStatus = GC_STATUS.getStatusNo(PLANT,DEF_GC_STATUS::HeatAnnounced);

    if(Status == HeatAnnStatus)
    {
      if(PD_HEAT_DATA_LIQADD.select(HEATID,TREATID,PLANT,PLANTNO))
      {
        LiqAddSampelRef = PD_HEAT_DATA_LIQADD.getSAMPLE_REF(1);

        RetValue = RetValue && PD_SAMPLE_REF.updateSAMPLE_REF(LiqAddSampelRef, SampleCounter, MeasType);
      }
    }
  }

  return RetValue;
}

//this structure need to be initialize, otherwize some random would exist and lead to error for save
void CARCHIVER_Wrapper::initialSampleRef(sSampleRef &pSample)
{
  pSample.mAluminium = -1;
  pSample.mCarbon = -1;
  pSample.mCelogSlag = -1;
  pSample.mEMF = -1;
  pSample.mHydrogen = -1;
  pSample.mOxygen = -1;
  pSample.mSlag = -1;
  pSample.mSlagCalc = -1;
  pSample.mSteel = -1;
  pSample.mSteelCalc = -1;
  pSample.mTemp = -1;
  pSample.mTempCalc = -1;
}

bool CARCHIVER_Wrapper::changeHeatStatus(CEventMessage& Event, long HeatStatusNo, long TreatmentPosition,bool commit)
{
  bool RetValue = true;

  CPD_PLANTSTATUS  PD_PLANTSTATUS (m_pArchiverTask->getStdConnection());
  CPD_HEAT_REF     PD_HEAT_REF    (m_pArchiverTask->getStdConnection());

  std::string HeatID    = Event.getHeatID();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

  if( PD_PLANTSTATUS.select(ActPlant,ActPlantNo,TreatmentPosition) )
  {
    if( HeatStatusNo > -1 )
    {
      PD_PLANTSTATUS.setHEATSTATUSNO(HeatStatusNo);
      RetValue = PD_PLANTSTATUS.update();
    }
  } 

  RetValue = RetValue && PD_HEAT_REF.switchHeatStatusNo(HeatID, HeatStatusNo, CSMC_DBData::unspecString, false, commit, m_lastError);
  
  if( commit )
  {
    if ( RetValue ) 
    {
      PD_HEAT_REF.commit();
    }
    else
    {
      PD_HEAT_REF.rollback();
    }
  }

  return RetValue;
}
