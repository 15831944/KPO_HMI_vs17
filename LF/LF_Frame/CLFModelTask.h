// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLF_MODEL_TASK_4110E43C02F8_INCLUDED
#define _INC_CLF_MODEL_TASK_4110E43C02F8_INCLUDED

//#include "cCorbaProxyAdapter.h"
#include "cCBS_CorbaProxy.h"//ffra01112018
#include "CSMM_ModelTask.h"
#include "cCBS_StdDB_Task.h"
#include "cCBS_DBExc.h"
#include "cCBS_DBExcODBC.h"

#include "CDateTime.h"
#include "iDM_Interface_s.hh"
#include "CProxyManager.h"

class CEventMessage;

class CLFModelResultWrapper;
class CLFModelTestResultWrapper;
class CIntfAdapt;
class CIntfMatMgr;
class CIntfParamMgr;
class CIntfPurposeMgr;
class CIntfLF;
class CCfgLF;

//##ModelId=41504CE80016
class CLFModelTask 
: public CSMM_ModelTask
{
private:

	//##ModelId=462767AD0396
  CLFModelResultWrapper* m_pLFModelResultWrapper;
  CLFModelTestResultWrapper* m_pLFModelTestResultWrapper;

	//##ModelId=4174D10D02DD
	static CLFModelTask* Instance;

public:

	//##ModelId=462767AD03B3
  virtual bool callModelResultWrapper(const std::string& Type ,CEventMessage& Event);

	//##ModelId=462767AD03E5
  virtual CIntf* getpModelInterface(const std::string& Type);

	//##ModelId=42A94B5002AB
	void setActLadleTransferCarID(std::string& value);

	//##ModelId=41513C6C027C
	virtual ~CLFModelTask();

	//##ModelId=4174D48B0224
	static CLFModelTask* getInstance();

  double AimSteelWeight;

protected:
	//##ModelId=41513C6C02B8
	CLFModelTask();

	//##ModelId=41513C6C0327
	CIntfAdapt* m_pIntfAdaptMatMgr;

	//##ModelId=41513C6C0363
	CIntfAdapt* m_pIntfAdaptParamMgr;

	//##ModelId=41513C6C03A8
	CIntfAdapt* m_pIntfAdaptPurposeMgr;

	//##ModelId=41513C6C03DB
	CIntfMatMgr* m_pIntfMatMgr;

	//##ModelId=41513C6D0025
	CIntfParamMgr* m_pIntfParamMgr;

	//##ModelId=41513C6D0061
	CIntfPurposeMgr* m_pIntfPurposeMgr;

	//##ModelId=41513C6D0115
	CIntfLF* m_pIntfLF;

	//##ModelId=4174EC520128
	CCfgLF* m_pCfgLF;


	//Virtual initialization method. Creates the task POA 
	//with the policies created by the createPolicies method 
	//and activates the task servant on this POA. Called by 
	//the activate method. Returns true on success.
	//##ModelId=41513C6D01B5
	virtual bool initialize();

};

#endif /* _INC_CLF_MODEL_TASK_4110E43C02F8_INCLUDED */
