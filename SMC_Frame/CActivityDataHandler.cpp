
// Copyright (C) 2004 SMS Demag AG

#include "CDateTime.h"
#include "CGasDataHandler.h"
#include "CActivityDataHandler.h"

CActivityDataHandler::CActivityDataHandler()
{
}

CActivityDataHandler::CActivityDataHandler(seqActivityData& seqData)
: m_SeqActivityData(seqData)
{
}


bool CActivityDataHandler::resetActivityData()
{
  return true;
}

bool CActivityDataHandler::resetActivityData(sActivityData &ActivityData)
{
  return true;
}

double CActivityDataHandler::getDuration(const std::string& ActivityName, long ActivityNo)
{
  double RetValue = DEF::Inv_Double;
  return RetValue;
}

double CActivityDataHandler::getAccumulatedTimes(const std::string& ActivityName, long ActivityNo, long ActivityStatus)
{
  double RetValue = DEF::Inv_Double;
  return RetValue;
}


bool CActivityDataHandler::resetActivityData(const std::string& ActivityName, long ActivityNo)
{
  bool RetValue = false;
  return RetValue;
}

bool CActivityDataHandler::setActivityDataAtStart(const std::string& ActivityName, long ActivityNo, const std::string& Device, long ActivityStatus, const std::string& Type, seqStirringData& SeqStirringData )
{
  bool RetValue = true;
  return RetValue;
}

bool CActivityDataHandler::setActivityDataAtEnd(const std::string& ActivityName, long ActivityNo, const std::string& Device, long ActivityStatus, const std::string& Type, seqStirringData& SeqStirringData )
{
  bool RetValue = true;
  return RetValue;
}



bool CActivityDataHandler::setActivityDataAtStart(const std::string& ActivityName, long ActivityNo, const std::string& Device, long ActivityStatus, const std::string& Type, seqGasData& SeqGasData )
{
  bool RetValue = true;
  return RetValue;
}

bool CActivityDataHandler::setActivityDataAtEnd(const std::string& ActivityName, long ActivityNo, const std::string& Device, long ActivityStatus, const std::string& Type, seqGasData& SeqGasData )
{
  bool RetValue = true;
  return RetValue;
}



bool CActivityDataHandler::setActivityDataAtStart(const std::string& ActivityName, long ActivityNo, const std::string& Device, long ActivityStatus, const std::string& Type, const std::string& ValueName, double Value )
{
  bool RetValue = false;
  return RetValue;
}

bool CActivityDataHandler::setActivityDataAtEnd(const std::string& ActivityName, long ActivityNo, const std::string& Device, long ActivityStatus, const std::string& Type, const std::string& ValueName, double Value )
{
  bool RetValue = false;
  return RetValue;
}

bool CActivityDataHandler::setActivityStatus(const std::string& ActivityName, long ActivityNo, long ActivityStatus )
{
  return true;
}


bool CActivityDataHandler::addActivityData(const std::string& ActivityName, long ActivityNo, long ActivityStatus )
{
  return true;
}


long CActivityDataHandler::getActivityStatus(const std::string& ActivityName, long ActivityNo)
{
  long RetValue = DEF::Inv_Long;
  return RetValue;
}

bool CActivityDataHandler::isActivityData(const std::string& ActivityName, long ActivityNo)
{
  bool RetValue = false;
  return RetValue;
}

bool CActivityDataHandler::isActivity(seqActivity & SeqActivity, const std::string& Device )
{
  bool RetValue = false;
  return RetValue;
}

bool CActivityDataHandler::isActivityValue(seqActivityValue & SeqActivityValue, const std::string& ValueName )
{
  bool RetValue = false;
  return RetValue;
}

CDateTime CActivityDataHandler::getStartTime(const std::string& ActivityName, long ActivityNo)
{
  CDateTime Date = CDateTime::InvalidDateTime();
  return Date;
}

CDateTime CActivityDataHandler::getEndTime(const std::string& ActivityName, long ActivityNo)
{
  CDateTime Date = CDateTime::InvalidDateTime();
  return Date;
}

double CActivityDataHandler::getValueAtStart(const std::string& ActivityName, long ActivityNo, const std::string& Device, const std::string& Type, const std::string& ValueName)
{
  double RetValue = DEF::Inv_Double;
  return RetValue;
}

double CActivityDataHandler::getValueAtEnd(const std::string& ActivityName, long ActivityNo, const std::string& Device, const std::string& Type, const std::string& ValueName)
{
  double RetValue = DEF::Inv_Double;
  return RetValue;
}

double CActivityDataHandler::getDiffValue(const std::string& ActivityName, long ActivityNo, const std::string& Device, const std::string& Type, const std::string& ValueName)
{
  double RetValue = getValueAtEnd(ActivityName, ActivityNo, Device, Type, ValueName) - 
                    getValueAtStart(ActivityName, ActivityNo, Device, Type, ValueName);

  return RetValue;
}

