// ----------------------------------------------------------------------------
// 
//                            S M S  D e m a g  A G
// 
//                             All Rights Reserved
// 
// 
//  project       : StraGang
//  filename      : 
//  originator    : 
//  department    : 
//  creation date : 03.03.2005 10:49
//  description   : Component for IBAS
// 
// ----------------------------------------------------------------------------
// 
//  change notes:
// 
//  version  dd-mmm-yyyy 	author  	remarks
//  0.1      03.03.2005 10:49 	Uli Bellgardt   First Version
// 
// ----------------------------------------------------------------------------
// 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CIBAS_COMPONENT
#define _INC_CIBAS_COMPONENT


#pragma warning (disable: 4311 4312 4267)
#include "CBS_StdAPI/cCBS_StdComponent.h"
#pragma warning (default: 4311 4312 4267)

class cIBAS_EventHdlTask;
class cIBAS_InterfaceTask;
class cIBAS_Server;
class cCBS_StdEventSenderTask;
class cIBAS_GetStatusTask;
class cIBAS_GetDCSValuesTask;
class cIBAS_getSpeedValuesTask;
class cIBAS_GetCLOResultTask;
class cIBAS_GetMSTDataTask;

class cIBAS_Component : 
public cCBS_StdComponent  
  
{
public:

	virtual void createSubtasks();

	virtual void afterSubtaskEnd();

	virtual void afterSubtaskStart();

	cIBAS_Component(cIBAS_Server *);

	~cIBAS_Component();

	void restore(const CBS_LocalTime& _timeOccured, const CBS_OctetSequence& _data);

protected:
  cIBAS_InterfaceTask     *m_pcIBAS_InterfaceTask;
  cIBAS_Server            *m_pcIBAS_Server;

  virtual void ownStartUp(void);
  virtual void ownShutDown(void);
};

#endif 
