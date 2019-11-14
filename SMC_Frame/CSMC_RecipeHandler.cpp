// Copyright (C) 2004 SMS Demag AG

#include <sstream>
#include <map>

#include "iSMC_DataDefinitions_s.hh"
#include "cCBS_StdEventLogFrameController.h"
#include "CSMC_EventLogFrameController.h"
#include "cCBS_StdLog_Task.h"
#include "cCBS_StdDB_Task.h"
#include "cCBS_StdInitBase.h"

#include "DEF_GC_RECIPE_STATUS.h"
#include "CGC_RECIPE_L1.h"
#include "CPD_RECIPE.h"
#include "cCBS_StdConnection.h"

#include "CSMC_RecipeHandler.h"

//##ModelId=42CE4AAD019A
CSMC_RecipeHandler::~CSMC_RecipeHandler()
{
	if (m_pPD_RECIPE)
  {
    delete m_pPD_RECIPE;
  }

  if ( m_pGC_RECIPE_L1 )
  {
    delete m_pGC_RECIPE_L1;
  }

}

//##ModelId=42CE4AAE0111
CSMC_RecipeHandler::CSMC_RecipeHandler()
: m_pStdConnection(0)
, m_pPD_RECIPE(0)
, m_pGC_RECIPE_L1(0)
{
  setDBConnection();

  if( m_pStdConnection )
  {
    m_pPD_RECIPE    = new CPD_RECIPE(m_pStdConnection);
    m_pGC_RECIPE_L1 = new CGC_RECIPE_L1(m_pStdConnection);
  }
}

//##ModelId=42D5196E003D
void CSMC_RecipeHandler::setDBConnection()
{

  cCBS_StdDB_Task* pDB_Task = cCBS_StdDB_Task::getInstance();
  cCBS_StdInitBase *pStdInitBase = cCBS_StdInitBase::getInstance();

  if (pDB_Task)
  {
    try
    {
      std::string DBName;
      std::string DBUser;
      std::string DBPassword;
      
      bool result = false;
      if ( !( pStdInitBase->getEntry("DATABASE", "SMC_DBName", DBName) &&
              pStdInitBase->getEntry("DATABASE", "SMC_DBUser", DBUser)  &&
              pStdInitBase->getEntry("DATABASE", "SMC_DBPassword", DBPassword) ))
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DatabaseConnectionError(sMessage,
                            "Can not read SMC database settings from ini-file",
                            "Terminating Program !");
        exit(EXIT_FAILURE);
      }

      m_pStdConnection = pDB_Task->getCBS_StdConnection(DBName, DBUser, DBPassword);

    }
    catch(...) 
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,"",
                          "CSMC_RecipeHandler::setDBConnection()",
                          "Can't get DB connection!");
    }
  }
}

