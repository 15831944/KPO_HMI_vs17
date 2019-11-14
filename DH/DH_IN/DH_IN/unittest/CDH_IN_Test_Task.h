#ifndef _INC_CDH_IN_Test_Task_INCLUDED
#define _INC_CDH_IN_Test_Task_INCLUDED

#include <fstream>
#include "CDH_Task.h"
#include "iDH_Interface_s.hh"
#include "iDH_Telcom_s.hh"
#include "Telcom_in_s.hh"
#include "TinyXml.h"
#include "CPP_HEAT_PLANT.h"
#include "CEventMessage.h"

#include "CEventStructure.h"

class CDH_IN_Test_Task : public CDH_Task
{
private:
  static CDH_IN_Test_Task *m_Instance;

  DH::iDH_Interface_var pDH_Interface;

  DH_Telcom::iDH_Telcom_var pDH_Telcom;

  CPP_HEAT_PLANT* m_pPP_Heat_Plant;

  TiXmlDocument doc; //document with description of telegram

  CEventStructure* EventStructure; // Class to handle event structure

  long TracingLevel;

  enum Trace {NO_MESSAGES, SHORT_ERRORS, ERRORS, FREE3, FREE4, SHORT_ALL, ALL, FREE7, FREE8, FREE9};

  std::string SheetName;//the worksheet to be used within the XML file event structure

  std::string InterfaceName;
  
  struct ElementDescription                // Description structure, content the description of telegram element 
  {
    std::string Name; //attribute "name" from Xml-file with telegram definitions
    
    int Count; //attribute "count" from Xml-file with telegram definitions

    std::string Type; //attribute "type" from Xml-file with telegram definitions

    std::string Unit; //attribute "unit" from Xml-file with telegram definitions

    int Multiplier; //part of attribute "unit" from Xml-file with telegram definitions
  };

  std::vector<ElementDescription> XmlElements; //Telegram elements from Xml-file

  std::vector<ElementDescription>::iterator XmlElem_it; //Telegram element description

  std::stringstream OutputStream;
  
  CDH_IN_Test_Task();

  void CleanTlgVars();

  // reads telegram structure from Xml-Node (names of vars, counts, multiplier...)
  bool ResolveElemDescription(TiXmlElement *Node);

  // find given Xml-Node 
  TiXmlElement* findRecord(std::string ElementName);

  //check one mapping rule
  bool checkMappingRule(std::string L2_VarValue, int MapPosition, std::string Tel_ElemValue);

  //check in mapping rule predefined value, 
  //return:
  //       -1 if received value isn'n equal to predefined
  //        0 if received value is equal to predefined
  //
  //        else if predefined value is multiple, return position that conforms with the received value
  //        for eg: predefined is "a|b|c" received is "b" --> return 2
  int checkPredefinition(std::string Predefined, std::string Received, int pos = 0);

  // Error reporting subsystem
  void ReportError(std::string ErrorMessage);

  void PrintMessage();
    
  void TestFailed();

  void TestOK();

  virtual void setCORBAConnections();
  
  virtual bool initialize();

  //handle error message and terminate the program
  void exitHandler(std::string ErrorMsg);

public:
  DH::iDH_Interface_var getDHInterface();

  DH_Telcom::iDH_Telcom_var getDHTelcom();

  static CDH_IN_Test_Task* getInstance();

  ~CDH_IN_Test_Task();

  long getTracingLevel(void);

  void setTracingLevel(long TraceLvl);

  std::string getSheetName(void);

  bool setSheetName(std::string Sh_Name);

  bool TestMain(CEventMessage &evMessage);

  //main init function
  void InitTest(void);

  //compares telegram code in szn with the telegram code of received event
  //this functions also takes care of time measurement. No match => no test
  bool MatchTelegram(std::string EventMsg);
};

#endif //_INC_CDH_IN_Task_INCLUDED
