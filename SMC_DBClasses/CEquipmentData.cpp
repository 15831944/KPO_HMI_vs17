// Copyright (C) 2006 SMS Demag AG, Germany 

#include <sstream>

#include "cCBS_StdEventLogFrameController.h"
#include "CDataConversion.h"
#include "CPD_EQUIP_MOUNT.h"
#include "CGD_EQUIP_TYPE.h"
#include "CGD_EQUIP_STRUCT.h"
#include "CGC_EQUIP_CAT.h"
#include "CPD_EQUIP_COUNTER.h"
#include "CHD_EQUIP_COUNTER.h"
#include "CHDH_EQUIP_COUNTER.h"
#include "CPD_PLANTSTATUS.h"
#include "CGC_EQUIP_COUNTER.h"

#include "DEF_GC_COUNTER_TYPE.h"
#include "DEF_GD_EQUIP_TYPE.h"

#include "cCBS_StdDB_Task.h"
#include "CSMC_EventLogFrameController.h"

#include "CEquipmentData.h"


CEquipmentData::CEquipmentData(cCBS_StdConnection* Connection)
: m_pCBS_StdConnection(Connection)
{
}

CEquipmentData::~CEquipmentData()
{
}

void CEquipmentData::log(const std::string& Message, long Level)
{
  if (cCBS_StdDB_Task::getInstance()->getTraceLevel() >= Level)
  {
    cCBS_StdDB_Task::getInstance()->log(Message, Level);
  }
}

cCBS_ODBC_DBError CEquipmentData::getLastError()
{
  return m_lastError; 
}


// ********************************************
// specific functions for given equipment types
// ********************************************
long CEquipmentData::getLanceAge(const std::string& PLANT, long PLANTNO, std::string& CustLanceId)
{
  return (long)getEquipmentAge(PLANT, PLANTNO, DEF_GD_EQUIP_TYPE::LANCE, CustLanceId, DEF_GC_COUNTER_TYPE::HEATS);
}

bool CEquipmentData::setLanceAge(const std::string& PLANT, long PLANTNO, std::string& CustLanceId, double NewAge, bool Commit)
{
  std::string STRUCT_SUB_ID_PARENT = CSMC_DBData::unspecString;

  if ( PLANTNO != CSMC_DBData::unspecLong )
  {
    STRUCT_SUB_ID_PARENT = CDataConversion::LongToString(PLANTNO);
  }

  return setEquipmentAge(PLANT, STRUCT_SUB_ID_PARENT, DEF_GD_EQUIP_TYPE::LANCE, CustLanceId, DEF_GC_COUNTER_TYPE::HEATS, NewAge, Commit);
}

bool CEquipmentData::increaseLanceAge(const std::string& PLANT, long PLANTNO, std::string& CustLanceId, double Value, bool Commit)
{
  std::string STRUCT_SUB_ID_PARENT = CSMC_DBData::unspecString;

  if ( PLANTNO != CSMC_DBData::unspecLong )
  {
    STRUCT_SUB_ID_PARENT = CDataConversion::LongToString(PLANTNO);
  }

  return increaseEquipmentAge(PLANT, STRUCT_SUB_ID_PARENT, DEF_GD_EQUIP_TYPE::LANCE, CustLanceId, DEF_GC_COUNTER_TYPE::HEATS, Value, Commit);
}

long CEquipmentData::getLanceTipAge(const std::string& PLANT, long PLANTNO, std::string& CustLanceId)
{
  return (long)getEquipmentAge(PLANT, PLANTNO, CustLanceId, DEF_GD_EQUIP_TYPE::LANCE_TIP, DEF_GC_COUNTER_TYPE::HEATS);
}

bool CEquipmentData::setLanceTipAge(const std::string& PLANT, long PLANTNO, std::string& CustLanceId, double NewAge, bool Commit)
{
  std::string STRUCT_SUB_ID_PARENT = CSMC_DBData::unspecString;

  if ( PLANTNO != CSMC_DBData::unspecLong )
  {
    STRUCT_SUB_ID_PARENT = CDataConversion::LongToString(PLANTNO);
  }

  return setEquipmentAge(PLANT, STRUCT_SUB_ID_PARENT, DEF_GD_EQUIP_TYPE::LANCE_TIP, CustLanceId, DEF_GC_COUNTER_TYPE::HEATS, NewAge, Commit);
}

bool CEquipmentData::increaseLanceTipAge(const std::string& PLANT, long PLANTNO, std::string& CustLanceId, double Value, bool Commit)
{
  std::string STRUCT_SUB_ID_PARENT = CSMC_DBData::unspecString;

  if ( PLANTNO != CSMC_DBData::unspecLong )
  {
    STRUCT_SUB_ID_PARENT = CDataConversion::LongToString(PLANTNO);
  }

  return increaseEquipmentAge(PLANT, STRUCT_SUB_ID_PARENT, DEF_GD_EQUIP_TYPE::LANCE_TIP, CustLanceId, DEF_GC_COUNTER_TYPE::HEATS, Value, Commit);
}

// ********************************************
// handling equipment no
// ********************************************
long CEquipmentData::getEquipmentNo(const std::string& PLANT, long PLANTNO, const std::string& EQUIP_TYPE, const std::string& STRUCT_SUB_ID, const std::string& COUNTER_TYPE )
{
  std::string STRUCT_SUB_ID_PARENT = CSMC_DBData::unspecString;

  if ( PLANTNO != CSMC_DBData::unspecLong )
  {
    STRUCT_SUB_ID_PARENT = CDataConversion::LongToString(PLANTNO);
  }

  return getEquipmentNo(PLANT, STRUCT_SUB_ID_PARENT, EQUIP_TYPE, STRUCT_SUB_ID, COUNTER_TYPE );
}

