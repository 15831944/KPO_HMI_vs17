#include <vector>

#include "Telcom_In_s.hh"

#include "cCBS_StdLog_Task.h"
#include "CSMC_EventLogFrameController.h"

#include "CTelcom_InTask.h"
#include "CTelcom_InMsgTypeTranslator.h"

#include "CTelcom_InOracleTransport.h"
#include "CDataConversion.h"


//##ModelId=45AB96E8003D
CTelcom_InOracleTransport::CTelcom_InOracleTransport()
: CTelcom_OracleTransport()
{
  m_fieldIterations = 99; 
  m_pStoredFunction = new CTelcom_OdbcStoredFunction();
}

//##ModelId=45AB96E801C3
CTelcom_InOracleTransport::~CTelcom_InOracleTransport()
{
  try
  {
    if (m_pStoredFunction) 
    {
      delete m_pStoredFunction;
      m_pStoredFunction = 0;
    }
  }
  catch(cCBS_DBExc &e) 
  {
    std::cout << e.getText() << std::endl;
  }  
}

void CTelcom_InOracleTransport::configure(const std::string & section, bas::Configuration & c)
{
  // execute the configuration of the base class:
  CTelcom_OracleTransport::configure(section, c);

  try
  {
    if ( m_pStoredFunction->ODBCConnection() )
    {
      CTelcom_InTask::getInstance()->setWorking(true);
    }
  }
  catch(cCBS_DBExc &e) 
  {
    std::cout << e.getText() << std::endl;
  }  
}

int CTelcom_InOracleTransport::doConnect()
{
  // -1 indicates timeout, 0 means "Connected.
  int retval = -1;  

  // must be called first, in order that thread sleep 1s
  retval = CTelcom_OracleTransport::doConnect(); 

  p_poort = "ORA";
  p_timeout = 2;

  cCBS_StdInitBase *pStdInitBase = cCBS_StdInitBase::getInstance();

  if( !( pStdInitBase->getEntry("SMS_Transport", "poort", p_poort) &&   
         pStdInitBase->getEntry("SMS_Transport", "timeout", p_timeout) ) )
  {
    std::cerr << "Can not read input settings from ini-file" << std::endl;
  }

  p_Proco2 = "Proco2";
  p_FDB = "FDB";
  p_BOF = "BOF";
  p_Sparcs = "Sparcs";
  p_Samtracs = "Samtracs";

  if( !( pStdInitBase->getEntry("SMS_Transport", "Proco2", p_Proco2) &&
    pStdInitBase->getEntry("SMS_Transport", "FDB", p_FDB) &&
    pStdInitBase->getEntry("SMS_Transport", "BOF", p_BOF) &&
    pStdInitBase->getEntry("SMS_Transport", "Sparcs", p_Sparcs) &&
    pStdInitBase->getEntry("SMS_Transport", "Samtracs", p_Samtracs) ) )
  {
    std::cerr << "Can not read sender settings from ini-file" << std::endl;
  }

  return retval;
}

int CTelcom_InOracleTransport::doDisconnect()
{
  try
  {
    if (m_pStoredFunction) 
    {
      m_pStoredFunction->freeAllHandles();
      //delete m_pStoredFunction;
      //m_pStoredFunction = 0;
    }
  }
  catch(cCBS_DBExc &e) 
  {
    std::cout << e.getText() << std::endl;
  }

  CTelcom_InTask::getInstance()->setWorking(false);

  int status = 0;

  //status = CTelcom_OracleTransport::doDisconnect();
  //if (status == -1)
  //{
  //  cCBS_StdLog_Task::getInstance()->log("Dis-Connection timeout!");
  //}
  //else
  //{
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_LostConnection(sMessage,cCBS_StdInitBase::getInstance()->m_ServerName.c_str());

  //  cCBS_StdLog_Task::getInstance()->log("CTelcom_InOracleTransport::doDisconnect: Dis-Connected!");
  //}

  return status;
}

int CTelcom_InOracleTransport::receive(TCMessage & msg)
{
  int retVal = -1;
  tofillMsg = &msg;

  // must be called first, in order that thread sleep for certain intervall
  retVal = CTelcom_OracleTransport::receive(msg);

  retVal = getBerichtFromDB();

  tofillMsg = 0;
  return retVal;
}

