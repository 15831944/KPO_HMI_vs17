// ---------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------
// Please note : Class needs linkage of WINDOWS PSAPI.lib 
// ---------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------
// A little helper class. When instantiated, it memorizes the current virtual memory size,
// and logs the difference upon destruction. 
// note that it has no interlock mechanism, which means that in multithreaded environments
// a memory increase or decrease might happen during the lifetime of this object but not
// in the code between ctor and dtor...
// ---------------------------------------------------------------------------------------

// Includes STL
#include <iostream>
#include <sstream>

#if defined(WIN32) || defined(_WIN32) 
  // Includes Windows API 
  #include "windows.h"
  #include "psapi.h"
#endif



#include "cCBS_StdInitBase.h"
#include "cCBS_StdLog_Task.h"
#include "CSMC_MemoryController.h"

// static data member
// ------------------
long CSMC_MemoryController::mDepth = 0;


// the obvious ctor
CSMC_MemoryController::CSMC_MemoryController (const std::string & logText, long logLevel /*  = 7*/ )
: mLogLevel(logLevel),
  mlogText (logText),
  mIsCopied(false)
{
  mCurrentDepth  = ++mDepth;                    // memorize Usage level at time of construction
  mPageFileUsage = getVirtualMemorySize();      // Store initial value now, to be compared
                                                // with current value in destructor.
}

CSMC_MemoryController::CSMC_MemoryController(const CSMC_MemoryController &src)
{
  // This class is simple enough to apply the assignment operator for copy construction
  // (Straightforward copying of bits, nothing special)
  *this = src;
  mIsCopied      = true;                        // This one is not copied. It tells the dtor not to decrement!

}

CSMC_MemoryController::~CSMC_MemoryController()
{
  long memNow = getVirtualMemorySize();           // Now current memory usage
  long delta = memNow - mPageFileUsage;           // Calculate Delta
  if   (delta)                    // Logging only if its worth logging, i.e. if memory usage has changed.
  {
    std::stringstream logLine;
    logLine << "(" <<mCurrentDepth << ") " << mlogText << " - Memory " << memNow/1024 
            << " K, Delta = " << delta/1024 << " K." ;

    cCBS_StdLog_Task::getInstance()->log(logLine.str(),mLogLevel);

  } // endif (delta)
    // no ELSE required because there is nothing to do when Mem has not changed.

  if   (! mIsCopied )   --mDepth;                                       // Finally, decrement Usage Nesting level
}


CSMC_MemoryController & CSMC_MemoryController::operator= (const CSMC_MemoryController & rhs) 
{
  if   (this == &rhs)    return *this;          // handle self-assignment a=a;

  // copy the bits
  mPageFileUsage = rhs.mPageFileUsage;          // snapshot virtual memory size
  mLogLevel      = rhs.mLogLevel;               // Log Level (1...9)
  mlogText       = rhs.mlogText;                // Start of each Log output line

  mCurrentDepth  = rhs.mCurrentDepth;           // Current value of mDepth at time of class instantiation
  
  // do not modified my previous mIsCopied      

  return         *this;
}

long CSMC_MemoryController::getVirtualMemorySize()
{
#if defined(WIN32) || defined(_WIN32) 

  PROCESS_MEMORY_COUNTERS pe;     // The entire Result set of GetProcessMemoryInfo.
  static HANDLE hOwnProcess=0;    // Static to avoid a growing Number of handles and reduce
                                  // the overhead of creatiung/destructing this handle.

  if   (!hOwnProcess)             // Initialize once
  {
    hOwnProcess = OpenProcess     (  PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                                     FALSE, 
                                     GetCurrentProcessId()) ;
  } // ENDIF - no else required. We have the value we need.
  
  GetProcessMemoryInfo            (  hOwnProcess, 
                                     &pe, 
                                     sizeof(pe));
  return  pe.PagefileUsage;
#else
  return  -1;
#endif
}


