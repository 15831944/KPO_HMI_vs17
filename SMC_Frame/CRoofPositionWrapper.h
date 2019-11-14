// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CROOFPOSITIONWRAPPER_4111FDD4024C_INCLUDED
#define _INC_CROOFPOSITIONWRAPPER_4111FDD4024C_INCLUDED

class CEventMessage;

//##ModelId=4111FDD4024C
class CRoofPositionWrapper 
{
public:
	//##ModelId=411201990160
	virtual bool doOnRoofInDownPos(CEventMessage &Event);

	//##ModelId=411201BD0043
	virtual bool doOnRoofInUpPos(CEventMessage &Event);

	//##ModelId=411201FF02B0
	virtual bool doOnGantrySwungIn(CEventMessage &Event);

	//##ModelId=4112023002DC
	virtual bool doOnGantrySwungOut(CEventMessage &Event);

};

#endif /* _INC_CROOFPOSITIONWRAPPER_4111FDD4024C_INCLUDED */
