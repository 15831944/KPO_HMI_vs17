// Copyright (C) 2004 SMS Demag AG, Germany 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGC_Charge_Dest_Container_424136530236_INCLUDED
#define _INC_CGC_Charge_Dest_Container_424136530236_INCLUDED

class CGC_CHARGE_DEST;

//##ModelId=424136530236
class CGC_Charge_Dest_Container 
{
private:
	//##ModelId=424A9FCC0048
	std::map< long, std::string > m_DestNameList;

public:
	//##ModelId=42413EC40201
	CGC_Charge_Dest_Container(cCBS_StdConnection * Connection, const std::string & Plant);

	//##ModelId=42413F1D0096
	std::string getDestNameByNo(const long & DestNo);

	//##ModelId=42413EC5025D
	virtual ~CGC_Charge_Dest_Container();

protected:
	//##ModelId=424136A5036A
	CGC_CHARGE_DEST* m_pCGC_CHARGE_DEST;

};

#endif /* _INC_CGC_Charge_Dest_Container_424136530236_INCLUDED */
