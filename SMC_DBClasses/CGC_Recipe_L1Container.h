// Copyright (C) 2004 SMS Demag AG, Germany 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGC_RECIPE_L1CONTAINER_423E8E310043_INCLUDED
#define _INC_CGC_RECIPE_L1CONTAINER_423E8E310043_INCLUDED

#include <string>
#include <map>

class cCBS_StdConnection;

class CGC_Recipe_L1Container 
{
public:
	std::string getL2RecipeNameByL1No(long L1_Recipe_No);

	long getL2RecipeNoByL1No(long L1_Recipe_No);

	virtual ~CGC_Recipe_L1Container();

	CGC_Recipe_L1Container(cCBS_StdConnection *Connection, const std::string &Plant);


	long getL1RecipeNoByL2Name(long L2_Recipe_No, const std::string  & RecipeName    );

private:
	std::map< long, std::pair< std::string, long> > m_L1RecipeNoList;

	 std::map<std::string, long>  m_L2RecipeNameList;
};

#endif /* _INC_CGC_RECIPE_L1CONTAINER_423E8E310043_INCLUDED */
