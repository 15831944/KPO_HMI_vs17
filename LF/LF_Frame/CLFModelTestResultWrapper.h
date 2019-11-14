// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLFModelTestResultWrapper_4118CC3401F4_INCLUDED
#define _INC_CLFModelTestResultWrapper_4118CC3401F4_INCLUDED

#include "CLFModelWrapper.h"
#include "CEventMessage.h"

class CLFModelTestResultWrapper : public CLFModelWrapper
  
{
public:

	virtual ~CLFModelTestResultWrapper();

	CLFModelTestResultWrapper();

  virtual bool doModelResult(CEventMessage& Event);

};

#endif /* _INC_CLFModelTestResultWrapper_4118CC3401F4_INCLUDED */
