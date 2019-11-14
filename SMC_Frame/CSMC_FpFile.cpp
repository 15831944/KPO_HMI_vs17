// Copyright (C) 2004 SMS Demag AG


#include "CSMC_FpFile.h"

#pragma warning( disable : 4996 ) // disable VS2005 warnings for _CRT_SECURE_NO_WARNINGS

//##ModelId=42A5A77503BB
CSMC_FpFile::~CSMC_FpFile()
{
	// ToDo: Add your specialized code here and/or call the base class
}

//##ModelId=42A5A77601DD
CSMC_FpFile::CSMC_FpFile(bool Redirect)
: m_Redirect(Redirect)
{
	
}

//##ModelId=42A5A7730227
int CSMC_FpFile::openModeFile(const char* omode_, const char* fileName_)
{
    // Checks the given file name
	if(fileName_ == 0 || strlen(fileName_) < 1) return -1;
	// If file already opened, returns
	if(isFileOpen()) return 1;

  if (m_Redirect)
  {
    // flush actual cerr
    std::cerr.flush();

  	// Tries to open the file
	  p_file = freopen(fileName_, omode_, stderr);

    // clear actual cerr
    std::cerr.clear();
  }
  else
  {
	  p_file = fopen(fileName_, omode_);
  }

	// Checks the function result
	if(p_file == 0) return -2;

	// Clears the state flags
	clear();
	// ok
	return 0;
}



//##ModelId=42A5A9D80015
int CSMC_FpFile::closeFile(void)
{
	// Auxiliary variable
	int res;

	// If the file is not opened, returns
	if(!isFileOpen()) return 1;
	// Clears the state flags
	clear();

  if (m_Redirect)
  {
    // flush actual cerr
    std::cerr.flush();

    // flush open writes
    fflush(p_file);

	  // Closes the file
	  res = fclose(p_file);

    // clear actual cerr
    std::cerr.clear();

  }
  else
  {
    // flush open writes
    fflush(p_file);

	  // Closes the file
	  res = fclose(p_file);
  }

	// The file cannot be used anymore anyhow
	p_file = 0;

	// ok
	return ((res == 0) ? 0 : -1);
}

