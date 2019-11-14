#include "cCBS_StdEvent_Task.h"
#include "CDH_IN_Test_EventHandler.h"
#include "CIntfData.h"
#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"
#include "CDH_IN_Test_Task.h"
#include "TinyXml.h"

#define __FFL__  __FILE__, __FUNCTION__, __LINE__
///////////////////////////////////////////////////////////////////////////////////////
// some macros to save editing time
///////////////////////////////////////////////////////////////////////////////////////
#if defined (GETOPER)
#undef GETOPER
#endif
#if defined (GET_DH_OUT)
#undef GET_DH_OUT
#endif

#define GETOPER(name) get##name

#define GET_DH_OUT(type, DataName)\
  DH_Interface_Out->GETOPER(type)(key.c_str(), DATA::DataName)


CDH_IN_Test_Task* CDH_IN_Test_Task::m_Instance = 0;

CDH_IN_Test_Task::CDH_IN_Test_Task()
: pDH_Interface(0)
, EventStructure(0)
, m_pPP_Heat_Plant(0)
{
  try
  {
    InitTest();
    m_pPP_Heat_Plant = new CPP_HEAT_PLANT(getConnection()); 
  }
  catch(const cCBS_Exception &e)
  {
    std::cout << std::endl << "CBS exception caught : " << e << std::endl;
  }
}//CDH_IN_Test_Task::CDH_IN_Test_Task()

CDH_IN_Test_Task::~CDH_IN_Test_Task()
{
  if(EventStructure) delete EventStructure;
  if (m_pPP_Heat_Plant) {delete m_pPP_Heat_Plant; m_pPP_Heat_Plant = 0;}
}

CDH_IN_Test_Task* CDH_IN_Test_Task::getInstance()
{
	if ( m_Instance == 0 )
	{
		m_Instance = new CDH_IN_Test_Task();
	}
	return m_Instance;
}

bool CDH_IN_Test_Task::initialize()
{
  bool ret = false;
  ret = CDH_Task::initialize();

  cCBS_StdEvent_Task *pEvent_Task = cCBS_StdEvent_Task::getInstance();
  CDH_IN_Test_EventHandler *eh = new CDH_IN_Test_EventHandler();

  pEvent_Task->registerEventHandler(eh);
  return ret;
}

void CDH_IN_Test_Task::setCORBAConnections()
{
  cCorbaProxyAdapter<DH::iDH_Interface>* DHProxy;
  cCorbaProxyAdapter<DH_Telcom::iDH_Telcom>* DHTelcomProxy ; 
  DHProxy = new cCorbaProxyAdapter<DH::iDH_Interface>();
  DHTelcomProxy = new cCorbaProxyAdapter<DH_Telcom::iDH_Telcom>();
  

  cCBS_StdCORBA_Task* pCORBA_Task = cCBS_StdCORBA_Task::getInstance();

  if (pCORBA_Task)
  {
    //***************************************************************************
    std::string Server         = "DH_Server";
    std::string ServerTask     = "DH_ServerTask";
    std::string ServerTaskPOA  = "DH_ServerPOA";
    std::string DH_Out    = "DH_Interface";

    cCBS_StdInitBase::getInstance()->replaceWithEntry("DataHandler", "ServerName", Server);
    cCBS_StdInitBase::getInstance()->replaceWithEntry(Server, "ServerTask", ServerTask);
    cCBS_StdInitBase::getInstance()->replaceWithEntry(Server, "ServerTaskPOA", ServerTaskPOA);
    cCBS_StdInitBase::getInstance()->replaceWithEntry(Server, "DHOutIntf", DH_Out);

    std::string DH_In = "DH_Telcom";
    cCBS_StdInitBase::getInstance()->replaceWithEntry(Server, "DHInIntf", DH_In);

    pCORBA_Task->registerProxy(DHProxy, DH_Out, ServerTask, ServerTaskPOA);
    pCORBA_Task->registerProxy(DHTelcomProxy, DH_In, ServerTask, ServerTaskPOA);

    pCORBA_Task->connectAllProxies();

    pDH_Interface = DHProxy->getObjRef();
    pDH_Telcom    = DHTelcomProxy->getObjRef();
  }
}

DH::iDH_Interface_var CDH_IN_Test_Task::getDHInterface()
{
  return pDH_Interface;
}
DH_Telcom::iDH_Telcom_var CDH_IN_Test_Task::getDHTelcom()
{
  return pDH_Telcom;
}



void CDH_IN_Test_Task::PrintMessage()
{
  if (OutputStream.str()!="")
  {
    std::cout << OutputStream.str();
    std::cout<< "\n------------------------------"; // footer
    OutputStream.str(""); // flush   
  }
}

void CDH_IN_Test_Task::TestOK() // This message has fixed tracing level = 6
{
  if (TracingLevel > SHORT_ALL)
  {
    OutputStream << "\nTest OK!";
  }   
}
void CDH_IN_Test_Task::TestFailed() // This message has fixed tracing level = 2
{
  if (TracingLevel > NO_MESSAGES)
  {
    OutputStream << "\nTest FAILED!";  
  }
}

