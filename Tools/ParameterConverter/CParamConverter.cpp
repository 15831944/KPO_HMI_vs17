#include "CParamConverter.h"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdDB_Task.h"

#include <fstream>
#include <algorithm>
#include <cctype>
#include <string>

CParamConverter::CParamConverter(void)
: m_ptStmt(0), m_ptRS(0), m_pConnection(0),m_SQLFilesOnly(false)
{
  initialize();
}

CParamConverter::~CParamConverter(void)
{
}

void CParamConverter::initialize(void)
{
  cCBS_StdInitBase *pI = cCBS_StdInitBase::getInstance();
  std::stringstream s;
  s << pI->getXPACT_SMC_LOG() << pI->m_ServerName << '/';
  m_OutputDir = s.str();

  std::string mode;
  pI->replaceWithEntry("CONVERSION","WriteOnlySQLFiles", mode);
  std::transform(mode.begin(), mode.end(), mode.begin(), std::tolower);
  if ("yes" == mode)
    m_SQLFilesOnly = true;

  pI->replaceWithEntry("PARAM_TABLES","SourceParamTable", m_SourceParamTable);
  pI->replaceWithEntry("PARAM_TABLES","SourceParamMatrixTable", m_SourceParamMatrixTable);
  pI->replaceWithEntry("PARAM_TABLES","DestinationParamTable", m_DestinationParamTable);
  pI->replaceWithEntry("PARAM_TABLES","DestinationParamMatrixTable", m_DestinationParamMatrixTable);

  std::string Db, User, Pwd;
  pI->replaceWithEntry("DATABASE","SMC_DBName",Db);
  pI->replaceWithEntry("DATABASE","SMC_DBUser",User);
  pI->replaceWithEntry("DATABASE","SMC_DBPassword",Pwd);
  m_pConnection = cCBS_StdDB_Task::getInstance()->getConnection(Db,User,Pwd);
  if (!m_pConnection)
  {
    std::cerr << "Database connection failed!!!" << std::endl;
    exit(EXIT_FAILURE);

  }
  std::vector<std::string> v;
  std::vector<std::string>::const_iterator vI;
  pI->getEntryList("PLANTS","Names",v);

  std::map<std::string, long> UnitGroupNumber;
  for (vI = v.begin(); vI != v.end(); ++vI)
  {
    long ung = 0;
    pI->replaceWithEntry(*vI,"UnitGroupNo",ung);
    if (*vI == "ALL")
      m_UnitGroupNumbers.insert(pair<std::string,long>("GEN",ung));
    else
      m_UnitGroupNumbers.insert(pair<std::string,long>(*vI,ung));
  }

  if(!m_SQLFilesOnly)
  {
    try
    {
      std::stringstream SQLStmt;
      SQLStmt << "TRUNCATE TABLE " << m_DestinationParamTable << ";";
      m_ptStmt = m_pConnection->createPtStatement();
      m_ptStmt->execute(SQLStmt.str());
      m_pConnection->freeStatement(m_ptStmt);

      SQLStmt.str("");
      SQLStmt << "TRUNCATE TABLE " << m_DestinationParamMatrixTable << ";";
      m_ptStmt = m_pConnection->createPtStatement();
  	  m_ptStmt->execute(SQLStmt.str());
      m_pConnection->freeStatement(m_ptStmt);

      m_pConnection->commit();
    }
    catch (cCBS_DBExc_ConnectionError &e)
	  {
      std::cerr << "cCBS_DBExc_ConnectionError caught in initialize(), " << e.getText() << std::endl;
	  }
	  catch (cCBS_DBExc &e)
	  {
      std::cerr << "cCBS_DBExc caught in initialize(), " << e.getText() << std::endl;
	  }
    catch(...)
    {
      std::cerr << "Unknown exception caught in initialize()" << std::endl;
    }
  }
}

CDateTime CParamConverter::getDate(const std::string& ColName)
{
  CDateTime RetValue;
  try
  {
    DB_CLASSLIB_DATE const *ptdDate = m_ptRS->getDate(ColName);
    //KLUW: This is special for the ODBC driver. There is an error with the precision.
    DB_CLASSLIB_DATE D = *ptdDate;
    D.msecond /= 1000000;
    RetValue.SetTime(&D);
  }
  catch(...)
  {
    std::cout << "Exception in getDate" << std::endl;
  }
  return RetValue;
}

