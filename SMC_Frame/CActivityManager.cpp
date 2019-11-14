
// Copyright (C) 2004 SMS Demag AG

#include "CDateTime.h"
#include "CActivityManager.h"

CActivityManager::CActivityManager(seqActivityStatus& seqData)
: m_SeqActivityStatus(seqData)
{
}

CActivityManager::CActivityManager()
{
}


CActivityManager::~CActivityManager()
{
}

bool CActivityManager::initActivity(const std::string& Type, const std::string& Name)
{
  bool RetValue = true;

  if ( !isActivityStatus(Type,Name))
  {
    // insert activity to m_SeqActivityStatus
    addActivityStatus(Type,Name,true,0);  // set active but not yet started
  }
  else
  {
    for ( long i = 0 ; i < CIntfData::getLength(m_SeqActivityStatus) ; ++i )
    {
      sActivityStatus ActivityStatus;
      CIntfData::getAt(ActivityStatus,m_SeqActivityStatus,i);

      if ( std::string(ActivityStatus.ActivityType) == Type )
      {
        if ( std::string(ActivityStatus.ActivityName) == Name )
        {
          ActivityStatus.ActivityStatus = true; // set active 

          // update m_SeqActivityStatus
          CIntfData::setAt(m_SeqActivityStatus,ActivityStatus,i);
        }
      }
    }
  }

  return RetValue;
}

bool CActivityManager::startCurrentActivity(const std::string& Type)
{
  std::string Name = getCurrentActivityName(Type);

  return startActivity(Type, Name);
}



bool CActivityManager::startActivity(const std::string& Type, const std::string& Name)
{
  bool RetValue = true;

  if ( !isActivityStatus(Type,Name))
  {
    // insert activity to m_SeqActivityStatus
    addActivityStatus(Type,Name,true,1);  
  }
  else
  {
    for ( long i = 0 ; i < CIntfData::getLength(m_SeqActivityStatus) ; ++i )
    {
      sActivityStatus ActivityStatus;
      CIntfData::getAt(ActivityStatus,m_SeqActivityStatus,i);

      if ( std::string(ActivityStatus.ActivityType) == Type )
      {
        if ( std::string(ActivityStatus.ActivityName) == Name )
        {
          // increase ActivityNo for each start !
          ActivityStatus.ActivityNo     = ActivityStatus.ActivityNo + 1;
          ActivityStatus.ActivityStatus = true;

          // update m_SeqActivityStatus
          CIntfData::setAt(m_SeqActivityStatus,ActivityStatus,i);
        }
      }
    }
  }

  return RetValue;
}

bool CActivityManager::endActivity(const std::string& Type, const std::string& Name)
{
  bool RetValue = true;

  if ( !isActivityStatus(Type,Name))
  {
    // insert activity to m_SeqActivityStatus
    addActivityStatus(Type,Name,false,1);  
  }
  else
  {
    for ( long i = 0 ; i < CIntfData::getLength(m_SeqActivityStatus) ; ++i )
    {
      sActivityStatus ActivityStatus;
      CIntfData::getAt(ActivityStatus,m_SeqActivityStatus,i);

      if ( std::string(ActivityStatus.ActivityType) == Type )
      {
        if ( std::string(ActivityStatus.ActivityName) == Name )
        {
          ActivityStatus.ActivityStatus = false;

          // update m_SeqActivityStatus
          CIntfData::setAt(m_SeqActivityStatus,ActivityStatus,i);

        }
      }
    }
  }

  return RetValue;
}


bool CActivityManager::addActivityStatus(const std::string& Type, const std::string& Name, bool Status, long No)
{
  sActivityStatus ActivityStatus;
  ActivityStatus.ActivityType   = Type.c_str();
  ActivityStatus.ActivityName   = Name.c_str();
  ActivityStatus.ActivityStatus = Status;
  ActivityStatus.ActivityNo     = No;

  CIntfData::insert(m_SeqActivityStatus,ActivityStatus);

  return true;
}


bool CActivityManager::presetActivityStatus(const std::string& Type, const std::string& Name, bool Status)
{
  bool RetValue = false;

  for ( long i = 0 ; i < CIntfData::getLength(m_SeqActivityStatus) ; ++i )
  {
    sActivityStatus ActivityStatus;
    CIntfData::getAt(ActivityStatus,m_SeqActivityStatus,i);

    if ( std::string(ActivityStatus.ActivityType) == Type )
    {
      if ( std::string(ActivityStatus.ActivityName) == Name )
      {
        ActivityStatus.ActivityStatus = Status;

        // update m_SeqActivityStatus
        CIntfData::setAt(m_SeqActivityStatus,ActivityStatus,i);

        RetValue = true;

      }
    }
  }

  return RetValue;
}

bool CActivityManager::presetActivityStatus(bool Status)
{
  bool RetValue = false;

  for ( long i = 0 ; i < CIntfData::getLength(m_SeqActivityStatus) ; ++i )
  {
    sActivityStatus ActivityStatus;
    CIntfData::getAt(ActivityStatus,m_SeqActivityStatus,i);

    ActivityStatus.ActivityStatus = Status;

    // update m_SeqActivityStatus
    CIntfData::setAt(m_SeqActivityStatus,ActivityStatus,i);

    RetValue = true;
  }

  return RetValue;
}