long CEquipmentData::getEquipmentNo(const std::string& EQUIP_TYPE_PARENT, const std::string& STRUCT_SUB_ID_PARENT, const std::string& EQUIP_TYPE, const std::string& STRUCT_SUB_ID, const std::string& COUNTER_TYPE )
{
  long RetVal = CSMC_DBData::unspecLong;

  CGD_EQUIP_STRUCT  GD_EQUIP_STRUCT(m_pCBS_StdConnection);
  CGC_EQUIP_CAT     GC_EQUIP_CAT(m_pCBS_StdConnection);
  CPD_EQUIP_MOUNT   PD_EQUIP_MOUNT(m_pCBS_StdConnection);

  std::vector<long> StructIdList ;
  std::vector<long>::iterator it;
  
  // select struct_id for EQUIP_TYPE and STRUCT_SUB_ID of given parent
  StructIdList = GD_EQUIP_STRUCT.getStructIdListOfParentId(EQUIP_TYPE_PARENT, STRUCT_SUB_ID_PARENT, EQUIP_TYPE, STRUCT_SUB_ID);

  it = StructIdList.begin();

  // we expect to use the first entry !
  if ( it != StructIdList.end() )
  {
    long STRUCT_ID = (*it);

    // select equip_id for EQUIP_TYPE and STRUCT_ID
    if ( PD_EQUIP_MOUNT.selectByEquipType(EQUIP_TYPE, STRUCT_ID) )
    {
      long EQUIP_ID = PD_EQUIP_MOUNT.getEQUIP_ID(1);

      // select equip_counter for EQUIP_ID, EQUIP_TYPE and COUNTER_TYPE
      if ( GC_EQUIP_CAT.select(EQUIP_ID) )
      {
        RetVal = GC_EQUIP_CAT.getEQUIP_NO(1);
      }
    }
  }

  if ( it == StructIdList.end() || RetVal == false )
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);

    if ( EQUIP_TYPE_PARENT != CSMC_DBData::unspecString ) 
    {
      pEventLog->EL_ErrorEquipmentIdentification(sMessage, EQUIP_TYPE_PARENT.c_str(), STRUCT_SUB_ID_PARENT.c_str(), EQUIP_TYPE.c_str(), STRUCT_SUB_ID.c_str());
    }
    else
    {
      pEventLog->EL_ErrorEquipmentIdentification(sMessage, EQUIP_TYPE.c_str(), STRUCT_SUB_ID.c_str());
    }
  }


  return RetVal;
}

// ********************************************
// handling customer specific equipment id
// ********************************************
std::string CEquipmentData::getEquipmentIdCust(const std::string& PLANT, long PLANTNO, const std::string& EQUIP_TYPE, const std::string& STRUCT_SUB_ID, const std::string& COUNTER_TYPE )
{
  std::string STRUCT_SUB_ID_PARENT = CSMC_DBData::unspecString;

  if ( PLANTNO != CSMC_DBData::unspecLong )
  {
    STRUCT_SUB_ID_PARENT = CDataConversion::LongToString(PLANTNO);
  }

  return getEquipmentIdCust(PLANT, STRUCT_SUB_ID_PARENT, EQUIP_TYPE, STRUCT_SUB_ID, COUNTER_TYPE );
}

std::string CEquipmentData::getEquipmentIdCust(const std::string& EQUIP_TYPE_PARENT, const std::string& STRUCT_SUB_ID_PARENT, const std::string& EQUIP_TYPE, const std::string& STRUCT_SUB_ID, const std::string& COUNTER_TYPE )
{
  std::string RetVal = CSMC_DBData::unspecString;

  CGD_EQUIP_STRUCT  GD_EQUIP_STRUCT(m_pCBS_StdConnection);
  CGC_EQUIP_CAT     GC_EQUIP_CAT(m_pCBS_StdConnection);
  CPD_EQUIP_MOUNT   PD_EQUIP_MOUNT(m_pCBS_StdConnection);

  std::vector<long> StructIdList ;
  std::vector<long>::iterator it;
  
  // select struct_id for EQUIP_TYPE and STRUCT_SUB_ID of given parent
  StructIdList = GD_EQUIP_STRUCT.getStructIdListOfParentId(EQUIP_TYPE_PARENT, STRUCT_SUB_ID_PARENT, EQUIP_TYPE, STRUCT_SUB_ID);

  it = StructIdList.begin();

  // we expect to use the first entry !
  if ( it != StructIdList.end() )
  {
    long STRUCT_ID = (*it);

    // select equip_id for EQUIP_TYPE and STRUCT_ID
    if ( PD_EQUIP_MOUNT.selectByEquipType(EQUIP_TYPE, STRUCT_ID) )
    {
      long EQUIP_ID = PD_EQUIP_MOUNT.getEQUIP_ID(1);

      // select equip_counter for EQUIP_ID, EQUIP_TYPE and COUNTER_TYPE
      if ( GC_EQUIP_CAT.select(EQUIP_ID) )
      {
        RetVal = GC_EQUIP_CAT.getEQUIP_ID_CUST(1);
      }
    }
  }
  
  if ( it == StructIdList.end() || RetVal == CSMC_DBData::unspecString )
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);

    if ( EQUIP_TYPE_PARENT != CSMC_DBData::unspecString ) 
    {
      pEventLog->EL_ErrorEquipmentIdentification(sMessage, EQUIP_TYPE_PARENT.c_str(), STRUCT_SUB_ID_PARENT.c_str(), EQUIP_TYPE.c_str(), STRUCT_SUB_ID.c_str());
    }
    else
    {
      pEventLog->EL_ErrorEquipmentIdentification(sMessage, EQUIP_TYPE.c_str(), STRUCT_SUB_ID.c_str());
    }
  }


  return RetVal;
}


