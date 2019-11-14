
#include "CSMC_DBMetaData.h"

//##ModelId=421C871D03AA
CSMC_DBMetaData::~CSMC_DBMetaData()
{
}

//##ModelId=421C871E01E9
CSMC_DBMetaData::CSMC_DBMetaData()
{
}

//##ModelId=421C879002F2
CSMC_DBMetaData::TypeColDescrList& CSMC_DBMetaData::getColumnDescrList()
{
  return cCBS_ODBCResultSet::m_vResltDescr;
}