int CTelcom_InOracleTransport::getBerichtFromDB()
{
  int retVal = -1;
  // 2 more then one message in queue
  // 1 only one message in queue
  // 0 no message in the queue
  int QueueResult = 0;

  m_sender = "";
  m_transmission = ""; // corus pointed out no need
  m_typeReport = "";
  m_timezone  = "";
  m_destination = ""; // corus pointed out no need
  m_messageContent = "";

  if( m_pStoredFunction )
  { 
    int QueueResult = m_pStoredFunction->getBerichtFromDB(p_poort, p_timeout, &m_sender, &m_transmission, &m_typeReport, &m_timezone , &m_destination, &m_messageContent);

    if ( m_timezone.length() > 2 )
    {
      // safty reasons
      m_timezone = "";
    }

    if ( QueueResult == 2)
    {
      m_retryInterval = 10;
      std::stringstream Message;    
      Message << "New polling RetryInterval. Using value '0,01' - more then one message is in the queue";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 2);    
    }
    else if ( QueueResult == 1)
    {
      m_retryInterval = 100; 
      std::stringstream Message;    
      Message << "New polling RetryInterval. Using value '0,1' - one message is in the queue";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 2);      
    }
    else if ( QueueResult == 0)
    {
      cCBS_StdInitBase *pStdInitBase = cCBS_StdInitBase::getInstance();

      long Interval = 1;
      pStdInitBase->getEntry("SMS_Transport", "RetryInterval", Interval);
      m_retryInterval = Interval * 1000; // 1s // later test 1 min 
    }

    if ( !m_typeReport.empty() )
    {
      // go to needed section
      //check sender from the message
      if ( retVal == -1 && !(m_sender.compare(p_Proco2)))
      {  
        retVal = Proco2ToLF22();      
      }
      if ( retVal == -1 && !(m_sender.compare(p_FDB)))
      {
        retVal = FDBToLF22();
      }
      if ( retVal == -1 && !(m_sender.compare(p_BOF)))
      {
        retVal = BOFToLF22();  
      }
      if ( retVal == -1 && !(m_sender.compare(p_Sparcs)))
      {   
        retVal = SparcsToLF22();    
      }
      if ( retVal == -1 && !(m_sender.compare(p_Samtracs)))
      {
        retVal = SamtracsToLF22();
      }

      if( retVal == -1 )
      {
        //msg is not handled
        std::stringstream Message;
        Message << "CTelcom_InOracleTransport::getBerichtFromDB(): Msg " << m_typeReport << " for sender - " << m_sender << " - is not handled";
        cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1); 

        m_pStoredFunction->set_Bstat(false);
      }
      else
      {
        tlg->setSerializer(FormatMgr::instance()->getSerializer(m_RemoteMsgFormat));
        // the ID 
        std::string TlgName = tlg->getId();

        tofillMsg->clear();
        tofillMsg->setType(TlgName);
        tofillMsg->setBufFormat(m_RemoteMsgFormat);

        // Copy the local message to user's TCMessage
        tlg->serialize(tofillMsg->bufOstr());     
        delete tlg;
        retVal = tofillMsg->bufLen();

        if(retVal != -1)
        {
          // Msg is received, set status in the Database
          m_pStoredFunction->set_Bstat(true);
        }
      }
    }// if ( !m_typeReport.empty() )
    else
    {
      CDateTime now;
      std::stringstream Message;    
      Message << "CTelcom_InOracleTransport::getBericht: "  << now << " - No message found ... Wait for message!";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 2);   
    }
  }//  if(m_pStoredFunction && m_pStoredFunction->getBerichtFromDB(p_poort, p_timeout, &m_sender, &m_transmission, &m_typeReport, &m_timezone , &m_destination, &m_messageContent) )
  else
  { 
    std::stringstream Message;
    Message << "CTelcom_InOracleTransport::getBerichtFromDB(): could not execute SQL - Sender: " << m_sender << " TypeReport: "  << m_typeReport << " Destination: " << m_destination;
    cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1); 
  }

  // return zero - connected. Then we come into Receive
  return retVal;
} // int CTelcom_InOracleTransport::getBerichtFromDB()

