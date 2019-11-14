// Copyright (C) 2011 SMS Siemag AG

#include <sstream>

#include "CIntfDataRuleSet.h"
#include "CIntfDataRuleValidatorDouble.h"



//##ModelId=42A0434A02E3
bool CIntfDataRuleValidatorDouble::validate(CIntfDataRuleSet* pRuleSet, double& Value)
{
  bool RetValue = true;

  if (pRuleSet)
  {
    std::stringstream Message;
    double RuleValue;
    double RuleDefault;

    // read values from rule set
    std::istringstream V(pRuleSet->getValue());
    std::istringstream D(pRuleSet->getDefault());

    // try to convert into RuleValue and RuleDefault of specific data type
    if ( V >> RuleValue && D >> RuleDefault )
    {
      // try to find rule and compare Rulevalue and ActValue according to comparator
      if ( pRuleSet->getComparator() == CIntfDataRuleSet::m_GT && Value > RuleValue )
      {
        Message << Value << " > " << RuleValue;
        RetValue = false;
      }
      else if ( pRuleSet->getComparator() == CIntfDataRuleSet::m_GE && Value >= RuleValue )
      {
        Message << Value << " >= " << RuleValue;
        RetValue = false;
      }
      else if ( pRuleSet->getComparator() == CIntfDataRuleSet::m_EQ && Value == RuleValue )
      {
        Message << Value << " == " << RuleValue;
        RetValue = false;
      }
      else if ( pRuleSet->getComparator() == CIntfDataRuleSet::m_LE && Value <= RuleValue )
      {
        Message << Value << " <= " << RuleValue;
        RetValue = false;
      }
      else if ( pRuleSet->getComparator() == CIntfDataRuleSet::m_LT && Value < RuleValue )
      {
        Message << Value << " < " << RuleValue;
        RetValue = false;
      }
      else if ( pRuleSet->getComparator() == CIntfDataRuleSet::m_NE && Value != RuleValue )
      {
        Message << Value << " != " << RuleValue;
        RetValue = false;
      }

      // if rule has been violated use default, if defined !
      if (!RetValue && pRuleSet->getDefault() != DEF::Inv_String)
      {
        Message << " -> : " << pRuleSet->getDefault();
        Value = RuleDefault;
      }

      // log respective violation
      if (!RetValue)
      {
        std::string LogMessage("CIntfDataRuleValidatorDouble::validate() failure : ");

        LogMessage += Message.str();

        log(LogMessage,5);
        
        EventLogValidationFailure(Message.str());
      }
    }
  }
  else
  { 
    log("CIntfDataRuleValidatorDouble::validate() : Invalid pointer to CIntfDataRuleSet detected ",1);
  }

	return RetValue;
}

