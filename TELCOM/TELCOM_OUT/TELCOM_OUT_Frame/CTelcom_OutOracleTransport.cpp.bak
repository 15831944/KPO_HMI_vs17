#include <vector>

#include "Telcom_Out_s.hh"

#include "cCBS_StdLog_Task.h"
#include "CSMC_EventLogFrameController.h"

#include "CTelcom_OutTask.h"
#include "CTelcom_OutMsgTypeTranslator.h"

#include "CTelcom_OutOracleTransport.h"
#include "CDataConversion.h"




#include "cCBS_StdDB_Task.h"
#include "cCBS_StdEvent_Task.h"

//##ModelId=45AB96E8003D
CTelcom_OutOracleTransport::CTelcom_OutOracleTransport()
: CTelcom_OracleTransport()
{
    //m_pStoredFunction = new CTelcom_OdbcStoredFunction();
    //m_fieldIterations = 99;



  cCBS_StdInitBase *pStdInitBase = cCBS_StdInitBase::getInstance();   
  long tebleCount = 0;
  
  if( !( pStdInitBase->getEntry("ORASEQUENCE", "SEQNAME", oracleSequence) ) )
  {
    std::cerr << "Can not read input settings from ini-file" << std::endl;
  }

  if( !( pStdInitBase->getEntry("ORASEQUENCE", "SEQCOL", oracleSequenceCol) ) )
  {
    std::cerr << "Can not read input settings from ini-file" << std::endl;
  }
	


  if( !( pStdInitBase->getEntry("TABLECOUNT", "TABLES", tebleCount) ) )
  {
    std::cerr << "Can not read input settings from ini-file" << std::endl;
  }
  
  for (int k = 0; k < tebleCount; k ++)
  {
    string group = "TABLECOUNT_" + CDataConversion::IntToString(k+1);
    string tableName = "";
    string telegramName = "";

    if( ! ( pStdInitBase->getEntry(group, "TLGTYPE", telegramName) && pStdInitBase->getEntry(group, "MASTERTABLE", tableName) ) )
    {
      std::cerr << "Can not read input settings from ini-file" << std::endl;
      continue;
    }
    TableList.insert( std::pair <std::string,std::string>(tableName,telegramName) ); 
  }


  pStdConnection = CTelcom_OutTask::getInstance()->getStdConnection();
  pCBSConnection = pStdConnection->getpCBSConnection();

}

//##ModelId=45AB96E801C3
CTelcom_OutOracleTransport::~CTelcom_OutOracleTransport()
{
  try
  {
    //if (m_pStoredFunction) 
    //{
    //  delete m_pStoredFunction;
    //  m_pStoredFunction = 0;
    //}
  }
  catch(cCBS_DBExc &e) 
  {
    std::cout << e.getText() << std::endl;
  }  
}

void CTelcom_OutOracleTransport::configure(const std::string & section, bas::Configuration & c)
{
  // execute the configuration of the base class:
  //CTelcom_OracleTransport::configure(section, c);

  try
  {

    //if ( m_pStoredFunction->ODBCConnection() )
    //{
    //  CTelcom_OutTask::getInstance()->setWorking(true);
    //}
  }
  catch(cCBS_DBExc &e) 
  {
    std::cout << e.getText() << std::endl;
  }
}

int CTelcom_OutOracleTransport::doConnect()
{
  // -1 indicates timeout, 0 means "Connected.
  int retval = -1;

  // must be called first, in order that thread sleep 100ms
  //retval = CTelcom_OracleTransport::doConnect();




  retval = 0;

  return retval;
}

int CTelcom_OutOracleTransport::doDisconnect()
{
  try
  {
    //if (m_pStoredFunction) 
    //{
    //  m_pStoredFunction->freeAllHandles();
    //  //delete m_pStoredFunction;
    //}
  }
  catch(cCBS_DBExc &e) 
  {
    std::cout << e.getText() << std::endl;
  }

  CTelcom_OutTask::getInstance()->setWorking(false);

  int sta = 0;

  //sta = CTelcom_OracleTransport::doDisconnect();
  //if (sta == -1)
  //{
  //  cCBS_StdLog_Task::getInstance()->log("Dis-Connection timeout!");
  //}
  //else
  //{
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_LostConnection(sMessage,cCBS_StdInitBase::getInstance()->m_ServerName.c_str());

  //  cCBS_StdLog_Task::getInstance()->log("CTelcom_OutOracleTransport::doDisconnect: Dis-Connected!");
  //}

  return sta;
}


void CTelcom_OutOracleTransport::send(const TCMessage & msg)
{
  int retVal = -1;
  
  std::map<std::string,std::string>::iterator it2;
  for (it2 = TableList.begin() ; it2 != TableList.end() ; ++it2)
  {
	  std::string tableName = (it2->first);
	  std::string telegramName = (it2->second);
	  if (msg.getType() == telegramName)
	  {
		   retVal = writeDataBase(msg,tableName,telegramName);
		   break;
	  }
  }




  //// get Date
  //CDateTime now;
  ////std::stringstream DateTime;
  //
  ////DateTime << now.getYear() << "-" << now.getMonth() << "-" << now.getDay();
  ////DateTime << " " << now.getHour() << ":" << now.getMinute() << ":" << now.getSecond();

  ////initialize members
  ////2009-01-29 00:00:00
  //m_transmission = now.asString("%Y-%m-%d %H:%M:%S");
  //m_typeReport = "TestOut";
  //m_timezone  = now.get_DST() ? "S":"W";
  //m_lastSender = msg.getSender();
  //m_currentSender = "L22";
  //
  //// will be set later
  //m_messageContent = "";
  //m_destination = "";  
  //
  //// get Message from DH and fill it into m_messageContent
  //retVal = setMessageForDB(msg);

  //if(retVal == -1)
  //{
  //  //msg is not handled
  //  std::stringstream Message;
  //  Message << "void CTelcom_OutOracleTransport::send: Message: - " << msg.getType() << " - could not be prepared for DataBase";
  //  cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),1); 
  //}
  //else
  //{   
  //  try
  //  {
  //    // If one found, open it and we really send
  //    if(m_pStoredFunction)
  //    {  
  //      // This method sends the message to the DB
  //      if( !m_pStoredFunction->sendBerichtToCorusDB(m_currentSender, m_typeReport, m_messageContent) )
  //      {
  //        //msg is not handled
  //        std::stringstream Message;
  //        Message << "void CTelcom_OutOracleTransport::send: Message: " << msg.getType() << " - is not send to " << m_destination;
  //        Message << "transmission: " << m_transmission;
  //        Message << "typeReport: " << m_typeReport;
  //        Message << "timezone: " << m_timezone;
  //        Message << "messageContent: " << m_messageContent;
  //        Message << "last sender: " << m_lastSender;
  //        Message << "current sender: " << m_currentSender;
  //        cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),3); 
  //      }
  //    }//if(m_pStoredFunction)
  //  }
  //  catch(cCBS_DBExc &eDB )
  //  {
  //    std::stringstream Message;
  //    Message << "CTelcom_OutOracleTransport::send:SQLERROR: " << eDB.getText();
  //    cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),0);
  //  }
  //}// else




}// void CTelcom_OutOracleTransport::send(const TCMessage & msg)

long CTelcom_OutOracleTransport::getMessageCountXXXXX()
{
  long retVal = -1;

  std::string stmt = "";
	std::string Scope("CTelcom_OutOracleTransport::getMessageCount()");

	cCBS_Statement* insertStatement = 0;
  try
  {   
    if(pCBSConnection)
      insertStatement = pCBSConnection->createPtStatement();
    else
    {
      cCBS_StdEvent_Task::getInstance()->log("CTelcom_OutOracleTransport::writeDataBase() no database connection" ,2); 
      cCBS_StdDB_Task::getInstance()->freeConnections();
      return retVal;
    }

    if(insertStatement)
      insertStatement->execute(stmt);
    else
    {
      cCBS_StdEvent_Task::getInstance()->log("CTelcom_OutOracleTransport::writeDataBase()  insertStatement failed" ,2); 
      return retVal;
    }


    retVal = 0;
    pCBSConnection->commit();
         
    if   (insertStatement)  {pCBSConnection->freeStatement(insertStatement);  insertStatement=0;}

  }
  catch(cCBS_DBExc_ConnectionError &cExc) 
  {
		cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc.getText().c_str(),Scope.c_str(), "");

    try
    {
      pStdConnection->reconnect();
      pCBSConnection = pStdConnection->getpCBSConnection();
    }
    catch (...)
    {
       cCBS_StdLog_Task::getInstance()->log("--- CTelcom_OutOracleTransport: pStdConnection->reconnect....database connection problem ---",3);
       retVal = -1;
    }

    retVal = -1;
    if   (insertStatement)  {pCBSConnection->freeStatement(insertStatement);  insertStatement=0;}
  }
  catch (cCBS_DBExc &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),Scope.c_str(), ""); 
    retVal = -1;
    if   (insertStatement)  {pCBSConnection->freeStatement(insertStatement);  insertStatement=0;}
  }
  catch(CORBA::SystemException& sExc) 
  {
		cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),Scope.c_str(), "");
    retVal = -1;
    if   (insertStatement)  {pCBSConnection->freeStatement(insertStatement);  insertStatement=0;}
  }
  catch(CORBA::Exception& cExc) 
  {
		cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),Scope.c_str(), "");
    retVal = -1;
    if   (insertStatement)  {pCBSConnection->freeStatement(insertStatement);  insertStatement=0;}
  }
  catch (...)
  {
     cCBS_StdLog_Task::getInstance()->log("--- CTelcom_OutOracleTransport: Unexpected exception caught.. ---",3);
     retVal = -1;
     if   (insertStatement)  {pCBSConnection->freeStatement(insertStatement);  insertStatement=0;}
  }

  return retVal;

}


