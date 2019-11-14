#ifndef _INC_CDH_IN_Test_DataProvider_INCLUDED
#define _INC_CDH_IN_Test_DataProvider_INCLUDED

#include "CPP_HEAT_PLANT.h"
#include "CPP_HEAT.h"

#include <string>

class CDH_IN_Test_DataProvider
{
private:

 CPP_HEAT_PLANT* m_pPP_Heat_Plant;

 CPP_HEAT* m_pPP_Heat;
  
public:

 typedef struct DataRow  // pick some better name!! :D 
  {
    std::string HeatIdCust;
    std::string TreatIdCust;
    std::string HeatId;
    std::string TreatId;
    std::string Plant;
    int PlantNo;
    std::string ExpirationDate;
  } ;

  CDH_IN_Test_DataProvider();

  ~CDH_IN_Test_DataProvider();

  void Init(); 
  
  void RunSimulator();

  void WriteSettingsToDatabase(DataRow *DatabaseData);

  void SetData(DataRow *DatabaseData);
 
  //std::string Xml;
  //std::string Ici;
  //std::string Icnf;
  //std::string Szn;
  //std::string TestSystem;
  //void SetSzenarium(std::string Szenarium);
};

#endif //_INC_CDH_IN_Test_DataProvider_INCLUDED