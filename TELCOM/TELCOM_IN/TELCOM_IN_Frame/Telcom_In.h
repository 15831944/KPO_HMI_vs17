#ifndef _TELCOM_IN_H_
#define _TELCOM_IN_H_
/*
****************************************
 File: Telcom_In

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
// telegram: LFL200
class LFL200: public GeneratedTlg
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
// telegram: LFL201
class LFL201: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal Address;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: LFL203
class LFL203: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	StringVal LadleId;
	IntegerVal CarNo;
	StringVal ProdOrderId;
	StringVal SteelGradeCode;
	NumberVal AimTemp;
	NumberVal AimWeight;
	StringVal HeatIdCust;
	StringVal TreatIdCust;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: LFL204
class LFL204: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	StringVal LadleId;
	IntegerVal CarNo;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: LFL205
class LFL205: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	StringVal LadleId;
	IntegerVal CarNo;
	IntegerVal ActionFlag;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: LFL206
class LFL206: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	IntegerVal CarNo;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: LFL209
class LFL209: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	IntegerVal CarNo;
	IntegerVal SampleType;
	IntegerVal SampleCounter;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: LFL211
class LFL211: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	IntegerVal CarNo;
	IntegerVal MeasType;
	IntegerVal MeasNo;
	NumberVal Temp;
	NumberVal ConcO2;
	NumberVal ConcAl;
	NumberVal ConcC;
	NumberVal ConcFeO;
	NumberVal ConcMnO;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: LFL212
class LFL212: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	NumberVal AimTemp;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: LFL213
class LFL213: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	std::vector<IntegerVal> AimDepTime;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: LFL217
class LFL217: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	IntegerVal CarNo;
	StringVal DelayCode;
	std::vector<IntegerVal> DelayStartTime;
	std::vector<IntegerVal> DelayEndTime;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: LFL220
class LFL220: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	IntegerVal CarNo;
	IntegerVal ModeElec;
	IntegerVal ModeStirr;
	IntegerVal ModeMat;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: LFL221
class LFL221: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	IntegerVal GantryPos;
	IntegerVal RoofPos;
	IntegerVal CarNo;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: LFL222
class LFL222: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	IntegerVal FurnBreakOn;
	IntegerVal FurnPowerOn;
	IntegerVal TapChanger;
	IntegerVal ElecPos;
	IntegerVal GantryPos;
	IntegerVal ElecHydSys;
	IntegerVal ElecVoltTap;
	IntegerVal ElecCurvNo;
	NumberVal ElecCons;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: LFL223
class LFL223: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	IntegerVal CarNo;
	IntegerVal ElecVoltTap;
	IntegerVal ElecCurvNo;
	NumberVal ElecCons;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: LFL224
class LFL224: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	IntegerVal CarNo;
	IntegerVal PlugNo;
	IntegerVal StirrGasType;
	IntegerVal StirrStat;
	IntegerVal BypassStat;
	IntegerVal PlugDefect;
	NumberVal StirrGasCons;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: LFL225
class LFL225: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	IntegerVal CarNo;
	IntegerVal StirrGasType;
	IntegerVal StirrStat;
	NumberVal StirrGasCons;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: LFL226
class LFL226: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	IntegerVal CarNo;
	std::vector<IntegerVal> StirrGasType;
	std::vector<IntegerVal> StirrInt;
	std::vector<NumberVal> FlowAct;
	std::vector<NumberVal> Pressure;
	std::vector<NumberVal> StirrGasCons;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: LFL230
class LFL230: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	IntegerVal CarNo;
	NumberVal RoofWaterInlet;
	NumberVal RoofWaterOutlet;
	NumberVal RoofWaterFlow;
	NumberVal WGWaterInlet;
	NumberVal WGWaterOutlet;
	NumberVal WGWaterFlow;
	NumberVal ElecCons;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: LFL240
class LFL240: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal ParamName;
	NumberVal ParamValue;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: LFL260
class LFL260: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	IntegerVal CarNo;
	IntegerVal Target;
	IntegerVal Source;
	IntegerVal RecipeNo;
	IntegerVal BatchStat;
	std::vector<StringVal> MatCode;
	std::vector<NumberVal> MatWeight;
	std::vector<IntegerVal> SourceNo;
	std::vector<NumberVal> FeedingRate;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: LFL261
class LFL261: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	IntegerVal ActionFlag;
	std::vector<StringVal> MatCode;
	std::vector<NumberVal> MinWeight;
	std::vector<IntegerVal> SourceNo;
	std::vector<IntegerVal> Source;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: LFL270
class LFL270: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	StringVal LadleId;
	IntegerVal WeighingStat;
	NumberVal Weight;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
// telegram: LFL281
class LFL281: public GeneratedTlg
{
public:
	TEHeaderType Header;
	std::vector<IntegerVal> CreateTime;
	StringVal HeatId;
	StringVal TreatId;
	StringVal LadleId;
	IntegerVal CarNo;
	IntegerVal StepNo;
	std::vector<IntegerVal> Spare;
	void load(std::istream & in, const string &_path_="") throw (ETAMError);
	void serialize(std::ostream & out, const string &_path_="") throw (ETAMError);
};
#endif
