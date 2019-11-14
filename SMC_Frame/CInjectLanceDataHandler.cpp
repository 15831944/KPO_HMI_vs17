// Copyright (C) 2008 SMS Demag AG

#include "CIntfData.h"

#include "CInjectLanceDataHandler.h"

CInjectLanceDataHandler::~CInjectLanceDataHandler()
{
}

CInjectLanceDataHandler::CInjectLanceDataHandler()
{
	m_InjectLanceData.length(0);
}

CInjectLanceDataHandler::CInjectLanceDataHandler(seqInjectLanceData& InjectLanceData)
{
	fill(InjectLanceData);
}

void CInjectLanceDataHandler::fill(seqInjectLanceData& InjectLanceData)
{
	m_InjectLanceData = InjectLanceData;
}

seqInjectLanceData& CInjectLanceDataHandler::getInjectLanceData()
{
  return m_InjectLanceData;
}

void CInjectLanceDataHandler::update(seqInjectLanceData& InjectLanceData)
{
  for ( long i = 0 ; i < CIntfData::getLength(InjectLanceData) ; ++i )
  {
    sInjectLanceData InjectLanceDataStruct;
    CIntfData::getAt(InjectLanceDataStruct,InjectLanceData,i);

    update(InjectLanceDataStruct);
  }
}

void CInjectLanceDataHandler::update(sInjectLanceData& InjectLanceData)
{
  // try to find existing device of InjectLanceData
  if ( isDevice( ( std::string)InjectLanceData.Device) )
  {
    for ( long i = 0 ; i < CIntfData::getLength(m_InjectLanceData) ; ++i )
    {
      sInjectLanceData InjectLanceDataStruct;
      CIntfData::getAt(InjectLanceDataStruct,m_InjectLanceData,i);

      // find position of new InjectLanceData at m_InjectLanceData
      if ( (std::string)InjectLanceDataStruct.Device == (std::string)InjectLanceData.Device )
      {
        CIntfData::setAt(m_InjectLanceData,InjectLanceData,i);
      }
    }
  }
  else
  {
    insertInjectLanceData(InjectLanceData);
  }
}

double CInjectLanceDataHandler::getLanceValue(const std::string& Device)
{
  double LanceVal = DEF::Inv_Double;

  sInjectLanceData InjectLanceData;

  for (long i = 0; i < CIntfData::getLength(m_InjectLanceData); i++)
  {
    CIntfData::getAt(InjectLanceData,m_InjectLanceData,i);
    if ( (std::string)InjectLanceData.Device == Device)
    {
      LanceVal = InjectLanceData.Value;
      break;
    }
  }
  return LanceVal;
}


bool CInjectLanceDataHandler::isDevice(const std::string& Device)
{
	return isDevice(m_InjectLanceData,Device);
}


bool CInjectLanceDataHandler::isDevice(seqInjectLanceData& InjectLanceData, const std::string& Device)
{
  bool RetValue = false;

  for ( long i = 0 ; i < CIntfData::getLength(InjectLanceData) ; ++i )
  {
    sInjectLanceData InjectLanceDataStruct;

    CIntfData::getAt(InjectLanceDataStruct,InjectLanceData,i);

    if ( (std::string)InjectLanceDataStruct.Device == Device )
    {
      RetValue = true;
      break;
    }
  }

	return RetValue;
}

sInjectLanceData CInjectLanceDataHandler::findInjectLanceData(seqInjectLanceData& InjectLanceData, const std::string& Device)
{
  sInjectLanceData RetValue;

  for ( long i = 0 ; i < CIntfData::getLength(InjectLanceData) ; ++i )
  {
    sInjectLanceData InjectLanceDataStruct;

    CIntfData::getAt(InjectLanceDataStruct,InjectLanceData,i);

    if ( (std::string)InjectLanceDataStruct.Device == Device )
    {
      RetValue = InjectLanceDataStruct;
      break;
    }
  }

	return RetValue;
}



sInjectLanceData CInjectLanceDataHandler::findInjectLanceData(const std::string& Device)
{
	return findInjectLanceData(m_InjectLanceData,Device);
}

void CInjectLanceDataHandler::insertInjectLanceData(sInjectLanceData& InjectLanceData)
{
  CIntfData::insert(m_InjectLanceData,InjectLanceData);
}

void CInjectLanceDataHandler::updateMatCode(const std::string& Device, const std::string& MatCode)
{
  if ( !isDevice(Device) )
  {
    sInjectLanceData InjectLanceData;
    InjectLanceData.Device = Device.c_str();
    InjectLanceData.MatCode = MatCode.c_str();
    CIntfData::insert(m_InjectLanceData,InjectLanceData);
  }
  else
  {
    for ( long i = 0 ; i < CIntfData::getLength(m_InjectLanceData) ; ++i )
    {
      sInjectLanceData InjectLanceData;
      CIntfData::getAt(InjectLanceData,m_InjectLanceData,i);

      // find position of new InjectLanceData at m_InjectLanceData
      if ( (std::string)InjectLanceData.Device == Device )
      {
        InjectLanceData.MatCode = MatCode.c_str();
      } // if ( (std::string)InjectLanceData.Device == Device )
      CIntfData::setAt(m_InjectLanceData,InjectLanceData,i);
    } // for ( long i = 0 ; i < CIntfData::getLength(m_InjectLanceData) ; ++i )
  }
}

