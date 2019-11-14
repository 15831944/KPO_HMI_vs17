// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CMANUALMATERIALBATCHWRAPPER_411254E200D2_INCLUDED
#define _INC_CMANUALMATERIALBATCHWRAPPER_411254E200D2_INCLUDED

class CEventMessage;

#include <string>

//##ModelId=411254E200D2
class CManualMaterialBatchWrapper 
{
public:
	//##ModelId=4110C1AD0207
	virtual bool doOnMaterialBatchCharged( CEventMessage & Event        );

	//##ModelId=4110C21500A8
	virtual bool doOnMaterialBatchDischarged( CEventMessage & Event      );

};

#endif /* _INC_CMANUALMATERIALBATCHWRAPPER_411254E200D2_INCLUDED */
