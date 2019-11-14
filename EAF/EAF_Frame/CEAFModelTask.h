// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAF_MODEL_TASK_4110E43C02F8_INCLUDED
#define _INC_CEAF_MODEL_TASK_4110E43C02F8_INCLUDED


#include "cCorbaProxyAdapter.h"
#include "cCBS_StdDB_Task.h"
#include "cCBS_DBExc.h"
#include "cCBS_DBExcODBC.h"

#include "CDateTime.h"
#include "iDM_Interface_s.hh"
#include "CProxyManager.h"

#include "CSMM_ModelTask.h"

class CEAFModelWrapper;
class CEAFModelResultWrapper;
class CEAFModelResults_Impl;
class CIntfAdapt;
class CIntfMatMgr;
class CIntfParamMgr;
class CIntfPurposeMgr;
class CIntfEAF;
class CCfgEAF;
class CParamMgr;

class CEventMessage;

//##ModelId=4146B9F103CD
class CEAFModelTask 
: public CSMM_ModelTask
{

public:

	//##ModelId=4146BA480147
	static CEAFModelTask* getInstance();

	//##ModelId=4146BA480179
	virtual ~CEAFModelTask();

	//##ModelId=467647CB0394
  virtual bool callModelResultWrapper(const std::string& Type ,CEventMessage& Event);

  virtual bool callModelResultWrapper(const std::string& Type ,CEventMessage& Event, CEAFModelWrapper& CallMeBack);

	//##ModelId=467647CB03C6
  virtual CIntf* getpModelInterface(const std::string& Type);

  //##ModelId=4146BA48015B
	CIntfEAF* getpIntfEAF();

  // should be const and return a const pointer, but parameter mgr lacks const. get-operations
	CParamMgr* getpParamMgr();

	const CCfgEAF* getpCfgEAF() const;

  CCfgEAF* getUnConstpCfgEAF();

protected:
	//##ModelId=4146BA480183
	CEAFModelTask();

	//##ModelId=4146BA4801CA
	CIntfAdapt* m_pIntfAdaptMatMgr;

	//##ModelId=4146BA4801DF
	CIntfAdapt* m_pIntfAdaptParamMgr;

	//##ModelId=4146BA4801E9
	CIntfAdapt* m_pIntfAdaptPurposeMgr;

	//##ModelId=4146BA4801FD
	CIntfMatMgr* m_pIntfMatMgr;

	//##ModelId=4146BA480211
	CIntfParamMgr* m_pIntfParamMgr;

	//##ModelId=4146BA480224
	CIntfPurposeMgr* m_pIntfPurposeMgr;

	//##ModelId=4146BA480243
	CCfgEAF* m_pCfgEAF;

	//##ModelId=4146BA480274
	CIntfEAF* m_pIntfEAF;

	//Virtual initialization method. Creates the task POA 
	//with the policies created by the createPolicies method 
	//and activates the task servant on this POA. Called by 
	//the activate method. Returns true on success.
	//##ModelId=4146BA4802B0
	virtual bool initialize();

private:
	//##ModelId=4178AB4E03DE
	static CEAFModelTask* Instance;

	//##ModelId=467647CB0381
  CEAFModelResultWrapper* m_pEAFModelResultWrapper;

};

#endif /* _INC_CEAF_MODEL_TASK_4110E43C02F8_INCLUDED */
