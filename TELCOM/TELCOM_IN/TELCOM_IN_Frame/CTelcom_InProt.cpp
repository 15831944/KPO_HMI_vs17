// Copyright (C) 2007 SMS Demag AG

#include "CDateTime.h"
#include "CDataConversion.h"

#include "cCBS_StdLog_Task.h"

#include "CTelcom_InTask.h"
#include "CTelcom_TcpipTransport.h"
#include "CTelcom_InTcpipTransport.h"

#include "CTelcom_InProt.h"



//##ModelId=45B4CC7901F3
int CTelcom_InProt::doHandleTlgError(TC_Exception &e, TCMessage &msg)
{
  static int numErrors = 0;

  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ExceptionCaught(sMessage, e.what(), "CTelcom_InProt::doHandleTlgError", msg.getBufString().c_str() );
  
  // default action: log error in base class
  (void)RProt::doHandleTlgError(e,msg);
 
  if (++numErrors > 100)
  {
    std::string Message;
    Message = "CTelcom_InProt: Too many errors. Disconnecting now.";
    cCBS_StdLog_Task::getInstance()->log(Message,1);
    logError(Message.c_str());
    setCommand(cmdDisconnect);
    numErrors = 0; // reset error count !
  }
  // do not confirm telegram (not used here).
  return tlgAbort;
}

//##ModelId=45AC957302DC
CTelcom_InProt::CTelcom_InProt() : m_Redundancy(false)
{
}

//##ModelId=45AC9574014D
CTelcom_InProt::~CTelcom_InProt()
{
}

bool CTelcom_InProt::onMessage(TCMessage& msg)
{
  // come here each time any msg comes in,.
  // CTelcom_InTask::getInstance()->setWorking(true);

  std::stringstream Message;
  Message << "len=" << std::setw(3) << msg.bufLen() << " msg=" << msg.getBuf();

  CTelcom_InTask::getInstance()->setStateDetails("Telegram content", Message.str(), 3);

  // the base class's method resets the Watchdog timer as specified in INI file.
  bool ReturnValue = RProt::onMessage(msg);  // this is smarter.

  return true;
}

//##ModelId=45AC96CB0166
void CTelcom_InProt::onMissingWatchdog()
{
  // Come here each time wdogInterval is expired.
  // This action appears only if 'receiveTimeout' in the ini file is smaller than 'wdogInterval'
  // Default we set the setCommand(cmdDisconnect) that results in an error message like
  // 11:58:14.37 [ERR]: tcp/ip receive: NETCOM-3 illegal connection handle
  //
  // This is harmless since it still does what it is expected to do, 
  // namely to disconnect the connection.
  //
  /////////////////////////////////////////////////////////////////////////////////
  std::stringstream Message;

  Message << "No Watchdog within " << getWdogInterval() << " seconds. Disconnect and wait for new connection.";

  if (! m_Redundancy)
  {
    setCommand(cmdDisconnect );
    Message << " Disconnect and wait for new connection.";
  }
  else
  {
    Message << " Disconnect and switch to other communication partner:";
    if (connected())
      disconnect();

    CTelcom_InTask::getInstance()->setWorking(false);
    static_cast<CTelcom_TcpipTransport*>(getTransport())->switchConnection();
    CTelcom_InTask::getInstance()->sendSwitchConnectMessage();
  }

  Message << " at " << CDateTime().asString();

  CTelcom_InTask::getInstance()->setStateDetails("onMissingWatchdog",Message.str().c_str(), 0);
  cCBS_StdLog_Task::getInstance()->log(Message.str(),2);
}

//##ModelId=45AC96CB017A
void CTelcom_InProt::configure(const std::string& section, Configuration& c)
{
  // must be called first to config base class
	RProt::configure(section, c);

  // read own configuration if needed
  std::string t = section;

  c.setSection("SMS_Definition");
  m_Redundancy = c.getbool("isRedundancy", false);

  c.setSection(t);
}