void CParamConverter::setDateTime(const CDateTime& value)
{
  try
  {
    DB_CLASSLIB_DATE D;
    D.year    = (short int)value.getYear();
    D.month   = (short int)value.getMonth();
    D.day     = (short int)value.getDay();
    D.hour    = (short int)value.getHour();
    D.minute  = (short int)value.getMinute();
    D.second  = (short int)value.getSecond();

    //KLUW: This is special for the ODBC driver. There is an error with the precision.
    D.msecond = (int)value.getMilliSecond()*1000000;
  }
  catch(...)
  {
    std::cout << "Exception in setDate" << std::endl;
  }
}

long CParamConverter::ConvertParamTable(void)
{
  long RetValue = 0;
  std::string PName;

  std::cout << "Converting table: " << m_DestinationParamTable << std::endl << std::endl;

  try
  {
    std::stringstream DTab;
    DTab << "insert into " << m_DestinationParamTable
          << " (PNAME, UNITGROUPNO, PRACNO, TYPE, UNIT, VALUE, INST_ACTV, DIALOG_PARAM, CONV, MIN_VALUE, MAX_VALUE, "
          << " CREATIONDATE, PARAMDESC, PARAMDESC_C, PARAMGROUP ) " 
          << "values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

    cCBS_PreparedStatement *ptPrepStmt = m_pConnection->preparePtStatement(DTab.str());
    m_ptStmt = m_pConnection->createPtStatement();

    std::map<std::pair<std::string,std::string>, std::pair<int,int> > check;
    std::map<std::pair<std::string,std::string>, std::pair<int,int> >::const_iterator checkI;

    std::map<std::pair<std::string,std::string>, std::set<int> > practices;
    std::map<std::pair<std::string,std::string>, std::set<int> >::const_iterator practicesI;

    std::set<int>::const_iterator sI;

    std::map<std::string, int>::const_iterator UngFinder;

    stringstream SQLStmt;
    SQLStmt << "SELECT PNAME, AREA, NO, TYPE, UNIT, VALUE, INST_ACTV, DIALOG_PARAM, CONV, MIN_VALUE, MAX_VALUE, "
            << "CREATIONDATE, PARAMDESC, PARAMDESC_C, PARAMGROUP FROM " << m_SourceParamTable;

    ofstream of;
    std::string file(m_OutputDir + m_DestinationParamTable + ".sql");
    of.open( file.c_str(), std::ios::out | std::ios::trunc);
    if (!of.is_open())
    {
      std::cerr << "Unable to open file " << file << std::endl;
      exit(EXIT_FAILURE);
    }

    m_ptRS   = m_ptStmt->executePtQuery(SQLStmt.str());
		m_ptRS->beforeFirst();
 		while (m_ptRS->next())
   	{
      ++RetValue;
//      if(RetValue==30) break;
      PName             = m_ptRS->getString("PNAME");
      std::string DBArea= m_ptRS->getString("AREA");
      int PracNo        = m_ptRS->getInt("NO");
      int Type          = m_ptRS->getInt("TYPE");
      std::string Unit  = m_ptRS->getString("UNIT");
      std::string Value = m_ptRS->getString("VALUE");
      int InstAct       = m_ptRS->getInt("INST_ACTV");
      int DiaPar        = m_ptRS->getInt("DIALOG_PARAM");
      double Conv       = m_ptRS->getDouble("CONV");
      double Min        = m_ptRS->getDouble("MIN_VALUE");
      double Max        = m_ptRS->getDouble("MAX_VALUE");
      CDateTime DT      = getDate("CREATIONDATE");
      std::string Desc  = m_ptRS->getString("PARAMDESC");
      std::string Desc_c= m_ptRS->getString("PARAMDESC_C");
      std::string Pgroup= m_ptRS->getString("PARAMGROUP");

      std::cout << RetValue <<" read parameter: " << PName << ", " << DBArea << ", Type: " << Type << ", PracNo: " << PracNo << std::endl;

      std::string::size_type pos;
      std::string Area;
      if ( (pos = DBArea.find("_")) != std::string::npos)
      {
        Area = DBArea.substr(0,pos);
        std::cout << "Spezialized parameter " << PName << " found for " << DBArea << "! Generalize to " << Area << std::endl;
      }
      else
        Area = DBArea;

      std::pair<std::string,std::string> p1 = std::make_pair<std::string, std::string>(PName, Area);
      if( (checkI = check.find(p1)) != check.end() )
      {
        if (checkI->second.first == Type)
        {
          practicesI = practices.find(p1);
          std::set<int> s = practicesI->second;
          if ((sI = s.find(PracNo))!= s.end())
          {
            // There was already an entry for the compination of name, area and type
            std::cout << "Inconsistency encountered, possible due to generalization of : " << DBArea << std::endl;
            std::cout << "   Values: "<< PName << " for "  << Area << ", Type: " << Type << ", PracNo: " << PracNo << std::endl;
            std::cout << "Check also " << m_SourceParamMatrixTable << std::endl;
          }
          else
          {
            practices[p1].insert(PracNo);
            std::cout << "Additional practice pointer encountered: " << PracNo << std::endl;
            std::set<int>::const_iterator I;
            std::cout << "\tCurrent pracnos: ";
            for(I = practices[p1].begin(); I != practices[p1].end(); ++I)
              std::cout << *I<< " ";
            std::cout << std::endl;
          }
        }
        else
        {
            std::cout << "New type for: "<< PName << ", " << Type << std::endl;
        }
      }
      else
      {
        std::set<int> s;
        s.insert(PracNo);
        std::pair<int,int> p2 = std::make_pair<int,int>(Type,PracNo);
        check.insert(std::make_pair<std::pair<std::string,std::string> , std::pair<int,int> >(p1,p2));
        practices.insert(std::make_pair<std::pair<std::string,std::string> , std::set<int> >(p1,s));
      }

      UngFinder = m_UnitGroupNumbers.find(Area);
      if(UngFinder == m_UnitGroupNumbers.end())
      {
        std::cerr << "Area: " << Area << " not found! Unable to find corresponding UnitGroupNo!! Terminate" << std::endl;
        exit(EXIT_FAILURE);
      }

      int ung = UngFinder->second;
      
      std::stringstream InsertSQLStmt;
      InsertSQLStmt << "insert into " << m_DestinationParamTable
          << " (PNAME, UNITGROUPNO, PRACNO, TYPE, UNIT, VALUE, INST_ACTV, DIALOG_PARAM, CONV, MIN_VALUE, MAX_VALUE, "
          << " CREATIONDATE, PARAMDESC, PARAMDESC_C, PARAMGROUP ) values('"
          << PName << "'," << ung <<"," << PracNo << "," << Type << ",'" << Unit << "','"
          << Value << "'," << InstAct << "," <<  DiaPar << "," << Conv << "," << Min <<","
          << Max << "," << "TO_DATE('" << DT.asString("%Y-%m-%d %H:%M:%S") << "','YYYY-MM-DD HH24:MI:SS'),'" << Desc << "','" << Desc_c << "','" << Pgroup << "');";
      of << InsertSQLStmt.str() << std::endl;

      if(!m_SQLFilesOnly)
      {
        ptPrepStmt->setString(0, PName);
        ptPrepStmt->setInt(1, ung);
        ptPrepStmt->setInt(2, PracNo);
        ptPrepStmt->setInt(3, Type);
        ptPrepStmt->setString(4, Unit);
        ptPrepStmt->setString(5, Value);
        ptPrepStmt->setInt(6, InstAct);
        ptPrepStmt->setInt(7, DiaPar);
        ptPrepStmt->setDouble(8, Conv);
        ptPrepStmt->setDouble(9, Min);
        ptPrepStmt->setDouble(10, Max);
        ptPrepStmt->setDate(11, DT.asDB_CLASSLIB_DATE());
        ptPrepStmt->setString(12, Desc);
        ptPrepStmt->setString(13, Desc_c);
        ptPrepStmt->setString(14, Pgroup);
        ptPrepStmt->executeUpdate();
      }
    }
    of.close();
    if(!m_SQLFilesOnly) m_pConnection->commit();
		m_pConnection->freeStatement(m_ptStmt);
    m_pConnection->freeStatement(ptPrepStmt);
  }
  catch (cCBS_DBExc_ConnectionError &e)
	{
    std::cerr << "cCBS_DBExc_ConnectionError caught in ConvertParamTable() while reading parameter " << PName << ", " << e.getText() << std::endl;
	}
	catch (cCBS_DBExc &e)
	{
    std::cerr << "cCBS_DBExc caught in ConvertParamTable() while reading parameter " << PName << ", " << e.getText() << std::endl;
	}
  catch(...)
  {
    std::cerr << "Unknown exception caught in ConvertParamTable() while reading parameter " << PName << std::endl;
  }
  return RetValue;
}

