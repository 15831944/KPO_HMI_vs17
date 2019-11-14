// Copyright (C) 2004 SMS Demag AG

#include "CIntfData.h"
#include "CGasDataHandler.h"

#include "CStirringDataHandler.h"


CStirringDataHandler::~CStirringDataHandler()
{
}

CStirringDataHandler::CStirringDataHandler()
{
	m_SeqStirringData.length(0);
}


CStirringDataHandler::CStirringDataHandler(seqStirringData& SeqStirringData)
{
  fill(SeqStirringData);
}

void CStirringDataHandler::fill(seqStirringData& SeqStirringData)
{
	m_SeqStirringData = SeqStirringData;
}

seqStirringData& CStirringDataHandler::getStirringData()
{
  return m_SeqStirringData;
}

void CStirringDataHandler::update(seqStirringData& SeqStirringData)
{
  for ( long i = 0 ; i < CIntfData::getLength(SeqStirringData) ; ++i )
  {
    sStirringData StirringData;
    CIntfData::getAt(StirringData,SeqStirringData,i);

    update(StirringData);
  }
}

void CStirringDataHandler::update(sStirringData& NewStirringData)
{
  // try to find existing device of StirringData
  if ( isDevice( ( std::string)NewStirringData.Device) )
  {
    for ( long i = 0 ; i < CIntfData::getLength(m_SeqStirringData) ; ++i )
    {
      sStirringData StirringData;
      CIntfData::getAt(StirringData,m_SeqStirringData,i);

      // find position of new StirringData at m_SeqStirringData
      if ( (std::string)NewStirringData.Device == (std::string)StirringData.Device )
      {
        // update existing gas data sequence
        updateGasData(StirringData.GasData, NewStirringData.GasData);

        // restore
        CIntfData::setAt(m_SeqStirringData,StirringData,i);
      }
    }
  }
  else
  {
    insertStirringData(NewStirringData);
  }
}

double CStirringDataHandler::getGasValue(const std::string& Device, const std::string& GasType)
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

double CStirringDataHandler::getAccumulatedGasValue(const std::string& GasType)
{
  double RetValue             = DEF::Inv_Double;
  double AccumulatedGasValue  = 0.0;

  seqGasData GasDataSeq = getAccumulatedGasDataSeq();

  for ( long i = 0 ; i < CIntfData::getLength(GasDataSeq) ; ++i )
  {
    sGasData GasData;

    CIntfData::getAt(GasData,GasDataSeq,i);

    if ( (std::string)GasData.GasType == GasType )
    {
      if ( GasData.GasValue > 0. )
      {
        AccumulatedGasValue += GasData.GasValue;
      }
    }
  }

  // check if valid entries have been detected at gas data
  if ( AccumulatedGasValue > 0.0 )
  {
    RetValue = AccumulatedGasValue;
  }

  return RetValue;
}


seqGasData CStirringDataHandler::getAccumulatedGasDataSeq()
{
  return getAccumulatedGasDataSeq(m_SeqStirringData);
}

seqGasData CStirringDataHandler::getAccumulatedGasDataSeq(seqStirringData& SeqStirringData)
{
  CGasDataHandler GasDataHandler;

  for ( long i = 0 ; i < CIntfData::getLength(SeqStirringData) ; ++i )
  {
    sStirringData StirringData;

    CIntfData::getAt(StirringData,SeqStirringData,i);

    GasDataHandler.addGasData(StirringData.GasData);
  }

  return GasDataHandler.getGasData();
}

seqGasData CStirringDataHandler::getGasDataSeq(seqStirringData& SeqStirringData, const std::string& Device)
{
  seqGasData RetValue;
  RetValue.length(0);

  for ( long i = 0 ; i < CIntfData::getLength(SeqStirringData) ; ++i )
  {
    sStirringData StirringData;

    CIntfData::getAt(StirringData,SeqStirringData,i);

    if ( (std::string)StirringData.Device == Device )
    {
      RetValue = StirringData.GasData;
      break;
    }
  }

  return RetValue;
}

seqGasData CStirringDataHandler::getGasDataSeq(const std::string& Device)
{
  return getGasDataSeq(m_SeqStirringData,Device);
}

bool CStirringDataHandler::isDevice(seqStirringData& SeqStirringData, const std::string& Device)
{
  bool RetValue = false;

  for ( long i = 0 ; i < CIntfData::getLength(SeqStirringData) ; ++i )
  {
    sStirringData StirringData;

    CIntfData::getAt(StirringData,SeqStirringData,i);

    if ( (std::string)StirringData.Device == Device )
    {
      RetValue = true;
      break;
    }
  }

	return RetValue;
}

