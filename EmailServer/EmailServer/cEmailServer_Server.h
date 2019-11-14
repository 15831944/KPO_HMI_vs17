#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEMAILSERVER_SERVER_41127C30015C_INCLUDED
#define _INC_CEMAILSERVER_41127C30015C_INCLUDED

#include <CBS_General.h>
#include <CBS_Tasks.h>
#include <CBS_StdAPI.h>

class cEmailServer_Comp;

class cEmailServer_Server 
  : public cCBS_StdServer
{
public:
  
  cEmailServer_Comp* m_pComponent;

  virtual ~cEmailServer_Server();

  cEmailServer_Server(int argc, const char* argv[]);

  //Abstract method. Should create the tasks that are part 
  //of this server.
  virtual void createTasks();

private:


};

#endif /* _INC_CEMAILSERVER_SERVER_41127C30015C_INCLUDED */
