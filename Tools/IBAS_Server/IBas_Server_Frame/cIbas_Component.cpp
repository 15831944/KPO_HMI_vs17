// ----------------------------------------------------------------------------
// 
//                            S M S  D e m a g  A G
// 
//                             All Rights Reserved
// 
// 
//  project       : StdCaster
//  filename      : 
//  originator    : 
//  department    : 
//  creation date : 03.03.2005 10:49
//  description   : Component for IBAS
// 
// ----------------------------------------------------------------------------
// 
//  change notes:
// 
//  version  dd-mmm-yyyy 	author  	remarks
//  0.1      03.03.2005 10:49 	Uli Bellgardt   First Version
// 
// ----------------------------------------------------------------------------
// 
#pragma warning (disable: 4503 4284 4290 4018 4786)    // get rid of the annoying warning from STL
#include "cIBAS_Component.h"
#include "cIBAS_Server.h" 
#include "cIBAS_InterfaceTask.h" 
#include "CBS_Utilities\cCBS_SimpleLog.h"
#pragma warning (default: 4503 4284 4290 4018 4786 4996)    // get rid of the annoying warning from STL



//##ModelId=3D6B8805018D
void cIBAS_Component::createSubtasks()
{
  // set output path
	std::string path;
 
  cCBS_SimpleLog logs;
  m_console->restoreOutput();

	// Use TestLogPath from configurationBase also for std::cout
	//
  cCBS_ConfigBase * conf = cCBS_ConfigBase::getConfigBase();

	if   (! conf->getActGrpEle("SYSTEM", "TestLogPath", path))   
		path=std::string(".\\");
	
  char slash=*(path.c_str()+strlen(path.c_str())-1);
	
  if (slash != '\\')   
    path +="\\";

  // config base sets current working dir unexpectedly so it is better to
	// have absolute paths in configuration, not something like "..\Log" 
 
 	std::string fileNameBase = cIBAS_Server::getInstance()->getComponentName();
  std::string TraceFile = logs.logfileName(fileNameBase.c_str());
  std::string DateTime = "";
  //logs.DateTime4Filename(&DateTime);
  path += fileNameBase + "_" + DateTime + ".log";
  m_console->setTraceFile( path.c_str() );
  m_console->redirectOutput(); 

 	CBS_TaskData taskData;

	taskData.critical     = true;
	taskData.autoRecovery = true;
  taskData.priority     = MCBS::MCBS_PrioNormal;

  std::string ComponentName = std::string(m_pcIBAS_Server->getComponentName());

  m_pcIBAS_InterfaceTask = cIBAS_InterfaceTask::getInstance();

  m_pcIBAS_InterfaceTask->activate(m_componentPOA, 
      (std::string(m_pcIBAS_Server->getComponentName())+ std::string("_InterfaceTask")).c_str());

  addSubtask(m_pcIBAS_InterfaceTask->getTaskName(),
             m_pcIBAS_InterfaceTask->getReference(),
             taskData);

  startUp(RuntimeMode);
}

void cIBAS_Component::ownStartUp(void)
{
}

void cIBAS_Component::ownShutDown(void)
{
}

void cIBAS_Component::afterSubtaskEnd()
{
  CBS::shutdown();
}

cIBAS_Component::cIBAS_Component(cIBAS_Server *theServer)
: m_pcIBAS_Server(theServer),
  m_pcIBAS_InterfaceTask(0)
{
}

cIBAS_Component::~cIBAS_Component()
{
  if   (m_pcIBAS_InterfaceTask)
  {
    //delete m_pcIBAS_InterfaceTask;
    //m_pcIBAS_InterfaceTask = 0;
  }
}

void cIBAS_Component::restore(const CBS_LocalTime& _timeOccured, const CBS_OctetSequence& _data)
{
}

void cIBAS_Component::afterSubtaskStart()
{
  // nix
}
