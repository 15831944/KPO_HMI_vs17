// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFMANUALMATERIALBATCHWRAPPER_41125B3B00BF_INCLUDED
#define _INC_CEAFMANUALMATERIALBATCHWRAPPER_41125B3B00BF_INCLUDED

#include "CEAFModelWrapper.h"
#include "CManualMaterialBatchWrapper.h"

//##ModelId=41126366010C
class CEAFManualMaterialBatchWrapper : public CManualMaterialBatchWrapper, public CEAFModelWrapper
  
{
public:
	//##ModelId=4152969701E8
	virtual bool doOnMaterialBatchCharged( CEventMessage &Event );

	//##ModelId=415296980110
	virtual bool doOnMaterialBatchDischarged( CEventMessage &Event );


};

#endif /* _INC_CEAFMANUALMATERIALBATCHWRAPPER_41125B3B00BF_INCLUDED */
