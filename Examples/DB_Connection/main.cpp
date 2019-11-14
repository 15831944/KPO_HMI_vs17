#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include "cCBS_StdFrame.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdDB_Task.h"
#include "cCBS_DBExc.h"
#include "cCBS_DBExcODBC.h"
#include "CGC_RECIPE_SOURCE.h"
#include "CPDA_ACTUAL_RES.h"
#include "CHD_PARAM.h"
#include "CGC_SOURCE.h"

#include "cCBS_ODBCResultSet.h"


// use command line argument: -config $(X-Pact)\cfg\Examples\DB_Connection.ini

class CDate_Test
: public CSMC_DBData
{
public:

  CDate_Test(cCBS_StdConnection* Connection):CSMC_DBData("DATE_TEST",Connection) {};

	std::string getKey(long Row) { return getString("KEY", Row); };

	void setKey(const std::string& value) { setString("KEY", value) ;};

	CDateTime getDate1(long Row) { return getDate("DATE1", Row); };

	void setDate1(CDateTime& value) { setDate("DATE1", value); };

	CDateTime getDate2(long Row) { return getDate("DATE2", Row); };

	void setDate2(CDateTime& value) { setDate("DATE2", value); };

  void CDate_Test::select(const std::string& key, CDateTime &d1, CDateTime &d2);
};

void CDate_Test::select(const std::string& key, CDateTime &d1, CDateTime &d2)
{
  cleanWhereStatement();

  m_Statement = "select * from " + m_TableName;

  addWhereClause("KEY",  key);
  addWhereClauseforDate("DATE1", d1);
  addWhereClauseforDate("DATE2", d2);
  m_Statement += getWhereStatement();
  m_Statement += " ; ";
  CSMC_DBData::select();
}


class CPrecision_Test
: public CSMC_DBData
{
public:

  CPrecision_Test(cCBS_StdConnection* Connection):CSMC_DBData("PRECISION_TEST",Connection) {};

	void setKey(const std::string& value) { setString("KEY", value) ;};
	std::string getKey(long Row) { return getString("KEY", Row); };

  void setD_VALUE(double value) {setDouble("D_VALUE",value);};
  double getD_VALUE(long Row) {return getDouble("D_VALUE",Row);};

  void CPrecision_Test::select(const std::string& key);
};

void CPrecision_Test::select(const std::string& key)
{
  cleanWhereStatement();

  m_Statement = "select * from " + m_TableName;

  addWhereClause("KEY",  key);
  m_Statement += getWhereStatement();
  m_Statement += " ; ";
  CSMC_DBData::select();
}


class CUpdate_Test
: public CSMC_DBData
{
public:

  CUpdate_Test(cCBS_StdConnection* Connection):CSMC_DBData("UPDATE_TEST",Connection) {};

	void setKey(const std::string& value) { setString("KEY", value) ;};
	std::string getKey(long Row) { return getString("KEY", Row); };

  void setD_VALUE(double value) {setDouble("D_VALUE",value);};
  double getD_VALUE(long Row) {return getDouble("D_VALUE",Row);};

  void CUpdate_Test::select(const std::string& key);
};

void CUpdate_Test::select(const std::string& key)
{
  cleanWhereStatement();

  m_Statement = "select * from " + m_TableName;

  addWhereClause("KEY",  key);
  m_Statement += getWhereStatement();
  m_Statement += " ; ";
  CSMC_DBData::select();
}



