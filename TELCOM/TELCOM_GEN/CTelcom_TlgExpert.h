// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELCOM_TLGEXPERT_45AB464902C4_INCLUDED
#define _INC_CTELCOM_TLGEXPERT_45AB464902C4_INCLUDED

#include "StdTlgExpert.h"
#include "telcom.h"

class CTelcom_MsgTypeTranslator;

//////////////////////////////////////////////////
//
//Telegram access interface for use by the Prot classes.
//The interface provides access methods to set and evaluate 
//header fields
//
//////////////////////////////////////////////////
//##ModelId=45AB464902C4
class CTelcom_TlgExpert : public StdTlgExpert
{
protected:
	//##ModelId=45ABA33203B2
	CTelcom_MsgTypeTranslator* m_pMsgTypeTranslator;

	//##ModelId=45AB9BD202BF
	virtual std::string translateType(unsigned int _t);

private:
	//Loop all Telegram Elements, until type is found or the 
	//end is reached
	//##ModelId=45AB9BC50081
	std::string scanForType(TlgElem& tlgElem, const std::string& type);

public:
	//##ModelId=45AB9BC50063
	virtual const string getTlgType();

	//##ModelId=45AB953A00CF
	CTelcom_TlgExpert(CTelcom_MsgTypeTranslator *TypeTransl);

	//##ModelId=45AB953A0358
	virtual ~CTelcom_TlgExpert();

};

#endif /* _INC_CTELCOM_TLGEXPERT_45AB464902C4_INCLUDED */
