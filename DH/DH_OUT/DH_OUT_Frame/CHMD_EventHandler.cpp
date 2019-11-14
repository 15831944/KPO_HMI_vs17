// Copyright (C) 2006 SMS Demag AG Germany
#include "CHMD_EventHandler.h"


#include "iDH_Telcom_s.hh"
#include "CDH_OUT_Task.h"
#include "CDateTime.h"
#include "CDH_OUT_Task.h"
#include "CDH_OUT_Telcom_Impl.h"
#include "CEventHandler.h"
#include "CEventMessage.h"
#include "IData_Provider_s.hh"
#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"


#include "Telcom_Out_s.hh"

// db classes
#include "CGC_Recipe_L1Container.h"
#include "CGC_Plant_Container.h"
#include "CHeatDataConverter.h"
#include "CGC_SourceContainer.h"
#include "CPD_Heat_data.h"
#include "CPP_HEAT_PLANT.h"
#include "CPP_HEAT.h"
#include "CPD_LADLE.h"
#include "CPD_PLANTSTATUS.h"
#include  "CPDH_HM_DATA.h"
#include "CGC_Plantgroup_Container.h"
#include "CGT_MAT_PURP.h"
#include "DEF_GT_PURP.h"
#include "DEF_GC_PLANT.h"

//##ModelId=4582C01C025D
CHMD_EventHandler::CHMD_EventHandler( )
{
  try
  {
		cCBS_StdConnection* pConnection = CDH_OUT_Task::getInstance()->getStdConnection();
    if (pConnection)
    {
      AppString = " ";

      m_pHeatDataConverter= new CHeatDataConverter    (pConnection);
      m_pPlantIdConverter = new CGC_Plant_Container   (pConnection);
      pPD_LADLE           = new CPD_LADLE             (pConnection);
			pPD_PlantStatus     = new CPD_PLANTSTATUS				(pConnection);
      pPP_HEAT_PLANT      = new CPP_HEAT_PLANT        (pConnection);
      pPP_HEAT            = new CPP_HEAT              (pConnection);
      pGT_Mat_Purp        = new CGT_MAT_PURP          (pConnection);
			pPDH_HM_Data				= new CPDH_HM_DATA						(pConnection);
			m_pGC_Plantgroup_Container = new CGC_Plantgroup_Container(pConnection);
			m_pGT_MAT_PURP             = new CGT_MAT_PURP(pConnection);
    }
    else
      log("ERROR: No connection from CDH_Task!",3);

    m_pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    m_SenderName = cCBS_StdInitBase::getInstance()->m_ServerName;
    m_DestinationName = "";

    cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage","SenderName",m_SenderName);
    cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage","DestinationName",m_DestinationName);

		//sankar
		long OracleTransfer = 1;
    cCBS_StdInitBase::getInstance()->replaceWithEntry("UseOracleTransfer", "OracleTransfer"  , OracleTransfer);
		if(OracleTransfer == 1)
			UseOracleTransfer = true;
		else
			UseOracleTransfer = false;


  }
  catch(...) 
  {
    cCBS_StdEventLogFrame EventLog;
    sEventLogMessage sMessage = cCBS_StdEventLogFrame::initMessage(__FILE__,__LINE__);
    EventLog.EL_ExceptionCaught(sMessage,"", "CHMD_EventHandler::CHMD_EventHandler","");
    throw;
  }
  // ToDo: Add your specialized code here and/or call the base class
}

//##ModelId=4582C01D013C
CHMD_EventHandler::~CHMD_EventHandler()
{
	// ToDo: Add your specialized code here and/or call the base class
  if(m_pHeatDataConverter)        {delete m_pHeatDataConverter;           m_pHeatDataConverter = 0;          }
  if(m_pPlantIdConverter)         {delete m_pPlantIdConverter;            m_pPlantIdConverter = 0;           }
  if(pPD_LADLE)                   {delete pPD_LADLE;                      pPD_LADLE = 0;                     }
  if(pPD_PlantStatus)             {delete pPD_PlantStatus;                pPD_PlantStatus = 0;               }
  if(pPP_HEAT_PLANT)              {delete pPP_HEAT_PLANT;                 pPP_HEAT_PLANT = 0;                }
  if(pPP_HEAT)                    {delete pPP_HEAT;                       pPP_HEAT = 0;                      }
  if(pGT_Mat_Purp)                {delete pGT_Mat_Purp;                   pGT_Mat_Purp = 0;                  }
  if(pPDH_HM_Data)                {delete pPDH_HM_Data;                   pPDH_HM_Data = 0;                  }
  if(m_pGC_Plantgroup_Container)  {delete m_pGC_Plantgroup_Container;     m_pGC_Plantgroup_Container = 0;    }
  if(m_pGT_MAT_PURP)              {delete m_pGT_MAT_PURP;                 m_pGT_MAT_PURP = 0;                }
	 
}