int CTelcom_InOracleTransport::Proco2ToLF22()
{
  int retVal = -1;
  std::basic_string <char>::size_type pos = -1;
  // find userdata in the header, please refer to the message description
  if ( !m_typeReport.compare(std::string("WRKUTGBE01") ) )
  {
    setRawMessage(std::string("WRKUTGBE01").length());
    cCBS_StdLog_Task::getInstance()->writeLog("Tlg " + m_typeReport + " started",1);

    try
    {
      // tlg -> Tlg
      tlg = m_pFactory->makeTlg("WRKUTGBE01");
      // xml ausgelesen

      // -(m_pFactory->getTlg(headTlgName)->getLen())
      long blen = tlg->getLen();;

      // makes the telegram empty 
      tlg->clear();

      // read telegramm elements from idl namespace

      // HERE SOMETHING IS STILL MISSING.

      //// struct HeaderType{
      //(*tlg)["Header"][Telegram_WRKUTGBE01::MessageId].set(3001L);
      //(*tlg)["Header"][Telegram_WRKUTGBE01::MessageLength].set(blen);
      //(*tlg)["Header"][Telegram_WRKUTGBE01::MessageCount].set(1L);
      //(*tlg)["Header"][Telegram_WRKUTGBE01::UnitNo].set(1L);
      //// } HeaderType

      //(*tlg)[Telegram_WRKUTGBE01::TimeZone] = m_timezone;

      //(*tlg)[Telegram_WRKUTGBE01::ActionCounter] = convertMessage("9",2);
      //(*tlg)[Telegram_WRKUTGBE01::Action]        = convertMessage("X",1);

      showContent((*tlg),m_typeReport,3);

      cCBS_StdLog_Task::getInstance()->writeLog("Tlg " + m_typeReport + " end",1);
      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_InOracleTransport::Proco2ToLF22(): Could not make telegramm ["<<m_typeReport<<"]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1); 
      retVal = -1;
    }
  }
  else if ( !m_typeReport.compare(std::string("WERKUITG03") ) )
  {
    setRawMessage(std::string("WERKUITG03").length());
    cCBS_StdLog_Task::getInstance()->writeLog("Tlg " + m_typeReport + " started",1);

    try
    {
      // tlg -> Tlg
      tlg = m_pFactory->makeTlg("WERKUITG03");

      // -(m_pFactory->getTlg(headTlgName)->getLen())
      long blen = tlg->getLen();;

      // makes the telegram empty 
      tlg->clear();

      // read telegramm elements from idl namespace

      // HERE SOMETHING IS STILL MISSING.

      //// struct HeaderType{
      //(*tlg)["Header"][Telegram_WERKUITG03::MessageId].set(3002L);
      //(*tlg)["Header"][Telegram_WERKUITG03::MessageLength].set(blen);
      //(*tlg)["Header"][Telegram_WERKUITG03::MessageCount].set(1L);
      //(*tlg)["Header"][Telegram_WERKUITG03::UnitNo].set(1L);
      //// } HeaderType

      //(*tlg)[Telegram_WERKUITG03::TimeZone] = m_timezone;

      //(*tlg)[Telegram_WERKUITG03::ProdOrderCounter] = convertMessage("9",2);

      //// lenght of one message except counter 
      //int nextMessage = 14; 

      //for ( long i = 0 ; i < m_fieldIterations ; ++i ) // 99*82 after convertMessage
      //{ 
      //  // this 14 elements are 82 byte long
      //  (*tlg)[Telegram_WERKUITG03::ProdOrderId]   [i] = convertMessage("9",4);
      //  (*tlg)[Telegram_WERKUITG03::HeatId]        [i] = convertMessage("X",5);
      //  (*tlg)[Telegram_WERKUITG03::CastSerNo]     [i] = convertMessage("9",3);
      //  (*tlg)[Telegram_WERKUITG03::CastSerSeqNo]  [i] = convertMessage("9",2);
      //  (*tlg)[Telegram_WERKUITG03::TrialNo]       [i] = convertMessage("X",4);
      //  (*tlg)[Telegram_WERKUITG03::GenParticulars][i] = convertMessage("X",13);
      //  (*tlg)[Telegram_WERKUITG03::SteelGrade]    [i] = convertMessage("X",5);
      //  (*tlg)[Telegram_WERKUITG03::TreatStartTime][i] = convertMessage("X",12);
      //  (*tlg)[Telegram_WERKUITG03::TreatEndTime]  [i] = convertMessage("X",12);
      //  (*tlg)[Telegram_WERKUITG03::PlanBOF]       [i] = convertMessage("9",2);
      //  (*tlg)[Telegram_WERKUITG03::PlanCast]      [i] = convertMessage("9",1);
      //  (*tlg)[Telegram_WERKUITG03::PlanDepTime]   [i] = convertMessage("X",12);
      //  (*tlg)[Telegram_WERKUITG03::PlanCastTime]  [i] = convertMessage("9",3);
      //  (*tlg)[Telegram_WERKUITG03::PlanDepTemp]   [i] = convertMessage("9",4);
      //}
      
      showContent((*tlg),m_typeReport,3);
      
      cCBS_StdLog_Task::getInstance()->writeLog("Tlg " + m_typeReport + " end",1);
      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_InOracleTransport::Proco2ToLF22(): Could not make telegramm ["<<m_typeReport<<"]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1); 
      retVal = -1;
    }
  }
  else if ( !m_typeReport.compare(std::string("LADNRCOR01") ) )
  {
    setRawMessage(std::string("LADNRCOR01").length());
    cCBS_StdLog_Task::getInstance()->writeLog("Tlg " + m_typeReport + " started",1);
    try
    {
      // tlg -> Tlg
      tlg = m_pFactory->makeTlg("LADNRCOR01");

      // -(m_pFactory->getTlg(headTlgName)->getLen())
      long blen = tlg->getLen();;

      // makes the telegram empty 
      tlg->clear();

      // read telegramm elements from idl namespace

      // HERE SOMETHING IS STILL MISSING.

      //// struct sHeaderType{
      //(*tlg)["Header"][Telegram_LADNRCOR01::MessageId].set(3003L);
      //(*tlg)["Header"][Telegram_LADNRCOR01::MessageLength].set(blen);
      //(*tlg)["Header"][Telegram_LADNRCOR01::MessageCount].set(1L);
      //(*tlg)["Header"][Telegram_LADNRCOR01::UnitNo].set(1L);
      //// } HeaderType  

      //(*tlg)[Telegram_LADNRCOR01::TimeZone] = m_timezone;

      //(*tlg)[Telegram_LADNRCOR01::ProdHeatCounter] = convertMessage("9",2);

      //// lenght of one message except counter 
      //int nextMessage = 2;

      //// 99*82 = 8118
      //for ( long i = 0 ; i < m_fieldIterations ; ++i )
      //{
      //  (*tlg)[Telegram_LADNRCOR01::ProdOrderId] [i] = convertMessage("9",4);
      //  (*tlg)[Telegram_LADNRCOR01::HeatId]      [i] = convertMessage("X",5);
      //}

      showContent((*tlg),m_typeReport,3);

      cCBS_StdLog_Task::getInstance()->writeLog("Tlg " + m_typeReport + " end",1);
      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_InOracleTransport::Proco2ToLF22(): Could not make telegramm ["<<m_typeReport<<"]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1);
      retVal = -1;
    }
  }
  else if ( !m_typeReport.compare(std::string("LADNRKOP02")) ) 
  {
    setRawMessage(std::string("LADNRKOP02").length());
    cCBS_StdLog_Task::getInstance()->writeLog("Tlg " + m_typeReport + " started",1);
    try
    {
      // tlg -> Tlg
      tlg = m_pFactory->makeTlg("LADNRKOP02");

      // -(m_pFactory->getTlg(headTlgName)->getLen())
      long blen = tlg->getLen();;

      // makes the telegram empty 
      tlg->clear();

      // read telegramm elements from idl namespace

      // HERE SOMETHING IS STILL MISSING.

      //// struct sHeaderType{
      //(*tlg)["Header"][Telegram_LADNRKOP02::MessageId].set(3004L);
      //(*tlg)["Header"][Telegram_LADNRKOP02::MessageLength].set(blen);
      //(*tlg)["Header"][Telegram_LADNRKOP02::MessageCount].set(1L);
      //(*tlg)["Header"][Telegram_LADNRKOP02::UnitNo].set(1L);
      //// } HeaderType

      //(*tlg)[Telegram_LADNRKOP02::TimeZone] = m_timezone;

      //(*tlg)[Telegram_LADNRKOP02::ProdHeatCounter] = convertMessage("9",2);

      //// lenght of one message except counter 
      //int nextMessage = 2;  
      ////m_vRawMessageContent.resize(m_fieldIterations*nextMessage+1,"") ;

      //for ( long i = 0 ; i < m_fieldIterations ; ++i )
      //{
      //  // this 14 elements are 82 byte long
      //  (*tlg)[Telegram_LADNRKOP02::ProdOrderId] [i] = convertMessage("9",4);
      //  (*tlg)[Telegram_LADNRKOP02::HeatId]      [i] = convertMessage("X",5);        
      //}

      showContent((*tlg),m_typeReport,3);

      cCBS_StdLog_Task::getInstance()->writeLog("Tlg " + m_typeReport + " end",1);
      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_InOracleTransport::Proco2ToLF22(): Could not make telegramm ["<<m_typeReport<<"]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1); 
      retVal = -1;
    }
  }
  else if ( !m_typeReport.compare(std::string("KWALDATA01")) )
  {
    setRawMessage(std::string("KWALDATA01").length());
    cCBS_StdLog_Task::getInstance()->writeLog("Tlg " + m_typeReport + " started",1);
    try
    {
      // tlg -> Tlg
      tlg = m_pFactory->makeTlg("KWALDATA01");

      // -(m_pFactory->getTlg(headTlgName)->getLen())
      long blen = tlg->getLen();;

      // makes the telegram empty 
      tlg->clear();

      // read telegramm elements from idl namespace

      // HERE SOMETHING IS STILL MISSING.

      //// struct sHeaderType{
      //(*tlg)["Header"][Telegram_KWALDATA01::MessageId].set(3005L);
      //(*tlg)["Header"][Telegram_KWALDATA01::MessageLength].set(blen);
      //(*tlg)["Header"][Telegram_KWALDATA01::MessageCount].set(1L);
      //(*tlg)["Header"][Telegram_KWALDATA01::UnitNo].set(1L);
      //// } HeaderType  

      //(*tlg)[Telegram_KWALDATA01::TimeZone] = m_timezone;

      //// see 2.5 message description to formats
      //// store Counter Msg
      //string ItemCounter = m_vRawMessageContent[0].substr(0, 2);
      // // cut Msg
      //m_vRawMessageContent[0] = m_vRawMessageContent[0].substr(2, m_vRawMessageContent[0].length());
    
      //(*tlg)[Telegram_KWALDATA01::ItemCounter] = ItemCounter;
      //
      //// lenght of one message except counter 
      //int nextMessage = 2;
      //m_vRawMessageContent.resize(m_fieldIterations*nextMessage) ;


      //for ( long i = 0 ; i < m_fieldIterations ; ++i )
      //{
      //  std::string item; 
      //  std::string value;
      //  long PositionOfEqual = -1;

      //  if ( std::string::npos != (PositionOfEqual = (long)m_vRawMessageContent[i].find_first_of("=")) )
      //  {
      //    item = m_vRawMessageContent[i].substr(0,PositionOfEqual);
      //    value = m_vRawMessageContent[i].substr(PositionOfEqual+1,m_vRawMessageContent[i].length());

      //    long PositionOfCarrat = -1;
      //    for ( long ii = i+1 ; i < m_fieldIterations ; ++ii )
      //    {
      //      //when the comma is part of remark the sign "^" is palced before comma
      //      if ( std::string::npos != (PositionOfCarrat = (long)value.rfind("^")) && value.length() == PositionOfCarrat+1 )
      //      {
      //        value.replace(PositionOfCarrat,1,",");
      //        value += m_vRawMessageContent[ii];
      //      }      
      //      else
      //        break;
      //    }
      //  } 

      //  if(item.length() > 20 || value.length() > 50)
      //  {
      //    continue;
      // 
      //  }

      //  (*tlg)[Telegram_KWALDATA01::Item]   [i] = item;
      //  (*tlg)[Telegram_KWALDATA01::Value]  [i] = value;
      //}// for ( long i = 0 ; i < m_fieldIterations ; ++i )

      showContent((*tlg),m_typeReport,3);
      
      cCBS_StdLog_Task::getInstance()->writeLog("Tlg " + m_typeReport + " end",1);
      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_InOracleTransport::Proco2ToLF22(): Could not make telegramm ["<<m_typeReport<<"]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1); 

      retVal = -1;
    }
  }
  // please note that message contains "-" sign taht is not usable for IDL definitions
  // TELCOM telegram name is UPDSTAT01 !
  else if ( !m_typeReport.compare(std::string("UPDSTAT-01")) ) 
  {
    setRawMessage(std::string("UPDSTAT-01").length());
    cCBS_StdLog_Task::getInstance()->writeLog("Tlg " + m_typeReport + " started",1);
    try
    {
      // tlg -> Tlg
      tlg = m_pFactory->makeTlg("UPDSTAT01");

      // -(m_pFactory->getTlg(headTlgName)->getLen())
      long blen = tlg->getLen();;

      // makes the telegram empty 
      tlg->clear();

      // read telegramm elements from idl namespace

      // HERE SOMETHING IS STILL MISSING.

      //// struct sHeaderType{
      //(*tlg)["Header"][Telegram_UPDSTAT01::MessageId].set(3006L);
      //(*tlg)["Header"][Telegram_UPDSTAT01::MessageLength].set(blen);
      //(*tlg)["Header"][Telegram_UPDSTAT01::MessageCount].set(1L);
      //(*tlg)["Header"][Telegram_UPDSTAT01::UnitNo].set(1L);
      //// } HeaderType  

      //(*tlg)[Telegram_UPDSTAT01::TimeZone] = m_timezone;

      //(*tlg)[Telegram_UPDSTAT01::StatusCounter] = convertMessage("9",2);

      //// lenght of one message except counter 
      //int nextMessage = 1;

      //for ( long i = 0 ; i < m_fieldIterations ; ++i )
      //{
      //  // this 14 elements are 82 byte long
      //  (*tlg)[Telegram_UPDSTAT01::Status]   [i] = convertMessage("X",1);
      //}

      showContent((*tlg),m_typeReport,3);

      cCBS_StdLog_Task::getInstance()->writeLog("Tlg " + m_typeReport + " end",1);
      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_InOracleTransport::Proco2ToLF22(): Could not make telegramm ["<<m_typeReport<<"]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1); 
      retVal = -1;
    }
  }

  return retVal;
}

