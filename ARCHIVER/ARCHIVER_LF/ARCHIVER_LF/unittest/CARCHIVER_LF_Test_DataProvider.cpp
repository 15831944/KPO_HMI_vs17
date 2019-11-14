
#include "CARCHIVER_LF_Test_DataProvider.h"
#include "CARCHIVER_LF_Test_Task.h"

// default constructor
CARCHIVER_LF_Test_DataProvider::CARCHIVER_LF_Test_DataProvider(cCBS_Connection* _pConnection)
{
  CDateTime DateTime;
  
  std::string  PlanLadleType   = DEF_LADLE_TYPES::TeemingLadle;
  std::string  TransferCar     = DEF_PLANT::TransferCar1;
  std::string Message;
  std::string DestinationName = "ARCHIVER_LF";
  std::string SenderName = "Tracking_LF_1";
  pConnection = 0;
  pConnection = _pConnection;

  cCBS_StdInitBase::getInstance()->replaceWithEntry("DataManager", "ServerName", TrackerName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TrackerName, "ServerTask", ServerTask);

  cCBS_StdCORBA_Task* pCORBA_Task = cCBS_StdCORBA_Task::getInstance();
}

CARCHIVER_LF_Test_DataProvider::~CARCHIVER_LF_Test_DataProvider()
{
}

