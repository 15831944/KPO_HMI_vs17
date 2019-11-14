// Copyright (C) 2007 SMS Siemag AG

#include "cCBS_StdInitBase.h"
#include "CDataConversion.h"

#include "CTelcom_OutMsgTypeTranslator.h"

CTelcom_OutMsgTypeTranslator::CTelcom_OutMsgTypeTranslator()
{
  // Read the mapping from the configuration file.
  // This is helpful if the same interface has different numbers in the same project.
  long NumberOfEntries = 0;

  cCBS_StdInitBase* CBS_StdInitBase = cCBS_StdInitBase::getInstance();
  CBS_StdInitBase->replaceWithEntry("TELEGRAM_MAPPING", "NumberOfEntries", NumberOfEntries);

  if ( NumberOfEntries < 0 )
  {
    NumberOfEntries = 0;
  }

  if ( NumberOfEntries > 0 )
  {
    std::string MessageName;
    long MessageID;
    for ( long i = 0; i < NumberOfEntries; i++ )
    {
      CBS_StdInitBase->replaceWithEntry("TELEGRAM_MAPPING", "MessageName_" + CDataConversion::LongToString(i), MessageName);
      CBS_StdInitBase->replaceWithEntry("TELEGRAM_MAPPING", "MessageID_" + CDataConversion::LongToString(i), MessageID);
      insert(MessageName,MessageID);
    }
  }
  else
  {
    // definition of mapping see Ext_Interface_Standards
    // HMD  sankar
    insert("HDL200", 2000);
    insert("L2HD01", 2001);
    insert("L2HD03", 2003);
    insert("L2HD06", 2006);
    insert("L2HD07", 2007);
    insert("L2HD25", 2025);
    insert("L2HD30", 2030);
    insert("L2HD71", 2071);
    insert("L2HD72", 2072);
    insert( "L2HD01_WATCH_DOG" , 4701);


    // EAF
    insert("EAL200", 2200);
    insert("L2EA01", 2201);
    insert("L2EA03", 2203);
    insert("L2EA05", 2205);
    insert("L2EA06", 2206);
    insert("L2EA07", 2207);
    insert("L2EA20", 2220);
    insert("L2EA23", 2223);
    insert("L2EA30", 2230);
    insert("L2EA31", 2231);
    insert("L2EA32", 2232);
    insert("L2EA40", 2240);
    insert("L2EA41", 2241);
    insert("L2EA42", 2242);
    insert("L2EA70", 2270);
    insert("L2EA71", 2271);
    insert("L2EA72", 2272);

    insert( "L2EA01_WATCH_DOG"        , 4201);
    insert( "L2EA40_PROC_PATT"        , 4240);
    insert( "L2EA41_PROC_VALUES"      , 4241);
    insert( "L2EA70_MAT_HANDL"        , 4270);


    insert( "L2SY91", 2291);
    insert( "L2SY92", 2292);
    insert( "L2SY95", 2295);

    insert( "L2SY91_WATCH_DOG"        , 4291);
    insert( "L2SY92_SCRAP_LOAD"       , 4292);
    insert( "L2SY95_SCRAP_MAT"        , 4295);
    

    insert( "LFL200", 2600);
    insert( "L2LF01", 2601);	
    insert( "L2LF03", 2603);
    insert( "L2LF05", 2605);
    insert( "L2LF06", 2606);
    insert( "L2LF07", 2607);
    insert( "L2LF20", 2620);
    insert( "L2LF22", 2622);
    insert( "L2LF23", 2623);
    insert( "L2LF25", 2625);
    insert( "L2LF30", 2630);
    insert( "L2LF31", 2631);	
    insert( "L2LF40", 2640);
    insert( "L2LF70", 2670);
    insert( "L2LF71", 2671);
    insert( "L2LF72", 2672);

    insert( "L2LF01_WATCH_DOG"        , 4601);
    insert( "L2LF20_VOLTAGE_TAP"      , 4620);
    insert( "L2LF30_ELEC_PATT"        , 4630);
    insert( "L2LF31_STIRR_PATT"       , 4631);
    insert( "L2LF70_MAT_HANDL"        , 4670);


    /*insert( "SMCLAB01", 20901);
    insert( "SMCLAB02", 20902);
    insert( "SMCLAB03", 20903);*/
    
    /*insert( "SMCCCS01", 10001);
    insert( "SMCCCS02", 10002);*/

    /*insert( "MS_HEAT_STATUS" , 40001);  // modified as per specs for JSPL agam 28 Jul 2011
    insert( "EAF_HEAT_REPORT", 40002);
    insert( "LF_HEAT_REPORT" , 40003);
    insert( "RH_HEAT_REPORT" , 40004);

    insert( "SMCIPQS01", 11901);*/

    //deb for RH 
 /*   insert( "RHL200", 2000);
	  insert( "L2RH01", 2001);
	  insert( "L2RH02", 2002);
	  insert( "L2RH03", 2003);
	  insert( "L2RH06", 2006);
	  insert( "L2RH07", 2007);
    insert( "L2RH20", 2020); 
	  insert( "L2RH25", 2025);
	  insert( "L2RH30", 2030);
	  insert( "L2RH31", 2031);
	  insert( "L2RH70", 2070);
	  insert( "L2RH71", 2071);
	  insert( "L2RH72", 2072);

    insert( "L2RH01_WATCH_DOG"        , 4001);
    insert( "L2RH31_PROCESS_PATT"  , 4031);
    insert( "L2RH70_MATERIAL_HANDLING", 4070);

    insert( "SMCL301", 2301);
    insert( "SMCL302", 2302);
    insert( "SMCL311", 2311);
    insert( "SMCL314", 2314);
    insert( "SMCL321", 2321);
    insert( "SMCL323", 2323);
    insert( "SMCL324", 2324);
    insert( "SMCL325", 2325);*/

	//sankar 
	insert( "L2_ALIVE", 8801);
    insert( "L2_SCHEDULE_RESPONSE", 8802);
    insert( "L2_HEAT_STATUS", 8803);
    insert( "L2_DELAY_REPORT", 8804);
	insert( "L2_HEAT_REPORT_MATERIAL", 8805);
	insert( "L2_EAF_HEAT_REPORT", 8806);
	insert( "L2_LF_HEAT_REPORT", 8807);
	insert( "L2_HMD_HEAT_REPORT", 8808);
	insert( "L2_SAMPLE_TAKEN", 8809);
	insert( "L2_TEMPERATURE_TAKEN", 8810);
	insert( "L2_ESTMT_LADLE_ARRIVAL", 8820);
    insert( "L2_HEAT_DATA", 8821);
    insert( "L2_ANALYSIS_STEEL", 8822);
    insert( "L2_ANALYSIS_SLAG", 8823);
    
    
 
  }
}

CTelcom_OutMsgTypeTranslator::~CTelcom_OutMsgTypeTranslator()
{
}

