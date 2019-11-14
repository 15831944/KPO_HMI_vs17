// Copyright (C) 2012 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iEventData_s.hh"

#include "CDataConversion.h"
#include "CProductID.h"

#include "CDM_PlantManagementInterface_Impl.h"

::CORBA::Boolean CDM_PlantManagementInterface_Impl::setProductFromTreatmentPos(const char* TreatmentPosition, ::sEventData_out EventData)
{
  if (! m_Critical_Section.lock("setProductFromTreatmentPos"))
  {
    return false;
  }

  bool RetValue = false;

  try
  {
    EventData = new sEventData();

    CProductID PID;

    std::string ActProduct = getString(TreatmentPosition, DATA::ProductID);

    if ( !ActProduct.empty()
      && DEF::Inv_String != ActProduct 
       )
    {
      EventData->m_HeatID = CORBA::string_dup(PID.getHeatID(ActProduct).c_str());
      EventData->m_TreatID = CORBA::string_dup(PID.getTreatID(ActProduct).c_str());
      EventData->m_ProductID = CORBA::string_dup(ActProduct.c_str());
      
      //set the other data to some default data
      EventData->m_DataKey = CORBA::string_dup(DEF::Inv_String);      
      EventData->m_isPlantEvent = false;
      EventData->m_Message = CORBA::string_dup(DEF::Inv_String);
      EventData->m_OrderID = CORBA::string_dup(DEF::Inv_String);
      EventData->m_PlantID = CORBA::string_dup(DEF::Inv_String);
      EventData->m_Receiver = CORBA::string_dup(DEF::Inv_String);
      EventData->m_RelatedInformation = CORBA::string_dup(DEF::Inv_String);
      EventData->m_Sender = CORBA::string_dup(DEF::Inv_String);

      RetValue = true;
    }
  }
  catch(...)
  {
    std::string Message = "while getting the product data for the treatment position : ";
    Message += TreatmentPosition;

    EventLogExc(Message, "CDM_PlantManagementInterface_Impl::setProductFromTreatmentPos", "");
  }

  m_Critical_Section.unlock("setProductFromTreatmentPos");

  return RetValue;
}