//##ModelId=45AC974C0316
void CTelcom_InProt::doMakeReply(const RProt::ReplyContext& context, const TCMessage& t, TCMessage& replybuf)
{
  cCBS_StdLog_Task::getInstance()->log("Making a reply message...",3);

  try 
  {

    std::string msgid = t.getType();
  	std::string l_seqNo = "1";

    Tlg *tlg = (getTlgFactory())->getTlg (msgid);

    if   (tlg)
    {
		  TlgFactory *origTf = getTlgFactory();

		  FmtConverter *cnv = new FmtConverter( *origTf);
		  std::stringstream strm (cnv->convert (msgid, t.getBufString(), "FEL", "CSV"));
		  tlg->setLoader(FormatMgr::instance()->getLoader     ("CSV"));
		  strm >> *tlg;

		  l_seqNo = (*tlg)["Header"]["MessageCount"].asString();
	  }
	  
  	TlgFactory *tf = getTlgFactory();

    if (tf)
    {
      string ackType = "ACKN_TO_TSV";
      cCBS_StdLog_Task::getInstance()->log("Start Reply..", 3);

	    string rcvType = t.getType();

	    std::string MsgIdStr; // JAST = allSendMsg->translateMsgName (rcvType);
		
	    int l_res = context.errCode;

      Tlg *replytlg = tf->makeTlg (ackType);
      
      if   (replytlg)
      {
        cCBS_StdLog_Task::getInstance()->log("Inside Reply..", 3);
        replytlg->setSerializer(FormatMgr::instance()->getSerializer("FEL"));
  
		    CDateTime now;

		    std::string time = now.asString("%Y%m%d%H%M%S");

		    std::string l_year = time.substr(0, 8);
		    std::string l_hours = time.substr(8, 14);

		    long     msglen = (*replytlg).getLen();
		  
        (*replytlg)["Header"]["MessageLength"].set("00000056");
		    (*replytlg)["Header"]["SenderNode"].set ("CC001");
		    (*replytlg)["Header"]["ReceiverNode"].set ("KR001");
		    (*replytlg)["Header"]["Date"].set (l_year);
		    (*replytlg)["Header"]["Time"].set (l_hours);
		    (*replytlg)["Header"]["MessageId"].set ("ZZ200");
		    (*replytlg)["Header"]["MessageCount"].set (l_seqNo);
		    (*replytlg)["Header"]["Flags"].set ("0");       // not used

        (*replytlg)["MessageId"].set(MsgIdStr);
		    
        if (l_res == 0)
        {
			    (*replytlg)["ResponseCode"].set("0");
        }
		    else
        {
			    (*replytlg)["ResponseCode"].set("1");
        }

		    cCBS_StdLog_Task::getInstance()->log("Response code :" + CDataConversion::LongToString(l_res), 3);

        cCBS_StdLog_Task::getInstance()->log("send Reply.." , 3);

        replytlg->serialize(replybuf.bufOstr());
        delete replytlg;

      }
      else
      {
        cCBS_StdLog_Task::getInstance()->log("Could not create a replytlg", 1);
      }
    }
    else
    {
      cCBS_StdLog_Task::getInstance()->log("Could not create a TlgFactory", 1);
    }
  }
  catch(EUnknownTlg &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, e.what(), "CTelcom_InProt::doMakeReply", "");
  }
  catch(EElemNotFound &e)
  {
    std::stringstream Message;
    Message << "InProt::doMakeReply: " << e.what() << e.getPath();
    cCBS_StdLog_Task::getInstance()->log(Message.str(), 1);
  }
  catch (ETAMError &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, e.what(), "CTelcom_InProt::doMakeReply", "");
  }
  catch (...)
  {
    cCBS_StdLog_Task::getInstance()->log("InProt::OOPS... making of a reply failed.", 1);
  }
}

//##ModelId=45ACA23D0238
void CTelcom_InProt::doOnConnectError(ETransport & ex, bool isTimeout)
{

  std::string Message;
  Message = "CTelcom_InProt::doOnConnectError: ";
  Message += ex.what();

  if (m_Redundancy)
  {
    if (isTimeout)
    {
      disconnect();

      Message += " communication disconnected because of timeout";

      Message += " at " + CDateTime().asString();

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ConnectionError(sMessage, cCBS_StdInitBase::getInstance()->m_ServerName.c_str(), Message.c_str());


      static_cast<CTelcom_TcpipTransport*>(getTransport())->switchConnection();

      CTelcom_InTask::getInstance()->sendSwitchConnectMessage();
    }
  }
}

//##ModelId=45B4D2DF0002
void CTelcom_InProt::onConnectHook()
{
  CTelcom_InTask::getInstance()->setWorking(true);
}

