#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <iostream>

using namespace std;

#include "CEventHandler.h"
#include "CEventMessage.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdFrame.h"

cCBS_StdInitBase *CreateInstance(int argc, const char **argv);

int main(int argc, const char **argv)
{

  try
  {

    cCBS_StdInitBase *pInitBAse = CreateInstance(argc, argv);

// Just for test the new environment
//    std::string tmp = pInitBAse->getXPact();
//    pInitBAse->replaceWithEntry("EventMessage", "SenderName", tmp);

    if(argc != 10)
    {
      std::cout << " usage: EventSender sender receiver message poductID relatedProductID isPlantEvent HeatID TreatID \n";
      std::cout << "        If relatedProductID is \"EMPTY\" an empty string is used in the event message\n";
      std::cout << "                      sender receiver Message               product relprod plantevent heat treat plant\n";
      std::cout << " example: EventSender DM_BOF TSM_BOF  BOF_HEAT_ANNOUNCEMENT 123456  EMPTY   0          HEAT TREAT BOF_1\n";
      return EXIT_FAILURE;
    }

    // activate SMC Application Environment
    cCBS_StdFrame *pFrame = new cCBS_StdFrame(argc, argv);

   // run the application / CORBA
    pFrame->runAsClient();

    std::string sender(argv[1]);
    std::string receiver(argv[2]);
    std::string msg(argv[3]);
    std::string productID(argv[4]);
    std::string relProductID(argv[5]);
    std::string plantEvent(argv[6]);
    std::string HeatID(argv[7]);
    std::string TreatID(argv[8]);
    std::string PlantID(argv[9]);

    bool isPlant = false;
    if(plantEvent.compare("1") == 0)
      isPlant = true;

    if (relProductID == "EMPTY") relProductID.erase();

    //CEventMessage(relatedKey, sender, receiver, message, bool isPlantEvent);
    CEventMessage message(sender, receiver, msg, productID, relProductID, isPlant);
    message.setHeatID(HeatID);
    message.setTreatID(TreatID);
    message.setPlantID(PlantID);
//    std::cout << "Send message: " << sender << "-> " << receiver
//              << " [" << msg << "] " << key << ", " << isPlant << std::endl;
    message.dispatch(sender,receiver);

    //delete pInitBAse;
    //delete pFrame;
  }
  catch(cCBS_Exception &Exc)
  {
    cout << Exc << endl;
  }
  catch(...)
  {
    cout << "exception caught "  << endl;
  }

  return EXIT_SUCCESS;
}

cCBS_StdInitBase *CreateInstance(int argc, const char **argv)
{
  // We define an artifical environment to have the abilitity to call the
  // the program mwithout the arguments " -config InifileName"

  char *res;
  std::string XPact;
  if ( (res = getenv("X-Pact")) != NULL)
  {
      XPact = res;
      if (XPact[XPact.length()-1] != '/')
      {
        XPact += '/';
      }
  }
  else
  {
    std::cerr << "Environment variable X-Pact not defined" << std::endl;
    exit(1);
  }

  std::string processName(*argv);
  processName.erase(0, processName.find_last_of('\\')+1 );
  std::string::size_type i = processName.find('.');
  if ( std::string::npos != i)
    processName.erase(i,processName.size());

  std::string iniFileName(XPact + "cfg/Tools/" + processName + ".ini");

  const int MAXLEN = 300;
  static char ProcName[MAXLEN];
  static char Config[] = "-config";
  static char ConfigFileName[MAXLEN];

  static char* newargv[3] = {ProcName, Config, ConfigFileName};

  if (processName.length() < MAXLEN && iniFileName.length() < MAXLEN)
  {
    strcpy(ProcName, *argv);
    strcpy(ConfigFileName, iniFileName.c_str());
    const int argc = 3;
    return new cCBS_StdInitBase(argc, newargv);
  }
  else
    return static_cast<cCBS_StdInitBase*>(0);
}