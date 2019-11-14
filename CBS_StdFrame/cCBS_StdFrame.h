// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMC_APPLICATION_4045EC3C03AB_INCLUDED
#define _INC_CSMC_APPLICATION_4045EC3C03AB_INCLUDED

#include "cCBS_StdFrame_Server.h"

//Central class providing all cCBS_StdFrame functionalities. 
//This class must be instantiated in an application.
//##ModelId=40EAA0930100
class cCBS_StdFrame : public cCBS_StdFrame_Server
  
{
public:
  //##ModelId=40EAA0930105
  cCBS_StdFrame(int argc, const char* argv[]);

  //##ModelId=40EAA093010B
  virtual ~cCBS_StdFrame();

};

#endif /* _INC_CSMC_APPLICATION_4045EC3C03AB_INCLUDED */
