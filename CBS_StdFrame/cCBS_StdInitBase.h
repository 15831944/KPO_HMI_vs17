// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CINITBASE_40C0768103A2_INCLUDED
#define _INC_CINITBASE_40C0768103A2_INCLUDED

#include <string>

//##ModelId=40EAA093029C
#include "cCBS_ConfigBase.h"

//Class representing CBS ConfigBase functionalities. Class 
//has Singleton implementation.
//##ModelId=40EAA093029C
class cCBS_StdInitBase 
{
public:
	//number og arguments
	//##ModelId=45ACF218010A
	int numCmdLineArgs();

	//fill Arguments with commandline arguments
	//##ModelId=45ACF218011E
	bool getCmdLineArgs(std::vector<std::string>& Arguments);

	//##ModelId=434CD3370002
	bool replaceWithEntry(const std::string& Group, const std::string& Element, std::vector<std::string>& value);

	// Provides a list of configuration elements of type 
	//string from INI file by calling  the ConfigBase element 
	//function getActGrpEle. All entries from INI file will 
	//be stored in a respective container.
	//If , e.g. InifileEntry = A,B,C,D,E, the Contgeines 
	//contains 5 elements.
	//##ModelId=412F1C8203C2
  bool getEntryList(const std::string& Group, const std::string& Element, std::vector<std:: string> & List);

  // provides by references the entry at position n of entryList, starts with position 1
  // InifileEntry = A,B,C,D,E for position 3 references to "C"
  bool getAtEntryList(const std::string& Group, const std::string& Element, long Position, std::string& Value);

  bool isValueOfList(const std::string& Group, const std::string& ListName, const std::string& Value);
  bool getValueOfListEntry(const std::string& Group, const std::string& ListName, const std::string& Entry, std::string& Value);
  bool getValueOfListEntry(const std::string& Group, const std::string& ListName, const std::string& Entry, long& Value);

	//Return name of INI file (without path name)
	//##ModelId=4124ECF600F8
	 std::string& getConfigName();


	//##ModelId=411B3E8403B3
	const std::string& getXPACT_SMC() const;

	//##ModelId=411B3E850308
	const std::string& getXPACT_SMC_LOG() const;

	const std::string& getXPACT_SMC_RT() const;

	// Provides a configuration element of type string from 
	//INI file by calling  the ConfigBase element function 
	//getActGrpEle.
	//##ModelId=410E60700070
	bool getEntry(const std::string & Group, const std::string & Element, bool  & value);

	//Replaces given value with an INI file entry, if existst.
	//##ModelId=410E6079018C
	bool replaceWithEntry(const std::string & Group, const std::string & Element, bool  & value);

	// Provides a configuration element of type int from INI 
	//file by calling
	// the ConfigBase element function getActGrpEle.
  //##ModelId=40EAA093029E
  bool getEntry(const std::string & Group, const std::string & Element, long  & value  );
  bool getEntry(const std::string & Group, const std::string & Element, long long & value  );


	// Provides a configuration element of type double from 
	//INI file by calling the ConfigBase element function 
	//getActGrpEle.
	//##ModelId=410E54EA0332
	bool getEntry(const std::string & Group, const std::string & Element, double  & value  );

	//Replaces given value with an INI file entry, if existst.
	//##ModelId=410E55070355
	bool replaceWithEntry(const std::string & Group, const std::string & Element, double  & value);

	//Replaces given value with an INI file entry, if existst.
	//##ModelId=410E53A2018C
	bool replaceWithEntry(const std::string & Group, const std::string & Element, long  & value);
	bool replaceWithEntry(const std::string & Group, const std::string & Element, long long & value);

	//Replaces given value with an INI file entry, if existst.
	//##ModelId=40F53EA1017E
	bool replaceWithEntry(const std::string & Group, const std::string & Element, std::string  & value);

  //##ModelId=40EAA09302CF
  int m_ArgcForEventSender;

  //##ModelId=40EAA09302C9
  void setArgForEventChannel();

  // Project name. must be the same for all applications
  // using OmniORB to communicate with each others .
  //##ModelId=40EAA09302E3
   std::string  m_ProjectName;

  // Component name. must be unique for each application. 
  //This name is 
  // used to identify the CORBA server application.
  //##ModelId=40EAA09302D5
   std::string  m_ComponentName;

  // The Task name is composed from Component name plus 
  //"Task"
  //##ModelId=40EAA09302E9
   std::string  m_TaskName;

  // Data base name
  //##ModelId=40EAA09302D9
   std::string  m_DataBase;

  // Data base access string user name.
  //##ModelId=40EAA09302DD
   std::string  m_DBUserName;

  // Data base access string password.
  //##ModelId=40EAA09302DB
   std::string  m_DBPassWd;

  // Name specified by the application to identify the 
  //server process.
  //##ModelId=40EAA09302E5
   std::string  m_ServerName;

  // port number the ORB should use to listen for IIOP 
  //calls.
  //##ModelId=40EAA09302DF
   std::string  m_IIOP_Port;

  // The name of the channel that the event service 
  //instance administers.
  //##ModelId=40EAA09302D3
   std::string  m_ChannelName;

  // Event Service name.
  //##ModelId=40EAA09302E7
   std::string  m_ServiceName;

  // Number of Arguments necessary to create an event 
  //channel instance.
  //##ModelId=40EAA09302CB
  int m_ArgcForEventConsumer;

  // Arguments necessary to create an event channel 
  //instance.
  //##ModelId=40EAA09302CD
  char* *  m_ArgvForEventConsumer   ;

  //##ModelId=40EAA09302D1
  char* *  m_ArgvForEventSender;

  //mz | created | 2003.07.23 
  //
  //To hide argc, argv parameters of the constructor
  //(made protected now)
  //##ModelId=40EAA09302A8
  static cCBS_StdInitBase* CreateInstance(const std::string   & procName = "SMCApplication_FrameProgram", const std::string   & iniFileName = "default");

  //##ModelId=40EAA09302AF
  static void DeleteInstance();

  //mz | created | 2003.07.23 
  //
  //To hide argc, argv parameters of the constructor
  //(made protected now)
  //##ModelId=40EAA09302B2
  static   cCBS_StdInitBase* getInstance();

	// Provides a configuration element of type string from 
	//INI file by calling
	// the ConfigBase element function getActGrpEle.
  //##ModelId=40EAA09302B8
  bool getEntry(const std::string & Group, const std::string & Element, std::string  &value    );

  //##ModelId=40EAA09302C0
  virtual ~cCBS_StdInitBase();

  //##ModelId=40EAA09302C3
  cCBS_StdInitBase(int argc, char *argv[]);

protected:
  //##ModelId=40EBCAAD03E6
  cCBS_ConfigBase* m_pCBS_ConfigBase;


  // sets all configuration data to initialize server 
  //object.
  //##ModelId=40EAA09302A6
  void initialize();

private:
	//##ModelId=4124E5CC034B
	std::string m_ConfigName;

	//##ModelId=411B395D03BE
	std::string m_XPACT_SMC;

	//##ModelId=411B39C0015E
	std::string m_XPACT_SMC_LOG;

	std::string m_XPACT_SMC_RT;

  //##ModelId=40EBCAAE000A
  static cCBS_StdInitBase* m_pInstance;

  std::string Trim(const std::string& Value, const std::string& Sign = " ");

};


#endif /* _INC_CINITBASE_40C0768103A2_INCLUDED */
