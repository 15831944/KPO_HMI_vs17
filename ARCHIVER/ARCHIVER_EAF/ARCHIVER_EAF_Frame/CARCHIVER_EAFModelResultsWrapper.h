// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_EAFMODELRESULTSWRAPPER_415297DD0128_INCLUDED
#define _INC_CARCHIVER_EAFMODELRESULTSWRAPPER_415297DD0128_INCLUDED

#include "CEventMessage.h"
#include "CARCHIVER_ModelResultWrapper.h"

class CGC_PhaseContainer;

//##ModelId=415297DD0128
class CARCHIVER_EAFModelResultsWrapper  : public CARCHIVER_ModelResultWrapper
{
public:

  //##ModelId=419CC21300A0
	virtual ~CARCHIVER_EAFModelResultsWrapper();

	//##ModelId=41A367AF0134
	CARCHIVER_EAFModelResultsWrapper();

	//##ModelId=415299D10072
	bool doOnActualSetpoints(CEventMessage& Event);
	bool doOnRecipeSetpoints(CEventMessage& Event);

private:
  CGC_PhaseContainer *m_pGC_PhaseContainer;

  //##ModelId=41ADE222018C
	virtual void deleteDBClasses();

	//##ModelId=41ADE23002EB
	virtual void initDBClasses();

};

#endif /* _INC_CARCHIVER_EAFMODELRESULTSWRAPPER_415297DD0128_INCLUDED */
