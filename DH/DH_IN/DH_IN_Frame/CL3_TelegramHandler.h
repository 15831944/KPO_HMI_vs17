// Copyright (C) 2012 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CL3_TELEGRAMHANDLER_4582CCB901FD_INCLUDED
#define _INC_CL3_TELEGRAMHANDLER_4582CCB901FD_INCLUDED

#include <string>
#include "CTelegram_Handler.h"
#include "CDH_EventHandler.h"

//class CGC_Recipe_L1Container;
//class CGC_SourceContainer;
//class CGC_Charge_Dest_Container;
class CGT_MAT;
class CGT_MAT_CHEM;
//class CGT_MAT_PURP;
//class CPD_MAT_AVAIL;
//class CPD_ACTION;
//class CPDE_HEAT_DATA_INJ;
//class CPDE_HEAT_DATA_LANCE;
//class CPD_COOLWATER;
//class CGTE_PP_FLAME_PROFILE;
//class CPD_HEAT_DATA_STIRR;
//class CPDE_HEAT_DATA_MELT;
//class CGT_MAT;
//class CPDC_BASKET_HEAT;
//class CPDC_BASKET_ENTRY_HEAT;
//class CPDC_BASKET_PHYS;
//class CPDC_BASKET_ENTRY_PHYS;
class CPP_ORDER;
class CPP_ORDER_SINGLE_AIMS;
class CPP_HEAT;
class CPD_RECIPE;
//class CPD_RECIPE_ENTRY;
class CPDE_HEAT_DATA;
class CPD_HEAT_DATA;
class CPP_HEAT_PLANT;
class CGT_DELAY_CODE;
class CGT_GRADE;
class CGT_GRADE_ANL;
class CGT_GRADE_SINGLE_AIMS;
class CGT_GRADE_PRODPRAC;
class CGT_PURP;
class CGT_MAT_PURP;
class CPD_HEAT_PLANT_REF;
class CPP_HM;
class CGC_LADLE_DEF;
class CPD_LADLE;
class CPD_LADLE_LIFE_DATA;
class CPDH_HM_DATA;

