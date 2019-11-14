// Copyright (C) 2009 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CMEDIADATAHANDLER_425FDBD601AD_INCLUDED
#define _INC_CMEDIADATAHANDLER_425FDBD601AD_INCLUDED

#include "iSMC_DataDefinitions_s.hh"

#include <string>
#include "CIntfData.h"
#include "DEF_GC_MODEL_MEDIA_TYPE.h"
#include "DEF_GC_MODEL_MEDIA_DEVICE.h"


//##ModelId=4725C63E0269
class CMediaDataHandler
{
public:
	//initialize with media data sequence
  void setMediaData(const seqConArcMediaData& MediaData);

  // Flow and Cons are output parameter
  bool getFlowCons(const std::string& DeviceName, long DeviceNo, long MediaTypeSelect, const std::string& MediaType, double& Flow, double& Cons);

  // all parameters are output parameters
  bool getBottmStirrData(std::string& GasType, double& Flow, double& Cons);

private:
  seqConArcMediaData m_MediaData;
};

#endif /* _INC_CMEDIADATAHANDLER_425FDBD601AD_INCLUDED */