bool CDH_IN_Test_Task::ResolveElemDescription(TiXmlElement *Node)
{
  bool RetValue = true;

  ElementDescription Elem_Desc;
  std::stringstream tmp_stream;
  char* Xml_Value = 0;
  if(!Node)
  {
    log("\nERROR: No Xml-Node to resolve element description received!\n", 1);
    return false;
  }
  
  Node = Node->FirstChildElement("element");
  //Read structure
  while (Node)
  {
    // if element is not user defined 
    if(!Node->FirstChildElement()->NextSiblingElement("userDefined"))
    {
      tmp_stream.clear();
      Xml_Value = (char *)Node->Attribute("name");
      if(Xml_Value)
        Elem_Desc.Name = Xml_Value;
      else
      {
        tmp_stream << "\nERROR: Attribute \"name\" is not found in Xml-Node :\"" << Node->Value() << "\"!\n";
        log(tmp_stream.str(), 1);
        RetValue = false;
      }

      //std::cout << "\nElem_Desc.Name: " << Elem_Desc.Name;

      Xml_Value = (char *)Node->Attribute("count");
      if(Xml_Value)
      {
        tmp_stream << Xml_Value;
        tmp_stream >> Elem_Desc.Count;
      }
      else
      {
        tmp_stream << "\nERROR: Attribute \"count\" is not found in Xml-Node :\"" << Node->Value() << "\"!\n";
        log(tmp_stream.str(), 1);
        RetValue = false;
      }

      if(Elem_Desc.Count == 0)
      {
        log("\nERROR: attribute \"count\", from Xml-file with telegram definitions, for Name:\"" + Elem_Desc.Name + "\" is 0!", 1);
        RetValue = false;
      }
      
      if(Node->FirstChildElement()->NextSiblingElement("primitive"))
      {
        Xml_Value = (char *)Node->FirstChildElement()->NextSiblingElement("primitive")->Attribute("appType");
        if(Xml_Value)
          Elem_Desc.Type = Xml_Value;
        else
        {
          tmp_stream << "\nERROR: Attribute \"appType\" is not found in Xml-Node :\"" 
                     << Node->FirstChildElement()->NextSiblingElement("primitive")->Value() << "\"!\n";
          log(tmp_stream.str(), 1);
          RetValue = false;
        }

        Xml_Value  = (char *)Node->FirstChildElement()->NextSiblingElement("primitive")->Attribute("unit");
        if(Xml_Value)
          Elem_Desc.Unit = Xml_Value;
        else
        {
          tmp_stream << "\nERROR: Attribute \"unit\" is not found in Xml-Node :\"" 
                     << Node->FirstChildElement()->NextSiblingElement("primitive")->Value() << "\"!\n";
          log(tmp_stream.str(), 1);
          RetValue = false;
        }

        if (!Elem_Desc.Unit.empty())
        {
          size_t start = 0;
          size_t start1=0;
          size_t end = 0;
          char numbers[] = {'1','2','3','4','5','6','7','8','9','0'};
          start1 = Elem_Desc.Unit.find_first_of('*',0);
          start = Elem_Desc.Unit.find_first_of(numbers, start1, sizeof(numbers));
          end = Elem_Desc.Unit.find_first_not_of(numbers, start1+1, sizeof(numbers));

          if (start < end)
          {
            tmp_stream.clear();
            tmp_stream << Elem_Desc.Unit.substr(start, (end - start));
            tmp_stream >> Elem_Desc.Multiplier;
          }
          else
            Elem_Desc.Multiplier = 1;
        }
      }
      else
      {
        Elem_Desc.Type = "";
        Elem_Desc.Unit = "";
      }
      XmlElements.push_back(Elem_Desc);
    }
    else// if element is user defined, call itself recursive 
      ResolveElemDescription(findRecord(Node->FirstChildElement()->NextSiblingElement("userDefined")->Attribute("name")));
    
    Node = Node->NextSiblingElement("element");
  }
  return RetValue;
}

TiXmlElement* CDH_IN_Test_Task::findRecord(std::string ElementName)
{
  TiXmlElement *Node;
  if(ElementName.empty())
  {
    log("ERROR: Received element name is empty, cann not search for Xml-Node!",1);
    return 0;
  }

  Node = doc.FirstChildElement();
  if(!Node)
    return Node;
  Node = Node->FirstChildElement();

  //find node with name == ElementName
  while(Node)
  {
    if(Node->Attribute("name") != 0 && ElementName == Node->Attribute("name"))
      break;
    Node = Node->NextSiblingElement();
  }

  //find record
  if(Node->FirstChildElement())
  {
    while(Node && !Node->FirstChildElement("record"))
    {
      Node = Node->FirstChildElement();
      //if no child node, search one
      while(Node && !Node->FirstChildElement())
        Node = Node->NextSiblingElement();
    }
  }
  if(Node)
    Node = Node->FirstChildElement("record");
  return Node;
}

void CDH_IN_Test_Task::CleanTlgVars()
{
  XmlElements.clear();
}

