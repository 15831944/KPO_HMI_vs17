// Copyright (C) SMS - DEMAG 2004

//======================================================================================
//  NAME :  CToken.h
//  DESCR:  Class "CToken" that discribes the token from the lexical analyser.
//
//  DATE :  12.01.05
//  AUTOR:  Gebert Johann
//======================================================================================
#ifndef _CToken_H
#define _CToken_H
#include <string>
using namespace std; 



//======================================================================================
class CToken
{
private:

	string m_text;   // token text

	int m_kind;      // kind of token

	int m_linenum;   // line number of token place

	string m_name;   // token name

public:
	// set name of token
	void setName(const char* _name);

	// set line number of token appearance
	void setLinenumber(int _num);

	// set tex of token
	void setText(const char* _t);

	// set kind of token
	void setTokenKind(int _k);

	// return token name
	string& getName();

	// return line number
	int getLinenumber();

	// return token text
	string& getText();

	// kind of token defined in "lexsymb.h"
	int getTokenKind();
	
	// constructor
	CToken(){m_kind=0;};

	// destructor
	~CToken(){};
};
#endif
