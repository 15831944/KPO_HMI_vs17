// Copyright (C) 2009 SMS Demag AG

#include <iomanip>

#include "iSMC_DataDefinitions_s.hh"

#include "cCBS_StdLog_Task.h"
#include "cCBS_StdDB_Task.h"

#include "CEventMessage.h"
#include "CIntfData.h"
#include "CDataConversion.h"
#include "CProductID.h"
#include "CGasDataHandler.h"

#include "CSMC_EventLogFrameController.h"

#include "CDM_DataInterface_Impl.h"
#include "CDM_Task.h"
#include "CDM_StatusHandler.h"
#include "CDM_ProductManagementInterface_Impl.h"
#include "CDM_PlantManagementInterface_Impl.h"
#include "CDM_GasDataHandler.h"
#include "CDM_SampleManager.h"

#include "CGC_Plant_Container.h"
#include "DEF_GC_MEASUREMENT_TYPE.h"
#include "DEF_GC_MEASUREMENT_ORIGIN.h"
#include "DEF_GC_SAMPLELOC.h"
#include "DEF_GC_SAMPLEUSABLE.h"

#include "CDM_ProductManager.h"


CDM_ProductManager::CDM_ProductManager(const std::string& newTreatIDPrefix)
: m_pProductManagementInterface( 0 )
, m_pDataInterface( 0 )
, m_TreatIDPrefix(newTreatIDPrefix)
, m_pGC_Plant_Container(0)
{

}

CDM_ProductManager::~CDM_ProductManager()
{
}

bool CDM_ProductManager::changeAssignedModel(CEventMessage& Event, const std::string& AssignedModel)
{
  return changeAssignedModel(Event.getProductID(), AssignedModel);
}

bool CDM_ProductManager::changeAssignedModel(const std::string& ProductID, const std::string& AssignedModel)
{
  bool RetValue = false;

  std::string ActProduct = ProductID;

  if (m_pProductManagementInterface)
  {
    if ( findProduct(ActProduct) )
    {
      m_pProductManagementInterface->setString(ActProduct,DATA::ActModel,AssignedModel);
      
      // reset persistance of Product if no longer assigned to model !
      if ( AssignedModel.empty() )
      {
        log("INFO: setting persistence to false for product " + ActProduct, 3);
        m_pProductManagementInterface->setPersistence(ActProduct,false);
      }
      else
      {
        log("INFO: setting persistence true for product " + ActProduct, 3);
        m_pProductManagementInterface->setPersistence(ActProduct,true);
      }

      RetValue = true;
    }
  }
  return RetValue;
}


bool CDM_ProductManager::changeOrderData(CEventMessage& Event, const std::string& OrderId)
{
  bool RetValue = false;
  
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();

  if ( findProduct(ProductID,HeatID,TreatID) )
  {
    if (m_pProductManagementInterface)
    {

      std::string OldOrderID = m_pProductManagementInterface->getString(ProductID,DATA::OrderId);
      m_pProductManagementInterface->setString(ProductID,DATA::OrderId,OrderId);

      std::string Mes = "Changed Order of " + ProductID;
      Mes += " from " + OldOrderID + " to " + OrderId;
      log(Mes,3);
      RetValue = true;
    }
  }
  return RetValue;
}


bool CDM_ProductManager::changeProductInformation(CEventMessage& Event)
{
  log("!!!!! CDM_ProductManager::changeProductInformation.. not implemented !", 9);
  return false;
}

bool CDM_ProductManager::findActualPlantLocation(std::string& ProductID, std::string& HeatID, std::string& TreatID, std::string& OrderId, std::string& PlantLocation)
{
  bool RetValue = false;

  std::stringstream Message;
  Message << "CDM_ProductManager::findActualPlantLocation searching for " 
          << "  ProductID "<< ProductID 
          << "  HeatID "<< HeatID
          << "  TreatID "<< TreatID
          << "  OrderId "<< OrderId
          << "  PlantLocation "<< PlantLocation;

  log(Message.str(),2);


  if ( PlantLocation.empty() || PlantLocation == DEF::Inv_String )
  {
    log("CDM_ProductManager::findActualPlantLocation() empty or invalid PlantLocation received",2);
  }
  else
  {
    if (m_pProductManagementInterface)
    {
      long Size = m_pProductManagementInterface->getSize();
      
      for ( long i = 0; i < Size; ++i )
      {
        std::string ActKey           = m_pProductManagementInterface->getKey(i);
        std::string ActPlantLocation = m_pProductManagementInterface->getString(ActKey,DATA::ActPlantLocation);

        if ( PlantLocation == ActPlantLocation && ActPlantLocation != DEF::Inv_String )
        {
          std::stringstream Message;
          ProductID = ActKey;

          std::string FoundHeatID  = m_pProductManagementInterface->getString(ActKey,DATA::HeatID);
          std::string FoundTreatID = m_pProductManagementInterface->getString(ActKey,DATA::TreatID);
          std::string FoundOrderID = m_pProductManagementInterface->getString(ActKey,DATA::OrderId);

          HeatID  = (FoundHeatID != DEF::Inv_String)?FoundHeatID:HeatID;
          TreatID = (FoundTreatID != DEF::Inv_String)?FoundTreatID:TreatID;
          OrderId = (FoundOrderID != DEF::Inv_String)?FoundOrderID:OrderId;


          Message << "Product " << ProductID 
                  << " found at m_pProductManagementInterface for " << ActPlantLocation
                  << " returning HeatID " << HeatID
                  << " returning TreatID " << TreatID
                  << " returning OrderId " << OrderId;
          log(Message.str(),3);

          RetValue = true;
          break;
        }
      }
    }
  }
  return RetValue;
}

bool CDM_ProductManager::findActualProduct(std::string& ProductID, std::string& HeatID, std::string& TreatID, std::string& OrderId)
{
  bool RetValue = false;

  std::stringstream Message;
  Message << "CDM_ProductManager::findActualProduct searching for " 
          << "  ProductID "<< ProductID 
          << "  HeatID "<< HeatID
          << "  TreatID "<< TreatID;

  log(Message.str(),3);

  if (m_pProductManagementInterface && m_pDMTask->getpPlantManagementInterface())
  {
    // try to find ProductID for DEF_PLANT::Furnace at PlantManagerInterface
    std::string ActProduct = m_pDMTask->getpPlantManagementInterface()->getString(DEF_PLANT::Furnace,DATA::ProductID);

    // product can only be taken when identical , not empty and not invalid
    if ( ActProduct == ProductID && 
        !ActProduct.empty() &&
         ActProduct != DEF::Inv_String )
    {
      std::stringstream Message;

      ProductID = ActProduct;
      std::string FoundHeatID    = m_pProductManagementInterface->getString(ActProduct,DATA::HeatID);
      std::string FoundTreatID   = m_pProductManagementInterface->getString(ActProduct,DATA::TreatID);
      std::string FoundOrderID   = m_pProductManagementInterface->getString(ActProduct,DATA::OrderId);

      HeatID  = (FoundHeatID != DEF::Inv_String)?FoundHeatID:HeatID;
      TreatID = (FoundTreatID != DEF::Inv_String)?FoundTreatID:TreatID;
      OrderId = (FoundOrderID != DEF::Inv_String)?FoundOrderID:OrderId;

      Message << "Product " << ProductID 
            << " found as ActualProduct at m_pPlantManagementInterface for " << DEF_PLANT::Furnace
            << " returning HeatID " << HeatID
            << " returning TreatID " << TreatID
            << " returning OrderId " << OrderId;
      log(Message.str(),3);

      RetValue = true;
    }
    else
    {
      Message << "Product " << ProductID 
            << " NOT found at m_pPlantManagementInterface ";
      log(Message.str(),1);
    }
  }
  return RetValue;
}

