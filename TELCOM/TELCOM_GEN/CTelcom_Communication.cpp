// Copyright (C) 2007 SMS Demag AG

#include "CTelcom_Communication.h"
#include "CTelcom_S7BinaryTransport.h"       // For binary comm with Big Endian boxes (e.g. Siemens S7)
#include "cCBS_StdLog_Task.h"
#include "cCBS_StdInitBase.h"
#include "telcom.h"



//##ModelId=45ACADF00044
CTelcom_Communication::~CTelcom_Communication()
{
}

//##ModelId=45ACADEF01AA
CTelcom_Communication::CTelcom_Communication()
{
}

//##ModelId=45ACC8F100B0
void CTelcom_Communication::initComm()
{
  bool BigEndPlatf = false;
  cCBS_StdInitBase::getInstance()->replaceWithEntry("SMS_Definition","BigEndian",BigEndPlatf);

  TransTypeDict* p_TT = new TransTypeDict();
  if (BigEndPlatf)
  {
    (*p_TT)["binary"] = new CTelcom_S7BinaryTransport(CTelcom_S7BinaryTransport::HL,CTelcom_S7BinaryTransport::HL);
    cCBS_StdLog_Task::getInstance()->log("Communication: Using CTelcom_S7BinaryTransport (big-endian communication partner)", 1);
  }
  else
  {
    (*p_TT)["binary"] = new HostBinaryTT();
    cCBS_StdLog_Task::getInstance()->log("Communication: Using HostBinaryTT", 1);
  }
  (*p_TT)["ascii"]  = new AsciiTT(); // ASCII

  // Prepare Format Manager to handle both FEL and CSV format
  FormatMgr::instance()->setLoader     ("FEL", new FELLoader     (*p_TT));
  FormatMgr::instance()->setSerializer ("FEL", new FELSerializer (*p_TT));
  FormatMgr::instance()->setLoader     ("CSV", new CSVLoader());
  FormatMgr::instance()->setSerializer ("CSV", new CSVSerializer());

  // loader and serializer for MsgConverter
  FormatMgr::instance()->setLoader     ("CSVConverter", new CSVLoader());
  FormatMgr::instance()->setSerializer ("CSVConverter", new CSVSerializer());
  FormatMgr::instance()->setLoader     ("FELConverter", new FELLoader     (*p_TT));
  FormatMgr::instance()->setSerializer ("FELConverter", new FELSerializer (*p_TT));

  // prepare arguments into init() in telcom
  m_argc = cCBS_StdInitBase::getInstance()->numCmdLineArgs();
  std::vector<std::string> argum;
  cCBS_StdInitBase::getInstance()->getCmdLineArgs(argum);
  if (argum.size() == 3)
  {
    m_argc = 2;
    //make "-cfg=XXXX.ini";
    argum.at(1) = "-cfg=" + argum.at(2);

    m_argv = new char*[m_argc];
    for (int ii=0; ii<m_argc; ii++)
    {
      m_argv[ii] = new char[argum.at(ii).size()+1];
      strcpy(m_argv[ii], argum[ii].c_str());
    }
  }
  else
  {
    std::string mes;
    mes = "Wrong number of arguments: use -config file.ini";
    std::cerr << mes;
    cCBS_StdLog_Task::getInstance()->log(mes, 1);
  }
}

