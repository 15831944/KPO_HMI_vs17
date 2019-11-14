// Copyright (C) 2004 SMS Demag AG, Germany 

#include "CVPD_RECIPE_CURR_STATUS.h"


CVPD_RECIPE_CURR_STATUS::CVPD_RECIPE_CURR_STATUS(cCBS_StdConnection* Connection)
:CSMC_DBData("VPD_RECIPE_CURR_STATUS",Connection)
{
}

CVPD_RECIPE_CURR_STATUS::~CVPD_RECIPE_CURR_STATUS()
{
}

bool CVPD_RECIPE_CURR_STATUS::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const std::string& SOURCE, const std::string& RECIPENAME, long RECIPENO)
{
	cleanWhereStatement();
	
	m_Statement = "Select * from " + m_TableName + " ";
	
	addWhereClause("HEATID",HEATID);
	addWhereClause("TREATID",TREATID);
	addWhereClause("PLANT",PLANT);
	addWhereClause("SOURCE",SOURCE);
	addWhereClause("RECIPENAME",RECIPENAME);
	addWhereClause("RECIPENO",RECIPENO);
	
	m_Statement += getWhereStatement() + ";";
	
	return CSMC_DBData::select();

}

string CVPD_RECIPE_CURR_STATUS::getPLANT(long Row)
{
	return getString("PLANT", Row);

}

void CVPD_RECIPE_CURR_STATUS::setPLANT(const std::string& value)
{
	setString("PLANT", value);

}

string CVPD_RECIPE_CURR_STATUS::getHEATID(long Row)
{
	return getString("HEATID", Row);

}

void CVPD_RECIPE_CURR_STATUS::setHEATID(const std::string& value)
{
	setString("HEATID", value);

}

string CVPD_RECIPE_CURR_STATUS::getTREATID(long Row)
{
	return getString("TREATID", Row);

}

void CVPD_RECIPE_CURR_STATUS::setTREATID(const std::string& value)
{
	setString("TREATID", value);

}

string CVPD_RECIPE_CURR_STATUS::getRECIPENAME(long Row)
{
	return getString("RECIPENAME", Row);

}

void CVPD_RECIPE_CURR_STATUS::setRECIPENAME(const std::string& value)
{
	setString("RECIPENAME", value);

}

long CVPD_RECIPE_CURR_STATUS::getRECIPENO(long Row)
{
	return getLong("RECIPENO", Row);

}

void CVPD_RECIPE_CURR_STATUS::setRECIPENO(long value)
{
	setLong("RECIPENO", value);

}

string CVPD_RECIPE_CURR_STATUS::getSOURCE(long Row)
{
	return getString("SOURCE", Row);

}

void CVPD_RECIPE_CURR_STATUS::setSOURCE(const std::string& value)
{
	setString("SOURCE", value);

}

long CVPD_RECIPE_CURR_STATUS::getBATCHSTATUSNO(long Row)
{
	return getLong("BATCHSTATUSNO", Row);

}

void CVPD_RECIPE_CURR_STATUS::setBATCHSTATUSNO(long value)
{
	setLong("BATCHSTATUSNO", value);

}

double CVPD_RECIPE_CURR_STATUS::getACT_O2_MOMENT(long Row)
{
	return getDouble("ACT_O2_MOMENT", Row);

}

void CVPD_RECIPE_CURR_STATUS::setACT_O2_MOMENT(double value)
{
	setDouble("ACT_O2_MOMENT", value);

}

double CVPD_RECIPE_CURR_STATUS::getACT_AR_MOMENT(long Row)
{
	return getDouble("ACT_AR_MOMENT", Row);

}

void CVPD_RECIPE_CURR_STATUS::setACT_AR_MOMENT(double value)
{
	setDouble("ACT_AR_MOMENT", value);

}

double CVPD_RECIPE_CURR_STATUS::getACT_N2_MOMENT(long Row)
{
	return getDouble("ACT_N2_MOMENT", Row);

}

void CVPD_RECIPE_CURR_STATUS::setACT_N2_MOMENT(double value)
{
	setDouble("ACT_N2_MOMENT", value);

}

double CVPD_RECIPE_CURR_STATUS::getACT_EGY(long Row)
{
	return getDouble("ACT_EGY", Row);

}

void CVPD_RECIPE_CURR_STATUS::setACT_EGY(double value)
{
	setDouble("ACT_EGY", value);

}

bool CVPD_RECIPE_CURR_STATUS::deleteBatches(const std::string & Plant, long BatchStatusNo)
{
  cleanWhereStatement();
  addWhereClause("PLANT",Plant);
  addWhereClause("BATCHSTATUSNO", BatchStatusNo);

  return deleteRows();
}