void CARCHIVER_LF_Test_DataProvider::setLFModelResult(const string& ForHeatID, const string& ForTreatID)
{
  CGCL_STIRR_PHASE* m_pGCL_Stirr_Phase;
    
  m_pGCL_Stirr_Phase = 0;

  m_pGCL_Stirr_Phase = new CGCL_STIRR_PHASE(pConnection);
  
  std::string HeatID;
  std::string Plant;
  std::string ProductID;
  std::string TreatID;

  ProductID = ForHeatID + "_" + ForTreatID; 
  //---------B A T C H
  seqBatchPrio          pSeqBatchPrio;
  //  seqBatchPrio *tmpSeqBatchPrio;
  sBatchPrio            theBatchPrio;
  sBatch                theBatch;
  seqLFElecPredRes      pSeqLFElecPredRes;
  sLFElecPredRes        theLFElecPredRes;
  sDate                 theRevTime;
  seqLFStirrPredRes     pseqLFStirrPredRes;
  sLFStirrPredRes       theLFStirrPredRes;
  seqAnalysis           SeqAnalysis;
  seqAnalysis          *tmpSeqAnalysis;
  sAnalysis             Analysis;
  sPredRes              PredRes;
  seqPredRes            pSeqPredRes;
  sGenRes               GenRes;
  seqRecipeList         pSeqRecipeList;
  sRecipe               theRecipe;
  
  //---------P r e d  R e s
  {
  Analysis.Element = "C";
  Analysis.Concentration = 4.2;
  CIntfData::insert(SeqAnalysis, Analysis);
  Analysis.Element = "P";
  Analysis.Concentration = 0.1;
  CIntfData::insert(SeqAnalysis, Analysis);
  tmpSeqAnalysis = new seqAnalysis(SeqAnalysis);

  //-------Met Time Stamp
  sMetTimeStamp MetTimeStamp;
  CDateTime Now;
  sDate RevDate = Now.assDate();
  sDate ActionDate = Now.assDate();;
  
  MetTimeStamp.O2_Moment = 11.000;
  MetTimeStamp.N2_Moment = 12.000;
  MetTimeStamp.Ar_Moment = 13.000;
  MetTimeStamp.Elec_Moment = 14.000;
  MetTimeStamp.DurSinceHeatAnnouncement = 15.000;
  MetTimeStamp.DurSinceStartOfHeat = 16.000;
  MetTimeStamp.RevDate = RevDate;
  MetTimeStamp.ActionDate = ActionDate;
  
  //------GenRes
  GenRes.MetTimeStamp = MetTimeStamp;
  GenRes.Analysis = *tmpSeqAnalysis;
  GenRes.SlagWeight = 1000.000;
  GenRes.SteelWeight = 2000.000;
  GenRes.Temp = 1500.000;
  GenRes.DurPhase = 1200.000;

  PredRes.Phase = "Actual";
  PredRes.PhaseNo = 10;
  PredRes.GenRes = GenRes;
  PredRes.PhaseActive = 1;

  CIntfData::insert(pSeqPredRes, PredRes);
  }
  //---------BATCH
  {
  theBatch.MatCode = "6100";
  theBatch.Mass = 200.7;
  theBatch.MatFeedSpeed = 70.3;
  theBatchPrio.BatchData = theBatch;
  theBatchPrio.ChargPrio = 1;

  CIntfData::insert(pSeqBatchPrio, theBatchPrio);

  theBatch.MatCode = "3100";
  theBatch.Mass = 103.7;
  theBatch.MatFeedSpeed = 73.3;
  theBatchPrio.BatchData = theBatch;
  theBatchPrio.ChargPrio = 2;

  CIntfData::insert(pSeqBatchPrio, theBatchPrio);

  theBatch.MatCode = "3501";
  theBatch.Mass = 250.7;
  theBatch.MatFeedSpeed = 72.3;
  theBatchPrio.BatchData = theBatch;
  theBatchPrio.ChargPrio = 3;

  CIntfData::insert(pSeqBatchPrio, theBatchPrio);

  theBatch.MatCode = "3601";
  theBatch.Mass = 150.7;
  theBatch.MatFeedSpeed = 71.3;
  theBatchPrio.BatchData = theBatch;
  theBatchPrio.ChargPrio = 4;

  CIntfData::insert(pSeqBatchPrio, theBatchPrio);
  }
  //--------- 1. R E C I P E
  {
  theRecipe.RecipeName = "SlagForm";
  theRecipe.RecipeNo = 1;
  theRecipe.RecipeSource = "Bin";
  theRecipe.MatFeedRate = 7003;
  theRecipe.O2_Charge_Moment = 111.1;
  theRecipe.RecipeContent = pSeqBatchPrio;
  theRecipe.RecipeData.HomogDuration = 700;
  theRecipe.RecipeData.BulkVolume = 77;
  theRecipe.RecipeData.TotalMass = 66.6;
  theRecipe.Product.HeatId = HeatID.c_str();
  theRecipe.Product.TreatId = TreatID.c_str();
  theRecipe.Product.Plant = Plant.c_str();

  CIntfData::insert(pSeqRecipeList, theRecipe);
  //---------2. R E C I P E
  //theRecipe.RecipeName = "AlloyFinal";
  //theRecipe.RecipeNo = 14;
  //theRecipe.RecipeSource = "Bin";
  //theRecipe.MatFeedRate = 7003;
  //theRecipe.O2_Charge_Moment = 222.2;
  //theRecipe.RecipeContent = pSeqBatchPrio;
  //theRecipe.RecipeData.HomogDuration = 703;
  //theRecipe.RecipeData.BulkVolume = 79;
  //theRecipe.RecipeData.TotalMass = 55.5;
  //theRecipe.Product.HeatId = HeatID.c_str();
  //theRecipe.Product.TreatId = TreatID.c_str();
  //theRecipe.Product.Plant = Plant.c_str();

  //CIntfData::insert(pSeqRecipeList, theRecipe);
  }
  //----------ELEC PRED RES
  {
  long input = 0;
  cout << "Enter the status for HeatingInitial (0/1)";
  cin >> input;
  for (long jj = 1; jj < 3; jj++)
  {
    theRevTime.year = 2008;
    theRevTime.month = 11;
    theRevTime.day = 13;
    theRevTime.hour = 13;
    theRevTime.minute = 46;
    theRevTime.second = 34;
    theRevTime.msec = 232;
    theRevTime.dstFlag = true;
    theLFElecPredRes.BaseMass = 12.00;
    theLFElecPredRes.DurStep  = 34.00+jj;
    theLFElecPredRes.DurUntilEndOfStep = 76.00;
    theLFElecPredRes.DurUntilStartOfStep = 234.00;
    theLFElecPredRes.ElecEgy = 45.23;
    theLFElecPredRes.ElecEgyStep = 151;
    theLFElecPredRes.ElecPhase = DEF_LF_PHASES::HeatingInitial;
    theLFElecPredRes.Enable = input;
    theLFElecPredRes.GasType = DEF_GAS::Ar;
    theLFElecPredRes.ImpCurve = jj;
    theLFElecPredRes.Order = 343;
    theLFElecPredRes.Priority = 1;
    theLFElecPredRes.RevDate = theRevTime;
    theLFElecPredRes.SpecEgy = 332;
    theLFElecPredRes.Step = jj;
    theLFElecPredRes.StirrFlow = 323;
    theLFElecPredRes.StirrIntensity = 643;
    theLFElecPredRes.StirrIntensityCode = "6100";
    theLFElecPredRes.VoltTap = 4;

    CIntfData::insert(pSeqLFElecPredRes, theLFElecPredRes);
  }

  input = 0;
  cout << "Enter the status for HeatingMain (0/1)";
  cin >> input;
  for (long jj = 1; jj < 3; jj++)
  {
    theRevTime.year = 2008;
    theRevTime.month = 11;
    theRevTime.day = 13;
    theRevTime.hour = 13;
    theRevTime.minute = 46;
    theRevTime.second = 34;
    theRevTime.msec = 232;
    theRevTime.dstFlag = true;
    theLFElecPredRes.BaseMass = 12.00;
    theLFElecPredRes.DurStep  = 35.00+jj;
    theLFElecPredRes.DurUntilEndOfStep = 76.00;
    theLFElecPredRes.DurUntilStartOfStep = 234.00;
    theLFElecPredRes.ElecEgy = 45.23;
    theLFElecPredRes.ElecEgyStep = 142;
    theLFElecPredRes.ElecPhase = DEF_LF_PHASES::HeatingMain;
    theLFElecPredRes.Enable = input;
    theLFElecPredRes.GasType = DEF_GAS::Ar;
    theLFElecPredRes.ImpCurve = 3+jj;
    theLFElecPredRes.Order = 343;
    theLFElecPredRes.Priority = 1;
    theLFElecPredRes.RevDate = theRevTime;
    theLFElecPredRes.SpecEgy = 332;
    theLFElecPredRes.Step = jj;
    theLFElecPredRes.StirrFlow = 323;
    theLFElecPredRes.StirrIntensity = 643;
    theLFElecPredRes.StirrIntensityCode = "3601";
    theLFElecPredRes.VoltTap = 5;

    CIntfData::insert(pSeqLFElecPredRes, theLFElecPredRes);
  }

  input = 0;
  cout << "Enter the status for HeatingFinal (0/1)";
  cin >> input;
  for (long jj = 1; jj < 3; jj++)
  {
    theRevTime.year = 2008;
    theRevTime.month = 11;
    theRevTime.day = 13;
    theRevTime.hour = 13;
    theRevTime.minute = 46;
    theRevTime.second = 34;
    theRevTime.msec = 232;
    theRevTime.dstFlag = true;
    theLFElecPredRes.BaseMass = 12.00;
    theLFElecPredRes.DurStep  = 36.00+jj;
    theLFElecPredRes.DurUntilEndOfStep = 76.00;
    theLFElecPredRes.DurUntilStartOfStep = 234.00;
    theLFElecPredRes.ElecEgy = 45.23;
    theLFElecPredRes.ElecEgyStep = 133;
    theLFElecPredRes.ElecPhase = DEF_LF_PHASES::HeatingFinal;
    theLFElecPredRes.Enable = input;
    theLFElecPredRes.GasType = DEF_GAS::Ar;
    theLFElecPredRes.ImpCurve = 2+jj;
    theLFElecPredRes.Order = 343;
    theLFElecPredRes.Priority = 1;
    theLFElecPredRes.RevDate = theRevTime;
    theLFElecPredRes.SpecEgy = 332;
    theLFElecPredRes.Step = jj;
    theLFElecPredRes.StirrFlow = 323;
    theLFElecPredRes.StirrIntensity = 643;
    theLFElecPredRes.StirrIntensityCode = "3100";
    theLFElecPredRes.VoltTap = 6;

    CIntfData::insert(pSeqLFElecPredRes, theLFElecPredRes);
  }

  input = 0;
  cout << "Enter the status for HeatingTempHold (0/1)";
  cin >> input;
  for (long jj = 1; jj < 3; jj++)
  {
    theRevTime.year = 2008;
    theRevTime.month = 11;
    theRevTime.day = 13;
    theRevTime.hour = 13;
    theRevTime.minute = 46;
    theRevTime.second = 34;
    theRevTime.msec = 232;
    theRevTime.dstFlag = true;
    theLFElecPredRes.BaseMass = 12.00;
    theLFElecPredRes.DurStep  = 36.00;
    theLFElecPredRes.DurUntilEndOfStep = 76.00;
    theLFElecPredRes.DurUntilStartOfStep = 234.00;
    theLFElecPredRes.ElecEgy = 45.23;
    theLFElecPredRes.ElecPhase = DEF_LF_PHASES::HeatingTempHold;
    theLFElecPredRes.ElecEgyStep = 123;
    theLFElecPredRes.Enable = input;
    theLFElecPredRes.GasType = DEF_GAS::Ar;
    theLFElecPredRes.ImpCurve = 1+jj;
    theLFElecPredRes.Order = 343;
    theLFElecPredRes.Priority = 1;
    theLFElecPredRes.RevDate = theRevTime;
    theLFElecPredRes.SpecEgy = 332;
    theLFElecPredRes.Step = jj;
    theLFElecPredRes.StirrFlow = 323;
    theLFElecPredRes.StirrIntensity = 643;
    theLFElecPredRes.StirrIntensityCode = "3600";
    theLFElecPredRes.VoltTap = 6;
    

    CIntfData::insert(pSeqLFElecPredRes, theLFElecPredRes);
  }
  }

  //----------Stirr Pred Res
  {
  // get all phases from the table
  std::string PhaseName;
  if (m_pGCL_Stirr_Phase->select(CSMC_DBData::unspecString))
  {
    long length = m_pGCL_Stirr_Phase->getLastRow();
    // there are only 19 fields in the telegramm
    if (length > 19)
      length = 19;
    for (long k = 1; k <= length; k++)
    {
      PhaseName = m_pGCL_Stirr_Phase->getPRACPHASE(k);//DEF_LF_PHASES::Cooling;
      theLFStirrPredRes.StirrPhase = PhaseName.c_str();
      if (m_pGCL_Stirr_Phase->getFLAGDUR(k) > 0)
      {
        theLFStirrPredRes.DurStep = k;
      }
      else
      {
        theLFStirrPredRes.DurStep = 0;
      }

      theLFStirrPredRes.DurUntilEndOfStep = 2434;
      theLFStirrPredRes.DurUntilStartOfStep = 1235;
      theLFStirrPredRes.ElecEgy = 452;
      theLFStirrPredRes.Enable = 2;
      theLFStirrPredRes.GasType = DEF_GAS::N2;
      theLFStirrPredRes.ImpCurve = 534;
      theLFStirrPredRes.isPatternOrActivity = 0;
      theLFStirrPredRes.Order = k;
      theLFStirrPredRes.Priority = 99;
      theLFStirrPredRes.SlagMass = 452;
      theLFStirrPredRes.SteelMass = 6342 + k;
      theLFStirrPredRes.StirrIntensity = 1;
      theLFStirrPredRes.StirrFlow = theLFStirrPredRes.StirrIntensity;
      theLFStirrPredRes.StirrIntensityCode = "435";
      theLFStirrPredRes.Temp = 2314;
      theLFStirrPredRes.VoltTap = 1245;

      CIntfData::insert(pseqLFStirrPredRes, theLFStirrPredRes);
    }
    // if there were less rows, set the last many times
    if (length < 19)
    {
      for (long k = length; k <= 19; k++)
      {
        CIntfData::insert(pseqLFStirrPredRes, theLFStirrPredRes);
      }
    }
  }
  }
  CARCHIVER_LF_Test_Task::getInstance()->setpDM_Interface(ServerTask,DM::PRODUCT);
  m_pDM_Interface = CARCHIVER_LF_Test_Task::getInstance()->getpDM_Interface();
  m_pDM_Interface->setRecipeList(ProductID.c_str(), DATA::LFMatRecipe, pSeqRecipeList);
  m_pDM_Interface->setLFStirrPredRes(ProductID.c_str(), DATA::LFStirrPredRes, pseqLFStirrPredRes);
  m_pDM_Interface->setLFElecPredRes(ProductID.c_str(), DATA::LFElecPredRes, pSeqLFElecPredRes);
  m_pDM_Interface->setPredRes(ProductID.c_str(), DATA::LFPredRes, pSeqPredRes);
}
void CARCHIVER_LF_Test_DataProvider::setComputerMode(const string& ForHeatID, const string& ForTreatID, long ElecMode, long StirrMode, long MatMode)
{
  std::string ProductID;
  ProductID = ForHeatID + "_" + ForTreatID;
  
  seqComputerModes pseqComputerMode;
  sComputerMode    theComputerMode;

  theComputerMode.Device = DEF_COMP_MODES::Electric;
  theComputerMode.Status = ElecMode;
  CIntfData::insert(pseqComputerMode, theComputerMode);

  theComputerMode.Device = DEF_COMP_MODES::Stirring;
  theComputerMode.Status = StirrMode;
  CIntfData::insert(pseqComputerMode, theComputerMode);

  theComputerMode.Device = DEF_COMP_MODES::MatHandle;
  theComputerMode.Status = MatMode;  
  CIntfData::insert(pseqComputerMode, theComputerMode);

  theComputerMode.Device = DEF_COMP_MODES::Level2Error;
  theComputerMode.Status = DEF_MAT_HANDLE_STATUS::NotAvailable;
  CIntfData::insert(pseqComputerMode, theComputerMode);

  theComputerMode.Device = DEF_COMP_MODES::RejectHeatL1;
  theComputerMode.Status = DEF_MAT_HANDLE_STATUS::NotAvailable;
  CIntfData::insert(pseqComputerMode, theComputerMode);

  theComputerMode.Device = DEF_COMP_MODES::MatHandleL1Error;
  theComputerMode.Status = DEF_MAT_HANDLE_STATUS::NotAvailable;
  CIntfData::insert(pseqComputerMode, theComputerMode);

  CARCHIVER_LF_Test_Task::getInstance()->setpDM_Interface(ServerTask,DM::PRODUCT);
  m_pDM_Interface = CARCHIVER_LF_Test_Task::getInstance()->getpDM_Interface();
  m_pDM_Interface->setComputerModes(ProductID.c_str(), DATA::ComputerModeAvail, pseqComputerMode);
  m_pDM_Interface->setComputerModes(ProductID.c_str(), DATA::ComputerModes, pseqComputerMode);
}

