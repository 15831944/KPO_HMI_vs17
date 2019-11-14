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
#include "CARCHIVER_LF_Test_DataProvider.h"
#include "CARCHIVER_LF_Test_EventHandler.h"
#include "CARCHIVER_LF_Test_MaterialHandling.h"
#include "CARCHIVER_LF_Test_Task.h"


int main( int argc, const char *argv[], char *envp[] )
{
  //-config $(X-Pact)\cfg\ARCHIVER\ARCHIVER_LF_Test.ini

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

    CARCHIVER_LF_Test_Task * pARCHIVER_Test_Task = CARCHIVER_LF_Test_Task::getInstance();
    pCBS_StdFrame->registerTask(TaskName,pARCHIVER_Test_Task);

    // run the application / CORBA
    pCBS_StdFrame->runAsClient();

    CARCHIVER_LF_Test_DataProvider *m_pTest_DataProvider = 
      new CARCHIVER_LF_Test_DataProvider(CARCHIVER_LF_Test_Task::getInstance()->getpConnection());

    pARCHIVER_Test_Task->setDataProvider(m_pTest_DataProvider);

    std::string Message;
    std::string DestinationName = "TSM_LF_1";
    std::string SenderName = "ARCHIVER_LF";

    cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage", "SenderName", SenderName);
    cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage", "DestinationName", DestinationName);

    cCBS_StdEvent_Task* pEvent_Task = cCBS_StdEvent_Task::getInstance();

    // To get heatID, use: m_pTest_DataProvider->HeatID 
    CEventMessage Event(SenderName,DestinationName,"UNDEFINED","", "",
                        "",false,"","","");

    long input = 1;
    long test_treat_id = 0;
    long ElecMode = 0;
    long StirrMode = 0;
    long MatHandMode = 0;
    long ProbeType = 0;
    std::string CarId;
    std::string LadleId;
    std::stringstream tmp;
    std::string TreatID;
    bool TempMeasReq;
    long InputOfTemp;
    bool SteelSampleReq;
    long InputOfSteel;

    do 
    {
      cout << "Input : " << endl;
      cout << "0 for exit" << endl;
      cout << "1 Heat Announcement                            L2LF03, L2LF07" << endl;
      cout << "2 Heat Cancel event                            L2LF06" <<endl;
      cout << "3 Model Result Code/Comp Mode event            L2LF07" << endl;
      cout << "4 Model Result Actual Set Points event         L2LF07, L2LF30, L2LF31" << endl;
      cout << "5 Model Result Recipe Set Points event         L2LF07, L2LF30, L2LF31,L2LF70" << endl;
      cout << "6 Request Mat Avail event                      L2LF71" << endl;
      cout << "7 Plant Status Request event                   L2LF72" << endl;
      cout << "8 Pull Electrode Request event                 L2LF22" << endl;
      cout << "9 Temperature Sample Request event             L2LF25" << endl;
      cout << "10 Electrode Hydraulic System Inhibit Request  L2LF23" << endl;
      cout << "11 Electrode Hydraulic System Release Request  L2LF23" << endl;
      cout << "99 Set ProbeType" << endl;
      cout << "---------------------" << endl;
      cout << "" << endl;
      cout << "" << endl;
      cout << "---------------------" << endl;
      cin >> input;
      cout << "Enter TreatID: ";
      cin >> TreatID;
      try
      {
        switch (input)
        {
          case 99:
          {
            cout << "Enter Probe Type: ";
            cin >> ProbeType;
            m_pTest_DataProvider->setProbeType(("7000004_"+TreatID), ProbeType);
            break;
          }
          case 1:
          {
            cout << "Enter Electric Status: ";
            cin >> ElecMode;
            cout << "Enter Stirring Status: ";
            cin >> StirrMode;
            cout << "Enter MatHand  Status: ";
            cin >> MatHandMode;
            cout << "Enter CarID: ";
            cin >> CarId;
            cout << "Enter LadleId: ";
            cin >> LadleId;

            Event.setMessage(LF_EvMsg::evLFHeatAnnouncement);
            Event.setHeatID("0000004");
            Event.setTreatID(TreatID);
            Event.setProductID("0000004_"+TreatID);
            tmp.clear();
            Event.setOrderID("7377");
            Event.setPlantID("LF_1_1");
            Event.setPlantEvent(false);
            m_pTest_DataProvider->setLadleCar(("0000004_"+TreatID), CarId, LadleId);
            m_pTest_DataProvider->setComputerMode("0000004", TreatID, ElecMode, StirrMode, MatHandMode);
            Event.dispatch("DH_HMI_LF", "Tracking_LF_1");            
            break;
          }
          case 2:
          {
            Event.setMessage(LF_EvMsg::evLFHeatCancellation);
            Event.setHeatID("0000004");
            Event.setTreatID(TreatID);
            Event.setProductID("7000004_"+TreatID);
            tmp.clear();
            Event.setOrderID("7377");
            Event.setPlantID("LF_1_1");
            Event.setPlantEvent(false);
            Event.dispatch("DH_HMI_LF", "Tracking_LF_1");
              break;
          }
          case 3:
          { 
            cout << "Enter Electric Status: ";
            cin >> ElecMode;
            cout << "Enter Stirring Status: ";
            cin >> StirrMode;
            cout << "Enter MatHand  Status: ";
            cin >> MatHandMode;

            Event.setMessage(LF_EvMsg::evLFModelResultCode);
            Event.setHeatID("7000004");
            Event.setTreatID(TreatID);
            Event.setProductID("7000004_"+TreatID);
            tmp.clear();
            Event.setOrderID("7377");
            Event.setPlantID("LF_1_1");
            Event.setDataKey("MODEL");
            Event.setPlantEvent(false);
            m_pTest_DataProvider->setComputerMode("7000004", TreatID, ElecMode, StirrMode, MatHandMode);
            Event.dispatch("LF_11", "Tracking_LF_1");

            Event.setMessage(LF_EvMsg::evLFSetComputerMode);
            Event.setHeatID("7000004");
            Event.setTreatID(TreatID);
            Event.setProductID("7000004_"+TreatID);
            tmp.clear();
            Event.setOrderID("7377");
            Event.setPlantID("LF_1_1");
            Event.setDataKey("MODEL");
            Event.setPlantEvent(false);
            m_pTest_DataProvider->setComputerMode("7000004", TreatID, ElecMode, StirrMode, MatHandMode);
            Event.dispatch("DH_HMI_LF", "Tracking_LF_1");
            break;
          }
          case 4:
          {
            cout << "Enter Electric Status: ";
            cin >> ElecMode;
            cout << "Enter Stirring Status: ";
            cin >> StirrMode;
            cout << "Enter MatHand  Status: ";
            cin >> MatHandMode;

            Event.setMessage(LF_EvMsg::evLFModelResultActualSetpoints);
            Event.setHeatID("7000004");
            Event.setTreatID(TreatID);
            tmp.clear();
            Event.setProductID("7000004_"+TreatID);
            Event.setOrderID("7377");
            Event.setPlantID("LF_1_1");
            Event.setDataKey("MODEL");
            Event.setPlantEvent(false);
            m_pTest_DataProvider->setComputerMode("7000004", TreatID, ElecMode, StirrMode, MatHandMode);
            m_pTest_DataProvider->setLFModelResult("7000004", TreatID);
            Event.dispatch("LF_11", "Tracking_LF_1");
            break;
          }
          case 5:
          {
            Event.setMessage(LF_EvMsg::evLFModelResultRecipeSetpoints);
            Event.setHeatID("7000004");
            Event.setTreatID(TreatID);
            tmp.clear();
            Event.setProductID("7000004_"+TreatID);
            Event.setOrderID("7377");
            Event.setPlantID("LF_1_1");
            Event.setDataKey("MODEL");
            Event.setPlantEvent(false);
            m_pTest_DataProvider->setLFModelResult("7000004", TreatID);
            Event.dispatch("LF_11", "Tracking_LF_1");
            break;
          }
          case 6:
          {
            Event.setMessage(LF_EvMsg::evLFRequestMatAvail);
            Event.setHeatID("7000004");
            Event.setTreatID(TreatID);
            Event.setProductID("7000004_"+TreatID);
            tmp.clear();
            Event.setOrderID("7377");
            Event.setPlantID("LF_1_1");
            Event.setPlantEvent(false);
            Event.dispatch("DH_HMI_LF", "Tracking_LF_1");
            break;
          }
          case 7:
          {
            Event.setMessage(LF_EvMsg::evLFPlantStatusRequest);
            Event.setHeatID("7000004");
            Event.setTreatID(TreatID);
            Event.setProductID("7000004_"+TreatID);
            tmp.clear();
            Event.setOrderID("7377");
            Event.setPlantID("LF_1_1");
            Event.setPlantEvent(false);
            Event.setDataKey("7000004_" + TreatID + "_1");
            Event.dispatch("DH_HMI_LF", "Tracking_LF_1");
            break;
          }
          case 8:
          {
            Event.setMessage(LF_EvMsg::evLFPullElectrodeRequest);
            Event.setHeatID("7000004");
            Event.setTreatID(TreatID);
            Event.setProductID("7000004_"+TreatID);
            tmp.clear();
            Event.setOrderID("7377");
            Event.setPlantID("LF_1_1");
            Event.setPlantEvent(false);
            Event.setDataKey("7000004_" + TreatID + "_1");
            Event.dispatch("DH_HMI_LF", "Tracking_LF_1");
            break;
          }
          case 9:
          {
            Event.setMessage(LF_EvMsg::evLFTemperatureSampleRequest);
            Event.setHeatID("7000004");
            Event.setTreatID(TreatID);
            Event.setProductID("7000004_"+TreatID);
            tmp.clear();
            Event.setOrderID("7377");
            Event.setPlantID("LF_1_1");
            Event.setPlantEvent(false);
            Event.setDataKey("7000004_" + TreatID + "_1");
            cout << "Please input the value of TempMeasReq and SteelSampleReq (0 - false, 1 - true):" << endl;
            cin  >> InputOfTemp;
            cin  >> InputOfSteel;
            if (InputOfTemp == 0)
            {
              TempMeasReq = false;
            }
            else if (InputOfTemp == 1)
            {
              TempMeasReq = true;
            } 
            else
            {
              cout << "ATTENTION: You input a wrong number for TempMeasReq!!" << endl;
              break;
            }
            if (InputOfSteel == 0)
            {
              SteelSampleReq = false;
            }
            else if (InputOfSteel == 1)
            {
              SteelSampleReq = true;
            } 
            else
            {
              cout << "ATTENTION: You input a wrong number for SteelSampleReq!!" << endl;
              break;
            }
            m_pTest_DataProvider->setTempAndSteelSampleReq("7000004_"+TreatID, TempMeasReq, SteelSampleReq);
            Event.dispatch("DH_HMI_LF", "Tracking_LF_1");
            break;
          }
          case 10:
          {
            Event.setMessage(LF_EvMsg::evLFElectrodeHydraulicSystemInhibitRequest);
            Event.setHeatID("7000004");
            Event.setTreatID(TreatID);
            Event.setProductID("7000004_"+TreatID);
            tmp.clear();
            Event.setOrderID("7377");
            Event.setPlantID("LF_1_1");
            Event.setPlantEvent(false);
            Event.setDataKey("7000004_" + TreatID + "_1");
            Event.dispatch("DH_HMI_LF", "Tracking_LF_1");
            break;
          }
          case 11:
          {
            Event.setMessage(LF_EvMsg::evLFElectrodeHydraulicSystemReleaseRequest);
            Event.setHeatID("7000004");
            Event.setTreatID(TreatID);
            Event.setProductID("7000004_"+TreatID);
            tmp.clear();
            Event.setOrderID("7377");
            Event.setPlantID("LF_1_1");
            Event.setPlantEvent(false);
            Event.setDataKey("7000004_" + TreatID + "_1");
            Event.dispatch("DH_HMI_LF", "Tracking_LF_1");
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

