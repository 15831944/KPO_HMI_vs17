#pragma once
//-------------------------------------------
// Name:  CProgressInfoByFileLogRead.h
// Descr: Die Klasse sammelt 
//          
// Date:
// Autor: Emeljanov Alexander
//--------------------------------------------
#include <windows.h>

class CProgressInfoByFileLogRead 
{
public:
  static CProgressInfoByFileLogRead* getProgressInfoByFileLogRead();
  void setData(long size);
  void resetData();
  long getData();
  void setStatusReady(bool st);
  bool getStatusReady(void);
  ~CProgressInfoByFileLogRead(void);
   CRITICAL_SECTION sec;
protected:
  CProgressInfoByFileLogRead();
private:
  long lineSize;
  //! Zeiger auf Objekt der Klasse
  static CProgressInfoByFileLogRead* ProgressInfoByFileLogRead; 
  bool ready;
};
