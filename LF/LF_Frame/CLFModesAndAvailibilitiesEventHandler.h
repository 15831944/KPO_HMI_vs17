// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLFMODESANDAVAILIBILITIESEVENTHANDLER_4118B8AD036B_INCLUDED
#define _INC_CLFMODESANDAVAILIBILITIESEVENTHANDLER_4118B8AD036B_INCLUDED

#include "CLFEventHandler.h"
#include "CLFModesandAvailibilitiesWrapper.h"

//##ModelId=4118B8AD036B
class CLFModesAndAvailibilitiesEventHandler 
: public CLFEventHandler
{
public:
	//##ModelId=4118B8BF0227
	virtual bool handleEvent( CEventMessage& EventMessage);

	//##ModelId=462767AB008C
  CLFModesAndAvailibilitiesEventHandler(CModelTask* pModelTask); 

protected:
	//##ModelId=416561B20179
	CLFModesAndAvailibilitiesWrapper LFModesAndAvailibilitiesWrapper;

};

#endif /* _INC_CLFMODESANDAVAILIBILITIESEVENTHANDLER_4118B8AD036B_INCLUDED */
