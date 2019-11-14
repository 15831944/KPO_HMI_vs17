#include "TinyXml.h"
#include "string"

class CXML_TlgReader
{
public:
  CXML_TlgReader(void);
  ~CXML_TlgReader(void);
  std::string makeIDL(std::string FileName);
  void elemEvaluate( TiXmlNode* pParent, bool isModule);
  void structEvaluate( TiXmlNode* pParent, bool isModule );
  void findUserType(std::string DefName, bool isModule);
  std::string str;
protected:
  TiXmlDocument* doc;
};