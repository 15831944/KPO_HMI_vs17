// Copyright (C) SMS - DEMAG 2004

//======================================================================================
//  NAME :  CTokenTable.h
//  DESCR:  Template class that represents a table to save token objects.
//          It is posible to get a token from table at actual position with
//          getToken() method, next token with lookaead() and 
//          previous token with getPreviousToken() method.
//
//  DATE :  12.01.05
//  AUTOR:  Gebert Johann
//======================================================================================
#ifndef _TOKEN_H
#define _TOKEN_H

//======================================================================================
#include <vector>
using namespace std;
#include "CToken.h"

template<class Tp> class CTokenTable
{
private:

	//!Type of token table
	typedef vector< Tp*,allocator<Tp*> > t_table; 

	//! Container to safe tokens
	typename t_table m_table;

	//! Iterator to delete all tokens
	typename t_table::iterator table_iter;

	//! Token counter to return a token at counter position. Will be increased 
	//when getToken() method is called and set to begin of table when call 
	//reinitialize().
	int token_at;

	//! Actual number of elements in the table
	typename t_table::size_type m_table_size;

	//! file name of tokens
	string m_file_name;

public:
	//! After reading tokens the table must be reinitialize for next reading. If 
	//call this method the token counter in the table will be set to start of 
	//table.
	void reinitialize()
	{
		token_at = -1;
		m_table_size = m_table.size();
	}
	//! Set the name of file in which the tokens will be read
	void setFileName(string& _fname)
	{
		m_file_name = _fname;
	}

	//! Return the name of file from whith tokens were read
	string& getFileName()
	{
		return m_file_name;
	}

	//! Return the next token without increasing token counter in the table
	Tp* lookahead()
	{
		Tp* tok = 0;
		if( m_table_size > 0 )
		{
			tok = m_table.at(token_at+1);
		}
		return tok;
	}

	//! Class default constructor
	CTokenTable(void)
	{
		token_at = -1;
		m_table_size = 0;
		m_table.clear();
	};
	//! Class destructor
	virtual ~CTokenTable(void)
	{
		clear();
	};

	//! Add token to the table
	void addToken( Tp* tok )
	{
		m_table.push_back( tok );
		m_table_size = m_table.size();
	};

	//! Return token from table and increase the token counter to next token
	Tp* getToken()
	{
		Tp* tok = 0;
		if( m_table_size > 0 )
		{
			token_at++;
			tok = m_table.at(token_at);
			m_table_size--;
		}
		return tok;
	};

	//! Return the previous token without decreasing token counter in the table
	Tp* getPreviousToken()
	{
		Tp* tok = 0;
		if( token_at > 0 )
		{
			tok = m_table.at(token_at-1);
		}
		return tok;
	};

	//! Delete all  token objects safed in table
	void clear()
	{
		token_at = -1;
//		token_at = 0;
		m_table_size = 0;
		for(table_iter=m_table.begin();
			table_iter!=m_table.end();table_iter++ )
		{
			delete *table_iter;
		}
		m_table.clear();
		m_file_name.clear();
	};
};// end class

#endif
