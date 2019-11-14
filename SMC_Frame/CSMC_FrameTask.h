// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMC_FRAME_TASK_4549B0B6031A_INCLUDED
#define _INC_CSMC_FRAME_TASK_4549B0B6031A_INCLUDED

#include "cCBS_StdFrame_Task.h"

class cCBS_StdConnection;


class CSMC_FrameTask 
: public cCBS_StdFrame_Task
{
public:

	static std::string EVENT;

	static std::string PLANT;

	static std::string PRODUCT;

	virtual ~CSMC_FrameTask();

	cCBS_StdConnection* getStdConnection();

	virtual void handleDBConnectionError();

  void log(const std::string& Message, long Level);

  virtual bool checkDBConnection();

protected:
	//Virtual initialization method. Creates the task POA 
	//with the policies created by the createPolicies method 
	//and activates the task servant on this POA. Called by 
	//the activate method. Returns true on success.
	virtual bool initialize();

	CSMC_FrameTask();

	virtual bool setDBConnectionParameter();

  std::string m_DBName;
  std::string m_DBUser;
  std::string m_DBPassword;

private:

};

#endif /* _INC_CSMC_FRAME_TASK_4549B0B6031A_INCLUDED */
