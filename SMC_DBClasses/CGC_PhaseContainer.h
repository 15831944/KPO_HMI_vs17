// Copyright (C) 2009 SMS Siemag AG, Germany 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGC_PHASECONTAINER_423B1F940254_INCLUDED
#define _INC_CGC_PHASECONTAINER_423B1F940254_INCLUDED

#include <list>

class CGC_PHASE;
class cCBS_Connection;
class cCBS_StdConnection;

class CGC_PhaseContainer 
{
private:
  
  typedef struct PhaseData
  {
    long L1PhaseNo;
    long ResPhaseNo;
    long PhaseNo;
    long Flag;
    std::string PhaseName;
  };

  std::map<std::string, long> m_PhaseNameList;
  std::map<std::string, PhaseData> m_PhaseDataList;

  // container for phases ordered by res_phaseno 
  // after select from GC_PHASE
  std::list<std::map<std::string,long> > m_Phases;

public:

  virtual ~CGC_PhaseContainer();

	CGC_PhaseContainer(cCBS_Connection * Connection, const std::string & Plant);

	CGC_PhaseContainer(cCBS_StdConnection * Connection, const std::string & Plant);

	long getL1PhaseNoByName(const std::string & PhaseName, const long & PhaseNo);

  long getResPhaseNo(const std::string & PhaseName, const long & PhaseNo);

  long getMaxResPhaseNo();

  // return phase name and phase number by parameter reference using L1 number
  bool getPhaseDataByL1PhaseNo(std::string& PhaseName, long& PhaseNo, long lL1PhaseNo);

  // return l2 phase name and phase number by parameter reference using L1 number
  bool getPhaseDataByResPhaseNo(std::string& PhaseName, long& PhaseNo, long ResPhaseNo);

  // return phase name with phase number ordered by RES_PHASENO
  std::list<std::map<std::string,long> > getPhases();

};

#endif /* _INC_CGC_PHASECONTAINER_423B1F940254_INCLUDED */
