#pragma warning (disable: 4311 4312 4267)
#include "cbs_tasks.h"
#include "CBS_Utilities\cCBS_ConfigBase.h"
#include "cCBS_StdFrame_Task.h"
#pragma warning (default: 4311 4312 4267)

#include "cBASIntrf_Impl.h"

//Class providing CBS-CORBA functionality.
class cIBAS_InterfaceTask : public cCBS_StdFrame_Task
{
private:
  cIBAS_InterfaceTask();
  virtual ~cIBAS_InterfaceTask();

public:
  static cIBAS_InterfaceTask* getInstance();

protected:
  cBASIntrf_Impl m_BASIntrf_Servant;  
  virtual void ownStartUp();
  virtual void ownRunDown();
	virtual void getOwnStateDetails(CORBA::String_out details);
  virtual void createSubtasks(void);

private:
	static cIBAS_InterfaceTask* m_Instance;
};