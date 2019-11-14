#ifndef _CSMC_EventLogHMD_h_
#define _CSMC_EventLogHMD_h_

#include <string>

#include "CSMC_EventLogFrame.h"
#include "CSMC_DestCodes.h"

class CSMC_EventLogHMD : public CSMC_EventLogFrame
{
protected:
  long lRetValue;
public:
  CSMC_EventLogHMD(std::string sProcName = "",std::string sServiceName = "",std::string sContextName = "");

  virtual ~CSMC_EventLogHMD();

long EL_BathLevelMeasurement( double BachLevel);

long EL_BathLevelMeasurement( sEventLogMessage &EventLogMessage, double BachLevel);

long EL_ChangeAimData();

long EL_ChangeAimData( sEventLogMessage &EventLogMessage );

long EL_ChangeAimDepartureTime( const char * AimDepTime);

long EL_ChangeAimDepartureTime( sEventLogMessage &EventLogMessage, const char * AimDepTime);

long EL_ChangePhysicalMatAvailibility( const char * MatCode);

long EL_ChangePhysicalMatAvailibility( sEventLogMessage &EventLogMessage, const char * MatCode);

long EL_ComputerModeOff();

long EL_ComputerModeOff( sEventLogMessage &EventLogMessage );

long EL_ComputerModeOn();

long EL_ComputerModeOn( sEventLogMessage &EventLogMessage );

long EL_CreateTreatmentID();

long EL_CreateTreatmentID( sEventLogMessage &EventLogMessage );

long EL_CyclicMeasurement();

long EL_CyclicMeasurement( sEventLogMessage &EventLogMessage );

long EL_DelayStatus( const char * DelayPlant,const char * DelayCode,const char * DelayStartDate,const char * DelayEndDate,const char * DelayDescription);

long EL_DelayStatus( sEventLogMessage &EventLogMessage, const char * DelayPlant,const char * DelayCode,const char * DelayStartDate,const char * DelayEndDate,const char * DelayDescription);

long EL_DeslaggingEnd( const char * DeslagEndTime);

long EL_DeslaggingEnd( sEventLogMessage &EventLogMessage, const char * DeslagEndTime);

long EL_DeslaggingStart( const char * DeslagStartTime,const char * DeslaggingStatus);

long EL_DeslaggingStart( sEventLogMessage &EventLogMessage, const char * DeslagStartTime,const char * DeslaggingStatus);

long EL_HandleUpdatePurpose();

long EL_HandleUpdatePurpose( sEventLogMessage &EventLogMessage );

long EL_HeatAnnouncement( const char * HeatID,const char * TreatID,const char * PlantID,const char * LadleId);

long EL_HeatAnnouncement( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID,const char * LadleId);

long EL_HeatAnnouncementOffline( const char * HeatID,const char * TreatID,const char * PlantID,const char * LadleId);

long EL_HeatAnnouncementOffline( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID,const char * LadleId);

long EL_HeatAnnounceStatus( const char * HeatAnnounceStatus,const char * HeatID,const char * TreatID,const char * PlantID);

long EL_HeatAnnounceStatus( sEventLogMessage &EventLogMessage, const char * HeatAnnounceStatus,const char * HeatID,const char * TreatID,const char * PlantID);

long EL_HeatCancellation( const char * HeatID,const char * TreatID,const char * PlantID);

long EL_HeatCancellation( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID);

long EL_HeatDeparture( const char * HeatID,const char * TreatID,const char * PlantID);

long EL_HeatDeparture( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID);

long EL_HeatStart( const char * HeatID,const char * TreatID,const char * PlantID);

long EL_HeatStart( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID);

long EL_HeatEnd( const char * HeatID,const char * TreatID,const char * PlantID);

long EL_HeatEnd( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID);

long EL_HoodInOperationPos();

long EL_HoodInOperationPos( sEventLogMessage &EventLogMessage );

long EL_HoodOutOfOperationPos();

long EL_HoodOutOfOperationPos( sEventLogMessage &EventLogMessage );

long EL_HotMetalAnalysisReceived( const char * SampleCode,long SampleCounterL1);

long EL_HotMetalAnalysisReceived( sEventLogMessage &EventLogMessage, const char * SampleCode,long SampleCounterL1);

long EL_HotMetalSampleTaken( const char * SampleCode,long SampleCounterL1,const char * SampleLocation);

long EL_HotMetalSampleTaken( sEventLogMessage &EventLogMessage, const char * SampleCode,long SampleCounterL1,const char * SampleLocation);

long EL_InjectionLanceBlowingStart();

long EL_InjectionLanceBlowingStart( sEventLogMessage &EventLogMessage );

long EL_InjectionLanceBlowingStop();

long EL_InjectionLanceBlowingStop( sEventLogMessage &EventLogMessage );

long EL_LanceInOperationPos( long LanceId);

long EL_LanceInOperationPos( sEventLogMessage &EventLogMessage, long LanceId);

long EL_LanceOutOfOperationPos( long LanceId);

long EL_LanceOutOfOperationPos( sEventLogMessage &EventLogMessage, long LanceId);

long EL_ModelResult();

long EL_ModelResult( sEventLogMessage &EventLogMessage );

long EL_ModelResultCode();

long EL_ModelResultCode( sEventLogMessage &EventLogMessage );

long EL_PhaseMonoInjectionCarbideEnd();

long EL_PhaseMonoInjectionCarbideEnd( sEventLogMessage &EventLogMessage );

long EL_PhaseMonoInjectionCarbideStart();

long EL_PhaseMonoInjectionCarbideStart( sEventLogMessage &EventLogMessage );

long EL_PhaseMonoInjectionContinued();

long EL_PhaseMonoInjectionContinued( sEventLogMessage &EventLogMessage );

long EL_PhaseMonoInjectionLimeEnd();

long EL_PhaseMonoInjectionLimeEnd( sEventLogMessage &EventLogMessage );

long EL_PhaseMonoInjectionLimeStart();

long EL_PhaseMonoInjectionLimeStart( sEventLogMessage &EventLogMessage );

long EL_SlagAnalysisReceived( const char * SampleCode,long SampleCounterL1);

long EL_SlagAnalysisReceived( sEventLogMessage &EventLogMessage, const char * SampleCode,long SampleCounterL1);

long EL_SlagSampleTaken( const char * SampleCode,long SampleCounterL1,const char * SampleLocation);

long EL_SlagSampleTaken( sEventLogMessage &EventLogMessage, const char * SampleCode,long SampleCounterL1,const char * SampleLocation);

long EL_TempMeasurement( double MeasTemp);

long EL_TempMeasurement( sEventLogMessage &EventLogMessage, double MeasTemp);

long EL_PhaseCoInjectionMagnesiumStart();

long EL_PhaseCoInjectionMagnesiumStart( sEventLogMessage &EventLogMessage );

long EL_PhaseCoInjectionMagnesiumEnd();

long EL_PhaseCoInjectionMagnesiumEnd( sEventLogMessage &EventLogMessage );
};
#endif
