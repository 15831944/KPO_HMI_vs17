#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <crtdbg.h>
#include <cstdio>


#include <string>
#include <iostream>
#include <sstream>

#include "CDateTime.h"
#include "CIntfData.h"
#include "cCBS_StdFrame.h"
#include "iSMC_DataProvider_s.hh"
#include "iSMC_DataDefinitions_s.hh"

#include "CData_Provider.h"
#include "CSMC_DataProvider_Impl.h"
#include "CSMC_FileLogHandler.h"
#include "CEventMessage.h"

// use command line argument: -config $(XPACT_SMC)\CFG\Examples\Data_Provider_Example.ini

class CData_Provider_Example : public CSMC_DataProvider_Impl
  
{
public:
  virtual void log(const string & Message){cout << Message << endl;};

  virtual void onComplete(){;};
  virtual void onIndicate(){;};
  virtual void afterDataAccess(){;};
  virtual void beforeDataAccess(){;};

};




int main( int argc, const char *argv[], char *envp[] )
{

  try
  {
    // activate SMM Application Environment
    cCBS_StdFrame *pCBS_StdFrame = new cCBS_StdFrame(argc, argv);

    CSMC_FileLogHandler* pSMC_FileLogHandler = new CSMC_FileLogHandler();
    pCBS_StdFrame->registerLogHandler(pSMC_FileLogHandler);

    pSMC_FileLogHandler = new CSMC_FileLogHandler("lujin");
    pCBS_StdFrame->registerLogHandler(pSMC_FileLogHandler);

    // run the application / CORBA
    pCBS_StdFrame->runAsClient();

    CData_Provider_Example *pData_Provider_Example = new CData_Provider_Example();

    DynamicAny::DynAnyFactory_var DynAnyFact = 0;
    CORBA::Object_var dynObj = CBS::getORB()->resolve_initial_references("DynAnyFactory");
    DynAnyFact               = DynamicAny::DynAnyFactory::_narrow(dynObj);

    //DynamicAny::DynSequence_var ds;

    //ds.insert_typecode(CORBA::_tc_any);


    //virtual void set_length (CORBA::ULong len) = 0;
    //virtual void set_elements(const AnySeq& value) = 0;
    //virtual void set_elements_as_dyn_any(const DynAnySeq& value) = 0;
    


    CORBA::StructMemberSeq SMS;
    
    CORBA::StructMember SM;

    SM.name = "Element";
    SM.type = CORBA::_tc_string;
    //SM.type_def = SMTC.type();
    CIntfData::insert(SMS,SM);

    SM.name = "Concentration";
    SM.type = CORBA::_tc_double;
    // SM.type_def = "double";
    CIntfData::insert(SMS,SM);
    
    CORBA::TypeCode_ptr tcAnalysisStruct = CBS::getORB()->create_struct_tc("sAnalysis","sAnalysis",SMS);

    CORBA::TypeCode_ptr tcAnalysisSEQ = CBS::getORB()->create_sequence_tc(1,tcAnalysisStruct);

    CORBA::Any MyAny;

    MyAny.type(tcAnalysisSEQ);

    CIntfData::getContent(MyAny);


   
    // CORBA::Any MyAny(TypeCode_ptr tc, void* value, Boolean release = 0);	


    long input = 1;

    do 
    {
      cout << "Input : " << endl;
      cout << "0 for exit" << endl;
      cout << "1 write data into interface " << endl;
      cout << "2 read string data from interface" << endl;
      cout << "3 read any data from interface" << endl;
      cout << "4 set maximum data buffer size " << endl;
      cout << "5 repeat writing any data into interface " << endl;
      cout << "55 repeat reading and check memory  " << endl;
      cout << "56 repeat writing and check memory  " << endl;
      cout << "6 write and read different data types into/from interface " << endl;
      cout << "7 write and read sDate data into/from interface " << endl;
      cout << "8 test data validation " << endl;
      cout << "9 interfaceDataList " << endl;
      cin >> input;

      switch (input)
      {
        case 1:
        {
          std::string DataKey;
//          cout << "insert Data Key" << endl;
//          cin >> DataKey;

          DataKey   = pData_Provider_Example->generateDataKey(DataKey.c_str());

          pData_Provider_Example->setString((DataKey).c_str(),"StringName","StringValue");
          pData_Provider_Example->setString((DataKey+"1").c_str(),"StringName","StringValue");
          pData_Provider_Example->setString((DataKey+"2").c_str(),"StringName","StringValue");
          pData_Provider_Example->setString((DataKey+"3").c_str(),"StringName","StringValue");
          pData_Provider_Example->setString((DataKey+"4").c_str(),"StringName","StringValue");
          pData_Provider_Example->setString((DataKey+"5").c_str(),"StringName","StringValue");
          pData_Provider_Example->setString((DataKey+"6").c_str(),"StringName","StringValue");
          pData_Provider_Example->setString((DataKey+"7").c_str(),"StringName","StringValue");


          seqAnalysis AnalysisSeq;
          sAnalysis AnalysisStruct;
          AnalysisStruct.Element = "C";
          AnalysisStruct.Concentration = 0.1;

          CIntfData::insert(AnalysisSeq,AnalysisStruct);


          pData_Provider_Example->setAnalysis((DataKey+"8").c_str(),"AnyName",AnalysisSeq);


          pData_Provider_Example->showContent();

          CEventMessage Message("SENDER","RECEIVER","MESSAGE","PRODID","RELPID",false,"HEAT","TREAT",DataKey);
          Message.dispatch("DATA_PROVIDER_EXAMPLE","JOHANN");

          break;

        }
        case 2:
        {
          pData_Provider_Example->showContent();

          std::string DataKey;
          cout << "insert Data Key" << endl;
          cin >> DataKey;

          cout << "Data found : "<< pData_Provider_Example->getString(DataKey.c_str(),"StringName") << endl;

          break;

        }
        case 3:
        {
          pData_Provider_Example->showContent();

          std::string DataKey;
          cout << "insert Data Key" << endl;
          cin >> DataKey;

          
          seqAnalysis* AnalysisSeq;

          AnalysisSeq = pData_Provider_Example->getAnalysis(DataKey.c_str(),"AnyName");

          for ( long i = 0 ; i < CIntfData::getLength(*AnalysisSeq) ; ++i)
          {
            sAnalysis AnalysisStruct;
            CIntfData::getAt(AnalysisStruct, AnalysisSeq, i);

            cout << "Data found : " << AnalysisStruct.Element << " " << AnalysisStruct.Concentration << endl;
          }


          break;

        }
        case 4:
        {
          long BufferSize;
          cout << "insert BufferSize" << endl;
          cin >> BufferSize;

          pData_Provider_Example->setBufferSize(BufferSize);

          break;

        }
        case 5:
        {
          std::string DataKey;
          DataKey   = pData_Provider_Example->generateDataKey(DataKey.c_str());

          long Counter;
          cout << "insert Counter" << endl;
          cin >> Counter;

          pData_Provider_Example->showContent();

          seqAnalysis AnalysisSeq;
          sAnalysis AnalysisStruct;
          AnalysisStruct.Element = "C";
          AnalysisStruct.Concentration = 0.1;

          CIntfData::insert(AnalysisSeq,AnalysisStruct);

          CORBA::Any AnalysisAny;
          AnalysisAny = CIntfData::ToAny(AnalysisSeq);

          pData_Provider_Example->setBufferSize(max(Counter/100,1));


          for ( long i = 0 ; i < Counter ; ++i)
          {
            std::ostringstream strDataKey;
            strDataKey << i ;
            std::string DataKey = strDataKey.str();

            pData_Provider_Example->setAny(DataKey.c_str(),"AnyName",AnalysisAny);

            //pData_Provider_Example->showContent();

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

          pData_Provider_Example->setCoolWaterData(DataKey.c_str(),DATA::CoolingWaterData,CoolWaterDataSeq);

          CoolWaterDataSeqRes = *pData_Provider_Example->getCoolWaterData(DataKey.c_str(),DATA::CoolingWaterData);

          
          for ( long i = 0 ; i < CIntfData::getLength(CoolWaterDataSeqRes) ; ++i)
          {
            sCoolWaterDevice CoolWaterDeviceStructRes;
            CIntfData::getAt(CoolWaterDeviceStructRes,CoolWaterDataSeqRes,i);

            cout << "Data found : " << CoolWaterDeviceStructRes.CoolWaterDevice << " "
                                    << CoolWaterDeviceStructRes.CoolWaterData.InletTemp << " "
                                    << CoolWaterDeviceStructRes.CoolWaterData.OutletTemp << " "
                                    << CoolWaterDeviceStructRes.CoolWaterData.WaterFlow ;
          }


          CoolWaterDataSeqRes = *pData_Provider_Example->getCoolWaterData("Jacobs",DATA::CoolingWaterData);

          break;

        }

        case 55:
        {
          seqCoolWaterData CoolWaterDataSeq;
          seqCoolWaterData CoolWaterDataSeqRes;
          sCoolWater CoolWaterStruct;
          sCoolWaterDevice CoolWaterDeviceStruct;

          CoolWaterStruct.InletTemp = 1200;
          CoolWaterStruct.OutletTemp = 1300;
          CoolWaterStruct.WaterFlow = 400;

          CoolWaterDeviceStruct.CoolWaterData = CoolWaterStruct;
          CoolWaterDeviceStruct.CoolWaterDevice = "Stefan";

          CIntfData::insert(CoolWaterDataSeq,CoolWaterDeviceStruct);

          pData_Provider_Example->setCoolWaterData("Stefan",DATA::CoolingWaterData,CoolWaterDataSeq);

          for ( long i = 1 ; i < 2000; ++i)
          {
            cout << i << " " ; 

            seqCoolWaterData *CoolWaterDataSeqRes = 0;

            CoolWaterDataSeqRes = pData_Provider_Example->getCoolWaterData("Stefan",DATA::CoolingWaterData);

            for ( long i = 0 ; i < CIntfData::getLength(CoolWaterDataSeqRes) ; ++i)
            {
              sCoolWaterDevice CoolWaterDeviceStructRes;
              CIntfData::getAt(CoolWaterDeviceStructRes,CoolWaterDataSeqRes,i);

              cout << "Data found : " << CoolWaterDeviceStructRes.CoolWaterDevice << " "
                                      << CoolWaterDeviceStructRes.CoolWaterData.InletTemp << " "
                                      << CoolWaterDeviceStructRes.CoolWaterData.OutletTemp << " "
                                      << CoolWaterDeviceStructRes.CoolWaterData.WaterFlow ;
            }


            delete CoolWaterDataSeqRes;

            Sleep(1);
            cout << endl ; 


          }

          break;

        }

        case 56:
        {
          seqCoolWaterData CoolWaterDataSeq;
          seqCoolWaterData CoolWaterDataSeqRes;
          sCoolWater CoolWaterStruct;
          sCoolWaterDevice CoolWaterDeviceStruct;

          CoolWaterStruct.InletTemp = 1200;
          CoolWaterStruct.OutletTemp = 1300;
          CoolWaterStruct.WaterFlow = 400;

          CoolWaterDeviceStruct.CoolWaterData = CoolWaterStruct;
          CoolWaterDeviceStruct.CoolWaterDevice = "Stefan";

          CIntfData::insert(CoolWaterDataSeq,CoolWaterDeviceStruct);

          std::vector<std::string> keylist;

          for ( long i = 1 ; i < 2000; ++i)
          {
            cout << i << " " ; 

            std::stringstream key;

            key << "Stefan" << i ;

            // test something with persistant keys
            if ( i > 200 && i < 400 )
            {
              pData_Provider_Example->setPersistence(key.str().c_str(),true);

              keylist.push_back(key.str());
            }


            if ( i == 1000 )
            {
              std::vector<std::string>::iterator it; 
              for ( it = keylist.begin() ; it != keylist.end() ; ++ it )
              {
                cout << "removing persistance for " << (*it) << endl ; 
                pData_Provider_Example->setPersistence((*it),false);
              }
            }


            pData_Provider_Example->setCoolWaterData(key.str().c_str(),DATA::CoolingWaterData,CoolWaterDataSeq);

            Sleep(1);
            cout << endl ; 


          }

          break;

        }



        case 6:
        {

          cout << endl << endl<< "Write DOUBLE and read LONG " << endl;
          pData_Provider_Example->setDouble("101","DoubleName",1234.5);
          pData_Provider_Example->showContent();
          cout << pData_Provider_Example->getLong("101","DoubleName") << endl;

          cout << endl << endl<< "Write LONG and read DOUBLE " << endl;
          pData_Provider_Example->setLong("102","LongName",1234);
          pData_Provider_Example->showContent();
          cout << pData_Provider_Example->getDouble("102","LongName") << endl;

          cout << endl << endl<< "Write LONG and read STRING " << endl;
          pData_Provider_Example->setLong("103","LongName",1234);
          pData_Provider_Example->showContent();
          cout << pData_Provider_Example->getString("103","LongName") << endl;

          cout << endl << endl<< "Write DOUBLE and read STRING " << endl;
          pData_Provider_Example->setDouble("104","DoubleName",1234.5);
          pData_Provider_Example->showContent();
          cout << pData_Provider_Example->getString("104","DoubleName") << endl;


          cout << endl << endl<< "Write BOOLEAN and read DOUBLE " << endl;
          pData_Provider_Example->setBoolean("105","BooleanName",true);
          pData_Provider_Example->showContent();
          cout << pData_Provider_Example->getDouble("105","BooleanName") << endl;

          break;

        }

        case 7:
        {

          cout << endl << endl<< "Write sDate " << endl;
          
          CDateTime ActDate;

          sDate sDateWrite = ActDate.assDate();
          
          pData_Provider_Example->setDate("300","sDate",sDateWrite);
          pData_Provider_Example->showContent();

          cout << endl << endl<< "Read sDate " << endl;

          sDate sDateRead = pData_Provider_Example->getDate("300","sDate");

          cout << sDateRead.year 
               << sDateRead.month
               << sDateRead.day
               << endl;



          break;

        }
        case 8:
        {
          std::string DataKey;
//          cout << "insert Data Key" << endl;
//          cin >> DataKey;

          DataKey   = pData_Provider_Example->generateDataKey(DataKey.c_str());

          // test validation rules for interface data

          pData_Provider_Example->Validator.loadRule("","","<","50","60");
          pData_Provider_Example->Validator.loadRule("","",">=","100","80");
          pData_Provider_Example->Validator.loadRule("","",">=","200","40");

          pData_Provider_Example->setLong((DataKey).c_str(),"LongValue1",20);
          pData_Provider_Example->setLong((DataKey).c_str(),"LongValue1",40);
          pData_Provider_Example->setLong((DataKey).c_str(),"LongValue1",60);
          pData_Provider_Example->setLong((DataKey).c_str(),"LongValue1",80);
          pData_Provider_Example->setLong((DataKey).c_str(),"LongValue1",100);
          pData_Provider_Example->setLong((DataKey).c_str(),"LongValue1",200);
          pData_Provider_Example->setLong((DataKey).c_str(),"LongValue1",220);

          pData_Provider_Example->showContent();

          break;

        }

        case 9:
        {
          std::string DataKey;
//          cout << "insert Data Key" << endl;
//          cin >> DataKey;

          DataKey   = pData_Provider_Example->generateDataKey(DataKey.c_str());

          // test validation rules for interface data

          pData_Provider_Example->setLong((DataKey).c_str(),"LongValue1",20);
          pData_Provider_Example->setLong((DataKey).c_str(),"LongValue2",40);
          pData_Provider_Example->setLong((DataKey).c_str(),"LongValue3",60);
          pData_Provider_Example->setLong((DataKey).c_str(),"LongValue4",80);
          pData_Provider_Example->setLong((DataKey).c_str(),"LongValue5",100);
          pData_Provider_Example->setLong((DataKey).c_str(),"LongValue6",200);
          pData_Provider_Example->setLong((DataKey).c_str(),"LongValue7",220);

          pData_Provider_Example->setString((DataKey).c_str(),"String","bla");


          for ( long i = 1 ; i < 2000; ++i)
          {
            cout << i << " " ; 
            std::string bla = pData_Provider_Example->getString(DataKey.c_str(),"String");


            Sleep(1);
            cout << endl ; 
          }


          pData_Provider_Example->showContent();

          break;

        }

     
        
        default:
          {
            input = 0;
            break;
          }

      }
    } while (input != 0);
    delete pCBS_StdFrame;
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
