// Copyright 2008 SMS - Demag AG
#ifndef _CMessageWrite_H_
#define _CMessageWrite_H_
#include "StdAfx.h"

ref class CMessageWrite
{
  private:
    static int CursorPosY = 11;

  public:
    static void writeMessage(System::String^ mess)
    {
      /*COORD CursorPosition;*/
      HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
      
      System::Console::WriteLine(mess);
      CONSOLE_SCREEN_BUFFER_INFO *CSBI = new CONSOLE_SCREEN_BUFFER_INFO;
      GetConsoleScreenBufferInfo(hConsoleHandle,CSBI);
      CursorPosY = (int)CSBI->dwCursorPosition.Y + 1;
    }

    static void writeProgress(int count)
    {
      COORD CursorPosition;
      HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

      CursorPosition.Y = 5;
      CursorPosition.X = 20;
      SetConsoleCursorPosition(hConsoleHandle,CursorPosition);
      System::Console::Write(count);
      CursorPosition.Y = CursorPosY;
      CursorPosition.X = 0;
      
      SetConsoleCursorPosition(hConsoleHandle,CursorPosition);
    }
};
#endif

/*#include <windows.h> 

#using <mscorlib.dll>

using namespace System;

int main()
{
COORD CursorPosition;
CursorPosition.X=0;
CursorPosition.Y=0;

HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

Console::WriteLine(S"Example for Console control\n\n");
Console::WriteLine(S"This is my counter: %");
Console::WriteLine(S"\n\n=====================");

CursorPosition.Y = 3;
CursorPosition.X = 20;
for (int i = 0; i <= 10; i++)
{
SetConsoleCursorPosition(hConsoleHandle,CursorPosition);
Console::Write(i);
System::Threading::Thread::Sleep(100);
}

CursorPosition.X = 10;
CursorPosition.Y = 10;
SetConsoleCursorPosition(hConsoleHandle,CursorPosition);

CONSOLE_SCREEN_BUFFER_INFO *CSBI = new CONSOLE_SCREEN_BUFFER_INFO;
GetConsoleScreenBufferInfo(hConsoleHandle,CSBI);

String * MsgStr = String::Concat("X Pos = ", CSBI->dwCursorPosition.X.ToString()," Y Pos = ", CSBI->dwCursorPosition.Y.ToString());
Console::WriteLine(MsgStr);

GetConsoleScreenBufferInfo(hConsoleHandle,CSBI);
Console::Write(CSBI->dwCursorPosition.X.ToString());
Console::WriteLine(CSBI->dwCursorPosition.Y.ToString());

return 0;
}    
*/