int main( int argc, const char *argv[], char *envp[] )
{

  try
  {
    // activate SMM Application Environment
    cCBS_StdFrame *pCBS_StdFrame = new cCBS_StdFrame(argc, argv);

    // run the application / CORBA
    pCBS_StdFrame->runAsClient();

    // getting Pointer to DB Task
    cCBS_StdDB_Task* pCBS_StdDB_Task = cCBS_StdDB_Task::getInstance();

    cCBS_Connection * pConnection = 0;
    cCBS_StdConnection * pStdConnection = 0;

    long input = 1;

    do 
    {
      std::cout << "***********************************" << std::endl;
      std::cout << "***********************************" << std::endl;
      std::cout << "Input : " << std::endl;
      std::cout << "0 for exit" << std::endl;
      std::cout << "1 connect to DB" << std::endl;
      std::cout << "2 select data from DB" << std::endl;
      std::cout << "3 insert data to DB (without commit!)" << std::endl;
      std::cout << "***********************************" << std::endl;
      std::cout << "7 select all data from GC_RECIPE_SOURCE Table" << std::endl;
      std::cout << "8 select RECIPE_L1_INTF_NO from GC_RECIPE_SOURCE Table" << std::endl;
      std::cout << "9 select RECIPENAME from GC_RECIPE_SOURCE Table" << std::endl;
      std::cout << "10 set time format" << std::endl;
      std::cout << "***********************************" << std::endl;
      std::cout << "20 insert and read NULL data to DB (without commit!)" << std::endl;
      std::cout << "22 select and update data to DB (without commit!)" << std::endl;
      std::cout << "23 select and update and insert data to DB (without commit!)" << std::endl;
      std::cout << "***********************************" << std::endl;
      std::cout << "30 check precision (without commit!)" << std::endl;
      std::cout << "40 test copy of data with GT_PARAM and HD_PARAM" << std::endl;

      std::cin >> input;

      switch (input)
      {
        case 1:
        {
          std::string DBName;
          std::string DBUser;
          std::string DBPassword;
          cCBS_StdInitBase *pStdInitBase = cCBS_StdInitBase::getInstance();
    
          bool result = false;
          if ( !( pStdInitBase->getEntry("DATABASE", "SMC_DBName", DBName) &&
                  pStdInitBase->getEntry("DATABASE", "SMC_DBUser", DBUser)  &&
                  pStdInitBase->getEntry("DATABASE", "SMC_DBPassword", DBPassword) ))
          {
            std::cerr << "Can not read SMC database settings from ini-file" << std::endl;
            exit(EXIT_FAILURE);
          }
          std::cout << " connecting : " << DBName << ", " << DBUser << ", " << DBPassword << std::endl;

          pStdConnection = pCBS_StdDB_Task->getCBS_StdConnection(DBName, DBUser, DBPassword);

          if ( pStdConnection )
          {
            pConnection = pStdConnection->getpCBSConnection();
          }

          break;
        }

        case 2:
        {
        	try
        	{
            if (pConnection)
            {
              // define Statement
        			cCBS_Statement *pStatement = pConnection->createPtStatement();
              // execute SQL stetement
              std::cout << " selecting : " << "select Plant from gc_grade ;" << std::endl;
              // std::cout << " selecting : " << "select * from GTA_MI_P_BLOW;" << std::endl;

        			cCBS_ResultSet *pResultSet = pStatement->executePtQuery
                (std::string("select * from GC_GRADE where rownum <= 2;"));

              //  (std::string("select * from GTA_MI_P_BLOW, GTA_MI_P_MAIN_BLOW where (GTA_MI_P_BLOW.NO=GTA_MI_P_MAIN_BLOW.NO(+) and GTA_MI_P_BLOW.NO=2) ;"));
              // set iterator on result set
          		pResultSet->beforeFirst();
          		try 
              {
                // iterating on result set
          			while (pResultSet->next()) 
                {
                  // reading data
                  std::cout << " PLANT = " << pResultSet->getString(std::string("PLANT") ) << std::endl;
                }
              }
		          catch(cCBS_DBExc &e) 
              {
          			std::cout << "exception caught at reading data " << e.getText() << std::endl;
		          }
              pConnection->freeStatement( pStatement ); 
//              pCBS_StdDB_Task->freeConnections(); // this invocation has no effect on the established connection.
            }//if (pConnection)
            else
            {
              std::cout << "Not connected !" << std::endl;
            }
          }
        	catch(cCBS_DBExc &e) 
          {
        		std::cout << "exception caught " << e.getText() << std::endl;
        	}
          break;
        }

        case 3:
        {
        	try
        	{
            if (pConnection)
            {
              // define Statement
              string Plant;
              std::cout << "Input Plant Name: " << std::endl;
              std::cin >> Plant;

          		try 
              {
            		cCBS_PreparedStatement *pPrepStatement = pConnection->preparePtStatement
                  (std::string("insert into gc_grade (plant) values(?)"));
            		pPrepStatement->setString(0,Plant);
            		pPrepStatement->executeUpdate();
              }
		          catch(cCBS_DBExc &e) 
              {
          			std::cout << "exception caught at reading data " << e.getText() << std::endl;
		          }
            }//if (pConnection)
            else
            {
              std::cout << "Not connected !" << std::endl;
            }
          }
        	catch(cCBS_DBExc &e) 
          {
        		std::cout << "exception caught " << e.getText() << std::endl;
        	}
          break;
        }

        case 4:
        {
        	try
        	{
            // using specialized class derived from CSMC_DBData
            if (pConnection)
            {
            }
          }
        	catch(cCBS_DBExc &e) 
          {
        		std::cout << "exception caught " << e.getText() << std::endl;
        	}
          break;
        }


        case 7:
        {
        	try
        	{
            // using specialized class derived from CSMC_DBData
            if (pStdConnection)
            {
              long LastRow = 0;

              CGC_RECIPE_SOURCE* pGC_RECIPE_SOURCE = new CGC_RECIPE_SOURCE(pStdConnection);

              // *******************************************

              for ( long k = 1 ; k < 100000 ; ++k )
              {
        	      try
        	      {
                  std::cout << "Select " << k << "times" << std::endl;

                  pGC_RECIPE_SOURCE->select(CSMC_DBData::unspecString,CSMC_DBData::unspecString,CSMC_DBData::unspecString);
                  LastRow = pGC_RECIPE_SOURCE->getLastRow();
                  for ( long i = 1 ; i <= LastRow ; ++i )
                  {
                    std::cout << "Plant           = " << pGC_RECIPE_SOURCE->getPLANT(i) << " - "
                              << "Source          = " << pGC_RECIPE_SOURCE->getSOURCE(i) << " - "
                              << "RecipeName      = " << pGC_RECIPE_SOURCE->getRECIPENAME(i) << " - "
                              << std::endl;
                  }
                }
        	      catch(cCBS_DBExc &e) 
                {
        		      std::cout << "exception caught " << e.getText() << std::endl;
        	      }
        	      catch(...) 
                {
        		      std::cout << "exception caught " << std::endl;
        	      }

              }
            }
          }
        	catch(cCBS_DBExc &e) 
          {
        		std::cout << "exception caught " << e.getText() << std::endl;
        	}
          break;
        }

        case 8:
        {
        	try
        	{
            if (pStdConnection)
            {
              std::string Plant;
              std::string RecipeName;
              std::string Source;
              long LastRow = 0;
              std::string Desc;

              std::cout << "Input Plant :" ;
              std::cin >> Plant;
              std::cout << "Input RecipeName :" ;
              std::cin >> RecipeName;
              std::cout << "Input Source :" ;
              std::cin >> Source;

              CGC_RECIPE_SOURCE* pGC_RECIPE_SOURCE = new CGC_RECIPE_SOURCE(pStdConnection);
              pGC_RECIPE_SOURCE->select(Plant,RecipeName,Source);

              if (pGC_RECIPE_SOURCE->getLastRow())
              {
                std::cout << "RECIPE_L1_INTF_NO = " << pGC_RECIPE_SOURCE->getRECIPENAME(1) << std::endl;
              }
            }
          }
        	catch(cCBS_DBExc &e) 
          {
        		std::cout << "exception caught " << e.getText() << std::endl;
        	}
          break;
        }

        case 9:
        {
        	try
        	{
            if (pStdConnection)
            {
              std::string Plant;
              long RecipeL1IntfNo;
              long LastRow = 0;
              std::string Desc;

              std::cout << "Input Plant :" ;
              std::cin >> Plant;
              std::cout << "Input RecipeL1IntfNo :" ;
              std::cin >> RecipeL1IntfNo;

              CGC_RECIPE_SOURCE* pGC_RECIPE_SOURCE = new CGC_RECIPE_SOURCE(pStdConnection);
              pGC_RECIPE_SOURCE->selectByPlant(Plant);

              if (pGC_RECIPE_SOURCE->getLastRow())
              {
                std::cout << "Plant           = " << pGC_RECIPE_SOURCE->getPLANT(1) << " - "
                          << "Source          = " << pGC_RECIPE_SOURCE->getSOURCE(1) << " - "
                          << "RecipeName      = " << pGC_RECIPE_SOURCE->getRECIPENAME(1) << " - "
                          << std::endl;
              }
            }
          }
        	catch(cCBS_DBExc &e) 
          {
        		std::cout << "exception caught " << e.getText() << std::endl;
        	}
          break;
        }
        case 10:
        {
        	try
        	{
            if (pConnection)
            {
          		try 
              {
                std::string createDateTestTable = std::string("CREATE TABLE DATE_TEST (KEY VARCHAR2(20), DATE1 DATE, DATE2 DATE)");
                std::string alterSession("ALTER SESSION SET NLS_TIMESTAMP_FORMAT = 'YYYY-MM-DD HH24:MI:SS.FF'");

                cCBS_Statement *ptStmt = pConnection->createPtStatement();
                //ptStmt->execute(createDateTestTable);
                //ptStmt->execute(alterSession);

                CDateTime now;
                std::cout << "Now: " << now.asString ("%Y-%m-%d %H:%M:%S.***") << std::endl;
                DB_CLASSLIB_DATE date1=now.asDB_CLASSLIB_DATE();
          
                CDateTime tomorrow = 
                  CDateTime::addTimes (now, CDeltaTime (0/*s*/,0/*ms*/,0/*min*/,0/*h*/,1/*day*/));
                std::cout << "tomorrow: " << tomorrow.asString ("%Y-%m-%d %H:%M:%S.***") << std::endl;
                DB_CLASSLIB_DATE date2 = tomorrow.asDB_CLASSLIB_DATE();

                CDate_Test *pDT = new CDate_Test(pStdConnection);
                pDT->setKey("Key1");
                pDT->setDate1(now);
                pDT->setDate2(tomorrow);
                pDT->insert();
                pStdConnection->getpCBSConnection()->commit();

                pDT->setKey("Key2");
                pDT->setDate1(now);
                pDT->setDate2(tomorrow);
                pDT->insert();

                pStdConnection->getpCBSConnection()->commit();

                pDT->select("Key1",CSMC_DBData::unspecDate,CSMC_DBData::unspecDate);

                long LastRow = pDT->getLastRow();

                for ( long i = 1 ; i <= LastRow ; ++i)
                {
                  std::cout << pDT->getDate1(i) << std::endl;
                }
                //ptStmt->execute(std::string("DROP TABLE DATE_TEST;"));
              }
		          catch(cCBS_DBExc &e) 
              {
          			std::cout << "exception caught at reading data " << e.getText() << std::endl;
		          }
            }//if (pConnection)
            else
            {
              std::cout << "Not connected !" << std::endl;
            }
          }
        	catch(cCBS_DBExc &e) 
          {
        		std::cout << "exception caught " << e.getText() << std::endl;
        	}
          break;
        }
        
        case 11:
        {
        	try
        	{
            if (pStdConnection)
            {
          		try 
              {
                CPDA_ACTUAL_RES * pPDA_ACTUAL_RES = new CPDA_ACTUAL_RES(pStdConnection);

                std::string HeatID("aHeatIDXXXXXXXXXXXXXXXXXXX");
                std::string TreatID(CSMC_DBData::unspecString);
                std::string Plant("bla");
                double d=1;
                CDateTime now;
                DB_CLASSLIB_DATE date=now.asDB_CLASSLIB_DATE();

                pPDA_ACTUAL_RES->setDECARBRATE(99999999999999999999999.3);
                pPDA_ACTUAL_RES->setAR_MOMENT(CSMC_DBData::unspecDouble);

                
            		pPDA_ACTUAL_RES->setHEATID(HeatID);
            		pPDA_ACTUAL_RES->setTREATID(TreatID);
                pPDA_ACTUAL_RES->setREVTIME(now);
                //...
            		/*pPDA_ACTUAL_RES->set(3,d);
            		pPDA_ACTUAL_RES->setDouble(4,d);
            		pPDA_ACTUAL_RES->setDouble(5,d);
            		pPDA_ACTUAL_RES->setDouble(6,d);
            		pPDA_ACTUAL_RES->setDouble(7,d);
            		pPDA_ACTUAL_RES->setDouble(8,d);
            		pPDA_ACTUAL_RES->setDouble(9,d);
            		pPDA_ACTUAL_RES->setDouble(10,d);
            		pPDA_ACTUAL_RES->setDouble(11,d);
            		pPDA_ACTUAL_RES->setDouble(12,d);
            		pPDA_ACTUAL_RES->setDouble(13,d);
            		pPDA_ACTUAL_RES->setDouble(14,d);
                */

                pPDA_ACTUAL_RES->insert();
                pPDA_ACTUAL_RES->select(HeatID,TreatID, Plant,now);

                long LastRow = pPDA_ACTUAL_RES->getLastRow();

                for ( long i = 1 ; i <= LastRow ; ++i)
                {
                  std::cout << pPDA_ACTUAL_RES->getHEATID(i) << std::endl;
                }

/*
                pPrepStatement->executeUpdate();



                cCBS_Statement *pStmt = pConnection->createPtStatement();
          			cCBS_ResultSet *pRSet1 = pStmt->executePtQuery(std::string("select HEATID, TREATID, REVTIME from PDA_ACTUAL_RES"));
                // set iterator on result set
          		  pRSet1->beforeFirst();
                  // iterating on result set
        			  while (pRSet1->next()) 
                {

                  DB_CLASSLIB_DATE const *ptdDate = pRSet1->getDate(std::string("REVTIME"));
                  std::cout << " HEATID= " << pRSet1->getString("HEATID") <<
                         " TREATID= " << pRSet1->getString("TREATID") <<
                         ptdDate->year << " " << ptdDate->month << " " << ptdDate->day << " "
                        << ptdDate->hour << ":" << ptdDate->minute << ":" << ptdDate->second<< ", " << ptdDate->msecond << std::endl;
                }



                cCBS_Statement *pStatement = pConnection->createPtStatement();
          			cCBS_ResultSet *pResultSet = pStatement->executePtQuery(std::string("select SYSDATE from dual"));
                // set iterator on result set
          		  pResultSet->beforeFirst();
                  // iterating on result set
        			  while (pResultSet->next()) 
                {
                    DB_CLASSLIB_DATE const *ptdDate = pResultSet->getDate(std::string("SYSDATE"));
                    std::cout << " SYSDATE = " << ptdDate->year << " " << ptdDate->month << " " << ptdDate->day << " "
                      << ptdDate->hour << ":" << ptdDate->minute << ":" << ptdDate->second<< ", " << ptdDate->msecond << std::endl;
                }

*/

              }
		          catch(cCBS_DBExc &e) 
              {
          			std::cout << "exception caught at reading data " << e.getText() << std::endl;
		          }
            }//if (pConnection)
            else
            {
              std::cout << "Not connected !" << std::endl;
            }
          }
        	catch(cCBS_DBExc &e) 
          {
        		std::cout << "exception caught " << e.getText() << std::endl;
        	}
          break;
        }

        case 20:
        {
        	try
        	{
            if (pStdConnection)
            {
              CGC_SOURCE* pGC_SOURCE = new CGC_SOURCE(pStdConnection);
              pGC_SOURCE->select(CSMC_DBData::unspecString,CSMC_DBData::unspecString);
              
             long  LastRow = pGC_SOURCE->getLastRow();

              std::cout << "READING DATA" << std::endl << std::endl ;


              for ( long i = 1 ; i <= LastRow ; ++i)
              {
                std::cout << i       << " " 
                          << pGC_SOURCE->getPLANT(i)       << " " 
                          << pGC_SOURCE->getSOURCE(i)     << " " 
                          << pGC_SOURCE->getSOURCE_NO(i)   << " "   
                          << pGC_SOURCE->getPURP_SOURCE_AVAIL(i)<< " "  
                          << pGC_SOURCE->getPURP_SOURCE_DEFAULT(i)  << " " 
                          << std::endl;
              }
              std::cout << "WRITING DATA" << std::endl << std::endl ;

              std::string NewPlant = "AOD";
              std::string NewSource = "Bla";
              long NewL1IntfNo = 9;


              pGC_SOURCE->setPLANT(NewPlant);
              pGC_SOURCE->setSOURCE(NewSource);
              pGC_SOURCE->setSOURCE_NO(NewL1IntfNo);
              pGC_SOURCE->setPURP_SOURCE_AVAIL(CSMC_DBData::unspecString);
              pGC_SOURCE->setPURP_SOURCE_DEFAULT(CSMC_DBData::unspecString);
              pGC_SOURCE->insert();

              std::cout << "READING DATA" << std::endl << std::endl ;

              pGC_SOURCE->select("AOD",CSMC_DBData::unspecString);
              LastRow = pGC_SOURCE->getLastRow();

              for ( long i = 1 ; i <= LastRow ; ++i)
              {
                std::cout << i       << " " 
                          << pGC_SOURCE->getPLANT(i)       << " " 
                          << pGC_SOURCE->getSOURCE(i)     << " " 
                          << pGC_SOURCE->getSOURCE_NO(i)   << " "   
                          << pGC_SOURCE->getPURP_SOURCE_AVAIL(i)<< " "  
                          << pGC_SOURCE->getPURP_SOURCE_DEFAULT(i)  << " " 
                          << std::endl;
              }

              std::cout << "UPDATING DATA" << std::endl << std::endl ;

              if ( pGC_SOURCE->setRow(2) )
              {
                pGC_SOURCE->setPURP_SOURCE_AVAIL("xxx");
                pGC_SOURCE->update();
              }

              if ( pGC_SOURCE->setRow(3) )
              {
                pGC_SOURCE->setPURP_SOURCE_AVAIL("yyy");
                pGC_SOURCE->update();
              }


              std::cout << "READING DATA" << std::endl << std::endl ;

              pGC_SOURCE->select("AOD",CSMC_DBData::unspecString);
              LastRow = pGC_SOURCE->getLastRow();

              for ( long i = 1 ; i <= LastRow ; ++i)
              {
                std::cout << i       << " " 
                          << pGC_SOURCE->getPLANT(i)       << " " 
                          << pGC_SOURCE->getSOURCE(i)     << " " 
                          << pGC_SOURCE->getSOURCE_NO(i)   << " "   
                          << pGC_SOURCE->getPURP_SOURCE_AVAIL(i)<< " "  
                          << pGC_SOURCE->getPURP_SOURCE_DEFAULT(i)  << " " 
                          << std::endl;
              }

            }
          }
        	catch(cCBS_DBExc &e) 
          {
        		std::cout << "exception caught " << e.getText() << std::endl;
        	}
          break;
        }
        case 21:
        {
          if ( pConnection )
          {
            std::string strSQL;
            strSQL = " select DISTINCT SOURCE, RECIPECOMBI, RECIPECOMBINO from GT_RESTRI_ENTRY ";
/*            strSQL += " where NO=? ";
            strSQL += " and RECIPECOMBINO=? ";
            strSQL += " and PLANT=? ";
*/            strSQL += ";";
            cCBS_PreparedStatement *pPrepStatement = pConnection->preparePtStatement(strSQL);
            if (pPrepStatement)
            { 
              int i=1, j=0;
/*   
              pPrepStatement->setInt(0, i);      // practice pointer used
              pPrepStatement->setInt(1, j);             // For AOD, RECIPECOMBINO has the value of zero.
              pPrepStatement->setString(2, "AOD");  // PLANT
*/              
              cCBS_ResultSet *pResultSet = pPrepStatement->executePtQuery();
              // pResultSet->beforeFirst();
              while ( pResultSet->next())
              {
                std::cout << "SOURCE:" << pResultSet->getString("SOURCE") << std::endl;
                std::cout << "RECIPECOMBI:" << pResultSet->getString("RECIPECOMBI") << std::endl;
                std::cout << "RECIPECOMBINO:" << pResultSet->getInt("RECIPECOMBINO") << std::endl;

              }
              pConnection->freeStatement(pPrepStatement);
              pPrepStatement = 0;
            }
          }
          break;
        }


        case 22:
        {
        	try
        	{
            if (pConnection)
            {

              std::string createTestTable;
              createTestTable = "CREATE TABLE UPDATE_TEST ( KEY VARCHAR2(20), D_VALUE NUMBER (";
              createTestTable += "10";
              createTestTable += ",";
              createTestTable += "2";
              createTestTable += ") )";
              
              cCBS_Statement *ptStmt = pConnection->createPtStatement();

              try
              {
                ptStmt->execute(std::string("DROP TABLE UPDATE_TEST;"));
                pConnection->commit();
              }
              catch(...)
              {
              }

              ptStmt->execute(createTestTable);
              pConnection->commit();

              // fill data

              CUpdate_Test *pUT = new CUpdate_Test(pStdConnection);
              pUT->setKey("A");
              pUT->setD_VALUE(1.0);
              pUT->insert();

              pUT->setKey("A");
              pUT->setD_VALUE(2.0);
              pUT->insert();

              pUT->setKey("A");
              pUT->setD_VALUE(3.0);
              pUT->insert();

              pUT->select("A");
              long  LastRow = pUT->getLastRow();

              std::cout << "READING DATA" << std::endl << std::endl ;


              for ( long i = 1 ; i <= LastRow ; ++i)
              {
                std::cout << i       << " " 
                          << pUT->getKey(i)       << " " 
                          << pUT->getD_VALUE(i)     << " " 
                          << std::endl;
              }

              std::cout << "UPDATING DATA" << std::endl << std::endl ;

              for ( long i = 1 ; i <= LastRow ; ++i)
              {
                pUT->getD_VALUE(i); 
                std::cout << i       << " " 
                          << pUT->getKey(i)       << " " 
                          << pUT->getD_VALUE(i)     << " " 
                          << std::endl;

                pUT->setD_VALUE(0.0);
                std::cout << i       << " " 
                          << pUT->getKey(i)       << " " 
                          << pUT->getD_VALUE(i)     << " " 
                          << std::endl;
              }

              pUT->update();


              for ( long i = 1 ; i <= LastRow ; ++i)
              {
                std::cout << i       << " " 
                          << pUT->getKey(i)       << " " 
                          << pUT->getD_VALUE(i)     << " " 
                          << std::endl;
              }


              ptStmt->execute(std::string("DROP TABLE UPDATE_TEST;"));
              pConnection->commit();

            }
          }
        	catch(cCBS_DBExc &e) 
          {
        		std::cout << "exception caught " << e.getText() << std::endl;
        	}
          break;
        }

// **************************************************************************
// **************************************************************************
// **************************************************************************
// **************************************************************************

        case 23:
        {
        	try
        	{
            if (pConnection)
            {

              std::string createTestTable;
              createTestTable = "CREATE TABLE UPDATE_TEST ( KEY VARCHAR2(20), D_VALUE NUMBER (10,2), PRIMARY KEY ( KEY ) )";
              
              cCBS_Statement *ptStmt = pConnection->createPtStatement();

              try
              {
                ptStmt->execute(std::string("DROP TABLE UPDATE_TEST;"));
                pConnection->commit();
              }
              catch(...)
              {
              }

              ptStmt->execute(createTestTable);
              pConnection->commit();

              // fill data

              CUpdate_Test *pUT = new CUpdate_Test(pStdConnection);
              pUT->setKey("A");
              pUT->setD_VALUE(1.0);
              pUT->insert();

              pUT->setKey("B");
              pUT->setD_VALUE(2.0);
              pUT->insert();

              pUT->setKey("C");
              pUT->setD_VALUE(3.0);
              pUT->insert();

              pUT->select(CSMC_DBData::unspecString);
              long  LastRow = pUT->getLastRow();

              std::cout << "READING DATA" << std::endl << std::endl ;


              for ( long i = 1 ; i <= LastRow ; ++i)
              {
                std::cout << i       << " " 
                          << pUT->getKey(i)       << " " 
                          << pUT->getD_VALUE(i)     << " " 
                          << std::endl;
              }

              std::cout << "UPDATING DATA LINE BY LINE" << std::endl << std::endl ;

              for ( long i = 1 ; i <= LastRow ; ++i)
              {
                pUT->getD_VALUE(i); 
                std::cout << i       << " " 
                          << pUT->getKey(i)       << " " 
                          << pUT->getD_VALUE(i)   << std::endl;

                pUT->setD_VALUE(0.0);
                pUT->update();
              }

              pUT->select(CSMC_DBData::unspecString);
              LastRow = pUT->getLastRow();

              for ( long i = 1 ; i <= LastRow ; ++i)
              {
                std::cout << i       << " " 
                          << pUT->getKey(i)       << " " 
                          << pUT->getD_VALUE(i)     << " " 
                          << std::endl;
              }

              pStdConnection->getpCBSConnection()->commit();

              ptStmt->execute(std::string("DROP TABLE UPDATE_TEST;"));
              pStdConnection->getpCBSConnection()->commit();

            }
          }
        	catch(cCBS_DBExc &e) 
          {
        		std::cout << "exception caught " << e.getText() << std::endl;
        	}
          break;
        }


        case 30:
        {
        	try
        	{
            if (pConnection)
            {

              std::string prec;
              std::cout << "Input precision:" ;
              std::cin >> prec;

              std::string dec;
              std::cout << "Input decimal:" ;
              std::cin >> dec;

              double value = 0.0;
              std::cout << "Input double value:" ;
              std::cin >> value;

          		try 
              {
                std::string createTestTable;
                createTestTable = "CREATE TABLE PRECISION_TEST ( KEY VARCHAR2(20), D_VALUE NUMBER (";
                createTestTable += prec;
                createTestTable += ",";
                createTestTable += dec;
                createTestTable += ") )";
                
                cCBS_Statement *ptStmt = pConnection->createPtStatement();
//                ptStmt->execute(std::string("DROP TABLE PRECISION_TEST;"));

                ptStmt->execute(createTestTable);
                pConnection->commit();

                CPrecision_Test *pPT = new CPrecision_Test(pStdConnection);
                pPT->setKey("Key1");
                pPT->setD_VALUE(value);
                pPT->insert();
                pConnection->commit();

                pPT->select("Key1");

                long LastRow = pPT->getLastRow();

                std::cout << "--------------------" << std::endl;
                for ( long i = 1 ; i <= LastRow ; ++i)
                {
                  std::cout << pPT->getD_VALUE(i) << std::endl;
                }
                std::cout << "--------------------" << std::endl;

                ptStmt->execute(std::string("DROP TABLE PRECISION_TEST;"));
              }
		          catch(cCBS_DBExc &e) 
              {
          			std::cout << "exception caught at reading data " << e.getText() << std::endl;
		          }
            }//if (pConnection)
            else
            {
              std::cout << "Not connected !" << std::endl;
            }
          }
        	catch(cCBS_DBExc &e) 
          {
        		std::cout << "exception caught " << e.getText() << std::endl;
        	}
          break;
        }

        case 40:
        {
        	try
        	{
            if (pStdConnection)
            {
              CHD_PARAM* pHD_PARAM = new CHD_PARAM(pStdConnection);

              pHD_PARAM->select("0000066","015","LF",CSMC_DBData::unspecLong,CSMC_DBData::unspecString,CSMC_DBData::unspecLong,0);  

              std::cout << pHD_PARAM->getPNAME(1) << std::endl;

              delete pHD_PARAM;
            }
          }
          catch(...)
          {
          }
          break;
        }

        default:
          {
            input = 0;
            break;
          }

      }
    } while (input != 0);
    delete pCBS_StdFrame;
  }

  catch(cCBS_DBExc &e) 
  {
    std::cout << e.getText() << std::endl;
  }

  catch(cCBS_Exception Exc)
  {
    std::cout << Exc << std::endl;
  }

  catch(...)
  {
    std::cout << "exception caught "  << std::endl;
  }

  return 0;
}
