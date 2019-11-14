// Copyright (C) 2009 SMS Siemag  AG, Germany

#include "CPCA_COMP.h"

CPCA_COMP::CPCA_COMP(cCBS_StdConnection* Connection)
:CSMC_DBData("PCA_COMP",Connection)
{
}

CPCA_COMP::~CPCA_COMP()
{
}

string CPCA_COMP::getCOMPCODE(long Row)
{
 return getString("COMPCODE", Row);
}

void CPCA_COMP::setCOMPCODE(const std::string& value)
{
 setString("COMPCODE", value);
}

string CPCA_COMP::getCOMPDESCR(long Row)
{
 return getString("COMPDESCR", Row);
}

void CPCA_COMP::setCOMPDESCR(const std::string& value)
{
 setString("COMPDESCR", value);
}

bool CPCA_COMP::select(const std::string& COMPCODE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

 addWhereClause("COMPCODE",COMPCODE);
 m_Statement += getWhereStatement() + ";";

 return CSMC_DBData::select();
}

