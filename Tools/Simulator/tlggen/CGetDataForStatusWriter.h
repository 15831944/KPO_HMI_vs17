#pragma once
#include <windows.h>
class CGetDataForStatusWriter
{
public:
  CGetDataForStatusWriter(void);
  ~CGetDataForStatusWriter(void);
 
protected:
 virtual long getData() = 0;

  
};
