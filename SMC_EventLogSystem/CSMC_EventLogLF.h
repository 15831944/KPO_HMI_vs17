#ifndef _CSMC_EventLogLF_h_
#define _CSMC_EventLogLF_h_

#include <string>

#include "CSMC_EventLogFrame.h"
#include "CSMC_DestCodes.h"

class CSMC_EventLogLF : public CSMC_EventLogFrame
{
protected:
  long lRetValue;
public:
  CSMC_EventLogLF(std::string sProcName = "",std::string sServiceName = "",std::string sContextName = "");

  virtual ~CSMC_EventLogLF();

long EL_SteelAnalysisReceived( const char * SampleID,const char * SampleTime);

long EL_SteelAnalysisReceived( sEventLogMessage &EventLogMessage, const char * SampleID,const char * SampleTime);

long EL_SlagAnalysisReceived( const char * SampleID,const char * SampleTime);

long EL_SlagAnalysisReceived( sEventLogMessage &EventLogMessage, const char * SampleID,const char * SampleTime);

long EL_SteelSampleTaken( const char * SampleID,const char * SampleIDLevel1,const char * SampleLocation);

long EL_SteelSampleTaken( sEventLogMessage &EventLogMessage, const char * SampleID,const char * SampleIDLevel1,const char * SampleLocation);

long EL_SlagSampleTaken( const char * SampleID,const char * SampleIDLevel1,const char * SampleLocation);

long EL_SlagSampleTaken( sEventLogMessage &EventLogMessage, const char * SampleID,const char * SampleIDLevel1,const char * SampleLocation);

long EL_ChangeLiquidAdditionData();

long EL_ChangeLiquidAdditionData( sEventLogMessage &EventLogMessage );

long EL_RemoveLiquidAdditionData();

long EL_RemoveLiquidAdditionData( sEventLogMessage &EventLogMessage );

long EL_MaterialWeighingReport( int MeasWeight,int WeighingType,const char * LadleID,const char * LadleDeslagged);

long EL_MaterialWeighingReport( sEventLogMessage &EventLogMessage, int MeasWeight,int WeighingType,const char * LadleID,const char * LadleDeslagged);

long EL_ChangePhysicalMatAvailibility( const char * MatCode);

long EL_ChangePhysicalMatAvailibility( sEventLogMessage &EventLogMessage, const char * MatCode);

long EL_HandleUpdatePurpose();

long EL_HandleUpdatePurpose( sEventLogMessage &EventLogMessage );

long EL_MatBatchCharged( const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget,int RecipeStatus);

long EL_MatBatchCharged( sEventLogMessage &EventLogMessage, const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget,int RecipeStatus);

long EL_MatBatchDischarged( const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget,int RecipeStatus);

long EL_MatBatchDischarged( sEventLogMessage &EventLogMessage, const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget,int RecipeStatus);

long EL_DisableSourceRecipe( const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget);

long EL_DisableSourceRecipe( sEventLogMessage &EventLogMessage, const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget);

long EL_EnableSourceRecipe( const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget);

long EL_EnableSourceRecipe( sEventLogMessage &EventLogMessage, const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget);

long EL_RecipeMaterialCharged( const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget);

long EL_RecipeMaterialCharged( sEventLogMessage &EventLogMessage, const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget);

long EL_RecipeMaterialDischarged( const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget);

long EL_RecipeMaterialDischarged( sEventLogMessage &EventLogMessage, const char * RecipeName,int RecipeNo,const char * RecipeSource,const char * RecipeTarget);

long EL_ModelResultCode();

long EL_ModelResultCode( sEventLogMessage &EventLogMessage );

long EL_ModelResultActualSetPoints();

long EL_ModelResultActualSetPoints( sEventLogMessage &EventLogMessage );

long EL_ModelResultRecipeSetPoints();

long EL_ModelResultRecipeSetPoints( sEventLogMessage &EventLogMessage );

long EL_SetComputerMode( const char * LadleTransferCarId,const char * Device,int Status);

long EL_SetComputerMode( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * Device,int Status);

long EL_LiquidSteelCharged();

long EL_LiquidSteelCharged( sEventLogMessage &EventLogMessage );

long EL_LiqMatHandlReport( const char * MeasWeight,const char * WeighingType,const char * LadleId,const char * LadleDeslagged);

long EL_LiqMatHandlReport( sEventLogMessage &EventLogMessage, const char * MeasWeight,const char * WeighingType,const char * LadleId,const char * LadleDeslagged);

long EL_WireFeedingStart( const char * WireFeederMatCode,const char * WireFeederLineNo);

long EL_WireFeedingStart( sEventLogMessage &EventLogMessage, const char * WireFeederMatCode,const char * WireFeederLineNo);

long EL_WireFeedingEnd( const char * WireFeederLineNo);

long EL_WireFeedingEnd( sEventLogMessage &EventLogMessage, const char * WireFeederLineNo);

long EL_ElectrodesInOperatingPosition();

long EL_ElectrodesInOperatingPosition( sEventLogMessage &EventLogMessage );

long EL_FurnaceBreakerOn();

long EL_FurnaceBreakerOn( sEventLogMessage &EventLogMessage );

long EL_FurnaceBreakerOff();

long EL_FurnaceBreakerOff( sEventLogMessage &EventLogMessage );

long EL_PowerOn();

long EL_PowerOn( sEventLogMessage &EventLogMessage );

long EL_PowerOff();

long EL_PowerOff( sEventLogMessage &EventLogMessage );

long EL_TapChangeStart( const char * VoltTapNo,const char * EltrdRegCurve);

long EL_TapChangeStart( sEventLogMessage &EventLogMessage, const char * VoltTapNo,const char * EltrdRegCurve);

long EL_TapChangeFinished( const char * VoltTapNo,const char * EltrdRegCurve);

long EL_TapChangeFinished( sEventLogMessage &EventLogMessage, const char * VoltTapNo,const char * EltrdRegCurve);

long EL_CyclicMeasurementElec( const char * CarNo,const char * VoltTapNo,const char * EltrdRegCurve,const char * ElecCons);

long EL_CyclicMeasurementElec( sEventLogMessage &EventLogMessage, const char * CarNo,const char * VoltTapNo,const char * EltrdRegCurve,const char * ElecCons);

long EL_CyclicMeasurementCool( const char * CarNo,const char * CoolWaterDevice,double InletTemp,double OutletTemp,double WaterFlow);

long EL_CyclicMeasurementCool( sEventLogMessage &EventLogMessage, const char * CarNo,const char * CoolWaterDevice,double InletTemp,double OutletTemp,double WaterFlow);

long EL_CyclicMeasurementStirring( const char * CarNo,const char * StirringDevice,const char * GasType,double GasValue);

long EL_CyclicMeasurementStirring( sEventLogMessage &EventLogMessage, const char * CarNo,const char * StirringDevice,const char * GasType,double GasValue);

long EL_CeloxMeasurement( const char * MeasCarbonConc,const char * MeasAlConc,const char * TempSampleId,const char * MeasTemp,const char * MeasO2Conc);

long EL_CeloxMeasurement( sEventLogMessage &EventLogMessage, const char * MeasCarbonConc,const char * MeasAlConc,const char * TempSampleId,const char * MeasTemp,const char * MeasO2Conc);

long EL_TempMeasurement( const char * MeasTemp,const char * TempSampleId,const char * MeasCarbonConc,const char * LadleCarPosition,const char * LadleId);

long EL_TempMeasurement( sEventLogMessage &EventLogMessage, const char * MeasTemp,const char * TempSampleId,const char * MeasCarbonConc,const char * LadleCarPosition,const char * LadleId);

long EL_DeslaggingData( const char * DeslagStartTime,const char * DeslagEndTime,const char * LadleTransferCarId,const char * LadleCarPosition,const char * LadleId);

long EL_DeslaggingData( sEventLogMessage &EventLogMessage, const char * DeslagStartTime,const char * DeslagEndTime,const char * LadleTransferCarId,const char * LadleCarPosition,const char * LadleId);

long EL_RoofArrivesInUpPosition( const char * CarNo);

long EL_RoofArrivesInUpPosition( sEventLogMessage &EventLogMessage, const char * CarNo);

long EL_RoofArrivesInDownPosition( const char * CarNo);

long EL_RoofArrivesInDownPosition( sEventLogMessage &EventLogMessage, const char * CarNo);

long EL_TransferCarPositionChanged( const char * LadleTransferCarId,const char * LadleCarPosition,const char * LadleId);

long EL_TransferCarPositionChanged( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * LadleCarPosition,const char * LadleId);

long EL_BottomStirringByPassOn( const char * LadleTransferCarId,const char * LadleId,const char * LadlePlugNo);

long EL_BottomStirringByPassOn( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * LadleId,const char * LadlePlugNo);

long EL_BottomStirringByPassOff( const char * LadleTransferCarId,const char * LadleId,const char * LadlePlugNo);

long EL_BottomStirringByPassOff( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * LadleId,const char * LadlePlugNo);

long EL_BottomStirringByPassOn( const char * LadleTransferCarId,const char * LadlePlugNo);

long EL_BottomStirringByPassOn( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * LadlePlugNo);

long EL_BottomStirringByPassOff( const char * LadleTransferCarId,const char * LadlePlugNo);

long EL_BottomStirringByPassOff( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * LadlePlugNo);

long EL_BottomStirringStart( const char * LadleTransferCarId,const char * LadleId,const char * StirrGasType,const char * LadlePlugNo);

long EL_BottomStirringStart( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * LadleId,const char * StirrGasType,const char * LadlePlugNo);

long EL_BottomStirringEnd( const char * LadleTransferCarId,const char * LadleId,const char * StirrGasType,const char * LadlePlugNo);

long EL_BottomStirringEnd( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * LadleId,const char * StirrGasType,const char * LadlePlugNo);

long EL_BottomStirringStart( const char * LadleTransferCarId,const char * StirrGasType,const char * LadlePlugNo);

long EL_BottomStirringStart( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * StirrGasType,const char * LadlePlugNo);

long EL_BottomStirringEnd( const char * LadleTransferCarId,const char * StirrGasType,const char * LadlePlugNo);

long EL_BottomStirringEnd( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * StirrGasType,const char * LadlePlugNo);

long EL_HMISetUpOfHeat();

long EL_HMISetUpOfHeat( sEventLogMessage &EventLogMessage );

long EL_HMIResetOfHeat();

long EL_HMIResetOfHeat( sEventLogMessage &EventLogMessage );

long EL_ParameterUpdate( const char * ParaArea,const char * ParaProcPT);

long EL_ParameterUpdate( sEventLogMessage &EventLogMessage, const char * ParaArea,const char * ParaProcPT);

long EL_GenParameterUpdate( const char * ParaArea,const char * ParaProcPT);

long EL_GenParameterUpdate( sEventLogMessage &EventLogMessage, const char * ParaArea,const char * ParaProcPT);

long EL_HeatAnnouncement( const char * HeatID,const char * TreatID,const char * PlantID,const char * LadleTransferCarId,const char * LadleId);

long EL_HeatAnnouncement( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID,const char * LadleTransferCarId,const char * LadleId);

long EL_HeatAnnouncementOffline( const char * HeatID,const char * TreatID,const char * PlantID,const char * LadleTransferCarId,const char * LadleId);

long EL_HeatAnnouncementOffline( sEventLogMessage &EventLogMessage, const char * HeatID,const char * TreatID,const char * PlantID,const char * LadleTransferCarId,const char * LadleId);

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

long EL_CleanlinessStirring( const char * PhaseElecAct,const char * PhaseStirrAct);

long EL_CleanlinessStirring( sEventLogMessage &EventLogMessage, const char * PhaseElecAct,const char * PhaseStirrAct);

long EL_CoolingStirring( const char * PhaseElecAct,const char * PhaseStirrAct);

long EL_CoolingStirring( sEventLogMessage &EventLogMessage, const char * PhaseElecAct,const char * PhaseStirrAct);

long EL_DelayStatus( const char * DelayPlant,const char * DelayCode,const char * DelayStartDate,const char * DelayEndDate,const char * DelayDescription);

long EL_DelayStatus( sEventLogMessage &EventLogMessage, const char * DelayPlant,const char * DelayCode,const char * DelayStartDate,const char * DelayEndDate,const char * DelayDescription);

long EL_FinalHeating( const char * PhaseElecAct,const char * PhaseStirrAct);

long EL_FinalHeating( sEventLogMessage &EventLogMessage, const char * PhaseElecAct,const char * PhaseStirrAct);

long EL_InitialHeating( const char * PhaseElecAct,const char * PhaseStirrAct);

long EL_InitialHeating( sEventLogMessage &EventLogMessage, const char * PhaseElecAct,const char * PhaseStirrAct);

long EL_MainHeating( const char * PhaseElecAct,const char * PhaseStirrAct);

long EL_MainHeating( sEventLogMessage &EventLogMessage, const char * PhaseElecAct,const char * PhaseStirrAct);

long EL_SoftStirring( const char * PhaseElecAct,const char * PhaseStirrAct);

long EL_SoftStirring( sEventLogMessage &EventLogMessage, const char * PhaseElecAct,const char * PhaseStirrAct);

long EL_CleanlinessStirring();

long EL_CleanlinessStirring( sEventLogMessage &EventLogMessage );

long EL_CoolingStirring();

long EL_CoolingStirring( sEventLogMessage &EventLogMessage );

long EL_FinalHeating();

long EL_FinalHeating( sEventLogMessage &EventLogMessage );

long EL_InitialHeating();

long EL_InitialHeating( sEventLogMessage &EventLogMessage );

long EL_MainHeating();

long EL_MainHeating( sEventLogMessage &EventLogMessage );

long EL_SoftStirring();

long EL_SoftStirring( sEventLogMessage &EventLogMessage );

long EL_TrimmingMaterialDischarged();

long EL_TrimmingMaterialDischarged( sEventLogMessage &EventLogMessage );

long EL_AlloyingMaterialDischarged();

long EL_AlloyingMaterialDischarged( sEventLogMessage &EventLogMessage );

long EL_ChangeAimData( const char * TempAim,const char * TreatEndAim);

long EL_ChangeAimData( sEventLogMessage &EventLogMessage, const char * TempAim,const char * TreatEndAim);

long EL_ChangeProdPracPointerElec( const char * ElecPracPt,const char * FlagHeatRelated);

long EL_ChangeProdPracPointerElec( sEventLogMessage &EventLogMessage, const char * ElecPracPt,const char * FlagHeatRelated);

long EL_ChangeProdPracPointerParameter( const char * ParamPracPt,const char * FlagHeatRelated);

long EL_ChangeProdPracPointerParameter( sEventLogMessage &EventLogMessage, const char * ParamPracPt,const char * FlagHeatRelated);

long EL_ChangeProdPracPointerRestriction( const char * RestriPracPt,const char * FlagHeatRelated);

long EL_ChangeProdPracPointerRestriction( sEventLogMessage &EventLogMessage, const char * RestriPracPt,const char * FlagHeatRelated);

long EL_ChangeProdPracPointerStirring( const char * StirrPracPt,const char * FlagHeatRelated);

long EL_ChangeProdPracPointerStirring( sEventLogMessage &EventLogMessage, const char * StirrPracPt,const char * FlagHeatRelated);

long EL_MaterialHandlingReport( const char * Recipename,const char * RecipeSource,const char * RecipeStatus,const char * matCode,double MatWeight);

long EL_MaterialHandlingReport( sEventLogMessage &EventLogMessage, const char * Recipename,const char * RecipeSource,const char * RecipeStatus,const char * matCode,double MatWeight);

long EL_MaterialHandlingReportCar( const char * CarNo,const char * LadleId,const char * RecipeName,const char * RecipeTarget);

long EL_MaterialHandlingReportCar( sEventLogMessage &EventLogMessage, const char * CarNo,const char * LadleId,const char * RecipeName,const char * RecipeTarget);

long EL_RecipeWeighingComplete();

long EL_RecipeWeighingComplete( sEventLogMessage &EventLogMessage );

long EL_RecipeWeighingCompleteUpdate();

long EL_RecipeWeighingCompleteUpdate( sEventLogMessage &EventLogMessage );

long EL_MinChargeableBinWeightUpdate();

long EL_MinChargeableBinWeightUpdate( sEventLogMessage &EventLogMessage );

long EL_ErrorTransferCarIdentification( const char * TransferCarId);

long EL_ErrorTransferCarIdentification( sEventLogMessage &EventLogMessage, const char * TransferCarId);

long EL_NoTransferCarInOperatingPosition();

long EL_NoTransferCarInOperatingPosition( sEventLogMessage &EventLogMessage );

long EL_TimeTempPrevPlantOutOfRange( const char * StdDurAODTap_LFHeatAnn);

long EL_TimeTempPrevPlantOutOfRange( sEventLogMessage &EventLogMessage, const char * StdDurAODTap_LFHeatAnn);

long EL_TransferCarInOperationPos( const char * LadleTransferCarId);

long EL_TransferCarInOperationPos( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId);

long EL_TransferCarOutOfOperationPos( const char * LadleTransferCarId);

long EL_TransferCarOutOfOperationPos( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId);

long EL_EquipmentIdentification();

long EL_EquipmentIdentification( sEventLogMessage &EventLogMessage );

long EL_GantryInTreatmentPosition( int Position,const char * LadleTransferCarId);

long EL_GantryInTreatmentPosition( sEventLogMessage &EventLogMessage, int Position,const char * LadleTransferCarId);

long EL_GantryOutTreatmentPosition();

long EL_GantryOutTreatmentPosition( sEventLogMessage &EventLogMessage );

long EL_GantryInMaintenancePosition();

long EL_GantryInMaintenancePosition( sEventLogMessage &EventLogMessage );

long EL_SlagCeloxMeasurement( const char * MeasFeOConc,const char * MeasMnOConc);

long EL_SlagCeloxMeasurement( sEventLogMessage &EventLogMessage, const char * MeasFeOConc,const char * MeasMnOConc);

long EL_SlagWeightCalculation( int SlagWeight);

long EL_SlagWeightCalculation( sEventLogMessage &EventLogMessage, int SlagWeight);

long EL_ErrorSlagWeightCalculation();

long EL_ErrorSlagWeightCalculation( sEventLogMessage &EventLogMessage );

long EL_CreateTreatmentID();

long EL_CreateTreatmentID( sEventLogMessage &EventLogMessage );

long EL_RecipeMaterialDischarged( const char * RecipeName,const char * RecipeNo,const char * RecipeSource,const char * MatCode,const char * MatWeight);

long EL_RecipeMaterialDischarged( sEventLogMessage &EventLogMessage, const char * RecipeName,const char * RecipeNo,const char * RecipeSource,const char * MatCode,const char * MatWeight);

long EL_TempMeasurement( const char * MeasTemp,int TempSampleNo,const char * LadleCarPosition);

long EL_TempMeasurement( sEventLogMessage &EventLogMessage, const char * MeasTemp,int TempSampleNo,const char * LadleCarPosition);

long EL_MaterialHandlingReport( const char * CarNo,const char * Recipename,const char * RecipeSource,const char * RecipeStatus,const char * matCode,double MatWeight);

long EL_MaterialHandlingReport( sEventLogMessage &EventLogMessage, const char * CarNo,const char * Recipename,const char * RecipeSource,const char * RecipeStatus,const char * matCode,double MatWeight);

long EL_ChangeProdPracPointerElec( const char * ProdPracPointer);

long EL_ChangeProdPracPointerElec( sEventLogMessage &EventLogMessage, const char * ProdPracPointer);

long EL_ChangeProdPracPointerParameter( const char * ProdPracPointer);

long EL_ChangeProdPracPointerParameter( sEventLogMessage &EventLogMessage, const char * ProdPracPointer);

long EL_ChangeProdPracPointerRestriction( const char * ProdPracPointer);

long EL_ChangeProdPracPointerRestriction( sEventLogMessage &EventLogMessage, const char * ProdPracPointer);

long EL_ChangeProdPracPointerStirring( const char * ProdPracPointer);

long EL_ChangeProdPracPointerStirring( sEventLogMessage &EventLogMessage, const char * ProdPracPointer);

long EL_SetComputerModeManual( const char * LadleTransferCarId,const char * Device);

long EL_SetComputerModeManual( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * Device);

long EL_SetComputerModeAutomatic( const char * LadleTransferCarId,const char * Device);

long EL_SetComputerModeAutomatic( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * Device);

long EL_SetComputerModeDynamic( const char * LadleTransferCarId,const char * Device);

long EL_SetComputerModeDynamic( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * Device);

long EL_SetComputerModePattern( const char * LadleTransferCarId,const char * Device);

long EL_SetComputerModePattern( sEventLogMessage &EventLogMessage, const char * LadleTransferCarId,const char * Device);

long EL_DesulphurizationStirring( const char * PhaseElecAct,const char * PhaseStirrAct);

long EL_DesulphurizationStirring( sEventLogMessage &EventLogMessage, const char * PhaseElecAct,const char * PhaseStirrAct);

long EL_DesulphurizationStirring();

long EL_DesulphurizationStirring( sEventLogMessage &EventLogMessage );

long EL_ChangeAimData( const char * Steelgrade,const char * TempAim,const char * TreatEndAim,const char * AimWeight);

long EL_ChangeAimData( sEventLogMessage &EventLogMessage, const char * Steelgrade,const char * TempAim,const char * TreatEndAim,const char * AimWeight);
};
#endif
