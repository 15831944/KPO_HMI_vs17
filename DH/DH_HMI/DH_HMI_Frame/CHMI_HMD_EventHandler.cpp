// Copyright (C) 2011 SMS Demag AG

#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"
#include "CSMC_DataProvider_Impl.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdLog_Task.h"
#include "CEventMessage.h"
#include "CHMI_EventHandler.h"
#include "CDH_HMI_Task.h"
#include "CPP_HEAT.h"


#include "CHMI_HMD_EventHandler.h"

bool CHMI_HMD_EventHandler::handleEvent(CEventMessage& evMessage)
{
  bool RetValue = false;

  std::string Message = evMessage.getMessage();
  std::string HeatID    = evMessage.getHeatID();
  std::string ProductID = evMessage.getProductID();
  std::string PlantID    = evMessage.getPlantID();

  log(evMessage,3);       
	CSMC_DataProvider_Impl* pDH_Interface = CDH_HMI_Task::getInstance()->getpInterface_OUT();
	pDH_Interface->showContent(evMessage.getDataKey(),3);

  // events from L2 (DM or TSM) to HMI !
  // do not forward to DM again !
  // copy data for respective Product !
  if ( Message == HMI_EvMsg::evHMIUpdateDialogueData )
  {
    RetValue = copyDMData(evMessage);
  }
  // send refresh trigger to HMI
  else if (Message.find("RDY") != Message.npos)
  {
    //HMI checks only the receiver which should be equal "HMI", message content is not important
    RetValue = dispatchEvent(m_SenderName,"HMI",evMessage);
  }
  // events from HMI to L2
  // forward to DM !
  else 
  {
    if ( Message == HMD_EvMsg::evHMDChangeAimData                    ||
         Message == HMD_EvMsg::evHMDChangeProdPracPointerRestriction ||
         Message == HMD_EvMsg::evHMDChangeProdPracPointerParameter   ||
         Message == HMD_EvMsg::evHMDHandleUpdatePurpose              ||
         Message == HMD_EvMsg::evHMDChangeProdPracPointerRestriction ||
         Message == HMD_EvMsg::evHMDParameterUpdate                  ||
         Message == HMD_EvMsg::evHMDUpdateAimDepartureTime           ||
         Message == HMD_EvMsg::evHMDChangePhysicalMatAvailibility    ||
         Message == HMD_EvMsg::evHMDPlantStatus                      ||
         Message == HMD_EvMsg::evHMDHeatScheduleUpdate               )
    {
      // make event to PlantEvent if no Heat Information is available
      if( HeatID.empty() )
      {
        evMessage.setPlantEvent(true);
        log("Event modified to PlantEvent, on Event: " + Message,3);       
      }
    }
  
    changeMissingEventDataHMD(evMessage);//SARS
    RetValue = dispatchEvent(m_SenderName,"",evMessage);

  }

  return RetValue;
}

CHMI_HMD_EventHandler::CHMI_HMD_EventHandler(std::string& ServerName)
{
  m_SenderName = ServerName;
}

CHMI_HMD_EventHandler::~CHMI_HMD_EventHandler()
{
	// TODO: Add your specialized code here.
}

bool CHMI_HMD_EventHandler::copyDMData(CEventMessage& Event, const std::string& Name, const std::string& Key)
{
	bool RetValue = true;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  " - ";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  Event.getDataKey();
  Action +=  " - ";
  Action +=  Key;
  Action +=  " - ";
  Action +=  Name;

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
        pDM_Interface = m_pDHTask->getpDM_Interface(ServerName,DM::PRODUCT);
        pDH_Interface = m_pDHTask->getpInterface_OUT();

			  if ( pDM_Interface && pDH_Interface )
			  {
				  // copy data from external interface to DataInterface
          // read external data at DM with datakey ProductID
          // write data with datakey ProductID
				  CIntfData::copyIntfData<DM::iDM_Interface_var>
					  (pDM_Interface,pDH_Interface,ProductID,ProductID,Name);

				  pDH_Interface->showContent(ProductID, 4);
			  }
        else
        {
          std::string Message = Action + " ERROR : invalid interface detected !";
          log(Message,3);
        }
      }
      else
      {
        std::string Message = Action + " ERROR : invalid ProductID detected !";
        log(Message,3);
      }
      // ************************************************
      // copy PLANT data
      // ************************************************
      if (!PlantID.empty() && PlantID != DEF::Inv_String)
      {
        pDM_Interface = m_pDHTask->getpDM_Interface(ServerName,DM::PLANT);

			  if ( pDM_Interface && pDH_Interface )
			  {
				  // copy data from external interface to DataInterface
          // read external data at DM with datakey DEF_PLANT::Furnace
          // write data with datakey PlantID
				  CIntfData::copyIntfData<DM::iDM_Interface_var>
            (pDM_Interface,pDH_Interface,DEF_PLANT::Furnace,PlantID,Name);

				  pDH_Interface->showContent(PlantID, 4);
			  }
        else
        {
          std::string Message = Action + " ERROR : invalid interface detected !";
          log(Message,3);
        }
      }
      else
      {
        std::string Message = Action + " ERROR : invalid PlantID detected !";
        log(Message,3);
      }
	  }
	}

  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc,
                                                                "CHMI_HMD_EventHandler::copyProductEventData",
                                                                Action);
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc,
                                                          "CHMI_HMD_EventHandler::copyProductEventData",
                                                          Action);
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException("CHMI_HMD_EventHandler::copyProductEventData",
                                                     Action);
	}

	return RetValue;
}