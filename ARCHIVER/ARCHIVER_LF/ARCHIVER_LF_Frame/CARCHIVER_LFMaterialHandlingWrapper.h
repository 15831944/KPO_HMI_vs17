// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_LFMATERIALHANDLINGWRAPPER_41EF73B702B6_INCLUDED
#define _INC_CARCHIVER_LFMATERIALHANDLINGWRAPPER_41EF73B702B6_INCLUDED

#include "CEventMessage.h"

#include "CARCHIVER_MaterialHandlingWrapper.h"


class CPDL_HEAT_DATA;
//##ModelId=462DDE5E011C
class CARCHIVER_LFMaterialHandlingWrapper 
: public CARCHIVER_MaterialHandlingWrapper
{
public:
	//##ModelId=462F05BD019C
  bool doOnMaterialHandlingReport(CEventMessage& Event);

	//##ModelId=462F05A5003A
  bool doOnLiqMatHandlingReport(CEventMessage& Event);

  //bool doOnhandleUpdatePurpose(CEventMessage& Event);

	//##ModelId=462E05C60173
	virtual ~CARCHIVER_LFMaterialHandlingWrapper();

	//##ModelId=462E05C502E3
	CARCHIVER_LFMaterialHandlingWrapper();

protected:
	//##ModelId=462E237F029B
	CPDL_HEAT_DATA* m_pPDL_HEAT_DATA;

	//##ModelId=462E05C90183
	virtual void deleteDBClasses();

	//##ModelId=462E05C80338
	virtual void initDBClasses();

};

#endif /* _INC_CARCHIVER_LFMATERIALHANDLINGWRAPPER_41EF73B702B6_INCLUDED */
