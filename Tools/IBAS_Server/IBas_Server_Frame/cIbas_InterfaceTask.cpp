#include "cIbas_InterfaceTask.h"
#define _CLOG9
#include "CBS_Utilities\CBS_Clog.h"

#include "cStorage.h"
#include "cBASIntrf_Impl.h"
#include "cCBS_CorbaApplServer.h"

cIBAS_InterfaceTask* cIBAS_InterfaceTask::m_Instance = 0;

cIBAS_InterfaceTask::cIBAS_InterfaceTask() 
{
}

cIBAS_InterfaceTask::~cIBAS_InterfaceTask() 
{
}

cIBAS_InterfaceTask* cIBAS_InterfaceTask::getInstance()
{
  if (! m_Instance)
  {
  	m_Instance = new cIBAS_InterfaceTask();
  }
  return m_Instance;
}

void cIBAS_InterfaceTask::ownStartUp()
{
  try
  {
    cCBS_StdFrame_Task::ownStartUp();
    PortableServer::POA_var rootPOA = CBS::getRootPOA();
    // Create New Object:
    // m_BASIntrf_Servant = new cBASIntrf_Impl();  

    rootPOA->activate_object(&m_BASIntrf_Servant);

    //Obtain a refence to object
    CORBA::Object_var obj = m_BASIntrf_Servant.POA_IBAS::IBASIntrf::_this();

    const char * ProjectName = CBS::getProjectName();
    //Register object with naming service
    CBS::bindObjectToName(obj, CBS::getProjectName(), "iBAS_SERVER_FRAME");

    //m_pCorbaServer->activateAllPOAs();
    setWorking(true);
  }
  catch (cCBS_App_ExcPOAundetermined &e)
  {
    CLOG1( << "Exception:" << e << std::endl);
  }
  catch (cCBS_App_ExcPOANotExist &e)
  {
    CLOG1( << "Exception:" << e << std::endl);
  }
}

void cIBAS_InterfaceTask::ownRunDown()
{
  cCBS_StdFrame_Task::ownRunDown();

  setWorking(false);

}
void cIBAS_InterfaceTask::getOwnStateDetails(CORBA::String_out details)
{
  // check whether our thread is running and post according message 
  if (CBS_Working == getOwnWorkState())
  {
    details = CORBA::string_dup("Task is Running\n");      
  }
  else
  {
    details = CORBA::string_dup("Task is not Running\n");
  }
}

void cIBAS_InterfaceTask::createSubtasks(void)
{
}
