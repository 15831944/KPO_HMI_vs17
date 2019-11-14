//## Copyright (C) 2010 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CPD_SCRAP_CONTAINER_ORDER_INCLUDED
#define _INC_CPD_SCRAP_CONTAINER_ORDER_INCLUDED

#include "CSMC_DBData.h"

class CPD_SCRAP_CONTAINER_ORDER
: public CSMC_DBData
{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PLANT;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PRODORDERID;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CONTAINERINSEQ;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STATUSNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CONTAINERNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CONTAINERTYPE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CONTAINERLAST;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string ORDERTIME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DISCHARGETIME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string REVTIME;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPD_SCRAP_CONTAINER_ORDER(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPD_SCRAP_CONTAINER_ORDER(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPD_SCRAP_CONTAINER_ORDER();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CPD_SCRAP_CONTAINER_ORDER();

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Plant identifier
  std::string getPLANT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPLANT(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Production order identifier
  std::string getPRODORDERID(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPRODORDERID(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Identifies the order within in charging sequence
  long getCONTAINERINSEQ(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCONTAINERINSEQ(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Number of the order status
  long getSTATUSNO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTATUSNO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Unique identification number
  long getCONTAINERNO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCONTAINERNO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##basket or chute
  std::string getCONTAINERTYPE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCONTAINERTYPE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Identifies the last container in a charging sequence -> 1
  long getCONTAINERLAST(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCONTAINERLAST(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##For displaying the scrap container in corresponding assignment dialog
  CDateTime getORDERTIME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setORDERTIME(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CDateTime getDISCHARGETIME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDISCHARGETIME(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Date and time of last revision
  CDateTime getREVTIME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setREVTIME(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(const std::string& PLANT, const std::string& PRODORDERID, long CONTAINERINSEQ);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

  bool selectByContainerNoAndType( const std::string& PLANT, const std::string& PRODORDERID, long CONTAINERINSEQ, long CONTAINERNO, const std::string& CONTAINERTYPE  );

  bool selectByContainerState( const std::string& PLANT, const std::string& PRODORDERID, long STATUSNO, bool ASC = true);

  bool selectByContainerType( const std::string& PLANT, const std::string& PRODORDERID, const std::string& CONTAINERTYPE);

  bool selectByContainerTypeAndState( const std::string& PLANT, const std::string& PRODORDERID, long CONTAINERINSEQ, long CONTAINERNO, const std::string& CONTAINERTYPE, long STATUSNO  );

  bool selectByContainerTypeAndState( const std::string& PLANT, const std::string& PRODORDERID, const std::string& CONTAINERTYPE, long STATUSNO  );

  bool selectByContainerTypeAndState( const std::string& PLANT, const std::string& PRODORDERID, const std::string& CONTAINERTYPE, std::vector<long> StatusNoList  );

  bool selectLastOrder(const std::string& PLANT, const std::string& CONTAINERTYPE);

  bool selectOrderedButNotCharged(const string& PLANT, const string& PRODORDERID, long CONTAINERNO, const string& CONTAINERTYPE);

  bool deleteData( const std::string& PLANT, const std::string& PRODORDERID, long CONTAINERINSEQ, const std::string& CONTAINERTYPE );

  bool deletePlannedDataOnDeparture(const std::string& PLANT, const std::string& PRODORDERID, cCBS_ODBC_DBError &Error);

  bool exists(const std::string& PLANT,const std::string& PRODORDERID, long CONTAINERINSEQ);

  std::set<std::string> getOrderList(const std::string& PLANT, const std::string& PRODORDERID, const std::string& CONTAINERTYPE, long STATUSNO  );

  bool insertData(const std::string& PLANT, const std::string& PRODORDERID, long CONTAINERINSEQ, long CONTAINERNO, const std::string&  CONTAINERTYPE, bool Commit, cCBS_ODBC_DBError &Error);

  bool setOrderedTime(const string& PLANT,const string &PRODORDERID, long CONTAINERINSEQ, bool Commit, cCBS_ODBC_DBError &Error);

  bool updateOrderTime(const std::string& PLANT, const std::string & PRODORDERID, const long & CONTAINERINSEQ, CDateTime& ORDERTIME, bool Commit, cCBS_ODBC_DBError &Error);

  bool isOrderInProcess(const std::string& PLANT, const std::string & PRODORDERID, cCBS_ODBC_DBError &Error);

};

#endif /* _INC_CPD_SCRAP_CONTAINER_ORDER_INCLUDED */
