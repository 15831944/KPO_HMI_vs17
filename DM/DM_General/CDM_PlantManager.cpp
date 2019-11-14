// Copyright (C) 2004 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"

#include "CEventMessage.h"
#include "cCBS_StdInitBase.h"
#include "CSMC_EventLogFrameController.h"
#include "CDM_PlantManagementInterface_Impl.h"
#include "CDM_ProductManagementInterface_Impl.h"
#include "CDM_DataInterface_Impl.h"
#include "CDM_Task.h"
#include "CDM_GasDataHandler.h"
#include "CIntfData.h"

#include "CDM_PlantManager.h"

CDM_PlantManager::CDM_PlantManager( ) 
: m_pPlantManagementInterface(0)
, m_pDataInterface(0)
{
//HF +++
  m_WasteGasTypeList.push_back(DEF_GAS::CO2);
  m_WasteGasTypeList.push_back(DEF_GAS::CO);
  m_WasteGasTypeList.push_back(DEF_GAS::O2);
  m_WasteGasTypeList.push_back(DEF_GAS::N2);
  m_WasteGasTypeList.push_back(DEF_GAS::Ar);
  m_WasteGasTypeList.push_back(DEF_GAS::He);
//HF ---
}

CDM_PlantManager::~CDM_PlantManager()
{
}

void CDM_PlantManager::init(CDM_Task *pDMTask)
{
	m_pDMTask = pDMTask;
	m_pPlantManagementInterface = m_pDMTask->getpPlantManagementInterface();
  m_pDataInterface            = m_pDMTask->getpDataInterface();
}

//checks product data against database to deassign heats from tracker 
//that are no longer in production
//Assigns the product to an idle Model process, because we might have multiple instances 
//running simultaneously, so find one of them as the assigned target. 
std::vector<std::string> CDM_PlantManager::getProductsOutOfProduction( CEventMessage& Event )
{
  // find first model without product assigned
  std::vector<std::string> ProductList;

  std::map<std::string,std::string>::iterator it;

	std::string ProductID = Event.getProductID();
  std::string PlantID   = Event.getPlantID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();

  if (m_pPlantManagementInterface && m_pDataInterface)
  {
    // check if PlantID value was avaialble at DataInterface
    if ( PlantID.empty() )
    {
      PlantID = m_pDataInterface->getString(Event.getDataKey(),DATA::PlantID);
    }


    // first try to find assignments of heats that are no longer in production
    for (it= m_ModelList.begin(); it != m_ModelList.end();++it)
    {
      // get internal data
      std::string ActModel       = it->first;
      log("INFO: CDM_PlantManager::getProductsOutOfProduction(): check Product at Model " + ActModel, 2);

      std::string FoundProductID = m_pPlantManagementInterface->getString(ActModel,DATA::ProductID);
      std::string FoundHeatID    = m_pPlantManagementInterface->getString(ActModel,DATA::HeatID);
      std::string FoundTreatID   = m_pPlantManagementInterface->getString(ActModel,DATA::TreatID);
      std::string FoundPlantID   = m_pPlantManagementInterface->getString(ActModel,DATA::PlantID);

      // check only valid products against database !
      if ( FoundProductID == DEF::Inv_String || FoundProductID.empty() )
      {
        std::string Message("CDM_PlantManager::getProductsOutOfProduction() No Product found at Model ");
        Message += ActModel;

        log(Message,2);
      }
      else
      {
        std::string Message("INFO: CDM_PlantManager::getProductsOutOfProduction(): Product found at Model "+ActModel);

        std::string OrderId;

        // if heat if not in Production remove assignment !
        if ( ! m_pDMTask->isProductInProduction(FoundHeatID,FoundTreatID,FoundPlantID,OrderId) )
        {
          ProductList.push_back(FoundProductID);
        }
      }
    }
  }  

  return ProductList;
}

