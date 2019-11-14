// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMC_RECIPEHANDLER_42CE4A5A02DE_INCLUDED
#define _INC_CSMC_RECIPEHANDLER_42CE4A5A02DE_INCLUDED

#include <string>
#include <set>

#include "CSMC_DBData.h"

class CPD_RECIPE;
class CGC_RECIPE_L1;
class cCBS_StdConnection;

//Class will read RecipeL1 data from DB for an respective 
//plant.
//##ModelId=42CE4A5A02DE
class CSMC_RecipeHandler 
{
public:
	//##ModelId=42D5196E003D
	void setDBConnection();

	//##ModelId=42CE4AAD019A
	virtual ~CSMC_RecipeHandler();

	//##ModelId=42CE4AAE0111
	CSMC_RecipeHandler();

  bool CSMC_RecipeHandler::checkMatHandlingRecipeData(const std::string& PlantID, 
                                                      const std::string& HeatID,  
                                                      const std::string& TreatID, 
                                                      const std::string& Source, 
                                                      const std::string& ActRecipeName, 
                                                      long  &ActRecipeNo);

	//checks if the given model recipe no is usable
	bool checkModelRecipeData(const std::string& PlantID, const std::string& HeatID,  const std::string & TreatID, const std::string   & Source, const std::string  & ModelRecipeName, long  ModelRecipeNo, std::string  &ActRecipeName, long &ActRecipeNo);

  long getNextRecipeNo(const std::string& HeatID,  const std::string &TreatID, const std::string &PlantID, const std::string  &RecipeName, const std::string &Source, long BatchStatus = CSMC_DBData::unspecLong);

  bool translateToModelRecipe(const std::string &Plant, const std::string &RecipeName, long RecipeNo, std::string &RecipeNameModel, long &RecipeNoModel);

  std::set<long> getBatchStatusList(const std::string& PlantID, const std::string& HeatID,  const std::string& TreatID, const std::string& RecipeName, long  RecipeNo );

  long getLastBatchStatusNo(const std::string& PlantID, const std::string& HeatID,  const std::string& TreatID, const std::string& RecipeName, long  RecipeNo );

  long getActiveRecipeNo(const std::string& PlantID, const std::string& HeatID,  const std::string& TreatID, const std::string& RecipeName);

private:
  typedef struct {
    std::string Plant;
    std::string RecipeName;
    long RecipeNo;
    std::string RecipeNameModel;
    long RecipeNoModel;
  } RecipeData;

  std::vector<RecipeData> m_RecipeData;

  CPD_RECIPE* m_pPD_RECIPE;
	CGC_RECIPE_L1* m_pGC_RECIPE_L1;

	//logging to LogTask
	void log(const std::string& Message, long TraceLevel = 1);

	cCBS_StdConnection* m_pStdConnection;

};

#endif /* _INC_CSMC_RECIPEHANDLER_42CE4A5A02DE_INCLUDED */