int CTelcom_InOracleTransport::FDBToLF22()
{
  int retVal = -1;
  std::basic_string <char>::size_type pos = -1;
  // find userdata in the header, please refer to the message description
  if ( !m_typeReport.compare(std::string("GEWICHT01")) ) 
  {
    setRawMessage(std::string("GEWICHT01").length());
    cCBS_StdLog_Task::getInstance()->writeLog("Tlg " + m_typeReport + " started",1);
    try
    {
      // tlg -> Tlg
      tlg = m_pFactory->makeTlg("GEWICHT01");

      // -(m_pFactory->getTlg(headTlgName)->getLen())
      long blen = tlg->getLen();;

      // makes the telegram empty 
      tlg->clear();

      // read telegramm elements from idl namespace

      // HERE SOMETHING IS STILL MISSING.

      //// struct sHeaderType{
      ////!!!
      //(*tlg)["Header"][Telegram_GEWICHT01::MessageId].set(3007L);
      //(*tlg)["Header"][Telegram_GEWICHT01::MessageLength].set(blen);
      //(*tlg)["Header"][Telegram_GEWICHT01::MessageCount].set(1L);
      //(*tlg)["Header"][Telegram_GEWICHT01::UnitNo].set(1L);
      //// } HeaderType  

      //(*tlg)[Telegram_GEWICHT01::TimeZone] = m_timezone;

      //(*tlg)[Telegram_GEWICHT01::WeightCounter] = convertMessage("9",2);

      //// lenght of one message except counter 
      //int nextMessage = 5;

      //for ( long i = 0 ; i < m_fieldIterations ; ++i )
      //{
      //  // this 14 elements are 82 byte long
      //  (*tlg)[Telegram_GEWICHT01::WeightCode]  [i] = convertMessage("X",1);
      //  (*tlg)[Telegram_GEWICHT01::Weight]      [i] = convertMessage("9",4);
      //  (*tlg)[Telegram_GEWICHT01::ProdOrderId] [i] = convertMessage("9",4);
      //  (*tlg)[Telegram_GEWICHT01::LadleId]     [i] = convertMessage("9",3);
      //  (*tlg)[Telegram_GEWICHT01::CraneNo]     [i] = convertMessage("9",2);
      //}

      showContent((*tlg),m_typeReport,3);
      
      cCBS_StdLog_Task::getInstance()->writeLog("Tlg " + m_typeReport + " end",1);
      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_InOracleTransport::FDBToLF22(): Could not make telegramm ["<<m_typeReport<<"]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1); 
      retVal = -1;
    }
  }
  return retVal;
}

