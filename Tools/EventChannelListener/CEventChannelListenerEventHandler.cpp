// Copyright (C) 2011 SMS Siemag AG

#include <sstream>
#include <fstream>

#include "cCBS_StdInitBase.h"
#include "cCBS_StdLog_Task.h"
#include "CSMC_EventLogFrameController.h"

#include "CEventMessage.h"
#include "CEventChannelProtocol.h"
#include "CEventChannelProtocolRule.h"

#include "CEventChannelListenerEventHandler.h"

CEventChannelListenerEventHandler::CEventChannelListenerEventHandler()
{
  loadRules();
}

CEventChannelListenerEventHandler::~CEventChannelListenerEventHandler()
{
}




//##ModelId=41405DEE01F6
bool CEventChannelListenerEventHandler::handleEvent(const FRIESEvent& Event)
{
	CEventMessage EventMessage(Event);

  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_EventChannelMessage(sMessage,EventMessage.getContent().c_str());

	return true;
}



//##ModelId=42BBC9C40272
bool CEventChannelListenerEventHandler::checkEventAcceptance(const FRIESEvent& Event)
{
  // accept all events !
	return true;
}



//##ModelId=42C298BB00F0
bool CEventChannelListenerEventHandler::doOnEventHandlingError(const FRIESEvent& Event)
{
  // do nothing !
	return true;
}

bool CEventChannelListenerEventHandler::doOnEventMessage(const CEventMessage& EventMessage)
{
  CEventChannelProtocol* pEventChannelProtocol = findEventChannelProtocol(EventMessage.getMessage(),EventMessage.getSender(),EventMessage.getReceiver());

  if (!pEventChannelProtocol)
  {
    pEventChannelProtocol = new CEventChannelProtocol(EventMessage);
    m_EventProtocolList.insert( std::pair<std::string,CEventChannelProtocol*>(EventMessage.getMessage(),pEventChannelProtocol));
  }

  pEventChannelProtocol->doOnEvent(EventMessage);

  return checkRules();
}


CEventChannelProtocol* CEventChannelListenerEventHandler::findEventChannelProtocol(const std::string& Message,const std::string& Sender,const std::string& Receiver)
{
  CEventChannelProtocol* pEventChannelProtocol = 0;

  std::multimap<std::string,CEventChannelProtocol*>::iterator it;

  // finding something at multimap
  // per definition a multimap is sorted and ordered by the key

  // first try to set iterator to first member of container which has respective key
  for ( it = m_EventProtocolList.find(Message); it != m_EventProtocolList.end(); it++)
  {
    if ( it->second->getMessage()  == Message &&
         it->second->getReceiver() == Receiver &&
         it->second->getSender()   == Sender )
    {
      pEventChannelProtocol = it->second;
      break;
    }

    // if the first element with different key is reached, finish for loop without succcess
    if (it->second->getMessage()  != Message)
    {
      break;
    }
  }

  return pEventChannelProtocol;
}

void CEventChannelListenerEventHandler::loadRules()
{
  cCBS_StdInitBase *pInitBase = cCBS_StdInitBase::getInstance();
  
  std::string EventRuleSet;

  pInitBase->replaceWithEntry("PATH", "EventRuleSet", EventRuleSet);

  if (!EventRuleSet.empty())
  {
    EventRuleSet =  pInitBase->getXPACT_SMC() + EventRuleSet;

    std::ifstream in(EventRuleSet.c_str());
    std::string lineBuffer;
    std::string Block;

    while (getline(in, lineBuffer))
	  {
      std::string Sender;
      std::string Receiver;
      std::string Message;

      std::istringstream istr(lineBuffer);

      // processing empty and comment lines
      if(lineBuffer.empty() || lineBuffer.substr(0,2) == "//")
      {
        continue;
      }

      // rule is defined like
      // [Ev]
      // Sender1 Receiver1
      // Sender1 Receiver2
      // Sender2 Receiver3
      // ....
      
      if(lineBuffer.substr(0,1) == "[")
      {
        // Block is value inbetween "[" and "]"
        if( istr >> Block )
        {
          Block = Block.substr(1,Block.length()-2);
        }
        else
        {
          Block.erase();
        }
      }

      std::multimap<std::string,std::string> RuleList;
    
      // data will have structure Event Receiver Event Receiver ......
      while ( ( istr >> Message ) && ( istr >> Receiver ) )
      {
        RuleList.insert( std::pair<std::string,std::string>(Message,Receiver));
      }

      if ( RuleList.size() > 0 )
      {
        addRule(Block,RuleList);
      }

    }

    in.close();
  }
  

}

void CEventChannelListenerEventHandler::addRule(const std::string& Block,std::multimap<std::string,std::string> RuleList)
{
  CEventChannelProtocolRule* pEventChannelProtocolRule = new CEventChannelProtocolRule(Block,RuleList);
 
  m_EventProtocolRuleList.insert( std::pair<std::string,CEventChannelProtocolRule*>(Block,pEventChannelProtocolRule));
}

bool CEventChannelListenerEventHandler::checkRules()
{
  // iteration for all rules
  std::multimap<std::string,CEventChannelProtocolRule*>::iterator it;

  // first try to set iterator to first member of container which has respective key
  for ( it = m_EventProtocolRuleList.begin(); it != m_EventProtocolRuleList.end(); it++)
  {
    std::stringstream LogMessage;
    LogMessage << it->second->getContent() ;

    // rule can be of content SUB1 -> EV1 -> SUB2 -> EV1 -> SUB3 -> EV2 -> SUB4 ->..........
    // Block == Sender !!!
    std::string Sender = it->first;
    CEventChannelProtocolRule* pEventChannelProtocolRule = it->second;

    // rule is matched if all defined events will be found at Protocol 

    bool ruleMatched = true;

    std::multimap<std::string,std::string> RuleList = pEventChannelProtocolRule->getRuleList();
    std::multimap<std::string,std::string>::iterator itRL;
    for ( itRL = RuleList.begin(); itRL != RuleList.end(); ++itRL)
    {
      // RuleList is of content Message,Receiver !
      // CEventChannelProtocol is of content Message,Sender,Receiver !
      std::string Message = itRL->first;
      std::string Receiver = itRL->second;

      // check if eventmessage has been detected for this rule !
      CEventChannelProtocol* pEventChannelProtocol = findEventChannelProtocol(Message,Sender,Receiver);

      // for interlinked rules receiver becomes sender
      Sender = Receiver;

      if (!pEventChannelProtocol)
      {
        ruleMatched = false;
        break;
      }
    } // for ( it = pEventChannelProtocolRule->getRuleList()........


      // protocollation
    if (ruleMatched)
    {
      cCBS_StdLog_Task::getInstance()->log(LogMessage.str(),0);
    }
    else
    {
      LogMessage << " - Rule mismatch !";
      cCBS_StdLog_Task::getInstance()->log(LogMessage.str(),0);
    }

  }
 
  return true;
}


void CEventChannelListenerEventHandler::clearProtocol()
{
  std::multimap<std::string,CEventChannelProtocol*>::iterator it;

  for ( it = m_EventProtocolList.begin(); it != m_EventProtocolList.end(); it++)
  {
    delete it->second;
  }

  m_EventProtocolList.erase(m_EventProtocolList.begin(),m_EventProtocolList.end());
}
