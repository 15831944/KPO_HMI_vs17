// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_MATERIALHANDLINGWRAPPER_45D5906A0176_INCLUDED
#define _INC_CARCHIVER_MATERIALHANDLINGWRAPPER_45D5906A0176_INCLUDED

#include "CARCHIVER_Wrapper.h"

#include "CPD_HEAT_DATA.h"
#include "CHD_HEAT_DATA.h"
#include "CPD_HEAT_DATA_LIQADD.h"
#include "CPD_PRETREATDATA.h"
#include "CPD_LADLE.h"
#include "CGC_LADLE_DEF.h"
#include "CPD_RECIPE.h"
#include "CPD_RECIPE_ENTRY.h"
#include "CPD_MAT_AVAIL.h"
#include "CPP_HEAT.h"
#include "CPP_ORDER.h"
#include "CPP_HEAT_PLANT.h"
#include "CGT_MAT_PURP.h"
#include "CGC_Plantgroup_Container.h"
#include "CHeatStatusContainer.h"
#include "CGT_MAT.h"
#include "CGT_PARAM.h"
#include "CGT_PARAM_MATRIX.h"
#include "CPD_ACTION.h"
#include "CGC_HEAT_STATUS.h"
#include "CPD_PLANTSTATUS.h"
#include "CPD_HEAT_REF.h"
#include "CPD_PRETREATDATA.h"
#include "CPD_SCRAP_CONTAINER.h"
#include "CPD_SCRAP_CONTAINER_ENTRY.h"
#include "CPD_SCRAP_CONTAINER_ORDER.h"
#include "CPD_HOT_METAL.h"
#include "CPD_HOT_METAL_ORDER.h"

#include "CEventMessage.h"


