
// Done By PAMA Completely...

#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdLog_Task.h"

#include "CSMC_RuntimeController.h"
#include "CEventMessageReady.h"

#include "CARCHIVER_LF_Test_MaterialHandling.h"
#include "CARCHIVER_LF_Test_Task.h"

CARCHIVER_LF_Test_MaterialHandling::~CARCHIVER_LF_Test_MaterialHandling()
{
}

CARCHIVER_LF_Test_MaterialHandling::CARCHIVER_LF_Test_MaterialHandling(CARCHIVER_Task *Task)
{
  pConnection = CARCHIVER_LF_Test_Task::getInstance()->getpConnection();
  cCBS_StdInitBase::getInstance()->replaceWithEntry("DataManager", "ServerName", TrackerName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TrackerName, "ServerTask", ServerTask);
}


bool CARCHIVER_LF_Test_MaterialHandling::handleLFLiqMatHandlingReportRDY(CEventMessage& Event)
{
  bool RetValue = false;
  std::stringstream Message;
  std::string DataKey = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string RecPlant = DEF_DB_PLANT::LF;
  bool TestCode = true;

  double GrossWeight = 0;
  long  LadleLocation = DEF_LADLE_POS::UNDEF;
  long  WeighingType;

  //Initialise database objects
  CPD_LADLE* m_pPD_LADLE = 0;
  
  if (pConnection)
  {
    m_pPD_LADLE = new CPD_LADLE(pConnection);
  }

  setpDM_Interface(Event.getSender(),DM::EVENT);

  //get data from Event Interface.
  WeighingType    = m_pDM_Interface->getLong(DataKey.c_str(),   DATA::WeighingType);
  GrossWeight = m_pDM_Interface->getDouble(DataKey.c_str(), DATA::MeasWeight);
  LadleLocation   = m_pDM_Interface->getLong(DataKey.c_str(),DATA::LadleLocation);

  Message << "\nPD_LADLE" << endl;
  if ((WeighingType == DEF_LIQ_MAT_REPORT::LadleWeightBeforeLF)||
            (WeighingType == DEF_LIQ_MAT_REPORT::LadleWeightAfterLF)||
            (WeighingType == DEF_LIQ_MAT_REPORT::GrossWeightUpdateAtLF)||
            (WeighingType == DEF_LIQ_MAT_REPORT::LadleGrossWeighBeforeCasting)||
            (WeighingType == DEF_LIQ_MAT_REPORT::LadleGrossWeighAfterCasting)||
            (WeighingType == DEF_LIQ_MAT_REPORT::LadleGrossWeightAfterBOFTapping)||
            (WeighingType == DEF_LIQ_MAT_REPORT::LadleWgtReturnHeat))
   {
      if(!m_pPD_LADLE->isNull("GROSSWEIGHT", 1))
      {
        if(m_pPD_LADLE->getGROSSWEIGHT(1)== GrossWeight)
        {
          Message << " GROSSWEIGHT = " << m_pPD_LADLE->getGROSSWEIGHT(1)<< endl;
        }
        else 
        {
          Message << "ERROR:\n  GROSSWEIGHT is not equal to "<< GrossWeight <<" it is " << m_pPD_LADLE->getGROSSWEIGHT(1) << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "ERROR:\n  GROSSWEIGHT is not set in nPD_LADLE" << endl;
        TestCode = false;      
      }
      if(!m_pPD_LADLE->isNull("LDLPOSID", 1))
      {
        if(m_pPD_LADLE->getLDLPOSID(1)== LadleLocation)
        {
          Message << " LDLPOSID = " << m_pPD_LADLE->getLDLPOSID(1)<< endl;
        }
        else 
        {
          Message << "ERROR:\n  LDLPOSID is not equal to "<< LadleLocation <<" it is " << m_pPD_LADLE->getLDLPOSID(1) << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "ERROR:\n  LDLPOSID is not set in nPD_LADLE" << endl;
        TestCode = false;      
      }   
   }
   if (WeighingType == DEF_LIQ_MAT_REPORT::LadleTareWeightBeforeBOFTapping)
      {
        if(!m_pPD_LADLE->isNull("TAREWGT", 1))
      {
        if(m_pPD_LADLE->getTAREWGT(1)== GrossWeight)
        {
          Message << " TAREWGT = " << m_pPD_LADLE->getTAREWGT(1)<< endl;
        }
        else 
        {
          Message << "ERROR:\n  TAREWGT is not equal to "<< GrossWeight <<" it is " << m_pPD_LADLE->getTAREWGT(1) << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "ERROR:\n  TAREWGT is not set in nPD_LADLE" << endl;
        TestCode = false;      
      } 
      }
 
  if (m_pPD_LADLE) { delete m_pPD_LADLE; m_pPD_LADLE = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test LF Liquid Material Handling Report use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test LF Liquid Material Handling Report use case failed",1);
 
  RetValue = true;

  return RetValue;
} 


bool CARCHIVER_LF_Test_MaterialHandling::handleLFMaterialHandlingReportRDY(CEventMessage& Event)
{
  bool RetValue = false;
  std::stringstream Message;
  std::string DataKey = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string RecPlant = DEF_DB_PLANT::LF;
  bool TestCode = true;

  seqGasData *SeqGasData; 
  sGasData theGasData;
  double HeatAnnTime;
  double HeatStartTime;

 //Initialise database objects
  CPD_RECIPE* m_pPD_RECIPE = 0;

  if (pConnection)
  {
    m_pPD_RECIPE = new CPD_RECIPE(pConnection);
  }

  
  setpDM_Interface(ServerTask,DM::EVENT);

  //get data from Event Interface and fill NonSeqRecipeInfo.

  std::string RecipeName   = m_pDM_Interface->getString(DataKey.c_str(),DATA::RecipeName);
  std::string RecipeSource = m_pDM_Interface->getString(DataKey.c_str(),DATA::RecipeSource);
  long RecipeStatus = m_pDM_Interface->getLong(DataKey.c_str(),DATA::RecipeStatus);
  long RecipeNo     = m_pDM_Interface->getLong(DataKey.c_str(),DATA::RecipeNo);

  setpDM_Interface(ServerTask,DM::PRODUCT);
  SeqGasData = m_pDM_Interface->getGasData(ProductID.c_str(),DATA::StirrAmount);
  HeatAnnTime = m_pDM_Interface->getDouble(ProductID.c_str(),DATA::HeatAnnounceTime);
  HeatStartTime = m_pDM_Interface->getDouble(ProductID.c_str(),DATA::HeatStartTime);

  Message << "\nPD_RECIPE" << endl;
  if (m_pPD_RECIPE->select(RecHeatID, RecipeNo, RecipeName, RecPlant,
                            RecipeStatus, RecipeSource, RecTreatID))
  {
    if(!m_pPD_RECIPE->isNull("DURSINCEHEATANNOUNCEMENT",1))
    {
      Message << "DURSINCEHEATANNOUNCEMENT(" << HeatAnnTime << ") = " << m_pPD_RECIPE->getDURSINCEHEATANNOUNCEMENT(1) << endl;
    }
    else
    {
      Message << "ERROR:\n  DURSINCEHEATANNOUNCEMENT is not set in PD_RECIPE"<<endl;
      TestCode = false;
    }

    if(!m_pPD_RECIPE->isNull("DURSINCESTARTOFFHEAT",1))
    {
      Message << "DURSINCESTARTOFFHEAT(" << HeatStartTime << ") = " << m_pPD_RECIPE->getDURSINCESTARTOFFHEAT(1) << endl;
    }
    else
    {
      Message << "ERROR:\n  DURSINCESTARTOFFHEAT is not set in PD_RECIPE"<<endl;
      TestCode = false;
    }

    long SeqLength = CIntfData::getLength(SeqGasData);
    std::string GasType = theGasData.GasType;
    double GasValue = theGasData.GasValue ;
    for (long i=0 ; i<SeqLength ; i++)
    {
      if (GasType == DEF_GAS::Ar)
      {
        if(!m_pPD_RECIPE->isNull("ACT_AR_MOMENT",1))
        {
          if(m_pPD_RECIPE->getACT_AR_MOMENT(1)==GasValue)
            {
              Message << "ACT_AR_MOMENT = " << m_pPD_RECIPE->getACT_AR_MOMENT(1) << endl;
            }
          else
            {
              Message << "ERROR:\n  ACT_AR_MOMENT is not equal to "<< GasValue <<" it is " << m_pPD_RECIPE->getACT_AR_MOMENT(1) << endl;
              TestCode = false;
            }
        }
        else
        {
          Message << "ERROR:\n  ACT_AR_MOMENT is not set in PD_RECIPE"<<endl;
          TestCode = false;
        }
      }
      if  (GasType == DEF_GAS::N2)
      {
       if(!m_pPD_RECIPE->isNull("ACT_N2_MOMENT",1))
        {
          if(m_pPD_RECIPE->getACT_N2_MOMENT(1)==GasValue)
            {
              Message << "ACT_N2_MOMENT = " << m_pPD_RECIPE->getACT_N2_MOMENT(1) << endl;
            }
          else
            {
              Message << "ERROR:\n  ACT_N2_MOMENT is not equal to "<< GasValue <<" it is " << m_pPD_RECIPE->getACT_N2_MOMENT(1) << endl;
              TestCode = false;
            }
        }
        else
        {
          Message << "ERROR:\n  ACT_N2_MOMENT is not set in PD_RECIPE"<<endl;
          TestCode = false;
        }
      }
    }
  }
  else
  {
    Message << "ERROR:\n  The selection from PD_RECIPE was not successfull"<<endl;
    TestCode = false;
  }

  if (m_pPD_RECIPE) { delete m_pPD_RECIPE; m_pPD_RECIPE = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
  {
      cCBS_StdLog_Task::getInstance()->log("Test Material Handling Report use case was successful",1);
  }
  else
  {
      cCBS_StdLog_Task::getInstance()->log("Test Material Handling Report use case failed",1);
  }


  RetValue = true;

  return RetValue;
}


bool CARCHIVER_LF_Test_MaterialHandling::handleLFWireFeedingStartRDY(CEventMessage& Event)
{
  bool RetValue = false;
  std::stringstream Message;
  std::string DataKey = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string RecPlant = DEF_DB_PLANT::LF;
  bool TestCode = true;

  long lBatchStatNo = DEF_RECIPE_STATUS::WireFeeder_Addition;


  //Initialise database objects
    CPD_RECIPE* m_pPD_RECIPE = 0;
    CPDL_WIRE_ADD* m_pPDL_Wire_Add = 0;

  if (pConnection)
  {
    m_pPD_RECIPE = new CPD_RECIPE(pConnection);
    m_pPDL_Wire_Add= new CPDL_WIRE_ADD(pConnection);
  }


  setpDM_Interface(Event.getSender(),DM::PRODUCT);

  long LineNum                = m_pDM_Interface->getLong(DataKey.c_str(),DATA::WireFeederLineNo);
  std::string MatCode         = m_pDM_Interface->getString(ProductID.c_str(), DATA::WireFeederMatCode);

  Message << "\nPDL_WIRE_ADD"<<endl;
  if (m_pPDL_Wire_Add->select(RecHeatID,RecTreatID))
  {
    if(!m_pPDL_Wire_Add->isNull("MAT_CODE", 1))
    {
      if(m_pPDL_Wire_Add->getMAT_CODE(1)== MatCode)
      {
        Message << " MAT_CODE = " << m_pPDL_Wire_Add->getMAT_CODE(1)<< endl;
      }
      else 
      {
         Message << "ERROR:\n  MAT_CODE is not equal to "<< MatCode <<" it is " << m_pPDL_Wire_Add->getMAT_CODE(1) << endl;
         TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  MAT_CODE is not set in PDL_WIRE_ADD" << endl;
      TestCode = false;      
    }
    if(!m_pPDL_Wire_Add->isNull("WIRE_LINE_NO", 1))
    {
      if(m_pPDL_Wire_Add->getWIRE_LINE_NO(1)== LineNum )
      {
        Message << " WIRE_LINE_NO = " << m_pPDL_Wire_Add->getWIRE_LINE_NO(1)<< endl;
      }
      else 
      {
         Message << "ERROR:\n  WIRE_LINE_NO is not equal to "<< LineNum <<" it is " << m_pPDL_Wire_Add->getWIRE_LINE_NO(1) << endl;
         TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  WIRE_LINE_NO is not set in PDL_WIRE_ADD" << endl;
      TestCode = false;      
    }
    if(!m_pPDL_Wire_Add->isNull("WIRE_FEED_START", 1))
    {
      Message << " WIRE_FEED_START= " << m_pPDL_Wire_Add->getWIRE_FEED_START(1)<< endl;
    }
    else
    {
      Message << "ERROR:\n  WIRE_FEED_START is not set in PDL_WIRE_ADD" << endl;
      TestCode = false;      
    }
   }
   else
   {
      Message << "ERROR:\n  In PDL_WIRE_ADD, select for HeatID: " << RecHeatID << ", TreatID: "
              << RecTreatID << " failed!\n";
      TestCode = false;
   }

  
  Message << "\nPD_RECIPE" << endl;

  setpDM_Interface(ServerTask,DM::EVENT);
  std::string RecipeName   = m_pDM_Interface->getString(DataKey.c_str(),DATA::RecipeName);
  std::string RecipeSource = m_pDM_Interface->getString(DataKey.c_str(),DATA::RecipeSource);
  long RecipeNo     = m_pDM_Interface->getLong(DataKey.c_str(),DATA::RecipeNo);
  
  if (m_pPD_RECIPE->select(RecHeatID, RecipeNo, RecipeName, RecPlant,
                            lBatchStatNo, RecipeSource, RecTreatID))
  {
    if(!m_pPD_RECIPE->isNull("RECIPENAME", 1))
    {
      if(m_pPD_RECIPE->getRECIPENAME(1)== RecipeName)
      {
        Message << " RECIPENAME = " << m_pPD_RECIPE->getRECIPENAME(1)<< endl;
      }
      else 
      {
         Message << "ERROR:\n  RECIPENAME is not equal to "<< RecipeName <<" it is " << m_pPD_RECIPE->getRECIPENAME(1) << endl;
         TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  RECIPENAME is not set in PD_RECIPE" << endl;
      TestCode = false;      
    }
    if(!m_pPD_RECIPE->isNull("RECIPENO", 1))
    {
     if(m_pPD_RECIPE->getRECIPENO(1)== RecipeNo)
      {
        Message << " RECIPENO = " << m_pPD_RECIPE->getRECIPENO(1)<< endl;
      }
      else 
      {
         Message << "ERROR:\n  RECIPENO is not equal to "<< RecipeNo <<" it is " << m_pPD_RECIPE->getRECIPENO(1) << endl;
         TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  RECIPENO is not set in PD_RECIPE" << endl;
      TestCode = false;      
    }
    if(!m_pPD_RECIPE->isNull("SOURCE", 1))
    {
      if(m_pPD_RECIPE->getSOURCE(1)== RecipeSource)
      {
        Message << " SOURCE = " << m_pPD_RECIPE->getSOURCE(1)<< endl;
      }
      else 
      {
         Message << "ERROR:\n  SOURCE is not equal to "<< RecipeSource <<" it is " << m_pPD_RECIPE->getSOURCE(1) << endl;
         TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  SOURCE is not set in PD_RECIPE" << endl;
      TestCode = false;      
    }
    if(!m_pPD_RECIPE->isNull("BATCHSTATUSNO", 1))
    {
      if(m_pPD_RECIPE->getBATCHSTATUSNO(1)== lBatchStatNo)
      {
        Message << " BATCHSTATUSNO = " << m_pPD_RECIPE->getBATCHSTATUSNO(1)<< endl;
      }
      else 
      {
         Message << "ERROR:\n  BATCHSTATUSNO is not equal to "<< lBatchStatNo <<" it is " << m_pPD_RECIPE->getBATCHSTATUSNO(1) << endl;
         TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  BATCHSTATUSNO is not set in PD_RECIPE" << endl;
      TestCode = false;      
    }
   }
   else
   {
      Message << "ERROR:\n  In PD_RECIPE, select for HeatID: " << RecHeatID << ", TreatID: "
              << RecTreatID << ", PLANT: " << RecPlant << " failed!\n";
      TestCode = false;
   }

   //Delete The Objects
  if (m_pPD_RECIPE) { delete m_pPD_RECIPE; m_pPD_RECIPE = 0;}
  if (m_pPDL_Wire_Add) { delete m_pPDL_Wire_Add; m_pPDL_Wire_Add = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

 if (TestCode)
  {
      cCBS_StdLog_Task::getInstance()->log("Test Wire Feeding Start use case was successful",1);
  }
  else
  {
      cCBS_StdLog_Task::getInstance()->log("Test Wire Feeding Start use case failed",1);
  }


  RetValue = true;

  return RetValue;
}


bool CARCHIVER_LF_Test_MaterialHandling::handleLFWireFeedingEndRDY(CEventMessage& Event)
{
 
  bool RetValue = false;
  std::stringstream Message;
  std::string DataKey = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string RecPlant = DEF_DB_PLANT::LF;
  bool TestCode = true;

  double HeatAnnTime;
  double HeatStartTime;
  double electricEgy;
  long BatchStatusNo=DEF_RECIPE_STATUS::Final;

  double total_mass = 0;
  double total_price = 0;
  double total_volume = 0;
  double total_bulvolume = 0;

  seqWireFeeder *WireFeedData;
  sWireFeeder theWireFeedData;


  //Initialise database objects
  CPD_REPORT* m_pPD_Report = 0;
  CPD_RECIPE* m_pPD_RECIPE = 0;
  CPD_RECIPE_ENTRY* m_pPD_RECIPE_ENTRY = 0;
  CPDL_WIRE_ADD* m_pPDL_Wire_Add = 0;
  CGT_MAT* m_pGT_MAT;

  if (pConnection)
  {
    m_pPD_Report = new CPD_REPORT(pConnection);
    m_pPD_RECIPE = new CPD_RECIPE(pConnection);
    m_pPD_RECIPE_ENTRY = new CPD_RECIPE_ENTRY(pConnection);
    m_pPDL_Wire_Add = new CPDL_WIRE_ADD(pConnection);
    m_pGT_MAT = new CGT_MAT (pConnection );
  }


  setpDM_Interface(Event.getSender(),DM::PRODUCT);

  HeatAnnTime   = m_pDM_Interface->getDouble(ProductID.c_str(),DATA::HeatAnnounceTime);
  HeatStartTime = m_pDM_Interface->getDouble(ProductID.c_str(),DATA::HeatStartTime);
  electricEgy   = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::TotalRemElecEgy);
  WireFeedData  = m_pDM_Interface->getWireFeeder(DataKey.c_str(),DATA::WireFeederData);

  std::string RecipeName   = m_pDM_Interface->getString(DataKey.c_str(),DATA::RecipeName);
  std::string RecipeSource = m_pDM_Interface->getString(DataKey.c_str(),DATA::RecipeSource);
  long RecipeNo     = m_pDM_Interface->getLong(DataKey.c_str(),DATA::RecipeNo);


 
  for (int i = 0; i < CIntfData::getLength(WireFeedData); i++)
  {     
    CIntfData::getAt(theWireFeedData,WireFeedData,i);

    std::string MatCode = theWireFeedData.WireFeederMatCode;
    double MatFeedSpeed = theWireFeedData.WireFeedSpeed;
    long LineNo = theWireFeedData.WireFeederLineNo;

    Message << "\nPDL_WIRE_ADD"<<endl;
    if(m_pPDL_Wire_Add->select(RecHeatID,LineNo,MatCode,RecTreatID))
    {
      if (m_pPDL_Wire_Add->getLastRow()>0)
      {
        if(!m_pPDL_Wire_Add->isNull("WIRE_FEED_END", 1))
        {
          Message << " WIRE_FEED_END =" << m_pPDL_Wire_Add->getWIRE_FEED_END(1)<< endl;
        }
        else
        {
          Message << "ERROR:\n  WIRE_FEED_END is not set in PDL_WIRE_ADD" << endl;
          TestCode = false;      
        }
        if(!m_pPDL_Wire_Add->isNull("MATWEIGHT", 1))
        {
          Message << " MATWEIGHT = " << m_pPDL_Wire_Add->getMATWEIGHT(1)<< endl;
        }
        else
        {
          Message << "ERROR:\n  MATWEIGHT is not set in PDL_WIRE_ADD" << endl;
          TestCode = false;      
        }
        if(!m_pPDL_Wire_Add->isNull("MATFEEDSPEED", 1))
        {
          if(m_pPDL_Wire_Add->getMATFEEDSPEED(1) == MatFeedSpeed)
          {
            Message << " MATFEEDSPEED = " << m_pPDL_Wire_Add->getMATFEEDSPEED(1)<< endl;
          }
          else
          {
            Message << "ERROR:\n  MATFEEDSPEED is not equal to "<< MatFeedSpeed <<" it is " << m_pPDL_Wire_Add->getMATFEEDSPEED(1) << endl;
            TestCode = false;
          }
        }
        else
        {
          Message << "ERROR:\n  MATFEEDSPEED is not set in PDL_WIRE_ADD" << endl;
          TestCode = false;      
        }
      }
    }
    else
    {
        Message << "ERROR:\n  Selection From PDL_WIRE_ADD failed!\n";
        TestCode = false;
    }
  
 

     total_mass = total_mass + theWireFeedData.WireFeederAmount;
      m_pGT_MAT->select((std::string)theWireFeedData.WireFeederMatCode);

      double single_price = m_pGT_MAT->getPRICE(1);

      total_price += single_price * theWireFeedData.WireFeederAmount;
      
      double single_density = m_pGT_MAT->getDENSITY(1);

      if (single_density >0)
        total_volume += theWireFeedData.WireFeederAmount / single_density;
      else
        log("the density of "+(std::string)theWireFeedData.WireFeederMatCode + "is incorrect");
      
      double single_bulkdensity = m_pGT_MAT->getBULK_DENSITY(1);
      
      if (single_bulkdensity>0)
        total_bulvolume += theWireFeedData.WireFeederAmount / single_bulkdensity;
      else
        log("the bulkdensity of "+(std::string)theWireFeedData.WireFeederMatCode + "is incorrect");
      
     
    Message << "\nPD_RECIPE_ENTRY"<<endl;
    if (m_pPD_RECIPE_ENTRY->select(RecHeatID,RecipeNo ,RecipeName ,RecPlant,BatchStatusNo ,RecipeSource ,RecTreatID,MatCode ))
    {
      if(!m_pPD_RECIPE_ENTRY->isNull("DURSINCEHEATANNOUNCEMENT",1))
      {
        Message << "DURSINCEHEATANNOUNCEMENT(" << HeatAnnTime << ") = " << m_pPD_RECIPE_ENTRY->getDURSINCEHEATANNOUNCEMENT(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  DURSINCEHEATANNOUNCEMENT is not set in PD_RECIPE_ENTRY"<<endl;
        TestCode = false;
      }

      if(!m_pPD_RECIPE_ENTRY->isNull("DURSINCESTARTOFFHEAT",1))
      {
        Message << "DURSINCESTARTOFFHEAT(" << HeatStartTime << ") = " << m_pPD_RECIPE_ENTRY->getDURSINCESTARTOFFHEAT(1) << endl;//getDURSINCESTARTOFFHEAT() function is not implemented in DBclass!!!
      }
      else
      {
        Message << "ERROR:\n  DURSINCESTARTOFFHEAT is not set in PD_RECIPE_ENTRY"<<endl;
        TestCode = false;
      }

      //What to do with this MATWEIGHT
      if(!m_pPD_RECIPE_ENTRY->isNull("MATWEIGHT", 1))
      {
        Message << " MATWEIGHT= " << m_pPD_RECIPE_ENTRY->getMATWEIGHT(1)<< endl;
      }
      else
      {
        Message << "ERROR:\n  MATWEIGHT is not set in PD_RECIPE_ENTRY" << endl;
        TestCode = false;      
      }

      if(!m_pPD_RECIPE_ENTRY->isNull("RECIPENAME", 1))
      {
        if(m_pPD_RECIPE_ENTRY->getRECIPENAME(1)=="FinalTrimming")
        {
          Message << " RECIPENAME= " << m_pPD_RECIPE_ENTRY->getRECIPENAME(1)<< endl;
        }
        else
        {
          Message << " RECIPENAME is not equal to FinalTrimming it is  " << m_pPD_RECIPE_ENTRY->getRECIPENAME(1)<< endl;
        }
      }
      else
      {
        Message << "ERROR:\n  RECIPENAME is not set in PD_RECIPE_ENTRY" << endl;
        TestCode = false;      
      }
      if(!m_pPD_RECIPE_ENTRY->isNull("RECIPENO", 1))
      {
        if(m_pPD_RECIPE_ENTRY->getRECIPENO(1)==0)
        {
          Message << " RECIPENO= " << m_pPD_RECIPE_ENTRY->getRECIPENO(1)<< endl;
        }
        else
        {
          Message << " RECIPENO is not equal to 0 it is  " << m_pPD_RECIPE_ENTRY->getRECIPENO(1)<< endl;
        }
      }
      else
      {
        Message << "ERROR:\n  RECIPENO is not set in PD_RECIPE_ENTRY" << endl;
        TestCode = false;      
      }
      if(!m_pPD_RECIPE_ENTRY->isNull("SOURCE", 1))
      {
        if(m_pPD_RECIPE_ENTRY->getSOURCE(1)=="LFWire")
        {
          Message << " SOURCE= " << m_pPD_RECIPE_ENTRY->getSOURCE(1)<< endl;
        }
        else
        {
          Message << " SOURCE is not equal to LFWire it is  " << m_pPD_RECIPE_ENTRY->getSOURCE(1)<< endl;
        }
      }
      else
      {
        Message << "ERROR:\n  SOURCE is not set in PD_RECIPE_ENTRY" << endl;
        TestCode = false;      
      }
      if(!m_pPD_RECIPE_ENTRY->isNull("BATCHSTATUSNO", 1))
      {
        if(m_pPD_RECIPE_ENTRY->getBATCHSTATUSNO(1)==BatchStatusNo)
        {
          Message << " BATCHSTATUSNO= " << m_pPD_RECIPE_ENTRY->getBATCHSTATUSNO(1)<< endl;
        }
        else
        {
          Message << " BATCHSTATUSNO is not equal to "<< BatchStatusNo <<" it is  " << m_pPD_RECIPE_ENTRY->getBATCHSTATUSNO(1)<< endl;
        }
      }
      else
      {
        Message << "ERROR:\n  BATCHSTATUSNO is not set in PD_RECIPE_ENTRY" << endl;
        TestCode = false;      
      }
      if(!m_pPD_RECIPE_ENTRY->isNull("ACT_EGY", 1))
      {
        if(m_pPD_RECIPE_ENTRY->getACT_EGY(1)==electricEgy)
        {
          Message << " ACT_EGY= " << m_pPD_RECIPE_ENTRY->getACT_EGY(1)<< endl;
        }
        else
        {
          Message << " ACT_EGY is not equal to "<< electricEgy <<" it is  " << m_pPD_RECIPE_ENTRY->getACT_EGY(1)<< endl;
        }
      }
      else
      {
        Message << "ERROR:\n  ACT_EGY is not set in PD_RECIPE_ENTRY" << endl;
        TestCode = false;      
      }
    }
    else
    {
        Message << "ERROR:\n  Slecetion From PD_RECIPE_ENTRY failed!\n";
        TestCode = false;
    }


  }//For Loop End
  
  //Should these variables total mass,bulkvol,vol etc.  be incremented one more time as in wrapper

  Message << "\nPD_RECIPE"<<endl;
  long  recipestatusarr[]={DEF_RECIPE_STATUS::Final,DEF_RECIPE_STATUS::WireFeeder_Addition};
  for(int j=0;j<sizeof(recipestatusarr);j++)
  {
   if(m_pPD_RECIPE->select(RecHeatID,0,"FinalTrimming",DEF_DB_PLANT::LF,recipestatusarr[j],"LFWire",RecTreatID))
    {
        if(!m_pPD_RECIPE->isNull("WEIGHTTOTAL", 1))
        {
          if(m_pPD_RECIPE->getWEIGHTTOTAL(1) == theWireFeedData.WireFeederAmount)
          {
            Message << " WEIGHTTOTAL = " << m_pPD_RECIPE->getWEIGHTTOTAL(1)<< endl;
          }
          else
          {
            Message << "ERROR:\n  WEIGHTTOTAL is not equal to "<< theWireFeedData.WireFeederAmount <<" it is " << m_pPD_RECIPE->getWEIGHTTOTAL(1) << endl;
            TestCode = false;
          }
        }
        else
        {
          Message << "ERROR:\n  WEIGHTTOTAL is not set in PD_RECIPE" << endl;
          TestCode = false;      
        }
        if(!m_pPD_RECIPE->isNull("COSTSBATCH", 1))
        {
          if(m_pPD_RECIPE->getCOSTSBATCH(1) == total_price)
          {
            Message << " COSTSBATCH = " << m_pPD_RECIPE->getCOSTSBATCH(1)<< endl;
          }
          else
          {
            Message << "ERROR:\n  COSTSBATCH is not equal to "<<  total_price <<" it is " << m_pPD_RECIPE->getCOSTSBATCH(1) << endl;
            TestCode = false;
          }
        }
        else
        {
          Message << "ERROR:\n  COSTSBATCH is not set in PD_RECIPE" << endl;
          TestCode = false;      
        }
        if(!m_pPD_RECIPE->isNull("BULKVOL", 1))
        {
          if(m_pPD_RECIPE->getBULKVOL(1) == total_bulvolume)
          {
            Message << " BULKVOL = " << m_pPD_RECIPE->getBULKVOL(1)<< endl;
          }
          else
          {
            Message << "ERROR:\n  BULKVOL is not equal to "<< total_bulvolume <<" it is " << m_pPD_RECIPE->getBULKVOL(1) << endl;
            TestCode = false;
          }
        }
        else
        {
          Message << "ERROR:\n  BULKVOL is not set in PD_RECIPE" << endl;
          TestCode = false;      
        }
        if(!m_pPD_RECIPE->isNull("VOLUME", 1))
        {
          if(m_pPD_RECIPE->getVOLUME(1) == total_volume)
          {
            Message << " VOLUME = " << m_pPD_RECIPE->getVOLUME(1)<< endl;
          }
          else
          {
            Message << "ERROR:\n  VOLUME is not equal to "<< total_volume <<" it is " << m_pPD_RECIPE->getVOLUME(1) << endl;
            TestCode = false;
          }
        }
        else
        {
          Message << "ERROR:\n  VOLUME is not set in PD_RECIPE" << endl;
          TestCode = false;      
        }
        if(recipestatusarr[j]==DEF_RECIPE_STATUS::Final)
        {
          if(!m_pPD_RECIPE->isNull("UPDTIME", 1))
          {
           Message << " UPDTIME = " << m_pPD_RECIPE->getUPDTIME(1)<< endl;
          }
          else
          {
           Message << "ERROR:\n  UPDTIME is not set in PD_RECIPE" << endl;
           TestCode = false;      
          }
        }
      }
   else
    {
      Message << "ERROR:\n  Selection From PD_RECIPE failed!\n";
      TestCode = false;
    }
  }

 /* if(m_pPD_RECIPE->select(RecHeatID,0,"FinalTrimming",DEF_DB_PLANT::LF,DEF_RECIPE_STATUS::Final,"LFWire",RecTreatID))
    {
        if(!m_pPD_RECIPE->isNull("WEIGHTTOTAL", 1))
        {
          if(m_pPD_RECIPE->getWEIGHTTOTAL(1) == theWireFeedData.WireFeederAmount)
          {
            Message << " WEIGHTTOTAL = " << m_pPD_RECIPE->getWEIGHTTOTAL(1)<< endl;
          }
          else
          {
            Message << "ERROR:\n  WEIGHTTOTAL is not equal to "<< theWireFeedData.WireFeederAmount <<" it is " << m_pPD_RECIPE->getWEIGHTTOTAL(1) << endl;
            TestCode = false;
          }
        }
        else
        {
          Message << "ERROR:\n  WEIGHTTOTAL is not set in PD_RECIPE" << endl;
          TestCode = false;      
        }
        if(!m_pPD_RECIPE->isNull("COSTSBATCH", 1))
        {
          if(m_pPD_RECIPE->getCOSTSBATCH(1) == total_price)
          {
            Message << " COSTSBATCH = " << m_pPD_RECIPE->getCOSTSBATCH(1)<< endl;
          }
          else
          {
            Message << "ERROR:\n  COSTSBATCH is not equal to "<<  total_price <<" it is " << m_pPD_RECIPE->getCOSTSBATCH(1) << endl;
            TestCode = false;
          }
        }
        else
        {
          Message << "ERROR:\n  COSTSBATCH is not set in PD_RECIPE" << endl;
          TestCode = false;      
        }
        if(!m_pPD_RECIPE->isNull("BULKVOL", 1))
        {
          if(m_pPD_RECIPE->getBULKVOL(1) == total_bulvolume)
          {
            Message << " BULKVOL = " << m_pPD_RECIPE->getBULKVOL(1)<< endl;
          }
          else
          {
            Message << "ERROR:\n  BULKVOL is not equal to "<< total_bulvolume <<" it is " << m_pPD_RECIPE->getBULKVOL(1) << endl;
            TestCode = false;
          }
        }
        else
        {
          Message << "ERROR:\n  BULKVOL is not set in PD_RECIPE" << endl;
          TestCode = false;      
        }
        if(!m_pPD_RECIPE->isNull("VOLUME", 1))
        {
          if(m_pPD_RECIPE->getVOLUME(1) == total_volume)
          {
            Message << " VOLUME = " << m_pPD_RECIPE->getVOLUME(1)<< endl;
          }
          else
          {
            Message << "ERROR:\n  VOLUME is not equal to "<< total_volume <<" it is " << m_pPD_RECIPE->getVOLUME(1) << endl;
            TestCode = false;
          }
        }
        else
        {
          Message << "ERROR:\n  VOLUME is not set in PD_RECIPE" << endl;
          TestCode = false;      
        }
        if(!m_pPD_RECIPE->isNull("UPDTIME", 1))
        {
           Message << " UPDTIME = " << m_pPD_RECIPE->getUPDTIME(1)<< endl;
        }
        else
        {
           Message << "ERROR:\n  UPDTIME is not set in PD_RECIPE" << endl;
           TestCode = false;      
        }
      }
    else
    {
      Message << "ERROR:\n  Selection From PD_RECIPE failed!\n";
      TestCode = false;
    }

    if(m_pPD_RECIPE->select(RecHeatID,0,"FinalTrimming",DEF_DB_PLANT::LF,DEF_RECIPE_STATUS::WireFeeder_Addition,"LFWire",RecTreatID))
    {
        if(!m_pPD_RECIPE->isNull("WEIGHTTOTAL", 1))
        {
          if(m_pPD_RECIPE->getWEIGHTTOTAL(1) == theWireFeedData.WireFeederAmount)
          {
            Message << " WEIGHTTOTAL = " << m_pPD_RECIPE->getWEIGHTTOTAL(1)<< endl;
          }
          else
          {
            Message << "ERROR:\n  WEIGHTTOTAL is not equal to "<< theWireFeedData.WireFeederAmount <<" it is " << m_pPD_RECIPE->getWEIGHTTOTAL(1) << endl;
            TestCode = false;
          }
        }
        else
        {
          Message << "ERROR:\n  WEIGHTTOTAL is not set in PD_RECIPE" << endl;
          TestCode = false;      
        }
        if(!m_pPD_RECIPE->isNull("COSTSBATCH", 1))
        {
          if(m_pPD_RECIPE->getCOSTSBATCH(1) == total_price)
          {
            Message << " COSTSBATCH = " << m_pPD_RECIPE->getCOSTSBATCH(1)<< endl;
          }
          else
          {
            Message << "ERROR:\n  COSTSBATCH is not equal to "<<  total_price <<" it is " << m_pPD_RECIPE->getCOSTSBATCH(1) << endl;
            TestCode = false;
          }
        }
        else
        {
          Message << "ERROR:\n  COSTSBATCH is not set in PD_RECIPE" << endl;
          TestCode = false;      
        }
        if(!m_pPD_RECIPE->isNull("BULKVOL", 1))
        {
          if(m_pPD_RECIPE->getBULKVOL(1) == total_bulvolume)
          {
            Message << " BULKVOL = " << m_pPD_RECIPE->getBULKVOL(1)<< endl;
          }
          else
          {
            Message << "ERROR:\n  BULKVOL is not equal to "<< total_bulvolume <<" it is " << m_pPD_RECIPE->getBULKVOL(1) << endl;
            TestCode = false;
          }
        }
        else
        {
          Message << "ERROR:\n  BULKVOL is not set in PD_RECIPE" << endl;
          TestCode = false;      
        }
        if(!m_pPD_RECIPE->isNull("VOLUME", 1))
        {
          if(m_pPD_RECIPE->getVOLUME(1) == total_volume)
          {
            Message << " VOLUME = " << m_pPD_RECIPE->getVOLUME(1)<< endl;
          }
          else
          {
            Message << "ERROR:\n  VOLUME is not equal to "<< total_volume <<" it is " << m_pPD_RECIPE->getVOLUME(1) << endl;
            TestCode = false;
          }
        }
        else
        {
          Message << "ERROR:\n  VOLUME is not set in PD_RECIPE" << endl;
          TestCode = false;      
        }
      }
    else
   {
      Message << "ERROR:\n  Selection From PD_RECIPE failed!\n";
      TestCode = false;
   }  */
   
  if (m_pGT_MAT) { delete m_pGT_MAT; m_pGT_MAT = 0;}
  if (m_pPD_Report) { delete m_pPD_Report; m_pPD_Report = 0;}
  if (m_pPD_RECIPE) { delete m_pPD_RECIPE; m_pPD_RECIPE = 0;}
  if (m_pPD_RECIPE_ENTRY) { delete m_pPD_RECIPE_ENTRY; m_pPD_RECIPE_ENTRY = 0;}
  if (m_pPDL_Wire_Add) { delete m_pPDL_Wire_Add; m_pPDL_Wire_Add = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
  {
      cCBS_StdLog_Task::getInstance()->log("Test LF Wire Feeding End use case was successful",1);
  }
  else
  {
      cCBS_StdLog_Task::getInstance()->log("Test LF Wire Feeding End use case failed",1);
  }

  RetValue = true;

  return RetValue;
}

void CARCHIVER_LF_Test_MaterialHandling::initDBClasses()
{
}

void CARCHIVER_LF_Test_MaterialHandling::deleteDBClasses()
{
}


