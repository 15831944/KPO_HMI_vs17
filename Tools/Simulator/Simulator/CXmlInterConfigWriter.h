// Copyright 2006 SMS - Demag AG

#ifndef _CXmlInterConfigWriter_H
#define _CXmlInterConfigWriter_H


//--------------------------------------------------------------------
#include "CTlgInterfaceWrapper.h"
#include "CTlgWrapper.h"
//--------------------------------------------------------------------
using namespace System;
using namespace System::Xml;
//--------------------------------------------------------------------
//-------------------------------------------
// Name:   CXmlInterConfigWriter.h
// Descr:  Schreibt Schnittstellenkonfiguration in einer
//         Schnittstellenkonfigurationsdatei
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------
public ref class CXmlInterConfigWriter
{
	public:
			CXmlInterConfigWriter();
			~CXmlInterConfigWriter();
			void createInterConfigFile(CTlgInterfaceWrapper^ interWr,String^ path);
      bool loadInterConfigFile(String^ path);
			void beginUpdate();
			void endUpdate();
      bool setSectionFocus(String^ sec);
      void setTelId(String^ telName,String^ id);
      void setTelIdInfo(String^ telId,String^ elemId,String^ typId,String^ lenId,String^ treatLenId);
      void setTransportInfo(String^& Swapping, String^& PaddingDir, String^& PaddingStr);
			void setLogFileSeparator(String^ sep);
			void setLimitTreatmentTyp(String^ lim);
			void setLogFileDate(String^ date);
			void setLogFileTime(String^ time);
			void setTranspSwapping(String^ swapping);
			void setTranspPaddingDir(String^ dir);
			void setTranspPaddingStr(String^ str);
      void addArrayRow(String^ nameElem,String^ nameTel,String^ countElem,array <String^>^ rowName);
      void addUseCase(String^ name,array <String^>^ descr,String^ items);
	private:
			XmlDocument^ XmlDocWriter;
			XmlElement^  Section;
      CTlgInterfaceWrapper^ InterWr;
			String^ FilePath;

      void createSegmentTelId(XmlTextWriter^ wr);
      void createSegmentLogFile(XmlTextWriter^ wr);
			void createSegmentTransport(XmlTextWriter^ wr);
			void createSegmentArrayView(XmlTextWriter^ wr);
			void createSegmentUseCaseView(XmlTextWriter^ wr);
			void createSegmentLimitValue(XmlTextWriter^ wr);
};

#endif
