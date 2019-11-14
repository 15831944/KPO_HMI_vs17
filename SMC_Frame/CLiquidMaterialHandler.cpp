// Copyright (C) 2012 SMS Siemag AG

#include "CIntfData.h"
#include "CLiquidMaterialHander.h"

// insert new liquid addition
void CLiquidMaterialHander::addLiquidMaterial(std::string& LadleType, long LadleNo, double Weight, double Temperature, seqAnalysis& Analysis)
{
  sLiquidMaterialInfo Material;

  if ( Weight < 0. || Weight == DEF::Inv_Double )
  {
    Weight = 0.;
  }
  if ( Temperature < 0. || Temperature == DEF::Inv_Double )
  {
    Temperature = 0.;
  }
  Material.Weight       = Weight;
  Material.Temperature  = Temperature;
  Material.LadleNo      = LadleNo;
  Material.LadleType    = LadleType;

  sAnalysis AnalysisDetail;
  long seqLenght =  CIntfData::getLength(Analysis);
  for ( long i = 0; i < seqLenght; i++ )
  {
    CIntfData::getAt(AnalysisDetail,Analysis,i);
    std::string Element = AnalysisDetail.Element;
    Material.Analysis.insert(std::pair<std::string,double>(Element,AnalysisDetail.Concentration));
  }

  long LiqNo = LiquidMaterialContainer.size();
  LiquidMaterialContainer.insert(std::pair<long,sLiquidMaterialInfo>(LiqNo+1,Material));
}

// return total weight over all liquid additions
double CLiquidMaterialHander::getTotalWeight()
{
  double RetValue   = DEF::Inv_Double;
  double TotalWeight = 0.;
  std::map<long, sLiquidMaterialInfo>::iterator it;

  for ( it = LiquidMaterialContainer.begin(); it != LiquidMaterialContainer.end(); ++it )
  {
    if ( it->second.Weight > 0. && it->second.Weight != DEF::Inv_Double )
    {
      TotalWeight += it->second.Weight;
    }
  }

  if ( TotalWeight > 0. )
  {
    RetValue = TotalWeight;
  }

  return RetValue;
}

// return mixed temperature over all liquid additions
double CLiquidMaterialHander::getTemperature()
{
  double Temp = DEF::Inv_Double;
  std::map<long, sLiquidMaterialInfo>::iterator it;

  double TotWeight = getTotalWeight();
  double TG = 0.;

  if ( TotWeight > 0. && TotWeight != DEF::Inv_Double )
  {
    for ( it = LiquidMaterialContainer.begin(); it != LiquidMaterialContainer.end(); ++it )
    {
      TG += ( it->second.Weight * it->second.Temperature );
    }

    if ( TG > 0. )
      Temp = TG / TotWeight;
  }

  return Temp;
}

// return mixed analysis over all liquid additions
seqAnalysis CLiquidMaterialHander::getAnalysis()
{
  seqAnalysis RetAnalysis;
  std::map<std::string, double> MixedAnalysis;
  std::map<std::string, double>::iterator mixed_it;
  std::map<long, sLiquidMaterialInfo>::const_iterator it;
  std::map<std::string, double>::const_iterator elems_it;

  double TotalWeight = getTotalWeight();
  if ( TotalWeight <= 0 || TotalWeight == DEF::Inv_Double )
  {
    return RetAnalysis;
  }

  // Iterate over all additions and fill temporary 
  // all existing chemical elements with 0.
  for ( it = LiquidMaterialContainer.begin(); it != LiquidMaterialContainer.end(); ++it )
  {
    for ( elems_it = it->second.Analysis.begin(); elems_it != it->second.Analysis.end(); ++elems_it )
    {
      if ( MixedAnalysis.end() == MixedAnalysis.find(elems_it->first) )
      {
        MixedAnalysis.insert(std::pair<std::string,double>(elems_it->first,0.));
      }
    }
  }

  // Calculation the summ of the same element
  // and devide by total weight
  for ( mixed_it = MixedAnalysis.begin(); mixed_it != MixedAnalysis.end(); ++mixed_it )
  {
    for ( it = LiquidMaterialContainer.begin(); it != LiquidMaterialContainer.end(); ++it )
    {
      double LiquidAddWeight = it->second.Weight;
      for ( elems_it = it->second.Analysis.begin(); elems_it != it->second.Analysis.end(); ++elems_it )
      {
        if ( mixed_it->first == elems_it->first )
        {
          mixed_it->second += (elems_it->second / 100.) * LiquidAddWeight;
        }
      }
    }

    mixed_it->second = (mixed_it->second / TotalWeight) * 100;
  }


  // fill seqAnalysis with mixed analysis
  sAnalysis MixedAnlElem;
  mixed_it = MixedAnalysis.begin();
  while ( mixed_it != MixedAnalysis.end() )
  {
    MixedAnlElem.Element = mixed_it->first.c_str();
    MixedAnlElem.Concentration = mixed_it->second;

    CIntfData::insert(RetAnalysis, MixedAnlElem);
    ++mixed_it;
  }

  return RetAnalysis;
}

// return number of liquid additions
long CLiquidMaterialHander::getCount()
{
  return LiquidMaterialContainer.size();
}
