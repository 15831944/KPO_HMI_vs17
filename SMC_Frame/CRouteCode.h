#ifndef _INC_CROUTECODE_INCLUDED
#define _INC_CROUTECODE_INCLUDED

#include <string>

class CRouteCode
{
public:

  CRouteCode(const std::string& ROUTECODE);
  ~CRouteCode();

  bool setRouteCode(const std::string& ROUTECODE);

  std::string getRouteCode();

  bool deleteLastLocation(long RecLength);

  bool deleteLastLocation(const std::string& RouteCodeID);

  bool setActualLocation(const std::string& RouteCodeID);

  bool compareLastLocation(const std::string& RouteCodeID);

private:

  std::string m_RouteCode;

};

#endif