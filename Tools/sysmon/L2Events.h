// file name L2Events.h
// generated by genL2Events.bat(genL2Events.awk)
// from file L2Events.txt

#ifndef __L2EVENTS_H__
#define  __L2EVENTS_H__

#define EV_MST_LADLE_OPEN     100001
// i1: heatSeqNo
// f1: steel_id
// s1: heatId

#define EV_MST_LADLE_CLOSE    100002
// i1: heatSeqNo
// f1: steel_id
// f2: weight
// s1: heatId

#define EV_MST_CAST_START     100011
// i1: strandNo
// s1: heatno

#define EV_MST_CLEAR_START    100012
// i1: strandNo
// f1: castLen
// s1: heatno

#define EV_MST_CLEAR_END      100013
// i1: strandNo
// f1: castLen
// f2: clearLen

#define EV_MST_CAST_ABORT_END    100023  // Same handling as for EVCHN_TailoutEnd
#define EV_MST_CAST_ABORT_END_2  110023  // Same handling as for EVCHN_TailoutEnd

#define EV_MST_HEAT_IN_MOLD     100014 // New heat in mold
// i1: heatSeqNo
// i2: strandNo
// f1: steel_id
// s1: heat id

#define EV_MST_HEAT_ANNOUNCE  100015 // Request for heat connect/disconnect was procesed ( HMI refreshes announcement dialog)
// i1: heatSeqNo
// i2: status: 1=Heat announced, 0=Heat disconnected
// f1: steel_id
// s1: heat id

#define EV_MST_TUND_CHG       100016 // Tundish change detected by MST

#define EV_MST_COMPOUND_CAST  100017 // Compound cast detected by MST

#define EV_MST_WIDTH_CHG_START 100018 // Width change start detected
// i1: strandNo
// f1: castLen
// f2: widthBOC

#define EV_MST_WIDTH_CHG_END  100019 // Width change end detected
// i1: strandNo
// f1: castLen
// f2: widthBOC

#define EV_MST_THICK_CHG_START 100020 // Thickness change start detected
// i1: strandNo
// f1: castLen
// f2: thickHsa1

#define EV_MST_THICK_CHG_END  100021 // Thickness change end detected
// i1: strandNo
// f1: castLen
// f2: thickHsa2

#define EV_MST_RETURN_HEAT   100022  // Return heat to be sent back to melt shop
// f1: steel_id
// s1: heat id


#define EV_MST_CASTER_STATUS  100201
// i1: status
// s1: caster id

#define EV_MST_HEAT_STATUS    100202
// i1: status
// f1: steel_id
// s1: heat id

#define EV_MST_HEAT_REPORT    100203 // steel_id from PDC_HEAT, V_HEAT_REPORT
// f1: steel_id

#define EV_MST_SLAB_REPORT    100204 // after slab has been created by Tracking / steel_id from PDC_PIECE, V_SLAB_REPORT
// f1: steel_id

#define EV_MST_PRE_SLAB_REPORT 100219 // preliminary slab report for next slab ( most data not yet available )

#define EV_MST_CUT_DONE       100205
// i1: strandNo
// f1: pieceLen
// f2: cutLen

#define EV_MST_CUT_START      100206 // slabSeqNo is slab sequence number within heat and strand scope
// i1: strandNo
// i2: slabSeqNo
// f1: pieceLen
// f2: cutLen
// s1: cuttype
// s2: cutmode

#define EV_MST_CUT_ABORT      100207
// i1: strandNo
// f1: pieceLen
// f2: cutLen

#define EV_MST_SLAB_PUSHED    100220 // slab pushed off pusher table
// f1: slab steel id
// 
#define EV_MST_SYNCHRONIZE    100215 // Pos of heat in sequence, Sequence Id
// i1: HeatSeqNo
// s1: SequenceId

#define EV_MST_SLAB_REPORT_L1 100208 // Data are prepared after receiving BAS_SLAB_REQUEST
// i1: slabNo

#define EV_MST_TZ_CALC        100209 // MST calculates transition zone iteration
#define EV_MST_TZ_CALC_2      110209 // MST calculates transition zone iteration

#define EV_MST_EQUIP_COUNTER    100210 // Equipment counters for HOUR and TONS should be incremented
#define EV_MST_EQUIP_COUNTER_2  110210

#define EV_MST_GET_STATUS       100211 // MST creates caster status update  for L3
#define EV_MST_GET_STATUS_2     110211 // MST creates caster status update  for L3

#define EV_MST_SLAB_REPORT_PRM 100212 // create slab report for PRM
// f1: steel_id

