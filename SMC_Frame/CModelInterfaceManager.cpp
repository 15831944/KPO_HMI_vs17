// Copyright (C) 2004 SMS Demag AG

#include "cCBS_StdInitBase.h"

#include "CModelInterfaceManager.h"
#include "CDateTime.h"

#include "CModelInterfaceData.h"



CModelInterfaceManager::CModelInterfaceManager() 
: m_MaxInterfaces(1)
{
  cCBS_StdInitBase::getInstance()->replaceWithEntry("Model","NoOfInterfaces",m_MaxInterfaces);
}

CModelInterfaceManager::~CModelInterfaceManager()
{
}

bool CModelInterfaceManager::addModelInterface(const std::string& ModelName, const std::string& Type, CIntf* pIntf )
{
  bool RetValue = false;

  CModelInterfaceData * pModelInterfaceData = findModelInterfaceDataByName(ModelName);

  if ( 0 == pModelInterfaceData )
  {
    CModelInterfaceData * pModelInterfaceData = new CModelInterfaceData();

    m_ModelInterfaceList.insert(std::pair<std::string,CModelInterfaceData*>(ModelName,pModelInterfaceData));
  }

  if ( 0 == pModelInterfaceData->getpIntf(Type) )
  {
    pModelInterfaceData->addInterface(Type,pIntf);
  }

  return RetValue;

}

bool CModelInterfaceManager::assignProduct(const std::string& ModelName, const std::string& ProductID, const std::string& HeatID, const std::string& TreatID, long TreatNo, bool OfflineCalculationStatus)
{
  bool RetValue = false;

  CModelInterfaceData * pModelInterfaceData = findModelInterfaceData(ModelName,ProductID);

  if ( pModelInterfaceData )
  {
    pModelInterfaceData->assignProduct(ProductID, HeatID, TreatID, TreatNo, OfflineCalculationStatus);

    RetValue = true;
  }

  return RetValue;
}

bool CModelInterfaceManager::deassignProduct(const std::string& ModelName, const std::string& ProductID)
{
  bool RetValue = false;

  CModelInterfaceData * pModelInterfaceData = findModelInterfaceData(ModelName,ProductID);

  if ( pModelInterfaceData )
  {
    pModelInterfaceData->deassignProduct();
    RetValue = true;
  }

  return RetValue;
}

bool CModelInterfaceManager::deassignProduct(const std::string& ProductID)
{
  bool RetValue = false;

  CModelInterfaceData * pModelInterfaceData = findModelInterfaceData(ProductID);

  if ( pModelInterfaceData )
  {
    pModelInterfaceData->deassignProduct();
    RetValue = true;
  }

  return RetValue;
}


bool CModelInterfaceManager::isProductID(const std::string& ModelName, const std::string& ProductID)
{
  bool RetValue = false;

  CModelInterfaceData * pModelInterfaceData = findModelInterfaceData(ModelName,ProductID);

  if ( pModelInterfaceData )
  {
    RetValue = true;
  }

  return RetValue;
}

bool CModelInterfaceManager::isProductID(const std::string& ProductID)
{
  bool RetValue = false;

  CModelInterfaceData * pModelInterfaceData = findModelInterfaceData(ProductID);

  if ( pModelInterfaceData )
  {
    RetValue = true;
  }

  return RetValue;
}


std::string CModelInterfaceManager::getHeatID(const std::string& ProductID)
{
  std::string RetValue;

  CModelInterfaceData * pModelInterfaceData = findModelInterfaceData(ProductID);

  if ( pModelInterfaceData )
  {
    RetValue = pModelInterfaceData->getHeatID();
  }

  return RetValue;
}

std::string CModelInterfaceManager::getTreatID(const std::string& ProductID)
{
  std::string RetValue;

  CModelInterfaceData * pModelInterfaceData = findModelInterfaceData(ProductID);

  if ( pModelInterfaceData )
  {
    RetValue = pModelInterfaceData->getTreatID();
  }

  return RetValue;
}

long CModelInterfaceManager::getTreatNo(const std::string& ProductID)
{
  long RetValue;

  CModelInterfaceData * pModelInterfaceData = findModelInterfaceData(ProductID);

  if ( pModelInterfaceData )
  {
    RetValue = pModelInterfaceData->getTreatNo();
  }

  return RetValue;
}

bool CModelInterfaceManager::getOfflineCalculationStatus(const std::string& ProductID)
{
  bool RetValue;

  CModelInterfaceData * pModelInterfaceData = findModelInterfaceData(ProductID);

  if ( pModelInterfaceData )
  {
    RetValue = pModelInterfaceData->getOfflineCalculationStatus();
  }

  return RetValue;
}

CModelInterfaceData *  CModelInterfaceManager::findModelInterfaceData(const std::string& ProductID)
{
  CModelInterfaceData * pModelInterfaceData = 0;

  std::map<std::string,CModelInterfaceData*>::iterator it;

  for ( it = m_ModelInterfaceList.begin() ; it != m_ModelInterfaceList.end() ; it++ )
  {
    if ( it->second->getProductID() == ProductID )
    {
      pModelInterfaceData = it->second;
      break;
    }
  }

  return pModelInterfaceData;
}

CModelInterfaceData *  CModelInterfaceManager::findModelInterfaceData(const std::string& ModelName, const std::string& ProductID)
{
  CModelInterfaceData * pModelInterfaceData = 0;

  std::map<std::string,CModelInterfaceData*>::iterator it;

  for ( it = m_ModelInterfaceList.begin() ; it != m_ModelInterfaceList.end() ; it++ )
  {
    if ( it->first == ModelName )
    {
      pModelInterfaceData = it->second;
      break;
    }

    if ( it->second->getProductID() == ProductID )
    {
      pModelInterfaceData = it->second;
      break;
    }

  }

  return pModelInterfaceData;
}


CModelInterfaceData *  CModelInterfaceManager::findModelInterfaceDataByName(const std::string& ModelName)
{
  CModelInterfaceData * pModelInterfaceData = 0;

  std::map<std::string,CModelInterfaceData*>::iterator it;

  for ( it = m_ModelInterfaceList.begin() ; it != m_ModelInterfaceList.end() ; it++ )
  {
    if ( it->first == ModelName )
    {
      pModelInterfaceData = it->second;
      break;
    }
  }

  return pModelInterfaceData;
}

CDateTime CModelInterfaceManager::getHeatAnnouncementTime(const std::string& ProductID)
{
  CDateTime RetValue;

  CModelInterfaceData * pModelInterfaceData = findModelInterfaceData(ProductID);

  if ( pModelInterfaceData )
  {
    RetValue = pModelInterfaceData->getHeatAnnouncementTime();
  }

  return RetValue;
}

CIntf* CModelInterfaceManager::getpModelInterface(const std::string& Type ,const std::string& ModelName, const std::string& ProductID )
{
  CIntf* pInitf = 0;

  CModelInterfaceData * pModelInterfaceData = findModelInterfaceData(ModelName,ProductID);

  if ( pModelInterfaceData )
  {
    pInitf = pModelInterfaceData->getpIntf(Type);
  }

	return pInitf;
}

CIntf* CModelInterfaceManager::getpModelInterface(const std::string& Type ,const std::string& ProductID )
{
  CIntf* pInitf = 0;

  CModelInterfaceData * pModelInterfaceData = findModelInterfaceData(ProductID);

  if ( pModelInterfaceData )
  {
    pInitf = pModelInterfaceData->getpIntf(Type);
  }

	return pInitf;
}



