// Copyright 2006 SMS - Demag AG

//-------------------------------------------------------------------- 
#include "CLogFileReader.h"
#include "CTlgProtoTypSet.h"
#include "CExpTimeError.h"
#include "CExpDateError.h"
#include "CMessageStack.h"
#include "CExpUnknownTlg.h"
#include "CExpInvalidTlg.h"
#include "CExpConvertError.h"
#include "CExpLimitError.h"
#include "CExpTlgLenError.h"
#include "CProgressInfoByFileLogRead.h"
#include "CLogWriter.h"
//--------------------------------------------------------------------
#include <string>
//--------------------------------------------------------------------
CLogFileReader::CLogFileReader():
TlgProtoTyp(0),TlgCount(0),EmptyLineCount(0),WrongLineCount(0)
{
}
//------------------------------------------------------------------
CLogFileReader::~CLogFileReader()
{
  TlgContainer.freeTlg(false);
}
//-------------------------------------------------------------------------
void CLogFileReader::setTlgProtoTyp(CTlgProtoTypSet* tlgProtoTyp)
{
  this->TlgProtoTyp = tlgProtoTyp;
}
//----------------------------------------------------------
int CLogFileReader::readLogFile(const std::string& path,bool const&abort)
{
  CTelTime tlgTime;
	CTlg* tlg=0;
	char buff[16384];
	std::string line;
	int pos;
	double time;
	std::string interName;
  long lineSize = 0;
  CProgressInfoByFileLogRead* InfoByFileLogRead = CProgressInfoByFileLogRead::getProgressInfoByFileLogRead();
  InfoByFileLogRead->setStatusReady(false);
  InfoByFileLogRead->resetData();
  CMessageStack* messStack = CMessageStack::getMessageStack(); 
  CLogWriter* logWriter = CLogWriter::getLogWriter();
	
	interName=TlgProtoTyp->getName();
	CInterConfig* interConf=CInterConfig::getInterConfig(interName);
	tlgTime.setTimeFormat(interConf->getTimeFormat());
  
  InFile.open(path.c_str(),std::ios::in);
	if(!InFile.is_open())
  {
    std::string mess = "<" + path + "> can't open.";
    logWriter->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
    return 1;
  }
	TlgCount=0;

  while(InFile.getline(buff,16384) && !abort)
	{
		TlgCount++;
	  line.clear();
		line.append(buff);
    lineSize = long(line.size());
    InfoByFileLogRead->setData(lineSize);
    //Pruefen, ob die Zeile leer ist.
    if(!line.empty())
    {
      if(createTimeTlg(tlgTime,line))
      {
        tlg=createTlg(line);
		    if(tlg != 0)
		    {
			    pos = (int)line.find_last_of(';');
			    if(pos != std::string::npos)
			    {
				    line = line.substr(pos+1,line.size()-pos-1);
    		    if(loadTlg(tlg,line))
				    {
					    time=tlgTime.getTimeAsDouble();
					    TlgContainer.addTlg(time,tlg);
					    //addTlg(tlg,tlgTime);	 
            } 
            else
            {
              std::string mess = "Loading telegram (" + interName + ") failed";
              logWriter->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
            }
			    }
        }
      }
    }
    else
    {
      TlgCount--;
      EmptyLineCount++; 
    }
    /*InfoByFileLogRead->setData(lineSize);*/
  }//end of while(inFile.getline(buff,1024))

	//Index neu bilden
	TlgContainer.BuildIndex();
  
  if (EmptyLineCount > 0)
  {
    std::string mess = CFormatConverter::IntToString(EmptyLineCount) + " empty lines in log file";
    messStack->addMessage(mess,1); 
    logWriter->WriteMessage(CLogWriter::Warning,mess + " in " + path,__FILE__,__FUNCTION__,__LINE__);
  }

  InfoByFileLogRead->setStatusReady(true);
	InFile.close();
  
	//Falls Vorgang abgebrochen
	if (abort)
	{
		TlgContainer.freeTlg(true);
		std::string mess = "Read of the log file aborted!";
    logWriter->WriteMessage(CLogWriter::Info,mess,__FILE__,__FUNCTION__,__LINE__);
		return -1;
	}
	
	return 0;
}
//-----------------------------------------------------------
bool CLogFileReader::createTimeTlg(CTelTime& time,const std::string& line)
{
  bool ret = true;
  size_t pos;
  std::string mess("");
  std::string str("");
  std::string datestr("");
  std::string timestr("");
  CMessageStack* messStack = CMessageStack::getMessageStack();
  
  try
  {
    str=line;
    pos=str.find(' ');
    if(pos != std::string::npos)
    {
      datestr=str.substr(0,pos);
	    str.erase(0,pos+1);
	    //time.setDate(token);
	    pos=str.find(' ');
      if(pos != std::string::npos)
      {
        timestr=str.substr(0,pos);
        time.setTime(datestr,timestr);
      }
	    else
	    {
	      mess = "Unknown Time Error";
        CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
        messStack->addMessage(mess,2);
        mess = "Line: " + line;
        CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
        messStack->addMessage(mess,2);
        ret=false;
	    }
    }
    else
    {
      mess = "Unknown Time Error";
      CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
      messStack->addMessage("Unknown Time Error",2);
      mess = "Line: " + line;
      CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
      messStack->addMessage("Line: " + line,2);
      ret=false;
    }
  }
  catch(CExpDateError& e)
  {
    mess = e.getDate() + " ---Unknown Date Format";
    CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);  
    messStack->addMessage(mess,2);
    CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
    mess = "Line: " + line;
    CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
    messStack->addMessage(mess,2);
    ret=false;
  }
  catch(CExpTimeError& e)
  {
    mess = e.getTime() + " ---Unknown Time Format";
    CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
    messStack->addMessage(mess,2);
    mess = "Line: " + line;
    CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
    messStack->addMessage(mess,2);
    ret=false;
  }
  catch(...)
  {   
    mess = "Unknown Time Error";
    CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
    messStack->addMessage(mess,2);
    mess = "Line: " + line;
    CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
    messStack->addMessage(mess,2);
    ret=false;
  }
  //Falls Fehler, incrementieren
  if (!ret)
    WrongLineCount++;
  
  return ret;
}
//------------------------------------
CTlg* CLogFileReader::createTlg(const std::string& line)
{
  CTlg* tlg=0;
  std::string mess("");
  std::string tlg_name("");
  size_t pos_name;
  CMessageStack* messStack = CMessageStack::getMessageStack();
  try
  {
    pos_name=line.find("TYPE");          //???????????????
    if(pos_name != std::string::npos)
    {
      tlg_name = line.substr(pos_name+1,line.size()-pos_name-1);
      pos_name = tlg_name.find(";");
      if(pos_name != std::string::npos)
      {
        tlg_name = tlg_name.substr(pos_name+1,tlg_name.size()-pos_name-1);
        pos_name = tlg_name.find(";");
        if(pos_name != std::string::npos)
        {
          tlg_name = tlg_name.substr(0,pos_name);
          if(pos_name != std::string::npos)
          {
            tlg=TlgProtoTyp->makeTlg(tlg_name);
          }
        }
      }
    }
    else
    {
      if(tlg == 0)
      {
        mess = "Unknown Error";
        CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
        messStack->addMessage(mess,2);
        mess = "Line: " + line;
        CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
        messStack->addMessage(mess,2);
      }
    }     
  }
  catch(CExpUnknownTlg& e)
  {
    mess = "Telegramm: " + e.getTlg() + " is unknown("+e.getLine()+")";
    CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
    messStack->addMessage(mess,2);
    if(tlg)
    {
      delete tlg;
      tlg = 0;
    }
  }
  catch(...)
  {
    mess = "Unknown Error: Line("+line+")";
    CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
    messStack->addMessage(mess,2);
    if(tlg)
    {
      delete tlg;
      tlg = 0;
    }
  }

  //Falls Fehler
  if (tlg == 0)
    WrongLineCount++;

  return tlg;
}
//------------------------------------
bool CLogFileReader::loadTlg(CTlg* tlg,const std::string& line)
{
	bool ret = true;
	CMessageStack* messStack = CMessageStack::getMessageStack();
  CLogWriter* logWriter = CLogWriter::getLogWriter();
  
  std::string mess("");
  try
	{
    tlg->load(line);
    tlg->setEmpty(false);
	}
  catch(CExpConvertError& e)
  {
    if(e.getType() == "String")
    {
      mess = "Value: " + e.getValue() + " to long "+e.getType();
      logWriter->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
      messStack->addMessage(mess,2);
    }
    else
    {
		  mess = "Value: " + e.getValue() + " is not "+e.getType();
      logWriter->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
      messStack->addMessage(mess,2);
    }
    mess = "Tel: "+tlg->getTlgName()+"  Elem: "+e.getElem();
    logWriter->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
    messStack->addMessage(mess,2);
    mess = "Line: " + line;
    logWriter->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
    messStack->addMessage(mess,2);
		delete tlg;
		ret = false;
    }
    catch(CExpInvalidTlg& e)
    {
      delete tlg;
	    ret = false;
      mess = "Telegram: " + e.getTlg() + " is "+e.getError();
      logWriter->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
      messStack->addMessage(mess,2);
      mess = "Line: " + line;
      logWriter->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
      messStack->addMessage(mess,2);
    }
	catch(CExpLimitError& e)
	{
		CInterConfig::LimitValueTyp lim = e.getLimitValueTyp();
		if(lim == CInterConfig::Error)
		{
			 //delete tlg;
			 ret = false;
			 mess="This value " + e.getValue() + " is overflow (underflow) (tel: ";
			 mess=mess+tlg->getTlgName()+" elem: "+e.getElem()+ " min: "+e.getMin()+" max: "+e.getMax() +")";
       logWriter->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
			 messStack->addMessage(mess,2);
       mess = "Line: " + line;
       logWriter->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
			 messStack->addMessage(mess,2);
			 delete tlg;
		}
		if(lim == CInterConfig::Warning)
		{
			 mess="This value " + e.getValue() + " is overflow (underflow) (tel: ";
			 mess=mess+tlg->getTlgName()+" elem: "+e.getElem()+ " min: "+e.getMin()+" max: "+e.getMax() +")";
       logWriter->WriteMessage(CLogWriter::Warning,mess,__FILE__,__FUNCTION__,__LINE__);
			 messStack->addMessage(mess,1);
       mess = "Line: " + line;
       logWriter->WriteMessage(CLogWriter::Warning,mess,__FILE__,__FUNCTION__,__LINE__);
			 messStack->addMessage(mess,1);
		}
		if(lim== CInterConfig::SetToMinMax)
		{
			 mess="This value" + e.getValue() + " is overflow (underflow) (tel: ";
			 mess=mess+tlg->getTlgName()+" elem: "+e.getElem()+ " min: "+e.getMin()+" max: "+e.getMax() +")";
			 logWriter->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
       messStack->addMessage(mess,2);

       mess = "Line: " + line;
       logWriter->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
			 messStack->addMessage(mess,2);
		}
	}
	catch(CExpTlgLenError& e)
	{
		 mess = "Length of Telegram: " + e.getTlg() + " is wrong";
     logWriter->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
		 messStack->addMessage(mess,2);
     
     mess = "Length=" + e.getValue();
     logWriter->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
		 mess=mess+" elem: "+e.getElem();
     messStack->addMessage(mess,2);

     mess = "Line: " + line;
		 logWriter->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
     messStack->addMessage(mess,2);
		 
     delete tlg;
		 ret = false;
	}
  catch(...)
	{
		delete tlg;
		ret = false;
		std::string str("Unknown Error");
    logWriter->WriteMessage(CLogWriter::Error,str,__FILE__,__FUNCTION__,__LINE__);
		messStack->addMessage(str,2);
		str = "Line: ";
		str.append(line);
		//line.insert(0,"Line: ");
    //messStack->addMessage(str+line,0);
    logWriter->WriteMessage(CLogWriter::Error,str,__FILE__,__FUNCTION__,__LINE__);
		messStack->addMessage(str,2);
	}
  
  //Falls Error
  if (!ret)
    WrongLineCount++;
  
  //CExpConvertError,CExpWrongOperation
	return ret;
}
//------------------------------------
int CLogFileReader::getTlgCountTotal() const
{
	return this->TlgCount;
}
//-------------------------------------
bool CLogFileReader::checkTlgProtoTypSet(std::string& path)
{
	bool ret = false;
	char buff[2048];
	CTlg* tlg=0;
	std::string line;
	InFile.open(path.c_str(),std::ios::in);
	if(InFile.is_open())
	{
		InFile.getline(buff,2048);
		line.append(buff);
		tlg=createTlg(line);
		CMessageStack::getMessageStack()->clearMessage();
		if(tlg != 0)
		{
			ret = true;
			delete tlg;
		}
		InFile.close();
	}
	return ret;
}
//-------------------------------------
int CLogFileReader::getEmptyLinesCount()const
{
  return EmptyLineCount;
}
//-------------------------------------
int CLogFileReader::getWrongLinesCount()const
{
	return WrongLineCount;
}
//-------------------------------------
int CLogFileReader::getTlgCountInFile()const
{
	return TlgContainer.getTlgCount();
}
//-------------------------------------
CTlg* CLogFileReader::getFlatTlg(int id)
{
	return TlgContainer.getFlatTlg(id);
}
//-------------------------------------
double CLogFileReader::getTlgTime(int id)
{
	return TlgContainer.getKeyTlg(id);
}
//-------------------------------------
std::string CLogFileReader::getTlgTimeAsString(int id)
{
	CTelTime tlgTime;
	std::string interName;
	interName=TlgContainer.getFlatTlg(id)->getInterfaceName();
	CInterConfig* interConf=CInterConfig::getInterConfig(interName);
	tlgTime.setTimeFormat(interConf->getTimeFormat());
	tlgTime.setTime(TlgContainer.getKeyTlg(id));
	return tlgTime.getTimeAsString();
}
//-------------------------------------
void CLogFileReader::addLogFile(CLogFileReader* logReader)
{
	TlgContainer.addContainer(logReader->getTlgContainer());
}
//-------------------------------------
CTlgContainer<double>& CLogFileReader::getTlgContainer()
{
	return TlgContainer;
}
//-------------------------------------
void CLogFileReader::clearContainer()
{
	TlgContainer.freeTlg(true);
  std::string mess = "LogFile telegramm container emptied";
  CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Info,mess,__FILE__,__FUNCTION__,__LINE__);
}
//-------------------------------------
void CLogFileReader::setTlgCountTotal(int total)
{
	this->TlgCount = total;
}
//-------------------------------------
//-------------------------------------
int CLogFileReader:: readLogFileToAnalyze(long& last_pos,const std::string& path,bool const& abort)
{
	CTelTime tlgTime;
	CTlg* tlg=0;
	char buff[16384];
	std::string line;
	int pos;
	double time;
  long lineSize = 0;
	std::string interName;
  CProgressInfoByFileLogRead* InfoByFileLogRead = CProgressInfoByFileLogRead::getProgressInfoByFileLogRead();
	InfoByFileLogRead->setStatusReady(false);
  InfoByFileLogRead->resetData();
  CMessageStack* messStack = CMessageStack::getMessageStack();
  CLogWriter* logWriter = CLogWriter::getLogWriter();

  interName=TlgProtoTyp->getName();
	CInterConfig* interConf=CInterConfig::getInterConfig(interName);
	tlgTime.setTimeFormat(interConf->getTimeFormat());

  // Wenn die Datei nicht geöfnet ist, wird 1 zurueckgegeben.
	InFile.open(path.c_str(),std::ios::in | std::ios::binary);
	if(!InFile.is_open())
  {
    std::string mess = "<" + path + "> can't open.";
    logWriter->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
    return 1;
  }
	TlgCount=0;
	//Springen zur letzten Stelle
	if (last_pos!=0)
		InFile.seekg(last_pos);
	
	//---------------------------
	while(InFile.getline(buff,16384) && !abort)
	{
		;
    TlgCount++;
	  line.clear();
		line.append(buff);
    
    lineSize = long(line.size());
    InfoByFileLogRead->setData(lineSize);

		if (!line.empty())
    {
      if(createTimeTlg(tlgTime,line))
      {
        tlg=createTlg(line);
	      if(tlg != 0)
	      {
			    pos = (int)line.find_last_of(';');
			    if(pos != std::string::npos)
			    {
				    line = line.substr(pos+1,line.size()-pos-1);
  			    if(loadTlg(tlg,line))
			      {
					    time=tlgTime.getTimeAsDouble();
					    TlgContainer.addTlg(time,tlg);
					  } 
            else
            {
              std::string mess = "Loading telegram (" + interName + ") failed";
              CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
            }
			    }
        }
      }
    }
    else
    {
      TlgCount--;
      EmptyLineCount++; 
    }
	  //Aktuelle Position im Log-File
		last_pos=InFile.tellg();
	}

	//Index neu bilden
	TlgContainer.BuildIndex();

  if (EmptyLineCount > 0)
  {
    std::string mess = CFormatConverter::IntToString(EmptyLineCount) + " empty lines in log file";
    messStack->addMessage(mess,1); 
    logWriter->WriteMessage(CLogWriter::Warning,mess + " in " + path,__FILE__,__FUNCTION__,__LINE__);
  }
  InfoByFileLogRead->setStatusReady(true);

  //Falls Vorgang abgebrochen
	if (abort)
	{
		TlgContainer.freeTlg(true);
		std::string mess = "Read of the log file for analyzer aborted!";
    logWriter->WriteMessage(CLogWriter::Info,mess,__FILE__,__FUNCTION__,__LINE__);
		return -1;
	}

	return 0;
}
//---------------------------------------------
void CLogFileReader:: closeInFile()
{
  InFile.close();
}