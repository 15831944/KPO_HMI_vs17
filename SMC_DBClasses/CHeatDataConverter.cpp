// Copyright (C) 2004, 2005 SMS Demag AG, Germany 

#include "CSMC_EventLogFrameController.h"
#include "cCBS_StdInitBase.h"
#include "CTreatID.h"

#include "CPD_HEAT_PLANT_REF.h"
#include "CPD_HEAT_DATA.h"
#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_PLANT_DEF.h"

#include "CHeatDataConverter.h"

//##ModelId=441037CD01E6
CHeatDataConverter::CHeatDataConverter(cCBS_StdConnection* Connection)
{
  m_pPD_HEAT_PLANT_REF  = new CPD_HEAT_PLANT_REF(Connection);
  m_pPD_HEAT_DATA  = new CPD_HEAT_DATA(Connection);

  //get the translation list from the config file
  std::vector<std::string> Plants;
  std::vector<std::string> Prefixes;
  cCBS_StdInitBase::getInstance()->replaceWithEntry("PLANT","TreatIDPlants",Plants);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("PLANT","TreatIDPrefixes",Prefixes);
  
  long Length = Plants.size();

  if ( Prefixes.size() == Length )
  {
    for ( long i=0; i<Length; i++ )
    {
      m_PlantTreatIDPrefixTrans.insert(std::pair<std::string,std::string>(Plants[i],Prefixes[i]));
    }
  }
  else
  {
    std::string ErrorMessage = "Configuration error, plants and prefixes do not match!";
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorMessage(sMessage, ErrorMessage.c_str());
  }
}

//##ModelId=441037CE004E
CHeatDataConverter::~CHeatDataConverter()
{
  if (m_pPD_HEAT_PLANT_REF) { delete m_pPD_HEAT_PLANT_REF; m_pPD_HEAT_PLANT_REF = 0;}
  if (m_pPD_HEAT_DATA) { delete m_pPD_HEAT_DATA; m_pPD_HEAT_DATA = 0;}
}

//##ModelId=441038100295
bool CHeatDataConverter::getInternalHeatData(std::string& CustHeatID, std::string& CustTreatID, std::string& HeatID, std::string& TreatID, std::string Plant)
{
  bool ret = true;

  // CustTreatID = L1CustTreatIdToL2CustTreatId(Plant,CustTreatID);

  if ( CustHeatID.empty() || CustTreatID.empty() || Plant.empty()
    || DEF::Inv_String == CustHeatID || DEF::Inv_String == CustTreatID || DEF::Inv_String == Plant )
    return false;

  // select data regarding EXPIRATIONDATE == NULL
  if ( m_pPD_HEAT_PLANT_REF->selectValidCustData(CustHeatID, CustTreatID, Plant) )
  {
    for ( long i = 1; i <= m_pPD_HEAT_PLANT_REF->getLastRow() ; ++i )
    {
      HeatID  = m_pPD_HEAT_PLANT_REF->getHEATID(i);
      TreatID = m_pPD_HEAT_PLANT_REF->getTREATID(i);

      if ( m_pPD_HEAT_DATA->select(HeatID,TreatID,Plant) )
      {
        // take only heat which is not departed.
        if ( m_pPD_HEAT_DATA->getHEATDEPARTURE_ACT(1) == CSMC_DBData::unspecDate )
        {
          break;
        }
      }
    }// for ( long i = 1; i <= m_pPD_HEAT_PLANT_REF->getLastRow() ; ++i )

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);

    if ( m_pPD_HEAT_PLANT_REF->getLastRow() == 1)
    {
    }
    else
    {
      // this case is important, when retreament is made on a departed heat with identical TREATID_CUST.
      std::string Message = "TREATID is identical:  For HeatId (" + CustHeatID + ") this InternalTreatId (" + TreatID + ") is used for retreatment";
      pEventLog->EL_DBReadInfo(sMessage,"TREATID","PD_HEAT_PLANT_REF",Message.c_str());
    }

    // heat is planed but not announced
    if (HeatID == CSMC_DBData::unspecString)
    {
      HeatID = CSMC_DBData::Default;
    }
    if (TreatID == CSMC_DBData::unspecString)
    {
      CTreatID NewTreatID;
      TreatID = NewTreatID.getTreatID("",0);
    }
  }
  else
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);

    if ( m_pPD_HEAT_PLANT_REF->selectByHEATID_CUST(CustHeatID, Plant) )
    {
      HeatID  = m_pPD_HEAT_PLANT_REF->getHEATID(1);
      TreatID = m_pPD_HEAT_PLANT_REF->getTREATID(1);

      std::string Message = "HeatId (" + CustHeatID + ") and TreatId (" + CustTreatID + ") are expired";
      pEventLog->EL_DBReadWarning(sMessage,"HEATID_CUST","PD_HEAT_PLANT_REF",Message.c_str());
    }
    else
    {
      pEventLog->EL_ErrorHeatDataConversion(sMessage,CustHeatID.c_str(),CustTreatID.c_str(),Plant.c_str());
    }

    ret = false;
  }

  return ret;
}

