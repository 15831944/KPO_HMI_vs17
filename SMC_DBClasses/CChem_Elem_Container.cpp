// Copyright (C) 2004, 2005 SMS Demag AG, Germany 
#include "DEF_GC_MEASUREMENT_NAME_SCOPE.h"
#include "CGC_MEASUREMENT_NAME.h"
#include "cCBS_StdDB_Task.h"
#include "CChem_Elem_Container.h"


CChem_Elem_Container::CChem_Elem_Container(cCBS_Connection* Connection)
{
  m_pCBS_StdConnection = cCBS_StdDB_Task::getInstance()->getCBS_StdConnection(Connection);

  init();
}

CChem_Elem_Container::CChem_Elem_Container(cCBS_StdConnection* Connection)
: m_pCBS_StdConnection(Connection)
{
  init();
}

void CChem_Elem_Container::init()
{
  CGC_MEASUREMENT_NAME GC_MEASUREMENT_NAME(m_pCBS_StdConnection);

  if (GC_MEASUREMENT_NAME.select(CSMC_DBData::unspecString))
  {
    m_Elements.erase(m_Elements.begin(), m_Elements.end() );

    std::string MEASNAME;
    long SCOPENO = -1;
    for (long i=1;i<=GC_MEASUREMENT_NAME.getLastRow(); i++)
    {
      MEASNAME  = GC_MEASUREMENT_NAME.getMEASNAME(i);
      SCOPENO   = GC_MEASUREMENT_NAME.getSCOPENO(i);
      m_Elements.insert(std::pair <std::string,long>(MEASNAME, SCOPENO));
    }
  }
  else
    GC_MEASUREMENT_NAME.log("ERROR: CChem_Elem_Container: cannot read elements from GC_MEASUREMENT_NAME",1);
}


//##ModelId=440D8F580257
CChem_Elem_Container::~CChem_Elem_Container()
{
}

//##ModelId=440D8F8000B0
bool CChem_Elem_Container::isSteelElem(std::string& elemName)
{
  return isMeasScope(elemName, DEF_GC_MEASUREMENT_NAME_SCOPE::Steel);
}

//##ModelId=440DB367035F
bool CChem_Elem_Container::isSlagElem(std::string& elemName)
{
  return isMeasScope(elemName, DEF_GC_MEASUREMENT_NAME_SCOPE::Slag);
}

bool CChem_Elem_Container::isEquivalence(std::string& elemName)
{
  return isMeasScope(elemName, DEF_GC_MEASUREMENT_NAME_SCOPE::Equiv);
}

bool CChem_Elem_Container::isMeasScope(std::string& elemName, long MEASUREMENT_NAME_SCOPE)
{
  bool ret = false;
  std::map<const std::string,long>::const_iterator it = m_Elements.find(elemName);

  if ( it != m_Elements.end() )
  {
    if (it->second == MEASUREMENT_NAME_SCOPE)
    {
      ret = true;
    }
  }

  return ret;
}

