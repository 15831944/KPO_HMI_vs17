// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELCOM_OUTAPPCOMMUNICATION_45AE4F51028B_INCLUDED
#define _INC_CTELCOM_OUTAPPCOMMUNICATION_45AE4F51028B_INCLUDED

#include "CTelcom_Communication.h"

#include "AdapterApp.h"
#include "CTelcom_OraAdapterApp.h"

class CTelcom_OutProt;
class CTelcom_QueueManager;

//##ModelId=45AE4F51028B
class CTelcom_OutAppCommunication : public CTelcom_Communication
{
private:
	//##ModelId=45AF9C570384
	CTelcom_QueueManager* m_pQueueManager;

	//##ModelId=45AE6FA802FC
	AdapterApp* m_pAppAdatper;

  OraAdapterApp  *m_pOraAppAdatper;

	//##ModelId=45AF3988001D
	CTelcom_OutProt* m_pOutProt;

  bool m_IsOraFlag;

public:
	//return actual status like connection, port/service, ip
	bool getStatus(std::string& _status);

	//##ModelId=45AF9CEB014E
	CTelcom_QueueManager* getQueueManager();

	//##ModelId=45AE4FC40282
	CTelcom_OutAppCommunication();

	//##ModelId=45AE4FC501D3
	virtual ~CTelcom_OutAppCommunication();

	//Initialize of application, protocol, transport, 
	//factory, source transport, event handler.
	//##ModelId=45AE4FCA0359
	virtual void initComm();

	//##ModelId=45AE4FCB0209
	virtual void startComm();

	//##ModelId=45AE4FCC011C
	virtual void stopComm();

	//##ModelId=45B4EBC1025A
	CTelcom_OutProt* getOutProt();

};

#endif /* _INC_CTELCOM_OUTAPPCOMMUNICATION_45AE4F51028B_INCLUDED */
