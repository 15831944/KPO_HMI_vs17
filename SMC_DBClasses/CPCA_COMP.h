// Copyright (C) 2009 SMS Siemag  AG, Germany

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CPCA_COMP_INCLUDED
#define _INC_CPCA_COMP_INCLUDED

#include "CSMC_DBData.h"

class CPCA_COMP
: public CSMC_DBData
{

public:

  CPCA_COMP(cCBS_StdConnection* Connection);

  ~CPCA_COMP();

  std::string getCOMPCODE(long Row);

  void setCOMPCODE(const std::string& value);

  std::string getCOMPDESCR(long Row);

  void setCOMPDESCR(const std::string& value);

  bool select(const std::string& COMPCODE);

};

#endif /* _INC_CPCA_COMP_INCLUDED */
