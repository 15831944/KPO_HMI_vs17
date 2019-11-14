// Copyright (C) 2004 SMS Demag AG

#include "cCBS_StdEventLogFrameController.h"
#include "CSMC_EventLogFrameController.h"
#include "CIntfData.h"
#include "CDM_LFTask.h"
#include "CSMC_RecipeHandler.h"

#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_SOURCE.h"
#include "DEF_GC_RECIPE_STATUS.h"
#include "DEF_GC_RECIPE.h"

#include "CSMC_RecipeHandler.h"
#include "CDM_ProductManagementInterface_Impl.h"

#include "CDM_LFMaterialEventHandler.h"

CDM_LFMaterialEventHandler::~CDM_LFMaterialEventHandler()
{
}

CDM_LFMaterialEventHandler::CDM_LFMaterialEventHandler()
{
}

bool CDM_LFMaterialEventHandler::handleEvent(CEventMessage& evMessage)
{
  // liquid material events
	HANDLE_EVENT(LFChangeLiquidAdditionData);
	HANDLE_EVENT_DATA(LFLiquidSteelCharged);
	HANDLE_EVENT_DATA(LFLiqMatHandlReport);

  // material availability handling
	HANDLE_EVENT_DATA(LFChangePhysicalMatAvailibility);
  //HANDLE_EVENT_DATA(LFHandleUpdatePurpose);
  HANDLE_EVENT_DATA(LFRequestMatAvail);

  // solid material handling
  HANDLE_EVENT(LFMaterialHandlingReport); 

  HANDLE_EVENT_DATA(LFMatBatchCharged);
  HANDLE_EVENT_DATA(LFMatBatchDischarged);


  // HMI events
	HANDLE_EVENT(LFHMIMaterialDischarged);
	HANDLE_EVENT_DATA(LFMinChargeableBinWeightUpdate);

  // wire feeding related events
  HANDLE_EVENT_DATA(LFWireFeederImage);
  HANDLE_EVENT_DATA(LFWireFeedingStart);
  HANDLE_EVENT_DATA(LFWireFeedingEnd);

  HANDLE_EVENT_DATA(LFTrimmingMaterialDischarged);
  HANDLE_EVENT_DATA(LFAlloyingMaterialDischarged);
	
	return false;
}

