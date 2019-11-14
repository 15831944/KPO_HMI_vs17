// Copyright (C) 2007 SMS Demag AG, Germany 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGC_STATUS_CONTAINER_INCLUDED
#define _INC_CGC_STATUS_CONTAINER_INCLUDED


// container class to provide status numbers
// depended on plant and status name
class CGC_StatusContainer 
{
public:
	virtual ~CGC_StatusContainer();

	//Return staus order for plant and status id
	long getStatusNo(const std::string& PLANT, std::string STATUSNAME);

  bool isStatusOfPlant(const std::string& PLANT, long STATUSNO);

  CGC_StatusContainer(cCBS_Connection* Connection);

	CGC_StatusContainer(cCBS_StdConnection* Connection);

private:
  struct StatusDef{
    long StatusNo;
    std::string StatusName;
    std::string StatusDescr;
  };

  //Container contains plant as first value and 
	//struct of status id with status number
	std::multimap<const std::string, StatusDef> m_StatusTable;

};

#endif /* _INC_CGC_STATUS_CONTAINER_INCLUDED */