bool CDM_ProductManager::findProductByEquipment(CEventMessage& Event, std::string& ProductID, std::string& HeatID, std::string& TreatID, std::string& OrderId)
{
  m_pDMTask->log("!!!!! CDM_ProductManager::findProductByEquipment.. not implemented !", 9);
  return false;
}

bool CDM_ProductManager::findHeat(std::string& ProductID, std::string& HeatID, std::string& TreatID, std::string& OrderId)
{
  bool RetValue = false;

  std::stringstream Message;
  Message << "CDM_ProductManager::findHeat searching for " 
          << "  ProductID "<< ProductID 
          << "  HeatID "<< HeatID
          << "  TreatID "<< TreatID
          << "  OrderId "<< OrderId;

  log(Message.str(),3);



  // find heat at ProductManagementInterface

  if ( HeatID.empty() || HeatID == DEF::Inv_String )
  {
    log("CDM_ProductManager::findHeat() invalid or empty HeatID detected",2);
  }
  else
  {
    if (m_pProductManagementInterface)
    {
      std::stringstream Message;
      Message << "Trying to find Product by HeatID " << HeatID << " and TreatID " << TreatID;
      log(Message.str(),3);

      // try to find product by comparing HeatID and TreatID first 
      long Size = m_pProductManagementInterface->getSize();
      
      for ( long i = 0; i < Size; ++i )
      {
        std::string ActKey     = m_pProductManagementInterface->getKey(i);
        std::string ActHeatID  = m_pProductManagementInterface->getString(ActKey,DATA::HeatID);

        if ( HeatID == ActHeatID )
        {
          std::string ActTreatID = m_pProductManagementInterface->getString(ActKey,DATA::TreatID);
          long ActTreatNo        = m_pProductManagementInterface->getLong(ActKey,DATA::TreatNo);
          std::string ActOrderID = m_pProductManagementInterface->getString(ActKey,DATA::OrderId);

          // search only with valid TreatID if exists
          if( TreatID != DEF::Inv_String && !TreatID.empty() )
          {
            if( TreatID == ActTreatID )
            {
              std::stringstream Message;
              Message << "Heat " << HeatID << " found at m_pProductManagementInterface!";
              log(Message.str(),2);

              HeatID  = ActHeatID;
              TreatID = ActTreatID;
              ProductID = ActKey;
              if ( !ActOrderID.empty() && ActOrderID != DEF::Inv_String )
                OrderId = ActOrderID;
              else
                log("WARNING: No order id available to supplement event with it!",2);

              RetValue = true;
              break;
            }// if( TreatID == ActTreatID )
          }// if( TreatID != DEF::Inv_String && !TreatID.empty() )
        }// if ( HeatID == ActHeatID )
      }// for ( long i = 0; i < Size; ++i )
    }// if (m_pProductManagementInterface)
  }

  return RetValue;
}

bool CDM_ProductManager::findProduct(std::string& ProductID, std::string& HeatID, std::string& TreatID, std::string& OrderId)
{
  bool RetValue = false;

  std::stringstream Message;
  Message << "CDM_ProductManager::findProduct searching by product for " 
          << "  ProductID "<< ProductID 
          << "  HeatID "<< HeatID
          << "  TreatID "<< TreatID
          << "  OrderId "<< OrderId;

  log(Message.str(),2);


  //if ( ( ProductID.empty() || ProductID == DEF::Inv_String ) &&
  //     ( HeatID.empty()    || HeatID    == DEF::Inv_String )    )
  if ( ProductID.empty() || ProductID == DEF::Inv_String )
  {
    log("CDM_ProductManager::findProduct(...) empty or invalid ProductID received",2);
  }
  else
  {
    bool KeyFound = false;

    if (m_pProductManagementInterface)
    {
      if (m_pProductManagementInterface->isKey(ProductID) )
      {
        KeyFound = true;
      }
      // commented out because findLastTreatNo returns previous heat 
      //else
      //{
      //  // first try to find simple solution for existing heatid and treatid 
      //  CProductID ID(m_TreatIDPrefix);
      //  ProductID = ID.getValidProductID(ProductID, HeatID, TreatID);

      //  // ProductID is not valid, try to find it by using last TreatNo
      //  if ( ProductID == DEF::Inv_String )
      //  {
      //    long LastTreatNo = findLastTreatNo(HeatID);

      //    ProductID = ID.getValidProductID(ProductID, HeatID, TreatID, LastTreatNo);
      //  }

      //  if (m_pProductManagementInterface->isKey(ProductID) )
      //  {
      //    KeyFound = true;
      //  }
      //}
    }

    if (KeyFound)
    {
      std::stringstream Message;
      Message << "Product '" << ProductID << "' found at m_pProductManagementInterface!";
      log(Message.str(),2);

      std::string FoundHeatID  = m_pProductManagementInterface->getString(ProductID,DATA::HeatID);
      std::string FoundTreatID = m_pProductManagementInterface->getString(ProductID,DATA::TreatID);
      std::string FoundOrderID = m_pProductManagementInterface->getString(ProductID,DATA::OrderId);

      HeatID  = (!FoundHeatID.empty() && FoundHeatID != DEF::Inv_String)?FoundHeatID:HeatID;
      TreatID = (!FoundTreatID.empty() && FoundTreatID != DEF::Inv_String)?FoundTreatID:TreatID;
      if ( !FoundOrderID.empty() && FoundOrderID != DEF::Inv_String )
        OrderId = FoundOrderID;
      else
        log("WARNING: No order id available to supplement event with it!",2);

      RetValue = true;
    }
    else
    {
      std::stringstream Message;
      Message << "ERROR: Product " << ProductID << " not found at m_pProductManagementInterface!";
      log(Message.str(),1);
    }
  }

  return RetValue ;
}

