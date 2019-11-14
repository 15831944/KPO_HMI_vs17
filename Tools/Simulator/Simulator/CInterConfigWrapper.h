// Copyright 2006 SMS - Demag AG

#ifndef _CInterConfigWrapper_H_
#define _CInterConfigWrapper_H_
//---------------------------------------------------------------------------------
#include "CStdConverter.h"
#include "CInterConfig.h"
#include "CXmlInterConfigReader.h"
#include "CInterUseCase.h"
#include "CInterListenElemView.h"
//---------------------------------------------------------------------------------
#include <string>
//---------------------------------------------------------------------------------
using namespace System;
//---------------------------------------------------------------------------------
//-------------------------------------------
// Name:  CInterConfigWrapper.h
// Descr: Wrapper fuer die Klasse CInterConfig
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------
public ref class CInterConfigWrapper
{
  public:
    CInterConfigWrapper();
    ~CInterConfigWrapper();
    void readInterConfigurationFile(String^ interName,String^ filePath);
    String^ getTlgIdName(String^ interName);
    String^ getTlgId(String^ interName,String^ telName);
		String^ getTlgName(String^ interName,String^ id);
    String^ getElemId(String^ interName);
    String^ getElemLenId(String^ interName);
		bool isSwapping(String^ interName);
    int getLenIdTreatModus(String^ interName);
    bool isIdElementDefined(String^ interName);
  private:
    void readTelIdConfiguration(CInterConfig* inter,CXmlInterConfigReader^ xmlReader);
		void readTransportConfiguration(CInterConfig* inter,CXmlInterConfigReader^ xmlReader);
		void readLimitTreatConfiguration(CInterConfig* inter,CXmlInterConfigReader^ xmlReader);
		void readLogFileConfiguration(CInterConfig* inter,CXmlInterConfigReader^ xmlReader);
		void readUseCaseConfiguration(CInterUseCase^ interUseCase,CXmlInterConfigReader^ xmlReader);
		void readListenElemConfiguration(CInterListenElemView^ interListenElem,CXmlInterConfigReader^ xmlReader);
};
#endif