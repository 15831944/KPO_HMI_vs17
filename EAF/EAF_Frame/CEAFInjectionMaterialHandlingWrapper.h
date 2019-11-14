// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFINJECTIONMATERIALHANDLINGWRAPPER_411127E5027D_INCLUDED
#define _INC_CEAFINJECTIONMATERIALHANDLINGWRAPPER_411127E5027D_INCLUDED

#include "CEAFModelWrapper.h"

//##ModelId=411127E5027D
class CEAFInjectionMaterialHandlingWrapper 
: public CEAFModelWrapper
{
public:
	//##ModelId=4111283C01EC
	bool doOnDolomiticLimeInjStart( CEventMessage &Event );

	//##ModelId=4111287D022C
	bool doOnDolomiticLimeInjStop( CEventMessage &Event );

};

#endif /* _INC_CEAFINJECTIONMATERIALHANDLINGWRAPPER_411127E5027D_INCLUDED */
