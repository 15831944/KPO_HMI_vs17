#pragma once

#include <sstream>       // required for the conversion

//##ModelId=425505F70317
class CL2LadleId
{
public:
	//##ModelId=4255072802FC
  CL2LadleId(void);
	//##ModelId=42550728031A
  ~CL2LadleId(void);



  /* From the box collection:
     On Level 1 the Ladle can only by identified via a Number.
     To distinguish different Types of Ladle Number circels are defined
      Ladle Numbers from 
                                                           Level 2 LadleId
      1-19 are Hot Metal Ladles before Mixer               B01-B19
      20-39 are Hot Metal ladles going to Steelplant       H20-H39
      40-59 are Pretreatment ladles                        P40-P59
      60-79 are Teeming Ladles                             P60-P79
   */
	//##ModelId=425507280338
  static std::string L2LadleIdFromL1LadleNo (long L1LadleNo);
};
