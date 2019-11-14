
// use config file e.g.: -config $(X-Pact)\CFG\DH\DH_L1_ConArc_IN_Test.ini
// use config file e.g.: -config $(X-Pact)\CFG\DH\DH_L1_LF_IN_Test.ini
// use config file e.g.: -config $(X-Pact)\CFG\DH\DH_L1_HMD_IN_Test.ini
// use config file e.g.: -config $(X-Pact)\CFG\DH\DH_L1_RH_IN_Test.ini


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
#include "iDH_Telcom_s.hh"
#include "Telcom_in_s.hh"

#include "CDateTime.h"

int main( int argc, const char *argv[], char *envp[] )
{

  try
  {

    string EventSender    = "DH_IN_Test";
    string EventReceiver  = "DM_IN_Test";

    // activate SMM Application Environment
    cCBS_StdFrame *pCBS_StdFrame = new cCBS_StdFrame(argc, argv);

    // run the application / CORBA
    pCBS_StdFrame->runAsClient();

    cCorbaProxyAdapter<DH_Telcom::iDH_Telcom>* newProxyTelcom;
    newProxyTelcom = new cCorbaProxyAdapter<DH_Telcom::iDH_Telcom>();

    cCorbaProxyAdapter<DH::iDH_Interface>* newProxyInterface;
    newProxyInterface = new cCorbaProxyAdapter<DH::iDH_Interface>();


    DH_Telcom::iDH_Telcom_var DH_Telcom;
    DH::iDH_Interface_var DH_L1_IN_Interface;

    string ServerTask     = "DH_L1_HMD_IN";
    string ServerTaskPOA  = "DH_L1_HMD_INPOA";

    cCBS_StdInitBase::getInstance()->replaceWithEntry("DH", "ServerTask", ServerTask);
    cCBS_StdInitBase::getInstance()->replaceWithEntry("DH", "ServerTaskPOA", ServerTaskPOA);

    cCBS_StdEvent_Task* pEvent_Task = cCBS_StdEvent_Task::getInstance();

    cCBS_StdCORBA_Task* pCORBA_Task = cCBS_StdCORBA_Task::getInstance();

    if (pCORBA_Task)
    {
      //***************************************************************************
      string TelcomServantName    = "DH_L1_HMD_INTelcom";

      cCBS_StdInitBase::getInstance()->replaceWithEntry("TELCOM", "ServantName", TelcomServantName);

      pCORBA_Task->registerProxy(newProxyTelcom,TelcomServantName,
                                  ServerTask,ServerTaskPOA);

      //***************************************************************************
      string InterfaceServantName    = "DH_L1_HMD_INInterface";

      cCBS_StdInitBase::getInstance()->replaceWithEntry("DH", "ServantName", InterfaceServantName);

      pCORBA_Task->registerProxy(newProxyInterface,InterfaceServantName,
                                  ServerTask,ServerTaskPOA);

      pCORBA_Task->connectAllProxies();

      DH_Telcom = newProxyTelcom->getObjRef();
      DH_L1_IN_Interface = newProxyInterface->getObjRef();

    }

    long input = 1;

    string HeatID;
    string TreatID;
    string PlantID;


    do 
    {
      cout << "Input : " << endl;
      cout << "0 for exit" << endl;
      cout << "1 for send event" << endl;
      cout << "2 set HeatID and TreatID " << endl;
      cout << "---------------------" << endl;
      cout << "3 for HMD send HEAT_ANNOUNCEMENT  Telegram_HDL203 to TELCOM interface" << endl;
      cout << "4 for HMD send HEAT_START         Telegram_HDL204 to TELCOM interface" << endl;
      cout << "5 for HMD send HEAT_END           Telegram_HDL205 to TELCOM interface" << endl;
      cout << "6 for HMD send HEAT_CANCEL        Telegram_HDL206 to TELCOM interface" << endl;
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
              Event.dispatch(Event.getSender(),Event.getReceiver());
            }
            break;
          }

          case 2 : // set HeatID and TreatID
          {

            if (DH_Telcom)
            {
              cout << "Input HeatID (C1234567): " << endl;
              cin >> HeatID;
              cout << "Input TreatID (001): " << endl;
              cin >> TreatID;
              
              // cout << "Input PlantID (LF_1_1) : " << endl;
              // cin >> PlantID;

              break;
            }
          }

          case 3: // HEAT_ANNOUNCEMENT
          {

            if (DH_Telcom)
            {
              //string ID = "HDL203";

              //DH_Telcom->indicate(ID.c_str());

              //DH_Telcom->setLong(ID.c_str(),Telegram_HDL203::UnitNo,1);
              //DH_Telcom->setString(ID.c_str(),Telegram_HDL203::HeatNo,HeatID.c_str());
              //DH_Telcom->setString(ID.c_str(),Telegram_HDL203::TreatId,TreatID.c_str());
              //DH_Telcom->setLong(ID.c_str(),Telegram_HDL203::LdlId,1);

              break;
            }
          }
          case 4: // HEAT_START
          {

            if (DH_Telcom)
            {
              break;
            }
          }

          case 5: // HEAT_END
          {

            if (DH_Telcom)
            {
              break;
            }
          }

          case 6: // HEAT_CANCLE
          {

            if (DH_Telcom)
            {

              string ID = "HDL206";

              DH_Telcom->indicate(ID.c_str());
              DH_Telcom->complete(ID.c_str(),ID.c_str());

              break;
            }
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

        DH_Telcom = newProxyTelcom->getObjRef();
        DH_L1_IN_Interface = newProxyInterface->getObjRef();

      }

      catch(CORBA::Exception& cExc) 
      {
        cout << "***********************************" << endl;
        cout << "reconenct" << endl;
        cout << "***********************************" << endl;
        pCORBA_Task->connectAllProxies();

        DH_Telcom = newProxyTelcom->getObjRef();
        DH_L1_IN_Interface = newProxyInterface->getObjRef();
        
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

