// Copyright (C) 2011 SMS Siemag AG

#include "cCBS_StdEventLogFrameController.h"
#include "CSMC_EventLogFrameController.h"
#include "CSMC_EventLogEAFController.h"
#include "CIntfData.h"
#include "CSMC_RecipeHandler.h"

#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_RECIPE.h"
#include "DEF_GC_RECIPE_STATUS.h"

#include "CDM_DataInterface_Impl.h"
#include "CDM_EAFTask.h"
#include "CDM_EAFDBManagerTask.h"

#include "CDM_EAFMaterialEventHandler.h"


CDM_EAFMaterialEventHandler::~CDM_EAFMaterialEventHandler()
{
}

CDM_EAFMaterialEventHandler::CDM_EAFMaterialEventHandler()
{
}

bool CDM_EAFMaterialEventHandler::handleEvent(CEventMessage& evMessage)
{
  HANDLE_EVENT(EAFMaterialHandlingReport);
  HANDLE_EVENT(EAFHMIMaterialDischarged);    

  HANDLE_EVENT_DATA(EAFChangedMatSetPointsByOperator);
  HANDLE_EVENT_DATA(EAFChangePhysicalMatAvailibility);

  HANDLE_EVENT_DATA(EAFDisableSourceRecipe);
  HANDLE_EVENT_DATA(EAFEnableSourceRecipe);

  HANDLE_EVENT(EAFChargedHotMetal);
  HANDLE_EVENT(EAFHotMetalAssigned);
  HANDLE_EVENT(EAFHotMetalLadleData);
  HANDLE_EVENT(EAFRemoveHotMetalData);

  HANDLE_EVENT_DATA(EAFMatBatchCharged);
  HANDLE_EVENT_DATA(EAFMatBatchDischarged);

  HANDLE_EVENT(EAFHandleBasketDischarged);
  HANDLE_EVENT(EAFHandleBasketAssignedToHeat);
  HANDLE_EVENT(EAFHandleBasketDeAssignedFromHeat);
  HANDLE_EVENT(EAFHandleSetBasketData);

  HANDLE_EVENT_DATA(EAFRecipeMaterialCharged);
  HANDLE_EVENT_DATA(EAFRecipeMaterialDischarged);
  HANDLE_EVENT_DATA(EAFRecipeWeighingComplete);

  HANDLE_EVENT(EAFChangeLiquidAdditionData);
  HANDLE_EVENT_DATA(EAFLiquidAdditionCharged);
  HANDLE_EVENT_DATA(EAFChargedLiquidSteel);
  HANDLE_EVENT_DATA(EAFRemoveLiquidAdditionData);

  HANDLE_EVENT_DATA(EAFDolomiticLimeInjectionStart);
  HANDLE_EVENT_DATA(EAFDolomiticLimeInjectionStop);
  HANDLE_EVENT_DATA(EAFChargedLiquidFeCr);

  HANDLE_EVENT_DATA(EAFDRIInjectionStart);
  HANDLE_EVENT_DATA(EAFDRIInjectionStop);

  HANDLE_EVENT_DATA(EAFRestrictionDataUpdate);

  HANDLE_EVENT_DATA(EAFLiqMatHandlReport);

  HANDLE_EVENT(EAFMatFeedingStart);  
  HANDLE_EVENT(EAFMatFeedingStop);  
  HANDLE_EVENT(EAFScrapMaterialAvail);


  return false;
}