//##ModelId=42D2630100D4
bool CSMC_RecipeHandler::checkModelRecipeData(const std::string& PlantID, 
                                              const std::string& HeatID,  
                                              const std::string& TreatID, 
                                              const std::string& Source, 
                                              const std::string  & ModelRecipeName, 
                                              long  ModelRecipeNo, 
                                              std::string  &ActRecipeName, 
                                              long &ActRecipeNo)
{
  // check if given ModelRecipeNo is usable 
  // if not, search next available RecipeNo from Database

  bool RetValue = false;

  ActRecipeName.erase(); 
  ActRecipeNo = DEF::Inv_Long;

  try
  {
    if ( m_pStdConnection )
    {
      // number of usable RecipeNo's is limited
      long MinRecipeNo  = m_pGC_RECIPE_L1->getMinRecipeNo(PlantID,ModelRecipeName,ModelRecipeNo); // default = 1
      long MaxRecipeNo  = m_pGC_RECIPE_L1->getMaxRecipeNo(PlantID,ModelRecipeName,ModelRecipeNo); // default = 1
      ActRecipeName     = m_pGC_RECIPE_L1->getRecipeNameByModelData(PlantID,ModelRecipeName,ModelRecipeNo);

      // check if data have been defined for ModelRecipeName and ModelRecipeNo
      if ( ActRecipeName != CSMC_DBData::unspecString )
      {
        ActRecipeNo       = m_pPD_RECIPE->getActRecipeNo(HeatID,TreatID,PlantID,ModelRecipeName,Source);

        if ( ActRecipeNo != CSMC_DBData::unspecLong )
        {
          if ( m_pPD_RECIPE->isRecipeIniUse(HeatID,TreatID,PlantID,ModelRecipeName,ActRecipeNo,Source) )
          {
            ActRecipeNo = ActRecipeNo + 1;
            ActRecipeNo = min( ActRecipeNo , MaxRecipeNo ); // there is a limit to be considered
          }
        }
        else
        {
          ActRecipeNo = MinRecipeNo;
        }

        RetValue = true;
      }
      else
      {
        std::stringstream Key;
        Key << PlantID <<  " " << ModelRecipeName << " " << ModelRecipeNo;

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorSearchingData(sMessage,Key.str().c_str(),"CGC_RECIPE_L1");
      }
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DatabaseConnectionError(sMessage,"","connecting to PD_RECIPE");
    }
  }
  catch(cCBS_DBExc &e) 
  { 
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), "CSMC_RecipeHandler::checkModelRecipeData", "");    
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_RecipeHandler::checkModelRecipeData", "");
  }

	return RetValue;
}


// check if given MaterialHandlingRecipeNo is usable 
// if not, search next available RecipeNo from Database
bool CSMC_RecipeHandler::checkMatHandlingRecipeData(const std::string& PlantID, 
                                                    const std::string& HeatID,  
                                                    const std::string& TreatID, 
                                                    const std::string& Source, 
                                                    const std::string& ActRecipeName, 
                                                    long  &ActRecipeNo)
{

  bool RetValue = false;

  try
  {
    if ( m_pStdConnection )
    {
      if ( ActRecipeName != CSMC_DBData::unspecString )
      {
        if ( !m_pPD_RECIPE->isRecipeIniUse(HeatID,TreatID,PlantID,ActRecipeName,ActRecipeNo,Source) )
        {
          ;
        }
        // select for given recipe and source with highest known recipno at first row
        else if ( m_pPD_RECIPE->selectOrderdByRecipeName(HeatID, TreatID, PlantID, ActRecipeName, CSMC_DBData::unspecLong, Source, false) )
        {
          for ( long i = 1 ; i <= m_pPD_RECIPE->getLastRow(); ++i )
          {
            long RECIPENO = m_pPD_RECIPE->getRECIPENO(i);

            // if recipe is already in use, increase RECIPENO
            long BATCHSTATUSNO = m_pPD_RECIPE->getBATCHSTATUSNO(i);
  
            if ( BATCHSTATUSNO != DEF_GC_RECIPE_STATUS::Disabled && 
                 BATCHSTATUSNO != DEF_GC_RECIPE_STATUS::Calculated )
            {
              // increase ActRecipeNo only if batch is completely finished
              if ( BATCHSTATUSNO == DEF_GC_RECIPE_STATUS::Discharged)
              {
                // recipe is in use, increase RECIPENO
                ActRecipeNo = RECIPENO + 1;

                CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                pEventLog->EL_RecipeConversion(sMessage, RECIPENO, ActRecipeNo, ActRecipeName.c_str() );

                break;
              }
            }
            else
            {
              // recipe is not in use, take RECIPENO
              ActRecipeNo = RECIPENO;
            }
          } // for ( long i = 1 ; i <= m_pPD_RECIPE->getLastRow(); ++i )
        }

        RetValue = true;

      }
      else
      {
        std::stringstream Key;
        Key << PlantID <<  " " << ActRecipeName << " " << ActRecipeNo;

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorSearchingData(sMessage,Key.str().c_str(),"CGC_RECIPE_L1");
      }
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DatabaseConnectionError(sMessage,"","connecting to PD_RECIPE");
    }
  }
  catch(cCBS_DBExc &e) 
  { 
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), "CSMC_RecipeHandler::checkModelRecipeData", "");    
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_RecipeHandler::checkModelRecipeData", "");
  }

	return RetValue;
}


