// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELCOM_INPROT_45AC94CD01C5_INCLUDED
#define _INC_CTELCOM_INPROT_45AC94CD01C5_INCLUDED

//#include <string>
#include "telcom.h"

//##ModelId=45AC94CD01C5
class CTelcom_InProt : public RProt
{
private:
	//Configuration from INI_file to indivate the CPU 
	//redundancy.
	//Default is false
	//##ModelId=45ACA5AC0196
	bool m_Redundancy;

public:
	//##ModelId=45AC957302DC
	CTelcom_InProt();

	//##ModelId=45AC9574014D
	virtual ~CTelcom_InProt();

protected:
	//##ModelId=45B4D2DF0002
	void onConnectHook();

	//Method called after connect errors which is executed 
	//after connect or listen 
	//on the remote transport fails, either with an error or 
	//with a timeout.
	//@param ex The ETransport exception which caused the 
	//error
	//@param isTimeout true if timeout, false if error.
	//##ModelId=45ACA23D0238
	void doOnConnectError(ETransport & ex, bool isTimeout);

	//##ModelId=45AC96CB0166
	virtual void onMissingWatchdog();

	//Reading additional information from ini file to 
	//configure of RProt can be done here.
	//##ModelId=45AC96CB017A
	virtual void configure(const std::string& section, Configuration& c);

  /** Process received telegram.
  *  <br>May call the <I>send</I> method of the remote transport to send
  *  n ACK telegram.
  *  <br>Message is logged, converted and passed to the used IMsgProcessor for further processing.
  */
  virtual bool onMessage(TCMessage & msg);

	//The function is only called if the <I>useReply</I> 
	//configuration parameter in the ini-file is true.
	//##ModelId=45AC974C0316
	void doMakeReply(const RProt::ReplyContext& context, const TCMessage& t, TCMessage& replybuf);

	//##ModelId=45B4CC7901F3
	virtual int doHandleTlgError(TC_Exception &e, TCMessage &msg);

};

#endif /* _INC_CTELCOM_INPROT_45AC94CD01C5_INCLUDED */
