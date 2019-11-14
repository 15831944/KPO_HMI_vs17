// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CANALYSISHANDLINGWRAPPER_410FBFF00055_INCLUDED
#define _INC_CANALYSISHANDLINGWRAPPER_410FBFF00055_INCLUDED

class CEventMessage;

//##ModelId=410FBFF00055
class CAnalysisHandlingWrapper 
{
public:
	//##ModelId=410FC011023D
	virtual bool doOnSlagSampleTaken(CEventMessage &Event);

	//##ModelId=410FC011023E
	virtual bool doOnSteelSampleTaken(CEventMessage &Event);

	//##ModelId=410FC0110247
	virtual bool doOnSteelAnalysisReceived(CEventMessage &Event);

	//##ModelId=410FC0110248
	virtual bool doOnSlagAnalysisReceived(CEventMessage &Event);

};

#endif /* _INC_CANALYSISHANDLINGWRAPPER_410FBFF00055_INCLUDED */
