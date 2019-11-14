// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CMODELPRODUCT_4562D98B020E_INCLUDED
#define _INC_CMODELPRODUCT_4562D98B020E_INCLUDED

#include <map>

#include "CDateTime.h"

class CIntf;

class CModelInterfaceData 
{
public:
	CIntf* getpIntf(const std::string& IntfType);

	void setDurSinceHeatAnnouncement(double Duration);

	virtual ~CModelInterfaceData();

	CModelInterfaceData();

	void assignProduct(const std::string& ProductID, const std::string& HeatID, const std::string& TreatID, long TreatNo, bool OfflineCalculationStatus);
	void deassignProduct();

	double getDurSinceHeatAnnouncement();

	std::string getProductID();
	void setProductID(const std::string& value);

	std::string getTreatID();
	void setTreatID(const std::string& value);

	long getTreatNo();

	bool getOfflineCalculationStatus();
	void setOfflineCalculationStatus(bool value);

	std::string getHeatID();
	void setHeatID(const std::string& value);

	CDateTime getHeatAnnouncementTime();

	std::string getIntfType();
	void setIntfType(const std::string& IntfType);

  bool addInterface(const std::string& IntfType,CIntf* pIntf);

private:
  std::map<std::string,CIntf*> m_IntfList;

	std::string m_ProductID;

	std::string m_HeatID;

	std::string m_TreatID;

	long m_TreatNo;

	CDateTime m_HeatAnnouncementTime;

	bool m_OfflineCalculationStatus;

	double m_DurSinceHeatAnnouncement;


};

#endif /* _INC_CMODELPRODUCT_4562D98B020E_INCLUDED */