sStirringData CStirringDataHandler::findStirringData(seqStirringData& SeqStirringData, const std::string& Device)
{
  sStirringData RetValue;

  for ( long i = 0 ; i < CIntfData::getLength(SeqStirringData) ; ++i )
  {
    sStirringData StirringData;

    CIntfData::getAt(StirringData,SeqStirringData,i);

    if ( (std::string)StirringData.Device == Device )
    {
      RetValue = StirringData;
      break;
    }
  }

	return RetValue;
}

sStirringData CStirringDataHandler::findStirringData(const std::string& Device)
{
	return findStirringData(m_SeqStirringData,Device);
}

bool CStirringDataHandler::isDevice(const std::string& Device)
{
	return isDevice(m_SeqStirringData,Device);
}

bool CStirringDataHandler::isGasType(seqGasData& GasData, const std::string& GasType)
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

sGasData CStirringDataHandler::findGasData(seqGasData& GasData, const std::string& GasType)
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

void CStirringDataHandler::insertGasData(const std::string& Device,  seqGasData& GasData)
{
  sStirringData NewStirringData;

  NewStirringData.Device = Device.c_str();
  NewStirringData.GasData = GasData;

  CIntfData::insert(m_SeqStirringData,NewStirringData);
}

void CStirringDataHandler::insertGasDataValue(const std::string& Device, const std::string& GasType, double GasValue)
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
    for ( long i = 0 ; i < CIntfData::getLength(m_SeqStirringData) ; ++i )
    {
      sStirringData StirringData;
      CIntfData::getAt(StirringData,m_SeqStirringData,i);

      if ( (std::string)StirringData.Device == Device )
      {
        seqGasData GasDataSeq = StirringData.GasData;
        CIntfData::insert(GasDataSeq,NewGasDataStruct);
        StirringData.GasData = GasDataSeq;
      }
      CIntfData::setAt(m_SeqStirringData,StirringData,i);
    }
  }
}

void CStirringDataHandler::insertStirringData(sStirringData& NewStirringData)
{
  CIntfData::insert(m_SeqStirringData,NewStirringData);
}

void CStirringDataHandler::updateGasData(seqGasData& GasData, const seqGasData& NewGasData)
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
        CIntfData::getAt(ActGasDataStruct,GasData,j);

        if ( (std::string)ActGasDataStruct.GasType == (std::string)NewGasDataStruct.GasType )
        {
          CIntfData::setAt(GasData,NewGasDataStruct,j);
        }
      }      
    }
  }
}

void CStirringDataHandler::diff(seqStirringData& SeqStirringData)
{
  // step throug SeqStirringData, build difference for each GasData value and store this at m_SeqStirringData
  for ( long i = 0 ; i < CIntfData::getLength(SeqStirringData) ; ++i )
  {
    sStirringData StirringData;
    CIntfData::getAt(StirringData,SeqStirringData,i);
    std::string Device = StirringData.Device;

    // find position of new StirringData at m_SeqStirringData
    if (this->isDevice(Device))
    {
      seqGasData GasData = StirringData.GasData;
      for ( long j = 0 ; j < CIntfData::getLength(GasData) ; ++j )
      {
        sGasData GasDataStruct;
        CIntfData::getAt(GasDataStruct,GasData,j);
        std::string GasType = GasDataStruct.GasType;
        double GasValue = GasDataStruct.GasValue;

        // compare StirringData.GasData.GasType with m_SeqStirringData.GasData.GasType
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
      this->insertStirringData(StirringData);
    }
  } // for ( long i = 0 ; i < CIntfData::getLength(SeqStirringData) ; ++i )
}

void CStirringDataHandler::updateGasDataValue(const std::string& Device, const std::string& GasType, double GasValue)
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
    for ( long i = 0 ; i < CIntfData::getLength(m_SeqStirringData) ; ++i )
    {
      sStirringData StirringData;
      CIntfData::getAt(StirringData,m_SeqStirringData,i);

      // find position of new StirringData at m_SeqStirringData
      if ( (std::string)StirringData.Device == Device )
      {
        sGasData GasData;
        seqGasData GasDataStruct = StirringData.GasData;
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
        StirringData.GasData = GasDataStruct;
      } // if ( (std::string)StirringData.Device == Device )
      CIntfData::setAt(m_SeqStirringData,StirringData,i);
    } // for ( long i = 0 ; i < CIntfData::getLength(m_SeqStirringData) ; ++i )
  }
}

