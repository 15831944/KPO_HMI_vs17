// ----------------------------------------------------------------------
// Copyright (C) 2009 Laurentiu Isopescu
// ----------------------------------------------------------------------
#ifndef CSMC_LogDataFileH
#define CSMC_LogDataFileH
// ----------------------------------------------------------------------
#include <cCBS_FdFile.h>
#include <cCBS_FpFile.h>
#include <CSMC_FpFile.h>
#include <cCBS_FileRing.h>
// ----------------------------------------------------------------------

// Parent class for all subsequent Oracle-using classes
class CSMC_LogDataFile
{
public:
	// The flush constants
	enum FlushData
	{
		FLUSH_LIMIT_MIN = 0,  // the minimum flush limit
		FLUSH_LIMIT_DEF = 0   // the default flush limit
	}; // FlushLimit
	// ------------------------------

public:
	// Default constructor
	CSMC_LogDataFile(void);
	// ------------------------------

	// Sets the file root name
	virtual int setFileRootName(const char* pRootName_);
	// ------------------------------
	// Sets the file directory
	virtual int setFileDir(const char* pFileDir_);
	// ------------------------------
	// Sets the file extension
	virtual int setFileExt(const char* pFileExt_);
	// ------------------------------
	// Sets the time separator
	virtual void setTimeSeparator(const char* value_);
	// ------------------------------
	// Sets the number of the ring files
	virtual void setRingFilesNum(int value_);
	// ------------------------------
	// Sets the number of datasets to be kept in one file
	virtual void setDataSetsNum(int value_);
	// ------------------------------
	// Sets the number of days the log file should be kept
	virtual void setDaysNum(int value_);
	// ------------------------------
	// Sets the name digits
  void setNameDigits(int value_);
	// ------------------------------

  // Sets the flush limit
	virtual int setFlushLimit(unsigned int uiFlushLimit_);
	// ------------------------------
	// Returns the current flush limit value
	virtual unsigned int getFlushLimit(void) { return m_uiFlushLimit; }
	// ------------------------------

	// Sets the active flag
	virtual void setActive(bool bActive_) { m_bActive = bActive_; }
	// ------------------------------
	// Returns the current value of the active flag
	virtual bool getActive(void) { return m_bActive; }
	// ------------------------------

	// Opens the next ring file
	// Remark: this function should be called after
	//         all settings have been performed
	void openRingFile(void);
	// ------------------------------

	// Writes the current time
	int getCurrentTime(std::string& _outstring);
	// ------------------------------
	// Takes over the given message of the given length
	// If the start flag is true, starts the thread
	int writeMessage(const char* pMessage_,
		long uiDataLen_);
	// ------------------------------
	// Writes the message contained in the given template object
	template<class TMessage>
	int writeTMessage(TMessage& rMessage_, bool bCloseFile_ = true)
	{
		// If the active flag is not set, returns warning
		if(!m_bActive) { return 1; }
		// Streams in the content
		std::stringstream sstr; // auxiliary variable
		sstr << std::endl; sstr << rMessage_;
		// Calls the other routine
		return writeMessage(sstr.str().c_str(), (long)strlen(sstr.str().c_str()), bCloseFile_);
	} // setTMessage
	// ------------------------------

	// Flushes and closes the file
	void closeFile(void);
	// ------------------------------

protected:
	// The file
	//cCBS_FpFile m_oLogFile;
  CSMC_FpFile m_oLogFile;
	// The file ring
	cCBS_FileRing m_oFileRing;
	// The flush limit
	unsigned int m_uiFlushLimit;
	// The flush counter - when the counter
	// reaches the flush limit, the flush is executed
	unsigned int m_uiFlushCounter;
	// The active flag
	bool m_bActive;
}; // CSMC_LogDataFile
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
#endif // CSMC_LogDataFileH
// ----------------------------------------------------------------------
