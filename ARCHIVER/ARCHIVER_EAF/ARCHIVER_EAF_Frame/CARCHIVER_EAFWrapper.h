// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_EAFWRAPPER_41A3606E009E_INCLUDED
#define _INC_CARCHIVER_EAFWRAPPER_41A3606E009E_INCLUDED

#include "CARCHIVER_Wrapper.h"

class CARCHIVER_EAFTask;



//##ModelId=41AC45FD01B5
class CARCHIVER_EAFWrapper : public CARCHIVER_Wrapper
{
public:

  //##ModelId=41AC494600FD
  CARCHIVER_EAFWrapper();

  //##ModelId=41AC49460252
  virtual ~CARCHIVER_EAFWrapper();



protected:

  //##ModelId=42B006340328
  virtual void deleteDBClasses();

  //##ModelId=42AFFF8A03CA
  virtual void initDBClasses();

};

#endif /* _INC_CARCHIVER_EAFWRAPPER_41A3606E009E_INCLUDED */

