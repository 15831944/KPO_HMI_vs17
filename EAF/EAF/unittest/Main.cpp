#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
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
#include "iSMC_DataDefinitions_s.hh"

#include "cCBS_StdFrame.h"
#include "CDM_ProductManagementInterface_Impl.h"
#include "CDM_DataInterface_Impl.h"
#include "CDM_PlantManagementInterface_Impl.h"
#include "CProductID.h"

// use config file e.g.: -config $(X-Pact)\cfg\EAF\EAF_Test.ini


int main( int argc, const char *argv[], char *envp[] )
{

  try
  {
    // activate SMM Application Environment
    cCBS_StdFrame *pCBS_StdFrame = new cCBS_StdFrame(argc, argv);

    // run the application / CORBA
    pCBS_StdFrame->runAsClient();

    std::string Message;
    std::string DestinationName = "EAF_1";
    std::string SenderName = "DM_EAF";

    cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage", "SenderName", SenderName);
    cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage", "DestinationName", DestinationName);



	  //##ModelId=416A973000F1
	  CDM_ProductManagementInterface_Impl* m_pProductManagementInterface = 0;

	  //##ModelId=416A97320194
	  CDM_DataInterface_Impl* m_pDataInterface = 0;

	  //##ModelId=41C981F101E3
	  CDM_PlantManagementInterface_Impl* m_pPlantManagementInterface = 0;


    cCBS_StdEvent_Task* pEvent_Task = cCBS_StdEvent_Task::getInstance();

    cCBS_StdCORBA_Task* pCORBA_Task = cCBS_StdCORBA_Task::getInstance();

    if (pCORBA_Task)
    {
      // init DM interfaces
	    m_pDataInterface = new CDM_DataInterface_Impl();
      m_pProductManagementInterface = new CDM_ProductManagementInterface_Impl();
      m_pPlantManagementInterface = new CDM_PlantManagementInterface_Impl();

      std::string ServerName = cCBS_StdInitBase::getInstance()->m_ServerName;

      std::string ServantName    = ServerName + "DataInterface";
      cCBS_StdInitBase::getInstance()->replaceWithEntry(ServerName, "DataInterface", ServantName);
      pCORBA_Task->registerServant(m_pDataInterface,ServantName);
      m_pDataInterface->setProviderName(ServantName);

      ServantName    = ServerName + "ProductManagementInterface";
      cCBS_StdInitBase::getInstance()->replaceWithEntry(ServerName, "ProductManagementInterface", ServantName);
      pCORBA_Task->registerServant(m_pProductManagementInterface,ServantName);
      m_pProductManagementInterface->setProviderName(ServantName);

      ServantName    = ServerName + "PlantManagementInterface";
      cCBS_StdInitBase::getInstance()->replaceWithEntry(ServerName, "PlantManagementInterface", ServantName);
      pCORBA_Task->registerServant(m_pPlantManagementInterface,ServantName);
      m_pPlantManagementInterface->setProviderName(ServantName);


    }

    long input = 1;

    do 
    {

      cout << "Input : " << endl;
      cout << "0 for exit" << endl;
      cout << "1 for send event" << endl;
      cout << "---------------------" << endl;
      cout << "4 for send EAF_HEAT_ANNOUNCEMENT to " << DestinationName << endl;
      cout << "5 for send EAF_HEAT_CANCLE to " << DestinationName << endl;
      cout << "---------------------" << endl;
      cout << "6 for send EAF_TEMPMEASUREMENT to " << DestinationName<< endl;
      cout << "7 for send EAF_CYCLIC_MEASUREMENT to " << DestinationName << endl;
      cout << "---------------------" << endl;
      cout << "10 for send EAF_AIM_DATA_cHANGE to " << DestinationName<< endl;
      cout << "11 for send /restriction change to " << DestinationName << endl;
      cout << "12 for send /basket change      to " << DestinationName << endl;
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


              CEventMessage Event(SenderName,DestinationName,ActMessage,ProductID,"",false);
              Event.dispatch(Event.getSender(),Event.getReceiver());
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

          case 4: // EAF_HEAT_ANNOUNCEMENT
          {

            string HeatID;
            cout << "Input HeatID : " << endl;
            cin >> HeatID;

            string TreatID;
            cout << "Input TreatID : " << endl;
            cin >> TreatID;

            std::string PlantID = "EAF";
            std::string ModelID = "EAF_1";

            cCBS_StdInitBase::getInstance()->replaceWithEntry("PROCESS", "PlantID", PlantID);
            cCBS_StdInitBase::getInstance()->replaceWithEntry("Model", "ServerName", ModelID);

            CProductID PID;
            std::string ProductID = PID.getProductID(HeatID,TreatID);

            // registering Product
            m_pProductManagementInterface->setString(ProductID,DATA::ProductID,ProductID);
            m_pProductManagementInterface->setString(ProductID,DATA::HeatID,HeatID);
            m_pProductManagementInterface->setString(ProductID,DATA::TreatID,TreatID);

            // assign Product to Model
            m_pPlantManagementInterface->setString(ModelID,DATA::ProductID,ProductID);
            m_pPlantManagementInterface->setString(ModelID,DATA::HeatID,HeatID);
            m_pPlantManagementInterface->setString(ModelID,DATA::TreatID,TreatID);

            Message = EAF_EvMsg::evEAFHeatAnnouncement;

            if (pEvent_Task)
            {
              CEventMessage Event(SenderName,DestinationName,Message,ProductID,"",false,HeatID,TreatID,ProductID);
              Event.setPlantID(PlantID);
              Event.dispatch(Event.getSender(),Event.getReceiver());
            }

            break;
          }


          case 5: //EAF_HEAT_CANCLE
          {
            string ProductID;
            cout << "Input ProductID : " << endl;
            cin >> ProductID;

            Message = EAF_EvMsg::evEAFHeatCancellation;

            if (pEvent_Task)
            {
              CEventMessage Event(SenderName,DestinationName,Message,ProductID,"",false);
              Event.dispatch(Event.getSender(),Event.getReceiver());
            }

            break;
          }

          case 6: //EAF_TEMPMEASUREMENT
          {
            string ProductID;
            cout << "Input ProductID : " << endl;
            cin >> ProductID;

            Message = EAF_EvMsg::evEAFTempMeasurement;

            if (pEvent_Task)
            {
              CEventMessage Event(SenderName,DestinationName,Message,ProductID,"",false);
              Event.dispatch(Event.getSender(),Event.getReceiver());
            }

            break;
          }

          case 7: //EAF_CYCLIC_MEASUREMENT
          {

            string ProductID;
            cout << "Input ProductID : " << endl;
            cin >> ProductID;

            Message = EAF_EvMsg::evEAFCyclicMeasurement;

            if (pEvent_Task)
            {
              CEventMessage Event(SenderName,DestinationName,Message,ProductID,"",false);
              Event.dispatch(Event.getSender(),Event.getReceiver());
            }

            break;
          }

//
          case 10: //EAF_AIM_DATA_cHANGE
          {
              // data in PD_heat_data , pd_heat_data_prod_prac should have been changed
            //string ProductID;
            //cout << "Input ProductID : " << endl;
            //cin >> ProductID;


            string HeatID;
            cout << "Input HeatID : " << endl;
            cin >> HeatID;

            string TreatID;
            cout << "Input TreatID : " << endl;
            cin >> TreatID;

            std::string PlantID = "EAF";
            std::string ModelID = "EAF_1";

            //cCBS_StdInitBase::getInstance()->replaceWithEntry("PROCESS", "PlantID", PlantID);
            //cCBS_StdInitBase::getInstance()->replaceWithEntry("Model", "ServerName", ModelID);

            CProductID PID;
            std::string ProductID = PID.getProductID(HeatID,TreatID);



            Message = EAF_EvMsg::evEAFChangeAimData;

            if (pEvent_Task)
            {
              //CEventMessage Event(SenderName,DestinationName,Message,ProductID,"",false);
              CEventMessage Event(SenderName,DestinationName,Message,ProductID,"",false,HeatID,TreatID,ProductID);
              Event.setPlantID(PlantID);

              Event.dispatch(Event.getSender(),Event.getReceiver());
            }

            break;
          }
          case 11: //restriction change
          {
              // data in PD_heat_data , pd_heat_data_prod_prac should have been changed
            string HeatID;
            cout << "Input HeatID : " << endl;
            cin >> HeatID;

            string TreatID;
            cout << "Input TreatID : " << endl;
            cin >> TreatID;

            std::string PlantID = "EAF";
            std::string ModelID = "EAF_1";

             CProductID PID;
            std::string ProductID = PID.getProductID(HeatID,TreatID);

            Message = EAF_EvMsg::evEAFChangeProdPracDataRecipeCTRL;

            m_pProductManagementInterface->setLong(ProductID,DATA::FlagHeatRelated, 0L);
            m_pProductManagementInterface->setLong(ProductID,DATA::ProdPracPointer, 1L);   // switch to ptr 1

            if (pEvent_Task)
            {
              CEventMessage Event(SenderName,DestinationName,Message,ProductID,"",false,HeatID,TreatID,ProductID);
              Event.setPlantID(PlantID);
              Event.dispatch(Event.getSender(),Event.getReceiver());
            }

            break;
          }
          case 12: //basket change
          {
              // data in pd_basket_heat should have been changed !!
            string HeatID;
            cout << "Input HeatID : " << endl;
            cin >> HeatID;

            string TreatID;
            cout << "Input TreatID : " << endl;
            cin >> TreatID;

            std::string PlantID = "EAF";
            std::string ModelID = "EAF_1";

             CProductID PID;
            std::string ProductID = PID.getProductID(HeatID,TreatID);

            Message = EAF_EvMsg::evEAFHandleSetBasketData;

            if (pEvent_Task)
            {
              CEventMessage Event(SenderName,DestinationName,Message,ProductID,"",false,HeatID,TreatID,ProductID);
              Event.setPlantID(PlantID);
              Event.dispatch(Event.getSender(),Event.getReceiver());
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

