#pragma once

#include <map>
#include <string>

#include "cCBS_Connection.h"
#include "CDateTime.h"

class CParamConverter
{
public:
  CParamConverter(void);
  virtual ~CParamConverter(void);
  long ConvertParamTable(void);
  long ConvertParamMatrixTable(void);
  const std::string& getSourceParamTableName() {return m_SourceParamTable;};
  const std::string& getSourceParamMatrixTableName() {return m_SourceParamMatrixTable;};
  const std::string& getDestinationParamTable() {return m_DestinationParamTable;};
  const std::string& getDestinationParamMatrixTable() {return m_DestinationParamMatrixTable;};
private:

  void initialize();
  CDateTime getDate(const std::string& ColName);
  void setDateTime(const CDateTime& value);

  std::map<std::string, int> m_UnitGroupNumbers;
  std::string m_SourceParamTable;
  std::string m_SourceParamMatrixTable;
  std::string m_DestinationParamTable;
  std::string m_DestinationParamMatrixTable;

  std::string m_OutputDir;
  bool m_SQLFilesOnly;

	cCBS_Statement  *m_ptStmt;
	cCBS_ResultSet  *m_ptRS;
  cCBS_Connection *m_pConnection;

};
