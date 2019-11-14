#pragma warning(disable:4183 4786 4503 4018 )    // get rid of some warnings
#pragma warning(disable:4290)    // get rid of some warnings

#include <sstream>
#include "cCBS_StdInitBase.h"
#include "cCBS_ConfigBase.h"

#include "CCBS_StdFrame.h"

#include "cIBAS_InterfaceTask.h"
#include "CSMC_FileLogHandler.h"
#include "CSMC_AsyncFileLogHandler.h"

extern const char *CBS_PROJECT_NAME;

// -config $(X-Pact)\cfg\Tools\IBas_Server.ini

int main( int argc, const char *argv[], char *envp[] )
{
  CBS_PROJECT_NAME  = "JSW-SMS-3";
  try
  {
    cCBS_StdFrame *pApplication_Frame = new cCBS_StdFrame(argc, argv);

    // registering logFile handler
    bool AsyncLog = true;

    cCBS_StdInitBase::getInstance()->replaceWithEntry("LOG", "AsyncLog", AsyncLog);

    if (AsyncLog)
    {
      CSMC_AsyncFileLogHandler* pSMC_FileLogHandler = new CSMC_AsyncFileLogHandler();
      pApplication_Frame->registerLogHandler(pSMC_FileLogHandler);
    }
    else
    {
      CSMC_FileLogHandler* pSMC_FileLogHandler = new CSMC_FileLogHandler();
      pApplication_Frame->registerLogHandler(pSMC_FileLogHandler);
    }

    std::string ComponentName = std::string(pApplication_Frame->getComponentName());

    cIBAS_InterfaceTask *p_iBAS_InterfaceTask = cIBAS_InterfaceTask::getInstance();
    pApplication_Frame->registerTask("InterfaceTask", p_iBAS_InterfaceTask);


    // run the application / CORBA
    pApplication_Frame->runAsServer ();  // This is supposed to run "forever"
  }
  
  catch(const CORBA::Exception& e)  
  {
    cout << e << endl;
  } 
	catch( const cCBS_Exception& e ) 
  { 
		cout << e << endl;
	}

  catch (...)                          // Catch 'them all
  {
   cout << "exception caught "  << endl;
  }
	return (0);

}  // main() 