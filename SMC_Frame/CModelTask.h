// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CMODEL_TASK_4549B0B6031A_INCLUDED
#define _INC_CMODEL_TASK_4549B0B6031A_INCLUDED

#include "iDM_Interface_s.hh"
#include "CSMC_FrameTask.h"

#include "CEventMessage.h"

#include "CProxyManager.h"

#include "CDateTime.h"

#include "CModelResults_Impl.h"

class CEventMessage;

class CModelTask 
: public CSMC_FrameTask
{
public:

  virtual std::string getActProcessData(const std::string& ID);
  virtual void setActProcessData(const std::string& ID, const std::string& Value);

  virtual std::string getPlantEquipment(const std::string& Value);
  virtual void setPlantEquipment(const std::string& Equipment, const std::string& Value);

  virtual bool callModelResultWrapper(const std::string& Type ,CEventMessage& Event) = 0;

  bool checkProductAssignment(CEventMessage& Event, bool OfflineCalculationStatus);

  bool isAssignedProductID(const std::string& ProductID);

	bool getOfflineCalculationStatus(const std::string& ProductID);

	void setOfflineCalculationStatus(bool value);

	virtual ~CModelTask();

	DM::iDM_Interface_var& getpDM_Interface(const std::string& ServerName, const std::string& InterfaceTypeName);

	void initCORBAInterfaces();

	const CDateTime& getActHeatAnnouncementTime(CEventMessage & Event) const;

	void setActHeatAnnouncementTime(sDate& value);

	const std::string& getActHeatID() const;

  const std::string& getActHeatIDCust() const;

  void setActHeatIDCust(const std::string& ActHeatIDCust);

	const std::string& getActProductID() const;

	const std::string& getActTreatID() const;

  const std::string& getActTreatIDCust() const;

  void setActTreatIDCust(const std::string& ActTreatIDCust);

	const std::string& getActOrderID();

  void setActOrderID(const std::string& ActOrderID);

	const long getActTreatNo(CEventMessage & Event) const;

	void cleanProductData();

	const std::string& getActPlant();

	long getActPlantNo();

  void log(const std::string& Message, long Level);

	CModelResults_Impl* getpModelResults();

protected:

  std::string m_ProcessID;

	std::map<std::string,std::string> ActProcessDataList;
	std::map<std::string,std::string> PlantEquipmentList;

	//Virtual initialization method. Creates the task POA 
	//with the policies created by the createPolicies method 
	//and activates the task servant on this POA. Called by 
	//the activate method. Returns true on success.
	virtual bool initialize();

	CModelTask();

	std::string  m_ActPlant;

	long m_ActPlantNo;

private:
	std::string m_ActOrderID;

	bool m_OfflineCalculationStatus;

	CModelResults_Impl* m_pModelResults;

	CProxyManager<DM::iDM_Interface>* m_pDMProxyManager;

	std::string m_ActProductID;

	std::string m_ActHeatID;

	std::string m_ActTreatID;

	std::string m_ActHeatIDCust;

	std::string m_ActTreatIDCust;

	long m_ActTreatNo;

	CDateTime m_ActHeatAnnouncementTime;

	DM::iDM_Interface_var m_pDM_Interface;

};

#endif /* _INC_CMODEL_TASK_4549B0B6031A_INCLUDED */