bool CDM_LFMaterialEventHandler::doLFMaterialHandlingReport( CEventMessage& Event)
{
  std::string OriginalEventMessage = Event.getMessage();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();
  try
  {
    if ( checkEventAssignment(Event) )
    {
      // copy data form DH interface
	    if ( copyDataEventData(Event) )
      {
        if ( CDM_LFDBManagerTask::getInstance()->getDBManager()->evMaterialHandlingReport(Event) )
        {
          // try to read recipe status from received data
          if (m_pDataInterface)
          {
            long RecipeStatus = m_pDataInterface->getLong(Event.getDataKey(),DATA::RecipeStatus);

            // change Event Message according to respective recipe status
            // for 1,3,4,6,7,0,99
            if ( RecipeStatus == DEF_GC_RECIPE_STATUS::Enabled ) // 1
            {
              Event.setMessage(LF_EvMsg::evLFEnableSourceRecipe);
            }
            else if ( RecipeStatus == DEF_GC_RECIPE_STATUS::Weighed ) // 3
            {
              Event.setMessage(LF_EvMsg::evLFRecipeMatCharged);
            }
            else if ( RecipeStatus == DEF_GC_RECIPE_STATUS::WeighingComplete ) // 4
            {
              Event.setMessage(LF_EvMsg::evLFRecipeWeighingComplete);
            }
            else if ( RecipeStatus == DEF_GC_RECIPE_STATUS::DischargeStart ) // 6
            {
              Event.setMessage(LF_EvMsg::evLFRecipeMatDischargedStart);
            }
            else if ( RecipeStatus == DEF_GC_RECIPE_STATUS::WeighingCompleteUpdate ) // 7
            {
              Event.setMessage(LF_EvMsg::evLFRecipeWeighingCompleteUpdate);
            }
            else if ( RecipeStatus == DEF_GC_RECIPE_STATUS::Disabled ) // 0
            {
              Event.setMessage(LF_EvMsg::evLFDisableSourceRecipe); // 2,5,8
            }
            else if ( RecipeStatus == DEF_GC_RECIPE_STATUS::ProcessingStart ||
                      RecipeStatus == DEF_GC_RECIPE_STATUS::FirstMaterialInChargingHopper ||
                      RecipeStatus == DEF_GC_RECIPE_STATUS::LastMaterialInChargingHopper )
            {
              Event.setMessage(LF_EvMsg::evLFRecipeMatDischargedStart); 
            }
            else if ( RecipeStatus == DEF_GC_RECIPE_STATUS::UnKnown ) // 99
            {
              // call ProductManager, set MatHanldeL1Error = Error 
              if (m_pDMTask->getpProductManager()) 
              {
                m_pDMTask->getpProductManager()->changeComputerModeAvailabilities(Event);
              }

              Event.setMessage(LF_EvMsg::evLFRecipeMatDischarged);
            }
            else // default = Unknown
            {
              Event.setMessage(LF_EvMsg::evLFRecipeMatDischarged);
            }

            bool RetValue = dispatchEvent(Event);

            // in the case of doLFMaterialHandlingReport
            // send original event also
            if ( RetValue ) 
            {
              Event.setMessage(OriginalEventMessage);
              dispatchEvent(Event);
            }
          } // if (m_pDataInterface)
        } // if ( CDM_LFDBManagerTask::getInstance()->getDBManager()->evMaterialHandlingReport(Event) )
      } // if ( copyDataEventData(Event) )
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_LFMaterialEventHandler::doLFMaterialHandlingReport()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFMaterialEventHandler::doLFMaterialHandlingReport()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFMaterialEventHandler::doLFMaterialHandlingReport()",
                                         ExceptionMsg.str().c_str());
  }
  return true;
}

