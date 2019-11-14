// ----------------------------------------------------------------------
// Copyright (C) 2009 Laurentiu Isopescu
// ----------------------------------------------------------------------
#include <CSMC_LogDataHolder.h>
// ----------------------------------------------------------------------

// Default constructor
CSMC_LogDataHolder::CSMC_LogDataHolder(void)
{
	// Data initialization
	initialize();
} // constructor
// ----------------------------------------------------------------------

// Class constructor
CSMC_LogDataHolder::CSMC_LogDataHolder(const char* pDataBuff_,
									 unsigned int uiDataLen_)
{
	// Data initialization
	initialize();
	// Sets the given data
	setData(pDataBuff_, uiDataLen_);
} // constructor
// ----------------------------------------------------------------------

// Class destructor
CSMC_LogDataHolder::~CSMC_LogDataHolder(void)
{
	// Deletes the data
	resetData();
} // destructor
// ----------------------------------------------------------------------

// operator=
CSMC_LogDataHolder& CSMC_LogDataHolder::operator=(const CSMC_LogDataHolder& cdp)
{
	// Checks the data length
	if(cdp.m_uiDataLen < 1) { return *this; }
	// Allocates and copies the data
	setData(cdp.m_pDataBuff, cdp.m_uiDataLen);
	// ok
	return *this;
} // operator=
// ----------------------------------------------------------------------

// Initialization function
void CSMC_LogDataHolder::initialize(void)
{
	m_uiDataLen = 0;
	m_pDataBuff = NULL;
} // initialize
// ----------------------------------------------------------------------

// Sets the data
int CSMC_LogDataHolder::setData(const char* pDataBuff_,
							   unsigned int uiDataLen_)
{
	// Checks the data buffer
	if(pDataBuff_ == NULL) { return -1; }
	// Checks the given data length
	if(uiDataLen_ < 1)     { return -2; }

	// Deallocates the own data
	resetData();
	// Takes over the data length
	m_uiDataLen = uiDataLen_;
	// Creates a buffer with the given length
	try { m_pDataBuff = new char[m_uiDataLen]; } // try
	catch(std::bad_alloc) { return -3; } // catch
	// Copies the given data
	memcpy(m_pDataBuff, pDataBuff_, m_uiDataLen);
	// ok
	return 0;
} // setData
// ----------------------------------------------------------------------

// Returns true if the data is set
bool CSMC_LogDataHolder::isSet(void)
{
	return (m_pDataBuff != NULL && m_uiDataLen > 0);
} // isSet
// ----------------------------------------------------------------------

// Resets the data
void CSMC_LogDataHolder::resetData(void)
{
	// Deallocates the own data
	if(m_pDataBuff != NULL) { delete [] m_pDataBuff; m_pDataBuff = NULL; } // if
	// Makes sure the data length is set to 0
	m_uiDataLen = (unsigned int)0;
} // resetData
// ----------------------------------------------------------------------