//##ModelId=4587AA8300F3
bool CHMD_EventHandler::handleEvent(CEventMessage& evMessage)
{
  bool RetValue = true;
  CEventMessage ActEvent(evMessage);
  std::string ActMessage = ActEvent.getMessage();

  if (ActMessage == HMD_EvMsg::evHMDHeatAnnouncement)
  {
    RetValue  = provideData_L2HM03(evMessage); 
  }
  else if (ActMessage == HMD_EvMsg::evHMDHeatCancellation)
  {
    RetValue  = provideData_L2HM06(evMessage);
  }
  else if(ActMessage == HMD_EvMsg::evHMDModelResult)
  {
    RetValue  = provideData_L2HM07(evMessage);
    RetValue  = provideData_L2HM25(evMessage);  ///open for JSW
    RetValue  = provideData_L2HM30(evMessage);
  }
  else if ((ActMessage == HMD_EvMsg::evHMDSetComputerModeOn)||(ActMessage == HMD_EvMsg::evHMDSetComputerModeOff))
  {
    RetValue  = provideData_L2HM07(evMessage);
  }
  else if (ActMessage == HMD_EvMsg::evHMDRequestMatAvail)
  {
    RetValue  = provideData_L2HM71(evMessage);
  }
  else if (ActMessage == HMD_EvMsg::evHMDPlantStatusRequest)
  {
    RetValue  = provideData_L2HM72(evMessage);
  }
  return  RetValue;
}


