
#ifndef _CInterAssignment_H_
#define _CInterAssignment_H_

#include "CTlgInterfaceWrapper.h" 
#include "CTlgAssignment.h"

using namespace System::Collections::Generic;

public ref class CInterAssignment
{
  public:
    CInterAssignment(CTlgInterfaceWrapper^ source,CTlgInterfaceWrapper^ dest);
    ~CInterAssignment();
    bool isMatchAssignment(String^ source,String^ dest);
    CTlgInterfaceWrapper^ getSourceInter();
    CTlgInterfaceWrapper^ getDestInter();
    String^ getAssignedTlgName(String^ sourceTlgName);
		int getSourceTlgCount();
		String^ getSourceTlgName(int index);
    void setAssignedTlgName(String^ sourceTlg,String^ destTlg);
    void setAssignedTlgElem(String^ sourceTlg,String^ sourceElem,String^ sourceSubElem,
    String^ destElem,String^ destSubElem);
		CTlgAssignment^ getTlgAssignment(String^ sourceName);
		String^ getTlgAssignmentName(String^ sourceName);
		array <String^>^ getTlgElemAssignment(String^ sourceTlg,String^ destTlg);
    // String^ getAssignedElem(String^ sourceTlg,String^ elem,String^ subElem);
    void clearAssignment();
  private:
    CTlgInterfaceWrapper^ SourceInter;
    CTlgInterfaceWrapper^ DestInter; 
    System::Collections::Generic::SortedList<String^,CTlgAssignment^>^ InterTlgAssignmentList;
    void initInterTlgAssignment();
    String^ getAssignmentItemAsString(CTlgInterfaceWrapper^ inter,String^ tlgId,ArrayList^ pathList);
};
#endif