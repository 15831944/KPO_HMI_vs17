// Copyright (C) 2010 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _CData_Provider_Critical_Section_INCLUDED
#define _CData_Provider_Critical_Section_INCLUDED

#include <string>
#include "cCBS_CriticalSection.h"

class CData_Provider_Critical_Section
{
private:
  std::string m_ProviderName;

  cCBS_CriticalSection m_Section;

  bool m_Locked;

public:

  virtual ~CData_Provider_Critical_Section();

  CData_Provider_Critical_Section();

  CData_Provider_Critical_Section(const std::string& scope, bool lock = true);

  bool isLocked();

  bool tryLock(const std::string& scope);

  bool unlock(const std::string& scope);

  bool lock(const std::string& scope);

  void setProviderName(const std::string& scope);
};

#endif /* _INC_CDATA_PROVIDER_MUTEX_422ED6330280_INCLUDED */
