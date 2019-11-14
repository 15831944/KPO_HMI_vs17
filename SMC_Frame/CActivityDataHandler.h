
// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CActivityDataHandler_425FDBD601AD_INCLUDED
#define _INC_CActivityDataHandler_425FDBD601AD_INCLUDED

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"

#include <map>
#include <string>
#include "CIntfData.h"

class CDateTime;


class CActivityDataHandler 
{
public:
  CActivityDataHandler();

  CActivityDataHandler(seqActivityData& seqData);

	bool resetActivityData();

  bool resetActivityData(const std::string& ActivityName, long ActivityNo);

  bool resetActivityData(sActivityData &ActivityData);

	bool fillSequence(seqActivityData& seqData);

  CDateTime getStartTime(const std::string& ActivityName, long ActivityNo);
  CDateTime getEndTime(const std::string& ActivityName, long ActivityNo);

	bool addActivityData(const std::string& ActivityName, long ActivityNo, long ActivityStatus  );
  bool setActivityStatus(const std::string& ActivityName, long ActivityNo, long ActivityStatus );
	
  bool setActivityDataAtStart(const std::string& ActivityName, long ActivityNo, const std::string& Device, long ActivityStatus, const std::string& Type, const std::string& ValueName, double Value );
  bool setActivityDataAtEnd(const std::string& ActivityName, long ActivityNo, const std::string& Device, long ActivityStatus, const std::string& Type, const std::string& ValueName, double Value );

  bool setActivityDataAtStart(const std::string& ActivityName, long ActivityNo, const std::string& Device, long ActivityStatus, const std::string& Type, seqGasData& SeqGasData );
  bool setActivityDataAtEnd(const std::string& ActivityName, long ActivityNo, const std::string& Device, long ActivityStatus, const std::string& Type, seqGasData& SeqGasData );

  bool setActivityDataAtStart(const std::string& ActivityName, long ActivityNo, const std::string& Device, long ActivityStatus, const std::string& Type, seqStirringData& SeqStirringData );
  bool setActivityDataAtEnd(const std::string& ActivityName, long ActivityNo, const std::string& Device, long ActivityStatus, const std::string& Type, seqStirringData& SeqStirringData );

  //bool getActivityStart(const std::string& ActivityName, long ActivityNo, const std::string& Device, const std::string& Type, sActivity& Activity);
  //bool getActivityEnd(const std::string& ActivityName, long ActivityNo, const std::string& Device, const std::string& Type, sActivity& Activity);

  double getValueAtStart(const std::string& ActivityName, long ActivityNo, const std::string& Device, const std::string& Type, const std::string& ValueName);
  double getValueAtEnd(const std::string& ActivityName, long ActivityNo, const std::string& Device, const std::string& Type, const std::string& ValueName);

  seqGasData getGasDataAtStart(const std::string& ActivityName, long ActivityNo, const std::string& Device, const std::string& Type);
  seqGasData getGasDataAtEnd(const std::string& ActivityName, long ActivityNo, const std::string& Device, const std::string& Type);

  seqStirringData getStirringDataAtStart(const std::string& ActivityName, long ActivityNo, const std::string& Device, const std::string& Type);
  seqStirringData getStirringDataAtEnd(const std::string& ActivityName, long ActivityNo, const std::string& Device, const std::string& Type);

  double getDiffValue(const std::string& ActivityName, long ActivityNo, const std::string& Device, const std::string& Type, const std::string& ValueName);
  seqGasData getDiffGasData(const std::string& ActivityName, long ActivityNo, const std::string& Device, const std::string& Type);
  seqStirringData getDiffStirringData(const std::string& ActivityName, long ActivityNo, const std::string& Device, const std::string& Type);


  long getActivityStatus(const std::string& ActivityName, long ActivityNo);


  bool isActivityData(const std::string& ActivityName, long ActivityNo);
  bool isActivity(seqActivity & SeqActivity, const std::string& Device);
  bool isActivityValue(seqActivityValue & SeqActivityValue, const std::string& ValueName );


	//bool getActivityData(const std::string& ActivityName, long ActivityNo, sActivityData& ActivityData  );

	seqActivityData& getSequence();

  double getDuration(const std::string& ActivityName, long ActivityNo);
  double getAccumulatedTimes(const std::string& ActivityName, long ActivityNo, long ActivityStatus);

  seqActivityData getActivitiesAtStart(const std::string& ActivityName, const std::string& Device, const std::string& Type);
  seqActivityData getActivitiesAtEnd(const std::string& ActivityName, const std::string& Device, const std::string& Type);

  seqActivityData getActivities(const std::string& ActivityName, const std::string& Device);

  long getNoOfActivities();


private:
	seqActivityData  m_SeqActivityData;

};

#endif /* _INC_CActivityDataHandler_425FDBD601AD_INCLUDED */
