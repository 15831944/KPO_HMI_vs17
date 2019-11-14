// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFTAPPINGLADLEWRAPPER_411232C8003E_INCLUDED
#define _INC_CEAFTAPPINGLADLEWRAPPER_411232C8003E_INCLUDED

#include "CEAFModelWrapper.h"

//##ModelId=411232C8003E
class CEAFTappingLadleWrapper 
: public CEAFModelWrapper
{
public:
	//##ModelId=411232FF03D3
	bool doOnLadleStirringStart( CEventMessage &Event );

	//##ModelId=411233150265
	bool doOnLadleStirringStop( CEventMessage &Event );


	bool doOnFurnaceBottomStirringStart( CEventMessage &Event );

	//##ModelId=411233150265
	bool doOnFurnaceBottomStirringStop( CEventMessage &Event );

};

#endif /* _INC_CEAFTAPPINGLADLEWRAPPER_411232C8003E_INCLUDED */
