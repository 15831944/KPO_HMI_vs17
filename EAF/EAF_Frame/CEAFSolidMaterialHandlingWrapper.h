// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFSOLIDMATERIALHANDLINGWRAPPER_4110E49E02A0_INCLUDED
#define _INC_CEAFSOLIDMATERIALHANDLINGWRAPPER_4110E49E02A0_INCLUDED

#include "CEAFModelWrapper.h"
#include "CSolidMaterialHandlingWrapper.h"

//##ModelId=4111209C0019
class CEAFSolidMaterialHandlingWrapper : public CSolidMaterialHandlingWrapper, public CEAFModelWrapper
  
{
public:
  //##ModelId=416CF2820285
  virtual bool doOnRecipeWeighingCompleteUpdate(CEventMessage& Event);

  //##ModelId=4152C08B01E1
  virtual bool doOnChangedMatSetPointsOperator( CEventMessage &Event );

  //##ModelId=4152C08E01AA
  virtual bool doOnDisableSourceRecipe( CEventMessage &Event );

  //##ModelId=4152C0900289
  virtual bool doOnEnableSourceRecipe( CEventMessage &Event );

  //##ModelId=4152C09402E9
  virtual bool doOnRecipeMaterialCharged( CEventMessage &Event );

  //##ModelId=4152C0970134
  virtual bool doOnRecipeMaterialDischarged( CEventMessage &Event );

  //##ModelId=4152C098037D
  virtual bool doOnRecipeWeighingComplete( CEventMessage &Event );

  //virtual bool readHopperImage (const std::string & HeatID, const std::string & TreatID);

};

#endif /* _INC_CEAFSOLIDMATERIALHANDLINGWRAPPER_4110E49E02A0_INCLUDED */
