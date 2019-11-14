// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFLANCEMANIPWRAPPER_411225CD0325_INCLUDED
#define _INC_CEAFLANCEMANIPWRAPPER_411225CD0325_INCLUDED

#include "CEAFModelWrapper.h"

//##ModelId=411225CD0325
class CEAFLanceManipWrapper 
: public CEAFModelWrapper
{
public:
	//##ModelId=41122602015B
	bool doOnManipGasLanceStart( CEventMessage &Event );

	//##ModelId=4112261D0081
	bool doOnManipGasLanceStop( CEventMessage &Event );

	//##ModelId=4112263D01B7
	bool doOnManipInjLanceStart( CEventMessage &Event );

	//##ModelId=4112265700C7
	bool doOnManipInjLanceStop( CEventMessage &Event );

};

#endif /* _INC_CEAFLANCEMANIPWRAPPER_411225CD0325_INCLUDED */
