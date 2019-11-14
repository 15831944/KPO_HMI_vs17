/*
****************************************
 File: Telcom_In_factory

 Telegram Factory
 generated on Mon Sep 16 11:10:48 IST 2019

*****************************************/

#include "Telcom_In_factory.h"
 Telcom_In_factory::Telcom_In_factory(
)
{
	EncodingRules * erPtr = 0;
	erPtr = erMgr.create();
	{
		erPtr->nullVal = " ";
		erPtr->trueVal = "1";
		erPtr->falseVal = "0";
		erPtr->padding = EncodingRules::padRight;
		erPtr->fillChar = ' ';
		erPtr->numFmt = "";
		erPtr->intFmt = "";
		erPtr->dtFmt = "";
	}
	erPtr->intFmt = "";
	erMgr.set("ascii", erPtr);
	create_Head();
	create_LFL200();
	create_LFL201();
	create_LFL203();
	create_LFL204();
	create_LFL205();
	create_LFL206();
	create_LFL209();
	create_LFL211();
	create_LFL212();
	create_LFL213();
	create_LFL217();
	create_LFL220();
	create_LFL221();
	create_LFL222();
	create_LFL223();
	create_LFL224();
	create_LFL225();
	create_LFL226();
	create_LFL230();
	create_LFL240();
	create_LFL260();
	create_LFL261();
	create_LFL270();
	create_LFL281();
}
void Telcom_In_factory::create_Head(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("Head");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_In_factory::create_LFL200(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("LFL200");
	builder.makeCompositeTE("Header");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	builder.endCompositeTE();
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("Status", "ascii", 2, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("RcvMsgId", "ascii", 6, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("ErrInf", "ascii", 4, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("ErrMess", "ascii", 64, erPtr);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_In_factory::create_LFL201(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("LFL201");
	builder.makeCompositeTE("Header");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	builder.endCompositeTE();
	builder.makeArrayTE("CreateTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("Address", "ascii", 20, erPtr);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_In_factory::create_LFL203(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("LFL203");
	builder.makeCompositeTE("Header");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	builder.endCompositeTE();
	builder.makeArrayTE("CreateTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("HeatId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("TreatId", "ascii", 2, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("LadleId", "ascii", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("CarNo", "binary", 4, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("ProdOrderId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("SteelGradeCode", "ascii", 12, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("AimTemp", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("AimWeight", "binary", 4, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("HeatIdCust", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("TreatIdCust", "ascii", 2, erPtr);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_In_factory::create_LFL204(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("LFL204");
	builder.makeCompositeTE("Header");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	builder.endCompositeTE();
	builder.makeArrayTE("CreateTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("HeatId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("TreatId", "ascii", 2, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("LadleId", "ascii", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("CarNo", "binary", 4, erPtr);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_In_factory::create_LFL205(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("LFL205");
	builder.makeCompositeTE("Header");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	builder.endCompositeTE();
	builder.makeArrayTE("CreateTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("HeatId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("TreatId", "ascii", 2, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("LadleId", "ascii", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("CarNo", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("ActionFlag", "binary", 4, erPtr);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_In_factory::create_LFL206(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("LFL206");
	builder.makeCompositeTE("Header");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	builder.endCompositeTE();
	builder.makeArrayTE("CreateTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("HeatId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("TreatId", "ascii", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("CarNo", "binary", 4, erPtr);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_In_factory::create_LFL209(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("LFL209");
	builder.makeCompositeTE("Header");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	builder.endCompositeTE();
	builder.makeArrayTE("CreateTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("HeatId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("TreatId", "ascii", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("CarNo", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("SampleType", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("SampleCounter", "binary", 4, erPtr);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_In_factory::create_LFL211(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("LFL211");
	builder.makeCompositeTE("Header");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	builder.endCompositeTE();
	builder.makeArrayTE("CreateTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("HeatId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("TreatId", "ascii", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("CarNo", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MeasType", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MeasNo", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("Temp", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("ConcO2", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("ConcAl", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("ConcC", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("ConcFeO", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("ConcMnO", "binary", 4, erPtr);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_In_factory::create_LFL212(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("LFL212");
	builder.makeCompositeTE("Header");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	builder.endCompositeTE();
	builder.makeArrayTE("CreateTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("HeatId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("TreatId", "ascii", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("AimTemp", "binary", 4, erPtr);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_In_factory::create_LFL213(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("LFL213");
	builder.makeCompositeTE("Header");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	builder.endCompositeTE();
	builder.makeArrayTE("CreateTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("HeatId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("TreatId", "ascii", 2, erPtr);
	builder.makeArrayTE("AimDepTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_In_factory::create_LFL217(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("LFL217");
	builder.makeCompositeTE("Header");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	builder.endCompositeTE();
	builder.makeArrayTE("CreateTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("HeatId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("TreatId", "ascii", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("CarNo", "binary", 4, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("DelayCode", "ascii", 4, erPtr);
	builder.makeArrayTE("DelayStartTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	builder.makeArrayTE("DelayEndTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_In_factory::create_LFL220(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("LFL220");
	builder.makeCompositeTE("Header");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	builder.endCompositeTE();
	builder.makeArrayTE("CreateTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("HeatId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("TreatId", "ascii", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("CarNo", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("ModeElec", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("ModeStirr", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("ModeMat", "binary", 4, erPtr);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_In_factory::create_LFL221(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("LFL221");
	builder.makeCompositeTE("Header");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	builder.endCompositeTE();
	builder.makeArrayTE("CreateTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("GantryPos", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("RoofPos", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("CarNo", "binary", 4, erPtr);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_In_factory::create_LFL222(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("LFL222");
	builder.makeCompositeTE("Header");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	builder.endCompositeTE();
	builder.makeArrayTE("CreateTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("FurnBreakOn", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("FurnPowerOn", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("TapChanger", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("ElecPos", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("GantryPos", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("ElecHydSys", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("ElecVoltTap", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("ElecCurvNo", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("ElecCons", "binary", 4, erPtr);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_In_factory::create_LFL223(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("LFL223");
	builder.makeCompositeTE("Header");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	builder.endCompositeTE();
	builder.makeArrayTE("CreateTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("HeatId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("TreatId", "ascii", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("CarNo", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("ElecVoltTap", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("ElecCurvNo", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("ElecCons", "binary", 4, erPtr);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_In_factory::create_LFL224(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("LFL224");
	builder.makeCompositeTE("Header");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	builder.endCompositeTE();
	builder.makeArrayTE("CreateTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("HeatId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("TreatId", "ascii", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("CarNo", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("PlugNo", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("StirrGasType", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("StirrStat", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("BypassStat", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("PlugDefect", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("StirrGasCons", "binary", 4, erPtr);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_In_factory::create_LFL225(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("LFL225");
	builder.makeCompositeTE("Header");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	builder.endCompositeTE();
	builder.makeArrayTE("CreateTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("HeatId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("TreatId", "ascii", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("CarNo", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("StirrGasType", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("StirrStat", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("StirrGasCons", "binary", 4, erPtr);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_In_factory::create_LFL226(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("LFL226");
	builder.makeCompositeTE("Header");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	builder.endCompositeTE();
	builder.makeArrayTE("CreateTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("HeatId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("TreatId", "ascii", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("CarNo", "binary", 4, erPtr);
	builder.makeArrayTE("StirrGasType");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(4);
	builder.makeArrayTE("StirrInt");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(3);
	builder.makeArrayTE("FlowAct");
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("", "binary", 4, erPtr);
	builder.endArrayTE(4);
	builder.makeArrayTE("Pressure");
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("", "binary", 4, erPtr);
	builder.endArrayTE(4);
	builder.makeArrayTE("StirrGasCons");
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("", "binary", 4, erPtr);
	builder.endArrayTE(4);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_In_factory::create_LFL230(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("LFL230");
	builder.makeCompositeTE("Header");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	builder.endCompositeTE();
	builder.makeArrayTE("CreateTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("HeatId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("TreatId", "ascii", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("CarNo", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("RoofWaterInlet", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("RoofWaterOutlet", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("RoofWaterFlow", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("WGWaterInlet", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("WGWaterOutlet", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("WGWaterFlow", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("ElecCons", "binary", 4, erPtr);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_In_factory::create_LFL240(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("LFL240");
	builder.makeCompositeTE("Header");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	builder.endCompositeTE();
	builder.makeArrayTE("CreateTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("ParamName", "ascii", 30, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("ParamValue", "binary", 4, erPtr);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_In_factory::create_LFL260(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("LFL260");
	builder.makeCompositeTE("Header");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	builder.endCompositeTE();
	builder.makeArrayTE("CreateTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("HeatId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("TreatId", "ascii", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("CarNo", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("Target", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("Source", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("RecipeNo", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("BatchStat", "binary", 4, erPtr);
	builder.makeArrayTE("MatCode");
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("", "ascii", 10, erPtr);
	builder.endArrayTE(10);
	builder.makeArrayTE("MatWeight");
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("", "binary", 4, erPtr);
	builder.endArrayTE(10);
	builder.makeArrayTE("SourceNo");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(10);
	builder.makeArrayTE("FeedingRate");
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("", "binary", 4, erPtr);
	builder.endArrayTE(10);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_In_factory::create_LFL261(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("LFL261");
	builder.makeCompositeTE("Header");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	builder.endCompositeTE();
	builder.makeArrayTE("CreateTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("ActionFlag", "binary", 4, erPtr);
	builder.makeArrayTE("MatCode");
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("", "ascii", 10, erPtr);
	builder.endArrayTE(20);
	builder.makeArrayTE("MinWeight");
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("", "binary", 4, erPtr);
	builder.endArrayTE(20);
	builder.makeArrayTE("SourceNo");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(20);
	builder.makeArrayTE("Source");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(20);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_In_factory::create_LFL270(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("LFL270");
	builder.makeCompositeTE("Header");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	builder.endCompositeTE();
	builder.makeArrayTE("CreateTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("HeatId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("TreatId", "ascii", 2, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("LadleId", "ascii", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("WeighingStat", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("Weight", "binary", 4, erPtr);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_In_factory::create_LFL281(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("LFL281");
	builder.makeCompositeTE("Header");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	builder.endCompositeTE();
	builder.makeArrayTE("CreateTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("HeatId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("TreatId", "ascii", 2, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("LadleId", "ascii", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("CarNo", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("StepNo", "binary", 4, erPtr);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
