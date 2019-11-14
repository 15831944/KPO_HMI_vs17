#include "CRouteCode.h"
#include <string>

CRouteCode::CRouteCode(const std::string& ROUTECODE)
{
  m_RouteCode = ROUTECODE;
}

CRouteCode::~CRouteCode()
{
}

bool CRouteCode::setRouteCode(const std::string& ROUTECODE)
{
  bool RetValue = false;

  m_RouteCode = ROUTECODE;

  return RetValue;
}

std::string CRouteCode::getRouteCode()
{
  return m_RouteCode;
}

bool CRouteCode::deleteLastLocation(long RecLength)
{
  bool RetValue = false;
  if ((long)m_RouteCode.length() >= RecLength)
  {
    m_RouteCode = m_RouteCode.substr(0, (m_RouteCode.length()-RecLength));
    RetValue = true;
  }

  return RetValue;
}

bool CRouteCode::deleteLastLocation(const std::string& RouteCodeID)
{
  bool RetValue = false;

  if (m_RouteCode.length() >= RouteCodeID.length())
  {
    if(m_RouteCode.substr((m_RouteCode.length()-RouteCodeID.length()),RouteCodeID.length()) == RouteCodeID)
    {
      deleteLastLocation(RouteCodeID.length());
      RetValue = true;
    }
  }

  return RetValue;
}

bool CRouteCode::setActualLocation(const std::string& RouteCodeID)
{
  m_RouteCode += RouteCodeID;

  return true;
}

bool CRouteCode::compareLastLocation(const std::string& RouteCodeID)
{
  bool RetValue = false;

  if (!m_RouteCode.empty() && !RouteCodeID.empty() && (m_RouteCode.length() >= RouteCodeID.length()))
  {
    if(m_RouteCode.substr((m_RouteCode.length()-RouteCodeID.length()),RouteCodeID.length()) == RouteCodeID)
    {
      RetValue = true;
    }
  }

  return RetValue;
}