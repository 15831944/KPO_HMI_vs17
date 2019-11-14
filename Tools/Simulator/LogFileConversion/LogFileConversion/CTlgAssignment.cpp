#include "stdafx.h"
#include "CTlgAssignment.h"

//------------------------------------------------
CTlgAssignment::CTlgAssignment(CTlgWrapper^ sourceTlg)
{
    this->DestTlgName = nullptr;
    this->SourceTlgName = sourceTlg->getName();
    ElemAssignmentList = gcnew ArrayList();
    initSourceTlgElemAssignment(sourceTlg);
}
//------------------------------------------------
CTlgAssignment::~CTlgAssignment()
{
    ElemAssignmentList->Clear();
}
//------------------------------------------------
void CTlgAssignment::initSourceTlgElemAssignment(CTlgWrapper^ sourceTlg)
{
  value struct ElemAssignmentTyp^ elemAss=nullptr;
  int count = sourceTlg->getTlgElemCount();
  int subCount,j;
  ElemAssignmentList->Clear();
  for(int i=0;i<count;i++)
  {
    subCount=sourceTlg->getSubElemCount(i+1);
    if(subCount == 0)
    {
      elemAss = gcnew ElemAssignmentTyp();
      elemAss->SourceList = gcnew ArrayList();
      elemAss->DestList = gcnew ArrayList();
      elemAss->SourceList->Add((i+1));
      elemAss->DestList->Add((int)0);
      ElemAssignmentList->Add(elemAss);
    }
    for(j=0;j<subCount;j++)
    {
      elemAss = gcnew ElemAssignmentTyp();
      elemAss->SourceList = gcnew ArrayList();
      elemAss->DestList = gcnew ArrayList();
      elemAss->SourceList->Add((i+1));
      elemAss->SourceList->Add((j+1));
      elemAss->DestList->Add((int)0);
      ElemAssignmentList->Add(elemAss);
    }
  }
}
//------------------------------------------------
String^ CTlgAssignment::getSourceTlgName()
{
    return SourceTlgName;
}
//------------------------------------------------
void CTlgAssignment::setDestTlgName(String^ name)
{
  DestTlgName = name;
}
//------------------------------------------------
String^ CTlgAssignment::getDestTlgName()
{
  return DestTlgName;
}
//------------------------------------------------
void CTlgAssignment::setDestTlgElemName(int sourceElem,int sourceSubElem,int destElem,int destSubElem)
{
  //__gc struct ElemAssignmentTyp^ assElem = safe_cast<__gc struct ElemAssignmentTyp^>(ElemAssignmentList[sourceElem-1));
  value struct ElemAssignmentTyp^ assElem = findSourceElement(sourceElem,sourceSubElem);
  if(assElem)
  {
    //assElem->SourceList->Clear();
    assElem->DestList->Clear();
    //assElem->SourceList->Add((sourceElem));
    //if(sourceSubElem > 0)
    //assElem->SourceList->Add((sourceSubElem));
    assElem->DestList->Add((destElem));
    if(destSubElem > 0)
      assElem->DestList->Add((destSubElem));
  }
}
//------------------------------------------------
CTlgAssignment::ElemAssignmentTyp^ CTlgAssignment::findSourceElement(int sourceElem,int sourceSubElem)
{
  CTlgAssignment::ElemAssignmentTyp^ ret=nullptr;
  CTlgAssignment::ElemAssignmentTyp^ elemAss=nullptr;
  int count = ElemAssignmentList->Count;
  int i=0;
  bool flag = false;

  while((!flag) && (i<count))
  {
    elemAss = safe_cast<CTlgAssignment::ElemAssignmentTyp^>(ElemAssignmentList[i]);
	  if(System::Convert::ToInt32(elemAss->SourceList[0]) == sourceElem)
    {
      if(sourceSubElem > 0)
      {
				if(System::Convert::ToInt32(elemAss->SourceList[1]) == sourceSubElem)
        {
          ret = elemAss;
          flag = true;
        }
        else
        {
          i++;
        }
      }
      else
      {
          ret = elemAss;
          flag = true;
      }
    }
    else
    {
        i++;
    }
  }
  return ret;
}
//------------------------------------------------
int CTlgAssignment::getAssignmentTlgCount()
{
  return ElemAssignmentList->Count;
}
//------------------------------------------------
CTlgAssignment::ElemAssignmentTyp^ CTlgAssignment::getElemAssignment(int index)
{
  return safe_cast<ElemAssignmentTyp^>(ElemAssignmentList[index-1]);
}
//------------------------------------------------
void CTlgAssignment::clearAssignment()
{
	value struct ElemAssignmentTyp^ elemAss=nullptr;
	int count = ElemAssignmentList->Count;
	DestTlgName=nullptr;
	for(int i=0;i<count;i++)
	{
		elemAss = safe_cast<ElemAssignmentTyp^>(ElemAssignmentList[i]);
		elemAss->DestList->Clear();
		elemAss->DestList->Add((int)(0));
	}
}
//------------------------------------------------
void CTlgAssignment::getSourceTlgElem(int destElem,int destSubElem,int& sourceElem,int& sourceSubElem)
{
  int count,i;
  bool flag = false;
  value struct ElemAssignmentTyp^ elemAss = nullptr;
  count = ElemAssignmentList->Count;
  i=1;
  while((!flag) && (i<=count))
  {
    elemAss = safe_cast<value struct ElemAssignmentTyp^>(ElemAssignmentList[i-1]);
    if(System::Convert::ToInt32(elemAss->DestList[0]) == destElem)
    {
      if(destSubElem != 0)
      {
        if((elemAss->DestList->Count > 1) && (System::Convert::ToInt32(elemAss->DestList[1]) == destSubElem))
        {
            flag=true;
        }
        else
        {
            i++;
        }
      }
      else
      {
        flag=true;
      }
    }
    else
    {
        i++;
    }
  }

  if(flag)
  {
    sourceElem = System::Convert::ToInt32(elemAss->SourceList[0]);
    if(elemAss->SourceList->Count > 1)
    {
      sourceSubElem = System::Convert::ToInt32(elemAss->SourceList[1]);
    }
    else
    {
      sourceSubElem = 0;
    }
  }
  else
  {
    sourceElem = 0;
    sourceSubElem = 0;
  }
}
//------------------------------------------------