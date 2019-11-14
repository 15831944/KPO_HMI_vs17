// Copyright (C) 2009 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_DELAYWRAPPER_462DD2EB0212_INCLUDED
#define _INC_CARCHIVER_DELAYWRAPPER_462DD2EB0212_INCLUDED

#include "CARCHIVER_Wrapper.h"


class CARCHIVER_DelayWrapper 
: public CARCHIVER_Wrapper
{
protected:
  virtual void initDBClasses();

  virtual void deleteDBClasses();


public:
  CARCHIVER_DelayWrapper();

  virtual ~CARCHIVER_DelayWrapper();

};

#endif /* _INC_CARCHIVER_DELAYWRAPPER_462DD2EB0212_INCLUDED */
