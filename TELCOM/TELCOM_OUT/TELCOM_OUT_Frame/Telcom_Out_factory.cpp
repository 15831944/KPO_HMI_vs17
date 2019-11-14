/*
****************************************
 File: Telcom_Out_factory

 Telegram Factory
 generated on Mon Sep 16 11:10:48 IST 2019

*****************************************/

#include "Telcom_Out_factory.h"
 Telcom_Out_factory::Telcom_Out_factory(
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
	create_L2LF00();
	create_L2LF01();
	create_L2LF01_WATCH_DOG();
	create_L2LF03();
	create_L2LF05();
	create_L2LF06();
	create_L2LF07();
	create_L2LF20();
	create_L2LF20_VOLTAGE_TAP();
	create_L2LF22();
	create_L2LF23();
	create_L2LF25();
	create_L2LF30();
	create_L2LF30_ELEC_PATT();
	create_L2LF31();
	create_L2LF31_STIRR_PATT();
	create_L2LF40();
	create_L2LF70();
	create_L2LF70_MAT_HANDL();
	create_L2LF71();
	create_L2LF72();
}
void Telcom_Out_factory::create_Head(
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
void Telcom_Out_factory::create_L2LF00(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("L2LF00");
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
void Telcom_Out_factory::create_L2LF01(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("L2LF01");
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
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_Out_factory::create_L2LF01_WATCH_DOG(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("L2LF01_WATCH_DOG");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("CreateTime", "ascii", 23, erPtr);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_Out_factory::create_L2LF03(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("L2LF03");
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
	builder.makeStringTE("ProdOrderId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("SteelGradeCode", "ascii", 12, erPtr);
	builder.makeArrayTE("ProdDate");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	builder.makeArrayTE("DepTime");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(8);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("CarNo", "binary", 4, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("LadleId", "ascii", 4, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("ShiftCode", "ascii", 2, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("CrewCode", "ascii", 2, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("OperCode", "ascii", 6, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("RouteCode", "ascii", 20, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("AimTemp", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UpdateFlag", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("LadleTareWeight", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("LadleGrossWeight", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("SteelWeight", "binary", 4, erPtr);
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
void Telcom_Out_factory::create_L2LF05(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("L2LF05");
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
	builder.makeIntegerTE("StirrActivity", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("StirrGasType", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("StirrInt", "binary", 4, erPtr);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_Out_factory::create_L2LF06(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("L2LF06");
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
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_Out_factory::create_L2LF07(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("L2LF07");
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
void Telcom_Out_factory::create_L2LF20(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("L2LF20");
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
	builder.makeIntegerTE("AimVoltTap", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("AimCurveNo", "binary", 4, erPtr);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_Out_factory::create_L2LF20_VOLTAGE_TAP(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("L2LF20_VOLTAGE_TAP");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("CreateTime", "ascii", 23, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("HeatId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("TreatId", "ascii", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("AimVoltTap", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("AimCurveNo", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("Spare", "binary", 4, erPtr);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_Out_factory::create_L2LF22(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("L2LF22");
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
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_Out_factory::create_L2LF23(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("L2LF23");
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
	builder.makeIntegerTE("ActionFlag", "binary", 4, erPtr);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_Out_factory::create_L2LF25(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("L2LF25");
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
	builder.makeIntegerTE("Type", "binary", 4, erPtr);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_Out_factory::create_L2LF30(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("L2LF30");
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
	builder.makeArrayTE("Enabled");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(7);
	builder.makeArrayTE("RemDurStep");
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("", "binary", 4, erPtr);
	builder.endArrayTE(7);
	builder.makeArrayTE("ElecEnergyStep");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(7);
	builder.makeArrayTE("TempEndStep");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(7);
	builder.makeArrayTE("AimVoltTap");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(7);
	builder.makeArrayTE("AimCurveNo");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(7);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_Out_factory::create_L2LF30_ELEC_PATT(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("L2LF30_ELEC_PATT");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("CreateTime", "ascii", 23, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("HeatId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("TreatId", "ascii", 2, erPtr);
	builder.makeArrayTE("ENTRY");
	builder.makeCompositeTE("");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageIndex", "binary", 2, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("HeatId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("TreatId", "ascii", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("ActivityType", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("StepNo", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("Enabled", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("RemDurStep", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("ElecEnergyStep", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("TempEndStep", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("AimVoltTap", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("AimCurveNo", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("Spare_1", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("Spare_2", "binary", 4, erPtr);
	builder.endCompositeTE();
	builder.endArrayTE(7);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_Out_factory::create_L2LF31(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("L2LF31");
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
	builder.makeArrayTE("PhaseNo");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(20);
	builder.makeArrayTE("Enabled");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(20);
	builder.makeArrayTE("Duration");
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("", "binary", 4, erPtr);
	builder.endArrayTE(20);
	builder.makeArrayTE("StirrInt");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(20);
	builder.makeArrayTE("StirrGasFlow");
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("", "binary", 4, erPtr);
	builder.endArrayTE(20);
	builder.makeArrayTE("StirrGasType");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(20);
	builder.makeArrayTE("StepPriority");
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
void Telcom_Out_factory::create_L2LF31_STIRR_PATT(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("L2LF31_STIRR_PATT");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("CreateTime", "ascii", 23, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("HeatId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("TreatId", "ascii", 2, erPtr);
	builder.makeArrayTE("ENTRY");
	builder.makeCompositeTE("");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageIndex", "binary", 2, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("HeatId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("TreatId", "ascii", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("PhaseNo", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("Enabled", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("Duration", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("StirrInt", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("StirrGasFlow", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("StirrGasType", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("StepPriority", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("Spare_1", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("Spare_2", "binary", 4, erPtr);
	builder.endCompositeTE();
	builder.endArrayTE(20);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_Out_factory::create_L2LF40(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("L2LF40");
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
	builder.makeArrayTE("ParamName");
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("", "ascii", 20, erPtr);
	builder.endArrayTE(5);
	builder.makeArrayTE("ParamValue");
	erPtr = erMgr.get("binary");
	builder.makeNumberTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_Out_factory::create_L2LF70(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("L2LF70");
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
	builder.makeIntegerTE("Source", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("RecipeNo", "binary", 4, erPtr);
	builder.makeArrayTE("MatCode");
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("", "ascii", 10, erPtr);
	builder.endArrayTE(10);
	builder.makeArrayTE("MatWeight");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(10);
	builder.makeArrayTE("MatSequence");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(10);
	builder.makeArrayTE("FeedRate");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(10);
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_Out_factory::create_L2LF70_MAT_HANDL(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("L2LF70_MAT_HANDL");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageLength", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageId", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("UnitNo", "binary", 2, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("CreateTime", "ascii", 23, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("HeatId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("TreatId", "ascii", 2, erPtr);
	builder.makeArrayTE("ENTRY");
	builder.makeCompositeTE("");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageCount", "binary", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MessageIndex", "binary", 2, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("HeatId", "ascii", 10, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("TreatId", "ascii", 2, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("Source", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("RecipeNo", "binary", 4, erPtr);
	erPtr = erMgr.get("ascii");
	builder.makeStringTE("MatCode", "ascii", 10, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MatWeight", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("MatSequence", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("FeedRate", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("Spare_1", "binary", 4, erPtr);
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("Spare_2", "binary", 4, erPtr);
	builder.endCompositeTE();
	builder.endArrayTE(300);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_Out_factory::create_L2LF71(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("L2LF71");
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
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
void Telcom_Out_factory::create_L2LF72(
)
{
	EncodingRules * erPtr = 0;
	Tlg * tlgPtr;
	builder.makeTlg("L2LF72");
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
	builder.makeArrayTE("Spare");
	erPtr = erMgr.get("binary");
	builder.makeIntegerTE("", "binary", 4, erPtr);
	builder.endArrayTE(5);
	tlgPtr = builder.getTlg();
	prototypes[tlgPtr->getId()] = tlgPtr;
}
