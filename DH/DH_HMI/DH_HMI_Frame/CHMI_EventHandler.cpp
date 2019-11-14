// Copyright (C) 2006 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"
#include "CSMC_DataProvider_Impl.h"

#include "CHMI_EventHandler.h"
#include "cCBS_StdLog_Task.h"
#include "CDH_HMI_Task.h"

//##ModelId=4586739B010A
CHMI_EventHandler::~CHMI_EventHandler()
{
}

//##ModelId=4586739B00EC
CHMI_EventHandler::CHMI_EventHandler()
: m_pPP_HEAT(0)
, m_pPD_HEAT_PLANT_REF(0)
, m_pGC_Plant_Container(0)
, m_pPP_HM(0)
{
  cCBS_StdConnection* pDBConnection = CDH_HMI_Task::getInstance()->getStdConnection();

  if (pDBConnection)
  {
    m_pPP_HEAT              = new CPP_HEAT(pDBConnection);
    m_pPD_HEAT_PLANT_REF    = new CPD_HEAT_PLANT_REF(pDBConnection);
    m_pGC_Plant_Container  = new CGC_Plant_Container(pDBConnection);
    m_pPP_HM               = new CPP_HM(pDBConnection);
  }

  // predefine valid transmitter, per default HMI sends with sender "HMI"
  m_TransmitterList.push_back("HMI");
}

//##ModelId=4586739B013C
bool CHMI_EventHandler::changeMissingEventData(CEventMessage& Event)
{
  bool RetValue = true;

  std::string DataKey     = Event.getDataKey();
  std::string HeatID      = Event.getHeatID();
  std::string TreatID     = Event.getTreatID();
  std::string OrderID     = Event.getOrderID();
  std::string PlantID     = Event.getPlantID();
  std::string ActPlant    = m_pGC_Plant_Container->getPlant(Event.getPlantID());
  long ActPlantNo         = m_pGC_Plant_Container->getPlantNo(Event.getPlantID());


  if ( OrderID.empty() && !HeatID.empty())
  {
    if ( m_pPP_HEAT && m_pPP_HEAT->select(HeatID) )
    {
      OrderID = m_pPP_HEAT->getPRODORDERID(1);
      Event.setOrderID(OrderID);
      cCBS_StdLog_Task::getInstance()->log("INFO: Using OrderID from DB : " + OrderID, 3);
    }
  }

  CSMC_DataProvider_Impl* pDH_Interface = CDH_HMI_Task::getInstance()->getpInterface_OUT();

  if (pDH_Interface)
  {
    // external heat information is needed for event logs in tracker

    std::string HeatIDCust  = pDH_Interface->getString(DataKey,DATA::CustHeatID);
    std::string TreatIDCust = pDH_Interface->getString(DataKey,DATA::CustTreatID);

    if ( (HeatIDCust == DEF::Inv_String || HeatIDCust.empty()) && !HeatID.empty() && !TreatID.empty())
    {
      // more than one row is possible. But that is O.K. because independent of plant
      // the pare of internal and external heat data are the same.
      if ( m_pPD_HEAT_PLANT_REF && m_pPD_HEAT_PLANT_REF->select(HeatID, TreatID, ActPlant) )
      {
        HeatIDCust  = m_pPD_HEAT_PLANT_REF->getHEATID_CUST(1);
        TreatIDCust = m_pPD_HEAT_PLANT_REF->getTREATID_CUST(1);

        std::string Message;
        Message = "INFO: Using from DB HeatIDCust: " + HeatIDCust;
        Message += ", TreatIDCust: " + TreatIDCust;

        cCBS_StdLog_Task::getInstance()->log(Message, 3);

        pDH_Interface->setString(DataKey,DATA::CustHeatID, HeatIDCust);
        pDH_Interface->setString(DataKey,DATA::CustTreatID, TreatIDCust);
      }
      else
        cCBS_StdLog_Task::getInstance()->log("ERROR: select customer heat from PD_HEAT_PLANT_REF!",1);
    }

    // it happens that HMI or DB doesn't set heatid in PP_HEAT.
    // if order still empty get it by cust heatid
    if (OrderID.empty())
    {
      if (!HeatIDCust.empty() && HeatIDCust != DEF::Inv_String)
      {
        if (m_pPP_HEAT && m_pPP_HEAT->select(HeatIDCust))
        {
          OrderID = m_pPP_HEAT->getPRODORDERID(1);
          Event.setOrderID(OrderID);
          cCBS_StdLog_Task::getInstance()->log("Take OrderID from DB",3);
        }
      }
    }

  }
  else
  {
    cCBS_StdLog_Task::getInstance()->log("ERROR: CHMI_EventHandler::changeMissingEventData: pDH_Interface is 0!",1);
  }

  return RetValue;
}