// function is used to check if heat can be assigned to a model
// before modification of data base.
//
bool CDM_PlantManager::checkAssignement( CEventMessage& Event )
{
  // assignment of a heat can be done:
  // if a model does not have any heat
  // if a model has the same heat and multiple announcement (re-announcement) is allowed. (ini file)
  bool RetValue = false;
  std::string AssignedModel;
  std::map<std::string,std::string>::iterator it;

	std::string ProductID;
  std::string PlantID   = Event.getPlantID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();

  bool MultipleAnnouncements   = false;
  bool PreserveLastUsedModel   = false;

  std::string ActModel;
  std::string ModelProductID;
  std::string ModelHeatID;
  std::string ModelTreatID;

  cCBS_StdInitBase::getInstance()->replaceWithEntry("PROCESS","MultipleAnnouncements",MultipleAnnouncements);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("PROCESS","PreserveLastUsedModel",PreserveLastUsedModel);

  log("INFO: Product check assignment routine!",3);

  if (m_pPlantManagementInterface && m_pDataInterface)
  {
    // first check if product aready at some model
    for (it= m_ModelList.begin(); it != m_ModelList.end();++it)
    {
      std::string Model    = it->first;
      std::stringstream Message;
      Message << "Check if model " << Model << " " << "has a heat\n";
      // get internal data
      ModelProductID = m_pPlantManagementInterface->getString(Model,DATA::ProductID);

      // Product is still assigned to this model !!!
      if ( ModelProductID.empty() || ModelProductID == DEF::Inv_String )
      {
        Message << "No heat at this model. Assignment is possible.";
        log(Message.str(),3);

        RetValue = true;
        break;
      }
      else
      {
        ModelHeatID = m_pPlantManagementInterface->getString(Model,DATA::HeatID);
        ModelTreatID = m_pPlantManagementInterface->getString(Model,DATA::TreatID);

        if (MultipleAnnouncements)
        {

          if (HeatID == ModelHeatID && TreatID == ModelTreatID)
          {
            Message << "Model has the same heat and multiple announcement is allowed. Assignment is possible.\n";
            Message << "Product '" << ModelProductID << "' HeatID '" << ModelHeatID << "' TreatID '" << ModelTreatID << "'";
            
            RetValue = true;
            break;
          }
					else  //SARS
					{
						Message << "Product '" << ModelProductID << "' HeatID '" << ModelHeatID << "' TreatID '" << ModelTreatID << "'";
						RetValue = true;
						break;
					}
        }
        else
        {
          Message << "Model not free " << " Product '" << ModelProductID << "' HeatID '" << ModelHeatID << "' TreatID '" << ModelTreatID << "'";
        }
      }
      m_pDMTask->log(Message.str(), 3);
    }
  }
  return RetValue;
}

