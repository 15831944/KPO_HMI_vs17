// Copyright (C) 2006 SMS Demag AG

#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"
#include "CSMC_DataProvider_Impl.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdLog_Task.h"
#include "CEventMessage.h"
#include "CHMI_EventHandler.h"
#include "CDH_HMI_Task.h"
#include "CPP_HEAT.h"

#include "CHMI_LF_EventHandler.h"


//##ModelId=458830080325
CHMI_LF_EventHandler::CHMI_LF_EventHandler(std::string& ServerName)
{
  m_SenderName = ServerName;
}

//##ModelId=4588300C0212
CHMI_LF_EventHandler::~CHMI_LF_EventHandler()
{

}

//##ModelId=4588300300A8
bool CHMI_LF_EventHandler::handleEvent(CEventMessage& evMessage)
{
  log("Class.CHMI_LF_EventHandler v.1.0.0", 3);

  bool RetValue = false;

  std::string Message   = evMessage.getMessage();
  std::string HeatID    = evMessage.getHeatID();
  std::string ProductID = evMessage.getProductID();

  log(evMessage, 3);       

  // events from L2 (DM or TSM)
  // do not forward to DM again !
  // copy data for respective Product !
  if ( Message == HMI_EvMsg::evHMIUpdateDialogueData )
  {
    RetValue = copyDMData(evMessage);
  }
  // this event is sent by Tracker on start up and is never stoped
  else if ( Message == HMI_EvMsg::evHMIUpdatePlantData )
  {
    evMessage.setProductID("");
    RetValue = copyDMData(evMessage);
  }
  else 
  {
    if ( checkTransmitter(evMessage) ) // trasmitterlist set with "HMI" as default 
    {
      if ( Message == LF_EvMsg::evLFChangeAimData                    ||
           Message == LF_EvMsg::evLFChangePhysicalMatAvailibility    ||
           Message == LF_EvMsg::evLFChangeProdPracPointerStirring    ||
           Message == LF_EvMsg::evLFChangeProdPracPointerElec        ||
           Message == LF_EvMsg::evLFChangeProdPracPointerRestriction ||
           Message == LF_EvMsg::evLFChangeProdPracPointerParameter   ||
           Message == LF_EvMsg::evLFChangeLiquidAdditionData         ||
           Message == LF_EvMsg::evLFChangeProdPracDataElec           ||
           Message == LF_EvMsg::evLFChangeProdPracDataRecipeCtrl     ||
           Message == LF_EvMsg::evLFChangeProdPracDataStirring       ||
           Message == LF_EvMsg::evLFHandleUpdatePurpose              ||
           Message == LF_EvMsg::evLFRestrictionDataUpdate            ||    
           Message == LF_EvMsg::evLFParameterUpdate                  ||  
           Message == LF_EvMsg::evLFUpdateAimDepartureTime           ||
           Message == LF_EvMsg::evLFUpdateAimTemperature             ||  
           Message == LF_EvMsg::evLFRecipeWeighingCompleteUpdate     ||  
           Message == LF_EvMsg::evLFMinChargeableBinWeightUpdate     ||
           Message == LF_EvMsg::evLFUpdatePlantStatus                ||
           Message == LF_EvMsg::evLFHeatScheduleUpdate               ||
           Message == LF_EvMsg::evLFProductionOrderDataUpdate        )

      {
        // make event to PlantEvent if no Heat Information is available
        if( HeatID.empty() )
        {
          evMessage.setPlantEvent(true);
          log("Event modified to PlantEvent, on Event: " + Message, 3);
        }
      }

      changeMissingEventData(evMessage);

      RetValue = dispatchEvent(m_SenderName,"",evMessage);
    } // if ( checkTransmitter(evMessage) )
  }

  return RetValue;
}