// ********************************************
// handling equipment age
// ********************************************
double CEquipmentData::getEquipmentAge(const std::string& PLANT, long PLANTNO, const std::string& EQUIP_TYPE, const std::string COUNTER_TYPE)
{
  log("++++++ CEquipmentData::getEquipmentAge ##1",3);
  
  std::string STRUCT_SUB_ID_PARENT = CSMC_DBData::unspecString;
  if ( PLANTNO != CSMC_DBData::unspecLong )
  {
    STRUCT_SUB_ID_PARENT = CDataConversion::LongToString(PLANTNO);
  }

  return getEquipmentAge(PLANT, STRUCT_SUB_ID_PARENT, EQUIP_TYPE, CSMC_DBData::unspecString, COUNTER_TYPE );

}

double CEquipmentData::getEquipmentAge(const std::string& PLANT, long PLANTNO, const std::string& EQUIP_TYPE, long EQUIP_NO, const std::string COUNTER_TYPE)
{
  log("++++++ CEquipmentData::getEquipmentAge ##2",3);
  
  std::string STRUCT_SUB_ID_PARENT = CSMC_DBData::unspecString;
  std::string STRUCT_SUB_ID        = CSMC_DBData::unspecString;

  if ( PLANTNO != CSMC_DBData::unspecLong )
  {
    STRUCT_SUB_ID_PARENT = CDataConversion::LongToString(PLANTNO);
  }
  if ( EQUIP_NO != CSMC_DBData::unspecLong )
  {
    STRUCT_SUB_ID = CDataConversion::LongToString(EQUIP_NO);
  }

  return getEquipmentAge(PLANT, STRUCT_SUB_ID_PARENT, EQUIP_TYPE, STRUCT_SUB_ID, COUNTER_TYPE );
}

double CEquipmentData::getEquipmentAge(const std::string& PLANT, long PLANTNO, const std::string& EQUIP_TYPE, const std::string& EQUIP_NAME, const std::string COUNTER_TYPE)
{
  log("++++++ CEquipmentData::getEquipmentAge ##3",3);

  std::string STRUCT_SUB_ID_PARENT = CSMC_DBData::unspecString;

  if ( PLANTNO != CSMC_DBData::unspecLong )
  {
    STRUCT_SUB_ID_PARENT = CDataConversion::LongToString(PLANTNO);
  }

  return getEquipmentAge(PLANT, STRUCT_SUB_ID_PARENT, EQUIP_TYPE, EQUIP_NAME, COUNTER_TYPE );
}



double CEquipmentData::getEquipmentAge(const std::string& EQUIP_TYPE_PARENT, const std::string& STRUCT_SUB_ID_PARENT, const std::string& EQUIP_TYPE, const std::string& STRUCT_SUB_ID, const std::string& COUNTER_TYPE )
{
  log("++++++ CEquipmentData::getEquipmentAge ##4",3);
  double RetVal = CSMC_DBData::unspecDouble;

  CGD_EQUIP_STRUCT  GD_EQUIP_STRUCT(m_pCBS_StdConnection);
  CPD_EQUIP_COUNTER PD_EQUIP_COUNTER(m_pCBS_StdConnection);
  CPD_EQUIP_MOUNT   PD_EQUIP_MOUNT(m_pCBS_StdConnection);

  std::vector<long> StructIdList ;
  std::vector<long>::iterator it;
  
  // select struct_id for EQUIP_TYPE and STRUCT_SUB_ID of given parent
  StructIdList = GD_EQUIP_STRUCT.getStructIdListOfParentId(EQUIP_TYPE_PARENT, STRUCT_SUB_ID_PARENT, EQUIP_TYPE, STRUCT_SUB_ID);

  it = StructIdList.begin();

  // we expect to use the first entry !
  if ( it != StructIdList.end() )
  {
    long STRUCT_ID = (*it);

    // select equip_id for EQUIP_TYPE and STRUCT_ID
    if ( PD_EQUIP_MOUNT.selectByEquipType(EQUIP_TYPE, STRUCT_ID) )
    {
      long EQUIP_ID = PD_EQUIP_MOUNT.getEQUIP_ID(1);

      // select equip_counter for EQUIP_ID, EQUIP_TYPE and COUNTER_TYPE
      if ( PD_EQUIP_COUNTER.select(EQUIP_ID, EQUIP_TYPE, COUNTER_TYPE) )
      {
        RetVal = PD_EQUIP_COUNTER.getCOUNTER_VALUE(1);
      }
    }
  }
  
  if ( it == StructIdList.end() || RetVal == CSMC_DBData::unspecDouble )
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);

    if ( EQUIP_TYPE_PARENT != CSMC_DBData::unspecString ) 
    {
      pEventLog->EL_ErrorEquipmentIdentification(sMessage, EQUIP_TYPE_PARENT.c_str(), STRUCT_SUB_ID_PARENT.c_str(), EQUIP_TYPE.c_str(), STRUCT_SUB_ID.c_str());
    }
    else
    {
      pEventLog->EL_ErrorEquipmentIdentification(sMessage, EQUIP_TYPE.c_str(), STRUCT_SUB_ID.c_str());
    }
  }

  return RetVal;
}

bool CEquipmentData::setEquipmentAge(const std::string& PLANT, long PLANTNO, const std::string& EQUIP_TYPE, const std::string COUNTER_TYPE, double EQUIP_AGE, bool Commit)
{
  log("++++++ CEquipmentData::setEquipmentAge ##1",3);
  return setEquipmentAge(PLANT, PLANT, EQUIP_TYPE, CSMC_DBData::unspecString, COUNTER_TYPE, EQUIP_AGE, Commit );
}

