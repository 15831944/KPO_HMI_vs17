//-------------------------------------------------------------------------------------------------
// 
//                           S M S  D e m a g  A G 
// 
//                            All Rights Reserved 
// 
// 
// project       : Email Server
// filename      : cEmailServer_EventHandlerTask.cpp 
// author        : Dominik Terhorst
// department    : EAM4
// creation date : 06-JUL-2010 
// description   : Eventchannel class for receiving of Email events.
// 
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// compile test log levels op to #9
#define _CLOG9

#include <iostream>
#include "cEmailServer_EventHandlerTask.h"
#include "cEmailServer_Comp.h"

// some CBS Includes to make compiler happy (need only cCBS_StdEventSenderTask but that requires more)
#include "cCBS_StdTask.h"
#include "cCBS_EvChannelSender.h"
#include "cCBS_StdEventSenderTask.h"

#include "CBS_Utilities\CBS_Clog.h"

#include "iEventData_s.hh"
#include "iEventMessages_s.hh"
#include "cCBS_StdInitBase.h" //SARS


using namespace System::Data;
using namespace System::Text;
using namespace Oracle::DataAccess::Client;
using namespace System::Runtime::InteropServices;
using namespace SendEmailOutlookSmtp;
using namespace HMI::SubProviders::Base;
//using namespace SMSSiemag::XPact::HMI::XPactCore::Utils::SQLOracle;
//using namespace SMSSiemag::XPact::HMI::XPactCore::Utils::SQL;
using namespace SMSSiemag::XPact::HMI::XPactCore::Utils;
using namespace SMSSiemag::XPact::HMI::XPactCore::Utils;
std::string MailId_HMD;
std::string MailId_LF;
std::string MailId_EAF;
std::string DbName;
std::string DbUser;
std::string DbPwd;
std::string GmailUser;
std::string GmailPwd;
std::string SendTrhughtGmail;
std::string FilePath;

std::string ReportSubject;
std::string ReportBody;

cEmailServerEventHdlTask::cEmailServerEventHdlTask (const char * channelName, const char * serviceName)	 : cCBS_StdEventHdlTask ()
{
  
}

cEmailServerEventHdlTask::~cEmailServerEventHdlTask(void)
{
}

void cEmailServerEventHdlTask::ownStartUp()
{
  cCBS_StdEventHdlTask::ownStartUp();

  setWorking(true);

  CLOG6(<< "ownStartUp performed!" << std::endl);
  m_cfb = cCBS_ConfigBase::getConfigBase();
  if (!m_cfb)
  {
    CLOG1("cCLM_Comp::createSubtasks(): ConfigBase not found !" << std::endl);
    return;
  }
  m_cfb->getActGrpEle("MAIL_HMD", "MAILID", MailId_HMD);
  m_cfb->getActGrpEle("MAIL_LF", "MAILID", MailId_LF);
  m_cfb->getActGrpEle("MAIL_EAF", "MAILID", MailId_EAF);
  m_cfb->getActGrpEle("DATABASE", "SMC_DBName", DbName);
  m_cfb->getActGrpEle("DATABASE", "SMC_DBUser", DbUser);
  m_cfb->getActGrpEle("DATABASE", "SMC_DBPassword", DbPwd);
  m_cfb->getActGrpEle("GMAIL_CONFIG", "GmailUser", GmailUser);
  m_cfb->getActGrpEle("GMAIL_CONFIG", "GmailPwd", GmailPwd);
  m_cfb->getActGrpEle("GMAIL_CONFIG", "SendTroughGmail", SendTrhughtGmail);
  m_cfb->getActGrpEle("REPORT_ROOT_PATH", "REPORT_PATH", FilePath);

  m_cfb->getActGrpEle("REPORT_ROOT_PATH", "REPORT_SUBJECT", ReportSubject);
  m_cfb->getActGrpEle("REPORT_ROOT_PATH", "REPORT_BODY", ReportBody);
	

	//SARS:: use of testing only
	//sleep(10);
	//String^ sBody = gcnew String("Heat Report");				
	//String^ sSub  = gcnew String("Heat Report... ");
	//String^ sReci  = gcnew String(MailId_LF.c_str());
	//String^ sGmailUser  = gcnew String(GmailUser.c_str());
	//String^ sGmailPwd  = gcnew String(GmailPwd.c_str());
	//String^ sFilePath  = gcnew String(FilePath.c_str());

	//SendEmailOutlookSmtp::SendEmail^ mm = gcnew SendEmailOutlookSmtp::SendEmail();	
	//mm->SendMail(sReci, sSub, sBody, sGmailUser, sGmailPwd,sFilePath);

	  //for testing purpose
		//String^ sBody = gcnew String("");
		//sBody = GetEmailBody("EAF","1");	
		//std::stringstream Message;
		//Message << "Message : " 
		//		    << ConvertString(sBody);
		//CLOG1(<<  Message.str() << std::endl);

}