bool CHMI_LF_EventHandler::copyDMData(CEventMessage& Event, const std::string& Name, const std::string& Key)
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

    DM::iDM_Interface_var DM_Interface = 0;

		if( m_pDHTask )
		{
      CSMC_DataProvider_Impl* pDH_Interface = CDH_HMI_Task::getInstance()->getpInterface_OUT();
      
			if ( pDH_Interface )
			{
        // ************************************************
        // copy transfer car data used in plant
        // ************************************************
        if (!PlantID.empty() && PlantID != DEF::Inv_String)
        {
          DM_Interface = m_pDHTask->getpDM_Interface(ServerName, DM::PRODUCT);

			    if ( DM_Interface)
			    {
            //======================================================================
            log("INFO: copy product data!",3);
				    // copy data from external interface to DataInterface
            // read external data at DM with datakey ProductID
            // write data with datakey ProductID

            std::vector<std::string> requestedList = getRequestedDataList(ProductID,Name);
            // first time the interface doesn't have any data to get requested value names
            // so copy everything.
            if(! requestedList.empty() )
            {
              //log("size of requested list for key " + ProductID + " " +CDataConversion::LongToString(requestedList.size()), 4);
   			      CIntfData::copyIntfData<DM::iDM_Interface_var>
                (DM_Interface,pDH_Interface,ProductID,ProductID,requestedList);
            }
            else
            {
              log("requestedList is empty for key " + ProductID, 2);
            }

				    pDH_Interface->showContent(ProductID,4);
			    }
          else
          {
            std::string Message = Action + " ERROR : access DM::PRODUCT interface failed!";
            log(Message,1);
          }

          DM_Interface = m_pDHTask->getpDM_Interface(ServerName,DM::PLANT);
			    if ( DM_Interface )
			    {
            //======================================================================
            log("INFO: copy furnace data!",3);
			      // copy data from external interface to DataInterface
            // read external data at DM with datakey DEF_PLANT::Furnace
            // write data with datakey PlantID

            std::vector<std::string> requestedListPlantID = getRequestedDataList(PlantID,Name);
            // first time the interface doesn't have any data to get requested value names
            // so copy everything.
            if(! requestedListPlantID.empty() )
            {
   			      CIntfData::copyIntfData<DM::iDM_Interface_var>
                (DM_Interface,pDH_Interface,DEF_PLANT::Furnace,PlantID,getRequestedDataList(PlantID,Name));
            }
            else
            {
              log("requestedList is empty for key " + PlantID, 2);
            }

  
            pDH_Interface->showContent(PlantID,4);

            //======================================================================
            log("INFO: copy transfer car data!",3);

            // tracker has information about both car

            std::vector<std::string> requestedList1 = getRequestedDataList(DEF_PLANT::TransferCar1,Name);
            // first time the interface doesn't have any data to get requested value names
            // so copy everything.
            if(! requestedList1.empty() )
            {
              CIntfData::copyIntfData<DM::iDM_Interface_var>
                (DM_Interface,pDH_Interface,DEF_PLANT::TransferCar1,DEF_PLANT::TransferCar1,requestedList1);
            }
            else
            {
              log("requestedList is empty for key TransferCar1", 2);
            }

            std::vector<std::string> requestedList2 = getRequestedDataList(DEF_PLANT::TransferCar2,Name);
            // first time the interface doesn't have any data to get requested value names
            // so copy everything.
            if(! requestedList2.empty() )
            {
              CIntfData::copyIntfData<DM::iDM_Interface_var>
                (DM_Interface,pDH_Interface,DEF_PLANT::TransferCar2,DEF_PLANT::TransferCar2,requestedList2);
            }
            else
            {
              log("requestedList is empty for key TransferCar2", 2);
            }

				    pDH_Interface->showContent(DEF_PLANT::TransferCar1,4);
				    pDH_Interface->showContent(DEF_PLANT::TransferCar2,4);
			    }
          else
          {
            std::string Message = Action + " ERROR: failed to access DM interfaces!";
            log(Message,1);
          }
        }
        else
        {
          std::string Message = Action + " ERROR : invalid PlantID detected !";
          log(Message,1);
        }
      }
      else
        log("ERROR: pDH_Interface is 0",1);
	  }
    else
      log("ERROR: m_pDHTask is 0",1);
	}

  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc,
                                                                "CHMI_LF_EventHandler::copyDMData",
                                                                Action);
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc,
                                                          "CHMI_LF_EventHandler::copyDMData",
                                                          Action);
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException("CHMI_LF_EventHandler::copyDMData",
                                                     Action);
	}

	return RetValue;
}