bool CEquipmentData::setEquipmentAge(const std::string& PLANT, long PLANTNO, const std::string& EQUIP_TYPE, long EQUIP_NO, const std::string COUNTER_TYPE, double EQUIP_AGE, bool Commit)
{
  log("++++++ CEquipmentData::setEquipmentAge ##2",3);

  std::string STRUCT_SUB_ID_PARENT = CSMC_DBData::unspecString;
  std::string STRUCT_SUB_ID        = CSMC_DBData::unspecString;

  if ( PLANTNO != CSMC_DBData::unspecLong )
  {
    STRUCT_SUB_ID_PARENT = CDataConversion::LongToString(PLANTNO);
  }
  if ( EQUIP_NO != CSMC_DBData::unspecLong )
  {
    STRUCT_SUB_ID = CDataConversion::LongToString(EQUIP_NO);
  }

  return setEquipmentAge(PLANT, STRUCT_SUB_ID_PARENT, EQUIP_TYPE, STRUCT_SUB_ID, COUNTER_TYPE, EQUIP_AGE, Commit );
}

bool CEquipmentData::setEquipmentAge(const std::string& PLANT, long PLANTNO, const std::string& EQUIP_TYPE, const std::string& EQUIP_NAME, const std::string COUNTER_TYPE, double EQUIP_AGE, bool Commit)
{
  log("++++++ CEquipmentData::setEquipmentAge ##3",3);

  std::string STRUCT_SUB_ID_PARENT = CSMC_DBData::unspecString;

  if ( PLANTNO != CSMC_DBData::unspecLong )
  {
    STRUCT_SUB_ID_PARENT = CDataConversion::LongToString(PLANTNO);
  }

  return setEquipmentAge(PLANT, STRUCT_SUB_ID_PARENT, EQUIP_TYPE, EQUIP_NAME, COUNTER_TYPE, EQUIP_AGE, Commit );
}


bool CEquipmentData::setEquipmentAge(const std::string& EQUIP_TYPE_PARENT, const std::string& STRUCT_SUB_ID_PARENT, const std::string& EQUIP_TYPE, const std::string& STRUCT_SUB_ID, const std::string& COUNTER_TYPE, double EQUIP_AGE, bool Commit )
{
  log("++++++ CEquipmentData::setEquipmentAge ##4",3);
  bool RetVal = false;

  CGD_EQUIP_STRUCT  GD_EQUIP_STRUCT(m_pCBS_StdConnection);
  CPD_EQUIP_COUNTER PD_EQUIP_COUNTER(m_pCBS_StdConnection);
  CPD_EQUIP_MOUNT   PD_EQUIP_MOUNT(m_pCBS_StdConnection);

  std::vector<long> StructIdList ;
  std::vector<long>::iterator it;
  
  // select struct_id for EQUIP_TYPE and STRUCT_SUB_ID of given parent
  StructIdList = GD_EQUIP_STRUCT.getStructIdListOfParentId(EQUIP_TYPE_PARENT, STRUCT_SUB_ID_PARENT, EQUIP_TYPE, STRUCT_SUB_ID);

  it = StructIdList.begin();

  for (it = StructIdList.begin(); it != StructIdList.end(); ++it)
  {
    long STRUCT_ID = (*it);

    // select equip_id for EQUIP_TYPE and STRUCT_ID
    if ( PD_EQUIP_MOUNT.selectByEquipType(EQUIP_TYPE, STRUCT_ID) )
    {
      long EQUIP_ID = PD_EQUIP_MOUNT.getEQUIP_ID(1);

      // select equip_counter for EQUIP_ID, EQUIP_TYPE and COUNTER_TYPE
      if ( PD_EQUIP_COUNTER.select(EQUIP_ID, EQUIP_TYPE, COUNTER_TYPE) )
      {
        PD_EQUIP_COUNTER.setCOUNTER_VALUE(EQUIP_AGE);

        RetVal = PD_EQUIP_COUNTER.update();

        if ( Commit )
        {
          if ( RetVal )
          {
            PD_EQUIP_COUNTER.commit();
          }
          else
          {
            PD_EQUIP_COUNTER.rollback();
          }
        }
      }
      else
      {
        PD_EQUIP_COUNTER.setEQUIP_ID(EQUIP_ID);
        PD_EQUIP_COUNTER.setEQUIP_TYPE(EQUIP_TYPE);
        PD_EQUIP_COUNTER.setCOUNTER_TYPE(COUNTER_TYPE);

        PD_EQUIP_COUNTER.setCOUNTER_VALUE(1.0);

        RetVal = PD_EQUIP_COUNTER.insert();

        if ( Commit )
        {
          if ( RetVal )
          {
            PD_EQUIP_COUNTER.commit();
          }
          else
          {
            PD_EQUIP_COUNTER.rollback();
          }
        }
      }
    }
  }
  
  if ( it == StructIdList.end() || RetVal == false )
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);

    if ( EQUIP_TYPE_PARENT != CSMC_DBData::unspecString ) 
    {
      pEventLog->EL_ErrorEquipmentIdentification(sMessage, EQUIP_TYPE_PARENT.c_str(), STRUCT_SUB_ID_PARENT.c_str(), EQUIP_TYPE.c_str(), STRUCT_SUB_ID.c_str());
    }
    else
    {
      pEventLog->EL_ErrorEquipmentIdentification(sMessage, EQUIP_TYPE.c_str(), STRUCT_SUB_ID.c_str());
    }
  }


  return RetVal;
}

