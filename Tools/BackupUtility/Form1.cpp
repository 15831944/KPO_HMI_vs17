#include "stdafx.h"
#include "Form1.h"
#include <windows.h>

using namespace BackupUtility;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	System::Threading::Thread::CurrentThread->ApartmentState = System::Threading::ApartmentState::STA;
	Application::Run(new Form1(lpCmdLine));

	return 0;
}
