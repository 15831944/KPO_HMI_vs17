// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CCBS_STDCONNECTION_411746DA00C5_INCLUDED
#define _INC_CCBS_STDCONNECTION_411746DA00C5_INCLUDED

#include <vector>
#include <map>


#include "cCBS_Connection.h"
//##ModelId=411746DA00C5
#include "cCBS_DriverManager.h"

class cCBS_ODBCDriver;

//Class representing cCBS_Connection classes
//##ModelId=411746DA00C5
class cCBS_StdConnection 
  
{
protected:
	//##ModelId=411895FC0322
	void log(const std::string & Message, long Level);

	//##ModelId=4117722C0115
	cCBS_Connection* m_pCBSConnection;

public:
	//##ModelId=411892B50024
	virtual ~cCBS_StdConnection();

	//##ModelId=411771EC027E
	cCBS_Connection* getpCBSConnection();

  bool establishNewConnection();

  void revokeConnection();

  bool reconnect();

	//##ModelId=41177009007C
	cCBS_StdConnection(cCBS_DriverManager * DriverManager,  cCBS_ODBCDriver  *Driver, const std::string  &Url, const std::string  &Login, const std::string &Password);

	//##ModelId=4117630B002C
  std::string& getLogin();

	//##ModelId=411763170069
	std::string& getUrl();

	//##ModelId=4117631D03D9
	std::string& getPassword();

  void rollback();

  void commit();


private:
	//##ModelId=43958A9C02EB
	cCBS_ODBCDriver* m_pODBCDriver;

	//##ModelId=411892070291
	cCBS_DriverManager* m_pDriverManager;

	//##ModelId=411747AF01C3
	std::string  m_Url;

	//##ModelId=411747B6037C
	std::string  m_Login;

	//##ModelId=411747C30209
	std::string  m_Password;

};

#endif /* _INC_CCBS_STDCONNECTION_411746DA00C5_INCLUDED */