//Heat Anounncement at HMD
bool CHMD_EventHandler::provideData_L2HM03 (CEventMessage& Event)
{
  bool retval = true; 
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = ProductID;
  std::string PlantID   = Event.getPlantID();
  std::string Plant     = m_pPlantIdConverter->getPlant(PlantID);
  std::string L1PlantID = CDataConversion::LongToString(m_pPlantIdConverter->getL1PlantID(PlantID));
	long PlantNo = m_pPlantIdConverter->getL1PlantID(PlantID);

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  try
  {
    if (m_pTelcom_Interface)
    {
      log("### L2HM03: Entry",3);
      std::string TlgType   = std::string("L2HD03");
      std::string DataKeyL1 = m_pTelcom_Interface->generateDataKey(TlgType);

			CDateTime now;
      m_pTelcom_Interface->setAny(DataKeyL1.c_str(), Telegram_L2HD03::CreateTime, now.asCORBAAny());

      double dLdlTareWgt = 0.;
      double dLdlGrossWgt = 0.;
      
			m_pTelcom_Interface->setString (DataKeyL1.c_str(),Telegram_L2HD03::HeatNo, HeatID.c_str() );
			m_pTelcom_Interface->setString (DataKeyL1.c_str(),Telegram_L2HD03::TreatId, TreatID.c_str() );
      m_pTelcom_Interface->setString (DataKeyL1.c_str(),Telegram_L2HD03::GradeId, "" );
			m_pTelcom_Interface->setString(DataKeyL1.c_str(), Telegram_L2HD03::RouteCode, "E1L1");
			m_pTelcom_Interface->setAny(DataKeyL1.c_str(), Telegram_L2HD03::ProdDate, now.asCORBAAny());			
		  m_pTelcom_Interface->setString(DataKeyL1.c_str(), Telegram_L2HD03::OperCode, "OPR");
		
			if(pPD_PlantStatus->select(Plant,PlantNo,1))      
      {
					m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD03::LdlId, pPD_PlantStatus->getLADLENO(1));    
	        					
					if(pPD_LADLE->select(pPD_PlantStatus->getLADLENO(1),pPD_PlantStatus->getLADLETYPE(1)))
					{
						dLdlTareWgt = pPD_LADLE->getTAREWEIGHT(1);
						if (dLdlTareWgt != CSMC_DBData::unspecDouble)
						{
							m_pTelcom_Interface->setDouble(DataKeyL1.c_str(), Telegram_L2HD03::LdlTareWgt, dLdlTareWgt);
						}
						
					}
				}

     

			if(pPDH_HM_Data->select(HeatID,TreatID,Plant))
			{
				double sAim = pPDH_HM_Data->getAIM_S_OPER(1);
				double sAct = pPDH_HM_Data->getAIM_S_GRADE(1) ;
				long TEMP = pPDH_HM_Data->getTEMP_INITIAL(1);
				dLdlGrossWgt = pPDH_HM_Data->getHM_WEIGHT_START(1) + dLdlTareWgt;

				CDateTime planEndTime  = pPDH_HM_Data->getTREATEND_PLAN(1);
				m_pTelcom_Interface->setAny(DataKeyL1.c_str(), Telegram_L2HD03::DepTime, planEndTime.asCORBAAny());
			  m_pTelcom_Interface->setString(DataKeyL1.c_str(), Telegram_L2HD03::Shift, pPDH_HM_Data->getSHIFT_CODE(1));
		    m_pTelcom_Interface->setString (DataKeyL1.c_str(),Telegram_L2HD03::Crew, pPDH_HM_Data->getCREW_CODE(1) );
			
				m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD03::FreeSpare2, sAim * 10000); //as per TATA
				m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD03::FreeSpare3, sAct * 10000); //as per TATA
				m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD03::FreeSpare4, TEMP); //as per TATA
				m_pTelcom_Interface->setDouble(DataKeyL1.c_str(), Telegram_L2HD03::LdlGrossWgt, dLdlGrossWgt);
			}
			else
			{
				m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD03::FreeSpare2, 0);
				m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD03::FreeSpare3, 0);
				m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD03::FreeSpare4, 0);
			}

      m_pTelcom_Interface->complete(DataKeyL1.c_str(),DataKeyL1.c_str() );
      m_pTelcom_Interface->showContent(DataKeyL1.c_str(),1);

			
      CEventMessage MstToL1Sender(m_SenderName, 
        m_DestinationName, 
        std::string("TELEGRAM_") + TlgType, 
        std::string ("UNUSED"), 
        std::string ("UNUSED"),
        false,
        HeatID,
        TreatID,
        DataKeyL1);

        MstToL1Sender.setPlantID(L1PlantID);
				MstToL1Sender.setHeatID(HeatID);
				MstToL1Sender.setTreatID(TreatID);
        MstToL1Sender.dispatch(m_SenderName,m_DestinationName);
				
    }
    else
    {
      retval=false;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc,
      "CHMD_EventHandler::provideData_L2HM03",
      Action);
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc,
      "CHMD_EventHandler::provideData_L2HM03",
      Action);
  } 
  catch(...)
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException("CHMD_EventHandler::provideData_L2HM03",
      Action);
  }

  return retval;
}



//Heat Cancelled
bool CHMD_EventHandler::provideData_L2HM06 (CEventMessage& Event)
{
  bool retval = true;
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string Plant     = m_pPlantIdConverter->getPlant(PlantID);
  std::string L1PlantID = CDataConversion::LongToString(m_pPlantIdConverter->getL1PlantID(PlantID));

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  try
  {
    if (m_pTelcom_Interface)
    {
      log("### L2HM06: Entry",3);
      std::string TlgType   = std::string ("L2HD06");
      std::string DataKeyL1 = m_pTelcom_Interface->generateDataKey(TlgType);

      m_pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(), DM::EVENT);

      CDateTime now;
      m_pTelcom_Interface->setAny(DataKeyL1.c_str(), Telegram_L2HD06::CreateTime, now.asCORBAAny());

      m_pTelcom_Interface->setString(DataKeyL1.c_str(),Telegram_L2HD06::HeatNo, HeatID.c_str());
      m_pTelcom_Interface->setString(DataKeyL1.c_str(),Telegram_L2HD06::TreatId,TreatID.c_str()); 
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD06::FreeSpare1, 0);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD06::FreeSpare2, 0);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD06::FreeSpare3, 0);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD06::FreeSpare4, 0);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD06::FreeSpare5, 0);

      m_pTelcom_Interface->complete(DataKeyL1.c_str(),DataKeyL1.c_str() );
      m_pTelcom_Interface->showContent(DataKeyL1.c_str(),1);

      CEventMessage MstToL1Sender(m_SenderName, 
        m_DestinationName, 
        std::string("TELEGRAM_") + TlgType, 
        std::string ("UNUSED"), 
        std::string ("UNUSED"),
        false,
        HeatID,
        TreatID,
        DataKeyL1);

      MstToL1Sender.setPlantID(L1PlantID);
      MstToL1Sender.dispatch(m_SenderName,m_DestinationName);
    }
    else
    {
      retval=false;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc,
      "CHMD_EventHandler::provideData_L2HM06",
      Action);
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc,
      "CHMD_EventHandler::provideData_L2HM06",
      Action);
  } 
  catch(...)
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException("CHMD_EventHandler::provideData_L2HM06",
      Action);
  }

  return retval;
}


