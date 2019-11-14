// Copyright (C) 2004 SMS Demag AG, Germany 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CVPD_RECIPE_CURR_STATUS_41F75F7D02EA_INCLUDED
#define _INC_CVPD_RECIPE_CURR_STATUS_41F75F7D02EA_INCLUDED

#include "CSMC_DBData.h"

class CVPD_RECIPE_CURR_STATUS 
: public CSMC_DBData
{
public:
	CVPD_RECIPE_CURR_STATUS(cCBS_StdConnection* Connection);

	~CVPD_RECIPE_CURR_STATUS();

	bool select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const std::string& SOURCE, const std::string& RECIPENAME, long RECIPENO);

  bool deleteBatches(const std::string & Plant, long BatchStatusNo);

	string getPLANT(long Row);

	void setPLANT(const std::string& value);

	string getHEATID(long Row);

	void setHEATID(const std::string& value);

	string getTREATID(long Row);

	void setTREATID(const std::string& value);

	string getRECIPENAME(long Row);

	void setRECIPENAME(const std::string& value);

	long getRECIPENO(long Row);

	void setRECIPENO(long value);

	string getSOURCE(long Row);

	void setSOURCE(const std::string& value);

	long getBATCHSTATUSNO(long Row);

	void setBATCHSTATUSNO(long value);

	double getACT_O2_MOMENT(long Row);

	void setACT_O2_MOMENT(double value);

	double getACT_AR_MOMENT(long Row);

	void setACT_AR_MOMENT(double value);

	double getACT_N2_MOMENT(long Row);

	void setACT_N2_MOMENT(double value);

	double getACT_EGY(long Row);

	void setACT_EGY(double value);

};

#endif /* _INC_CVPD_RECIPE_CURR_STATUS_41F75F7D02EA_INCLUDED */
