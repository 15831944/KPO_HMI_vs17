#include "CEventStructure.h"

CEventStructure::CEventStructure(void)
{
}

CEventStructure::CEventStructure(std::string EventDefs_FileName)
{
  if(FileExists(EventDefs_FileName))
  {
    Defs_FileName = EventDefs_FileName;
    EventDefsXml.LoadFile(EventDefs_FileName);
  }
  else
  {
    // program will be terminated, if no file with event definitions found
    log("ERROR: Cannot open " + EventDefs_FileName + " to read!",1);
    log("Program will be terminated!!",1);
    exit(-1);
  }
}

CEventStructure::~CEventStructure(void)
{
}

void CEventStructure::log(const std::string& Message, long Level)
{
  cCBS_StdLog_Task::getInstance()->log(Message, Level);
}


bool CEventStructure::FileExists(std::string FileName)
{
  bool RetValue = true;
  FILE* FileToOpen = NULL;
  
  FileToOpen = fopen(FileName.c_str(),"r"); // try to open
  
  if(!FileToOpen)
    return false;

  fclose(FileToOpen);
  FileToOpen = NULL;

  return RetValue;
}

bool CEventStructure::ReadEventStructure(const std::string& SheetName)
{
  int index = -1;
  TiXmlElement *ActNode;
  TiXmlElement *ActCell;
  std::string   XmlText;

  ActNode = EventDefsXml.FirstChildElement();  // first child of the document... should be workbook

  ActNode = ActNode->FirstChildElement("Worksheet"); 
  if (!ActNode)
  {  
    log("No worksheet found, XLS/XML file corrupted", 1);
    return false;
  }

  // SheetName search
  while(ActNode->Attribute("ss:Name") != SheetName)
  {
    ActNode = ActNode->NextSiblingElement();
    if(!ActNode)
    {
      log("No worksheet for " + SheetName + " found, XLS/XML file corrupted\n",1); 
      return false;
    }
  }

  ActNode = ActNode->FirstChildElement("Table");
  if (!ActNode)
  {
    log("No table found, XLS/XML file corrupted\n",1);
    return false;
  }

  ActNode = ActNode->FirstChildElement("Row");
  if (!ActNode)
  {
    log("No rows found, XLS/XML file corrupted\n",1);
    return false;
  }

  ActCell = ActNode->FirstChildElement("Cell");
  if (!ActCell)
  {
    log("No cells found, XLS/XML file corrupted\n",1);
    return false;
  }

  // read data for received SheetName
  while(ActNode = ActNode->NextSiblingElement("Row"))
  {
    ActCell = ActNode->FirstChildElement("Cell");
    // read Event Name 
    if (getXML_Text(ActCell, XmlText))
    {
      if(XmlText.length() > 2)
      {
        EventName = XmlText;
        index = -1; // reset index 
      }
      index++;
      EventDesc[EventName].resize(index + 1);
    }
    else
    {
      log("ERROR: No cell in section \"Event Message\"",1);
      return false;
    }
    
    //read L2 variable name
    ActCell = ActCell->NextSiblingElement("Cell");
    if (getXML_Text(ActCell, XmlText))
    {
      EventDesc[EventName][index].L2_VarName = XmlText;
    }
    else
    {
      log("ERROR: No cell in section \"L2 variable name\"",1);
      return false;
    }

    //read L2 variable type
    ActCell = ActCell->NextSiblingElement("Cell");
    if (getXML_Text(ActCell, XmlText))
    {
      EventDesc[EventName][index].L2_VarType = XmlText;
    }
    else
    {
      log("ERROR: No cell in section \"L2 variable type\"",1);
      return false;
    }

    //read L2 variable aim value
    ActCell = ActCell->NextSiblingElement("Cell");
    if (getXML_Text(ActCell, XmlText))
    {
      EventDesc[EventName][index].L2_VarAimValue = XmlText;
    }
    else
    {
      log("ERROR: No cell in section \"L2 variable aim value\"",1);
      return false;
    }

    //read Telegram element name
    ActCell = ActCell->NextSiblingElement("Cell");
    if (getXML_Text(ActCell, XmlText))
    {
      EventDesc[EventName][index].Tel_ElemName = XmlText;
    }
    else
    {
      log("ERROR: No cell in section \"Telegram element name\"",1);
      return false;
    }

    //read Telegram element value
    ActCell = ActCell->NextSiblingElement("Cell");
    if (getXML_Text(ActCell, XmlText))
    {
      EventDesc[EventName][index].RecValue = XmlText;
    }
    else
    {
      log("ERROR: No cell in section \"Telegram element value\"",1);
      return false;
    }

    //read Telegram name
    ActCell = ActCell->NextSiblingElement("Cell");
    if (getXML_Text(ActCell, XmlText))
    {
      if(XmlText == "-" && index > 0) //take last telegram name if received text is "-"
        EventDesc[EventName][index].Telegram_Name = EventDesc[EventName][index-1].Telegram_Name;
      else
        EventDesc[EventName][index].Telegram_Name = XmlText;
    }
    else
    {
      log("ERROR: No cell in section \"Telegram name\"",1);
      return false;
    }

    // read comments
    ActCell = ActCell->NextSiblingElement("Comments");
    if (getXML_Text(ActCell, XmlText))
    {
      EventDesc[EventName][index].Comment = XmlText;
    }
  }// end of while(ActNode = ActNode->NextSiblingElement("Row"))

  return true;
}// end of function ReadEventStructure

