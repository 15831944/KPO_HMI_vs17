// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMM_MODEL_TASK_4549B0B6031A_INCLUDED
#define _INC_CSMM_MODEL_TASK_4549B0B6031A_INCLUDED

#include <string>

#include "CModelTask.h"

class CIntf;

class CSMM_ModelTask 
: public CModelTask
{
public:

  virtual CIntf* getpModelInterface(const std::string& Type) = 0;

	virtual ~CSMM_ModelTask();

protected:

	CSMM_ModelTask();

private:

};

#endif /* _INC_CSMM_MODEL_TASK_4549B0B6031A_INCLUDED */
