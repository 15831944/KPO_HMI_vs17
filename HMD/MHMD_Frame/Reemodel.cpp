/**************************************************
*                   RECalc.cpp                   *
**************************************************
*                                                *
* Created at  :  01.10.03   11:24                *
* Author      :  Kubbe, Andreas	                 *
* Company Name:  SMS Mevac GmbH                  *
* File Name   :  RECalc.cpp                      *
*                                                *
*  Updated By     Date      Description          *
*  -------------+---------+------------          *
*      Kubbe    |23.08.07 |		                 *
*      Kubbe    |01.06.12 | Errors renumbered	 *
*      Kubbe    |28.08.13 | Weight check         *
**************************************************/


//#include "stdafx.h"
//#include "ree.h"
//#include "RECalc.h"
#include <iostream>
#include <tchar.h>


#include <stdlib.h>

#include "math.h"
//#include <afxconv.h>
//#include "registry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// play sound at end
//#include <mmsystem.h>


//#include "BaseValueDlg.h"
//#include "TempCorrDlg.h"
//#include "ParameterTablesDlg.h"
//#include "MatDataDlg.h"
//#include "ParameterTabel1Dlg.h"
//#include "DlgMELTDATA.h"

#include "reemodel.h"


double koeff(const BaseValueTableTyp *bvt, double dSstart, double dSfinal, int rows);
void sort(const double *raim, int *isort, int length);
double interpol(double dXw, const double *dXptr, const double *dYptr, int iDim);
int check(double value, double min, double max);
ReeOutput rop;
int m_treatment_type;

//****check variables
int CheckPriceOptimum, CheckTreatmentKind; // not used yet
int errorloopprevention;
//int monoforce; //get value by OPC and force it at end of model


// Interpolation from Base Value Table


double koeff(const BaseValueTableTyp* bvt, double dSstart, double dSfinal, int rows)
{
	int i;
	double mg[BVT_ROWS];

	for (i = 0; i < rows; i++)	// For each start sulphur determine interolated value
		// acc. to aim sulphur
		mg[i] = interpol(dSfinal, bvt->SFinal, bvt->Mg[i], BVT_COLUMNS);

	return interpol(dSstart, bvt->SStart, mg, rows);
}


double interpol(double dXw, const double *dXptr, const double *dYptr, int iDim)
{
	int i, *isort;
	double dInterpol, dX;

	if (iDim < 0)
	{ //Brauner - 2004-02-07
		rop.iwarn = 1005;
		return -1.;
	} //Brauner - 2004-02-07
	// create vector isort

	isort = (int *)calloc(iDim, sizeof(int));   
	if (isort == NULL)
	{
		free(isort);
		rop.iwarn = 1001;
		return -1.;
	}	
	sort(dXptr, isort, iDim); // descending order

	for (i = 0; i<iDim && dXw < dXptr[isort[i]]; i++)	;
	// unbehandelte Ausnahme erschien hier!
	// @err in watchfenster einbinden und Fehlerzahl abwarten
	//Extras - Fehler suchen - Fehlerzahl eingeben
	//FILE *fp = fopen("c:\\a_file_that_does_not_exist.txt", "r"); //Probefehler
	if (i >= iDim)
		dInterpol = dYptr[isort[i - 1]];
	else if (i>0)
	{
		dX = dXptr[isort[i]] - dXptr[isort[i - 1]];
		if (dX != 0.)
			dInterpol = dYptr[isort[i - 1]]+ (dXw - dXptr[isort[i - 1]])/dX* (dYptr[isort[i]] - dYptr[isort[i - 1]]);
		else 
		{
			free(isort);
			rop.iwarn = 1002;
			return -1.;
		}
	}
	else     
		dInterpol = dYptr[isort[0]];
	free(isort);
	return dInterpol;
}

void sort(const double *raim, int *isort, int length)
/* Function: return isort so that raim(isort(1)) is the biggest element of 
raim, raim(isort(2)) the second biggest etc. */
{
	double rcomp;
	int length1;
	int icomp, iold;
	int i, j, k;

	length1 = length;

	for (k = 0; k < length1; k++) // do k=1,length1
		isort[k] = k;       // Position

	for (k = 0; k < length1 - 1; k++)
	{
		//    do k=1,length1-1
		rcomp= raim[isort[k]];
		icomp= k;
		for (i = k + 1; i < length1; i++)
		{
			// do i=k+1,length1
			// find the biggest
			if (raim[isort[i]]>rcomp)
			{
				rcomp = raim[isort[i]];
				icomp = i;
			}
		}
		// Shift down
		if (icomp >= k)
		{
			iold = isort[icomp];
			for (j = icomp; j >= k + 1; j--)
			{
				//      do j=icomp,k+1,-1
				isort[j] = isort[j - 1];
			}
			isort[k] = iold;
		}
	}
	return;
}
int check(double value, double min, double max)
{ 
	if (value < min || value > max)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}


