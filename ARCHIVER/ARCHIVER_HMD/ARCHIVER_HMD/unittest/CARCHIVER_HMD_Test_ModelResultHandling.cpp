#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdLog_Task.h"

#include "CSMC_RuntimeController.h"
#include "CEventMessageReady.h"

#include "CARCHIVER_HMD_Test_ModelResultHandling.h"
#include "CARCHIVER_HMD_Test_Task.h"

bool AlmostEqual( double d1, double d2)
{
  return abs(d1 - d2) < 1.0;
}

CARCHIVER_HMD_Test_ModelResultHandling::~CARCHIVER_HMD_Test_ModelResultHandling()
{
}

CARCHIVER_HMD_Test_ModelResultHandling::CARCHIVER_HMD_Test_ModelResultHandling(CARCHIVER_Task *Task)
{
  pConnection = CARCHIVER_HMD_Test_Task::getInstance()->getpConnection();
  cCBS_StdInitBase::getInstance()->replaceWithEntry("DataManager", "ServerName", TrackerName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TrackerName, "ServerTask", ServerTask);
}

bool CARCHIVER_HMD_Test_ModelResultHandling::handleHMDModelResultRDY(CEventMessage& Event)
{
  bool RetValue = false;
  std::stringstream Message;
  std::string DataKey = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string RecPlant = DEF_DB_PLANT::HMD;

  long PhaseNo = 0;
  bool VPDEntryExists = false;
  std::string strLadleNo, strLadleType;
  bool TestCode = true;

  CPDH_ACTUAL_RES* m_pPDH_Actual_Res = 0;

  if (pConnection)
  {
    m_pPDH_Actual_Res = new CPDH_ACTUAL_RES(pConnection);
  }

  double d1; 
  double d2;
  seqHMDModelResult *pSeqHMDModelResult = 0; 
  sHMDModelResult    HMDModelResult;
  sHMDCalc        HMDCalcAmount;
  sHMDCalc        HMDCalcFlow;
  sComputerMode ComputerMode;
  seqComputerModes *pSeqComputerModesAvail = 0; 
  seqRecipeList     pSeqRecipeList = 0;
  seqBatchPrio      pSeqRecipeContent = 0;
  sBatchPrio        theBatch ;
  sRecipe           theRecipe;
  seqAnalysis       pSeqAnalysis = 0;
  sAnalysis         theAnalysis;
  double Act_Egy = 0.0;
  long ResPhaseNo = 0;
  long lRows = 0;
  double slagMassModel = 0.0;
  double slagMass = 0.0;
  double temp_end = 0.0;
  double temp_endModel = 0.0 ;
  double mg_co = 0.0;
  double mg_coModel = 0.0;
  double lime_co = 0.0;
  double lime_coModel = 0.0;


  setpDM_Interface(ServerTask,DM::PRODUCT);
  d1             = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatAnnounceTime);
  d2             = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatStartTime);
  pSeqHMDModelResult  = m_pDM_Interface->getHMDModelResult(ProductID.c_str(),DATA::HMDPredRes);

  pSeqComputerModesAvail = m_pDM_Interface->getComputerModes(ProductID.c_str(), DATA::ComputerModeAvail);

  //setpDM_Interface(ServerTask,DM::PLANT);
  //pSeqComputerModesAvail = m_pDM_Interface->getComputerModes(DEF_PLANT::Furnace, DATA::ComputerModes);
  
  long SeqLength = CIntfData::getLength(*pSeqComputerModesAvail);
  long ModelResSeqLength = CIntfData::getLength(*pSeqHMDModelResult);
  if (ModelResSeqLength > 0)
  {
    Message << "\nPDH_ACTUAL_RES" << endl;
  }
  CIntfData::getAt(HMDModelResult, pSeqHMDModelResult, 0);
  CIntfData::getAt(ComputerMode, pSeqComputerModesAvail, 0);
  seqHMDCalc tempCalcAmount = HMDModelResult.CalcAmount;
  seqHMDCalc tempCalcFlow   = HMDModelResult.CalcFlow;
  long InjType = HMDModelResult.TreatmentKind;
  long i = 0;
  //for (long i = 0; i < 5; i++)
  //{
    if (m_pPDH_Actual_Res->selectActual(RecHeatID, RecTreatID, RecPlant,InjType))
    {
          CIntfData::getAt(HMDCalcAmount, tempCalcAmount, i);
          CIntfData::getAt(HMDCalcFlow, tempCalcFlow, i);
          Message <<"Treatment Type"<<i + 1<<endl;

          if (!m_pPDH_Actual_Res->isNull("HEATID",1))
          {
            Message << "HEATID = " << m_pPDH_Actual_Res->getHEATID(1) <<endl;
          } 
          else
          {
            Message << "ERROR:\n  HEATID was not set in PDH_ACTUAL_RES" << endl;
            TestCode = false;
          }
          if (!m_pPDH_Actual_Res->isNull("TREATID",1))
          {
            Message << "TREATID = " << m_pPDH_Actual_Res->getTREATID(1) <<endl;
          } 
          else
          {
            Message << "ERROR:\n  TREATID was not set in PDH_ACTUAL_RES" << endl;
            TestCode = false;
          }
          if (!m_pPDH_Actual_Res->isNull("PLANT",1))
          {
            Message << "PLANT = " << m_pPDH_Actual_Res->getPLANT(1) <<endl;
          } 
          else
          {
            Message << "ERROR:\n  PLANT was not set in PDH_ACTUAL_RES" << endl;
            TestCode = false;
          }
          if (!m_pPDH_Actual_Res->isNull("UPDATENO",1))
          {
            Message << "UPDATENO = " << m_pPDH_Actual_Res->getUPDATENO(1) <<endl;
          } 
          else
          {
            Message << "ERROR:\n  UPDATENO was not set in PDH_ACTUAL_RES" << endl;
            TestCode = false;
          }
          if (!m_pPDH_Actual_Res->isNull("DURSINCEHEATANNOUNCEMENT",1))
          {
            Message << "DURSINCEHEATANNOUNCEMENT = " << m_pPDH_Actual_Res->getDURSINCEHEATANNOUNCEMENT(1) <<endl;
          } 
          else
          {
            Message << "ERROR:\n  DURSINCEHEATANNOUNCEMENT was not set in PDH_ACTUAL_RES" << endl;
            TestCode = false;
          }
          if (!m_pPDH_Actual_Res->isNull("TREAT_TYPE",1))
          {
            Message << "TREAT_TYPE = " << m_pPDH_Actual_Res->getTREAT_TYPE(1) <<endl;
          } 
          else
          {
            Message << "ERROR:\n  TREAT_TYPE was not set in PDH_ACTUAL_RES" << endl;
            TestCode = false;
          }
          if (!m_pPDH_Actual_Res->isNull("REVTIME",1))
          {
            Message << "REVTIME = " << m_pPDH_Actual_Res->getREVTIME(1) <<endl;
          } 
          else
          {
            Message << "ERROR:\n  REVTIME was not set in PDH_ACTUAL_RES" << endl;
            TestCode = false;
          }
          if (!m_pPDH_Actual_Res->isNull("SLAG_MASS",1))
          {
           slagMassModel = HMDModelResult.SlagAmount[i];
           slagMass = m_pPDH_Actual_Res->getSLAG_MASS(1);
           if ( AlmostEqual (slagMassModel,slagMass))
            {
              Message << "SLAG_MASS ("<< HMDModelResult.SlagAmount[i] <<") = " << m_pPDH_Actual_Res->getSLAG_MASS(1) <<endl;
            } 
           else
            {
              Message << "ERROR:\n  The value of SLAG_MASS is different from HMDModelResult.SlagAmount["<<i<<"]" << HMDModelResult.SlagAmount[i] <<endl;
              TestCode = false;
            }
          } 
          else
          {
            Message << "ERROR:\n  SLAG_MASS was not set in PDH_ACTUAL_RES" << endl;
            TestCode = false;
          }
          if (!m_pPDH_Actual_Res->isNull("TEMP_END",1))
          {
            temp_end = m_pPDH_Actual_Res->getTEMP_END(1);
            temp_endModel = HMDModelResult.TemperatureAfter[i];
            if ( AlmostEqual(temp_end, temp_endModel) )
            {
              Message << "TEMP_END ("<< HMDModelResult.TemperatureAfter[i] <<") = " << m_pPDH_Actual_Res->getTEMP_END(1) <<endl;
            } 
            else
            {
              Message << "ERROR:\n  The value of TEMP_END is different from HMDModelResult.TemperatureAfter["<<i<<"]" << HMDModelResult.TemperatureAfter[i] <<endl;
              TestCode = false;
            }
          } 
          else
          {
            Message << "ERROR:\n  TEMP_END was not set in PDH_ACTUAL_RES" << endl;
            TestCode = false;
          }
          if (!m_pPDH_Actual_Res->isNull("MG_CO",1))
          {
            mg_co = m_pPDH_Actual_Res->getMG_CO(1) ;
            mg_coModel = HMDCalcAmount.Magnesium[2];
            if (AlmostEqual (mg_co,mg_coModel) )
            {
              Message << "MG_CO ("<< HMDCalcFlow.Magnesium[2] <<") = " << m_pPDH_Actual_Res->getMG_CO(1) <<endl;
            } 
            else
            {
              Message << "ERROR:\n  The value of MG_CO is different from HMDCalcAmount.Magnesium[2]" << HMDCalcAmount.Magnesium[2] <<endl;
              TestCode = false;
            }
          } 
          else
          {
            Message << "ERROR:\n  MG_CO was not set in PDH_ACTUAL_RES" << endl;
            TestCode = false;
          }
          if (!m_pPDH_Actual_Res->isNull("RATE_MG_CO",1))
          {
            if (m_pPDH_Actual_Res->getRATE_MG_CO(1) == HMDCalcFlow.Magnesium[2])
            {
              Message << "RATE_MG_CO ("<< HMDCalcFlow.Magnesium[2] <<") = " << m_pPDH_Actual_Res->getRATE_MG_CO(1) <<endl;
            } 
            else
            {
              Message << "ERROR:\n  The value of RATE_MG_CO is different from HMDCalcFlow.Magnesium[2]" << HMDCalcFlow.Magnesium[2] <<endl;
              TestCode = false;
            }
          } 
          else
          {
            Message << "ERROR:\n  RATE_MG_CO was not set in PDH_ACTUAL_RES" << endl;
            TestCode = false;
          }
          if (!m_pPDH_Actual_Res->isNull("DUR_CO_PHASE",1))
          {
            if ((m_pPDH_Actual_Res->getDUR_CO_PHASE(1) - HMDModelResult.Duration[i]) < 0.00001)
            {
              Message << "DUR_PHASE_CO ("<< HMDModelResult.Duration[i] <<") = " << m_pPDH_Actual_Res->getDUR_CO_PHASE(1) <<endl;
            } 
            else
            {
              Message << "ERROR:\n  The value of DUR_PHASE_CO is different from HMDModelResult.Duration["<<i<<"]" << HMDModelResult.Duration[i] <<endl;
              TestCode = false;
            }
          } 
          else
          {
            Message << "ERROR:\n  DUR_PHASE_CO was not set in PDH_ACTUAL_RES" << endl;
            TestCode = false;
          }
          if (!m_pPDH_Actual_Res->isNull("MAT_COST_CO",1))
          {
            if ((m_pPDH_Actual_Res->getMAT_COST_CO(1) - HMDModelResult.Cost[i])<0.00001)
            {
              Message << "MAT_COST_CO ("<< HMDModelResult.Cost[i] <<") = " << m_pPDH_Actual_Res->getMAT_COST_CO(1) <<endl;
            } 
            else
            {
              Message << "ERROR:\n  The value of MAT_COST_CO is different from HMDModelResult.Cost["<<i<<"]" << HMDModelResult.Cost[i] <<endl;
              TestCode = false;
            }
          } 
          else
          {
            Message << "ERROR:\n  MAT_COST_CO was not set in PDH_ACTUAL_RES" << endl;
            TestCode = false;
          }
          if (!m_pPDH_Actual_Res->isNull("COMP_AVAIL",1))
          { 
            bool CompFlag1 = true;
            bool CompFlag2 = true;
            for (int x = 0; x < SeqLength; x++)
            { 
              if (CompFlag2)
              {
                CIntfData::getAt(ComputerMode, pSeqComputerModesAvail, x);
                std::string temp = ComputerMode.Device;
                if ((temp == DEF_COMP_MODES::Blowing) && (m_pPDH_Actual_Res->getCOMP_AVAIL(1) == ComputerMode.Status))
                {
                   Message << "COMP_AVAIL ("<< ComputerMode.Status <<") = " << m_pPDH_Actual_Res->getCOMP_AVAIL(1) <<endl;
                   CompFlag1 = false;
                   CompFlag2 = false;
                 } 
              }
            }          
            if (CompFlag1)
            {
              Message << "ERROR:\n  The ComputerMode.Device ("<< ComputerMode.Device <<") are not equal to DEF_COMP_MODES::Blowing" <<endl;
              TestCode = false;
            }
           } 
          else
          {
            Message << "ERROR:\n  COMP_AVAIL was not set in PDH_ACTUAL_RES" << endl;
            TestCode = false;
          }
          if (!m_pPDH_Actual_Res->isNull("LIME_START1",1))
          {
              if (m_pPDH_Actual_Res->getLIME_START1(1) == HMDCalcAmount.Lime[0])
              {
                Message << "LIME_START1 (" << HMDCalcAmount.Lime[0] << ") = " <<m_pPDH_Actual_Res->getLIME_START1(1) <<endl;
              } 
              else
              {
                Message << "ERROR:\n  The value of LIME_START1""<< m_pPDH_Actual_Res->getLIME_START1(1) << ""is different from HMDCalcAmount.Lime[0]" << HMDCalcAmount.Lime[0] <<endl;
                TestCode = false;
              }
          } 
          else
          {
              Message<< "ERROR:\n  The selection of LIME_START1 from the table PDH_ACTUAL_RES was not successful" << endl;
              TestCode = false;
          }
          //if (!m_pPDH_Actual_Res->isNull("LIME_START2",1))
          //{
          //  if (m_pPDH_Actual_Res->getLIME_START2(1) == HMDCalcAmount.Lime[1])
          //  {
          //    Message << "LIME_START2 (" << HMDCalcAmount.Lime[1] << ") = " <<m_pPDH_Actual_Res->getLIME_START2(1) <<endl;
          //  } 
          //  else
          //  {
          //    Message << "ERROR:\n  The value of LIME_START2"<< m_pPDH_Actual_Res->getLIME_START2(1) <<" is different from HMDCalcAmount.Lime[1]" << HMDCalcAmount.Lime[1] <<endl;
          //    TestCode = false;
          //  }
          //} 
          //else
          //{
          //  Message<< "ERROR:\n  The selection of LIME_START2 from the table PDH_ACTUAL_RES was not successful" << endl;
          //  TestCode = false;
          //}
          if (!m_pPDH_Actual_Res->isNull("LIME_CO",1))
          {
            lime_co = m_pPDH_Actual_Res->getLIME_CO(1) ;
            lime_coModel = HMDCalcAmount.Lime[2];
            if (AlmostEqual(lime_co,lime_coModel) )
            {
              Message << "LIME_CO (" << HMDCalcAmount.Lime[2] << ") = " <<m_pPDH_Actual_Res->getLIME_CO(1) <<endl;
            } 
            else
            {
              Message << "ERROR:\n  The value of LIME_CO "<< m_pPDH_Actual_Res->getLIME_CO(1)<<" is different from HMDCalcAmount.Lime[2] " << HMDCalcAmount.Lime[2] <<endl;
              TestCode = false;
            }
          } 
          else
          {
            Message<< "ERROR:\n  The selection of LIME_CO from the table PDH_ACTUAL_RES was not successful" << endl;
            TestCode = false;
          }
          if (!m_pPDH_Actual_Res->isNull("LIME_END1",1))
          {
            if ((m_pPDH_Actual_Res->getLIME_END1(1) - HMDCalcAmount.Lime[3]) < 0.00001)
            {
              Message << "LIME_END1 (" << HMDCalcAmount.Lime[3] << ") = " <<m_pPDH_Actual_Res->getLIME_END1(1) <<endl;
            } 
            else
            {
              Message << "ERROR:\n  The value of LIME_END1" <<m_pPDH_Actual_Res->getLIME_END1(1)<<" is different from HMDCalcAmount.Lime[3]" <<HMDCalcAmount.Lime[3]<<endl;
              TestCode = false;
            }
          } 
          else
          {
            Message<< "ERROR:\n  The selection of LIME_END1 from the table PDH_ACTUAL_RES was not successful" << endl;
            TestCode = false;
          }
          //if (!m_pPDH_Actual_Res->isNull("LIME_END2",1))
          //{
          //  if ((m_pPDH_Actual_Res->getLIME_END2(1) - HMDCalcAmount.Lime[4]) < 0.00001)
          //  {
          //    Message << "LIME_END2 (" << HMDCalcAmount.Lime[4] << ") = " <<m_pPDH_Actual_Res->getLIME_END2(1) <<endl;
          //  } 
          //  else
          //  {
          //    Message << "ERROR:\n  The value of LIME_END2"<<m_pPDH_Actual_Res->getLIME_END2(1)<<" is different from " << HMDCalcAmount.Lime[4] <<endl;
          //    TestCode = false;
          //  }
          //} 
          //else
          //{
          //  Message<< "ERROR:\n  The selection of LIME_END2 from the table PDH_ACTUAL_RES was not successful" << endl;
          //  TestCode = false;
          //}
          if (!m_pPDH_Actual_Res->isNull("CARB_START1",1))
          {
            if (m_pPDH_Actual_Res->getCARB_START1(1) == HMDCalcAmount.Carbide[0])
            {
              Message << "CARB_START1 (" << HMDCalcAmount.Carbide[0] << ") = " <<m_pPDH_Actual_Res->getCARB_START1(1) <<endl;
            } 
            else
            {
              Message << "ERROR:\n  The value of CARB_START1"<<m_pPDH_Actual_Res->getCARB_START1(1)<<" is different from HMDCalcAmount.Carbide[0]" << HMDCalcAmount.Carbide[0] <<endl;
              TestCode = false;
            }
          } 
          else
          {
            Message<< "ERROR:\n  The selection of CARB_START1 from the table PDH_ACTUAL_RES was not successful" << endl;
            TestCode = false;
          }
          //if (!m_pPDH_Actual_Res->isNull("CARB_START2",1))
          //{
          //  if (m_pPDH_Actual_Res->getCARB_START2(1) == HMDCalcAmount.Carbide[1])
          //  {
          //    Message << "CARB_START2 (" << HMDCalcAmount.Carbide[1] << ") = " <<m_pPDH_Actual_Res->getCARB_START2(1) <<endl;
          //  } 
          //  else
          //  {
          //    Message << "ERROR:\n  The value of CARB_START2"<<m_pPDH_Actual_Res->getCARB_START2(1)<<" is different from HMDCalcAmount.Carbide[1]" <<HMDCalcAmount.Carbide[1]<<endl;
          //    TestCode = false;
          //  }
          //} 
          //else
          //{
          //  Message<< "ERROR:\n  The selection of CARB_START2 from the table PDH_ACTUAL_RES was not successful" << endl;
          //  TestCode = false;
          //}
          if (!m_pPDH_Actual_Res->isNull("CARB_CO",1))
          {
            if (m_pPDH_Actual_Res->getCARB_CO(1) == HMDCalcAmount.Carbide[2])
            {
              Message << "CARB_CO (" << HMDCalcAmount.Carbide[2] << ") = " <<m_pPDH_Actual_Res->getCARB_CO(1) <<endl;
            } 
            else
            {
              Message << "ERROR:\n  The value of CARB_CO"<<m_pPDH_Actual_Res->getCARB_CO(1)<<" is different from HMDCalcAmount.Carbide[2]" << HMDCalcAmount.Carbide[2] <<endl;
              TestCode = false;
            }
          } 
          else
          {
            Message<< "ERROR:\n  The selection of CARB_CO from the table PDH_ACTUAL_RES was not successful" << endl;
            TestCode = false;
          }
          if (!m_pPDH_Actual_Res->isNull("CARB_END1",1))
          {
            if ((m_pPDH_Actual_Res->getCARB_END1(1) - HMDCalcAmount.Carbide[3]) < 0.00001)
            {
              Message << "CARB_END1 (" << HMDCalcAmount.Carbide[3] << ") = " <<m_pPDH_Actual_Res->getCARB_END1(1) <<endl;
            } 
            else
            {
              Message << "ERROR:\n  The value of CARB_END1"<<m_pPDH_Actual_Res->getCARB_END1(1)<<" is different from HMDCalcAmount.Carbide[3]" <<HMDCalcAmount.Carbide[3]<<endl;
              TestCode = false;
            }
          } 
          else
          {
            Message<< "ERROR:\n  The selection of CARB_END1 from the table PDH_ACTUAL_RES was not successful" << endl;
            TestCode = false;
          }
          //if (!m_pPDH_Actual_Res->isNull("CARB_END2",1))
          //{
          //  if (m_pPDH_Actual_Res->getCARB_END2(1) == HMDCalcAmount.Carbide[4])
          //  {
          //    Message << "CARB_END2 (" << HMDCalcAmount.Carbide[4] << ") = " <<m_pPDH_Actual_Res->getCARB_END2(1) <<endl;
          //  } 
          //  else
          //  {
          //    Message << "ERROR:\n  The value of CARB_END2"<<m_pPDH_Actual_Res->getCARB_END2(1)<<" is different from HMDCalcAmount.Carbide[4]" <<HMDCalcAmount.Carbide[4]<<endl;
          //    TestCode = false;
          //  }
          //} 
          //else
          //{
          //  Message<< "ERROR:\n  The selection of CARB_END2 from the table PDH_ACTUAL_RES was not successful" << endl;
          //  TestCode = false;
          //}

          if (!m_pPDH_Actual_Res->isNull("RATE_LIME_START1",1))
          {
            if (m_pPDH_Actual_Res->getRATE_LIME_START1(1) == HMDCalcFlow.Lime[0])
            {
              Message << "RATE_LIME_START1 (" << HMDCalcFlow.Lime[0] << ") = " <<m_pPDH_Actual_Res->getRATE_LIME_START1(1) <<endl;
            } 
            else
            {
              Message << "ERROR:\n  The value of RATE_LIME_START1"<<m_pPDH_Actual_Res->getRATE_LIME_START1(1)<<" is different from HMDCalcFlow.Lime[0]" <<HMDCalcFlow.Lime[0]<<endl;
              TestCode = false;
            }
          } 
          else
          {
            Message<< "ERROR:\n  The selection of RATE_LIME_START1 from the table PDH_ACTUAL_RES was not successful" << endl;
            TestCode = false;
          }
          //if (!m_pPDH_Actual_Res->isNull("RATE_LIME_START2",1))
          //{
          //  if ((m_pPDH_Actual_Res->getRATE_LIME_START2(1) - HMDCalcFlow.Lime[1]) < 0.00001 )
          //  {
          //    Message << "RATE_LIME_START2 (" << HMDCalcFlow.Lime[1] << ") = " <<m_pPDH_Actual_Res->getRATE_LIME_START2(1) <<endl;
          //  } 
          //  else
          //  {
          //    Message << "ERROR:\n  The value of RATE_LIME_START2"<<m_pPDH_Actual_Res->getRATE_LIME_START2(1)<<" is different from HMDCalcFlow.Lime[1]" <<HMDCalcFlow.Lime[1]<<endl;
          //    TestCode = false;
          //  }
          //} 
          //else
          //{
          //  Message<< "ERROR:\n  The selection of RATE_LIME_START2 from the table PDH_ACTUAL_RES was not successful" << endl;
          //  TestCode = false;
          //}
          if (!m_pPDH_Actual_Res->isNull("RATE_LIME_CO",1))
          {
            if ((m_pPDH_Actual_Res->getRATE_LIME_CO(1) - HMDCalcFlow.Lime[2]) < 0.00001)
            {
              Message << "RATE_LIME_CO (" << HMDCalcFlow.Lime[2] << ") = " <<m_pPDH_Actual_Res->getRATE_LIME_CO(1) <<endl;
            } 
            else
            {
              Message << "ERROR:\n  The value of RATE_LIME_CO"<<m_pPDH_Actual_Res->getRATE_LIME_CO(1)<<" is different from HMDCalcFlow.Lime[2]" << HMDCalcFlow.Lime[2] <<endl;
              TestCode = false;
            }
          } 
          else
          {
            Message<< "ERROR:\n  The selection of RATE_LIME_CO from the table PDH_ACTUAL_RES was not successful" << endl;
            TestCode = false;
          }
          if (!m_pPDH_Actual_Res->isNull("RATE_LIME_END1",1))
          {
            if (m_pPDH_Actual_Res->getRATE_LIME_END1(1) == HMDCalcFlow.Lime[3])
            {
              Message << "RATE_LIME_END1 (" << HMDCalcFlow.Lime[3] << ") = " <<m_pPDH_Actual_Res->getRATE_LIME_END1(1) <<endl;
            } 
            else
            {
              Message << "ERROR:\n  The value of RATE_LIME_END1"<<m_pPDH_Actual_Res->getRATE_LIME_END1(1)<<" is different from HMDCalcFlow.Lime[3]" << HMDCalcFlow.Lime[3] <<endl;
              TestCode = false;
            }
          } 
          else
          {
            Message<< "ERROR:\n  The selection of RATE_LIME_END1 from the table PDH_ACTUAL_RES was not successful" << endl;
            TestCode = false;
          }
          //if (!m_pPDH_Actual_Res->isNull("RATE_LIME_END2",1))
          //{
          //  if (m_pPDH_Actual_Res->getRATE_LIME_END2(1) == HMDCalcFlow.Lime[4])
          //  {
          //    Message << "RATE_LIME_END2 (" << HMDCalcFlow.Lime[4] << ") = " <<m_pPDH_Actual_Res->getRATE_LIME_END2(1) <<endl;
          //  } 
          //  else
          //  {
          //    Message << "ERROR:\n  The value of RATE_LIME_END2"<<m_pPDH_Actual_Res->getRATE_LIME_END2(1)<<" is different from HMDCalcFlow.Lime[4]" << HMDCalcFlow.Lime[4] <<endl;
          //    TestCode = false;
          //  }
          //} 
          //else
          //{
          //  Message<< "ERROR:\n  The selection of RATE_LIME_END2 from the table PDH_ACTUAL_RES was not successful" << endl;
          //  TestCode = false;
          //}

          if (!m_pPDH_Actual_Res->isNull("RATE_CARB_START1",1))
          {
            if (m_pPDH_Actual_Res->getRATE_CARB_START1(1) == HMDCalcFlow.Carbide[0])
            {
              Message << "RATE_CARB_START1 (" << HMDCalcFlow.Carbide[0] << ") = " <<m_pPDH_Actual_Res->getRATE_CARB_START1(1) <<endl;
            } 
            else
            {
              Message << "ERROR:\n  The value of RATE_CARB_START1"<<m_pPDH_Actual_Res->getRATE_CARB_START1(1)<<" is different from HMDCalcFlow.Carbide[0]" << HMDCalcFlow.Carbide[0] <<endl;
              TestCode = false;
            }
          } 
          else
          {
            Message<< "ERROR:\n  The selection of RATE_CARB_START1 from the table PDH_ACTUAL_RES was not successful" << endl;
            TestCode = false;
          }
          //if (!m_pPDH_Actual_Res->isNull("RATE_CARB_START2",1))
          //{
          //  if (m_pPDH_Actual_Res->getRATE_CARB_START2(1) == HMDCalcFlow.Carbide[1])
          //  {
          //    Message << "RATE_CARB_START2 (" << HMDCalcFlow.Carbide[1] << ") = " <<m_pPDH_Actual_Res->getRATE_CARB_START2(1) <<endl;
          //  } 
          //  else
          //  {
          //    Message << "ERROR:\n  The value of RATE_CARB_START2"<<m_pPDH_Actual_Res->getRATE_CARB_START2(1)<<" is different from HMDCalcFlow.Carbide[1]" << HMDCalcFlow.Carbide[1] <<endl;
          //    TestCode = false;
          //  }
          //} 
          //else
          //{
          //  Message<< "ERROR:\n  The selection of RATE_CARB_START2 from the table PDH_ACTUAL_RES was not successful" << endl;
          //  TestCode = false;
          //}
          if (!m_pPDH_Actual_Res->isNull("RATE_CARB_CO",1))
          {
            if ((m_pPDH_Actual_Res->getRATE_CARB_CO(1) - HMDCalcFlow.Carbide[2]) < 0.00001)
            {
              Message << "RATE_CARB_CO (" << HMDCalcFlow.Carbide[2] << ") = " <<m_pPDH_Actual_Res->getRATE_CARB_CO(1) <<endl;
            } 
            else
            {
              Message << "ERROR:\n  The value of RATE_CARB_CO"<<m_pPDH_Actual_Res->getRATE_CARB_CO(1)<<" is different from HMDCalcFlow.Carbide[2]" <<HMDCalcFlow.Carbide[2]<<endl;
              TestCode = false;
            }
          } 
          else
          {
            Message<< "ERROR:\n  The selection of RATE_CARB_CO from the table PDH_ACTUAL_RES was not successful" << endl;
            TestCode = false;
          }
          if (!m_pPDH_Actual_Res->isNull("RATE_CARB_END1",1))
          {
            if (m_pPDH_Actual_Res->getRATE_CARB_END1(1) == HMDCalcFlow.Carbide[3])
            {
              Message << "RATE_CARB_END1 (" << HMDCalcFlow.Carbide[3] << ") = " <<m_pPDH_Actual_Res->getRATE_CARB_END1(1) <<endl;
            } 
            else
            {
              Message << "ERROR:\n  The value of RATE_CARB_END1"<<m_pPDH_Actual_Res->getRATE_CARB_END1(1)<<"is different from HMDCalcFlow.Carbide[3]" << HMDCalcFlow.Carbide[3] <<endl;
              TestCode = false;
            }
          } 
          else
          {
            Message<< "ERROR:\n  The selection of RATE_CARB_END1 from the table PDH_ACTUAL_RES was not successful" << endl;
            TestCode = false;
          }
          //if (!m_pPDH_Actual_Res->isNull("RATE_CARB_END2",1))
          //{
          //  if (m_pPDH_Actual_Res->getRATE_CARB_END2(1) == HMDCalcFlow.Carbide[4])
          //  {
          //    Message << "RATE_CARB_END2 (" << HMDCalcFlow.Carbide[4] << ") = " <<m_pPDH_Actual_Res->getRATE_CARB_END2(1) <<endl;
          //  } 
          //  else
          //  {
          //    Message << "ERROR:\n  The value of RATE_CARB_END2"<<m_pPDH_Actual_Res->getRATE_CARB_END2(1) <<" is different from HMDCalcFlow.Carbide[4]" << HMDCalcFlow.Carbide[4] <<endl;
          //    TestCode = false;
          //  }
          //} 
          //else
          //{
          //  Message<< "ERROR:\n  The selection of RATE_CARB_END2 from the table PDH_ACTUAL_RES was not successful" << endl;
          //  TestCode = false;
          //}
       }
      else
      {
        Message << "ERROR:\n  PDH_ACTUAL_RES, select for HeatID: " << RecHeatID << ", TreatID: "
          << RecTreatID << ", PLANT: " << RecPlant << " failed!\n";
        TestCode = false;
      }      
      Message << endl;
    //}
  
  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (m_pPDH_Actual_Res) { delete m_pPDH_Actual_Res; m_pPDH_Actual_Res = 0;}

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Model Result use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Model Result use case failed",1);

  RetValue = true;

  return RetValue;
}

void CARCHIVER_HMD_Test_ModelResultHandling::initDBClasses()
{
}

void CARCHIVER_HMD_Test_ModelResultHandling::deleteDBClasses()
{
}