bool CEquipmentData::increaseEquipmentAge(const std::string& PLANT, long PLANTNO, const std::string& EQUIP_TYPE, const std::string COUNTER_TYPE, double Value, bool Commit)
{
  log("++++++ CEquipmentData::increaseEquipmentAge ##1",3);

  std::string STRUCT_SUB_ID_PARENT = CSMC_DBData::unspecString;

  if ( PLANTNO != CSMC_DBData::unspecLong )
  {
    STRUCT_SUB_ID_PARENT = CDataConversion::LongToString(PLANTNO);
  }

  return increaseEquipmentAge(PLANT, STRUCT_SUB_ID_PARENT, EQUIP_TYPE, CSMC_DBData::unspecString, COUNTER_TYPE, Value, Commit );
}

bool CEquipmentData::increaseEquipmentAge(const std::string& PLANT, long PLANTNO, const std::string& EQUIP_TYPE, long EQUIP_NO, const std::string COUNTER_TYPE, double Value, bool Commit)
{
  log("++++++ CEquipmentData::increaseEquipmentAge ##2",3);

  std::string STRUCT_SUB_ID_PARENT = CSMC_DBData::unspecString;
  std::string STRUCT_SUB_ID        = CSMC_DBData::unspecString;

  if ( PLANTNO != CSMC_DBData::unspecLong )
  {
    STRUCT_SUB_ID_PARENT = CDataConversion::LongToString(PLANTNO);
  }
  if ( EQUIP_NO != CSMC_DBData::unspecLong )
  {
    STRUCT_SUB_ID = CDataConversion::LongToString(EQUIP_NO);
  }

  return increaseEquipmentAge(PLANT, STRUCT_SUB_ID_PARENT, EQUIP_TYPE, STRUCT_SUB_ID, COUNTER_TYPE, Value, Commit );
}

bool CEquipmentData::increaseEquipmentAge(const std::string& PLANT, long PLANTNO, const std::string& EQUIP_TYPE, const std::string& EQUIP_NAME, const std::string COUNTER_TYPE, double Value, bool Commit)
{
  log("++++++ CEquipmentData::increaseEquipmentAge ##3",3);

  std::string STRUCT_SUB_ID_PARENT = CSMC_DBData::unspecString;

  if ( PLANTNO != CSMC_DBData::unspecLong )
  {
    STRUCT_SUB_ID_PARENT = CDataConversion::LongToString(PLANTNO);
  }

  return increaseEquipmentAge(PLANT, STRUCT_SUB_ID_PARENT, EQUIP_TYPE, EQUIP_NAME, COUNTER_TYPE, Value, Commit );
}

bool CEquipmentData::increaseEquipmentAge(const std::string& EQUIP_TYPE_PARENT, const std::string& STRUCT_SUB_ID_PARENT, const std::string& EQUIP_TYPE, const std::string& STRUCT_SUB_ID, const std::string& COUNTER_TYPE, double Value, bool Commit )
{
  log("++++++ CEquipmentData::increaseEquipmentAge ##4",3);
  bool RetVal = false;

  CGD_EQUIP_STRUCT  GD_EQUIP_STRUCT(m_pCBS_StdConnection);
  CPD_EQUIP_COUNTER PD_EQUIP_COUNTER(m_pCBS_StdConnection);
  CPD_EQUIP_MOUNT   PD_EQUIP_MOUNT(m_pCBS_StdConnection);

  std::vector<long> StructIdList ;
  std::vector<long>::iterator it;
  
  // select struct_id for EQUIP_TYPE and STRUCT_SUB_ID of given parent
  StructIdList = GD_EQUIP_STRUCT.getStructIdListOfParentId(EQUIP_TYPE_PARENT, STRUCT_SUB_ID_PARENT, EQUIP_TYPE, STRUCT_SUB_ID);

  it = StructIdList.begin();

  for (it = StructIdList.begin(); it != StructIdList.end(); ++it)
  {
    long STRUCT_ID = (*it);

    // select equip_id for EQUIP_TYPE and STRUCT_ID
    if ( PD_EQUIP_MOUNT.selectByEquipType(EQUIP_TYPE, STRUCT_ID) )
    {
      for ( long i = 1; i <= PD_EQUIP_MOUNT.getLastRow(); ++i )
      {
        long EQUIP_ID = PD_EQUIP_MOUNT.getEQUIP_ID(i);

        // select equip_counter for EQUIP_ID, EQUIP_TYPE and COUNTER_TYPE
        if ( PD_EQUIP_COUNTER.select(EQUIP_ID, EQUIP_TYPE, COUNTER_TYPE) )
        {
          double COUNTER_VALUE = PD_EQUIP_COUNTER.getCOUNTER_VALUE(1);

          PD_EQUIP_COUNTER.setCOUNTER_VALUE(CDataConversion::SetInvalidToDefault(COUNTER_VALUE, 0.0 ) + Value);

          RetVal = PD_EQUIP_COUNTER.update();

          if ( Commit )
          {
            if ( RetVal )
            {
              PD_EQUIP_COUNTER.commit();
            }
            else
            {
              PD_EQUIP_COUNTER.rollback();
            }
          }
        } // if ( PD_EQUIP_COUNTER.select(EQUIP_ID, EQUIP_TYPE, COUNTER_TYPE) )
        else
        {
          PD_EQUIP_COUNTER.setEQUIP_ID(EQUIP_ID);
          PD_EQUIP_COUNTER.setEQUIP_TYPE(EQUIP_TYPE);
          PD_EQUIP_COUNTER.setCOUNTER_TYPE(COUNTER_TYPE);

          PD_EQUIP_COUNTER.setCOUNTER_VALUE(1.0);

          RetVal = PD_EQUIP_COUNTER.insert();

          if ( Commit )
          {
            if ( RetVal )
            {
              PD_EQUIP_COUNTER.commit();
            }
            else
            {
              PD_EQUIP_COUNTER.rollback();
            }
          }
        }

      } // for ( long i = 1; i <= PD_EQUIP_MOUNT.getLastRow(); ++i )
    } // if ( PD_EQUIP_MOUNT.selectByEquipType(EQUIP_TYPE, STRUCT_ID) )
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorEquipmentMountIdentification(sMessage, EQUIP_TYPE.c_str(), CDataConversion::LongToString(STRUCT_ID).c_str());
    }
  }

  if ( it == StructIdList.end() || RetVal == false )
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);

    if ( EQUIP_TYPE_PARENT != CSMC_DBData::unspecString ) 
    {
      pEventLog->EL_ErrorEquipmentIdentification(sMessage, EQUIP_TYPE_PARENT.c_str(), STRUCT_SUB_ID_PARENT.c_str(), EQUIP_TYPE.c_str(), STRUCT_SUB_ID.c_str());
    }
    else
    {
      pEventLog->EL_ErrorEquipmentIdentification(sMessage, EQUIP_TYPE.c_str(), STRUCT_SUB_ID.c_str());
    }
  }

  return RetVal;
}

