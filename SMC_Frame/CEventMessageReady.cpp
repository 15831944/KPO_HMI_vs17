// Copyright (C) 2004 SMS Demag AG

#include "CEventMessageReady.h"

//##ModelId=41239DC602F8
CEventMessageReady::CEventMessageReady(const CEventMessage& orig)
{
  // changing Sender / Receiver
  this->m_Sender        = orig.getReceiver();
  this->m_Receiver      = orig.getSender();
  this->m_PlantID       = orig.getPlantID();
  this->m_PlantLocation = orig.getPlantLocation();

  // adding special Message extension
  this->m_Message       = orig.getMessage() + ".RDY";

  this->m_ProductID           = orig.getProductID();
  this->m_RelatedInformation  = orig.getRelatedInformation();

  this->m_isPlantEvent  = orig.isPlantEvent();
  this->m_HeatID        = orig.getHeatID();
  this->m_TreatID       = orig.getTreatID();
  this->m_OrderID       = orig.getOrderID();
  this->m_DataKey       = orig.getDataKey();
}
