// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CMODELPRODUCTHANDLER_4562D974010F_INCLUDED
#define _INC_CMODELPRODUCTHANDLER_4562D974010F_INCLUDED

#include <vector>

class CModelProduct;

class CDateTime;

class CModelInterfaceData;

class CIntf;

class CModelInterfaceManager 
{
public:

	CIntf* getpModelInterface(const std::string& Type, const std::string& ModelName, const std::string& ProductID);

  CIntf* getpModelInterface(const std::string& Type, const std::string& ProductID);

  bool addModelInterface(const std::string& ModelName, const std::string& Type, CIntf* pIntf );

	CModelInterfaceManager();

	virtual ~CModelInterfaceManager();

	CDateTime getHeatAnnouncementTime(const std::string& ProductID);

	bool assignProduct(const std::string& ModelName, const std::string& ProductID, const std::string& HeatID, const std::string& TreatID, long TreatNo, bool OfflineCalculationStatus);

	bool deassignProduct(const std::string& ModelName, const std::string& ProductID);

	bool deassignProduct(const std::string& ProductID);

	bool isProductID(const std::string& ModelName, const std::string& ProductID);
	bool isProductID(const std::string& ProductID);

	std::string getHeatID(const std::string& ProductID);

	std::string getTreatID(const std::string& ProductID);

	long getTreatNo(const std::string& ProductID);

	bool getOfflineCalculationStatus(const std::string& ProductID);

private:

  std::map<std::string,CModelInterfaceData*> m_ModelInterfaceList;

	long m_MaxInterfaces;

	CModelInterfaceData *  findModelInterfaceData(const std::string& ModelName, const std::string& ProductID);

	CModelInterfaceData *  findModelInterfaceData(const std::string& ProductID);

	CModelInterfaceData *  findModelInterfaceDataByName(const std::string& ModelName);


};

#endif /* _INC_CMODELPRODUCTHANDLER_4562D974010F_INCLUDED */