std::string CEventStructure::getL2_VarName(unsigned int index)
{
  if(index < EventDesc[EventName].size())
    return EventDesc[EventName][index].L2_VarName;
  
  log("ERROR in CEventStructure::getL2_VarName(index): Index is out of range, cannot get L2 variable name!",1);
  return "";
}

std::string CEventStructure::getL2_VarType(unsigned int index)
{
  if(index < EventDesc[EventName].size())
    return EventDesc[EventName][index].L2_VarType;

  log("ERROR in CEventStructure::getL2_VarType(index): Index is out of range, cannot get L2 variable type!",1);
  return "";
}

std::string CEventStructure::getL2_VarAimValue(unsigned int index)
{
  if(index < EventDesc[EventName].size())
    return EventDesc[EventName][index].L2_VarAimValue;

  log("ERROR in CEventStructure::getL2_VarAimValue(index): Index is out of range, cannot get L2 variable aim value!",1);
  return "";
}

std::string CEventStructure::getTel_ElemName(unsigned int index)
{
  if(index < EventDesc[EventName].size())
    return EventDesc[EventName][index].Tel_ElemName;

  log("ERROR in CEventStructure::getTel_ElemName(index): Index is out of range, cannot get Telegram element name!",1);
  return "";
}

std::string CEventStructure::getRecValue(unsigned int index)
{
  if(index < EventDesc[EventName].size())
    return EventDesc[EventName][index].RecValue;

  log("ERROR in CEventStructure::getRecValue(index): Index is out of range, cannot get Telegram element value!",1);
  return "";
}

std::string CEventStructure::getTelegram_Name()
{
  std::map< std::string, std::vector<MappingRule> >::iterator it = EventDesc.begin();

  while(it != EventDesc.end())
  {
    if(it->first == EventName)
      break;
    it++;
  }
  if(it != EventDesc.end())
    return EventDesc[EventName][0].Telegram_Name;

  log("ERROR in CEventStructure::getTelegram_Name: Event name \"" + EventName + "\" is not defined in mapping rules!",1);
  //log("ERROR in CEventStructure::getTelegram_Name: Cannot get Telegram name!",1);
  return "";
}

std::string CEventStructure::getComment(unsigned int index)
{
  if(index < EventDesc[EventName].size())
    return EventDesc[EventName][index].Comment;

  log("ERROR in CEventStructure::getComment(index): Index is out of range, cannot get Comment!",1);
  return "";
}

int CEventStructure::getNumOfMappingRules() 
{
  return EventDesc[EventName].size();
}

std::string CEventStructure::getActEventName(void)
{
  return EventName;
}

std::string CEventStructure::getDefs_FileName(void)
{
  return Defs_FileName;
}

void CEventStructure::setActEventName(const std::string &e_name)
{
  EventName = e_name;
  std::cout << "\nCurrent event name: " << EventName << std::endl;
}

bool CEventStructure::getXML_Text(TiXmlElement *Cell, std::string &_value)
{
  TiXmlElement *XmlData;
  if(Cell)
  {
    XmlData = Cell->FirstChildElement("Data");
    
    //if XmlData not empty only
    if(XmlData)
    {
      _value = XmlData->FirstChild()->ToText()->Value(); 
    }
    else
      _value = "-"; // <-- symbol for empty data
    return true;
  }
  else
    return false;
}

void CEventStructure::clearEventDesc(void)
{
  std::map<std::string, std::vector<MappingRule> >::iterator m_it = EventDesc.begin();

  for(m_it ; m_it != EventDesc.end(); m_it++)
  {
    m_it->second.clear();
  }  
  EventDesc.clear();
}

void CEventStructure::showEventDesc(void) 
{
  std::map<std::string, std::vector<MappingRule> >::iterator m_it = EventDesc.begin();
  std::vector<MappingRule> temp_v;
  std::vector<MappingRule>::iterator v_it;
  int count = 0;
  
  std::cout << "Event Message\t\t\tL2 VarName\tL2 VarType\tL2 VarAimValue\tTelElementName\tTelElementValue\tTelName\n";

  for(m_it ; m_it != EventDesc.end(); m_it++)
  {
    temp_v = m_it->second;
    std::cout << m_it->first << "\t" << temp_v[0].L2_VarName << "\t" << m_it->second[0].L2_VarType << "\t" << m_it->second[0].L2_VarAimValue << "\t" 
        << m_it->second[0].Tel_ElemName << "\t" << m_it->second[0].RecValue << "\t" << std::endl;

    count++;

    for(v_it = temp_v.begin() + 1 ; v_it != temp_v.end(); v_it++)
      std::cout << "-\t" << v_it->L2_VarName << "\t" << v_it->L2_VarType << "\t" << v_it->L2_VarAimValue << "\t" 
           << v_it->Tel_ElemName << "\t" << v_it->RecValue << "\t" << std::endl;
  }
  std::cout << "Number of events: " << count << std::endl;
}