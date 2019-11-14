#include "CMediaDataHandler.h"

void CMediaDataHandler::setMediaData(const seqConArcMediaData& SeqMediaData)
{
  for (long i = 0; i < CIntfData::getLength(SeqMediaData); ++i)
  {
    sConArcMediaData StrMediaData;
    CIntfData::getAt(StrMediaData, SeqMediaData, i);
    CIntfData::insert(m_MediaData, StrMediaData);
  }
}

// Flow and Cons are output parameter
bool CMediaDataHandler::getFlowCons(const std::string& DeviceName, long DeviceNo, long MediaTypeSelect, const std::string& MediaType, double& Flow, double& Cons)
{
  for (long i = 0; i < CIntfData::getLength(m_MediaData); ++i)
  {
    sConArcMediaData StrMediaData;
    CIntfData::getAt(StrMediaData, m_MediaData, i);
    if (DeviceName == std::string(StrMediaData.DeviceName) &&
        DeviceNo == StrMediaData.DeviceNo &&
        MediaTypeSelect == StrMediaData.MediaTypeSelect && 
        MediaType == std::string(StrMediaData.MediaType))
    {
      Flow = StrMediaData.Flow;
      Cons = StrMediaData.Cons;
      return true;
    }
  }
  Flow = 0;
  Cons = 0;
  return false;
}

bool CMediaDataHandler::getBottmStirrData(std::string& GasType, double& Flow, double& Cons)
{
  for (long i = 0; i < CIntfData::getLength(m_MediaData); ++i)
  {
    sConArcMediaData StrMediaData;
    CIntfData::getAt(StrMediaData, m_MediaData, i);
    std::string DeviceName = StrMediaData.DeviceName;
    if (DeviceName == DEF_GC_MODEL_MEDIA_DEVICE::BotmStirr)
    {
      GasType = std::string(StrMediaData.MediaType);
      Flow = StrMediaData.Flow;
      Cons = StrMediaData.Cons;
      return true;
    }
  }
  Flow = 0;
  Cons = 0;
  GasType = "";
  return false;
}