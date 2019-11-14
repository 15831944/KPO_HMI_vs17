// Copyright (C) 2012 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLIQUIDMATERIALHANDLER_INCLUDED
#define _INC_CLIQUIDMATERIALHANDLER_INCLUDED

#include "iSMC_DataProvider_s.hh"
#include <string>
#include <map>

class CLiquidMaterialHander 
{
private:
  struct sLiquidMaterialInfo
  {
    double      Weight;
    double      Temperature;
    long        LadleNo;
    std::string LadleType;
    //seqAnalysis Analysis;
    std::map<std::string, double> Analysis;

    sLiquidMaterialInfo()
    {
      Weight      = 0.;
      Temperature = 0.;
      LadleNo     = DEF::Inv_Long;
      LadleType   = DEF::Inv_String;
    };
  };

  std::map<long, sLiquidMaterialInfo> LiquidMaterialContainer;

public:
  // return number of liquid additions
  long getCount();

  // insert new liquid addition
  void addLiquidMaterial(std::string& LadleType, long LadleNo, double Weight, double Temperature, seqAnalysis& Analysis);

  // return total weight over all liquid additions
  double getTotalWeight();

  // return mixed temperature over all liquid additions
  double getTemperature();

  // return mixed analysis over all liquid additions
  seqAnalysis getAnalysis();

};

#endif /* _INC_CLIQUIDMATERIALHANDLER_INCLUDED */
