
#include "CExpWrongOperation.h"

//-----------------------------------------------------------------------
//##ModelId=4404D3B400AD
CExpWrongOperation::CExpWrongOperation(const std::string& tlg,const std::string& elem,const std::string& eltyp,const std::string& optyp):
CBaseExp(tlg,elem)
{
	this->ElemTyp=eltyp;
	this->OperationTyp=optyp;
}
//-------------------------------------------------------------------
//##ModelId=4404D3B400BD
CExpWrongOperation::~CExpWrongOperation()
{
}
//--------------------------------------------------------------------
//##ModelId=4404D3B400BE
const std::string& CExpWrongOperation::getElemTyp()
{
	return this->ElemTyp;
}
//--------------------------------------------------------------------
//##ModelId=4404D3B400BF
const std::string& CExpWrongOperation::getOpTyp()
{
	return this->OperationTyp;
}
//--------------------------------------------------------------------