long CTelcom_OutOracleTransport::newMessageCount()
{
  long retVal = -1;

  std::string stmt = "select " + oracleSequence + ".nextval as messageCount from dual";
	std::string Scope("CTelcom_OutOracleTransport::newMessageCount()");

	cCBS_Statement* selectStatement = 0;
  try
  {   
    if(pCBSConnection)
      selectStatement = pCBSConnection->createPtStatement();
    else
    {
      cCBS_StdEvent_Task::getInstance()->log("CTelcom_OutOracleTransport::newMessageCount() no database connection" ,2); 
      cCBS_StdDB_Task::getInstance()->freeConnections();
      return retVal;
    }

    if(selectStatement)
      m_pResultSet = selectStatement->executePtQuery(stmt);
    else
    {
      cCBS_StdEvent_Task::getInstance()->log("CTelcom_OutOracleTransport::newMessageCount()  selectStatement failed" ,2); 
      return retVal;
    }


		if ( (m_pResultSet) && (m_pResultSet->first()))
		{
			retVal = m_pResultSet->getInt(0); 
		}

    m_pResultSet = 0;     
    if   (selectStatement)  {pCBSConnection->freeStatement(selectStatement);  selectStatement=0;}

  }
  catch(cCBS_DBExc_ConnectionError &cExc) 
  {
		cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc.getText().c_str(),Scope.c_str(), "");

    try
    {
      pStdConnection->reconnect();
      pCBSConnection = pStdConnection->getpCBSConnection();
    }
    catch (...)
    {
       cCBS_StdLog_Task::getInstance()->log("--- CTelcom_OutOracleTransport: pStdConnection->reconnect....database connection problem ---",3);
       retVal = -1;
    }

    retVal = -1;
    if   (selectStatement)  {pCBSConnection->freeStatement(selectStatement);  selectStatement=0;}
  }
  catch (cCBS_DBExc &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),Scope.c_str(), ""); 
    retVal = -1;
    if   (selectStatement)  {pCBSConnection->freeStatement(selectStatement);  selectStatement=0;}
  }
  catch(CORBA::SystemException& sExc) 
  {
		cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),Scope.c_str(), "");
    retVal = -1;
    if   (selectStatement)  {pCBSConnection->freeStatement(selectStatement);  selectStatement=0;}
  }
  catch(CORBA::Exception& cExc) 
  {
		cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),Scope.c_str(), "");
    retVal = -1;
    if   (selectStatement)  {pCBSConnection->freeStatement(selectStatement);  selectStatement=0;}
  }
  catch (...)
  {
     cCBS_StdLog_Task::getInstance()->log("--- CTelcom_OutOracleTransport: Unexpected exception caught.. ---",3);
     retVal = -1;
     if   (selectStatement)  {pCBSConnection->freeStatement(selectStatement);  selectStatement=0;}
  }

  return retVal;

}

int CTelcom_OutOracleTransport::writeDataBase(const TCMessage & msg,std::string tableName,std::string telegramName)
{	
  int retVal = -1;

  std::string eNameWithType = "";
  std::string stmt = "";

  std::string Scope("CTelcom_OutOracleTransport::writeDataBase(TCMessage & msg,std::string tableName,std::string telegramName)");
  cCBS_Statement* insertStatement = 0;

  try
  {
		if(m_pFactory)
		{

			long messageCount = newMessageCount();
			std::string msgCount =  CDataConversion::LongToString(messageCount);

			stmt =  "INSERT INTO " + tableName + " VALUES ( " ;
   
			// get tlg referance to store data from received msg
			tlg = m_pFactory->getTlg(msg.getType());
			// loader to load msg buffer. Message will be saved in local format 
			std::string lFormat("CSV");
			cCBS_StdInitBase::getInstance()->replaceWithEntry("rprot", "localFormat", lFormat);
			tlg->setLoader(FormatMgr::instance()->getLoader(lFormat));
			// load msg buffer into telegram
			tlg->load(msg.getBufString());

			int elNo = tlg->countElems();

			for (int ii=0; ii<elNo; ii++)   // get each element's value
			{
				TlgElem& te = (*tlg)[ii];
				std::string stName = te.getName();
				const char * elemName = stName.c_str();

				switch (te.getType())
				{
				case TlgElem::tInteger:
				{
					eNameWithType = " - " + stName + " with type integer  " ;
					if(oracleSequenceCol == stName)
						stmt =  stmt + msgCount + ",";
					else
						stmt =  stmt + CDataConversion::IntToString(te.asInteger()) + ",";
					break;
				}
				case TlgElem::tNumber:
				{
					eNameWithType = " - " + stName + " with type number  " ;
					if(oracleSequenceCol == stName)
						stmt =  stmt + msgCount + ",";
					else
						stmt =  stmt + CDataConversion::LongToString(te.asNumber()) + ",";
					break;
				}
				case TlgElem::tBool:
				{
					eNameWithType = " - " + stName + " with type bool  " ;
					//stmt =  stmt + te.asString() + ",";
					break;
				}
				case TlgElem::tString:
				{
					eNameWithType = " - " + stName + " with type string  " ;
					stmt =  stmt + "'"+ te.asString() + "'" + ",";
					break;
				}
				case TlgElem::tDateTime:
				{
					eNameWithType = " - " + stName + " with type datetime  " ;
					stmt =  stmt + te.asString() + ",";
					break;
				}//case TlgElem::tDateTime:        
				default:
					break;
				}

			} //for...

			stmt = stmt.substr(0,stmt.length() -1); //remove last ,
			stmt =  stmt + " );";
			cCBS_StdLog_Task::getInstance()->log("insert statement :  " + stmt ,2);

		} //m_pFactory
  }
  catch (ETAMError &e)
  {
    std::string Action;
    Action = "TAM Error converting Telegram : ";
    Action += tlg->getId();//TlgType;
    Action += eNameWithType;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, e.what(),
                                  "CTelcom_OutOracleTransport::writeDataBase",
                                  Action.c_str());
    retVal = -1;
  }
  catch (...)
  {
    std::string Action;
    Action = "Converting Telegram : ";
    Action += tlg->getId();//TlgType;
    Action += eNameWithType;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "Unknown Exception",
                                  "CTelcom_OutOracleTransport::writeDataBase",
                                  Action.c_str());
    retVal = -1;
  }



  try
  {   
    if(pCBSConnection)
      insertStatement = pCBSConnection->createPtStatement();
    else
    {
      cCBS_StdEvent_Task::getInstance()->log("CTelcom_OutOracleTransport::writeDataBase() no database connection" ,2); 
      cCBS_StdDB_Task::getInstance()->freeConnections();
      return retVal;
    }

    if(insertStatement)
      insertStatement->execute(stmt);
    else
    {
      cCBS_StdEvent_Task::getInstance()->log("CTelcom_OutOracleTransport::writeDataBase()  insertStatement failed" ,2); 
      return retVal;
    }


    retVal = 0;
    pCBSConnection->commit();
         
    if   (insertStatement)  {pCBSConnection->freeStatement(insertStatement);  insertStatement=0;}

  }
  catch(cCBS_DBExc_ConnectionError &cExc) 
  {
		cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc.getText().c_str(),Scope.c_str(), "");

    try
    {
      pStdConnection->reconnect();
      pCBSConnection = pStdConnection->getpCBSConnection();
    }
    catch (...)
    {
       cCBS_StdLog_Task::getInstance()->log("--- CTelcom_OutOracleTransport: pStdConnection->reconnect....database connection problem ---",3);
       retVal = -1;
    }

    retVal = -1;
    if   (insertStatement)  {pCBSConnection->freeStatement(insertStatement);  insertStatement=0;}
  }
  catch (cCBS_DBExc &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),Scope.c_str(), ""); 
    retVal = -1;
    if   (insertStatement)  {pCBSConnection->freeStatement(insertStatement);  insertStatement=0;}
  }
  catch(CORBA::SystemException& sExc) 
  {
		cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),Scope.c_str(), "");
    retVal = -1;
    if   (insertStatement)  {pCBSConnection->freeStatement(insertStatement);  insertStatement=0;}
  }
  catch(CORBA::Exception& cExc) 
  {
		cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),Scope.c_str(), "");
    retVal = -1;
    if   (insertStatement)  {pCBSConnection->freeStatement(insertStatement);  insertStatement=0;}
  }
  catch (...)
  {
     cCBS_StdLog_Task::getInstance()->log("--- CTelcom_OutOracleTransport: Unexpected exception caught.. ---",3);
     retVal = -1;
     if   (insertStatement)  {pCBSConnection->freeStatement(insertStatement);  insertStatement=0;}
  }

  return retVal;
}

