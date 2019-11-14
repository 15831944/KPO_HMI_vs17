// Copyright 2006 SMS - Demeg AG

//--------------------------------
#include "CTokenParser.h"
//-----------------------------
CTokenParser::CTokenParser():
Delimeter("|"),Pos(0) //Error("Overflow")
{
}
//-----------------------------
CTokenParser::~CTokenParser()
{
}
//-----------------------------
void CTokenParser::parsen(const std::string& line)
{
  std::string str("");
  size_t pos;

  str=line;
  TokenArray.clear();
  Pos=1;
	pos = str.find(Delimeter);
	
  while(str.size() != 0)
  {
    pos = str.find(Delimeter);
    if(pos != std::string::npos)
    {
      TokenArray.push_back(str.substr(0,pos));
      str.erase(0,pos+1);
    }
    else
    {
      TokenArray.push_back(str);
      str.clear();
    }
  }
}
//-----------------------------
std::string CTokenParser::getToken(int id) const
{
  if(((size_t)id <= TokenArray.size()) && (id > 0))
  {
    return TokenArray[id-1];
  }
  else
  {
    return "";
  }
}
//--------------------------------------------
int CTokenParser::getCountToken() const
{
  return (int)TokenArray.size();
}
//--------------------------------------------
bool CTokenParser::getNextToken(std::string& token)
{
	bool ret = false;
  if(Pos <= int(TokenArray.size()))
  {
    Pos++;
    token = TokenArray[Pos-2];
    ret = true;
  }
  else
  {
	token.clear();
  }
	return ret;
}
//--------------------------------------------
bool CTokenParser::isEmpty() const
{
  return (Pos > int(TokenArray.size()));
}
//--------------------------------------------
void CTokenParser::setDelimeter(char del)
{
	Delimeter.clear();
	Delimeter.append(1,del);
}
//--------------------------------------------

