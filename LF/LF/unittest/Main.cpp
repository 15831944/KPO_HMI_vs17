#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
	#pragma warning(disable:4099)
#endif

#include "CEventHandler.h"
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

#include "iEventMessages_s.hh"


#include "cCBS_StdFrame.h"



int main( int argc, const char *argv[], char *envp[] )
{

  try
  {
    // activate SMM Application Environment
    cCBS_StdFrame *pCBS_StdFrame = new cCBS_StdFrame(argc, argv);

    // run the application / CORBA
    pCBS_StdFrame->runAsClient();

    std::string Message;
    std::string Destination = "LF";
    std::string Sender = "LF_TEST";


    cCBS_StdEvent_Task* pEvent_Task = cCBS_StdEvent_Task::getInstance();

    cCBS_StdCORBA_Task* pCORBA_Task = cCBS_StdCORBA_Task::getInstance();

    if (pCORBA_Task)
    {
    }

    long input = 1;

    do 
    {

      cout << "Input : " << endl;
      cout << "0 for exit" << endl;
      cout << "1 for send event" << endl;
      cout << "---------------------" << endl;
      cout << "4 for send LF_HEAT_ANNOUNCEMENT to " << Destination << endl;
      cout << "5 for send LF_HEAT_CANCLE to " << Destination << endl;
      cout << "---------------------" << endl;
      cout << "6 for send LF_TEMPMEASUREMENT to " << Destination<< endl;
      cout << "7 for send LF_CYCLIC_MEASUREMENT to " << Destination << endl;
      cin >> input;

      try
      {


        switch (input)
        {
          case 1:
          {
            if (pEvent_Task)
            {
              string ActMessage;
              cout << "Input Message : " << endl;
              cin >> ActMessage;

              string ProductID;
              cout << "Input ProductID : " << endl;
              cin >> ProductID;
              
              CEventMessage Event(Sender,Destination,ActMessage,ProductID,"",false);
              Event.send();
            }
            break;
          }


          case 2:
          {
            break;
          }

          case 3:
          {
            break;
          }

          case 4: // LF_HEAT_ANNOUNCEMENT
          {
            string DataKey="testheatannounce";
            string HeatID;
            cout << "Input HeatID : " << endl;
            cin >>HeatID;
            string TreatID;
            cout << "Input TreatID : " << endl;
            cin >>TreatID;
            string ProductID;
            ProductID=HeatID+"_"+TreatID;
            
            Message = LF_EvMsg::evLFHeatAnnouncement;

            if (pEvent_Task)
            {
              CEventMessage Event(Sender,Destination,LF_EvMsg::evLFHeatAnnouncement,
                                  ProductID,"",true,HeatID,TreatID,DataKey.c_str());
              //CEventMessage Event(Sender,Destination,Message,ProductID,"",false);
              Event.send();
            }

            break;
          }


          case 5: //LF_HEAT_CANCLE
          {
            string ProductID;
            cout << "Input ProductID : " << endl;
            cin >> ProductID;

            Message = LF_EvMsg::evLFHeatCancellation;

            if (pEvent_Task)
            {
              CEventMessage Event(Sender,Destination,Message,ProductID,"",false);
              Event.send();
            }

            break;
          }

          case 6: //LF_TEMPMEASUREMENT
          {
            string ProductID;
            cout << "Input ProductID : " << endl;
            cin >> ProductID;

            Message = LF_EvMsg::evLFTempMeasurement;

            if (pEvent_Task)
            {
              CEventMessage Event(Sender,Destination,Message,ProductID,"",false);
              Event.send();
            }

            break;
          }

          case 7: //LF_CYCLIC_MEASUREMENT
          {

            string ProductID;
            cout << "Input ProductID : " << endl;
            cin >> ProductID;

            Message = LF_EvMsg::evLFCyclicMeasurement;

            if (pEvent_Task)
            {
              CEventMessage Event(Sender,Destination,Message,ProductID,"",false);
              Event.send();
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