int CTelcom_OutOracleTransport::setMessageForDB(const TCMessage & msg)
{
  int retVal = -1;

  std::stringstream Message;
  Message << "Received a message. "; 
  Message << "Msg Type is " << msg.getType();

  try
  {

    if(m_pFactory)
    {
      // get tlg referance to store data from received msg
      tlg = m_pFactory->getTlg(msg.getType());
      // loader to load msg buffer. Message will be saved in local format
      tlg->setLoader(FormatMgr::instance()->getLoader(m_RemoteMsgFormat));
      // load msg buffer into telegram m_LocalMsgFormat -> m_RemoteMsgFormat
      tlg->load(msg.getBufString());

      // depends on telegram id to call a function
      long MsgID = (*tlg)["Header"]["MessageId"].asInteger();

      // send to Level3
      if ( (MsgID >= 2300) && (MsgID <= 2304) )
      {
        retVal = LF22ToLevel3();
        m_destination = "Level3";
      }
      // send to RAS
      else if ( (MsgID >= 2305) && (MsgID <= 2311) )
      {
        retVal = LF22ToRAS();
        m_destination = "RAS";
      }
      // send to GWI
      else if ( (MsgID == 2312) )
      {
        retVal = LF22ToGWI();
        m_destination = "GWI";
      }
      // send to FDB
      else if ( (MsgID >= 2313) && (MsgID <= 2321) )
      {
        retVal = LF22ToFDB();
        m_destination = "FDB";
      }
      else
      {
        std::stringstream Message;
        Message << "CTelcom_OutOracleTransport::setMessageForDB: No receiver found : " << m_sender ;
        cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),1); 
        retVal = -1;
      } 

      // delete telgram
      tlg->clear();     
      //delete tlg; 

    }// if(m_pFactory)
    else 
    {
      std::stringstream Message;
      Message << "ERROR: CTelcom_OutOracleTransport::setMessageForDB: factory was not set";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),1);
      retVal = -1;
    }

  }
  catch( EUnknownTlg &e )
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, e.what(), "CTelcom_OutOracleTransport::setMessageForDB", "");
    retVal = -1;
  }
  catch (ETAMError &eTam)
  {
    Message.clear();
    Message << " - TAM Error converting Telegram : ";

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, eTam.what(),
      "CTelcom_OutOracleTransport::setMessageForDB",
      Message.str().c_str());
    retVal = -1;
  }
  catch( ... )
  {
    Message.clear();
    Message << "CCTelcom_OutOracleTransport::setMessageForDB: Unknown exception: ";
    cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),0);
    retVal = -1;
  }

  return retVal;
}// int CTelcom_OutOracleTransport::setMessageForDB(const TCMessage & msg)

int CTelcom_OutOracleTransport::LF22ToLevel3()
{
  int retVal = -1;

  // handle right Telegram
  if ( !tlg->getId().compare(std::string("AANKOMST01")) ) 
  {
    //MessageId(3008L)
    m_messageContent.clear();
    try
    {  
      m_typeReport = tlg->getId();

      // HERE SOMETHING IS STILL MISSING.

      //m_messageContent = convertMessage("X",5, (*tlg)[Telegram_AANKOMST01::HeatId].asString());
      //m_messageContent += convertMessage("9",3, (*tlg)[Telegram_AANKOMST01::LadleId].asString());
      //m_messageContent += convertMessage("9",4, (*tlg)[Telegram_AANKOMST01::LadleWeight].asString());
      //m_messageContent += convertMessage("X",12,(*tlg)[Telegram_AANKOMST01::LadleOnCarTime].asString());
      //m_messageContent += convertMessage("X",1, (*tlg)[Telegram_AANKOMST01::Indicator].asString());
      //m_messageContent += convertMessage("X",2, (*tlg)[Telegram_AANKOMST01::LadleCar].asString());

      showContent((*tlg),m_typeReport,3);

      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_OutOracleTransport::LF22ToLevel3(): Could not read telegram [AANKOMST01]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),0); 
      retVal = -1;
    }
  }
  else if ( !tlg->getId().compare(std::string("STARTBEH01")) ) 
  {
    //MessageId(3009L)
    m_messageContent.clear();
    try
    {
      m_typeReport = tlg->getId();

      // HERE SOMETHING IS STILL MISSING.

      //m_messageContent = convertMessage("X",5, (*tlg)[Telegram_STARTBEH01::HeatId].asString());
      //m_messageContent += convertMessage("X",12,(*tlg)[Telegram_STARTBEH01::TreatStartTime].asString());
      //m_messageContent += convertMessage("X",7, (*tlg)[Telegram_STARTBEH01::TreatType].asString());
      //m_messageContent += convertMessage("X",1, (*tlg)[Telegram_STARTBEH01::Indicator].asString());
      //m_messageContent += convertMessage("X",1, (*tlg)[Telegram_STARTBEH01::ProdOrderId].asString());

      showContent((*tlg),m_typeReport,3);

      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_OutOracleTransport::FDBToLF22(): Could not read telegram [STARTBEH01]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),0); 
      retVal = -1;
    }
  }
  else if ( !tlg->getId().compare(std::string("EINDEBEH01")) ) 
  {
    //MessageId(3010L)
    m_messageContent.clear();
    try
    {
      m_typeReport = tlg->getId();

      // HERE SOMETHING IS STILL MISSING.

      //m_messageContent = convertMessage("X",5, (*tlg)[Telegram_EINDEBEH01::HeatId].asString());
      //m_messageContent += convertMessage("X",12,(*tlg)[Telegram_EINDEBEH01::TreatEndTime].asString());
      //m_messageContent += convertMessage("X",5, (*tlg)[Telegram_EINDEBEH01::SteelGrade].asString());
      //m_messageContent += convertMessage("X",2, (*tlg)[Telegram_EINDEBEH01::SteelGradeChange].asString());
      //m_messageContent += convertMessage("9",4, (*tlg)[Telegram_EINDEBEH01::TempMeas].asString());   
      //m_messageContent += convertMessage("X",12,(*tlg)[Telegram_EINDEBEH01::TempMeasTime].asString());
      //m_messageContent += convertMessage("9",4, (*tlg)[Telegram_EINDEBEH01::SteelWeight].asString());      
      //m_messageContent += convertMessage("9",6, (*tlg)[Telegram_EINDEBEH01::SlagWeight].asString());
      //m_messageContent += convertMessage("X",1, (*tlg)[Telegram_EINDEBEH01::Indicator].asString());
      //m_messageContent += convertMessage("9",4, (*tlg)[Telegram_EINDEBEH01::TempCalc].asString());

      showContent((*tlg),m_typeReport,3);

      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_OutOracleTransport::LF22ToLevel3(): Could not read telegram [STARTBEH01]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),0); 
      retVal = -1;
    }
  }
  else if ( !tlg->getId().compare(std::string("UPDAANVR01")) ) 
  {
    //MessageId(3011L)
    m_messageContent.clear();
    try
    {
      m_typeReport = tlg->getId();

      // HERE SOMETHING IS STILL MISSING.

      //m_messageContent  =  convertMessage("X",1,  (*tlg)[Telegram_UPDAANVR01::Flag].asString());
      //m_messageContent +=  convertMessage("X",5,  (*tlg)[Telegram_UPDAANVR01::Id].asString());     

      showContent((*tlg),m_typeReport,3);

      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_OutOracleTransport::LF22ToLevel3(): Could not read telegram [UPDAANVR01]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),0); 
      retVal = -1;
    }
  }
  else if ( !tlg->getId().compare(std::string("VERTREKP01")) ) 
  {
    //MessageId(3012L)
    m_messageContent.clear();
    try
    {
      m_typeReport = tlg->getId();

      // HERE SOMETHING IS STILL MISSING.

      //m_messageContent = convertMessage("X",1, (*tlg)[Telegram_VERTREKP01::HeatId].asString());
      //m_messageContent += convertMessage("9",3, (*tlg)[Telegram_VERTREKP01::LadleId].asString());
      //m_messageContent += convertMessage("X",12,(*tlg)[Telegram_VERTREKP01::LadleDepartTime].asString());
      //m_messageContent += convertMessage("9",4, (*tlg)[Telegram_VERTREKP01::MatWeight].asString());  
      //m_messageContent += convertMessage("X",1, (*tlg)[Telegram_VERTREKP01::Indicator].asString());     
      //m_messageContent += convertMessage("X",2, (*tlg)[Telegram_VERTREKP01::LadleCarId].asString());     

      showContent((*tlg),m_typeReport,3);

      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_OutOracleTransport::LF22ToLevel3(): Could not read telegram [VERTREKP01]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),0); 
      retVal = -1;
    }
  }
  else
  {
    std::stringstream Message;
    Message << "CTelcom_OutOracleTransport::LF22ToRAS(): No userdata found in the telegram";
    cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),1); 
    retVal = -1;
  }
  return retVal;
}

