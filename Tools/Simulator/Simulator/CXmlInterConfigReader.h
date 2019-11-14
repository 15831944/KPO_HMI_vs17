// Copyright 2006 SMS - Demag AG

#ifndef _CXmlInterConfigReader_H_
#define _CXmlInterConfigReader_H_

//-----------------------------------------------------------
using namespace System;
using namespace System::Xml;
//-----------------------------------------------------------
//-------------------------------------------
// Name:   CXmlInterConfigReader.h
// Descr:  Liest Schnittstellenkonfiguration aus einer
//         Schnittstellenkonfigurationsdatei
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------
public ref class CXmlInterConfigReader
{
	public:
		CXmlInterConfigReader();
		~CXmlInterConfigReader();
    bool setInterConfigFile(String^ path);
    bool setSectionFocus(String^ sec);
    bool getNextTlgId(String^& tel,String^& id);
    String^ getTlgId(String^ tel);
    void getTelIdInfo(String^& telIdName,String^& elemIdName,String^& typId,String^& ElemLenName,String^& LenTreat);
    void getTransportInfo(String^& Swapping, String^& PaddingDir, String^& PaddingStr);
    String^ getLogFileSeparator();
    //String^ getLogFileLimit();
    String^ getLogFileDateFormat();
    String^ getLogFileTimeFormat();
		String^ getTranspSwapping();
		String^ getTranspPaddingDir();
		String^ getTranspPaddingStr();
    array <String^>^ getNextArrayElemInfo(String^& elemName,String^& telName,String^& elemCount);
		bool getNextUseCase(String^& name,String^& descr,String^& items);
    String^ getLimitValueTreatment();
    void getElemIdName (String^& telIdName,String^& elemIdName);
  private:
    XmlDocument^ XmlDoc;
    XmlElement^ Section;
    XmlNode^ Node;
};

#endif