bool CDH_IN_Test_Task::TestMain(CEventMessage &evMessage)
{
  bool RetValue = true;
  DH::iDH_Interface_var DH_Interface_Out = getDHInterface();
  DH_Telcom::iDH_Telcom_var DH_Telcom = getDHTelcom();

  XmlElem_it = XmlElements.begin(); //telegram element description
  std::string key = evMessage.getDataKey();

  //std::string TelegramName = EventStructure->getTelegram_Name();// current telegram name
  
  std::stringstream Tel_ElemValue;
  std::stringstream L2_VarValue;

  std::string HeatID = "";
  std::string TreatID = "";

  std::string HeatID_Cust = "";
  std::string TreatID_Cust = "";

  //loop over mapping rules for received telegram
  for (int MapPosition = 0; MapPosition < EventStructure->getNumOfMappingRules(); MapPosition++)
  {
    //reset variables
    XmlElem_it = XmlElements.begin();
    Tel_ElemValue.str("");
    L2_VarValue.str("");
    Tel_ElemValue.clear();
    L2_VarValue.clear();
    OutputStream.str("");
    OutputStream.clear();

    //search for description of telegram element 
    while((XmlElem_it != XmlElements.end()) && 
          (XmlElem_it->Name != EventStructure->getTel_ElemName(MapPosition)))
    {
      XmlElem_it++;
    }
    if (XmlElem_it == XmlElements.end() && EventStructure->getTel_ElemName(MapPosition) != "-")
    {
      std::cout << "\n\tWarning. Variable \"" << EventStructure->getTel_ElemName(MapPosition) 
                << "\" was not found in \"" << doc.Value() << "\" telegram definitions!\n"
                << "\tTEST FAILED.\n===========================\n ";
      RetValue = false;
      continue;
    }

    if(HeatID.empty() || TreatID.empty())
    {
      if(EventStructure->getL2_VarName(MapPosition) == "HeatID")
      {
        HeatID = DH_Interface_Out->getString(key.c_str(), DATA::HeatID);
        if(!HeatID.empty() && HeatID != DEF::Inv_String)
          log("WARNING: HeatID should not be setted in DH interface.",2);
          
        HeatID = evMessage.getHeatID();

        HeatID_Cust = DH_Telcom->getString(EventStructure->getTelegram_Name().c_str(), XmlElem_it->Name.c_str());
        continue;
      }
      else if(EventStructure->getL2_VarName(MapPosition) == "TreatID")
      {
        TreatID = DH_Interface_Out->getString(key.c_str(), DATA::TreatID);
        if(!TreatID.empty() && TreatID != DEF::Inv_String)
          log("WARNING: TreatID should not be setted in DH interface.", 2);
          
        TreatID = evMessage.getTreatID();

        TreatID_Cust = DH_Telcom->getString(EventStructure->getTelegram_Name().c_str(), XmlElem_it->Name.c_str());
        continue;
      }
    } 

    OutputStream << "\n|========================================================================================|";
    OutputStream << "\n\tTest of mapping rules for L2 Variable: \"" << EventStructure->getL2_VarName(MapPosition) << "\"";
    if(XmlElem_it != XmlElements.end())
      OutputStream << " and Telegram Element: \"" << XmlElem_it->Name << "\"";
    OutputStream << std::endl;
    log(OutputStream.str(), 1);

    if(EventStructure->getL2_VarType(MapPosition) == "-" || EventStructure->getL2_VarType(MapPosition).empty())
    {
      if(EventStructure->getL2_VarName(MapPosition) != "-" && !EventStructure->getL2_VarName(MapPosition).empty())
      {
        log("ERROR: no type for L2 variable in mapping rules defined!", 1);
      }

      if(XmlElem_it != XmlElements.end())
      {
        if(EventStructure->getTel_ElemName(MapPosition) != "-" && !(EventStructure->getTel_ElemName(MapPosition)).empty())
          Tel_ElemValue << DH_Telcom->getString(EventStructure->getTelegram_Name().c_str(), XmlElem_it->Name.c_str());
        //aim value for Telegramm element predefined?
        if(EventStructure->getRecValue(MapPosition) != "-" && !EventStructure->getRecValue(MapPosition).empty())
        {
          std::cout << "\n\tTelegram element has predifined value: " << EventStructure->getRecValue(MapPosition);
          if(EventStructure->getRecValue(MapPosition) == Tel_ElemValue.str())
            log("\n\tPredifined and received values are equal", 3);
          else
            log("\n\tERROR: Predifined value is \"" + EventStructure->getRecValue(MapPosition) + 
                "\" but received: \"" + Tel_ElemValue.str() + "\"", 1);
        }//value for Telegramm element is predefinedx 
      }//XmlElem_it != XmlElements.end()      
    }//if(L2_VarType == "-" || empty)
    else if(EventStructure->getL2_VarType(MapPosition) == "string" || EventStructure->getL2_VarType(MapPosition) == "long"
     ||EventStructure->getL2_VarType(MapPosition) == "double" || EventStructure->getL2_VarType(MapPosition) == "bool"
     ||EventStructure->getL2_VarType(MapPosition) == "sDate")
    {
      if(EventStructure->getL2_VarType(MapPosition) != "sDate")
      {
        L2_VarValue << DH_Interface_Out->getString(key.c_str(), EventStructure->getL2_VarName(MapPosition).c_str());
        if(EventStructure->getTel_ElemName(MapPosition) != "-" && !(EventStructure->getTel_ElemName(MapPosition)).empty())
          Tel_ElemValue << DH_Telcom->getString(EventStructure->getTelegram_Name().c_str(), XmlElem_it->Name.c_str());
      }
      else
      {
        CDateTime DH_Time_Out;
        DH_Time_Out.SetTime(DH_Interface_Out->getDate(key.c_str(), EventStructure->getL2_VarName(MapPosition).c_str()));
        L2_VarValue << DH_Time_Out;
        if(EventStructure->getTel_ElemName(MapPosition) != "-" && !(EventStructure->getTel_ElemName(MapPosition)).empty())
        {
          CORBA::Any DateTime = *DH_Telcom->getAny(EventStructure->getTelegram_Name().c_str(), XmlElem_it->Name.c_str());
          CDateTime DH_Time_In(DateTime);
          Tel_ElemValue << DH_Time_In;
        }
      }//L2_VarType(i) == "sDate"

      checkMappingRule(L2_VarValue.str(), MapPosition, Tel_ElemValue.str());

    }//if(L2_VarType == string || long || double || bool || sDate)
    else if(EventStructure->getL2_VarType(MapPosition) == "seqComputerModes")
    {
      seqComputerModes ComputerModes;
      sComputerMode Mode;
      int PointPos = 0;
      
      PointPos = EventStructure->getL2_VarName(MapPosition).find_first_of(".");
      if(PointPos == -1)
      {
        log("\n\tWARNING: L2 Variable: \"" + EventStructure->getL2_VarName(MapPosition) + "\" couldn't be tested!!!", 2);
        log("\tVariable name must take the form of ComputerModes.\"DeviceName\"", 2);
        std::cout << "\n|========================================================================================|\n";
        continue;
      }

      std::string Name = EventStructure->getL2_VarName(MapPosition).substr(0, PointPos);
      std::string Device = EventStructure->getL2_VarName(MapPosition).substr(PointPos + 1);
      std::transform(Device.begin(), Device.end(), Device.begin(), tolower);

      ComputerModes = *DH_Interface_Out->getComputerModes(key.c_str(), Name.c_str());
      if(EventStructure->getTel_ElemName(MapPosition) != "-" && !(EventStructure->getTel_ElemName(MapPosition)).empty())
        Tel_ElemValue << DH_Telcom->getString(EventStructure->getTelegram_Name().c_str(), XmlElem_it->Name.c_str());

      for(int ii = 0; ii < CIntfData::getLength(ComputerModes); ii++)
      {
        CIntfData::getAt(Mode, ComputerModes, ii);
        std::string tmpDevice = Mode.Device;
        std::transform(tmpDevice.begin(), tmpDevice.end(), tmpDevice.begin(), tolower);

        if(tmpDevice == Device)
        {
          L2_VarValue << Mode.Status;
        }
      }

      if(L2_VarValue.str().empty())
      {
        log("\n\tERROR: No status for computerdevice \"" + EventStructure->getTel_ElemName(MapPosition) + "\"", 1);
        continue;
      }

      checkMappingRule(L2_VarValue.str(), MapPosition, Tel_ElemValue.str());

    }//else if(L2_VarType(i) == "seqComputerModes")
    else if(EventStructure->getL2_VarType(MapPosition) == "seqGasData")
    {
      seqGasData SeqGasData;
      sGasData   GasData;
      int PointPos = 0;

      PointPos = EventStructure->getL2_VarName(MapPosition).find_first_of(".");
      if(PointPos == -1)
      {
        log("\n\tWARNING: L2 Variable: \"" + EventStructure->getL2_VarName(MapPosition) + "\" couldn't be tested!!!", 2);
        log("\tVariable name must take the form of StirrAmount.\"GasValue\" or StirrAmount.\"GasType\"", 2);
        std::cout << "\n|========================================================================================|\n";
        continue;
      }
      std::string Name = EventStructure->getL2_VarName(MapPosition).substr(0, PointPos);

      std::string GasAttr = EventStructure->getL2_VarName(MapPosition).substr(PointPos + 1);
      std::transform(GasAttr.begin(), GasAttr.end(), GasAttr.begin(), tolower);

      SeqGasData = *DH_Interface_Out->getGasData(key.c_str(), Name.c_str());
      if(EventStructure->getTel_ElemName(MapPosition) != "-" && !(EventStructure->getTel_ElemName(MapPosition)).empty())
        Tel_ElemValue << DH_Telcom->getString(EventStructure->getTelegram_Name().c_str(), XmlElem_it->Name.c_str());

      CIntfData::getAt(GasData, SeqGasData, 0);
      if(GasAttr == "gastype")
      {
        L2_VarValue << GasData.GasType;
      }
      else if(GasAttr == "gasvalue")
      {
        L2_VarValue << GasData.GasValue;
      }

      if(L2_VarValue.str().empty())
      {
        log("\n\tERROR: no value for L2 variable: \"" + EventStructure->getL2_VarName(MapPosition) + "\" received!", 1);
        continue;
      }

      checkMappingRule(L2_VarValue.str(), MapPosition, Tel_ElemValue.str());
    }//if(L2_VarType == "seqGasData")
    else if(EventStructure->getL2_VarType(MapPosition) == "seqCoolWaterData")
    {
      seqCoolWaterData SeqCoolWaterData;
      sCoolWaterDevice SCoolWaterDevice;
      int PointPos = 0;

      //find position of first Point in variable name 
      PointPos = EventStructure->getL2_VarName(MapPosition).find_first_of(".");
      if(PointPos == -1)
      {
        log("\n\tWARNING: L2 Variable: \"" + EventStructure->getL2_VarName(MapPosition) + "\" couldn't be tested!!!", 2);
        log("\tVariable name must take the form of CoolingWaterData.\"DeviceName\".\"WaterData\"", 2);
        std::cout << "\n|========================================================================================|\n";
        continue;
      }
      std::string Name = EventStructure->getL2_VarName(MapPosition).substr(0, PointPos);
      
      std::string Device = EventStructure->getL2_VarName(MapPosition).substr(PointPos + 1);
      Device = Device.substr(0, Device.find_first_of("."));
      std::transform(Device.begin(), Device.end(), Device.begin(), tolower);
      
      //find position of second Point in variable name 
      PointPos = EventStructure->getL2_VarName(MapPosition).find_first_of(".", PointPos + 1);

      if(PointPos == -1)
      {
        log("\n\tWARNING: L2 Variable: \"" + EventStructure->getL2_VarName(MapPosition) + "\" couldn't be tested!!!", 2);
        log("\tVariable name must take the form of CoolingWaterData.\"DeviceName\".\"WaterData\"", 2);
        std::cout << "\n|========================================================================================|\n";
        continue;
      }
      
      std::string WaterData = EventStructure->getL2_VarName(MapPosition).substr(PointPos + 1);
      std::transform(WaterData.begin(), WaterData.end(), WaterData.begin(), tolower);
      
      SeqCoolWaterData = *DH_Interface_Out->getCoolWaterData(key.c_str(), Name.c_str());
      if(EventStructure->getTel_ElemName(MapPosition) != "-" && !(EventStructure->getTel_ElemName(MapPosition)).empty())
        Tel_ElemValue << DH_Telcom->getLong(EventStructure->getTelegram_Name().c_str(), XmlElem_it->Name.c_str());


      for(int ii = 0; ii < CIntfData::getLength(SeqCoolWaterData); ii++)
      {
        CIntfData::getAt(SCoolWaterDevice, SeqCoolWaterData, ii);
        std::string tmpDevice = SCoolWaterDevice.CoolWaterDevice;
        std::transform(tmpDevice.begin(), tmpDevice.end(), tmpDevice.begin(), tolower);

        if(tmpDevice == Device)
        {
          //log("\n\tDevice: \"" + Device + "\" for CoolWaterData found!", 3);
          if(WaterData == "inlettemp")  
            L2_VarValue << SCoolWaterDevice.CoolWaterData.InletTemp;
          else if(WaterData == "outlettemp")
            L2_VarValue << SCoolWaterDevice.CoolWaterData.OutletTemp;
          else if(WaterData == "waterflow")
            L2_VarValue << SCoolWaterDevice.CoolWaterData.WaterFlow;
          break;
        }
      }

      if(L2_VarValue.str().empty())
      {
        log("\n\tERROR: no value for L2 variable: \"" + EventStructure->getL2_VarName(MapPosition) + "\" received!", 1);
        continue;
      }

      checkMappingRule(L2_VarValue.str(), MapPosition, Tel_ElemValue.str());

    }//if(L2_VarType == "seqCoolWaterData")
    else if(EventStructure->getL2_VarType(MapPosition) == "seqStirringData")
    {
      // NOT TESTED!!!
      seqStirringData SeqStirringData;
      sStirringData StirringData;
      int PointPos = 0;

      //find position of first Point in variable name 
      PointPos = EventStructure->getL2_VarName(MapPosition).find_first_of(".");
      if(PointPos == -1)
      {
        log("\n\tWARNING: L2 Variable: \"" + EventStructure->getL2_VarName(MapPosition) + "\" couldn't be tested!!!", 2);
        log("\tVariable name must take the form of SeqStirringData.\"DeviceName\".\"GasType\"", 2);
        std::cout << "\n|========================================================================================|\n";
        continue;
      }
      std::string Name = EventStructure->getL2_VarName(MapPosition).substr(0, PointPos);
      
      std::string Device = EventStructure->getL2_VarName(MapPosition).substr(PointPos + 1);
      Device = Device.substr(0, Device.find_first_of("."));
      std::transform(Device.begin(), Device.end(), Device.begin(), tolower);
      
      //find position of second Point in variable name 
      PointPos = EventStructure->getL2_VarName(MapPosition).find_first_of(".", PointPos + 1);

      if(PointPos == -1)
      {
        log("\n\tWARNING: L2 Variable: \"" + EventStructure->getL2_VarName(MapPosition) + "\" couldn't be tested!!!", 2);
        log("\tVariable name must take the form of SeqStirringData.\"DeviceName\".\"GasValue\" or SeqStirringData.\"DeviceName\".\"GasType\"", 2);
        std::cout << "\n|========================================================================================|\n";
        continue;
      }
      
      std::string GasAttr = EventStructure->getL2_VarName(MapPosition).substr(PointPos + 1);
      std::transform(GasAttr.begin(), GasAttr.end(), GasAttr.begin(), tolower);
      
      SeqStirringData = *DH_Interface_Out->getStirringData(key.c_str(), Name.c_str());
      if(EventStructure->getTel_ElemName(MapPosition) != "-" && !(EventStructure->getTel_ElemName(MapPosition)).empty())
        Tel_ElemValue << DH_Telcom->getLong(EventStructure->getTelegram_Name().c_str(), XmlElem_it->Name.c_str());


      for(int ii = 0; ii < CIntfData::getLength(SeqStirringData); ii++)
      {
        CIntfData::getAt(StirringData, SeqStirringData, ii);
        std::string tmpDevice = StirringData.Device;
        std::transform(tmpDevice.begin(), tmpDevice.end(), tmpDevice.begin(), tolower);

        if(tmpDevice == Device)
        {
          seqGasData SeqGasData = StirringData.GasData;
          sGasData GasData;

          CIntfData::getAt(GasData, SeqGasData, 0);
          if(GasAttr == "gastype")
          {
            L2_VarValue << GasData.GasType;
          }
          else if(GasAttr == "gasvalue")
          {
            L2_VarValue << GasData.GasValue;
          }
          else
            log("\n\tERROR: In mapping rule! Attribute \"" + GasAttr + "\" is not in sGasData structure defined!", 1);
          break;
        }//if(tmpDevice == Device)
      }//for(int ii = 0; ii < CIntfData::getLength(SeqStirringData); ii++)

      if(L2_VarValue.str().empty())
      {
        log("\n\tERROR: no value for L2 variable: \"" + EventStructure->getL2_VarName(MapPosition) + "\" received!", 1);
        continue;
      }

      checkMappingRule(L2_VarValue.str(), MapPosition, Tel_ElemValue.str());

    }//else if(getL2_VarType == "seqStirringData")
    else if(EventStructure->getL2_VarType(MapPosition) == "seqBatch")
    {
      seqBatch SeqBatch;
      sBatch   Batch;
      DEF::seqLong *longMaterialsSeq;      
      CORBA::Any theMaterialsAny;

      int PointPos = 0;

      PointPos = EventStructure->getL2_VarName(MapPosition).find_first_of(".");
      if(PointPos == -1)
      {
        log("\n\tWARNING: L2 Variable: \"" + EventStructure->getL2_VarName(MapPosition) + "\" couldn't be tested!!!", 2);
        log("\tVariable name must take the form of RecipeContent.\"MatCode\" or RecipeContent.\"Mass\" or RecipeContent.\"MatFeedSpeed\"", 2);
        std::cout << "\n|========================================================================================|\n";
        continue;
      }
      std::string L2_VarName = EventStructure->getL2_VarName(MapPosition).substr(0, PointPos);
      
      std::string Material = EventStructure->getL2_VarName(MapPosition).substr(PointPos + 1);
      std::transform(Material.begin(), Material.end(), Material.begin(), tolower);

      SeqBatch = *DH_Interface_Out->getBatch(key.c_str(), L2_VarName.c_str());

      if(EventStructure->getTel_ElemName(MapPosition) != "-" && !(EventStructure->getTel_ElemName(MapPosition)).empty())
      {
        if(Material == "matfeedspeed")
        {
          CIntfData::getAt(Batch, SeqBatch, 0);
          L2_VarValue << Batch.MatFeedSpeed;

          Tel_ElemValue << DH_Telcom->getLong(EventStructure->getTelegram_Name().c_str(), XmlElem_it->Name.c_str());
          checkMappingRule(L2_VarValue.str(), MapPosition, Tel_ElemValue.str());
          std::cout << "\n|========================================================================================|\n";
          continue;
        }
        //Read matirials from telcom interface, this is a sequence and it contains all info. about mat.
        theMaterialsAny = *DH_Telcom->getAny(EventStructure->getTelegram_Name().c_str(), XmlElem_it->Name.c_str());
        theMaterialsAny >>= longMaterialsSeq;
      }

      if(SeqBatch.length() == (longMaterialsSeq->length() / 2))
      {
        for(int i = 0; i < CIntfData::getLength(SeqBatch); i++)
        {
          Tel_ElemValue.str("");
          Tel_ElemValue.clear();

          Tel_ElemValue << i;
          log("-------------------", 9);
          log("\n\tTest sturcture " + Tel_ElemValue.str() + " in the sequence seqBatch", 3);

          Tel_ElemValue.str("");
          L2_VarValue.str("");
          Tel_ElemValue.clear();
          L2_VarValue.clear();
          
          CIntfData::getAt(Batch, SeqBatch, i);

          if(Material == "matcode")
          {
            L2_VarValue << Batch.MatCode;
            Tel_ElemValue << (*longMaterialsSeq)[i*2];
            checkMappingRule(L2_VarValue.str(), MapPosition, Tel_ElemValue.str());
          }
          else if(Material == "mass")
          {
            L2_VarValue << Batch.Mass;
            Tel_ElemValue << (*longMaterialsSeq)[i*2+1];
            checkMappingRule(L2_VarValue.str(), MapPosition, Tel_ElemValue.str());
          }
          else if(Material == "matfeedspeed")
          {
            //L2_VarValue << Batch.MatFeedSpeed;
            //Tel_ElemValue << DH_Telcom->getLong(EventStructure->getTelegram_Name().c_str(), Telegram_LFL260::FeedingRate);
            //checkMappingRule(L2_VarValue.str(), MapPosition, Tel_ElemValue.str());
            break;
          }
          else
          {
            log("\n\tERROR: Unknown element of Batch structure: " + Material, 1);
            break;
          }
        }//for(int i = 0; i < CIntfData::getLength(SeqBatch); i++)
      }
      else
        log("\n\tERROR: Length of SeqBatch must be equal length of Material/2", 1); // ???
      
    }//if(getL2_VarType(i) == "seqBatch")
    else if(EventStructure->getL2_VarType(MapPosition) == "seqStatus")
    {
    // NOT TESTED!!!!!!!!!!!!
      seqStatus SeqStatus;
      sStatus   Status;
      int PointPos = 0;

      PointPos = EventStructure->getL2_VarName(MapPosition).find_first_of(".");
      if(PointPos == -1)
      {
        log("\n\tWARNING: L2 Variable: \"" + EventStructure->getL2_VarName(MapPosition) + "\" couldn't be tested!!!", 2);
        log("\tVariable name must take the form of SeqStatus.\"Device\"", 2);
        std::cout << "\n|========================================================================================|\n";
        continue;
      }
      std::string Name = EventStructure->getL2_VarName(MapPosition).substr(0, PointPos);

      std::string Device = EventStructure->getL2_VarName(MapPosition).substr(PointPos + 1);
      std::transform(Device.begin(), Device.end(), Device.begin(), tolower);

      SeqStatus = *DH_Interface_Out->getStatus(key.c_str(), Name.c_str());

      if(EventStructure->getTel_ElemName(MapPosition) != "-" && !(EventStructure->getTel_ElemName(MapPosition)).empty())
        Tel_ElemValue << DH_Telcom->getString(EventStructure->getTelegram_Name().c_str(), XmlElem_it->Name.c_str());

      for(int ii = 0; ii < CIntfData::getLength(SeqStatus); ii++)
      {
        CIntfData::getAt(Status, SeqStatus, ii);
        std::string tmpDevice = Status.Device;
        std::transform(tmpDevice.begin(), tmpDevice.end(), tmpDevice.begin(), tolower);

        if(tmpDevice == Device)
        {
          L2_VarValue << Status.Status;
          break;
        }
      }

      if(L2_VarValue.str().empty())
      {
        log("\n\tERROR: no value for L2 variable: \"" + EventStructure->getL2_VarName(MapPosition) + "\" received!", 1);
        continue;
      }

      checkMappingRule(L2_VarValue.str(), MapPosition, Tel_ElemValue.str());
    }//if(L2_VarType == "seqStatus")
    std::cout << "\n|========================================================================================|\n";
  }//for (int i = 0; i < EventStructure->getNumOfMappingRules(); i++)

  //special test for HeatID and TreatID
  if(!HeatID.empty() && !TreatID.empty())
  {  
    if (m_pPP_Heat_Plant)
    {
      if (m_pPP_Heat_Plant->selectByCustData(HeatID_Cust, TreatID_Cust, SheetName))
      {
        log("\n\tSelect from PP_HEAT_PLANT for TREATID_CUST: \"" + TreatID_Cust + 
            "\" and HEATID_CUST: \"" + HeatID_Cust + "\" is successful", 2);
        if (m_pPP_Heat_Plant->getLastRow() > 1)
        {
          log("\n\tWARNING: Multiple rows selected from PP_HEAT_PLANT for TREATID_CUST: \"" + TreatID_Cust +
              "\" and HEATID_CUST: \"" + HeatID_Cust + "\"", 2);
        }
        if ((m_pPP_Heat_Plant->getHEATID(1)== HeatID)
          &&(m_pPP_Heat_Plant->getTREATID(1)== TreatID))
        {
          log("\n\tHeatID: \"" + HeatID + "\" and TreatID: \"" + TreatID + "\" in PP_HEAT_PLANT are equal to received from event message.", 3);
        }
        else
        {
          log("\n\tERROR:HeatID: \"" + HeatID + "\" and TreatID: \"" + TreatID + "\" in PP_HEAT_PLANT are not equal to received from event message.", 3);
          RetValue = false;
        }
      }
      else
      {
        log("\n\tSelect from PP_HEAT_PLANT for TREATID_CUST: \"" + TreatID_Cust + 
            "\" and HEATID_CUST: \"" + HeatID_Cust + "\" is failed", 2);
        RetValue = false;
      }
    }
    else
    {
      log("ERROR: PP_Heat_Plant is NULL!", 1);
      RetValue = false;
    }
  }

  return RetValue;
}

