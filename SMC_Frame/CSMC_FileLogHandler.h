// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMC_FILELOGHANDLER_41FE1027018F_INCLUDED
#define _INC_CSMC_FILELOGHANDLER_41FE1027018F_INCLUDED

#include "cCBS_StdLogHandler.h"

class cCBS_StdFile;
class cCBS_FileRing;
class CSMC_FpFile;

//##ModelId=41FE1027018F
class CSMC_FileLogHandler 
: public cCBS_StdLogHandler
{
private:
	//##ModelId=41FE182F02E4
	CSMC_FpFile* m_File;

	//##ModelId=41FE1843024E
	cCBS_FileRing* m_Ring;

public:
	//##ModelId=41FE13A403BA
	virtual ~CSMC_FileLogHandler();

	//##ModelId=41FE13A50180
  CSMC_FileLogHandler(const std::string& Filename = "");

	//##ModelId=41FE111D0299
	virtual void log(const std::string& Message, long Level);

};

#endif /* _INC_CSMC_FILELOGHANDLER_41FE1027018F_INCLUDED */
