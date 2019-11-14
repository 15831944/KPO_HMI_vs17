#ifndef SRECIPE_H
#define SRECIPE_H

#include <string>

//##ModelId=4225A6000053
struct sRecipeInfo
{
	//##ModelId=4225A600009A
  std::string RecipeName;
	//##ModelId=4225A60000AE
  std::string RecipeSource;
	//##ModelId=4225A60000B7
  long RecipeStatus;
	//##ModelId=4225A60000C1
  long RecipeNo;
	//##ModelId=4225A60000CC
  std::string RecipeTarget;
	//##ModelId=4225A60000D5
  double DurSinceHeatAnnounce;
	//##ModelId=4225A60000DF
  double DurSinceHeatStart;

  double ChargeMoment;
};
#endif