//Computer Mode Availability
bool CHMD_EventHandler::provideData_L2HM07 (CEventMessage& Event)
{
  bool retval = true;
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = ProductID;
  std::string PlantID   = Event.getPlantID();
  std::string Plant     = m_pPlantIdConverter->getPlant(PlantID);
  std::string L1PlantID = CDataConversion::LongToString(m_pPlantIdConverter->getL1PlantID(PlantID));


  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  try
  {
    if (m_pTelcom_Interface)
    {
      log("### L2HM07: Entry",3);
      std::string TlgType   = std::string ("L2HD07");
      std::string DataKeyL1 = m_pTelcom_Interface->generateDataKey(TlgType);

      CDateTime now;
      m_pTelcom_Interface->setAny(DataKeyL1.c_str(), Telegram_L2HD07::CreateTime, now.asCORBAAny());
      m_pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(), DM::PRODUCT);
      seqComputerModes scm = CIntfData::ToCORBAType(m_pDM_Interface->getComputerModes (ProductID.c_str(), DATA::ComputerModeAvail));
      log(CIntfData::getContent(CIntfData::ToAny(scm)),2);

      long Mode = 0l;      

      long lng = CIntfData::getLength(scm);
      for (long ii=0; ii<lng; ii++)
      {
        sComputerMode cm;
        CIntfData::getAt(cm, scm, ii);
				if ((std::string(cm.Device) == std::string (DEF_COMP_MODES::MatHandleModel)))
          Mode = cm.Status;
      }

      // write data to TELCOM_Interface
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD07::Mode, Mode);

      m_pTelcom_Interface->setString(DataKeyL1.c_str(),Telegram_L2HD07::HeatNo, HeatID.c_str());
      m_pTelcom_Interface->setString(DataKeyL1.c_str(),Telegram_L2HD07::TreatId,TreatID.c_str()); 
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD07::FreeSpare1, 0);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD07::FreeSpare2, 0);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD07::FreeSpare3, 0);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD07::FreeSpare4, 0);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD07::FreeSpare5, 0);

      m_pTelcom_Interface->complete(DataKeyL1.c_str(),DataKeyL1.c_str() );
      m_pTelcom_Interface->showContent(DataKeyL1.c_str(),1);

      CEventMessage MstToL1Sender(m_SenderName, 
        m_DestinationName, 
        std::string("TELEGRAM_") + TlgType, 
        std::string ("UNUSED"), 
        std::string ("UNUSED"),
        false,
        HeatID,
        TreatID,
        DataKeyL1);
  
      MstToL1Sender.setPlantID(L1PlantID);
      MstToL1Sender.dispatch(m_SenderName,m_DestinationName);
    }
    else
    {
      retval=false;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc,
      "CHMD_EventHandler::provideData_L2HM07",
      Action);
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc,
      "CHMD_EventHandler::provideData_L2HM07",
      Action);
  } 
  catch(...)
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException("CHMD_EventHandler::provideData_L2HM07",
      Action);
  }

  return retval;
}

