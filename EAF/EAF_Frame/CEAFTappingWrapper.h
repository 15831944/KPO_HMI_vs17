// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFTAPPINGWRAPPER_41123E2B037D_INCLUDED
#define _INC_CEAFTAPPINGWRAPPER_41123E2B037D_INCLUDED

#include "CEAFModelWrapper.h"

//##ModelId=411239BA0322
class CEAFTappingWrapper : public CEAFModelWrapper
  
{
public:
	//##ModelId=411239E901F9
	bool doOnTappingEnd( CEventMessage &Event );

	//##ModelId=41123A380198
	bool doOnTapLadleData( CEventMessage &Event );

	//##ModelId=411239F903C1
	bool doOnTappingStart( CEventMessage &Event );

private:
};

#endif /* _INC_CEAFTAPPINGWRAPPER_41123E2B037D_INCLUDED */