void CARCHIVER_LF_Test_DataProvider::setLadleCar(const string& ProductID, const string& CarID, const string& LadleId)
{
  CARCHIVER_LF_Test_Task::getInstance()->setpDM_Interface(ServerTask,DM::PRODUCT);
  m_pDM_Interface = CARCHIVER_LF_Test_Task::getInstance()->getpDM_Interface();
  m_pDM_Interface->setString(ProductID.c_str(), DATA::LadleId, LadleId.c_str());
  m_pDM_Interface->setLong  (ProductID.c_str(), DATA::ProbeType, 0);
  m_pDM_Interface->setString(ProductID.c_str(), DATA::LadleType, DEF_LADLE_TYPES::TeemingLadle);
  m_pDM_Interface->setString(ProductID.c_str(), DATA::LadleTransferCarId, CarID.c_str());
}
void CARCHIVER_LF_Test_DataProvider::setTempAndSteelSampleReq(const string& ProductID, bool TempReq, bool SteelSampleReq)
{
  CARCHIVER_LF_Test_Task::getInstance()->setpDM_Interface(ServerTask,DM::PRODUCT);
  m_pDM_Interface = CARCHIVER_LF_Test_Task::getInstance()->getpDM_Interface();
  m_pDM_Interface->setBoolean(ProductID.c_str(), DATA::TempMeasReq, TempReq);
  m_pDM_Interface->setBoolean(ProductID.c_str(), DATA::SteelSampleReq, SteelSampleReq);
}

void CARCHIVER_LF_Test_DataProvider::setProbeType(string ProductID, long ProbeType)
{
  CARCHIVER_LF_Test_Task::getInstance()->setpDM_Interface(ServerTask,DM::PRODUCT);
  m_pDM_Interface = CARCHIVER_LF_Test_Task::getInstance()->getpDM_Interface();
  m_pDM_Interface->setLong(ProductID.c_str(), DATA::ProbeType, ProbeType);
}