//checks product data against database to deassign heats from tracker 
//that are no longer in production
//Assigns the product to an idle Model process, because we might have multiple instances 
//running simultaneously, so find one of them as the assigned target. 
bool CDM_PlantManager::assignProduct( CEventMessage& Event )
{
  // find first model without product assigned
  bool RetValue = false;
  std::string AssignedModel;
  std::map<std::string,std::string>::iterator it;

	std::string ProductID = Event.getProductID();
  std::string PlantID   = Event.getPlantID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();

  bool MultipleAnnouncements   = false;
  bool PreserveLastUsedModel   = false;

  std::string ActModel;
  std::string ActProductID;
  std::string ActPlantID;
  std::string ActEquipmentId;

  cCBS_StdInitBase::getInstance()->replaceWithEntry("PROCESS","MultipleAnnouncements",MultipleAnnouncements);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("PROCESS","PreserveLastUsedModel",PreserveLastUsedModel);

  log("INFO: Product assignment routine!",3);

  if (m_pPlantManagementInterface && m_pDataInterface)
  {
    // check if PlantID value was available at DataInterface
    if ( PlantID.empty() )
    {
      PlantID = m_pDataInterface->getString(Event.getDataKey(),DATA::PlantID);
    }

    std::stringstream Message;
    Message << "INFO: checking if Product " << ProductID << " already assigned to some Model." << __FILE__ << __LINE__;
    log(Message.str(),3);

    long AssignCount = 0;

    // first check if product aready at some model
    for (it= m_ModelList.begin(); it != m_ModelList.end();++it)
    {
      // get internal data
      std::string Model    = it->first;
      ActProductID         = m_pPlantManagementInterface->getString(Model,DATA::ProductID);
      ActPlantID           = m_pPlantManagementInterface->getString(Model,DATA::PlantID);

      std::stringstream CheckMessage;
      CheckMessage << "INFO: Model " << ActModel << " Plant " << ActPlantID << " Product " << ActProductID;

      // Product is still assigned to this model !!!
      if ( ActProductID == ProductID && ActProductID != DEF::Inv_String )
      {
        CheckMessage << " is already assigned!";
        ActModel = Model;
        AssignCount++;
      }
      m_pDMTask->log(CheckMessage.str(),2);
    }

    // announcement on several models is not allowed. Log for information
    if (AssignCount == 1)
    {
      RetValue = true;
    }
    else if(AssignCount > 1)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorMultipleHeatAssignment(sMessage);

      // tracking error but proceed !
      RetValue = true;
    }
    else if ( AssignCount == 0)// product nor yet assigned
    {
      for (it= m_ModelList.begin(); it != m_ModelList.end();++it)
      {

        RetValue = false;
        
        // get internal data
        ActModel             = it->first;
        ActProductID         = m_pPlantManagementInterface->getString(ActModel,DATA::ProductID);
        ActPlantID           = m_pPlantManagementInterface->getString(ActModel,DATA::PlantID);

        std::stringstream AssignMessage;

        AssignMessage << " try to assign Product " << ProductID 
                      << " to model " << ActModel 
                      << " for plant " << ActPlantID
                      << " with actual Product  " << ActProductID;
                      

        m_pDMTask->log(AssignMessage.str(),2);

        // PlantId is identical to ActPlantID for ActModel of DM_Process
        // remark ! several models could be assigned to one plant !!!
        if ( ActPlantID != DEF::Inv_String && !ActPlantID.empty() )
        {
          if ( PlantID == ActPlantID )
          {
            // use assigned model at equipment data
            if ( !it->second.empty() && it->second != DEF::Inv_String )
            {
              std::string EquipmentId;
              
              if ( m_pDMTask->getpProductManagementInterface() )
              {
                EquipmentId = m_pDMTask->getpProductManagementInterface()->
                                            getString(ProductID,DATA::EquipmentId);
              }

              // assign Product to preset model if deined by EquipmentId
              if ( EquipmentId == it->second )
              {
                std::string Mess("INFO: PlantID is equal and EquipmentId is equal. Assign to it.");
                log(Mess,2);
                RetValue = true;
                break;
              }
            }
            else
            {
              // no product assigned to this model
              if ( ActProductID == DEF::Inv_String || ActProductID.empty() )  
              {
                std::string Mess("INFO: PlantID is equal to PlantID of model. And model doesn't have a product. Assign to it.");
                log(Mess,2);

                RetValue = true;
                break;
              }
              else
              {
                if ( PreserveLastUsedModel )
                {
                  std::string Mess("INFO: PlantID is equal to PlantID of model but model has already a product. Assign to due to <PreserveLastUsedModel = true> switch by ini file.");
                  log(Mess,2);

                  RetValue = true;
                  break;
                }
              }
            }
          }
          else
          {
            m_pDMTask->log("Plant ID not identical",2);
          }
        }
      } // for (it= m_ModelList.begin(); it != m_ModelList.end();++it)
    }

    // next is realy exceptional situation
    if ( !RetValue ) // stil not assigned. try to get a free model.
    {
      m_pDMTask->log("INFO: assign to first free model! Product " + ProductID,2);

      for (it= m_ModelList.begin(); it != m_ModelList.end();++it)
      {

        RetValue = false;
        
        // get internal data
        ActModel        = it->first;
        ActProductID    = m_pPlantManagementInterface->getString(ActModel,DATA::ProductID);
        ActPlantID      = m_pPlantManagementInterface->getString(ActModel,DATA::PlantID);
        std::stringstream AssignMessage;

        AssignMessage << "Try to find model " << ActModel 
                      << " for plant " << ActPlantID
                      << " for Equipment " << ActEquipmentId
                      << " with actual Product  " << ActProductID;

        m_pDMTask->log(AssignMessage.str(),2);

        // No Product assigned to this model 
        if ( ActProductID == DEF::Inv_String || ActProductID.empty() )
        {
          m_pDMTask->log("Model found " + ActModel,2);

          RetValue = true;
          break;
        }
      } // for (it= m_ModelList.begin(); it != m_ModelList.end();++it)
    }

    if ( RetValue ) // Product can be assigned now
    {

      AssignedModel = ActModel ;

      m_pPlantManagementInterface->setString(ActModel,DATA::ProductID,ProductID);

      // copy additional data from ProductInterface
      std::vector<std::string> DataList;
      DataList.push_back(DATA::CustHeatID);
      DataList.push_back(DATA::CustTreatID);
      DataList.push_back(DATA::TreatNo);
      DataList.push_back(DATA::HeatID);
      DataList.push_back(DATA::TreatID);
      DataList.push_back(DATA::OrderId);
      DataList.push_back(DATA::HeatingMode);

      m_pDMTask->copyDataFromProductToPlantInterface(ProductID,ActModel,DataList);

      m_pPlantManagementInterface->showContent(ActModel, 4);

      // write EventLog
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_HeatAssignedToModel(sMessage,HeatID.c_str(),TreatID.c_str(),AssignedModel.c_str());
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_HeatAnnouncementError(sMessage,HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
    } // if ( RetValue )
  }
  
  return RetValue;
}