bool CHMI_EventHandler::changeMissingEventDataHMD(CEventMessage& Event) //SARS
{
  bool RetValue = true;

  std::string DataKey     = Event.getDataKey();
  std::string HeatID      = Event.getHeatID();
  std::string TreatID     = Event.getTreatID();
  std::string OrderID     = Event.getOrderID();
  std::string PlantID     = Event.getPlantID();
  std::string ActPlant    = m_pGC_Plant_Container->getPlant(Event.getPlantID());
  long ActPlantNo         = m_pGC_Plant_Container->getPlantNo(Event.getPlantID());


  if ( OrderID.empty() && !HeatID.empty())
  {
    if ( m_pPP_HM && m_pPP_HM->select(HeatID) )
    {
      OrderID = m_pPP_HM->getPRODORDERID(1);
      Event.setOrderID(OrderID);
      cCBS_StdLog_Task::getInstance()->log("INFO: Using OrderID from DB : " + OrderID, 3);
    }
  }

  CSMC_DataProvider_Impl* pDH_Interface = CDH_HMI_Task::getInstance()->getpInterface_OUT();

  if (pDH_Interface)
  {
    // external heat information is needed for event logs in tracker

    std::string HeatIDCust  = pDH_Interface->getString(DataKey,DATA::CustHeatID);
    std::string TreatIDCust = pDH_Interface->getString(DataKey,DATA::CustTreatID);

    if ( (HeatIDCust == DEF::Inv_String || HeatIDCust.empty()) && !HeatID.empty() && !TreatID.empty())
    {
      // more than one row is possible. But that is O.K. because independent of plant
      // the pare of internal and external heat data are the same.
      if ( m_pPP_HM && m_pPP_HM->select(HeatID) )
      {
        HeatIDCust  = m_pPP_HM->getHM_ID_CUST_PLAN(1);
        TreatIDCust = "01";

        std::string Message;
        Message = "INFO: Using from DB HeatIDCust: " + HeatIDCust;
        Message += ", TreatIDCust: " + TreatIDCust;

        cCBS_StdLog_Task::getInstance()->log(Message, 3);

        pDH_Interface->setString(DataKey,DATA::CustHeatID, HeatIDCust);
        pDH_Interface->setString(DataKey,DATA::CustTreatID, TreatIDCust);
      }
      else
        cCBS_StdLog_Task::getInstance()->log("ERROR: select customer heat from PD_HEAT_PLANT_REF!",1);
    }

    // it happens that HMI or DB doesn't set heatid in PP_HEAT.
    // if order still empty get it by cust heatid
    if (OrderID.empty())
    {
      if (!HeatIDCust.empty() && HeatIDCust != DEF::Inv_String)
      {
        if (m_pPP_HM && m_pPP_HM->select(HeatIDCust))
        {
          OrderID = m_pPP_HM->getPRODORDERID(1);
          Event.setOrderID(OrderID);
          cCBS_StdLog_Task::getInstance()->log("Take OrderID from DB",3);
        }
      }
    }

  }
  else
  {
    cCBS_StdLog_Task::getInstance()->log("ERROR: CHMI_EventHandler::changeMissingEventData: pDH_Interface is 0!",1);
  }

  return RetValue;
}

bool CHMI_EventHandler::copyDMData(CEventMessage& Event, std::vector<std::string>& NameList, const std::string& Key)
{
	bool RetValue = false;

  std::string NewDataKey = generateDataKey(Event,Key);

  std::string DataKey = Event.getDataKey();
	std::vector<std:: string>::iterator itNames;

	for (itNames = NameList.begin() ; itNames != NameList.end() ; ++ itNames)
	{
	  if (!(*itNames).empty()) 
	  {
      // copy data always for the same datakey !
      Event.setDataKey(DataKey);
      // store data always unde the same datakey !
	    RetValue = copyDMData(Event,(*itNames),NewDataKey);
	    if ( RetValue == false )
	    {
	      break;
	    }
	  }
	}

	return RetValue;
}


