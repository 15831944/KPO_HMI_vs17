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
#include "cCBS_StdFrame.h"
#include "cCBS_StdLog_Task.h"
#include "iSMC_DataDefinitions_s.hh"

#include "CSampleCode.h"
#include "CProductID.h"
#include "CSMC_FileLogHandler.h"

// use command line argument: -config $(XPACT_SMC)\cfg\Examples\FormattedID.ini


int main( int argc, const char *argv[], char *envp[] )
{

  try
  {
    // activate SMM Application Environment
    cCBS_StdFrame *pCBS_StdFrame = new cCBS_StdFrame(argc, argv);

    CSMC_FileLogHandler* pSMC_FileLogHandler = new CSMC_FileLogHandler();
    pCBS_StdFrame->registerLogHandler(pSMC_FileLogHandler);

    // run the application / CORBA
    pCBS_StdFrame->runAsClient();

    cCBS_StdLog_Task::getInstance()->traceLevel(9);

    long input = 1;

    do 
    {
      cout << "Input : " << endl;
      cout << "0 for exit" << endl;
      cout << "1 set Sample Data " << endl;
      cout << "2 set Product Data " << endl;
      cin >> input;

      switch (input)
      {
        case 1:
        {
          CSampleCode SampleCode;

          std::string ProbeType = "10";
          std::string PlantID = "DS_2";
          std::string ProcessStage = "3";
          std::string Format = "PPSTTCC";

          long Counter = 1;

          std::cout << "ProbeType " << ProbeType << std::endl;
          std::cout << "PlantID " << PlantID << std::endl;
          std::cout << "ProcessStage " << ProcessStage << std::endl;
          std::cout << "Counter " << Counter << std::endl;
          std::cout << "Format " << Format << std::endl;

          SampleCode.setFormat(Format);


          std::cout << SampleCode.getSampleCode(ProbeType,PlantID,ProcessStage,Counter) << std::endl;

          break;

        }

        case 2:
        {
          CProductID Product;

          std::string ProductID;
          std::string HeatID;
          std::string TreatID;
          std::string Format;
          std::string PlantID;

          std::cout << "input ProductID :";
          std::cin >> ProductID;
          std::cout << "input HeatID :";
          std::cin >> HeatID;
          std::cout << "input TreatID :";
          std::cin >> TreatID;
          std::cout << "input PlantID :";
          std::cin >> PlantID;
          std::cout << "input Format :";
          std::cin >> Format;


          std::cout << "ProductID " << ProductID << std::endl;
          std::cout << "HeatID " << HeatID << std::endl;
          std::cout << "TreatID " << TreatID << std::endl;
          std::cout << "PlantID " << PlantID << std::endl;

          std::cout << "Format " << Format << std::endl;

          Product.setFormat(Format);

          std::cout << Product.getValidProductID(ProductID,HeatID,TreatID,PlantID) << std::endl;

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
