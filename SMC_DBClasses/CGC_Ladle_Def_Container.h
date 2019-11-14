// Copyright (C) 2004 SMS Demag AG, Germany 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGC_Charge_Dest_Container_424136530236_INCLUDED
#define _INC_CGC_Charge_Dest_Container_424136530236_INCLUDED

#include <string>
#include "cCBS_Connection.h"
#include "cCBS_StdConnection.h"

class CGC_Ladle_Def_Container 
{
private:
  std::multimap< long, std::string > m_LadleDefList;

public:
	CGC_Ladle_Def_Container(cCBS_StdConnection * Connection);

  bool isValidLadle(long LadleNo, const std::string& LadleType);

	virtual ~CGC_Ladle_Def_Container();

};

#endif /* _INC_CGC_Charge_Dest_Container_424136530236_INCLUDED */
