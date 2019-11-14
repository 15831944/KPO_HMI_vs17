
#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEMAILSERVER_COMP_41127C3B008F_INCLUDED
#define _INC_CEMAILSERVER_41127C3B008F_INCLUDED

#include <gcroot.h>

#include <CBS_General.h>
#include <CBS_Tasks.h>
#include <CBS_StdAPI/cCBS_StdComponent.h>
#include <CBS_Utilities/cCBS_ConfigBase.h>
#include "cEmailServer_EventHandlerTask.h"
//#include "emails_cParam.h"


class cEmailServer_Comp : public cCBS_StdComponent
{
public:
  virtual ~cEmailServer_Comp();
  virtual void createSubtasks();
  void afterSubtaskEnd();

  static cEmailServer_Comp * getComponent();	

  void connectDB();

  static void release(); 

  const char * getIniFile();

  cCBS_ConfigBase * getCfb() { return m_cfb ; };  

  //EMAILS::cParam::EmailParameter * ReadConfigParameters(std::string cfgSection);
  std::string m_EmailOutputPath;

protected:
  void ownStartUp();
  static std::string ConvertString(String^ s);
  static String^ ConvertString(const char* s);
  //void initializeEmailParameter();

private:
  cEmailServer_Comp();  

  cCBS_ConfigBase *m_cfb;

  cEmailServerEventHdlTask* m_pEmailServerEventHdlTask;

  //std::map<std::string,EMAILS::cParam::EmailParameter> m_EmailsParameterMap;

  static cEmailServer_Comp * m_comp;	
  std::string m_IniFile; 

  
};

#endif /* _INC_CEMAILSERVER_COMP_41127C3B008F_INCLUDED */
