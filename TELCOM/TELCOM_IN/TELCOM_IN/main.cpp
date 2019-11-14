#pragma warning(disable:4183 4786 4503 4018 4290)    // get rid of some warnings
#include "cCBS_ConfigBase.h"
#include <sstream>

#include "CCBS_StdFrame.h"

#include "CSMC_AsyncFileLogHandler.h"
#include "CSMC_FileLogHandler.h"

// STRICTLY, THIS IS ONLY REQUIRED FOR Telcom-Database type applications
// #include "basorasession.h"
#include "CTelcom_InTask.h"

#include "cIBAS_InterfaceTask.h"

// -config $(X-Pact)\cfg\TELCOM\TELCOM_L1_CONARC_1_IN.ini
// -config $(X-Pact)\cfg\TELCOM\TELCOM_L1_LF_1_IN.ini
// -config $(X-Pact)\cfg\TELCOM\TELCOM_L1_EAF_1_IN.ini
// -config $(X-Pact)\cfg\TELCOM\TELCOM_L1_VD_1_IN.ini

int main( int argc, const char *argv[], char *envp[] )
{
  try
  {
    // STRICTLY, THIS IS ONLY REQUIRED FOR Telcom-Database type applications
    //bas::OraSession::InitOraMultiThreading();

    // activate Application Environment 
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

    // Our Homegrown Task - the Telcom Application runs as a task
    CTelcom_InTask  *trct = CTelcom_InTask::getInstance();

    // Implant our Task into the Application Frame
    pApplication_Frame->registerTask("ReceiverTask", trct);

  /*  bool isBasServerActive = false;
    cCBS_StdInitBase::getInstance()->getEntry("IBAS","isActive", isBasServerActive);

    if ( isBasServerActive )
    {
      std::string ComponentName = std::string(pApplication_Frame->getComponentName());

      cIBAS_InterfaceTask *p_iBAS_InterfaceTask = cIBAS_InterfaceTask::getInstance();
      pApplication_Frame->registerTask("InterfaceTask", p_iBAS_InterfaceTask);
    }*/ //ffra31102018

    // run the application / CORBA
    pApplication_Frame->runAsServer ();  // This is supposed to run "forever"
  }
  catch(const cCBS_Exception &e)
  {
  	std::cout    << e << std::endl;
	  exit (EXIT_FAILURE);
  }
  catch(const CORBA::Exception& e)  
  {
    // just in case ... 
    //( most CORBA::Exceptions should be handled inside 
    // the server and only cCBS_Exceptions should be thrown, but ... )
    std::cout    << e._name() << std::endl;
    exit (EXIT_FAILURE);  
  } 
  catch(...)  // catch 'em all
  {
    std::cout    << "\n\nundocumented exception :-(" << std::endl;  
    exit (EXIT_FAILURE);
  }
  _exit(0);
  return 0;     // just to keep compiler happy
}
