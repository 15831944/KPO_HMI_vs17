#ifndef CSMC_MemoryController_H
#define CSMC_MemoryController_H

// ---------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------
// Please note : Class needs linkage of PSAPI.lib 
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
#include <string>



class CSMC_MemoryController
{
public:
  CSMC_MemoryController (const std::string & logText, long logLevel = 2);

  CSMC_MemoryController (const CSMC_MemoryController &);                // copy constructor
  CSMC_MemoryController & operator= (const CSMC_MemoryController &);    // assignment operator
  ~CSMC_MemoryController();                                     // Destructor: Big Three are complete.
  
  long getVirtualMemorySize();

private:
  long        mPageFileUsage; // snapshot virtual memory size
  long        mLogLevel;      // Log Level (1...9)
  std::string mlogText;       // Start of each Log output line
  static long mDepth;        // to detect usage within nested function calls
  long        mCurrentDepth;  // Current value of mDepth at time of class instantiation
  bool        mIsCopied;      // Indicates necessity to decrement counter mDepth in dtor
};

#endif // CSMC_MemoryController_H