std::string CDM_PlantManager::getAssignedModel(const std::string& ProductID)
{
  // find first model without product assigned
  std::string AssignedModel;
  
  std::map<std::string,std::string>::iterator it;

  if (m_pPlantManagementInterface)
  {
    for (it= m_ModelList.begin(); it != m_ModelList.end();++it)
    {
      std::string ActModel = it->first;
      std::string ActProductID = m_pPlantManagementInterface->getString(ActModel,DATA::ProductID);

      if ( ActProductID == ProductID )
      {
        AssignedModel = ActModel;
        break;
      }
    }
  }

  return AssignedModel;
}

bool CDM_PlantManager::deassignProduct( CEventMessage& Event )
{
  return deassignProduct(Event.getProductID());
}

bool CDM_PlantManager::deassignProduct( const std::string& ProductID)
{
  bool RetValue = false;

  if (m_pPlantManagementInterface)
  {
    std::map<std::string,std::string>::iterator it;

    for (it= m_ModelList.begin(); it != m_ModelList.end();++it)
    {

      std::string ActModel = it->first;
      std::string ActProductID = m_pPlantManagementInterface->getString(ActModel,DATA::ProductID);
      std::string ActPlantID   = m_pPlantManagementInterface->getString(ActModel,DATA::PlantID);
      std::string ActHeatID    = m_pPlantManagementInterface->getString(ActModel,DATA::HeatID);
      std::string ActTreatID   = m_pPlantManagementInterface->getString(ActModel,DATA::TreatID);

      std::stringstream DeassignMessage;

      DeassignMessage << " try to deassign Product " << ProductID 
                      << " from model " << ActModel 
                      << " for plant " << ActPlantID
                      << " with actual Product  " << ActProductID;

      m_pDMTask->log(DeassignMessage.str(),2);

      // keep assignment if product is not identical or model must be preserved
      if ( ActProductID == ProductID )
      {
        m_pPlantManagementInterface->setString(ActModel,DATA::CustHeatID,"");
        m_pPlantManagementInterface->setString(ActModel,DATA::CustTreatID,"");
        m_pPlantManagementInterface->setString(ActModel,DATA::ProductID,"");
        m_pPlantManagementInterface->setString(ActModel,DATA::HeatID,"");
        m_pPlantManagementInterface->setString(ActModel,DATA::TreatID,"");
        m_pPlantManagementInterface->setString(ActModel,DATA::OrderId,"");
        m_pPlantManagementInterface->setLong(ActModel,DATA::TreatNo,DEF::Inv_Long);

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_HeatDeassignedFromModel(sMessage,ActHeatID.c_str(),ActTreatID.c_str(),ActModel.c_str());
        RetValue = true;

        break;
      }
      else
      {
        std::stringstream mes;

        if (ActProductID.empty() || ActProductID == DEF::Inv_String)
        {
          mes << " No Product assigned to the Model: " << ActModel;
        }
        else
        {
          mes << " Products are different " << ProductID << " and " << ActProductID;
        }

        m_pDMTask->log(mes.str(),2);
      }

    }
  }
  return RetValue;
}


bool CDM_PlantManager::findProduct(const std::string& ProductID)
{
  // find first model without product assigned
  bool isProduct = false;

  if (m_pPlantManagementInterface)
  {
    std::map<std::string,std::string>::iterator it;

    std::stringstream Message;
    Message << "CDM_PlantManager: Searchig for Product " << ProductID << " at available models!";
    m_pDMTask->log(Message.str(),2);
    
    for (it= m_ModelList.begin(); it != m_ModelList.end();++it)
    {
      std::string ActModel = it->first;
      std::string ActProductID = m_pPlantManagementInterface->getString(ActModel,DATA::ProductID);

      if ( ActProductID == ProductID )
      {
        std::stringstream Message;
        Message << "CDM_PlantManager: Product " << ProductID << " found at model " << ActModel;
        m_pDMTask->log(Message.str(),2);

        isProduct = true;
        break;
      }
    }
  }
  return isProduct;
}

