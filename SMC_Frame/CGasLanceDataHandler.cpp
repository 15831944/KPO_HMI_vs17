// Copyright (C) 2004 SMS Demag AG

#include "CIntfData.h"
#include "CGasDataHandler.h"

#include "CGasLanceDataHandler.h"

CGasLanceDataHandler::~CGasLanceDataHandler()
{
}

CGasLanceDataHandler::CGasLanceDataHandler()
{
	m_GasLanceData.length(0);
}

CGasLanceDataHandler::CGasLanceDataHandler(seqGasLanceData& GasLanceData)
{
	fill(GasLanceData);
}

void CGasLanceDataHandler::fill(seqGasLanceData& GasLanceData)
{
	m_GasLanceData = GasLanceData;
}

seqGasLanceData& CGasLanceDataHandler::getGasLanceData()
{
  return m_GasLanceData;
}

void CGasLanceDataHandler::update(seqGasLanceData& GasLanceData)
{
  for ( long i = 0 ; i < CIntfData::getLength(GasLanceData) ; ++i )
  {
    sGasLanceData GasLanceDataStruct;
    CIntfData::getAt(GasLanceDataStruct,GasLanceData,i);

    update(GasLanceDataStruct);
  }
}

void CGasLanceDataHandler::update(sGasLanceData& GasLanceData)
{
  // try to find existing device of GasLanceData
  if ( isDevice( ( std::string)GasLanceData.Device) )
  {
    for ( long i = 0 ; i < CIntfData::getLength(m_GasLanceData) ; ++i )
    {
      sGasLanceData GasLanceDataStruct;
      CIntfData::getAt(GasLanceDataStruct,m_GasLanceData,i);

      // find position of new GasLanceData at m_GasLanceData
      if ( (std::string)GasLanceDataStruct.Device == (std::string)GasLanceData.Device )
      {
        CIntfData::setAt(m_GasLanceData,GasLanceData,i);
      }
    }
  }
  else
  {
    insertGasLanceData(GasLanceData);
  }
}

double CGasLanceDataHandler::getGasValue(const std::string& Device, const std::string& GasType)
{
  double RetValue = DEF::Inv_Double;

  seqGasData GasDataSeq = getGasDataSeq(Device);

  for ( long i = 0 ; i < CIntfData::getLength(GasDataSeq) ; ++i )
  {
    sGasData GasData;

    CIntfData::getAt(GasData,GasDataSeq,i);

    if ( (std::string)GasData.GasType == GasType )
    {
      RetValue = GasData.GasValue;
      break;
    }
  }

  return RetValue;
}

seqGasData CGasLanceDataHandler::getGasDataSeq(seqGasLanceData& GasLanceData, const std::string& Device)
{
  seqGasData RetValue;
  RetValue.length(0);

  for ( long i = 0 ; i < CIntfData::getLength(GasLanceData) ; ++i )
  {
    sGasLanceData GasLanceDataStruct;

    CIntfData::getAt(GasLanceDataStruct,GasLanceData,i);

    if ( (std::string)GasLanceDataStruct.Device == Device )
    {
      RetValue = GasLanceDataStruct.LanceData;
      break;
    }
  }

  return RetValue;
}

seqGasData CGasLanceDataHandler::getGasDataSeq(const std::string& Device)
{
  return getGasDataSeq(m_GasLanceData,Device);
}

bool CGasLanceDataHandler::isDevice(seqGasLanceData& GasLanceData, const std::string& Device)
{
  bool RetValue = false;

  for ( long i = 0 ; i < CIntfData::getLength(GasLanceData) ; ++i )
  {
    sGasLanceData GasLanceDataStruct;

    CIntfData::getAt(GasLanceDataStruct,GasLanceData,i);

    if ( (std::string)GasLanceDataStruct.Device == Device )
    {
      RetValue = true;
      break;
    }
  }

	return RetValue;
}

sGasLanceData CGasLanceDataHandler::findGasLanceData(seqGasLanceData& GasLanceData, const std::string& Device)
{
  sGasLanceData RetValue;

  for ( long i = 0 ; i < CIntfData::getLength(GasLanceData) ; ++i )
  {
    sGasLanceData GasLanceDataStruct;

    CIntfData::getAt(GasLanceDataStruct,GasLanceData,i);

    if ( (std::string)GasLanceDataStruct.Device == Device )
    {
      RetValue = GasLanceDataStruct;
      break;
    }
  }

	return RetValue;
}

sGasLanceData CGasLanceDataHandler::findGasLanceData(const std::string& Device)
{
	return findGasLanceData(m_GasLanceData,Device);
}

