
#include "stdafx.h"
#include "CTlgLogFileContainer.h"
#include "CTlgItemContainer.h"
//---------------------------------------
CTlgLogFileContainer::CTlgLogFileContainer()
{
    TlgLogFileContainer = gcnew ArrayList();
}
//---------------------------------------
CTlgLogFileContainer::~CTlgLogFileContainer()
{
    TlgLogFileContainer->Clear();
}
//---------------------------------------
void CTlgLogFileContainer::readLogFile(String^ path,CInterAssignment^ interAss)
{
    String^ logFileLine = nullptr;
    String^ tlgName = nullptr;
    String^ tlgBody = nullptr;
    String^ assTlgName = nullptr;
    CTlgItemContainer^ tlgItemCon = nullptr;
    CTlgWrapper^ wrDest = gcnew CTlgWrapper();
    CTlgWrapper^ wrSource = gcnew CTlgWrapper();
    Path = path;
    TlgLogFileContainer->Clear();
    System::IO::StreamReader^ sr = gcnew System::IO::StreamReader(Path);
    while((logFileLine = sr->ReadLine()) != nullptr)
    {
        tlgName = getTlgName(logFileLine);
        if(tlgName)
        {
            tlgBody = getTlgBody(logFileLine);
            if(tlgBody)
            {
                assTlgName = interAss->getAssignedTlgName(tlgName);
                if((assTlgName) && (!assTlgName->Equals("")))
                {
                    interAss->getDestInter()->getFlatTlg(wrDest,assTlgName);
                    interAss->getSourceInter()->getFlatTlg(wrSource,tlgName);
                    tlgItemCon = gcnew CTlgItemContainer(tlgBody,interAss->getTlgAssignment(tlgName),wrSource,wrDest);
                    TlgLogFileContainer->Add(tlgItemCon);
                }
            }
        }
    }
    sr->Close();
}
//---------------------------------------
void CTlgLogFileContainer::writeLogFile(String^ path)
{
    int count,i;
    CTlgItemContainer^ itemCon = nullptr;
    System::IO::StreamWriter^ wr = gcnew System::IO::StreamWriter(path);
    count = TlgLogFileContainer->Count;
    for(i=0;i<count;i++)
    {
        itemCon = safe_cast<CTlgItemContainer^>(TlgLogFileContainer[i]);
        wr->WriteLine(itemCon->getTlgLine());
    }
    wr->Close();
}
//---------------------------------------
String^ CTlgLogFileContainer::getTlgName(String^ line)
{
    String^ ret = nullptr;
    int pos_st,pos_end;
    int pos = line->IndexOf("TYPE");
    if(pos != -1)
    {
        pos_st = line->IndexOf(";",pos+1);
        if(pos_st != -1)
        {
            pos_end = line->IndexOf(";",pos_st+1);
            if(pos_end != -1)
            {
                ret = line->Substring(pos_st+1,pos_end-pos_st-1);
            }
        }
    }
    return ret;
}
//---------------------------------------
String^ CTlgLogFileContainer::getTlgBody(String^ line)
{
    String^ ret = nullptr;
    int pos = line->IndexOf("BODY");
    if(pos != -1)
    {
        pos = line->IndexOf(";",pos+1);
        if(pos != -1)
        {
            ret = line->Substring(pos+1,line->Length - pos - 1);
        }
    }
    return ret;
}
//---------------------------------------
int CTlgLogFileContainer::getTlgCount()
{
    return TlgLogFileContainer->Count;
}
//---------------------------------------
String^ CTlgLogFileContainer::getTlgAsString(int index)
{
    String^ ret=nullptr;
    CTlgItemContainer^ itemCon = safe_cast<CTlgItemContainer^>(TlgLogFileContainer[index-1]);
    ret = itemCon->getTlgLine();
    return ret;
}
//---------------------------------------
String^ CTlgLogFileContainer::getDestTlgName(int index)
{
    String^ ret=nullptr;
    CTlgItemContainer^ itemCon = safe_cast<CTlgItemContainer^>(TlgLogFileContainer[index-1]);
    ret = itemCon->getDestTlgName();
    return ret;
}
//---------------------------------------