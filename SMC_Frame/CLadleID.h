// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLadleID_43FDD101016D_INCLUDED
#define _INC_CLadleID_43FDD101016D_INCLUDED

class CLadleID 
{
public:
	virtual ~CLadleID();

	CLadleID();

  std::string generateLadleID(const std::string &LadleType, long LadleNo, bool ForceEventLog = false);

  std::string getLadleType(const std::string &LadleID);

  long getLadleNo(const std::string &LadleID);

  bool isValid(const std::string &LadleID);

  bool checkLadleIDWithDefaultType(const std::string &DefaultLadleType, std::string &LadleID);

};

#endif /* _INC_CLadleID_43FDD101016D_INCLUDED */