#define EV_MST_NEW_MARKING_SETPOINT 100214 // new Marking Setpoints available
#define EV_MST_NEW_MARKING_SETPOINT_2 110214 // new Marking Setpoints available


#define EV_MST_CLOSE_SEQ      100213 // close sequence in case that tail cut is not received
#define EV_MST_CLOSE_SEQ_2    110213

#define EV_MST_MISSING_ANNOUNCEMENT 100216 // A new ladle was delivered, but not announced

#define EV_MST_SNDINFODATA	100217	// Tell IBAS to Send L2 Setpoint Information to Runout PLC (not used as setpoint)
// i1: L1SlabNo
#define EV_MST_SNDINFODATA_2	110217	// Tell IBAS to Send L2 Setpoint Information to Runout PLC (not used as setpoint)
// i1: L1SlabNo
#define EV_L3_NEW_HEAT_ORDER  101001 // OrderId and SlabOrderId is primary key in PPC_PROD_ORDER
// s1: OrderId

#define EV_L3_NEW_SLAB_ORDER  101002 // OrderId and SlabOrderId is primary key in PPC_SLAB_ORDER
// s1: OrderId
// s2: SlabOrderId

#define EV_L3_NEW_STEEL_GRADE 101003 // event sent after proceeding steel grade
// i1: saved

#define EV_HMI_SCHED_REQUEST  102001 // Operator request new schedule from level 3

#define EV_HMI_HEAT_ANN       102002 // Heat announcment
// i1: heat_seq_no
// i2: shiftid
// f1: seq_steel_id
// s1: heatid
// s2: orderid

#define EV_HMI_OPERATOR_INFO  102003 // Should be sent when new operator comes and before each heat announcement
// s1: operaotr
// s2: shiftid

#define EV_HMI_BLOK_CHANGE    102004 // Should be send when user changes data in blok, trigger for refresh
// s1: blokname

#define EV_HMI_HEAT_DISCONNECT 102005 // Heat announcment was canceled
// i1: heat_seq_no
// f1: seq_steel_id
// s1: heatid
// s2: orderid

#define EV_HMI_OPERATOR_INPUT 102006 // Should be sent when operator enters info about cast in dialog System overview

#define EV_HMI_EQUIP_CHNG     102007 // Operator changes mounted equipment from HMI
#define EV_HMI_EQUIP_CHNG_2   112007 // Operator changes mounted equipment from HMI
// i1: struct_id
// i2: equip_id
// s1: cust_id

#define EV_HMI_TOGGLE_SAMPLE 102008 // Toggle sample cut in CLO
// i1: StradNo 
// i2: HeatNo
// f1: SlabNo
// f2: Enabled 0,1

#define EV_HMI_AUTO_ANNOUNCEMENT 102020 // Automatic announcement from HMI, either timer expired or announcement suggestion has been confirmed by operator
// i1: result: 1 = Announcement Confirmed,  = Announcement canceled
// i2: shiftid
// f1: seq_steel_id

#define EV_HMI_FORCE_LDL_TO_ICP 102010    // force ladle in casting position (from load position)

#define EV_HMI_FORCE_LDL_DEPT_ICP 102011  // force departure of ladle from casting position

#define EV_MST_CANCEL_AUTO_ANNOUNCEMENT_POPUP 102040 // Automatic announcement from MST canceled after timer expired or confirmed anouncement

#define EV_MST_TRANS_ZONE_EST 100220 // a new Transition Zone: estimated values at ladle open
// i1 = strand no
// i2 = heat No of old heat
// f1 = weight of steel to cast before start of transition zone 
// f2 = weight of transition zone
// s1 =

#define EV_MST_TRANS_ZONE_START 100221 // a new Transition Zone Start Point on a grade change has been calculated (for CLO)
// i1 = strand no
// i2 = heat No of old heat

#define EV_MST_TRANS_ZONE_END 100222 // a new Transition Zone Start Point on a grade change has been calculated (for CLO)
// i1 = strand no
// i2 = heat No of old heat

#define EV_CLO_RESULT         103001 // New calculation is available (err_no=0 means OK)
#define EV_CLO_RESULT_2       113001 // New calculation is available (err_no=0 means OK)
// i1: err_no

#define EV_CLO_RESULT_PREREPORT 103100 // New Calculation for next slab is available (err_no=0 means OK). This event is similar to EV_CLO_RESULT, it will be send only on cut event
// i1: err_no

#define EV_CLO_RESTART        103010 // CLO will send this event to himself on restart during cast in the case that CLO detects a cast in progress, Metadata may has to be defined...

