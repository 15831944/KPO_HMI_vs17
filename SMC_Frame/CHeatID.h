// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHEATID_43FDD101016D_INCLUDED
#define _INC_CHEATID_43FDD101016D_INCLUDED

#include "CFormattedID.h"

//##ModelId=43FDD101016D
class CHeatID 
: public CFormattedID
{
public:
	//##ModelId=43FDD13F0180
	virtual ~CHeatID();

	//##ModelId=43FDD13F032F
	CHeatID();

	//##ModelId=44FE9C2E036C
  std::string generateHeatID(const std::string ID, const std::string PlantPrefix = "");

protected:
	//##ModelId=43FDD12B01AA
	static std::string m_QualifierHeatID;

	//##ModelId=471C72590387
  static std::string m_QualifierSeparator;

  static std::string m_QualifierPlantIDPrefix;

	//##ModelId=43FDD1210227
	virtual void init();

private:
	//##ModelId=43FDD12B01BE
	std::string m_HeatID;

};

#endif /* _INC_CHEATID_43FDD101016D_INCLUDED */