int CTelcom_InOracleTransport::BOFToLF22()
{
  int retVal = -1;
  std::basic_string <char>::size_type pos = -1;
  // find userdata in the header, please refer to the message description
  if ( !m_typeReport.compare(std::string("LADNRKOP01")) )
  {
    setRawMessage(std::string("LADNRKOP01").length());
    cCBS_StdLog_Task::getInstance()->writeLog("Tlg " + m_typeReport + " started",1);
    try
    {
      // tlg -> Tlg
      tlg = m_pFactory->makeTlg("LADNRKOP01");

      // -(m_pFactory->getTlg(headTlgName)->getLen())
      long blen = tlg->getLen();;

      // makes the telegram empty 
      tlg->clear();

      // read telegramm elements from idl namespace

      // HERE SOMETHING IS STILL MISSING.

      //// struct sHeaderType{
      //(*tlg)["Header"][Telegram_LADNRKOP01::MessageId].set(3008L);
      //(*tlg)["Header"][Telegram_LADNRKOP01::MessageLength].set(blen);
      //(*tlg)["Header"][Telegram_LADNRKOP01::MessageCount].set(1L);
      //(*tlg)["Header"][Telegram_LADNRKOP01::UnitNo].set(1L);
      //// } HeaderType  

      //(*tlg)[Telegram_LADNRKOP01::TimeZone] = m_timezone;

      //(*tlg)[Telegram_LADNRKOP01::ProdOrderId] = convertMessage("9",4);
      //(*tlg)[Telegram_LADNRKOP01::HeatId]      = convertMessage("X",5);

      showContent((*tlg),m_typeReport,3);
      
      cCBS_StdLog_Task::getInstance()->writeLog("Tlg " + m_typeReport + " end",1);
      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_InOracleTransport::BOFToLF22(): Could not make telegramm ["<<m_typeReport<<"]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1); 
      retVal = -1;
    }
  }
  else if ( !m_typeReport.compare(std::string("LADINGGG01")) ) 
  {
    setRawMessage(std::string("LADINGGG01").length());
    cCBS_StdLog_Task::getInstance()->writeLog("Tlg " + m_typeReport + " started",1);
    try
    {
      // tlg -> Tlg
      tlg = m_pFactory->makeTlg("LADINGGG01");

      // -(m_pFactory->getTlg(headTlgName)->getLen())
      long blen = tlg->getLen();;

      // makes the telegram empty 
      tlg->clear();

      // read telegramm elements from idl namespace

      // HERE SOMETHING IS STILL MISSING.

      //// struct sHeaderType{
      //(*tlg)["Header"][Telegram_LADINGGG01::MessageId].set(3009L);
      //(*tlg)["Header"][Telegram_LADINGGG01::MessageLength].set(blen);
      //(*tlg)["Header"][Telegram_LADINGGG01::MessageCount].set(1L);
      //(*tlg)["Header"][Telegram_LADINGGG01::UnitNo].set(1L);
      //// } HeaderType  

      //(*tlg)[Telegram_LADINGGG01::TimeZone] = m_timezone;

      //(*tlg)[Telegram_LADINGGG01::ProdOrderId]         = convertMessage("9",4);
      //(*tlg)[Telegram_LADINGGG01::HeatId]              = convertMessage("X",5);
      //(*tlg)[Telegram_LADINGGG01::LadleId]             = convertMessage("9",3);
      //(*tlg)[Telegram_LADINGGG01::SteelWeight]         = convertMessage("9",6);
      //(*tlg)[Telegram_LADINGGG01::SteelGradeStart]     = convertMessage("X",5);
      //(*tlg)[Telegram_LADINGGG01::SteelGradeEnd]       = convertMessage("X",5);
      //(*tlg)[Telegram_LADINGGG01::LadleStatus]         = convertMessage("X",1);
      //(*tlg)[Telegram_LADINGGG01::BeginTap]            = convertMessage("X",12);

      showContent((*tlg),m_typeReport,3);
      
      cCBS_StdLog_Task::getInstance()->writeLog("Tlg " + m_typeReport + " end",1);
      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_InOracleTransport::BOFToLF22(): Could not make telegramm ["<<m_typeReport<<"]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1); 
      retVal = -1;
    }
  }
  else if ( !m_typeReport.compare(std::string("DWARSTRP01")) ) 
  {
    setRawMessage(std::string("DWARSTRP01").length());
    cCBS_StdLog_Task::getInstance()->writeLog("Tlg " + m_typeReport + " started",1);
    try
    {
      // tlg -> Tlg
      tlg = m_pFactory->makeTlg("DWARSTRP01");

      // -(m_pFactory->getTlg(headTlgName)->getLen())
      long blen = tlg->getLen();;

      // makes the telegram empty 
      tlg->clear();

      // read telegramm elements from idl namespace

      // HERE SOMETHING IS STILL MISSING.

      //// struct sHeaderType{
      //(*tlg)["Header"][Telegram_DWARSTRP01::MessageId].set(3010L);
      //(*tlg)["Header"][Telegram_DWARSTRP01::MessageLength].set(blen);
      //(*tlg)["Header"][Telegram_DWARSTRP01::MessageCount].set(1L);
      //(*tlg)["Header"][Telegram_DWARSTRP01::UnitNo].set(1L);
      //// } HeaderType  

      //(*tlg)[Telegram_DWARSTRP01::TimeZone] = m_timezone;

      //(*tlg)[Telegram_DWARSTRP01::HeatId]           = convertMessage("X",5);
      //(*tlg)[Telegram_DWARSTRP01::Date]             = convertMessage("X",12);
      //(*tlg)[Telegram_DWARSTRP01::TempTransp]       = convertMessage("9",4);
      //(*tlg)[Telegram_DWARSTRP01::O2SteelActTransp] = convertMessage("9",5);
      //(*tlg)[Telegram_DWARSTRP01::O2SlagActTransp]  = convertMessage("9",5);
      //(*tlg)[Telegram_DWARSTRP01::SlagDepth]        = convertMessage("9",3);
      //(*tlg)[Telegram_DWARSTRP01::StirrStatusPlug1] = convertMessage("X",1);
      //(*tlg)[Telegram_DWARSTRP01::StirrStatusPlug2] = convertMessage("X",1);
      //(*tlg)[Telegram_DWARSTRP01::FreeboardSteel]   = convertMessage("9",3);
      //(*tlg)[Telegram_DWARSTRP01::FreeboardSlag]    = convertMessage("9",3);

      showContent((*tlg),m_typeReport,3);
      
      cCBS_StdLog_Task::getInstance()->writeLog("Tlg " + m_typeReport + " end",1);
      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_InOracleTransport::BOFToLF22(): Could not make telegramm [DWARSTRP01]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1); 
      retVal = -1;
    }
  }
  else if ( !m_typeReport.compare(std::string("TAPMATGG01")) ) 
  {
    setRawMessage(std::string("TAPMATGG01").length());
    cCBS_StdLog_Task::getInstance()->writeLog("Tlg " + m_typeReport + " started",1);
    try
    {
      // tlg -> Tlg
      tlg = m_pFactory->makeTlg("TAPMATGG01");

      // -(m_pFactory->getTlg(headTlgName)->getLen())
      long blen = tlg->getLen();;

      // makes the telegram empty 
      tlg->clear();

      // read telegramm elements from idl namespace

      // HERE SOMETHING IS STILL MISSING.

      //// struct sHeaderType{
      //(*tlg)["Header"][Telegram_TAPMATGG01::MessageId].set(3011L);
      //(*tlg)["Header"][Telegram_TAPMATGG01::MessageLength].set(blen);
      //(*tlg)["Header"][Telegram_TAPMATGG01::MessageCount].set(1L);
      //(*tlg)["Header"][Telegram_TAPMATGG01::UnitNo].set(1L);
      //// } HeaderType

      //(*tlg)[Telegram_TAPMATGG01::TimeZone] = m_timezone;

      //(*tlg)[Telegram_TAPMATGG01::HeatId]          = convertMessage("X",5);
      //(*tlg)[Telegram_TAPMATGG01::Date]            = convertMessage("X",12);
      //(*tlg)[Telegram_TAPMATGG01::AdditionCounter] = convertMessage("9",2);

      //// lenght of one message except counter 
      //int nextMessage = 2;
      //
      //for ( long i = 0 ; i < m_fieldIterations ; ++i ) // 99*8 after convertMessage
      //{ 
      //  // this 14 elements are 82 byte long
      //  (*tlg)[Telegram_TAPMATGG01::MatCode]     [i] = convertMessage("X",2);
      //  (*tlg)[Telegram_TAPMATGG01::MatWeight]   [i] = convertMessage("9",6);
      //}

      showContent((*tlg),m_typeReport,3);
      
      cCBS_StdLog_Task::getInstance()->writeLog("Tlg " + m_typeReport + " end",1);
      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_InOracleTransport::BOFToLF22(): Could not make telegramm ["<<m_typeReport<<"]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1); 
      retVal = -1;
    }
  }
  else if ( !m_typeReport.compare(std::string("TAPANABE01")) ) 
  {
    setRawMessage(std::string("TAPANABE01").length());
    cCBS_StdLog_Task::getInstance()->writeLog("Tlg " + m_typeReport + " started",1);
    try
    {
      // tlg -> Tlg
      tlg = m_pFactory->makeTlg("TAPANABE01");

      // -(m_pFactory->getTlg(headTlgName)->getLen())
      long blen = tlg->getLen();;

      // makes the telegram empty 
      tlg->clear();

      // read telegramm elements from idl namespace

      // HERE SOMETHING IS STILL MISSING.

      //// struct sHeaderType{
      //(*tlg)["Header"][Telegram_TAPANABE01::MessageId].set(3012L);
      //(*tlg)["Header"][Telegram_TAPANABE01::MessageLength].set(blen);
      //(*tlg)["Header"][Telegram_TAPANABE01::MessageCount].set(1L);
      //(*tlg)["Header"][Telegram_TAPANABE01::UnitNo].set(1L);
      //// } HeaderType  

      //(*tlg)[Telegram_TAPANABE01::TimeZone] = m_timezone;

      //(*tlg)[Telegram_TAPANABE01::HeatId] = convertMessage("X",5);
      //(*tlg)[Telegram_TAPANABE01::Spare1] = convertMessage("X",4);
      //(*tlg)[Telegram_TAPANABE01::O]      = convertMessage("X",4);
      //(*tlg)[Telegram_TAPANABE01::N]      = convertMessage("X",4);
      //(*tlg)[Telegram_TAPANABE01::C]      = convertMessage("X",4);
      //(*tlg)[Telegram_TAPANABE01::Mn]     = convertMessage("X",4);
      //(*tlg)[Telegram_TAPANABE01::P]      = convertMessage("X",4);
      //(*tlg)[Telegram_TAPANABE01::S]      = convertMessage("X",4);
      //(*tlg)[Telegram_TAPANABE01::Si]     = convertMessage("X",4);
      //(*tlg)[Telegram_TAPANABE01::Al]     = convertMessage("X",4);
      //(*tlg)[Telegram_TAPANABE01::Cu]     = convertMessage("X",4);
      //(*tlg)[Telegram_TAPANABE01::Sn]     = convertMessage("X",4);
      //(*tlg)[Telegram_TAPANABE01::Cr]     = convertMessage("X",4);
      //(*tlg)[Telegram_TAPANABE01::Ni]     = convertMessage("X",4);
      //(*tlg)[Telegram_TAPANABE01::Mo]     = convertMessage("X",4);
      //(*tlg)[Telegram_TAPANABE01::Nb]     = convertMessage("X",4);
      //(*tlg)[Telegram_TAPANABE01::V]      = convertMessage("X",4);
      //(*tlg)[Telegram_TAPANABE01::B]      = convertMessage("X",4);
      //(*tlg)[Telegram_TAPANABE01::Ti]     = convertMessage("X",4);
      //(*tlg)[Telegram_TAPANABE01::Ca]     = convertMessage("X",4);
      //(*tlg)[Telegram_TAPANABE01::Spare2] = convertMessage("X",4);
      //(*tlg)[Telegram_TAPANABE01::Spare3] = convertMessage("X",4);
      //(*tlg)[Telegram_TAPANABE01::Alz]    = convertMessage("X",4);
      //(*tlg)[Telegram_TAPANABE01::H]      = convertMessage("X",4);

      showContent((*tlg),m_typeReport,3);
      
      cCBS_StdLog_Task::getInstance()->writeLog("Tlg " + m_typeReport + " end",1);
      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_InOracleTransport::BOFToLF22(): Could not make telegramm ["<<m_typeReport<<"]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1);
      retVal = -1;
    }
  }// else if ( !m_typeReport.compare(std::string("TAPANABE01")) )

  return retVal;
}// int CTelcom_InOracleTransport::BOFToLF22()


