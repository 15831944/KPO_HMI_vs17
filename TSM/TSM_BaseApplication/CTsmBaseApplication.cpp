// Copyright (C) 2004 SMS Demag AG


#include "CStartUpCtrl.h"
#include "CAddProductCtrl.h"
#include "CResetCtrl.h"
#include "CRemoveProductCtrl.h"
#include "CStateMachine.h"
#include "cCBS_StdInitBase.h"
#include "CProduct.h"
#include "CPlant.h"
#include "CEventMessage.h"
#include "CTsmFileLoggingDatabase.h"

#include "cCBS_StdFrame.h"  

#include "CMsg.h"
#include "CTsmBaseApplication.h"

const std::string CTsmBaseApplication::evSetProductState("SET_PRODUCT_STATE");

const std::string CTsmBaseApplication::evAddProduct("ADD_PRODUCT");

const std::string CTsmBaseApplication::evRemoveProduct("REMOVE_PRODUCT");

const std::string CTsmBaseApplication::evReset("RESET");

const std::string CTsmBaseApplication::evReloadTSM("RELOAD_TSM");

CTsmBaseApplication::CTsmBaseApplication(IDatabase * pDataBase,
                     CStateMachineConstructCtrl* pStateMachineConstructCtrl,
                     CPlantConstructCtrl * pPlantConstructCtrl,
                     CTSM_ObjectCreator *pObjectCreator,
                     const std::string &receiverName)
: m_pDataBase(pDataBase)
, m_pStateMachineConstructCtrl(pStateMachineConstructCtrl)
, m_pPlantConstructCtrl(pPlantConstructCtrl)
, m_pObjectCreator(pObjectCreator)
, m_receiverName(receiverName)
, m_pStateMachine(0)
, m_pPlant(0)
{
  try
  {
    CMSG_SUCCESS_MSG("Start up TSM application (receiver name = "<< m_receiverName << ")");

    // Start up state machine and mill model
    CStartUpCtrl startUpCtrl(m_pStateMachineConstructCtrl,
                             m_pDataBase,
                             m_pPlantConstructCtrl,
                             m_pObjectCreator,
                             m_receiverName);
    startUpCtrl.startUp(m_pStateMachine, m_pPlant);
  }
  catch(...)
  {
    CMSG_ERROR_MSG("Fatal error occured during CTsmBaseApplication::CTsmBaseApplication");
  }
}

CTsmBaseApplication::~CTsmBaseApplication()
{
	delete m_pDataBase;
	delete m_pStateMachineConstructCtrl;
	delete m_pPlantConstructCtrl;
	delete m_pObjectCreator;
	delete m_pStateMachine;
	delete m_pPlant;
}

std::string CTsmBaseApplication::getReceiverName()
{
  return m_receiverName;
}

bool CTsmBaseApplication::doSetProductState(CEventMessage& evMessage)
{
  if (!m_pPlant)
  {
    CMSG_ERROR_MSG("Plant object missing in CTsmBaseApplication::doSetProductState");
    return false;
  }

  // Separate product ID and state from key information
  int pos = evMessage.getProductID().find(":");
  if (std::string::npos == pos)
  {
    CMSG_ERROR_MSG("Cannot find separator ':' in " << evMessage.getProductID() << " for CTsmBaseApplication::doSetProductState");
    return false;
  }

  std::string productId = evMessage.getProductID().substr(0,pos);
  std::string newState = evMessage.getProductID().substr(pos+1);

  // Try to get Product object for the event.
  CProduct* pProduct = m_pPlant->getProduct(productId);
  if (!pProduct)
  {
    CMSG_ERROR_MSG("No product object found for "<< productId << " in CTsmBaseApplication::doSetProductState");
    return false;
  }

  pProduct->setProcessStatus(newState);
  CMSG_SUCCESS_MSG("Successfully set product state to "<< newState <<" for product "<< productId);

  return true;}

bool CTsmBaseApplication::doAddProduct(CEventMessage& evMessage)
{
  try
  {
    CAddProductCtrl addProductCtrl(m_pStateMachine, m_pPlant, m_pObjectCreator);
    addProductCtrl.addProduct(evMessage.getProductID());
    return true;
  }
  catch(...)
  {
    CMSG_ERROR_MSG("Could not create product for ID = " << evMessage.getProductID());
    return false;
  }}

bool CTsmBaseApplication::doRemoveProduct(CEventMessage& evMessage)
{
  try
  {
    CRemoveProductCtrl removeProductCtrl(m_pPlant, m_pStateMachine);
    removeProductCtrl.removeProduct(evMessage.getProductID());

    return true;
  }
  catch(...)
  {
    CMSG_ERROR_MSG("Could not remove product for ID = " << evMessage.getProductID());
    return false;
  }
}