void CDM_PlantManager::registerModel()
{
  std::vector<std::string> PlantList;
  std::vector<std::string> ModelList;
  std::vector<std::string> EquipmentList;
  bool ModelOnlineStatus = true;

  // search ini file for entry [Plant] : PlantID
  if ( cCBS_StdInitBase::getInstance()->replaceWithEntry(m_pDMTask->getTaskName(),"PlantId", PlantList) || 
       cCBS_StdInitBase::getInstance()->getEntryList("PLANT","PlantId", PlantList) )
  {
    std::vector<std::string>::iterator itPlant;
    for ( itPlant = PlantList.begin(); itPlant != PlantList.end(); ++itPlant)
    {
      std::string PlantID = *itPlant;

      // use values from entry [PlantID] : ModelName
      // this is e.g. used if one plant has a number on models, EAF, BOF
      if ( cCBS_StdInitBase::getInstance()->getEntryList(PlantID,"ModelName", ModelList))
      {
        std::vector<std::string>::iterator itModel;
        for ( itModel = ModelList.begin(); itModel != ModelList.end(); ++itModel)
        {
          cCBS_StdInitBase::getInstance()->replaceWithEntry(*itModel,"OnlineModel",ModelOnlineStatus);
          insertModel(*itModel,"",PlantID,ModelOnlineStatus);
          ModelOnlineStatus = true;
        }
      }
      // use values from entry [PlantID] : EquipmentName and ["EquipmentName"] : ModelName
      // this is e.g. used if one plant equipment has a number on models LF-Transfercar1, RH-TransferCar2
      else if ( cCBS_StdInitBase::getInstance()->getEntryList(PlantID,"EquipmentName", EquipmentList))
      {
        std::vector<std::string>::iterator itEquipment;
        for ( itEquipment = EquipmentList.begin(); itEquipment != EquipmentList.end(); ++itEquipment)
        {
          if ( cCBS_StdInitBase::getInstance()->getEntryList(*itEquipment,"ModelName", ModelList))
          {
            std::vector<std::string>::iterator itModel;
            for ( itModel = ModelList.begin(); itModel != ModelList.end(); ++itModel)
            {
              cCBS_StdInitBase::getInstance()->replaceWithEntry(*itModel,"OnlineModel",ModelOnlineStatus);
              insertModel(*itModel,*itEquipment,PlantID,ModelOnlineStatus);
              ModelOnlineStatus = true;
            }
          }
        }
      }
      else
      {
        cCBS_StdInitBase::getInstance()->replaceWithEntry(PlantID,"OnlineModel",ModelOnlineStatus);
        log("WARNING: Register Plant as an available model",2);
        insertModel(PlantID,"","",ModelOnlineStatus);
      }
    }// for ( itPlant = PlantList.begin(); itPlant != PlantList.end(); ++itPlant)
  }
  else
  {
    // use values from entry [Task] : Model
    std::string TaskName    = m_pDMTask->getTaskName();
    std::string ModelEntry  = "Model";
    
    cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"Model", ModelEntry);

    // use values from entry [ModelEntry] : ServerName 
    if ( cCBS_StdInitBase::getInstance()->getEntryList(ModelEntry,"ServerName", ModelList))
    {
      std::vector<std::string>::iterator itModel;
      for ( itModel = ModelList.begin(); itModel != ModelList.end(); ++itModel)
      {
        std::string PlantID;
        cCBS_StdInitBase::getInstance()->replaceWithEntry(*itModel,"PlantId",PlantID);
        cCBS_StdInitBase::getInstance()->replaceWithEntry(*itModel,"OnlineModel",ModelOnlineStatus);
        insertModel(*itModel,"",PlantID,ModelOnlineStatus);
        ModelOnlineStatus = true;
      }
    }
    else
    {
      std::string PlantID;
      cCBS_StdInitBase::getInstance()->replaceWithEntry(ModelEntry,"PlantId",PlantID);
      cCBS_StdInitBase::getInstance()->replaceWithEntry(ModelEntry,"OnlineModel",ModelOnlineStatus);
      insertModel(ModelEntry,"",PlantID,ModelOnlineStatus);
    }
  }
}

bool CDM_PlantManager::findModel(const std::string& ModelName)
{
  bool RetValue = false;

  if (m_pPlantManagementInterface)
  {
    long Size = m_pPlantManagementInterface->getSize();
    
    for ( long i = 0; i < Size; ++i )
    {
      std::string ActKey = m_pPlantManagementInterface->getKey(i);

      if ( ActKey == ModelName )
      {
        RetValue = true;
        break;
      }
    }
  }
  return RetValue;
}