//##ModelId=45D5906A0176
class CARCHIVER_MaterialHandlingWrapper 
	: public CARCHIVER_Wrapper
{
public:
	//##ModelId=45D5909A030F
	CARCHIVER_MaterialHandlingWrapper();

	//##ModelId=45D5909B0157
	virtual ~CARCHIVER_MaterialHandlingWrapper();

protected:
	//##ModelId=4745736A017D
	bool handleMaterialFeedingStart(CEventMessage& Event, seqGasData& SeqGasData, double ElecEgy = 0.0);

	//##ModelId=4745736D03A2
	bool handleMaterialFeedingStop(CEventMessage& Event, seqGasData& SeqGasData, double ElecEgy = 0.0);

	//##ModelId=4688C4F70022
	bool handleBasketDischargeStart(CEventMessage& Event, const std::string& BasketNo, seqGasData& SeqGasData, double ElecEgy = 0.0);

	//##ModelId=46714E6A00EA
	bool handleBasketDischarged(CEventMessage& Event, const std::string& BasketNo, seqGasData& SeqGasData, double ElecEgy = 0.0);

	//##ModelId=468234CB01CD
	bool handleHotMetalDischargeStart(CEventMessage& Event, const std::string& LadleType, long LadleNo, seqGasData& SeqGasData);

	//##ModelId=4682398003B5
	bool handleHotMetalDischarged(CEventMessage& Event, const std::string& LadleType, long LadleNo, seqGasData& SeqGasData);

	//##ModelId=46823A6203DD
	bool handleAddLiquidAddition(CEventMessage& Event, const std::string& LadleType, long LadleNo);

	//write recipes into PD_RECIPE and recipe content into 
	//PD_RECIPE_ENTRY
	//##ModelId=45F560B603AE
	bool handleMaterialHandlingReport(CEventMessage& Event, sMetTimeStamp &MetTimeStamp, long TreatmentPosition);

	// update min chargable weight in PD_MAT_AVAIL
	//##ModelId=462E0590034C
	//bool handleMinChargeableBinWeightUpdate(CEventMessage& Event, seqMaterials& SeqMaterials);

	// update/insert material weights in PD_MAT_AVAIL
	//##ModelId=462E05910040
	bool handleMaterialAvailability(CEventMessage& Event, seqMaterials& SeqMaterials, bool AllMat = false);

	// insert relation material<->purpose into GT_MAT_PURP if weight is > 0
	// delete relation material<->purpose from GT_MAT_PURP if weight is <= 0
	//##ModelId=462E0591016D
	bool handleUpdatePurpose(CEventMessage& Event, seqMaterials& SeqMaterials, bool AllMat = false);

	bool handleUpdateLiquidAddition(CEventMessage& Event, long LiqAddNo);

	bool handleLiqMatHandlingReport(CEventMessage& Event);

  bool handleMinChargeableBinWeightUpdate(CEventMessage& Event, seqMaterials& SeqMaterials);

	//##ModelId=474570640123
	CGC_HEAT_STATUS* m_pGC_HEAT_STATUS;

	//##ModelId=462E04AA03AE
	CGC_Plantgroup_Container* m_pGC_Plantgroup_Container;

	//##ModelId=474575260252
	CHeatStatusContainer* m_pHeatStatusContainer;

	//##ModelId=462E0435000B
	CPD_MAT_AVAIL* m_pPD_MAT_AVAIL;

	//##ModelId=462DDFE50095
	CGT_MAT* m_pGT_MAT;

	//##ModelId=462E04780046
	CGT_MAT_PURP* m_pGT_MAT_PURP;

	//##ModelId=47457A2B021C
	CGT_PARAM* m_pGT_PARAM;

	//##ModelId=47457A380191
	CGT_PARAM_MATRIX* m_pGT_PARAM_MATRIX;

	//##ModelId=45D5D1390026
	CPD_RECIPE* m_pPD_RECIPE;

	//##ModelId=45D5BA9701A3
	CPD_RECIPE_ENTRY* m_pPD_RECIPE_ENTRY;

	//##ModelId=468234A20038
	CPD_ACTION* m_pPD_ACTION;

	CPD_PLANTSTATUS* m_pPD_PLANTSTATUS;

	CPD_HEAT_REF* m_pPD_HEAT_REF;

	//##ModelId=45D5B93E028F
	long getHighestRecipeNo(const std::string& HeatID, const std::string& TreatID, const std::string& Plant, const std::string& RecipeName, long RecipeStatus, const std::string& RecipeSource);

	//##ModelId=45D5B2BA03AC
	CPD_PRETREATDATA* m_pPD_PRETREATDATA;

	//##ModelId=45D5AAD9006F
	CPD_HEAT_DATA_LIQADD* m_pPD_HEAT_DATA_LIQADD;

	//##ModelId=47457B4C0343
	CPD_HEAT_DATA* m_pPD_HEAT_DATA;

  CHD_HEAT_DATA* m_pHD_HEAT_DATA;

	//##ModelId=45D5A8F60196
	CPD_LADLE* m_pPD_LADLE;
	CGC_LADLE_DEF* m_pGC_LADLE_DEF;

	//##ModelId=47457AC900EF
	CPP_HEAT* m_pPP_HEAT;

	//##ModelId=47457ADD0075
	CPP_ORDER* m_pPP_ORDER;

	//##ModelId=47457B0701C5
	CPP_HEAT_PLANT* m_pPP_HEAT_PLANT;

  CPD_SCRAP_CONTAINER* m_pPD_SCRAP_CONTAINER;

  CPD_SCRAP_CONTAINER_ENTRY* m_pPD_SCRAP_CONTAINER_ENTRY;

  CPD_SCRAP_CONTAINER_ORDER* m_pPD_SCRAP_CONTAINER_ORDER;

  CPD_HOT_METAL* m_pPD_HOT_METAL;

  CPD_HOT_METAL_ORDER* m_pPD_HOT_METAL_ORDER;

  cCBS_ODBC_DBError m_lastError;


	//##ModelId=45D590B50023
	virtual void initDBClasses();

	//##ModelId=45D590B5027D
	virtual void deleteDBClasses();

};

#endif /* _INC_CARCHIVER_MATERIALHANDLINGWRAPPER_45D5906A0176_INCLUDED */
