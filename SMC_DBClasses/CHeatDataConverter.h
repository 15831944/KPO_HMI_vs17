// Copyright (C) 2004, 2005 SMS Demag AG, Germany 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHEATDATACONVERTER_4410338B0046_INCLUDED
#define _INC_CHEATDATACONVERTER_4410338B0046_INCLUDED

class CPD_HEAT_PLANT_REF;
class CPD_HEAT_DATA;

//Instance of this class converts HeatID and TreatID between 
//internal and external presentation
//##ModelId=4410338B0046
class CHeatDataConverter 
{
public:
  //##ModelId=441037CD01E6
  CHeatDataConverter(cCBS_StdConnection* Connection);

  //##ModelId=441037CE004E
  virtual ~CHeatDataConverter();

  //##ModelId=441038100295
  bool getInternalHeatData(std::string& CustHeatID, std::string& CustTreatID, std::string& HeatID, std::string& TreatID, std::string Plant);
  bool getInternalHeatDataByCustHeatID(std::string& CustHeatID, std::string& HeatID, std::string& TreatID, std::string Plant);

  //##ModelId=44103829019C
  bool getCustHeatData(std::string& HeatID, std::string& TreatID, std::string& CustHeatID, std::string& CustTreatID, std::string Plant);

  bool getHeatPlantNo( const std::string HeatID, const std::string TreatID, const std::string Plant,long& lngPlantNo );

  //L2CustTreatId's lenth is 3, for example A01,L01,E01.This function Remove first letter in L2CustTreatId, A01->01 ,L01->01,E01->01
  std::string  L2CustTreatIdToL1CustTreatId(std::string& L2CustTreatId);

  //LF 01->L01, EAF 01->E01, AOD 01->A01
  std::string  L1CustTreatIdToL2CustTreatId(std::string& Plant ,std::string& L1CustTreatId);

private:
  //##ModelId=441042480118
  std::string m_Plant;

  //##ModelId=44103BD7000C
  std::string m_InternalHeatID;

  //##ModelId=44103BED027E
  std::string m_InternalTreatID;

  //##ModelId=44103C1B0104
  std::string m_CustHeatID;

  //##ModelId=44103C320074
  std::string m_CustTreatID;

  CPD_HEAT_PLANT_REF* m_pPD_HEAT_PLANT_REF;

  CPD_HEAT_DATA* m_pPD_HEAT_DATA;

  std::map<std::string,std::string> m_PlantTreatIDPrefixTrans;

};

#endif /* _INC_CHEATDATACONVERTER_4410338B0046_INCLUDED */
