// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_ActivityManager_425FDBD601AD_INCLUDED
#define _INC_CDM_ActivityManager_425FDBD601AD_INCLUDED

#include "CActivityManager.h"

//##ModelId=425FDBD601AD
class CDM_ActivityManager : public CActivityManager
{
public:
  CDM_ActivityManager();

  CDM_ActivityManager(seqActivityStatus& seqData);

};

#endif /* _INC_CDM_ActivityManager_425FDBD601AD_INCLUDED */
