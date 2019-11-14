// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_LFSAMPLEMANAGER_4164FDA9006D_INCLUDED
#define _INC_CDM_LFSAMPLEMANAGER_4164FDA9006D_INCLUDED

#include "CDM_SampleManager.h"

class CDM_LFProductManagementInterface_Impl;
class CEventMessage;

class CDM_LFSampleManager : public CDM_SampleManager
{
public:

	virtual ~CDM_LFSampleManager();

	CDM_LFSampleManager();

  std::string createSampleCodeFromScratch(std::string& ProductID, long ActSampleType, const std::string ActPlantID, const std::string ActProcessStage, long ActSampleNo);

  void initProductSampleInformation(const std::string& ProductID, const std::string& Plant);
};

#endif /* _INC_CDM_LFSAMPLEMANAGER_4164FDA9006D_INCLUDED */