void CSMC_RecipeHandler::log(const std::string& Message, long TraceLevel)
{
  cCBS_StdLog_Task::getInstance()->log(Message,TraceLevel);
}

bool CSMC_RecipeHandler::translateToModelRecipe(const std::string &Plant, const std::string &RecipeName, long RecipeNo, std::string &RecipeNameModel, long &RecipeNoModel)
{
  bool RetValue = false;

  RecipeNameModel = CSMC_DBData::unspecString;
  RecipeNoModel   = CSMC_DBData::unspecLong;

  if ( Plant      != CSMC_DBData::unspecString  &&
       RecipeName != CSMC_DBData::unspecString  &&
       RecipeNo   != CSMC_DBData::unspecLong    )
  {
    if ( m_RecipeData.empty() )
    {
      // fill intermediate container with all recipes for respective plant unit
      if ( m_pGC_RECIPE_L1->select(Plant, CSMC_DBData::unspecString, CSMC_DBData::unspecLong) )
      {
        for ( long i = 1; i <= m_pGC_RECIPE_L1->getLastRow(); i++ )
        {
          RecipeData RD;
          RD.Plant            = m_pGC_RECIPE_L1->getPLANT(i);
          RD.RecipeName       = m_pGC_RECIPE_L1->getRECIPENAME(i);
          RD.RecipeNo         = m_pGC_RECIPE_L1->getRECIPENO(i);
        
          // to avoid reading recipes for report purpose
          if ( m_pGC_RECIPE_L1->getRECIPENAME_MODEL(i) != CSMC_DBData::unspecString )
          {
            RD.RecipeNameModel  = m_pGC_RECIPE_L1->getRECIPENAME_MODEL(i);
            RD.RecipeNoModel    = m_pGC_RECIPE_L1->getRECIPENO_MODEL(i);

            m_RecipeData.push_back(RD);
          }
        }
      }
    }

    std::vector<RecipeData>::iterator it;

    // search at intermediat container for incoming RecipeName & RecipeNo to find Model data
    for ( it = m_RecipeData.begin(); it != m_RecipeData.end(); ++it )
    {
      if ( it->Plant == Plant && it->RecipeNo == RecipeNo && it->RecipeName == RecipeName )
      {
        RecipeNameModel = it->RecipeNameModel;
        RecipeNoModel   = it->RecipeNoModel;
        RetValue = true;

        break;
      }
    }

    if ( RecipeNameModel == CSMC_DBData::unspecString )
    {
      std::stringstream Key;
      Key << Plant <<  " " << RecipeName <<  " " << RecipeNo;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorSearchingData(sMessage,Key.str().c_str(),"GC_RECIPE_L1");

      RetValue = false;
    }
  }

  return RetValue;
}

long CSMC_RecipeHandler::getNextRecipeNo(const std::string& HeatID,  const std::string &TreatID, const std::string &PlantID, const std::string  &RecipeName, const std::string &Source, long BatchStatus)
{
  long MinRecipeNo  = 1;
  long MaxRecipeNo  = 1;
  
  if ( m_pGC_RECIPE_L1->selectOrdered(PlantID, RecipeName, CSMC_DBData::unspecLong) )
  {
    MinRecipeNo = m_pGC_RECIPE_L1->getRECIPENO(1);
    MaxRecipeNo = m_pGC_RECIPE_L1->getRECIPENO(m_pGC_RECIPE_L1->getLastRow());
  }

  long ActRecipeNo = CSMC_DBData::unspecLong;

  // switch to next version of recipe dependent on BatchStatus 
  if ( m_pPD_RECIPE->select(HeatID, TreatID, PlantID, RecipeName, CSMC_DBData::unspecLong, Source, BatchStatus) &&
       m_pPD_RECIPE->getLastRow() == 1 )
  {
    ActRecipeNo = m_pPD_RECIPE->getRECIPENO(1);

    ActRecipeNo = ActRecipeNo + 1;
    ActRecipeNo = min( ActRecipeNo , MaxRecipeNo ); // there is a limit to be considered
  }
  else
  {
    // if recipe does not have any status excepted 0 and 90 than take start number
    if ( !m_pPD_RECIPE->isRecipeIniUse(HeatID, TreatID, PlantID, RecipeName, ActRecipeNo, Source) )
    {
      ActRecipeNo = MinRecipeNo;
    }
  }

  return ActRecipeNo;
}