bool CActivityManager::endCurrentActivity(const std::string& Type)
{
  std::string Name = getCurrentActivityName(Type);

  return endActivity(Type, Name);
}

bool  CActivityManager::getActivityStatus(const std::string& Type, const std::string& Name)
{
  bool RetValue = false;

  for ( long i = 0 ; i < CIntfData::getLength(m_SeqActivityStatus) ; ++i )
  {
    sActivityStatus ActivityStatus;
    CIntfData::getAt(ActivityStatus,m_SeqActivityStatus,i);

    if ( std::string(ActivityStatus.ActivityType) == Type )
    {
      if ( std::string(ActivityStatus.ActivityName) == Name )
      {
        RetValue = ActivityStatus.ActivityStatus;
        break;
      }
    }
  }

  return RetValue;
}

std::string CActivityManager::getCurrentActivityName(const std::string& Type)
{
  std::string ActivityName;

  for ( long i = 0 ; i < CIntfData::getLength(m_SeqActivityStatus) ; ++i )
  {
    sActivityStatus ActivityStatus;
    CIntfData::getAt(ActivityStatus,m_SeqActivityStatus,i);

    if ( std::string(ActivityStatus.ActivityType) == Type )
    {
      if ( ActivityStatus.ActivityStatus == true )
      {
        ActivityName = ActivityStatus.ActivityName;
        break;
      }
    }
  }

  return ActivityName;
}

long CActivityManager::getCurrentActivityNo(const std::string& Type)
{
  long ActivityNo = DEF::Inv_Long;

  for ( long i = 0 ; i < CIntfData::getLength(m_SeqActivityStatus) ; ++i )
  {
    sActivityStatus ActivityStatus;
    CIntfData::getAt(ActivityStatus,m_SeqActivityStatus,i);

    if ( std::string(ActivityStatus.ActivityType) == Type )
    {
      if ( ActivityStatus.ActivityStatus == true )
      {
        ActivityNo = ActivityStatus.ActivityNo;
        break;
      }
    }
  }


  return ActivityNo;
}


seqActivityStatus& CActivityManager::getSequence()
{
  return m_SeqActivityStatus;
}


bool CActivityManager::fillSequence(seqActivityStatus& seqData)
{
  m_SeqActivityStatus = seqData;
  return true;
}

std::vector<std::string> CActivityManager::getActivityNames(const std::string& Type)
{
  std::vector<std::string> ActivityNames;

  for ( long i = 0 ; i < CIntfData::getLength(m_SeqActivityStatus) ; ++i )
  {
    sActivityStatus ActivityStatus;
    CIntfData::getAt(ActivityStatus,m_SeqActivityStatus,i);

    if ( std::string(ActivityStatus.ActivityType) == Type )
    {
      ActivityNames.push_back(std::string(ActivityStatus.ActivityName));
    }
  }

  return ActivityNames;
}

bool CActivityManager::isActivityStatus(const std::string& Type, const std::string& Name, bool Status)
{
  bool RetValue = false;

  for ( long i = 0 ; i < CIntfData::getLength(m_SeqActivityStatus) ; ++i )
  {
    sActivityStatus ActivityStatus;
    CIntfData::getAt(ActivityStatus,m_SeqActivityStatus,i);

    if ( std::string(ActivityStatus.ActivityType) == Type )
    {
      if ( std::string(ActivityStatus.ActivityName) == Name )
      {
        if ( ActivityStatus.ActivityStatus == Status )
        {
          RetValue = true;
        }
      }
    }
  }

  return RetValue;
}

bool CActivityManager::isActivityStatus(const std::string& Type, const std::string& Name)
{
  bool RetValue = false;

  for ( long i = 0 ; i < CIntfData::getLength(m_SeqActivityStatus) ; ++i )
  {
    sActivityStatus ActivityStatus;
    CIntfData::getAt(ActivityStatus,m_SeqActivityStatus,i);

    if ( std::string(ActivityStatus.ActivityType) == Type )
    {
      if ( std::string(ActivityStatus.ActivityName) == Name )
      {
        RetValue = true;
      }
    }
  }

  return RetValue;
}


long CActivityManager::getActivityNo(const std::string& Type, const std::string& Name)
{
  long ActivityNo = DEF::Inv_Long;

  for ( long i = 0 ; i < CIntfData::getLength(m_SeqActivityStatus) ; ++i )
  {
    sActivityStatus ActivityStatus;
    CIntfData::getAt(ActivityStatus,m_SeqActivityStatus,i);

    if ( std::string(ActivityStatus.ActivityType) == Type )
    {
      if ( std::string(ActivityStatus.ActivityName) == Name )
      {
        ActivityNo = ActivityStatus.ActivityNo;
        break;
      }
    }
  }


  return ActivityNo;
}
