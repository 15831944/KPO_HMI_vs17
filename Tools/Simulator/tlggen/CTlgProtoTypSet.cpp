// Copyright 2006 SMS - Demag AG

//----------------------------------------------------
#include "CTlgProtoTypSet.h"
#include "CTlg.h"
#include "CExpUnknownTlg.h"
#include "CFormatConverter.h"
//----------------------------------------------------
CTlgProtoTypSet::CTlgProtoTypSet():
Name(""),Version(""),Comment("")
{
}
//---------------------------------------------------
CTlgProtoTypSet::~CTlgProtoTypSet()
{
	freeTlg();
}
//-------------------------------------------------------------
const std::string& CTlgProtoTypSet::getName() const
{
  return Name;
}
//-------------------------------------------------------------
void CTlgProtoTypSet::setName(const std::string& value)
{
  Name = value;
}
//-------------------------------------------------------------
const std::string& CTlgProtoTypSet::getVersion() const
{
  return Version;
}
//-------------------------------------------------------------
void CTlgProtoTypSet::setVersion(const std::string& value)
{
  Version = value;
}
//---------------------------------------------------------------
int CTlgProtoTypSet::getTlgCount() const
{
  return TlgProtoMap.getTlgCount();
}
//---------------------------------------------------------------
void CTlgProtoTypSet::addTlgPrototyp(CTlg* tlg)
{
  TlgProtoMap.addTlg(tlg->getTlgName(),tlg);
  //Da die Funktion nur bei ProtoTyp - Telegrammen aufgerufen wird, wird der Index jedes Mal neu gebildet.
	TlgProtoMap.BuildIndex();
  //TlgProtoMap.insert(std::pair<std::string,CTlg*>(tlg->getTlgName(),tlg));
}
//---------------------------------------------------------------
void CTlgProtoTypSet::setComment(const std::string& value)
{
	Comment = value;
}
//---------------------------------------------------------------
const std::string& CTlgProtoTypSet::getComment() const
{
	return Comment;
}
//---------------------------------------------------------------
CTlg* CTlgProtoTypSet::makeFlatTlg(const std::string& name) throw (CExpUnknownTlg)
{
	CTlg* ret=0;
	ret = TlgProtoMap.getFlatTlg(name);
	if(ret == 0)
	{
		throw CExpUnknownTlg(name,"");
	}
	return ret;
}
//---------------------------------------------------------------------
CTlg* CTlgProtoTypSet::makeTlg(int id) throw (CExpUnknownTlg)
{
	CTlg* ret = 0;
	CTlg* tlg=TlgProtoMap.getFlatTlg(id);
  if(tlg)
  {
	  ret = tlg->clone();
  }
  else
  {
    std::string err = CFormatConverter::IntToString(id);
	  throw CExpUnknownTlg(err,"");
  }
	return ret;
}
//---------------------------------------------------------------------
CTlg* CTlgProtoTypSet::makeFlatTlg(int id) throw (CExpUnknownTlg)
{
	CTlg* ret=0;
	ret = TlgProtoMap.getFlatTlg(id);
	if(ret == 0)
	{
		std::string err = CFormatConverter::IntToString(id);
		throw CExpUnknownTlg(err,"");
	}
	return ret;
}
//---------------------------------------------------------------------
CTlg* CTlgProtoTypSet::makeTlg(const std::string& name) throw (CExpUnknownTlg)
{
	CTlg* ret=0;
	CTlg* tlg=0;
	tlg = TlgProtoMap.getFlatTlg(name);
	if(tlg == 0)
	{
		throw CExpUnknownTlg(name,"");
	}
	else
	{
		ret = tlg->clone();
	}
	return ret;
}
//---------------------------------------------------------------------
void CTlgProtoTypSet::freeTlg()
{
	TlgProtoMap.freeTlg(true);
}
//---------------------------------------------------------------------
