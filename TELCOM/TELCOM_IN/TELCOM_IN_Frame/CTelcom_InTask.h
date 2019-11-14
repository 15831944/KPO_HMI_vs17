// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELCOM_INTASK_45AB5BD800B0_INCLUDED
#define _INC_CTELCOM_INTASK_45AB5BD800B0_INCLUDED

#include "CTelcom_Task.h"

class CTelcom_InAppCommunication;

//##ModelId=45AB5BD800B0
class CTelcom_InTask : public CTelcom_Task
{
protected:
	//##ModelId=45AD03DC01AB
	CTelcom_InAppCommunication* m_pInAppCommunication;

	//##ModelId=45AB96F5018F
	CTelcom_InTask();
	//##ModelId=45AC967B01A7
	virtual bool initialize();

	//##ModelId=45AC967B01C5
	virtual void ownStartUp();

	//##ModelId=45AC967B01E3
	virtual void ownRunDown();

	//##ModelId=45AC967B01F7
	virtual void performWorkingStep();

private:
	//##ModelId=45ACA7B5012F
	static CTelcom_InTask* m_Instance;

public:
	void getOwnStateDetails(CORBA::String_out details);

	//##ModelId=45AC967B0214
	bool sendSwitchConnectMessage();

	//##ModelId=45ACA7DB0181
	static CTelcom_InTask* getInstance();

	//##ModelId=45AB96F3026B
	virtual void setCORBAConnections();


	//##ModelId=45AB96F50344
	virtual ~CTelcom_InTask();

};

#endif /* _INC_CTELCOM_INTASK_45AB5BD800B0_INCLUDED */
