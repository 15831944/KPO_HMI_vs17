
//--------------------------------------------
#include "stdafx.h"
#include "CInterAssignment.h"
#include "CTlgWrapper.h"
//--------------------------------------------
CInterAssignment::CInterAssignment(CTlgInterfaceWrapper^ source,CTlgInterfaceWrapper^ dest)
{
  this->SourceInter = source;
  this->DestInter = dest;
  InterTlgAssignmentList = gcnew System::Collections::Generic::SortedList<String^,CTlgAssignment^>();
  initInterTlgAssignment();
}
//--------------------------------------------
CInterAssignment::~CInterAssignment()
{
  InterTlgAssignmentList->Clear();
}
//--------------------------------------------
void CInterAssignment::initInterTlgAssignment()
{
  CTlgAssignment^ tlgAss = nullptr;
  CTlgWrapper^ wrTlg = gcnew CTlgWrapper();
  int count = SourceInter->getTlgCount();
  InterTlgAssignmentList->Clear();
  for(int i=0;i<count;i++)
  {
    SourceInter->getClonedTlg(wrTlg,i+1);
    tlgAss = gcnew CTlgAssignment(wrTlg);
    InterTlgAssignmentList->Add(wrTlg->getName(),tlgAss);
  }
}
//--------------------------------------------
CTlgInterfaceWrapper^ CInterAssignment::getSourceInter()
{
  return this->SourceInter;
}
//--------------------------------------------
CTlgInterfaceWrapper^ CInterAssignment::getDestInter()
{
  return this->DestInter;
}
//--------------------------------------------
bool CInterAssignment::isMatchAssignment(String^ source,String^ dest)
{
  bool ret=false;
  if(source->Equals(SourceInter->getInterfaceName()))
  {
    if((dest == nullptr) && (DestInter == nullptr))
    {
      ret = true;
    }
    else
    {
      if((dest != nullptr) && (DestInter != nullptr))
      {
        if(dest->Equals(DestInter->getInterfaceName()))
        {
          ret = true;
        }
      }
    }
  }
  return ret;
}
//--------------------------------------------
int CInterAssignment::getSourceTlgCount()
{
	return SourceInter->getTlgCount();
}
//--------------------------------------------
String^ CInterAssignment::getSourceTlgName(int index)
{
	CTlgWrapper^ wr = gcnew CTlgWrapper();
	SourceInter->getClonedTlg(wr,index);
	return wr->getName();
}
//--------------------------------------------
CTlgAssignment^ CInterAssignment::getTlgAssignment(String^ sourceName)
{
	return safe_cast<CTlgAssignment^>(InterTlgAssignmentList[sourceName]);
}
//--------------------------------------------
String^ CInterAssignment::getTlgAssignmentName(String^ sourceName)
{
	return safe_cast<CTlgAssignment^>(InterTlgAssignmentList[sourceName])->getDestTlgName();
}
//--------------------------------------------
void CInterAssignment::setAssignedTlgName(String^ sourceTlg,String^ destTlg)
{
  CTlgAssignment^ tlgAss = safe_cast<CTlgAssignment^>(InterTlgAssignmentList[sourceTlg]);
  tlgAss->setDestTlgName(destTlg);
}
//--------------------------------------------
String^ CInterAssignment::getAssignedTlgName(String^ sourceTlgName)
{
  String^ ret = nullptr;
  CTlgAssignment^ tlgAss = safe_cast<CTlgAssignment^>(InterTlgAssignmentList[sourceTlgName]);
  if(tlgAss)
      ret=tlgAss->getDestTlgName();
  return ret;
}
//--------------------------------------------
void CInterAssignment::setAssignedTlgElem(String^ sourceTlg,String^ sourceElem,String^ sourceSubElem,
                                String^ destElem,String^ destSubElem)
{
  CTlgAssignment^ tlgAss = safe_cast<CTlgAssignment^>(InterTlgAssignmentList[sourceTlg]);
  if(tlgAss)
  {
    int sourceElemIndex, sourceSubElemIndex;
    int destElemIndex,destSubElemIndex;
    CTlgWrapper^ sourceWr = gcnew CTlgWrapper();
    CTlgWrapper^ destWr = gcnew CTlgWrapper();
    SourceInter->getFlatTlg(sourceWr,sourceTlg);
    DestInter->getFlatTlg(destWr,tlgAss->getDestTlgName());
    sourceElemIndex=sourceWr->getElemIndex(sourceElem);
    destElemIndex=destWr->getElemIndex(destElem);
    if(sourceSubElem) //komplexes source Element
    {
      sourceSubElemIndex=sourceWr->getSubElemIndex(sourceElem,sourceSubElem);
    }
    else  //einfaches source Element
    {
      sourceSubElemIndex=0;
    }
    if(destSubElem) //komplexes destination Element
    {
      destSubElemIndex=destWr->getSubElemIndex(destElem,destSubElem);
    }
    else // einfaches destination Element
    {
      destSubElemIndex=0;
    }
    tlgAss->setDestTlgElemName(sourceElemIndex,sourceSubElemIndex,destElemIndex,destSubElemIndex);
  }
}
//--------------------------------------------
array <String^>^ CInterAssignment::getTlgElemAssignment(String^ sourceTlg,String^ destTlg)
{
	array <String^>^ arr = nullptr;
  //ArrayList^ arrList = gcnew ArrayList();
  CTlgAssignment::ElemAssignmentTyp^ elemAss = nullptr;
  int countElem,i;
  CTlgAssignment^ tlgAss = safe_cast<CTlgAssignment^>(InterTlgAssignmentList[sourceTlg]);
    
  countElem = tlgAss->getAssignmentTlgCount();
  arr = gcnew array <String^> (countElem*2);
  for(i=1;i<=countElem;i++)
  {
    elemAss = tlgAss->getElemAssignment(i);
    arr[(i-1)*2] = getAssignmentItemAsString(SourceInter,tlgAss->getSourceTlgName(),elemAss->SourceList);
    arr[(i-1)*2+1] = getAssignmentItemAsString(DestInter,tlgAss->getSourceTlgName(),elemAss->DestList);
  }
	return arr;
}
//--------------------------------------------
String^ CInterAssignment::getAssignmentItemAsString(CTlgInterfaceWrapper^ inter,String^ tlgId,ArrayList^ pathList)
{
  String^ ret = "";
  int elemId,subElemId;
 
  elemId = System::Convert::ToInt32(pathList[0]);
  if(elemId > 0)
  {
    CTlgWrapper^ wr = gcnew CTlgWrapper();
    inter->getFlatTlg(wr,tlgId);
    ret = wr->getElemName(elemId);
    if(pathList->Count > 1)
    {
      subElemId = System::Convert::ToInt32(pathList[1]);
      ret = String::Concat(ret,"\\",wr->getSubElemName(elemId,subElemId));
    }
  }
  return ret;
}
//--------------------------------------------
void CInterAssignment::clearAssignment()
{
	CTlgAssignment^ tlgAss = nullptr;
	int count = InterTlgAssignmentList->Count;

  System::Collections::IEnumerator^ iterator;
  iterator = InterTlgAssignmentList->Keys->GetEnumerator();
  iterator->Reset();

  while(iterator->MoveNext())
	{
    tlgAss = safe_cast <CTlgAssignment^> (iterator->Current);
		tlgAss->clearAssignment();
	}
}
//--------------------------------------------
//String^ CInterAssignment::getAssignedElem(String^ sourceTlg,String^ elem,String^ subElem)
//{
  //  String^ ret = "";
   // CTlgAssignment^ tlgAss = safe_cast<CTlgAssignment^>(InterTlgAssignmentList[sourceTlg));

   // tlgAss->getElemAssignment(
   // return ret;
//}
//--------------------------------------------