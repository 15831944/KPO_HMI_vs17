// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSOLIDMATERIALHANDLINGWRAPPER_4110C0980317_INCLUDED
#define _INC_CSOLIDMATERIALHANDLINGWRAPPER_4110C0980317_INCLUDED

class CEventMessage;

#include <string>

//##ModelId=4110C0980317
class CSolidMaterialHandlingWrapper 
{
public:
	//##ModelId=4111032D0078
	virtual bool doOnChangedMatSetPointsOperator( CEventMessage & Event        );

	//##ModelId=4111143E02E7
	virtual bool doOnDisableSourceRecipe( CEventMessage & Event      );

	//##ModelId=411114D00034
	virtual bool doOnEnableSourceRecipe( CEventMessage & Event      );

	//##ModelId=411115DD033E
	virtual bool doOnRecipeMaterialCharged( CEventMessage & Event            );

	//##ModelId=411116A801B9
	virtual bool doOnRecipeMaterialDischarged( CEventMessage & Event          );

	//##ModelId=4111175600A1
	virtual bool doOnRecipeWeighingComplete( CEventMessage & Event      );

};

#endif /* _INC_CSOLIDMATERIALHANDLINGWRAPPER_4110C0980317_INCLUDED */
