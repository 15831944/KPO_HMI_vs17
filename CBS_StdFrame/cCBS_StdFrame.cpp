// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include "CBS_StdAPI.h"
#include "cCBS_StdFrame.h"


//##ModelId=40EAA0930105
cCBS_StdFrame::cCBS_StdFrame(int argc, const char* argv[])
: cCBS_StdFrame_Server( argc, argv )
{
}

//##ModelId=40EAA093010B
cCBS_StdFrame::~cCBS_StdFrame()
{
  // ToDo: Add your specialized code here and/or call the base class
}