bool CDM_ProductManager::findProduct(std::string& ProductID, std::string& HeatID, std::string& TreatID)
{
  bool RetValue = false;

  std::stringstream Message;
  Message << "CDM_ProductManager::findProduct searching for " 
          << "  ProductID "<< ProductID 
          << "  HeatID "<< HeatID
          << "  TreatID "<< TreatID;

  log(Message.str(),2);


  if ( ( ProductID.empty() || ProductID == DEF::Inv_String ) &&
       ( HeatID.empty()    || HeatID    == DEF::Inv_String )    )
  {
    log("CDM_ProductManager::findProduct(...) empty or invalid HeatID and ProductID received",2);
  }
  else
  {
    bool KeyFound = false;

    if (m_pProductManagementInterface)
    {
      if (m_pProductManagementInterface->isKey(ProductID) )
      {
        KeyFound = true;
      }
      /**  don't use this strategy to find product because wrong product will be found
      else
      {
        // first try to find simple solution for existing heatid and treatid 
        CProductID ID(m_TreatIDPrefix);
        ProductID = ID.getValidProductID(ProductID, HeatID, TreatID);

        // ProductID is not valid, try to find it by using last TreatNo
        if ( ProductID == DEF::Inv_String )
        {
          long LastTreatNo = findLastTreatNo(HeatID);

          ProductID = ID.getValidProductID(ProductID, HeatID, TreatID, LastTreatNo);
        }

        if (m_pProductManagementInterface->isKey(ProductID) )
        {
          KeyFound = true;
        }
      }
      **/
    }

    if (KeyFound)
    {
      std::stringstream Message;
      Message << "Product " << ProductID << " found at m_pProductManagementInterface!";
      log(Message.str(),2);

      std::string FoundHeatID  = m_pProductManagementInterface->getString(ProductID,DATA::HeatID);
      std::string FoundTreatID = m_pProductManagementInterface->getString(ProductID,DATA::TreatID);

      HeatID  = (FoundHeatID != DEF::Inv_String)?FoundHeatID:HeatID;
      TreatID = (FoundTreatID != DEF::Inv_String)?FoundTreatID:TreatID;

      RetValue = true;
    }
    else
    {
      std::stringstream Message;
      Message << "Product " << ProductID << " not found at m_pProductManagementInterface!";
      log(Message.str(),2);

    }
  }

  return RetValue ;
}

// for use at getProcessState
bool CDM_ProductManager::findProduct(std::string& ProductID)
{
  bool RetValue = false;

  std::stringstream Message;
  Message << "CDM_ProductManager::findProduct searching for " 
          << "  ProductID "<< ProductID ;

  log(Message.str(),2);

  if ( ProductID.empty() || ProductID == DEF::Inv_String ) 
  {
    log("CDM_ProductManager::findProduct(.) empty or invalid ProductID received",2);
  }
  else
  {
    if (m_pProductManagementInterface && m_pProductManagementInterface->isKey(ProductID) )
    {
      RetValue = true;

      std::stringstream Message;
      Message << "Product " << ProductID << " found at m_pProductManagementInterface!";
      log(Message.str(),2);
    }
    else
    {
      std::stringstream Message;
      Message << "Product " << ProductID << " not found at m_pProductManagementInterface!";
      log(Message.str(),2);
    }
  }

  return RetValue ;
}


bool CDM_ProductManager::registerProduct(CEventMessage& Event)
{
  bool RetValue = false;
  
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string OrderId   = Event.getOrderID();

  RetValue = registerProduct(ProductID,HeatID,TreatID,OrderId);

  Event.setProductID(ProductID);
  Event.setHeatID(HeatID);
  Event.setTreatID(TreatID);
  Event.setOrderID(OrderId);

  return RetValue;
}

bool CDM_ProductManager::removeProduct(std::string& ProductID, std::string& HeatID, std::string& TreatID)
{
  log("!!!!! CDM_ProductManager::removeProduct.. not implemented !", 9);
  return false;
}

void CDM_ProductManager::addProduct(std::string& ProductID, std::string& HeatID, std::string& TreatID, std::string& OrderId)
{
  if (m_pProductManagementInterface)
  {
    log("INFO: CDM_ProductManager::addProduct",3);
    m_pProductManagementInterface->setString(ProductID,DATA::HeatID,HeatID);
    m_pProductManagementInterface->setString(ProductID,DATA::TreatID,TreatID);
    m_pProductManagementInterface->setString(ProductID,DATA::OrderId,OrderId);
    m_pProductManagementInterface->setString(ProductID,DATA::ProductID,ProductID);
  }
  return;
}

long CDM_ProductManager::findLastTreatNo(std::string& HeatID)
{
  long LastTreatNo = 0;
  long TreatNo = 0;

  std::stringstream Message;
  Message << "CDM_ProductManager::findLastTreatNo searching for " 
          << "  HeatID "<< HeatID;

  log(Message.str(),2);


  if ( HeatID.empty() || HeatID == DEF::Inv_String )
  {
    log("CDM_ProductManager::findLastTreatNo() invalid or empty HeatID detected",2);
  }
  else
  {
    if (m_pProductManagementInterface)
    {
      long Size = m_pProductManagementInterface->getSize();
      
      for ( long i = 0; i < Size; ++i )
      {
        std::string ActKey    = m_pProductManagementInterface->getKey(i);
        std::string ActHeatID = m_pProductManagementInterface->getString(ActKey,DATA::HeatID);

        if ( ActHeatID == HeatID )
        {
          TreatNo = m_pProductManagementInterface->getLong(ActKey,DATA::TreatNo);
          LastTreatNo = max(LastTreatNo,TreatNo);
        }
      }
    }
  }

  return LastTreatNo;
}

bool CDM_ProductManager::registerProduct(std::string& ProductID, std::string& HeatID, std::string& TreatID, std::string& OrderId)
{

  bool RetValue = true;

  if (  ( HeatID.empty() && ProductID.empty() ) || 
        ( ProductID == DEF::Inv_String )            )
  {
    // worst case, heat cannot be announced!. No valid identification data available
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_UnspecificEventReceived(sMessage);

    RetValue = false;
  }
  else
  {
    // generate HeatID and TreatID from ProductID or vice versa
    CProductID PID;

    if ( HeatID.empty() )
    {
      HeatID    = PID.getHeatID(ProductID);
      TreatID   = PID.getTreatID(ProductID);
    }
    else if ( ProductID.empty() )
    {
      ProductID = PID.getProductID(HeatID, TreatID);
    }

    //add product to ProductManagementInterface
    addProduct(ProductID, HeatID, TreatID, OrderId);
  }

  return RetValue;
}

void CDM_ProductManager::init(CDM_Task *pDMTask)
{
  m_pDMTask = pDMTask;
  m_pProductManagementInterface = m_pDMTask->getpProductManagementInterface();
  m_pDataInterface              = m_pDMTask->getpDataInterface();

  cCBS_StdConnection* pConnection = m_pDMTask->getStdConnection();
  if (pConnection)
  {
    m_pGC_Plant_Container = new CGC_Plant_Container(pConnection);
  }

}

bool CDM_ProductManager::changeSampleInformation(CEventMessage& Event)
{
  return false;
}

bool CDM_ProductManager::changeBlowingData(CEventMessage& Event)
{
  log("!!!!! CDM_ProductManager::changeBlowingData.. not implemented !", 9);
	return false;
}

