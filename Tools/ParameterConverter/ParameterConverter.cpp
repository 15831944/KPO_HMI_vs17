#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "cCBS_StdFrame.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdDB_Task.h"  

#include "CParamConverter.h"

// use config file e.g.: -config $(XPACT_SMC)\cfg\Tools\ParameterConverter.ini

int main(int argc, const char **argv)
{
  try
  {
    cCBS_StdFrame * pCBS_StdFrame = new cCBS_StdFrame(argc, argv);

    CParamConverter PC;

    long ParamCount = PC.ConvertParamTable();
    std::cout << "Processed parameter in " << PC.getSourceParamTableName() << ": " << ParamCount << std::endl;

    ParamCount = PC.ConvertParamMatrixTable();
    std::cout << "Processed parameter in " << PC.getSourceParamMatrixTableName() << ": " << ParamCount << std::endl;
//    pCBS_StdFrame->runAsClient();
  }
  catch(...)
  {
    std::cout << "Exception caught in main() !" << std::endl;
  }
  return 0;
}