int CTelcom_InOracleTransport::SparcsToLF22()
{
  int retVal = -1;
  std::basic_string <char>::size_type pos = -1;
  // find userdata in the header, please refer to the message description
  if ( !m_typeReport.compare(std::string("ANALYSE1")) ) 
  {

    setRawMessage(std::string("ANALYSE1").length());    
    cCBS_StdLog_Task::getInstance()->writeLog("Tlg " + m_typeReport + " started",1);
    try
    {
      // tlg -> Tlg
      tlg = m_pFactory->makeTlg("ANALYSE01");

      // -(m_pFactory->getTlg(headTlgName)->getLen())
      long blen = tlg->getLen();;

      // makes the telegram empty 
      tlg->clear();

      // read telegramm elements from idl namespace

      // HERE SOMETHING IS STILL MISSING.

      //// struct sHeaderType{
      //(*tlg)["Header"][Telegram_ANALYSE01::MessageId].set(1202L);
      //(*tlg)["Header"][Telegram_ANALYSE01::MessageLength].set(blen);
      //(*tlg)["Header"][Telegram_ANALYSE01::MessageCount].set(1L);
      //(*tlg)["Header"][Telegram_ANALYSE01::UnitNo].set(1L);
      //// } HeaderType

      //(*tlg)[Telegram_ANALYSE01::TimeZone] = m_timezone;

      //(*tlg)[Telegram_ANALYSE01::Hour]               = convertMessage("X",2, m_vRawMessageContent[0]);
      //(*tlg)[Telegram_ANALYSE01::Minute]             = convertMessage("X",2, m_vRawMessageContent[1]);
      //(*tlg)[Telegram_ANALYSE01::Day]                = convertMessage("X",2, m_vRawMessageContent[2]);
      //(*tlg)[Telegram_ANALYSE01::Month]              = convertMessage("X",2, m_vRawMessageContent[3]);
      //(*tlg)[Telegram_ANALYSE01::Year]               = convertMessage("X",2, m_vRawMessageContent[4]);
      //(*tlg)[Telegram_ANALYSE01::ProgramName]        = convertMessage("X",6, m_vRawMessageContent[5]);
      //(*tlg)[Telegram_ANALYSE01::SampleMode]         = convertMessage("X",2, m_vRawMessageContent[6]);
      //(*tlg)[Telegram_ANALYSE01::CalculationMode]    = convertMessage("X",2, m_vRawMessageContent[7]);
      //(*tlg)[Telegram_ANALYSE01::ModeNo]             = convertMessage("X",2, m_vRawMessageContent[8]);
      //(*tlg)[Telegram_ANALYSE01::PlantId]            = convertMessage("X",2, m_vRawMessageContent[9]);
      //(*tlg)[Telegram_ANALYSE01::Unknown1]           = convertMessage("X",6, m_vRawMessageContent[10]);
      //(*tlg)[Telegram_ANALYSE01::HeatId]             = convertMessage("X",5, m_vRawMessageContent[11]);
      //(*tlg)[Telegram_ANALYSE01::SampleNo]           = convertMessage("X",3, m_vRawMessageContent[12]);
      //(*tlg)[Telegram_ANALYSE01::MassageCode]        = convertMessage("X",6, m_vRawMessageContent[13]);
      //(*tlg)[Telegram_ANALYSE01::Unknown2]           = convertMessage("X",6, m_vRawMessageContent[14]);
      //(*tlg)[Telegram_ANALYSE01::InstrumentNo]       = convertMessage("X",1, m_vRawMessageContent[15]); 
      //(*tlg)[Telegram_ANALYSE01::TransmissionStatus] = convertMessage("X",1, m_vRawMessageContent[16]);
      //(*tlg)[Telegram_ANALYSE01::Average]            = convertMessage("X",2, m_vRawMessageContent[17]); 
      //(*tlg)[Telegram_ANALYSE01::InstrumentType]     = convertMessage("X",2, m_vRawMessageContent[18]);
      //(*tlg)[Telegram_ANALYSE01::Counter]            = convertMessage("X",2, m_vRawMessageContent[19]); 

      //// lenght of one message except counter 
      //int nextMessage = 2;  
      //// vector resize of telegramm length
      //m_vRawMessageContent.resize(m_fieldIterations*nextMessage+20,"") ;

      ////repeat n=1 -> (n-1) = 0
      //int MsgRepeat = atoi(m_vRawMessageContent[19].c_str()); 

      //for ( long i = 0 ; i < m_fieldIterations ; ++i )
      //{
      //  if ( i+1 <= MsgRepeat ) 
      //  {
      //    (*tlg)[Telegram_ANALYSE01::Name]          [i] = convertMessage("X",6,  m_vRawMessageContent[(20+i*nextMessage)]);
      //    (*tlg)[Telegram_ANALYSE01::Concentration] [i] = convertMessage("X",7,  m_vRawMessageContent[(21+i*nextMessage)]);
      //  }
      //  else // fill the tlg object 
      //  {
      //    // fill the rest of the fields with an empty string
      //    (*tlg)[Telegram_ANALYSE01::Name]          [i] = convertMessage("X",6,  "");
      //    (*tlg)[Telegram_ANALYSE01::Concentration] [i] = convertMessage("X",7,  "");        
      //  }
      //}  

      //(*tlg)[Telegram_ANALYSE01::Text]               = convertMessage("X",22, m_vRawMessageContent[22+(MsgRepeat-1)*2]);

      showContent((*tlg),m_typeReport,3);
      
      cCBS_StdLog_Task::getInstance()->writeLog("Tlg " + m_typeReport + " end",1);
      retVal = 0;
    }
    catch(...)
    {
      std::stringstream Message;
      Message << "CTelcom_InOracleTransport::SparcsToLF22(): Could not make telegramm ["<<m_typeReport<<"]";
      cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1); 
      retVal = -1;
    }
  }// if ( !m_typeReport.compare(std::string("ANALYSE-01")) )

  return retVal;
}// int CTelcom_InOracleTransport::SparcsToLF22()

