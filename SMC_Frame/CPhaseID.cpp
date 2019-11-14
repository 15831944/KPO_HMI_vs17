// Copyright (C) 2004 SMS Demag AG

#include <iostream>
#include <sstream>

#include "CPhaseID.h"





//##ModelId=471DB27303C4
std::string CPhaseID::m_QualifierSeparator(":");

//##ModelId=471DB20602DA
std::string CPhaseID::getPhase(const std::string& PhaseID)
{
  std::string RetValue = DEF::Inv_String;

  long Position = -1;

  if ( std::string::npos != (Position = (long)PhaseID.find_first_of(CPhaseID::m_QualifierSeparator)) )
  {
    RetValue = PhaseID.substr(0,Position - 1);
  }

  return RetValue;
}

//##ModelId=471DB22C00E6
long CPhaseID::getPhaseNo(const std::string& PhaseID)
{
  long RetValue = DEF::Inv_Long;

  long Position = -1;

  if ( std::string::npos != (Position = (long)PhaseID.find_first_of(CPhaseID::m_QualifierSeparator)) )
  {
    std::string PhaseNo = PhaseID.substr(Position + 1 ,PhaseID.length());

    std::istringstream istr(PhaseNo);

    istr >> RetValue;
  }

	return RetValue;
}

//##ModelId=471DB24401B2
std::string CPhaseID::getPhaseID(const std::string& Phase, long PhaseNo)
{
  std::string RetValue = DEF::Inv_String;
  std::stringstream PhaseID;

  PhaseID << Phase;
  
  if ( PhaseNo != DEF::Inv_Long )
  {
    PhaseID << CPhaseID::m_QualifierSeparator << PhaseNo;
  }

  RetValue = PhaseID.str();

  return RetValue;

}