class CL3_TelegramHandler 
: public CTelegram_Handler
{
private:

  void getSteelAnalysisStream(DEF::seqString& SteelAnalysisDB);
  void getSlagAnalysisStream(DEF::seqString& SlagAnalysisDB);
  void WriteDataInto_GT_GRADE_ANL(std::string &SteelGradeCode,std::string &Plant,CORBA::Any &anyElement,std::string &AimType,long Update_flag);
  bool WriteDataInto_GT_GRADE_ANL_Sub(std::string &SteelGradeCode, std::string &PLANT, std::string &ENAME, double ANL, std::string &AimType, long Update_flag);

  void WriteDataInto_GT_MAT_CHEM(std::string &MatCode,CORBA::Any &anySteelElements,CORBA::Any &anySlagCompounds,long Update_flag);
  bool WriteDataInto_GT_MAT_CHEM_Sub(std::string &MatCode,std::string &ENAME, double VAL,long Update_flag);


  CDateTime FromTelegramFormat14(std::string strDateTime);

  cCBS_ODBC_DBError m_lastError;

  typedef struct {
    std::string ElementName;
    long ElementAim;
    long ElementMin;
    long ElementMax;
  } L3Analysis;


  typedef struct {
    long ActionFlag;
    std::string ProdOrderNo;
    std::string SteelGradeCode;
    long SteelWeight_EAF;
    long SteelWeight_CCS;
    long CastingLength;
    long ProductWidth;
    long ProductThickness;
  } L3OrderData;

  typedef struct {
    long ActionFlag;
    std::string HeatId;
    std::string ProdOrderNo;
    std::string RouteCode;
    long CasterSeqNo;
    long HeatSeqNo;
    std::string Plant;
    long PlantNo;
    long TreatmentSeq;
    std::string StartTime;
    std::string EndTime;
  } L3HeatScheduleData;



  void SendEventMessage(const std::string& Key, 
                        const std::string& TlgName,
                        const std::string& DataKey,
                        const std::string& PlantId,
                        const std::string& HeatNo,
                        const std::string& TreatId,
                        const std::string& OrderID,
                        bool isPlantEvent);


  bool DoProcessSteelGradeCodeDefinition(const std::string& Key, const std::string& TlgName);
  
  
  bool DoProcessHeatSchedule(const std::string& Key, const std::string& TlgName);

  bool DoProcessMaterialCodeDefinition(const std::string& Key, const std::string& TlgName);
  bool DoProcessDelayCodeDefinition(const std::string& Key, const std::string& TlgName);
  bool DoProcessHMLadle(const std::string& Key, const std::string& TlgName);
  bool DoProcessTeemingLadle(const std::string& Key, const std::string& TlgName);

  bool DoProcessSteelGradeChange(const std::string& Key, const std::string& TlgName);
  bool DoProcessLadleChange(const std::string& Key, const std::string& TlgName);

  bool DoProcessSteelAnalysis(const std::string& Key, const std::string& TlgName);
  bool DoProcessSlagAnalysis(const std::string& Key, const std::string& TlgName);

  seqAnalysis handleGradeAnalysis(const std::string& Key, const std::string& AnalysisPrefix,const std::string& Type);

  std::map<long,std::pair<std::string,double> > m_SteelElementMap; //contains the mapping from element number to element name as in definition 
  std::map<long,std::pair<std::string,double> > m_SlagElementMap; //slag elements as in definition plus conversion factor


public:

  static const long Update;
  static const long New   ;
  static const long Delete;

  CL3_TelegramHandler();

	virtual ~CL3_TelegramHandler();


	virtual bool doOnComplete(const std::string& Key, const std::string& TlgName);

  /************************************************************************/
  /*Add by Zhu Xinhong  */
  //CGC_Recipe_L1Container* m_pGC_Recipe_L1Container;

  //CGC_SourceContainer*   m_pGC_Source;

  //CGC_Charge_Dest_Container* m_pGC_Charge_Dest;

  CGT_MAT* m_pGT_MAT;
  CGT_MAT_CHEM* m_pGT_MAT_CHEM;

  //CGT_MAT_PURP* m_pGT_MAT_PURP;

  //CPD_MAT_AVAIL* m_pPD_MAT_AVAIL;

  //CPD_ACTION* m_pPD_ACTION;

  //CPDE_HEAT_DATA_INJ* m_pPDE_HEAT_DATA_INJ;
  //CPDE_HEAT_DATA_LANCE* m_pPDE_HEAT_DATA_LANCE; 
  //CPD_COOLWATER* m_pPD_COOLWATER;
  //CGTE_PP_FLAME_PROFILE* m_pGTE_PP_FLAME_PROFILE;
  //CPD_HEAT_DATA_STIRR* m_pPD_HEAT_DATA_STIRR;
  //CPDE_HEAT_DATA_MELT* m_pPDE_HEAT_DATA_Melt;
  //CPDC_ASKET_HEAT* m_pPDC_Bakset_Heat;
  //CPDC_BASKET_ENTRY_HEAT* m_pPDC_BASKET_ENTRY_HEAT;
  //CPDC_BASKET_PHYS* m_pPDC_BASKET_PHYS;
  //CPDC_BASKET_ENTRY_PHYS* m_pPDC_BASKET_ENTRY_PHYS;
  CPP_ORDER* m_pPP_ORDER;
  CPP_ORDER_SINGLE_AIMS* m_pPP_ORDER_SINGLE_AIMS;
  CPP_HEAT* m_pPP_HEAT;
  CPP_HEAT_PLANT* m_pPP_HEAT_PLANT;
  CPD_RECIPE* m_pPD_RECIPE;
  //CPD_RECIPE_ENTRY* m_pPD_RECIPE_entry;
  CPDE_HEAT_DATA* m_pPDE_HEAT_DATA;
  CPD_HEAT_DATA* m_pPD_HEAT_DATA;
  CGT_DELAY_CODE* m_pGT_DELAY_CODE;
  CGT_GRADE* m_pGT_GRADE;
  CGT_GRADE_ANL* m_pGT_GRADE_ANL; 
  CGT_GRADE_SINGLE_AIMS* m_pGT_GRADE_SINGLE_AIMS;
  CGT_GRADE_PRODPRAC* m_pGT_GRADE_PRODPRAC;
  CGT_GRADE_SAMPLE_FLAG* m_pGT_GRADE_SAMPLE_FLAG;
  CPD_HEAT_REF* m_pPD_HEAT_REF;
  CHeatStatusContainer* m_pHeatStatusContainer;
  CGT_PURP* m_pGT_PURP;
  CGT_MAT_PURP* m_pGT_MAT_PURP;
  CPP_HM* m_pPP_HM;
	CPD_LADLE* m_pPD_LADLE;
	CPD_LADLE_LIFE_DATA* m_pPD_LADLE_LIFE_DATA;


  CGC_LADLE_DEF* m_pGC_LADLE_DEF;

  CPD_HEAT_PLANT_REF* m_pPD_HEAT_PLANT_REF;
	CPDH_HM_DATA* m_pPDH_HM_DATA;

  /************************************************************************/
};

#endif /* _INC_CL3_TELEGRAMHANDLER_4582CCB901FD_INCLUDED */
