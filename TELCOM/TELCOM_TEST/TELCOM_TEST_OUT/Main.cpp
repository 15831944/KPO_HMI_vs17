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
#include "cCBS_StdFrame.h"

//#include "iDH_Interface_s.hh"
//#include "iDH_Telcom_s.hh"

//-config $(X-Pact)\cfg\TELCOM\TELCOM_TEST_OUT.ini
int main( int argc, const char *argv[], char *envp[] )
{

  try
  {


    // activate SMM Application Environment
    cCBS_StdFrame *pCBS_StdFrame = new cCBS_StdFrame(argc, argv);

    // run the application / CORBA
    pCBS_StdFrame->runAsClient();

    cCBS_StdEvent_Task* pEvent_Task = cCBS_StdEvent_Task::getInstance();
/**
    cCorbaProxyAdapter<DH_Telcom::iDH_Telcom>* newProxyTelcom;
    newProxyTelcom = new cCorbaProxyAdapter<DH_Telcom::iDH_Telcom>();

    cCorbaProxyAdapter<DH::iDH_Interface>* newProxyInterface;
    newProxyInterface = new cCorbaProxyAdapter<DH::iDH_Interface>();


    DH_Telcom::iDH_Telcom_var DH_Telcom;
    DH::iDH_Interface_var DH_L1_BOF_IN_Interface;

    string ServerTask     = "DH_L1_BOF_IN";
    string ServerTaskPOA  = "DH_L1_BOF_INPOA";

    cCBS_StdInitBase::getInstance()->replaceWithEntry("DH", "ServerTask", ServerTask);
    cCBS_StdInitBase::getInstance()->replaceWithEntry("DH", "ServerTaskPOA", ServerTaskPOA);


    cCBS_StdCORBA_Task* pCORBA_Task = cCBS_StdCORBA_Task::getInstance();

    if (pCORBA_Task)
    {
      //***************************************************************************
      string TelcomServantName    = "DH_L1_BOF_INTelcom";

      cCBS_StdInitBase::getInstance()->replaceWithEntry("TELCOM", "ServantName", TelcomServantName);

      pCORBA_Task->registerProxy(newProxyTelcom,TelcomServantName,
                                  ServerTask,ServerTaskPOA);

      //***************************************************************************
      string InterfaceServantName    = "DH_L1_BOF_INInterface";

      cCBS_StdInitBase::getInstance()->replaceWithEntry("DH", "ServantName", InterfaceServantName);

      pCORBA_Task->registerProxy(newProxyInterface,InterfaceServantName,
                                  ServerTask,ServerTaskPOA);

      pCORBA_Task->connectAllProxies();

      DH_Telcom = newProxyTelcom->getObjRef();
      DH_L1_BOF_IN_Interface = newProxyInterface->getObjRef();

    }
    **/
    long input = 1;
    cout << "To test TELCOM_OUT_XX processes,\n";
    cout << "you have to fill the tlg you want to test with test data.\n";
    cout << "Do it after setting header data!\n";
    cout << "*****************************************";
    
    do 
    {
      string HeatNo;
      string TreatID;

      cout << "Input : " << endl;
      cout << "0 for exit" << endl;
      cout << "1 for send event to TELCOM_CCS_OUT " << endl;
      cout << "2 for send event to TELCOM_HMP_OUT " << endl;
      cout << "3 for send event to TELCOM_L3_OUT " << endl;
      cout << "4 for send event to TELCOM_L1_BOF_1_OUT " << endl;
      cout << "5 for send event to TELCOM_L1_LF_1_OUT " << endl;
      cout << "6 for send event to TELCOM_L1_RH_1_OUT " << endl;
      cout << "7 for send event to TELCOM_L1_CONARC_1_OUT " << endl;
      cout << "9 for send event some event " << endl;
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
              string Message("TELEGRAM_");
              string tel;
              string rec;
              string send;

              cout << "Input Telegram : ";
              cin >> tel;
              Message += tel;

              CEventMessage Event("DH_CCS_OUT","TELCOM_CCS_OUT",Message,"12345","",true);
              Event.dispatch(Event.getSender(),Event.getReceiver());
            }
            break;
          }
          case 2:
          {
            if (pEvent_Task)
            {
              string Message("TELEGRAM_L2HM");
              string tel;
              string rec;
              string send;

              cout << "Input Telegram : " << "L2HM";
              cin >> tel;
              Message += tel;

              CEventMessage Event("DH_HMP_OUT","TELCOM_HMP_OUT",Message,"12345","",true);
              Event.dispatch(Event.getSender(),Event.getReceiver());
            }
            break;
          }
          case 3:
          {
            if (pEvent_Task)
            {
              string Message("TELEGRAM_L2L3");
              string tel;
              string rec;
              string send;

              cout << "Input Telegram : " << "L2L3";
              cin >> tel;
              Message += tel;

              CEventMessage Event("DH_L3_OUT","TELCOM_L3_OUT",Message,"12345","",true);
              Event.dispatch(Event.getSender(),Event.getReceiver());
            }
            break;
          }
          case 4:
          {
            if (pEvent_Task)
            {
              string Message("TELEGRAM_L2BO");
              string tel;
              string rec;
              string send;

              cout << "Input Telegram : " << "L2BO";
              cin >> tel;
              Message += tel;

              CEventMessage Event("DH_L1_BOF_OUT","TELCOM_L1_BOF_OUT",Message,"12345","",true);
              Event.setPlantID("1");
              Event.dispatch(Event.getSender(),Event.getReceiver());
            }
            break;
          }
          case 5:
          {
            if (pEvent_Task)
            {
              int mmsec = 500;
              cout << "Send interval in mmsec? : ";
                cin >> mmsec;
              if (mmsec==0)
                mmsec = 500;

              int num = 500;
              cout << "How many send? : ";
                cin >> num;

              string Message("TELEGRAM_L2LF");
              string tel;
              string rec;
              string send;

              cout << "Input Telegram : " << "L2LF";
              cin >> tel;
              Message += tel;

              CEventMessage Event("DH_L1_LF_OUT","TELCOM_L1_LF_1_OUT",Message,"12345","",true);
              Event.setDataKey("L2LF06_5");
              Event.setHeatID("abc");
              Event.setPlantID("1");
              for (int i=0; i<num; i++)
              {
                /* für 1*
                Event.dispatch(Event.getSender(),Event.getReceiver());
                Event.setReceiver("TELCOM_L1_LF_1_OUT");
                Sleep(mmsec);

                Event.dispatch(Event.getSender(),Event.getReceiver());
                Event.setReceiver("TELCOM_L1_LF_2_OUT");
                Sleep(mmsec + 43);

                Event.dispatch(Event.getSender(),Event.getReceiver());
                Event.setReceiver("TELCOM_L1_LF_3_OUT");
                Sleep(mmsec + 3);

                Event.dispatch(Event.getSender(),Event.getReceiver());
                Event.setReceiver("TELCOM_L1_LF_4_OUT");
                Sleep(mmsec + 2);

                Event.dispatch(Event.getSender(),Event.getReceiver());
                Event.setReceiver("TELCOM_L1_LF_5_OUT");
                Sleep(mmsec + 61);
                /**/

                /* für 2 *
                Event.dispatch(Event.getSender(),Event.getReceiver());
                Event.setReceiver("TELCOM_L1_LF_6_OUT");
                Sleep(mmsec + 27);

                Event.dispatch(Event.getSender(),Event.getReceiver());
                Event.setReceiver("TELCOM_L1_LF_7_OUT");
                Sleep(mmsec + 51);

                Event.dispatch(Event.getSender(),Event.getReceiver());
                Event.setReceiver("TELCOM_L1_LF_8_OUT");
                Sleep(mmsec + 21);

                Event.dispatch(Event.getSender(),Event.getReceiver());
                Event.setReceiver("TELCOM_L1_LF_9_OUT");
                Sleep(mmsec + 18);

                Event.dispatch(Event.getSender(),Event.getReceiver());
                Event.setReceiver("TELCOM_L1_LF_10_OUT");
                Sleep(mmsec + 1);
                /**/

                /* für 3*/
                Event.dispatch(Event.getSender(),Event.getReceiver());
                Event.setReceiver("TELCOM_L1_LF_11_OUT");
                Sleep(mmsec + 27);

                Event.dispatch(Event.getSender(),Event.getReceiver());
                Event.setReceiver("TELCOM_L1_LF_12_OUT");
                Sleep(mmsec + 51);

                Event.dispatch(Event.getSender(),Event.getReceiver());
                Event.setReceiver("TELCOM_L1_LF_13_OUT");
                Sleep(mmsec + 21);

                Event.dispatch(Event.getSender(),Event.getReceiver());
                Event.setReceiver("TELCOM_L1_LF_14_OUT");
                Sleep(mmsec + 18);

                Event.dispatch(Event.getSender(),Event.getReceiver());
                Event.setReceiver("TELCOM_L1_LF_15_OUT");
                Sleep(mmsec + 1);
                /**/
              }
            }
            break;
          }
          case 6:
          {
            if (pEvent_Task)
            {
              string Message("TELEGRAM_L2RH");
              string tel;
              string rec;
              string send;

              cout << "Input Telegram : " << "L2RH";
              cin >> tel;
              Message += tel;

              CEventMessage Event("DH_L1_RH_1_OUT","TELCOM_L1_RH_1_OUT",Message,"12345","",true);
              Event.setHeatID("abc");
              Event.setPlantID("1");
              Event.dispatch(Event.getSender(),Event.getReceiver());
            }
            break;
          }
          case 7:
          {
            if (pEvent_Task)
            {
              string Message("TELEGRAM_L2CO");
              string tel;
              string rec;
              string send;

              cout << "Input Telegram : " << "L2CO";
              cin >> tel;
              Message += tel;

              CEventMessage Event("DH_L1_CONARC_1_OUT","TELCOM_L1_CONARC_1_OUT",Message,"12345","",true);
              Event.setHeatID("abc");
              Event.setPlantID("1");
              Event.dispatch(Event.getSender(),Event.getReceiver());
            }
            break;
          }
          case 8:
          {
            if (pEvent_Task)
            {
              string Message("TELEGRAM_L2HD");
              string tel;
              string rec;
              string send;

              cout << "Input Telegram : " << "L2HD";
              cin >> tel;
              Message += tel;

              CEventMessage Event("DH_L1_HMD_1_OUT","TELCOM_L1_HMD_1_OUT",Message,"12345","",true);
              Event.setHeatID("abc");
              Event.setPlantID("1");
              Event.dispatch(Event.getSender(),Event.getReceiver());
            }
            break;
          }
          case 9:
          {
            if (pEvent_Task)
            {
              string Message("TELEGRAM_");
              string tel;
              string rec("TELCOM_");
              string send;

              cout << "Input Receiver name: " << "TELCOM_";
              string r;
              cin >> r;
              rec += r;

              cout << "\nInput Telegram name: ";
              cin >> tel;
              Message += tel;

              CEventMessage Event("DH_L3_OUT",rec,Message,"12345","",true);
              Event.dispatch(Event.getSender(),Event.getReceiver());
            }
            break;
          }
          default:
          {
            input = 0;
            break;
          }
        }// switch

      }// try
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

