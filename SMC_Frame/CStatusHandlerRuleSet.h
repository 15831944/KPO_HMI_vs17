// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CStatusHandlerRULESET_4292ED7600CB_INCLUDED
#define _INC_CStatusHandlerRULESET_4292ED7600CB_INCLUDED

#include <string>

class CStatusHandlerRuleSet 
{
protected:
public:
	std::string& getKey();

	long getState();

	long getTransition();

	virtual ~CStatusHandlerRuleSet();

	CStatusHandlerRuleSet( const std::string& Key, long State, long Transition);

private:
	std::string m_Key;
	long m_State;
	long m_Transition;

};

#endif /* _INC_CStatusHandlerRULESET_4292ED7600CB_INCLUDED */
