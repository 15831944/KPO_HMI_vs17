#pragma once

#include "CExpConvertError.h"

public ref class CFormatConverterWrapper
{
public:
	//throw(CExpConvertError)
  static double StringToDouble(System::String^ val);
	//throw(CExpConvertError)
  static System::String^ DoubleToString(double val);
  static int StringToInt(System::String^ val);
  static long StringToLong(System::String^ val);
  static System::String^ LongToString(long val);
  static System::String^ IntToString(int val);
  CFormatConverterWrapper(void);

  ~CFormatConverterWrapper(void);
private:
  static std::string* mTemp = 0;
};