bool CDH_IN_Test_Task::checkMappingRule(std::string L2_VarValue, int MapPosition, std::string Tel_ElemValue)
{
  bool RetValue = true;
  std::string AimValue;
  int AimValPos = 0;

  if(L2_VarValue != Tel_ElemValue)
  {
    log("\n\tWARNING: Values of Telegram variable and of L2 variable are not equal!", 2);
    log("\tL2 value: \"" + L2_VarValue + "\"\tTelegram value: \"" + Tel_ElemValue + "\"\n", 2);
    log("\n\t------------------- CHECK FOR PREDEFINITIONS -------------------", 2);
    //if L2 varible name is not empty
    if(EventStructure->getL2_VarName(MapPosition) != "-" && !EventStructure->getL2_VarName(MapPosition).empty())
    {
      AimValue = EventStructure->getL2_VarAimValue(MapPosition);
      //value for L2 variable is predefined?
      if(AimValue != "-" && !AimValue.empty())
      {
        log("\n\tL2 variable has predefined value: " + AimValue, 3);
        AimValPos = checkPredefinition(AimValue, L2_VarValue);
        if(AimValPos != -1)
          log("\n\tPredifined and received values are equal", 3);
        else
        {
          log("\n\tERROR: Predifined value is \"" + AimValue + 
              "\" but received: \"" + L2_VarValue + "\"", 1);
          RetValue = false;
        }
      }
      else if(XmlElem_it == XmlElements.end())
      {
        log("\n\tERROR: L2 Variable: \"" + EventStructure->getL2_VarName(MapPosition) + "\" hasn't predefined value and no equal Telegram Value", 2);
      }
      else
      {
        //log("\n\tERROR: Value of \"" + EventStructure->getL2_VarName(MapPosition) + "\" = " +
        //    L2_VarValue + " is not equal to value of \"" + XmlElem_it->Name + "\" = " + 
        //    Tel_ElemValue, 1);
        log("\n\tERROR: Value are not equal and are not predefined!", 1);
        RetValue = false;
      }//no predefined value for L2 variable
    }//L2 varible name is not empty

    //if Telegram varible name is not empty
    if(EventStructure->getTel_ElemName(MapPosition) != "-" && !EventStructure->getTel_ElemName(MapPosition).empty())
    {
      AimValue = EventStructure->getRecValue(MapPosition);
      //value for Telegram variable is predefined?
      if(AimValue != "-" && !AimValue.empty())
      {
        log("\n\tTelegram element has predifined value: " + EventStructure->getRecValue(MapPosition), 3);
        AimValPos = checkPredefinition(AimValue, Tel_ElemValue, AimValPos);
        if(AimValPos != -1)
          log("\n\tPredifined and received values are equal", 3);
        else
        {
          log("\n\tERROR: Predifined value is \"" + AimValue + 
              "\" but received: \"" + Tel_ElemValue + "\"", 1);
          RetValue = false;
        }
      }
      else if(RetValue)
      {
        log("\n\tERROR: Value of telegram element is not predefined and is not equal to value of L2 variable!", 1);
        RetValue = false;
      }//no predefined value for telegram variable
    }//Telegram varible name is not empty
    else

  log("\n\t----------------------------------------------------------------", 2);
  }//if values are not equal
  else
    log("\n\tValues are equal: " + L2_VarValue, 3);

  return RetValue;
}//bool checkMappingRule(std::string L2_VarValue, int MapPosition, std::string Tel_ElemValue)

