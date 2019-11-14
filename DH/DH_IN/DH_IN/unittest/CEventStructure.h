#pragma once
#include "cCBS_StdLog_Task.h"
#include "TinyXml.h"

class CEventStructure
{
public:

  CEventStructure(void);  

  CEventStructure(std::string EventDefs_FileName);
  
  ~CEventStructure(void);

  //read structure of event
  bool ReadEventStructure(const std::string& SheetName);

  //try to open File with name "FileName"
  bool FileExists(std::string FileName);

  void log(const std::string& Message, long Level);

  //////////////////////////////////////  Get functions  /////////////////////////////////////
  std::string getL2_VarName(unsigned int index);
  std::string getL2_VarType(unsigned int index);
  std::string getL2_VarAimValue(unsigned int index);
  std::string getTel_ElemName(unsigned int index);
  std::string getRecValue(unsigned int index);
  std::string getTelegram_Name(void);
  std::string getComment(unsigned int index);
  int getNumOfMappingRules();
  bool getXML_Text(TiXmlElement *Cell, std::string& value);
  std::string getActEventName(void);
  std::string getDefs_FileName(void);

  void setActEventName(const std::string &e_name);
  void showEventDesc(void);
  void clearEventDesc(void);     // clears container with Mappingrules

private:

  struct MappingRule             // Description structure, describes the Eventstructures   
  {
    std::string L2_VarName;      // L2 variable name

    std::string L2_VarType;      // L2 variable type

    std::string L2_VarAimValue;  // L2 variable aim value

    std::string Tel_ElemName;    // Telegram element name

    std::string RecValue;        // Telegram element value
    
    std::string Telegram_Name;   // Telegram name

    std::string Comment;         // Comment
  };
  
  map<std::string, std::vector<MappingRule> > EventDesc; // containt Eventnames and Mappingrules

  std::string EventName;          // Current Eventname

  std::string Defs_FileName;      // Filename for xml-document with event definitions 

  TiXmlDocument EventDefsXml;     // event definitions xml-document, describes the Eventstructures 
};
