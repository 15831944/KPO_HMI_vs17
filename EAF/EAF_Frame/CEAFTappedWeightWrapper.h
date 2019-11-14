// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFTAPPEDWEIGHTWRAPPER_41123B27033F_INCLUDED
#define _INC_CEAFTAPPEDWEIGHTWRAPPER_41123B27033F_INCLUDED

#include "CEAFModelWrapper.h"

//##ModelId=41123B27033F
class CEAFTappedWeightWrapper 
: public CEAFModelWrapper
{
public:
	//##ModelId=41123B65009C
	bool doOnSetTappedWeight( CEventMessage &Event );

};

#endif /* _INC_CEAFTAPPEDWEIGHTWRAPPER_41123B27033F_INCLUDED */
