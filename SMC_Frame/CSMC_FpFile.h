// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMC_FPFILE_42A5A70C0246_INCLUDED
#define _INC_CSMC_FPFILE_42A5A70C0246_INCLUDED

#include "cCBS_FpFile.h"

//##ModelId=42A5A70C0246
class CSMC_FpFile 
: public cCBS_FpFile
{
private:
	//##ModelId=42A5B3BF01E7
	bool m_Redirect;

public:
	// ------------------------------
	// Closes the file source
	//##ModelId=42A5A9D80015
	virtual int closeFile(void);

	//##ModelId=42A5A77503BB
	virtual ~CSMC_FpFile();

	//##ModelId=42A5A77601DD
	CSMC_FpFile(bool Redirect = false);

protected:
	// Opens the file with the given mode
	//##ModelId=42A5A7730227
	virtual int openModeFile(const char* omode_, const char* fileName_ = 0);

};

#endif /* _INC_CSMC_FPFILE_42A5A70C0246_INCLUDED */