int CTelcom_OutOracleTransport::LF22ToRAS()
{
  int retVal = -1;

  // find userdata in the header, please refer to the message description
  if ( !tlg->getId().compare(std::string("LADINGEG02")) ) 
  {
    //MessageId(3013L)
    m_messageContent.clear();
    try
    {
      m_typeReport = tlg->getId();

      // HERE SOMETHING IS STILL MISSING.

      //m_messageContent = convertMessage("X",4,  (*tlg)[Telegram_LADINGEG02::MsgId].asString());
      //m_messageContent += convertMessage("X",4,  (*tlg)[Telegram_LADINGEG02::InstallationId].asString());
      //m_messageContent += convertMessage("9",4,  (*tlg)[Telegram_LADINGEG02::ProdOrderId].asString());
      //m_messageContent += convertMessage("X",5,  (*tlg)[Telegram_LADINGEG02::HeatId].asString());
      //m_messageContent += convertMessage("9",1,  (*tlg)[Telegram_LADINGEG02::TreatId].asString());
      //m_messageContent += convertMessage("9",3,  (*tlg)[Telegram_LADINGEG02::LadleId].asString());
      //m_messageContent += convertMessage("X",2,  (*tlg)[Telegram_LADINGEG02::LadleCarId].asString());
      //m_messageContent += convertMessage("9",1,  (*tlg)[Telegram_LADINGEG02::RoutePlan].asString());
      //m_messageContent += convertMessage("9",1,  (*tlg)[Telegram_LADINGEG02::RouteCur].asString());
      //m_messageContent += convertMessage("X",14, (*tlg)[Telegram_LADINGEG02::TreatStartTime].asString());
      //m_messageContent += convertMessage("X",14, (*tlg)[Telegram_LADINGEG02::TreatEndTime].asString());
      //m_messageContent += convertMessage("X",1,  (*tlg)[Telegram_LADINGEG02::ShiftNo].asString());
      //m_messageContent += convertMessage("X",254,(*tlg)[Telegram_LADINGEG02::Remark].asString());
      //m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_LADINGEG02::SteelWeightStart].asString());
      //m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_LADINGEG02::SteelWeightAim].asString());
      //m_messageContent += convertMessage("9",5,  (*tlg)[Telegram_LADINGEG02::SlagWeightStart].asString());
      //m_messageContent += convertMessage("9",5,  (*tlg)[Telegram_LADINGEG02::SlagWeightAim].asString());
      //m_messageContent += convertMessage("9",4,  (*tlg)[Telegram_LADINGEG02::SteelTempAim].asString());
      //m_messageContent += convertMessage("X",14, (*tlg)[Telegram_LADINGEG02::LadleDepartureTime].asString());
      //m_messageContent += convertMessage("9",4,  (*tlg)[Telegram_LADINGEG02::SteelTempDepart].asString());
      //m_messageContent += convertMessage("X",5,  (*tlg)[Telegram_LADINGEG02::SteelGradeAim].asString());
      //m_messageContent += convertMessage("X",5,  (*tlg)[Telegram_LADINGEG02::SteelGradePlan].asString());
      //m_messageContent += convertMessage("X",5,  (*tlg)[Telegram_LADINGEG02::SteelGradeCur].asString());
      //m_messageContent += convertMessage("X",1,  (*tlg)[Telegram_LADINGEG02::SteelPractice].asString());
      //m_messageContent += convertMessage("X",2,  (*tlg)[Telegram_LADINGEG02::SteelGradeChange].asString());
      //m_messageContent += convertMessage("9",7,  (*tlg)[Telegram_LADINGEG02::TotalEgy].asString());
      //m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_LADINGEG02::TotalPowerOnDur].asString());
      //m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_LADINGEG02::TotalArConsLance].asString());
      //m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_LADINGEG02::TotalArDurLance].asString());
      //m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_LADINGEG02::TotalN2ConsLance].asString());
      //m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_LADINGEG02::TotalN2DurLance].asString());
      //m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_LADINGEG02::TotalArConsPlug].asString());
      //m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_LADINGEG02::TotalArDurPlug].asString());
      //m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_LADINGEG02::TotalN2ConsPlug].asString());
      //m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_LADINGEG02::TotalN2DurPlug].asString());
      //m_messageContent += convertMessage("9",2,  (*tlg)[Telegram_LADINGEG02::SampleNo].asString());
      //m_messageContent += convertMessage("9",2,  (*tlg)[Telegram_LADINGEG02::ElemCounter].asString()); 

      //int MsgRepeat = CDataConversion::StringToInt((*tlg)[Telegram_LADINGEG02::ElemCounter].asString().c_str());

      //for ( long i = 0 ; i < 35; ++i ) // 35 pointed out from Corus 
      //{        
      //  m_messageContent += convertMessage("X",3, (*tlg)[Telegram_LADINGEG02::Elem]       [i].asString());
      //  m_messageContent += convertMessage("X",6, (*tlg)[Telegram_LADINGEG02::ElemConc]   [i].asString()); // X pointed out from Corus 
      //  m_messageContent += convertMessage("X",1, (*tlg)[Telegram_LADINGEG02::ElemStatus] [i].asString());      
      //}

      //m_messageContent += convertMessage("X",1, (*tlg)[Telegram_LADINGEG02::Plug1Stat].asString());
      //m_messageContent += convertMessage("X",1, (*tlg)[Telegram_LADINGEG02::Plug2Stat].asString());
      //m_messageContent += convertMessage("X",14,(*tlg)[Telegram_LADINGEG02::StirringEndTimePlug].asString());
      //m_messageContent += convertMessage("X",14,(*tlg)[Telegram_LADINGEG02::StirringEndTimeLance].asString());
      //m_messageContent += convertMessage("X",1, (*tlg)[Telegram_LADINGEG02::CaStat].asString());
      //m_messageContent += convertMessage("X",1, (*tlg)[Telegram_LADINGEG02::SlagWeightStatus].asString());
      //m_messageContent += convertMessage("9",5, (*tlg)[Telegram_LADINGEG02::SlagWeightCalcStart].asString());

      showContent((*tlg),m_typeReport,3);

      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_OutOracleTransport::LF22ToRAS(): Could not read telegram [LADINGEG02]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),0); 
      retVal = -1;
    }
  }
  else if ( !tlg->getId().compare(std::string("LADINGMG02")) ) 
  {
    //MessageId(3014L)
    m_messageContent.clear();
    try
    {
      m_typeReport = tlg->getId();

      // HERE SOMETHING IS STILL MISSING.

      //m_messageContent = convertMessage("X",4, (*tlg)[Telegram_LADINGMG02::MsgId].asString());
      //m_messageContent += convertMessage("X",4, (*tlg)[Telegram_LADINGMG02::InstallationId].asString());
      //m_messageContent += convertMessage("9",4, (*tlg)[Telegram_LADINGMG02::ProdOrderId].asString());
      //m_messageContent += convertMessage("X",5, (*tlg)[Telegram_LADINGMG02::HeatId].asString());
      //m_messageContent += convertMessage("9",1, (*tlg)[Telegram_LADINGMG02::TreatId].asString());
      //m_messageContent += convertMessage("9",2, (*tlg)[Telegram_LADINGMG02::SampleCounter].asString());

      //int MsgRepeat = CDataConversion::StringToInt( (*tlg)[Telegram_LADINGMG02::SampleCounter].asString().c_str() );

      //for ( long i = 0 ; i < MsgRepeat ; ++i )
      //{        
      //  m_messageContent += convertMessage("X",14, (*tlg)[Telegram_LADINGMG02::SampleTime]     [i].asString());
      //  m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_LADINGMG02::TempMeas]       [i].asString());
      //  m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_LADINGMG02::TempCalc]       [i].asString());
      //  m_messageContent += convertMessage("X",3,  (*tlg)[Telegram_LADINGMG02::Freeboard]      [i].asString());
      //  m_messageContent += convertMessage("X",6,  (*tlg)[Telegram_LADINGMG02::SteelAcivityO2] [i].asString());
      //  m_messageContent += convertMessage("X",6,  (*tlg)[Telegram_LADINGMG02::AlConc]         [i].asString());      
      //  m_messageContent += convertMessage("X",4,  (*tlg)[Telegram_LADINGMG02::EMK]            [i].asString());
      //  m_messageContent += convertMessage("X",5,  (*tlg)[Telegram_LADINGMG02::SlagActivityO2] [i].asString());
      //}

      showContent((*tlg),m_typeReport,3);

      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_OutOracleTransport::LF22ToRAS(): Could not read telegram [LADINGMG01]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),0); 
      retVal = -1;
    }
  }
  else if ( !tlg->getId().compare(std::string("LADINGTG03")) ) 
  {
    //MessageId(3015L)
    m_messageContent.clear();
    try
    {
      m_typeReport = tlg->getId();

      // HERE SOMETHING IS STILL MISSING.

      //m_messageContent = convertMessage("X",4, (*tlg)[Telegram_LADINGTG03::MsgId].asString());
      //m_messageContent += convertMessage("X",4, (*tlg)[Telegram_LADINGTG03::InstallationId].asString());
      //m_messageContent += convertMessage("9",4, (*tlg)[Telegram_LADINGTG03::ProdOrderId].asString());
      //m_messageContent += convertMessage("X",5, (*tlg)[Telegram_LADINGTG03::HeatId].asString());
      //m_messageContent += convertMessage("9",1, (*tlg)[Telegram_LADINGTG03::TreatId].asString());
      //m_messageContent += convertMessage("9",2, (*tlg)[Telegram_LADINGTG03::AdditionCounter].asString());

      //int MsgRepeat = CDataConversion::StringToInt( (*tlg)[Telegram_LADINGTG03::AdditionCounter].asString().c_str() );

      //for ( long i = 0 ; i < MsgRepeat ; ++i )
      //{        
      //  m_messageContent += convertMessage("X",6,  (*tlg)[Telegram_LADINGTG03::MaterialCode]           [i].asString());
      //  m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_LADINGTG03::MaterialWeightCalc]     [i].asString());        
      //  m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_LADINGTG03::MaterialWeightRequest]  [i].asString());
      //  m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_LADINGTG03::MaterialWeightReport]   [i].asString());
      //  m_messageContent += convertMessage("X",14, (*tlg)[Telegram_LADINGTG03::AdditionTime]           [i].asString());
      //  m_messageContent += convertMessage("X",3,  (*tlg)[Telegram_LADINGTG03::MaterialDevice]         [i].asString());        
      //}

      showContent((*tlg),m_typeReport,3);

      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_OutOracleTransport::LF22ToRAS(): Could not read telegram [LADINGMG01]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),0); 
      retVal = -1;
    }
  }
  else if ( !tlg->getId().compare(std::string("LADINGBW02")) ) 
  {
    //MessageId(3016L)
    m_messageContent.clear();
    try
    {
      m_typeReport = tlg->getId();

      // HERE SOMETHING IS STILL MISSING.

      //m_messageContent = convertMessage("X",4, (*tlg)[Telegram_LADINGBW02::MsgId].asString());
      //m_messageContent += convertMessage("X",4, (*tlg)[Telegram_LADINGBW02::InstallationId].asString());
      //m_messageContent += convertMessage("9",4, (*tlg)[Telegram_LADINGBW02::ProdOrderId].asString());
      //m_messageContent += convertMessage("X",5, (*tlg)[Telegram_LADINGBW02::HeatId].asString());
      //m_messageContent += convertMessage("9",1, (*tlg)[Telegram_LADINGBW02::TreatId].asString());
      //m_messageContent += convertMessage("9",2, (*tlg)[Telegram_LADINGBW02::StepCounter].asString());

      //int MsgRepeat = CDataConversion::StringToInt( (*tlg)[Telegram_LADINGBW02::StepCounter].asString().c_str() );

      //for ( long i = 0 ; i < MsgRepeat ; ++i )
      //{        
      //  m_messageContent += convertMessage("X",20, (*tlg)[Telegram_LADINGBW02::StepId]         [i].asString());
      //  m_messageContent += convertMessage("X",14, (*tlg)[Telegram_LADINGBW02::StepStartTime]  [i].asString());
      //  m_messageContent += convertMessage("X",7,  (*tlg)[Telegram_LADINGBW02::Energy]         [i].asString());
      //  m_messageContent += convertMessage("X",6,  (*tlg)[Telegram_LADINGBW02::PowerOnDur]     [i].asString());
      //  m_messageContent += convertMessage("X",6,  (*tlg)[Telegram_LADINGBW02::ArConsLance]    [i].asString());
      //  m_messageContent += convertMessage("X",6,  (*tlg)[Telegram_LADINGBW02::N2ConsLance]    [i].asString());
      //  m_messageContent += convertMessage("X",6,  (*tlg)[Telegram_LADINGBW02::ArConsPlug1]    [i].asString());      
      //  m_messageContent += convertMessage("X",6,  (*tlg)[Telegram_LADINGBW02::ArConsPlug2]    [i].asString());
      //  m_messageContent += convertMessage("X",6,  (*tlg)[Telegram_LADINGBW02::N2ConsPlug]     [i].asString());
      //  m_messageContent += convertMessage("X",3,  (*tlg)[Telegram_LADINGBW02::ArPressPlug1]   [i].asString());
      //  m_messageContent += convertMessage("X",3,  (*tlg)[Telegram_LADINGBW02::ArPressPlug2]   [i].asString());
      //}

      showContent((*tlg),m_typeReport,3);

      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_OutOracleTransport::LF22ToRAS(): Could not read telegram [LADINGBW01]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),0); 
      retVal = -1;
    }
  }
  else if ( !tlg->getId().compare(std::string("LADINGVT02")) ) 
  {
    //MessageId(3017L)
    m_messageContent.clear();
    try
    {
      m_typeReport = tlg->getId();

      // HERE SOMETHING IS STILL MISSING.

      //m_messageContent = convertMessage("X",4, (*tlg)[Telegram_LADINGVT02::MsgId].asString());
      //m_messageContent += convertMessage("X",4, (*tlg)[Telegram_LADINGVT02::InstallationId].asString());
      //m_messageContent += convertMessage("9",4, (*tlg)[Telegram_LADINGVT02::ProdOrderId].asString());
      //m_messageContent += convertMessage("X",5, (*tlg)[Telegram_LADINGVT02::HeatId].asString());
      //m_messageContent += convertMessage("9",1, (*tlg)[Telegram_LADINGVT02::TreatId].asString());
      //m_messageContent += convertMessage("9",2, (*tlg)[Telegram_LADINGVT02::DelayCounter].asString());

      //int MsgRepeat = CDataConversion::StringToInt( (*tlg)[Telegram_LADINGVT02::DelayCounter].asString().c_str() );

      //for ( long i = 0 ; i < MsgRepeat ; ++i )
      //{        
      //   m_messageContent += convertMessage("X",14,  (*tlg)[Telegram_LADINGVT02::DelayStartTime] [i].asString());
      //   m_messageContent += convertMessage("X",14,  (*tlg)[Telegram_LADINGVT02::DelayEndTime]   [i].asString());
      //   m_messageContent += convertMessage("X",10,  (*tlg)[Telegram_LADINGVT02::DelayCode]      [i].asString());
      //   m_messageContent += convertMessage("X",80,  (*tlg)[Telegram_LADINGVT02::DelayNote]      [i].asString());
      //}

      showContent((*tlg),m_typeReport,3);

      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_OutOracleTransport::LF22ToRAS(): Could not read telegram [LADINGVT01]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),0); 
      retVal = -1;
    }
  }
  else if ( !tlg->getId().compare(std::string("LADINGMT02")) ) 
  {
    //MessageId(3018L)
    m_messageContent.clear();
    try
    {
      m_typeReport = tlg->getId();

      // HERE SOMETHING IS STILL MISSING.

      //m_messageContent = convertMessage("X",4, (*tlg)[Telegram_LADINGMT02::MsgId].asString());
      //m_messageContent += convertMessage("X",4, (*tlg)[Telegram_LADINGMT02::InstallationId].asString());
      //m_messageContent += convertMessage("9",4, (*tlg)[Telegram_LADINGMT02::ProdOrderId].asString());
      //m_messageContent += convertMessage("X",5, (*tlg)[Telegram_LADINGMT02::HeatId].asString());
      //m_messageContent += convertMessage("9",1, (*tlg)[Telegram_LADINGMT02::TreatId].asString());
      //m_messageContent += convertMessage("9",2, (*tlg)[Telegram_LADINGMT02::SampleCounter].asString());

      //int MsgRepeat = CDataConversion::StringToInt( (*tlg)[Telegram_LADINGMT02::SampleCounter].asString().c_str() );

      //for ( long i = 0 ; i < MsgRepeat ; ++i )
      //{        
      //  m_messageContent += convertMessage("X",2, (*tlg)[Telegram_LADINGMT02::SampleNo]       [i].asString());
      //  m_messageContent += convertMessage("X",14,(*tlg)[Telegram_LADINGMT02::SampleTime]     [i].asString());
      //}
      
      showContent((*tlg),m_typeReport,3);
      
      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_OutOracleTransport::LF22ToRAS(): Could not read telegram [LADINGMT01]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),0); 
      retVal = -1;
    }
  }
  else if ( !tlg->getId().compare(std::string("LADINGUP03")) )
  {
    //MessageId(3019L)
    m_messageContent.clear();
    try
    {
      m_typeReport = tlg->getId();

      // HERE SOMETHING IS STILL MISSING.

      //m_messageContent = convertMessage("X",4,   (*tlg)[Telegram_LADINGUP03::MsgId].asString());
      //m_messageContent += convertMessage("X",4,   (*tlg)[Telegram_LADINGUP03::InstallationId].asString());
      //m_messageContent += convertMessage("X",5,   (*tlg)[Telegram_LADINGUP03::HeatId].asString());
      //m_messageContent += convertMessage("9",1,   (*tlg)[Telegram_LADINGUP03::TreatId].asString());
      //m_messageContent += convertMessage("9",14,  (*tlg)[Telegram_LADINGUP03::Date].asString());
      //m_messageContent += convertMessage("X",254, (*tlg)[Telegram_LADINGUP03::Remark].asString());
      //m_messageContent += convertMessage("X",21,  (*tlg)[Telegram_LADINGUP03::Filler].asString());

      showContent((*tlg),m_typeReport,3);

      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_OutOracleTransport::LF22ToRAS(): Could not read telegram [LADINGUP02]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),0); 
      retVal = -1;
    }     
  }
  else
  {
    std::stringstream Message;
    Message << "CTelcom_OutOracleTransport::LF22ToRAS(): No userdata found in the telegram";
    cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),1); 
    retVal = -1;
  }
  return retVal;
}// int CTelcom_OutOracleTransport::LF22ToRAS()


