#ifndef _TELCOM_OUT_H_
#define _TELCOM_OUT_H_
/*
****************************************
 File: Telcom_Out

 TAM (Telegram Access Model) Classes
 generated on Mon Sep 16 11:10:48 IST 2019

*****************************************/

#include "tam.h"
#include <vector>
#include <string>
using std::string;
// user type: HeaderType
class TEHeaderType: public GeneratedTlg
{
public:
	IntegerVal MessageLength;
	IntegerVal MessageId;
	IntegerVal MessageCount;
	IntegerVal UnitNo;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: Head
class Head: public GeneratedTlg
{
public:
	IntegerVal MessageLength;
	IntegerVal MessageId;
	IntegerVal MessageCount;
	IntegerVal UnitNo;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: L2LF00
class L2LF00: public GeneratedTlg
{
public:
	TEHeaderType Header;
	StringVal Status;
	StringVal RcvMsgId;
	StringVal ErrInf;
	StringVal ErrMess;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: L2LF01
class L2LF01: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: L2LF01_WATCH_DOG
class L2LF01_WATCH_DOG: public GeneratedTlg
{
public:
	IntegerVal MessageLength;
	IntegerVal MessageId;
	IntegerVal MessageCount;
	IntegerVal UnitNo;
	StringVal CreateTime;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: L2LF03
class L2LF03: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	StringVal ProdOrderId;
	StringVal SteelGradeCode;
	std::vector<IntegerVal> ProdDate;
	std::vector<IntegerVal> DepTime;
	IntegerVal CarNo;
	StringVal LadleId;
	StringVal ShiftCode;
	StringVal CrewCode;
	StringVal OperCode;
	StringVal RouteCode;
	NumberVal AimTemp;
	IntegerVal UpdateFlag;
	NumberVal LadleTareWeight;
	NumberVal LadleGrossWeight;
	NumberVal SteelWeight;
	StringVal HeatIdCust;
	StringVal TreatIdCust;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: L2LF05
class L2LF05: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	IntegerVal StirrActivity;
	IntegerVal StirrGasType;
	IntegerVal StirrInt;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: L2LF06
class L2LF06: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: L2LF07
class L2LF07: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	IntegerVal ModeElec;
	IntegerVal ModeStirr;
	IntegerVal ModeMat;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: L2LF20
class L2LF20: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	IntegerVal AimVoltTap;
	IntegerVal AimCurveNo;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: L2LF20_VOLTAGE_TAP
class L2LF20_VOLTAGE_TAP: public GeneratedTlg
{
public:
	IntegerVal MessageLength;
	IntegerVal MessageId;
	IntegerVal MessageCount;
	IntegerVal UnitNo;
	StringVal CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	IntegerVal AimVoltTap;
	IntegerVal AimCurveNo;
	IntegerVal Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: L2LF22
class L2LF22: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: L2LF23
class L2LF23: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	IntegerVal ActionFlag;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: L2LF25
class L2LF25: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	IntegerVal Type;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: L2LF30
class L2LF30: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	std::vector<IntegerVal> Enabled;
	std::vector<NumberVal> RemDurStep;
	std::vector<IntegerVal> ElecEnergyStep;
	std::vector<IntegerVal> TempEndStep;
	std::vector<IntegerVal> AimVoltTap;
	std::vector<IntegerVal> AimCurveNo;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: L2LF30_ELEC_PATT
class L2LF30_ELEC_PATT: public GeneratedTlg
{
public:
	class TEENTRY: public GeneratedTlg
	{
	public:
		IntegerVal MessageCount;
		IntegerVal MessageIndex;
		StringVal HeatId;
		StringVal TreatId;
		IntegerVal ActivityType;
		IntegerVal StepNo;
		IntegerVal Enabled;
		NumberVal RemDurStep;
		IntegerVal ElecEnergyStep;
		IntegerVal TempEndStep;
		IntegerVal AimVoltTap;
		IntegerVal AimCurveNo;
		IntegerVal Spare_1;
		IntegerVal Spare_2;
		void load(std::istream & in, const string &_path_="") throw (ETAMError);
		void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
	};
	IntegerVal MessageLength;
	IntegerVal MessageId;
	IntegerVal MessageCount;
	IntegerVal UnitNo;
	StringVal CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	std::vector<TEENTRY> ENTRY;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: L2LF31
class L2LF31: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	std::vector<IntegerVal> PhaseNo;
	std::vector<IntegerVal> Enabled;
	std::vector<NumberVal> Duration;
	std::vector<IntegerVal> StirrInt;
	std::vector<NumberVal> StirrGasFlow;
	std::vector<IntegerVal> StirrGasType;
	std::vector<IntegerVal> StepPriority;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: L2LF31_STIRR_PATT
class L2LF31_STIRR_PATT: public GeneratedTlg
{
public:
	class TEENTRY: public GeneratedTlg
	{
	public:
		IntegerVal MessageCount;
		IntegerVal MessageIndex;
		StringVal HeatId;
		StringVal TreatId;
		IntegerVal PhaseNo;
		IntegerVal Enabled;
		NumberVal Duration;
		IntegerVal StirrInt;
		NumberVal StirrGasFlow;
		IntegerVal StirrGasType;
		IntegerVal StepPriority;
		IntegerVal Spare_1;
		IntegerVal Spare_2;
		void load(std::istream & in, const string &_path_="") throw (ETAMError);
		void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
	};
	IntegerVal MessageLength;
	IntegerVal MessageId;
	IntegerVal MessageCount;
	IntegerVal UnitNo;
	StringVal CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	std::vector<TEENTRY> ENTRY;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: L2LF40
class L2LF40: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	std::vector<StringVal> ParamName;
	std::vector<NumberVal> ParamValue;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: L2LF70
class L2LF70: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	IntegerVal Source;
	IntegerVal RecipeNo;
	std::vector<StringVal> MatCode;
	std::vector<IntegerVal> MatWeight;
	std::vector<IntegerVal> MatSequence;
	std::vector<IntegerVal> FeedRate;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: L2LF70_MAT_HANDL
class L2LF70_MAT_HANDL: public GeneratedTlg
{
public:
	class TEENTRY: public GeneratedTlg
	{
	public:
		IntegerVal MessageCount;
		IntegerVal MessageIndex;
		StringVal HeatId;
		StringVal TreatId;
		IntegerVal Source;
		IntegerVal RecipeNo;
		StringVal MatCode;
		IntegerVal MatWeight;
		IntegerVal MatSequence;
		IntegerVal FeedRate;
		IntegerVal Spare_1;
		IntegerVal Spare_2;
		void load(std::istream & in, const string &_path_="") throw (ETAMError);
		void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
	};
	IntegerVal MessageLength;
	IntegerVal MessageId;
	IntegerVal MessageCount;
	IntegerVal UnitNo;
	StringVal CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	std::vector<TEENTRY> ENTRY;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: L2LF71
class L2LF71: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: L2LF72
class L2LF72: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
#endif