bool CDM_EAFMaterialEventHandler::doEAFMaterialHandlingReport( CEventMessage& Event)
{
  bool RetValue = false;

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
        if ( CDM_EAFDBManagerTask::getInstance()->getDBManager()->evMaterialHandlingReport(Event) )
        {
          // try to read recipe status from received data
          if (m_pDataInterface)
          {
            long RecipeStatus = m_pDataInterface->getLong(Event.getDataKey().c_str(),DATA::RecipeStatus);

            // change Event Message according to respective recipe status
            // for 1,3,4,6,7,0,99
            if ( RecipeStatus == DEF_GC_RECIPE_STATUS::Enabled ) // 1
            {
              Event.setMessage(EAF_EvMsg::evEAFEnableSourceRecipe);
            }
            else if ( RecipeStatus == DEF_GC_RECIPE_STATUS::Weighed ) // 3
            {
              Event.setMessage(EAF_EvMsg::evEAFRecipeMaterialCharged);
            }
            else if ( RecipeStatus == DEF_GC_RECIPE_STATUS::WeighingComplete ) // 4
            {
              Event.setMessage(EAF_EvMsg::evEAFRecipeWeighingComplete);
            }
            else if ( RecipeStatus == DEF_GC_RECIPE_STATUS::DischargeStart || // 6
              RecipeStatus == DEF_GC_RECIPE_STATUS::Discharged) //9
            {
              Event.setMessage(EAF_EvMsg::evEAFRecipeMaterialDischarged);
            }
            else if ( RecipeStatus == DEF_GC_RECIPE_STATUS::WeighingCompleteUpdate ) // 7
            {
              Event.setMessage(EAF_EvMsg::evEAFRecipeWeighingCompleteUpdate);
            }
            else if ( RecipeStatus == DEF_GC_RECIPE_STATUS::Disabled ) // 0
            {
              Event.setMessage(EAF_EvMsg::evEAFDisableSourceRecipe); // 2,5,8
            }
            else if ( RecipeStatus == DEF_GC_RECIPE_STATUS::ProcessingStart ||
                      RecipeStatus == DEF_GC_RECIPE_STATUS::FirstMaterialInChargingHopper ||
                      RecipeStatus == DEF_GC_RECIPE_STATUS::LastMaterialInChargingHopper )
            {
              Event.setMessage(EAF_EvMsg::evEAFRecipeMaterialDischargedStart); 
            }
            else if ( RecipeStatus == DEF_GC_RECIPE_STATUS::UnKnown ) // 99
            {
              // call ProductManager, set MatHanldeL1Error = Error 
              if (m_pDMTask->getpProductManager()) 
              {
                m_pDMTask->getpProductManager()->changeComputerModeAvailabilities(Event);
              }

              Event.setMessage(EAF_EvMsg::evEAFRecipeMaterialDischarged);
            }
            else // default = Unknown
            {
              Event.setMessage(EAF_EvMsg::evEAFRecipeMaterialDischarged);
            }

            RetValue = dispatchEvent(Event);

            // in the case of doEAFMaterialHandlingReport
            // send original event also
            if ( RetValue ) 
            {
              Event.setMessage(OriginalEventMessage);
              RetValue = dispatchEvent(Event);
            }
          } // if (m_pDataInterface)
        } // if ( CDM_EAFDBManagerTask::getInstance()->getDBManager()->evMaterialHandlingReport(Event) )
      } // if ( copyDataEventData(Event) )
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFMaterialEventHandler::doEAFMaterialHandlingReport()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFMaterialEventHandler::doEAFMaterialHandlingReport()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFMaterialEventHandler::doEAFMaterialHandlingReport()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_EAFMaterialEventHandler::doEAFHMIMaterialDischarged(CEventMessage& Event)
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
            RecipeHandler.checkMatHandlingRecipeData(DEF_GC_PLANT_DEF::EAF,
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
            // Event must have message EAF_EvMsg::evEAFMaterialHandlingReport
            std::string DataKey     = Event.getDataKey();
            std::string NewDataKey  = m_pDataInterface->generateDataKey(Event.getProductID());
            
            NewEventMessage.setMessage(EAF_EvMsg::evEAFMaterialHandlingReport);
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
            RetValue = RetValue && CDM_EAFDBManagerTask::getInstance()->getDBManager()->evMaterialHandlingReport(NewEventMessage);

            // ***************************************************************************************************************************************
            // set status and call internal method to handle single event with respective status, Method will force database writing and calling model
            // ***************************************************************************************************************************************
            m_pDataInterface->setLong(NewDataKey,DATA::RecipeStatus,DEF_GC_RECIPE_STATUS::Weighed);
            RetValue = RetValue && CDM_EAFDBManagerTask::getInstance()->getDBManager()->evMaterialHandlingReport(NewEventMessage);

            // ***************************************************************************************************************************************
            // set status and call internal method to handle single event with respective status, Method will force database writing and calling model
            // ***************************************************************************************************************************************
            m_pDataInterface->setLong(NewDataKey,DATA::RecipeStatus,DEF_GC_RECIPE_STATUS::WeighingComplete);
            RetValue = RetValue && CDM_EAFDBManagerTask::getInstance()->getDBManager()->evMaterialHandlingReport(NewEventMessage);

            // ***************************************************************************************************************************************
            // set status and call internal method to handle single event with respective status, Method will force database writing and calling model
            // ***************************************************************************************************************************************
            m_pDataInterface->setLong(NewDataKey,DATA::RecipeStatus,DEF_GC_RECIPE_STATUS::Discharged);
            RetValue = RetValue && CDM_EAFDBManagerTask::getInstance()->getDBManager()->evMaterialHandlingReport(NewEventMessage);

            // ****************************************************************
            // provide events for Model !
            // ****************************************************************

            // init EAF_HMI_Material_Discharged
            Event.setMessage(EAF_EvMsg::evEAFEnableSourceRecipe);
            dispatchEvent(Event);

            // send EAF_RECIPE_MATERIAL_CHARGED 
            // model frame could handle batch!
            // sending single materials is not neccessary
            Event.setMessage(EAF_EvMsg::evEAFRecipeMaterialCharged);
            dispatchEvent(Event);
            
            // finishing EAF_HMI_Material_Discharged
            // send EAF_RECIPE_WEIGHING_COMPLETE and EAF_RECIPE_MATERIAL_DISCHARGED
            Event.setMessage(EAF_EvMsg::evEAFRecipeWeighingComplete);
            dispatchEvent(Event);

            Event.setMessage(EAF_EvMsg::evEAFRecipeMaterialDischarged);
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
                                         "CDM_EAFMaterialEventHandler::doEAFHMIMaterialDischarged()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFMaterialEventHandler::doEAFHMIMaterialDischarged()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFMaterialEventHandler::doEAFHMIMaterialDischarged()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_EAFMaterialEventHandler::doEAFHandleBasketDischarged(CEventMessage& Event)
{

  bool RetValue = false;

  copyDataEventData(Event);

  if (checkEventAssignment(Event))
  {
    // we have to inform model for new assigend basket if unplanned basket was discharged
    if(!CDM_EAFDBManagerTask::getInstance()->getDBManager()->checkBasketAssignment(Event))
    {
      CEventMessage NewMessage(Event);

      NewMessage.setMessage(EAF_EvMsg::evEAFHandleBasketAssignedToHeat);
      dispatchEvent( NewMessage );
    }

    if(!CDM_EAFDBManagerTask::getInstance()->getDBManager()->checkTreatMode(Event))
    {
      CEventMessage NewMessage(Event);

      NewMessage.setMessage(EAF_EvMsg::evEAFChangeTreatmentMode);
      dispatchEvent( NewMessage );
    }

    if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evHandleBasketDischarged(Event))
    {
      if (m_pDMTask->getpProductManager()) 
      {
        m_pDMTask->getpProductManager()->changeChargingData(Event);
      }

      RetValue = dispatchEvent( Event );
    }
  }

  return RetValue;

}