int CDH_IN_Test_Task::checkPredefinition(std::string Predefined, std::string Received, int pos)
{
  int ValPos = 1;

  //if predefined value has multiple entrys
  while(Predefined.find_first_of("|") != -1)
  {
    if(Received != Predefined.substr(0, Predefined.find_first_of("|")))
    {
      ValPos++;
      Predefined = Predefined.substr(Predefined.find_first_of("|") + 1);
    }
    else if(pos != 0 && pos != ValPos)
    {
      log("\n\tWARNING: Order of values in predefined variable is corrupt!", 2);
      return ValPos;
    }
    else
      return ValPos;
  }//while(!Predefined.find_first_of("|"))

  if(Received == Predefined)
  {
    if(pos != 0 && pos != ValPos)
      log("\n\tWARNING: Order of values in predefined variable is corrupt!", 2);
    if(ValPos == 1)
      ValPos = 0;
    return ValPos;
  }
  else
    return -1;
}

bool CDH_IN_Test_Task::MatchTelegram(std::string EventMsg)
{
  bool RetValue = true;
  
  CleanTlgVars(); // Prepare to read new telegram

  EventStructure->setActEventName(EventMsg);

  if(!ResolveElemDescription(findRecord(EventStructure->getTelegram_Name())))
  {
    OutputStream << "\nERROR: Read telegram element description from \"" << doc.Value() << "\" failed!";
    log(OutputStream.str(), 1);
    RetValue = false;
  }
  
  return RetValue;
} // end of function

