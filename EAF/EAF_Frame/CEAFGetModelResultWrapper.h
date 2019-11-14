// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFGETMODELRESULTWRAPPER_4118A65401D7_INCLUDED
#define _INC_CEAFGETMODELRESULTWRAPPER_4118A65401D7_INCLUDED

#include "iSMC_DataProvider_s.hh"
#include "CEAFModelWrapper.h"

class CEAFModelResultEventHandler;

//##ModelId=4118A7460383
class CEAFGetModelResultWrapper : public CEAFModelWrapper  
{
private:
	//unique generated key readed from model result interface
	//##ModelId=41470BC303CD
  string m_Key;  
public:
	//##ModelId=4147F9F600E1
	virtual long getPredictionCalculationResult();

	//##ModelId=4118A79202E2
	long getModelResult();

	//##ModelId=41470BC40084
	virtual long getModelActualSetpoints();

	//##ModelId=41470BC400B6
	virtual long getMatRecipeSetpoints();

	//##ModelId=41470BC401D9
	virtual bool doModelResult(CEventMessage EventMessage );

	//##ModelId=41470BC40247
	virtual long getResultCodeAndMessage();

};

#endif /* _INC_CEAFGETMODELRESULTWRAPPER_4118A65401D7_INCLUDED */