int CTelcom_OutOracleTransport::LF22ToGWI()
{
  int retVal = -1;

  // find userdata in the header, please refer to the message description
  if ( !tlg->getId().compare(std::string("LADINGIF02")) ) 
  {
    //MessageId(3025L)
    m_messageContent.clear();
    try
    {
      m_typeReport = tlg->getId();

      // HERE SOMETHING IS STILL MISSING.

     // m_messageContent = convertMessage("X",5, (*tlg)[Telegram_LADINGIF02::HeatId].asString());
     // m_messageContent += convertMessage("9",4, (*tlg)[Telegram_LADINGIF02::ProdOrderId].asString());
     // m_messageContent += convertMessage("X",12,(*tlg)[Telegram_LADINGIF02::TreatEndTime].asString());
     // m_messageContent += convertMessage("9",4, (*tlg)[Telegram_LADINGIF02::TempMeas].asString());
     // m_messageContent += convertMessage("X",12,(*tlg)[Telegram_LADINGIF02::TempMeasTime].asString());
     // m_messageContent += convertMessage("X",1, (*tlg)[Telegram_LADINGIF02::CaStatus].asString());
     // m_messageContent += convertMessage("9",3, (*tlg)[Telegram_LADINGIF02::LadleId].asString());
     // m_messageContent += convertMessage("X",5, (*tlg)[Telegram_LADINGIF02::SteelGradeEnd].asString());
     // m_messageContent += convertMessage("X",2, (*tlg)[Telegram_LADINGIF02::SteelGradeChange].asString());
     // m_messageContent += convertMessage("X",2, (*tlg)[Telegram_LADINGIF02::Counter].asString());

     //int MsgRepeat = CDataConversion::StringToInt( (*tlg)[Telegram_LADINGIF02::Counter].asString().c_str() );

     //for ( long i = 0 ; i < MsgRepeat ; ++i )
     //{        
     //  m_messageContent += convertMessage("X",3,  (*tlg)[Telegram_LADINGIF02::Name]          [i].asString());
     //  m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_LADINGIF02::Concentration] [i].asString());
     //  m_messageContent += convertMessage("X",1,  (*tlg)[Telegram_LADINGIF02::Status]        [i].asString());
     //}
         
     showContent((*tlg),m_typeReport,3);

     retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_OutOracleTransport::LF22ToGWI(): Could not read telegram [LADINGIF02]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),0); 
      retVal = -1;
    }     
  }
  else
  {
    std::stringstream Message;
    Message << "CTelcom_OutOracleTransport::LF22ToGWI(): No userdata found in the telegram";
    cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),1); 
    retVal = -1;
  }
  return retVal;
}// int CTelcom_OutOracleTransport::LF22ToGWI()