bool CHMI_EventHandler::copyDMData(CEventMessage& Event, const std::string& Name, const std::string& Key)
{
	bool RetValue = true;

  std::string Action;
	try
	{
	  std::string ProductID        = Event.getProductID();
	  std::string DataKey          = Event.getDataKey();
    std::string ServerName       = Event.getSender();
	  std::string PlantID          = Event.getPlantID();

    DM::iDM_Interface_var   pDM_Interface  = 0;
    CSMC_DataProvider_Impl* pDH_Interface = 0;

		if( m_pDHTask )
		{
      // ************************************************
      // copy PRODUCT data
      // ************************************************
      if (!ProductID.empty() && ProductID != DEF::Inv_String)
      {
        Action = "get DM_Interface DM::PRODUCT and Interface_OUT";

        pDM_Interface = m_pDHTask->getpDM_Interface(ServerName,DM::PRODUCT);
        pDH_Interface = m_pDHTask->getpInterface_OUT();

			  if ( pDM_Interface && pDH_Interface )
			  {
          Action = "copy product data";
				  // copy data from external interface to DataInterface
          // read external data at DM with datakey ProductID
          // write data with datakey ProductID
				  CIntfData::copyIntfData<DM::iDM_Interface_var>
					  (pDM_Interface,pDH_Interface,ProductID,ProductID,getRequestedDataList(ProductID,Name));

				  pDH_Interface->showContent(ProductID,4);
			  }
        else
        {
          log("pointer not initialized. (pDM_Interface && pDH_Interface)", 3);
        }
      }
      else
      {
        log("No ProductID in event!",3);
      }
      // ************************************************
      // copy PLANT data
      // ************************************************
      if (!PlantID.empty() && PlantID != DEF::Inv_String)
      {
        Action = "get DM_Interface DM::PLANT";

        pDM_Interface = m_pDHTask->getpDM_Interface(ServerName,DM::PLANT);
        pDH_Interface = m_pDHTask->getpInterface_OUT();

			  if ( pDM_Interface && pDH_Interface )
			  {
          Action = "copy plant data";
				  // copy data from external interface to DataInterface
          // read external data at DM with datakey DEF_PLANT::Furnace
          // write data with datakey PlantID
          std::vector<std::string>RequestedDataList = getRequestedDataList(PlantID,Name);

				  CIntfData::copyIntfData<DM::iDM_Interface_var>
            (pDM_Interface,pDH_Interface,DEF_PLANT::Furnace,PlantID,RequestedDataList);

				  pDH_Interface->showContent(PlantID,4);
			  }
        else
        {
          std::string Message = Action + " ERROR : ( pDM_Interface && pDH_Interface ) !";
          log(Message,1);
        }
      }
      else
      {
        std::string Message = Action + "No PlantID in event";
        log(Message,3);
      }
	  }
	}

  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc,
                                                                "CHMI_EventHandler::copyDMData",
                                                                Action);
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc,
                                                          "CHMI_EventHandler::copyDMData",
                                                          Action);
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException("CHMI_EventHandler::copyDMData",
                                                     Action);
	}

	return RetValue;
}

// returns list of requested data names from Data_Provider or inserts Name as default
std::vector<std::string> CHMI_EventHandler::getRequestedDataList(const std::string& Key, const std::string& Name)
{
  std::vector<std::string>   NameList;

  CSMC_DataProvider_Impl* pDH_Interface = m_pDHTask->getpInterface_OUT();
  if (pDH_Interface)
  {
    std::set<std::string>::iterator it;
    std::set<std::string> IntfReqList = pDH_Interface->getIntfReqList(Key);

    if ( IntfReqList.size() > 0 )
    {
      std::string ReqData = "REQUESTED DATA FROM HMI FOR KEY : " + Key + " : ";

      for ( it = IntfReqList.begin() ; it != IntfReqList.end(); ++it )
      {
        NameList.push_back(*it);
        ReqData += *it + ", ";
      }
      
      if ( IntfReqList.find(Name) != IntfReqList.end())
      {
        log(Name + " is not yet in requested list. Add to list", 4);
        NameList.push_back(Name);
        ReqData += Name + ", ";
      }

      log(ReqData, 3);
    }
    else
    {
      if ( !Name.empty() )
      {
        NameList.push_back(Name);
      }
    }
  }

  return NameList;
}
