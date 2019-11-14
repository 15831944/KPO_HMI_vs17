// Copyright (C) 2009 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CMODEL_EVENTHANDLER_4549B0F602FE_INCLUDED
#define _INC_CMODEL_EVENTHANDLER_4549B0F602FE_INCLUDED

#include "CEventHandler.h"

class CEventMessage;

class CModelTask;

class CModelEventHandler 
: public CEventHandler
{
protected:
  CModelEventHandler(CModelTask* pModelTask);

  void cleanProductData();

  void setActEventMessage(const std::string& ActEventMessage);

  std::string getActEventMessage() const;

private:

	CModelTask* m_pModelTask;

  static std::string m_ActEventMessage;

public:

  bool isAssignedProductID(const std::string& ProductID);

  bool checkAnnouncement( CEventMessage & EventMessage, bool OfflineCalculationStatus);

  void setOfflineCalculationStatus(bool value);

  virtual ~CModelEventHandler();

  bool checkProductAcceptance(CEventMessage& Event);

  virtual bool handleEvent(const FRIESEvent& Event);

  virtual bool handleEvent(CEventMessage& EventMessage) = 0;

};

#endif /* _INC_CMODEL_EVENTHANDLER_4549B0F602FE_INCLUDED */