bool CDM_ProductManager::changeBurningData(CEventMessage& Event)
{
  log("!!!!! CDM_ProductManager::changeBurningData.. not implemented !", 9);
	return false;
}

bool CDM_ProductManager::changeTappingData(CEventMessage& Event)
{
  log("!!!!! CDM_ProductManager::changeTappingData.. not implemented !", 9);
  return false;
}

bool CDM_ProductManager::changeStirringData(CEventMessage& Event)
{
  log("!!!!! CDM_ProductManager::changeStirringData.. not implemented !", 9);
  return false;
}

bool CDM_ProductManager::changeAnalysisInformation(CEventMessage& Event)
{
  log("!!!!! CDM_ProductManager::changeAnalysisInformation.. not implemented !", 9);
  return false;
}

std::string CDM_ProductManager::setSampleData( CEventMessage& Event,  long ActSampleType)
{
  std::string PlantID    = Event.getPlantID();
  std::string ProductID  = Event.getProductID();
  std::string DataKey    = Event.getDataKey();

  long SampleNo         = DEF::Inv_Long;
  long SampleUsable    = DEF::Inv_Long;
  long SampleMode       = DEF::Inv_Long;
  long SampleType       = DEF::Inv_Long;
  long SampleOrigin     = DEF::Inv_Long;

  CDateTime Now;

  std::string SampleId;
  std::string ProcessStage;
  std::string SampleLocation;
  std::string SampleCode;

  sDate SampleTime; 

  if (m_pDataInterface && m_pProductManagementInterface )
  {
    // in case of hot metal sample a HMP-PlantID in interface is available and 
    // must be taken to create hot metal specific sample code
    if (m_pDataInterface->getString(DataKey,DATA::PlantID) != DEF::Inv_String)
    {
      PlantID = m_pDataInterface->getString(DataKey,DATA::PlantID);
    }

    SampleType      = m_pDataInterface->getLong(DataKey, DATA::SampleType);
    SampleNo        = m_pDataInterface->getLong(DataKey, DATA::SampleNo);
    SampleUsable   = m_pDataInterface->getLong(DataKey, DATA::SampleUsable);
    SampleMode      = m_pDataInterface->getLong(DataKey, DATA::SampleMode);
    SampleOrigin    = m_pDataInterface->getLong(DataKey, DATA::SampleOrigin);

    SampleId        = m_pDataInterface->getString(DataKey, DATA::SampleId);
    ProcessStage    = m_pDataInterface->getString(DataKey, DATA::ProcessStage);
    SampleLocation  = m_pDataInterface->getString(DataKey, DATA::SampleLocation);
    
    if (ActSampleType == DEF_GC_MEASUREMENT_TYPE::Steel)
    {
      SampleTime  = m_pDataInterface->getDate(DataKey.c_str(),DATA::SteelSampleTime); 
    }
    else if (ActSampleType == DEF_GC_MEASUREMENT_TYPE::Slag)
    {
      SampleTime  = m_pDataInterface->getDate(DataKey.c_str(),DATA::SlagSampleTime); 
    }
    else if (ActSampleType == DEF_GC_MEASUREMENT_TYPE::HM)
    {
      SampleTime  = m_pDataInterface->getDate(DataKey.c_str(),DATA::HMSampleTime); 
    }
    else 
    {
      SampleTime  = Now.assDate();
    }
    

    // read further Sample information as CORBA sequence
    sSampleData AimStruct ; 
    seqSampleData AimSeq = CIntfData::ToCORBAType(m_pProductManagementInterface->getSampleData(ProductID.c_str(),DATA::SampleData));

    // insert "actual" and "next" sample id and time into SampleSequence
    // handle sample data
    sSampleData SampleDataStruct ; 
    seqSampleData SampleDataSeq;

    // fill SampleDataStruct structure
    if  ( SampleId.empty() || SampleId == DEF::Inv_String )
    {
      CDM_SampleManager SampleManager;

      // Actual pahse will be used within SampleId generation
      // we will get this phase from m_pProductManagementInterface
      // respective entries will be read from ini file according to DATA::PhaseAct
      std::string PhaseAct    = m_pProductManagementInterface->getString(Event.getProductID(), DATA::PhaseAct);
      std::string SamplePhase = CDataConversion::SetInvalidToDefault(PhaseAct,"");

      cCBS_StdInitBase::getInstance()->replaceWithEntry("SAMPLEID",PhaseAct,SamplePhase);

      SampleId = SampleManager.generateSampleId(SampleType, PlantID, SamplePhase, SampleNo, SampleLocation);

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
      pEventLog->EL_HandleGeneratedSampleId(sMessage,SampleId.c_str());
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
      pEventLog->EL_HandleSubmittedSampleId(sMessage,SampleId.c_str());
    }

    // SampleCose is still used in model interfaces
    SampleCode = SampleId;

    // we assume everything as usable if nothing else is defined
    if ( SampleUsable == DEF::Inv_Long )
    {
      SampleUsable = DEF_GC_SAMPLEUSABLE::usablewithsampletaken; // 1
    }

    SampleDataStruct.SampleNo       = SampleNo;
    SampleDataStruct.SampleTime     = SampleTime;
    SampleDataStruct.SampleType     = ActSampleType;
    SampleDataStruct.PlantID        = PlantID.c_str();
    SampleDataStruct.SampleMode     = SampleMode;
    SampleDataStruct.SampleLocation = SampleLocation.c_str();
    SampleDataStruct.ProcessStage   = ProcessStage.c_str();
    SampleDataStruct.SampleId       = SampleId.c_str();
    SampleDataStruct.SampleCode     = SampleCode.c_str();
    SampleDataStruct.SampleOrigin   = SampleOrigin;
    SampleDataStruct.SampleUsable   = SampleUsable;

    // fill Sequence
    CIntfData::insert(SampleDataSeq,SampleDataStruct);

    // update or insert further sequence with new data
    UPDATE_SEQ(&SampleDataSeq,SampleDataStruct,&AimSeq,AimStruct,SampleId,std::string);

    // write updated sequence to ProductManagerInterface
    m_pProductManagementInterface->setSampleData(ProductID.c_str(),DATA::SampleData,AimSeq);

    m_pDataInterface->setSampleData(DataKey.c_str(),DATA::SampleData,SampleDataSeq);

    log(CIntfData::getContent(CIntfData::ToAny(SampleDataSeq)),4);
  }

  return SampleId;
}

