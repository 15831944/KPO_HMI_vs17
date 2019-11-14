#ifndef _CSMC_EventLogFrame_h_
#define _CSMC_EventLogFrame_h_

#include <string>

#include "cCBS_StdEventLogFrame.h"
#include "CSMC_DestCodes.h"

class CSMC_EventLogFrame : public cCBS_StdEventLogFrame
{
protected:
  long lRetValue;
public:
  CSMC_EventLogFrame(std::string sProcName = "",std::string sServiceName = "",std::string sContextName = "");

  virtual ~CSMC_EventLogFrame();

long EL_Analysis( const char * Elem1,double AnlVal1,const char * Elem2,double AnlVal2,const char * Elem3,double AnlVal3,const char * Elem4,double AnlVal4,const char * Elem5,double AnlVale5);

long EL_Analysis( sEventLogMessage &EventLogMessage, const char * Elem1,double AnlVal1,const char * Elem2,double AnlVal2,const char * Elem3,double AnlVal3,const char * Elem4,double AnlVal4,const char * Elem5,double AnlVale5);

long EL_DatabaseConnectionError( const char * Decription,const char * Action);

long EL_DatabaseConnectionError( sEventLogMessage &EventLogMessage, const char * Decription,const char * Action);

long EL_DatabaseReconnect( const char * table,const char * user,const char * pwd,const char * url);

long EL_DatabaseReconnect( sEventLogMessage &EventLogMessage, const char * table,const char * user,const char * pwd,const char * url);

long EL_DataProviderReadError( const char * Message);

long EL_DataProviderReadError( sEventLogMessage &EventLogMessage, const char * Message);

long EL_DataProviderValidation( const char * Message);

long EL_DataProviderValidation( sEventLogMessage &EventLogMessage, const char * Message);

long EL_ErrorConnectingProxy( const char * ProxyName,const char * Description);

long EL_ErrorConnectingProxy( sEventLogMessage &EventLogMessage, const char * ProxyName,const char * Description);

long EL_ErrorDetectingHeat( const char * HeatID,const char * TreatID,const char * EventMessage);

long EL_ErrorDetectingHeat( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * EventMessage);

long EL_ErrorDetectingProxy( const char * ProxyName,const char * Description);

long EL_ErrorDetectingProxy( sEventLogMessage &EventLogMessage, const char * ProxyName,const char * Description);

long EL_ErrorHandlingBatch( const char * Name,const char * Description);

long EL_ErrorHandlingBatch( sEventLogMessage &EventLogMessage, const char * Name,const char * Description);

long EL_ErrorHandlingDateTime();

long EL_ErrorHandlingDateTime( sEventLogMessage &EventLogMessage );

long EL_ErrorHandlingRecipe( const char * RecipeName,const char * DefaultRecipeName);

long EL_ErrorHandlingRecipe( sEventLogMessage &EventLogMessage, const char * RecipeName,const char * DefaultRecipeName);

long EL_ErrorHandlingSample( const char * HeatID,const char * TreatID,const char * PlantID,const char * SampleId);

long EL_ErrorHandlingSample( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID,const char * SampleId);

long EL_ErrorProcessingData( const char * Function,const char * Params);

long EL_ErrorProcessingData( sEventLogMessage &EventLogMessage, const char * Function,const char * Params);

long EL_ErrorRegisterProxy( const char * ListName,const char * Description);

long EL_ErrorRegisterProxy( sEventLogMessage &EventLogMessage, const char * ListName,const char * Description);

long EL_ErrorSearchingData( const char * SearchKey,const char * TableName);

long EL_ErrorSearchingData( sEventLogMessage &EventLogMessage, const char * SearchKey,const char * TableName);

long EL_EventChannelMessage( const char * Message);

long EL_EventChannelMessage( sEventLogMessage &EventLogMessage, const char * Message);

long EL_EventSuccessfullyExecuted( const char * Message);

long EL_EventSuccessfullyExecuted( sEventLogMessage &EventLogMessage, const char * Message);

long EL_HeatAnnoucementAdditional( const char * HeatID,const char * TreatID,const char * PlantID);

long EL_HeatAnnoucementAdditional( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID);

long EL_HeatAnnouncementRepeated( const char * HeatID,const char * TreatID,const char * PlantID);

long EL_HeatAnnouncementRepeated( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID);

long EL_HeatAnnouncementError( const char * HeatID,const char * TreatID,const char * PlantID);

long EL_HeatAnnouncementError( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID);

long EL_InconsistentDataReceived( const char * DataDescription,const char * EventMessage);

long EL_InconsistentDataReceived( sEventLogMessage &EventLogMessage, const char * DataDescription,const char * EventMessage);

long EL_LiquidAdditionCharged( int LiqAddnNo,double Weight);

long EL_LiquidAdditionCharged( sEventLogMessage &EventLogMessage, int LiqAddnNo,double Weight);

long EL_LiquidAdditionNotFound();

long EL_LiquidAdditionNotFound( sEventLogMessage &EventLogMessage );

long EL_ModelAvailable( const char * ProcessName);

long EL_ModelAvailable( sEventLogMessage &EventLogMessage, const char * ProcessName);

long EL_ProcessAvailable( const char * ProcessName,const char * Usage);

long EL_ProcessAvailable( sEventLogMessage &EventLogMessage, const char * ProcessName,const char * Usage);

long EL_HeatAssignedToModel( const char * HeatID,const char * TreatID,const char * ModelName);

long EL_HeatAssignedToModel( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * ModelName);

long EL_HeatDeassignedFromModel( const char * HeatID,const char * TreatID,const char * ModelName);

long EL_HeatDeassignedFromModel( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * ModelName);

long EL_StateTransition( const char * KindOfTransition,const char * prevState,const char * newState,const char * product,const char * event);

long EL_StateTransition( sEventLogMessage &EventLogMessage, const char * KindOfTransition,const char * prevState,const char * newState,const char * product,const char * event);

long EL_SteelWeightComp( double HDWeight,double HHWeight);

long EL_SteelWeightComp( sEventLogMessage &EventLogMessage, double HDWeight,double HHWeight);

long EL_UnspecificEventReceived();

long EL_UnspecificEventReceived( sEventLogMessage &EventLogMessage );

long EL_UseOfProdPracPt( const char * Type,int ProdPrac,const char * ColumnName);

long EL_UseOfProdPracPt( sEventLogMessage &EventLogMessage, const char * Type,int ProdPrac,const char * ColumnName);

long EL_ViolationColPrecision( const char * TableName,const char * Col,const char * Old,const char * New);

long EL_ViolationColPrecision( sEventLogMessage &EventLogMessage, const char * TableName,const char * Col,const char * Old,const char * New);

long EL_ErrorTelegramFrequency( const char * TelegramName,int Amount,int Seconds);

long EL_ErrorTelegramFrequency( sEventLogMessage &EventLogMessage, const char * TelegramName,int Amount,int Seconds);

long EL_InvalidMaterialCode( const char * MaterialCode);

long EL_InvalidMaterialCode( sEventLogMessage &EventLogMessage, const char * MaterialCode);

long EL_TerminatingCyclicTrigger( const char * Event,const char * HeatID,const char * TreatID);

long EL_TerminatingCyclicTrigger( sEventLogMessage &EventLogMessage, const char * Event,const char * HeatID,const char * TreatID);

long EL_ErrorHeatDataConversion( const char * HeatID,const char * TreatID,const char * Plant);

long EL_ErrorHeatDataConversion( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * Plant);

long EL_ErrorHeatDataConversion( const char * HeatID,const char * TreatID,const char * Plant,const char * Message);

long EL_ErrorHeatDataConversion( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * Plant,const char * Message);

long EL_ErrorPlantDataConversion( const char * Plant,int PlantNo);

long EL_ErrorPlantDataConversion( sEventLogMessage &EventLogMessage, const char * Plant,int PlantNo);

long EL_ErrorPlantDataConversion( const char * Plant);

long EL_ErrorPlantDataConversion( sEventLogMessage &EventLogMessage, const char * Plant);

long EL_ErrorPlantDataConversion( int PlantNo);

long EL_ErrorPlantDataConversion( sEventLogMessage &EventLogMessage, int PlantNo);

long EL_ErrorFormattedIdHandling( const char * Type,const char * ErrorMessage);

long EL_ErrorFormattedIdHandling( sEventLogMessage &EventLogMessage, const char * Type,const char * ErrorMessage);

long EL_HandlingTelegramData( const char * Telegram);

long EL_HandlingTelegramData( sEventLogMessage &EventLogMessage, const char * Telegram);

long EL_NoProdPracPtAssigned( const char * Type,const char * HeatID,const char * TreatID,const char * PlantID);

long EL_NoProdPracPtAssigned( sEventLogMessage &EventLogMessage, const char * Type,const char * HeatID,const char * TreatID,const char * PlantID);

long EL_LostTelegramInQueue( const char * ProcessName,const char * TelegramName);

long EL_LostTelegramInQueue( sEventLogMessage &EventLogMessage, const char * ProcessName,const char * TelegramName);

long EL_LostConnection( const char * ProcessName);

long EL_LostConnection( sEventLogMessage &EventLogMessage, const char * ProcessName);

long EL_PredictionCalculationError( const char * CustHeatID,const char * CustTreatID,const char * PlantID);

long EL_PredictionCalculationError( sEventLogMessage &EventLogMessage, const char * CustHeatID,const char * CustTreatID,const char * PlantID);

long EL_MaterialCodeUndefined( const char * MatCode);

long EL_MaterialCodeUndefined( sEventLogMessage &EventLogMessage, const char * MatCode);

long EL_HeatNotInProduction( const char * CustHeatID,const char * CustTreatID,const char * PlantID);

long EL_HeatNotInProduction( sEventLogMessage &EventLogMessage, const char * CustHeatID,const char * CustTreatID,const char * PlantID);

long EL_HeatAlreadyInProduction( const char * CustHeatID,const char * CustTreatID,const char * PlantID);

long EL_HeatAlreadyInProduction( sEventLogMessage &EventLogMessage, const char * CustHeatID,const char * CustTreatID,const char * PlantID);

long EL_HeatStatusChanged( const char * HeatID,const char * TreatID,const char * Plant,const char * NewStatus);

long EL_HeatStatusChanged( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * Plant,const char * NewStatus);

long EL_InvalidTemperature( const char * CustHeatID,double Temperature);

long EL_InvalidTemperature( sEventLogMessage &EventLogMessage, const char * CustHeatID,double Temperature);

long EL_LiquidMaterialReport( const char * Ladle,const char * WgtType,double Weight);

long EL_LiquidMaterialReport( sEventLogMessage &EventLogMessage, const char * Ladle,const char * WgtType,double Weight);

long EL_SteelGradeUpdate( const char * CustHeatID,const char * CustTreatID,const char * GradeBefore,const char * GradeAfter,const char * OrderBefore,const char * OrderAfter);

long EL_SteelGradeUpdate( sEventLogMessage &EventLogMessage, const char * CustHeatID,const char * CustTreatID,const char * GradeBefore,const char * GradeAfter,const char * OrderBefore,const char * OrderAfter);

long EL_OrderChanged( const char * CustHeatID,const char * CustTreatID,const char * Plant,const char * OrderAfter);

long EL_OrderChanged( sEventLogMessage &EventLogMessage, const char * CustHeatID,const char * CustTreatID,const char * Plant,const char * OrderAfter);

long EL_SteelGradeChanged( const char * CustHeatID,const char * CustTreatID,const char * Plant,const char * GradeAfter);

long EL_SteelGradeChanged( sEventLogMessage &EventLogMessage, const char * CustHeatID,const char * CustTreatID,const char * Plant,const char * GradeAfter);

long EL_ProdPracChanged( const char * Grade,const char * Type,int Number,const char * CustHeatID,const char * CustTreatID,const char * Plant);

long EL_ProdPracChanged( sEventLogMessage &EventLogMessage, const char * Grade,const char * Type,int Number,const char * CustHeatID,const char * CustTreatID,const char * Plant);

long EL_ProdPracNotDefined( const char * Grade);

long EL_ProdPracNotDefined( sEventLogMessage &EventLogMessage, const char * Grade);

long EL_NoChangeOfProdPrac();

long EL_NoChangeOfProdPrac( sEventLogMessage &EventLogMessage );

long EL_ErrorHeatStatusChange( const char * HeatID,const char * TreatID,const char * Plant,const char * NewStatus);

long EL_ErrorHeatStatusChange( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * Plant,const char * NewStatus);

long EL_ErrorHandlingAnalysis( const char * HeatID,const char * TreatID,const char * Plant,const char * Message);

long EL_ErrorHandlingAnalysis( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * Plant,const char * Message);

long EL_HandlingNotUsableAnalysis( const char * HeatID,const char * TreatID,const char * Plant,const char * Message);

long EL_HandlingNotUsableAnalysis( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * Plant,const char * Message);

long EL_UsingDefaultSample( const char * SampleId,const char * DefaultSampleId);

long EL_UsingDefaultSample( sEventLogMessage &EventLogMessage, const char * SampleId,const char * DefaultSampleId);

long EL_ModelNotAvailable( const char * ProcessName,const char * Message);

long EL_ModelNotAvailable( sEventLogMessage &EventLogMessage, const char * ProcessName,const char * Message);

long EL_InvalidTlgData( const char * TlgName,const char * Element,const char * Value);

long EL_InvalidTlgData( sEventLogMessage &EventLogMessage, const char * TlgName,const char * Element,const char * Value);

long EL_InvalidTlgData( const char * TlgName,const char * Element,int Value);

long EL_InvalidTlgData( sEventLogMessage &EventLogMessage, const char * TlgName,const char * Element,int Value);

long EL_InvalidTlgData( const char * TlgName,const char * Element,int Value,int Min,int Max);

long EL_InvalidTlgData( sEventLogMessage &EventLogMessage, const char * TlgName,const char * Element,int Value,int Min,int Max);

long EL_InvalidTlgData( const char * TlgName,const char * Element,double Value,double Min,double Max);

long EL_InvalidTlgData( sEventLogMessage &EventLogMessage, const char * TlgName,const char * Element,double Value,double Min,double Max);

long EL_ErrorReceivingModelResult( const char * HeatID,const char * TreatID,const char * PlantID,const char * Message);

long EL_ErrorReceivingModelResult( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID,const char * Message);

long EL_ErrorHandlingTelegram( const char * TlgName,const char * Message);

long EL_ErrorHandlingTelegram( sEventLogMessage &EventLogMessage, const char * TlgName,const char * Message);

long EL_MaterialAvailabilityChanged( int Available,const char * MatCode,const char * Source);

long EL_MaterialAvailabilityChanged( sEventLogMessage &EventLogMessage, int Available,const char * MatCode,const char * Source);

long EL_MaterialAvailabilityUnused();

long EL_MaterialAvailabilityUnused( sEventLogMessage &EventLogMessage );

long EL_ErrorPointerHandling( const char * Function,const char * Message);

long EL_ErrorPointerHandling( sEventLogMessage &EventLogMessage, const char * Function,const char * Message);

long EL_ErrorMessage( const char * Message);

long EL_ErrorMessage( sEventLogMessage &EventLogMessage, const char * Message);

long EL_TelegramHandled( const char * Telegram,const char * Message);

long EL_TelegramHandled( sEventLogMessage &EventLogMessage, const char * Telegram,const char * Message);

long EL_HeatDetected( const char * HeatID,const char * TreatID,const char * EventMessage);

long EL_HeatDetected( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * EventMessage);

long EL_ErrorMultipleHeatAssignment();

long EL_ErrorMultipleHeatAssignment( sEventLogMessage &EventLogMessage );

long EL_MeasurementRejected( const char * MeasType,double MeasValue);

long EL_MeasurementRejected( sEventLogMessage &EventLogMessage, const char * MeasType,double MeasValue);

long EL_LadleAssignmentPlanningData( const char * LadleType,int LadleNo);

long EL_LadleAssignmentPlanningData( sEventLogMessage &EventLogMessage, const char * LadleType,int LadleNo);

long EL_LadleAssignmentPretreatmentData( const char * LadleType,int LadleNo);

long EL_LadleAssignmentPretreatmentData( sEventLogMessage &EventLogMessage, const char * LadleType,int LadleNo);

long EL_ErrorSteelGradePractice( const char * PracticeName,const char * SteelGradeCode);

long EL_ErrorSteelGradePractice( sEventLogMessage &EventLogMessage, const char * PracticeName,const char * SteelGradeCode);

long EL_ResettingData( const char * Data,const char * HeatID,const char * TreatID,const char * Plant);

long EL_ResettingData( sEventLogMessage &EventLogMessage, const char * Data,const char * HeatID,const char * TreatID,const char * Plant);

long EL_RejectingRecipe( const char * RecipeName,const char * HeatID,const char * TreatID,const char * Plant);

long EL_RejectingRecipe( sEventLogMessage &EventLogMessage, const char * RecipeName,const char * HeatID,const char * TreatID,const char * Plant);

long EL_TrackingState( const char * ActState);

long EL_TrackingState( sEventLogMessage &EventLogMessage, const char * ActState);

long EL_ErrorStateTransition( const char * StatusName,const char * ActStatus,const char * NewStatus);

long EL_ErrorStateTransition( sEventLogMessage &EventLogMessage, const char * StatusName,const char * ActStatus,const char * NewStatus);

long EL_HeatScheduleUpdate( const char * CustHeatID,const char * CustTreatID,const char * OrderID);

long EL_HeatScheduleUpdate( sEventLogMessage &EventLogMessage, const char * CustHeatID,const char * CustTreatID,const char * OrderID);

long EL_ErrorOrderData( const char * OrderID,const char * CustHeatID,const char * CustTreatID,const char * Message);

long EL_ErrorOrderData( sEventLogMessage &EventLogMessage, const char * OrderID,const char * CustHeatID,const char * CustTreatID,const char * Message);

long EL_ErrorHeatAlreadyInProduction( const char * CustHeatID,const char * CustTreatID,const char * PlantID);

long EL_ErrorHeatAlreadyInProduction( sEventLogMessage &EventLogMessage, const char * CustHeatID,const char * CustTreatID,const char * PlantID);

long EL_OrderData( const char * OrderID,const char * CustHeatID,const char * CustTreatID,const char * Plant);

long EL_OrderData( sEventLogMessage &EventLogMessage, const char * OrderID,const char * CustHeatID,const char * CustTreatID,const char * Plant);

long EL_HeatScheduleUpdate( const char * CustHeatID,const char * CustTreatID,const char * OrderID,const char * Message);

long EL_HeatScheduleUpdate( sEventLogMessage &EventLogMessage, const char * CustHeatID,const char * CustTreatID,const char * OrderID,const char * Message);

long EL_ErrorUnknownHeatStart( const char * HeatID,const char * TreatmentPos);

long EL_ErrorUnknownHeatStart( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatmentPos);

long EL_Analysis( const char * Elem1,double AnlVal1,const char * Elem2,double AnlVal2,const char * Elem3,double AnlVal3,const char * Elem4,double AnlVal4,const char * Elem5,double AnlVale5,const char * Elem6,double AnlVale6,const char * Elem7,double AnlVale7);

long EL_Analysis( sEventLogMessage &EventLogMessage, const char * Elem1,double AnlVal1,const char * Elem2,double AnlVal2,const char * Elem3,double AnlVal3,const char * Elem4,double AnlVal4,const char * Elem5,double AnlVale5,const char * Elem6,double AnlVale6,const char * Elem7,double AnlVale7);

long EL_InitialHeatPropertyChanged( const char * Type,const char * CurrentValue,const char * NewValue);

long EL_InitialHeatPropertyChanged( sEventLogMessage &EventLogMessage, const char * Type,const char * CurrentValue,const char * NewValue);

long EL_UserNotFound( const char * PlantID);

long EL_UserNotFound( sEventLogMessage &EventLogMessage, const char * PlantID);

long EL_AddedProduct( const char * ProductID);

long EL_AddedProduct( sEventLogMessage &EventLogMessage, const char * ProductID);

long EL_RecipeConversion( int L1RecNo);

long EL_RecipeConversion( sEventLogMessage &EventLogMessage, int L1RecNo);

long EL_RecipeConversion( const char * RecipeName,int RecipeNo);

long EL_RecipeConversion( sEventLogMessage &EventLogMessage, const char * RecipeName,int RecipeNo);

long EL_LogMessageLost( int Size);

long EL_LogMessageLost( sEventLogMessage &EventLogMessage, int Size);

long EL_ErrorWrongHeatingModeStarted( int L1HeatingMode,int L2HeatingMode);

long EL_ErrorWrongHeatingModeStarted( sEventLogMessage &EventLogMessage, int L1HeatingMode,int L2HeatingMode);

long EL_StatusNotChanged( const char * PlantID,const char * StatusName,int Status);

long EL_StatusNotChanged( sEventLogMessage &EventLogMessage, const char * PlantID,const char * StatusName,int Status);

long EL_ErrorHandlingLadleData( const char * LadleType,int LadleNo,const char * Message);

long EL_ErrorHandlingLadleData( sEventLogMessage &EventLogMessage, const char * LadleType,int LadleNo,const char * Message);

long EL_ChangeEquipmentThermalStatus( const char * EquipmentName,const char * ThermStatus);

long EL_ChangeEquipmentThermalStatus( sEventLogMessage &EventLogMessage, const char * EquipmentName,const char * ThermStatus);

long EL_HeatAnnouncementModelError( const char * HeatID,const char * TreatID,const char * PlantID);

long EL_HeatAnnouncementModelError( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID);

long EL_ErrorUnknownLadleReceived( const char * LadleType,const char * LadleNo);

long EL_ErrorUnknownLadleReceived( sEventLogMessage &EventLogMessage, const char * LadleType,const char * LadleNo);

long EL_ErrorUnknownScrapContainerNoReceived( const char * ContainerNo);

long EL_ErrorUnknownScrapContainerNoReceived( sEventLogMessage &EventLogMessage, const char * ContainerNo);

long EL_ErrorHandlingCyclicData( const char * Measurement,const char * Function,const char * Message);

long EL_ErrorHandlingCyclicData( sEventLogMessage &EventLogMessage, const char * Measurement,const char * Function,const char * Message);

long EL_InvalidTlgDataToDefault( const char * TlgName,const char * Element,int Value,int Min,int Max,int Default);

long EL_InvalidTlgDataToDefault( sEventLogMessage &EventLogMessage, const char * TlgName,const char * Element,int Value,int Min,int Max,int Default);

long EL_InvalidTlgDataToDefault( const char * TlgName,const char * Element,double Value,double Min,double Max,double Default);

long EL_InvalidTlgDataToDefault( sEventLogMessage &EventLogMessage, const char * TlgName,const char * Element,double Value,double Min,double Max,double Default);

long EL_ErrorHandlingScrapContainerData( const char * ContainerType,int ScrapContainerNo,const char * Message);

long EL_ErrorHandlingScrapContainerData( sEventLogMessage &EventLogMessage, const char * ContainerType,int ScrapContainerNo,const char * Message);

long EL_Analysis( const char * Elem1,const char * AnlVal1,const char * Elem2,const char * AnlVal2,const char * Elem3,const char * AnlVal3,const char * Elem4,const char * AnlVal4,const char * Elem5,const char * AnlVale5);

long EL_Analysis( sEventLogMessage &EventLogMessage, const char * Elem1,const char * AnlVal1,const char * Elem2,const char * AnlVal2,const char * Elem3,const char * AnlVal3,const char * Elem4,const char * AnlVal4,const char * Elem5,const char * AnlVale5);

long EL_SteelGradeChanged( const char * NewSteelGrade);

long EL_SteelGradeChanged( sEventLogMessage &EventLogMessage, const char * NewSteelGrade);

long EL_ErrorHandlingDateTime( const char * Description);

long EL_ErrorHandlingDateTime( sEventLogMessage &EventLogMessage, const char * Description);

long EL_LostTelegramInQueue( const char * ConnectString,const char * ProcessName,const char * TelegramName);

long EL_LostTelegramInQueue( sEventLogMessage &EventLogMessage, const char * ConnectString,const char * ProcessName,const char * TelegramName);

long EL_HeatNotInProduction( const char * CustHeatID,const char * CustTreatID);

long EL_HeatNotInProduction( sEventLogMessage &EventLogMessage, const char * CustHeatID,const char * CustTreatID);

long EL_ScrapContainerDischargedError( int ContainerInSeq,int ContainerNo);

long EL_ScrapContainerDischargedError( sEventLogMessage &EventLogMessage, int ContainerInSeq,int ContainerNo);

long EL_ErrorHeatingModeHeatAlreadyStarted( const char * CustHeatID);

long EL_ErrorHeatingModeHeatAlreadyStarted( sEventLogMessage &EventLogMessage, const char * CustHeatID);

long EL_InvalidLadle( const char * LadleType,int LadleNo,const char * Message);

long EL_InvalidLadle( sEventLogMessage &EventLogMessage, const char * LadleType,int LadleNo,const char * Message);

long EL_InvalidProductionOrder( const char * OrderId,const char * Message);

long EL_InvalidProductionOrder( sEventLogMessage &EventLogMessage, const char * OrderId,const char * Message);

long EL_HMAnalysisAssignmentError( const char * HMLadleID,int SampleRef);

long EL_HMAnalysisAssignmentError( sEventLogMessage &EventLogMessage, const char * HMLadleID,int SampleRef);

long EL_HotMetalAnalysisReceived( const char * HotMetalID,const char * Elem1,double AnlVal1,const char * Elem2,double AnlVal2,const char * Elem3,double AnlVal3,const char * Elem4,double AnlVal4,const char * Elem5,double AnlVale5,const char * Elem6,double AnlVale6,const char * Elem7,double AnlVale7);

long EL_HotMetalAnalysisReceived( sEventLogMessage &EventLogMessage, const char * HotMetalID,const char * Elem1,double AnlVal1,const char * Elem2,double AnlVal2,const char * Elem3,double AnlVal3,const char * Elem4,double AnlVal4,const char * Elem5,double AnlVale5,const char * Elem6,double AnlVale6,const char * Elem7,double AnlVale7);

long EL_InvalidHotMetalId( const char * HotMetalID);

long EL_InvalidHotMetalId( sEventLogMessage &EventLogMessage, const char * HotMetalID);

long EL_HotMetalTemperatureReceived( const char * HotMetalID,double MeasTemp);

long EL_HotMetalTemperatureReceived( sEventLogMessage &EventLogMessage, const char * HotMetalID,double MeasTemp);

long EL_HMTemperatureAssignmentError( const char * HMLadleID,int SampleRef);

long EL_HMTemperatureAssignmentError( sEventLogMessage &EventLogMessage, const char * HMLadleID,int SampleRef);

long EL_InvalidTlgDataToDefault( const char * TlgName,const char * Element,const char * Value,const char * Default);

long EL_InvalidTlgDataToDefault( sEventLogMessage &EventLogMessage, const char * TlgName,const char * Element,const char * Value,const char * Default);

long EL_ProdOrderNew( const char * OrderID,const char * UserCode);

long EL_ProdOrderNew( sEventLogMessage &EventLogMessage, const char * OrderID,const char * UserCode);

long EL_ProdOrderUpdate( const char * OrderID,const char * UserCode);

long EL_ProdOrderUpdate( sEventLogMessage &EventLogMessage, const char * OrderID,const char * UserCode);

long EL_ProdOrderDelete( const char * OrderID,const char * UserCode);

long EL_ProdOrderDelete( sEventLogMessage &EventLogMessage, const char * OrderID,const char * UserCode);

long EL_ProdOrderAlreadyExists( const char * OrderID,const char * UserCode);

long EL_ProdOrderAlreadyExists( sEventLogMessage &EventLogMessage, const char * OrderID,const char * UserCode);

long EL_ProdOrderDeleteError( const char * OrderID,const char * UserCode);

long EL_ProdOrderDeleteError( sEventLogMessage &EventLogMessage, const char * OrderID,const char * UserCode);

long EL_ProdOrderUpdateError( const char * OrderID,const char * UserCode);

long EL_ProdOrderUpdateError( sEventLogMessage &EventLogMessage, const char * OrderID,const char * UserCode);

long EL_SteelGradeNew( const char * SteelGradeCode,const char * UserCode);

long EL_SteelGradeNew( sEventLogMessage &EventLogMessage, const char * SteelGradeCode,const char * UserCode);

long EL_SteelGradeUpdate( const char * SteelGradeCode,const char * UserCode);

long EL_SteelGradeUpdate( sEventLogMessage &EventLogMessage, const char * SteelGradeCode,const char * UserCode);

long EL_SteelGradeDelete( const char * SteelGradeCode,const char * UserCode);

long EL_SteelGradeDelete( sEventLogMessage &EventLogMessage, const char * SteelGradeCode,const char * UserCode);

long EL_HeatDelete( const char * CustHeatID);

long EL_HeatDelete( sEventLogMessage &EventLogMessage, const char * CustHeatID);

long EL_HeatDeleteError( const char * CustHeatID);

long EL_HeatDeleteError( sEventLogMessage &EventLogMessage, const char * CustHeatID);

long EL_HandleHeatReport( const char * ReportReceiver,const char * CustHeatID,const char * CustTreatID,const char * Plant);

long EL_HandleHeatReport( sEventLogMessage &EventLogMessage, const char * ReportReceiver,const char * CustHeatID,const char * CustTreatID,const char * Plant);

long EL_HandleHeatReportError( const char * ReportReceiver,const char * CustHeatID,const char * CustTreatID,const char * Plant,const char * Reason);

long EL_HandleHeatReportError( sEventLogMessage &EventLogMessage, const char * ReportReceiver,const char * CustHeatID,const char * CustTreatID,const char * Plant,const char * Reason);

long EL_ApplicationSystemRestart();

long EL_ApplicationSystemRestart( sEventLogMessage &EventLogMessage );

long EL_HandleHMIOperatorAcknowledge( const char * Message);

long EL_HandleHMIOperatorAcknowledge( sEventLogMessage &EventLogMessage, const char * Message);

long EL_ConnectionError( const char * ProcessName,const char * Message);

long EL_ConnectionError( sEventLogMessage &EventLogMessage, const char * ProcessName,const char * Message);

long EL_ErrorHandlingRecipe( const char * RecipeName,int RecipeNo,const char * Message);

long EL_ErrorHandlingRecipe( sEventLogMessage &EventLogMessage, const char * RecipeName,int RecipeNo,const char * Message);

long EL_HandleRestriction( const char * Source,const char * RecipeName,const char * Purpose);

long EL_HandleRestriction( sEventLogMessage &EventLogMessage, const char * Source,const char * RecipeName,const char * Purpose);

long EL_HandleGeneratedSampleId( const char * SampleId);

long EL_HandleGeneratedSampleId( sEventLogMessage &EventLogMessage, const char * SampleId);

long EL_HandleSubmittedSampleId( const char * SampleId);

long EL_HandleSubmittedSampleId( sEventLogMessage &EventLogMessage, const char * SampleId);

long EL_ErrorHandlingRestriction( const char * RestrictionName,const char * Plant,int Practice,int TreatModeNo);

long EL_ErrorHandlingRestriction( sEventLogMessage &EventLogMessage, const char * RestrictionName,const char * Plant,int Practice,int TreatModeNo);

long EL_ErrorLadleIdGeneration( const char * Function,const char * LadleType,int LadleNo);

long EL_ErrorLadleIdGeneration( sEventLogMessage &EventLogMessage, const char * Function,const char * LadleType,int LadleNo);

long EL_ErrorLadleIdGeneration( const char * Function,const char * LadleId);

long EL_ErrorLadleIdGeneration( sEventLogMessage &EventLogMessage, const char * Function,const char * LadleId);

long EL_CreatePretreatmentData( const char * HeatID,const char * TreatID,const char * Plant);

long EL_CreatePretreatmentData( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * Plant);

long EL_ProcessMonitorSwitchOffCompMode( const char * PRODUCT,const char * PLANT);

long EL_ProcessMonitorSwitchOffCompMode( sEventLogMessage &EventLogMessage, const char * PRODUCT,const char * PLANT);

long EL_RecipeConversion( int OldRecipeNo,int NewRecipeNo,const char * Recipe);

long EL_RecipeConversion( sEventLogMessage &EventLogMessage, int OldRecipeNo,int NewRecipeNo,const char * Recipe);

long EL_MaterialCodeDefinitionInserted( const char * MatCode);

long EL_MaterialCodeDefinitionInserted( sEventLogMessage &EventLogMessage, const char * MatCode);

long EL_MaterialCodeDefinitionAltered( const char * MatCode);

long EL_MaterialCodeDefinitionAltered( sEventLogMessage &EventLogMessage, const char * MatCode);

long EL_MaterialCodeDefinitionDeleted( const char * MatCode);

long EL_MaterialCodeDefinitionDeleted( sEventLogMessage &EventLogMessage, const char * MatCode);

long EL_RecipeWithoutMaterials( const char * RecipeName,int RecipeNo,int RecipeStatus);

long EL_RecipeWithoutMaterials( sEventLogMessage &EventLogMessage, const char * RecipeName,int RecipeNo,int RecipeStatus);

long EL_CreateHotMetalCounter( int HMCounter,const char * HMLadleID);

long EL_CreateHotMetalCounter( sEventLogMessage &EventLogMessage, int HMCounter,const char * HMLadleID);

long EL_EmptyHotMetalLadleDischarged( const char * HMLadleID);

long EL_EmptyHotMetalLadleDischarged( sEventLogMessage &EventLogMessage, const char * HMLadleID);

long EL_EmptyPurpose( const char * PURP_CODE,int UNITGROUPNO);

long EL_EmptyPurpose( sEventLogMessage &EventLogMessage, const char * PURP_CODE,int UNITGROUPNO);

long EL_ErrorEquipmentIdentification( const char * EQUIP_TYPE_PARENT,const char * STRUCT_SUB_ID_PARENT,const char * EQUIP_TYPE,const char * STRUCT_SUB_ID);

long EL_ErrorEquipmentIdentification( sEventLogMessage &EventLogMessage, const char * EQUIP_TYPE_PARENT,const char * STRUCT_SUB_ID_PARENT,const char * EQUIP_TYPE,const char * STRUCT_SUB_ID);

long EL_ErrorEquipmentIdentification( const char * EQUIP_TYPE,const char * STRUCT_SUB_ID);

long EL_ErrorEquipmentIdentification( sEventLogMessage &EventLogMessage, const char * EQUIP_TYPE,const char * STRUCT_SUB_ID);

long EL_ErrorEquipmentTypeIdentification( const char * EQUIP_TYPE,const char * ID,const char * PARENT_ID);

long EL_ErrorEquipmentTypeIdentification( sEventLogMessage &EventLogMessage, const char * EQUIP_TYPE,const char * ID,const char * PARENT_ID);

long EL_ErrorEquipmentTypeIdentification( const char * EQUIP_TYPE,const char * ID);

long EL_ErrorEquipmentTypeIdentification( sEventLogMessage &EventLogMessage, const char * EQUIP_TYPE,const char * ID);

long EL_ErrorEquipmentMountIdentification( const char * EQUIP_TYPE,const char * ID);

long EL_ErrorEquipmentMountIdentification( sEventLogMessage &EventLogMessage, const char * EQUIP_TYPE,const char * ID);

long EL_NextHeatNotReadyForAnnounce();

long EL_NextHeatNotReadyForAnnounce( sEventLogMessage &EventLogMessage );

long EL_NoHeatForAutoAnnounce();

long EL_NoHeatForAutoAnnounce( sEventLogMessage &EventLogMessage );

long EL_UseDefaultLadle( const char * LadleType,int LadleNo);

long EL_UseDefaultLadle( sEventLogMessage &EventLogMessage, const char * LadleType,int LadleNo);

long EL_ScrapContainerDataUpdate( const char * ContainerType,int ContainerNo,const char * MaterialData);

long EL_ScrapContainerDataUpdate( sEventLogMessage &EventLogMessage, const char * ContainerType,int ContainerNo,const char * MaterialData);

long EL_ChangeLadleData( const char * PrevLadleType,int PrevLadleNo,const char * ActLadleType,int ActLadleNo,int Content);

long EL_ChangeLadleData( sEventLogMessage &EventLogMessage, const char * PrevLadleType,int PrevLadleNo,const char * ActLadleType,int ActLadleNo,int Content);

long EL_RecipeConversionFailure( int L1RecNo);

long EL_RecipeConversionFailure( sEventLogMessage &EventLogMessage, int L1RecNo);

long EL_RecipeConversionFailure( const char * RecipeName,int RecipeNo);

long EL_RecipeConversionFailure( sEventLogMessage &EventLogMessage, const char * RecipeName,int RecipeNo);

long EL_UnknownAnalysisElement( const char * ElemName,double AnlVal);

long EL_UnknownAnalysisElement( sEventLogMessage &EventLogMessage, const char * ElemName,double AnlVal);

long EL_MinChargeableWeightViolated( const char * RecipeName,const char * MatCode,double Weight,double MinWeight);

long EL_MinChargeableWeightViolated( sEventLogMessage &EventLogMessage, const char * RecipeName,const char * MatCode,double Weight,double MinWeight);
};
#endif