bool CDM_PlantManager::insertModel(const std::string& ModelName, const std::string& EquipmentId, const std::string &PlantID, bool OnlineStatus)
{
  bool RetValue = false;
  if (m_pPlantManagementInterface)
  {
    if ( !findModel(ModelName) )
    {
      // hold manager specific list of defined model names from inifile
      m_ModelList.insert(std::pair<std::string,std::string> (ModelName,EquipmentId) );

      std::string ModelMessage   = " model " + ModelName;

      std::string ProcessMessage = cCBS_StdInitBase::getInstance()->m_ServerName;
      if ( !EquipmentId.empty() )
      {
        ProcessMessage = ProcessMessage + " - " + EquipmentId;
      }

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ProcessAvailable(sMessage,ModelMessage.c_str(),ProcessMessage.c_str());

      m_pPlantManagementInterface->setString(ModelName,DATA::ActModel,ModelName);
      if (!PlantID.empty())
      {
        m_pPlantManagementInterface->setString(ModelName,DATA::PlantID,PlantID);
      }

      m_pPlantManagementInterface->setPersistence(ModelName,true);
      RetValue = true;
    }
  }
  return RetValue;
}

bool CDM_PlantManager::changePlantInformation(CEventMessage& Event)
{
  m_pDMTask->log("!!!!! CDM_PlantManager::changePlantInformation.. not implemented !", 9);
  return false;
}

bool CDM_PlantManager::changeComputerModes(CEventMessage& Event)
{
  m_pDMTask->log("!!!!! CDM_PlantManager::changeComputerModes.. not implemented !", 9);
  return false;
}

bool CDM_PlantManager::changeAvailabilities(CEventMessage& Event)
{
  m_pDMTask->log("!!!!! CDM_PlantManager::changeAvailabilities.. not implemented !", 9);
	return false;
}

bool CDM_PlantManager::changeLadleData(CEventMessage& Event)
{
  m_pDMTask->log("!!!!! CDM_PlantManager::changeLadleData.. not implemented !", 9);
	return false;
}

bool CDM_PlantManager::changeTappingData(CEventMessage& Event)
{
  m_pDMTask->log("!!!!! CDM_PlantManager::changeTappingData.. not implemented !", 9);
	return false;
}

bool CDM_PlantManager::changeStirringData(CEventMessage& Event)
{
  m_pDMTask->log("!!!!! CDM_PlantManager::changeStirringData.. not implemented !", 9);
	return false;
}

bool CDM_PlantManager::changeBlowingData(CEventMessage& Event)
{
  m_pDMTask->log("!!!!! CDM_PlantManager::changeBlowingData.. not implemented !", 9);
	return false;
}

bool CDM_PlantManager::changeBurningData(CEventMessage& Event)
{
  m_pDMTask->log("!!!!! CDM_PlantManager::changeBurningData.. not implemented !", 9);
	return false;
}


bool CDM_PlantManager::changeGasData(CEventMessage& Event   )
{
  m_pDMTask->log("!!!!! CDM_PlantManager::changeGasData.. not implemented !", 9);
  return false;
}


void CDM_PlantManager::resetPlantManager(CEventMessage &Event)
{
  m_pDMTask->log("!!!!! CDM_PlantManager::resetPlantManager.. not implemented !", 9);
}

bool CDM_PlantManager::changeTapLadleStirringData(CEventMessage& Event)
{
  m_pDMTask->log("!!!!! CDM_PlantManager::changeTapLadleStirringData.. not implemented !", 9);
	return false;
}
void CDM_PlantManager::resetBlowingData(CEventMessage& Event)
{
  m_pDMTask->log("!!!!! CDM_PlantManager::resetBlowingData.. not implemented !", 9);
}

void CDM_PlantManager::resetComputerModes(CEventMessage& Event)
{
  m_pDMTask->log("!!!!! CDM_PlantManager::resetComputerModes.. not implemented !", 9);
}

bool CDM_PlantManager::findProduct(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  
  if ( findProduct(ProductID) )
  {
    RetValue = true;
  }
  else
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorDetectingHeat(sMessage,HeatID.c_str(),TreatID.c_str(),Event.getMessage().c_str());
  }

	return RetValue;
}



bool CDM_PlantManager::changeWasteGasData(CEventMessage& Event)
{
  m_pDMTask->log("!!!!! CDM_PlantManager::changeWasteGasData.. not implemented !", 9);
  return false;
}

bool CDM_PlantManager::changeCoolingWaterData(CEventMessage& Event)
{
  m_pDMTask->log("!!!!! CDM_PlantManager::changeCoolingWaterData.. not implemented !", 9);
  return false;
}



void CDM_PlantManager::resetStirringData(CEventMessage& Event)
{
  m_pDMTask->log("!!!!! CDM_PlantManager::resetStirringData.. not implemented !", 9);
}