//SANKAR
bool CEquipmentData::increaseEquipmentAge(const std::string& HEATID,const std::string& TREATID,const std::string& PLANT, long PLANTNO, const std::string& EQUIP_TYPE, long EQUIP_NO, const std::string& COUNTER_TYPE, double Value, bool Commit )
{
  log("++++++ CEquipmentData::increaseEquipmentAge ##4",3);
  bool RetVal = false;

  std::string EQUIP_TYPE_PARENT = CSMC_DBData::unspecString;
  std::string STRUCT_SUB_ID_PARENT = CSMC_DBData::unspecString;
  std::string STRUCT_SUB_ID = CSMC_DBData::unspecString;

  if ( PLANT != CSMC_DBData::unspecString )
  {
    EQUIP_TYPE_PARENT = PLANT;
  }

	if ( PLANTNO != CSMC_DBData::unspecLong )
  {
    STRUCT_SUB_ID_PARENT = CDataConversion::LongToString(PLANTNO);
  }

  if ( EQUIP_NO != CSMC_DBData::unspecLong )
  {
    STRUCT_SUB_ID = CDataConversion::LongToString(EQUIP_NO);
  }

  CGD_EQUIP_STRUCT  GD_EQUIP_STRUCT(m_pCBS_StdConnection);
  CPD_EQUIP_COUNTER PD_EQUIP_COUNTER(m_pCBS_StdConnection);
  CPD_EQUIP_MOUNT   PD_EQUIP_MOUNT(m_pCBS_StdConnection);

  CHD_EQUIP_COUNTER    HD_EQUIP_COUNTER(m_pCBS_StdConnection);
  CHDH_EQUIP_COUNTER   HDH_EQUIP_COUNTER(m_pCBS_StdConnection);
  CPD_PLANTSTATUS      PD_PLANTSTATUS(m_pCBS_StdConnection);
	CGC_EQUIP_COUNTER     GC_EQUIP_COUNTER(m_pCBS_StdConnection);

  std::vector<long> StructIdList ;
  std::vector<long>::iterator it;
  
  // select struct_id for EQUIP_TYPE and STRUCT_SUB_ID of given parent
  StructIdList = GD_EQUIP_STRUCT.getStructIdListOfParentId(EQUIP_TYPE_PARENT, STRUCT_SUB_ID_PARENT, EQUIP_TYPE, STRUCT_SUB_ID);

  it = StructIdList.begin();

  for (it = StructIdList.begin(); it != StructIdList.end(); ++it)
  {
    long STRUCT_ID = (*it);

    // select equip_id for EQUIP_TYPE and STRUCT_ID
    if ( PD_EQUIP_MOUNT.selectByEquipType(EQUIP_TYPE, STRUCT_ID) )
    {
      for ( long i = 1; i <= PD_EQUIP_MOUNT.getLastRow(); ++i )
      {
        long EQUIP_ID = PD_EQUIP_MOUNT.getEQUIP_ID(i);
        std::string EQUIP_TYPE_TEMP = PD_EQUIP_MOUNT.getEQUIP_TYPE(i);
        

				double COUNTER_VALUE_TEMP = Value;

        // select equip_counter for EQUIP_ID, EQUIP_TYPE and COUNTER_TYPE
        if ( PD_EQUIP_COUNTER.select(EQUIP_ID, EQUIP_TYPE_TEMP, COUNTER_TYPE) )
        {
          double COUNTER_VALUE = PD_EQUIP_COUNTER.getCOUNTER_VALUE(1);

          PD_EQUIP_COUNTER.setCOUNTER_VALUE(CDataConversion::SetInvalidToDefault(COUNTER_VALUE, 0.0 ) + Value);

					COUNTER_VALUE_TEMP =  CDataConversion::SetInvalidToDefault(COUNTER_VALUE, 0.0 ) + Value;

          RetVal = PD_EQUIP_COUNTER.update();

          if ( Commit )
          {
            if ( RetVal )
            {
              PD_EQUIP_COUNTER.commit();
            }
            else
            {
              PD_EQUIP_COUNTER.rollback();
            }
          }
        } // if ( PD_EQUIP_COUNTER.select(EQUIP_ID, EQUIP_TYPE, COUNTER_TYPE) )
        else
        {
          PD_EQUIP_COUNTER.setEQUIP_ID(EQUIP_ID);
          PD_EQUIP_COUNTER.setEQUIP_TYPE(EQUIP_TYPE_TEMP);
          PD_EQUIP_COUNTER.setCOUNTER_TYPE(COUNTER_TYPE);

          PD_EQUIP_COUNTER.setCOUNTER_VALUE(Value);
					
          RetVal = PD_EQUIP_COUNTER.insert();

          if ( Commit )
          {
            if ( RetVal )
            {
              PD_EQUIP_COUNTER.commit();
            }
            else
            {
              PD_EQUIP_COUNTER.rollback();
            }
          }
        }

				
				if(PLANT == "HMD")
				{
					HDH_EQUIP_COUNTER.updateOrInsert(HEATID,TREATID,PLANT,EQUIP_ID,EQUIP_TYPE_TEMP,COUNTER_TYPE,COUNTER_VALUE_TEMP,Commit,m_lastError);
				}
				else
				{
					HD_EQUIP_COUNTER.updateOrInsert(HEATID,TREATID,PLANT,EQUIP_ID,EQUIP_TYPE_TEMP,COUNTER_TYPE,COUNTER_VALUE_TEMP,Commit,m_lastError);
				}


				if(GC_EQUIP_COUNTER.select(EQUIP_TYPE_TEMP,COUNTER_TYPE))
				{
					if (GC_EQUIP_COUNTER.getCOUNTER_LIMIT(1) < COUNTER_VALUE_TEMP)
					{
						//send the log if life is expired
						sEventLogMessage msg = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
						msg.language = 1;
						//msg.destination = CSMC_DestCodes::HMDBotLine;
						msg.plantUnit = string(PLANT);
						//msg.processState = "";
						msg.eventId = 999999; 

						msg.messageText = string( "Equipment life is expired for EQUIP_TYPE : ") + string(EQUIP_TYPE_TEMP);
						msg.messageText2 = string( "Equipment life is expired for EQUIP_TYPE : ") + string(EQUIP_TYPE_TEMP);
						msg.severity = static_cast<c_e_severity_t>(c_e_warning);
						msg.opAckn = 1;
						msg.spare2 = string(HEATID) + "_" + string(TREATID);
						//msg.uniMessage = L"Equipment life is expired for EQUIP_TYPE : " ;
						cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
						pEventLog->sendMessage( msg);
					}
				}

				
      } // for ( long i = 1; i <= PD_EQUIP_MOUNT.getLastRow(); ++i )
    } // if ( PD_EQUIP_MOUNT.selectByEquipType(EQUIP_TYPE, STRUCT_ID) )
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorEquipmentMountIdentification(sMessage, EQUIP_TYPE.c_str(), CDataConversion::LongToString(STRUCT_ID).c_str());
    }
  } //for..

	//ladle life handling - not required because ladle life is mainted by other class
	//std::string ladleTypeNo = CSMC_DBData::unspecString;
	//if (PD_PLANTSTATUS.select(PLANT,PLANTNO,1))
	//{
	//	std::string ladleType = PD_PLANTSTATUS.getLADLETYPE(1);
	//	long ladleNo = PD_PLANTSTATUS.getLADLENO(1);
	//	ladleTypeNo =  ladleType + "_" + CDataConversion::LongToString(ladleNo);
	//  ladleLifeHandline(HEATID, TREATID, PLANT,ladleTypeNo,COUNTER_TYPE,Value,true);
	//}


  if ( it == StructIdList.end() || RetVal == false )
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);

    if ( EQUIP_TYPE_PARENT != CSMC_DBData::unspecString ) 
    {
      pEventLog->EL_ErrorEquipmentIdentification(sMessage, EQUIP_TYPE_PARENT.c_str(), STRUCT_SUB_ID_PARENT.c_str(), EQUIP_TYPE.c_str(), STRUCT_SUB_ID.c_str());
    }
    else
    {
      pEventLog->EL_ErrorEquipmentIdentification(sMessage, EQUIP_TYPE.c_str(), STRUCT_SUB_ID.c_str());
    }
  }

  return RetVal;
}