int CTelcom_InOracleTransport::SamtracsToLF22()
{
  int retVal = -1;
  //std::basic_string <char>::size_type pos = -1;
  //plz look int the message description 9.1 // 
  // get sample id information (get_monsterid) Oracle funktion
  return retVal;
}

// put the message from Database into a vector and cut header
void CTelcom_InOracleTransport::setRawMessage(int headerLength)
{
  std::basic_string <char>::size_type posA = 0;
  std::basic_string <char>::size_type posB = 0;
  m_vRawMessageContent.clear();
  m_vRawMessageContent.resize(0);


  // cut header
  // std::string RawMessage = m_messageContent.substr(headerLength,m_messageContent.length());
  
  std::string RawMessage = m_messageContent;

  // only CSV is implemented! 
  // read the message to the end
  while (posB != RawMessage.length())
  {
    posB = RawMessage.find(",",posA);

    // if no seprator found then its the end of a string
    if ( std::string::npos == posB )
    {
      posB = RawMessage.length();
    }
    
    // if its comma seprated, drop the frist seprator
    if ( posB == 0 )
    {
      posA = posB+1;
      posB = RawMessage.find(",", posA);
    }    

    std::string message = RawMessage.substr(posA,(posB-posA));

    // separates the fields
    m_vRawMessageContent.push_back(message);

    posA = posB+1;
  }// while (posB != RawMessage.length()-1)
}

