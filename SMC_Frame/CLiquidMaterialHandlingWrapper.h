// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLIQUIDMATERIALHANDLINGWRAPPER_4110B1E9015A_INCLUDED
#define _INC_CLIQUIDMATERIALHANDLINGWRAPPER_4110B1E9015A_INCLUDED

class CEventMessage;

#include <string>

//##ModelId=4110B1E9015A
class CLiquidMaterialHandlingWrapper 
{
public:
	//##ModelId=4110B6A10297
	virtual bool doOnHotMetalCharged( CEventMessage & Event    );

	//##ModelId=4110B7600242
	virtual bool doOnLiquidAdditionCharged( CEventMessage & Event    );

	//##ModelId=4110B89B03AD
	virtual bool doOnChangeOfLiquidAdditionData(CEventMessage &Event);

	//##ModelId=4110B93601A7
	virtual bool doOnLiquidFeCrCharged( CEventMessage & Event    );

	//##ModelId=4110B9DE007C
	virtual bool doOnLiquidSteelCharged( CEventMessage & Event  );

	//##ModelId=4110BA5E013F
	virtual bool doOnRemoveHotMetalData( CEventMessage & Event    );

	//##ModelId=4110BAE4025A
	virtual bool doOnRemoveLiquidAddition( CEventMessage & Event    );

	//##ModelId=4110BB7E03C4
	virtual bool doOnRemoveLiquidFeCrData( CEventMessage & Event    );

	//##ModelId=4110BBF503A7
	virtual bool doOnRemoveLiquidSteelData( CEventMessage & Event  );

protected:
	//##ModelId=4110B26C02A2
	virtual bool doSetLiquidMaterialData( CEventMessage & Event    );

	//##ModelId=4110B30C016C
	virtual bool doSetLiquidSteelData( CEventMessage & Event  );

	//##ModelId=4110B3220358
	virtual bool doSetLiquidFeCrData( CEventMessage & Event    );

	//##ModelId=4110B3630077
	virtual bool doSetLiquidAdditionData( CEventMessage & Event    );

	//##ModelId=4110B38C01D4
	virtual bool doSetHotMetalData( CEventMessage & Event  );

};

#endif /* _INC_CLIQUIDMATERIALHANDLINGWRAPPER_4110B1E9015A_INCLUDED */
