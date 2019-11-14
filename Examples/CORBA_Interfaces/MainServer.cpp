#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include "CCORBA_Interfaces_Impl.h"

#include "cCBS_StdEvent_Task.h"
#include "cCBS_StdCORBA_Task.h"

#include "cCorbaProxyAdapter.h"
#include "cCorbaTraits.h"
#include "cCorbaPOAAdapter.h"
#include "cCBSClientTask.h"
#include "cTheAppORB.h"
#include "cTheAppPOA.h"
#include "cTheAppTraits.h"
#include "cCBS_CPPException.h"

#include "CIntfData.h"
#include "cCBS_StdInitBase.h"

#include "cCBS_StdFrame.h"

// use command line argument: -config $(X-Pact)\source\Examples\CORBA_Interfaces\CORBA_Interfaces_Server.ini


int main( int argc, const char *argv[], char *envp[] )
{

  try
  {
    // activate SMM Application Environment
    cCBS_StdFrame *pCBS_StdFrame = new cCBS_StdFrame(argc, argv);

    cCBS_StdCORBA_Task* pCORBA_Task = cCBS_StdCORBA_Task::getInstance();

    if (pCORBA_Task)
    {

      CCORBA_Interfaces_Impl *pCORBA_Interfaces_Impl = new CCORBA_Interfaces_Impl();

      std::string ServantName    = "CORBA_InterfaceName";

      pCORBA_Task->registerServant(pCORBA_Interfaces_Impl,ServantName);

    }


    // run the application / CORBA
    pCBS_StdFrame->runAsServer();



  }
  catch(cCBS_Exception Exc)
  {
    cout << Exc << endl;
  }

  catch(...)
  {
    cout << "exception caught "  << endl;
  }

  return 0;
}