seqGasData CActivityDataHandler::getDiffGasData(const std::string& ActivityName, long ActivityNo, const std::string& Device, const std::string& Type)
{
  seqGasData SeqGasData;

  CGasDataHandler GasDataHandler;
  
  GasDataHandler.setGasData(  getGasDataAtStart(ActivityName, ActivityNo, Device, Type) );
  GasDataHandler.diffGasData( getGasDataAtEnd  (ActivityName, ActivityNo, Device, Type) );

  GasDataHandler.fillSequence(SeqGasData);

  return SeqGasData;
}
  

seqStirringData CActivityDataHandler::getDiffStirringData(const std::string& ActivityName, long ActivityNo, const std::string& Device, const std::string& Type)
{
  seqStirringData SeqStirringData;

  return SeqStirringData;
}



seqGasData CActivityDataHandler::getGasDataAtStart(const std::string& ActivityName, long ActivityNo, const std::string& Device, const std::string& Type)
{
  seqGasData SeqGasData;

  sActivity Activity;
  sActivityData ActivityData;

  for ( long i = 0 ; i < CIntfData::getLength(m_SeqActivityData) ; ++i )
  {
    CIntfData::getAt(ActivityData,m_SeqActivityData,i);

    if ( ActivityName == std::string(ActivityData.ActivityName) && 
         ActivityNo   == ActivityData.ActivityNo                      ) 
    {
      for ( long j = 0 ; j < CIntfData::getLength(ActivityData.StartActivity) ; ++j )
      {
        sActivity Activity;

        CIntfData::getAt(Activity,ActivityData.StartActivity,j);

        if ( Device == std::string(Activity.Device) && 
             Type   == std::string(Activity.Type)     )
        {
          for ( long k = 0 ; k < CIntfData::getLength(Activity.ActivityValue); ++k )
          {
            sActivityValue ActivityValue;
            CIntfData::getAt(ActivityValue,Activity.ActivityValue,k);

            std::string Name  = ActivityValue.Name;
            double      Value = ActivityValue.Value;

            sGasData GasData;
            GasData.GasType   = Name.c_str();
            GasData.GasValue  = Value;

            CIntfData::insert(SeqGasData,GasData);
          }
        }
      }
    }
  }

  return SeqGasData;
}

seqGasData CActivityDataHandler::getGasDataAtEnd(const std::string& ActivityName, long ActivityNo, const std::string& Device, const std::string& Type)
{
  seqGasData SeqGasData;

  sActivity Activity;
  sActivityData ActivityData;

  for ( long i = 0 ; i < CIntfData::getLength(m_SeqActivityData) ; ++i )
  {
    CIntfData::getAt(ActivityData,m_SeqActivityData,i);

    if ( ActivityName == std::string(ActivityData.ActivityName) && 
         ActivityNo   == ActivityData.ActivityNo                      ) 
    {
      for ( long j = 0 ; j < CIntfData::getLength(ActivityData.EndActivity) ; ++j )
      {
        sActivity Activity;

        CIntfData::getAt(Activity,ActivityData.EndActivity,j);

        if ( Device == std::string(Activity.Device) && 
             Type   == std::string(Activity.Type)     )
        {
          for ( long k = 0 ; k < CIntfData::getLength(Activity.ActivityValue); ++k )
          {
            sActivityValue ActivityValue;
            CIntfData::getAt(ActivityValue,Activity.ActivityValue,k);

            std::string Name  = ActivityValue.Name;
            double      Value = ActivityValue.Value;

            sGasData GasData;
            GasData.GasType   = Name.c_str();
            GasData.GasValue  = Value;

            CIntfData::insert(SeqGasData,GasData);
          }
        }
      }
    }
  }

  return SeqGasData;
}

seqStirringData CActivityDataHandler::getStirringDataAtStart(const std::string& ActivityName, long ActivityNo, const std::string& Device, const std::string& Type)
{
  seqStirringData SeqStirringData;

  sActivity Activity;
  sActivityData ActivityData;

  for ( long i = 0 ; i < CIntfData::getLength(m_SeqActivityData) ; ++i )
  {
    CIntfData::getAt(ActivityData,m_SeqActivityData,i);

    if ( ActivityName == std::string(ActivityData.ActivityName) && 
         ActivityNo   == ActivityData.ActivityNo                      ) 
    {
      for ( long j = 0 ; j < CIntfData::getLength(ActivityData.StartActivity) ; ++j )
      {
        sActivity Activity;

        CIntfData::getAt(Activity,ActivityData.StartActivity,j);

        if ( Device == std::string(Activity.Device) && 
             Type   == std::string(Activity.Type)     )
        {
          for ( long k = 0 ; k < CIntfData::getLength(Activity.ActivityValue); ++k )
          {
            sActivityValue ActivityValue;
            CIntfData::getAt(ActivityValue,Activity.ActivityValue,k);

            std::string Name  = ActivityValue.Name;
            double      Value = ActivityValue.Value;

            sStirringData StirringData;

            seqGasData SeqGasData;

            SeqGasData = getGasDataAtStart(ActivityName, ActivityNo, Device, Type);

            StirringData.Device   = Device.c_str();
            StirringData.GasData  = SeqGasData;
            
            CIntfData::insert(SeqStirringData,StirringData);
          }
        }
      }
    }
  }

  return SeqStirringData;
}