void CDM_ProductManager::setAnalysisData(CEventMessage& Event, const std::string& AnalysisType)
{
  std::string ProductID  = Event.getProductID();
  std::string DataKey    = Event.getDataKey();
  std::string PlantID    = Event.getPlantID();

  long SampleNo         = DEF::Inv_Long;
  long SampleUsable    = DEF::Inv_Long;
  long SampleMode       = DEF::Inv_Long;
  long SampleType       = DEF::Inv_Long;
  long SampleOrigin     = DEF::Inv_Long;

  std::string SampleId;
  std::string ProcessStage;
  std::string SampleLocation;
  std::string SampleCode;

  sDate SampleTime; 

  sAnalysisData AimStruct ; 
  sAnalysisData SourceStruct ; 
  seqAnalysisData SourceSeq;
  seqAnalysis MeasAnalysis;

  if (m_pDataInterface && m_pProductManagementInterface )
  {
    if (AnalysisType == DATA::SteelMeasAnalysis)
    {
      // extract incoming CORBA data from DataInterface
      MeasAnalysis    = CIntfData::ToCORBAType(m_pDataInterface->getAnalysis(DataKey.c_str(),DATA::SteelMeasAnalysis));
      SampleTime      = m_pDataInterface->getDate(DataKey.c_str(),DATA::SteelSampleTime); 

      SampleType      = m_pDataInterface->getLong(DataKey, DATA::SampleType);
      SampleNo        = m_pDataInterface->getLong(DataKey, DATA::SampleNo);
      SampleUsable   = m_pDataInterface->getLong(DataKey, DATA::SampleUsable);
      SampleMode      = m_pDataInterface->getLong(DataKey, DATA::SampleMode);
      SampleOrigin    = m_pDataInterface->getLong(DataKey, DATA::SampleOrigin);

      SampleId        = m_pDataInterface->getString(DataKey, DATA::SampleId);
      ProcessStage    = m_pDataInterface->getString(DataKey, DATA::ProcessStage);
      SampleLocation  = m_pDataInterface->getString(DataKey, DATA::SampleLocation);

      if ( SampleType == DEF::Inv_Long )
      {
        SampleType = DEF_GC_MEASUREMENT_TYPE::Steel;
      }
    }

    if (AnalysisType == DATA::SlagMeasAnalysis)
    {
      // extract incoming CORBA data from DataInterface
      MeasAnalysis  = CIntfData::ToCORBAType(m_pDataInterface->getAnalysis(DataKey.c_str(),DATA::SlagMeasAnalysis));
      SampleTime    = m_pDataInterface->getDate(DataKey.c_str(),DATA::SlagSampleTime); 

      SampleType      = m_pDataInterface->getLong(DataKey, DATA::SampleType);
      SampleNo        = m_pDataInterface->getLong(DataKey, DATA::SampleNo);
      SampleUsable   = m_pDataInterface->getLong(DataKey, DATA::SampleUsable);
      SampleMode      = m_pDataInterface->getLong(DataKey, DATA::SampleMode);
      SampleOrigin    = m_pDataInterface->getLong(DataKey, DATA::SampleOrigin);

      SampleId        = m_pDataInterface->getString(DataKey, DATA::SampleId);
      ProcessStage    = m_pDataInterface->getString(DataKey, DATA::ProcessStage);
      SampleLocation  = m_pDataInterface->getString(DataKey, DATA::SampleLocation);

      if ( SampleType == DEF::Inv_Long )
      {
        SampleType = DEF_GC_MEASUREMENT_TYPE::Slag;
      }
    }

    if (AnalysisType == DATA::HMMeasAnalysis)
    {
      // extract incoming CORBA data from DataInterface
      // extract incoming CORBA data from DataInterface
      MeasAnalysis  = CIntfData::ToCORBAType(m_pDataInterface->getAnalysis(DataKey.c_str(),DATA::HMMeasAnalysis));
      SampleTime    = m_pDataInterface->getDate(DataKey.c_str(),DATA::HMSampleTime); 

      SampleType      = m_pDataInterface->getLong(DataKey, DATA::SampleType);
      SampleNo        = m_pDataInterface->getLong(DataKey, DATA::SampleNo);
      SampleUsable   = m_pDataInterface->getLong(DataKey, DATA::SampleUsable);
      SampleMode      = m_pDataInterface->getLong(DataKey, DATA::SampleMode);
      SampleOrigin    = m_pDataInterface->getLong(DataKey, DATA::SampleOrigin);

      SampleId        = m_pDataInterface->getString(DataKey, DATA::SampleId);
      ProcessStage    = m_pDataInterface->getString(DataKey, DATA::ProcessStage);
      SampleLocation  = m_pDataInterface->getString(DataKey, DATA::SampleLocation);

      if ( SampleType == DEF::Inv_Long )
      {
        SampleType = DEF_GC_MEASUREMENT_TYPE::HM;
      }
    }

    // fill SampleDataStruct structure
    if ( SampleId.empty() || SampleId == DEF::Inv_String )
    {
      SampleId = CDataConversion::LongToString(SampleType) + "_" + CDataConversion::LongToString(SampleNo);
    }

    // SampleCose is still used in model interfaces
    SampleCode = SampleId;

    // we assume everything as usable if nothing else is defined
    if ( SampleUsable == DEF::Inv_Long )
    {
      SampleUsable = DEF_GC_SAMPLEUSABLE::usablewithsampletaken; // 1
    }

    SourceStruct.SampleData.SampleId        = SampleId.c_str();
    SourceStruct.SampleData.SampleCode      = SampleCode.c_str();    
    SourceStruct.SampleData.SampleNo        = SampleNo;
    SourceStruct.SampleData.SampleTime      = SampleTime;
    SourceStruct.SampleData.SampleType      = SampleType;
    SourceStruct.SampleData.PlantID         = PlantID.c_str();
    SourceStruct.SampleData.SampleMode      = SampleMode;
    SourceStruct.SampleData.SampleLocation  = SampleLocation.c_str();
    SourceStruct.SampleData.SampleOrigin    = SampleOrigin;
    SourceStruct.SampleData.SampleUsable    = SampleUsable;

    // fill analysis into analysis data structure (sAnalysisData)
    SourceStruct.Analysis = MeasAnalysis;

    // fill Sequence
    CIntfData::insert(SourceSeq,SourceStruct);

    // read further information as CORBA sequence
    seqAnalysisData AimSeq = CIntfData::ToCORBAType(m_pProductManagementInterface->getAnalysisData(ProductID.c_str(),AnalysisType.c_str()));

    // update or insert further sequence with new data
    UPDATE_SEQ(&SourceSeq,SourceStruct,&AimSeq,AimStruct,SampleData.SampleId,std::string);

    // write updated sequence to ProductManagerInterface
    m_pProductManagementInterface->setAnalysisData(ProductID.c_str(),AnalysisType.c_str(),AimSeq);

    m_pDataInterface->setAnalysisData(DataKey.c_str(),AnalysisType.c_str(),SourceSeq);

  }
}

bool CDM_ProductManager::changeMaterialData(CEventMessage& Event)
{
  log("!!!!! CDM_ProductManager::changeMaterialData.. not implemented !", 9);
  return false;
}

bool CDM_ProductManager::changeComputerModeAvailabilities(CEventMessage& Event)
{
  log("!!!!! CDM_ProductManager::changeComputerModeAvailabilities.. not implemented !", 9);
  return false;
}

