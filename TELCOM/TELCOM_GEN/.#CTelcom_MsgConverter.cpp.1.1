// Copyright (C) 2007 SMS Demag AG

#include "CTelcom_Msg.h"
#include "CTelcom_MsgTypeTranslator.h"
#include "FormatMgr.h"
#include "TCMessage.h"
#include "cCBS_StdLog_Task.h"
#include "cCBS_StdInitBase.h"
#include "CSMC_EventLogFrameController.h"
#include "CDateTime.h"
#include "CDataConversion.h"

#include "CTelcom_MsgConverter.h"

//##ModelId=45B0C3D502AD
CTelcom_MsgConverter::CTelcom_MsgConverter()
{
  m_WatchdogType = "";  
  m_LocalFormat  = "CSV";
  m_RemoteFormat = "FEL";

  cCBS_StdInitBase::getInstance()->replaceWithEntry("WatchdogThread","WatchdogType",m_WatchdogType);
}

//##ModelId=45B0C3D70011
CTelcom_MsgConverter::~CTelcom_MsgConverter()
{
}

//##ModelId=45B0C3F3012A
bool CTelcom_MsgConverter::fillTCMessage(CTelcom_Msg* telcommsg, TCMessage& tcmsg)
{
  bool retval = true;
  try
  {
    tcmsg.clear();                          // prepare for filling
    Tlg&  teltlg = *telcommsg->getTlg();
    // set Tlg loader to it with data from stream
    teltlg.setLoader(FormatMgr::instance()->getLoader (m_LocalFormat + "Converter"));
    cCBS_StdLog_Task::getInstance()->log("fillTCMessage: set loader: " + m_LocalFormat + "Converter",3);

    // Set some data that are not dependent on telegram-type
    //setApplicationHeaderData( *ptmpTlg );
    long  msglen = teltlg.getLen();

    // depends on telegram type we set here an message id.
    long MsgIDTrans = m_pMsgTypeTranslator->translate(teltlg.getId());
    std::string MsgID;

    if ( MsgIDTrans == 0 ) // translation failure
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "Message Translation", "CTelcom_MsgConverter::fillTCMessage", teltlg.getId().c_str() );
    }

    // translation must not be used, in this case use teltlg.getId() as MsgID
    // to make translation opsolete fill negative values into CTelcom_L3_InMsgTypeTranslator
    // e.g. insert("MSS101",-3201);        
    if ( MsgIDTrans < 0 )     
    {
      MsgID = teltlg.getId();
    }
    else
    {
      MsgID = CDataConversion::LongToString(MsgIDTrans);
    }


    if ( teltlg.hasElem("Header") )
    {
      if ( teltlg["Header"].hasElem("MessageLength") )
      {
        teltlg["Header"]["MessageLength"].set(msglen);
      }

      if ( teltlg["Header"].hasElem("MessageId") )
      {
        teltlg["Header"]["MessageId"].set(MsgID);
      }

      if ( teltlg["Header"].hasElem("MessageCount") )
      {
        teltlg["Header"]["MessageCount"] = telcommsg->getCounter();
      }

      if (teltlg["Header"].hasElem("UnitNo"))
      {
        teltlg["Header"]["UnitNo"].set(telcommsg->getPlantID());
      }
    }
    else
    {
      if ( teltlg.hasElem("MessageLength") )
      {
        teltlg["MessageLength"].set(msglen);
      }

      if ( teltlg.hasElem("MessageId") )
      {
        teltlg["MessageId"].set(MsgID);
      }

      //if ( teltlg.hasElem("MessageCount") )
      //{
      //  teltlg["MessageCount"] = telcommsg->getCounter();
      //}

      if ( teltlg.hasElem("UnitNo") )
      {
        teltlg["UnitNo"].set(telcommsg->getPlantID());
      }
    }

    std::string MsgType      = telcommsg->getType();

    if ( m_WatchdogType == MsgType )
    {
      CDateTime now;

      std::string strCreateTime = "CreateTime";

      if ( teltlg.hasElem(strCreateTime) )
      {
        if ( teltlg[strCreateTime].getType() == TlgElem::tArray  && teltlg[strCreateTime].countElems() == 8 )
        {
          teltlg[strCreateTime][0].set(now.getYear());
          teltlg[strCreateTime][1].set(now.getMonth());
          teltlg[strCreateTime][2].set(now.getDay());
          teltlg[strCreateTime][3].set(now.getHour());
          teltlg[strCreateTime][4].set(now.getMinute());
          teltlg[strCreateTime][5].set(now.getSecond());
          teltlg[strCreateTime][6].set(now.getMilliSecond());
          teltlg[strCreateTime][7].set(now.get_DST());
        }
        else if ( teltlg[strCreateTime].getType() == TlgElem::tString && teltlg[strCreateTime].countElems() == 0 )
        {
          teltlg[strCreateTime].set(now.toDBString());
        }
        else if ( teltlg[strCreateTime].getType() == TlgElem::tDateTime && teltlg[strCreateTime].countElems() == 0 ) //sankar
        {
          time_t t = now.asTime_T(); 

          tm *dt = localtime(&t);

          teltlg[strCreateTime].set ((*dt));
        }
		
      }
    }

    // in following method you can set test data for each tlg
    //setTestData(teltlg);

    // prepare to serialize into Caller's TCMessage defined as local format in ini file
    teltlg.setSerializer( FormatMgr::instance()->getSerializer(m_LocalFormat + "Converter"));
    cCBS_StdLog_Task::getInstance()->log("fillTCMessage: set serializer: " + m_LocalFormat + "Converter",3);

    teltlg.serialize(tcmsg.bufOstr());      // Copy the local message to user's TCMessage
    cCBS_StdLog_Task::getInstance()->log("fillTCMessage: serialized,",3);
    tcmsg.reset();                          // Prepare user's TCMessage for Reading
    tcmsg.setType(teltlg.getId());	        // set tlg type
    tcmsg.setSender(telcommsg->getSender());// set sender of tlg
  }
  catch (std::bad_alloc)
  {
    cCBS_StdLog_Task::getInstance()->log("Error allocating Memory for ptmpTlg", 1);
    retval = false;
  }
  catch (EElemNotFound &e)
  {
    std::stringstream Message;
    Message << "ERROR: fillTCMessage: " << e.what();
    cCBS_StdLog_Task::getInstance()->log(Message.str(), 1);
    retval = false;            // indicate error
  }
  catch (ETAMError &e)
  {
    std::stringstream Message;
    Message << "ERROR: fillTCMessage: " << e.what();
    cCBS_StdLog_Task::getInstance()->log(Message.str(), 1);
    retval = false;            // indicate error
  }
  catch (...)
  {
    cCBS_StdLog_Task::getInstance()->log("ERROR: fillTCMessage: Unknown exception!", 1);
    retval = false;            // indicate error
  }

  return retval;
}

