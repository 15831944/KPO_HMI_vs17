// Copyright (C) 2007 SMS Demag AG

#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <string>
#include <vector>
using namespace std;
#include "cCBS_StdLog_Task.h"
#include "cCBS_StdEvent_Task.h"
#include "cCBS_StdCORBA_Task.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"

#include "CIntfData.h"



#include "CDM_HMDSignalsAndMeasurementsEventHandler.h"
#include "CDM_HMDTreatmentManagementEventHandler.h"
#include "CDM_HMDAnalysisEventHandler.h"
#include "CDM_HMDMaterialEventHandler.h"
#include "CDM_HMDModesAndAvailabilitiesEventHandler.h"
#include "CDM_HMDPurposeEventHandler.h"
#include "CDM_HMDModelResultEventHandler.h"


#include "CDM_HMDEventHandler.h"

#include "CDM_HMDEventLogHandlerAnalysis.h"
#include "CDM_HMDEventLogHandlerMaterial.h"
#include "CDM_HMDEventLogHandlerModelResults.h"
#include "CDM_HMDEventLogHandlerModesAndAvailabilities.h"
#include "CDM_HMDEventLogHandlerPurpose.h"
#include "CDM_HMDEventLogHandlerSignalsAndMeasurements.h"

//##ModelId=412E15D30084
#include "CDM_HMDTask.h"
//##ModelId=45139A71033B
#include "CDM_HMDEventLogHandler.h"


//##ModelId=412E15D30084
CDM_HMDTask::CDM_HMDTask()
{
}

//##ModelId=45139A710333
CDM_HMDTask::~CDM_HMDTask()
{
}

//##ModelId=45139A710335
bool CDM_HMDTask::initialize()
{
	bool RetCode = true;
  // must be called first 
  RetCode = CDM_Task::initialize();

    // N2, Ar
  m_GasDataList.push_back(DEF_GAS::N2);
  m_GasDataList.push_back(DEF_GAS::Ar);

  m_pPlantManager             = new CDM_HMDPlantManager();

  std::string TreatIDPrefix = "H";  //use standard prefix "H"
  // read from ini-file a new prefix. If there one defined than use it
  cCBS_StdInitBase::getInstance()->replaceWithEntry( "Plant","TreatPrefix",TreatIDPrefix );
  
  // create product manager with prefix to maintain the products 
  m_pProductManager           = new CDM_HMDProductManager(TreatIDPrefix);

  initManager();

  return RetCode;
}


//##ModelId=45139A710331
 CDM_HMDTask* CDM_HMDTask::getInstance()
{
	if ( m_Instance == 0 )
	{
		m_Instance = new CDM_HMDTask( );
	}
	return m_Instance;
}

//##ModelId=45139A710339
 void CDM_HMDTask::registerEventHandlers()
{
	cCBS_StdEvent_Task* m_pEventTask = cCBS_StdEvent_Task::getInstance();

  // register event handler classes
  if (m_pEventTask)
  {
    CDM_EventHandler * EventHandler = 0;
    EventHandler = new CDM_HMDTreatmentManagementEventHandler();
    m_pEventTask->registerEventHandler(EventHandler);

    EventHandler = new CDM_HMDSignalsAndMeasurementsEventHandler();
    m_pEventTask->registerEventHandler(EventHandler);

    EventHandler = new CDM_HMDAnalysisEventHandler();
    m_pEventTask->registerEventHandler(EventHandler);

    EventHandler = new CDM_HMDMaterialEventHandler();
    m_pEventTask->registerEventHandler(EventHandler);

    EventHandler = new CDM_HMDModesAndAvailabilitiesEventHandler();
    m_pEventTask->registerEventHandler(EventHandler);

    EventHandler = new CDM_HMDPurposeEventHandler();
    m_pEventTask->registerEventHandler(EventHandler);

    EventHandler = new CDM_HMDModelResultEventHandler();
    m_pEventTask->registerEventHandler(EventHandler);

  }
}




//##ModelId=45139A710337
void CDM_HMDTask::registerEventLogHandlers()
{
  CDM_HMDEventLogHandler * pEventLogHandler;

  pEventLogHandler = new CDM_HMDEventLogHandlerAnalysis();
  registerEventLogHandler(pEventLogHandler);

  pEventLogHandler = new CDM_HMDEventLogHandlerMaterial();
  registerEventLogHandler(pEventLogHandler);

  pEventLogHandler = new CDM_HMDEventLogHandlerModelResults();
  registerEventLogHandler(pEventLogHandler);

  pEventLogHandler = new CDM_HMDEventLogHandlerModesAndAvailabilities();
  registerEventLogHandler(pEventLogHandler);

  pEventLogHandler = new CDM_HMDEventLogHandlerPurpose();
  registerEventLogHandler(pEventLogHandler);

  pEventLogHandler = new CDM_HMDEventLogHandlerSignalsAndMeasurements();
  registerEventLogHandler(pEventLogHandler);

}



//##ModelId=45139A710310
std::string CDM_HMDTask::getProcessState(const std::string& ID)
{
  std::stringstream RetValue;
  std::vector<std::string>::iterator it;

  // search Process state data for ID = Product ID
  if ( m_pProductManager && m_pProductManagementInterface )
  {
    std::string ProductID(ID);

    if ( m_pProductManager->findProduct(ProductID) )
    {
      // process state is characterized by the TotalMetAmount data
      seqGasData GasData = CIntfData::ToCORBAType(m_pProductManagementInterface->getGasData(ID.c_str(),DATA::TotalMetAmount));
      
      // order of output is given by the m_GasDataList
      for( it = m_GasDataList.begin() ; it != m_GasDataList.end() ; ++it)
      {
        // find GasData for each GasType
        for( long i = 0 ; i < CIntfData::getLength(GasData); ++i)
        {
          sGasData ActData;
          CIntfData::getAt(ActData,GasData,i);
          std::string GasType = ActData.GasType;

          // fill Return value
          if ( (*it) == GasType )
          {
            RetValue << ActData.GasValue << " ";
          }
        }
      } // for( it = m_GasDataList.begin() ; it != m_GasDataList.end() ; ++it)
    } // if ( m_pProductManager->findProduct(ProductID,HeatID,TreatID) )
  }

  return RetValue.str();
}

//##ModelId=45C9A46A0348
CDM_HMDTask* CDM_HMDTask::m_Instance = 0;

//##ModelId=45139A710313
void CDM_HMDTask::sendInitialEvents()
{
  CEventMessage Message;

  std::string PlantID = DEF_SUBSYSTEMS::HMD;
  std::vector<std::string> DestinationList;
  std::string SenderName;

  cCBS_StdInitBase::getInstance()->getEntry("Plant","PlantID",PlantID);
  
  std::string TaskName = "DM_Task";
  cCBS_StdInitBase::getInstance()->replaceWithEntry("TASKS","DM_Task",TaskName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"SenderName",SenderName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"DestinationName", DestinationList);

  std::vector<std::string> PlantList;
  std::vector<std::string>::iterator it;
  
  cCBS_StdInitBase::getInstance()->getEntryList("Plant","PlantID",PlantList);

  for ( it = PlantList.begin() ; it != PlantList.end(); it ++)
  { 
    Message.setPlantID( (*it) );
    Message.setMessage(HMD_EvMsg::evHMDPlantStatusRequest);
    Message.setPlantEvent(true);
    Message.dispatch(SenderName,DestinationList);
  }
}

