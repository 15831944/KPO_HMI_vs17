// Copyright (C) 2009 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_COMPUTERMODEWRAPPER_45E5334A01A8_INCLUDED
#define _INC_CARCHIVER_COMPUTERMODEWRAPPER_45E5334A01A8_INCLUDED

#include "CEventMessage.h"
#include "CARCHIVER_Wrapper.h"
#include "CPD_COMP_DATA.h"


class CARCHIVER_ComputerModeWrapper 
: public CARCHIVER_Wrapper
{
public:
  CARCHIVER_ComputerModeWrapper();

  virtual ~CARCHIVER_ComputerModeWrapper();

protected:
  CPD_COMP_DATA* m_pPD_COMP_DATA;

  bool handleSetComputerMode(CEventMessage& Event, seqComputerModes& SeqComputerModes, long CarNo=-1);

  virtual void initDBClasses();

  virtual void deleteDBClasses();

};

#endif /* _INC_CARCHIVER_COMPUTERMODEWRAPPER_45E5334A01A8_INCLUDED */
