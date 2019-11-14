// Copyright 2006 SMS - Demag AG

//---------------------------------------------------------
#include "stdafx.h"
#include "CTlgLogFileReaderWrapper.h"
#include "CLogWriterWrapper.h"
#include "CStdConverter.h"
#include "CTlgWrapper.h"
//----------------------------------------------------------
CTlgLogFileReaderWrapper::CTlgLogFileReaderWrapper():
CItemBaseContainerWrapper()
{
	LogFileReader = new CLogFileReader();
	Path = nullptr;
}
//----------------------------------------------------------
CTlgLogFileReaderWrapper::~CTlgLogFileReaderWrapper()
{
  //if(LogFileReader)
  //delete LogFileReader;
}
//----------------------------------------------------------
void CTlgLogFileReaderWrapper::getClonedTlg(CItemWrapper^ tlg,int id)
{
  tlg->setTlg(LogFileReader->getFlatTlg(id));
}
//----------------------------------------------------------
void CTlgLogFileReaderWrapper::getClonedTlg(CItemWrapper^ tlg,String^ tlgName)
{
   
}
//----------------------------------------------------------
CItemWrapper^ CTlgLogFileReaderWrapper::getTlg(int id)
{
 
  CItemWrapper^ ret = gcnew CTlgWrapper();
  ret->setTlg(LogFileReader->getFlatTlg(id));
  
  /*CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,
                                                    "This methode is not implement in this cla",
                                                    __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);*/
  return ret;
}
//----------------------------------------------------------
CItemWrapper^ CTlgLogFileReaderWrapper::getTlg(String^ tlgName)
{
 CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,
                                                    "This methode is not implement in this cla",
                                                    __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  return nullptr;
}
//----------------------------------------------------------
double CTlgLogFileReaderWrapper::getTlgTime(int id)
{
	return LogFileReader->getTlgTime(id);
}
//----------------------------------------------------------
double CTlgLogFileReaderWrapper::getVirtualTlgTime(int id)
{
	int index = System::Convert::ToInt32(VirtuallContainer[id-1]);
  return LogFileReader->getTlgTime(index+1);
}
//----------------------------------------------------------
int CTlgLogFileReaderWrapper::getTlgCount()
{
	if(LogFileReader)
		return LogFileReader->getTlgCountInFile();
	else
		return 0;
}
//----------------------------------------------------------
int CTlgLogFileReaderWrapper::loadFromFile(String^ path,bool const&abort)
{
  int ret = 0;
  std::string pathstr("");
	CLogFileReader* reader = new CLogFileReader(); 
	reader->setTlgProtoTyp(TlgProtoTyp);
	Path = path;
	int test;
	test=LogFileReader->getTlgCountInFile();
	CStdConverter::StringToStdStr(path,pathstr);
  ret = reader->readLogFile(pathstr,abort);
	if(ret==0)
	{
		LogFileReader->addLogFile(reader);
		LogFileReader->setTlgCountTotal(reader->getTlgCountTotal());
    delete reader;
	}
	if (ret == -1)
	{
		delete reader;
	}
	reset();
	//LogFileReader
	//if(LogFileReader == 0)
	//LogFileReader = new CLogFileReader();
    //LogFileReader->setTlgProtoTyp(TlgProtoTyp);
  //CStdConverter::StringToStdStr(path,pathstr);
    //ret = LogFileReader->readLogFile(pathstr);
  
  return ret;
}
// !! ----------------------------------------------------------
int CTlgLogFileReaderWrapper:: loadFromFileToAnalyze(long& last_pos,String^ path,bool const& abort)
{
  int ret;
  CLogFileReader* reader = new CLogFileReader(); 
	reader->setTlgProtoTyp(TlgProtoTyp);
  /*CLogFileReader* LogFileReader;
  CTlgProtoTypSet* TlgProtoTyp;*/
  std::string pathstr ("");
  CStdConverter::StringToStdStr(path,pathstr);
  ret=reader->readLogFileToAnalyze(last_pos,pathstr,abort);
  if(ret==0)
	{
    LogFileReader->addLogFile(reader);
    LogFileReader->setTlgCountTotal(reader->getTlgCountTotal());
    delete reader;
	}
  if (ret == -1)
	{
		delete reader;
	}
  reset();
  return ret;
}
//-----------------------------------------------------------
void CTlgLogFileReaderWrapper:: closeLogFile()
{
  //LogFileReader
}
//// !!------------------------------------------------------
//int CTlgLogFileReaderWrapper:: findTelegramForAnalyze(int pos,String^ tlgName)
//{
//	int ret=0;
//	int count,i;
//	bool flag;
//	count = LogFileReader->getTlgCountTotal();
//	if(pos <= count)
//	{
//		CItemWrapper^ wr = new CTlgWrapper();
//		flag=false;
//		i=pos;
//		while((i<=count) && (!flag))
//		{
//			this->getClonedVirtualTlg(wr,i);
//			if(wr->getName()->Equals(tlgName))
//			{
//				flag=true;
//				ret=i;
//			}
//			else
//			{
//				i++;
//			}
//		}
//	}
//	
//	return ret;
//}
//----------------------------------------------------------
void CTlgLogFileReaderWrapper::setTlgProtoTyp(CTlgProtoTypSet* TlgProto)
{
    this->TlgProtoTyp = TlgProto;
}
//----------------------------------------------------------
int CTlgLogFileReaderWrapper::getCountTlgTotal()
{
	return LogFileReader->getTlgCountTotal();
}
//----------------------------------------------------------
bool CTlgLogFileReaderWrapper::checkInterface(String^ path)
{
	bool ret = false;
	std::string pathstr("");
	CLogFileReader* reader = new CLogFileReader();
	//if(LogFileReader == 0)
	//LogFileReader = new CLogFileReader();
  reader->setTlgProtoTyp(TlgProtoTyp);
  CStdConverter::StringToStdStr(path,pathstr);
	ret=reader->checkTlgProtoTypSet(pathstr);
	delete reader;
	return ret;
}
//----------------------------------------------------------
/*void CTlgLogFileReaderWrapper::reset()
{
	int count,i;
	VirtuallContainer->Clear();
    if(LogFileReader)
    {
	    count = LogFileReader->getTlgCountInFile();
	    for(i=0;i<count;i++)
	    {
		    VirtuallContainer->Add(__box(i));
	    }
    }
}*/
//----------------------------------------------------------
/*void CTlgLogFileReaderWrapper::setFilterByTelName(ArrayList* nameListe)
{
    int count,i;
	int index;
	String^ name=0;
	ArrayList* tempListe= new ArrayList(); 
	count = VirtuallContainer->Count;
	for(i=0;i<count;i++)
	{
		index = System::Convert::ToInt32(VirtuallContainer[i));
		name=CStdConverter::StdStrToString(LogFileReader->getFlatTlg(index+1)->getTlgName());
		if(nameListe->IndexOf(name) != -1)
			tempListe->Add(__box(index));
	}

	VirtuallContainer->Clear();
	VirtuallContainer=tempListe;
}*/
//----------------------------------------------------------
/*void CTlgLogFileReaderWrapper::setFilterByRegExp(String^ reg)
{
	int count,i;
	System::Text::RegularExpressions::Match* matchEx=0;
	String^ tlgName=0;
	System::Text::RegularExpressions::Regex* regEx = new System::Text::RegularExpressions::Regex(regToNetReg(reg));
	VirtuallContainer->Clear();
	if(LogFileReader)
    {
	    count = LogFileReader->getTlgCountInFile();
	    for(i=0;i<count;i++)
	    {
			tlgName=CStdConverter::StdStrToString(LogFileReader->getFlatTlg(i+1)->getTlgName());
			matchEx=regEx->Match(tlgName);
			if(matchEx->Success)
			{
				VirtuallContainer->Add(__box(i));
			}
	    }
    }
}*/
//----------------------------------------------------------
void CTlgLogFileReaderWrapper::getClonedVirtualTlg(CItemWrapper^ tlg,int id)
{
  int index = System::Convert::ToInt32(VirtuallContainer[id-1]);
  tlg->setTlg(LogFileReader->getFlatTlg(index+1));
}
//----------------------------------------------------------
void CTlgLogFileReaderWrapper::getClonedVirtualTlg(CItemWrapper^ tlg,String^ tlgName)
{
  bool flag=false;
	int count,i;
  int index;
  String^ name=nullptr;
	i=0;
  count = this->getVirtualTlgCount();
	while((!flag) && (i<count))
	{
    index=System::Convert::ToInt32(VirtuallContainer[i]);
    tlg->setTlg(LogFileReader->getFlatTlg(index+1));
    name=tlg->getName();
		if(name->Equals(tlgName))
		{
			flag=true;
		}
		else
		{
			i++;
		}
	}
}
//------------------------------------------------------------------
String^ CTlgLogFileReaderWrapper::getTlgTimeAsString(int id)
{
	return CStdConverter::StdStrToString(LogFileReader->getTlgTimeAsString(id));
}
//----------------------------------------------------------
void CTlgLogFileReaderWrapper::clearContainer()
{
	CItemBaseContainerWrapper::clearContainer();
	LogFileReader->clearContainer();
}
//----------------------------------------------------------
String^ CTlgLogFileReaderWrapper::getVirtualTlgDescr(int id)
{
	String^ ret=nullptr;
  int index=System::Convert::ToInt32(VirtuallContainer[id-1]);
  ret=CStdConverter::StdStrToString(LogFileReader->getTlgTimeAsString(index+1));
	return ret;
}
//----------------------------------------------------------
/*int CTlgLogFileReaderWrapper::findTelegramm(int pos,String^ tlgName)
{
	int ret=0;
	int count,i;
	bool flag;
	count = this->getVirtualTlgCount();
	if(pos <= count)
	{
		CItemWrapper^ wr = new CTlgWrapper();
		flag=false;
		i=pos;
		while((i<=count) && (!flag))
		{
			this->getVirtualTlg(wr,i);
			if(wr->getName()->Equals(tlgName))
			{
				flag=true;
				ret=i;
			}
			else
			{
				i++;
			}
		}
	}
	
	return ret;
}*/
//----------------------------------------------------------
/*int CTlgLogFileReaderWrapper::findTelegramm(int pos,String^ tlgName,String^ elemName,String^ rel,String^ val)
{
	int ret=0;
	int count,i;
  int pos_del;
  int relInt;
	bool flag;
	String^ elem=0;
	String^ subelem=0;
	count = this->getVirtualTlgCount();
	if(pos <= count)
	{
		CItemWrapper^ wr = new CTlgWrapper();
		flag=false;
		i=pos;
		while((i<=count) && (!flag))
		{
			this->getVirtualTlg(wr,i);
			if(wr->getName()->Equals(tlgName))
			{
          pos_del=elemName->IndexOf("\\");
          if(pos_del = -1)
          {
              subelem="";
          }
          else
          {
            subelem=elemName->Substring(pos_del+1,elemName->Length-pos_del-1);
            elemName=elemName->Substring(0,pos_del-1);
          }
          relInt=wr->compareElem(elemName,subelem,val);
          flag = ((relInt==0) && (rel->Equals("="))) || ((relInt==1) && (rel->Equals("<"))) || 
                 ((relInt==2) && (rel->Equals("<="))) || ((relInt == 3) && (rel->Equals(">"))) ||
                 ((relInt == 4) && (rel->Equals(">=")));

          if(flag)
            ret=i;
			}
			if(!flag)
				i++;

		}
	}
	return ret;
}*/
//----------------------------------------------------------