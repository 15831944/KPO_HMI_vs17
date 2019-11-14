#include <iomanip>

#include "cl2ladleid.h"

//##ModelId=4255072802FC
CL2LadleId::CL2LadleId(void)
{
  ; // nothing, Obviously. Makes no sense anyway to instantiate this class
}

//##ModelId=42550728031A
CL2LadleId::~CL2LadleId(void)
{
  ; // nothing
}

//##ModelId=425507280338
std::string CL2LadleId::L2LadleIdFromL1LadleNo (long L1LadleNo)
{
  std::stringstream lIdS;
  if        (L1LadleNo >=  1 && L1LadleNo <=  9)    lIdS << 'B'<< 0 << L1LadleNo;	//HML before Mixer
  else if   (L1LadleNo >= 10 && L1LadleNo <= 19)    lIdS << 'B'     << L1LadleNo;	//HML before Mixer
  else if   (L1LadleNo >= 20 && L1LadleNo <= 39)    lIdS << 'H'     << L1LadleNo;	//HML after Mixer
  else if   (L1LadleNo >= 40 && L1LadleNo <= 59)    lIdS << 'P'     << L1LadleNo;	//PreMetal Ladle EAF-AOD
  else if   (L1LadleNo >= 60 && L1LadleNo <= 79)    lIdS << 'T'     << L1LadleNo;	//Steel Ladle
  else
  {
    // return number only.
    lIdS << L1LadleNo;
  }
  return lIdS.str();  // should be safe, returns a copy of the temporary std::string.
}
