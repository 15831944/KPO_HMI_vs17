// Copyright (C) 2009 SMS Demag AG Germany

#include "CProcess_Monitor_TelcomIntf_Impl.h"


CProcess_Monitor_TelcomIntf_Impl::CProcess_Monitor_TelcomIntf_Impl()
{
  setBufferSize(100L);
}

CProcess_Monitor_TelcomIntf_Impl::~CProcess_Monitor_TelcomIntf_Impl()
{

}

void CProcess_Monitor_TelcomIntf_Impl::addProcess(const std::string& _plantid, const std::string& _process)
{
  if (! m_Critical_Section.lock("CProcess_Monitor_TelcomIntf_Impl::addProcess"))
  {
    return;
  }

  try
  {
    std::map< std::string, t_set >::iterator itProcesses;

    itProcesses = m_Processes.find(_plantid);
    if (itProcesses != m_Processes.end())
    {
      if (!_process.empty())
        itProcesses->second.insert(_process);
    }
    else
    {
      t_set proc;
      if (!_process.empty())
        proc.insert(_process);

      m_Processes.insert(std::make_pair<std::string,t_set>(_plantid,proc));
    }
  }
  catch(...)
  {
    m_Critical_Section.unlock("CProcess_Monitor_TelcomIntf_Impl::addProcess");

    throw;
  }

  m_Critical_Section.unlock("CProcess_Monitor_TelcomIntf_Impl::addProcess");
}

void CProcess_Monitor_TelcomIntf_Impl::addDefaultProcess(const std::string& _plantid, const std::string& _process)
{
  if (! m_Critical_Section.lock("CProcess_Monitor_TelcomIntf_Impl::addDefaultProcess"))
  {
    return;
  }

  try
  {
    std::map< std::string, t_set >::iterator itProcesses;

    itProcesses = m_DefaultProcesses.find(_plantid);
    if (itProcesses != m_DefaultProcesses.end())
    {
      if (!_process.empty())
        itProcesses->second.insert(_process);
    }
    else
    {
      t_set proc;
      if (!_process.empty())
        proc.insert(_process);
      m_DefaultProcesses.insert(std::make_pair<std::string,t_set>(_plantid,proc));
    }
  }
  catch(...)
  {
    m_Critical_Section.unlock("CProcess_Monitor_TelcomIntf_Impl::addDefaultProcess");

    throw;
  }

  m_Critical_Section.unlock("CProcess_Monitor_TelcomIntf_Impl::addDefaultProcess");
}

void CProcess_Monitor_TelcomIntf_Impl::resetProcesses(std::string _plantid)
{
  if (! m_Critical_Section.lock("CProcess_Monitor_TelcomIntf_Impl::resetProcesses"))
  {
    return;
  }

  try
  {
    std::map< std::string, t_set >::iterator itProcesses;

    itProcesses = m_Processes.find(_plantid);
    if (itProcesses != m_Processes.end())
    {
      itProcesses->second.clear();
    }
  }
  catch(...)
  {
    m_Critical_Section.unlock("CProcess_Monitor_TelcomIntf_Impl::resetProcesses");

    throw;
  }

  m_Critical_Section.unlock("CProcess_Monitor_TelcomIntf_Impl::resetProcesses");
}

std::set<std::string> CProcess_Monitor_TelcomIntf_Impl::getProcesses(std::string _plantid)
{
  std::set<std::string> RetValue;

  if (! m_Critical_Section.lock("CProcess_Monitor_TelcomIntf_Impl::getProcesses"))
  {
    return RetValue;
  }

  try
  {

    std::map< std::string, t_set >::const_iterator itProcesses;

    itProcesses = m_Processes.find(_plantid);
    if (itProcesses != m_Processes.end())
    {
      RetValue = itProcesses->second;
    }
  }
  catch(...)
  {
    m_Critical_Section.unlock("CProcess_Monitor_TelcomIntf_Impl::getProcesses");

    throw;
  }

  m_Critical_Section.unlock("CProcess_Monitor_TelcomIntf_Impl::getProcesses");

  return RetValue;
}

std::map< std::string, std::set<std::string> > CProcess_Monitor_TelcomIntf_Impl::getMonitorList()
{
  std::map< std::string, std::set<std::string> > RetValue;
  
  if (! m_Critical_Section.lock("CProcess_Monitor_TelcomIntf_Impl::getMonitorList"))
  {
    return RetValue;
  }

  try
  {
    RetValue = m_Processes;
  }
  catch(...)
  {
    m_Critical_Section.unlock("CProcess_Monitor_TelcomIntf_Impl::getMonitorList");

    throw;
  }

  m_Critical_Section.unlock("CProcess_Monitor_TelcomIntf_Impl::getMonitorList");

  return RetValue;
}

void CProcess_Monitor_TelcomIntf_Impl::initProcesses(std::string& _plantid)
{
  if (! m_Critical_Section.lock("CProcess_Monitor_TelcomIntf_Impl::initProcesses"))
  {
    return;
  }

  try
  {
    std::map< std::string, t_set >::iterator it;
    std::map< std::string, t_set >::iterator it_def;

    it = m_Processes.find(_plantid);
    if (it != m_Processes.end())
      it->second.clear();
    else
    {
      // make an empty item
      t_set proc;
      m_Processes.insert(std::make_pair<std::string,t_set>(_plantid,proc));
      it = m_Processes.find(_plantid);
    }

    // copy default task names
    it_def = m_DefaultProcesses.find(_plantid);
    if (it != m_Processes.end() && 
        it_def != m_DefaultProcesses.end())
    {
      it->second = it_def->second;
    }
  }
  catch(...)
  {
    m_Critical_Section.unlock("CProcess_Monitor_TelcomIntf_Impl::initProcesses");

    throw;
  }

  m_Critical_Section.unlock("CProcess_Monitor_TelcomIntf_Impl::initProcesses");
}

bool CProcess_Monitor_TelcomIntf_Impl::isPlantId(std::string _plantid)
{
  bool RetValue = false;
  
  if (! m_Critical_Section.lock("CProcess_Monitor_TelcomIntf_Impl::isPlantId"))
  {
    return RetValue;
  }

  try
  {
    if (m_Processes.find(_plantid) != m_Processes.end())
      RetValue = true;
  }
  catch(...)
  {
    m_Critical_Section.unlock("CProcess_Monitor_TelcomIntf_Impl::isPlantId");

    throw;
  }

  m_Critical_Section.unlock("CProcess_Monitor_TelcomIntf_Impl::isPlantId");

  return RetValue;
}