// Notify message (FEL)
std::string CTelcom_InOracleTransport::convertMessage(std::string messageFormat, int maxLength)
{ 
  std::string message = "";

  if (m_vRawMessageContent.size() > 1)
  {
    // see void CTelcom_InOracleTransport::setRawMessage(int headerLength)
    throw (cCBS_DBExc("CTelcom_InOracleTransport::convertMessage(): wrong Msg coding!\n"));
  }
  
  // 9 = numeric characters (left padded 0) "interger"
  if( !(messageFormat.compare("9")) )
  {    
    // If the maximum size of the array is exceeded
    if (maxLength > (int)m_vRawMessageContent[0].length() )
    {
      // store Msg
      message = m_vRawMessageContent[0];      
      int spacing = maxLength - message.length();

      for(int index=0; index < spacing; index++)
      {
        message = message.insert(0,"0");
      }

      // cut Msg
      m_vRawMessageContent[0].clear();
    }// if (maxLength > m_vRawMessageContent[0].length() )
    else
    {
      // store Msg
      message = m_vRawMessageContent[0].substr(0, maxLength);
      // cut Msg
      m_vRawMessageContent[0] = m_vRawMessageContent[0].substr(maxLength, m_vRawMessageContent[0].length());    
    }
  } // if( !(messageFormat.compare("9")) )

  // x = alphanumeric characters (right padded blanks) "string" 
  else if( !(messageFormat.compare("X")) )
  {
    // If the maximum size of the array is exceeded
    if (maxLength > (int)m_vRawMessageContent[0].length() )
    {
      // store Msg
      message = m_vRawMessageContent[0];
      int spacing = maxLength - message.length();

      for(int index=0; index < spacing; index++)
      {
        message = message.insert(message.length()," ");
      }
      // cut Msg
      m_vRawMessageContent[0].clear();
    }//  if (maxLength > m_vRawMessageContent[0].length() )
    else
    {
      // store Msg
      message = m_vRawMessageContent[0].substr(0, maxLength);
      // cut Msg
      m_vRawMessageContent[0] = m_vRawMessageContent[0].substr(maxLength, m_vRawMessageContent[0].length());    
    }
  } // if( !(messageFormat.compare("X")) )
  else
  {
    std::stringstream Message;
    Message << "CTelcom_InOracleTransport::convertMessage(): Warning: No messageformat";
    cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1);
  }
  return message;
}

// padded message left and right (CSV)
std::string CTelcom_InOracleTransport::convertMessage(std::string messageFormat, int maxLength, std::string fieldMessage)
{
  std::string message = "";
  int messageLength = fieldMessage.length();

  // if the maximum length of message is too short
  if (maxLength < messageLength)
  {
    maxLength = messageLength;
    std::stringstream Message;
    Message << "CTelcom_InOracleTransport::convertMessage(): Warning - Value: \"" << fieldMessage <<"\" to long";
    cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1);
  }   

  // 9 = numeric characters (left padded 0) "integer"
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
  } // if( !(messageFormat.compare("9")) )

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
  } // if( !(messageFormat.compare("X")) )
  else
  {
    std::stringstream Message;
    Message << "CTelcom_InOracleTransport::convertMessage(): Warning: No messageformat";
    cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1);
  }

  TestTlgLog << message;

  // see 2.5 example in the message description(CSV and FEL)
  fieldMessage.erase(0,maxLength);

  return message;
}// std::string CTelcom_InOracleTransport::convertMessage(std::string messageFormat, int maxLength, std::string fieldMessage)

