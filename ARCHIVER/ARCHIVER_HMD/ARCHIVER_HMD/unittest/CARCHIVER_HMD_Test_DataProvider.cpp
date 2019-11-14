
#include "CARCHIVER_HMD_Test_DataProvider.h"
#include "CARCHIVER_HMD_Test_Task.h"

// default constructor
CARCHIVER_HMD_Test_DataProvider::CARCHIVER_HMD_Test_DataProvider(cCBS_Connection* _pConnection)
{
  std::string Message;
  std::string DestinationName = "ARCHIVER_HMD";
  std::string SenderName = "Tracking_HMD_1";
  pConnection = 0;
  pConnection = _pConnection;

  cCBS_StdInitBase::getInstance()->replaceWithEntry("DataManager", "ServerName", TrackerName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TrackerName, "ServerTask", ServerTask);

  cCBS_StdCORBA_Task* pCORBA_Task = cCBS_StdCORBA_Task::getInstance();
}

CARCHIVER_HMD_Test_DataProvider::~CARCHIVER_HMD_Test_DataProvider()
{
}

void CARCHIVER_HMD_Test_DataProvider::setHMDModelResult(const string& ProdID, long InjType)
{
  string  ProductID = ProdID;
//  HMD Model
  seqHMDCalc pSeqHMDFlowCalc;
  seqHMDCalc pSeqHMDAmountCalc;
  sHMDCalc   theHMDCalc;
//---------H M D M O D E L
 // for (double ii = 0; ii < 5; ii++)
  //{
  theHMDCalc.Lime.length(5);
  theHMDCalc.Carbide.length(5);
  theHMDCalc.Magnesium.length(5);

  theHMDCalc.Lime[0]      =  6.0000 ;
  theHMDCalc.Carbide[0]   = 11.0000 ;
  theHMDCalc.Magnesium[0] = 34.0000;

  theHMDCalc.Lime[1]      =  6.1000 ;
  theHMDCalc.Carbide[1]   = 11.1000 ;
  theHMDCalc.Magnesium[1] = 54.0000;

  theHMDCalc.Lime[2]      =  6.2000 ;
  theHMDCalc.Carbide[2]   = 11.2000 ;
  theHMDCalc.Magnesium[2] = 67.2000 ;

  theHMDCalc.Lime[3]      =  6.3000 ;
  theHMDCalc.Carbide[3]   = 11.3000 ;
  theHMDCalc.Magnesium[3] = 36.6434;

  theHMDCalc.Lime[4]      =  6.4000 ;
  theHMDCalc.Carbide[4]   = 11.4000 ;
  theHMDCalc.Magnesium[4] = 453.865;

  CIntfData::insert(pSeqHMDFlowCalc, theHMDCalc);

  theHMDCalc.Lime[0]      = 31.0000 ;
  theHMDCalc.Carbide[0]   = 41.0000 ;
  theHMDCalc.Magnesium[0] = 543.000;

  theHMDCalc.Lime[1]      = 31.1000 ;
  theHMDCalc.Carbide[1]   = 41.1000 ;
  theHMDCalc.Magnesium[1] = 422.522;

  theHMDCalc.Lime[2]      = 31.2000 ;
  theHMDCalc.Carbide[2]   = 41.2000 ;
  theHMDCalc.Magnesium[2] = 51.2000 ; 

  theHMDCalc.Lime[3]      = 31.3000 ;
  theHMDCalc.Carbide[3]   = 41.3000 ;
  theHMDCalc.Magnesium[3] = 342.234;

  theHMDCalc.Lime[4]      = 31.40000 ;
  theHMDCalc.Carbide[4]   = 41.40000 ;
  theHMDCalc.Magnesium[4] = 35656.34;
  CIntfData::insert(pSeqHMDAmountCalc, theHMDCalc);
 // }
  seqHMDModelResult   pSeqHMDModelResult;
  sHMDModelResult     theHMDModelResult;

  DEF::seqDouble seqSlagAmount;
  DEF::seqDouble seqDuration;
  DEF::seqDouble DurationDeslagging;
  DEF::seqDouble seqTemperatureAfter;
  DEF::seqDouble seqCost;

  seqCost.length(5);
  seqDuration.length(5);
  DurationDeslagging.length(5);
  seqSlagAmount.length(5);
  seqTemperatureAfter.length(5);

  seqSlagAmount[0] = 64.0000;
  seqSlagAmount[1] = 64.1000;
  seqSlagAmount[2] = 64.2000;
  seqSlagAmount[3] = 64.3000;
  seqSlagAmount[4] = 64.4000;

  DurationDeslagging[0] = 76.0000;
  DurationDeslagging[1] = 77.0000;
  DurationDeslagging[2] = 78.0000;
  DurationDeslagging[3] = 79.0000;
  DurationDeslagging[4] = 80.0000;

  seqDuration[0] = 75.0000;
  seqDuration[1] = 75.1000;
  seqDuration[2] = 75.2000;
  seqDuration[3] = 75.3000;
  seqDuration[4] = 75.4000;  

  seqTemperatureAfter[0] = 68.0000;
  seqTemperatureAfter[1] = 68.1000;
  seqTemperatureAfter[2] = 68.2000;
  seqTemperatureAfter[3] = 68.3000;
  seqTemperatureAfter[4] = 68.4000;

  seqCost[0] = 70.0000;
  seqCost[1] = 70.1000;
  seqCost[2] = 70.2000;
  seqCost[3] = 70.3000;
  seqCost[4] = 70.4000;
  
  theHMDModelResult.TreatmentKind      = InjType;
  theHMDModelResult.SlagAmount         = seqSlagAmount;
  theHMDModelResult.DurationDeslagging = DurationDeslagging;
  theHMDModelResult.TemperatureAfter   = seqTemperatureAfter;
  theHMDModelResult.Cost               = seqCost;
  theHMDModelResult.Duration           = seqDuration;
  theHMDModelResult.IWarn              = 80;
  theHMDModelResult.CalcAmount         = pSeqHMDAmountCalc;
  theHMDModelResult.CalcFlow           = pSeqHMDFlowCalc;
  
  CIntfData::insert(pSeqHMDModelResult, theHMDModelResult);

//  if (tmpSeqAnalysis) { delete tmpSeqAnalysis; tmpSeqAnalysis = 0;}
//-----------------------------
  CARCHIVER_HMD_Test_Task::getInstance()->setpDM_Interface(ServerTask,DM::PRODUCT);
  m_pDM_Interface = CARCHIVER_HMD_Test_Task::getInstance()->getpDM_Interface();
  m_pDM_Interface->setHMDModelResult(ProductID.c_str(), DATA::HMDPredRes, pSeqHMDModelResult);
}

