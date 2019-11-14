//## Copyright (C) 2011 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#include "CSMC_EventLogFrameController.h"
#include "CDataConversion.h"

#include "CGD_EQUIP_STRUCT.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGD_EQUIP_STRUCT::STRUCT_ID("STRUCT_ID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGD_EQUIP_STRUCT::EQUIP_TYPE("EQUIP_TYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGD_EQUIP_STRUCT::STRUCT_SUB_ID("STRUCT_SUB_ID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGD_EQUIP_STRUCT::ORDER_IN_LEVEL("ORDER_IN_LEVEL");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGD_EQUIP_STRUCT::PARENT_ID("PARENT_ID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGD_EQUIP_STRUCT::STRUCT_NAME("STRUCT_NAME");

//##DBClassCodeUtility ! DO NOT EDIT !
CGD_EQUIP_STRUCT::CGD_EQUIP_STRUCT(cCBS_StdConnection* Connection)
:CSMC_DBData("GD_EQUIP_STRUCT",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGD_EQUIP_STRUCT::CGD_EQUIP_STRUCT(cCBS_Connection* Connection)
:CSMC_DBData("GD_EQUIP_STRUCT",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGD_EQUIP_STRUCT::CGD_EQUIP_STRUCT()
:CSMC_DBData("GD_EQUIP_STRUCT")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGD_EQUIP_STRUCT::~CGD_EQUIP_STRUCT()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Identification of structure element
long CGD_EQUIP_STRUCT::getSTRUCT_ID(long Row)
{
  return getLong(CGD_EQUIP_STRUCT::STRUCT_ID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGD_EQUIP_STRUCT::setSTRUCT_ID(long value)
{
  setLong(CGD_EQUIP_STRUCT::STRUCT_ID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Equipment type of structure element
std::string CGD_EQUIP_STRUCT::getEQUIP_TYPE(long Row)
{
  return getString(CGD_EQUIP_STRUCT::EQUIP_TYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGD_EQUIP_STRUCT::setEQUIP_TYPE(const std::string& value)
{
  setString(CGD_EQUIP_STRUCT::EQUIP_TYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Sub Id of structure element
std::string CGD_EQUIP_STRUCT::getSTRUCT_SUB_ID(long Row)
{
  return getString(CGD_EQUIP_STRUCT::STRUCT_SUB_ID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGD_EQUIP_STRUCT::setSTRUCT_SUB_ID(const std::string& value)
{
  setString(CGD_EQUIP_STRUCT::STRUCT_SUB_ID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Order of structure element related to hierarchy level
long CGD_EQUIP_STRUCT::getORDER_IN_LEVEL(long Row)
{
  return getLong(CGD_EQUIP_STRUCT::ORDER_IN_LEVEL, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGD_EQUIP_STRUCT::setORDER_IN_LEVEL(long value)
{
  setLong(CGD_EQUIP_STRUCT::ORDER_IN_LEVEL, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Parent id of structure element
long CGD_EQUIP_STRUCT::getPARENT_ID(long Row)
{
  return getLong(CGD_EQUIP_STRUCT::PARENT_ID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGD_EQUIP_STRUCT::setPARENT_ID(long value)
{
  setLong(CGD_EQUIP_STRUCT::PARENT_ID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Name of this equipment in tree
std::string CGD_EQUIP_STRUCT::getSTRUCT_NAME(long Row)
{
  return getString(CGD_EQUIP_STRUCT::STRUCT_NAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGD_EQUIP_STRUCT::setSTRUCT_NAME(const std::string& value)
{
  setString(CGD_EQUIP_STRUCT::STRUCT_NAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGD_EQUIP_STRUCT::select(long STRUCT_ID)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGD_EQUIP_STRUCT::STRUCT_ID,STRUCT_ID);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

// selects all data on same level 
bool CGD_EQUIP_STRUCT::selectByEquipType(const std::string& EQUIP_TYPE, const std::string& STRUCT_SUB_ID)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGD_EQUIP_STRUCT::EQUIP_TYPE,EQUIP_TYPE);
  addWhereClause(CGD_EQUIP_STRUCT::STRUCT_SUB_ID,STRUCT_SUB_ID);

  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();

}

// data can be structured as follows
//                                                  STRUCT_ID   = 1
//                                                  EQUIP_TYPE  = DEF_GD_EQUIP_TYPE::SMC
// 
//                                    STRUCT_ID   = 2                                       STRUCT_ID   = 3
//                                    EQUIP_TYPE  = EAF                                     EQUIP_TYPE  = LF
//                                    PARENT_ID   = 1                                       PARENT_ID   = 1
//                                                |                                                     |
//                ----------------------------------------------------------------------------------    .......................
//                |                          |                          |                          | 
//  STRUCT_ID     = 4          STRUCT_ID     = 5          STRUCT_ID     = 6          STRUCT_ID     = 7
//  EQUIP_TYPE    = ELECTRODE  EQUIP_TYPE    = ELECTRODE  EQUIP_TYPE    = ELECTRODE  EQUIP_TYPE    = TAPHOLE 
//  PARENT_ID     = 2          PARENT_ID     = 2          PARENT_ID     = 2          PARENT_ID     = 2                          
//  STRUCT_SUB_ID = 1          STRUCT_SUB_ID = 2          STRUCT_SUB_ID = 3          STRUCT_SUB_ID = NULL
// selects all data and its complete child tree starting from EQUIP_TYPE and STRUCT_SUB_ID
bool CGD_EQUIP_STRUCT::selectStructTreeByEquipType(const std::string& EQUIP_TYPE, const std::string& STRUCT_SUB_ID)
{
  cleanWhereStatement();

  m_Statement =   "select level as depth, STRUCT_ID, EQUIP_TYPE, STRUCT_SUB_ID, ORDER_IN_LEVEL, PARENT_ID from " + m_TableName;

  m_Statement +=  " connect by prior STRUCT_ID = PARENT_ID start with EQUIP_TYPE = '" + EQUIP_TYPE + "' and STRUCT_SUB_ID = '" + STRUCT_SUB_ID +"'";

  return CSMC_DBData::select();
}

// returns vector of all struct_ids and its complete child tree starting from EQUIP_TYPE_PARENT and STRUCT_SUB_ID_PARENT
std::vector<long> CGD_EQUIP_STRUCT::getStructIdListOfParentId(const std::string& EQUIP_TYPE_PARENT, const std::string& STRUCT_SUB_ID_PARENT, const std::string& EQUIP_TYPE, const std::string& STRUCT_SUB_ID)
{
  std::vector<long> StructIdList;

  if ( selectStructTreeByEquipType(EQUIP_TYPE_PARENT, STRUCT_SUB_ID_PARENT) )
  {
    for ( long i = 1; i <= getLastRow(); ++i )
    {
      if ( (getEQUIP_TYPE(i)    == EQUIP_TYPE    || EQUIP_TYPE    == CSMC_DBData::unspecString ) &&
           (getSTRUCT_SUB_ID(i) == STRUCT_SUB_ID || STRUCT_SUB_ID == CSMC_DBData::unspecString ) )
      {
        StructIdList.push_back(getSTRUCT_ID(i));
      }
    }
  }
  else
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorEquipmentTypeIdentification(sMessage, EQUIP_TYPE_PARENT.c_str(), STRUCT_SUB_ID_PARENT.c_str());

  }

  return StructIdList;
}

//sankar
bool CGD_EQUIP_STRUCT::InsertData(long STRUCT_ID,const std::string &EQUIP_TYPE, const std::string &STRUCT_SUB_ID, long ORDER_IN_LEVEL,long PARENT_ID,const std::string &STRUCT_NAME, bool Commit, cCBS_ODBC_DBError &Error)
{
  bool RetValue = true;

  setSTRUCT_ID           (STRUCT_ID);
  setEQUIP_TYPE          (EQUIP_TYPE);
  setSTRUCT_SUB_ID       (STRUCT_SUB_ID);
  setORDER_IN_LEVEL      (ORDER_IN_LEVEL);
  setPARENT_ID           (PARENT_ID);
	setSTRUCT_NAME         (STRUCT_NAME);

  RetValue = RetValue && insert();

  if (!RetValue)
    Error = getLastError();

  if (Commit)
  {
    if (RetValue)
      commit();
    else
      rollback();
  }

  return RetValue;
}

long CGD_EQUIP_STRUCT::GetMaxSTRUCT_ID()
{
	long STRUCT_ID;

	cleanWhereStatement();

  m_Statement = "Select max(STRUCT_ID) as STRUCT_ID from " + m_TableName;

  //m_Statement += getWhereStatement();

  if ( CSMC_DBData::select() )
  {
    STRUCT_ID = getSTRUCT_ID(1);
  }

  return STRUCT_ID;
}