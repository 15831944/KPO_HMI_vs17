#include <windows.h>
#include <sql.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include "cCBS_DBExc.h"
#include "cCBS_DBExcODBC.h"
#include "cCBS_Connection.h"
#include "cCBS_Driver.h"
#include "cCBS_ODBCDriver.h"
#include "cCBS_DriverManager.h"
#include "cCBS_Statement.h"
#include "cCBS_ODBCStatement.h"
#include "cCBS_PreparedStatement.h"
#include "cCBS_ODBCPreparedStatement.h"

int mysqlTest()
{
	std::string sURL = "ODBC_Driver@mysql_db_odbc";
	std::string sLogin = "root";
	std::string sPW = "ist9_dkgss";
	const char* cbuf = "Physicist";
	cCBS_DriverManager cDM;
	cCBS_ODBCDriver *ptODBCDrv;

	ptODBCDrv = new cCBS_ODBCDriver();
	cDM.registerDriver(ptODBCDrv);
	try 
	{
		cCBS_Connection & myrefConn = cDM.getConnection(sURL,sLogin,sPW);

		try
		{
			cCBS_Statement *ptStmtDate = myrefConn.createPtStatement();
			cCBS_ResultSet *ptRSDate = ptStmtDate->executePtQuery(std::string("select dob, Provider from provider1 where provider='Brandli, Warren';"));
			ptRSDate->first();
			try {
				DB_CLASSLIB_DATE const *ptdDate = ptRSDate->getDate(0);
				std::string sProvider = std::string(ptRSDate->getChars(1));
				std::cout << sProvider << " date of birth: ";
				std::cout << ptdDate->year << "-" << ptdDate->month << "-" << ptdDate->day << " " << ptdDate->hour << ":" << ptdDate->minute << ":" << ptdDate->second << std::endl;
				DB_CLASSLIB_DATE inDate;
				inDate.year = 2000;
				inDate.month = 9;
				inDate.day = 5;
				inDate.hour = 2;
				inDate.minute = 1;
				inDate.second = 0;
				inDate.msecond = 0;
				ptRSDate->updateDate(0,inDate);
				ptRSDate->updateRow();
				ptRSDate->moveToInsertRow();
				inDate.month = 9;
				inDate.day = 18;
				ptRSDate->updateDate(0,inDate);
				ptRSDate->updateString(1,std::string("Abraham Lincoln II"));
				ptRSDate->insertRow();
				myrefConn.commit();
				ptRSDate->moveToInsertRow();
				inDate.month = 11;
				inDate.day = 17;
				ptRSDate->updateDate(0,inDate);
				ptRSDate->updateString(1,std::string("Isaac Newton II"));
				ptRSDate->insertRow();
				myrefConn.commit();
				ptRSDate->moveToInsertRow();
				inDate.month = 6;
				inDate.day = 19;
				ptRSDate->updateDate(0,inDate);
				ptRSDate->updateString(1,std::string("Mahatma Ghandi II"));
				ptRSDate->insertRow();
				myrefConn.commit();
			}
			catch(cCBS_DBExc &e) {
				std::cout << "exception test date while getting date raised, end" << e.getText() << std::endl;
			}
		}
		catch(cCBS_DBExc &e) {
			std::cout << "exception test date while creating statement or resultSet raised, end" << e.getText() << std::endl;
		}
		int iContents[16000];  // limit !!!
		float fContents[16000];  // limit !!!
		int iStep = 500;
		int nCS = sizeof(fContents) / sizeof(int);
//		int nCS = sizeof(iContents) / sizeof(int);
		int nptCS = nCS * sizeof(int) / sizeof(char);
		char *ptcContents = new char[nptCS];
/**		try
		{
			cCBS_Statement *ptStmtArr[10];
			for (int i=0; i<5; i++)
			{
				ptStmtArr[i] = myrefConn.createPtStatement();
			}
			myrefConn.freeStatement(ptStmtArr[1]);
			ptStmtArr[5] = myrefConn.createPtStatement();
			ptStmtArr[6] = myrefConn.createPtStatement();
			myrefConn.freeStatement(ptStmtArr[0]);
			myrefConn.freeStatement(ptStmtArr[2]);
			ptStmtArr[7] = myrefConn.createPtStatement();
			ptStmtArr[8] = myrefConn.createPtStatement();
			myrefConn.freeStatement(ptStmtArr[3]);
			myrefConn.freeStatement(ptStmtArr[6]);
			myrefConn.freeStatement(ptStmtArr[5]);
			myrefConn.freeStatement(ptStmtArr[4]);
			ptStmtArr[9] = myrefConn.createPtStatement();
			myrefConn.freeStatement(ptStmtArr[7]);
			myrefConn.freeStatement(ptStmtArr[8]);
			myrefConn.freeStatement(ptStmtArr[9]);
		}
		catch(cCBS_DBExc &e) {
			std::cout << "exception raised, end" << e.getText() << std::endl;
		}

		cCBS_Statement *ptStmtExcTest;
		try
		{
			ptStmtExcTest = myrefConn.createPtStatement();
			ptStmtExcTest->execute(std::string("blablabla"));
		}
		catch(cCBS_DBExc &e) {
			std::cout << "exception raised, end" << e.getText() << std::endl;
			myrefConn.freeStatement(ptStmtExcTest);
//			std::cout << "now by ostream:\n" << e << std::endl;
//			cCBS_Exception c_e = static_cast<const cCBS_Exception>(e);
//			std::cout << "native exception info: " << c_e << std::endl;
		}
		**/
			
		try
		{
			cCBS_PreparedStatement *ptPrepStmtNLT = myrefConn.preparePtStatement(std::string("insert into newlibtest (id, name, descript, binid, contents) values(?, ?, ?, ?, ?)"));
//			cCBS_PreparedStatement *ptPrepStmtNLT = myrefConn.preparePtStatement(std::string("insert into newlibtest set id=?, name=?, descript=?, binid=?, contents=?"));
			int ione = 1;
			ptPrepStmtNLT->setInt(0,ione);
			ptPrepStmtNLT->setString(1,std::string("1stName"));
			char * ptcBuf = "Hallo test!";
			cCBS_Blob insertBlob(ptcBuf,strlen(ptcBuf));
			char ptcBinid[10], *ptcBinidSet="binid1";
			cCBS_Blob insertBinidBlob(ptcBinid,10);
			insertBinidBlob.setBytes(0,ptcBinidSet,0,strlen(ptcBinidSet));
			ptPrepStmtNLT->setBlob(2,insertBlob);
			ptPrepStmtNLT->setBlob(3,insertBinidBlob);
			cCBS_Blob insertContentsBlob(ptcContents,nptCS);
			for (int i1=0; i1<nCS; i1+=iStep)
			{
				iContents[i1] = i1;
				fContents[i1] = exp(i1*10/nCS);
				std::cout << i1 << " " << fContents[i1] << " ";
			}
			std::cout << std::endl;
			insertContentsBlob.setBytes(0,(char *) fContents,0,nptCS);
//			insertContentsBlob.setBytes(0,(char *) iContents,0,nptCS);
			ptPrepStmtNLT->setBlob(4,insertContentsBlob);
			ptPrepStmtNLT->executeUpdate();
			myrefConn.commit();
			myrefConn.freeStatement(ptPrepStmtNLT);
		}
		catch(cCBS_DBExc &e) {
			std::cout << "exception raised, end" << std::endl;
		}
		try
		{
			cCBS_Statement *ptStmtNLT = myrefConn.createPtStatement();
			cCBS_ResultSet *ptRSNLT = ptStmtNLT->executePtQuery(std::string("select id, name, descript, binid, contents from newlibtest"));
			ptRSNLT->first();
			cCBS_Blob readContentsBlob;
			readContentsBlob = ptRSNLT->getBlob(4);
			int nBlobSize = readContentsBlob.getSize();
			float *freadContents = readContentsBlob.getFloats(0,nBlobSize);
//			int *ireadContents = readContentsBlob.getInts(0,nBlobSize);
			for (int i2=0; i2<nBlobSize/sizeof(int); i2+=iStep)
			{
				std::cout << freadContents[i2] << " ";
//				std::cout << ireadContents[i2] << " ";
			}
			std::cout << std::endl;
			myrefConn.freeStatement(ptStmtNLT);
		}
		catch(cCBS_DBExc &e) {
			std::cout << "exception 1 raised, end" << std::endl;
		}

		cCBS_Statement *ptStmt = myrefConn.createPtStatement();
		cCBS_ResultSet *ptRS = ptStmt->executePtQuery(std::string("select referrals, Provider, Retired, address1, comment from provider;"));
		int ireferrals = ptRS->getInt(0);
		ptRS->first();
		try {
			for (int i=0; i<20; i++) {
				ireferrals = ptRS->getInt(std::string("referrals"));
				std::string sProvider = std::string(ptRS->getChars(1));
				std::string sRetired = std::string(ptRS->getChars(2));
				std::string sAddress = ptRS->getString(std::string("address1"));
				std::cout << ireferrals << ", " << sProvider << ", " << sRetired << sAddress << std::endl;
				ptRS->next();
				if (i==10) {
					ptRS->updateInt(0,859);
//					ptRS->updateString(1,std::string("6"));
//					ptRS->updateString(1,std::string("Brandom, David R."));
					ptRS->updateString(1,std::string("Brandli, Warren J."));
					ptRS->updateInt(2,3);
					ptRS->updateString(4,std::string("comment"));
					ptRS->updateRow();
				}
				else if (i==5)
				{
					ptRS->moveToInsertRow();
					ptRS->updateInt(0,777);
					ptRS->updateString(1,std::string("Sven-Louis Stuecher"));
					ptRS->updateInt(2,7);
					ptRS->updateString(4,std::string("sweet honey"));
					ptRS->insertRow();
				}
			}
			std::string sCur = ptStmt->getCursorName();
			std::string sPrepQuery = std::string("update provider set zip=?, type=? WHERE CURRENT OF ") + sCur;
			cCBS_PreparedStatement *pstmt1 = myrefConn.preparePtStatement(sPrepQuery); 
			float f109 = 109.88;
			pstmt1->setFloat(0, f109);
			pstmt1->setString(1,std::string("baker"));
			pstmt1->executeUpdate();
			myrefConn.freeStatement(pstmt1);
			/**
			pstmt1 = myrefConn.preparePtStatement(std::string("update provider set Provider=?, retired=? WHERE referrals=858")); 
			pstmt1->setString(0, std::string("Brandli, Warren"));
			int ii = 859;
			pstmt1->setInt(1,ii);
			pstmt1->executeUpdate();
			myrefConn.freeStatement(pstmt1);
**/
		}
		catch(cCBS_DBExc &e) {
			std::cout << "exception 2 raised, end" << std::endl;
		}
		std::cout << "again check update" << std::endl;
/**		ptRS->first();
		try {
			for (int i=0; i<21; i++) {
				ireferrals = ptRS->getInt(std::string("referrals"));
				std::string sProvider = std::string(ptRS->getChars(1));
				std::string sRetired = std::string(ptRS->getChars(2));
				std::string sAddress = ptRS->getString(std::string("address1"));
				std::cout << ireferrals << ", " << sProvider << ", " << sRetired << sAddress << std::endl;
				ptRS->next();
			}
		}
		catch(cCBS_DBExc &e) {
			std::cout << "exception raised, end" << std::endl;
		}
		**/
		ptRS->beforeFirst();
		try {
			bool bFirstPass = true;
			for (int i=0; ptRS->next(); i++) {
				ireferrals = ptRS->getInt(std::string("referrals"));
				std::string sProvider = std::string(ptRS->getChars(1));
				std::string sRetired = std::string(ptRS->getChars(2));
				std::string sAddress = ptRS->getString(std::string("address1"));
				std::cout << ireferrals << ", " << sProvider << ", " << sRetired << sAddress << std::endl;
				if (sProvider.find("Sven-Lois Stuecher") != std::string::npos  &&  bFirstPass)
				{
					ptRS->deleteRow();
					bFirstPass = false;
				}
			}
		}
		catch(cCBS_DBExc &e)
		{
			std::cout << "exception raised, end" << std::endl;
		}
		myrefConn.freeStatement(ptStmt);
		try
		{
			cCBS_PreparedStatement *pstmt = myrefConn.preparePtStatement(std::string("update provider1 set zip=?, type=? where provider='Turner, Donald'"));
			int izip = 7776;
			float fzip = 123.456789;
			std::string sType(cbuf);
//			std::string sType("Physicist");
			pstmt->setFloat(0,fzip);
			pstmt->setString(1,sType);
//			pstmt->setInt(0,izip);
			pstmt->executeUpdate();
			myrefConn.freeStatement(pstmt);
			pstmt = myrefConn.preparePtStatement(std::string("update provider1 set zip=?, type=? where provider=?"));
			std::string sProvider("Alvarez, Mike");
			izip = 7775;
			fzip = 88.99;
			sType = std::string("Theoreticist");
			pstmt->setFloat(0,fzip);
			pstmt->setString(1,sType);
			pstmt->setString(2,sProvider);
			pstmt->executeUpdate();
		}
		catch(cCBS_DBExc &e) {
			std::cout << "exception on prepared statement raised, end" << std::endl;
		}
		/**
		std::string sCreaTable("drop TABLE SIGNALS_QUAT_COMMON");
		ptStmt = myrefConn.createPtStatement();
		ptStmt->execute(sCreaTable);
		sCreaTable = std::string("CREATE TABLE SIGNALS_QUAT_COMMON ("
			"  PLANT_ID 		NUMERIC(5,0),"
			"  RECORD_NO		NUMERIC(9,0),"
			"  CNFG_ID_AUTOMATION	NUMERIC(5,0),"
			"  RES_ID_AUTOMATION 	NUMERIC(5,0),"
			"  QUAT_ID 		NUMERIC(9,0),"
			"  RELATED_DATA_ID 	NUMERIC(5,0),"
			"  CONFIDENCE 		NUMERIC(5,2),"
			"  TIMESTRING		VARCHAR(23),"
			"  DB_TIMESTAMP 		DATE)");
		ptStmt->execute(sCreaTable);
		**/
		cDM.freeConnection(myrefConn);
	}
	catch (cCBS_DBExc &e)
	{
		std::cout << e.getText().c_str() << std::endl;
	}
	return (0);
}
