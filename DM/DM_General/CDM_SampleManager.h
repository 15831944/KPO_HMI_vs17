// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_SAMPLEMANAGER_416A504B001C_INCLUDED
#define _INC_CDM_SAMPLEMANAGER_416A504B001C_INCLUDED

#include <string>

class CEventMessage;


//Class handling Sample relevant Data
class CDM_SampleManager 
{
public:

	virtual ~CDM_SampleManager();

	CDM_SampleManager();

  // returns generated sampel id
  std::string generateSampleId(long SampleType, const std::string& PlantId, const std::string& ProcessStage, long SampleNo, const std::string& SampleLocation);

};

#endif /* _INC_CDM_SAMPLEMANAGER_416A504B001C_INCLUDED */