bool CTsmBaseApplication::doReset(CEventMessage& evMessage)
{
  try
  {
    CResetCtrl resetCtrl(m_pStateMachine, m_pPlant);
    resetCtrl.reset();
    return true;
  }
  catch(...)
  {
    CMSG_ERROR_MSG("Reset failed");
    return false;
  }
}

bool CTsmBaseApplication::doReloadTSM(CEventMessage& evMessage)
{
	bool result = false;

	try
	{
		if (!m_pStateMachineConstructCtrl)
		{
			CMSG_ERROR_MSG("Missing state machine constructor in CTsmBaseApplication::doReloadTSM");
			return false;
		}

		// Delete old state machine
		CMSG_WARNING_MSG("Removing old state machine @"<<m_pStateMachine);
		delete m_pStateMachine;
		m_pStateMachine = 0;

		// Create a new state machine
		m_pStateMachine = new CStateMachine;

    // Construct state machine
		m_pStateMachineConstructCtrl->constructStateMachine(m_pStateMachine);

		// Connect the new mill object and the database to the state machine
		m_pStateMachine->connectDatabase(m_pDataBase);
    m_pStateMachine->connectPlant(m_pPlant);

		// Everything is ok
		CMSG_SUCCESS_MSG("New state machine constructed @" << m_pStateMachine);
		result = true;
	}
	catch (...)
	{
		CMSG_ERROR_MSG(
			"Unknown error while CTsmApplication::reloadTSM");
	}
	return result;
}

bool CTsmBaseApplication::handleEvent(CEventMessage& evMessage)
{
  try
  {    
    if (evMessage.isPlantEvent())
    {
      // Handle plant event messages
      HANDLE_EVENT(ReloadTSM);
      HANDLE_EVENT(Reset);
      HANDLE_EVENT(SetProductState);

      // From here, try to handle event with state machine
      return doHandlePlantEvent(evMessage);
    }
    else
    {
      // Handle product event messages
      
      //HANDLE_EVENT(AddProduct);
      //HANDLE_EVENT(RemoveProduct);

      // From here, try to handle event with state machine
      return doHandleProductEvent(evMessage);
    }
    return true;
  }
  catch(...)
  {
    return false;
  }
}

bool CTsmBaseApplication::doHandleProductEvent(CEventMessage& evMessage)
{
  CEventID evID;
  evID = evMessage.getSender()+"$"+evMessage.getMessage();
  CProduct *pr;
  std::string prID;
  prID = evMessage.getProductID();
  pr = m_pPlant->getProduct(prID);
  m_pStateMachine->handleProductEvent(evID,pr);
  return true;
}

bool CTsmBaseApplication::doHandlePlantEvent(CEventMessage& evMessage)
{
  m_pStateMachine->handlePlantEvent(evMessage.getSender()+"$"+evMessage.getMessage());
  return true;
}


bool CTsmBaseApplication::isProductEventRegistered(CEventMessage& evMessage)
{
  return m_pStateMachine->isProductEventRegistered(evMessage.getSender()+"$"+evMessage.getMessage());
}


bool CTsmBaseApplication::isPlantEventRegistered(CEventMessage& evMessage)
{
  return m_pStateMachine->isPlantEventRegistered(evMessage.getSender()+"$"+evMessage.getMessage());
}


bool CTsmBaseApplication::isProductRegistered(CEventMessage& evMessage)
{
  bool RetValue = true;

  if (m_pPlant)
  {
    std::string ProductId = evMessage.getProductID();

    // Try to get Product object for the event.
    CProduct* pProduct = m_pPlant->getProduct(ProductId);
    if (!pProduct)
    {
      CMSG_ERROR_MSG("WARNING: Product not found "<< ProductId << " in CTsmBaseApplication::isProductRegistered");
      RetValue = false;
    }
  }
  else
  {
    CMSG_ERROR_MSG("ERROR: Plant object missing in CTsmBaseApplication::isProductRegistered");
    RetValue = false;
  }

  return RetValue;
}

std::string CTsmBaseApplication::getProductStatus(CEventMessage& evMessage)
{
  std::string RetValue;

  if (m_pPlant)
  {
    std::string ProductId = evMessage.getProductID();

    // Try to get Product object for the event.
    CProduct* pProduct = m_pPlant->getProduct(ProductId);
    if (pProduct)
    {
      RetValue = pProduct->getProcessStatus();
    }
  }

  return RetValue;
}