long CParamConverter::ConvertParamMatrixTable(void)
{
  long RetValue = 0;
  std::string PName;

  std::cout << "Converting table: " << m_SourceParamMatrixTable << std::endl << std::endl;

  try
  {
    std::stringstream DTab;
    DTab << "insert into " << m_DestinationParamMatrixTable
          << " (PNAME, UNITGROUPNO, PRACNO, TYPE, KEY1, KEY2, VALUE) " 
          << "values(?, ?, ?, ?, ?, ?, ?)";

    cCBS_PreparedStatement *ptPrepStmt = m_pConnection->preparePtStatement(DTab.str());
    m_ptStmt = m_pConnection->createPtStatement();

    std::map<std::string, int>::const_iterator UngFinder;

    stringstream SQLStmt;
    SQLStmt << "SELECT PNAME, AREA, NO, TYPE, KEY1, KEY2, VALUE FROM " << m_SourceParamMatrixTable;

    ofstream of;
    std::string file(m_OutputDir + m_DestinationParamMatrixTable + ".sql");
    of.open( file.c_str(), std::ios::out | std::ios::trunc);
    if (!of.is_open())
    {
      std::cerr << "Unable to open file " << file << std::endl;
      exit(EXIT_FAILURE);
    }

    m_ptRS   = m_ptStmt->executePtQuery(SQLStmt.str());
		m_ptRS->beforeFirst();
 		while (m_ptRS->next())
   	{
      ++RetValue;
//      if(RetValue==30) break;
      PName             = m_ptRS->getString("PNAME");
      std::string DBArea= m_ptRS->getString("AREA");
      int PracNo        = m_ptRS->getInt("NO");
      int Type          = m_ptRS->getInt("TYPE");
      std::string Key1  = m_ptRS->getString("KEY1");
      std::string Key2  = m_ptRS->getString("KEY2");
      std::string Value = m_ptRS->getString("VALUE");

      std::cout << RetValue <<" read parameter: " << PName << ", " << DBArea << ", Type: " << Type << ", PracNo: " << PracNo << std::endl;

      std::string::size_type pos;
      std::string Area;
      if ( (pos = DBArea.find("_")) != std::string::npos)
      {
        Area = DBArea.substr(0,pos);
        std::cout << "Spezialized parameter " << PName << " found for " << DBArea << "! Generalize to " << Area << std::endl;
      }
      else
        Area = DBArea;

      UngFinder = m_UnitGroupNumbers.find(Area);
      if(UngFinder == m_UnitGroupNumbers.end())
      {
        std::cerr << "Area: " << Area << " not found! Unable to find corresponding UnitGroupNo!! Terminate" << std::endl;
        exit(EXIT_FAILURE);
      }

      int ung = UngFinder->second;

    DTab << "insert into " << m_DestinationParamMatrixTable
          << " (PNAME, UNITGROUPNO, PRACNO, TYPE, KEY1, KEY2, VALUE) " 
          << "values(?, ?, ?, ?, ?, ?, ?)";

    
      std::stringstream InsertSQLStmt;
      InsertSQLStmt << "insert into " << m_DestinationParamMatrixTable
          << " (PNAME, UNITGROUPNO, PRACNO, TYPE, KEY1, KEY2, VALUE) values('"
          << PName << "'," << ung <<"," << PracNo << "," << Type << ",'" << Key1 << "','" << Key2 << "','" << Value << "');";
      of << InsertSQLStmt.str() << std::endl;

    if(!m_SQLFilesOnly)
    {
      ptPrepStmt->setString(0, PName);
      ptPrepStmt->setInt(1, ung);
      ptPrepStmt->setInt(2, PracNo);
      ptPrepStmt->setInt(3, Type);
      ptPrepStmt->setString(4, Key1);
      ptPrepStmt->setString(5, Key2);
      ptPrepStmt->setString(6, Value);
      ptPrepStmt->executeUpdate();
    }
    }
    of.close();
    if(!m_SQLFilesOnly) m_pConnection->commit();
		m_pConnection->freeStatement(m_ptStmt);
    m_pConnection->freeStatement(ptPrepStmt);
  }
  catch (cCBS_DBExc_ConnectionError &e)
	{
    std::cerr << "cCBS_DBExc_ConnectionError caught in ConvertParamTable() while reading parameter " << PName << ", " << e.getText() << std::endl;
	}
	catch (cCBS_DBExc &e)
	{
    std::cerr << "cCBS_DBExc caught in ConvertParamTable() while reading parameter " << PName << ", " << e.getText() << std::endl;
	}
  catch(...)
  {
    std::cerr << "Unknown exception caught in ConvertParamTable() while reading parameter " << PName << std::endl;
  }
  return RetValue;
}