bool CHMD_EventHandler::provideData_L2HM25 (CEventMessage& Event)
{
  bool retval = true;
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = ProductID;
  std::string PlantID   = Event.getPlantID();
  std::string Plant     = m_pPlantIdConverter->getPlant(PlantID);
  std::string L1PlantID = CDataConversion::LongToString(m_pPlantIdConverter->getL1PlantID(PlantID));

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  try
  {
    if (m_pTelcom_Interface)
    {
      log("### L2HM25: Entry",3);
      std::string TlgType   = std::string("L2HD25");
      std::string DataKeyL1 = m_pTelcom_Interface->generateDataKey(TlgType);

      CDateTime now;
      m_pTelcom_Interface->setAny(DataKeyL1.c_str(), Telegram_L2HD25::CreateTime, now.asCORBAAny());

      // write data to TELCOM_Interface
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD25::MeasType, 4);
      m_pTelcom_Interface->setString(DataKeyL1.c_str(),Telegram_L2HD25::HeatNo, HeatID.c_str());
      m_pTelcom_Interface->setString(DataKeyL1.c_str(),Telegram_L2HD25::TreatId,TreatID.c_str()); 
			
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD25::FreeSpare1, 0);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD25::FreeSpare2, 0);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD25::FreeSpare3, 0);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD25::FreeSpare4, 0);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD25::FreeSpare5, 0);

      m_pTelcom_Interface->complete(DataKeyL1.c_str(),DataKeyL1.c_str() );
      m_pTelcom_Interface->showContent(DataKeyL1.c_str(),1);

      CEventMessage MstToL1Sender(m_SenderName, 
        m_DestinationName, 
        std::string("TELEGRAM_") + TlgType, 
        std::string ("UNUSED"), 
        std::string ("UNUSED"),
        false,
        HeatID,
        TreatID,
        DataKeyL1);

      MstToL1Sender.setPlantID(L1PlantID);
      MstToL1Sender.dispatch(m_SenderName,m_DestinationName);
      
    }
    else
    {
      retval=false;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc,
      "CHMD_EventHandler::provideData_L2HM25",
      Action);
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc,
      "CHMD_EventHandler::provideData_L2HM25",
      Action);
  } 
  catch(...)
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException("CHMD_EventHandler::provideData_L2HM25",
      Action);
  }

  return retval;
}


//Material Availability Request
bool CHMD_EventHandler::provideData_L2HM71 (CEventMessage& Event)
{
  bool retval = true;
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = ProductID;
  std::string PlantID   = Event.getPlantID();
  std::string Plant     = m_pPlantIdConverter->getPlant(PlantID);
  std::string L1PlantID = CDataConversion::LongToString(m_pPlantIdConverter->getL1PlantID(PlantID));

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  try
  {
    if (m_pTelcom_Interface)
    {
      log("### L2HM71: Entry",3);
      std::string TlgType   = std::string ("L2HD71");
      std::string DataKeyL1 = m_pTelcom_Interface->generateDataKey(TlgType);

      CDateTime now;
      m_pTelcom_Interface->setAny(DataKeyL1.c_str(), Telegram_L2HD71::CreateTime, now.asCORBAAny());

      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD71::FreeSpare1, 0);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD71::FreeSpare2, 0);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD71::FreeSpare3, 0);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD71::FreeSpare4, 0);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD71::FreeSpare5, 0);

      m_pTelcom_Interface->complete(DataKeyL1.c_str(),DataKeyL1.c_str() );
      m_pTelcom_Interface->showContent(DataKeyL1.c_str(),1);

      CEventMessage MstToL1Sender(m_SenderName, 
        m_DestinationName, 
        std::string("TELEGRAM_") + TlgType, 
        std::string ("UNUSED"), 
        std::string ("UNUSED"),
        false,
        HeatID,
        TreatID,
        DataKeyL1);

      MstToL1Sender.setPlantID(L1PlantID);
      MstToL1Sender.dispatch(m_SenderName,m_DestinationName);
    }
    else
    {
      retval=false;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc,
      "CHMD_EventHandler::provideData_L2HM71",
      Action);
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc,
      "CHMD_EventHandler::provideData_L2HM71",
      Action);
  } 
  catch(...)
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException("CHMD_EventHandler::provideData_L2HM71",
      Action);
  }

  return retval;
}

