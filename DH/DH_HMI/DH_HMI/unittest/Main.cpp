
// use config file e.g.: -config $(XPACT_SMC)\CFG\DH\DH_HMI_AOD_Test.ini
// use config file e.g.: -config $(XPACT_SMC)\CFG\DH\DH_HMI_BOF_Test.ini
// use config file e.g.: -config $(XPACT_SMC)\CFG\DH\DH_HMI_ConArc_Test.ini
// use config file e.g.: -config $(XPACT_SMC)\CFG\DH\DH_HMI_EAF_Test.ini
// use config file e.g.: -config $(XPACT_SMC)\CFG\DH\DH_HMI_LF_Test.ini

#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include "iEventMessages_s.hh"
#include "CEventMessage.h"
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
#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"
#include "CProductID.h"
#include "cCBS_StdFrame.h"

#include "iDH_Interface_s.hh"

#include "CDateTime.h"


int main( int argc, const char *argv[], char *envp[] )
{

  try
  {

    std::string SenderName      = "DH_HMI_Test";
    std::vector<std::string>  DestinationList;
    
    // activate SMM Application Environment
    cCBS_StdFrame *pCBS_StdFrame = new cCBS_StdFrame(argc, argv);

    // run the application / CORBA
    pCBS_StdFrame->runAsClient();


    cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage", "DestinationName", DestinationList);
    cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage", "SenderName", SenderName);

    cCorbaProxyAdapter<DH::iDH_Interface>* newProxyInterface;
    newProxyInterface = new cCorbaProxyAdapter<DH::iDH_Interface>();

    DH::iDH_Interface_var DH_HMI_LFInterface;

    string ServerTask     = "DH_HMI_LF";
    string ServerTaskPOA  = "DH_HMI_LFPOA";

    cCBS_StdInitBase::getInstance()->replaceWithEntry("DH", "ServerTask", ServerTask);
    cCBS_StdInitBase::getInstance()->replaceWithEntry("DH", "ServerTaskPOA", ServerTaskPOA);

    cCBS_StdEvent_Task* pEvent_Task = cCBS_StdEvent_Task::getInstance();

    cCBS_StdCORBA_Task* pCORBA_Task = cCBS_StdCORBA_Task::getInstance();

    if (pCORBA_Task)
    {
      //***************************************************************************
      string InterfaceServantName    = "DH_HMI_LFInterface";

      cCBS_StdInitBase::getInstance()->replaceWithEntry("DH", "ServantName", InterfaceServantName);

      pCORBA_Task->registerProxy(newProxyInterface,InterfaceServantName,
                                  ServerTask,ServerTaskPOA);

      pCORBA_Task->connectAllProxies();

      DH_HMI_LFInterface = newProxyInterface->getObjRef();

    }

    long input = 1;

    string HeatNo;
    string RetreatId;

    do 
    {
      cout << "Input : " << endl;
      cout << "0 for exit" << endl;
      cout << "1 for send event" << endl;
      cout << "---------------------" << endl;
      cout << "4 send LF_HEAT_ANNOUNCEMENT " << endl;
      cout << "---------------------" << endl;
      cout << "---------------------" << endl;
      cin >> input;

      try
      {


        switch (input)
        {
          case 1:
          {
            if (pEvent_Task)
            {
              string Message;
              cout << "Input Message : " << endl;
              cin >> Message;

              CEventMessage Event("bla","bla","bla",Message,"",true);
              Event.dispatch(SenderName,DestinationList,true);
            }
            break;
          }

          case 4:
          {
            if (pEvent_Task)
            {
              std::string HeatID;
              std::string TreatID;
              std::string PlantID;
              std::string ProductID;
              std::string Message  = LF_EvMsg::evLFHeatAnnouncement ;

              cout << "Input HeatID (C1234567): " << endl;
              cin >> HeatID;
              cout << "Input TreatID (001): " << endl;
              cin >> TreatID;
              cout << "Input PlantID (LF_1_1) : " << endl;
              cin >> PlantID;

              CProductID ID;

              ProductID = ID.getProductID(HeatID,PlantID,TreatID);

              CEventMessage Event("",
                                  "",
                                  Message,
                                  ProductID,"",false,
                                  HeatID,
                                  TreatID,
                                  ProductID);

              Event.setPlantID(PlantID);

              Event.dispatch(SenderName,DestinationList,true);
            }
            break;
          }

          default:
            {
              input = 0;
              break;
            }

        }

      }

      catch(CORBA::SystemException& sExc) 
      {
        cout << "***********************************" << endl;
        cout << "reconenct" << endl;
        cout << "***********************************" << endl;

        pCORBA_Task->connectAllProxies();

        DH_HMI_LFInterface = newProxyInterface->getObjRef();

      }

      catch(CORBA::Exception& cExc) 
      {
        cout << "***********************************" << endl;
        cout << "reconenct" << endl;
        cout << "***********************************" << endl;
        pCORBA_Task->connectAllProxies();

        DH_HMI_LFInterface = newProxyInterface->getObjRef();
        
      }

      catch(...)
      {
        cout << "exception caught "  << endl;
      }

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

