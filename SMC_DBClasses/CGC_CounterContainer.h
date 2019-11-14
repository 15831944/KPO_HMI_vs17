// Copyright (C) 2005 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGC_COUNTERCONTAINER_INCLUDED
#define _INC_CGC_COUNTERCONTAINER_INCLUDED

#include <string>

#include "CSMC_DBData.h"

class CGC_CounterContainer: public CSMC_DBData
{
public:

  CGC_CounterContainer(cCBS_StdConnection* Connection);

   ~CGC_CounterContainer();

  //get sample counter using sequence
  long GetSampleCounter();

  long GetSampleRefCounter();

  //get Pretreat counter using sequence
  long GetPretreatCounter();

};

#endif //_INC_CGC_COUNTERCONTAINER_INCLUDED