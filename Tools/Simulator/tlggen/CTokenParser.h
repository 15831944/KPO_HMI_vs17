// Copyright 2006 SMS - Demeg AG

#ifndef _CTokenParser_H_
#define _CTokenParser_H_

#include <string>
#include <vector>

//------------------------------------------------------------------
// NAME : CTokenParser.h
// DESCR: Mit diese Klasse Stringlines in einzelne Token zerlegt
// DATE:
// AUTOR: Emeljanov Anatolij
//------------------------------------------------------------------
class CTokenParser
{
  public:
    CTokenParser();
    ~CTokenParser();
		//! zerlegt line in Token
    void parsen(const std::string& line);
		//! gibt Token, der auf Position id in Container steht, zurueck
    std::string getToken(int id) const;
		//! gibt die Tokenanzahl zurueck
    int getCountToken() const;
		//! gibt true zurueck, wenn es keinen Token mehr gibt.
    bool isEmpty() const;
		//! gibt naechste Token zurueck
		bool getNextToken(std::string& token);
		//! setzt Delimeter zwischen Elementen
		void setDelimeter(char del);
  private:
		//! Delimeter zwischen Elemente in zu parsende Zeile
    std::string Delimeter;
		//! Container mit Tokens
    std::vector<std::string> TokenArray;
		//! Position naechste Token in Container
    int Pos;
		//!
		//std::string Error;
};
#endif
