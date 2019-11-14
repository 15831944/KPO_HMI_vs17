// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CPHASEDATAHANDLER_471EF995039E_INCLUDED
#define _INC_CPHASEDATAHANDLER_471EF995039E_INCLUDED

#include <string>

#include "iSMC_DataProvider_s.hh"

class CDateTime;

//##ModelId=471EF995039E
class CPhaseDataHandler 
{
private:
	//##ModelId=471EF9C20153
	seqPhaseData m_PhaseDataSeq;

public:
	//##ModelId=4720AF640016
	static CORBA::Any getStartValue(sPhaseData& PhaseData, const std::string& Name);

	//##ModelId=4720AF68027F
	static CORBA::Any getEndValue(sPhaseData& PhaseData, const std::string& Name);

	//##ModelId=4720AF6D0150
	static CORBA::Any getDeltaValue(sPhaseData& PhaseData, const std::string& Name);

	//##ModelId=4720AC3B0215
	sPhaseData getPhaseData(const std::string& PhaseName, long PhaseNo, long PhaseStatus);

	//##ModelId=472092D30113
	double sumDuration( long PhaseStatus    );

	//##ModelId=4720897802BA
	long getLastPhaseNo(const std::string& PhaseName);

	//##ModelId=472076ED025E
	bool isPhase(const std::string& PhaseName);

	//##ModelId=4720523A0385
	void setStartTime(const std::string& PhaseName, long PhaseNo, CDateTime& Value);

	//##ModelId=4720524E02D0
	void setEndTime(const std::string& PhaseName, long PhaseNo, CDateTime& Value);

	//##ModelId=4720515D017F
	void newPhase(const std::string& PhaseName, long PhaseNo, long PhaseStatus);

	//##ModelId=4720527401F8
	void newPhase(sPhaseData& Phase);

	//##ModelId=471F475B03E5
	double getDuration(const std::string& PhaseName, long PhaseNo);

	//##ModelId=471F477600AC
	long getStatus(const std::string& PhaseName, long PhaseNo);

	//##ModelId=471F472A036F
	void setStatus(const std::string& PhaseName, long PhaseNo, long Value);

	//##ModelId=471F3ABA02CE
	sPhaseData getPhaseData(const std::string& PhaseName, long PhaseNo);

	//##ModelId=471F25EA0258
	void setStartTime(const std::string& PhaseName, long PhaseNo, sDate& Value);

	//##ModelId=471F25EB0306
	void setEndTime(const std::string& PhaseName, long PhaseNo, sDate& Value);

	//##ModelId=471F25ED021B
	void setDuration(const std::string& PhaseName, long PhaseNo, double Value);

	//##ModelId=471F22C200CD
	bool isPhaseDataName(const std::string& PhaseName, long PhaseNo, const std::string& Name);

	//##ModelId=471F22C70059
	bool isPhaseDataName(sPhaseData& Phase, const std::string& Name);

	//##ModelId=471F1FDD0350
	void setPhaseData(sPhaseData Value);

	//##ModelId=471F202C0276
	bool isPhase(sPhaseData& Phase);

	//##ModelId=471F10F902DD
	bool isPhase(const std::string& PhaseName, long PhaseNo);

	//##ModelId=471F06FE0266
	static bool checkLength(seqPhaseData& PhaseData);

	//##ModelId=471F072E0012
	static bool checkLength(seqPhaseDataNames& PhaseDataNames);

	//##ModelId=471EFC4C01C1
	seqPhaseData &  getPhaseDataSeq();

	//##ModelId=471EFA5E01C5
	seqPhaseDataNames getPhaseDataNamesSeq(const std::string& PhaseName, long PhaseNo);

	//##ModelId=471EFC9D01C5
	sPhaseDataNames getPhaseDataNames(const std::string& PhaseName, long PhaseNo, const std::string& Name);

	//##ModelId=471EFCCF0370
	static sPhaseDataNames getPhaseDataNames(seqPhaseDataNames PhaseDataNames, const std::string& Name);

	//##ModelId=471EFB2001A1
	CORBA::Any getStartValue(const std::string& PhaseName, long PhaseNo, const std::string& Name);

	//##ModelId=471EFCFD000C
	CORBA::Any getEndValue(const std::string& PhaseName, long PhaseNo, const std::string& Name);

	//##ModelId=471EFCFE02A8
	CORBA::Any getDeltaValue(const std::string& PhaseName, long PhaseNo, const std::string& Name);

	//##ModelId=471F03AD02CA
	void setPhaseDataSeq(seqPhaseData value);

	//##ModelId=471F03AD037E
	void setStartValue(const std::string& PhaseName, long PhaseNo, const std::string& Name, CORBA::Any Value);

	//##ModelId=471F03AD0392
	void setEndValue(const std::string& PhaseName, long PhaseNo, const std::string& Name, CORBA::Any Value);

	//##ModelId=471F03AD03BA
	void setDeltaValue(const std::string& PhaseName, long PhaseNo, const std::string& Name, CORBA::Any Value);

	//##ModelId=471EF9AA0073
	virtual ~CPhaseDataHandler();

	//##ModelId=471EF9AA01BE
	CPhaseDataHandler();

};

#endif /* _INC_CPHASEDATAHANDLER_471EF995039E_INCLUDED */
