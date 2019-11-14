// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFOXYGENSIDELANCESWRAPPER_41122A5C00A2_INCLUDED
#define _INC_CEAFOXYGENSIDELANCESWRAPPER_41122A5C00A2_INCLUDED

#include "CEAFModelWrapper.h"

//##ModelId=41122A5C00A2
class CEAFOxygenSideLancesWrapper 
: public CEAFModelWrapper
{
public:
	//##ModelId=41122A9B01C3
	bool doOnOxygenSideLanceStart( CEventMessage &Event );

	//##ModelId=41122AB6005C
	bool doOnOxygenSideLanceStop( CEventMessage &Event );

};

#endif /* _INC_CEAFOXYGENSIDELANCESWRAPPER_41122A5C00A2_INCLUDED */