void CDM_PlantManager::fillGasDataHandler(CDM_GasDataHandler& GasDataHandler, seqGasData* seqData)
{
  GasDataHandler.clear();

  long ActLength = CIntfData::getLength(*seqData);
  for ( long i = 0 ; i < ActLength; ++i )
  {
    sGasData GasStruct ; 
    // init availabilities to actual state
    CIntfData::getAt(GasStruct,seqData,i);
    GasDataHandler.setGasData(std::string(GasStruct.GasType),GasStruct.GasValue);
  }
}

void CDM_PlantManager::fillGasDataHandler(CDM_GasDataHandler& GasDataHandler, std::vector<std::string>& seqData, double Value)
{
  GasDataHandler.clear();

  std::vector<std::string>::iterator it;
  for ( it = seqData.begin(); it != seqData.end(); ++it)
  {
    std::string GasDataName = (*it);
    GasDataHandler.addGasData(GasDataName,Value);
  }
}

void CDM_PlantManager::fillGasDataSequence(CDM_GasDataHandler& GasDataHandler, seqGasData& seqData)
{
  std::map<std::string,double> GasDataList;
  std::map<std::string,double>::iterator it;

  sGasData GasStruct ; 

  GasDataList = GasDataHandler.getGasDataList();

  for ( it  = GasDataList.begin(); it != GasDataList.end(); ++it)
  {
    GasStruct.GasType = it->first.c_str();
    GasStruct.GasValue = it->second;
    CIntfData::insert(seqData,GasStruct);
  }

}

void CDM_PlantManager::initGasData(const std::string& Key, const std::string& Data, double Init)
{
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " ;

  try
  {
    if (m_pPlantManagementInterface)
    {
      CDM_GasDataHandler GasDataHandler;
      seqGasData GasData; 

      // fill GasDataHandler with GasTypeList enries and init GasData with Init
      fillGasDataHandler(GasDataHandler,m_GasTypeList,Init);

      // write 0 data to ProductManagementInterface
      fillGasDataSequence(GasDataHandler,GasData);
      m_pPlantManagementInterface->setGasData(Key.c_str(),Data.c_str(),GasData);

    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                          "CDM_PlantManager::initGasData",
                                          ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                          "CDM_PlantManager::initGasData",
                                          ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                          "CDM_PlantManager::initGasData",
                                          ExceptionMsg.str().c_str());
  }

}



bool CDM_PlantManager::changeElectricalData(CEventMessage& Event)
{
  m_pDMTask->log("!!!!! CDM_PlantManager::changeElectricalData.. not implemented !", 9);
  return false;
}



std::string CDM_PlantManager::getRelevantTransferCar(CEventMessage& Event)
{
  std::string RetValue;
  m_pDMTask->log("!!!!! CDM_PlantManager::getRelevantTransferCar.. not implemented !", 9);
  return RetValue;
}


bool CDM_PlantManager::changeInjectionData(CEventMessage& Event)
{
  m_pDMTask->log("!!!!! CDM_PlantManager::changeInjectionData.. not implemented !", 9);
  return false;
}

bool CDM_PlantManager::changeVacuumData(CEventMessage& Event)
{
  m_pDMTask->log("!!!!! CDM_PlantManager::changeVacuumData.. not implemented !", 9);
  return false;
}

bool CDM_PlantManager::changeLiftGasData(CEventMessage& Event)
{
  m_pDMTask->log("!!!!! CDM_PlantManager::changeLiftGasData.. not implemented !", 9);
  return false;
}

std::string CDM_PlantManager::getPlantEquipmentData(const std::string& Equipment)
{
  m_pDMTask->log("!!!!! CDM_PlantManager::getPlantEquipmentData.. not implemented !", 9);
  return std::string("");
}

std::string CDM_PlantManager::getProductAtPlantEquipment(const std::string& Equipment)
{
  m_pDMTask->log("!!!!! CDM_PlantManager::getProductAtPlantEquipment.. not implemented !", 9);
  return std::string("");
}

std::string CDM_PlantManager::getPlantEquipmentOfProduct(const std::string& ProductID)
{
  m_pDMTask->log("!!!!! CDM_PlantManager::getPlantEquipmentOfProduct.. not implemented !", 9);
  return std::string("");
}


