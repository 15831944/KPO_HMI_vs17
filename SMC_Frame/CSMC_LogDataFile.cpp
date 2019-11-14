// ----------------------------------------------------------------------
// Copyright (C) 2009 Laurentiu Isopescu
// ----------------------------------------------------------------------
#include <CSMC_LogDataFile.h>
// ----------------------------------------------------------------------
#include <cCBS_Time.h>
//#include <cCBS_NTime.h>
//#include <cCBS_NTimeStruct.h>
// ----------------------------------------------------------------------
#include <iomanip>
// ----------------------------------------------------------------------

// Default constructor
CSMC_LogDataFile::CSMC_LogDataFile(void)
{
  m_bActive = true;

  // The flush limit & counter
	m_uiFlushLimit   = (unsigned int)FLUSH_LIMIT_DEF;
	m_uiFlushCounter = (unsigned int)0;
} // default constructor
// ----------------------------------------------------------------------

// Sets the file root name
int CSMC_LogDataFile::setFileRootName(const char* pRootName_)
{
	// Sets the name
	if(m_oFileRing.setFileRootName(pRootName_) < 0) { return -1; }
	// If not active, returns (does not open the log file)
	if(!m_bActive) { return 1; }
	// If active, opens the first ring file
  m_oFileRing.setFile(&m_oLogFile);
	//if(m_oFileRing.openRingFile() < 0) { return -2; }
	// ok
	return 0;
} // setFileRootName
// ----------------------------------------------------------------------

// Sets the file directory
int CSMC_LogDataFile::setFileDir(const char* pFileDir_)
{
	return m_oFileRing.setFileDir(pFileDir_);
} // setFileDir
// ----------------------------------------------------------------------

// Sets the file extension
int CSMC_LogDataFile::setFileExt(const char* pFileExt_)
{
	return m_oFileRing.setFileExt(pFileExt_);
} // setFileExt
// ----------------------------------------------------------------------

// Sets the time separator
void CSMC_LogDataFile::setTimeSeparator(const char* value_)
{
	m_oFileRing.setTimeSeparator(value_);
} // setTimeSeparator
// ----------------------------------------------------------------------

// Sets the number of the ring files
void CSMC_LogDataFile::setRingFilesNum(int value_)
{
	m_oFileRing.setRingFilesNum(value_);
} // setRingFilesNum
// ----------------------------------------------------------------------

// Sets the number of datasets to be kept in one file
void CSMC_LogDataFile::setDataSetsNum(int value_)
{
	m_oFileRing.setDataSetsNum(value_);
} // setDataSetsNum
// ----------------------------------------------------------------------

// Sets the number of days the log file should be kept
void CSMC_LogDataFile::setDaysNum(int value_)
{
	m_oFileRing.setDaysNum(value_);
} // setDaysNum
// ----------------------------------------------------------------------

// Sets the number of days the log file should be kept
void CSMC_LogDataFile::setNameDigits(int value_)
{
	m_oFileRing.setNameDigits(value_);
} // setNameDigits
// ----------------------------------------------------------------------

// Sets the flush limit
int CSMC_LogDataFile::setFlushLimit(unsigned int uiFlushLimit_)
{
	// Checks the given value
	if(uiFlushLimit_ < FLUSH_LIMIT_MIN) { return -1; }
	// Takes it over
	m_uiFlushLimit = uiFlushLimit_;
	// ok
	return 0;
} // setFlushLimit
// ----------------------------------------------------------------------

// Opens the next ring file
// Remark: this function should be called after
//         all settings have been performed
void CSMC_LogDataFile::openRingFile(void)
{

	m_oFileRing.openRingFile();
} // openRingFile
// ----------------------------------------------------------------------

// Closes the file
void CSMC_LogDataFile::closeFile(void)
{
	m_oLogFile.flush();
	m_oLogFile.closeFile();
} // closeFile
// ----------------------------------------------------------------------

// Writes the current time
int CSMC_LogDataFile::getCurrentTime(std::string& _outstring)
{
	// Auxiliary variables
  CBS_LocalTime crtTime;
	std::stringstream sstr;
	// Obtains the current time
  cCBS_Time::localTime(crtTime);
	// Writes the date into the given string
	_outstring.clear();

  sstr << std::setw(4) << crtTime.year  << "-";
	sstr << std::setw(2) << crtTime.month << "-";
	sstr << std::setw(2) << crtTime.day  << "  ";
	sstr << std::setw(2) << crtTime.hour << ":";
	sstr << std::setw(2) << crtTime.minute  << ":";
	sstr << std::setw(2) << crtTime.second  << ".";
	sstr << std::setw(3) << crtTime.msec;
	_outstring = sstr.str();
	_outstring += " |   ";
	// ok
	return 0;
} // getCurrentTime
// ----------------------------------------------------------------------

// Takes over the given message of the given length
// If the start flag is true, starts the thread
int CSMC_LogDataFile::writeMessage(const char* pMessage_, long uiDataLen_)
{
	// Auxiliary variable
	std::string strTimestamp;

	// If the active flag is not set, returns warning
	if(!m_bActive) { return 1; }
	// If the given data is invalid, returns error
	if(pMessage_ == NULL || uiDataLen_ < 1) { return -1; }

	// If cannot open the source file, returns
	// Remark: the open options must be properly set
	if(m_oLogFile.openWrite() < 0) { return -2; }

  // Writes the given data in an output stream
  // do not use "endchar1/2" here because its additional IO operation
  m_oLogFile.writeData(pMessage_);

  //m_oLogFile.writeData(pMessage_, uiDataLen_);

  // Checks the flush limit & counter
	if(++m_uiFlushCounter > m_uiFlushLimit)
	{
		// Flushes the file content
		m_oLogFile.flush();

		// Resets the counter
		m_uiFlushCounter = (unsigned int)0;
	} // if
	// ok
	return 0;
} // writeMessage
// ----------------------------------------------------------------------
