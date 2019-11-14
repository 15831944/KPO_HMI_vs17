// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLFMANUALMATERIALBATCHWRAPPER_41125FCA0243_INCLUDED
#define _INC_CLFMANUALMATERIALBATCHWRAPPER_41125FCA0243_INCLUDED

#include "CManualMaterialBatchWrapper.h"
#include "CLFModelWrapper.h"

//##ModelId=41125FCA0243
class CLFManualMaterialBatchWrapper 
: public CManualMaterialBatchWrapper
, public CLFModelWrapper
{
public:
	//##ModelId=41669117003A
	 bool doOnMaterialBatchCharged(CEventMessage& Event);

	//##ModelId=416691170282
	 bool doOnMaterialBatchDischarged(CEventMessage& Event);

};

#endif /* _INC_CLFMANUALMATERIALBATCHWRAPPER_41125FCA0243_INCLUDED */