void CDM_PlantManager::initWasteGasData(const std::string& Key     )
{
  m_pPlantManagementInterface->setDouble(Key,DATA::WasteGasFlow,0.0);
  m_pPlantManagementInterface->setDouble(Key,DATA::WasteGasTemp,0.0);

  seqWasteGas WasteGas;

 std::vector<std::string>::iterator itWasteGasTypeList;
  // for ech member of m_WasteGasTypeList
  for ( itWasteGasTypeList = m_WasteGasTypeList.begin() ; 
        itWasteGasTypeList != m_WasteGasTypeList.end() ; 
        ++itWasteGasTypeList)
  {
    // search for all Gas types in actual member of m_WasteGasDeviceList
    sWasteGas WasteGasStruct;
    WasteGasStruct.WasteGasConc = 0.0;
    WasteGasStruct.WasteGasType = (*itWasteGasTypeList).c_str();

    CIntfData::insert(WasteGas,WasteGasStruct);
  }

  m_pPlantManagementInterface->setWasteGas(Key.c_str(),DATA::WasteGasConc,WasteGas);
}

void CDM_PlantManager::log(const std::string& Message, long Level)
{
  m_pDMTask->log(Message, Level);
}

void CDM_PlantManager::getAdditionallyMessages(std::vector<std::string>& Messages)
{
  std::vector<std::string>::iterator it;
  for (it = m_AdditionallyMessages.begin(); it != m_AdditionallyMessages.end(); it++)
  {
    Messages.push_back(*it);
    log(std::string("Reading additionally event message to send:") + *it,2);
  }
  // clear
  m_AdditionallyMessages.clear();
}

void CDM_PlantManager::addEventMessageToSend(std::string Message)
{
  m_AdditionallyMessages.push_back(Message);
}

void CDM_PlantManager::initStirringDataSequence(const std::string& Key, std::vector<std::string>& m_StirringDef, std::vector<std::string>& m_StirringDevices, double Init)
{
  seqStirringData SeqStirrData;
  sStirringData theStirring;
  seqGasData SeqGasData;
  sGasData theGasData;

  //init gas data sequence
  for( long k = 0; k < (long)m_GasTypeList.size(); ++k)
  {
    theGasData.GasType = m_GasTypeList[k].c_str();
    theGasData.GasValue = Init;
    CIntfData::insert(SeqGasData, theGasData);
  }

  //init stirring sequence
  for( long j = 0; j < (long)m_StirringDevices.size(); ++j)
  {
    theStirring.GasData = SeqGasData;
    theStirring.Device = m_StirringDevices[j].c_str();
    CIntfData::insert(SeqStirrData, theStirring);
  }

  //set stirring sequence in interface
  for( long i = 0; i < (long)m_StirringDef.size(); ++i)
  {
    m_pPlantManagementInterface->setStirringData(Key.c_str(), m_StirringDef[i].c_str(), SeqStirrData);
  }
  
  return;
}

void CDM_PlantManager::initStatusSequence(const std::string& Key, std::vector<std::string>& m_StatusDef, std::vector<std::string>& m_StatusDevices, long Init)
{
  seqStatus SeqStatus;
  sStatus theStatus;

  for (long j = 0; j < (long)m_StatusDevices.size(); ++j)
  {
    theStatus.Device = m_StatusDevices[j].c_str();
    theStatus.Status = Init;
    CIntfData::insert(SeqStatus, theStatus);
  }

  for (long i = 0; i < (long)m_StatusDef.size(); ++i)
  {
    m_pPlantManagementInterface->setStatus(Key.c_str(), m_StatusDef[i].c_str(), SeqStatus);
  }
}

bool CDM_PlantManager::changeConverterPosition(CEventMessage& Event)
{
  bool RetValue = false;
  std::string DataKey = Event.getDataKey();
  std::string Message = Event.getMessage();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << Event.getProductID() << ", " << Event.getHeatID()
    << ", " << Event.getTreatID() << ", " << DataKey;

  try
  {
    if ( m_pPlantManagementInterface && m_pDataInterface )
    {
      // copy Plant relevant data from Event interface
      std::vector<std::string> NameList;
      NameList.push_back(DATA::ConverterAngle);
      NameList.push_back(DATA::ConverterPosition);

      long ConverterPositionPrev = m_pPlantManagementInterface->getLong(DEF_PLANT::Furnace, DATA::ConverterPosition);

      // set new converter data
      CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,
        m_pPlantManagementInterface,
        DataKey,
        DEF_PLANT::Furnace,
        NameList);

      long ConverterPositionAct = m_pPlantManagementInterface->getLong(DEF_PLANT::Furnace, DATA::ConverterPosition);

      if ( ConverterPositionPrev != ConverterPositionAct )
      {
        //converter position has been changed
        RetValue = true; // event will be sent to archiver to store this change
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      "CDM_PlantManager::changeConverterPosition()",
      ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      "CDM_PlantManager::changeConverterPosition()",
      ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
      "CDM_PlantManager::changeConverterPosition()",
      ExceptionMsg.str().c_str());
  }
  return RetValue;
}
