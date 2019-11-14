// Copyright (C) 2007 SMS Demag AG

#include <iostream>
#include <sstream>
#include <fstream>

#include "cCBS_StdInitBase.h"
#include "CSMC_EventValidator.h"


//##ModelId=471C7256004E
CSMC_EventValidator::~CSMC_EventValidator()
{
  m_RuleSetList.erase(m_RuleSetList.begin(),m_RuleSetList.end());
}

//##ModelId=471C72560050
CSMC_EventValidator::CSMC_EventValidator()
{
	loadRules();
}

//##ModelId=471C72560051
void CSMC_EventValidator::loadRules()
{

  // rule is of content
  // [Block]
  // Names = Name1,Name2,Name3.... (default)
  // PRODUCT = Name1,Name2,Name3... (specialized entry)
  // PLANT = Name1,Name2,Name3... (specialized entry)

  // Names MUST not contain spaces !!!!


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
      std::string Name;
      std::string Entry;
      std::string Comp;
      std::vector<std::string> List;

      std::istringstream istr(lineBuffer);

      // processing empty and comment lines
      if(lineBuffer.empty() || lineBuffer.substr(0,2) == "//")
      {
        continue;
      }
      
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

      // read next line for last recognized Block
      // e.g.
      // Names = Name1,Name2,Name3.... (default)
      // PRODUCT = Name1,Name2,Name3... (specialized entry)
      // PLANT = Name1,Name2,Name3... (specialized entry)

      // Names MUST not contain spaces !!!!

      if( istr >> Entry >> Comp )
      {
        if( istr >> Name )
        {
          // check for comma separation
          std::string ActValue = Name;

          while (!ActValue.empty())
          {
            std::string ActSubstr = ActValue;

            std::basic_string <char>::size_type pos = ActValue.find(",");

            if ( std::string::npos != pos )
            {
              ActSubstr = ActValue.substr(0,pos );
              ActValue = ActValue.substr(pos+1,ActValue.length());
            }
            else
            {
              ActValue.erase();
            }

            List.push_back(ActSubstr);        
          } // while (!ActValue.empty())
        } // if( istr >> Name )
        
        std::vector<std::string>::iterator it;

        for ( it = List.begin(); it != List.end(); ++it)
        {
          std::map<std::string,std::string> EntryName;
          EntryName.insert(std::pair<std::string,std::string>(Name,(*it)));

          m_RuleSetList.insert( std::pair<std::string,std::map<std::string,std::string> >(Block,EntryName));
        }        
        
      }
    }

    in.close();
  }
  
}

//##ModelId=471C72560058
std::set<std::string> CSMC_EventValidator::getRuleSetNames(const std::string& EventMessage,const std::string& Enty /* = "Names" */)
{
  std::multimap< std::string,std::map<std::string,std::string> >::iterator it;
  std::map<std::string,std::string>::iterator itEntry;
  std::set<std::string> RuleSetNames;

  for( it = m_RuleSetList.begin() ; it != m_RuleSetList.end() ; ++it)
  {
    if ( it->first == EventMessage )
    {
      std::map<std::string,std::string> Entry = it->second;
      for( itEntry = Entry.begin() ; itEntry != Entry.end() ; ++itEntry)
      {
        if ( itEntry->first == Enty )
        {
           RuleSetNames.insert(itEntry->second);
        }
      } // for( itEntry = Entry.begin() ; itEntry != Entry.end() ; ++itEntry)
    } // if ( it->first == EventMessage )
  }

	return RuleSetNames;
}