bool CGasLanceDataHandler::isDevice(const std::string& Device)
{
	return isDevice(m_GasLanceData,Device);
}

bool CGasLanceDataHandler::isGasType(seqGasData& GasData, const std::string& GasType)
{
  bool RetValue = false;

  for ( long i = 0 ; i < CIntfData::getLength(GasData) ; ++i )
  {
    sGasData GasDataStruct;

    CIntfData::getAt(GasDataStruct,GasData,i);

    if ( (std::string)GasDataStruct.GasType == GasType )
    {
      RetValue = true;
      break;
    }
  }

	return RetValue;
}

sGasData CGasLanceDataHandler::findGasData(seqGasData& GasData, const std::string& GasType)
{
  sGasData RetValue;

  for ( long i = 0 ; i < CIntfData::getLength(GasData) ; ++i )
  {
    sGasData GasDataStruct;

    CIntfData::getAt(GasDataStruct,GasData,i);

    if ( (std::string)GasDataStruct.GasType == GasType )
    {
      RetValue = GasDataStruct;
      break;
    }
  }

	return RetValue;
}

void CGasLanceDataHandler::insertGasData(const std::string& Device,  seqGasData& GasData)
{
  sGasLanceData NewGasLanceData;

  NewGasLanceData.Device = Device.c_str();
  NewGasLanceData.LanceData = GasData;

  CIntfData::insert(m_GasLanceData,NewGasLanceData);
}

void CGasLanceDataHandler::insertGasDataValue(const std::string& Device, const std::string& GasType, double GasValue)
{
  sGasData NewGasDataStruct;

  NewGasDataStruct.GasType  = GasType.c_str();
  NewGasDataStruct.GasValue = GasValue;

  if ( !isDevice(Device) )
  {
    seqGasData NewGasData;
    CIntfData::insert(NewGasData,NewGasDataStruct);
    insertGasData(Device, NewGasData);
  }
  else
  {
    updateGasDataValue(Device,GasType,GasValue);
  }
}

void CGasLanceDataHandler::insertGasLanceData(sGasLanceData& GasLanceData)
{
  CIntfData::insert(m_GasLanceData,GasLanceData);
}

void CGasLanceDataHandler::updateGasData(seqGasData& GasData, const seqGasData& NewGasData)
{
  for ( long i = 0 ; i < CIntfData::getLength(NewGasData) ; ++i )
  {
    sGasData NewGasDataStruct;
    CIntfData::getAt(NewGasDataStruct,NewGasData,i);

    if ( ! isGasType(GasData,(std::string)NewGasDataStruct.GasType) )
    {
      CIntfData::insert(GasData,NewGasDataStruct);
    }
    else
    {
      for ( long j = 0 ; j < CIntfData::getLength(GasData) ; ++j )
      {
        sGasData ActGasDataStruct;
        CIntfData::getAt(ActGasDataStruct,GasData,i);

        if ( (std::string)ActGasDataStruct.GasType == (std::string)NewGasDataStruct.GasType )
        {
          CIntfData::setAt(GasData,NewGasDataStruct,j);
        }
      }      
    }
  }
}

void CGasLanceDataHandler::diff(seqGasLanceData& GasLanceData)
{
  // step throug GasLanceData, build difference for each GasData value and store this at m_GasLanceData
  for ( long i = 0 ; i < CIntfData::getLength(GasLanceData) ; ++i )
  {
    sGasLanceData GasLanceDataStruct;
    CIntfData::getAt(GasLanceDataStruct,GasLanceData,i);
    std::string Device = GasLanceDataStruct.Device;

    // find position of new GasLanceData at m_GasLanceData
    if (this->isDevice(Device)  )
    {
      seqGasData GasData = GasLanceDataStruct.LanceData;
      for (long j = 0 ; j < CIntfData::getLength(GasData) ; ++j)
      {
        sGasData GasDataStruct;
        CIntfData::getAt(GasDataStruct,GasData,j);
        std::string GasType = GasDataStruct.GasType;
        double GasValue = GasDataStruct.GasValue;

        // compare GasLanceData.LanceData.GasType with m_GasLanceData.LanceData.GasType
        if (this->isGasType(this->getGasDataSeq(Device), GasType))
        {
          double Diff = max(0, (this->getGasValue(Device, GasType) - GasValue));
          this->updateGasDataValue(Device, GasType, Diff);
        }
        else
        {
          this->insertGasDataValue(Device, GasType, GasValue);
        }
      }
    }
    else
    {
      this->insertGasLanceData(GasLanceDataStruct);
    }
  } // for ( long i = 0 ; i < CIntfData::getLength(GasLanceData) ; ++i )
}

