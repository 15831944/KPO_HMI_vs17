// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CMODELWRAPPER_4118A55C0130_INCLUDED
#define _INC_CMODELWRAPPER_4118A55C0130_INCLUDED

#include <string>
#include <limits>

#include "CModelTask.h"

class CEventMessage;


//##ModelId=4118A55C0130
class CModelWrapper 
{
protected:

  //##ModelId=4123A06F0296
  CModelWrapper();

	//##ModelId=462758FF004E
  CModelTask* m_pModelTask;

  // return trace level of log task
  long getTraceLevel();

  cCBS_ODBC_DBError m_lastError;

public:

	//##ModelId=462758FF0075
  virtual void setpModelTask(CModelTask* pModelTask);

  // KLUW Site 30.04.06 use DBL_MIN and LONG_MIN
  //##ModelId=418791F9038D
  virtual long setToRange(long value, long Default = -1, long Min = LONG_MIN, long Max = LONG_MAX);

  //##ModelId=418792E701F0
  virtual double setToRange(double value, double Default = -1.0, double Min = DBL_MIN, double Max = DBL_MAX);

  //##ModelId=4187931800C0
  virtual std::string setToRange(const std::string& value, std::string Default = "***");

  //##ModelId=412CBFDB0051
  virtual void log(const std::string  & Message, long Level);

  //##ModelId=418793FB022A
  virtual bool dispatchEvent(const std::string & SenderName, const std::string  & DestinationName, CEventMessage &Event);

	//##ModelId=462758FF0093
  virtual bool dispatchEvent(const std::string & SenderName, std::vector<std::string>  & DestinationName, CEventMessage &Event);

  //##ModelId=4123A07000E8
  virtual ~CModelWrapper();

};

#endif /* _INC_CMODELWRAPPER_4118A55C0130_INCLUDED */