//Plant Status Request
bool CHMD_EventHandler::provideData_L2HM72 (CEventMessage& Event)
{
  bool retval = true;
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = ProductID;
  std::string PlantID   = Event.getPlantID();
  std::string Plant     = m_pPlantIdConverter->getPlant(PlantID);
  std::string L1PlantID = CDataConversion::LongToString(m_pPlantIdConverter->getL1PlantID(PlantID));

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  try
  {
    if (m_pTelcom_Interface)
    {
      log("### L2HM72: Entry",3);
      std::string TlgType   = std::string ("L2HD72");
      std::string DataKeyL1 = m_pTelcom_Interface->generateDataKey(TlgType);

      CDateTime now;
      m_pTelcom_Interface->setAny(DataKeyL1.c_str(), Telegram_L2HD72::CreateTime, now.asCORBAAny());

      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD72::FreeSpare1, 0);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD72::FreeSpare2, 0);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD72::FreeSpare3, 0);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD72::FreeSpare4, 0);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD72::FreeSpare5, 0);

      m_pTelcom_Interface->complete(DataKeyL1.c_str(),DataKeyL1.c_str() );
      m_pTelcom_Interface->showContent(DataKeyL1.c_str(),1);

      CEventMessage MstToL1Sender(m_SenderName, 
        m_DestinationName, 
        std::string("TELEGRAM_") + TlgType, 
        std::string ("UNUSED"), 
        std::string ("UNUSED"),
        false,
        HeatID,
        TreatID,
        DataKeyL1);

      MstToL1Sender.setPlantID(L1PlantID);
      MstToL1Sender.dispatch(m_SenderName,m_DestinationName);
    }
    else
    {
      retval=false;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc,
      "CHMD_EventHandler::provideData_L2HM72",
      Action);
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc,
      "CHMD_EventHandler::provideData_L2HM72",
      Action);
  } 
  catch(...)
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException("CHMD_EventHandler::provideData_L2HM72",
      Action);
  }

  return retval;
}