void CGasLanceDataHandler::updateGasDataValue(const std::string& Device, const std::string& GasType, double GasValue)
{
  bool GasFound = false;

  sGasData NewGasDataStruct;
  NewGasDataStruct.GasType  = GasType.c_str();
  NewGasDataStruct.GasValue = GasValue;

  if ( !isDevice(Device) )
  {
    seqGasData NewGasData;
    CIntfData::insert(NewGasData,NewGasDataStruct);
    insertGasData(Device, NewGasData);
  }
  else
  {
    for ( long i = 0 ; i < CIntfData::getLength(m_GasLanceData) ; ++i )
    {
      sGasLanceData GasLanceData;
      CIntfData::getAt(GasLanceData,m_GasLanceData,i);

      // find position of new GasLanceData at m_GasLanceData
      if ( (std::string)GasLanceData.Device == Device )
      {
        sGasData GasData;
        seqGasData GasDataStruct = GasLanceData.LanceData;
        for ( long j = 0 ; j < CIntfData::getLength(GasDataStruct) ; ++j )
        {
          CIntfData::getAt(GasData,GasDataStruct,j);
          if ( (std::string)GasData.GasType == GasType )
          {
            GasFound = true;
            GasData.GasValue = GasValue;
            CIntfData::setAt(GasDataStruct,GasData,j);
          }
        }
        if (!GasFound)
        {
          GasData.GasType = GasType.c_str();
          GasData.GasValue = GasValue;
          CIntfData::insert(GasDataStruct,GasData);
        }
        GasLanceData.LanceData = GasDataStruct;
      } // if ( (std::string)GasLanceData.Device == Device )
      CIntfData::setAt(m_GasLanceData,GasLanceData,i);
    } // for ( long i = 0 ; i < CIntfData::getLength(m_GasLanceData) ; ++i )
  }
}

double CGasLanceDataHandler::getTotalGasValue(const std::string& GasType)
{
  double RetValue = 0.0;
  CGasDataHandler GasDataHandler;

  for (long i = 0; i < CIntfData::getLength(m_GasLanceData); ++i)
  {
    sGasLanceData GasLanceData;
    CIntfData::getAt(GasLanceData,m_GasLanceData,i);
    GasDataHandler.setGasData(GasLanceData.LanceData);
    if (GasDataHandler.getGasData(GasType) != DEF::Inv_Double && GasDataHandler.getGasData(GasType) > 1)
    {
      RetValue = RetValue + GasDataHandler.getGasData(GasType);
    }
  }

  return RetValue;
}

void CGasLanceDataHandler::add(seqGasLanceData& GasLanceData)
{
  // step throug GasLanceData, build difference for each GasData value and store this at m_GasLanceData
  for ( long i = 0 ; i < CIntfData::getLength(GasLanceData) ; ++i )
  {
    sGasLanceData GasLanceDataStruct;
    CIntfData::getAt(GasLanceDataStruct,GasLanceData,i);
    std::string Device = GasLanceDataStruct.Device;

    // find position of new GasLanceData at m_GasLanceData
    if ( isDevice(Device)  )
    {
      seqGasData GasData = GasLanceDataStruct.LanceData;
      for ( long j = 0 ; j < CIntfData::getLength(GasData) ; ++j )
      {
        sGasData GasDataStruct;
        CIntfData::getAt(GasDataStruct,GasData,j);
        std::string GasType = GasDataStruct.GasType;
        double GasValue = GasDataStruct.GasValue;

        // compare GasLanceData.LanceData.GasType with m_GasLanceData.LanceData.GasType
        if ( isGasType(GasData,GasType) )
        {
          double Sum = getGasValue(Device, GasType) + GasValue;
          updateGasDataValue(Device,GasType,Sum);
        }
        else
        {
          insertGasDataValue(Device, GasType, GasValue);
        }
      }
    }
    else
    {
      this->insertGasLanceData(GasLanceDataStruct);
    }
  } // for ( long i = 0 ; i < CIntfData::getLength(GasLanceData) ; ++i )
}

std::set<std::string> CGasLanceDataHandler::getDeviceList()
{
  std::set<std::string> DeviceList;

  for ( long i = 0 ; i < CIntfData::getLength(m_GasLanceData) ; ++i )
  {
    sGasLanceData GasLanceDataStruct;
    CIntfData::getAt(GasLanceDataStruct,m_GasLanceData,i);

    DeviceList.insert(std::string(GasLanceDataStruct.Device));
  }

  return DeviceList;

}