// set gas value for all used gas types of existing Device only
void CStirringDataHandler::setGasDataValue(std::vector<std::string> DeviceList, double Value)
{
  std::vector<std::string>::iterator it;

  // check if PlantId check is used by respective inifile entry
  for ( it = DeviceList.begin() ; it != DeviceList.end() ; ++it)
  {
    std::string Device = (*it);

    setGasDataValue(Device, Value);
  }
}

// set gas value for all used gas types of existing Device only
void CStirringDataHandler::setGasDataValue(const std::string& Device, double Value)
{
  bool GasFound = false;

  if ( isDevice(Device) )
  {
    for ( long i = 0 ; i < CIntfData::getLength(m_SeqStirringData) ; ++i )
    {
      sStirringData StirringData;
      CIntfData::getAt(StirringData,m_SeqStirringData,i);

      // find position of new StirringData at m_SeqStirringData
      if ( (std::string)StirringData.Device == Device )
      {
        sGasData GasData;
        seqGasData GasDataStruct = StirringData.GasData;
        for ( long j = 0 ; j < CIntfData::getLength(GasDataStruct) ; ++j )
        {
          CIntfData::getAt(GasData,GasDataStruct,j);
          GasData.GasValue = Value;
          CIntfData::setAt(GasDataStruct,GasData,j);
        }
        StirringData.GasData = GasDataStruct;
      } // if ( (std::string)StirringData.Device == Device )
      CIntfData::setAt(m_SeqStirringData,StirringData,i);
    } // for ( long i = 0 ; i < CIntfData::getLength(m_SeqStirringData) ; ++i )
  }
}


double CStirringDataHandler::getMaxGasDataValue(const std::string& GasType)
{
  double RetValue = DEF::Inv_Double;

  // iteration over all devices
  for ( long i = 0 ; i < CIntfData::getLength(m_SeqStirringData) ; ++i )
  {
    sStirringData StirringData;
    CIntfData::getAt(StirringData,m_SeqStirringData,i);

    seqGasData SeqGasData = StirringData.GasData;

    // iteration over all gas types
    for ( long j = 0 ; j < CIntfData::getLength(SeqGasData) ; ++j )
    {
      sGasData GasData ;

      CIntfData::getAt(GasData,SeqGasData,j);

      if ( (std::string)GasData.GasType == GasType )
      {
        if ( GasData.GasValue != DEF::Inv_Double )
        {
          RetValue = max(RetValue,GasData.GasValue);
        }
      } // if ( (std::string)GasData.GasType == GasType )
    } // for ( long j = 0 ; j < CIntfData::getLength(SeqGasData) ; ++j )
  } // for ( long i = 0 ; i < CIntfData::getLength(m_SeqStirringData) ; ++i )

  return RetValue;
}

void CStirringDataHandler::add(seqStirringData& SeqStirringData)
{
  // step throug SeqStirringData, build difference for each GasData value and store this at m_SeqStirringData
  for ( long i = 0 ; i < CIntfData::getLength(SeqStirringData) ; ++i )
  {
    sStirringData StirringData;
    CIntfData::getAt(StirringData,SeqStirringData,i);
    std::string Device = StirringData.Device;

    // find position of new StirringData at m_SeqStirringData
    if (this->isDevice(Device))
    {
      seqGasData GasData = StirringData.GasData;
      for ( long j = 0 ; j < CIntfData::getLength(GasData) ; ++j )
      {
        sGasData GasDataStruct;
        CIntfData::getAt(GasDataStruct,GasData,j);
        std::string GasType = GasDataStruct.GasType;
        double GasValue = GasDataStruct.GasValue;

        // compare StirringData.GasData.GasType with m_SeqStirringData.GasData.GasType
        if (this->isGasType(this->getGasDataSeq(Device), GasType))
        {
          double Sum = this->getGasValue(Device, GasType) + GasValue;
          this->updateGasDataValue(Device, GasType, Sum);
        }
        else
        {
          this->insertGasDataValue(Device, GasType, GasValue);
        }
      }
    }
    else
    {
      this->insertStirringData(StirringData);
    }
  } // for ( long i = 0 ; i < CIntfData::getLength(SeqStirringData) ; ++i )
}

