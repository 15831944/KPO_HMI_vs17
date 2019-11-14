// Copyright (C) 2004 SMS Demag AG

#include "CEventMessageError.h"

//##ModelId=41239F33022E
CEventMessageError::CEventMessageError(const CEventMessage& orig)
{
  // changing Sender / Receiver
  this->m_Sender        = orig.getReceiver();
  this->m_Receiver      = orig.getSender();
  this->m_PlantID       = orig.getPlantID();
  this->m_PlantLocation = orig.getPlantLocation();

  // adding special Message extension
  this->m_Message       = orig.getMessage() + ".ERR";

  this->m_ProductID           = orig.getProductID();
  this->m_RelatedInformation  = orig.getRelatedInformation();

  this->m_isPlantEvent  = orig.isPlantEvent();
  this->m_HeatID        = orig.getHeatID();
  this->m_TreatID       = orig.getTreatID();
  this->m_OrderID       = orig.getOrderID();
  this->m_DataKey       = orig.getDataKey();
}

