#include "CGC_CounterContainer.h"

CGC_CounterContainer::CGC_CounterContainer(cCBS_StdConnection *Connection)
:CSMC_DBData("DUAL",Connection)
{  
}

CGC_CounterContainer::~CGC_CounterContainer(void)
{
}

 long CGC_CounterContainer::GetSampleCounter()
 {
   long nCounter = -1;
   cleanWhereStatement();

   m_Statement = "Select SEQ_SAMPLE_COUNTER.NextVal  as COUNTER from " + m_TableName;

   if(CSMC_DBData::select())
   {
     nCounter = getLong("COUNTER", 1);
   }

   return nCounter;
 }

 long CGC_CounterContainer::GetSampleRefCounter()
 {
   long nCounter = -1;
   cleanWhereStatement();

   m_Statement = "Select SEQ_SAMPLE_REF_COUNTER.NextVal  as COUNTER from " + m_TableName;

   if(CSMC_DBData::select())
   {
     nCounter = getLong("COUNTER", 1);
   }

   return nCounter;
 }

 long CGC_CounterContainer::GetPretreatCounter()
 {
   long nCounter = -1;

   cleanWhereStatement();

   m_Statement = "Select SEQ_PRETREAT_COUNTER.NextVal  as COUNTER from " + m_TableName;

   if(CSMC_DBData::select())
   {
     nCounter = getLong("COUNTER", 1);
   }

   return nCounter;
 }