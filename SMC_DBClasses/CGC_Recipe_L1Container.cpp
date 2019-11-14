// Copyright (C) 2004 SMS Demag AG, Germany 

#include <sstream>

#include "CSMC_EventLogFrameController.h"
#include "CGC_RECIPE_L1.h"
#include "CGC_Recipe_L1Container.h"

CGC_Recipe_L1Container::~CGC_Recipe_L1Container()
{
  m_L1RecipeNoList.clear();
  m_L2RecipeNameList.clear();
}

CGC_Recipe_L1Container::CGC_Recipe_L1Container(cCBS_StdConnection *Connection, const std::string &Plant)
{
  if ( Connection )
  {
	  CGC_RECIPE_L1 GC_RECIPE_L1( Connection );
    m_L1RecipeNoList   = GC_RECIPE_L1.getL1RecipeNoList( Plant );
    m_L2RecipeNameList = GC_RECIPE_L1.getL2RecipeNameList( Plant );    
  }
  else
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DatabaseConnectionError(sMessage,
                        "Can not instantiate DB class in case of NULL pointer to connection",
                        "Terminating program!");
    exit(EXIT_FAILURE);
  }
}

long CGC_Recipe_L1Container::getL1RecipeNoByL2Name(long L2_Recipe_No, const std::string  & RecipeName )
{
  long lL1RecipeNo = -1;
  std::ostringstream L2RecipeName;

  L2RecipeName << RecipeName;
  L2RecipeName << "_";
  L2RecipeName << L2_Recipe_No;
  
  std::map<std::string,long>::iterator it;

  it = m_L2RecipeNameList.find(L2RecipeName.str());

  if ( it != m_L2RecipeNameList.end() )
  {
  	lL1RecipeNo = it->second;
  }
  else
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_RecipeConversion(sMessage, RecipeName.c_str(), L2_Recipe_No);
  }

  return lL1RecipeNo;
}

std::string CGC_Recipe_L1Container::getL2RecipeNameByL1No(long  L1_Recipe_No)
{
  std::string RecipeName = DEF::Undefined ;
  std::map< long, std::pair< std::string, long> >::iterator it;

  it = m_L1RecipeNoList.find( L1_Recipe_No );
  if ( it != m_L1RecipeNoList.end() )
  {
    RecipeName = it->second.first;
  }
  else
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_RecipeConversion(sMessage, L1_Recipe_No);
  }

  return RecipeName;
}

long CGC_Recipe_L1Container::getL2RecipeNoByL1No( long  L1_Recipe_No)
{
  long lRecipeNo = -1;
  std::map< long, std::pair< std::string, long> >::iterator it;

  it = m_L1RecipeNoList.find( L1_Recipe_No );
  if ( it != m_L1RecipeNoList.end() )
  {
    lRecipeNo = it->second.second;
  }
  else
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_RecipeConversion(sMessage, L1_Recipe_No);
  }

  return lRecipeNo;
}

