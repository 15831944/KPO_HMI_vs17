// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CINTFDATAELEMENT_4067E7210287_INCLUDED
#define _INC_CINTFDATAELEMENT_4067E7210287_INCLUDED

#include <vector>
#include <set>

class CIntfData;
class CIntfDataBuffer;

//##ModelId=4067E7210287
class CIntfDataElement 
{
public:
	//##ModelId=418F95AC00E7
	CIntfData* findData(const std::string& Type, const std::string& Name);

  void setRequestedName(const std::string& Name);

	//##ModelId=41496A6302F6
	 bool getPersistent() ;

	//##ModelId=4149688D001C
	void setPersistent(bool value);

	//##ModelId=41371FE003A8
	void setCompleted(bool value);

	//##ModelId=41371FE003B2
	bool getCompleted();

  //##ModelId=40BF15B600E9
  std::vector<CIntfData*>  getIntfDataList();

	//##ModelId=40B70F7500D8
	long deleteData(const std::string  & Name);

	//##ModelId=40B70A170394
	CIntfDataElement( CIntfDataBuffer  * DataBuffer, const std::string &Key);

	//##ModelId=40B6FFB80138
	void log(const std::string  & Message, long Level);

	//##ModelId=40B6F4B00028
	CIntfData* findData(const std::string & Name);

	//##ModelId=40B6F4B0003C
	bool insertData(const std::string & Name, CIntfData *pIntfData);

	//##ModelId=40B6F7370155
	long eraseIntfDataList(   );

	//##ModelId=44FE999A01AE
  bool deleteIntfData();

	//##ModelId=40B6F5C001A6
	virtual ~CIntfDataElement();

	//##ModelId=40B6F61700E3
	const std::string&  getKey();

	//##ModelId=44FE999A01C2
  bool isUpdated(const std::string Name);

  std::set<std::string> getIntfReqList();
  bool isRequested(const std::string Name);

protected:
	//##ModelId=407FAE240319
	std::string  m_Key;

private:
	//##ModelId=42315BF60032
	CIntfDataBuffer* m_pDataBuffer;

	//##ModelId=414968540200
	bool is_Persistent;

	//##ModelId=41371FD601AF
	bool is_Completed;

	//##ModelId=40B6F44000DC
	std::vector<CIntfData*>   m_IntfDataList;
  std::set<std::string>     m_IntfReqList;

};

#endif /* _INC_CINTFDATAELEMENT_4067E7210287_INCLUDED */
