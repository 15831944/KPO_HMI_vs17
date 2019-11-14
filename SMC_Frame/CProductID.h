#ifndef _INC_CPRODUCTID_INCLUDED
#define _INC_CPRODUCTID_INCLUDED

#include <string>

class CProductID
{
private:
  static std::string m_QualifierSeparator;

public:

	std::string getHeatID(const std::string& ProductID);

	std::string getTreatID(const std::string& ProductID);

	std::string getProductID(const std::string& HeatID, const std::string& TreatID);

};

#endif
