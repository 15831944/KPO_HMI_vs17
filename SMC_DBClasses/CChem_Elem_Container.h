// Copyright (C) 2004, 2005 SMS Demag AG, Germany 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CCHEM_ELEM_CONTAINER_440D8D1D0184_INCLUDED
#define _INC_CCHEM_ELEM_CONTAINER_440D8D1D0184_INCLUDED

#include <string>
#include "cCBS_Connection.h"
#include "cCBS_StdConnection.h"

//##ModelId=440D8D1D0184
class CChem_Elem_Container 
{
public:
	//##ModelId=440D8F580257
	virtual ~CChem_Elem_Container();

	//Return values:
	//false element is not a steel element
	//true element is a steel element
	//##ModelId=440D8F8000B0
	bool isSteelElem(std::string& elemName);

  CChem_Elem_Container(cCBS_Connection* Connection);

	CChem_Elem_Container(cCBS_StdConnection* Connection);

  void init();

	//Return values:
	//false element is not a slag element
	//
	//true element is a slag element
	//##ModelId=440DB367035F
  bool isSlagElem(std::string& elemName);

	//Return values:
	//false element is not an equivalence
	//
	//true element is an equivalence
	bool isEquivalence(std::string& elemName);

  bool isMeasScope(std::string& elemName, long MEASUREMENT_NAME_SCOPE);


protected:

private:
	//Container that contains ElementName as first value and 
	//steel/slag specification (1 if element is a steel 
	//element)
	//##ModelId=440D8E5F0367
	std::map<const std::string,long> m_Elements;

  cCBS_StdConnection *m_pCBS_StdConnection;

};

#endif /* _INC_CCHEM_ELEM_CONTAINER_440D8D1D0184_INCLUDED */