long CSMC_RecipeHandler::getLastBatchStatusNo(const std::string& PlantID, const std::string& HeatID,  const std::string& TreatID, const std::string& RecipeName, long  RecipeNo )
{
  long BatchStatusNo = CSMC_DBData::unspecLong;

  try
  {
    if ( m_pStdConnection )
    {
      // search for highest BatchStatusNo of given recipe
      if ( m_pPD_RECIPE->selectOrderdByBatchStatusNo(HeatID, TreatID, PlantID, RecipeName, RecipeNo, false) )
      {
         BatchStatusNo = m_pPD_RECIPE->getBATCHSTATUSNO(1);
      }
      else
      {
        std::stringstream Key;
        Key << PlantID <<  " " << RecipeName << " " << RecipeNo;

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorSearchingData(sMessage,Key.str().c_str(),"PD_RECIPE");
      }
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DatabaseConnectionError(sMessage,"","connecting to PD_RECIPE");
    }
  }
  catch(cCBS_DBExc &e) 
  { 
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), "CSMC_RecipeHandler::getLastBatchStatusNo", "");    
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_RecipeHandler::getLastBatchStatusNo", "");
  }

	return BatchStatusNo;
}

std::set<long> CSMC_RecipeHandler::getBatchStatusList(const std::string& PlantID, const std::string& HeatID,  const std::string& TreatID, const std::string& RecipeName, long  RecipeNo )
{
  std::set<long> BatchStatusList;

  try
  {
    if ( m_pStdConnection )
    {
      // search for highest BatchStatusNo of given recipe
      if ( m_pPD_RECIPE->selectOrderdByBatchStatusNo(HeatID, TreatID, PlantID, RecipeName, RecipeNo, false) )
      {
        for ( long i = 1; i <= m_pPD_RECIPE->getLastRow(); ++i )
        {
          BatchStatusList.insert(m_pPD_RECIPE->getBATCHSTATUSNO(1));
        }
      }
      else
      {
        std::stringstream Key;
        Key << PlantID <<  " " << RecipeName << " " << RecipeNo;

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorSearchingData(sMessage,Key.str().c_str(),"PD_RECIPE");
      }
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DatabaseConnectionError(sMessage,"","connecting to PD_RECIPE");
    }
  }
  catch(cCBS_DBExc &e) 
  { 
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), "CSMC_RecipeHandler::getBatchStatusList", "");    
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_RecipeHandler::getBatchStatusList", "");
  }

	return BatchStatusList;
}


long CSMC_RecipeHandler::getActiveRecipeNo(const std::string& PlantID, const std::string& HeatID,  const std::string& TreatID, const std::string& RecipeName)
{
  long RecipeNo = CSMC_DBData::unspecLong;

  try
  {
    if ( m_pStdConnection )
    {
      // search for highest recipeNo of given recipe
      if ( m_pPD_RECIPE->selectInUse(HeatID, TreatID, PlantID, RecipeName, CSMC_DBData::unspecLong, CSMC_DBData::unspecString) )
      {
        RecipeNo = m_pPD_RECIPE->getRECIPENO(1);
      }
      else
      {
        std::stringstream Key;
        Key << PlantID <<  " " << RecipeName << " " << RecipeNo;

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorSearchingData(sMessage,Key.str().c_str(),"PD_RECIPE");
      }
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DatabaseConnectionError(sMessage,"","connecting to PD_RECIPE");
    }
  }
  catch(cCBS_DBExc &e) 
  { 
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), "CSMC_RecipeHandler::getActiveRecipeNo", "");    
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSMC_RecipeHandler::getActiveRecipeNo", "");
  }

	return RecipeNo;
}



