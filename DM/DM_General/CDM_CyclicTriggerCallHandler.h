// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_CYCLICTRIGGERCALLHANDLER_42666D430181_INCLUDED
#define _INC_CDM_CYCLICTRIGGERCALLHANDLER_42666D430181_INCLUDED

#include <vector>
#include <string>

class CDM_CyclicTriggerCallProfile;
class CDM_Task;

//Class is handling cyclic trigger calls for events. On call 
//per unique EventMessage and ProductID will be handled in 
//the internal ProfileList. If the "call" method will be 
//called, the respective event will be inserted into the 
//list. If the "remove" method will be called, the respective 
//Event will be removed form the list and the cyclic trigger 
//will be deleted.
class CDM_CyclicTriggerCallHandler 
{
protected:
	CDM_CyclicTriggerCallHandler();

private:
	static CDM_CyclicTriggerCallHandler* m_Instance;

	std::vector<CDM_CyclicTriggerCallProfile*> m_ProfileList;

public:
	static CDM_CyclicTriggerCallHandler* getInstance();

	virtual ~CDM_CyclicTriggerCallHandler();


	//inserting Event into cyclic handling and instantiating 
	//cyclic trigger call
	void call(CEventMessage& Event , CDM_Task* pDM_Task );

  void reset(CEventMessage& Event , CDM_Task* pDM_Task );

	//removing Event form cyclic handling and deleting cyclic 
	//trigger call
	void remove(CEventMessage& Event, bool RemoveAllTriggers = false);
  void removeHeat(const std::string& HeatID, const std::string& Message, bool RemoveAllTriggers = false);
  void removeProduct(const std::string& ProductID, const std::string& Message, bool RemoveAllTriggers = false);

};

#endif /* _INC_CDM_CYCLICTRIGGERCALLHANDLER_42666D430181_INCLUDED */
