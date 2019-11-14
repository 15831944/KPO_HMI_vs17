#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include "iSMC_DataProvider_s.hh"
#include "iSMC_DataDefinitions_s.hh"
#include "CSMC_DataProvider_Impl.h"
#include "iCORBA_Interfaces_s.hh"
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


class CData_Provider_Example : public CSMC_DataProvider_Impl
  
{
public:

  virtual void log(const string & Message){cout << Message << endl;};

};

// use command line argument: -config $(X-Pact)\source\Examples\CORBA_Interfaces\CORBA_Interfaces_Client.ini

int main( int argc, const char *argv[], char *envp[] )
{

  try
  {
    // activate SMM Application Environment
    cCBS_StdFrame *pCBS_StdFrame = new cCBS_StdFrame(argc, argv);

    // run the application / CORBA
    pCBS_StdFrame->runAsClient();

    cCorbaProxyAdapter<iCORBA_Interfaces>* newProxy;
    newProxy = new cCorbaProxyAdapter<iCORBA_Interfaces>();

    iCORBA_Interfaces_var CORBA_Interface;

    cCBS_StdCORBA_Task* pCORBA_Task = cCBS_StdCORBA_Task::getInstance();

    if (pCORBA_Task)
    {
      //***************************************************************************
      std::string ServerTask     = "CORBA_Interfaces_Server";
      std::string ServerTaskPOA  = "TEST";
      std::string ServantName    = "CORBA_InterfaceName";

      pCORBA_Task->registerProxy(newProxy,ServantName,
                                  ServerTask,ServerTaskPOA);

      pCORBA_Task->connectAllProxies();

      CORBA_Interface = newProxy->getObjRef();

      //***************************************************************************


      if (CORBA_Interface)
      {
        std::string key = "Key1";

        do
        {
          cout << "Input Key  ( 0 = exit ) : " << endl;
          cin >> key;

          // ***********************************************************************
          // ***********************************************************************

          std::cout << " Reading non-existing data from CORBA interface" << std::endl << std::endl;

          sDate UnknownDate = CORBA_Interface->getDate(key.c_str(),"DateName");
          

          //********************************************************
          std::cout << " Writing data to CORBA interface" << std::endl << std::endl;
          //********************************************************

          // filling simple data types
          CORBA_Interface->setString(key.c_str(),"StringName","MyString");
          CORBA_Interface->setDouble(key.c_str(),"DoubleName",1.5);

          // filling complex data types
          sAnalysis AnalysisStruct1;
          sAnalysis AnalysisStruct2;
          seqAnalysis AnalysisSequence;

          std::string Elem;
          double Conc;

          // filling structure data
          Elem = "C";
          Conc = 0.5;
          AnalysisStruct1.Concentration = Conc;
          AnalysisStruct1.Element       = Elem.c_str();

          // filling structure data into CORBA sequence
          CIntfData::insert(AnalysisSequence,AnalysisStruct1);

          Elem = "S";
          Conc = 0.3;
          AnalysisStruct2.Concentration = Conc;
          AnalysisStruct2.Element       = Elem.c_str();

          CIntfData::insert(AnalysisSequence,AnalysisStruct2);

          // writing Data into CORBA interface
          //********************************************************
          std::cout << " Writing Analysis data to CORBA interface" << std::endl << std::endl;
          //********************************************************
          CORBA_Interface->setAnalysis(key.c_str(),"AnalysisName",AnalysisSequence);

          // ***********************************************************************
          // reading data from CORBA interface
          // ***********************************************************************

          //********************************************************
          std::cout << " Reading data from CORBA interface" << std::endl << std::endl;
          //********************************************************

          // reading simple data types
          
          std::cout << "String = " << CORBA_Interface->getString(key.c_str(),"StringName") << std::endl;
          std::cout << "Double = " << CORBA_Interface->getDouble(key.c_str(),"DoubleName") << std::endl;

          // reading complex data types
          sAnalysis ResAnalysisStruct;
          seqAnalysis * ResAnalysisSequence;
          long Len = 0;

          ResAnalysisSequence = CORBA_Interface->getAnalysis(key.c_str(),"AnalysisName");
          Len = CIntfData::getLength(*ResAnalysisSequence);

          for ( long i = 0; i < Len ; ++i)
          {
            CIntfData::getAt(ResAnalysisStruct,ResAnalysisSequence,i);
            
            std::cout << " Element = "       << ResAnalysisStruct.Element 
              << " Concentration = " << ResAnalysisStruct.Concentration << std::endl;
          }

          //********************************************************
          std::cout << " Again Reading data from CORBA interface" << std::endl << std::endl;
          //********************************************************

          ResAnalysisSequence = CORBA_Interface->getAnalysis(key.c_str(),"AnalysisName");
          Len = CIntfData::getLength(*ResAnalysisSequence);

          for ( long i = 0; i < Len ; ++i)
          {
            CIntfData::getAt(ResAnalysisStruct,ResAnalysisSequence,i);
            
            std::cout << " Element = "       << ResAnalysisStruct.Element 
              << " Concentration = " << ResAnalysisStruct.Concentration << std::endl;
          }


          //********************************************************
          std::cout << " Copy data from / to CORBA interface" << std::endl << std::endl;
          //********************************************************

          seqIntfDataList * IntfDataListSeq;
          sIntfDataList IntfDataListStruct;
          
          IntfDataListSeq = CORBA_Interface->getIntfDataList(key.c_str());

          Len = CIntfData::getLength(*IntfDataListSeq);

          for ( long i = 0; i < Len ; ++i)
          {
            CIntfData::getAt(IntfDataListStruct,IntfDataListSeq,i);
            
            std::cout << " Name = " << IntfDataListStruct.Name << " Type = " << IntfDataListStruct.Type << std::endl;
          }


          //********************************************************
          std::cout << " Create Client Interface and copy data from Server " << std::endl << std::endl;
          //********************************************************

          CData_Provider_Example *pIntf = new CData_Provider_Example();

          std::string newKey = key + "x";

          CIntfData::copyIntfData( CORBA_Interface, pIntf, key, newKey );

          pIntf->showContent(newKey, 0);

          //********************************************************
          std::cout << " Reading copied data from CORBA interface" << std::endl << std::endl;
          //********************************************************


          ResAnalysisSequence = pIntf->getAnalysis(newKey.c_str(),"AnalysisName");

          Len = CIntfData::getLength(*ResAnalysisSequence);

          for ( long i = 0; i < Len ; ++i)
          {
            CIntfData::getAt(ResAnalysisStruct,ResAnalysisSequence,i);
            
            std::cout << " Element = "       << ResAnalysisStruct.Element 
              << " Concentration = " << ResAnalysisStruct.Concentration << std::endl;
          }


          seqCoolWaterData CoolWaterDataSeq;
          seqCoolWaterData CoolWaterDataSeqRes;
          sCoolWater CoolWaterStruct;
          sCoolWaterDevice CoolWaterDeviceStruct;

          CoolWaterStruct.InletTemp = 1200;
          CoolWaterStruct.OutletTemp = 1300;
          CoolWaterStruct.WaterFlow = 400;

          CoolWaterDeviceStruct.CoolWaterData = CoolWaterStruct;
          CoolWaterDeviceStruct.CoolWaterDevice = "yang";

          CIntfData::insert(CoolWaterDataSeq,CoolWaterDeviceStruct);

          pIntf->setCoolWaterData(newKey.c_str(),DATA::CoolingWaterData,CoolWaterDataSeq);

          CoolWaterDataSeqRes = *pIntf->getCoolWaterData(newKey.c_str(),DATA::CoolingWaterData);

          
          for ( long i = 0 ; i < CIntfData::getLength(CoolWaterDataSeqRes) ; ++i)
          {
            sCoolWaterDevice CoolWaterDeviceStructRes;
            CIntfData::getAt(CoolWaterDeviceStructRes,CoolWaterDataSeqRes,i);

            cout << "Data found : " << CoolWaterDeviceStructRes.CoolWaterDevice << " "
                                    << CoolWaterDeviceStructRes.CoolWaterData.InletTemp << " "
                                    << CoolWaterDeviceStructRes.CoolWaterData.OutletTemp << " "
                                    << CoolWaterDeviceStructRes.CoolWaterData.WaterFlow ;
          }


          CoolWaterDataSeqRes = *pIntf->getCoolWaterData("Jacobs",DATA::CoolingWaterData);


        } while (key != "0");
      }
    }



  }
  catch(cCBS_Exception Exc)
  {
    cout << "CBS exception caught : " << Exc << endl;
  }
  catch(CORBA::SystemException& sExc)
  {
    cout << "CORBA::SystemException caught : " << sExc._name() << endl;
  }
  catch(CORBA::Exception& cExc)
  {
    cout << "CORBA::Exception caught : " << cExc._name() << endl;
  }
  catch(...)
  {
    cout << "General exception caught "  << endl;
  }

  return 0;
}


