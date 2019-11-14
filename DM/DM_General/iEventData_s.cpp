// This file is generated by omniidl (C++ backend)- omniORB_4_2. Do not edit.

#include "iEventData_s.hh"
#include <omniORB4/IOP_S.h>
#include <omniORB4/IOP_C.h>
#include <omniORB4/callDescriptor.h>
#include <omniORB4/callHandle.h>
#include <omniORB4/objTracker.h>


OMNI_USING_NAMESPACE(omni)

static const char* _0RL_library_version = omniORB_4_2;



void
sEventData::operator>>= (cdrStream &_n) const
{
  _n.marshalString(m_Sender,0);
  _n.marshalString(m_Receiver,0);
  _n.marshalString(m_Message,0);
  _n.marshalString(m_PlantID,0);
  _n.marshalString(m_PlantLocation,0);
  _n.marshalString(m_ProductID,0);
  _n.marshalString(m_RelatedInformation,0);
  _n.marshalBoolean(m_isPlantEvent);
  _n.marshalString(m_HeatID,0);
  _n.marshalString(m_TreatID,0);
  _n.marshalString(m_OrderID,0);
  _n.marshalString(m_DataKey,0);

}

void
sEventData::operator<<= (cdrStream &_n)
{
  m_Sender = _n.unmarshalString(0);
  m_Receiver = _n.unmarshalString(0);
  m_Message = _n.unmarshalString(0);
  m_PlantID = _n.unmarshalString(0);
  m_PlantLocation = _n.unmarshalString(0);
  m_ProductID = _n.unmarshalString(0);
  m_RelatedInformation = _n.unmarshalString(0);
  m_isPlantEvent = _n.unmarshalBoolean();
  m_HeatID = _n.unmarshalString(0);
  m_TreatID = _n.unmarshalString(0);
  m_OrderID = _n.unmarshalString(0);
  m_DataKey = _n.unmarshalString(0);

}

