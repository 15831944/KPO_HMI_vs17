// Copyright (C) 2007 SMS Demag AG

#include "CTelcom_MsgTypeTranslator.h"


//##ModelId=45ABA2800016
CTelcom_MsgTypeTranslator::CTelcom_MsgTypeTranslator()
{
	// ToDo: Add your specialized code here and/or call the base class
}

//##ModelId=45ABA28001E3
CTelcom_MsgTypeTranslator::~CTelcom_MsgTypeTranslator()
{
	// ToDo: Add your specialized code here and/or call the base class
}

//##ModelId=45ABA29501EE
long CTelcom_MsgTypeTranslator::translate(const std::string& MsgName)
{
  std::map<std::string,long>::const_iterator it = TlgStringNumMap.find(MsgName);
  if (it != TlgStringNumMap.end())
    return it->second;
  else
    return 0;
}

//##ModelId=45ABA2950216
std::string CTelcom_MsgTypeTranslator::translate(const long MsgNum)
{
  std::map<long,std::string>::const_iterator it = TlgNumStringMap.find(MsgNum);
  if (it != TlgNumStringMap.end())
    return it->second;
  else
    return "";
}

//##ModelId=45ABA295023E
void CTelcom_MsgTypeTranslator::insert(const std::string MsgName, const long MsgNum)
{
  TlgStringNumMap.insert(std::pair<std::string,long>(MsgName,MsgNum));
  TlgNumStringMap.insert(std::pair<long,std::string>(MsgNum,MsgName));
}