bool CDM_ProductManager::resetComputerModeAvailabilities(CEventMessage& Event)
{
  log("!!!!! CDM_ProductManager::resetComputerModeAvailabilities.. not implemented !", 9);
  return false;
}

bool CDM_ProductManager::resetProductManager(CEventMessage& Event)
{
  log("!!!!! CDM_ProductManager::resetProductManager.. not implemented !", 9);
  return false;
}

void CDM_ProductManager::fillStatusHandler(CDM_StatusHandler& StatusHandler, seqComputerModes* seqModes)
{
  long ActLength = CIntfData::getLength(*seqModes);
  for ( long i = 0 ; i < ActLength; ++i )
  {
    sComputerMode ModeStruct ; 
    // init availabilities to actual state
    CIntfData::getAt(ModeStruct,seqModes,i);
    StatusHandler.setStatus(std::string(ModeStruct.Device),ModeStruct.Status);
  }
}

void CDM_ProductManager::fillStatusHandler(CDM_StatusHandler& StatusHandler, seqComputerModes& seqModes)
{
  fillStatusHandler(StatusHandler, &seqModes);
}

void CDM_ProductManager::fillStatusHandler(CDM_StatusHandler& StatusHandler, std::vector<std::string>& StateList, long Value)
{
  std::vector<std::string>::iterator it;
  for ( it = StateList.begin(); it != StateList.end(); ++it)
  {
    std::string StatusName = (*it);
    StatusHandler.setStatus(StatusName,Value);
  }
}


void CDM_ProductManager::fillComputerModesSequence(CDM_StatusHandler& StatusHandler, seqComputerModes& seqModes)
{
  std::map<std::string,long> StatusList;
  std::map<std::string,long>::iterator it;

  sComputerMode ModeStruct ; 

  StatusList = StatusHandler.getStatusList();

  for ( it  = StatusList.begin(); it != StatusList.end(); ++it)
  {
    ModeStruct.Device = it->first.c_str();
    ModeStruct.Status = it->second;
    CIntfData::insert(seqModes,ModeStruct);
  }
}

bool CDM_ProductManager::findHeat(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string OrderId   = Event.getOrderID();
  
  if ( findHeat(ProductID, HeatID, TreatID, OrderId) )
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

bool CDM_ProductManager::findProduct(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string OrderId   = Event.getOrderID();
  
  if ( findProduct(ProductID, HeatID, TreatID, OrderId) )
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

void CDM_ProductManager::fillGasDataHandler(CDM_GasDataHandler& GasDataHandler, seqGasData* seqData)
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

void CDM_ProductManager::fillGasDataHandler(CDM_GasDataHandler& GasDataHandler, seqGasData& seqData)
{
  fillGasDataHandler(GasDataHandler, &seqData);
}


void CDM_ProductManager::fillGasDataHandler(CDM_GasDataHandler& GasDataHandler, std::vector<std::string>& GasList, double Value)
{
  // remove all gases from gas list in gas handler
  GasDataHandler.clear();

  // add gases with the given value
  std::vector<std::string>::iterator it;
  for ( it = GasList.begin(); it != GasList.end(); ++it)
  {
    std::string GasDataName = (*it);
    GasDataHandler.setGasData(GasDataName,Value);
  }
}

void CDM_ProductManager::fillGasDataSequence(CDM_GasDataHandler& GasDataHandler, seqGasData& seqData)
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

void CDM_ProductManager::addGasDataHandler(CDM_GasDataHandler& GasDataHandler, seqGasData& seqData)
{
  // step through seqData and ...(see below)
  long ActLength = CIntfData::getLength(seqData);
  for ( long i = 0 ; i < ActLength; ++i )
  {
    sGasData GasStruct ; 
    CIntfData::getAt(GasStruct,&seqData,i);
    // ... add gas value to an axist gas or insert new pair of gas type and value if doesn't exist
    GasDataHandler.addGasData(std::string(GasStruct.GasType),GasStruct.GasValue);
  }
}

void CDM_ProductManager::log(const std::string& Message, long Level)
{
  m_pDMTask->log(Message, Level);
}

void CDM_ProductManager::diffGasDataHandler(CDM_GasDataHandler& GasDataHandler, seqGasData& seqData)
{
  // step through seqData and try to find data for respective gas types
  long ActLength = CIntfData::getLength(seqData);
  for ( long i = 0 ; i < ActLength; ++i )
  {
    sGasData GasStruct ; 
    // init availabilities to actual state
    CIntfData::getAt(GasStruct,&seqData,i);
    GasDataHandler.diffGasData(std::string(GasStruct.GasType),GasStruct.GasValue);
  }
}

void CDM_ProductManager::initGasData(const std::string& Key, const std::string& Data, const std::string& GasDataName, double Init)
{
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " ;

  try
  {
    if (m_pProductManagementInterface)
    {
      CDM_GasDataHandler GasDataHandler;
      seqGasData GasData; 

      // fill GasDataHandler with GasTypeList enries and init GasData with Init
      GasDataHandler.setGasData(GasDataName,Init);

      // write 0 data to ProductManagementInterface
      fillGasDataSequence(GasDataHandler,GasData);
      m_pProductManagementInterface->setGasData(Key.c_str(),Data.c_str(),GasData);

    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                          "CDM_ProductManager::initGasData",
                                          ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                          "CDM_ProductManager::initGasData",
                                          ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                          "CDM_ProductManager::initGasData",
                                          ExceptionMsg.str().c_str());
  }
}

void CDM_ProductManager::initGasData(const std::string& Key, const std::string& Data, double Init)
{
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " ;

  try
  {
    if (m_pProductManagementInterface)
    {
      CDM_GasDataHandler GasDataHandler;
      seqGasData GasData; 

      // fill GasDataHandler with GasTypeList enries and init GasData with Init
      fillGasDataHandler(GasDataHandler,m_GasTypeList,Init);

      // write 0 data to ProductManagementInterface
      fillGasDataSequence(GasDataHandler,GasData);
      m_pProductManagementInterface->setGasData(Key.c_str(),Data.c_str(),GasData);

    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                          "CDM_ProductManager::initGasData",
                                          ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                          "CDM_ProductManager::initGasData",
                                          ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                          "CDM_ProductManager::initGasData",
                                          ExceptionMsg.str().c_str());
  }
}

bool CDM_ProductManager::changeMaterialFeedingData(CEventMessage& Event)
{
	return false;
}

bool CDM_ProductManager::changeGasData(CEventMessage& Event)
{
	return false;
}

bool CDM_ProductManager::changeElectricalData(CEventMessage& Event)
{
	return false;
}

bool CDM_ProductManager::changeSetpoints(CEventMessage& Event)
{
	return false;
}

bool CDM_ProductManager::changeEventDataInformation(CEventMessage& Event)
{
  bool RetValue = false;
  
  std::string ProductID = Event.getProductID();
  std::string DataKey   = Event.getDataKey();

  if ( m_pDataInterface && m_pProductManagementInterface )
  {
    // change date/time information of product for following data
    std::map<std::string,std::string> DataKeys;
    std::map<std::string,std::string>::iterator it;

    // first == name of data to be read
    // second == name of data to be written
    DataKeys.insert( std::pair<std::string,std::string>(DATA::HeatAnnounceTime,DATA::DurSinceHeatAnnounce));
    DataKeys.insert( std::pair<std::string,std::string>(DATA::HeatStartTime,DATA::DurSinceHeatStart));

    try
    {
      for( it = DataKeys.begin(); it != DataKeys.end() ; ++ it)
      {
        std::string getName = it->first;
        std::string setName = it->second;

        // check if data exists for this key !
        if ( m_pProductManagementInterface->isKey(ProductID) )
        {
          sDate DateStruct = m_pProductManagementInterface->getDate(ProductID.c_str(), getName.c_str());
          CDateTime invDate ((time_t)0);

          // valid date found ?
          if ( DateStruct.year > invDate.getYear() ) 
          {
            double Duration = 0.0;
            CDateTime   HeatTime;
            CDateTime   ActTime;

            // calculate difference between "now" and heat related time
            HeatTime.SetTime(DateStruct);
            Duration = CDateTime::subTimes(ActTime,HeatTime).asSeconds() / 60.0;

            // write results to CORBA interface for product
            m_pProductManagementInterface->setDouble(ProductID.c_str(), setName.c_str(), Duration );

            // write results to CORBA interface for event
            m_pDataInterface->setDouble(DataKey, setName.c_str(), Duration );

            std::ostringstream Message;
            Message << "Recalculated " << setName << " at CDM_ProductManager::changeEventDataInformation() : " << Duration;

            log(Message.str(),2);
          }
        }
      }
    }
    catch(...)
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,"",
                                          "CDM_ProductManager::changeEventDataInformation()",
                                          "");
    }

    RetValue = true;
  }

  return RetValue;

}

