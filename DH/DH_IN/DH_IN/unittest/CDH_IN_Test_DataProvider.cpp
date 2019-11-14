#include "CDH_IN_Test_DataProvider.h"
#include "cCBS_StdInitBase.h"
#include "CDH_IN_Test_Task.h"


CDH_IN_Test_DataProvider::CDH_IN_Test_DataProvider()
:m_pPP_Heat_Plant(0)
,m_pPP_Heat(0)
{
  m_pPP_Heat       = new CPP_HEAT(CDH_IN_Test_Task::getInstance()->getConnection()); 
  m_pPP_Heat_Plant = new CPP_HEAT_PLANT(CDH_IN_Test_Task::getInstance()->getConnection()); 
}
  
CDH_IN_Test_DataProvider::~CDH_IN_Test_DataProvider()
{
  if (m_pPP_Heat)       {delete m_pPP_Heat; m_pPP_Heat = 0;}
  if (m_pPP_Heat_Plant) {delete m_pPP_Heat_Plant; m_pPP_Heat_Plant = 0;}
}

void CDH_IN_Test_DataProvider::Init()
{
  //std::string SimulatorArguments = "SimulatorArguments";
  //Xml = "Telcom_In.xml";
  //Ici = "Connection_RH.ici";
  //Icnf = "Telcom_In.icnf";
  //cCBS_StdInitBase::getInstance()->replaceWithEntry(SimulatorArguments, "Xml", Xml);
  //cCBS_StdInitBase::getInstance()->replaceWithEntry(SimulatorArguments, "Icnf", Icnf);
  //cCBS_StdInitBase::getInstance()->replaceWithEntry(SimulatorArguments, "Ici", Ici);
  //cCBS_StdInitBase::getInstance()->replaceWithEntry(SimulatorArguments, "TestSystem", TestSystem);
}

void CDH_IN_Test_DataProvider::RunSimulator()
{
  // run test
  //system(TestSystem.c_str());
}

//void CDH_IN_Test_DataProvider::SetSzenarium(std::string Szenarium)
//{
//  Szn = Szenarium;
//}

void CDH_IN_Test_DataProvider::WriteSettingsToDatabase(DataRow * DatabaseData)
{
  std::cout<< "Writing into database...";

  m_pPP_Heat->setHEATID_CUST("16011");
  m_pPP_Heat->setROUTECODEPLAN("2131");
  m_pPP_Heat->setPRODORDERID("123456");
  m_pPP_Heat->setUSERCODE("ADM");
  m_pPP_Heat->setHEATSTATORDER(0);

  if (m_pPP_Heat->select("16011"))
    m_pPP_Heat->update();
  else
    m_pPP_Heat->insert();
 
  m_pPP_Heat->commit();
  
  if (m_pPP_Heat->select("16011"))
  {
    // set test data in data base first
    if (m_pPP_Heat_Plant)
    {
      CDateTime now;
      m_pPP_Heat_Plant->setHEATID_CUST(m_pPP_Heat->getHEATID_CUST(1));
      m_pPP_Heat_Plant->setTREATID_CUST(DatabaseData->TreatIdCust);
      m_pPP_Heat_Plant->setHEATID(DatabaseData->HeatId);
      m_pPP_Heat_Plant->setTREATID(DatabaseData->TreatId);
      m_pPP_Heat_Plant->setPLANT(DatabaseData->Plant);
      m_pPP_Heat_Plant->setPLANTNO(DatabaseData->PlantNo);
      m_pPP_Heat_Plant->setPLANTREATSTART(now);
      m_pPP_Heat_Plant->setPLANTREATEND(now);
      m_pPP_Heat_Plant->setString("EXPIRATIONDATE","VALID");

      if (m_pPP_Heat_Plant->select(DatabaseData->HeatId,DatabaseData->TreatId,DatabaseData->Plant))
        m_pPP_Heat_Plant->update();
      else
        m_pPP_Heat_Plant->insert();
      m_pPP_Heat_Plant->commit(); 
    }
  }
}

void CDH_IN_Test_DataProvider::SetData(DataRow *DatabaseData)
{
  //std::cout<< "Setting test data to be written in to database...";
  //DatabaseData->TreatIdCust="1";
  //DatabaseData->HeatId="0000066";
  //DatabaseData->TreatId="015";
  //DatabaseData->PlantNo=1;
  //DatabaseData->Plant="RH";
  //DatabaseData->ExpirationDate = "2006-11-06 16:13:48,851";
  //DatabaseData->ExpirationDate = "VALID";
}
