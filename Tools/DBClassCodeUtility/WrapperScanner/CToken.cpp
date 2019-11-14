// Copyright (C) 1991 - 1999 Rational Software Corporation

#include "CToken.h"



//##ModelId=40DC21980232
string& CToken::getName()
{
	return m_name;
}

//##ModelId=40DC21C60242
int CToken::getLinenumber()
{
	return m_linenum;
}

//##ModelId=40DC21DE0261
string& CToken::getText()
{
	return m_text;
}

//##ModelId=40DC21F80222
int CToken::getTokenKind()
{
	return m_kind;
}



//##ModelId=40DC2AD600AB
void CToken::setName(const char* _name)
{
	m_name = _name;
}

//##ModelId=40DC2B3B003E
void CToken::setLinenumber(int _num)
{
	m_linenum = _num;
}

//##ModelId=40DC2B74002E
void CToken::setText(const char* _t)
{
	m_text = _t;
}

//##ModelId=40DC2BBD007D
void CToken::setTokenKind(int _k)
{
	m_kind = _k;
}

