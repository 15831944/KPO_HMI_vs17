// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CPHASEID_471DB0A002D0_INCLUDED
#define _INC_CPHASEID_471DB0A002D0_INCLUDED

#include <string>
#include "iSMC_DataDefinitions_s.hh"

//PhaseID has fixed format PPPPPPP:C, e.g. MeltDownBsk:1
//class is not derived from CFormattedID for undefined lenght 
//of PPPPP (Phase) and fixed seperator ":".
//##ModelId=471DB0A002D0
class CPhaseID 
{
private:
	//##ModelId=471DB27303C4
	static std::string m_QualifierSeparator;

public:
	//##ModelId=471DB20602DA
	static std::string getPhase(const std::string& PhaseID);

	//##ModelId=471DB22C00E6
	static long getPhaseNo(const std::string& PhaseID);

	//##ModelId=471DB24401B2
  static std::string getPhaseID(const std::string& Phase, long PhaseNo   );

};

#endif /* _INC_CPHASEID_471DB0A002D0_INCLUDED */
