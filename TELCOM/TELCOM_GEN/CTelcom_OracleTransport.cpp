 #include <sstream>
#include "CDateTime.h"

#include "cCBS_StdLog_Task.h"
#include "cCBS_StdInitBase.h"

#include "CTelcom_OracleTransport.h"


//##ModelId=4374B4F202FB
CTelcom_OracleTransport::CTelcom_OracleTransport()
: m_pStoredFunction(0)
{
  m_LocalMsgFormat  = "CSV";
  m_RemoteMsgFormat = "FEL";
  m_TraceLevel      = 2;
}

//##ModelId=4370C62002A3
CTelcom_OracleTransport::~CTelcom_OracleTransport()
{
}

//##ModelId=4373077803B5
void CTelcom_OracleTransport::configure(const std::string & section, bas::Configuration & c)
{
  // execute the configuration of the base class:
  AbstractTransport::configure(section, c);
  
  // go to needed section
  c.setSection("SMS_Transport");

  // configuration parameters 'DB' and 'service2':
  anlUser = c.gets("user");
  anlPassword = c.gets("password");
  anlService = c.gets("service", "");

  m_ConnectInfo = anlUser+":"+anlPassword+":"+anlService;

  //// safe temporary
  //std::string t = section;
  //c.setSection("SMS_Definition");
  //c.setSection(t);

  m_retryInterval = c.geti("RetryInterval",2);
  
  std::stringstream Message;
  Message << "Use analysis database: " << m_ConnectInfo;
  Message << ", database polling interval: " << m_retryInterval << " sec.";
  cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1);

  m_retryInterval = m_retryInterval * 1000; // 1s
}

//##ModelId=437307790012
int  CTelcom_OracleTransport::receive(TCMessage & msg)
{
  Sleep(m_retryInterval);
  return 0;
}

//##ModelId=437307790044
void CTelcom_OracleTransport::send(const TCMessage & msg)
{
}

//##ModelId=437307790076
int CTelcom_OracleTransport::doConnect()
{
  Sleep(1000);

  cCBS_StdInitBase *pStdInitBase = cCBS_StdInitBase::getInstance();
  
  if( !( pStdInitBase->getEntry("TRACING", "TraceLevel", m_TraceLevel) ) )
  {
    std::cerr << "Can not read trace settings from ini-file" << std::endl;
  }
  
  return 0;
}

//##ModelId=43730779008A
int CTelcom_OracleTransport::doDisconnect()
{
  int retval = 0;
  
  AbstractTransport::disconnect();
  return retval;
}



//##ModelId=4373077900A8
int CTelcom_OracleTransport::doListen()
{
  // there is no real Client or Server behaviour in File reading. Just read ...
  return doConnect();
}


void CTelcom_OracleTransport::setFactory(TlgFactory* Factory)
{
	m_pFactory = Factory;
}

void CTelcom_OracleTransport::setHeaderTlgType(std::string headName)
{
  headName = headName;
}

bool CTelcom_OracleTransport::showContent(Tlg& tlg, const std::string & MessageType, long level)
{
  if ( m_TraceLevel >= level && level >= 2)
  {
    int elno = tlg.countElems();
    for (int ii=0; ii<elno; ii++)
      logTelegram(tlg[ii], MessageType);

    return true;
  }
  return false;
}


