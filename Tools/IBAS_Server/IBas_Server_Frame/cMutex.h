#ifndef CMUTEX_H
#define CMUTEX_H

#include "cCBS_Mutex.h"
#include "cCBS_AccessSync.h"

class cMutex 
{
public:
  cMutex(void);
  virtual ~cMutex(void);

private:
  static 	cCBS_Mutex  m_Mutex;
  cCBS_AccessSync m_accessSync;
};



#endif  // CMUTEX_H