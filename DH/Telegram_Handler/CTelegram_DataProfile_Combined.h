// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELEGRAM_DATAPROFILE_COMBINED_426F8F9202CE_INCLUDED
#define _INC_CTELEGRAM_DATAPROFILE_COMBINED_426F8F9202CE_INCLUDED

#include "CTelegram_DataProfile.h"

//##ModelId=426F8F9202CE
class CTelegram_DataProfile_Combined 
{
public:
	//##ModelId=426F8FFD0304
	virtual ~CTelegram_DataProfile_Combined();

	//##ModelId=426F8FFE00D4
	CTelegram_DataProfile_Combined(const std::string& TelegramID, const std::string& SourceName, const std::string& SourceType, const std::string& SourceNameSecond, const std::string& SourceTypeSecond, const std::string& TargetName, const std::string &TargetType   );
	
};

#endif /* _INC_CTELEGRAM_DATAPROFILE_COMBINED_426F8F9202CE_INCLUDED */
