// Copyright (C) 2005 SMS Demag AG Germany

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTraceLogCleaner_Controller_4253CDEE012D_INCLUDED
#define _INC_CTraceLogCleaner_Controller_4253CDEE012D_INCLUDED


#include <string>

class CTraceLogCleaner_Controller 
{
protected:
	//task controller thread. this calls cecks the time 
//difference between the time when the "control" method has 
//been called . If the duraction reaches the given 
//ControlTime, the doOnThreadControlError of the respective 
//task will be called.
  class cCTraceLogCleaner_Thread 
	: public cCBS_Thread
	{
	private:

    std::string m_ZipFileName;
    std::string m_FullPathName;
    std::vector<std::string> m_FileExtensions;
    long m_FileLifeTime;
    long m_NoOfFiles; // size if Files vector for No of files to be deleteed/zipped at one control cycle

    std::vector<std::string> m_FileList;
    std::vector<std::string>::iterator m_FileListIterator;



    friend class CTraceLogCleaner_Controller;

	public:
		void terminate();

		//Expects the ControlTime in ms
		cCTraceLogCleaner_Thread(const std::string& ControlPath, const std::string& ControlDirectory);

	protected:
		//Work function called in a loop by the thread (via the 
	//work method). Can be redefined by subclasses. 
	//
	//The default implementation does nothing (except 
	//sleeping for 1 second). This method could have been 
	//declared abstract. Anyway, in order to allow instances 
	//of cCBS_Thread to be created (in the case where a 
	//thread function has been specified for execution), it 
	//has been implemented doing nothing.
		virtual void performWorkingStep();

		long m_ControlTime;

    bool m_ZipFiles;
    bool m_ZipPerDay;

    std::string m_ControlPath;
    std::string m_ControlDirectory;
    std::string m_ZipDirectory;
    std::string m_Xpact_Smc_Rt;
    std::string m_Xpact_Smc;
    
		virtual ~cCTraceLogCleaner_Thread();

		//Virtual work method. Sleeps for the specified ControlTime and checks status 
	  //will run down task and component in case of errors
		virtual void work();

    bool removeFiles(std::vector<std::string> FileList);
    
    void setFileList(const std::string& FullPath);

	};

public:

	CTraceLogCleaner_Controller(const std::string& ControlPath, const std::string& ControlDirectory);

	virtual ~CTraceLogCleaner_Controller();

  void log(const std::string& Message, long Level = 1);

private:

  std::string m_ControlPath;
  std::string m_ControlDirectory;

protected:

	cCTraceLogCleaner_Thread* m_pCleaner_Thread;


};

#endif /* _INC_CTraceLogCleaner_Controller_4253CDEE012D_INCLUDED */
