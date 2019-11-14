// Copyright (C) 2004 SMS Demag AG, Germany 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGC_Ladle_Pos_Container_424136530236_INCLUDED
#define _INC_CGC_Ladle_Pos_Container_424136530236_INCLUDED

#include <string>
#include "cCBS_Connection.h"
#include "cCBS_StdConnection.h"

class CGC_Ladle_Pos_Container 
{
private:

  typedef struct LadlePosData
  {
    long LadlePosId;
    std::string LadlePos;
    std::string LadlePosDesc;
    std::string LadleType;
  };

  std::map<std::string, LadlePosData> m_LadlePosDataList;

public:
	CGC_Ladle_Pos_Container(cCBS_StdConnection * Connection);

  long getLadlePosId(const std::string& LadlePos, const std::string& LadleType);

  long getLadlePosIdDefault(const std::string& LadleType);

	virtual ~CGC_Ladle_Pos_Container();

};

#endif /* _INC_CGC_Ladle_Pos_Container_424136530236_INCLUDED */
