// Copyright (C) 2009 SMS Demag AG Germany

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CProcess_Monitor_TelcomIntf_Impl_INCLUDED
#define _INC_CProcess_Monitor_TelcomIntf_Impl_INCLUDED

#include "CSMC_DataProvider_Impl.h"
#include "iDH_Telcom_s.hh"

class CProcess_Monitor_TelcomIntf_Impl 
  : public CSMC_DataProvider_Impl
  , public POA_DH_Telcom::iDH_Telcom
{
public:
	virtual ~CProcess_Monitor_TelcomIntf_Impl();

	CProcess_Monitor_TelcomIntf_Impl();

  // add process to list of controlled processes
  void addProcess(const std::string& _plantid, const std::string& _process);

  // add process to list of static (not changed) controled processes
  void addDefaultProcess(const std::string& _plantid, const std::string& _process);

  // return all controlled process names of a plant
  std::set<std::string> getProcesses(std::string _plantid);

  // return list of plants with process names to controll
  std::map< std::string, std::set<std::string> > getMonitorList();

  // clear processes list for a plant
  void resetProcesses(std::string _plantid);

  // call resetProcesses() and preset with static
  void initProcesses(std::string& _plantid);

  // return true if plantid is in the monitor list 
  bool isPlantId(std::string _plantid);

private:
  typedef std::set<std::string> t_set;
  //container for static process names from ini
  std::map< std::string, t_set > m_DefaultProcesses;

  //container of process names from ini file and added on runtime
  std::map< std::string, t_set > m_Processes;
};

#endif /* _INC_CProcess_Monitor_TelcomIntf_Impl_INCLUDED */
