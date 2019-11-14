// Copyright 2006 SMS - Demag AG
//-------------------------------------------
// Name:  CCyclicElemStatus.h
// Date:  21.11.08
// Autor: Emeljanov Alexander 
//--------------------------------------------
#ifndef _CCyclicElemStatus_H_
#define  _CCyclicElemStatus_H_

#include "CTlgElemWrapper.h"

using namespace System;

public ref class CCyclicElemStatus
{
    public:

      enum class changeTyp 
		  {
			  none,
			  plus,
			  minus,
			  multiple,
			  divide
		  };

      CCyclicElemStatus();
      CCyclicElemStatus(changeTyp typ, double value,double min, double max);
      CCyclicElemStatus(int typ, double value,double min, double max);
      ~CCyclicElemStatus();

      double getMaxValue();
      double getMinValue();
      double getVariabelValue();
      changeTyp getVariabelTyp();
      System::String^ getVariabelTypAsString();
      
      void setMinValue(double minValue);
      void setMaxValue(double maxValue);
      void setVariabelValue(double changeValue);
      void setVariabelTyp(CCyclicElemStatus::changeTyp typ);
      void setMinimalAndMaximalValuesForMinAndMax(CTlgElemWrapper^ subElem);
      void setMinimumValueForMin(CTlgElemWrapper^ subElem);
      void setMaximumValueForMax(CTlgElemWrapper^ subElem);
  
    private:
      double minValue;
      double maxValue;
      changeTyp change;
      double changeValue; 
};
#endif