void cEmailServerEventHdlTask::ownRunDown()
{
  setWorking(false);
  cCBS_Task::ownRunDown();
}

String^ cEmailServerEventHdlTask::GetEmailBody(String^ PlantName, String^ PlantNo)
{
	StringBuilder^  SQLcmd = gcnew StringBuilder("select Pdd.Plant,Pdd.plantno,Pdd.heatid,Pdd.treatid,Pdd.code,Gtd.Groupno,Gcd.GroupName,Gtd.delaydescr,Pdd.DelayStart,Pdd.Delayend,Pdd.Comment_operator");
    SQLcmd->Append(" , (select HEATID_CUST from PD_HEAT_PLANT_REF where heatid = Pdd.heatid and treatid = Pdd.treatid and plant = Pdd.plant) as HEATID_CUST,CALCDURATION(Pdd.Delayend,Pdd.DelayStart) as DURATION "); //SARS
  SQLcmd->Append(" from Pd_Delays Pdd, Gt_Delay_Code Gtd, Gc_Delay_Group Gcd ");
	SQLcmd->Append(" where Pdd.code = Gtd.delay_Code ");
	SQLcmd->Append(" and Pdd.Plant = Gtd.Plant ");
	SQLcmd->Append(" and Gtd.Groupno = Gcd.Groupno ");
	SQLcmd->Append(" and  Pdd.Plant = '");
	SQLcmd->Append(PlantName);
	SQLcmd->Append("' and  Pdd.Plantno = '");
	SQLcmd->Append(PlantNo);
	SQLcmd->Append("' and Pdd.REVTIME = (select max(pdda.revtime) from pd_delays pdda where pdda.plant ='");
	SQLcmd->Append(PlantName);
	SQLcmd->Append("' and pdd.EXPIRATIONDATE is null ");
	SQLcmd->Append(" and pdda.plantno = '");
	SQLcmd->Append(PlantNo);
	SQLcmd->Append("')");
	String^ sqlstring = gcnew String(SQLcmd->ToString());
	String^ sConnectionstring = gcnew String("user id=");
	String^ sdbUser  = gcnew String(DbUser.c_str());
	sConnectionstring = sConnectionstring + sdbUser;
	sConnectionstring = sConnectionstring + "; data source=";
	String^ sdbName  = gcnew String(DbName.c_str());
	sConnectionstring = sConnectionstring + sdbName;
	sConnectionstring = sConnectionstring + "; password=";
	String^ sDbPwd  = gcnew String(DbPwd.c_str());
	sConnectionstring = sConnectionstring + sDbPwd;
	OracleConnection^ Conn = gcnew OracleConnection(sConnectionstring);
	Conn->Open();
    OracleCommand^ cmd = gcnew OracleCommand(SQLcmd->ToString());
	cmd->CommandType = CommandType::Text;
	cmd->Connection = Conn;
	OracleDataAdapter^ Adptr = gcnew OracleDataAdapter(static_cast<OracleCommand ^>(cmd));
	System::Data::DataTable^ table1 = gcnew System::Data::DataTable();
	Adptr->Fill(table1);
	String^ sBody = gcnew String("Delay occurred in ");
	sBody = sBody + PlantName;
	sBody = sBody + PlantNo ;
	sBody = sBody + "\n" ;
	if (table1->Rows->Count > 0)
		{
			sBody = sBody + "Heat Id : ";
			//String^ Heatid = gcnew String(table1->Rows[0]["HEATID"]->ToString()); SARS
			String^ Heatid = gcnew String(table1->Rows[0]["HEATID_CUST"]->ToString());

			sBody = sBody + Heatid ;
			sBody = sBody + "\n" ;
			sBody = sBody + "Treat Id : ";
			String^ treatid = gcnew String(table1->Rows[0]["TREATID"]->ToString());
			sBody = sBody + treatid ;
			sBody = sBody + "\n" ;
			sBody = sBody + "GROUPNO : ";
			String^ groupno = gcnew String(table1->Rows[0]["GROUPNO"]->ToString());
			sBody = sBody + groupno ;
			sBody = sBody + "\n" ;
			sBody = sBody + "GROUPNAME : ";
			String^ groupname = gcnew String(table1->Rows[0]["GROUPNAME"]->ToString());
			sBody = sBody + groupname ;
			sBody = sBody + "\n" ;
			sBody = sBody + "CODE : ";
			String^ code = gcnew String(table1->Rows[0]["CODE"]->ToString());
			sBody = sBody + code ;
			sBody = sBody + "\n" ;
			sBody = sBody + "DELAYDESCR : ";
			String^ delaydescr = gcnew String(table1->Rows[0]["DELAYDESCR"]->ToString());
			sBody = sBody + delaydescr ;
			sBody = sBody + "\n" ;
			sBody = sBody + "DELAYSTART : ";
			String^ delaystart = gcnew String(table1->Rows[0]["DELAYSTART"]->ToString());
			sBody = sBody + delaystart ;
			sBody = sBody + "\n" ;
			sBody = sBody + "DELAYEND : ";
			String^ delayend = gcnew String(table1->Rows[0]["DELAYEND"]->ToString());
			sBody = sBody + delayend ;
			sBody = sBody + "\n" ;

			//SARS
			sBody = sBody + "DURATION(min) : ";
			String^ duration = gcnew String(table1->Rows[0]["DURATION"]->ToString());
			sBody = sBody + duration ;
			sBody = sBody + "\n" ;


			sBody = sBody + "COMMENT_OPERATOR : ";
			String^ Comment_opr = gcnew String(table1->Rows[0]["COMMENT_OPERATOR"]->ToString());
			sBody = sBody + Comment_opr ;
			sBody = sBody + "\n" ;
		}
	Conn->Close();
	return sBody;
}