//Initialize/Reset of test values
void  CDH_IN_Test_Task::InitTest(void)
{
  std::string In_Xml;
  std::string Directory = "";
  std::string LoadFile = ""; 
  TracingLevel = 9;
  SheetName = "";

  cCBS_StdInitBase::getInstance()->replaceWithEntry("SimulatorArguments", "RootDir", Directory);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("SimulatorArguments", "EventDifinitions", LoadFile);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("SimulatorArguments", "SheetName", SheetName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("TRACING", "TraceLevel", TracingLevel);

  if(SheetName == "")
  {
    if(TracingLevel >= SHORT_ALL)
      std::cout << "\nWARNING: SheetName is not set in ini-file! Use default SheetName -> LF !\n";
    SheetName = "LF";
  }

  if(Directory == "")
    exitHandler("ERROR: Root directory (RootDir) is not defined in ini-file!");

  if(LoadFile == "")
    exitHandler("ERROR: Filename for EventDifinitions is not defined in ini-file!");

  if(EventStructure)
    delete EventStructure;
  EventStructure = 0;
  EventStructure = new CEventStructure(Directory + LoadFile);
  EventStructure->ReadEventStructure(SheetName);

  cCBS_StdInitBase::getInstance()->replaceWithEntry("SimulatorArguments", "Xml", In_Xml);

  // program will be terminated, if no file with telegram definitions found  
  doc.LoadFile(Directory + In_Xml);
  if(doc.Error())
    exitHandler("ERROR: failed to load \"" + Directory + In_Xml + "\"");

  if(!doc.FirstChildElement()->Attribute("name"))
    exitHandler("ERROR: no interface name in \"" + Directory + In_Xml + "\"");

  InterfaceName = doc.FirstChildElement()->Attribute("name");
  std::cout << "\nInterface name: \"" + InterfaceName + "\"\n";

  std::cout<< "\nTest Initialization OK!\n";
}//InitTest(string NextSzn)

//Handle error message and exit the program with status -1
void CDH_IN_Test_Task::exitHandler(std::string ErrorMsg)
{
  ErrorMsg = "\n" + ErrorMsg + "\nProgram will be terminated!!\n";
  log(ErrorMsg, 1);
  //std::cout << "Program will be terminated!! Please press ENTER to exit!\n";
  //getchar();
  exit(-1);
}

long CDH_IN_Test_Task::getTracingLevel(void)
{
  return TracingLevel;
}

void CDH_IN_Test_Task::setTracingLevel(long TraceLvl)
{
  TracingLevel = TraceLvl;
}

std::string CDH_IN_Test_Task::getSheetName(void)
{
  //EventStructure->showEventDesc();
  return SheetName;
}

bool CDH_IN_Test_Task::setSheetName(std::string Sh_Name)
{
  bool RetValue = false;

  EventStructure->clearEventDesc(); // clear container with Mappingrules

  if(EventStructure->ReadEventStructure(Sh_Name))
  {  
    SheetName = Sh_Name;
    RetValue = true;
  }
  return RetValue;
}
