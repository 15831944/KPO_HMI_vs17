#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTelcom_OutOracleTransport_45AB541F00B0_INCLUDED
#define _INC_CTelcom_OutOracleTransport_45AB541F00B0_INCLUDED

#include <vector>
#include "CDateTime.h"
#include "CTelcom_OracleTransport.h"

#include "CEventMessage.h"

//////////////////////////////////////////////////
//
// This class provides a transport interface which 
// calls stored functions from the database.
//
//////////////////////////////////////////////////
//##ModelId=45AB541F00B0
class CTelcom_OutOracleTransport : public CTelcom_OracleTransport
{ 
public:
	CTelcom_OutOracleTransport();

	virtual ~CTelcom_OutOracleTransport();

protected:
  /*
  The overloaded virtual method "receive" - reads 
  first few bytes of each message to determine the remaining 
  number of bytes to read so that Telcom can handle 
  the remainder of the message.
  */

  virtual void configure(const std::string & section, bas::Configuration & c);

  virtual int doConnect();

	virtual void send(const TCMessage & msg);  

	virtual int doDisconnect();

  // to fill the fields on specific policy with information
  // fieldMessage can leave blank
  // x = alphanumeric characters (right padded blanks) 
  // 9 = numeric characters (left padded 0) 
  std::string convertMessage(std::string messageFormat, int maxLength, std::string fieldMessage);

private:
  // fill m_messageContent before sending to DB  
  int setMessageForDB(const TCMessage & msg);
  
  // returns M12 = YYYYMMDDhhmm i.e. 200801310915
  std::string SMSDateToM12(std::string SMString);

  // Treated send message
  int LF22ToLevel3();

  int LF22ToRAS();

  int LF22ToGWI();

  int LF22ToFDB();

protected:
  //dutch: zender
  std::string m_sender;
  
  //dutch: dt_verzending
  std::string m_transmission;
  
  //dutch: type_bericht
  std::string m_typeReport;
  
  //dutch: tijdzone
  std::string m_timezone ;
  
  //dutch: bestemming
  std::string m_destination;
  
  //dutch: inhoud
  std::string m_messageContent;
  
  //dutch: p_type_zender_vorig
  std::string m_lastSender;
   
  //dutch: p_type_zender_huidig
  std::string m_currentSender;

  // ???
  long m_nr;

private:
  Tlg *tlg;
  
  // Message fields are repeates N times
  int m_fieldIterations;

  
};

#endif /* _INC_CTelcom_OutOracleTransport_45AB541F00B0_INCLUDED */