int CTelcom_OutOracleTransport::LF22ToFDB()
{
  int retVal = -1;

  // find userdata in the header, please refer to the message description
  if ( !tlg->getId().compare(std::string("AANKMSTP02")) ) 
  {
    //MessageId(3027L)
    m_messageContent.clear();
    try
    {
      m_typeReport = tlg->getId(); 

      // HERE SOMETHING IS STILL MISSING.

      //m_messageContent = convertMessage("X",5, (*tlg)[Telegram_AANKMSTP02::HeatId].asString());
      //m_messageContent += convertMessage("9",1, (*tlg)[Telegram_AANKMSTP02::TreatId].asString());
      //m_messageContent += convertMessage("9",2, (*tlg)[Telegram_AANKMSTP02::Installation].asString());  
      //m_messageContent += convertMessage("9",3, (*tlg)[Telegram_AANKMSTP02::LadleId].asString());  
      //m_messageContent += convertMessage("X",2, (*tlg)[Telegram_AANKMSTP02::LadleCarId].asString());  
      //m_messageContent += convertMessage("X",14,(*tlg)[Telegram_AANKMSTP02::TreatStartTime].asString());  
      //m_messageContent += convertMessage("X",1, (*tlg)[Telegram_AANKMSTP02::Shift].asString());  
      //m_messageContent += convertMessage("9",4, (*tlg)[Telegram_AANKMSTP02::ProdOrderId].asString());  
      //m_messageContent += convertMessage("9",4, (*tlg)[Telegram_AANKMSTP02::TreatStartTemp].asString());  

      showContent((*tlg),m_typeReport,3);

      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_OutOracleTransport::LF22ToFDB(): Could not read telegram [AANKMSTP02]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),0); 
      retVal = -1;
    } 
  }
  else if ( !tlg->getId().compare(std::string("ONDERKAP02")) ) 
  {
    //MessageId(3028L)
    m_messageContent.clear();
    try
    {
      m_typeReport = tlg->getId();

      // HERE SOMETHING IS STILL MISSING.

      //m_messageContent = convertMessage("X",5, (*tlg)[Telegram_ONDERKAP02::HeatId].asString());
      //m_messageContent += convertMessage("9",1, (*tlg)[Telegram_ONDERKAP02::TreatId].asString());
      //m_messageContent += convertMessage("X",14,(*tlg)[Telegram_ONDERKAP02::Time].asString());  
      //m_messageContent += convertMessage("9",4, (*tlg)[Telegram_ONDERKAP02::TreatStartTemp].asString());  

      showContent((*tlg),m_typeReport,3);

      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_OutOracleTransport::LF22ToFDB(): Could not read telegram [ONDERKAP02]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),0); 
      retVal = -1;
    } 
  }
  else if ( !tlg->getId().compare(std::string("BUITNKAP02")) ) 
  {
    //MessageId(3029L)
    m_messageContent.clear();
    try
    {
      m_typeReport = tlg->getId();

      // HERE SOMETHING IS STILL MISSING.

      //m_messageContent = convertMessage("X",5, (*tlg)[Telegram_BUITNKAP02::HeatId].asString());
      //m_messageContent += convertMessage("9",1, (*tlg)[Telegram_BUITNKAP02::TreatId].asString());
      //m_messageContent += convertMessage("X",14,(*tlg)[Telegram_BUITNKAP02::Time].asString());  
      //m_messageContent += convertMessage("9",4, (*tlg)[Telegram_BUITNKAP02::TreatEndTemp].asString());

      showContent((*tlg),m_typeReport,3);

      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_OutOracleTransport::LF22ToFDB(): Could not read telegram [BUITNKAP02]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),0); 
      retVal = -1;
    } 
  }
  else if ( !tlg->getId().compare(std::string("VERTRKPN02")) ) 
  {
    //MessageId(3030L)
    m_messageContent.clear();
    try
    {
      m_typeReport = tlg->getId();

      // HERE SOMETHING IS STILL MISSING.

      //m_messageContent = convertMessage("X",5,  (*tlg)[Telegram_VERTRKPN02::HeatId].asString());
      //m_messageContent += convertMessage("9",1,  (*tlg)[Telegram_VERTRKPN02::TreatId].asString());
      //m_messageContent += convertMessage("X",14, (*tlg)[Telegram_VERTRKPN02::TreatEndTime].asString());
      //m_messageContent += convertMessage("9",2,  (*tlg)[Telegram_VERTRKPN02::CraneNo].asString());
      //m_messageContent += convertMessage("9",4,  (*tlg)[Telegram_VERTRKPN02::TreatEndTemp].asString());
      //m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_VERTRKPN02::StirrTimeTotal].asString());
      //m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_VERTRKPN02::SteelWeightStart].asString());
      //m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_VERTRKPN02::SteelWeightEnd].asString());
      //m_messageContent += convertMessage("9",5,  (*tlg)[Telegram_VERTRKPN02::SlagWeightStart].asString());
      //m_messageContent += convertMessage("9",5,  (*tlg)[Telegram_VERTRKPN02::SlagWeightEnd].asString());
      //m_messageContent += convertMessage("X",5,  (*tlg)[Telegram_VERTRKPN02::SteelGradeEnd].asString());
      //m_messageContent += convertMessage("X",2,  (*tlg)[Telegram_VERTRKPN02::SteelGradeChange].asString());
      //m_messageContent += convertMessage("X",254,(*tlg)[Telegram_VERTRKPN02::Remark].asString());
      //m_messageContent += convertMessage("9",7,  (*tlg)[Telegram_VERTRKPN02::Energy].asString());
      //m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_VERTRKPN02::PowerOnDur].asString());
      //m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_VERTRKPN02::ArConsLance].asString());
      //m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_VERTRKPN02::ArStirrDurationLance].asString());
      //m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_VERTRKPN02::N2ConsLance].asString());
      //m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_VERTRKPN02::N2StirrDurationLance].asString());
      //m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_VERTRKPN02::ArConsPlug].asString());
      //m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_VERTRKPN02::ArStirrDurationPlug].asString());
      //m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_VERTRKPN02::N2ConsPlug].asString());
      //m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_VERTRKPN02::N2StirrDurationPlug].asString());
      //m_messageContent += convertMessage("X",1,  (*tlg)[Telegram_VERTRKPN02::Plug1Stat].asString());
      //m_messageContent += convertMessage("X",1,  (*tlg)[Telegram_VERTRKPN02::Plug2Stat].asString());      
      //m_messageContent += convertMessage("X",14, (*tlg)[Telegram_VERTRKPN02::StirringEndTimePlug].asString());
      //m_messageContent += convertMessage("X",14, (*tlg)[Telegram_VERTRKPN02::StirringEndTimeLance].asString());
      //m_messageContent += convertMessage("9",4,  (*tlg)[Telegram_VERTRKPN02::TreatEndTempAim].asString());
      //m_messageContent += convertMessage("X",14, (*tlg)[Telegram_VERTRKPN02::TreatEndTimeAim].asString());      
      //m_messageContent += convertMessage("9",4,  (*tlg)[Telegram_VERTRKPN02::HandOverTemp].asString());
      //m_messageContent += convertMessage("9",14, (*tlg)[Telegram_VERTRKPN02::HandOverTime].asString());
      //m_messageContent += convertMessage("9",3,  (*tlg)[Telegram_VERTRKPN02::CastingStartTime].asString());
      //m_messageContent += convertMessage("9",1,  (*tlg)[Telegram_VERTRKPN02::RoutePlan].asString());
      //m_messageContent += convertMessage("X",14, (*tlg)[Telegram_VERTRKPN02::LastCalcTime].asString());
      //m_messageContent += convertMessage("X",1,  (*tlg)[Telegram_VERTRKPN02::CaStat].asString());        

      showContent((*tlg),m_typeReport,3);

      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_OutOracleTransport::LF22ToFDB(): Could not read telegram [BUITNKAP02]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),0); 
      retVal = -1;
    }
  }
  else if ( !tlg->getId().compare(std::string("MONSTRGG02")) ) 
  {
    //MessageId(3031L)
    m_messageContent.clear();
    try
    {
      m_typeReport = tlg->getId();

      // HERE SOMETHING IS STILL MISSING.

      //m_messageContent = convertMessage("X",5, (*tlg)[Telegram_MONSTRGG02::HeatId].asString());
      //m_messageContent += convertMessage("9",1, (*tlg)[Telegram_MONSTRGG02::TreatId].asString());
      //m_messageContent += convertMessage("X",14,(*tlg)[Telegram_MONSTRGG02::TimeMeas].asString());
      //m_messageContent += convertMessage("9",6,(*tlg)[Telegram_MONSTRGG02::TempMeas].asString());
      //m_messageContent += convertMessage("9",6, (*tlg)[Telegram_MONSTRGG02::TempCalc].asString());
      //m_messageContent += convertMessage("X",3, (*tlg)[Telegram_MONSTRGG02::Freeboard].asString());
      //m_messageContent += convertMessage("X",6, (*tlg)[Telegram_MONSTRGG02::SteelAcivityO2].asString());
      //m_messageContent += convertMessage("X",6, (*tlg)[Telegram_MONSTRGG02::AlConc].asString());
      //m_messageContent += convertMessage("X",4, (*tlg)[Telegram_MONSTRGG02::EMK].asString());
      //m_messageContent += convertMessage("X",5, (*tlg)[Telegram_MONSTRGG02::SlagActivityO2].asString());               

      showContent((*tlg),m_typeReport,3);

      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_OutOracleTransport::LF22ToFDB(): Could not read telegram [MONSTRGG02]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),0); 
      retVal = -1;
    }
  }
  else if ( !tlg->getId().compare(std::string("PROCESGG01")) ) 
  {
    //MessageId(3032L)
    m_messageContent.clear();
    try
    {
      m_typeReport = tlg->getId();

      // HERE SOMETHING IS STILL MISSING.

      //m_messageContent = convertMessage("X",5, (*tlg)[Telegram_PROCESGG01::HeatId].asString());
      //m_messageContent += convertMessage("9",1, (*tlg)[Telegram_PROCESGG01::TreatId].asString());
      //m_messageContent += convertMessage("9",2, (*tlg)[Telegram_PROCESGG01::StepCounter].asString());

      //int MsgRepeat = CDataConversion::StringToInt( (*tlg)[Telegram_PROCESGG01::StepCounter].asString().c_str() );

      //for ( long i = 0 ; i < MsgRepeat ; ++i )
      //{        
      //  m_messageContent += convertMessage("X",20, (*tlg)[Telegram_PROCESGG01::StepId]                 [i].asString());
      //  m_messageContent += convertMessage("X",14, (*tlg)[Telegram_PROCESGG01::StepStartTime]          [i].asString());   
      //  m_messageContent += convertMessage("X",14, (*tlg)[Telegram_PROCESGG01::StepEndTime]            [i].asString());   
      //  m_messageContent += convertMessage("9",7,  (*tlg)[Telegram_PROCESGG01::Energy]                 [i].asString());   
      //  m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_PROCESGG01::PowerOnDur]             [i].asString());   
      //  m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_PROCESGG01::ArConsLance]            [i].asString());   
      //  m_messageContent += convertMessage("9",4,  (*tlg)[Telegram_PROCESGG01::ArStirrDurationLance]   [i].asString());   
      //  m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_PROCESGG01::N2ConsLance]            [i].asString());   
      //  m_messageContent += convertMessage("9",4,  (*tlg)[Telegram_PROCESGG01::N2StirrDurationLance]   [i].asString());   
      //  m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_PROCESGG01::ArConsPlug1]            [i].asString());   
      //  m_messageContent += convertMessage("9",3,  (*tlg)[Telegram_PROCESGG01::ArPressPlug1]           [i].asString());   
      //  m_messageContent += convertMessage("9",4,  (*tlg)[Telegram_PROCESGG01::ArStirrDurationPlug1]   [i].asString());   
      //  m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_PROCESGG01::ArConsPlug2]            [i].asString());
      //  m_messageContent += convertMessage("9",3,  (*tlg)[Telegram_PROCESGG01::ArPressPlug2]           [i].asString());   
      //  m_messageContent += convertMessage("9",4,  (*tlg)[Telegram_PROCESGG01::ArStirrDurationPlug2]   [i].asString());   
      //  m_messageContent += convertMessage("9",6,  (*tlg)[Telegram_PROCESGG01::N2ConsPlug]             [i].asString());   
      //  m_messageContent += convertMessage("9",4,  (*tlg)[Telegram_PROCESGG01::N2StirrDurationPlug]    [i].asString());   
      //}

      showContent((*tlg),m_typeReport,3);

      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_OutOracleTransport::LF22ToFDB(): Could not read telegram [PROCESGG01]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),0); 
      retVal = -1;
    }
  }
  else if ( !tlg->getId().compare(std::string("DOSEERGG04")) ) 
  {
    //MessageId(3033L)
    m_messageContent.clear();
    try
    {
      m_typeReport = tlg->getId();

      //m_messageContent = convertMessage("X",5, (*tlg)[Telegram_DOSEERGG04::HeatId].asString());
      //m_messageContent += convertMessage("9",1, (*tlg)[Telegram_DOSEERGG04::TreatId].asString());
      //m_messageContent += convertMessage("9",2, (*tlg)[Telegram_DOSEERGG04::AdditionCounter].asString());

      //int MsgRepeat = CDataConversion::StringToInt( (*tlg)[Telegram_DOSEERGG04::AdditionCounter].asString().c_str() );
     
      //for ( long i = 0 ; i < MsgRepeat ; ++i )
      //{        
      //  m_messageContent += convertMessage("X",14,  (*tlg)[Telegram_DOSEERGG04::AdditionTime]         [i].asString());
      //  m_messageContent += convertMessage("X",2,   (*tlg)[Telegram_DOSEERGG04::MaterialCode]         [i].asString());
      //  m_messageContent += convertMessage("X",20,  (*tlg)[Telegram_DOSEERGG04::MaterialName]         [i].asString());
      //  m_messageContent += convertMessage("9",6,   (*tlg)[Telegram_DOSEERGG04::MaterialWeightCalc]   [i].asString());
      //  m_messageContent += convertMessage("9",6,   (*tlg)[Telegram_DOSEERGG04::MaterialWeightCharged][i].asString());
      //  m_messageContent += convertMessage("9",6,   (*tlg)[Telegram_DOSEERGG04::TempCalc]             [i].asString());
      //  m_messageContent += convertMessage("X",2,   (*tlg)[Telegram_DOSEERGG04::WireFeederNo]         [i].asString());
      //}

      showContent((*tlg),m_typeReport,3);

      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_OutOracleTransport::LF22ToFDB(): Could not read telegram " << m_typeReport;
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),0); 
      retVal = -1;
    }
  }
  else if ( !tlg->getId().compare(std::string("VERWRMGG01")) ) 
  {
    //MessageId(3034L)
    m_messageContent.clear();
    try
    {
      m_typeReport = tlg->getId();

      // HERE SOMETHING IS STILL MISSING.

      //m_messageContent = convertMessage("X",5, (*tlg)[Telegram_VERWRMGG01::HeatId].asString());
      //m_messageContent += convertMessage("9",1, (*tlg)[Telegram_VERWRMGG01::TreatId].asString());
      //m_messageContent += convertMessage("9",2, (*tlg)[Telegram_VERWRMGG01::HeatingCounter].asString());

      //int MsgRepeat = CDataConversion::StringToInt( (*tlg)[Telegram_VERWRMGG01::HeatingCounter].asString().c_str() );
      //long HeatingCounter = 1;

      //if ( MsgRepeat > 0 )
      //{
      //  for ( long i = 0 ; i < 99 ; ++i )
      //  { 
      //    m_messageContent += convertMessage("X",14,  (*tlg)[Telegram_VERWRMGG01::HeatingOnTime]      [i].asString());
      //    m_messageContent += convertMessage("9",4,   (*tlg)[Telegram_VERWRMGG01::HeatingOnTemp]      [i].asString());
      //    m_messageContent += convertMessage("X",14,  (*tlg)[Telegram_VERWRMGG01::HeatingOffTime]     [i].asString());
      //    m_messageContent += convertMessage("9",4,   (*tlg)[Telegram_VERWRMGG01::HeatingOffTemp]     [i].asString());
      //    m_messageContent += convertMessage("9",2,   (*tlg)[Telegram_VERWRMGG01::StepCounter]        [i].asString());

      //    int StepRepeat = CDataConversion::StringToInt( (*tlg)[Telegram_VERWRMGG01::StepCounter]     [i].asString().c_str() );

      //    if ( StepRepeat == 0 )
      //    {
      //      // StepRepeat is 00 then fill with spaces 
      //      //m_messageContent += convertMessage("X",22,   (*tlg)[Telegram_VERWRMGG01::ElecTapCh]         [i].asString());
      //    }
      //    else
      //    {
      //      for ( long ii = 0 ; ii < (StepRepeat); ++ii )
      //      {  
      //        m_messageContent += convertMessage("X",22,   (*tlg)[Telegram_VERWRMGG01::ElecTapCh]         [i+ii].asString());                      
      //      }
      //      i=i+(StepRepeat-1);      
      //    }

      //    if ( MsgRepeat == HeatingCounter )
      //    {
      //      break;
      //    }

      //    HeatingCounter++;

      //    // ElecTapCh is a special string and contains the following
      //    //m_messageContent += convertMessage("X",14,  (*tlg)[Telegram_VERWRMGG01::TapChangeTime]      [i].asString());
      //    //m_messageContent += convertMessage("9",2,   (*tlg)[Telegram_VERWRMGG01::TapPositionNew]     [i].asString());
      //    //m_messageContent += convertMessage("9",2,   (*tlg)[Telegram_VERWRMGG01::TapPositionCurr]    [i].asString());
      //    //m_messageContent += convertMessage("9",4,   (*tlg)[Telegram_VERWRMGG01::TempCalc]           [i].asString());
      //  }
      //}

      showContent((*tlg),m_typeReport,3);

      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_OutOracleTransport::LF22ToFDB(): Could not read telegram [VERWRMGG01]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),0); 
      retVal = -1;
    }
  }
  else if ( !tlg->getId().compare(std::string("EINDTIJD01")) ) 
  {
    //MessageId(3035L)
    m_messageContent.clear();
    try
    {
      m_typeReport = tlg->getId();

      // HERE SOMETHING IS STILL MISSING.

      //m_messageContent = convertMessage("9",4,  (*tlg)[Telegram_EINDTIJD01::ProdOrderId].asString());
      //m_messageContent += convertMessage("9",14, (*tlg)[Telegram_EINDTIJD01::TreatEndTime].asString());

      showContent((*tlg),m_typeReport,3);

      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_OutOracleTransport::LF22ToFDB(): Could not read telegram [EINDTIJD01]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),0); 
      retVal = -1;
    }
  }
  else
  {
    std::stringstream Message;
    Message << "CTelcom_OutOracleTransport::LF22ToFDB(): No userdata found in the telegram";
    cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),1); 
    retVal = -1;
  }

  if(retVal == -1)
  {
    std::stringstream Message;
    Message << "CTelcom_OutOracleTransport::LF22ToFDB(); No userdata found";
    cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(),1); 
  }

  return retVal;
}

