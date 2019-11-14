// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_EAFSAMPLEMANAGER_4164FDA9006D_INCLUDED
#define _INC_CDM_EAFSAMPLEMANAGER_4164FDA9006D_INCLUDED

#include "CDM_SampleManager.h"

class CDM_EAFProductManagementInterface_Impl;
class CEventMessage;

class CDM_EAFSampleManager : public CDM_SampleManager
{
public:

	virtual ~CDM_EAFSampleManager();

	CDM_EAFSampleManager();

  std::string createSampleCodeFromScratch(std::string& ProductID, long ActSampleType, const std::string ActPlant, const std::string ActProcessStage, long ActSampleNo);

private:




};

#endif /* _INC_CDM_EAFSAMPLEMANAGER_4164FDA9006D_INCLUDED */
