// Copyright (C) 2004 SMS Demag AG, Germany 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMC_DBSteelGrade_41D930570288_INCLUDED
#define _INC_CSMC_DBSteelGrade_41D930570288_INCLUDED

#include <string>
#include "CSMC_DBTableBase.h"

class CPD_HEAT_DATA;
class CGT_GRADE;
class CGT_GRADE_ANL;
class CHD_GRADE;
class CHD_GRADE_ANL;


// **
//##ModelId=41D930570288
class CSMC_DBSteelGrade : public CSMC_DBTableBase
{
private:
  CPD_HEAT_DATA* m_pHeatDataProduction;
  CGT_GRADE* m_pSteelGradePlanned;
  CGT_GRADE_ANL* m_pSteelGradeAnalysisPlanned;
  CHD_GRADE* m_pSteelGradeAct;
  CHD_GRADE_ANL* m_pSteelGradeAnalysisAct;


public:
	//##ModelId=41D9305A037D
	CSMC_DBSteelGrade(cCBS_Connection* Connection);

	//##ModelId=41D9305C0004
	~CSMC_DBSteelGrade();

	//##ModelId=41D9305C0203
	bool selectSteelGrade(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT);
	bool selectSteelGradeAnalysis(const std::string& HEATID, const std::string& TREATID ,const std::string& STEELGRADECODE,const std::string& PLANT, const std::string& ENAME, const std::string& AIMTYPE);

  bool copySteelGrade(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT);
  bool updateSteelGrade(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT);

  bool copySteelGradeAnalysis(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const std::string& ENAME, const std::string& AIMTYPE);
  bool updateSteelGradeAnalysis(const std::string& HEATID, const std::string& TREATID,const std::string& STEELGRADECODE, const std::string& PLANT, const std::string& ENAME, const std::string& AIMTYPE);

	//##ModelId=41D9305D0146
	std::string getSTEELGRADECODE(long Row);

	//##ModelId=41D9305E0007
	void setSTEELGRADECODE(const std::string& value);

	//##ModelId=44FEA5D302E3
	bool deleteSteelGrade(const std::string& Grade);

	std::string getPLANT(long Row);
	void setPLANT(const std::string& value);

	std::string getHEATID(long Row);
	void setHEATID(const std::string& value);
	std::string getTREATID(long Row);
	void setTREATID(const std::string& value);


	std::string getSTEELGRADECODEDESC(long Row);

	void setSTEELGRADECODEDESC(const std::string& value);
	std::string getSTEELGRADECODEDESC_C(long Row);
	void setSTEELGRADECODEDESC_C(const std::string& value);
	double getLiqTemp(long Row);
	void setLiqTemp(double value);
	CDateTime getREVTIME(long Row);
	void setREVTIME(const CDateTime& value);
	std::string getHOTMETALCOMPOSITION(long Row);
	void setHOTMETALCOMPOSITION(const std::string& value);
	std::string getUSERCODE(long Row);
	void setUSERCODE(const std::string& value);

  double getANL(long Row);
	void setANL(double value);
	string getENAME(long Row);
	void setENAME(const std::string& value);
	string getAIMTYPE(long Row);
	void setAIMTYPE(const std::string& value);



};

#endif /* _INC_CSMC_DBSteelGrade_41D930570288_INCLUDED */
