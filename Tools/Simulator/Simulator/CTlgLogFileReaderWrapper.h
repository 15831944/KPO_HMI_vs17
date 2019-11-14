// Copyright 2006 SMS - Demag AG

#ifndef _CTlgLogFileReaderWrapper_H_
#define _CTlgLogFileReaderWrapper_H_

//--------------------------------------------------------
#include "CItemBaseContainerWrapper.h"
#include "CLogFileReader.h"
#include "CTlgProtoTypSet.h"
//--------------------------------------------------------
//-------------------------------------------
// Name:  CTlgLogFileReaderWrapper.h
// Descr: Wrapper fuer die Klasse CTlgLogFileReader
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------
public ref class CTlgLogFileReaderWrapper : public CItemBaseContainerWrapper
{
  public:
    CTlgLogFileReaderWrapper();
    virtual ~CTlgLogFileReaderWrapper();
    virtual CItemWrapper^ getTlg(int id) override;
    virtual CItemWrapper^ getTlg(String^ tlgName) override;
    virtual void getClonedTlg(CItemWrapper^ tlg,int id) override;
    virtual void getClonedTlg(CItemWrapper^ tlg,String^ tlgName) override;
    virtual String^ getTlgTimeAsString(int id) override;
    virtual int getTlgCount() override;
    virtual int loadFromFile(String^ path,bool const&abort) override;
    virtual void getClonedVirtualTlg(CItemWrapper^ tlg,int id) override;
    virtual void getClonedVirtualTlg(CItemWrapper^ tlg,String^ tlgName) override;
    void setTlgProtoTyp(CTlgProtoTypSet* TlgProto);
    int getCountTlgTotal();
    bool checkInterface(String^ path);	
    virtual double getTlgTime(int id) override;
    virtual double getVirtualTlgTime(int id) override;
    virtual void clearContainer() override;
    virtual String^ getVirtualTlgDescr(int id) override;
    int loadFromFileToAnalyze(long& last_pos,String^ path,bool const& abort);
    void closeLogFile();
  private:
    CLogFileReader* LogFileReader;
    CTlgProtoTypSet* TlgProtoTyp;
};

#endif
