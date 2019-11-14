#include "StdAfx.h"
#include "BackupString.h"

using namespace BackupUtility;

void BackupString::MarshalString ( System::String* s, std::string& os )
{
	using namespace System::Runtime::InteropServices;
	const char* chars = 
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(System::IntPtr((void*)chars));
}