//**************************************************
//*the model
//**************************************************
__declspec( dllexport ) int reemodel( const ReeInput& rip, ReeOutput *rop)
{

	// The M O D E L 
	// == == == == ==

	// Version 22.9.00 Kub
	// Version 31.8.11 Kub Bhushan...
	// Version 28.8.13 Kub 

	// FeLoss in reemodel.h (nicht in rip)
	// KOEFF und EXPO für CaO-Korrektur

	// rounded flow rates
	// time violation message only if no treatment without time violation
	// co-relation close to aim

	// rip.dur sind jetzt 7 Reserveparameter. Die ersten sind wie folgt belegt:
	//	rip.dur[0,1,2]=KOEFF,EXPO,FE-LOSS

	// Für Fehlermeldung Check des schon gerundeten Mg-Max
	/*
	Das sind alle für das Modell relevanten Routinen in RECalc.cpp. 
	Folgende Änderungen mußten für die PSI - Kompatibilität gemacht werden 


	Der Modellcode beginnt ab dem Statement int CRECalc::reemodel(ReeInput rip, ...
	und endet beim(nicht mehr dazugehörigen) Statement 
	void CRECalc::OnSelchangeCombo1Kindoftreatment() 

	Diesen Code in eine neue Datei reemodel.cxx schreiben. Folgende weitere Aktionen:

	a) CRECalc:: weg! Es bleibt int reemodel(ReeInput rip, ...
	b) vor dieses statement diverse Deklarationen und includes. Siehe reemodel.cxx.

	Nämlich:

	#include "reemodel.h"
	#include <stdlib.h>
	#include <math.h>


	float koeff(BaseValueTableTyp *bvt, float dSstart, float dSfinal);
	void sort(float *raim, int *isort, int length);
	float interpol(float dXw, float *dXptr, float *dYptr, int iDim);
	int check(float value, float min, float max);


	c) alle double in float umwandeln(in reemodel.cxx und reemodel.h)
	d) alle BOOL in int umwandeln(auch in cxx und h)

	*/
//to be defined (#define CONSIDERQTIES), if amounts of materials to be considered for determining their availability
	#undef CONSIDERQTIES


	const double STDHMWEIGHT=80000.;
	const double seven=7.0;
	
	double	mg, mv, mvmax, mvmin;
	double	carbide, carbidemono2, carbidemono3, carbidemono3ECO, carbidemono2ECO, SlagAmount, DurationDeslagging;
	double	MgRateMax, CarbideRateMax;
	//CString StringValue;

	int iwarn = 0, i, j;
	int iTreatment;

	rop->iTreatmentKind = -1; // default setting
	for (iTreatment = 4; iTreatment >= 0; iTreatment--)rop->llwarn[iTreatment]=0;
	rop->iwarn=0;

	// if no carbide available: no corresponding checks:
	const bool carbavl = rip.Strt.bAvail_carbide != 0;
	const bool limeavl = rip.Strt.bAvail_lime != 0;
	const bool mgavl = rip.Strt.bAvail_mg != 0;
	//to set standard values, if necessary
	double Temp_iron=rip.Strt.dTemp_iron;
	double Freeboard=rip.Strt.dFreeboard;
	double Amt_iron=rip.Strt.dAmt_iron;
	double Aim_sulphur=rip.Strt.dAim_sulphur;

	if (!carbavl){
		rop->llwarn[CO_CARBIDE]=22513;
		rop->llwarn[ECO]=22513;
		rop->llwarn[MONO_CARBIDE]=22513;
	}
	if (!limeavl){
		rop->llwarn[CO_LIME]=22512;
		rop->llwarn[ECO]=22512;
		rop->llwarn[MONO_LIME]=22512;
	}
	if (!mgavl){
		rop->llwarn[CO_LIME]=22514;
		rop->llwarn[CO_CARBIDE]=22514;
		rop->llwarn[ECO]=22514;
	}

	// Reset output values
	for (i = 0; i < 5; i++)
	{
		rop->dSlagAmount[i]=
			rop->dCost[i]=
			rop->dDurationDeslagging[i]=
			rop->dTemperatureAfter[i]=
			rop->dSlagAmount[i]=
			rop->dDuration[i] = 0.;

		for (j = 0; j < 5; j++)
		{
			rop->CalcAmount[i].dCarbide[j] = 0.;
			rop->CalcAmount[i].dMagnesium[j] = 0.;
			rop->CalcAmount[i].dLime[j] = 0.;
			rop->CalcFlow[i].dCarbide[j] = 0.;
			rop->CalcFlow[i].dMagnesium[j] = 0.;
			rop->CalcFlow[i].dLime[j] = 0.;
		}
	}


	// Determine price-optimum blowing relation mv for Carbide-Co.


	mvmax = rip.Mat[CARBIDE].AddRateMax/rip.Mat[MAGNESIUM].AddRateMin;
	mvmin = rip.Mat[CARBIDE].AddRateMin/rip.Mat[MAGNESIUM].AddRateMax;

	// rop->cWarning[0]="No Error";
	rop->iwarn  = 0;

	// Check input variables

	// BASE VALUE TABLE

	if (check(rip.Bvt.BlowingRelation, 1., 10.))
	{
		rop->iwarn  = 22102;
		// rop->cWarning[iwarn++]="Blowing Relation Base-Value-Table out of order";
		return -1;
	}
	if (check(rip.Bvt.MgContent, 10., 100.))
	{
		rop->iwarn  = 22103;
		// rop->cWarning[iwarn++]="Mg-Content of reference Material Base-Value-Table out of order";
		return -1;
	}
	if (carbavl && check(rip.Bvt.CaC2Content, 10., 100.))
	{
		rop->iwarn  = 22101;
		// rop->cWarning[iwarn++]="CaC2-Content of reference Material Base-Value-Table out of order";
		return -1;
	}

	for (i = 0; i < rip.iBVT_ROWS; i++)
	{
		if (check(rip.Bvt.SStart[i], 30., 2000.))
		{
			rop->iwarn  = 22104;
			// rop->cWarning[iwarn++]="Start Sulphur values in Base-Value-Table out of order";
			return -1;
		}
	}
	for (i = 0; i < BVT_COLUMNS; i++)
	{
		if (check(rip.Bvt.SFinal[i], 0., 1000.))
		{
			rop->iwarn  = 22106;
			// rop->cWarning[iwarn++]="Final Sulphur values in Base-Value-Table out of order";
			return -1;
		}
	}
	for (i = 0; i < rip.iBVT_ROWS; i++)
	{
		for (j = 0; j < BVT_COLUMNS; j++)
			if (check(rip.Bvt.Mg[i][j], 0., 10.))
			{
				rop->iwarn  = 22105;
				// rop->cWarning[iwarn++]="One or more values in Base-Value-Table out of order";
				return -1;
			}
	}
	// PATTERN

	if (check(rip.Pat[CO_LIME].CoRel, 0., 10.)) // in Bhushan Db: 336
	{
		rop->iwarn  = 22425;
		rop->llwarn[CO_LIME]=22425;
		//return -1;
	}
	if (carbavl && check(rip.Pat[CO_CARBIDE].CoRel, 0., 10.))
	{
		rop->iwarn  = 22430;
		rop->llwarn[CO_CARBIDE]=22430;

		//return -1;
	}
	if (carbavl && check(rip.Pat[ECO].CoRel, 0., 10.))
	{
		rop->iwarn  = 22431;
		rop->llwarn[ECO]=22431;
		
		//return -1;
	}
	// Injection Relation of pattern out of order
	if (check(rip.Pat[CO_LIME].MinMagnesium, 5., 20.))
	{
		rop->iwarn  = 22426;
		rop->llwarn[CO_LIME]=22426;
		
		//return -1;
	}
	if (carbavl && check(rip.Pat[CO_CARBIDE].MinMagnesium, 5., 20.))
	{
		rop->iwarn  = 22432;
		rop->llwarn[CO_CARBIDE]=22432;

		//return -1;
	}
	if (carbavl && check(rip.Pat[ECO].MinMagnesium, 5., 20.))
	{
		rop->iwarn  = 22433;
		rop->llwarn[ECO]=22433;

		//return -1;
	}
	// Min. Mg-Addition out of order

	if (carbavl && check(rip.Pat[ECO].FixedLime, 0., 100.))
	{
		rop->iwarn  = 22422;
		rop->llwarn[ECO]=22422;
		//return -1;
	}// Initial Lime addition of pattern out of order
	if (check(rip.Pat[CO_LIME].FixedLime, 0., 100.))
	{
		rop->iwarn  = 22427;
		rop->llwarn[CO_LIME]=22427;

		//return -1;
	}// Initial Lime addition of pattern out of order
	if (carbavl && check(rip.Pat[CO_CARBIDE].FixedCarbide, 0., 100.))
	{
		rop->iwarn  = 22424;
		rop->llwarn[CO_CARBIDE]=22424;
		//return -1;
	}// Initial Carbide addition of pattern out of order

	if (carbavl && check(rip.Pat[ECO].MinLime, 0., 100.))
	{
		rop->iwarn  = 22429;
		rop->llwarn[ECO]=22429;

		//return -1;
	}// Min Lime addition of pattern out of order
	if (check(rip.Pat[CO_LIME].MinLime, 0., 100.))
	{
		rop->iwarn  = 22428;
		rop->llwarn[CO_LIME]=22428;

		//return -1;
	}// Min Lime addition of pattern out of order
	if (carbavl && check(rip.Pat[CO_CARBIDE].MinCarbide, 0., 100.))
	{
		rop->iwarn  = 22423;
		rop->llwarn[CO_CARBIDE]=22423;
		//return -1;
	}// Min Carbide addition of pattern out of order

	for (i = 0; i < 6; i++)
	{
		if (check(SWITCHDUR[i], 0., 2.))
		{
			rop->iwarn  = 22421;
			rop->llwarn[ECO]=22421;
			break;//return -1;
		}// Duration of steps (ECO) out of order
	}

	// PARAMETERS

	for (i = 0; i < 2; i++)
	{
		if (check(rip.Freebd.Fbrd[i], 0., 100.))
		{
			rop->iwarn  = 22201;
			return -1;
		}// Freeboard/Mg-Correction table out of order
	}
	for (i = 0; i < 2; i++)
	{
		if (check(rip.Freebd.MgRate[i], 1., 110.))
		{
			rop->iwarn  = 22202;
			return -1;
		}
		// Freeboard/Mg-Correction table out of order
	}
	for (i = 0; i < 4; i++)
	{			
		if (check(rip.CCorrSlag.Slag[i], 0., 12000.))
		{
			rop->iwarn  = 22203;
			return -1;
		}// Table Carbide/Slag correction out of order
	}
	for (i = 0; i < 4; i++)
	{
		if (check(rip.CCorrSlag.Corr[i], -50., 110.)) // 100.0 
		{
			rop->iwarn  = 22209;
			rop->llwarn[CO_CARBIDE]=22209;

			//return -1;
		}
		// Table Carbide/Slag correction out of order
	}
	if (carbavl)
	{
		for (i = 0; i < 4; i++)
		{
			if (check(rip.CMono3.Carbide[i], 0., 2.))
			{
				rop->iwarn  = 22210;
				return -1;
			}// Carbide (Mono3) = f(Mg) table out of order
		}
	}
	for (i = 0; i < 4; i++)
	{	
		if (check(rip.CMono3.Mg[i], 0., 5.))
		{
			rop->iwarn  = 22211;
			return -1;
		}
		// Carbide (Mono3) = f(Mg) table out of order
	}
	for (i = 0; i < 4; i++)
	{
		if (check(rip.SlgDur.Duration[i], 0., 30.))
		{
			rop->iwarn  = 22204;
			return -1;
		}// Deslagging duration table out of order
	}

	for (i = 0; i < 4; i++)
	{		
		if (check(rip.SlgDur.Slag[i], 0., 18000.))
		{
			rop->iwarn  = 22205;
			return -1;
		}
	}		// Deslagging duration table out of order

	if (carbavl)
	{
		for (i = 0; i < 4; i++)
		{
			if (check(rip.MonoCorrCarbide.dSend[i], 0., 300.))
			{
				rop->iwarn  = 22212;
				rop->llwarn[MONO_LIME]=22212;
				rop->llwarn[MONO_CARBIDE]=22212;


				//return -1;
			}// Correction factor table mono injection out of order
		}
	}
	if (carbavl)
	{
		for (i = 0; i < 4; i++)
			if (check(rip.MonoCorrCarbide.dCorr[i], 0., 3.))
			{
				rop->iwarn  = 22213;
				rop->llwarn[MONO_LIME]=22213;
				rop->llwarn[MONO_CARBIDE]=22213;

				//return -1;
			}
			// Correction factor table mono injection out of order
	}
	// TEMPERATURE CORRECTION

	for (i = 0; i < 5; i++)
	{
		if (check(rip.TCorrMg.CoRel[i], 1., 12.))
		{
			rop->iwarn  = 22206;
			return -1;
		}// Temperature correction table Mg out of order
	}
	for (i = 0; i < 5; i++)
	{
		if (check(rip.TCorrMg.Corr[i], -25., 25.))
		{
			rop->iwarn  = 22216;
			return -1;
		}
		// Temperature correction table Mg out of order
	}

	if (carbavl)
	{
		for (i = 0; i < 5; i++)
			if (check(rip.TCorrCarb.Corr[i], -50., 50.))
			{
				rop->iwarn  = 22214;
				return -1;
			}// Temperature correction table Carbide out of order
	}

	if (carbavl)
	{
		for (i = 0; i < 5; i++)
			if (check(rip.TCorrCarb.Temp[i], 1100., 1600.))
			{
				rop->iwarn  = 22215;
				return -1;
			}
			// Temperature correction table Carbide out of order
	}
	if (check(rip.dTempLoss, 0., 10.))
	{
		rop->iwarn  = 22207;
		return -1;
	}// Temperature loss per minute out of order

	// MATERIALS

	for (i = 0; i < 3; i++)
	{
		if (!carbavl)
			if (i == CARBIDE)
				continue;
		if (check(rip.Mat[i].TempCoeff, 0., 30.))
		{
			rop->iwarn  = 22303;
			if (i==CARBIDE){
				rop->llwarn[MONO_CARBIDE]=22303;
				rop->llwarn[CO_CARBIDE]=22303;
				rop->llwarn[ECO]=22303;
			}
			else if (i==LIME){
				rop->llwarn[MONO_LIME]=22302;
				rop->llwarn[CO_LIME]=22302;
				rop->llwarn[ECO]=22302;
			}
			else if (i==MAGNESIUM){
				rop->llwarn[CO_LIME]=22301;
				rop->llwarn[CO_CARBIDE]=22301;
				rop->llwarn[ECO]=22301;
			}




			//return -1;
		}// Temperature coefficient of material out of order
		if (check(rip.Mat[i].Price, 0., 15000.))
		{
			rop->iwarn  = 22306;
			if (i==CARBIDE){
				rop->llwarn[MONO_CARBIDE]=22306;
				rop->llwarn[CO_CARBIDE]=22306;
				rop->llwarn[ECO]=22306;
			}
			else if (i==LIME){
				rop->llwarn[MONO_LIME]=22305;
				rop->llwarn[CO_LIME]=22305;
				rop->llwarn[ECO]=22305;
			}
			else if (i==MAGNESIUM){
				rop->llwarn[CO_LIME]=22304;
				rop->llwarn[CO_CARBIDE]=22304;
				rop->llwarn[ECO]=22304;
			}




			//return -1;
		}// Price  of material out of order
		if (check(rip.Mat[i].AddRateMax, 0., 100.))
		{
			rop->iwarn  = 22402;
			if (i==CARBIDE){
				rop->llwarn[MONO_CARBIDE]=22402;
				rop->llwarn[CO_CARBIDE]=22402;
				rop->llwarn[ECO]=22402;
			}
			else if (i==LIME){
				rop->llwarn[MONO_LIME]=22401;
				rop->llwarn[CO_LIME]=22401;
				rop->llwarn[ECO]=22401;
			}
			else if (i==MAGNESIUM){
				rop->llwarn[CO_LIME]=22400;
				rop->llwarn[CO_CARBIDE]=22400;
				rop->llwarn[ECO]=22400;
			}





			//return -1;
		}
		// Min/Max/Aim addition rate  of material out of order
		if (check(rip.Mat[i].AddRateMin, 0., rip.Mat[i].AddRateMax))
		{
			rop->iwarn  = 22405;
			if (i==CARBIDE){
				rop->llwarn[MONO_CARBIDE]=22405;
				rop->llwarn[CO_CARBIDE]=22405;
				rop->llwarn[ECO]=22405;
			}
			else if (i==LIME){
				rop->llwarn[MONO_LIME]=22404;
				rop->llwarn[CO_LIME]=22404;
				rop->llwarn[ECO]=22404;
			}
			else if (i==MAGNESIUM){
				rop->llwarn[CO_LIME]=22403;
				rop->llwarn[CO_CARBIDE]=22403;
				rop->llwarn[ECO]=22403;
			}

		}// Min/Max/Aim  addition rate  of material out of order
		if (check(rip.Mat[i].AddRateStd, rip.Mat[i].AddRateMin, rip.Mat[i].AddRateMax))
		{
			rop->iwarn  = 22408;
			if (i==CARBIDE){
				rop->llwarn[MONO_CARBIDE]=22408;
				rop->llwarn[CO_CARBIDE]=22408;
				rop->llwarn[ECO]=22408;
			}
			else if (i==LIME){
				rop->llwarn[MONO_LIME]=22407;
				rop->llwarn[CO_LIME]=22407;
				rop->llwarn[ECO]=22407;
			}
			else if (i==MAGNESIUM){
				rop->llwarn[CO_LIME]=22406;
				rop->llwarn[CO_CARBIDE]=22406;
				rop->llwarn[ECO]=22406;
			}
		}// Min/Max/Aim  addition rate  of material out of order


		if (check(rip.dPrevAdd[i], 0., 4000.))
		{
			rop->iwarn  = 22511;
			if (i==CARBIDE){
				rop->llwarn[MONO_CARBIDE]=22511;
				rop->llwarn[CO_CARBIDE]=22511;
				rop->llwarn[ECO]=22511;
			}
			else if (i==LIME){
				rop->llwarn[MONO_LIME]=22510;
				rop->llwarn[CO_LIME]=22510;
				rop->llwarn[ECO]=22510;
			}
			else if (i==MAGNESIUM){
				rop->llwarn[CO_LIME]=22509;
				rop->llwarn[CO_CARBIDE]=22509;
				rop->llwarn[ECO]=22509;
			}
			//return -1;
		}// previous addition of material out of order
	}
	if (carbavl && check(rip.Mat[CARBIDE].AddRateMaxMono, 0., 60.))
	{
		rop->iwarn  = 22412;
		rop->llwarn[MONO_CARBIDE]=22412;

		//return -1;
	}
	// Min/Max/Aim addition rate  of material out of order
	if (carbavl && check(rip.Mat[CARBIDE].AddRateMinMono, 0., rip.Mat[CARBIDE].AddRateMaxMono))
	{
		rop->iwarn  = 22413;
		rop->llwarn[MONO_CARBIDE]=22413;

		//return -1;
	}// Min/Max/Aim  addition rate  of material out of order
	if (carbavl && check(rip.Mat[CARBIDE].AddRateStdMono, rip.Mat[CARBIDE].AddRateMinMono, rip.Mat[CARBIDE].AddRateMaxMono))
	{
		rop->iwarn  = 22414;
		rop->llwarn[MONO_CARBIDE]=22414;

		//return -1;
	}// Min/Max/Aim  addition rate  of material out of order

	if (check(rip.Mat[LIME].AddRateMaxMono, 0., 60.))
	{
		rop->iwarn  = 22409;
		rop->llwarn[MONO_LIME]=22409;

		//return -1;
	}
	// Min/Max/Aim addition rate  of material out of order
	if (check(rip.Mat[LIME].AddRateMinMono, 0., rip.Mat[LIME].AddRateMaxMono))
	{
		rop->iwarn  = 22410;
		rop->llwarn[MONO_LIME]=22410;

		//return -1;
	}// Min/Max/Aim  addition rate  of material out of order
	if (check(rip.Mat[LIME].AddRateStdMono, rip.Mat[LIME].AddRateMinMono, rip.Mat[LIME].AddRateMaxMono))
	{
		rop->iwarn  = 22411;
		rop->llwarn[MONO_LIME]=22411;

		//return -1;
	}// Min/Max/Aim  addition rate  of material out of order

	if (check(rip.Mat[LIME].CaOCont, 50., 100.))
	{
		rop->iwarn  = 22314;
		rop->llwarn[MONO_LIME]=22314;
		rop->llwarn[CO_LIME]=22314;
		rop->llwarn[ECO]=22314;
		//return -1;
	}// CaO content of lime out of order
	if (carbavl && check(rip.Mat[CARBIDE].CaC2Cont, 50., 90.))
	{
		rop->iwarn  = 22308;
		rop->llwarn[MONO_CARBIDE]=22308;
		rop->llwarn[CO_CARBIDE]=22308;
		rop->llwarn[ECO]=22308;


		//return -1;
	}// CAD analysis  out of order
	if (carbavl && check(rip.Mat[CARBIDE].CCont, 0., 15.))
	{
		rop->iwarn  = 22311;
		rop->llwarn[MONO_CARBIDE]=22311;
		rop->llwarn[CO_CARBIDE]=22311;
		rop->llwarn[ECO]=22311;


		//return -1;
	}// CAD analysis out of order
	if (check(rip.Mat[MAGNESIUM].MgCont, 70., 100.))
	{
		rop->iwarn  = 22310;
		rop->llwarn[CO_LIME]=22310;
		rop->llwarn[CO_CARBIDE]=22310;
		rop->llwarn[ECO]=22310;

		//return -1;
	}// Mg analyis out of order

	if (check(rip.Mat[LIME].MgEqui, 10., 20.))
	{
		rop->iwarn  = 22312;
		rop->llwarn[MONO_LIME]=22312;
		rop->llwarn[CO_LIME]=22312;
		rop->llwarn[ECO]=22312;

		//return -1;
	}// Mg equivalent of carbide or lime out of order
	if (carbavl && check(rip.Mat[CARBIDE].MgEqui, 5., 10.))
	{
		rop->iwarn  = 22313;
		rop->llwarn[MONO_CARBIDE]=22313;
		rop->llwarn[CO_CARBIDE]=22313;
		rop->llwarn[ECO]=22313;

		//return -1;
	}// Mg equivalent of carbide or lime out of order

	// START CONDITIONS

	if (check(Aim_sulphur, 0., rip.Strt.dCont_sulphur))
	{
		//rop->iwarn  = 22507;
		rop->llwarn[ECO]=rop->llwarn[CO_CARBIDE]=rop->llwarn[CO_LIME]=
			rop->llwarn[MONO_LIME]=rop->llwarn[MONO_CARBIDE]=22507;
		Aim_sulphur=100.;

		//return -1;
	}// Aim sulphur out of order
	if (check(rip.Strt.dCont_sulphur, 30., 2001.))
	{
		rop->iwarn  = 22501;
		return -1;
	}// Start sulphur out of order
	if (check((rip.Strt.dAmt_iron/1000.), 100., 200.))
	{
		//rop->iwarn  = 22502;
		rop->llwarn[ECO]=rop->llwarn[CO_CARBIDE]=rop->llwarn[CO_LIME]=
			rop->llwarn[MONO_LIME]=rop->llwarn[MONO_CARBIDE]=22502;
		Amt_iron=STDHMWEIGHT;
		//return -1;
	}// Start Iron amount out of order
	if (check(rip.Strt.dAmt_slag, 0., 1600.))
	{
		rop->iwarn   = 22503;
		return -1;
	}// Start slag amount out of order
	if (check(rip.Strt.dAmt_soda, 0., 20000.))
	{
		rop->iwarn   = 22506;
		return -1;
	}// Start soda amount out of order
	if (check(rip.Strt.dFreeboard, 10., 300.))
	{
		//rop->iwarn  = 22504;

		rop->llwarn[ECO]=rop->llwarn[CO_CARBIDE]=rop->llwarn[CO_LIME]=22504;
		Freeboard=100.;//standard value

	}// Start freeboard out of order
	if (check(rip.Strt.dTemp_iron, 1100., 1700.))
	{
		rop->llwarn[ECO]=rop->llwarn[CO_CARBIDE]=rop->llwarn[CO_LIME]=
			rop->llwarn[MONO_LIME]=rop->llwarn[MONO_CARBIDE]=22505;
		Temp_iron=1300;//standard value
		//rop->iwarn  = 22505;
		//return -1;
	}// Start temperature out of order
	if (!carbavl&&!rip.Strt.bAvail_lime)
	{
		rop->iwarn  = 22601;
		return -1;

	}// Neither carbide nor lime available
	/*
	if (check(rip.dur[0], 0., 20.))
	{
	rop->iwarn  = 10999;
	return -1;
	}// KOEFF out ouf order
	if (check(rip.dur[1], - 1., 0.))
	{
	rop->iwarn  = 10999;
	return -1;
	}// EXPO out ouf order
	if (check(rip.dur[2], 0., 70.))
	{
	rop->iwarn  = 10999;
	return -1;
	}// FELOSS out ouf order


	*/


	// Determine available time
	int iMinutesAvail;
	iMinutesAvail = (int)rip.Strt.dTimeAvail;
	if (iMinutesAvail < 0)
		iMinutesAvail = 0;

	// Co-Injection with Carbide
	double durationold, ddur, duration, maxduration, maxdurblowing;
	double priceold, dmv, price;
	double mgBaseValue;
	double lfak, mfak, cfak;
	double dS, EtaMg, MgS, MgO, EtaCa, CaS, CaO, Cfree;
	double proz, dTemp;
	double mgPrevAdd, mgprev, carbideprev, limeprev, mgBaseValueSav;

	double mcorr[3];
	// Determine correction factor of mono-injection

	if (carbavl)
		mcorr[CARBIDE] = interpol(Aim_sulphur, rip.MonoCorrCarbide.dSend, rip.MonoCorrCarbide.dCorr, 4);
	mcorr[LIME] = interpol(Aim_sulphur, rip.MonoCorrLime.dSend, rip.MonoCorrLime.dCorr, 4);
	if (carbavl)
		if (mcorr[CARBIDE] <= 0.||mcorr[CARBIDE]>2.)
			mcorr[CARBIDE] = rip.dCorrmono;
	if (mcorr[LIME] <= 0.||mcorr[LIME]>2.)
		mcorr[LIME] = rip.dCorrmono; // Standard lime is used if range outside 2 and 0 - Explanation of Brauner 2004-02-02

	priceold = price = 1e12;
	dmv=.5;
	duration = ddur = 0.;
	durationold = 1e12;
	maxduration = (double)iMinutesAvail;

	// Mg-equivalent of previously added materials

	mfak = rip.Bvt.MgContent/rip.Mat[MAGNESIUM].MgCont;
	cfak = rip.Bvt.CaC2Content/rip.Mat[CARBIDE].CaC2Cont;
	lfak = 1.;

	mgPrevAdd = 7.*rip.dPrevAdd[MAGNESIUM]/mfak;


	if (mgPrevAdd != 0.)
	{
		// Co-Injection
		// 07-10-2003-Hismelt	mgPrevAdd+=rip.Mat[CARBIDE].MgEqui/rip.Mat[LIME].MgEqui*rip.dPrevAdd[LIME];

		// 07-10-2003-Hismelt	mgPrevAdd+=7./rip.Mat[CARBIDE].MgEqui*rip.dPrevAdd[CARBIDE]/cfak;
		mgPrevAdd += 7/rip.Mat[LIME].MgEqui*rip.dPrevAdd[LIME];

		if (carbavl)
			mgPrevAdd += 7./7.*rip.dPrevAdd[CARBIDE]/cfak;
	}
	else 
	{ // Consider Correction factor mcorr[] for Mono-Injection:
		// 07-10-2003-Hismelt	mgPrevAdd+=rip.Mat[CARBIDE].MgEqui/rip.Mat[LIME].MgEqui*rip.dPrevAdd[LIME]/mcorr[LIME];
		mgPrevAdd += 7./rip.Mat[LIME].MgEqui*rip.dPrevAdd[LIME]/mcorr[LIME];

		if (carbavl)
			mgPrevAdd += 7./rip.Mat[CARBIDE].MgEqui*rip.dPrevAdd[CARBIDE]/cfak/mcorr[CARBIDE];
	}

	mgPrevAdd /=(Amt_iron/1000.)* (7.+rip.Bvt.BlowingRelation);

	if (carbavl)
		carbideprev = rip.dPrevAdd[CARBIDE]/ (Amt_iron/1000.);
	else 
		carbideprev = 0.;// 07-10-2003-Hismelt

	limeprev = rip.dPrevAdd[LIME]/ (Amt_iron/1000.);
	mgprev = rip.dPrevAdd[MAGNESIUM]/ (Amt_iron/1000.);

	// Estimation of desulphurisation due to previous additions


	// Co-Treatments: CO_LIME, CO_CARBIDE, ECO
	//rop->iwarn  = 0;
	
	//set iwarn 0 if still one possible treatment
	for (iTreatment = 0; iTreatment < 5; iTreatment++)
		if(rop->llwarn[iTreatment]  == 0){
			rop->iwarn=0;
			break;
		}
	// rop->cWarning[0]="No Error";
	mgBaseValue = koeff(& (rip.Bvt), rip.Strt.dCont_sulphur, Aim_sulphur, rip.iBVT_ROWS);
	mgBaseValueSav = mgBaseValue;
	mgBaseValue -= mgPrevAdd;
	if (mgBaseValue <= 0)
		rop->iwarn  = 22500;

	if (mgBaseValue > 0)
	{
		for (iTreatment = 0; iTreatment < 5; iTreatment++) // msel: 3 -> 5
		{
			if(rop->llwarn[iTreatment]  != 0 
				&& rop->llwarn[iTreatment]!=22502 
				&& rop->llwarn[iTreatment]!=22504 
				&& rop->llwarn[iTreatment]!=22505 
				&& rop->llwarn[iTreatment]!=22507 
				
				
				)continue;
			if( iTreatment == MONO_LIME || iTreatment == MONO_CARBIDE)
				continue; // before the loop did not over these (limit 2, MONO_... = 3, 4) 

			if (!carbavl&& (iTreatment == ECO || iTreatment == CO_CARBIDE))
				continue;
			if (iTreatment == CO_CARBIDE || iTreatment == ECO)
			{
				mvmax = rip.Mat[CARBIDE].AddRateMax/rip.Mat[MAGNESIUM].AddRateMin;
				mvmin = rip.Mat[CARBIDE].AddRateMin/rip.Mat[MAGNESIUM].AddRateMax;
			}
			else 
			{
				mvmax = rip.Mat[LIME].AddRateMax/rip.Mat[MAGNESIUM].AddRateMin;
				mvmin = rip.Mat[LIME].AddRateMin/rip.Mat[MAGNESIUM].AddRateMax;
			}


			if (mvmax>rip.Pat[iTreatment].CoRel+0.5)
				mvmax=rip.Pat[iTreatment].CoRel+0.5;
			if (mvmin<rip.Pat[iTreatment].CoRel-0.5)
				mvmin=rip.Pat[iTreatment].CoRel-0.5;
			if (mvmax<mvmin)
				mvmax=mvmin;

			if (check(mvmax, 1., 10.) )
			{
					rop->llwarn[iTreatment]  = 22415;
					continue;
			}
			if (check(mvmin, 1., mvmax)  )
			{
					rop->llwarn[iTreatment]  = 22416;
					continue;
			}
			if (check(mvmax - mvmin, 0., 10.) )
			{
					rop->llwarn[iTreatment]  = 22417;
					continue;
			}





			// Find mv with minimum price: start from minium injection relation mv and then step-wise
			// increment 
			mv = mvmin;
			dmv=.5;
			int k;
			for (j = 0; j < 10; j++)
			{
				for (k = 0; k<2|| (mv<mvmax	&& ((rip.Strt.bPriceOptimum && priceold >= price)|| (!rip.Strt.bPriceOptimum && mv<rip.Pat[iTreatment].CoRel)|| (ddur < 0 && duration > maxduration))
					&& (ddur<0 || duration <= maxduration)); mv += dmv, k++)
				{
					// continue as long as ( price drops OR (duration drops while there is time-violation))
					// AND (duration is below max. OR duration drops)
					double mgTCorrected, mgTCorrected2, Tfak;
					durationold = duration;
					priceold = price;

					// Interpolated value from base value table
					mg = mgBaseValue;
					// Correction acc. to deviating blowing relation and material composition
					// Material composition related to Mg 97 = 97%Mg and CAD70 = 70% CaC2
					if (iTreatment == CO_CARBIDE || iTreatment == ECO)
						mg *=(rip.Bvt.BlowingRelation + seven)/ (seven/mfak + mv*seven/rip.Mat[CARBIDE].MgEqui/cfak);
					else
						mg *=(rip.Bvt.BlowingRelation + seven)/ (seven/mfak + seven/rip.Mat[LIME].MgEqui*mv/lfak);


					// Temperature correction Mg

					if ((proz = interpol(mv, rip.TCorrMg.CoRel, rip.TCorrMg.Corr, TEMPCORR_MG_ROWS)) != 0)
					{
						proz *=(1370.-Temp_iron)/10.;

						mgTCorrected = mg* (1.-proz/100);
						// efficiency change from 7 (in relation to Carbide)
						Tfak = 7.* (mg/mgTCorrected - 1.);
						// Tfak=(mg/mgTCorrected*(rip.Mat[CARBIDE].MgEqui/mfak+mv/cfak)-mv/cfak)*mfak-7.;

						if (iTreatment == CO_CARBIDE || iTreatment == ECO)
							mgTCorrected2 = mg* (seven/mfak + seven/rip.Mat[CARBIDE].MgEqui*mv/cfak)/ ((seven+Tfak)/mfak + seven/rip.Mat[CARBIDE].MgEqui*mv/cfak);
						else
							// 07-10-2003-Hismelt	mgTCorrected2=mg*(7./mfak+rip.Mat[CARBIDE].MgEqui/rip.Mat[LIME].MgEqui*mv/lfak)/((7.+Tfak)/mfak+rip.Mat[CARBIDE].MgEqui/rip.Mat[LIME].MgEqui*mv/lfak);
							mgTCorrected2 = mg* (seven/mfak+ seven/rip.Mat[LIME].MgEqui*mv/lfak)/ ((seven+Tfak)/mfak+ seven/rip.Mat[LIME].MgEqui*mv/lfak);

						mg = mgTCorrected2;
					}
					else 
					{
							rop->llwarn[iTreatment]  = 22604;
						// rop->cWarning[iwarn++]="Final Sulphur values in Base-Value-Table out of order";
						goto afterOneTreatment;
					}	

					// Correction for co-lime according to final sulphur

					if (iTreatment == CO_LIME && rip.dur[0]>0.&&rip.dur[1]>0.)
					{
						double CorrLime;
						// correction=KOEFF*S-aim^EXPO
						CorrLime = rip.dur[0]/*KOEFF*/*exp(log(Aim_sulphur)*rip.dur[1]/*EXPO*/);
						mg *= CorrLime;
					}



					carbide = mv*mg; // variable carbide stands also for lime
					if (carbide*Amt_iron/1000.<10.)
						carbide = carbide;
					// Temperature correction Carbide (nothing like this for lime!)
					/*	proz = interpol(Temp_iron, rip.TCorrCarb.Temp, rip.TCorrCarb.Corr, TEMPCORR_CARB_ROWS);



					carbide = mv*mg* (1.-proz/100.);
					mg = carbide/mv;
					*/

					// Here calculate with max. Rate to know the minimum duration; later actual time
					// and check vs. rate: reduce rate to standard, if possible.


					// Determine the max permissible Mg-Rate with regard to the Ca-Rate
					MgRateMax = rip.Mat[MAGNESIUM].AddRateMax;
					proz = interpol(Freeboard, rip.Freebd.Fbrd, rip.Freebd.MgRate, 2);
					MgRateMax *= proz/100.;
					if (MgRateMax < rip.Mat[MAGNESIUM].AddRateMin)
					{
						rop->llwarn[iTreatment]  = 22603;
						// rop->cWarning[iwarn++]="Max. permissible Mg-Rate due to freeboard out of range";
						MgRateMax = rip.Mat[MAGNESIUM].AddRateMin;
					}

					if (carbavl)
					{
						if (mv*MgRateMax > rip.Mat[CARBIDE].AddRateMax)
							MgRateMax = rip.Mat[CARBIDE].AddRateMax/mv;
					}
					else 
					{// 7-10-2003-Hismelt 
						if (mv*MgRateMax > rip.Mat[LIME].AddRateMax)
							MgRateMax = rip.Mat[LIME].AddRateMax/mv;
					}


					// The corresponding rate of carbide must be higher than its minimum value. Adap mv accordingly!
					if (mv*MgRateMax < rip.Mat[CARBIDE].AddRateMin)
					{
						mv = rip.Mat[CARBIDE].AddRateMin/MgRateMax;
						if (mv > mvmax)
							mv = mvmax;
					}

					CarbideRateMax = mv*MgRateMax;


					// Carbide for concluding  mono-phase
					// = carbide for co-carbide (mono3)
					// = lime for co-lime (mono3)
					// = lime for eco (mono4)

					carbidemono3 = interpol(mg, rip.CMono3.Mg, rip.CMono3.Carbide, 5);
					if (iTreatment == CO_CARBIDE)
					{
						// Check if above min-amount
						if (carbidemono3 < rip.Pat[CO_CARBIDE].MinCarbide/ (Amt_iron/1000.))
							carbidemono3 = rip.Pat[CO_CARBIDE].MinCarbide/ (Amt_iron/1000.);
						// Carbide for beginning mono-phase
						carbidemono2 = rip.Pat[CO_CARBIDE].FixedCarbide/ (Amt_iron/1000.);
						// Price
						price = rip.Mat[MAGNESIUM].Price/1000.*mg + rip.Mat[CARBIDE].Price/1000.* (carbide + carbidemono2 + carbidemono3);
					}
					else if (iTreatment == CO_LIME)
					{
						if (carbidemono3 < rip.Pat[CO_LIME].MinLime/ (Amt_iron/1000.))
							carbidemono3 = rip.Pat[CO_LIME].MinLime/ (Amt_iron/1000.);
						carbidemono2 = rip.Pat[CO_LIME].FixedLime/ (Amt_iron/1000.);
						price = rip.Mat[MAGNESIUM].Price/1000.*mg + rip.Mat[LIME].Price/1000.* (carbide + carbidemono2 + carbidemono3);
					}
					else if (iTreatment == ECO)
					{
						// Bhushan: just minimum amount according to pattern
						//if (carbidemono3 < rip.Pat[ECO].MinLime/ (Amt_iron/1000.))
							carbidemono3 = rip.Pat[ECO].MinLime/ (Amt_iron/1000.);
						carbidemono2 = rip.Pat[ECO].FixedLime/ (Amt_iron/1000.);
						carbidemono3ECO = (SWITCHDUR[4] + 0.5*SWITCHDUR[5])*CarbideRateMax/ (Amt_iron/1000.);
						carbidemono2ECO = (SWITCHDUR[2] + 0.5*SWITCHDUR[1])*CarbideRateMax/ (Amt_iron/1000.);

						// Bhushan
						carbidemono3ECO = carbidemono3/2.;
						carbidemono2ECO = carbidemono3/2.;

						price = rip.Mat[MAGNESIUM].Price/1000.*mg	+ rip.Mat[CARBIDE].Price/1000.*carbide
							+ rip.Mat[LIME].Price/1000.* (carbidemono2 + carbidemono3);
					}


					// Duration of Co-Phase

					// Total blowing duration
					// Co-Phase
					duration = mg/MgRateMax* (Amt_iron/1000.);
					// Mono2+3 
					duration +=(carbidemono2 + carbidemono3)/ (mv*MgRateMax)* (Amt_iron/1000.);
					duration += rip.dAvgDur;// Handling etc.

					if (iTreatment == ECO)
						duration += SWITCHDUR[4] + SWITCHDUR[5];

					// Slag calculation

					// Magnesium-Slag
					// efficiency Mg:

					dS = rip.Strt.dCont_sulphur - Aim_sulphur;
					EtaMg = dS*rip.Mat[LIME].MgEqui/ (rip.Mat[LIME].MgEqui + mv)/32./mgBaseValueSav*34./1000.;
					MgS = EtaMg* (mg + mgprev)* (24.+32.)/24.;
					MgO = ((1.-EtaMg)* (mg + mgprev) - 0.01)* (24.+16.)/24.;

					// Calcium slag
					if (iTreatment == CO_CARBIDE)
					{
						EtaCa = dS * rip.Bvt.BlowingRelation / (rip.Mat[CARBIDE].MgEqui + rip.Bvt.BlowingRelation) / 32. / (rip.Bvt.BlowingRelation*mgBaseValueSav) * 64. / 1000.;
						CaS = EtaCa * (carbide + carbideprev) * 72. / 64.;
						CaO = (1 - EtaCa) * (carbide + carbidemono2 + carbidemono3 + carbideprev + limeprev) * 56. / 64;
						Cfree = 0.3 * (1 - EtaCa) * (carbide + carbidemono2 + carbidemono3) * 24. / 60.;
					}
					else if (iTreatment == CO_LIME)
					{
						EtaCa = dS * rip.Bvt.BlowingRelation*rip.Mat[LIME].MgEqui/rip.Mat[CARBIDE].MgEqui / (rip.Mat[LIME].MgEqui +rip.Mat[LIME].MgEqui/rip.Mat[CARBIDE].MgEqui* rip.Bvt.BlowingRelation) / 32. / (rip.Bvt.BlowingRelation*mgBaseValueSav) * 64. / 1000.;
						CaS = EtaCa * (carbide + limeprev + carbideprev) * 72. / 56.;
						CaO = (1 - EtaCa) * (carbide + carbidemono2 + carbidemono3 + limeprev + carbideprev);
						Cfree = 0.;
					}
					if (iTreatment == ECO)
					{
						EtaCa = dS * rip.Bvt.BlowingRelation / (rip.Mat[CARBIDE].MgEqui + rip.Bvt.BlowingRelation) / 32. / (rip.Bvt.BlowingRelation*mgBaseValueSav) * 64. / 1000.;
						CaS = EtaCa * (carbide + carbideprev + limeprev) * 72. / 64.;
						CaO = (1 - EtaCa) * (carbide* 56. / 64 + carbidemono2 + carbidemono3 + carbideprev + limeprev);
						Cfree = 0.3 * (1 - EtaCa) * carbide * 24. / 60.;
					}

					SlagAmount = (MgS + MgO + CaO + CaS + Cfree)* (Amt_iron/1000.) + rip.Strt.dAmt_slag + rip.Strt.dAmt_soda;
					if (rip.dur[2]>0.&&rip.dur[2]<100.) // rip.dur[2]=FELOSS
						SlagAmount /=(1.-rip.dur[2]/100.);// rip.dur[2]=FELOSS

					DurationDeslagging = interpol(SlagAmount, rip.SlgDur.Slag, rip.SlgDur.Duration, 4);

					// Correction of Carbide mono2 according to total slag amount (only if no previous addition)

					if (iTreatment == CO_CARBIDE && carbideprev == 0.)
					{
						//||iTreatment==ECO){
						proz = interpol(SlagAmount, rip.CCorrSlag.Slag, rip.CCorrSlag.Corr, 4);
						carbidemono2 *=(1.+proz/100.);
					}

					duration += DurationDeslagging;
					ddur = duration - durationold; // Increase in time due to change of mv
				}
				// Price bigger or mv beyond max
				if (mv >= mvmax && j == 5)
					mv = mvmax; // last iteration over
				else 
					mv -= 2.*dmv;
				price = priceold;
				dmv /= 2.;
			}
			// check actual duration with standard rate
			// and determine flow rate

			// if  calculated mg-rate above standard value take standard value instead
			// but observe the min Carbide rate

			if (MgRateMax > rip.Mat[MAGNESIUM].AddRateStd)
			{
				duration = mg/rip.Mat[MAGNESIUM].AddRateStd* (Amt_iron/1000.);
				duration +=(carbidemono2 + carbidemono3)/ (mv*rip.Mat[MAGNESIUM].AddRateStd)* (Amt_iron/1000.);
				duration += DurationDeslagging;
				duration += rip.dAvgDur;

				MgRateMax = rip.Mat[MAGNESIUM].AddRateStd;
				// if the duration is exceeded take the max. permissible value:
				if (duration > maxduration)
				{
					if (maxduration - DurationDeslagging - rip.dAvgDur > 0)
						MgRateMax = (Amt_iron/1000.)* (mv*mg + carbidemono2 + carbidemono3)/mv/ (maxduration - DurationDeslagging - rip.dAvgDur);
					// mg/maxduration*Amt_iron;
					else
						MgRateMax = rip.Mat[MAGNESIUM].AddRateMax;

					// but not higher than max rate
					if (MgRateMax > rip.Mat[MAGNESIUM].AddRateMax)
						MgRateMax = rip.Mat[MAGNESIUM].AddRateMax;
				}
				// The corresponding rate of carbide must be higher than its minimum value. 
				if (iTreatment == CO_CARBIDE || iTreatment == ECO)
				{
					if (mv*MgRateMax < rip.Mat[CARBIDE].AddRateMin)
					{
						MgRateMax = rip.Mat[CARBIDE].AddRateMin/mv;
					}
				}	
				else 
				{// Lime
					if (mv*MgRateMax < rip.Mat[LIME].AddRateMin)
					{
						MgRateMax = rip.Mat[LIME].AddRateMin/mv;
					}
				}
				// The corresponding rate of carbide must be lower than its maximum value. 
				if (iTreatment == CO_CARBIDE || iTreatment == ECO)
				{
					if (mv*MgRateMax > rip.Mat[CARBIDE].AddRateMax)
					{
						MgRateMax = rip.Mat[CARBIDE].AddRateMax/mv;
					}
				}	
				else 
				{// Lime
					if (mv*MgRateMax > rip.Mat[LIME].AddRateMax)
					{
						MgRateMax = rip.Mat[LIME].AddRateMax/mv;
					}
				}
			}
			duration = (Amt_iron/1000.)* (mg/MgRateMax+ (carbidemono2 + carbidemono3)/mv/MgRateMax);
			duration += rip.dAvgDur;
			duration += DurationDeslagging;



			CarbideRateMax = mv*MgRateMax;

			// Co-Ratio to be rounded to aim value if close enough to this aim value
			if (fabs(rip.Pat[iTreatment].CoRel - mv) < .15)
				mv = rip.Pat[iTreatment].CoRel;

			// Flow-Rate must be 'integer' values:

			MgRateMax = floor(MgRateMax+.5);
			if (check(MgRateMax, rip.Mat[MAGNESIUM].AddRateMin, rip.Mat[MAGNESIUM].AddRateMax))
			{
				rop->llwarn[iTreatment]  = 22600;
				// rop->cWarning[iwarn++]="Magnesium-rate out of order";
			}

			//	CarbideRateMax = (double)(int)(mv*MgRateMax);
			CarbideRateMax = floor(mv*MgRateMax);

			if (MgRateMax > 0.)
				carbide = CarbideRateMax/MgRateMax*mg;


			if (iTreatment == CO_CARBIDE || iTreatment == ECO)
			{
				if (check(CarbideRateMax, rip.Mat[CARBIDE].AddRateMin*0.95, rip.Mat[CARBIDE].AddRateMax*1.05))
				{
					rop->llwarn[iTreatment]  = 22605;
					// rop->cWarning[iwarn++]="Carbide-rate out of order";
				}
			}
			else 
			{
				if (check(CarbideRateMax, rip.Mat[LIME].AddRateMin*0.95, rip.Mat[LIME].AddRateMax*1.05))
				{
					if (iwarn < MAX_NO_WARN - 1)
						rop->llwarn[iTreatment]  = 22602;
					// rop->cWarning[iwarn++]="Lime-rate out of order";
				}
			}

			// Temperature model
			// Time-dependent losses
			dTemp = duration*rip.dTempLoss;
			// Material-dependent losses: 
			if (iTreatment == CO_CARBIDE)
			{
				dTemp +=(carbidemono2 + carbidemono3 + carbide)*rip.Mat[CARBIDE].TempCoeff/1000.*100.;
				// Magnesium
				dTemp += mg*rip.Mat[MAGNESIUM].TempCoeff/ (Amt_iron/1000.)/1000.*100.;
			}
			else if (iTreatment == CO_LIME)
			{
				dTemp +=(carbidemono2 + carbidemono3 + carbide)*rip.Mat[LIME].TempCoeff/1000.*100.;
				// Magnesium
				dTemp += mg*rip.Mat[MAGNESIUM].TempCoeff/ (Amt_iron/1000.)/1000.*100.;
			}
			else if (iTreatment == ECO)
			{
				dTemp +=(carbidemono2 + carbidemono3)*rip.Mat[LIME].TempCoeff/1000.*100.;
				dTemp +=(carbide)*rip.Mat[CARBIDE].TempCoeff/1000.*100.;
				// Magnesium
				dTemp += mg*rip.Mat[MAGNESIUM].TempCoeff/ (Amt_iron/1000.)/1000.*100.;
			}


			// set output variables

			rop->dCost[iTreatment] = price* (Amt_iron/1000.);

			rop->dDurationDeslagging[iTreatment] = DurationDeslagging;

			rop->CalcFlow[iTreatment].dMagnesium[CO] = MgRateMax;

			if (iTreatment == CO_CARBIDE || iTreatment == ECO)
			{
				rop->CalcFlow[iTreatment].dCarbide[CO] = CarbideRateMax;
				rop->CalcFlow[iTreatment].dLime[CO] = 0.;

				rop->CalcAmount[iTreatment].dMagnesium[CO] = mg* (Amt_iron/1000.);
				rop->CalcAmount[iTreatment].dCarbide[CO] = carbide* (Amt_iron/1000.);
				rop->CalcAmount[iTreatment].dLime[CO] = 0.;
			}
			else 
			{ // CO_LIME
				rop->CalcFlow[iTreatment].dLime[CO] = CarbideRateMax;
				rop->CalcFlow[iTreatment].dCarbide[CO] = 0.;

				rop->CalcAmount[iTreatment].dMagnesium[CO] = mg* (Amt_iron/1000.);
				rop->CalcAmount[iTreatment].dLime[CO] = carbide* (Amt_iron/1000.);
				rop->CalcAmount[iTreatment].dCarbide[CO] = 0.;

				if (carbide*Amt_iron/1000.<10.)
					carbide = carbide;
			}

			if (iTreatment == CO_CARBIDE || iTreatment == CO_LIME)
			{
				rop->CalcFlow[iTreatment].dLime[MONO1] = 0.;
				rop->CalcFlow[iTreatment].dMagnesium[MONO1] = 0.;
				rop->CalcFlow[iTreatment].dCarbide[MONO1] = 0.;

				rop->CalcAmount[iTreatment].dCarbide[MONO1] = 0.;
				rop->CalcAmount[iTreatment].dMagnesium[MONO1] = 0.;
				rop->CalcAmount[iTreatment].dLime[MONO1] = 0.;
			}
			else 
			{// ECO
				rop->CalcFlow[iTreatment].dLime[MONO1] = CarbideRateMax;// + MgRateMax;
				rop->CalcFlow[iTreatment].dMagnesium[MONO1] = 0.;
				rop->CalcFlow[iTreatment].dCarbide[MONO1] = 0.;

				rop->CalcAmount[iTreatment].dCarbide[MONO1] = 0.;
				rop->CalcAmount[iTreatment].dMagnesium[MONO1] = 0.;
				rop->CalcAmount[iTreatment].dLime[MONO1] = carbidemono2* (Amt_iron/1000.);
			}

			if (iTreatment == CO_CARBIDE)
			{
				rop->CalcFlow[iTreatment].dLime[MONO2] = 0.;
				rop->CalcFlow[iTreatment].dMagnesium[MONO2] = 0.;
				rop->CalcFlow[iTreatment].dCarbide[MONO2] = rip.Mat[CARBIDE].AddRateStdMono;// CarbideRateMax ;//+ MgRateMax;

				rop->CalcAmount[iTreatment].dCarbide[MONO2] = carbidemono2* (Amt_iron/1000.);
				rop->CalcAmount[iTreatment].dMagnesium[MONO2] = 0.;
				rop->CalcAmount[iTreatment].dLime[MONO2] = 0.;
			}
			else if (iTreatment == CO_LIME)
			{
				//
				rop->CalcFlow[iTreatment].dLime[MONO2] = CarbideRateMax ;//+ MgRateMax;
				rop->CalcFlow[iTreatment].dMagnesium[MONO2] = 0.;
				rop->CalcFlow[iTreatment].dCarbide[MONO2] = 0.;

				rop->CalcAmount[iTreatment].dCarbide[MONO2] = 0.;
				rop->CalcAmount[iTreatment].dMagnesium[MONO2] = 0.;
				rop->CalcAmount[iTreatment].dLime[MONO2] = carbidemono2* (Amt_iron/1000.);
			}
			else 
			{// ECO
				rop->CalcFlow[iTreatment].dLime[MONO2] = 0.;
				rop->CalcFlow[iTreatment].dMagnesium[MONO2] = 0.;
				rop->CalcFlow[iTreatment].dCarbide[MONO2] = CarbideRateMax ;//+ MgRateMax;

				rop->CalcAmount[iTreatment].dCarbide[MONO2] = carbidemono2ECO* (Amt_iron/1000.);
				rop->CalcAmount[iTreatment].dMagnesium[MONO2] = 0.;
				rop->CalcAmount[iTreatment].dLime[MONO2] = 0.;
			}


			if (iTreatment == CO_CARBIDE)
			{
				rop->CalcFlow[iTreatment].dLime[MONO3] = 0.;
				rop->CalcFlow[iTreatment].dMagnesium[MONO3] = 0.;
				rop->CalcFlow[iTreatment].dCarbide[MONO3] = rip.Mat[CARBIDE].AddRateStdMono;//CarbideRateMax ;//+ MgRateMax;

				rop->CalcAmount[iTreatment].dCarbide[MONO3] = carbidemono3* (Amt_iron/1000.);
				rop->CalcAmount[iTreatment].dMagnesium[MONO3] = 0.;
				rop->CalcAmount[iTreatment].dLime[MONO3] = 0.;
			}
			else if (iTreatment == CO_LIME)
			{
				//
				rop->CalcFlow[iTreatment].dLime[MONO3] = CarbideRateMax ;//+ MgRateMax;
				rop->CalcFlow[iTreatment].dMagnesium[MONO3] = 0.;
				rop->CalcFlow[iTreatment].dCarbide[MONO3] = 0.;

				rop->CalcAmount[iTreatment].dCarbide[MONO3] = 0.;
				rop->CalcAmount[iTreatment].dMagnesium[MONO3] = 0.;
				rop->CalcAmount[iTreatment].dLime[MONO3] = carbidemono3* (Amt_iron/1000.);
			}
			else 
			{// ECO
				rop->CalcFlow[iTreatment].dLime[MONO3] = 0.;
				rop->CalcFlow[iTreatment].dMagnesium[MONO3] = 0.;
				rop->CalcFlow[iTreatment].dCarbide[MONO3] = CarbideRateMax ;//+ MgRateMax;

				rop->CalcAmount[iTreatment].dCarbide[MONO3] = carbidemono3ECO* (Amt_iron/1000.);
				rop->CalcAmount[iTreatment].dMagnesium[MONO3] = 0.;
				rop->CalcAmount[iTreatment].dLime[MONO3] = 0.;
			}	

			if (iTreatment == CO_CARBIDE || iTreatment == CO_LIME)
			{
				rop->CalcFlow[iTreatment].dLime[MONO4] = 0.;
				rop->CalcFlow[iTreatment].dMagnesium[MONO4] = 0.;
				rop->CalcFlow[iTreatment].dCarbide[MONO4] = 0.;

				rop->CalcAmount[iTreatment].dCarbide[MONO4] = 0.;
				rop->CalcAmount[iTreatment].dMagnesium[MONO4] = 0.;
				rop->CalcAmount[iTreatment].dLime[MONO4] = 0.;
			}
			else 
			{ // ECO
				rop->CalcFlow[iTreatment].dLime[MONO4] = CarbideRateMax ;//+ MgRateMax;
				rop->CalcFlow[iTreatment].dMagnesium[MONO4] = 0.;
				rop->CalcFlow[iTreatment].dCarbide[MONO4] = 0.;

				rop->CalcAmount[iTreatment].dCarbide[MONO4] = 0.;
				rop->CalcAmount[iTreatment].dMagnesium[MONO4] = 0.;
				rop->CalcAmount[iTreatment].dLime[MONO4] = carbidemono3* (Amt_iron/1000.);
			}


			rop->dTemperatureAfter[iTreatment] = Temp_iron - dTemp;

			rop->dDuration[iTreatment] = duration;
			rop->dSlagAmount[iTreatment] = SlagAmount;


			//  Calculate Iron-loss

			/*	int iphase;

			// Total amount desulphurizer:
			for (iphase = 0, TotalAmountDS = 0.; iphase <= 4; iphase++)
			TotalAmountDS += rop->CalcAmount[iTreatment].dCarbide[iphase] + rop->CalcAmount[iTreatment].dLime[iphase] + rop->CalcAmount[iTreatment].dMagnesium[iphase];
			SlagBefore = (rip.Strt.dAmt_slag + rip.Strt.dAmt_soda)/ (Amt_iron/1000.);// kg/t
			IronLoss = (FELOSS.dCoeff*SlagBefore + FELOSS.dConst)*TotalAmountDS;
			*/
afterOneTreatment:;
		}



		// Mono - Injection with Lime or Carbide

		// Material amounts

		int imat;

		// Correction according to final S


		for (iTreatment = 0; iTreatment < 5; iTreatment++)
		{
			if(rop->llwarn[iTreatment]!=0&&rop->iwarn!=0)continue;
			if( iTreatment == CO_LIME || iTreatment == CO_CARBIDE || iTreatment == ECO)
				continue; // before the loop did not over these (start 3, MONO_... = 3, 4) 

			if (iTreatment == MONO_CARBIDE)
			{
				imat = CARBIDE;
				carbide = cfak*mcorr[imat]* (seven+rip.Bvt.BlowingRelation)*mgBaseValue;// Carbide
				// Temperature correction Carbide (nothing like this for lime!)
				proz = interpol(Temp_iron, rip.TCorrCarb.Temp, rip.TCorrCarb.Corr, TEMPCORR_CARB_ROWS);
				carbide *=(1.-proz/100.);
			}
			else 
			{
				imat = LIME;
				// 07-10-2003-Hismelt: carbide=rip.Mat[LIME].MgEqui/rip.Mat[CARBIDE].MgEqui*mcorr[imat]*(7.+rip.Bvt.BlowingRelation)*mgBaseValue;//Lime
				carbide = rip.Mat[LIME].MgEqui/seven*mcorr[imat]* (seven+rip.Bvt.BlowingRelation)*mgBaseValue;// Lime
			}



			// Slag amount

			if (iTreatment == MONO_CARBIDE)
			{
				EtaCa = dS * rip.Bvt.BlowingRelation / (rip.Mat[CARBIDE].MgEqui + rip.Bvt.BlowingRelation) 
					/ 32. / (rip.Bvt.BlowingRelation*mgBaseValueSav) * 64. / 1000.;

				CaS = EtaCa * (carbide + carbideprev) * 72. / 64.; // carbideprev= previous addition
				CaO = (1 - EtaCa) * (carbide + carbideprev + limeprev) * 56. / 64;
				Cfree = 0.3 * (1 - EtaCa) * (carbide + carbideprev + limeprev) * 24. / 60.;
			}
			else 
			{ // MONO_LIME
				EtaCa = dS * rip.Bvt.BlowingRelation / (rip.Mat[LIME].MgEqui + rip.Bvt.BlowingRelation) 
					/ 32. / (rip.Bvt.BlowingRelation*mgBaseValueSav) * 64. / 1000.;
				CaS = EtaCa * (carbide + limeprev + carbideprev) * 72. / 56.; // carbideprev= previous addition
				CaO = (1 - EtaCa) * (carbide + limeprev + carbideprev);
				Cfree = 0.;
			}

			SlagAmount = (CaO + CaS + Cfree)* (Amt_iron/1000.) + rip.Strt.dAmt_slag + rip.Strt.dAmt_soda;

			if (rip.dur[2]/*FELOSS*/>0.&&rip.dur[2]/*FELOSS*/<100.)
				SlagAmount /=(1.-rip.dur[2]/*FELOSS*// 100.);


			DurationDeslagging = interpol(SlagAmount, rip.SlgDur.Slag, rip.SlgDur.Duration, 4);

			// Treatment duration incl. deslagging etc.

			CarbideRateMax = rip.Mat[imat].AddRateStdMono;
			duration = carbide* (Amt_iron/1000.)/CarbideRateMax;

			maxdurblowing = maxduration - DurationDeslagging - rip.dAvgDur;

			if (duration > maxdurblowing)
			{
				if (maxdurblowing > 0.)
				{
					CarbideRateMax = carbide/maxdurblowing* (Amt_iron/1000.);
					if (CarbideRateMax > rip.Mat[imat].AddRateMaxMono)
						CarbideRateMax = rip.Mat[imat].AddRateMaxMono;
				}
				else
					CarbideRateMax = rip.Mat[imat].AddRateMaxMono;

				duration = carbide/CarbideRateMax* (Amt_iron/1000.);
			}

			duration += DurationDeslagging + rip.dAvgDur;

			// Temperature model

			// Time-dependent losses
			dTemp = duration*rip.dTempLoss;
			// Material-dependent losses: 
			dTemp += carbide*rip.Mat[imat].TempCoeff/1000.*100.;


			// Costs
			price = rip.Mat[imat].Price/1000.*carbide;

			// set output variables
			if (iTreatment == MONO_CARBIDE)
			{
				rop->CalcAmount[iTreatment].dCarbide[MONO4] = carbide* (Amt_iron/1000.);
				rop->CalcAmount[iTreatment].dMagnesium[MONO4] = 0.;
				rop->CalcAmount[iTreatment].dLime[MONO4] = 0.;

				rop->CalcFlow[iTreatment].dLime[MONO4] = 0.;
				rop->CalcFlow[iTreatment].dMagnesium[MONO4] = 0.;
				rop->CalcFlow[iTreatment].dCarbide[MONO4] = CarbideRateMax;
			}
			else 
			{
				rop->CalcAmount[iTreatment].dCarbide[MONO4] = 0.;
				rop->CalcAmount[iTreatment].dMagnesium[MONO4] = 0.;
				rop->CalcAmount[iTreatment].dLime[MONO4] = carbide* (Amt_iron/1000.);

				rop->CalcFlow[iTreatment].dLime[MONO4] = CarbideRateMax;
				rop->CalcFlow[iTreatment].dMagnesium[MONO4] = 0.;
				rop->CalcFlow[iTreatment].dCarbide[MONO4] = 0.;
			}



			rop->dTemperatureAfter[iTreatment] = Temp_iron - dTemp;


			rop->dDuration[iTreatment] = duration;

			rop->dSlagAmount[iTreatment] = SlagAmount;
			rop->dDurationDeslagging[iTreatment] = DurationDeslagging;
			rop->dCost[iTreatment] = price* (Amt_iron/1000.);
			//  Calculate Iron-loss
			/*	int iphase;

			// Total amount desulphurizer:
			for (iphase = 0, TotalAmountDS = 0.; iphase <= 4; iphase++)
			TotalAmountDS += rop->CalcAmount[iTreatment].dCarbide[iphase] + rop->CalcAmount[iTreatment].dLime[iphase] + rop->CalcAmount[iTreatment].dMagnesium[iphase];
			SlagBefore = (rip.Strt.dAmt_slag + rip.Strt.dAmt_soda)/ (Amt_iron/1000.);// kg/t
			IronLoss = (FELOSS.dCoeff*SlagBefore + FELOSS.dConst)*TotalAmountDS;
			*/
		}


		// Select Treatment Kind according to availability and price:

		int isort[5];

		// sort by cost
		sort(rop->dCost, isort, 5); // descending order

		// check by availability and time-condition

		for (iTreatment = 4; iTreatment >= 0; iTreatment--)
		{

			double LimeTot=rop->CalcAmount[isort[iTreatment]].dLime[CO]
			+rop->CalcAmount[isort[iTreatment]].dLime[MONO1]
			+rop->CalcAmount[isort[iTreatment]].dLime[MONO2]
			+rop->CalcAmount[isort[iTreatment]].dLime[MONO3]
			+rop->CalcAmount[isort[iTreatment]].dLime[MONO4];

			double CarbideTot=rop->CalcAmount[isort[iTreatment]].dCarbide[CO]
			+rop->CalcAmount[isort[iTreatment]].dCarbide[MONO1]
			+rop->CalcAmount[isort[iTreatment]].dCarbide[MONO2]
			+rop->CalcAmount[isort[iTreatment]].dCarbide[MONO3]
			+rop->CalcAmount[isort[iTreatment]].dCarbide[MONO4];

			double MagnesiumTot=rop->CalcAmount[isort[iTreatment]].dMagnesium[CO];

			bool CarbideAvl, LimeAvl, MagnesiumAvl;
#ifdef CONSIDERQTIES
			CarbideAvl=	rip.Strt.bAvail_carbide&&rip.Strt.dAvail_carbide>=CarbideTot;
			LimeAvl=		rip.Strt.bAvail_lime&&rip.Strt.dAvail_lime>=LimeTot;
			MagnesiumAvl=		rip.Strt.bAvail_mg&&rip.Strt.dAvail_mg>=MagnesiumTot;
#else
			CarbideAvl=	rip.Strt.bAvail_carbide		;
			LimeAvl=		rip.Strt.bAvail_lime	;
			MagnesiumAvl=		rip.Strt.bAvail_mg	;
#endif
			if (isort[iTreatment] == CO_CARBIDE)
			{
				// Check whether Mg and Carbide available
				if (!CarbideAvl||!MagnesiumAvl || rop->dDuration[isort[iTreatment]]>rip.Strt.dTimeAvail||rop->dDuration[isort[iTreatment]]<=0.0)
					continue;// next treatment type
				else 
					break;// both available
			}
			else if (isort[iTreatment] == CO_LIME)
			{
				// Check whether Mg and Lime available
				if (!LimeAvl||!MagnesiumAvl || rop->dDuration[isort[iTreatment]]>rip.Strt.dTimeAvail||rop->dDuration[isort[iTreatment]]<=0.0)
					continue;// next treatment type
				else 
					break;
			}
			else if (isort[iTreatment] == ECO)
			{
				// Check whether Mg and Lime and Carbide available
				if (!LimeAvl||!CarbideAvl||!MagnesiumAvl || rop->dDuration[isort[iTreatment]]>rip.Strt.dTimeAvail||rop->dDuration[isort[iTreatment]]<=0.0)
					continue;// next treatment type
				else 
					break;
			}
			else if (isort[iTreatment] == MONO_LIME)
			{
				// Check whether Lime available
				if (!LimeAvl || rop->dDuration[isort[iTreatment]]>rip.Strt.dTimeAvail||rop->dDuration[isort[iTreatment]]<=0.0)
					continue;// next treatment type
				else 
					break;
			}
			else if (isort[iTreatment] == MONO_CARBIDE)
			{
				// Check whether Carbide available
				if (!CarbideAvl || rop->dDuration[isort[iTreatment]]>rip.Strt.dTimeAvail||rop->dDuration[isort[iTreatment]]<=0.0)
					continue;// next treatment type
				else 
					break;
			}
			//continue; // not possible (msel: and useless :-)
		}


		double timvek[5]; // for sorting acc. to time consumption

		if (check(iTreatment, 0, 4))//if outside limits  returns false, 
			//then no treatment was found within available materials and time-timit
		{



			// now, check availability of materials only
			for (i = 0; i < 5; i++)
				timvek[i] = 1e10;

			for (iTreatment = 4; iTreatment >= 0; iTreatment--)
			{
				 double LimeTot=rop->CalcAmount[isort[iTreatment]].dLime[CO]
				+rop->CalcAmount[isort[iTreatment]].dLime[MONO1]
				+rop->CalcAmount[isort[iTreatment]].dLime[MONO2]
				+rop->CalcAmount[isort[iTreatment]].dLime[MONO3]
				+rop->CalcAmount[isort[iTreatment]].dLime[MONO4];

				 double CarbideTot=rop->CalcAmount[isort[iTreatment]].dCarbide[CO]
				+rop->CalcAmount[isort[iTreatment]].dCarbide[MONO1]
				+rop->CalcAmount[isort[iTreatment]].dCarbide[MONO2]
				+rop->CalcAmount[isort[iTreatment]].dCarbide[MONO3]
				+rop->CalcAmount[isort[iTreatment]].dCarbide[MONO4];

				 double MagnesiumTot=rop->CalcAmount[isort[iTreatment]].dMagnesium[CO];

			bool CarbideAvl, LimeAvl, MagnesiumAvl;
#ifdef CONSIDERQTIES
				CarbideAvl=	rip.Strt.bAvail_carbide&&rip.Strt.dAvail_carbide>=CarbideTot;
				LimeAvl=		rip.Strt.bAvail_lime&&rip.Strt.dAvail_lime>=LimeTot;
				MagnesiumAvl=		rip.Strt.bAvail_mg&&rip.Strt.dAvail_mg>=MagnesiumTot;
#else
				CarbideAvl=	rip.Strt.bAvail_carbide		;
				LimeAvl=		rip.Strt.bAvail_lime	;
				MagnesiumAvl=		rip.Strt.bAvail_mg	;
#endif



				if (carbavl && isort[iTreatment] == CO_CARBIDE)
				{
					// Check whether Mg and Carbide available
					if (!CarbideAvl||!MagnesiumAvl)
						continue;// next treatment type
					else 
						timvek[isort[iTreatment]] = rop->dDuration[isort[iTreatment]];
				}
				else if (isort[iTreatment] == CO_LIME)
				{
					// Check whether Mg and Lime available
					if (!LimeAvl||!MagnesiumAvl)
						continue;// next treatment type
					else 
						timvek[isort[iTreatment]] = rop->dDuration[isort[iTreatment]];
				}
				else if (carbavl && isort[iTreatment] == ECO)
				{
					// Check whether Mg and Lime and Carbide available
					if (!LimeAvl||!CarbideAvl||!MagnesiumAvl)
						continue;// next treatment type
					else 
						timvek[isort[iTreatment]] = rop->dDuration[isort[iTreatment]];
				}
				else if (isort[iTreatment] == MONO_LIME)
				{
					// Check whether Lime available
					if (!LimeAvl)
						continue;// next treatment type
					else 
						timvek[isort[iTreatment]] = rop->dDuration[isort[iTreatment]];
				}
				else if (carbavl && isort[iTreatment] == MONO_CARBIDE)
				{
					// Check whether Carbide available
					if (!CarbideAvl)
						continue;// next treatment type
					else 
						timvek[isort[iTreatment]] = rop->dDuration[isort[iTreatment]];
				}
				continue; // not possible
			}

			//+++++++++++Force mono available+++++++++++++++++
			//if (monoforce == 1)
			//{
			//		rop->iTreatmentKind = MONO_LIME;
			//
			////		CalculationError = 2; //global
			//		return 0;
			//}
			//
			sort(timvek, isort, 5); // descending order
			if (timvek[isort[4]]<1e10)
			{
				rop->iTreatmentKind = isort[4];
				for (iTreatment = 4; iTreatment >= 0; iTreatment--)

					rop->llwarn[iTreatment]  = 22606; // duration exceeded
				//		CalculationError = 2; //global
				return 0;
			}
			else 
			{
				rop->iwarn  = 22601;
				// rop->cWarning[iwarn++]="No Treatment possible: neither Carbide nor Lime available";
				return -1;
			}
		}

		// solution without time violation:
		//CalculationError = 1; //global
		rop->iTreatmentKind = isort[iTreatment];
		//rop->llwarn[iTreatment] = 0; //2000;//aus irgendeinem Grund nimmt er diesen Value nicht
	}

	//+++++++++++Force mono available+++++++++++++++++ hier nochmal, da er tielweise rausgesprungen ist
	//if (monoforce == 1)
	//{
	//		rop->iTreatmentKind = MONO_LIME;
	//
	////		CalculationError = 2; //global
	//		return 0;
	//}

	return 0; // success
}                    
//**************************************************
//*End of model
//**************************************************