////Treatment Pattern
bool CHMD_EventHandler::provideData_L2HM30 (CEventMessage& Event)
{
  bool retval = true;
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = ProductID;
  std::string PlantID   = Event.getPlantID();
  std::string Plant     = m_pPlantIdConverter->getPlant(PlantID);
  std::string L1PlantID = CDataConversion::LongToString(m_pPlantIdConverter->getL1PlantID(PlantID));	
  long        PlantNo   = m_pPlantIdConverter->getPlantNo(PlantID);

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  try
  {
    m_pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(), DM::PRODUCT);

		long UnitGroupNo = m_pGC_Plantgroup_Container->getUnitGroupNo(Plant);
		std::string LimeCode = m_pGT_MAT_PURP->getRelatedMatCode( UnitGroupNo,DEF_GT_PURP::Lime);
		std::string MgCode =  m_pGT_MAT_PURP->getRelatedMatCode(UnitGroupNo,DEF_GT_PURP:: Magnesium );
		std::string CarbCode =  m_pGT_MAT_PURP->getRelatedMatCode(UnitGroupNo,DEF_GT_PURP::Carbide);

    if (m_pTelcom_Interface && m_pDM_Interface)
    {
      log("### L2HM30: Entry",3);
      std::string TlgType   = std::string ("L2HD30");
      std::string DataKeyL1 = m_pTelcom_Interface->generateDataKey(TlgType);

      CDateTime now;
      m_pTelcom_Interface->setAny(DataKeyL1.c_str(), Telegram_L2HD30::CreateTime, now.asCORBAAny());

      long RelTemp = -1;
      long Slag = -1;
      long DeslagDur = -1; 
      long TotCost = -1;
      long InjType = -1;

      //sankar
      if(pPDH_HM_Data->select(HeatID,TreatID,Plant))
			{
				InjType = pPDH_HM_Data->getTREAT_TYPE_OPER(1);
			}

      DEF::seqLong PhaseEnabled;
      PhaseEnabled.length(5);

      DEF::seqLong PhaseDuration;
      PhaseDuration.length(5);

			DEF::seqString MatCode;
      MatCode.length(6);

      DEF::seqLong Weight;
      Weight.length(6);

      DEF::seqLong InjectionRate;
      InjectionRate.length(6);
      

      seqHMDModelResult sql = CIntfData::ToCORBAType(m_pDM_Interface->getHMDModelResult(ProductID.c_str(),DATA::HMDPredRes));
      log(CIntfData::getContent(CIntfData::ToAny(sql)),2);
      long ll = sql.length();

      if (ll > 0)
      {
        log("provideData_L2HD30, something to do",3);
        long ii = 0;
        for (ii = 0; ii < 5; ii++)
        {
          PhaseEnabled[ii] = -1;
          PhaseDuration[ii] = -1;
        }

        for (ii = 0; ii < 6; ii++)
        {
          Weight[ii]        = -1;
					InjectionRate[ii] = -1;
					MatCode[ii]       = "";
        }


        for (ii = 0; ii < ll; ii++)
        {
          sHMDModelResult theModelResult;
          sHMDCalc   theHMDAmount;
          sHMDCalc   theHMDFlow;
          CIntfData::getAt(theModelResult, sql, ii);
          
					//sankar
          //InjType = (long)theModelResult.TreatmentKind;

          RelTemp = (long) (theModelResult.TemperatureAfter[InjType]);
          Slag = (long) (theModelResult.SlagAmount[InjType]);
          DeslagDur = (long) (theModelResult.DurationDeslagging[InjType] ); // SANKAR (long) (theModelResult.DurationDeslagging[InjType] * 100);
          TotCost = (long) (theModelResult.Cost[InjType]);

          CIntfData::getAt(theHMDAmount,theModelResult.CalcAmount, InjType);
          CIntfData::getAt(theHMDFlow,theModelResult.CalcFlow, InjType);

          if (InjType == 0)   // mono lime
          {
						PhaseEnabled[0] = 1;
						PhaseDuration[0] = (long)theModelResult.Duration[InjType]; //phase duration is not required by L1
						MatCode[0]       = LimeCode.c_str(); //mat code for lime.
						Weight[0]        = theHMDAmount.Lime[2];
						InjectionRate[0] = theHMDFlow.Lime[2];
          }


          if (InjType == 1)   // mono carbide
          {
            PhaseEnabled[0] = 1;
						PhaseDuration[0] = (long)theModelResult.Duration[InjType];  //phase duration is not required by L1
						MatCode[0]       = CarbCode.c_str(); //mat code for carbide.
						Weight[0]        = theHMDAmount.Carbide[2];
						InjectionRate[0] = theHMDFlow.Carbide[2];
          }


          if (InjType == 2)   // co lime
          {
            PhaseEnabled[0] = 1;
            PhaseEnabled[2] = 1;
						PhaseEnabled[4] = 1;
						PhaseDuration[0] = (long)theModelResult.Duration[InjType]; // phase duration is not required by L1
						MatCode[0]       = LimeCode.c_str(); //mat code for lime.
						MatCode[2]       = LimeCode.c_str(); //mat code for lime.
						MatCode[3]       = MgCode.c_str(); //mat code for Mg
						MatCode[5]       = LimeCode.c_str(); //mat code for lime.
						Weight[0]        = theHMDAmount.Lime[0];
						Weight[2]        = theHMDAmount.Lime[1];
						Weight[3]        = theHMDAmount.Magnesium[1];
						Weight[5]        = theHMDAmount.Lime[2];
						InjectionRate[0] = theHMDFlow.Lime[0];
						InjectionRate[2] = theHMDFlow.Lime[1];
						InjectionRate[3] = theHMDFlow.Magnesium[1];
						InjectionRate[5] = theHMDFlow.Lime[2];
          }


          if (InjType == 3)   // co carbide
          {
            PhaseEnabled[0] = 1;
            PhaseEnabled[2] = 1;
						PhaseEnabled[4] = 1;
						PhaseDuration[0] = (long)theModelResult.Duration[InjType];  //phase duration is not required by L1
						MatCode[0]       = CarbCode.c_str(); //mat code for carbide.
						MatCode[2]       = CarbCode.c_str(); //mat code for carbide.
						MatCode[3]       = MgCode.c_str(); //mat code for Mg
						MatCode[5]       = CarbCode.c_str(); //mat code for carbide.
						Weight[0]        = theHMDAmount.Carbide[0];
						Weight[2]        = theHMDAmount.Carbide[1];
						Weight[3]        = theHMDAmount.Magnesium[1];
						Weight[5]        = theHMDAmount.Carbide[2];
						InjectionRate[0] = theHMDFlow.Carbide[0];
						InjectionRate[2] = theHMDFlow.Carbide[1];
						InjectionRate[3] = theHMDFlow.Magnesium[1];
						InjectionRate[5] = theHMDFlow.Carbide[2];
          }


		  if (InjType == 4)   // eco 
      {
            PhaseEnabled[0] = 1;
            PhaseEnabled[2] = 1;
						PhaseEnabled[4] = 1;
						PhaseDuration[0] = (long)theModelResult.Duration[InjType]; // phase duration is not required by L1
						MatCode[0]       = LimeCode.c_str(); //mat code for lime.
						MatCode[2]       = CarbCode.c_str(); //mat code for carbide.
						MatCode[3]       = MgCode.c_str(); //mat code for Mg
						MatCode[5]       = LimeCode.c_str(); //mat code for lime.
						Weight[0]        = theHMDAmount.Lime[0];
						Weight[2]        = theHMDAmount.Carbide[1];
						Weight[3]        = theHMDAmount.Magnesium[1];
						Weight[5]        = theHMDAmount.Lime[2];
						InjectionRate[0] = theHMDFlow.Lime[0];
						InjectionRate[2] = theHMDFlow.Carbide[1];
						InjectionRate[3] = theHMDFlow.Magnesium[1];
						InjectionRate[5] = theHMDFlow.Lime[2];
       }


		   CORBA::Any PhaseEnabledAny;
		   PhaseEnabledAny<<=PhaseEnabled;

		   CORBA::Any PhaseDurationAny;
		   PhaseDurationAny<<=PhaseDuration;

		   CORBA::Any MatCodeAny;
		   MatCodeAny<<=MatCode;

		   CORBA::Any WeightAny;
		   WeightAny<<=Weight;

		   CORBA::Any InjectionRateAny;
		   InjectionRateAny<<=InjectionRate;

		   InjType += 1;


		  m_pTelcom_Interface->setLong(DataKeyL1.c_str(),Telegram_L2HD30::RelTemp, RelTemp);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(),Telegram_L2HD30::Slag, Slag);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(),Telegram_L2HD30::DeslagDur, DeslagDur);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(),Telegram_L2HD30::TotCost, TotCost);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(),Telegram_L2HD30::InjType, InjType);

		  m_pTelcom_Interface->setAny(DataKeyL1.c_str(),Telegram_L2HD30::PhaseEnabled,  PhaseEnabledAny);
		  m_pTelcom_Interface->setAny(DataKeyL1.c_str(),Telegram_L2HD30::PhaseDuration, PhaseDurationAny);
		  m_pTelcom_Interface->setAny(DataKeyL1.c_str(),Telegram_L2HD30::MatCode,       MatCodeAny);
		  m_pTelcom_Interface->setAny(DataKeyL1.c_str(),Telegram_L2HD30::Weight,        WeightAny);
		  m_pTelcom_Interface->setAny(DataKeyL1.c_str(),Telegram_L2HD30::InjectionRate, InjectionRateAny);


      }
        
      }

      m_pTelcom_Interface->setString(DataKeyL1.c_str(),Telegram_L2HD30::HeatNo, HeatID.c_str());
      m_pTelcom_Interface->setString(DataKeyL1.c_str(),Telegram_L2HD30::TreatId,TreatID.c_str()); 
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD30::FreeSpare1, 0);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD30::FreeSpare2, 0);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD30::FreeSpare3, 0);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD30::FreeSpare4, 0);
      m_pTelcom_Interface->setLong(DataKeyL1.c_str(), Telegram_L2HD30::FreeSpare5, 0);

      m_pTelcom_Interface->complete(DataKeyL1.c_str(),DataKeyL1.c_str() );
      m_pTelcom_Interface->showContent(DataKeyL1.c_str(),1);

      CEventMessage MstToL1Sender(m_SenderName, 
        m_DestinationName, 
        std::string("TELEGRAM_") + TlgType, 
        std::string ("UNUSED"), 
        std::string ("UNUSED"),
        false,
        HeatID,
        TreatID,
        DataKeyL1);

      MstToL1Sender.setPlantID(L1PlantID);
      MstToL1Sender.dispatch(m_SenderName,m_DestinationName);
    }
    else
    {
      retval=false;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc,
      "CHMD_EventHandler::provideData_L2HM30",
      Action);
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc,
      "CHMD_EventHandler::provideData_L2HM30",
      Action);
  } 
  catch(...)
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException("CHMD_EventHandler::provideData_L2HM06",
      Action);
  }

  return retval;
}