seqStirringData CActivityDataHandler::getStirringDataAtEnd(const std::string& ActivityName, long ActivityNo, const std::string& Device, const std::string& Type )
{
  seqStirringData SeqStirringData;

  sActivity Activity;
  sActivityData ActivityData;

  for ( long i = 0 ; i < CIntfData::getLength(m_SeqActivityData) ; ++i )
  {
    CIntfData::getAt(ActivityData,m_SeqActivityData,i);

    if ( ActivityName == std::string(ActivityData.ActivityName) && 
         ActivityNo   == ActivityData.ActivityNo                      ) 
    {
      for ( long j = 0 ; j < CIntfData::getLength(ActivityData.EndActivity) ; ++j )
      {
        sActivity Activity;

        CIntfData::getAt(Activity,ActivityData.EndActivity,j);

        if ( Device == std::string(Activity.Device) && 
             Type   == std::string(Activity.Type)     )
        {
          for ( long k = 0 ; k < CIntfData::getLength(Activity.ActivityValue); ++k )
          {
            sActivityValue ActivityValue;
            CIntfData::getAt(ActivityValue,Activity.ActivityValue,k);

            std::string Name  = ActivityValue.Name;
            double      Value = ActivityValue.Value;

            sStirringData StirringData;

            seqGasData SeqGasData;

            SeqGasData = getGasDataAtEnd(ActivityName, ActivityNo, Device, Type);

            StirringData.Device   = Device.c_str();
            StirringData.GasData  = SeqGasData;
            
            CIntfData::insert(SeqStirringData,StirringData);
          }
        }
      }
    }
  }

  return SeqStirringData;
}




seqActivityData& CActivityDataHandler::getSequence()
{
  return m_SeqActivityData;
}

long CActivityDataHandler::getNoOfActivities()
{
  return CIntfData::getLength(m_SeqActivityData);
}



bool CActivityDataHandler::fillSequence(seqActivityData& seqData)
{
  m_SeqActivityData = seqData;
  return true;
}

seqActivityData CActivityDataHandler::getActivitiesAtStart(const std::string& ActivityName, const std::string& Device, const std::string& Type)
{
  seqActivityData SeqActivityData;

  for ( long i = 0 ; i < CIntfData::getLength(m_SeqActivityData); ++i )
  {
    sActivityData ActivityData;
    CIntfData::getAt(ActivityData,m_SeqActivityData,i);

    if ( ActivityName   == std::string( ActivityData.ActivityName ) )
    {
      for ( long j = 0 ; j < CIntfData::getLength(ActivityData.StartActivity); ++j )
      {
        sActivity Activity;
        CIntfData::getAt(Activity,ActivityData.EndActivity,j);

        if ( Device == std::string(Activity.Device) && 
             Type   == std::string(Activity.Type)      )
        {
          CIntfData::insert(SeqActivityData,ActivityData);
        }
      }
    }
  }

  return SeqActivityData;
}

seqActivityData CActivityDataHandler::getActivitiesAtEnd(const std::string& ActivityName, const std::string& Device, const std::string& Type)
{
  seqActivityData SeqActivityData;

  for ( long i = 0 ; i < CIntfData::getLength(m_SeqActivityData); ++i )
  {
    sActivityData ActivityData;
    CIntfData::getAt(ActivityData,m_SeqActivityData,i);

    if ( ActivityName   == std::string( ActivityData.ActivityName ) )
    {
      for ( long j = 0 ; j < CIntfData::getLength(ActivityData.EndActivity); ++j )
      {
        sActivity Activity;
        CIntfData::getAt(Activity,ActivityData.EndActivity,j);

        if ( Device == std::string(Activity.Device) && 
             Type   == std::string(Activity.Type)      )
        {
          CIntfData::insert(SeqActivityData,ActivityData);
        }
      }
    }
  }

  return SeqActivityData;
}

seqActivityData CActivityDataHandler::getActivities(const std::string& ActivityName, const std::string& Device)
{
  seqActivityData SeqActivityData;

  for ( long i = 0 ; i < CIntfData::getLength(m_SeqActivityData); ++i )
  {
    sActivityData ActivityData;
    CIntfData::getAt(ActivityData,m_SeqActivityData,i);

    if ( ActivityName   == std::string( ActivityData.ActivityName ) )
    {
      for ( long j = 0 ; j < CIntfData::getLength(ActivityData.EndActivity); ++j )
      {
        sActivity Activity;
        CIntfData::getAt(Activity,ActivityData.StartActivity,j);

        if ( Device == std::string(Activity.Device) )
        {
          CIntfData::insert(SeqActivityData,ActivityData);
        }

        CIntfData::getAt(Activity,ActivityData.EndActivity,j);

        if ( Device == std::string(Activity.Device) )
        {
          CIntfData::insert(SeqActivityData,ActivityData);
        }

      }
    }
  }

  return SeqActivityData;
}