void cEmailServerEventHdlTask::handleEvent(const FRIESEvent& Event)
{
    try
    {
		const sEventData* pData;
		if(Event.eventData >>= pData)
		{			
			String^ sMessage = gcnew String(pData->m_Message);
			String^ sHeatId = gcnew String(pData->m_HeatID);
			String^ sTreatId = gcnew String(pData->m_TreatID);
			String^ reportPlant = gcnew String(pData->m_PlantID);
			String^ reportType = gcnew String(pData->m_RelatedInformation);

			String^ pdataKey  = gcnew String(pData->m_DataKey);
			String^ now = System::DateTime::Now.ToString("dd.MM.yyyy HH:mm:ss");
			String^ sSender = gcnew String(pData->m_Sender);
			String^ sReceiver = gcnew String(pData->m_Receiver);
			String^ PlantName = gcnew String("");
			String^ PlantNo = gcnew String("");

			if (reportPlant == "LF_1")
			{
				PlantName = "LF";
				PlantNo = "1";
			}
			if (reportPlant == "EAF_1")
			{
				PlantName = "EAF";
				PlantNo = "1";
			}
			if (reportPlant == "HMD_1")
			{
				PlantName = "HMD";
				PlantNo = "1";
			}
			if (reportPlant == "HMD_2")
			{
				PlantName = "HMD";
				PlantNo = "2";
			}

			
			//SARS
			//String^ ReceiverName = "Tracking_"+ PlantName + "_" + PlantNo;
			String^ ReceiverName = "DH_L1_"+ PlantName + "_" + PlantNo + "_OUT";
			std::stringstream Message;
			Message << "Message : " 
				  << ConvertString(sMessage) 
					<< " comes from receiver : " 
					<< ConvertString(sReceiver);
			if ( (sMessage == gcnew String(LF_EvMsg::evLFDelayStatus))   || 
				   (sMessage == gcnew String(EAF_EvMsg::evEAFDelayStatus)) || 
				   (sMessage == gcnew String(HMD_EvMsg::evHMDDelayStatus)) || 
				   (sMessage == gcnew String("REPORT_GENERATED")) 
				 )
			{
			  CLOG1(<<  Message.str() << std::endl);
			}

			if (sMessage == gcnew String("REPORT_GENERATED") && sSender == "ReportServer")
			{

				SendEmailOutlookSmtp::SendEmail^ mm = gcnew SendEmailOutlookSmtp::SendEmail();
				String^ sBody = gcnew String("Please see attached file. Please do not reply to this auto-generated mail.");	
				String^ sSub  = gcnew String("  Report generated for ");
				sSub = reportType + sSub + PlantName;
				 
				String^ sEmailID = gcnew String("");
				if(PlantName == "HMD") sEmailID = gcnew String(MailId_HMD.c_str());
				if(PlantName == "EAF") sEmailID = gcnew String(MailId_EAF.c_str());
				if(PlantName == "LF")  sEmailID = gcnew String(MailId_LF.c_str());

				String^ sReci  = gcnew String(sEmailID);
				String^ sGmailUser  = gcnew String(GmailUser.c_str());
				String^ sGmailPwd  = gcnew String(GmailPwd.c_str());
				String^ sFilePath  = gcnew String(FilePath.c_str());
				mm->SendemailSmtp(sReci, sSub, sBody, sGmailUser, sGmailPwd,sFilePath,pdataKey,true);
			}


			if (sMessage == gcnew String(LF_EvMsg::evLFDelayStatus) && sReceiver == ReceiverName)
			{
				SendEmailOutlookSmtp::SendEmail^ mm = gcnew SendEmailOutlookSmtp::SendEmail();
				String^ sBody = gcnew String("");
				sBody = GetEmailBody(PlantName,PlantNo);
				String^ sSub  = gcnew String("Delay occurred in ");
				sSub = sSub + PlantName;
				sSub = sSub + PlantNo;
				String^ sReci  = gcnew String(MailId_LF.c_str());
				String^ sGmailUser  = gcnew String(GmailUser.c_str());
				String^ sGmailPwd  = gcnew String(GmailPwd.c_str());
				mm->SendemailSmtp(sReci, sSub, sBody, sGmailUser, sGmailPwd,"","",false);
			}
			if (sMessage == gcnew String(EAF_EvMsg::evEAFDelayStatus)  && sReceiver == ReceiverName)
			{
				SendEmailOutlookSmtp::SendEmail^ mm = gcnew SendEmailOutlookSmtp::SendEmail();
				String^ sBody = gcnew String("");
				sBody = GetEmailBody(PlantName,PlantNo);
				String^ sSub  = gcnew String("Delay occurred in ");
				sSub = sSub + PlantName;
				sSub = sSub + PlantNo;
				String^ sReci  = gcnew String(MailId_EAF.c_str());
				String^ sGmailUser  = gcnew String(GmailUser.c_str());
				String^ sGmailPwd  = gcnew String(GmailPwd.c_str());
				mm->SendemailSmtp(sReci, sSub, sBody, sGmailUser, sGmailPwd,"","",false);

			}
			if (sMessage == gcnew String(HMD_EvMsg::evHMDDelayStatus)  && sReceiver == ReceiverName)
			{
				SendEmailOutlookSmtp::SendEmail^ mm = gcnew SendEmailOutlookSmtp::SendEmail();
				String^ sBody = gcnew String("");
				sBody = GetEmailBody(PlantName,PlantNo);
				String^ sSub  = gcnew String("Delay occurred in ");
				sSub = sSub + PlantName;
				sSub = sSub + PlantNo;
				String^ sReci  = gcnew String(MailId_HMD.c_str());
				String^ sGmailUser  = gcnew String(GmailUser.c_str());
				String^ sGmailPwd  = gcnew String(GmailPwd.c_str());
				mm->SendemailSmtp(sReci, sSub, sBody, sGmailUser, sGmailPwd,"","",false);

				//test
				//std::vector<std::string> MailList;
				//cCBS_StdInitBase::getInstance()->replaceWithEntry("MAIL_HMD","MAILID",MailList);
				////m_cfb->replaceWithEntry("MAIL_HMD","MAILID",MailList);
				//if (!MailList.empty())
				//{
				//	std::vector<std::string>::iterator it;
				//	for ( it = MailList.begin(); it != MailList.end(); ++it)
				//	{						
				//		String^ recipe = gcnew String((*it).c_str());
				//		mm->SendemailSmtp(recipe, sSub, sBody, sGmailUser, sGmailPwd);
				//	}
				//}




			}
		}
	  }
    catch(...)
    {
			 CLOG1(<< "email server is unable to send message!" << std::endl);
    }

	
 
}


String^ cEmailServerEventHdlTask::ConvertString(const char* s)
{
	if(s == 0)
		return nullptr;
	return Marshal::PtrToStringAnsi(IntPtr((void*)s));
}

std::string cEmailServerEventHdlTask::ConvertString(String^ s)
{
	if(s == nullptr)
		return "";
	IntPtr p = Marshal::StringToHGlobalAnsi(s);
	std::string ret((const char*)p.ToPointer());
	Marshal::FreeHGlobal(p);
	return ret;
}