void CInjectLanceDataHandler::updateLanceValue(const std::string& Device, double LanceVal)
{
  sInjectLanceData InjectLanceData;
  if ( !isDevice(Device) )
  {
    InjectLanceData.Device = Device.c_str();
    InjectLanceData.Value  = LanceVal;
    CIntfData::insert(m_InjectLanceData,InjectLanceData);
  }
  else
  {
    for ( long i = 0 ; i < CIntfData::getLength(m_InjectLanceData) ; ++i )
    {
      CIntfData::getAt(InjectLanceData,m_InjectLanceData,i);

      // find position of new InjectLanceData at m_InjectLanceData
      if ( (std::string)InjectLanceData.Device == Device )
      {
        InjectLanceData.Value = LanceVal;
      } // if ( (std::string)InjectLanceData.Device == Device )
      CIntfData::setAt(m_InjectLanceData,InjectLanceData,i);
    } // for ( long i = 0 ; i < CIntfData::getLength(m_InjectLanceData) ; ++i )
  }
}

void CInjectLanceDataHandler::updateModuleName(const std::string& Device, const std::string& ModuleName)
{
  sInjectLanceData InjectLanceData;

  if ( !isDevice(Device) )
  {
    InjectLanceData.Device = Device.c_str();
    InjectLanceData.ModuleName = ModuleName.c_str();
    CIntfData::insert(m_InjectLanceData,InjectLanceData);
  }
  else
  {
    for ( long i = 0 ; i < CIntfData::getLength(m_InjectLanceData) ; ++i )
    {
      CIntfData::getAt(InjectLanceData,m_InjectLanceData,i);

      // find position of new InjectLanceData at m_InjectLanceData
      if ( (std::string)InjectLanceData.Device == Device )
      {
        InjectLanceData.ModuleName = ModuleName.c_str();
      } // if ( (std::string)InjectLanceData.Device == Device )
      CIntfData::setAt(m_InjectLanceData,InjectLanceData,i);
    } // for ( long i = 0 ; i < CIntfData::getLength(m_InjectLanceData) ; ++i )
  }
}

std::string CInjectLanceDataHandler::getMatCode(const std::string& Device)
{
  std::string MatCode;
  sInjectLanceData InjectLanceData;

  for (long i = 0; i < CIntfData::getLength(m_InjectLanceData); i++)
  {
    CIntfData::getAt(InjectLanceData,m_InjectLanceData,i);
    if ( (std::string)InjectLanceData.Device == Device)
    {
      MatCode = InjectLanceData.MatCode;
      break;
    }
  }
  return MatCode;
}

std::string CInjectLanceDataHandler::getModuleName(const std::string& Device)
{
  std::string ModuleName = DEF::Inv_String;
  sInjectLanceData InjectLanceData;

  for (long i = 0; i < CIntfData::getLength(m_InjectLanceData); i++)
  {
    CIntfData::getAt(InjectLanceData,m_InjectLanceData,i);
    if ( (std::string)InjectLanceData.Device == Device)
    {
      ModuleName = InjectLanceData.ModuleName;
      break;
    }
  }
  return ModuleName;
}

void CInjectLanceDataHandler::diff(seqInjectLanceData& InjectLanceData)
{
  for ( long i = 0 ; i < CIntfData::getLength(InjectLanceData) ; ++i )
  {
    sInjectLanceData InjectLanceDataStruct;
    CIntfData::getAt(InjectLanceDataStruct,InjectLanceData,i);
    std::string Device = InjectLanceDataStruct.Device;

    if (this->isDevice(Device))
    {
      double Diff = max(0, (getLanceValue(Device) - InjectLanceDataStruct.Value));
      this->updateLanceValue(Device, Diff);
    }
    else
    {
      // insert a new device
      this->updateLanceValue(Device, InjectLanceDataStruct.Value);
    }
  }
}

void CInjectLanceDataHandler::add(seqInjectLanceData& InjectLanceData)
{
  for ( long i = 0 ; i < CIntfData::getLength(InjectLanceData) ; ++i )
  {
    sInjectLanceData InjectLanceDataStruct;
    CIntfData::getAt(InjectLanceDataStruct,InjectLanceData,i);
    std::string Device = InjectLanceDataStruct.Device;

    if (isDevice(Device))
    {
      double Sum = getLanceValue(Device) + InjectLanceDataStruct.Value;
      updateLanceValue(Device, Sum);
    }
    else
    {
      // insert a new device
      updateLanceValue(Device, InjectLanceDataStruct.Value);
    }
  }
}

std::set<std::string> CInjectLanceDataHandler::getDeviceList()
{
  std::set<std::string> DeviceList;

  for ( long i = 0 ; i < CIntfData::getLength(m_InjectLanceData) ; ++i )
  {
    sInjectLanceData InjectLanceDataStruct;
    CIntfData::getAt(InjectLanceDataStruct,m_InjectLanceData,i);

    DeviceList.insert(std::string(InjectLanceDataStruct.Device));
  }

  return DeviceList;

}