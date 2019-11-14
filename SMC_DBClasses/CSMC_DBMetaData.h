
#ifndef __CSMC_DBMetaData_H__
#define __CSMC_DBMetaData_H__

#include <vector>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>

#include "cCBS_ODBCColDescr.h"
#include "cCBS_Blob.h"
#include "cCBS_Clob.h"
#include "cCBS_ODBCResultSet.h"


//##ModelId=421C85CF00CB
class CSMC_DBMetaData : public cCBS_ODBCResultSet
{
  public:  
	//##ModelId=421C871E01E9
    CSMC_DBMetaData();
	//##ModelId=421C871D03AA
    virtual ~CSMC_DBMetaData();

	//##ModelId=429DBCDD0247
  typedef std::vector<cCBS_ODBCColDescr> TypeColDescrList;

	//##ModelId=421C879002F2
    TypeColDescrList& getColumnDescrList();

};

#endif //__CSMC_DBMetaData_H__
