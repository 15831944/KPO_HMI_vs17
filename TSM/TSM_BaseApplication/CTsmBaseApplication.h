// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTSMBASEAPPLICATION_4105368801EB_INCLUDED
#define _INC_CTSMBASEAPPLICATION_4105368801EB_INCLUDED

#include "CTsmFileLoggingDatabase.h"
#include "CEmptyStateMachineConstructCtrl.h"
#include "CEmptyPlantConstructCtrl.h"
#include "CTsmEmptyObjectCreator.h"

class CEventMessage;
class IDatabase;

#include <string>

class CTsmBaseApplication 
{
public:

  std::string getProductStatus(CEventMessage& evMessage);

  bool isProductRegistered(CEventMessage& evMessage);

  bool isProductEventRegistered(CEventMessage& evMessage);

  bool isPlantEventRegistered(CEventMessage& evMessage);

	bool doReloadTSM(CEventMessage& evMessage);

	virtual ~CTsmBaseApplication();

	bool doHandleProductEvent(CEventMessage& evMessage);

	bool doHandlePlantEvent(CEventMessage& evMessage);

	bool doReset(CEventMessage& evMessage);

	bool handleEvent( CEventMessage& evMessage);

  CTsmBaseApplication(IDatabase *pDataBase,
                      CStateMachineConstructCtrl *pStateMachineConstructCtrl,
                      CPlantConstructCtrl *pPlantConstructCtrl,
                      CTSM_ObjectCreator *pObjectCreator,
                      const std::string &receiverName);

	bool doSetProductState(CEventMessage& evMessage);

	bool doAddProduct(CEventMessage& evMessage);

	bool doRemoveProduct(CEventMessage& evMessage);

	std::string getReceiverName();

protected:
	IDatabase* m_pDataBase;

	CStateMachineConstructCtrl* m_pStateMachineConstructCtrl;

	CPlantConstructCtrl* m_pPlantConstructCtrl;

	CTSM_ObjectCreator* m_pObjectCreator;

	CStateMachine* m_pStateMachine;

	CPlant* m_pPlant;

	std::string m_receiverName;

private:
	static const std::string evReloadTSM;

	static const std::string evReset;

	static const std::string evSetProductState;

	static const std::string evAddProduct;

	static const std::string evRemoveProduct;

// This macro defines the action handling of the handleEvent functions.
//
// Example:
//
// Contents of event string is "CERTAIN_EVENT"
// Name of event string variable is CMyClass::evCertainEvent, type
// std::string
// Name of the event handling function is CMyClass::doCertainEvent,
//      argument type CEventMessage&, return type bool
//
// bool CMyClass::handleEvent(CEventMessage& evMessage)
// {
//    HANDLE_EVENT(CertainEvent);
//    return false;
// }
#define HANDLE_EVENT(action) if (ev##action == evMessage.getMessage()) return do##action(evMessage);

};
#endif /* _INC_CTSMBASEAPPLICATION_4105368801EB_INCLUDED */