std::string CTelcom_OutOracleTransport::convertMessage(std::string messageFormat, int maxLength, std::string fieldMessage)
{
  std::string message = "";
  int messageLength = fieldMessage.length();

  // if the maximum length of message is too short
  if (maxLength < messageLength)
  {
    maxLength = messageLength;
  }   

  // 9 = numeric characters (left padded 0) "interger"
  if( !(messageFormat.compare("9")) )
  {
    if(maxLength == messageLength)
    {
      message = fieldMessage;
    }   
    else if (maxLength > messageLength)
    {
      int spacing = maxLength - messageLength;
      message = fieldMessage;

      for(int index=0; index < spacing; index++)
      {
        message = message.insert(0,"0");
      } 
    } 
  } // if( !(messageFormat.compare("9").length())

  // x = alphanumeric characters (right padded blanks) "string" 
  else if( !(messageFormat.compare("X")) )
  {
    if(maxLength == messageLength)
    {
      message = fieldMessage;
    }   
    else if (maxLength > messageLength)
    {
      int spacing = maxLength - messageLength;
      message = fieldMessage;

      for(int index=0; index < spacing; index++)
      {
        message = message.insert(message.length()," ");
      } 
    }
  } // if( !(messageFormat.compare("X").length())
  else
  {
    message = " ";
    for(int index=0; index < maxLength; index++)
    {
      message += message; 
    } 
  }

  return message;
}

// returns M12 = YYYYMMDDhhmm i.e. 200801310915
std::string CTelcom_OutOracleTransport::SMSDateToM12(std::string SMString)
{
  CDateTime now(SMString);
  long test = now.getYear();

  // HERE SOMETHING IS STILL MISSING. LOOKS LIKE

  std::string M12 = "YYYYMMDDhhmm";

  return M12;
}