#define EV_SMC_EST_LADLE_ARR  104001 // Estimated ladle arrival from SMC
// i1: estTurretTime
// i2: estTurretTemp
// s1: heatid
// s2: lf_id

#define EV_SMC_REQ_LADLE_ARR  104002 // Required ladle arrival to SMC
// i1: castSpeed
// i2: moldWidth
// f1: remainLadleWgt
// f2: remainTundishWgt
// s1: caster id
// s2: reqTurretTime

#define EV_SMC_HEAT_DATA      104003 // Heat data received from SMC
// i1: saved
// s1: heatid

#define EV_SMC_HEAT_STATUS    104004 // Heat status received to SMC
// i1: saved
// s1: heatid
// s2: heat_status

#define EV_LAB_HEAT_ANALYSIS  104501 // New analysis received
// f1: analysis_id
// s1: heatid

#define EV_BAS_WATER_CURVES     105001 // Data from Instrumentation PLC 3 - Water Curves
// i1: waterCurveNo

#define EV_BAS_AIR_TABLES     105002 // Air tables from Instrumentation PLC 3

#define EV_BAS_DEBURRER_REPORT   105003 // Deburrer Report, Drive PLC 2
#define EV_BAS_DEBURRER_REPORT_2 115003 // Deburrer Report, Drive PLC 2
// i1: slabNo
// i2: position

#define EV_BAS_SLAB_REQUEST     105004 // Slab ID Request from Drive, PLC 2
#define EV_BAS_SLAB_REQUEST_2   115004 // Slab ID Request from Drive, PLC 2
// i1: slabNo

#define EV_BAS_MARKER_DATA      105005 // Marker Data Report from Drive, PLC 2
#define EV_BAS_MARKER_DATA_2    115005 // Marker Data Report from Drive, PLC 2
// i1: slabNo
// i2: markingMode
// f1: markState
// s1: slabId
// s2: actualMarkingData

#define EV_BAS_SLAB_REPORT      105006 // Slab Leaves Machine Report - Drive PLC
#define EV_BAS_SLAB_REPORT_2    115006 // Slab Leaves Machine Report - Drive PLC
// i1: slabNo
// i2: CCSDeparturePos

#define EV_BAS_SLAB_ROUTE     105007 // Slab Route from BAS
// i1: slabNo
// i2: BASSlabRoute

#define EV_BAS_RUNOUT_SP      105101 // Data to Runout PLC 2 / Drive
// i1: slabNo
// s1: slabId
// s2: markingData

#define EV_L2_REOPEN_LOGS     106001 // after sending this event all log files are reopened - this allows to backup or delete old logs

#define EV_INT_LAST_TLG_TIME  107001 // event for storing time of last received (sent) telegram
// i1: telegramID
// s1: time

#define EV_SMON_GET_STATUS    107002 // SMON process shall get working flags from process models


#define EV_MST_IFACE_REFRESH  200001 // Corba interface of MST should take new data from Tracking

#define EV_HMI_HEAT_ANALYSIS  102009 // Operator has entered a (new) heat steel analysis
// f1: analysis_id
// s1: heatid

#define EV_MST_SLAB_REPORT_IPQS      108003  // transmits defect and scarf for slab report
// s1: slab id
// i1: scarfing code
// i2: defect code

#define EV_IPQS_RESULT                108001  // triggers reading of ipqs evaluator result
// i1: section key for which a result is available
#define EV_IPQS_INSP_RESULT           108002  // transmits defect and scarf code from manual inspection input
// s1: slab id
// i1: scarfing code
// i2: defect code

#define EV_COPT_NEWMOULDTAPERVALUE    109001 // to inform L1 about availability of new taper setpoint through CastingOpt
#define EV_COPT_NEWMOULDTAPERVALUE_2  119001
#define EV_COPT_REREADPRACTTABLES     109002 // forces CastingOpt to re-read practice table contents

#define EV_QE_NEW_SLAB_RESULT      130000 //QE model successfully evaluated slab quality data
// i1: StrandNo
// f1: steel_id (slab)
// s1: SlabID
// s2: HeatID

#define EV_QE_SCRAP_ZONE       130001 //QE model successfully trigger CLO cutting
// i1: strandNo
// f1: castLenBegin
// f2: castLenEnd
#define EV_QE_REREADPRACTTABLES       130002 //QE practicetable read once more (after HMI change)
#define EV_QE_MINUTE_AFTER_LADLE_OPEN     130003 //QE practicetable read once more (after HMI change)
// i1: strandNo
// i2: minute
// f1: steel_id (heat)
// s1: heatid
#define EV_SHM_MISSING_SHIFT_CREW_ASSIGNMENT		140001 //to inform about missing shiftplan for today

#endif
