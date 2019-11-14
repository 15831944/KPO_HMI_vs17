#ifndef REEMODEL_H__
#define REEMODEL_H__

//Date: 22.09.00

// Fe-Loss
//	const double FELOSS=25.; now in rip.dur[2]

// Mg-correction for co-lime treatment
//	const double KOEFF=4.235; now in rip.dur[0]
//	const double EXPO=-0.2204; now in rip.dur[1]

const double SWITCHDUR[7]={0.2,0.2,0.2,0.2,0.2,0.2,0.2,};

// Materials
const int LIME=0;
const int CARBIDE=1;
const int MAGNESIUM=2;

// Treatment Types	
const int CO_LIME=2;
const int CO_CARBIDE=3;
const int ECO=4;
const int MONO_LIME=0;
const int MONO_CARBIDE=1;

// Treatment Phases
const int MONO1=0;
const int MONO2=1;
const int CO=2;
const int MONO3=3;
const int MONO4=4;

//Dimensions
const int BVT_ROWS=13;
const int BVT_COLUMNS=5;

const int TEMPCORR_MG_ROWS=5;
const int TEMPCORR_CARB_ROWS=5;

const int MAX_NO_WARN=50;



// Input variables

struct BaseValueTableTyp{

  double  BlowingRelation;
  double	MgContent;
  double	CaC2Content;
  double	Mg[BVT_ROWS][BVT_COLUMNS];
  double  SStart[BVT_ROWS];
  double  SFinal[BVT_COLUMNS];

};

struct MaterialTyp{
  double TempCoeff;
  double Price;
  double MgEqui;
  double CaOCont;
  double CaC2Cont;
  double CCont;
  double MgCont;
  double AddRateMin;
  double AddRateStd;
  double AddRateMax;
  double AddRateMinMono;
  double AddRateStdMono;
  double AddRateMaxMono;

};
struct PatternTyp{
  double CoRel;
  double FixedLime;
  double FixedCarbide;
  double MinLime;
  double MinCarbide;
  double MinMagnesium;
};
struct FreeboardTyp{
  double Fbrd[2];
  double MgRate[2];
};
struct CarbCorrSlagTyp{
  double Slag[4];
  double Corr[4];
};
struct CarbMono3Typ{
  double Mg[5];
  double Carbide[5];
};
struct SlagDurTyp{
  double Slag[5];
  double Duration[5];
};


struct TempCorrMgTyp{
  double CoRel[TEMPCORR_MG_ROWS];
  double Corr[TEMPCORR_MG_ROWS];
};
struct TempCorrCarbTyp{
  double Temp[TEMPCORR_CARB_ROWS];
  double Corr[TEMPCORR_CARB_ROWS];
};
struct StartConditionsTyp{
  double dAmt_iron;	
  double dAmt_slag;
  double dAim_sulphur;
  double dFreeboard;
  double dTemp_iron;
  double dCont_sulphur;
  int    bAvail_carbide;
  int    bAvail_lime;
  int    bAvail_mg;
  double    dAvail_carbide;
  double    dAvail_lime;
  double    dAvail_mg;

  double dTimeAvail;
  double dAmt_soda;
  bool   bPriceOptimum;
  //CString sSTART_TIME;
  //CString	sRELEASE_TIME;
};

struct MonoCorrTyp{
  double dSend[4];
  double dCorr[4];
};

// MODEL INPUT
//****************

struct ReeInput{
  StartConditionsTyp Strt;
  BaseValueTableTyp  Bvt;
  MaterialTyp        Mat[3];
  PatternTyp         Pat[5];//16.8.2011 anku corrected ([3] previously)
  double             dur[7];
  double             dAvgDur;
  double             dCorrmono;
  FreeboardTyp       Freebd;
  CarbCorrSlagTyp    CCorrSlag;
  CarbMono3Typ       CMono3;
  SlagDurTyp         SlgDur;
  TempCorrMgTyp      TCorrMg;
  TempCorrCarbTyp    TCorrCarb;
  double             dTempLoss;
  double             dPrevAdd[3];
  double  dActFlow[3];
  double  dActLancePos;
  MonoCorrTyp        MonoCorrLime;
  MonoCorrTyp        MonoCorrCarbide;
  int                iBVT_ROWS;
  //double FeLoss;
};

// Output variables

struct CalcAmountsTyp{
  double dLime[5];
  double dCarbide[5];
  double dMagnesium[5];

  CalcAmountsTyp()
  {
	  for( int i=0;i<5; ++i)
	  {
		  dLime[i] = 0.0;
		  dCarbide[i] = 0.0;
		  dMagnesium[i] = 0.0;
	  }
  }
};

//struct CalcFlowTyp{
//  double dLime[5];			//5 Process Phases
//  double dCarbide[5];
//  double dMagnesium[5];
//
//  CalcFlowTyp()
//  {
//	  for( int i=0;i<5; ++i)
//	  {
//		  dLime[i] = 0.0;
//		  dCarbide[i] = 0.0;
//		  dMagnesium[i] = 0.0;
//	  }
//  }
//};


// MODEL OUTPUT
//****************

struct ReeOutput{

  int		iTreatmentKind;
  CalcAmountsTyp CalcAmount[5]; //5 Treatment kinds
CalcAmountsTyp CalcFlow[5];
//CalcFlowTyp    CalcFlow[5];
  double	dSlagAmount[5];
  double	dDurationDeslagging[5];
  double	dTemperatureAfter[5];
  double	dCost[5];
  double	dDuration[5];
  float	  iwarn;
  long    llwarn[5]; // new array for separate warning/error for each treatment type

  ReeOutput()
  {
	  iTreatmentKind = -1;
	  for( int i=0;i<5; ++i)
	  {
		  dSlagAmount[i] = 0.0;
		  dDurationDeslagging[i] = 0.0;
		  dTemperatureAfter[i] = 0.0;
		  dCost[i] = 0.0;
		  dDuration[i] = 0.0;
		  llwarn[i] = 0; // new array for separate warning/error for each treatment type
	  }
	  float	  iwarn = 0.0;
  }

};

// model function
__declspec( dllexport ) int reemodel( const ReeInput& rip, ReeOutput *rop);

#endif // REEMODEL_H__

