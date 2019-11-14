// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_EAFTASK_4152969B02AD_INCLUDED
#define _INC_CARCHIVER_EAFTASK_4152969B02AD_INCLUDED

#include "CARCHIVER_Task.h"
#include "cCorbaProxyAdapter.h"
#include "cCBS_StdFrame_Task.h"
#include "CProxyManager.h"


//##ModelId=4152969B02AD
class CARCHIVER_EAFTask : public CARCHIVER_Task
{
public:
  //##ModelId=419B7B310072
  static CARCHIVER_EAFTask* getInstance();

  //##ModelId=4152992901EF
  virtual ~CARCHIVER_EAFTask();

protected:

	//##ModelId=4152992A0113
	CARCHIVER_EAFTask();

	//Virtual initialization method. Creates the task POA 
	//with the policies created by the createPolicies method 
	//and activates the task servant on this POA. Called by 
	//the activate method. Returns true on success.
	//##ModelId=419A1E7C001D
	virtual bool initialize();

private:
	//##ModelId=419A2FC10223
	static CARCHIVER_EAFTask* m_Instance;

};

#endif /* _INC_CARCHIVER_EAFTASK_4152969B02AD_INCLUDED */
