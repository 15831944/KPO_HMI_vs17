#pragma warning(disable:4183 4786 4503 4018 4290)    // get rid of some warnings

#include "cCBS_StdFrame.h"


#include "CTelcom_OutTask.h"
#include "CTelcom_QueueMonitoringTask.h"
#include "CSMC_FileLogHandler.h"
#include "CSMC_AsyncFileLogHandler.h"

// -config $(X-Pact)\cfg\TELCOM\TELCOM_L1_AOD_1_OUT.ini
// -config $(X-Pact)\cfg\TELCOM\TELCOM_L1_LF_1_OUT.ini
// -config $(X-Pact)\cfg\TELCOM\TELCOM_L1_CONARC_1_OUT.ini
// -config $(X-Pact)\cfg\TELCOM\TELCOM_L1_RH_1_OUT.ini
// -config $(X-Pact)\cfg\TELCOM\TELCOM_L1_HMD_1_OUT.ini
// -config $(X-Pact)\cfg\TELCOM\TELCOM_L1_VD_1_OUT.ini
// -config $(X-Pact)\cfg\TELCOM\TELCOM_L1_EAF_1_OUT.ini
// -config $(X-Pact)\cfg\TELCOM\TELCOM_L1_HMI_EAF_1_OUT.ini

int main(int argc, const char *argv[])
{
  try 
  {
    // activate SMM Application Environment (WHAT THE F**K MEANS SMM ? )
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

    // Our Homegrown Tasks - the Telcom Application runs as a task
    CTelcom_OutTask  *comTask  = CTelcom_OutTask::getInstance();
    CTelcom_QueueMonitoringTask *monTask = CTelcom_QueueMonitoringTask::getInstance();

    // Implant our Tasks into the Application Frame
    pApplication_Frame->registerTask("CommunicationTask", comTask); 
    pApplication_Frame->registerTask("QueueMonitoringTask", monTask); 


    // run the application / CORBA
    pApplication_Frame->runAsServer ();  // This is supposed to run "forever"
  }
	catch( const cCBS_Exception& e ) 
  { 
		// need to catch all kinds of cCBS_Exceptions that might be thrown by cCBS_StdServer ( cDScIfcCbsServer )
    // ( all of them are regarded fatal )
  	std::cout << e << std::endl;
	  exit (EXIT_FAILURE);
	}
  catch(const CORBA::Exception& e)  
  {
    // just in case ... ( most CORBA::Exceptions should be handled inside the server and only cCBS_Exceptions should
    // be thrown, but ... )
    std::cout << e._name() << std::endl;
    exit (EXIT_FAILURE);  
  } 
  catch (...)                          // Catch 'them all
  {
    std::cout << "\n\nundocumented exception :-(" << std::endl;  
    exit (EXIT_FAILURE);
  }
  _exit(0);
  return (0);   // just to keep compiler happy
}  // main()