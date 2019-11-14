// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELCOM_FILETRANSPORT_4370B1A202C3_INCLUDED
#define _INC_CTELCOM_FILETRANSPORT_4370B1A202C3_INCLUDED

#include <fstream>
#include <iostream>
#include <map>
#include "telcom.h"
#include "transport.h"

//////////////////////////////////////////////////
//
// This class is used if communication to laboratory 
// is done via files.
// 
// Configuration for this is in ini
//
// [SMS_FileReaderTransport]
// AnalysisFilePath=D:\SMS_Demag\AnalysisDir
// RetryInterval=5
// deleteProcessedFiles=0
// renameProcessedFiles=1
// HotMetalBF=Hot_Metal_BF.txt
// HotMetalBeforeDS=Hot_Metal_DS_before.txt
// HotMetalAfterDS=Hot_Metal_DS_after.txt
// SteelAnlBOF=Steel_Analysis_BOF.txt
// SteelAnlLF=Steel_Analysis_LF.txt
// SlagAnlBOF=Slag_Analysis_BOF.txt
// SlagAnlLF=Slag_Analysis_LF.txt
//////////////////////////////////////////////////
//##ModelId=4370B1A202C3
class CTelcom_FileTransport : public AbstractTransport
{
public:
	//##ModelId=4374B4F202FB
	CTelcom_FileTransport();
  void setHeaderTlgType(std::string headName);
	//##ModelId=437307EC00F6
	void setFactory(TlgFactory* Factory);
	//##ModelId=4370C62002A3
	virtual ~CTelcom_FileTransport();
	//##ModelId=4373077803B5
  virtual void configure(const std::string & section, bas::Configuration & c) ;
	//##ModelId=437307790012
  virtual int  receive(TCMessage & msg);
	//##ModelId=437307790044
  virtual void send(const TCMessage & msg);

protected:
	//Read steel and hot metal analysis file.
	//##ModelId=4381894F0056
	int receiveSteelAnl();

	//##ModelId=43818A0A0192
	int receiveSlagAnl();

	//##ModelId=437307790076
  virtual int doConnect();
	//##ModelId=43730779008A
  virtual int doDisconnect();
	//##ModelId=4373077900A8
  virtual int doListen();

private:
	std::string m_LocalMsgFormat;

	std::string m_RemoteMsgFormat;

	//To create tlgs
	TlgFactory* m_pFactory;

	//Connection retry interval.
	//##ModelId=438473AB02B3
	int retryInterval;

	//##ModelId=4382EEF5010C
	std::string anlFilePath;

	//Current opened anl file.
	//##ModelId=4382EE3400EF
	std::string currentFile;

	//##ModelId=43819BEC0225
	TCMessage* tofillMsg;

	//Type of analysis and process stage.
	//0 = nothing,
	//1 = HMBF,
	//2 = HMDSBefore,
	//3 = HMDSAfter,
	//4 = SteelBOF,
	//5 = SteelLF,
	//6 = SlagBOF,
	//7 = SlagLF.
	//##ModelId=438194960200
  enum eAnlKind{

		//##ModelId=438196FF0328
		nothing,

		//##ModelId=438196FF0332
		HMBF,

		//##ModelId=438196FF033C
		HMDSBefore,

		//##ModelId=438196FF0350
		HMDSAfter,

		//##ModelId=438196FF035A
		SteelBOF,

		//##ModelId=438196FF035B
		SteelLF,
  
		//##ModelId=438196FF0364
		SlagBOF,

		//##ModelId=4381971002D3
		SlagLF
	};
		//Type of analysis and process stage.
	//##ModelId=43818E66005E
	int anlKind;

	//Name of the header telegram.
	//##ModelId=4374B63B00D2
	std::string headTlgName;

	//File name for HM analysis from Blast Furnace
	//##ModelId=4374ADA901D1
	std::string HotMetalBF;

	//File name for HM analysis before DS
	//##ModelId=4374AE490038
	std::string HotMetalBeforeDS;

	//File name for HM analysis after DS
	//##ModelId=4374AEC602C5
	std::string HotMetalAfterDS;

	//File name of BOF steel analysis.
	//##ModelId=4374AF1B026D
	std::string SteelAnlBOF;

	//File name of LF steel analysis.
	//##ModelId=4374AF32030C
	std::string SteelAnlLF;

	//File name of BOF slag analysis.
	//##ModelId=4374AF52016E
	std::string SlagAnlBOF;

	//File name of LF slag analysis.
	//##ModelId=4374AF66015B
	std::string SlagAnlLF;

  // If true, files will be deleted
	//##ModelId=437307790102
  bool deleteProcessedFiles;

  // If true, files will be renamed
	//##ModelId=43730779012A
  bool renameProcessedFiles;

	//##ModelId=437307790152
  bool finishedFileProcessing;
	//##ModelId=437307790184
  std::ifstream    *openFile;

	// Translate Element Names from ANAL File to Column names in 
  //Tlg.

	//##ModelId=4373077901DD
  typedef std::map<std::string,std::string>  strstrmaptype;

	//Container for translation of steel or hot metal 
	//elements from file into the General Standarts 
	//definition.
	//##ModelId=43738AF20107
  strstrmaptype     elemTransSteelHM;
	
  //Container for translation of slag analysis elements 
	//from file into the General Standarts definition.
	//##ModelId=43738A510193
  strstrmaptype     elemTransSlag;

public:
	//##ModelId=438199B5006A
	int receiveHotMetalAnl();

};

//A little helper class to parse analysis line from lab file.
//##ModelId=43730C5C0104
class cTokenizer
{
public:
	//##ModelId=43730C84039F
  cTokenizer(char * strng)
  {
    p0 = new char [strlen(strng)+1];
    strcpy (p0, strng);
    p=st=p0;
  }
	//##ModelId=43730C8403C7
  ~cTokenizer()
  {
    delete[] p0;
  }

	//##ModelId=43730C8403D1
  std::string nextToken()
  {
    std::string retstr;
    if (!*p)
    {
      retstr = ",";
    }
    else
    {
      if (*st==',')
      {
        // two commas encountered: aaa,bbb,, 
        retstr="";                            // return empty string
        ++p; ++st;                            // increment pointer pair
      }
      else 
      {
        // find end of current token: either \0 or ','
        while (*p && *p!=',')
          ++p;

        // distinguish END/NOT END
        if (*p)
        {
          // normal case: 
          *p=0;
          retstr = std::string(st);
          *p=',';
          st=p+1;
          p=st;
        }
        else
        {
          // p encountered end of string.
          retstr=std::string(st);
        }
      }
    }
    return retstr;
  }

private:
	//##ModelId=43730C8403DB
  char * p;
	//##ModelId=43730C850011
  char * p0;
	//##ModelId=43730C85002F
  char * st;

};

#endif /* _INC_CTELCOM_FILETRANSPORT_4370B1A202C3_INCLUDED */
