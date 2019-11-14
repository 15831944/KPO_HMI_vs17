
#ifndef _CTlgAssignment_H_
#define _CTlgAssignment_H_
//-------------------------------------------
//#include "CTlgAssignment.h"
#include "CTlgWrapper.h"
//-------------------------------------------
using namespace System;
using namespace System::Collections;
//-------------------------------------------

public ref class CTlgAssignment
{
  public:
    value struct ElemAssignmentTyp
    {
      ArrayList^ SourceList;
      ArrayList^ DestList;
    };
    CTlgAssignment(CTlgWrapper^ sourceTlg);
    ~CTlgAssignment();
    String^ getSourceTlgName();
    String^ getDestTlgName();
    void setDestTlgName(String^ name);
    void setDestTlgElemName(int sourceElem,int sourceSubElem,int destElem,int destSubElem);
    int getAssignmentTlgCount();
    ElemAssignmentTyp^ getElemAssignment(int index);
	  void clearAssignment();
    void getSourceTlgElem(int destElem,int destSubElem,int& sourceElem,int& sourceSubElem);
  private:
    String^ SourceTlgName;
    String^ DestTlgName;
    ArrayList^ ElemAssignmentList;

    void initSourceTlgElemAssignment(CTlgWrapper^ sourceTlg);
    ElemAssignmentTyp^ findSourceElement(int sourceElem,int sourceSubElem);
};
#endif