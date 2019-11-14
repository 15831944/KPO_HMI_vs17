// Copyright (C) 2007 SMS Demag AG

#include <sstream>
#include "CTelcom_TlgExpert.h"
#include "tam.h"
#include "cCBS_StdLog_Task.h"
#include "CTelcom_MsgTypeTranslator.h"



//##ModelId=45AB953A00CF
CTelcom_TlgExpert::CTelcom_TlgExpert(CTelcom_MsgTypeTranslator *TypeTransl)
{
  m_pMsgTypeTranslator = TypeTransl;
}

//##ModelId=45AB953A0358
CTelcom_TlgExpert::~CTelcom_TlgExpert()
{
	// ToDo: Add your specialized code here and/or call the base class
}

//##ModelId=45AB9BC50063
const string CTelcom_TlgExpert::getTlgType()
{
	// Telegram Type is defined under 'typeItem' in ini file
  // here we look for typeItem  defined as string

  std::string typ;
  
  Tlg * tlg = getCurrHeaderTlg();
  std::string typeItem = getTypeItem();
  
  // We need to see whether the TypeItem is a single Telegram Element
  // or if it is hidden within a compound.
  
  if( tlg->hasElem(typeItem) )        // type is simple TelegramElement
  {
    int t = 0;
    int elem_t = (*tlg)[typeItem].getType(); // depends on type element we read the value
    if (elem_t == TlgElem::tInteger)
    {
      t = (*tlg)[typeItem].asInteger();
      typ = translateType(t);
    }
    else // string element
      typ = (*tlg)[typeItem].asString();

    if (typ.empty())
    {
      std::stringstream mes;
      mes << "CTELCOM_TlgExpert:cannot convert message type: ";
      mes << t;
      cCBS_StdLog_Task::getInstance()->log(mes.str(), 1);
    }
  }
  else                                  // type item is within a compound 
  {
    // go deeper into Telegram structure.
    std::string mes;
    mes = "INFO: Scan for type item: " + typeItem;
    cCBS_StdLog_Task::getInstance()->log(mes, 2);
    typ = scanForType(tlg->getRoot(), typeItem);
    if (typ.empty())
    {
      mes = "ERROR: Telegram doesn't have type item: " + typeItem;
      cCBS_StdLog_Task::getInstance()->log(mes, 1);
    }
  }
  return typ;
}

//##ModelId=45AB9BD202BF
std::string CTelcom_TlgExpert::translateType(unsigned int _t)
{
  return m_pMsgTypeTranslator->translate(_t);
}

//##ModelId=45AB9BC50081
std::string CTelcom_TlgExpert::scanForType(TlgElem& tlgElem, const std::string& type)
{
  // Loop all Telegram Elements, until type is found or the end is reached,

  std::string retType = "";

  if( tlgElem.hasElem (type) )
  {
    retType = tlgElem[type].asString();

    int t = 0;
    int elem_t = tlgElem[type].getType(); // depends on type element we read the value
    if (elem_t == TlgElem::tInteger)
    {
      t = tlgElem[type].asInteger();
      retType = translateType(t);
    }
    else // string element
      retType = tlgElem[type].asString();

  }
  else
  {
    for (int ii=0; ii<tlgElem.countElems(); ii++)
    {
      retType = scanForType (tlgElem[ii], type) ;     
      if (retType != std::string (""))
        break;
    }
  }
  return retType;
}

