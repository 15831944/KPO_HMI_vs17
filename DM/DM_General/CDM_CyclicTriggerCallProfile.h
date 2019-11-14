// Copyright (C) 2009 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_CYCLICTRIGGERCALLPROFILE_42666D9501CF_INCLUDED
#define _INC_CDM_CYCLICTRIGGERCALLPROFILE_42666D9501CF_INCLUDED

class CEventMessage;
class CCyclicTriggerCall;
class CDateTime;

//Class representing one cyclic trigger call. The profiles 
//will be unique for EventMessage and ProductID.
class CDM_CyclicTriggerCallProfile 
{
public:

	void update(CEventMessage& Event);

  void reset();

	void send();

	bool isUsed();

	virtual ~CDM_CyclicTriggerCallProfile();

	CDM_CyclicTriggerCallProfile(CEventMessage& Event , CDM_Task* pDM_Task );

	std::string& getMessage();

	std::string& getProductID();
	std::string& getHeatID();
	std::string& getTreatID();
	std::string& getPlantID();


private:
	std::string m_DataKey;

	CDateTime m_LastUpdate;

	std::string m_ProductID;
	
	std::string m_HeatID;
	std::string m_TreatID;
	std::string m_PlantID;


	std::string m_Message;

	CCyclicTriggerCall* m_pTrigger;

};

#endif /* _INC_CDM_CYCLICTRIGGERCALLPROFILE_42666D9501CF_INCLUDED */
