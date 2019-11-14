// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEVENTMESSAGE_40C03C6800E4_INCLUDED
#define _INC_CEVENTMESSAGE_40C03C6800E4_INCLUDED

#include <string>
#include <vector>

#include "CBS_StdAPI.h"

//##ModelId=4108FFFF010E
class CEventMessage 
{
public:

	//##ModelId=471C725C027A
  static std::string getSenderName(const std::string& SenderName);

	//##ModelId=471C725C0306
  static std::vector<std::string> getDestinationList(const std::string& SenderName);

	//Provides an produtID like productID::extension for 
	//unique ID within the e.g. phase tracking
	//##ModelId=434D20C70243
	static std::string getExtendedProductID(const std::string& productID, const std::string  & extension);

	//Provides the original productID from which the extended 
	//one was created.
	//##ModelId=434D21750339
	static std::string getOriginalProductID(const std::string& extendedProductID   );

	//##ModelId=430C484A02C7
	CEventMessage(const std::string& sender, 
                const std::string& receiver, 
                const std::string& message, 
                const std::string& plantID, 
                const std::string& productID, 
                const std::string& relatedInformation, 
                bool isPlantEvent, 
                const std::string& HeatID, 
                const std::string& TreatID, 
                const std::string& DataKey);


	CEventMessage(const std::string& sender, 
                const std::string& receiver, 
                const std::string& message, 
                const std::string& plantID, 
                const std::string& plantLocation, 
                const std::string& productID, 
                const std::string& relatedInformation, 
                bool isPlantEvent, 
                const std::string& HeatID, 
                const std::string& TreatID, 
                const std::string& DataKey);

	//##ModelId=4109002502EF
	CEventMessage(const std::string& sender,
                const std::string& receiver, 
                const std::string& message, 
                const std::string& productID, 
                const std::string& relatedInformation, 
                bool isPlantEvent);

  //##ModelId=413320B6026F
  CEventMessage(const std::string& sender, 
                const std::string& receiver, 
                const std::string& message, 
                const std::string& productID, 
                const std::string& relatedInformation,  
                bool isPlantEvent, 
                const std::string&HeatID,
                const std::string&TreatID,
                const std::string&DataKey);

	//This default constructor is used for the static member 
	//of CEventMessageCtrl. Don't initialize m_pEventTask. 
	//This will be done in the send method.
  //##ModelId=41239E5201B6
	CEventMessage();

	CEventMessage( CORBA::Any seqAny );

  CORBA::Any asCORBAAny();

  static bool isAsCORBAAny( CORBA::Any seqAny );

  //##ModelId=4309CD4D02CE
  void setPlantID(const std::string& value);

  //##ModelId=4309CD1A0008
  const std::string& getPlantID() const;

  void setPlantLocation(const std::string& value);

  const std::string& getPlantLocation() const;

	//##ModelId=413DFD6802BD
	void setPlantEvent(bool value);

	//##ModelId=413DFD7500A0
	void setMessage(const std::string& value);

	//##ModelId=413DFD9202CE
	void setReceiver(const std::string& value);

	//##ModelId=413DFDA20029
	void setSender(const std::string& value);

	//##ModelId=413D85BC0394
	const std::string& getRelatedInformation() const;

	//##ModelId=413D85BE0076
	void setRelatedInformation(const std::string& value);

  //##ModelId=41239A280011
	void setDataKey(const std::string& value);

	//##ModelId=41239A2A01B8
	void setHeatID(const std::string& value);

	//##ModelId=41239A2D0267
	void setOrderID(const std::string& value);

	//##ModelId=41239A310169
	void setTreatID(const std::string& value);

	//##ModelId=4123982502D5
	 const std::string& getDataKey() const ;

	//##ModelId=4123982701AE
	 const std::string& getHeatID() const ;

	//##ModelId=412398290052
	 bool isPlantEvent() const ;

	//##ModelId=4123982A02F1
	 const std::string& getMessage() const ;

	//##ModelId=4123982C0146
	 const std::string& getOrderID() const ;

	//##ModelId=4123982F019D
	 const std::string& getReceiver() const ;

	//##ModelId=412398300393
	 const std::string& getProductID() const ;

	//##ModelId=412398310113
	void setProductID(const std::string& value);

	//##ModelId=41239832034E
	 const std::string& getSender() const ;

	//##ModelId=4123983603A4
	 const std::string& getTreatID() const ;

  long getEventId() const  ;
  long getEventType() const ;
  void setEventId(long value);
  void setEventType(long value);


	//##ModelId=4109FFFF0099
	CEventMessage(const FRIESEvent& Event);

	//##ModelId=44FE9C2F0196
  bool dispatch(const std::string& SenderName, std::vector<std::string>& DestinationList, bool sendExternal = true);

	//sending event from "SenderName" to "DestinationName". 
	//If inifile contains an entry for "DestinationName" at 
	//[EventMessage] block, event will be send to this 
	//destination. A comma seperated list is possible like 
	//DestinationName = A,B,C
	//##ModelId=42660C6400F4
	bool dispatch(const std::string& SenderName, const std::string& DestinationName, bool sendExternal = true);

	//##ModelId=410900250305
  std::string  getContent();

  //##ModelId=4109002502EE
  virtual ~CEventMessage();

private:

	//##ModelId=471C725D03D0
	bool doDispatch(const std::string& SenderName, const std::string& DestinationName, bool sendExternal);

	//calling EventTask and sending event from m_Sender to 
	//m_Receiver
	//##ModelId=410A012D0288
	bool send();

	//##ModelId=471C725D025D
	bool send(bool sendExternal);



protected:
  //##ModelId=4309CAD201BD
  std::string m_PlantID;
  std::string m_PlantLocation;

  //##ModelId=412397890305
  std::string  m_Sender;
  //##ModelId=4123978902FB
  std::string  m_Receiver;
  //##ModelId=4123978902F1
  std::string  m_Message;
  //##ModelId=41239789030F
  std::string  m_ProductID;
	//##ModelId=413D81F80278
	std::string m_RelatedInformation;
  //Is the event plant or product related
  //##ModelId=412397890319
  bool m_isPlantEvent;
	//##ModelId=412397890323
	std::string m_HeatID;
	//##ModelId=41239789032D
	std::string m_TreatID;
	//##ModelId=412397890341
	std::string m_OrderID;
	//##ModelId=41239789034B
	std::string m_DataKey;

  // to store Fries data
  long m_EventId;
  long m_EventType;
};

#endif /* _INC_CEVENTMESSAGE_40C03C6800E4_INCLUDED */
