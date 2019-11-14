// Copyright (C) 2007 SMS Demag AG, Germany 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHEAT_STATUS_CONTAINER_INCLUDED
#define _INC_CHEAT_STATUS_CONTAINER_INCLUDED

class cCBS_StdConnection;

#include <map>

// container class to provide heat status numbers
// depended on plant and status id
//##ModelId=467942700346
class CHeatStatusContainer 
{
public:
	//##ModelId=467942AE0234
	virtual ~CHeatStatusContainer();

	//Return heat staus order for plant and status id
	//##ModelId=4679433101CE
	long getHeatStatus(const std::string& PLANT, std::string HEATSTATUS);

	//##ModelId=4679433101D9
	CHeatStatusContainer(cCBS_StdConnection* Connection);

private:
	//##ModelId=4679433102B5
  struct HeatStat{
		//##ModelId=4679433102DE
    std::string HeatStatus;
		//##ModelId=4679433102F1
    long HeatStatusNo;
  };

  //Container that contains plant as first value and 
	//struct of status id with status order number
	//##ModelId=46794331028E
	std::multimap<const std::string,HeatStat> m_StatusTable;

};

#endif /* _INC_CHEAT_STATUS_CONTAINER_INCLUDED */
