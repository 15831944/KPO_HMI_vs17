// Copyright (C) 2004 SMS Demag AG

#include "CDM_PhaseChangeController.h"

CDM_PhaseChangeController::~CDM_PhaseChangeController()
{
}

CDM_PhaseChangeController::CDM_PhaseChangeController()
{
}

void CDM_PhaseChangeController::createTransitionRule(std::string prevState,  std::string  event, std::string targetState)
{
  std::string EventMessage(event);
  m_TransitionRules.insert(std::pair<std::string,std::string>(prevState + EventMessage, targetState));
}

