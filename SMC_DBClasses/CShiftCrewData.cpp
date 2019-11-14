// Copyright (C) 2012 SMS Demag AG, Germany 

#include "cCBS_StdDB_Task.h"
#include "CDataConversion.h"

#include "CPP_SHIFT_CREW_ASSIGNMENT.h"
#include "CPP_MEMBER_CREW_ASSIGNMENT.h"
#include "CGC_MEMBER_CAT.h"
#include "CGC_CREW_CAT.h"
#include "CGC_SHIFT_CAT.h"


#include "CShiftCrewData.h"


CShiftCrewData::CShiftCrewData(cCBS_StdConnection* Connection)
: m_pCBS_StdConnection(Connection)
{
}

CShiftCrewData::~CShiftCrewData()
{
}

void CShiftCrewData::log(const std::string& Message, long Level)
{
  if (cCBS_StdDB_Task::getInstance()->getTraceLevel() >= Level)
  {
    cCBS_StdDB_Task::getInstance()->log(Message, Level);
  }
}

cCBS_ODBC_DBError CShiftCrewData::getLastError()
{
  return m_lastError; 
}

void CShiftCrewData::getCrewAndShiftByDate(std::string& CREW_ID, std::string& SHIFT_ID, const CDateTime& ActDate, const std::string& PLANT, long PLANTNO)
{
	//SARS
  CPP_SHIFT_CREW_ASSIGNMENT PP_SHIFT_CREW_ASSIGNMENT  (m_pCBS_StdConnection);
  CGC_CREW_CAT              GC_CREW_CAT               (m_pCBS_StdConnection);
  CGC_SHIFT_CAT             GC_SHIFT_CAT              (m_pCBS_StdConnection);

  // to be changed into e.g. CPlantID or CGC_CREW_LOCATIN_CAT class
  std::string LOCATION = CSMC_DBData::unspecString;

  if ( PLANT    != CSMC_DBData::unspecString &&
       PLANTNO  != CSMC_DBData::unspecLong )
  {
    LOCATION = PLANT + " " + CDataConversion::LongToString(PLANTNO);
  }

  CREW_ID  = CSMC_DBData::unspecString;    
  SHIFT_ID = CSMC_DBData::unspecString;     

	std::string sActDate = ActDate.toDBString();
	std::string sHourMinute = sActDate.substr(11 ,5);
	std::string sShiftStart = sActDate.substr(0 ,10); //yyyy-mm-dd
	std::string ShiftStartTime = CSMC_DBData::unspecString;

  if ( GC_SHIFT_CAT.select(CSMC_DBData::unspecLong, CSMC_DBData::unspecString) ) //consider there are one Shift_type in a table
  {
		int rowNo = GC_SHIFT_CAT.getLastRow() + 1;
		for ( long i = 1 ; i <= GC_SHIFT_CAT.getLastRow() ; ++i )
		{
			rowNo--;

			ShiftStartTime = GC_SHIFT_CAT.getSTART_TIME(rowNo); // Note : Format is 'hh:mm' only !
			if(ShiftStartTime <= sHourMinute)
			{
				SHIFT_ID = GC_SHIFT_CAT.getSHIFT_ID(rowNo);
				break;
			}
		}//for..


		if ( SHIFT_ID == CSMC_DBData::unspecString )
		{
			for ( long i = 1 ; i <= GC_SHIFT_CAT.getLastRow() ; ++i )
			{
				ShiftStartTime = GC_SHIFT_CAT.getSTART_TIME(i); // Note : Format is 'hh:mm' only !
				if(ShiftStartTime > sHourMinute)
				{
					SHIFT_ID = GC_SHIFT_CAT.getSHIFT_ID(i);
					
					CDateTime dt;
					dt.addTime(-1*24*60*60.0);
					std::string sDate = dt.toDBString();
					sShiftStart = sDate.substr(0 ,10); //yyyy-mm-dd
				}
			}
		}//if..

  } //if..
    
  if ( PP_SHIFT_CREW_ASSIGNMENT.selectOrdered(CSMC_DBData::unspecLong,SHIFT_ID,sShiftStart) ) 
  {
    for ( long i = 1 ; i <= PP_SHIFT_CREW_ASSIGNMENT.getLastRow() ; ++i )
    {
      CREW_ID    = PP_SHIFT_CREW_ASSIGNMENT.getCREW_ID(i);

      // check PLANT + PLANTNO against LOCATION at GC_CREW_CAT
      if ( LOCATION != CSMC_DBData::unspecString )
      {
        // skip entry if crew cannot be assigned to location
        if ( CREW_ID  != CSMC_DBData::unspecString )
        {
          if ( !GC_CREW_CAT.selectByLocation(CREW_ID, LOCATION) )
          {
            // reset crewid if no location was identified
            CREW_ID = CSMC_DBData::unspecString;
          }
					else
					{
						break;
					}
        }
      }
      else
      {
        // reset crewid if no location was identified
        CREW_ID = CSMC_DBData::unspecString;
      }

    }
  } //if..

  log ( "ShiftStartDate " + sShiftStart, 2 );
  log ( "ShiftStartTime " + ShiftStartTime, 2 );
  log ( "ActDate " + ActDate.asString(), 2 );

 // CPP_SHIFT_CREW_ASSIGNMENT PP_SHIFT_CREW_ASSIGNMENT  (m_pCBS_StdConnection);
 // CGC_CREW_CAT              GC_CREW_CAT               (m_pCBS_StdConnection);
 // CGC_SHIFT_CAT             GC_SHIFT_CAT              (m_pCBS_StdConnection);

 // // to be changed into e.g. CPlantID or CGC_CREW_LOCATIN_CAT class
 // std::string LOCATION = CSMC_DBData::unspecString;

 // if ( PLANT    != CSMC_DBData::unspecString &&
 //      PLANTNO  != CSMC_DBData::unspecLong )
 // {
 //   LOCATION = PLANT + " " + CDataConversion::LongToString(PLANTNO);
 // }


	//
	//// now all datasets with given shift_type and date < ActDate are available ordered desc
 // 
 // if ( PP_SHIFT_CREW_ASSIGNMENT.selectOrderedBeforeTime(ActDate) ) 
 // {
 //   for ( long i = 1 ; i <= PP_SHIFT_CREW_ASSIGNMENT.getLastRow() ; ++i )
 //   {
 //     std::string ShiftStartDate = PP_SHIFT_CREW_ASSIGNMENT.getSHIFT_START_DATE(i);
 //     std::string ShiftStartTime = CSMC_DBData::unspecString;

 //     SHIFT_ID   = PP_SHIFT_CREW_ASSIGNMENT.getSHIFT_ID(i);
 //     CREW_ID    = PP_SHIFT_CREW_ASSIGNMENT.getCREW_ID(i);

 //     // check PLANT + PLANTNO against LOCATION at GC_CREW_CAT
 //     if ( LOCATION != CSMC_DBData::unspecString )
 //     {
 //       // skip entry if crew cannot be assigned to location
 //       if ( CREW_ID  != CSMC_DBData::unspecString )
 //       {
 //         if ( !GC_CREW_CAT.selectByLocation(CREW_ID, LOCATION) )
 //         {
 //           // reset crewid if no location was identified
 //           CREW_ID = CSMC_DBData::unspecString;

 //           // skip
 //           continue;
 //         }
 //       }
 //     }
 //     else
 //     {
 //       // reset crewid if no location was identified
 //       CREW_ID = CSMC_DBData::unspecString;
 //     }

 //     // get start time for shift
 //     if ( SHIFT_ID != CSMC_DBData::unspecString )
 //     {
 //       if ( GC_SHIFT_CAT.select(CSMC_DBData::unspecLong, SHIFT_ID) )
 //       {
 //         ShiftStartTime = GC_SHIFT_CAT.getSTART_TIME(1); // Note : Format is 'hh:mm' only !
 //       }
 //     }

 //     if ( ShiftStartDate != CSMC_DBData::unspecString &&
 //          ShiftStartTime != CSMC_DBData::unspecString )
 //     {


 //       if ( !ShiftStartDate.empty() && !ShiftStartTime.empty() )
 //       {
 //         long year     = CDataConversion::StringToLong(ShiftStartDate.substr(0  ,4));
 //         long month    = CDataConversion::StringToLong(ShiftStartDate.substr(5  ,2));
 //         long day      = CDataConversion::StringToLong(ShiftStartDate.substr(8  ,2));
 //         long hour     = CDataConversion::StringToLong(ShiftStartTime.substr(0  ,2));
 //         long minute   = CDataConversion::StringToLong(ShiftStartTime.substr(3 ,5));
 //         long second   = 0; // not transferred
 //         long millisec = 0; // not transferred
 //         long dst      = 0; // always UTC

 //         CDateTime ShiftStart(year,month,day,hour,minute,second,millisec,dst);

 //         log ( "ShiftStartDate " + ShiftStartDate, 2 );
 //         log ( "ShiftStartTime " + ShiftStartTime, 2 );
 //         log ( "ShiftStart " + ShiftStart.asString(), 2 );
 //         log ( "ActDate " + ActDate.asString(), 2 );

 //         // we assume that shifts are defined for all times !
 //         // if not, it is possible to select a shift that has been defined sometimes in the past
 //         if ( ShiftStart <= ActDate )
 //         {
 //           break;
 //         }

 //       }
 //     }

 //     CREW_ID  = CSMC_DBData::unspecString;    
 //     SHIFT_ID = CSMC_DBData::unspecString;     
 //   }
 // }


}

