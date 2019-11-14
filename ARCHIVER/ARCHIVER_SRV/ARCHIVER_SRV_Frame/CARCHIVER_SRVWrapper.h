#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_SVRDWRAPPER_419CCDC6024D_INCLUDED
#define _INC_CARCHIVER_SVRWRAPPER_419CCDC6024D_INCLUDED

#include "CDateTime.h"
#include "CARCHIVER_Wrapper.h"

class CARCHIVER_SRVTask;
class CEventMessage;

class CPP_HEAT;
class CPP_HEAT_PLANT;
class CPP_ORDER;

class CPD_PRETREATDATA;

class CPD_HEAT_DATA;
class CPDL_HEAT_DATA;
class CPD_SAMPLE_REF;
class CPD_PLANTSTATUS;
class CPD_SAMPLE;


class CHD_HEAT_DATA;
class CHD_SAMPLE_REF;
class CHD_SAMPLE;
class CHD_LADLE_LIFE_DATA;

class CPD_HEAT_PLANT_REF;
class CPD_HEAT_REF;
class CPD_HOT_METAL;



//##ModelId=41DD3D480317
class CARCHIVER_SRVWrapper : public CARCHIVER_Wrapper
{
private:
	//##ModelId=41DD3EB90134
	void deleteDBClasses();
	//##ModelId=41DD3EB9013F
	void initDBClasses();
public:
	//##ModelId=42D53EA6030C
  CDateTime getDeletionDate(const std::string& TableName);


	//##ModelId=41DD3EB900B3
  bool doOnServiceEvent(CEventMessage& Event);
	//##ModelId=41DD3EB90030
	CARCHIVER_SRVWrapper();
	//##ModelId=41DD3EB9004E
	virtual ~CARCHIVER_SRVWrapper();

protected:

  CPP_HEAT            * m_pPP_HEAT;
  CPP_HEAT_PLANT      * m_pPP_HEAT_PLANT;
  CPP_ORDER           * m_pPP_ORDER;
  CPD_PRETREATDATA    * m_pPD_PRETREATDATA;
  CPD_HEAT_DATA       * m_pPD_HEAT_DATA;
  CPDL_HEAT_DATA      * m_pPDL_HEAT_DATA;
  CPD_SAMPLE_REF      * m_pPD_SAMPLE_REF;
  CPD_PLANTSTATUS     * m_pPD_PLANTSTATUS;
  CPD_SAMPLE          * m_pPD_SAMPLE;
  CHD_HEAT_DATA       * m_pHD_HEAT_DATA;
  CHD_SAMPLE_REF      * m_pHD_SAMPLE_REF;
  CHD_SAMPLE          * m_pHD_SAMPLE;
  CHD_LADLE_LIFE_DATA * m_pHD_LADLE_LIFE_DATA;
  CPD_HEAT_PLANT_REF  * m_pPD_HEAT_PLANT_REF;
  CPD_HEAT_REF        * m_pPD_HEAT_REF;
	CPD_HOT_METAL       * m_pPD_HOT_METAL;

};

#endif /* _INC_CARCHIVER_SRVWRAPPER_419CCDC6024D_INCLUDED */
