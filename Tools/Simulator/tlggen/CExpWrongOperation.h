#ifndef _CExpWrongOperation_H_
#define _CExpWrongOperation_H_

#include "CBaseExp.h"

//##ModelId=4404D3B400AB
class CExpWrongOperation : public CBaseExp
{
	public:
	//##ModelId=4404D3B400AD
		CExpWrongOperation(const std::string& tlg,const std::string& elem,const std::string& eltyp,const std::string& optyp);
	//##ModelId=4404D3B400BD
		~CExpWrongOperation();
	//##ModelId=4404D3B400BE
		const std::string& getElemTyp();
	//##ModelId=4404D3B400BF
		const std::string& getOpTyp();
	private:
	//##ModelId=4404D3B400C1
		std::string ElemTyp;
	//##ModelId=4404D3B400CC
		std::string OperationTyp;
};
#endif
