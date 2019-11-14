// Copyright (C) 2004, 2005 SMS Demag AG, Germany 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGC_PLANT_CONTAINER_43C65D5801D9_INCLUDED
#define _INC_CGC_PLANT_CONTAINER_43C65D5801D9_INCLUDED

#include <string>
#include <map>
#include <vector>

struct sPlantRoute
{
  std::string Plant;
  long        PlantNo;
};

class CGC_PLANT;
class cCBS_StdConnection;

//##ModelId=43C65D5801D9
class CGC_Plant_Container 
{
protected:
	//##ModelId=43C662C402B1
	CGC_PLANT* m_pGC_PLANT;

  //##ModelId=43C6699F00B6
	struct stPlantDef 
	{
	public:
	//CCS plant id from db
		//##ModelId=44896E7B0116
		std::string PlantId_CCS;

	//Plant name from db
		//##ModelId=43C669BB003E
		std::string Plant;

	//Plant number from db
		//##ModelId=43C669E300B3
		long PlantNo;

	//L1 plant id (long) from db
		//##ModelId=43C669ED014E
		long PlantId_L1;

	//L3 plant id from db
		//##ModelId=43C669FD015B
		std::string PlantId_l3;

	//Route code definition
		//##ModelId=43E8865B0012
		std::string RouteCode;
	};
public:
	//Returns CCS PlantID depends on L2 plant id definition.
	//##ModelId=448E865A014F
	std::string getCCSPlantID(std::string L2PlantId);

	//Returns L2 PlantID depends on CCS plant id definition. 
	//To do this Plant must be set before.
	//##ModelId=448974180080
	std::string getL2PlantIDFromCCS(std::string& CCSPlantId);

	//##ModelId=43E885F70221
  std::string getRouteCodeID(std::string L2PlantId);

  std::string getRouteCodeID(std::string& Plant, long PlantNo);

  std::string getL2RouteCodeID(std::string L3PlantId);


	//##ModelId=43C6774C016E
	void setPlant(const std::string& value);

	//Returns L2 PlantID depends on L3 plant id definition. 
	//To do this Plant must be set before.
	//##ModelId=43C65EA702A3
	std::string getL2PlantID(std::string& L3PlantId);

	//Returns L2 PlantID depends on L1 plant id definition.To 
	//do this the Plant must be set before.
	//##ModelId=43C65F060014
	std::string getL2PlantID(long L1PlantId);

	//Returns L2 PlantID depends on plant name and plant 
	//number.
	//##ModelId=43C6611F002A
	std::string getL2PlantID(std::string& Plant, long PlantNo);

	//Returns plant name depends on L2 plant id definition.
	//##ModelId=43C661C3003A
	std::string getPlant(std::string L2PlantId);

	//Returns plant number depends on L2 plant id definition.
	//##ModelId=43C661E10282
	long getPlantNo(std::string L2PlantId);

	//Returns L1 PlantID depends on L2 plant id definition.
	//##ModelId=43C6621D0293
	long getL1PlantID(std::string L2PlantId);

	//Returns L3 PlantID depends on L2 plant id definition.
	//##ModelId=43C662450023
	std::string getL3PlantID(std::string L2PlantId);

	//##ModelId=43C663440215
	CGC_Plant_Container(cCBS_StdConnection *Connection);

	//Set m_Plant during instantiation.
	//##ModelId=43C666240321
	CGC_Plant_Container(cCBS_StdConnection *Connection, std::string Plant);

	//##ModelId=43C663870276
	virtual ~CGC_Plant_Container();

  bool isRouteCode(const std::string &RouteCode);

  std::vector<sPlantRoute> getPlantRoute(const std::string &RouteCode);

private:

  sPlantRoute getSinglePlantRoute(const std::string &RouteCode);

	//##ModelId=43C7C97202DC
	bool init(cCBS_StdConnection* Connection);

	//Unit name
	//##ModelId=43C6754403AB
	std::string m_Plant;

	//Empty std::string for fast return
	//##ModelId=43C672F800C1
	std::string m_Empty;

	//Container that contains PlantID_L2 as first value and 
	//structure of plant names of L1, L3 and CCS , and unit 
	//name 
	//with unit number
	//##ModelId=43C666610211
	std::map<const std::string,stPlantDef> m_PlantMapList;

};

#endif /* _INC_CGC_PLANT_CONTAINER_43C65D5801D9_INCLUDED */
