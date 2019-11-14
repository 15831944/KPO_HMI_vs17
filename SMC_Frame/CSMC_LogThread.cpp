// ----------------------------------------------------------------------
// Copyright (C) 2009 Laurentiu Isopescu
// ----------------------------------------------------------------------
#include "CSMC_EventLogFrameController.h"
#include <CSMC_LogThread.h>
// ----------------------------------------------------------------------

// Default constructor
CSMC_LogThread::CSMC_LogThread(void)
{
	// The thread should be waited for
	this->setFreeOnTerminate(false);
	// Creates the wake event
	createWakeEvent();
	// The default data queue size
	m_uiMaxQueueSize = (unsigned int)DATA_QUEUE_SIZE_DEF;
} // constructor
// ----------------------------------------------------------------------

// Class destructor
CSMC_LogThread::~CSMC_LogThread(void)
{
	// Destroys the wake event
	m_oWakeEvent.destroy();
} // destructor
// ----------------------------------------------------------------------

// The thread work routine
void CSMC_LogThread::work(void)
{
  try
  {
	  // Acquires the critical section
	  m_csCallSync.lock();
	  // Loops the task work main function
	  do {
		  // Gets the first queue message
		  while(getFirstQueueMessage() == 0)
		  {
			  // Releases the critical section
			  m_csCallSync.unlock();
			  // Writes the message
			  writeMessage();
			  // Locks again
			  m_csCallSync.lock();
		  } // while
		  // Unlocks
		  m_csCallSync.unlock();
		  // If the thread terminate flag is set, breaks the loop
		  if(m_terminateThread) { break; }
		  // Since now run-and-block mode, stops in the wake event
		  m_oWakeEvent.wait();
		  // If the loop is to continue, acquires
		  // the critical section for the next step
		  m_csCallSync.lock();
	  } while(!m_terminateThread);
	  // Releases the critical section
	  m_csCallSync.unlock();
  }
  catch(...)
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "Unknown", "CSMC_LogThread::work", "");
  }
} // work
// ----------------------------------------------------------------------

// Takes over the given message and starts the thread
void CSMC_LogThread::setMessage(const char* pMessage_,
                               unsigned int uiDataLen_,
                               bool bStartThread_)
{
  try
  {
	  // If not active, returns
	  if(!m_bActive) { return; }
	  // Checks the given message
	  if(pMessage_ == NULL || uiDataLen_ < 1) { return; }
	  // Acquires the critical section
	  m_csCallSync.lock();
	  // Takes over the given message
	  CSMC_LogDataHolder* pNewDataPair = new CSMC_LogDataHolder(pMessage_, uiDataLen_);
	  m_dqMessages.push_back(pNewDataPair);
	  // Checks the queue size and pops the first element if needed
	  if(m_dqMessages.size() > m_uiMaxQueueSize)
    {
      long del = m_dqMessages.size() < 10 ? m_dqMessages.size() : 10;
      for (long l=0; l<del; l++)
      {
        delete m_dqMessages.front();
        m_dqMessages.pop_front();
      }

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_LogMessageLost(sMessage, m_uiMaxQueueSize);
    }
	  // Releases the critical section
	  m_csCallSync.unlock();
	  // If the given start flag is false, returns
	  if(!bStartThread_) { return; }
	  // The start flag is true: awakes the thread
	  awakeThread();
  }
  catch(...)
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "Unknown", "CSMC_LogThread::setMessage", "");
  }
} // setMessage
// ----------------------------------------------------------------------

// Awakes the thread
void CSMC_LogThread::awakeThread(void)
{
	m_oWakeEvent.raise();
} // awakeThread
// ----------------------------------------------------------------------

// Starts the thread
void CSMC_LogThread::startThread(void)
{
	// If the active flag is not set, returns
	if(!m_bActive) { return; }
	// Starts the thread only if the active flag is set
	this->run();
} // startThread
// ----------------------------------------------------------------------

// Stops the thread
void CSMC_LogThread::stopThread(void)
{
	// If the thread is not running, returns
	if(!this->running()) { return; }
	// Else sets the termination flag
	cCBS_Thread::setTerminateThread();
	// Awakes the thread (if not already awoken)
	awakeThread();
	// Waits until the thread finishes
	cCBS_Thread::waitForExit();
} // stopThread
// ----------------------------------------------------------------------

// Gets the first message from the queue
int CSMC_LogThread::getFirstQueueMessage(void)
{
	// Resets the first message object
	m_oFirstMessage.resetData();
	// Checks the queue; if empty, returns a negative number
	if(m_dqMessages.empty()) { return -1; }
	// If not empty, copies the first queue element
	m_oFirstMessage = *m_dqMessages.front();
	// Destroys and pops the first queue element
	delete m_dqMessages.front(); m_dqMessages.pop_front();
	// ok
	return 0;
} // getFirstQueueMessage
// ----------------------------------------------------------------------

// Writes the message pointed to by the stored pointer
void CSMC_LogThread::writeMessage(void)
{
	// Checks the first element; if not set, returns
	if(!m_oFirstMessage.isSet()) { return; }
	// If valid, writes the first element
	CSMC_LogDataFile::writeMessage(m_oFirstMessage.m_pDataBuff, (long)m_oFirstMessage.m_uiDataLen);
	// Calls the file ring visit routine
  m_oFileRing.visit();
  m_oLogFile.acceptVisit(&m_oFileRing);
} // writeMessage
// ----------------------------------------------------------------------

// Creates the wake event
void CSMC_LogThread::createWakeEvent(void)
{
	// The event resets itself after awakening one thread
	m_oWakeEvent.setManual(false);
	m_oWakeEvent.setInitActive(false);
	// Creates the wake event
	m_oWakeEvent.create();
} // createWakeEvent
// ----------------------------------------------------------------------

// Sets the data queue maximum size
int CSMC_LogThread::setDataQueueMaxSize(unsigned int uiSize_)
{
	// Checks the given data
	if(uiSize_ < DATA_QUEUE_SIZE_MIN) { return -1; }
	// If the same value, returns
	if(m_uiMaxQueueSize == uiSize_) { return 0; }
	// Acquires the critical section
	m_csCallSync.lock();
	// Takes over the new value
	m_uiMaxQueueSize = uiSize_;
	// Releases the critical section
	m_csCallSync.unlock();
	// ok
	return 0;
} // setDataQueueMaxSize
// ----------------------------------------------------------------------

long CSMC_LogThread::getQueueSize()
{
  long RetValue = -1;
	// Acquires the critical section
	m_csCallSync.lock();
	// Read current queue size
  RetValue = m_dqMessages.size();
	// Releases the critical section
	m_csCallSync.unlock();
	// Returns the current queue size
  return RetValue;
}