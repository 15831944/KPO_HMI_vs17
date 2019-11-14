// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CINTFDATABUFFER_4067E66601E0_INCLUDED
#define _INC_CINTFDATABUFFER_4067E66601E0_INCLUDED

#include <vector>
#include <string>

class CIntfDataElement;
class CData_Provider;

//##ModelId=4067E66601E0
class CIntfDataBuffer 
{
protected:
	//##ModelId=4149B97B00AC
	CData_Provider* m_pData_Provider;

	//##ModelId=40B712640348
	long m_KeyCounter;

public:
	//##ModelId=42E764680078
	CData_Provider* getpData_Provider();

	//##ModelId=429370F5013C
	void EventLogValidationFailure(const std::string& Message);

	//##ModelId=414EC21302A2
	long getIntfDataElementListLength();

	//##ModelId=414EC25B0285
	std::string  findKey(long Index);

	//##ModelId=4149BA2B000E
	void setpData_Provider(CData_Provider* value);

	//##ModelId=41496991021C
	void checkIntfDataElementList();

	//##ModelId=41371F5B01DA
	void setCompleted(const std::string & Key);

  //##ModelId=40D6CE8302E8
  void showContent(const std::string& Key, long Level);

	//##ModelId=40B747C401E3
	 CIntfDataElement* getLastIntfDataElement() ;

	//##ModelId=40B747C5022D
	void setLastIntfDataElement(CIntfDataElement* value);

	//##ModelId=40B7127E0397
	void generateKey(std::string& Key);

	//##ModelId=40B6FFB40286
	void log(const std::string & Message, long Level);

	//##ModelId=406AE1EB00D6
	CIntfDataElement* findElement(const std::string& Key);

	//##ModelId=406AE3520276
	CIntfDataElement* insertElement(const std::string& Key);

	//##ModelId=407D08D403C6
	virtual ~CIntfDataBuffer();

	//##ModelId=407D08D50199
	CIntfDataBuffer( );

	//##ModelId=407FAEFC02F1
  void setBufferSize(long value);

  std::vector<CIntfDataElement*>  getIntfDataElementList();

private:
	//##ModelId=40B7421C0175
	CIntfDataElement* m_LastIntfDataElement;

	//##ModelId=4067E7B90129
  std::vector<CIntfDataElement*> m_IntfDataElementList;

	//##ModelId=407FAE6B0232
	long m_IntfDataElementListMaxSize;

	//##ModelId=4067E7F9039D
	long deleteElement(const std::string& Key);

};

#endif /* _INC_CINTFDATABUFFER_4067E66601E0_INCLUDED */