bool CDM_LFMaterialEventHandler::doLFHMIMaterialDischarged(CEventMessage& Event)
{
  bool RetValue = true;

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();
  try
  {

    if ( checkEventAssignment(Event) )
    {
      // copy data form DH interface
	    if ( copyDataEventData(Event) )
      {
        // try to read recipe name from received data
        if (m_pDataInterface)
        {
          std::string RecipeName    = m_pDataInterface->getString(Event.getDataKey(),DATA::RecipeName);

          std::string RecipeSource  = m_pDataInterface->getString(Event.getDataKey(),DATA::RecipeSource);

          long RecipeNo             = m_pDataInterface->getLong(Event.getDataKey(),DATA::RecipeNo);


          seqBatch RecipeBatch      = CIntfData::ToCORBAType(m_pDataInterface->getBatch(Event.getDataKey().c_str(),
                                                              DATA::RecipeContent));

          if (CIntfData::getLength(RecipeBatch) > 0)
          {
            // recipe name not send, set recipe name to "High Priority Batch"
            if ( RecipeName == DEF::Inv_String )
            {
              RecipeName = DEF_GC_RECIPE::HighPrioBatch;
              m_pDataInterface->setString(Event.getDataKey(),
                                          DATA::RecipeName,
                                          RecipeName);
              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,Event.getProductID());
              pEventLog->EL_ErrorHandlingRecipe(sMessage,RecipeName.c_str(), RecipeNo, "Empty RecipeName changed to High Priority");
            }
          
            // recipeno from HMI might be adapted to last known database entry
            CSMC_RecipeHandler RecipeHandler;
            RecipeHandler.checkMatHandlingRecipeData(DEF_GC_PLANT_DEF::LF,
                                                      Event.getHeatID(),
                                                      Event.getTreatID(),
                                                      RecipeSource,RecipeName,RecipeNo);
          
            m_pDataInterface->setLong(Event.getDataKey(),DATA::RecipeNo,RecipeNo);
          
            CEventMessage NewEventMessage(Event);

            // ****************************************************************
            // provide events for ARCHIVER & MODEL!
            // ****************************************************************
            // processes must get data in specific order of 
            // Enabled -> Weighed -> Weighing_Complete -> Discharged
            // Event data must be duplicated here to have seperate DataKey for each event
            // Event must have message LF_EvMsg::evLFMaterialHandlingReport
            std::string DataKey     = Event.getDataKey();
            std::string NewDataKey  = m_pDataInterface->generateDataKey(Event.getProductID());
            
            NewEventMessage.setMessage(LF_EvMsg::evLFMaterialHandlingReport);
            NewEventMessage.setDataKey(NewDataKey);

            // ****************************
            // copy data into new data key 
            // ****************************
            CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,
                                                  m_pDataInterface,
                                                  DataKey,
                                                  NewDataKey);

            // ***************************************************************************************************************************************
            // set status and call internal method to handle single event with respective status, Method will force database writing and calling model
            // ***************************************************************************************************************************************
            m_pDataInterface->setLong(NewDataKey,DATA::RecipeStatus,DEF_GC_RECIPE_STATUS::Enabled);
            RetValue = RetValue && CDM_LFDBManagerTask::getInstance()->getDBManager()->evMaterialHandlingReport(NewEventMessage);

            // ***************************************************************************************************************************************
            // set status and call internal method to handle single event with respective status, Method will force database writing and calling model
            // ***************************************************************************************************************************************
            m_pDataInterface->setLong(NewDataKey,DATA::RecipeStatus,DEF_GC_RECIPE_STATUS::Weighed);
            RetValue = RetValue && CDM_LFDBManagerTask::getInstance()->getDBManager()->evMaterialHandlingReport(NewEventMessage);

            // ***************************************************************************************************************************************
            // set status and call internal method to handle single event with respective status, Method will force database writing and calling model
            // ***************************************************************************************************************************************
            m_pDataInterface->setLong(NewDataKey,DATA::RecipeStatus,DEF_GC_RECIPE_STATUS::WeighingComplete);
            RetValue = RetValue && CDM_LFDBManagerTask::getInstance()->getDBManager()->evMaterialHandlingReport(NewEventMessage);

            // ***************************************************************************************************************************************
            // set status and call internal method to handle single event with respective status, Method will force database writing and calling model
            // ***************************************************************************************************************************************
            m_pDataInterface->setLong(NewDataKey,DATA::RecipeStatus,DEF_GC_RECIPE_STATUS::Discharged);
            RetValue = RetValue && CDM_LFDBManagerTask::getInstance()->getDBManager()->evMaterialHandlingReport(NewEventMessage);

            // ****************************************************************
            // provide events for Model !
            // ****************************************************************

            // init LF_HMI_Material_Discharged
            Event.setMessage(LF_EvMsg::evLFEnableSourceRecipe);
            dispatchEvent(Event);

            // send LF_RECIPE_MATERIAL_CHARGED 
            // model frame could handle batch!
            // sending single materials is not neccessary
            Event.setMessage(LF_EvMsg::evLFRecipeMatCharged);
            dispatchEvent(Event);
            
            // finishing LF_HMI_Material_Discharged
            // send LF_RECIPE_WEIGHING_COMPLETE and LF_RECIPE_MATERIAL_DISCHARGED
            Event.setMessage(LF_EvMsg::evLFRecipeWeighingComplete);
            dispatchEvent(Event);

            Event.setMessage(LF_EvMsg::evLFRecipeMatDischarged);
            dispatchEvent(Event);

          }
          else
          {
            RetValue = false;

	          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_RecipeWithoutMaterials(sMessage, RecipeName.c_str(), RecipeNo, 0);
          }
        } // if (m_pDataInterface)
      } // if ( copyDataEventData(Event) )
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_LFMaterialEventHandler::doLFHMIMaterialDischarged()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFMaterialEventHandler::doLFHMIMaterialDischarged()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFMaterialEventHandler::doLFHMIMaterialDischarged()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_LFMaterialEventHandler::doLFChangeLiquidAdditionData(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if ( checkEventAssignment(Event) )
  {
    if(CDM_LFDBManagerTask::getInstance()->getDBManager()->evChangeLiquidAdditionData(Event))
    {
      RetValue = dispatchEvent(Event);
    }
  }

  return RetValue;
}