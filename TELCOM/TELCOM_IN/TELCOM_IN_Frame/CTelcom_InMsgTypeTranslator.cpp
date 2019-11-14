// Copyright (C) 2007 SMS Siemag AG

#include "cCBS_StdInitBase.h"
#include "CDataConversion.h"

#include "CTelcom_InMsgTypeTranslator.h"

CTelcom_InMsgTypeTranslator::CTelcom_InMsgTypeTranslator()
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
    // mapping definition see in Ext_Interface_Standards
	//HMD sankar
    insert( "L2HD00", 1000);
    insert( "HDL201", 1001);
    insert( "HDL202", 1002);
    insert( "HDL203", 1003);
    insert( "HDL204", 1004);
    insert( "HDL205", 1005);
    insert( "HDL206", 1006);
    insert( "HDL209", 1009);
    insert( "HDL211", 1011);
    insert( "HDL213", 1013);
    insert( "HDL220", 1020);
    insert( "HDL221", 1021);
    insert( "HDL223", 1023);
    insert( "HDL260", 1060);
    insert( "HDL261", 1061);
    insert( "HDL270", 1070);
    insert( "HDL281", 1081);
			
	//EAF
    insert("L2EA00",2200);
    insert("EAL201",1201);
    insert("EAL203",1203);
    insert("EAL204",1204);
    insert("EAL205",1205);
    insert("EAL206",1206);
    insert("EAL207",1207);
    insert("EAL209",1209);
    insert("EAL211",1211);
    insert("EAL214",1214);
    insert("EAL215",1215);
    insert("EAL216",1216);
    insert("EAL217",1217);
    insert("EAL220",1220);
    insert("EAL221",1221);
    insert("EAL222",1222);
    insert("EAL223",1223);
    insert("EAL224",1224);
    insert("EAL225",1225);
    insert("EAL226",1226);
    insert("EAL227",1227);
    insert("EAL228",1228);
    insert("EAL229",1229);
    insert("EAL230",1230);
    insert("EAL231",1231);
    insert("EAL232",1232);
    insert("EAL233",1233);
    insert("EAL234",1234);
    insert("EAL235",1235);
    insert("EAL236",1236);
    insert("EAL237",1237);
    insert("EAL240",1240);
    insert("EAL241",1241);
    insert("EAL250",1250);
    insert("EAL260",1260);
    insert("EAL261",1261);
    insert("EAL262",1262);
    insert("EAL263",1263);
    insert("EAL270",1270);
    insert("EAL280",1280);
    insert("EAL281",1281);

    insert( "EAL260_MAT_HAND_REPORT", 3260);

    insert("SYL291",1291);
    insert("SYL292",1292);
    insert("SYL293",1293);
    insert("SYL295",1295);

	//LF
    insert( "L2LF00", 2000);
    insert( "LFL201", 1601);  
    insert( "LFL203", 1603);
    insert( "LFL204", 1604);
    insert( "LFL205", 1605);
    insert( "LFL206", 1606);
    insert( "LFL209", 1609);
    insert( "LFL211", 1611);
    insert( "LFL212", 1612);
    insert( "LFL213", 1613);
    insert( "LFL217", 1617);
    insert( "LFL220", 1620);
    insert( "LFL221", 1621);
    insert( "LFL222", 1622);
    insert( "LFL223", 1623);
    insert( "LFL224", 1624);
    insert( "LFL225", 1625);
    insert( "LFL226", 1626);
    insert( "LFL230", 1630);
    insert( "LFL240", 1640);
    insert( "LFL260", 1660);
    insert( "LFL261", 1661);
    insert( "LFL270", 1670);
    insert( "LFL281", 1681);	  
   
    /*insert( "LABSMC01", 10901);    
    insert( "LABSMC02", 10902);    
    insert( "LABSMC03", 10903);    

    insert( "CCS_CASTER_STATUS", 9998);*/    
    //insert( "CCSSMC02", 11002);    

	//sankar
	insert( "L3_ALIVE", 9901);
	insert( "L3_HEAT_SCHEDULE", 9902);
	insert( "L3_HM_LADLE", 9903);
	insert( "L3_MATERIAL_CODES", 9904);
	insert( "L3_STEELGRADES", 9905);
	insert( "L3_DELAY_CODES", 9906);
	insert( "L3_ANALYSIS_STEEL", 9907);
	insert( "L3_ANALYSIS_SLAG", 9908);
	insert( "L3_TEEMING_LADLE", 9909);
	insert( "L3_STEELGRADE_CHANGE", 9911);
	insert( "L3_LADLE_CHANGE", 9912);

	insert( "CCS_ALIVE", 9920);
	insert( "CCS_HEAT_STATUS", 9921);

	//Motor maintenance
	insert( "EAL290", 1290);
	insert( "LFL290", 1690);
	insert( "HDL290", 1090);
	


  }
}

CTelcom_InMsgTypeTranslator::~CTelcom_InMsgTypeTranslator()
{
}