bool CDM_ProductManager::changeInjectionData(CEventMessage& Event)
{
  log("!!!!! CDM_ProductManager::changeInjectionData.. not implemented !", 9);
  return false;
}

bool CDM_ProductManager::findOrder(std::string& ProductID,std::string& HeatID,std::string& TreatID,std::string& OrderId)
{

  std::stringstream Message;
  Message << "CDM_ProductManager::findOrder searching for " 
          << "  ProductID "<< ProductID 
          << "  HeatID "<< HeatID
          << "  TreatID "<< TreatID
          << "  OrderId "<< OrderId;

  log(Message.str(),2);

  bool RetValue = false;

  if (m_pProductManagementInterface)
  {
    // do nothing for empty or invalid OrderId

    if ( OrderId.empty() || OrderId == DEF::Inv_String )
    {
      log("Invalid or empty OrderId received !",2);
    }
    else
    {
      long Size = m_pProductManagementInterface->getSize();
      
      for ( long i = 0; i < Size; ++i )
      {
        std::string ActKey = m_pProductManagementInterface->getKey(i);

        if ( !ActKey.empty() && ActKey != DEF::Inv_String )
        {
          std::string ActOrderID = m_pProductManagementInterface->getString(ActKey,DATA::OrderId);

          if ( ActOrderID == OrderId )
          {
            HeatID  = m_pProductManagementInterface->getString(ActKey,DATA::HeatID);
            TreatID = m_pProductManagementInterface->getString(ActKey,DATA::TreatID);
            ProductID = m_pProductManagementInterface->getString(ActKey,DATA::ProductID);

            std::stringstream Message;
            Message << "Product " << ProductID << " found at m_pProductManagementInterface for OrderId " << OrderId;
            log(Message.str(),2);

            RetValue = true;
            break;
          }
        }
      }
    }
  }
  return RetValue ;
}

bool CDM_ProductManager::changeCoolingWaterData(CEventMessage& Event)
{
  log("!!!!! CDM_ProductManager::changeCoolingWaterData.. not implemented !",3);
  return false;
}

bool CDM_ProductManager::changeHeatingData(CEventMessage& Event)
{
  log("!!!!! CDM_ProductManager::changeHeatingData.. not implemented !",3);
  return false;
}

bool CDM_ProductManager::changeVacuumData(CEventMessage& Event)
{
  log("!!!!! CDM_ProductManager::changeVacuumData... not implemented !",3);
  return false;
}

bool CDM_ProductManager::changeWasteGasData(CEventMessage& Event)
{
  log("!!!!! CDM_ProductManager::changeWasteGasData... not implemented !",3);
  return false;
}

bool CDM_ProductManager::changeLiftGasData(CEventMessage& Event)
{
  log("!!!!! CDM_ProductManager::changeLiftGasData... not implemented !",3);
  return false;
}

bool CDM_ProductManager::changeChargingData(CEventMessage& Event)
{
  log("!!!!! CDM_ProductManager::changeChargingData... not implemented !",3);
  return false;
}


bool CDM_ProductManager::changeGasLanceData(CEventMessage& Event)
{
  log("!!!!! CDM_ProductManager::changeGasLanceData... not implemented !",3);
  return false;
}

double CDM_ProductManager::getDurationSince(const std::string& ProductID, const char* TimePoint)
{
  double Dur = DEF::Inv_Double;

  if (m_pProductManagementInterface)
  {
    std::stringstream LogMessage;
    LogMessage << "INFO: Calculated duration since:";
    LogMessage << TimePoint << " for product:" << ProductID;

    CDateTime now;
    CDateTime TPoint;
    CDeltaTime dtTime;

    TPoint.SetTime(m_pProductManagementInterface->getDate(ProductID.c_str(), TimePoint));
    dtTime = CDateTime::subTimes(now, TPoint);
    Dur = dtTime.asSeconds()/60;

    LogMessage << " Duration (min):" << Dur;
    log(LogMessage.str(),3);
  }
  return Dur;
}

