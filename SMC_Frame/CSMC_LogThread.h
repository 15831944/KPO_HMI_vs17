// ----------------------------------------------------------------------
// Copyright (C) 2009 Laurentiu Isopescu
// ----------------------------------------------------------------------
#ifndef CSMC_LogThreadH
#define CSMC_LogThreadH
// ----------------------------------------------------------------------
#include <cCBS_CriticalSection.h>
#include <cCBS_LocalSyncEvent.h>
#include <cCBS_Thread.h>
// ----------------------------------------------------------------------
#include <CSMC_LogDataFile.h>
#include <CSMC_LogDataHolder.h>
#include <CDateTime.h>
// ----------------------------------------------------------------------

class CSMC_LogThread :
	public CSMC_LogDataFile,
	public cCBS_Thread
{
public:
	// The data queue size constants
	enum DataQueueSizes
	{
		DATA_QUEUE_SIZE_MIN = 10, // the minimum value
		DATA_QUEUE_SIZE_DEF = 100
	}; // DataQueueSizes
	// ------------------------------

  // wait time between loging that messages were lost constants
  enum LostMessagesLogInterval
  {
    LOST_LOG_INTERVAL_MIN = 10, // minim of 10 seconds
    LOST_LOG_INTERVAL_DEF = 60
  }; //LostMessagesLogInterval
  // ------------------------------

public:
	// Default constructor
	CSMC_LogThread(void);
	// ------------------------------
	// Class destructor
	~CSMC_LogThread(void);
	// ------------------------------

	// Takes over the given message of the given length
	// If the start flag is true, starts the thread
	void setMessage(const char* pMessage_,
		unsigned int uiDataLen_,
		bool bStartThread_ = true);
	// ------------------------------
	// Sets the message contained in the given class
	template<class TMessage>
	void setTMessage(TMessage& rMessage_, bool bStartThread_ = true)
	{
		// If the active flag is not set, returns
		if(!m_bActive) { return; }
		// Streams in the content
		std::stringstream sstr; // auxiliary variable
		sstr << std::endl; sstr << rMessage_;
		// Calls the other routine
		setMessage(sstr.str().c_str(), (unsigned int)strlen(sstr.str().c_str()), bStartThread_);
	} // setTMessage
	// ------------------------------
	// Awakes the thread
	void awakeThread(void);
	// ------------------------------
	// Starts the thread
	void startThread(void);
	// ------------------------------
	// Stops the thread
	void stopThread(void);
	// ------------------------------

	// Sets the data queue maximum size
	int setDataQueueMaxSize(unsigned int uiSize_);
	// ------------------------------
	// Returns the current data queue max size
	unsigned int getDataQueueMaxSize(void) { return m_uiMaxQueueSize; }
	// ------------------------------

	// Returns the current queue size
  long getQueueSize();
	// ------------------------------

  // Sets the log interval for notifying lost messages
	int setLostMessagesLogInterval(unsigned int uiSize_);
	// ------------------------------
	// Returns the current log interval
	unsigned int getLostMessagesLogInterval(void) { return m_uiLostMessageLogInterval; }
	// ------------------------------

protected:
	// The thread work routine
	virtual void work(void);
	// ------------------------------
	// Creates the wake event
	void createWakeEvent(void);
	// ------------------------------
	// Gets the first message from the queue
	int getFirstQueueMessage(void);
	// ------------------------------
	// Writes the message pointed to by the stored pointer
	void writeMessage(void);
	// ------------------------------

protected:
	// A sync event object, used for thread activation
	cCBS_LocalSyncEvent m_oWakeEvent;
	// The critical section used to synchronize the calls
	cCBS_CriticalSection m_csCallSync;
	// The data pair deque
	CSMC_LogDataHolderDeque m_dqMessages;
	// The first message
	CSMC_LogDataHolder m_oFirstMessage;
	// The maximum data queue size
	unsigned int m_uiMaxQueueSize;
  // The log interval for the lost messages message
  unsigned int m_uiLostMessageLogInterval;
  // The last time we loged a lost message
  CDateTime m_lastLogLostMessage;
}; // CSMC_LogThread
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
#endif // CSMC_LogThreadH
// ----------------------------------------------------------------------
