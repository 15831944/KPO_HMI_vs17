#include <sstream>
#include <ctime>

#include "reemodel.h"

using namespace std;

string WriteReeInput( const ReeInput& HMDInput, const string& filename)
{
	time_t rawtime;
	struct tm *timeinfo;
	time ( &rawtime );
	timeinfo = localtime( &rawtime );

	string timeString(asctime(timeinfo));
	timeString = timeString.substr( 0, timeString.length() - 1); // strip '/n'

	ostringstream os;//( filename.c_str());

	os << endl << endl << endl << endl;
	os << "<START HMD model data --  " << filename << "  ------------------------------------------------------->" << endl;
	os << "<ReeInput 1.0>" << endl;
	os << "<filename: " << filename.c_str() << ">" << endl;
	os << "<created: " << timeString.c_str() << ">" << endl;

	os << "dPrevAdd";
	for( long a=0; a<3; ++a)
		os << "\t" << HMDInput.dPrevAdd[a];
	os << endl;

	os << "dAvgDur\t" << HMDInput.dAvgDur << endl;

	//typedef struct _StartConditionsTyp{
	//  float dAmt_iron;	
	//  float dAmt_slag;
	//  float dAim_sulphur;
	//  float dFreeboard;//PDH_HEAT_DATA.LADLE_FREEBOARD (wenn undefiniert oder 0: aus _BF)
	//  float dTemp_iron;
	//  float dCont_sulphur;
	//  int    bAvail_carbide;
	//  int    bAvail_lime;
	//  int    bAvail_mg;
	//  float dTimeAvail;
	//  float dAmt_soda;
	//  int   bPriceOptimum;
	//}StartConditionsTyp;

	const StartConditionsTyp& StartConditions = HMDInput.Strt;
	os << "Strt.bPriceOptimum\t" << StartConditions.bPriceOptimum << endl;
	os << "Strt.dFreeboard\t" << StartConditions.dFreeboard << endl;
	os << "Strt.dAmt_soda\t" << StartConditions.dAmt_soda << endl;
	os << "Strt.dTimeAvail\t" << StartConditions.dTimeAvail << endl;


	os << "Strt.bAvail_carbide\t" << StartConditions.bAvail_carbide << endl;
	os << "Strt.bAvail_lime\t" << StartConditions.bAvail_lime << endl;
	os << "Strt.bAvail_mg\t" << StartConditions.bAvail_mg << endl;

	os << "Strt.dAmt_iron\t" << StartConditions.dAmt_iron << endl;
	os << "Strt.dAmt_slag\t" << StartConditions.dAmt_slag << endl;
	os << "Strt.dTemp_iron\t" << StartConditions.dTemp_iron << endl;

	os << "Strt.dCont_sulphur\t" << StartConditions.dCont_sulphur << endl;
	os << "Strt.dAim_sulphur\t" << StartConditions.dAim_sulphur << endl;

	//typedef struct _BaseValueTableTyp{// HDH_PP_BASE_VAL (_STEP)
	//	float  BlowingRelation; //HDH_PP_BASE_VAL
	//	float	MgContent;//HDH_PP_BASE_VAL
	//	float	CaC2Content;//HDH_PP_BASE_VAL
	//	float	Mg[BVT_ROWS][BVT_COLUMNS];//HDH_PP_BASE_VAL_STEP
	//	float  SStart[BVT_ROWS];//HDH_PP_BASE_VAL_STEP
	//	float  SFinal[BVT_COLUMNS];//HDH_PP_BASE_VAL
	//}BaseValueTableTyp;
	const BaseValueTableTyp& BaseValueTable = HMDInput.Bvt;

	os << "Bvt.BlowingRelation\t" << BaseValueTable.BlowingRelation << endl;
	os << "Bvt.MgContent\t" << BaseValueTable.MgContent << endl;
	os << "Bvt.CaC2Content\t" << BaseValueTable.CaC2Content << endl;
	os << "Bvt.SFinal";
	for( long a=0; a<5; ++a)
		os << "\t" << BaseValueTable.SFinal[a];
	os << endl;

	os << "iBVT_ROWS\t" << HMDInput.iBVT_ROWS << endl;

	long BVT_ROWS = HMDInput.iBVT_ROWS;

	for( long s=1; s<=BVT_ROWS; ++s)
	{
		os << "Bvt.Mg[" << s-1 << "]";
		for( long a=0; a<5; ++a)
			os << "\t" << BaseValueTable.Mg[s-1][a];
		os << endl;
	}

	os << "Bvt.SStart";
	for( long s=1; s<=BVT_ROWS; ++s)
		os << "\t" << BaseValueTable.SStart[s-1];
	os << endl;

	//typedef struct _FreeboardTyp{
	//  float Fbrd[2];//HDH_PP_PARA.MGFREEB_RATE_FREEB_1 _2
	//  float MgRate[2];//HDH_PP_PARA.MGFREEB_RATE_
	//}FreeboardTyp;
	// typedef struct _CarbCorrSlagTyp{//HDH_PP_PARA.CORR_MONO1... 
	//	float Slag[4];
	//	float Corr[4];
	//   }CarbCorrSlagTyp;
	// typedef struct _CarbMono3Typ{//HDH_PP_PARA.CALC_MONO2...
	//	float Mg[5];
	//	float Carbide[5];
	//}CarbMono3Typ;
	// typedef struct _SlagDurTyp{//HDH_PP_PARA.DESL_RELATION_SLAG_WGT... und ...RELATION_DESL_DUR...
	//	float Slag[5];
	//	float Duration[5];
	//}SlagDurTyp;
	//typedef struct _MonoCorrTyp{ //HDH_PP_PARA.CORR_FACT_MONO_LIME_S_END ...MONO_LIME_CORR
	//	float dSend[4];
	//	float dCorr[4];
	//}MonoCorrTyp;

	const FreeboardTyp& Freeboard = HMDInput.Freebd;
	const CarbCorrSlagTyp& CarbCorrSlag = HMDInput.CCorrSlag;
	const CarbMono3Typ& CarbMono3 = HMDInput.CMono3;
	const SlagDurTyp& SlagDur = HMDInput.SlgDur;
	const MonoCorrTyp& MonoCorrLime = HMDInput.MonoCorrLime;
	const MonoCorrTyp& MonoCorrCarbide = HMDInput.MonoCorrCarbide;

	os << "dCorrmono\t" << HMDInput.dCorrmono << endl;

	os << "Freebd.Fbrd\t" << Freeboard.Fbrd[ 0] << "\t" << Freeboard.Fbrd[ 1] << endl;
	os << "Freebd.MgRate\t" << Freeboard.MgRate[ 0] << "\t" << Freeboard.MgRate[ 1] << endl;

	os << "CCorrSlag.Slag\t" << CarbCorrSlag.Slag[ 0] << "\t"  << CarbCorrSlag.Slag[ 1] << "\t"  << CarbCorrSlag.Slag[ 2] << "\t"  << CarbCorrSlag.Slag[ 3] << endl;
	os << "CCorrSlag.Corr\t" << CarbCorrSlag.Corr[ 0] << "\t"  << CarbCorrSlag.Corr[ 1] << "\t"  << CarbCorrSlag.Corr[ 2] << "\t"  << CarbCorrSlag.Corr[ 3] << endl;

	os << "CMono3.Mg\t" << CarbMono3.Mg[ 0] << "\t"  << CarbMono3.Mg[ 1] << "\t"  << CarbMono3.Mg[ 2] << "\t"  << CarbMono3.Mg[ 3] << "\t" << CarbMono3.Mg[ 4] << endl;
	os << "CMono3.Carbide\t" << CarbMono3.Carbide[ 0] << "\t"  << CarbMono3.Carbide[ 1] << "\t"  << CarbMono3.Carbide[ 2] << "\t"  << CarbMono3.Carbide[ 3] << "\t" << CarbMono3.Carbide[ 4] << endl;

	os << "SlgDur.Slag\t" << SlagDur.Slag[ 0] << "\t"  << SlagDur.Slag[ 1] << "\t"  << SlagDur.Slag[ 2] << "\t"  << SlagDur.Slag[ 3] << "\t" << SlagDur.Slag[ 4] << endl;
	os << "SlgDur.Duration\t" << SlagDur.Duration[ 0] << "\t"  << SlagDur.Duration[ 1] << "\t"  << SlagDur.Duration[ 2] << "\t"  << SlagDur.Duration[ 3] << "\t" << SlagDur.Duration[ 4] << endl;

	os << "MonoCorrLime.dSend\t" << MonoCorrLime.dSend[ 0] << "\t"  << MonoCorrLime.dSend[ 1] << "\t"  << MonoCorrLime.dSend[ 2] << "\t"  << MonoCorrLime.dSend[ 3] << endl;
	os << "MonoCorrLime.dCorr\t" << MonoCorrLime.dCorr[ 0] << "\t"  << MonoCorrLime.dCorr[ 1] << "\t"  << MonoCorrLime.dCorr[ 2] << "\t"  << MonoCorrLime.dCorr[ 3] << endl;

	os << "MonoCorrCarbide.dSend\t" << MonoCorrCarbide.dSend[ 0] << "\t"  << MonoCorrCarbide.dSend[ 1] << "\t"  << MonoCorrCarbide.dSend[ 2] << "\t"  << MonoCorrCarbide.dSend[ 3] << endl;
	os << "MonoCorrCarbide.dCorr\t" << MonoCorrCarbide.dCorr[ 0] << "\t"  << MonoCorrCarbide.dCorr[ 1] << "\t"  << MonoCorrCarbide.dCorr[ 2] << "\t"  << MonoCorrCarbide.dCorr[ 3] << endl;


	//typedef struct _MaterialTyp{//GT_MAT
	//	float TempCoeff;//aus ENTHALPY and SPEC_HEAT
	//	float Price;// PRICE
	//	float MgEqui;//MG_EQUIVALENT
	//	float CaOCont;//GT_MAT_CHEM
	//	float CaC2Cont;//GT_MAT_CHEM
	//	float CCont;//GT_MAT_CHEM
	//	float MgCont;//GT_MAT_CHEM
	//	float AddRateMin;//HDH_PP_INJECTION über Purpose code GT_MAT_PURP 'Lime', 'Carbide', 'Magnesium' -purposes
	//	float AddRateStd;//HDH_PP_INJECTION 
	//	float AddRateMax;//HDH_PP_INJECTION 
	//	float AddRateMinMono;//HDH_PP_INJECTION 
	//	float AddRateStdMono;//HDH_PP_INJECTION 
	//	float AddRateMaxMono;//HDH_PP_INJECTION 
	//}MaterialTyp;
	os << "Mat.TempCoeff";
	for( long m=0; m<3; ++m)
	{
		const MaterialTyp& Material = HMDInput.Mat[ m]; // Mat[ 3] +++
		os << "\t" << Material.TempCoeff;
	}
	os << endl;

	os << "Mat.Price";
	for( long m=0; m<3; ++m)
	{
		const MaterialTyp& Material = HMDInput.Mat[ m]; // Mat[ 3] +++
		os << "\t" << Material.Price;
	}
	os << endl;

	os << "Mat.MgEqui";
	for( long m=0; m<3; ++m)
	{
		const MaterialTyp& Material = HMDInput.Mat[ m]; // Mat[ 3] +++
		os << "\t" << Material.MgEqui;
	}
	os << endl;

	os << "Mat.CaOCont";
	for( long m=0; m<3; ++m)
	{
		const MaterialTyp& Material = HMDInput.Mat[ m]; // Mat[ 3] +++
		os << "\t" << Material.CaOCont;
	}
	os << endl;

	os << "Mat.CaC2Cont";
	for( long m=0; m<3; ++m)
	{
		const MaterialTyp& Material = HMDInput.Mat[ m]; // Mat[ 3] +++
		os << "\t" << Material.CaC2Cont;
	}
	os << endl;

	os << "Mat.CCont";
	for( long m=0; m<3; ++m)
	{
		const MaterialTyp& Material = HMDInput.Mat[ m]; // Mat[ 3] +++
		os << "\t" << Material.CCont;
	}
	os << endl;

	os << "Mat.MgCont";
	for( long m=0; m<3; ++m)
	{
		const MaterialTyp& Material = HMDInput.Mat[ m]; // Mat[ 3] +++
		os << "\t" << Material.MgCont;
	}
	os << endl;

	os << "Mat.AddRateMin";
	for( long m=0; m<3; ++m)
	{
		const MaterialTyp& Material = HMDInput.Mat[ m]; // Mat[ 3] +++
		os << "\t" << Material.AddRateMin;
	}
	os << endl;
	os << "Mat.AddRateStd";
	for( long m=0; m<3; ++m)
	{
		const MaterialTyp& Material = HMDInput.Mat[ m]; // Mat[ 3] +++
		os << "\t" << Material.AddRateStd;
	}
	os << endl;
	os << "Mat.AddRateMax";
	for( long m=0; m<3; ++m)
	{
		const MaterialTyp& Material = HMDInput.Mat[ m]; // Mat[ 3] +++
		os << "\t" << Material.AddRateMax;
	}
	os << endl;

	os << "Mat.AddRateMinMono";
	for( long m=0; m<3; ++m)
	{
		const MaterialTyp& Material = HMDInput.Mat[ m]; // Mat[ 3] +++
		os << "\t" << Material.AddRateMinMono;
	}
	os << endl;
	os << "Mat.AddRateStdMono";
	for( long m=0; m<3; ++m)
	{
		const MaterialTyp& Material = HMDInput.Mat[ m]; // Mat[ 3] +++
		os << "\t" << Material.AddRateStdMono;
	}
	os << endl;
	os << "Mat.AddRateMaxMono";
	for( long m=0; m<3; ++m)
	{
		const MaterialTyp& Material = HMDInput.Mat[ m]; // Mat[ 3] +++
		os << "\t" << Material.AddRateMaxMono;
	}
	os << endl;

	//typedef struct _PatternTyp{//HDH_PP_BLOWING
	//  float CoRel;
	//  float FixedLime;
	//  float FixedCarbide;
	//  float MinLime;
	//  float MinCarbide;
	//  float MinMagnesia;
	//}PatternTyp;
	//	PatternTyp Pat[3];
	os << "Pat.CoRel";
	for( long p=0; p<5; ++p)
	{
		const PatternTyp& Pattern = HMDInput.Pat[ p];
		os << "\t" << Pattern.CoRel;
	}
	os << endl;
	os << "Pat.FixedLime";
	for( long p=0; p<5; ++p)
	{
		const PatternTyp& Pattern = HMDInput.Pat[ p];
		os << "\t" << Pattern.FixedLime;
	}
	os << endl;
	os << "Pat.FixedCarbide";
	for( long p=0; p<5; ++p)
	{
		const PatternTyp& Pattern = HMDInput.Pat[ p];
		os << "\t" << Pattern.FixedCarbide;
	}
	os << endl;

	os << "Pat.MinLime";
	for( long p=0; p<5; ++p)
	{
		const PatternTyp& Pattern = HMDInput.Pat[ p];
		os << "\t" << Pattern.MinLime;
	}
	os << endl;
	os << "Pat.MinCarbide";
	for( long p=0; p<5; ++p)
	{
		const PatternTyp& Pattern = HMDInput.Pat[ p];
		os << "\t" << Pattern.MinCarbide;
	}
	os << endl;
	os << "Pat.MinMagnesium";
	for( long p=0; p<5; ++p)
	{
		const PatternTyp& Pattern = HMDInput.Pat[ p];
		os << "\t" << Pattern.MinMagnesium;
	}
	os << endl;

	//typedef struct _TempCorrMgTyp{ //HDH_PP_TEMP_CORR
	//	float CoRel[TEMPCORR_MG_ROWS];
	//	float Corr[TEMPCORR_MG_ROWS];
	//}TempCorrMgTyp;
	// typedef struct _TempCorrCarbTyp{ //HDH_PP_TEMP_CORR
	//	float Temp[TEMPCORR_CARB_ROWS];
	//	float Corr[TEMPCORR_CARB_ROWS];
	//}TempCorrCarbTyp;

	os << "dTempLoss\t" << HMDInput.dTempLoss << endl;

	const TempCorrMgTyp& TempCorrMg = HMDInput.TCorrMg;
	const TempCorrCarbTyp& TempCorrCarb = HMDInput.TCorrCarb;

	os << "TCorrMg.CoRel\t" << TempCorrMg.CoRel[ 0] << "\t" << TempCorrMg.CoRel[ 1] << "\t" << TempCorrMg.CoRel[ 2] << "\t" << TempCorrMg.CoRel[ 3] << "\t" << TempCorrMg.CoRel[ 4] << endl;
	os << "TCorrMg.Corr\t" << TempCorrMg.Corr[ 0] << "\t" << TempCorrMg.Corr[ 1] << "\t" << TempCorrMg.Corr[ 2] << "\t" << TempCorrMg.Corr[ 3] << "\t" << TempCorrMg.Corr[ 4] << endl;

	os << "TCorrCarb.Temp\t" << TempCorrCarb.Temp[ 0] << "\t" << TempCorrCarb.Temp[ 1] << "\t" << TempCorrCarb.Temp[ 2] << "\t" << TempCorrCarb.Temp[ 3] << "\t" << TempCorrCarb.Temp[ 4] << endl;
	os << "TCorrCarb.Corr\t" << TempCorrCarb.Corr[ 0] << "\t" << TempCorrCarb.Corr[ 1] << "\t" << TempCorrCarb.Corr[ 2] << "\t" << TempCorrCarb.Corr[ 3] << "\t" << TempCorrCarb.Corr[ 4] << endl;

	os << "<END HMD model data --  " << filename << "  ------------------------------------------------------->" << endl;
	os << endl << endl << endl;

	return os.str(); //close();
}
