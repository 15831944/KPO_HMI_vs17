#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTelcom_InOracleTransport_45AB541F00B0_INCLUDED
#define _INC_CTelcom_InOracleTransport_45AB541F00B0_INCLUDED

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
class CTelcom_InOracleTransport : public CTelcom_OracleTransport
{ 
public:
	CTelcom_InOracleTransport();

	virtual ~CTelcom_InOracleTransport();

protected:
  /*  The overloaded virtual method "receive" - reads first few bytes of 
  each message to determine the remaining  number of bytes to read so 
  that Telcom can handle the remainder of the message.  */

  virtual void configure(const std::string & section, bas::Configuration & c);

  virtual int doConnect();

	virtual int receive(TCMessage & msg);

	virtual int doDisconnect();
  
  // Notify message (FEL)
  // x = alphanumeric characters (right padded blanks) 
  // 9 = numeric characters (left padded 0)
  std::string convertMessage(std::string messageFormat, int maxLength);

  // to fill the fields on specific policy with information
  // x = alphanumeric characters (right padded blanks) 
  // 9 = numeric characters (left padded 0)
  // only for comma separated MSGs (CSV)
  std::string convertMessage(std::string messageFormat, int maxLength, std::string fieldMessage);

private:
  int getBerichtFromDB();

  // fills the elements of a message in a vector
  void setRawMessage(int headerLength);

  // Treated received message
  int Proco2ToLF22();

  int FDBToLF22();

  int BOFToLF22();

  int SparcsToLF22();

  int SamtracsToLF22();

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
  
  std::string p_poort;
  std::string p_Proco2;
  std::string p_FDB;
  std::string p_BOF;
  std::string p_Sparcs;
  std::string p_Samtracs;

  double p_timeout;

  // contains a Msg without the header
  std::vector<std::string> m_vRawMessageContent; 

private:
  TCMessage* tofillMsg;

  // Message fields are repeates N times
  int m_fieldIterations;
  
  Tlg *tlg;
  
  // test stream
  ofstream TestTlgLog; 
  
};

#endif /* _INC_CTelcom_InOracleTransport_45AB541F00B0_INCLUDED */