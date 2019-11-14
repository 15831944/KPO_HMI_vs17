
// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CActivityManager_425FDBD601AD_INCLUDED
#define _INC_CActivityManager_425FDBD601AD_INCLUDED

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"

#include <map>
#include <string>
#include "CIntfData.h"


class CActivityManager 
{
public:
  CActivityManager();

  CActivityManager(seqActivityStatus& seqData);

  virtual ~CActivityManager();

  bool initActivity(const std::string& Type, const std::string& Name);

  bool startActivity(const std::string& Type, const std::string& Name);
  bool endActivity(const std::string& Type, const std::string& Name);


  bool startCurrentActivity(const std::string& Type);
  bool endCurrentActivity(const std::string& Type);


  bool isActivityStatus(const std::string& Type, const std::string& Name, bool Status);
  bool isActivityStatus(const std::string& Type, const std::string& Name);

  bool addActivityStatus(const std::string& Type, const std::string& Name, bool Status, long No);

  long getActivityNo(const std::string& Type, const std::string& Name);

  bool fillSequence(seqActivityStatus& seqData);

  std::vector<std::string> getActivityNames(const std::string& Type);

  bool presetActivityStatus(const std::string& Type, const std::string& Name, bool Status);
  bool presetActivityStatus(bool Status);

  bool  getActivityStatus(const std::string& Type, const std::string& Name);

  std::string getCurrentActivityName(const std::string& Type);
  long getCurrentActivityNo(const std::string& Type);

	seqActivityStatus& getSequence();

private:
  seqActivityStatus  m_SeqActivityStatus;

};

#endif /* _INC_CActivityManager_425FDBD601AD_INCLUDED */
