#if defined(WIN32) || defined(_WIN32) 
#pragma warning(disable:4786)
#pragma warning(disable:4503)
#endif

#include "cCBS_StdFrame.h"
#include "CEventHandler.h"
#include "CEventMessage.h"
#include "cCBS_StdEvent_Task.h"
#include "cCBS_StdInitBase.h"
#include "CSMC_FileLogHandler.h"

#include "cCorbaProxyAdapter.h"
#include "cCorbaTraits.h"
#include "cCorbaPOAAdapter.h"
#include "cCBSClientTask.h"
#include "cTheAppORB.h"
#include "cTheAppPOA.h"
#include "cTheAppTraits.h"
#include "cCBS_CPPException.h"

#include "CIntfData.h"

#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"

#include "cCBS_StdFrame.h"
#include "CProductID.h"

#include "CDateTime.h"
#include "CARCHIVER_HMD_Test_DataProvider.h"
#include "CARCHIVER_HMD_Test_EventHandler.h"

#include "CARCHIVER_HMD_Test_Task.h"


int main( int argc, const char *argv[], char *envp[] )
{
  //-config $(XPACT_SMC)\cfg\ARCHIVER\ARCHIVER_HMD_Test.ini

  int		actualProc = -1;

  try
  {
    // activate SMM Application Environment
    cCBS_StdFrame *pCBS_StdFrame = new cCBS_StdFrame(argc, argv);

    CSMC_FileLogHandler* pSMC_FileLogHandler = new CSMC_FileLogHandler();
    pCBS_StdFrame->registerLogHandler(pSMC_FileLogHandler);

    std::string ServerName;
    ServerName = cCBS_StdInitBase::getInstance()->m_ServerName;
    std::string TaskName = ServerName + "Task";
    cCBS_StdInitBase::getInstance()->replaceWithEntry("TASKS", ServerName, TaskName);

    CARCHIVER_HMD_Test_Task * pARCHIVER_Test_Task = CARCHIVER_HMD_Test_Task::getInstance();
    pCBS_StdFrame->registerTask(TaskName,pARCHIVER_Test_Task);

    // run the application / CORBA
    pCBS_StdFrame->runAsClient();

    CARCHIVER_HMD_Test_DataProvider *m_pTest_DataProvider = 
      new CARCHIVER_HMD_Test_DataProvider(CARCHIVER_HMD_Test_Task::getInstance()->getpConnection());

    pARCHIVER_Test_Task->setDataProvider(m_pTest_DataProvider);

    std::string Message;
    std::string DestinationName = "TSM_HMD_1";
    std::string SenderName = "ARCHIVER_HMD";

    cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage", "SenderName", SenderName);
    cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage", "DestinationName", DestinationName);

    cCBS_StdEvent_Task* pEvent_Task = cCBS_StdEvent_Task::getInstance();

    // To get heatID, use: m_pTest_DataProvider->HeatID 
    CEventMessage Event(SenderName,DestinationName,"UNDEFINED","", "",
      "",false,"","","");

    //////////////////////////////////////////////////////////////////////////////////
    long input = 1;
    long test_treat_id = 0;
    std::stringstream tmp;
    std::string TreatID;
    std::string HeatID;
    std::string ProductID;
    //long TestType;
    do 
    {

      cout << "Input : " << endl;
      cout << "0 for exit" << endl;
      cout << "1 Heat Announce        L2HD03" << endl;
      cout << "2 Heat Cancel          L2HD06" << endl;
      cout << "3 Status Request       L2HD72" << endl;
      cout << "4 Model Result         L2HD07 and L2HD30" << endl;//not used for BHUSHAN L2HD25 
      cout << "5 Mat Avail Request    L2HD71" << endl;
      cout << "---------------------" << endl;
      cout << "" << endl;
      cout << "" << endl;
      cout << "---------------------" << endl;
      cin >> input;
      cout << "Enter HeatID :- ";
      cin >> HeatID;
      cout << "Enter TreatID :- ";
      cin >> TreatID;
      ProductID = HeatID;
      ProductID += "_";
      ProductID += TreatID;
      try
      {
        switch (input)
        {
        case 1:
          {
            Event.setMessage(HMD_EvMsg::evHMDHeatAnnouncement);
            Event.setHeatID(HeatID);
            Event.setTreatID(TreatID);
            tmp.clear();
            Event.setOrderID("7111");
            Event.setPlantID("HMD_1");
            Event.setPlantEvent(false);
            Event.dispatch("DH_HMI_HMD", "Tracking_HMD_1");
            break;
          }
        case 2:
          {
            Event.setMessage(HMD_EvMsg::evHMDHeatCancellation);
            Event.setHeatID(HeatID);
            Event.setTreatID(TreatID);
            tmp.clear();
            Event.setOrderID("7111");
            Event.setPlantID("HMD_1");
            Event.setPlantEvent(false);
            Event.dispatch("DH_HMI_HMD", "Tracking_HMD_1");
            break;
          }
        case 3:
          {
            Event.setMessage(HMD_EvMsg::evHMDPlantStatusRequest);
            Event.setHeatID(HeatID);
            Event.setTreatID(TreatID);
            tmp.clear();
            Event.setOrderID("7111");
            Event.setPlantID("HMD_1");
            Event.setPlantEvent(false);
            Event.dispatch("DH_HMI_HMD", "Tracking_HMD_1");
            break;
          }
        case 4:
          {
            Event.setMessage(HMD_EvMsg::evHMDModelResult);
            Event.setHeatID(HeatID);
            Event.setTreatID(TreatID);
            Event.setProductID(ProductID);
            tmp.clear();
            Event.setOrderID("7111");
            Event.setPlantID("HMD_1");
            Event.setPlantEvent(false);
            //cout << "Please input the Injection type (1 - 5, 1=Mono Lime,2=Mono Carbide,3=Co-lime,4=Co-carbide,5=ECO):" << endl;
            //cin  >> TestType;
            //m_pTest_DataProvider->setHMDModelResult(ProductID, TestType);
            Event.dispatch("HMD_11", "Tracking_HMD_1");
            break;
          }
        case 5:
          {
            Event.setMessage(HMD_EvMsg::evHMDRequestMatAvail);
            Event.setHeatID(HeatID);
            Event.setTreatID(TreatID);
            tmp.clear();
            Event.setOrderID("7111");
            Event.setPlantID("HMD_1");
            Event.setPlantEvent(false);
            Event.dispatch("DH_HMI_HMD", "Tracking_HMD_1");
            break;
          }
        default:
          {
            input = 0;
            break;
          }
        }
      }
      catch(...)
      {
        cout << "exception caught in ARCHIVER_HMD_TEST::Main"  << endl;
      }
      Sleep(2000);
    } while (input != 0);

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