std::string CShiftCrewData::getMemberNameByRole(const CDateTime& ActDate, const std::string& PLANT, long PLANTNO, long MemberRole)
{
  std::string UserCode;
  std::string CrewId;
  std::string ShiftId;

  CPP_MEMBER_CREW_ASSIGNMENT  PP_MEMBER_CREW_ASSIGNMENT (m_pCBS_StdConnection);
  CGC_MEMBER_CAT              GC_MEMBER_CAT             (m_pCBS_StdConnection);

  getCrewAndShiftByDate(CrewId, ShiftId, ActDate, PLANT, PLANTNO);

  if ( !CrewId.empty() )
  {
    if ( PP_MEMBER_CREW_ASSIGNMENT.select(CrewId, CSMC_DBData::unspecString) )
    {
      for ( long i = 1; i <= PP_MEMBER_CREW_ASSIGNMENT.getLastRow(); ++i )
      {
        std::string MEMBER_ID = PP_MEMBER_CREW_ASSIGNMENT.getMEMBER_ID(i);

        if ( GC_MEMBER_CAT.selectByMemeberRole(MEMBER_ID, MemberRole) )
        {
          UserCode = GC_MEMBER_CAT.getMEMBER_NAME(i);
          break;
        }
      }
    }
  }

  return UserCode;
}

std::string CShiftCrewData::getMemberIdByRole(const CDateTime& ActDate, const std::string& PLANT, long PLANTNO, long MemberRole)
{
  std::string MemberId;
  std::string CrewId;
  std::string ShiftId;

  CPP_MEMBER_CREW_ASSIGNMENT  PP_MEMBER_CREW_ASSIGNMENT (m_pCBS_StdConnection);
  CGC_MEMBER_CAT              GC_MEMBER_CAT             (m_pCBS_StdConnection);

  getCrewAndShiftByDate(CrewId, ShiftId, ActDate, PLANT, PLANTNO);

  if ( !CrewId.empty() )
  {
    if ( PP_MEMBER_CREW_ASSIGNMENT.select(CrewId, CSMC_DBData::unspecString) )
    {
      for ( long i = 1; i <= PP_MEMBER_CREW_ASSIGNMENT.getLastRow(); ++i )
      {
        std::string MEMBER_ID = PP_MEMBER_CREW_ASSIGNMENT.getMEMBER_ID(i);

        if ( GC_MEMBER_CAT.selectByMemeberRole(MEMBER_ID, MemberRole) )
        {
          MemberId = MEMBER_ID;
          break;
        }
      }
    }
  }

  return MemberId;
}