//SANKAR
bool CEquipmentData::ladleLifeHandline(const std::string& HEATID,const std::string& TREATID,const std::string& PLANT, const std::string& EQUIP_TYPE1, const std::string& COUNTER_TYPE, double COUNTER_VALUE, bool Commit )
{
  log("++++++ CEquipmentData::ladleLifeHandline ##4",3);
  bool RetVal = false;

	long PARENT_STRUCT_ID;
	long STRUCT_ID1 = CSMC_DBData::unspecLong;
	long EQUIP_ID1 = CSMC_DBData::unspecLong;

  CGD_EQUIP_TYPE  GD_EQUIP_TYPE1(m_pCBS_StdConnection);
	CGD_EQUIP_STRUCT GD_EQUIP_STRUCT1(m_pCBS_StdConnection);
	CGC_EQUIP_COUNTER GC_EQUIP_COUNTER1(m_pCBS_StdConnection);
	CGC_EQUIP_CAT GC_EQUIP_CAT1(m_pCBS_StdConnection);
	CPD_EQUIP_MOUNT PD_EQUIP_MOUNT1(m_pCBS_StdConnection);
  CHD_EQUIP_COUNTER    HD_EQUIP_COUNTER1(m_pCBS_StdConnection);
  CHDH_EQUIP_COUNTER   HDH_EQUIP_COUNTER1(m_pCBS_StdConnection);
	CPD_EQUIP_COUNTER PD_EQUIP_COUNTER1(m_pCBS_StdConnection);

	std::string desc;
	if(EQUIP_TYPE1.substr(0,1) == "T")
		desc = "Teeming Ladle " + EQUIP_TYPE1.substr(2,EQUIP_TYPE1.length());
	else
		desc = "HM Ladle " + EQUIP_TYPE1.substr(2,EQUIP_TYPE1.length());
	 
	if(! GD_EQUIP_TYPE1.select(EQUIP_TYPE1))
	{
		RetVal = GD_EQUIP_TYPE1.InsertData(EQUIP_TYPE1,CSMC_DBData::unspecString,desc,CSMC_DBData::unspecLong,0,Commit,m_lastError);
	}

	if ( GD_EQUIP_STRUCT1.selectByEquipType(EQUIP_TYPE1,CSMC_DBData::unspecString))
	{
		STRUCT_ID1  = GD_EQUIP_STRUCT1.getSTRUCT_ID(1);
	}


	//STRUCT_ID for LADLE must be set manuallly in database before
	if ((STRUCT_ID1 == CSMC_DBData::unspecLong) && ( GD_EQUIP_STRUCT1.selectByEquipType("LADLE","1")) )
	{
		PARENT_STRUCT_ID  = GD_EQUIP_STRUCT1.getSTRUCT_ID(1);
		STRUCT_ID1 = GD_EQUIP_STRUCT1.GetMaxSTRUCT_ID() + 1;		

	  RetVal = GD_EQUIP_STRUCT1.InsertData(STRUCT_ID1,EQUIP_TYPE1,CSMC_DBData::unspecString,1,PARENT_STRUCT_ID, EQUIP_TYPE1,Commit,m_lastError);
	}

	
	if(! GC_EQUIP_COUNTER1.select(EQUIP_TYPE1,COUNTER_TYPE))
	{
		if(COUNTER_TYPE == "HEATS") 
			RetVal = GC_EQUIP_COUNTER1.InsertData(EQUIP_TYPE1,COUNTER_TYPE,100.,Commit,m_lastError);
		else
			RetVal = GC_EQUIP_COUNTER1.InsertData(EQUIP_TYPE1,COUNTER_TYPE,10000.,Commit,m_lastError);
	}
	std::vector<long> EquipIDList ;
  std::vector<long>::iterator it;
	EquipIDList = GC_EQUIP_CAT1.getEquipIdList(CSMC_DBData::unspecString,EQUIP_TYPE1);

  it = EquipIDList.begin();
  // we expect to use the first entry !
  if ( it != EquipIDList.end() )
  {
    EQUIP_ID1 = *it;
  }

	if(EQUIP_ID1 == CSMC_DBData::unspecLong) 
	{
			EQUIP_ID1 = GC_EQUIP_CAT1.GetMaxEQUIP_ID() + 1;		
			RetVal = GC_EQUIP_CAT1.InsertData(EQUIP_ID1,EQUIP_TYPE1,desc,CSMC_DBData::unspecLong,desc,Commit,m_lastError);
	}

	if(! PD_EQUIP_MOUNT1.select(EQUIP_ID1,EQUIP_TYPE1))
	{
		RetVal = PD_EQUIP_MOUNT1.InsertData(EQUIP_ID1,EQUIP_TYPE1,STRUCT_ID1,Commit,m_lastError);
	}

	if(PD_EQUIP_COUNTER1.select(EQUIP_ID1,EQUIP_TYPE1,COUNTER_TYPE))
	{
		 COUNTER_VALUE =  COUNTER_VALUE + PD_EQUIP_COUNTER1.getCOUNTER_VALUE(1);
     RetVal = PD_EQUIP_COUNTER1.updateOrInsert(EQUIP_ID1,EQUIP_TYPE1,COUNTER_TYPE,COUNTER_VALUE,Commit,m_lastError);
	}
	else
	{
     RetVal = PD_EQUIP_COUNTER1.updateOrInsert(EQUIP_ID1,EQUIP_TYPE1,COUNTER_TYPE,COUNTER_VALUE,Commit,m_lastError);
	}


	if(PLANT == "HMD")
	{
		RetVal = HDH_EQUIP_COUNTER1.updateOrInsert(HEATID,TREATID,PLANT,EQUIP_ID1,EQUIP_TYPE1,COUNTER_TYPE,COUNTER_VALUE,Commit,m_lastError);
	}
	else
	{
		RetVal = HD_EQUIP_COUNTER1.updateOrInsert(HEATID,TREATID,PLANT,EQUIP_ID1,EQUIP_TYPE1,COUNTER_TYPE,COUNTER_VALUE,Commit,m_lastError);
	}


	  if(GC_EQUIP_COUNTER1.select(EQUIP_TYPE1,COUNTER_TYPE))
		{
			if (GC_EQUIP_COUNTER1.getCOUNTER_LIMIT(1) < COUNTER_VALUE)
			{
				//send the log if life is expired
				sEventLogMessage msg = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
				msg.language = 1;
				//msg.destination = CSMC_DestCodes::HMDBotLine;
				msg.plantUnit = string(PLANT);
				//msg.processState = "";
				msg.eventId = 999999; 

				msg.messageText = string( "Equipment life is expired for EQUIP_TYPE : ") + string(EQUIP_TYPE1);
				msg.messageText2 = string( "Equipment life is expired for EQUIP_TYPE : ") + string(EQUIP_TYPE1);
				msg.severity = static_cast<c_e_severity_t>(c_e_warning);
				msg.opAckn = 1;
				msg.spare2 = string(HEATID) + "_" + string(TREATID);
				//msg.uniMessage = L"Equipment life is expired for EQUIP_TYPE : " ;
				cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
				pEventLog->sendMessage( msg);
			}
		}

  return RetVal;
}