bool CTelcom_OracleTransport::logTelegram(const TlgElem& te, const std::string & MessageType)
{
  bool retval = true;

  std::string stName = te.getName();
  //const char * elemName = stName.c_str();
  // if within a compound, there is no name. Use Parent's name instead
  const char * elemName = stName.c_str();
  if   (strlen(elemName) == 0)
    elemName = te.getParent()->getName().c_str();

  try 
  {
    switch (te.getType())
    {
    case TlgElem::tInteger:
      {
        std::stringstream Message;
        Message << "Content of " << MessageType << " - Name: " << stName << " - Value: " << te.asInteger();
        cCBS_StdLog_Task::getInstance()->log(Message.str(), 2);
        break;
      }
    case TlgElem::tNumber:
      {
        std::stringstream Message;
        Message << "Content of " << MessageType << " - Name: " << stName << " - Value: " << te.asNumber();
        cCBS_StdLog_Task::getInstance()->log(Message.str(), 2);
        break;
      }
    case TlgElem::tBool:
      {
        std::stringstream Message;
        Message << "Content of " << MessageType << " - Name: " << stName << " - Value: " <<te.asInteger()? true:false;
        cCBS_StdLog_Task::getInstance()->log(Message.str(), 2);
        break;
      }
    case TlgElem::tString:
      {
        std::stringstream Message;
        Message << "Content of " << MessageType << " - Name: " << stName << " - Value: " << te.asString().c_str();
        cCBS_StdLog_Task::getInstance()->log(Message.str(), 2);
        break;
      }
    case TlgElem::tDateTime:
      {
        // HERE SOMETHING IS STILL MISSING. LOOKS LIKE
        // sDate dateStruct = ;  // and fill this structure somehow, then
        //pCorbaInf->setDate (DataKey.c_str(), elemName, dateStruct);
      }
      break;
    case TlgElem::tArray:
      // Distinguish Array of Compounds from Array of primitives
      {
        int ndim = te.countElems();               // Get Dimension
        if   (ndim >1 && te.getElem(0).countElems() >1)
        {
          // we have an array of compounds
          // fill sequence of <compound type> 
          // AT THE TIME BEING, THIS DOES NOT EXIST IN BAS INTERFACE 
          cCBS_StdLog_Task::getInstance()->log("ERROR: This kind of type is not treated!",2);
          //////////////////////////////////////////////////////////////
        }
        else
        {
          // we have an array of primitives: make sequence of <primitive type>
          // and put into Corba ANY
          switch (te.getElem(0).getType())    // depend on type of 1st element
          {
          case TlgElem::tInteger:
            {
              DEF::seqLong ls;
              ls.length(ndim);
              for (int ii=0; ii<ndim; ii++)
              {
                std::stringstream Message;
                Message << "Content of " << MessageType << " - Name: " << stName << " - Value[" << ii << "]: " << te.getElem(ii).asInteger();
                cCBS_StdLog_Task::getInstance()->log(Message.str(), 2);
              }
            }
            break;
          case TlgElem::tDateTime:
            {
              std::vector<std::string> stdVector; 
              for (int ii=0; ii<ndim; ii++)
              {
                std::stringstream Message;
                Message << "Content of " << MessageType << " - Name: " << stName << " - Value[" << ii << "]: " << te.getElem(ii).asString();
                cCBS_StdLog_Task::getInstance()->log(Message.str(), 2);
              }
            }
            break;
          case TlgElem::tNumber:
            {
              DEF::seqDouble ls;
              ls.length(ndim);
              for (int ii=0; ii<ndim; ii++)
              {
                std::stringstream Message;
                Message << "Content of " << MessageType << " - Name: " << stName << " - Value[" << ii << "]: " << te.getElem(ii).asNumber();
                cCBS_StdLog_Task::getInstance()->log(Message.str(), 2);
              }
            }
            break;
          case TlgElem::tBool:
            {
              DEF::seqBoolean  ls;
              ls.length(ndim);
              for (int ii=0; ii<ndim; ii++)
              {
                std::stringstream Message;
                Message << "Content of " << MessageType << " - Name: " << stName << " - Value[" << ii << "]: " << te.getElem(ii).asNumber()? true:false;
                cCBS_StdLog_Task::getInstance()->log(Message.str(), 2);
              }
            }
            break;
          case TlgElem::tString:
            {
              DEF::seqString ls;
              ls.length(ndim);
              for (int ii=0; ii<ndim; ii++)
              {
                std::stringstream Message;
                Message << "Content of " << MessageType << " - Name: " << stName << " - Value[" << ii << "]: " << te.getElem(ii).asString();
                cCBS_StdLog_Task::getInstance()->log(Message.str(), 2);
              }
            }
            break;
          default:
            cCBS_StdLog_Task::getInstance()->log("Invalid Message Definition: Array of Compounds...", 1);
            break;
          } // end switch (te.getElem(0).getType())
        }
      }
      break;
    case TlgElem::tRecord:
      // Here only if it's not within an array of records.
      {
        int nelems = te.countElems(); 
        for (int ii=0; ii<nelems; ii++)
          logTelegram(te.getElem(ii), MessageType);
      }

      break;
    default:
      break;
    } // END   switch (te.getType())
  }
  catch (...)
  {
    std::stringstream Message;
    Message << "Could log TelegramElement " << te.getName() << "," << te.getPath();
    cCBS_StdLog_Task::getInstance()->log(Message.str(), 1);
    retval = false;
  }
  return retval;
}


