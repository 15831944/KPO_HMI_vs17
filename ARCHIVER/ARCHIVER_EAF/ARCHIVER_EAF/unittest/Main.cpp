#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include "iSMC_DataDefinitions_s.hh"
#include "iDM_Interface_s.hh"
#include "iEAF_Interface_s.hh"
#include "iEventMessages_s.hh"
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

#include "cCBS_StdFrame.h"

#include "CDateTime.h"


int main( int argc, const char *argv[], char *envp[] )
{

  try
  {
    // activate SMM Application Environment
    cCBS_StdFrame *pCBS_StdFrame = new cCBS_StdFrame(argc, argv);

    // run the application / CORBA
    pCBS_StdFrame->runAsClient();

    CEventHandler Handler;

    EAF_Model::iEAFModelResults_var EAF_Model_Interface;
    DM::iDM_Interface_var DM_Interface;

    string ServerTask     = "ARCHIVER_EAF";
    string ServerTaskPOA  = "ARCHIVER_EAFPOA";

    cCBS_StdInitBase::getInstance()->replaceWithEntry("DH", "ServerTask", ServerTask);
    cCBS_StdInitBase::getInstance()->replaceWithEntry("DH", "ServerTaskPOA", ServerTaskPOA);

    cCBS_StdEvent_Task* pEvent_Task = cCBS_StdEvent_Task::getInstance();

    cCBS_StdCORBA_Task* pCORBA_Task = cCBS_StdCORBA_Task::getInstance();

    if (pCORBA_Task)
    {
      //***************************************************************************
      cCorbaProxyAdapter<EAF_Model::iEAFModelResults>* EAFModelResultsProxy;
      EAFModelResultsProxy = new cCorbaProxyAdapter<EAF_Model::iEAFModelResults>();

      std::string ServerTask     = "EAF_1";
      std::string ServerTaskPOA  = "EAF_1POA";
      std::string ServantName    = "EAF_1ModelResultInterface";

      pCORBA_Task->registerProxy(EAFModelResultsProxy,ServantName,
                                  ServerTask,ServerTaskPOA);

      //***************************************************************************
      cCorbaProxyAdapter<DM::iDM_Interface>* DMModelResultsProxy;
      DMModelResultsProxy = new cCorbaProxyAdapter<DM::iDM_Interface>();

      ServerTask     = "DM_EAF";
      ServerTaskPOA  = "DM_EAFPOA";
      ServantName    = "DM_EAFProductManagementInterface";

      pCORBA_Task->registerProxy(DMModelResultsProxy,ServantName,
                                  ServerTask,ServerTaskPOA);

      //***************************************************************************


      pCORBA_Task->connectAllProxies();

      EAF_Model_Interface = EAFModelResultsProxy->getObjRef();
      if (DMModelResultsProxy && DMModelResultsProxy->isExecuted())
      {
        DM_Interface = DMModelResultsProxy->getObjRef();
      }

    }

    long input = 1;

    do 
    {

      cout << "Input : " << endl;
      cout << "0 for exit" << endl;
      cout << "1 send message to event channel" << endl;
      cout << "2 write and read data from/to EAF_1 Model Result interface" << endl;
      cout << "3 write and read data from/to DM Product interface" << endl;
      cout << "---------------------" << endl;
      cout << "4 for send EAF_MODEL_RESULT_ACTUAL_SETPOINTS to ARCHIVER interface" << endl;
      cout << "5 for send EAF_MODEL_RESULT_RECIPE_SETPOINTS to ARCHIVER interface" << endl;
      cout << "---------------------" << endl;
      cout << "6 for send EAF_MODEL_RESULT_ACTUAL_SETPOINTS to DM interface" << endl;
      cout << "7 for send EAF_MODEL_RESULT_RECIPE_SETPOINTS to DM interface" << endl;
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
              Event.send();
            }
            break;
          }


          case 2:
          {

            string ProductID;
            cout << "Input Product ID = Data Key : " << endl;
            cin >> ProductID;

//            sEAFPredBlowRes PredBlowRes;

    	      sGenRes GenRes;

            GenRes.SlagWeight = 11.11;
            GenRes.SteelWeight = 12.12;
            GenRes.Temp = 1234.0;

            sAnalysis Ana;
            Ana.Element = "S";
            Ana.Concentration = 0.5;

            seqAnalysis sA;
            CIntfData::insert(sA,Ana);
            Ana.Element = "N";
            Ana.Concentration = 0.1;
            CIntfData::insert(sA,Ana);

            GenRes.Analysis = sA;

            sMetTimeStamp sM;

            sM.O2_Moment = 1;
            sM.Ar_Moment = 2;
            sM.N2_Moment = 3;
            sM.Elec_Moment =4;
            sM.DurSinceHeatAnnouncement = 3;
            sM.DurSinceStartOfHeat = 2.5;

            CDateTime now;
            CDeltaTime dt(0 /*s*/, 0/*ms*/,10);
            CDateTime d;
            d = CDateTime::addTimes(now,dt);

            sM.ActionDate = now.assDate();
            sM.RevDate    = d.assDate();

            GenRes.MetTimeStamp = sM;
//            PredBlowRes.GenRes = GenRes;

/*            PredBlowRes.ChromDeslagRate = 1.1;
            PredBlowRes.DecarbRate = 2.2;
            PredBlowRes.O2Vol = 3.3;
            PredBlowRes.Phase = "DynBlowNo";
            PredBlowRes.PhaseActive = 2;
            PredBlowRes.PhaseNo = 1;
            PredBlowRes.TopLanceArFlow = 4.4;
            PredBlowRes.TopLanceHeight = 5.5;
            PredBlowRes.TopLanceN2Flow = 6.6;
            PredBlowRes.TopLanceO2Flow = 7.7;
            PredBlowRes.TuyerArFlow = 8.8;
            PredBlowRes.TuyerN2Flow = 9.9;
            PredBlowRes.TuyerO2Flow = 10.10;*/

//            seqEAFBlowPredRes seqBlowPredRes;


  //          CIntfData::insert(seqBlowPredRes,PredBlowRes);
//            PredBlowRes.Phase = DEF_EAF_PRED_PHASES::Actual;
            //CIntfData::insert(seqBlowPredRes,PredBlowRes);

            if (EAF_Model_Interface)
            {
//              EAF_Model_Interface->setEAFBlowPredRes(ProductID.c_str(),DATA::EAFBlowPredRes,seqBlowPredRes);
            }

            break;
          }

          case 3:
          {
            string ProductID;

            cout << "Input Product ID = Data Key : " << endl;
            cin >> ProductID;
    
            DM_Interface->setDouble(ProductID.c_str(),DATA::DurSinceHeatAnnounce, 1.11);    
            DM_Interface->setDouble(ProductID.c_str(),DATA::DurSinceHeatStart, 2.22);    
            DM_Interface->setLong(ProductID.c_str(),DATA::ElecPullReq, 3);    
            DM_Interface->setLong(ProductID.c_str(),DATA::ElecInhibitReq, 4);

            // -----------------------------------------------------------------------
            // DM_Interface->setPredRes(DataKey.c_str(),DATA::EAFPredRes, SeqPredRes);
            seqPredRes SeqPredRes;
            /* struct sPredRes {
	            string Phase;
	            long PhaseNo;
	            sGenRes GenRes;	
	            long PhaseActive;
            }; */
            sPredRes PredRes;
            PredRes.Phase = "Actual";
            PredRes.PhaseNo = 0;
            PredRes.PhaseActive = 2;
            /*struct sGenRes {
	              seqAnalysis Analysis;
	              double SteelWeight;
	              double SlagWeight;
	              double Temp;
	              double DurPhase;	            
	              sMetTimeStamp MetTimeStamp;
              };*/
            sGenRes GenRes;
            seqAnalysis SeqAnalysis;
            /*struct sAnalysis {
	            string Element;
	            double Concentration;
            };*/
            sAnalysis Analysis;
            Analysis.Element = "S";
            Analysis.Concentration = 0.11;
            CIntfData::insert(SeqAnalysis,Analysis);
            Analysis.Element = "N2";
            Analysis.Concentration = 0.22;
            CIntfData::insert(SeqAnalysis,Analysis);
            GenRes.Analysis=SeqAnalysis;
            GenRes.SteelWeight = 5.55;
            GenRes.SlagWeight = 6.66;
            GenRes.Temp = 7.77;
            GenRes.DurPhase = 8.88;
            /*struct sMetTimeStamp {	            
	            double O2_Moment;	            
	            double Ar_Moment;	            
	            double N2_Moment;	            
	            double Elec_Moment;
	            double DurSinceHeatAnnouncement;
	            double DurSinceStartOfHeat;	            
	            sDate RevDate;	            
	            sDate ActionDate;
            };*/
            sMetTimeStamp MetTimeStamp;
            MetTimeStamp.O2_Moment = 9.99;
            MetTimeStamp.Ar_Moment = 10.10;
            MetTimeStamp.N2_Moment = 11.11;
            MetTimeStamp.Elec_Moment = 12.12;
            MetTimeStamp.DurSinceHeatAnnouncement = 13.13;
            MetTimeStamp.DurSinceStartOfHeat = 14.14;
            CDateTime now;
            CDeltaTime dt(0 /*s*/, 0/*ms*/,10);
            CDateTime d;
            d = CDateTime::addTimes(now,dt);
            MetTimeStamp.RevDate    = d.assDate();
            MetTimeStamp.ActionDate = now.assDate();            
            GenRes.MetTimeStamp = MetTimeStamp;

            PredRes.GenRes = GenRes;
    
            CIntfData::insert(SeqPredRes,PredRes);

            PredRes.Phase = "MeltBskNo:";
            PredRes.PhaseNo = 1;
            PredRes.PhaseActive = 2;

            CIntfData::insert(SeqPredRes,PredRes);

            DM_Interface->setPredRes(ProductID.c_str(),DATA::EAFPredRes, SeqPredRes);
            
            // -----------------------------------------------------------------------------          
            // Data_Interface->setEAFElecPredRes(DataKey.c_str(),DATA::EAFElecPredRes, SeqElecPredRes);
            seqEAFElecPredRes SeqElecPredRes;
            /* struct sEAFElecPredRes {
	              string Phase;
	              long BasketNo;
	              long Step;
	              long VoltTap;
	              long ImpCurve;
	              double DurStep;
	              double SpecEgy;
	              double ElecEgy;
              };*/
            sEAFElecPredRes EAFElecPredRes;
            EAFElecPredRes.Phase = "LiqAdd";
            EAFElecPredRes.BasketNo= 2;
            EAFElecPredRes.Step = 1;
            EAFElecPredRes.VoltTap = 2;
            EAFElecPredRes.ImpCurve = 3;
            EAFElecPredRes.DurStep = 4.44;
            EAFElecPredRes.SpecEgy = 5.55;
            EAFElecPredRes.ElecEgy = 6.66;
            CIntfData::insert(SeqElecPredRes, EAFElecPredRes);              
            EAFElecPredRes.Phase = "LastBsk";
            EAFElecPredRes.BasketNo= 3;
            EAFElecPredRes.Step = 2;
            EAFElecPredRes.VoltTap = 22;
            EAFElecPredRes.ImpCurve = 33;
            EAFElecPredRes.DurStep = 44.44;
            EAFElecPredRes.SpecEgy = 55.55;
            EAFElecPredRes.ElecEgy = 66.66;
            CIntfData::insert(SeqElecPredRes, EAFElecPredRes);              

            DM_Interface->setEAFElecPredRes(ProductID.c_str(),DATA::EAFElecPredRes, SeqElecPredRes);

            // ------------------------------------------------------------------
            // seqEAFGasLancePredRes SeqGasLanceRes 
            // Data_Interface->
            // setEAFGasLancePredRes(DataKey.c_str(),DATA::EAFGasLancePredRes, SeqGasLanceRes); 
            seqEAFGasLancePredRes SeqGasLanceRes;
            /*struct sEAFGasLancePredRes {
	              string Phase;
	              long BasketNo;
	              long Step;
	              long LanceNo;
	              double DurStep;
	              double SpecEgy;
	              double GasFlow;
	              string GasTyp;
              }; */
            sEAFGasLancePredRes EAFGasLancePredRes;
            EAFGasLancePredRes.Phase = "LiqAdd";
            EAFGasLancePredRes.BasketNo = 2;
            EAFGasLancePredRes.Step = 22;
            EAFGasLancePredRes.LanceNo = 1;
            EAFGasLancePredRes.DurStep = 122.22;
            EAFGasLancePredRes.SpecEgy = 123.33;

          	seqGasData Flow;
            sGasData   Data;
            Data.GasType  = "N2";
            Data.GasValue = 124.44;
            CIntfData::insert(Flow, Data);
            EAFGasLancePredRes.GasFlow = Flow;
            CIntfData::insert(SeqGasLanceRes, EAFGasLancePredRes);

            EAFGasLancePredRes.Phase = "LastBsk";
            EAFGasLancePredRes.BasketNo = 3;
            EAFGasLancePredRes.Step = 44;
            EAFGasLancePredRes.DurStep = 222.22;
            EAFGasLancePredRes.SpecEgy = 223.33;

            Data.GasType  = "N2";
            Data.GasValue = 224.44;
            CIntfData::insert(Flow, Data);
            EAFGasLancePredRes.GasFlow = Flow;

            CIntfData::insert(SeqGasLanceRes, EAFGasLancePredRes);

            DM_Interface->
            setEAFGasLancePredRes(ProductID.c_str(),DATA::EAFGasLancePredRes, SeqGasLanceRes); 

            // -----------------------------------------------------------------------------
            // seqEAFInjectLance SeqInjectLanceRes
            // Data_Interface->
            // setEAFInjectLance(DataKey.c_str(),DATA::EAFInjectLance,SeqInjectLanceRes); 
            seqEAFInjectLance SeqInjectLanceRes;
            /* struct sEAFInjectLance {
	              string Phase;
	              long BasketNo;
	              long Step;
	              double DurStep;
	              double SpecEgy;
	              string InjctTyp;
	              double SetpVal;
              };*/
            sEAFInjectLance EAFInjectLance;
            EAFInjectLance.Phase = "LiqAdd";
            EAFInjectLance.BasketNo = 4;
            EAFInjectLance.Step = 44;
            EAFInjectLance.DurStep = 311.11;
            EAFInjectLance.Egy  = 312.22;

      	    seqInjectData InjectFlow;
            sInjectData   InjectData;
            InjectData.InjectType     = "1002";
            InjectData.InjectMatCode  = "1002";
            InjectData.InjectMatValue = 313.33;
            CIntfData::insert(InjectFlow, InjectData);
            CIntfData::insert(SeqInjectLanceRes, EAFInjectLance);

            EAFInjectLance.Phase = "LastBsk";
            EAFInjectLance.BasketNo = 5;
            EAFInjectLance.Step = 55;
            EAFInjectLance.DurStep = 411.11;
            EAFInjectLance.Egy  = 412.22;

            InjectData.InjectType     = "1002";
            InjectData.InjectMatCode  = "1002";
            InjectData.InjectMatValue = 413.33;
            CIntfData::insert(InjectFlow, InjectData);
            CIntfData::insert(SeqInjectLanceRes, EAFInjectLance);

            DM_Interface->
            setEAFInjectLance(ProductID.c_str(),DATA::EAFInjectLance,SeqInjectLanceRes); 
  
            // ---------------------------------------------------------------------------
            // seqComputerModes SeqComputerModes
            // Data_Interface->
            // setComputerModes( DataKey.c_str(), DATA::EAFComputerModeAvail, SeqComputerModes);
            seqComputerModes SeqComputerModes;
            /* struct sComputerMode {
	              string Device;	                
	              long Status;
              }; */
            sComputerMode ComputerMode;
            ComputerMode.Device = "DeviceComputerMode1";
            ComputerMode.Status=1;
            CIntfData::insert(SeqComputerModes, ComputerMode);
            ComputerMode.Device = "DeviceComputerMode2";
            ComputerMode.Status=2;
            CIntfData::insert(SeqComputerModes, ComputerMode);

            DM_Interface->
            setComputerModes( ProductID.c_str(), DATA::EAFComputerModeAvail, SeqComputerModes);

            // ================================================================================
                                      
            cout << " Read Data from DM interface " << endl ;

            double RetValue = 
              DM_Interface->getDouble(ProductID.c_str(),DATA::DurSinceHeatAnnounce);
            double RetValue2 = 
              DM_Interface->getDouble(ProductID.c_str(),DATA::DurSinceHeatStart);

            if (DM_Interface)
            {
              cout << "DATA::DurSinceHeatAnnounce : " << RetValue << ", DurSinceHeatStart " <<RetValue2 << endl;
            }

            break;
          }

          case 4:
          {
            if (pEvent_Task)
            {
              string HeatID;
              cout << "Input HeatID : " << endl;
              cin >> HeatID;
              string TreatID;
              cout << "Input TreatID : " << endl;
              cin >> TreatID;
              string ProductID;
              cout << "Input Product ID : " << endl;
              cin >> ProductID;


              /**
              CEventMessage(const string & sender, 
                            const string & receiver, 
                            const string & message, 
                            const string & productID, 
                            const string & relatedProductID,  
                            bool isPlantEvent, 
                            const string &HeatID,
                            const string &TreatID,
                            const string &DataKey);
              */

              CEventMessage Event("TSM_EAF","ARCHIVER_EAF",EAF_EvMsg::evEAFModelResultActualSetpoints,
                                  ProductID,"EMPTY",true,HeatID,TreatID,ProductID);
              Event.send();
            }

            break;
          }


          case 5:
          {
            if (pEvent_Task)
            {
              string ProductID;
              cout << "Input Product ID : " << endl;
              cin >> ProductID;

              CEventMessage Event("TSM_EAF","ARCHIVER_EAF",EAF_EvMsg::evEAFModelResultRecipeSetpoints,
                                  ProductID,"",true,"","",ProductID);
              Event.send();
            }
            break;
          }

          case 6:
          {
            if (pEvent_Task)
            {
              string ProductID;
              cout << "Input Product ID : " << endl;
              cin >> ProductID;

              CEventMessage Event("EAF","DM_EAF",EAF_EvMsg::evEAFModelResultActualSetpoints,
                                  ProductID,"",true,"","",ProductID);
              Event.send();
            }

            break;
          }


          case 7:
          {
            if (pEvent_Task)
            {
              string ProductID;
              cout << "Input Product ID : " << endl;
              cin >> ProductID;

              CEventMessage Event("EAF","DM_EAF",EAF_EvMsg::evEAFModelResultRecipeSetpoints,
                                  ProductID,"",true,"","",ProductID);
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