//##ModelId=45B0E1EC033F
void CTelcom_MsgConverter::setLocalFormat(std::string& value)
{
	m_LocalFormat = value;
}

//##ModelId=45B0E209005B
void CTelcom_MsgConverter::setRemoteFormat(std::string& value)
{
	m_RemoteFormat = value;
}

//##ModelId=45B0F012013E
void CTelcom_MsgConverter::setMsgTypeTranslator(CTelcom_MsgTypeTranslator* value)
{
	m_pMsgTypeTranslator = value;
}

void CTelcom_MsgConverter::setTestData(Tlg& tlg)
{
    CDateTime now;

    std::string msgtype = tlg.getId();

    std::stringstream Message;
    Message << "Fill test data for  " << msgtype;
    cCBS_StdLog_Task::getInstance()->log(Message.str(), 2);

    if (msgtype == "L2LF03")        // Heat Announcement at LF
    {
      tlg["CreateTime"][0].set (now.getYear());
      tlg["CreateTime"][1].set (now.getMonth());
      tlg["CreateTime"][2].set (now.getDay());
      tlg["CreateTime"][3].set (now.getHour());
      tlg["CreateTime"][4].set (1L);
      tlg["CreateTime"][5].set (2L);
      tlg["CreateTime"][6].set (3L);
      tlg["CreateTime"][7].set (4L);

      tlg["HeatNo"]      = "abcdef";
      tlg["TreatId"]    = "ab";
      tlg["GradeId"]    = "abcdef";

      tlg["ProdDate"][0] = 1L;
      tlg["ProdDate"][1] = 2L;
      tlg["ProdDate"][2] = 3L;
      tlg["ProdDate"][3] = 4L;
      tlg["ProdDate"][4] = 5L;
      tlg["ProdDate"][5] = 6L;
      tlg["ProdDate"][6] = 7L;
      tlg["ProdDate"][7] = 8L;

      tlg["Shift"]      = 1l;
      tlg["Crew"]      = "ab";
      tlg["OperCode"]    = "abcd";

      tlg["DepTime"][0]    = 1L;
      tlg["DepTime"][1]    = 2L;
      tlg["DepTime"][2]    = 3L;
      tlg["DepTime"][3]    = 4L;
      tlg["DepTime"][4]    = 5L;
      tlg["DepTime"][5]    = 6L;
      tlg["DepTime"][6]    = 7L;
      tlg["DepTime"][7]    = 8L;

      tlg["LdlId"]      = 1l;
      tlg["LdlTareWgt"]    = 2l;
      tlg["LdlGrossWgt"]  = 3l;
      tlg["RouteCode"]    = "abcdefghijklmnopqrst";
      tlg["FreeSpare2"]    = 1l;
      tlg["FreeSpare3"]    = 2l;
      tlg["FreeSpare4"]    = 3l;
    }
    else if (msgtype == "L2LF05")       // Stirring Actual Setpoints
    {
      tlg["CreateTime"][0].set (now.getYear());
      tlg["CreateTime"][1].set (now.getMonth());
      tlg["CreateTime"][2].set (now.getDay());
      tlg["CreateTime"][3].set (now.getHour());
      tlg["CreateTime"][4].set (1L);
      tlg["CreateTime"][5].set (2L);
      tlg["CreateTime"][6].set (3L);
      tlg["CreateTime"][7].set (4L);

      tlg["HeatNo"]           = "abcdefgh";
      tlg["TreatId"]          = "ab";
      tlg["StirActivity"]     = 1l;
      tlg["StirGasType"]      = 2l;
      tlg["StirrInt"]         = 3l;

      tlg["FreeSpare1"]         = 4l;
      tlg["FreeSpare2"]         = 5l;
      tlg["FreeSpare3"]         = 6l;
      tlg["FreeSpare4"]         = 7l;
      tlg["FreeSpare5"]         = 8l;
    }
    else if (msgtype == "L2LF06")       // Heat Cancelled
    {
      tlg["CreateTime"][0].set (now.getYear());
      tlg["CreateTime"][1].set (now.getMonth());
      tlg["CreateTime"][2].set (now.getDay());
      tlg["CreateTime"][3].set (now.getHour());
      tlg["CreateTime"][4].set (1L);
      tlg["CreateTime"][5].set (2L);
      tlg["CreateTime"][6].set (3L);
      tlg["CreateTime"][7].set (4L);

      tlg["HeatNo"]         = "abcdefgh";
      tlg["TreatId"]        = "ab";

      tlg["FreeSpare1"]     = 1l;
      tlg["FreeSpare2"]     = 2l;
      tlg["FreeSpare3"]     = 3l;
      tlg["FreeSpare4"]     = 4l;
      tlg["FreeSpare5"]     = 5l;
    }
    else if (msgtype == "L2LF07")       // Computer Mode Availability
    {
      tlg["CreateTime"][0].set (now.getYear());
      tlg["CreateTime"][1].set (now.getMonth());
      tlg["CreateTime"][2].set (now.getDay());
      tlg["CreateTime"][3].set (now.getHour());
      tlg["CreateTime"][4].set (1L);
      tlg["CreateTime"][5].set (2L);
      tlg["CreateTime"][6].set (3L);
      tlg["CreateTime"][7].set (4L);

      tlg["HeatNo"]         = "abcdefgh";
      tlg["TreatId"]        = "ab";
      tlg["ElecMode"]       = 1l;
      tlg["StirMode"]       = 2l;
      tlg["MatMode"]        = 3l;

      tlg["FreeSpare1"]     = 4l;
      tlg["FreeSpare2"]     = 5l;
      tlg["FreeSpare3"]     = 6l;
      tlg["FreeSpare4"]     = 7l;
      tlg["FreeSpare5"]     = 8l;
    }
    else if (msgtype == "L2LF20")       // VoltageTap/RegCurve 
    {
      tlg["CreateTime"][0].set (now.getYear());
      tlg["CreateTime"][1].set (now.getMonth());
      tlg["CreateTime"][2].set (now.getDay());
      tlg["CreateTime"][3].set (now.getHour());
      tlg["CreateTime"][4].set (1L);
      tlg["CreateTime"][5].set (2L);
      tlg["CreateTime"][6].set (3L);
      tlg["CreateTime"][7].set (4L);

      tlg["HeatNo"]         = "abcdefgh";
      tlg["TreatId"]        = "ab";
      tlg["AimVoltTap"]     = 1l;
      tlg["AimRegCurve"]    = 2l;

      tlg["FreeSpare1"]     = 3l;
      tlg["FreeSpare2"]     = 4l;
      tlg["FreeSpare3"]     = 5l;
      tlg["FreeSpare4"]     = 6l;
      tlg["FreeSpare5"]     = 7l;
    }
    else if (msgtype == "L2LF22")       // Pull Electrodes 
    {
      tlg["CreateTime"][0].set (now.getYear());
      tlg["CreateTime"][1].set (now.getMonth());
      tlg["CreateTime"][2].set (now.getDay());
      tlg["CreateTime"][3].set (now.getHour());
      tlg["CreateTime"][4].set (1L);
      tlg["CreateTime"][5].set (2L);
      tlg["CreateTime"][6].set (3L);
      tlg["CreateTime"][7].set (4L);

      tlg["HeatNo"]         = "abcdefgh";
      tlg["TreatId"]    = "ab";

      tlg["FreeSpare1"]     = 1l;
      tlg["FreeSpare2"]     = 2l;
      tlg["FreeSpare3"]     = 3l;
      tlg["FreeSpare4"]     = 4l;
      tlg["FreeSpare5"]     = 5l;
    }
  else if (msgtype == "L2LF23")       // Release/Inhibit Electrodes  
  {
      tlg["CreateTime"][0].set (now.getYear());
      tlg["CreateTime"][1].set (now.getMonth());
      tlg["CreateTime"][2].set (now.getDay());
      tlg["CreateTime"][3].set (now.getHour());
      tlg["CreateTime"][4].set (1L);
      tlg["CreateTime"][5].set (2L);
      tlg["CreateTime"][6].set (3L);
      tlg["CreateTime"][7].set (4L);

      tlg["HeatNo"]        = "abcdefgh";
      tlg["TreatId"]       = "ab";
      tlg["RelFlag"]       = 1l;

      tlg["FreeSpare1"]    = 2l;
      tlg["FreeSpare2"]    = 3l;
      tlg["FreeSpare3"]    = 4l;
      tlg["FreeSpare4"]    = 5l;
      tlg["FreeSpare5"]    = 6l;
  } 
  else if (msgtype == "L2LF25")       // T/Sample measurement Request
  {
      tlg["CreateTime"][0].set (now.getYear());
      tlg["CreateTime"][1].set (now.getMonth());
      tlg["CreateTime"][2].set (now.getDay());
      tlg["CreateTime"][3].set (now.getHour());
      tlg["CreateTime"][4].set (1L);
      tlg["CreateTime"][5].set (2L);
      tlg["CreateTime"][6].set (3L);
      tlg["CreateTime"][7].set (4L);

      tlg["HeatNo"]         = "abcdefgh";
      tlg["TreatId"]        = "ab";
      tlg["MeasType"]       = 1l;
      tlg["FreeSpare1"]     = 2l;
  } 
  else if (msgtype == "L2LF30")       // Electric Process Pattern
  {
      tlg["CreateTime"][0].set (now.getYear());
      tlg["CreateTime"][1].set (now.getMonth());
      tlg["CreateTime"][2].set (now.getDay());
      tlg["CreateTime"][3].set (now.getHour());
      tlg["CreateTime"][4].set (1L);
      tlg["CreateTime"][5].set (2L);
      tlg["CreateTime"][6].set (3L);
      tlg["CreateTime"][7].set (4L);

      tlg["HeatNo"]       = "abcdefgh";
      tlg["TreatId"]      = "ab";
      tlg["StepID"]       = 1l;
      tlg["Enabled"]      = "ab";
      tlg["RemDurStep"]    = 1l;
      tlg["ElecEnerStep"] = 2l;
      tlg["TempEndStep"]  = 3l;
      tlg["AimVoltTap"]   = 4l;
      tlg["AimRegCurve"]  = 5l;

      tlg["FreeSpare1"]    = 6l;
      tlg["FreeSpare2"]    = 7l;
      tlg["FreeSpare3"]    = 8l;
      tlg["FreeSpare4"]    = 9l;
      tlg["FreeSpare5"]    = 1l;
  }
  else if (msgtype == "L2LF31")       // Stirring Pattern
  {
      tlg["CreateTime"][0].set (now.getYear());
      tlg["CreateTime"][1].set (now.getMonth());
      tlg["CreateTime"][2].set (now.getDay());
      tlg["CreateTime"][3].set (now.getHour());
      tlg["CreateTime"][4].set (1L);
      tlg["CreateTime"][5].set (2L);
      tlg["CreateTime"][6].set (3L);
      tlg["CreateTime"][7].set (4L);

      for(long i=0; i<19; i++)
      {
        tlg["NumCode"][i]    = i+1;
        tlg["Enabled"][i]    = "ab";
        tlg["Duration"][i]   = i+1;
        tlg["StirrInt"][i]  = i+1;
        tlg["GasFlow"][i]    = i+1;
        tlg["CStirGasType"][i]  = "ab";
        tlg["StepPriority"][i]  = i+1;
      }
  }
  else if (msgtype == "L2LF40")       // Model Parameter
  {
      tlg["CreateTime"][0].set (now.getYear());
      tlg["CreateTime"][1].set (now.getMonth());
      tlg["CreateTime"][2].set (now.getDay());
      tlg["CreateTime"][3].set (now.getHour());
      tlg["CreateTime"][4].set (1L);
      tlg["CreateTime"][5].set (2L);
      tlg["CreateTime"][6].set (3L);
      tlg["CreateTime"][7].set (4L);

      for(long i=0; i<19; i++)
        tlg["TreatStepPrior"][i]  = i+1;

      tlg["FreeSpare1"]    = 1l;
      tlg["FreeSpare2"]    = 2l;
      tlg["FreeSpare3"]    = 3l;
      tlg["FreeSpare4"]    = 4l;
      tlg["FreeSpare5"]    = 5l;
  }
  else if (msgtype == "L2LF70")       // Material Handling Model Result
  {
      tlg["CreateTime"][0].set (now.getYear());
      tlg["CreateTime"][1].set (now.getMonth());
      tlg["CreateTime"][2].set (now.getDay());
      tlg["CreateTime"][3].set (now.getHour());
      tlg["CreateTime"][4].set (now.getMinute());
      tlg["CreateTime"][5].set (now.getSecond());
      tlg["CreateTime"][6].set (now.getMilliSecond());
      tlg["CreateTime"][7].set (5L);

      tlg["HeatNo"]         = "abcdefgh";
      tlg["TreatId"]        = "ab";
      tlg["RecipeName"]     = 1l;
      tlg["BatchNo"]        = 2l;
      tlg["Source"]         = 3l;
      for(long i=0; i<80; i++)
        tlg["CalcMat"][i]  = i+1;
      
      tlg["FreeSpare1"]    = 1l;
      tlg["FreeSpare2"]    = 2l;
      tlg["FreeSpare3"]    = 3l;
      tlg["FreeSpare4"]    = 4l;
      tlg["FreeSpare5"]    = 5l;
  }
  else if (msgtype == "L2LF71")       // Material Availability Request
  {
      tlg["CreateTime"][0].set (now.getYear());
      tlg["CreateTime"][1].set (now.getMonth());
      tlg["CreateTime"][2].set (now.getDay());
      tlg["CreateTime"][3].set (now.getHour());
      tlg["CreateTime"][4].set (1L);
      tlg["CreateTime"][5].set (2L);
      tlg["CreateTime"][6].set (3L);
      tlg["CreateTime"][7].set (4L);

      tlg["FreeSpare1"]    = 1l;
      tlg["FreeSpare2"]    = 2l;
      tlg["FreeSpare3"]    = 3l;
      tlg["FreeSpare4"]    = 4l;
      tlg["FreeSpare5"]    = 5l;
  }
  else if (msgtype == "L2LF72")       // Plant Status Request
  {
      tlg["CreateTime"][0].set (now.getYear());
      tlg["CreateTime"][1].set (now.getMonth());
      tlg["CreateTime"][2].set (now.getDay());
      tlg["CreateTime"][3].set (now.getHour());
      tlg["CreateTime"][4].set (1L);
      tlg["CreateTime"][5].set (2L);
      tlg["CreateTime"][6].set (3L);
      tlg["CreateTime"][7].set (4L);

      tlg["FreeSpare1"]    = 1l;
      tlg["FreeSpare2"]    = 2l;
      tlg["FreeSpare3"]    = 3l;
      tlg["FreeSpare4"]    = 4l;
      tlg["FreeSpare5"]    = 5l;
  }

}