bool CDM_EAFMaterialEventHandler::doEAFChangeLiquidAdditionData(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if (checkEventAssignment(Event))
  {
    if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evChangeLiquidAdditionData(Event))
    {
      RetValue = dispatchEvent( Event );
    }
  }

  return RetValue;
}

bool CDM_EAFMaterialEventHandler::doEAFMatFeedingStart(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if (checkEventAssignment(Event))
  {
    if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evMatFeeding(Event))
    {
      RetValue = dispatchEvent( Event );
    }
  }

  return RetValue;
}

bool CDM_EAFMaterialEventHandler::doEAFMatFeedingStop(CEventMessage& Event)
{  
  bool RetValue = false;

  copyDataEventData(Event);

  if (checkEventAssignment(Event))
  {
    if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evMatFeeding(Event))
    {
      RetValue = dispatchEvent( Event );
    }
  }

  return RetValue;
}

bool CDM_EAFMaterialEventHandler::doEAFHandleBasketAssignedToHeat(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evHandleBasketAssignedToHeat(Event))
  {
    // when HMI send wrong event type otherwise model will not accept
    Event.setPlantEvent(false);
    if (checkEventAssignment(Event))
    {
      RetValue = dispatchEvent( Event );
    }
  }

  return RetValue;

}


bool CDM_EAFMaterialEventHandler::doEAFHandleSetBasketData(CEventMessage& Event)
{

  bool RetValue = false;

  copyDataEventData(Event);

  if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evHandleSetBasketData(Event))
  {
    if (checkEventAssignment(Event))
    {
      RetValue = dispatchEvent( Event );
    }
    else
    {
      Event.setPlantEvent(true);
      RetValue = dispatchEvent( Event );
    }
  }

  return RetValue;

}

bool CDM_EAFMaterialEventHandler::doEAFHandleBasketDeAssignedFromHeat(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if (checkEventAssignment(Event))
  {
    if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evHandleBasketDeAssignedFromHeat(Event))
    {
      RetValue = dispatchEvent( Event );
    }
  }

  return RetValue;

}



bool CDM_EAFMaterialEventHandler::doEAFChargedHotMetal(CEventMessage& Event)
{

  bool RetValue = false;

  copyDataEventData(Event);

  if (checkEventAssignment(Event))
  {
    if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evChargedHotMetal(Event))
    {
      RetValue = dispatchEvent( Event );
    }
  }

  return RetValue;

}

bool CDM_EAFMaterialEventHandler::doEAFHotMetalAssigned(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if (checkEventAssignment(Event))
  {
    if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evHotMetalAssigned(Event))
    {
      RetValue = dispatchEvent( Event );
    }
  }

  return RetValue;
}

bool CDM_EAFMaterialEventHandler::doEAFHotMetalLadleData(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if (checkEventAssignment(Event))
  {
    if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evHotMetalLadleData(Event))
    {
      RetValue = dispatchEvent( Event );
    }
  }

  return RetValue;
}

bool CDM_EAFMaterialEventHandler::doEAFRemoveHotMetalData(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if (checkEventAssignment(Event))
  {
    if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evRemoveHotMetalData(Event))
    {
      RetValue = dispatchEvent( Event );
    }
  }

  return RetValue;
}
bool CDM_EAFMaterialEventHandler::doEAFScrapMaterialAvail(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  RetValue = dispatchEvent( Event );

  return RetValue;
}