bool CDM_ProductManager::addDifferenceToGasData(CEventMessage& Event, const std::string& GasData1, const std::string& GasData2, const std::string& DestGasData, double DiffValue)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string Message   = Event.getMessage();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << ProductID << ", " << Event.getHeatID()
               << ", " << Event.getTreatID();

  try
  {
    if (m_pProductManagementInterface)
    {
      CGasDataHandler GasDataHandler2; // for difference calculation
      CGasDataHandler destGasDataHandler;// to add difference to existing dada

      seqGasData seqCalcGasData;//sequence for setting calculated data
      sGasData sGD;

      seqGasData SeqGasData1    = CIntfData::ToCORBAType(m_pProductManagementInterface->getGasData(ProductID.c_str(),GasData1.c_str()));
      seqGasData SeqGasData2    = CIntfData::ToCORBAType(m_pProductManagementInterface->getGasData(ProductID.c_str(),GasData2.c_str()));
      seqGasData SeqDestGasData = CIntfData::ToCORBAType(m_pProductManagementInterface->getGasData(ProductID.c_str(),DestGasData.c_str()));

      if (DiffValue != DEF::Inv_Double)
      {
        // fill GasDataHandler with gas types from pGasData2
        // and init with _value
        long len = CIntfData::getLength(SeqGasData2);
        for ( long x=0; x<len; x++)
        {
          CIntfData::getAt(sGD, SeqGasData2, x);

          GasDataHandler2.setGasData(std::string(sGD.GasType), DiffValue);
        }
      }
      else
        GasDataHandler2.setGasData(SeqGasData2);

      // calculate (delta value) differences between GasData1 and GasData2
      GasDataHandler2.diffGasData(SeqGasData1);

      // write current data from destination to GasDataHandler to add the difference
      destGasDataHandler.setGasData(SeqDestGasData);

      //add delta value to destData
      destGasDataHandler.addGasData(GasDataHandler2);

      // write difference from handler to sequence
      destGasDataHandler.fillSequence(seqCalcGasData);

      // overwrite in interface
      m_pProductManagementInterface->setGasData(ProductID.c_str(), DestGasData.c_str(), seqCalcGasData);

      RetValue = true;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_ProductManager::addDifferenceToGasData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_ProductManager::addDifferenceToGasData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_ProductManager::addDifferenceToGasData()",
                                         ExceptionMsg.str().c_str());
  }

  return RetValue;
}

void CDM_ProductManager::initStirringData(const std::string& Key, std::vector<std::string>& m_StirringDef, std::vector<std::string>& m_StirringDevices, double Init)
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
    m_pProductManagementInterface->setStirringData(Key.c_str(), m_StirringDef[i].c_str(), SeqStirrData);
  }
  
  return;
}

bool CDM_ProductManager::setTreatmentPosition(const std::string& ProductID, long TreatmentPosition)
{
  bool RetValue = false;


  std::stringstream ExceptionMsg;

  try
  {
    if (m_pProductManagementInterface)
    {
      if ( findProduct(std::string(ProductID)) )
      {
        m_pProductManagementInterface->setLong(ProductID, DATA::TreatmentPosition, TreatmentPosition);
        RetValue = true;
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_ProductManager::setTreatmentPosition()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_ProductManager::setTreatmentPosition()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_ProductManager::setTreatmentPosition()",
                                         ExceptionMsg.str().c_str());
  }

  return RetValue;

}


bool CDM_ProductManager::setProductData(const std::string& ProductID, long TreatmentPosition)
{
 return false;
}


bool CDM_ProductManager::setProductData(const std::string& ProductID, const std::string& LadleType, long LadleNo, CDateTime& HeatAnnounceTime, CDateTime& HeatDepartTime, CDateTime& HeatStartTime )
{
  bool RetValue = false;


  std::stringstream ExceptionMsg;

  try
  {
    if (m_pProductManagementInterface)
    {
      if ( findProduct(std::string(ProductID)) )
      {
        m_pProductManagementInterface->setString(ProductID.c_str(), DATA::LadleType,         LadleType);
        m_pProductManagementInterface->setLong  (ProductID.c_str(), DATA::LadleNo,           LadleNo);
        m_pProductManagementInterface->setDate  (ProductID.c_str(), DATA::HeatAnnounceTime,  HeatAnnounceTime.assDate());
        m_pProductManagementInterface->setDate  (ProductID.c_str(), DATA::HeatDepartureTime, HeatDepartTime.assDate());
        m_pProductManagementInterface->setDate  (ProductID.c_str(), DATA::HeatStartTime,     HeatStartTime.assDate());

        RetValue = true;
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_ProductManager::setProductData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_ProductManager::setProductData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_ProductManager::setProductData()",
                                         ExceptionMsg.str().c_str());
  }

  return RetValue;
}

bool CDM_ProductManager::changePhaseState(CEventMessage& Event)
{
  bool RetValue = false;


  std::stringstream ExceptionMsg;

  try
  {
    if (m_pProductManagementInterface)
    {
      // remember last phase information
      std::string PhaseAct  = m_pProductManagementInterface->getString(Event.getProductID(), DATA::PhaseAct   );
      long PhaseNoAct       = m_pProductManagementInterface->getLong  (Event.getProductID(), DATA::PhaseNoAct );

      // set PhaseAct/PhasNoAct for HMI presentation with priority
      // 1 = PhaseModel
      // 2 = PhaseProcess (set by Level 1)
      // 3 = PhaseTracker

      std::string NewPhase    = DEF::Inv_String;
      long        NewPhaseNo  = DEF::Inv_Long;

      std::string PhaseModel      = m_pProductManagementInterface->getString(Event.getProductID(),DATA::PhaseModel);
      long        PhaseNoModel    = m_pProductManagementInterface->getLong  (Event.getProductID(),DATA::PhaseNoModel);
      std::string PhaseProcess    = m_pProductManagementInterface->getString(Event.getProductID(),DATA::PhaseProcess);
      long        PhaseNoProcess  = m_pProductManagementInterface->getLong  (Event.getProductID(),DATA::PhaseNoProcess);
      std::string PhaseTracker    = m_pProductManagementInterface->getString(Event.getProductID(),DATA::PhaseTracker);
      long        PhaseNoTracker  = m_pProductManagementInterface->getLong  (Event.getProductID(),DATA::PhaseNoTracker);

      if ( PhaseModel != DEF::Inv_String && !PhaseModel.empty() )
      {
        NewPhase    = PhaseModel;
        NewPhaseNo  = PhaseNoModel;
      }     
      else if ( PhaseProcess != DEF::Inv_String && !PhaseProcess.empty() )
      {
        NewPhase    = PhaseProcess;
        NewPhaseNo  = PhaseNoProcess;
      }
      else if ( PhaseTracker != DEF::Inv_String && !PhaseTracker.empty() )
      {
        NewPhase    = PhaseTracker;
        NewPhaseNo  = PhaseNoTracker;
      }

      // new valid phase data detected
      if ( NewPhase != DEF::Inv_String )
      {
        m_pProductManagementInterface->setString(Event.getProductID(), DATA::PhaseAct   , NewPhase);
        m_pProductManagementInterface->setLong  (Event.getProductID(), DATA::PhaseNoAct , NewPhaseNo);

        // phase change detected
        if ( PhaseAct   != NewPhase ||
             PhaseNoAct != NewPhaseNo )
        {
          doOnPhaseStateChange(Event);
        }
      }

      RetValue = true;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_ProductManager::changePhaseState()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_ProductManager::changePhaseState()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_ProductManager::changePhaseState()",
                                         ExceptionMsg.str().c_str());
  }

  return RetValue;
}

bool CDM_ProductManager::doOnPhaseStateChange(CEventMessage& Event)
{
  return false;
}

void CDM_ProductManager::getAdditionallyMessages(std::vector<std::string>& Messages)
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

void CDM_ProductManager::addEventMessageToSend(std::string Message)
{
  m_AdditionallyMessages.push_back(Message);
}
