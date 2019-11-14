// Copyright (C) 2004 SMS Demag AG

#include "CModelInterfaceData.h"



CModelInterfaceData::~CModelInterfaceData()
{
}

CModelInterfaceData::CModelInterfaceData()
{
}

bool CModelInterfaceData::addInterface(const std::string& IntfType, CIntf* pIntf)
{
  bool RetValue = false;

  CIntf* pModelInterface = getpIntf(IntfType);

  if ( ! pModelInterface )
  {
    m_IntfList.insert(std::pair<std::string,CIntf*>(IntfType,pIntf));
    RetValue = true;
  }

  return RetValue;
}

void CModelInterfaceData::assignProduct(const std::string& ProductID, const std::string& HeatID, const std::string& TreatID, long TreatNo, bool OfflineCalculationStatus)
{
  m_ProductID                = ProductID;
  m_HeatID                   = HeatID;
  m_TreatID                  = TreatID;
  m_TreatNo                  = TreatNo;
  m_OfflineCalculationStatus = OfflineCalculationStatus;
}

void CModelInterfaceData::deassignProduct()
{
  m_ProductID                = "";
  m_HeatID                   = "";
  m_TreatID                  = "";
  m_TreatNo                  = -1;
  m_OfflineCalculationStatus = false;
}

double CModelInterfaceData::getDurSinceHeatAnnouncement()
{
	return m_DurSinceHeatAnnouncement;
}

std::string CModelInterfaceData::getProductID()
{
	return m_ProductID;
}

std::string CModelInterfaceData::getTreatID()
{
	return m_TreatID;
}

long CModelInterfaceData::getTreatNo()
{
	return m_TreatNo;
}

bool CModelInterfaceData::getOfflineCalculationStatus()
{
	return m_OfflineCalculationStatus;
}

std::string CModelInterfaceData::getHeatID()
{
	return m_HeatID;
}

CDateTime CModelInterfaceData::getHeatAnnouncementTime()
{
	return m_HeatAnnouncementTime;
}

void CModelInterfaceData::setDurSinceHeatAnnouncement(double Duration)
{
  m_DurSinceHeatAnnouncement = Duration;
}

CIntf* CModelInterfaceData::getpIntf(const std::string& IntfType)
{
  CIntf* pIntf = 0;

  std::map<std::string,CIntf*>::iterator it;

  for ( it = m_IntfList.begin() ; it != m_IntfList.end() ; ++ it)
  {
    if ( it->first == IntfType )
    {
      pIntf = it->second;
      break;
    }
  }

	return pIntf;
}

void CModelInterfaceData::setOfflineCalculationStatus(bool value)
{
	m_OfflineCalculationStatus = value;
}

