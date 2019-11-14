// ----------------------------------------------------------------------
// Copyright (C) 2009 Laurentiu Isopescu
// ----------------------------------------------------------------------
#ifndef CSMC_LogDataHolderH
#define CSMC_LogDataHolderH
// ----------------------------------------------------------------------
#include <StdInc.h>
// ----------------------------------------------------------------------

// The structure that holds the data
struct CSMC_LogDataHolder
{
	// Default constructor
	CSMC_LogDataHolder(void);
	// ------------------------------
	// Class constructor
	CSMC_LogDataHolder(const char* pDataBuff_, unsigned int uiDataLen_);
	// ------------------------------
	// Class destructor
	~CSMC_LogDataHolder(void);
	// ------------------------------
	// operator=
	CSMC_LogDataHolder& operator=(const CSMC_LogDataHolder& cdp);
	// ------------------------------
	// Initialization function
	void initialize(void);
	// ------------------------------
	// Sets the data
	int setData(const char* pDataBuff_, unsigned int uiDataLen_);
	// ------------------------------
	// Returns true if the data is set
	bool isSet(void);
	// ------------------------------
	// Resets the data
	void resetData(void);
	// ------------------------------

	// The data length
	unsigned int m_uiDataLen;
	// The data buffer
	char* m_pDataBuff;
}; // CSMC_LogDataHolder
// ----------------------------------------------------------------------

// A queue of LogDataPair pointers
typedef std::deque<CSMC_LogDataHolder*> CSMC_LogDataHolderDeque;
// ----------------------------------------------------------------------
// Deque iterators
typedef CSMC_LogDataHolderDeque::iterator CSMC_LogDataHolderDequeIter;
typedef CSMC_LogDataHolderDeque::const_iterator CSMC_LogDataHolderDequeConstIter;
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
#endif // CSMC_LogDataHolderH
// ----------------------------------------------------------------------