bool CHeatDataConverter::getInternalHeatDataByCustHeatID(std::string& CustHeatID, std::string& HeatID, std::string& TreatID, std::string Plant)
{
  bool ret = true;

  if ( DEF::Inv_String != CustHeatID
    && m_pPD_HEAT_PLANT_REF->selectByHEATID_CUST(CustHeatID, Plant) )
  {
    HeatID  = m_pPD_HEAT_PLANT_REF->getHEATID(1);
    TreatID = m_pPD_HEAT_PLANT_REF->getTREATID(1);

    // heat is planed but not announced
    if (HeatID == CSMC_DBData::unspecString)
    {
      HeatID = CSMC_DBData::Default;
    }
    if (TreatID == CSMC_DBData::unspecString)
    {
      CTreatID NewTreatID;
      TreatID = NewTreatID.getTreatID("",0);
    }
  }
  else
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorHeatDataConversion(sMessage,CustHeatID.c_str(),"",Plant.c_str());

    ret = false;
  }

  return ret;
}


//##ModelId=44103829019C
bool CHeatDataConverter::getCustHeatData(std::string& HeatID, std::string& TreatID, std::string& CustHeatID, std::string& CustTreatID, std::string Plant)
{
  bool ret = true;

  if ( m_pPD_HEAT_PLANT_REF->selectValidData(HeatID, TreatID, Plant) )
  {
    CustHeatID  = m_pPD_HEAT_PLANT_REF->getHEATID_CUST(1);
    CustTreatID = m_pPD_HEAT_PLANT_REF->getTREATID_CUST(1);
  }
  else
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);

    if ( m_pPD_HEAT_PLANT_REF->selectDataByExpirationDate(HeatID, TreatID, Plant, CSMC_DBData::unspecLong, false) )
    {
      CustHeatID  = m_pPD_HEAT_PLANT_REF->getHEATID_CUST(1);
      CustTreatID = m_pPD_HEAT_PLANT_REF->getTREATID_CUST(1);

      std::string Message = "HeatId (" + CustHeatID + ") and TreatId (" + CustTreatID + ") are expired";
      pEventLog->EL_DBReadWarning(sMessage,"HEATID_CUST","PD_HEAT_PLANT_REF",Message.c_str());
    }
    else
    {
      pEventLog->EL_ErrorHeatDataConversion(sMessage,HeatID.c_str(),TreatID.c_str(),Plant.c_str());
    }

    ret = false;
  }

  return ret;
}


bool CHeatDataConverter::getHeatPlantNo( const std::string HeatID, const std::string TreatID, const std::string Plant,long& lngPlantNo )
{
  bool ret = true;

  if ( m_pPD_HEAT_PLANT_REF->selectValidData(HeatID, TreatID, Plant) )
  {
    lngPlantNo  = m_pPD_HEAT_PLANT_REF->getPLANTNO(1);
  }
  else
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorHeatDataConversion(sMessage,HeatID.c_str(),TreatID.c_str(),Plant.c_str());

    ret = false;
  }

  return ret;
}


std::string CHeatDataConverter::L2CustTreatIdToL1CustTreatId(std::string& L2CustTreatId)
{
  if(L2CustTreatId.length() == 3)
    return L2CustTreatId.substr(1,2);
  else
    return L2CustTreatId;
}

std::string CHeatDataConverter::L1CustTreatIdToL2CustTreatId(std::string& Plant, std::string& L1CustTreatId)
{
  if (L1CustTreatId.length() == 3)
    return L1CustTreatId;

  std::map<std::string,std::string>::const_iterator it = m_PlantTreatIDPrefixTrans.find(Plant);
  if ( it != m_PlantTreatIDPrefixTrans.end() )
    return it->second.substr(0,1) + L1CustTreatId;
  else 
    return L1CustTreatId;
}
