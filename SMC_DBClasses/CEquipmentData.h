// Copyright (C) 2004, 2005 SMS Demag AG, Germany 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEQUIPMENTDATAWRAPPER_44BC99390315_INCLUDED
#define _INC_CEQUIPMENTDATAWRAPPER_44BC99390315_INCLUDED

#include "CSMC_DBData.h"

/////////////////////////////////////////////////////////
//
//This is not a generated class for a table. It provides 
//possibility to get equipment data depends on 2,3 or more 
//tables.
//
/////////////////////////////////////////////////////////
class CEquipmentData 
{
protected:
  
  cCBS_StdConnection * m_pCBS_StdConnection;

  void log(const std::string& Message, long Level);

  cCBS_ODBC_DBError m_lastError; 

public:

  cCBS_ODBC_DBError getLastError();

	// set new LANCE age given by customer lance id
	bool setLanceAge(const std::string& PLANT, long PLANTNO, std::string& CustLanceId, double NewAge, bool Commit);
  bool increaseLanceAge(const std::string& PLANT, long PLANTNO, std::string& CustLanceId, double Value, bool Commit);

	// set new LANCE TIP age given by customer lance id
	bool setLanceTipAge(const std::string& PLANT, long PLANTNO, std::string& CustLanceId, double NewAge, bool Commit);
  bool increaseLanceTipAge(const std::string& PLANT, long PLANTNO, std::string& CustLanceId, double Value, bool Commit);

	//return CUSTOMER_ID from GC_EQUIP_CAT.
	long getEquipmentNo(const std::string& PLANT, long PLANTNO, const std::string& EQUIP_TYPE, const std::string& STRUCT_SUB_ID, const std::string& COUNTER_TYPE );
  long getEquipmentNo(const std::string& EQUIP_TYPE_PARENT, const std::string& STRUCT_SUB_ID_PARENT, const std::string& EQUIP_TYPE, const std::string& STRUCT_SUB_ID, const std::string& COUNTER_TYPE );


	//return PRI_COUNTER from PD_EQUIP_MOUNT.
	//PLANT           - argegate
	//PLANTNO      - agregate number
	//EQUIP_TYPE - equipment type
	//This method can't be used for an equipment that is more 
	//than one time in the argegate i.e. LANCE at BOF because 
	//lance and standby lance are from the same EQUIP_TYPE.
  double getEquipmentAge(const std::string& EQUIP_TYPE_PARENT, const std::string& STRUCT_SUB_ID_PARENT, const std::string& EQUIP_TYPE, const std::string& STRUCT_SUB_ID, const std::string& COUNTER_TYPE );
	double getEquipmentAge(const std::string& PLANT, long PLANTNO, const std::string& EQUIP_TYPE, const std::string COUNTER_TYPE);
  double getEquipmentAge(const std::string& PLANT, long PLANTNO, const std::string& EQUIP_TYPE, long EQUIP_NO, const std::string COUNTER_TYPE);
  double getEquipmentAge(const std::string& PLANT, long PLANTNO, const std::string& EQUIP_TYPE, const std::string& EQUIP_NAME, const std::string COUNTER_TYPE);

	//Set new age of EQUIP_TYPE
  bool setEquipmentAge(const std::string& EQUIP_TYPE_PARENT, const std::string& STRUCT_SUB_ID_PARENT, const std::string& EQUIP_TYPE, const std::string& STRUCT_SUB_ID, const std::string& COUNTER_TYPE, double EQUIP_AGE, bool Commit );
  bool setEquipmentAge(const std::string& PLANT, long PLANTNO, const std::string& EQUIP_TYPE, const std::string COUNTER_TYPE, double EQUIP_AGE, bool Commit);
  bool setEquipmentAge(const std::string& PLANT, long PLANTNO, const std::string& EQUIP_TYPE, long EQUIP_NO, const std::string COUNTER_TYPE, double EQUIP_AGE, bool Commit);
  bool setEquipmentAge(const std::string& PLANT, long PLANTNO, const std::string& EQUIP_TYPE, const std::string& EQUIP_NAME, const std::string COUNTER_TYPE, double EQUIP_AGE, bool Commit);

	//increase age of EQUIP_TYPE
  bool increaseEquipmentAge(const std::string& EQUIP_TYPE_PARENT, const std::string& STRUCT_SUB_ID_PARENT, const std::string& EQUIP_TYPE, const std::string& STRUCT_SUB_ID, const std::string& COUNTER_TYPE, double Value, bool Commit );
  bool increaseEquipmentAge(const std::string& PLANT, long PLANTNO, const std::string& EQUIP_TYPE, const std::string COUNTER_TYPE, double Value, bool Commit);
  bool increaseEquipmentAge(const std::string& PLANT, long PLANTNO, const std::string& EQUIP_TYPE, long EQUIP_NO, const std::string COUNTER_TYPE, double Value, bool Commit);
  bool increaseEquipmentAge(const std::string& PLANT, long PLANTNO, const std::string& EQUIP_TYPE, const std::string& EQUIP_NAME, const std::string COUNTER_TYPE, double Value, bool Commit);

	//return CUSTOMER_ID from GC_EQUIP_CAT.
	std::string getEquipmentIdCust(const std::string& PLANT, long PLANTNO, const std::string& EQUIP_TYPE, const std::string& STRUCT_SUB_ID, const std::string& COUNTER_TYPE );
  std::string getEquipmentIdCust(const std::string& EQUIP_TYPE_PARENT, const std::string& STRUCT_SUB_ID_PARENT, const std::string& EQUIP_TYPE, const std::string& STRUCT_SUB_ID, const std::string& COUNTER_TYPE );

	//returrn age of equipment type 'LANCE'.
	//CustLanceId - customer lance id.
	long getLanceAge(const std::string& PLANT, long PLANTNO, std::string& CustLanceId);
  
  //return age of lance tip.
  long getLanceTipAge(const std::string& PLANT, long PLANTNO, std::string& CustLanceId);

	CEquipmentData(cCBS_StdConnection* Connection);

	virtual ~CEquipmentData();

	bool increaseEquipmentAge(const std::string& HEATID,const std::string& TREATID,const std::string& PLANT, long PLANTNO, const std::string& EQUIP_TYPE, long EQUIP_NO, const std::string& COUNTER_TYPE, double Value, bool Commit );
	bool ladleLifeHandline(const std::string& HEATID,const std::string& TREATID,const std::string& PLANT, const std::string& EQUIP_TYPE, const std::string& COUNTER_TYPE, double COUNTER_VALUE, bool Commit );
};

#endif /* _INC_CEQUIPMENTDATAWRAPPER_44BC99390315_INCLUDED */
