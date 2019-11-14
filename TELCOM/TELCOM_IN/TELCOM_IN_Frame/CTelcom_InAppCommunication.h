// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELCOM_INAPPCOMMUNICATION_45ACAD9303E1_INCLUDED
#define _INC_CTELCOM_INAPPCOMMUNICATION_45ACAD9303E1_INCLUDED

#include "CTelcom_Communication.h"
#include "AdapterApp.h"
#include "CTelcom_OraAdapterApp.h"

class CTelcom_InProt;

//##ModelId=45ACAD9303E1
class CTelcom_InAppCommunication : public CTelcom_Communication
{
public:
  //return actual status like connection, port/service, ip
	bool getStatus(std::string& _status);

	//Here you have to initialize the application.
	//##ModelId=45ACC9B301DE
	virtual void initComm();

	//##ModelId=45ACEDCE0104
	virtual void startComm();

	//##ModelId=45ACEDCE0386
	virtual void stopComm();

	//##ModelId=45ACAE8E01EF
	CTelcom_InAppCommunication();

	//##ModelId=45ACAE8F0242
	virtual ~CTelcom_InAppCommunication();

protected:
	//##ModelId=45AF394B0371
	CTelcom_InProt* m_pInProt;

private:
	//##ModelId=45ACCB090065
	AdapterApp* m_pAppAdatper;

  OraAdapterApp  *m_pOraAppAdatper;

  bool m_IsOraFlag;

};

#endif /* _INC_CTELCOM_INAPPCOMMUNICATION_45ACAD9303E1_INCLUDED */
